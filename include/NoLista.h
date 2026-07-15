#ifndef NOLISTA_H
#define NOLISTA_H

#include "Conteudo.h" // A carga de dados que os nós vão carregar

// ==========================================
//       NÓ PARA LISTA SIMPLES (RECOMENDAÇÕES)
// ==========================================
// A estrutura NoSimples é usada exclusivamente nas "folhas" da Árvore de Decisão.
// Como a lista de recomendações só precisa ser lida do início ao fim 
// (para exibir as opções ao usuário), apenas o ponteiro "proximo" é suficiente.
struct NoSimples {
    Conteudo* conteudo;     // O "pacote" de dados (o filme/série em si)
    NoSimples* proximo;     // Ponteiro que liga ao próximo nó da fila
    
    // Construtor: Inicializa guardando o conteúdo e apontando o próximo para nulo
    NoSimples(Conteudo* c) : conteudo(c), proximo(nullptr) {}
};

// ==========================================
//       NÓ PARA LISTA DUPLA (HISTÓRICO)
// ==========================================
// A estrutura NoDuplo é o coração do Histórico de Assistidos.
// Como o ranking precisa reordenar filmes constantemente (fazendo-os subir ou 
// descer posições de acordo com as visualizações), precisamos olhar para os dois lados.
struct NoDuplo {
    Conteudo* conteudo;     // O "pacote" de dados (o filme/série em si)
    NoDuplo* proximo;       // Ponteiro para o título que está ABAIXO no ranking
    NoDuplo* anterior;      // Ponteiro para o título que está ACIMA no ranking
    
    // Construtor: Inicializa guardando o filme e deixando os dois ponteiros nulos
    NoDuplo(Conteudo* c) : conteudo(c), proximo(nullptr), anterior(nullptr) {}
};

#endif