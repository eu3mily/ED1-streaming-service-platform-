#ifndef ARVOREDECISAO_H
#define ARVOREDECISAO_H

#include "NoArvore.h" // estrutura do no 

class ArvoreDecisao {
private:
    NoArvore* raiz; // criando raiz da arvore

public:
    ArvoreDecisao();
    ~ArvoreDecisao();
    
    void criarArvoreEstatica();   // cria árvore com 6 níveis (no minimo)
    void navegar();               // percorre árvore interativamente
    NoArvore* getRaiz() const;
    
private:
    void deletarArvore(NoArvore* no);  // destroi a arvore
};

#endif