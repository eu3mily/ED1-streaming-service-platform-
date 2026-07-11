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

void ListaHistorico::atualizarPosicao(Conteudo* c) {
    if (inicio == nullptr) return;

    NoDuplo* atual = inicio;
    
    // Passo 1: Procura o nó que guarda este conteúdo na lista
    while (atual != nullptr && atual->conteudo != c) {
        atual = atual->proximo;
    }

    // Se não achou na lista (ex: primeira vez assistindo), apenas insere
    if (atual == nullptr) {
        inserirOrdenado(c);
        return;
    }

    // Se achou, mas a lista só tem 1 elemento, não há o que reordenar
    if (tamanho == 1) return;

    // Passo 2: Desconecta o nó da posição atual para removê-lo
    if (atual == inicio) {
        inicio = atual->proximo;
        if (inicio != nullptr) inicio->anterior = nullptr;
    } else if (atual == fim) {
        fim = atual->anterior;
        if (fim != nullptr) fim->proximo = nullptr;
    } else {
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
    }

    tamanho--;
    delete atual; // Deleta apenas o nó antigo (o conteúdo segue intacto)

    // Passo 3: Reinsere o conteúdo. Como a visualização dele já aumentou
    // no SistemaStreaming, ele vai cair na posição correta do ranking.
    inserirOrdenado(c);
}

void ListaHistorico::imprimirTopAssistidos() const {
    cout << "\n=== HISTÓRICO DE MAIS ASSISTIDOS ===" << endl;
    if (inicio == nullptr) {
        cout << "Nenhum conteúdo foi assistido ainda!" << endl;
        return;
    }

    NoDuplo* atual = inicio;
    int posicao = 1;
    while (atual != nullptr) {
        cout << posicao++ << "º Lugar - ";
        atual->conteudo->exibir();
        atual = atual->proximo;
    }
}

NoDuplo* ListaHistorico::getInicio() const {
    return inicio;
}

int ListaHistorico::getTamanho() const {
    return tamanho;
}

void ListaHistorico::limpar() {
    NoDuplo* atual = inicio;
    while (atual != nullptr) {
        NoDuplo* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}