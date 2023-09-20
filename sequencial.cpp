#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;
vector<vector<int>> multiplicarMatrizes(vector<vector<int>> &M1, vector<vector<int>> &M2)
{
    int linhas1 = M1.size();
    int colunas1 = M1[0].size();
    int linhas2 = M2.size();
    int colunas2 = M2[0].size();

    vector<vector<int>> resultado(linhas1, vector<int>(colunas2, 0));

    for (int i = 0; i < linhas1; i++)
    {
        for (int j = 0; j < colunas2; j++)
        {
            for (int k = 0; k < colunas1; k++)
            {
                resultado[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    return resultado;
}

int main(int argc, char *argv[])
{
    // pegando o nome dos arquivos do terminal
    string arquivo_M1 = argv[1];
    string arquivo_M2 = argv[2];
    //
    fstream arquivo1(arquivo_M1);
    fstream arquivo2(arquivo_M2);
    fstream resultado;
    resultado.open("resultado.txt", ios::out | ios::app);

    int linha_m1, linha_m2, coluna_m1, coluna_m2;

    // lendo o arquivo
    arquivo1 >> linha_m1 >> coluna_m1;
    vector<vector<int>> Matrix1(linha_m1, vector<int>(coluna_m1));
    arquivo2 >> linha_m2 >> coluna_m2;
    vector<vector<int>> Matrix2(linha_m2, vector<int>(coluna_m2));

    // pegando dados dos arquivos e colocando nos respectivos vector
    for (int i = 0; i < linha_m1; ++i)
    {
        for (int j = 0; j < coluna_m1; ++j)
        {
            arquivo1 >> Matrix1[i][j];
        }
    }

    for (int i = 0; i < linha_m2; ++i)
    {
        for (int j = 0; j < coluna_m2; ++j)
        {
            arquivo2 >> Matrix2[i][j];
        }
    }

    arquivo1.close();
    arquivo2.close();
    auto start = std::chrono::high_resolution_clock::now();
    vector<vector<int>> Resultado = multiplicarMatrizes(Matrix1, Matrix2);
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = end - start;
    double tempo_decorrido_milissegundos = elapsed.count();
    cout << setprecision(2) << "Tempo decorrido: " << tempo_decorrido_milissegundos << " milissegundos" << std::endl;
    resultado << tempo_decorrido_milissegundos << "m/s";

    return 0;
}