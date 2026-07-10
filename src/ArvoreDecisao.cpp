#include "ArvoreDecisao.h"
#include <iostream>
using namespace std;
 
ArvoreDecisao::ArvoreDecisao() : raiz(nullptr) {}
 
ArvoreDecisao::~ArvoreDecisao() {
    deletarArvore(raiz);
}
 
void ArvoreDecisao::criarArvoreEstatica() {
    // nivel 1 = RAIZ
    raiz = new NoArvore("Qual tipo de conteúdo você prefere?");
    
    // nivel 2 (começar o afunilamento)
    raiz->esquerda = new NoArvore("Você gosta de conteúdo de AÇÃO?");
    raiz->direita = new NoArvore("Prefere conteúdo LEVE e DIVERTIDO?");
    
    // nivel 3
    raiz->esquerda->esquerda = new NoArvore("Prefere assistir FILMES ou SÉRIES de AÇÂO?");
    raiz->esquerda->direita = new NoArvore("Gosta de FICÇÃO CIENTÍFICA?");
    
    raiz->direita->esquerda = new NoArvore("Você gosta de COMÉDIA?");
    raiz->direita->direita = new NoArvore("Prefere conteúdo que faz REFLETIR?");
    
    // nivel 4
    raiz->esquerda->esquerda->esquerda = new NoArvore("Gosta de ação MODERNA ou CLÁSSICA?");
    raiz->esquerda->esquerda->direita = new NoArvore("Gosta de ANIMES de ação?");
    
    raiz->esquerda->direita->esquerda = new NoArvore("Prefere DISTÓPICO ou FUTURISTA?");
    raiz->esquerda->direita->direita = new NoArvore("Gosta de SPACE OPERA?");
    
    raiz->direita->esquerda->esquerda = new NoArvore("Prefere COMÉDIA ROMÂNTICA?");
    raiz->direita->esquerda->direita = new NoArvore("Gosta de COMÉDIA DARK?");
    
    raiz->direita->direita->esquerda = new NoArvore("Prefere DRAMA HISTÓRICO?");
    raiz->direita->direita->direita = new NoArvore("Gosta de DOCUMENTÁRIOS?");
    
    // niveis 5 E 6 = FOLHAS (fim da arvore = lista de recomendacoes)
    
    // Filmes de Ação Moderna
    raiz->esquerda->esquerda->esquerda->esquerda = new NoArvore("Folha");
    raiz->esquerda->esquerda->esquerda->esquerda->listaFolha = new ListaRecomendacoes(); // cospe uma lista de acordo c afolha
    
    raiz->esquerda->esquerda->esquerda->direita = new NoArvore("Folha");
    raiz->esquerda->esquerda->esquerda->direita->listaFolha = new ListaRecomendacoes();
    
    // Animes de Ação
    raiz->esquerda->esquerda->direita->esquerda = new NoArvore("Folha");
    raiz->esquerda->esquerda->direita->esquerda->listaFolha = new ListaRecomendacoes();
    
    raiz->esquerda->esquerda->direita->direita = new NoArvore("Folha");
    raiz->esquerda->esquerda->direita->direita->listaFolha = new ListaRecomendacoes();
    
    // Ficção Científica
    raiz->esquerda->direita->esquerda->esquerda = new NoArvore("Folha");
    raiz->esquerda->direita->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    
    raiz->esquerda->direita->esquerda->direita = new NoArvore("Folha");
    raiz->esquerda->direita->esquerda->direita->listaFolha = new ListaRecomendacoes();
    
    // Space Opera
    raiz->esquerda->direita->direita->esquerda = new NoArvore("Folha");
    raiz->esquerda->direita->direita->esquerda->listaFolha = new ListaRecomendacoes();
    
    raiz->esquerda->direita->direita->direita = new NoArvore("Folha");
    raiz->esquerda->direita->direita->direita->listaFolha = new ListaRecomendacoes();
    
    // Comédia Romântica
    raiz->direita->esquerda->esquerda->esquerda = new NoArvore("Folha");
    raiz->direita->esquerda->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    
    raiz->direita->esquerda->esquerda->direita = new NoArvore("Folha");
    raiz->direita->esquerda->esquerda->direita->listaFolha = new ListaRecomendacoes();
    
    // Comédia Dark
    raiz->direita->esquerda->direita->esquerda = new NoArvore("Folha");
    raiz->direita->esquerda->direita->esquerda->listaFolha = new ListaRecomendacoes();
    
    raiz->direita->esquerda->direita->direita = new NoArvore("Folha");
    raiz->direita->esquerda->direita->direita->listaFolha = new ListaRecomendacoes();
    
    // Drama Histórico
    raiz->direita->direita->esquerda->esquerda = new NoArvore("Folha");
    raiz->direita->direita->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    
    raiz->direita->direita->esquerda->direita = new NoArvore("Folha");
    raiz->direita->direita->esquerda->direita->listaFolha = new ListaRecomendacoes();
    
    // Documentários
    raiz->direita->direita->direita->esquerda = new NoArvore("Folha");
    raiz->direita->direita->direita->esquerda->listaFolha = new ListaRecomendacoes();
    
    raiz->direita->direita->direita->direita = new NoArvore("Folha");
    raiz->direita->direita->direita->direita->listaFolha = new ListaRecomendacoes();
}
 
void ArvoreDecisao::navegar() {
    if (raiz == nullptr) {
        cout << "Árvore não inicializada!!" << endl;
        return;
    }
    
    NoArvore* atual = raiz;
    
    while (!atual->ehFolha()) {
        cout << "\n" << atual->pergunta << endl;
        cout << "[1] Sim / [2] Não : ";
        
        int opcao;
        cin >> opcao; // tipo um switch case
        cin.ignore();
        
        if (opcao == 1) { // se sim, vai pra esquerda
            if (atual->esquerda != nullptr) {
                atual = atual->esquerda;
            } else { // se nao tiver ramo para esquerda
                cout << "Caminho inválido!" << endl;
                return;
            }
        } else if (opcao == 2) { // se nao, vai pra direita
            if (atual->direita != nullptr) {
                atual = atual->direita;
            } else { // se nao tiver ramo pra direita
                cout << "Caminho inválido!" << endl;
                return;
            }
        } else { // se nao for nenhum dos dois
            cout << "Opção inválida! Digite apenas 1 ou 2." << endl;
        }
    }
    
    cout << "=== RECOMENDAÇÕES PERSONALIZADAS PARA VOCÊ === " << endl;
    if (atual->listaFolha != nullptr) {
        atual->listaFolha->imprimirLista();
    } else {
        cout << "Sem recomendações disponíveis para esse caminho. :/" << endl;
    }
}
 
NoArvore* ArvoreDecisao::getRaiz() const {
    return raiz;
}
 //se o ponteiro for nulo, volta nulo, sendo o ponteiro da raiz, se nao, é pra seguir o fluxo normal ate chegar na folha (recomendacoes)
void ArvoreDecisao::deletarArvore(NoArvore* no) {
    if (no == nullptr) return;
    
    deletarArvore(no->esquerda);
    deletarArvore(no->direita);
    
    if (no->listaFolha != nullptr) {
        delete no->listaFolha;
    }
    
    delete no;
}
 