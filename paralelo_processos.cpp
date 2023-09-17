#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cmath>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

// Função para multiplicação de matrizes por uma parte
vector<vector<int>> multiplyMatrixPart(const vector<vector<int>>& A, const vector<vector<int>>& B,
                                       int start_row, int end_row) {
    int n = A.size();
    int m = B[0].size();
    int common = A[0].size();
    vector<vector<int>> result(end_row - start_row, vector<int>(m, 0));

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < common; ++k) {
                result[i - start_row][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

// Função para salvar uma matriz em um arquivo com o tempo de cálculo
void saveMatrixWithTime(const vector<vector<int>>& matrix, const string& filename, double calculation_time) {
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

    file << "Tempo de cálculo: " << calculation_time << " segundos" << endl;

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " M1.txt M2.txt P output_prefix" << endl;
        return 1;
    }

    string input_file1 = argv[1];
    string input_file2 = argv[2];
    int P = atoi(argv[3]);
    string output_prefix = argv[4];

    vector<vector<int>> M1, M2;
    vector<ofstream> output_files;

    // Carregue as matrizes M1 e M2
    // Certifique-se de que os arquivos de entrada existam e leia-os aqui

    // Inicialize os arquivos de saída
    for (int i = 0; i < P; ++i) {
        output_files.emplace_back(output_prefix + to_string(i) + ".txt");
        output_files[i] << M1.size() << " " << M2[0].size() << endl;
    }

    int rows_per_process = ceil(static_cast<double>(M1.size()) / P);
    vector<chrono::duration<double>> process_times(P);

    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < P; ++i) {
        int start_row = i * rows_per_process;
        int end_row = min((i + 1) * rows_per_process, static_cast<int>(M1.size()));

        pid_t pid = fork();

        if (pid == 0) { // Processo filho
            auto process_start_time = chrono::high_resolution_clock::now();
            vector<vector<int>> result = multiplyMatrixPart(M1, M2, start_row, end_row);
            auto process_end_time = chrono::high_resolution_clock::now();
            chrono::duration<double> process_execution_time = process_end_time - process_start_time;

            saveMatrixWithTime(result, output_prefix + to_string(i) + ".txt", process_execution_time.count());

            exit(0);
        }
    }

    // Aguarde todos os processos filhos terminarem
    for (int i = 0; i < P; ++i) {
        wait(nullptr);
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> total_execution_time = end_time - start_time;

    cout << "Tempo total de cálculo: " << total_execution_time.count() << " segundos" << endl;

    return 0;
}
