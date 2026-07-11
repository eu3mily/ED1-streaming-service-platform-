#include "SistemaStreaming.h"
#include <iostream>
#include <iomanip>
using namespace std;


//sistema completo com tudo
SistemaStreaming::SistemaStreaming() 
    : totalRecomendacoes(0), totalVisualizacoes(0) {
    
    arvoreDecisao = new ArvoreDecisao();
    arvoreDecisao->criarArvoreEstatica();
    
    historicoAssistidos = new ListaHistorico();
    
    inserirConteudosIniciais();

    arvoreDecisao->popularArvore(catalogoGeral);
}
 
SistemaStreaming::~SistemaStreaming() {
    delete arvoreDecisao;
    delete historicoAssistidos;
    
    for (auto c : catalogoGeral) {
        delete c;
    }
    catalogoGeral.clear();
}
 
void SistemaStreaming::menuPrincipal() {
    int opcao = 0;
    
    while (opcao != 5) {
        cout << "\n" << string(50, '=') << endl;
        cout << "  🎬 SISTEMA DE RECOMENDAÇÃO DE STREAMING  - TRABALHO FINAL ED1 SI!! 🎬" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Cadastrar novo conteúdo" << endl;
        cout << "2. Receber recomendações (Iniciar uma árvore)" << endl;
        cout << "3. Ver histórico dos mais assistidos" << endl;
        cout << "4. Ver estatísticas do sistema" << endl;
        cout << "5. Sair" << endl;
        cout << string(50, '=') << endl;
        cout << "Escolha uma opção: ";
        
        cin >> opcao;
        cin.ignore();
        
        switch (opcao) {
            case 1:
                cadastrarConteudo();
                break;
            case 2:
                executarFluxoRecomendacao();
                break;
            case 3:
                historicoAssistidos->imprimirTopAssistidos();
                break;
            case 4:
                exibirEstatisticas();
                break;
            case 5:
                cout << "\nMuito obrigado por usar nosso sistema! Volte sempre :)\n" << endl;
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    }
}
 
void SistemaStreaming::cadastrarConteudo() {
    string nome, tipo, genero;
    int ano;
    
    cout << "\n=== CADASTRAR NOVO CONTEÚDO ===" << endl;
    cout << "Nome do título: ";
    getline(cin, nome);
    
    cout << "Tipo (Filme/Serie/Documentario/Anime/Outro...): ";
    getline(cin, tipo);
    
    cout << "Gênero (Acao/Comedia/Drama/Terror/Ficcao/Outro..): ";
    getline(cin, genero);
    
    cout << "Ano de lançamento: ";
    cin >> ano;
    cin.ignore();
    
    Conteudo* novoConteudo = new Conteudo(nome, tipo, genero, ano);
    catalogoGeral.push_back(novoConteudo);
    
    cout << "OBAA! Conteúdo cadastrado com sucesso!" << endl;
}
 
void SistemaStreaming::listarConteudos() const {
    cout << "\n=== CATÁLOGO GERAL ===" << endl;
    if (catalogoGeral.empty()) {
        cout << "Nenhum conteúdo foi cadastrado ainda." << endl;
        return;
    }
    
    for (int i = 0; i < catalogoGeral.size(); i++) {
        cout << i + 1 << ". ";
        catalogoGeral[i]->exibir();
    }
}
 
void SistemaStreaming::removerConteudo() {
    listarConteudos();
    
    cout << "\nDigite o número do conteúdo a remover (0 para cancelar): ";
    int numero;
    cin >> numero;
    cin.ignore();
    
    if (numero > 0 && numero <= catalogoGeral.size()) {
        delete catalogoGeral[numero - 1];
        catalogoGeral.erase(catalogoGeral.begin() + numero - 1);
        cout << "Conteúdo removido!" << endl;
    } else if (numero != 0) {
        cout << "Número inválido!" << endl;
    }
}
 
void SistemaStreaming::executarFluxoRecomendacao() {
    cout << "\n AGORA VAMOS ENCONTRAR O CONTEÚDO PERFEITO PARA VOCÊ!\n";
    cout << "Responda as perguntas abaixo:\n" << endl;
    
    arvoreDecisao->navegar();
    totalRecomendacoes++;
    
    cout << "\nDeseja assistir a um desses conteúdos? (Digite o nome ou apenas 'nao'): ";
    string titulo;
    getline(cin, titulo);
    
    if (titulo != "nao") {
        assistirConteudo(titulo);
    }
}
 
void SistemaStreaming::assistirConteudo(const string& titulo) {
    Conteudo* conteudo = encontrarConteudo(titulo);
    
    if (conteudo != nullptr) {
        conteudo->incrementarVisualizacoes();
        totalVisualizacoes++;
        historicoAssistidos->atualizarPosicao(conteudo);
        cout << "\nBOA!! " << titulo << " foi adicionado ao histórico!" << endl;
    } else {
        cout << "Vixe, Conteúdo não encontrado!" << endl;
    }
}
 
Conteudo* SistemaStreaming::encontrarConteudo(const string& titulo) const {
    for (auto c : catalogoGeral) {
        if (c->getNome() == titulo) {
            return c;
        }
    }
    return nullptr;
}
 
void SistemaStreaming::exibirEstatisticas() const {
    cout << "\n" << string(60, '=') << endl;
    cout << "   ESTATÍSTICAS DO SISTEMA" << endl;
    cout << string(60, '=') << endl;
    
    cout << "Total de recomendações realizadas: " << totalRecomendacoes << endl;
    cout << "Total de visualizações: " << totalVisualizacoes << endl;
    cout << "Total de títulos no catálogo: " << catalogoGeral.size() << endl;
    cout << string(60, '=') << "\n" << endl;
}
 
void SistemaStreaming::inserirConteudosIniciais() {
    catalogoGeral.push_back(new Conteudo("Vingadores Ultimato", "Filme", "Acao", 2018));
    catalogoGeral.push_back(new Conteudo("John Wick", "Filme", "Acao", 2014));
    catalogoGeral.push_back(new Conteudo("Homem-Aranha", "Filme", "Acao", 2002));
    
    catalogoGeral.push_back(new Conteudo("Breaking Bad", "Serie", "Drama", 2008));
    catalogoGeral.push_back(new Conteudo("The Mandalorian", "Serie", "Acao", 2019));
    catalogoGeral.push_back(new Conteudo("Stranger Things", "Serie", "Ficcao", 2016));
    
    catalogoGeral.push_back(new Conteudo("Minha Mãe é uma Peça", "Filme", "Comedia", 2018));
    catalogoGeral.push_back(new Conteudo("A Vida é Bela", "Filme", "Comedia", 1997));
    
    catalogoGeral.push_back(new Conteudo("Planet Earth", "Documentario", "Natureza", 2016));
    catalogoGeral.push_back(new Conteudo("The Social Dilemma", "Documentario", "Tecnologia", 2020));
    
    catalogoGeral.push_back(new Conteudo("Attack On Titan", "Anime", "Acao", 2018));
    catalogoGeral.push_back(new Conteudo("Death Note", "Anime", "Suspense", 2006));
}
 