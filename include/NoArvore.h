#ifndef NOARVORE_H
#define NOARVORE_H

#include "Conteudo.h"
#include "ListaRecomendacoes.h"
#include <string> // Biblioteca padrão para textos

// A estrutura NoArvore define cada "ponto de parada" dentro da Árvore de Decisão.
// Usamos 'struct' em vez de 'class' aqui porque é um objeto puramente de agrupamento 
// de dados, onde a classe ArvoreDecisao fará o gerenciamento direto.
struct NoArvore {
    // ==========================================
    //                 ATRIBUTOS
    // ==========================================
    std::string pergunta;           // O texto da pergunta (Ex: "Prefere filmes?")
    
    // Ponteiros de navegação da Árvore Binária
    NoArvore* esquerda;             // Caminho tomado se a resposta for "SIM"
    NoArvore* direita;              // Caminho tomado se a resposta for "NÃO"
    
    // Carga de dados (O que a árvore guarda de verdade)
    ListaRecomendacoes* listaFolha; // Ponteiro para a lista de filmes. 
                                    // Fica como 'nullptr' nas perguntas e só é preenchido no final.

    // ==========================================
    //                CONSTRUTOR
    // ==========================================
    // Inicializa o nó recebendo a pergunta. 
    // Por padrão, os filhos e a lista nascem nulos até que a ArvoreDecisao os conecte.
    NoArvore(std::string p) 
        : pergunta(p), esquerda(nullptr), direita(nullptr), listaFolha(nullptr) {}
        
    // ==========================================
    //                 MÉTODOS
    // ==========================================
    // Método auxiliar prático para saber se o nó atual é o fim da linha.
    // Se a listaFolha não for nula, significa que chegamos ao resultado da recomendação.
    bool ehFolha() const {
        return listaFolha != nullptr; 
    }
};

#endif