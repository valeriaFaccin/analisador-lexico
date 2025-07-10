#include "transicoes.h"
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <iostream>
#include "slr.h"
#include "tabela_slr.h"

using namespace std;

string geraFita(string buffer, set<int> finais){
    set<int> separadores = {' ', '\n', '\t', '\r', '\v', '\f'};
    string fita = "";
    int y, estado = 0;
    for (int i = 0; buffer[i]; i++){
        y = estado;
        if (separadores.find(buffer[i]) != separadores.end()) {
            if (!estado) continue;

            estado = 0;
            if (finais.find(y) != finais.end()){
                fita += " " + to_string(y);
                continue;
            } 

            fita += " 31";
            continue;
        }

        if(transicoes[estado].find(buffer[i]) != transicoes[estado].end()) 
            estado = transicoes[estado][buffer[i]];
        else
            estado = 31;

        
       
    }

    if (estado) 
        if (finais.find(estado) != finais.end()) 
            fita += " " + to_string(estado);
        else 
            fita += " 31";

    return fita;
}

int main(){
    inicializaTransicoes();
    set<int> finais = {
        1, 2, 7, 8, 10, 11, 13, 14, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };
    string buffer, fita = "";
    vector<vector<string>> tabelafita(2);
    int i = 0;

    cout << "\033[1mIniciando etapa léxica\033[0m" << endl << endl;
    while(getline(cin, buffer)){
        tabelafita[0].push_back(buffer);
        tabelafita[1].push_back(geraFita(buffer, finais));
        fita += tabelafita[1][i];
        i++;
    }
    fita += " 36";
    for (int j = 0; j < tabelafita[0].size(); j++) 
        cout << j << " L: " << tabelafita[0][j] << " tokens: " << tabelafita[1][j] << endl;

    cout << endl << "fita: " << fita << endl;

    // Verifica se existe algum token de erro (31) na fita
    if (fita.find(" 31") != string::npos) {
        cout << endl << "\033[1;31mErro: Código reprovou na etapa léxica\033[0m" << endl;
        return 1;
    }

    cout << endl << "\033[1;32mPassou etapa léxica\033[0m" << endl << endl;

    cout << "\033[1mIniciando etapa sintática\033[0m" << endl << endl;
    slr(fita);
}

 