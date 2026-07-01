# ED1-streaming-service-platform-
Um sistema inteligente de recomendação de conteúdo para uma plataforma de streaming. O sistema deverá simular o funcionamento básico de plataformas modernas de streaming, realizando recomendações personalizadas a partir de preferências do usuário e armazenando informações estatísticas sobre os conteúdos assistidos.

# Sistema de Streaming - Especificação Técnica de Arquitetura

Este repositório contém a implementação de uma plataforma de streaming robusta desenvolvida em C++. O projeto utiliza conceitos avançados de estruturas de dados dinâmicas, como listas encadeadas (simples e duplas), árvores de decisão binárias e gerenciamento global de estados para criar um motor de recomendação e análise de dados eficiente.

## 🛠️ Estrutura do Projeto e Modularização

O sistema foi arquitetado de forma modular, dividindo as responsabilidades em 5 módulos principais:

### Módulo 1: Entidades (Dados Puros)
Focado na representação dos objetos de negócio e na garantia de sua integridade fundamental.
* **`Conteudo.h` / `Conteudo.cpp`**: 
    * **Definição**: Classe ou `struct` `Conteudo`.
    * **Atributos**: Nome do título (string), Tipo (enum/string: Filme, Série, Documentário, Anime, Outros), Gênero (enum/string: Ação, Comédia, Drama, Terror, Ficção científica, Outros), Ano de lançamento (int) e Número de visualizações (int).
    * **Interface**: Construtores (padrão e parametrizado), Getters/Setters básicos e método `incrementarVisualizacoes()` para atualizar o contador quando o título for assistido.

### Módulo 2: Estruturas de Listas Encadeadas
Responsável pelo gerenciamento de coleções dinâmicas para o histórico de exibição e sugestões de conteúdo.
* **`NoLista.h`**: Contém as estruturas de nós utilizadas pelas listas:
    * `NoSimples`: Ponteiro para `Conteudo` e ponteiro `proximo`.
    * `NoDuplo`: Ponteiro para `Conteudo`, ponteiro `proximo` e ponteiro `anterior`.
* **`ListaRecomendacao.h` / `.cpp`**: Classe `ListaRecomendacao` (Lista Simplesmente Encadeada Ordenada). Organiza sugestões por critérios específicos como ordem alfabética ou avaliação através dos métodos `inserirOrdenado(Conteudo* c)` e `imprimirLista()`.
* **`ListaHistorico.h` / `.cpp`**: Classe `ListaHistorico` (Lista Duplamente Encadeada Ordenada). Mantém o "Top Assistidos" baseado no volume decrescente de visualizações. Métodos: `inserirOrdenado(Conteudo* c)`, `atualizarPosicao(Conteudo* c)` (rearranjo automático pós-visualização) e `imprimirTopAssistidos()`.

### Módulo 3: Motor de Recomendação (Árvore)
Implementa a inteligência de filtragem do sistema baseada em decisões binárias.
* **`NoArvore.h`**: Estrutura do nó de decisão contendo a Pergunta (string), Ponteiro Esquerdo (Sim), Ponteiro Direito (Não) e Ponteiro de Lista para os nós Folha.
* **`ArvoreDecisao.h`**: Gerenciador da árvore que contém o ponteiro raiz e os métodos de navegação e montagem.
* **`ArvoreDecisao.cpp`**: Contém a lógica de percurso, o método `criarArvoreEstatica()` (composta por 6 níveis de profundidade) e o método `navegar(NoArvore* atual)`.

### Módulo 4: Gerenciamento Global e Estatísticas
O núcleo operacional do sistema que conecta todas as estruturas de dados e processa informações analíticas.
* **`SistemaStreaming.h` / `.cpp`**:
    * **Instâncias Globais**: Controla a `ArvoreDecisao`, a `ListaHistorico` e o Contêiner Master de catálogos.
    * **Controle de Fluxo**: 
        * `executarFluxoRecomendacao()`: Inicia o processo de perguntas ao usuário.
        * `assistirConteudo(string titulo)`: Localiza o título desejado, incrementa suas visualizações e reordena o histórico automaticamente.
    * **Análise de Dados**: `exibirEstatisticas()` calcula e exibe o gênero mais e menos recomendado, além de identificar títulos que possuem zero visualizações.

### Módulo 5: Ponto de Entrada (Interface)
* **`main.cpp`**: Interface de interação em modo terminal com o usuário final. Realiza a inclusão do `SistemaStreaming.h`, instancia o objeto principal e gerencia o fluxo através de um loop `while` com uma estrutura `switch-case`.

---

## 💻 Funcionalidades do Menu Principal

Ao executar o sistema, o usuário terá acesso às seguintes opções via terminal:

1.  **Cadastrar Conteúdo**: Permite a inserção de novos títulos no catálogo master.
2.  **Recomendar (Iniciar Árvore)**: Inicia o motor de recomendação navegando pelos 6 níveis de perguntas binárias para sugerir um conteúdo adequado.
3.  **Ver Histórico (Top Assistidos)**: Exibe a lista duplamente encadeada de conteúdos ordenados de forma decrescente pelo número de visualizações.
4.  **Ver Estatísticas de Uso**: Apresenta análises de dados sobre os gêneros mais/menos recomendados e títulos nunca assistidos.
5.  **Sair do Sistema**: Encerra o loop do programa com segurança.

---

## 🚀 Como Compilar e Executar

Para compilar o projeto utilizando o `g++` (ou qualquer compilador compatível com C++), utilize o comando a seguir no terminal a partir do diretório raiz:

```bash
g++ -std=c++17 main.cpp Conteudo.cpp ListaRecomendacao.cpp ListaHistorico.cpp ArvoreDecisao.cpp SistemaStreaming.cpp -o SistemaStreaming
