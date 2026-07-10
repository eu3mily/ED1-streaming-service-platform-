#ifndef SISTEMASTREAMING_H
#define SISTEMASTREAMING_H

#include "ArvoreDecisao.h"
#include "ListaHistorico.h"
#include <vector>

class SistemaStreaming {
private:
    ArvoreDecisao* arvoreDecisao;
    ListaHistorico* historicoAssistidos;
    vector<Conteudo*> catalogoGeral;
    int totalRecomendacoes;
    int totalVisualizacoes;

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
    
    Conteudo* encontrarConteudo(const string& titulo) const;
    
private:
    void inserirConteudosIniciais();
};

#endif