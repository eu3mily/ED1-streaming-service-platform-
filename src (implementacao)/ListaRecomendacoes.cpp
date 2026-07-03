#include "../include (arquivos header)/ListaRecomendacoes.h"
#include <iostream>

ListaRecomendacoes::ListaRecomendacoes() : inicio(nullptr), tamanho(0) {}

ListaRecomendacoes::~ListaRecomendacoes() {
    limpar();
}

void ListaRecomendacoes::inserirOrdenado(Conteudo* c) {
    NoSimples* novoNo = new NoSimples(c);
    
    if (inicio == nullptr) {
        inicio = novoNo;
    } else if (inicio->conteudo->getNome() > c->getNome()) {
        novoNo->proximo = inicio;
        inicio = novoNo;
    } else {
        NoSimples* atual = inicio;
        while (atual->proximo != nullptr && 
               atual->proximo->conteudo->getNome() < c->getNome()) {
            atual = atual->proximo;
        }
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
    }
    tamanho++;
}

void ListaRecomendacoes::imprimirLista() const {
    cout << "\n=== RECOMENDAÇÕES ===" << endl;
    NoSimples* atual = inicio;
    int numero = 1;
    while (atual != nullptr) {
        cout << numero++ << ". ";
        atual->conteudo->exibir();
        atual = atual->proximo;
    }
    cout << endl;
}

NoSimples* ListaRecomendacoes::getInicio() const {
    return inicio;
}

int ListaRecomendacoes::getTamanho() const {
    return tamanho;
}

void ListaRecomendacoes::limpar() {
    NoSimples* atual = inicio;
    while (atual != nullptr) {
        NoSimples* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    inicio = nullptr;
    tamanho = 0;
}