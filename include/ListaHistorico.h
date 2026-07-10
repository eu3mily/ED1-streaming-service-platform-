
#ifndef LISTAHISTORICO_H
#define LISTAHISTORICO_H

#include "NoLista.h"

class ListaHistorico { // é uma lista dupla
private:
    NoDuplo* inicio;  
    NoDuplo* fim;     
    int tamanho;

public:
    ListaHistorico();
    ~ListaHistorico();
    
    // ordenado por VISUALIZAÇÕES = DECRESCENTE
    void inserirOrdenado(Conteudo* c);
    
    // metodo de atualizar posição quando o conteúdo é assistido
    void atualizarPosicao(Conteudo* c);
    
    // metodos adicionais
    void imprimirTopAssistidos() const;
    NoDuplo* getInicio() const;
    int getTamanho() const;
    void limpar();
};

#endif