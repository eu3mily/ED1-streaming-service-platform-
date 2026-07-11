#ifndef ARVOREDECISAO_H
#define ARVOREDECISAO_H

#include "NoArvore.h" // estrutura do no
#include <vector>

class ArvoreDecisao {
private:
    NoArvore* raiz; // criando raiz da arvore

public:
    ArvoreDecisao();
    ~ArvoreDecisao();
    
    void criarArvoreEstatica();   // cria árvore com 6 níveis (no minimo)
    void navegar();               // percorre árvore interativamente
    void popularArvore(const std::vector<Conteudo*>& catalogo);
    NoArvore* getRaiz() const;
    
private:
    void deletarArvore(NoArvore* no);  // destroi a arvore
};

#endif