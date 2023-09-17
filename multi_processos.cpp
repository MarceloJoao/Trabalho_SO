#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
using namespace std;

void multiplicar_segmento(std::vector<std::vector<int>>& M1, std::vector<std::vector<int>>& M2, 
std::vector<std::vector<int>>& resultado, int inicio, int fim) {
    int n = M1.size();
    int m = M2[0].size();
    int p = M2.size();

    for (int i = inicio; i < fim; i++) {
        for (int j = 0; j < m; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < p; k++) {
                resultado[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}
int main(int argc, char *argv[]){
string arquivo_M1 = argv[1];
string arquivo_M2 = argv[2];
int P = atoi(argv[3]); 

for(int i=0; i < P; i++){
  pid_t pid = fork();

  if(pid == 0){
    
  }
}


 return 0;
}