#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
vector<vector<int>> multiplicarMatrizes(vector<vector<int>>& M1, vector<vector<int>>& M2) {
    int linhas1 = M1.size();
    int colunas1 = M1[0].size();
    int linhas2 = M2.size();
    int colunas2 = M2[0].size();

  vector<vector<int>> resultado(linhas1, vector<int>(colunas2, 0));

    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas2; j++) {
            for (int k = 0; k < colunas1; k++) {
                resultado[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    return resultado;
}

int main(int argc, char *argv[]) {
//pegando o nome dos arquivos do terminal
string arquivo_M1 = argv[1];
string arquivo_M2 = argv[2];
//
fstream arquivo1(arquivo_M1);
fstream arquivo2(arquivo_M2);
fstream resultado;
resultado.open("resultado.txt", ios::out | ios::app);

int linha_m1, linha_m2, coluna_m1, coluna_m2;

//lendo o arquivo
arquivo1 >> linha_m1 >> coluna_m1;
vector<vector<int>> Matrix1(linha_m1, vector<int>(coluna_m1));
arquivo2 >> linha_m2 >> coluna_m2;
vector<vector<int>> Matrix2(linha_m2, vector<int>(coluna_m2));


//pegando dados dos arquivos e colocando nos respectivos vector
    for (int i = 0; i < linha_m1; ++i) {
        for (int j = 0; j < coluna_m1; ++j) {
            arquivo1 >> Matrix1[i][j];
        }
    }

    for (int i = 0; i < linha_m2; ++i) {
        for (int j = 0; j < coluna_m2; ++j) {
            arquivo2 >> Matrix2[i][j];
        }
    }

    arquivo1.close();
    arquivo2.close();
    //tempo quando começa o calculo
   auto start = chrono::steady_clock::now();
   vector<vector<int>> Resultado = multiplicarMatrizes(Matrix1, Matrix2);
   //tempo quando termina o calculo
   auto end = chrono::steady_clock::now();
   // diferença entre fim e inicio
   auto diff = end - start;
   auto tempo_decorrido_ms = chrono::duration <double, milli> (diff).count();
  cout << "tempo foi: " << tempo_decorrido_ms;
  if (resultado.is_open()) {
        for (int i = 0; i < Resultado.size(); i++) {
            for (int j = 0; j < Resultado[i].size(); j++) {
                resultado << Resultado[i][j] << " ";
            }
            resultado << endl;
        }
     }
 return 0;
 }