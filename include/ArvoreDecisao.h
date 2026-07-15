#ifndef ARVOREDECISAO_H
#define ARVOREDECISAO_H

#include "NoArvore.h" // Inclui a estrutura do nó que compõe a árvore
#include <vector>     // Inclui a biblioteca de vetores do C++ padrão

// Forward Declaration: Avisa ao compilador que a classe Conteudo existe em algum lugar.
// Usamos isso no .h ao invés de dar um #include "Conteudo.h" para evitar conflitos 
// de dependência circular e deixar a compilação mais rápida.
class Conteudo; 

class ArvoreDecisao {
private:
    // Ponteiro fundamental que guarda o topo (início) da árvore de decisão
    NoArvore* raiz; 

public:
    // Construtor: Inicializa a árvore (geralmente apontando a raiz para nullptr)
    ArvoreDecisao();
    
    // Destrutor: Limpa a árvore inteira da memória quando o programa fecha
    ~ArvoreDecisao();
    
    // Metódos principais da estrutura
    void criarArvoreEstatica();   // Monta a estrutura fixa da árvore (as perguntas de sim/não)
    NoArvore* navegar();          // Guia o usuário pelas perguntas e retorna a "folha" final alcançada
    
    // Recebe o catálogo completo de filmes e os distribui nas folhas corretas.
    // O prefixo std:: garante que o compilador saiba de onde vem o 'vector'.
    void popularArvore(const std::vector<Conteudo*>& catalogo); 
    
    NoArvore* getRaiz() const;    // Retorna a raiz (útil para consultas externas e testes)
    
private:
    // Método auxiliar recursivo usado pelo destrutor para apagar nó por nó e evitar vazamento de memória
    void deletarArvore(NoArvore* no);  
};

#endif