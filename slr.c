#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stack>
#include "tabela_slr.h"

using namespace std;

void slr(string fitaString) {
    stack<int> pilha;
    pilha.push(0);

    // converte string em fita
    stringstream ss(fitaString);
    string token;
    while (ss >> token) {
        fita.push_back(token);
    }

    vector<tuple<int, int>> producoes = getProducoes();
    while (1) {
        int estado = pilha.top();
        char simbolo = fitaString[0];

        if (get<0>(tabela[estado][simbolo]) == 'E') {
            int estado = get<1>(tabela[estado][simbolo]);
            pilha.push(simbolo);
            pilha.push(estado); // 0 -> 0 13 2
            continue;
        }

        if (get<0>(tabela[estado][simbolo]) == 'R') {
            int reduzProducao = get<1>(tabela[estado][simbolo]); // 2
            tuple<int, int> producao = producoes[reduzProducao]; // idProd - tamanho
            
            // remove simbolos * 2 elementos da pilha
            int tamanho = get<1>(producao) * 2;
            for (int i = 0; i < tamanho; i++) {
                pilha.pop();
            }

            // faz a operacao 0 -> 0 T -> 0 T 2 por exemplo:
            estado = pilha.top();
            cabecaProducao = get<0>(producao);
            pilha.push(cabecaProducao);
            pilha.push(tabela[estado][cabecaProducao]);

            continue;
        }

        if (get<0>(tabela[estado][simbolo]) == 'A') {
            printf("Aceito\n");
            return;
        }

        if (get<0>(tabela[estado][simbolo]) == '\0') {
            printf("Rejeitado na etapa léxica\n");
            return;
        } 

    }
}