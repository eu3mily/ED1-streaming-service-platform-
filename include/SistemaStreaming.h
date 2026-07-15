#ifndef SISTEMASTREAMING_H
#define SISTEMASTREAMING_H

#include "ArvoreDecisao.h"
#include "ListaHistorico.h"
#include <vector> // Necessário para o catálogo geral
#include <map>    // Necessário para as estatísticas

// A classe SistemaStreaming é o "Cérebro" ou "Orquestrador" do projeto.
// Ela conecta todas as estruturas de dados (Árvore, Listas, Vetores, Mapas)
// e gerencia a interação direta com o usuário através do terminal.
class SistemaStreaming {
private:
    // ==========================================
    //         ESTRUTURAS DE DADOS (BASE)
    // ==========================================
    ArvoreDecisao* arvoreDecisao;         // Motor de recomendação (Árvore Binária)
    ListaHistorico* historicoAssistidos;  // Ranking de visualizações (Lista Duplamente Encadeada)
    
    // O catálogo geral usa um std::vector pois precisamos de acesso rápido a todos os filmes
    // para listagem, busca e salvamento no arquivo TXT.
    std::vector<Conteudo*> catalogoGeral; 
    
    // ==========================================
    //         MÉTRICAS E ESTATÍSTICAS
    // ==========================================
    int totalRecomendacoes;               // Contador global de recomendações feitas
    int totalVisualizacoes;               // Contador global de filmes assistidos

    // Estrutura std::map ideal para contar ocorrências por chave de texto.
    std::map<std::string, int> contagemTiposRecomendados;
    std::map<std::string, int> contagemGenerosRecomendados;

public:
    // ==========================================
    //         CONSTRUTOR E DESTRUTOR
    // ==========================================
    SistemaStreaming();
    ~SistemaStreaming();
    
    // ==========================================
    //         MÉTODOS DO MENU PRINCIPAL
    // ==========================================
    void menuPrincipal();                 // Loop principal que mantém o programa rodando
    void cadastrarConteudo();             // Opção 1: Insere novo filme no catálogo e atualiza a árvore
    void removerConteudo();               // Opção 2: Remove um título do catálogo e reconstrói a árvore
    void executarFluxoRecomendacao();     // Opção 3: Inicia a navegação de perguntas na árvore
    void exibirEstatisticas() const;      // Opção 5: Calcula pódios e imprime o relatório do sistema
    void buscarPorNome() const;           // Opção 6: Busca textual percorrendo o vetor do catálogo geral
    void listarConteudos() const;         // Opção 7: Exibe todos os títulos cadastrados
    
    // ==========================================
    //         MÉTODOS DE AÇÃO DO USUÁRIO
    // ==========================================
    // Chamado após escolher um filme. Atualiza visualizações, histórico e pede nota (estrelas)
    void assistirConteudo(const std::string& titulo);
    
    // ==========================================
    //         PERSISTÊNCIA DE DADOS (TXT)
    // ==========================================
    void salvarDados() const;             // Salva o vetor catalogoGeral no arquivo banco_streaming.txt
    bool carregarDados();                 // Lê o arquivo ao iniciar. Retorna falso se o arquivo não existir
    
    // ==========================================
    //              MÉTODOS AUXILIARES
    // ==========================================
    Conteudo* encontrarConteudo(const std::string& titulo) const;
    
private:
    // Popula o catálogo pela primeira vez caso o banco_streaming.txt não exista
    void inserirConteudosIniciais();
};

#endif