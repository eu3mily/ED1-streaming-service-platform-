#ifndef LISTARECOMENDACOES_H
#define LISTARECOMENDACOES_H

#include "NoLista.h"

class ListaRecomendacoes {
private:
    NoSimples* inicio;
    int tamanho;

public:
    ListaRecomendacoes();
    ~ListaRecomendacoes();
    
    void inserirOrdenado(Conteudo* c);  // Por nome alfabético
    void imprimirLista() const;
    NoSimples* getInicio() const;
    int getTamanho() const;
    void limpar();
};

#endif