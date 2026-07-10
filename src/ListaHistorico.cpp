#include "ListaHistorico.h"
#include <iostream>
using namespace std;

ListaHistorico::ListaHistorico() : inicio(nullptr), fim(nullptr), tamanho(0) {}

ListaHistorico::~ListaHistorico() {
    limpar();
}

void ListaHistorico::inserirOrdenado(Conteudo* c) {
    NoDuplo* novoNo = new NoDuplo(c);
    
    // Lista vazia
    if (inicio == nullptr) {
        inicio = fim = novoNo;
        tamanho++;
        return;
    }
    
    // Comparar por número de visualizações (DECRESCENTE)
    if (inicio->conteudo->getNumVisualizacoes() < c->getNumVisualizacoes()) {
        // Insere no início
        novoNo->proximo = inicio;
        inicio->anterior = novoNo;
        inicio = novoNo;
    } else {
        // Percorre até encontrar a posição correta
        NoDuplo* atual = inicio;
        while (atual->proximo != nullptr && 
               atual->proximo->conteudo->getNumVisualizacoes() >= c->getNumVisualizacoes()) {
            atual = atual->proximo;
        }
        
        // Insere na posição correta
        novoNo->proximo = atual->proximo;
        novoNo->anterior = atual;
        
        if (atual->proximo != nullptr) {
            atual->proximo->anterior = novoNo;
        } else {
            fim = novoNo;  // Atualiza fim se inseriu no final
        }
        
        atual->proximo = novoNo;
    }
    
    tamanho++;
}