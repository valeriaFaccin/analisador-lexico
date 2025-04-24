#include "transicoes.h"
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <iostream>

using namespace std;

string geraFita(string buffer, set<int> finais){
    string fita = "";
    int y, estado = 0;
    for (int i = 0; buffer[i]; i++){
        y = estado;

        if(transicoes[estado].find(buffer[i]) != transicoes[estado].end()) 
            estado = transicoes[estado][buffer[i]];
        else if (estado != 36)
            estado = -1;

        if(estado != -1) continue;
        
        if (finais.find(y) != finais.end()){
            fita += " " + to_string(y);
            estado = 0;
            i--;
            continue;
        }

        estado = 36;
    }

    if (estado) 
        if (finais.find(estado) != finais.end()) 
            fita += " " + to_string(estado);
        else 
            fita += " 36";

    return fita;
}

int main(){
    set<int> finais = {1, 2, 7, 8, 10, 11, 13, 14, 21, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36};
    string buffer, fita = "";
    vector<vector<string>> tabelafita(2);
    int i = 0;
    while(getline(cin, buffer)){
        tabelafita[0].push_back(buffer);
        tabelafita[1].push_back(geraFita(buffer, finais));
        fita += tabelafita[1][i];
        i++;
    }
    for (int j = 0; j < tabelafita[0].size(); j++) 
        cout << j << " L: " << tabelafita[0][j] << " tokens: " << tabelafita[1][j] << endl;

    cout << fita << endl;
}

 