#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) {
  int linha_m1 = atoi(argv[1]);
  int coluna_m1 = atoi(argv[2]);
  int linha_m2 = atoi(argv[3]);
  int coluna_m2 = atoi(argv[4]);
  fstream m1;
  m1.open("matrix1.txt", ios::out | ios::app);
  fstream m2;
  m2.open("matrix2.txt", ios::out | ios::app);
  srand(time(0));

    // Criação e inicialização das matrizes
    vector<vector<int>> M1(linha_m1, vector<int>(coluna_m1));
    vector<vector<int>> M2(linha_m2, vector<int>(coluna_m2));
    //gerando numeros aleotorios
    for(int i = 0; i < linha_m1; i++){
        for(int j = 0; j < coluna_m1; j++){
            M1[i][j] = rand() % 10;
        }
    }

    if(m1.is_open()){
      for (int i = 0; i < linha_m1; ++i) {
        for (int j = 0; j < coluna_m1; ++j) {
            m1 << M1[i][j] << " ";
        }
        m1 << "\n"; // Nova linha para cada nova linha da matriz
    }
    }
    m1.close();


    for(int i = 0; i < linha_m2; i++){
        for(int j = 0; j < coluna_m2; j++){
            M2[i][j] = rand() % 10;
        }
    }
   
     if(m2.is_open()){
      for (int i = 0; i < linha_m2; ++i) {
        for (int j = 0; j < coluna_m2; ++j) {
            m2 << M2[i][j] << " ";       
        }
        m2 << "\n";
     // Nova linha para cada nova linha da matri
    }
    }
    m2.close();
  return 0;
}