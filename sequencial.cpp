#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
//pegando o nome dos arquivos do terminal
string arquivo_M1 = argv[1];
string arquivo_M2 = argv[2];
//
fstream arquivo1(arquivo_M1);
fstream arquivo2(arquivo_M2);

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


 return 0;
 }