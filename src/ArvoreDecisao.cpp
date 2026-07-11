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

void ArvoreDecisao::popularArvore(const vector<Conteudo*>& catalogo) {
    if (raiz == nullptr) return;

    // Percorre cada conteúdo do catálogo geral
    for (Conteudo* c : catalogo) {
        NoArvore* atual = raiz;

        // Enquanto não chegar em um nó folha, o filme navega pela árvore
        while (!atual->ehFolha()) {
            
            // LÓGICA DO NÍVEL 1: Tipo de conteúdo ou bifurcação inicial
            if (atual == raiz) {
                // Se for Ação, Ficção, Anime ou se for Filme/Série no geral, mandamos para a esquerda (ramo da ação/sci-fi)
                if (c->getGenero() == "Acao" || c->getGenero() == "Ficcao" || c->getTipo() == "Anime") {
                    atual = atual->esquerda;
                } else {
                    atual = atual->direita; // Comédia, Drama, Documentários vão para a direita
                }
            }
            
            // LÓGICA DO NÍVEL 2 (Ramo da Esquerda: Foco em Ação/Sci-Fi)
            else if (atual == raiz->esquerda) {
                if (c->getGenero() == "Acao" || c->getTipo() == "Anime") {
                    atual = atual->esquerda; // Vai para perguntas de Ação/Anime
                } else {
                    atual = atual->direita;  // Vai para perguntas de Ficção Científica
                }
            }
            
            // LÓGICA DO NÍVEL 2 (Ramo da Direita: Conteúdos Leves / Reflexivos)
            else if (atual == raiz->direita) {
                if (c->getGenero() == "Comedia") {
                    atual = atual->esquerda; // Vai para o ramo de Comédia
                } else {
                    atual = atual->direita;  // Vai para o ramo de Drama/Documentário (Refletir)
                }
            }
            
            // LÓGICA DO NÍVEL 3 (Sub-ramos de escolha: Filmes vs Séries, Estilos)
            else if (atual == raiz->esquerda->esquerda) { // Filmes ou Séries de Ação?
                if (c->getTipo() == "Filme") atual = atual->esquerda;
                else atual = atual->direita;
            }
            else if (atual == raiz->esquerda->direita) { // Ficção Científica?
                if (c->getGenero() == "Ficcao") atual = atual->esquerda;
                else atual = std::move(atual->direita); // Outros/Space Opera
            }
            else if (atual == raiz->direita->esquerda) { // Comédia?
                if (c->getAnoLancamento() > 2010) atual = atual->esquerda; // Romântica/Moderna
                else atual = atual->direita; // Dark/Outros
            }
            else if (atual == raiz->direita->esquerda || atual == raiz->direita->direita) { // Drama ou Documentário?
                if (c->getTipo() == "Documentario") atual = atual->direita;
                else atual = atual->esquerda; // Drama
            }
            
            // LÓGICA DO NÍVEL 4 (Último afunilamento antes das folhas: Clássico vs Moderno, etc)
            else {
                // Para simplificar o último nível e não estourar caminhos nulos,
                // se o nó filho para onde vamos for nulo, paramos aqui, caso contrário avançamos.
                if (c->getAnoLancamento() >= 2015) {
                    if (atual->esquerda != nullptr) atual = atual->esquerda;
                    else break;
                } else {
                    if (atual->direita != nullptr) atual = atual->direita;
                    else break;
                }
            }
        }

        // Ao encontrar a folha correta, insere o ponteiro do filme de forma ordenada nela
        if (atual != nullptr && atual->ehFolha() && atual->listaFolha != nullptr) {
            atual->listaFolha->inserirOrdenado(c);
        }
    }
}