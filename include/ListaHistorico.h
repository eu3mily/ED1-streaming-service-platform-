#ifndef LISTAHISTORICO_H
#define LISTAHISTORICO_H

#include "NoLista.h" // Inclui a estrutura dos nós (NoSimples e NoDuplo)

// A classe ListaHistorico implementa uma Lista Duplamente Encadeada.
// O objetivo principal dela é manter um ranking (Top Assistidos) sempre dinâmico
// e ordenado de forma DECRESCENTE (do conteúdo mais assistido para o menos assistido).
class ListaHistorico { 
private:
    // Ponteiros fundamentais da lista dupla
    NoDuplo* inicio;  // Aponta para o primeiro elemento (o "Top 1" em visualizações)
    NoDuplo* fim;     // Aponta para o último elemento (o menos assistido)
    int tamanho;      // Mantém o controle exato de quantos títulos únicos estão no histórico

public:
    // ==========================================
    //         CONSTRUTOR E DESTRUTOR
    // ==========================================
    ListaHistorico();
    
    // O destrutor chama o método limpar() para desalocar todos os nós da memória
    ~ListaHistorico();
    
    // ==========================================
    //       MÉTODOS DE MANIPULAÇÃO (RANKING)
    // ==========================================
    
    // Insere um novo conteúdo no histórico já na posição correta.
    // O algoritmo percorre a lista e "estaciona" o nó garantindo a ordem DECRESCENTE.
    void inserirOrdenado(Conteudo* c);
    
    // Método inteligente de atualização:
    // Se o filme já existe no histórico e é assistido de novo, ele "desconecta" 
    // o nó da posição atual, aumenta a visualização, e o reinsere usando a 
    // lógica do inserirOrdenado() para ele subir no ranking.
    void atualizarPosicao(Conteudo* c);
    
    // ==========================================
    //             MÉTODOS AUXILIARES
    // ==========================================
    
    // Percorre a lista dupla do início ao fim, imprimindo o pódio formatado no terminal
    void imprimirTopAssistidos() const;
    
    // Retorna o ponteiro inicial (útil para consultas ou validações de testes)
    NoDuplo* getInicio() const;
    
    // Retorna a quantidade total de elementos no histórico
    int getTamanho() const;
    
    // Esvazia a lista, deletando todos os nós iterativamente para evitar vazamentos (memory leaks)
    void limpar();
};

#endif