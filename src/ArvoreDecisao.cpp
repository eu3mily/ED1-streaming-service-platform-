#include "ArvoreDecisao.h"
#include <iostream>
using namespace std;
 
ArvoreDecisao::ArvoreDecisao() : raiz(nullptr) {}
 
ArvoreDecisao::~ArvoreDecisao() {
    deletarArvore(raiz);
}
 
void ArvoreDecisao::criarArvoreEstatica() {
    // ============================================================
    // NIVEL 1: RAIZ - Pergunta principal de divisão
    // ============================================================
    raiz = new NoArvore("Você prefere conteúdos com adrenalina/fantasia (Ação/Ficção/Anime)?");
    
    // ============================================================
    // NIVEL 2: Afunilamento por subcategoria
    // ============================================================
    raiz->esquerda = new NoArvore("O seu foco principal é AÇÃO ou ANIMES?");
    raiz->direita  = new NoArvore("Você está procurando algo para rir (COMÉDIA)?");
    
    // ============================================================
    // NIVEL 3: Formato ou estilo
    // ============================================================
    raiz->esquerda->esquerda = new NoArvore("Você prefere assistir no formato de FILME?");
    raiz->esquerda->direita  = new NoArvore("Gosta de histórias puramente de FICÇÃO CIENTÍFICA?");
    
    raiz->direita->esquerda  = new NoArvore("Prefere comédias mais recentes (lançadas após 2010)?");
    raiz->direita->direita   = new NoArvore("Você prefere um bom DRAMA? (Se 'Não', focaremos em Documentários)");
    
    // ============================================================
    // NIVEL 4: Critério de época (recente vs clássico)
    // ============================================================
    string perguntaEpoca = "Para fechar: prefere produções RECENTES (lançadas de 2015 em diante)?";
    
    raiz->esquerda->esquerda->esquerda = new NoArvore(perguntaEpoca);
    raiz->esquerda->esquerda->direita  = new NoArvore(perguntaEpoca);
    raiz->esquerda->direita->esquerda  = new NoArvore(perguntaEpoca);
    raiz->esquerda->direita->direita   = new NoArvore(perguntaEpoca);
    raiz->direita->esquerda->esquerda  = new NoArvore(perguntaEpoca);
    raiz->direita->esquerda->direita   = new NoArvore(perguntaEpoca);
    raiz->direita->direita->esquerda   = new NoArvore(perguntaEpoca);
    raiz->direita->direita->direita    = new NoArvore(perguntaEpoca);

    // ============================================================
    // NIVEL 5: Critério de popularidade
    // ============================================================
    string perguntaPop = "Prefere títulos MUITO POPULARES (blockbusters/hits conhecidos)?";

    // Filmes de Ação
    raiz->esquerda->esquerda->esquerda->esquerda = new NoArvore(perguntaPop);
    raiz->esquerda->esquerda->esquerda->direita  = new NoArvore(perguntaPop);
    // Animes de Ação
    raiz->esquerda->esquerda->direita->esquerda  = new NoArvore(perguntaPop);
    raiz->esquerda->esquerda->direita->direita   = new NoArvore(perguntaPop);
    // Ficção Científica
    raiz->esquerda->direita->esquerda->esquerda  = new NoArvore(perguntaPop);
    raiz->esquerda->direita->esquerda->direita   = new NoArvore(perguntaPop);
    // Space Opera / Outros Sci-Fi
    raiz->esquerda->direita->direita->esquerda   = new NoArvore(perguntaPop);
    raiz->esquerda->direita->direita->direita    = new NoArvore(perguntaPop);
    // Comédia Recente
    raiz->direita->esquerda->esquerda->esquerda  = new NoArvore(perguntaPop);
    raiz->direita->esquerda->esquerda->direita   = new NoArvore(perguntaPop);
    // Comédia Clássica
    raiz->direita->esquerda->direita->esquerda   = new NoArvore(perguntaPop);
    raiz->direita->esquerda->direita->direita    = new NoArvore(perguntaPop);
    // Drama
    raiz->direita->direita->esquerda->esquerda   = new NoArvore(perguntaPop);
    raiz->direita->direita->esquerda->direita    = new NoArvore(perguntaPop);
    // Documentário
    raiz->direita->direita->direita->esquerda    = new NoArvore(perguntaPop);
    raiz->direita->direita->direita->direita     = new NoArvore(perguntaPop);

    // ============================================================
    // NIVEL 6: FOLHAS (Lista de recomendações final)
    // Cada folha tem sua própria ListaRecomendacoes que será populada
    // automaticamente pelo método popularArvore() com base no catálogo.
    // ============================================================

    // --- RAMO: Filmes de Ação ---
    // Recentes + Populares
    raiz->esquerda->esquerda->esquerda->esquerda->esquerda = new NoArvore("Folha");
    raiz->esquerda->esquerda->esquerda->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    // Recentes + Alternativos
    raiz->esquerda->esquerda->esquerda->esquerda->direita = new NoArvore("Folha");
    raiz->esquerda->esquerda->esquerda->esquerda->direita->listaFolha = new ListaRecomendacoes();
    // Clássicos + Populares
    raiz->esquerda->esquerda->esquerda->direita->esquerda = new NoArvore("Folha");
    raiz->esquerda->esquerda->esquerda->direita->esquerda->listaFolha = new ListaRecomendacoes();
    // Clássicos + Alternativos
    raiz->esquerda->esquerda->esquerda->direita->direita = new NoArvore("Folha");
    raiz->esquerda->esquerda->esquerda->direita->direita->listaFolha = new ListaRecomendacoes();

    // --- RAMO: Animes de Ação ---
    // Recentes + Populares
    raiz->esquerda->esquerda->direita->esquerda->esquerda = new NoArvore("Folha");
    raiz->esquerda->esquerda->direita->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    // Recentes + Alternativos
    raiz->esquerda->esquerda->direita->esquerda->direita = new NoArvore("Folha");
    raiz->esquerda->esquerda->direita->esquerda->direita->listaFolha = new ListaRecomendacoes();
    // Clássicos + Populares
    raiz->esquerda->esquerda->direita->direita->esquerda = new NoArvore("Folha");
    raiz->esquerda->esquerda->direita->direita->esquerda->listaFolha = new ListaRecomendacoes();
    // Clássicos + Alternativos
    raiz->esquerda->esquerda->direita->direita->direita = new NoArvore("Folha");
    raiz->esquerda->esquerda->direita->direita->direita->listaFolha = new ListaRecomendacoes();

    // --- RAMO: Ficção Científica ---
    raiz->esquerda->direita->esquerda->esquerda->esquerda = new NoArvore("Folha");
    raiz->esquerda->direita->esquerda->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->esquerda->direita->esquerda->esquerda->direita = new NoArvore("Folha");
    raiz->esquerda->direita->esquerda->esquerda->direita->listaFolha = new ListaRecomendacoes();
    raiz->esquerda->direita->esquerda->direita->esquerda = new NoArvore("Folha");
    raiz->esquerda->direita->esquerda->direita->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->esquerda->direita->esquerda->direita->direita = new NoArvore("Folha");
    raiz->esquerda->direita->esquerda->direita->direita->listaFolha = new ListaRecomendacoes();

    // --- RAMO: Space Opera / Sci-Fi Outros ---
    raiz->esquerda->direita->direita->esquerda->esquerda = new NoArvore("Folha");
    raiz->esquerda->direita->direita->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->esquerda->direita->direita->esquerda->direita = new NoArvore("Folha");
    raiz->esquerda->direita->direita->esquerda->direita->listaFolha = new ListaRecomendacoes();
    raiz->esquerda->direita->direita->direita->esquerda = new NoArvore("Folha");
    raiz->esquerda->direita->direita->direita->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->esquerda->direita->direita->direita->direita = new NoArvore("Folha");
    raiz->esquerda->direita->direita->direita->direita->listaFolha = new ListaRecomendacoes();

    // --- RAMO: Comédia Recente ---
    raiz->direita->esquerda->esquerda->esquerda->esquerda = new NoArvore("Folha");
    raiz->direita->esquerda->esquerda->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->esquerda->esquerda->esquerda->direita = new NoArvore("Folha");
    raiz->direita->esquerda->esquerda->esquerda->direita->listaFolha = new ListaRecomendacoes();
    raiz->direita->esquerda->esquerda->direita->esquerda = new NoArvore("Folha");
    raiz->direita->esquerda->esquerda->direita->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->esquerda->esquerda->direita->direita = new NoArvore("Folha");
    raiz->direita->esquerda->esquerda->direita->direita->listaFolha = new ListaRecomendacoes();

    // --- RAMO: Comédia Clássica ---
    raiz->direita->esquerda->direita->esquerda->esquerda = new NoArvore("Folha");
    raiz->direita->esquerda->direita->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->esquerda->direita->esquerda->direita = new NoArvore("Folha");
    raiz->direita->esquerda->direita->esquerda->direita->listaFolha = new ListaRecomendacoes();
    raiz->direita->esquerda->direita->direita->esquerda = new NoArvore("Folha");
    raiz->direita->esquerda->direita->direita->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->esquerda->direita->direita->direita = new NoArvore("Folha");
    raiz->direita->esquerda->direita->direita->direita->listaFolha = new ListaRecomendacoes();

    // --- RAMO: Drama ---
    raiz->direita->direita->esquerda->esquerda->esquerda = new NoArvore("Folha");
    raiz->direita->direita->esquerda->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->direita->esquerda->esquerda->direita = new NoArvore("Folha");
    raiz->direita->direita->esquerda->esquerda->direita->listaFolha = new ListaRecomendacoes();
    raiz->direita->direita->esquerda->direita->esquerda = new NoArvore("Folha");
    raiz->direita->direita->esquerda->direita->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->direita->esquerda->direita->direita = new NoArvore("Folha");
    raiz->direita->direita->esquerda->direita->direita->listaFolha = new ListaRecomendacoes();

    // --- RAMO: Documentário ---
    raiz->direita->direita->direita->esquerda->esquerda = new NoArvore("Folha");
    raiz->direita->direita->direita->esquerda->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->direita->direita->esquerda->direita = new NoArvore("Folha");
    raiz->direita->direita->direita->esquerda->direita->listaFolha = new ListaRecomendacoes();
    raiz->direita->direita->direita->direita->esquerda = new NoArvore("Folha");
    raiz->direita->direita->direita->direita->esquerda->listaFolha = new ListaRecomendacoes();
    raiz->direita->direita->direita->direita->direita = new NoArvore("Folha");
    raiz->direita->direita->direita->direita->direita->listaFolha = new ListaRecomendacoes();
}
 
NoArvore* ArvoreDecisao::navegar() {
    if (raiz == nullptr) {
        cout << "Árvore não inicializada!!" << endl;
        return nullptr;
    }
    
    NoArvore* atual = raiz;
    
    while (!atual->ehFolha()) {
        cout << "\n" << atual->pergunta << endl;
        cout << "[1] Sim / [2] Não : ";
        
        int opcao = 0;
        while (true) {
            cin >> opcao;

            if (cin.fail() || (opcao != 1 && opcao != 2)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "⚠️ Entrada inválida! Por favor, digite apenas [1] para Sim ou [2] para Não: ";
            } else {
                cin.ignore(10000, '\n');
                break;
            }
        }
        
        if (opcao == 1) {
            if (atual->esquerda != nullptr) {
                atual = atual->esquerda;
            } else {
                cout << "Caminho inválido!" << endl;
                return nullptr;
            }
        } else {
            if (atual->direita != nullptr) {
                atual = atual->direita;
            } else {
                cout << "Caminho inválido!" << endl;
                return nullptr;
            }
        }
    }
    
    cout << "\n=== RECOMENDAÇÕES PERSONALIZADAS PARA VOCÊ ===" << endl;
    if (atual->listaFolha != nullptr) {
        atual->listaFolha->imprimirLista();
    } else {
        cout << "Sem recomendações disponíveis para esse caminho. :/" << endl;
    }

    return atual;
}
 
NoArvore* ArvoreDecisao::getRaiz() const {
    return raiz;
}

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

    for (Conteudo* c : catalogo) {
        NoArvore* atual = raiz;

        while (!atual->ehFolha()) {
            
            // NIVEL 1: Ação/Ficção/Anime (esq) vs Comédia/Drama/Doc (dir)
            if (atual == raiz) {
                if (c->getGenero() == "Acao" || c->getGenero() == "Ficcao" || c->getTipo() == "Anime") {
                    atual = atual->esquerda;
                } else {
                    atual = atual->direita;
                }
            }
            
            // NIVEL 2 (Esq): Ação/Anime (esq) vs Ficção (dir)
            else if (atual == raiz->esquerda) {
                if (c->getGenero() == "Acao" || c->getTipo() == "Anime") {
                    atual = atual->esquerda;
                } else {
                    atual = atual->direita;
                }
            }
            
            // NIVEL 2 (Dir): Comédia (esq) vs Drama/Doc (dir)
            else if (atual == raiz->direita) {
                if (c->getGenero() == "Comedia") {
                    atual = atual->esquerda;
                } else {
                    atual = atual->direita;
                }
            }
            
            // NIVEL 3: Filme de Ação (esq) vs Anime de Ação (dir)
            else if (atual == raiz->esquerda->esquerda) {
                if (c->getTipo() == "Filme") atual = atual->esquerda;
                else atual = atual->direita;
            }
            // NIVEL 3: Ficção pura (esq) vs Space Opera (dir)
            else if (atual == raiz->esquerda->direita) {
                if (c->getGenero() == "Ficcao") atual = atual->esquerda;
                else atual = atual->direita;
            }
            // NIVEL 3: Comédia recente (esq) vs Comédia clássica (dir)
            else if (atual == raiz->direita->esquerda) {
                if (c->getAnoLancamento() > 2010) atual = atual->esquerda;
                else atual = atual->direita;
            }
            // NIVEL 3: Drama (esq) vs Documentário (dir)
            else if (atual == raiz->direita->direita) {
                if (c->getTipo() == "Documentario") atual = atual->direita;
                else atual = atual->esquerda;
            }
            
            // NIVEL 4: Recente (esq) vs Clássico (dir) — para todos os ramos
            else if (!atual->esquerda->ehFolha() && !atual->direita->ehFolha()) {
                if (c->getAnoLancamento() >= 2015) atual = atual->esquerda;
                else atual = atual->direita;
            }

            // NIVEL 5: Popular (esq) vs Alternativo (dir)
            // Considera "popular" filmes com mais de 5 visualizações OU com avaliação >= 4.0
            else {
                bool popular = (c->getNumVisualizacoes() >= 5 || c->getAvaliacaoMedia() >= 4.0f);
                if (popular) {
                    if (atual->esquerda != nullptr) atual = atual->esquerda;
                    else break;
                } else {
                    if (atual->direita != nullptr) atual = atual->direita;
                    else break;
                }
            }
        }

        if (atual != nullptr && atual->ehFolha() && atual->listaFolha != nullptr) {
            atual->listaFolha->inserirOrdenado(c);
        }
    }
}