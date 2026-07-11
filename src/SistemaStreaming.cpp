#include "SistemaStreaming.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;


//sistema completo com tudo
SistemaStreaming::SistemaStreaming() 
    : totalRecomendacoes(0), totalVisualizacoes(0) {
    
    arvoreDecisao = new ArvoreDecisao();
    arvoreDecisao->criarArvoreEstatica();
    
    historicoAssistidos = new ListaHistorico();
    
    inserirConteudosIniciais();
    arvoreDecisao->popularArvore(catalogoGeral);

    // Inicializa os tipos
    contagemTiposRecomendados["Filme"] = 0;
    contagemTiposRecomendados["Serie"] = 0;
    contagemTiposRecomendados["Documentario"] = 0;
    contagemTiposRecomendados["Anime"] = 0;

    // Inicializa os gêneros
    contagemGenerosRecomendados["Acao"] = 0;
    contagemGenerosRecomendados["Comedia"] = 0;
    contagemGenerosRecomendados["Drama"] = 0;
    contagemGenerosRecomendados["Terror"] = 0;
    contagemGenerosRecomendados["Ficcao"] = 0;
    contagemGenerosRecomendados["Natureza"] = 0;
    contagemGenerosRecomendados["Tecnologia"] = 0;
    contagemGenerosRecomendados["Suspense"] = 0;
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
    
    while (opcao != 6) {
        cout << "\n" << string(50, '=') << endl;
        cout << "  🎬 SISTEMA DE RECOMENDAÇÃO DE STREAMING  - TRABALHO FINAL ED1 SI!! 🎬" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Cadastrar novo conteúdo" << endl;
        cout << "2. Receber recomendações (Iniciar uma árvore)" << endl;
        cout << "3. Ver histórico dos mais assistidos" << endl;
        cout << "4. Ver estatísticas do sistema" << endl;
        cout << "5. Buscar título por nome" << endl;
        cout << "6. Sair" << endl;
        cout << string(50, '=') << endl;
        cout << "Escolha uma opção: ";
        
        cin >> opcao;
        cin.ignore();
        
        switch (opcao) {
            case 1: cadastrarConteudo(); break;
            case 2: executarFluxoRecomendacao(); break;
            case 3: historicoAssistidos->imprimirTopAssistidos(); break;
            case 4: exibirEstatisticas(); break;
            case 5: buscarPorNome(); break;
            case 6:
                cout << "\nMuito obrigado por usar nosso sistema! Volte sempre :)\n" << endl; 
                break;
            default: cout << "Opção inválida! Tente novamente." << endl;
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
    
    // Captura qual nó folha o usuário atingiu
    NoArvore* folhaAlcancada = arvoreDecisao->navegar();
    totalRecomendacoes++;
    
    // Registra a recomendação para as estatísticas globais
    if (folhaAlcancada != nullptr && folhaAlcancada->listaFolha != nullptr) {
        NoSimples* primeiroNo = folhaAlcancada->listaFolha->getInicio();
        if (primeiroNo != nullptr) {
            // Analisa as propriedades do primeiro item da lista para pontuar a categoria
            string tipoRec = primeiroNo->conteudo->getTipo();
            string generoRec = primeiroNo->conteudo->getGenero();
            
            contagemTiposRecomendados[tipoRec]++;
            contagemGenerosRecomendados[generoRec]++;
        }
    }
    
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
    cout << "   📊 ESTATÍSTICAS DETALHADAS DO SISTEMA 📊" << endl;
    cout << string(60, '=') << endl;
    
    cout << "Total de recomendações realizadas: " << totalRecomendacoes << endl;
    cout << "Total de visualizações: " << totalVisualizacoes << endl;
    cout << "Total de títulos no catálogo: " << catalogoGeral.size() << endl;
    cout << string(60, '-') << endl;

    // 1. Calcular Tipo Mais e Menos Recomendado
    string tipoMaisRec = "Nenhum", tipoMenosRec = "Nenhum";
    int maxTipo = -1, minTipo = 1e9;
    for (auto const& par : contagemTiposRecomendados) {
        if (par.second > maxTipo) { maxTipo = par.second; tipoMaisRec = par.first; }
        if (par.second < minTipo) { minTipo = par.second; tipoMenosRec = par.first; }
    }
    if (contagemTiposRecomendados.empty()) minTipo = 0;

    // 2. Calcular Gênero Mais e Menos Recomendado
    string generoMaisRec = "Nenhum", generoMenosRec = "Nenhum";
    int maxGen = -1, minGen = 1e9;
    for (auto const& par : contagemGenerosRecomendados) {
        if (par.second > maxGen) { maxGen = par.second; generoMaisRec = par.first; }
        if (par.second < minGen) { minGen = par.second; generoMenosRec = par.first; }
    }
    if (contagemGenerosRecomendados.empty()) minGen = 0;

    cout << "Tipo de conteúdo MAIS recomendado: " << tipoMaisRec << " (" << (maxTipo == -1 ? 0 : maxTipo) << "x)" << endl;
    cout << "Gênero MAIS recomendado:           " << generoMaisRec << " (" << (maxGen == -1 ? 0 : maxGen) << "x)" << endl;
    cout << "Tipo de conteúdo MENOS recomendado: " << (minTipo == 1e9 || minTipo == 0 ? "Nenhum" : tipoMenosRec) << endl;
    cout << "Gênero MENOS recomendado:           " << (minGen == 1e9 || minGen == 0 ? "Nenhum" : generoMenosRec) << endl;
    cout << string(60, '-') << endl;

    // 3. Título Mais Assistido por Tipo
    cout << "🎬 Título mais assistido por TIPO:" << endl;
    vector<string> tiposConhecidos = {"Filme", "Serie", "Documentario", "Anime"};
    for (const string& t : tiposConhecidos) {
        Conteudo* maisVisto = nullptr;
        for (Conteudo* c : catalogoGeral) {
            if (c->getTipo() == t) {
                if (maisVisto == nullptr || c->getNumVisualizacoes() > maisVisto->getNumVisualizacoes()) {
                    maisVisto = c;
                }
            }
        }
        if (maisVisto != nullptr && maisVisto->getNumVisualizacoes() > 0) {
            cout << "  • " << t << ": " << maisVisto->getNome() << " (" << maisVisto->getNumVisualizacoes() << " views)" << endl;
        } else {
            cout << "  • " << t << ": Nenhum assistido ainda" << endl;
        }
    }
    cout << string(60, '-') << endl;

    // 4. Título Mais Assistido por Gênero
    cout << "🏷️ Título mais assistido por GÊNERO:" << endl;
    vector<string> generosConhecidos = {"Acao", "Comedia", "Drama", "Terror", "Ficcao"};
    for (const string& g : generosConhecidos) {
        Conteudo* maisVisto = nullptr;
        for (Conteudo* c : catalogoGeral) {
            if (c->getGenero() == g) {
                if (maisVisto == nullptr || c->getNumVisualizacoes() > maisVisto->getNumVisualizacoes()) {
                    maisVisto = c;
                }
            }
        }
        if (maisVisto != nullptr && maisVisto->getNumVisualizacoes() > 0) {
            cout << "  • " << g << ": " << maisVisto->getNome() << " (" << maisVisto->getNumVisualizacoes() << " views)" << endl;
        } else {
            cout << "  • " << g << ": Nenhum assistido ainda" << endl;
        }
    }
    cout << string(60, '-') << endl;

    // 5. Títulos Nunca Selecionados
    cout << "💤 Títulos NUNCA selecionados (0 visualizações):" << endl;
    bool nenhumNulo = true;
    for (Conteudo* c : catalogoGeral) {
        if (c->getNumVisualizacoes() == 0) {
            cout << "  • " << c->getNome() << " [" << c->getTipo() << "]" << endl;
            nenhumNulo = false;
        }
    }
    if (nenhumNulo) {
        cout << "  • Todos os conteúdos do catálogo já foram assistidos ao menos uma vez!" << endl;
    }
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

void SistemaStreaming::buscarPorNome() const {
    cout << "\n=== 🔎 BUSCAR CONTEÚDO POR NOME ===" << endl;
    cout << "Digite o nome ou parte do título que deseja encontrar: ";
    string termo;
    getline(cin, termo);

    // Converte o termo de busca para minúsculo
    string termoBusca = termo;
    transform(termoBusca.begin(), termoBusca.end(), termoBusca.begin(), ::tolower);

    bool encontrou = false;
    cout << "\nResultados da busca:" << endl;
    
    // Percorre o catálogo geral
    for (Conteudo* c : catalogoGeral) {
        // Pega o nome do filme e também converte para minúsculo
        string nomeConteudo = c->getNome();
        string nomeLower = nomeConteudo;
        transform(nomeLower.begin(), nomeLower.end(), nomeLower.begin(), ::tolower);

        // Verifica se o termo de busca existe dentro do nome do filme
        // A função find() retorna string::npos se NÃO encontrar nada
        if (nomeLower.find(termoBusca) != string::npos) {
            c->exibir();
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Nenhum conteúdo encontrado com o termo '" << termo << "' :(" << endl;
    }
}