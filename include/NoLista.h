#ifndef NOLISTA_H
#define NOLISTA_H

#include "Conteudo.h"

// no para lista simplesmente encadeada
struct NoSimples {
    Conteudo* conteudo;
    NoSimples* proximo;
    
    NoSimples(Conteudo* c) : conteudo(c), proximo(nullptr) {}
};

// no para lista duplamente encadeada
struct NoDuplo {
    Conteudo* conteudo;
    NoDuplo* proximo;
    NoDuplo* anterior;
    
    NoDuplo(Conteudo* c) : conteudo(c), proximo(nullptr), anterior(nullptr) {}
};

#endif