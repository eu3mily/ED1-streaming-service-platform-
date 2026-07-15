#include "SistemaStreaming.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>  // <-- PARA LER ARQUIVOS
#include <sstream>  // <-- PARA SEPARAR OS TEXTOS
using namespace std;


//sistema completo com tudo
SistemaStreaming::SistemaStreaming() 
    : totalRecomendacoes(0), totalVisualizacoes(0) {
    
    arvoreDecisao = new ArvoreDecisao();
    arvoreDecisao->criarArvoreEstatica();
    
    historicoAssistidos = new ListaHistorico();
    
    if (!carregarDados()) {
        inserirConteudosIniciais();
    }
    
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
    
    while (opcao != 7) {
        cout << "\n" << string(50, '=') << endl;
        cout << "  🎬 SISTEMA DE RECOMENDAÇÃO DE STREAMING  - TRABALHO FINAL ED1 SI!! 🎬" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Cadastrar novo conteúdo" << endl;
        cout << "2. Receber recomendações (Iniciar uma árvore)" << endl;
        cout << "3. Ver histórico dos mais assistidos" << endl;
        cout << "4. Ver estatísticas do sistema" << endl;
        cout << "5. Buscar título por nome" << endl;
        cout << "6. Listar todo o catálogo" << endl;
        cout << "7. Sair" << endl;
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
            case 6: listarConteudos(); break;
            case 7: 
                salvarDados(); 
                cout << "\nMuito obrigado por usar nosso sistema! Volte sempre :)\n" << endl; 
                break;
            default: cout << "Opção inválida! Tente novamente." << endl;
        }
    }
}
 
void SistemaStreaming::cadastrarConteudo() {
    string nome, tipo, genero;
    int ano = 0;
    
    cout << "\n=== CADASTRAR NOVO CONTEÚDO ===" << endl;
    cout << "Nome do título: ";
    getline(cin, nome);
    
    // --- SELEÇÃO DE TIPO POR ÍNDICE ---
    int opTipo = 0;
    while (opTipo < 1 || opTipo > 4) {
        cout << "\n--- Selecione o Tipo ---" << endl;
        cout << "[1] Filme | [2] Serie | [3] Documentario | [4] Anime" << endl;
        cout << "Opção: ";
        if (!(cin >> opTipo)) { // Se o usuário digitar letra, isso dá falso
            cin.clear(); 
            cin.ignore(10000, '\n'); 
        }
        if (opTipo == 1) tipo = "Filme";
        else if (opTipo == 2) tipo = "Serie";
        else if (opTipo == 3) tipo = "Documentario";
        else if (opTipo == 4) tipo = "Anime";
        else cout << "❌ Opção inválida! Digite um número de 1 a 4." << endl;
    }
    
    // --- SELEÇÃO DE GÊNERO POR ÍNDICE ---
    int opGenero = 0;
    while (opGenero < 1 || opGenero > 8) {
        cout << "\n--- Selecione o Gênero ---" << endl;
        cout << "[1] Acao | [2] Comedia | [3] Drama | [4] Terror" << endl;
        cout << "[5] Ficcao | [6] Suspense | [7] Natureza | [8] Tecnologia" << endl;
        cout << "Opção: ";
        if (!(cin >> opGenero)) {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
        }
        if (opGenero == 1) genero = "Acao";
        else if (opGenero == 2) genero = "Comedia";
        else if (opGenero == 3) genero = "Drama";
        else if (opGenero == 4) genero = "Terror";
        else if (opGenero == 5) genero = "Ficcao";
        else if (opGenero == 6) genero = "Suspense";
        else if (opGenero == 7) genero = "Natureza";
        else if (opGenero == 8) genero = "Tecnologia";
        else cout << "❌ Opção inválida! Digite um número de 1 a 8." << endl;
    }
    
    // --- CORREÇÃO DO LOOP INFINITO NO ANO ---
    while (true) {
        cout << "\nAno de lançamento: ";
        if (cin >> ano) {
            cin.ignore(); // Limpa o buffer do Enter e sai do loop
            break; 
        } else {
            cout << "❌ Erro: Por favor, digite um NÚMERO inteiro válido." << endl;
            cin.clear(); // Limpa a falha do cin
            cin.ignore(10000, '\n'); // Descarta o texto digitado errado
        }
    }
    
    Conteudo* novoConteudo = new Conteudo(nome, tipo, genero, ano);
    catalogoGeral.push_back(novoConteudo);
    
    cout << "\nOBAA! Conteúdo cadastrado com sucesso!" << endl;
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
            // Conta estatísticas
            string tipoRec = primeiroNo->conteudo->getTipo();
            string generoRec = primeiroNo->conteudo->getGenero();
            contagemTiposRecomendados[tipoRec]++;
            contagemGenerosRecomendados[generoRec]++;

            // --- SELEÇÃO POR ÍNDICE ---
            cout << "\nDeseja assistir a um desses conteúdos? (Digite o NÚMERO correspondente ou 0 para voltar): ";
            int escolha;
            
            // Proteção contra letras (loop infinito)
            while (!(cin >> escolha)) {
                cout << "❌ Erro: Digite um NÚMERO válido: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore();
            if (escolha > 0) {
                NoSimples* atual = folhaAlcancada->listaFolha->getInicio();
                int cont = 1;
                
                // Pula de nó em nó até chegar no número escolhido
                while (atual != nullptr && cont < escolha) {
                    atual = atual->proximo;
                    cont++;
                }
                
                // Se encontrou o nó, chama o método assistir passando o nome que está lá dentro
                if (atual != nullptr) {
                    assistirConteudo(atual->conteudo->getNome());
                } else {
                    cout << "❌ Número inválido! O catálogo não tem essa posição." << endl;
                }
            }
        }
    }
}
 
void SistemaStreaming::assistirConteudo(const string& titulo) {
    Conteudo* conteudo = encontrarConteudo(titulo);
    
    if (conteudo != nullptr) {
        conteudo->incrementarVisualizacoes();
        totalVisualizacoes++;
        historicoAssistidos->atualizarPosicao(conteudo);

        cout << "\nBOA!! " << titulo << " foi adicionado ao histórico!" << endl;

        // --- LÓGICA DE AVALIAÇÃO POR ESTRELAS ---
        int nota = 0;
        while (true) {
            cout << "Que nota (de 1 a 5 estrelas) dá para este conteúdo? ";
            if (cin >> nota && nota >= 1 && nota <= 5) {
                cin.ignore(); // Limpa o buffer
                conteudo->avaliar(nota);
                cout << "⭐ Avaliação de " << nota << " estrelas registada com sucesso!" << endl;
                break; // Sai do loop após sucesso
            } else {
                cout << "❌ Erro: Por favor, digite um NÚMERO válido entre 1 e 5!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }


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

    if (totalRecomendacoes == 0) {
        tipoMaisRec = "Nenhum";
        generoMaisRec = "Nenhum";
        tipoMenosRec = "Nenhum";
        generoMenosRec = "Nenhum";
        maxTipo = 0;
        maxGen = 0;
    }

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
    vector<string> generosConhecidos = {"Acao", "Comedia", "Drama", "Terror", "Ficcao", "Suspense", "Natureza", "Tecnologia"};
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

void SistemaStreaming::salvarDados() const {
    ofstream arquivo("banco_streaming.txt"); // Cria ou substitui o arquivo
    
    if (arquivo.is_open()) {
        for (Conteudo* c : catalogoGeral) {
            // Salva cada atributo separado por uma barra em pé (|)
            arquivo << c->getNome() << "|"
                    << c->getTipo() << "|"
                    << c->getGenero() << "|"
                    << c->getAnoLancamento() << "|"
                    << c->getNumVisualizacoes() << "|"
                    << c->getSomaAvaliacoes() << "|"
                    << c->getQtdAvaliacoes() << "\n";
        }
        arquivo.close();
        cout << "\n💾 Dados salvos com sucesso no arquivo 'banco_streaming.txt'!" << endl;
    } else {
        cout << "\n❌ Erro ao salvar os dados no arquivo!" << endl;
    }
}

bool SistemaStreaming::carregarDados() {
    ifstream arquivo("banco_streaming.txt"); // Tenta abrir o arquivo
    
    if (!arquivo.is_open()) {
        return false; // Retorna falso se for a primeira vez rodando (arquivo não existe)
    }

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, tipo, genero, anoStr, vizStr, somaStr, qtdStr;

        // "Corta" a linha toda vez que acha um | e guarda nas variáveis
        getline(ss, nome, '|');
        getline(ss, tipo, '|');
        getline(ss, genero, '|');
        getline(ss, anoStr, '|');
        getline(ss, vizStr, '|');
        getline(ss, somaStr, '|');
        getline(ss, qtdStr, '|');

        if (!nome.empty()) {
            // Recria o filme com os dados do arquivo
            Conteudo* c = new Conteudo(nome, tipo, genero, stoi(anoStr), stoi(vizStr));
            c->setAvaliacoes(stoi(somaStr), stoi(qtdStr));
            catalogoGeral.push_back(c);

            // Adiciona ao histórico se já tiver sido assistido
            if (c->getNumVisualizacoes() > 0) {
                historicoAssistidos->inserirOrdenado(c);
            }
        }
    }
    arquivo.close();
    return true; // Sucesso na leitura
}