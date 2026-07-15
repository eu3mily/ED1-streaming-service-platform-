# 🎬 ED1 Streaming Service Platform

Um sistema inteligente de recomendação de conteúdo para uma plataforma de streaming. Este projeto simula o núcleo de funcionamento de plataformas modernas, realizando recomendações personalizadas através de uma Árvore de Decisão Binária, ordenando históricos dinamicamente e persistindo os dados dos usuários de forma segura.

> **Trabalho Final da disciplina de Estrutura de Dados 1 (ED1)**

---

## 🌟 Diferenciais e Funcionalidades Extras

Para enriquecer a experiência do usuário e ir além dos requisitos obrigatórios da especificação, implementamos três grandes funcionalidades extras de nível profissional:

1. **💾 Sistema de Persistência Real (Banco de Dados em TXT)**
   O programa não "reseta" quando fecha! Todas as alterações no catálogo (novos cadastros), número de visualizações, histórico de assistidos e notas dadas são salvas automaticamente no arquivo `banco_streaming.txt` ao sair, e recarregadas perfeitamente ao iniciar o sistema.
2. **⭐ Avaliação por Estrelas (Notas de 1 a 5)**
   Ao assistir a um conteúdo recomendado, o usuário pode dar uma nota. O sistema calcula e exibe em tempo real a média geométrica das avaliações de cada filme/série com precisão decimal no catálogo geral.
3. **🔎 Motor de Busca Inteligente (Busca Textual)**
   Implementamos um sistema de busca case-insensitive (ignora maiúsculas/minúsculas) que varre o catálogo principal por aproximação de caracteres. Você pode buscar por `"homem"` e ele listará *"Homem de Ferro"*, *"Homem Aranha"*, etc.
4. **🛡️ Blindagem Total do Terminal**
   Todas as entradas de dados do teclado foram validadas. Se o usuário digitar letras no menu ou nas perguntas de sim/não da árvore, o buffer do `cin` é limpo automaticamente para evitar loops infinitos.

---

## 🛠️ Especificação Técnica e Arquitetura

O sistema foi desenvolvido inteiramente em **C++** e arquitetado de forma modular, dividindo as responsabilidades para aplicar conceitos avançados de estruturas de dados dinâmicas. O projeto está estruturado nos diretórios `include/` (arquivos de cabeçalho) e `src/` (implementações).

### Módulo 1: Entidades (Dados Puros)
Focado na representação dos objetos de negócio e na garantia de sua integridade.
* **`Conteudo.h` / `Conteudo.cpp`**: 
    * **Atributos Base**: Nome (string), Tipo (Filme, Série, Documentário, Anime), Gênero (Ação, Comédia, Drama, Terror, etc.), Ano e Visualizações.
    * **Atributos Extras (Estrelas)**: Soma e Quantidade de avaliações para cálculo de média geométrica.
    * **Interface**: Construtores, Getters/Setters e métodos de negócio (`incrementarVisualizacoes()`, `avaliar()`).

### Módulo 2: Estruturas de Listas Encadeadas
Gerenciamento de coleções dinâmicas de conteúdo.
* **`NoLista.h`**: Contém as estruturas dos nós (`NoSimples` e `NoDuplo`).
* **`ListaRecomendacoes.h` / `.cpp`**: Lista Simplesmente Encadeada que habita as "folhas" da árvore. Organiza as sugestões finais em ordem alfabética para o usuário.
* **`ListaHistorico.h` / `.cpp`**: Lista Duplamente Encadeada que compõe o "Top Assistidos". Reordena automaticamente os nós de forma decrescente toda vez que um título ganha uma visualização, através do método `atualizarPosicao()`.

### Módulo 3: Motor de Recomendação (Árvore)
Implementa a inteligência de filtragem baseada em decisões binárias (Sim/Não).
* **`NoArvore.h`**: Estrutura contendo a Pergunta, Ponteiro Esquerdo (Sim), Ponteiro Direito (Não) e o ponteiro para a `ListaRecomendacoes` (se for um nó folha).
* **`ArvoreDecisao.h` / `.cpp`**: Gerenciador da árvore. Distribui dinamicamente o catálogo nas folhas correspondentes através do método `popularArvore()` e guia o usuário pelas perguntas em `navegar()`.

### Módulo 4: Gerenciamento Global, Estatísticas e Persistência
O orquestrador do sistema (`SistemaStreaming.h` / `.cpp`).
* **Análise de Dados**: Calcula visualizações totais, mapeia os gêneros/tipos mais e menos recomendados e alerta sobre títulos "esquecidos" (zero visualizações).
* **Persistência de Dados (Arquivo TXT)**: O motor de salvamento lê e escreve no arquivo `banco_streaming.txt`, garantindo que novos cadastros, visualizações e notas não sejam perdidos ao fechar o programa.

---

## 💻 Funcionalidades do Menu Principal

A interface via terminal foi blindada contra erros de digitação e navega por opções numéricas fluídas:

1.  **Cadastrar Conteúdo**: Insere novos títulos dinamicamente no catálogo geral e na árvore.
2.  **Receber Recomendações**: Navega pela árvore de perguntas (Sim/Não) para encontrar o título perfeito.
3.  **Ver Histórico (Top Assistidos)**: Exibe a lista dupla em ordem decrescente de popularidade.
4.  **Ver Estatísticas**: Apresenta as métricas de uso detalhadas do sistema.
5.  **Buscar por Nome (Extra)**: Realiza uma busca textual (case-insensitive) diretamente no catálogo.
6.  **Listar Todo o Catálogo**: Exibe o banco de dados completo do sistema com as avaliações por estrelas.
7.  **Sair**: Salva automaticamente todas as alterações no arquivo `.txt` e encerra o sistema.

---

## 🚀 Como Compilar e Executar

O projeto conta com um **Makefile** nativo na raiz para automatizar o processo de compilação, unindo os arquivos das pastas `src/` e `include/`.

**Opção 1: Usando o Makefile (Recomendado)**
Se você possuir o comando `make` ou `mingw32-make` configurado no terminal:
```bash
# Compila o projeto e gera o executável
make all

# Compila e já executa o programa automaticamente
make run

# Limpa o arquivo executável gerado
make clean
```

**Opção 2: Compilação Manual Direta (Terminal Windows/Linux)**
Caso não utilize o Makefile, basta abrir o terminal na pasta raiz do projeto e colar o comando:
```bash
g++ -Wall -Wextra -I include src/*.cpp -o streaming.exe ; .\streaming.exe
```