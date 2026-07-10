#ifndef LISTARECOMENDACOES_H
#define LISTARECOMENDACOES_H

#include "NoLista.h"

class ListaRecomendacoes { // é uma lista simples
private:
    NoSimples* inicio;
    int tamanho;

public:
    ListaRecomendacoes();
    ~ListaRecomendacoes();
    
        //metodos adicionais
    void inserirOrdenado(Conteudo* c);  // por ordem alfabetica
    void imprimirLista() const;
    NoSimples* getInicio() const;
    int getTamanho() const;
    void limpar();
};

#endif