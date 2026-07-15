#ifndef LISTARECOMENDACOES_H
#define LISTARECOMENDACOES_H

#include "NoLista.h" // Inclui a estrutura do nó simples

// A classe ListaRecomendacoes implementa uma Lista Simplesmente Encadeada.
// Ela fica armazenada nas "folhas" da Árvore de Decisão e guarda os filmes
// correspondentes àquele caminho específico, ordenando-os alfabeticamente.
class ListaRecomendacoes { 
private:
    // Ponteiro fundamental da lista simples
    NoSimples* inicio;  // Aponta para o primeiro conteúdo da lista de recomendação
    int tamanho;        // Quantidade de conteúdos armazenados nesta lista específica

public:
    // ==========================================
    //         CONSTRUTOR E DESTRUTOR
    // ==========================================
    ListaRecomendacoes();
    
    // O destrutor chama o método limpar() para esvaziar a lista da memória
    ~ListaRecomendacoes();
    
    // ==========================================
    //       MÉTODOS DE MANIPULAÇÃO E BUSCA
    // ==========================================
    
    // Insere um novo conteúdo na lista garantindo a ORDEM ALFABÉTICA.
    // Diferente do Histórico (que usa o número de visualizações), aqui a regra
    // de negócio dita que o usuário veja as opções de A a Z.
    void inserirOrdenado(Conteudo* c);  
    
    // Percorre a lista simples nó por nó imprimindo as opções de filmes/séries
    // para o usuário escolher o que quer assistir.
    void imprimirLista() const;
    
    // Retorna o ponteiro inicial (vital para quando o usuário escolhe um filme
    // por número e o sistema precisa iterar pela lista para achá-lo)
    NoSimples* getInicio() const;
    
    // Retorna a quantidade de opções de filmes/séries disponíveis nesta lista
    int getTamanho() const;
    
    // Esvazia a lista deletando cada NoSimples da memória para evitar memory leak
    void limpar();
};

#endif