#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std;

void readMatrixFromFile(const char* filename, vector<vector<int>>& matrix) {
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

void writeMatrixToFile(const char* filename, const vector<vector<int>>& matrix) {
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

void multiplyMatricesSegment(const vector<vector<int>>& A, const vector<vector<int>>& B,
                             vector<vector<int>>& result, int start, int end) {
    int n = A.size();
    int m = B[0].size();
    int common = A[0].size();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < common; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " M1.txt M2.txt P" << endl;
        return 1;
    }

    vector<vector<int>> M1, M2;
    readMatrixFromFile(argv[1], M1);
    readMatrixFromFile(argv[2], M2);

    int P = atoi(argv[3]);
    int n = M1.size();
    int m = M2[0].size();
    vector<vector<int>> result(n, vector<int>(m, 0));

    vector<thread> threads;
    int rows_per_thread = n / P;

    auto start_time = chrono::high_resolution_clock::now();
    for (int i = 0; i < P; ++i) {
        int start = i * rows_per_thread;
        int end = (i < P - 1) ? (i + 1) * rows_per_thread : n;
        threads.emplace_back(multiplyMatricesSegment, ref(M1), ref(M2), ref(result), start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> execution_time = end_time - start_time;

    writeMatrixToFile("result_threaded.txt", result);

    ofstream time_file("time_threaded.txt");
    time_file << execution_time.count() << endl;
    time_file.close();

    return 0;
}
