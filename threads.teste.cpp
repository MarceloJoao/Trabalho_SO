#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

// Função para ler uma matriz de um arquivo
void readMatrixFromFile(const char *filename, vector<vector<int>> &matrix) {
  ifstream file(filename);
  int rows, cols;
  file >> rows >> cols;
  matrix.resize(rows, vector<int>(cols));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      file >> matrix[i][j];
    }
  }

  file.close();
}

// Função para escrever uma matriz em um arquivo
void writeMatrixToFile(const char *filename,
                       const vector<vector<int>> &matrix) {
  ofstream file(filename);
  int rows = matrix.size();
  int cols = matrix[0].size();

  file << rows << " " << cols << endl;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      file << matrix[i][j] << " ";
    }
    file << endl;
  }

  file.close();
}

// Função para multiplicação de matrizes em uma faixa específica
void multiplyMatrices(const vector<vector<int>> &A,
                      const vector<vector<int>> &B, vector<vector<int>> &result,
                      int start, int end, mutex &mtx) {
  int n = A.size();
  int m = B[0].size();
  int common = A[0].size();

  for (int i = start; i < end; ++i) {
    for (int j = 0; j < m; ++j) {
      result[i][j] = 0; // Inicialize a célula da matriz de resultados
      for (int k = 0; k < common; ++k) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  // Bloqueie o mutex antes de acessar a seção crítica
  lock_guard<mutex> lock(mtx);
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    cout << "Usage: " << argv[0] << " M1.txt M2.txt P output.txt" << endl;
    return 1;
  }

  vector<vector<int>> M1, M2;
  readMatrixFromFile(argv[1], M1);
  readMatrixFromFile(argv[2], M2);

  int P = atoi(argv[3]);
  int n = M1.size();
  int m = M2[0].size();
  int common = M1[0].size();

  if (common != M2.size()) {
    cerr << "Erro: Dimensões das matrizes incompatíveis. O número de colunas de M1 deve ser igual ao número de linhas de M2." << endl;
    return 1;
  }

  vector<vector<int>> result(n, vector<int>(m, 0));

  vector<thread> threads;
  int rows_per_thread = n / P;
  int remaining_rows = n % P;
  int start = 0;

  mutex mtx; // Mutex para sincronização

  auto start_time = chrono::high_resolution_clock::now();
  for (int i = 0; i < P; ++i) {
    int end = start + rows_per_thread + (i < remaining_rows ? 1 : 0);
    cout << "Thread " << i << ": start = " << start << ", end = " << end << endl;
    threads.emplace_back(multiplyMatrices, ref(M1), ref(M2), ref(result), start, end, ref(mtx));
    start = end;
  }

  for (auto &thread : threads) {
    thread.join();
  }
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double> execution_time = end_time - start_time;

  writeMatrixToFile(argv[4], result);

  ofstream time_file("time_threaded.txt");
  time_file << execution_time.count() << " seconds" << endl;
  time_file.close();

  return 0;
}
