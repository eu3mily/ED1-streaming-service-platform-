#ifndef SISTEMASTREAMING_H
#define SISTEMASTREAMING_H

#include "ArvoreDecisao.h"
#include "ListaHistorico.h"
#include <vector>
#include <map>

class SistemaStreaming {
private:
    ArvoreDecisao* arvoreDecisao;
    ListaHistorico* historicoAssistidos;
    vector<Conteudo*> catalogoGeral;
    int totalRecomendacoes;
    int totalVisualizacoes;

    std::map<string, int> contagemTiposRecomendados;
    std::map<string, int> contagemGenerosRecomendados;

public:
    SistemaStreaming();
    ~SistemaStreaming();
    
    void menuPrincipal();
    void cadastrarConteudo();
    void listarConteudos() const;
    void removerConteudo();
    void executarFluxoRecomendacao();
    void assistirConteudo(const string& titulo);
    void exibirEstatisticas() const;
    void buscarPorNome() const;
    
    Conteudo* encontrarConteudo(const string& titulo) const;
    
private:
    void inserirConteudosIniciais();
};

#endif