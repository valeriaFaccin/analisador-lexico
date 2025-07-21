#include "transicoes.h"
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <iostream>
#include <sstream>
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
    vector<tuple<vector<string>, string>> tabelafita;
    int i = 0;

    cout << "\033[1mStarting lexical analysis\033[0m" << endl << endl;
    while(getline(cin, buffer)){
        // Separa a string por espaços
        stringstream ss(buffer);
        string palavra;
        vector<string> palavras;
        while(ss >> palavra) {
            palavras.push_back(palavra);
        }
        if(palavras.size()){
            tabelafita.push_back(make_tuple(palavras, geraFita(buffer, finais)));
        }
        fita += get<1>(tabelafita[i]);
        i++;
    }
    fita += " 36";
    
    // Mostra as linhas e seus tokens
    for (int j = 0; j < tabelafita.size(); j++) {
        vector<string> palavras = get<0>(tabelafita[j]);
        string tokens = get<1>(tabelafita[j]);
        
        cout << j << " L: [";
        for(int k = 0; k < palavras.size(); k++) {
            if(k > 0) cout << ", ";
            cout << palavras[k];
        }
        cout << "] tokens: " << tokens << endl;
    }

    cout << endl << "fita: " << fita << endl;

    // Verifica se existe algum token de erro (31) na fita
    if (fita.find(" 31") != string::npos) {
        cout << endl << "\033[1;31mError: Failed lexical analysis\033[0m" << endl;
        return 1;
    }

    cout << endl << "\033[1;32mPassed lexical analysis\033[0m" << endl << endl;

    cout << "\033[1mStarting syntax analysis\033[0m" << endl << endl;
    slr(fita, tabelafita);
}

 