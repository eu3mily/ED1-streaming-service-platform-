#ifndef NOARVORE_H
#define NOARVORE_H
#include "Conteudo.h"
#include "ListaRecomendacoes.h"
#include <string>

// logica do no apenas
struct NoArvore{
    string pergunta;
    NoArvore* esquerda; // resposta = "sim"
    NoArvore* direita; // resposta = "nao"
    ListaRecomendacoes* listaFolha; // nullptr se nao for folha

    NoArvore(string p) 
        : pergunta(p), esquerda(nullptr), direita(nullptr), listaFolha(nullptr) {}
        
    bool ehFolha() const {
        return listaFolha != nullptr; 
    }
};

#endif