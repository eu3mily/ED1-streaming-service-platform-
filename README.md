# 🎬 ED1 Streaming Service Platform

Um sistema inteligente de recomendação de conteúdo para uma plataforma de streaming. Este projeto simula o núcleo de funcionamento de plataformas modernas, realizando recomendações personalizadas através de uma **Árvore de Decisão Binária de 6 níveis**, ordenando históricos dinamicamente e persistindo os dados dos usuários de forma segura.

> **Trabalho Final da disciplina de Estrutura de Dados 1 (ED1)**
> **Professora:** Maria Inés Restovic — DCET-I / Sistemas de Informação / UNEB
> **Discentes:** Emily Camile Veloz Valente e João Victor Novaes Cirino

---

## 🌟 Diferenciais e Funcionalidades Extras

Para enriquecer a experiência do usuário e ir além dos requisitos obrigatórios da especificação, implementamos quatro funcionalidades extras:

1. **💾 Sistema de Persistência Real (Banco de Dados em TXT)**
   O programa não "reseta" quando fecha! Todas as alterações no catálogo (novos cadastros, remoções), número de visualizações, histórico de assistidos e notas dadas são salvas automaticamente no arquivo `banco_streaming.txt` ao sair, e recarregadas perfeitamente ao iniciar o sistema.

2. **⭐ Avaliação por Estrelas!! (Notas de 1 a 5)**
   Ao assistir a um conteúdo recomendado, o usuário pode dar uma nota. O sistema calcula e exibe em tempo real a média das avaliações de cada filme/série com precisão decimal no catálogo geral.

3. **🔎 Motor de Busca Inteligente (Busca Textual)**
   Sistema de busca case-insensitive (ignora maiúsculas/minúsculas) que varre o catálogo principal por aproximação de caracteres. Busque por `"homem"` e o sistema listará *"Homem-Aranha"*, e outros títulos que contenham o termo.

4. **🛡️ Blindagem Total do Terminal**
   Todas as entradas de dados do teclado foram validadas com `cin.fail()` + `cin.clear()`. Se o usuário digitar letras no menu ou nas perguntas de Sim/Não da árvore, o buffer é limpo automaticamente para evitar loops infinitos.

---

## 🛠️ Especificação Técnica e Arquitetura

O sistema foi desenvolvido integralmente em **C++** e arquitetado de forma modular, dividindo as responsabilidades para aplicar conceitos avançados de estruturas de dados dinâmicas. O projeto está estruturado nos diretórios `include/` (arquivos de cabeçalho) e `src/` (implementações).

### Módulo 1: Entidades (Dados Puros)
Focado na representação dos objetos de negócio e na garantia de sua integridade.
* **`Conteudo.h` / `Conteudo.cpp`**:
    * **Atributos Base**: Nome, Tipo (Filme, Série, Documentário, Anime), Gênero (Ação, Comédia, Drama, Terror, etc.), Ano e Visualizações.
    * **Atributos Extras (Estrelas)**: Soma e quantidade de avaliações para cálculo de média aritmética.
    * **Interface**: Construtores, Getters/Setters e métodos de negócio (`incrementarVisualizacoes()`, `avaliar()`).

### Módulo 2: Estruturas de Listas Encadeadas
Gerenciamento de coleções dinâmicas de conteúdo.
* **`NoLista.h`**: Contém as estruturas dos nós (`NoSimples` e `NoDuplo`).
* **`ListaRecomendacoes.h` / `.cpp`**: Lista Simplesmente Encadeada que habita as "folhas" da árvore. Organiza as sugestões finais em **ordem alfabética**.
* **`ListaHistorico.h` / `.cpp`**: Lista Duplamente Encadeada que compõe o "Top Assistidos". Reordena automaticamente os nós em **ordem decrescente de visualizações** através do método `atualizarPosicao()`.

### Módulo 3: Motor de Recomendação (Árvore de 6 Níveis)
Implementa a inteligência de filtragem baseada em decisões binárias (Sim/Não).
* **`NoArvore.h`**: Estrutura contendo a Pergunta, Ponteiro Esquerdo (Sim), Ponteiro Direito (Não) e ponteiro para a `ListaRecomendacoes` (apenas nos nós folha).
* **`ArvoreDecisao.h` / `.cpp`**: Gerenciador da árvore com **6 níveis de decisão**:
  * **Nível 1** — Preferência geral: adrenalina/fantasia vs. leve/reflexivo
  * **Nível 2** — Subcategoria: ação/anime vs. ficção / comédia vs. drama
  * **Nível 3** — Formato: filme vs. série / ficção pura vs. space opera / comédia por época
  * **Nível 4** — Época: recente (2015+) vs. clássico
  * **Nível 5** — Popularidade: blockbuster vs. alternativo
  * **Nível 6** — Folhas com `ListaRecomendacoes` populada dinamicamente via `popularArvore()`

### Módulo 4: Gerenciamento Global, Estatísticas e Persistência
O orquestrador do sistema (`SistemaStreaming.h` / `.cpp`).
* **Cadastro e Remoção**: Inserção e remoção de títulos com reconstrução automática da árvore após cada alteração.
* **Análise de Dados**: Calcula visualizações totais, mapeia os gêneros/tipos mais e menos recomendados e alerta sobre títulos nunca selecionados (zero visualizações).
* **Persistência (Arquivo TXT)**: Lê e escreve no arquivo `banco_streaming.txt`, preservando cadastros, visualizações e notas entre sessões.

---

## 💻 Funcionalidades do Menu Principal

A interface via terminal foi blindada contra erros de digitação e navega por 8 opções numéricas:

| # | Funcionalidade | Descrição |
|---|---|---|
| 1 | **Cadastrar Conteúdo** | Insere novos títulos no catálogo e atualiza a árvore automaticamente |
| 2 | **Remover Conteúdo** | Remove um título pelo número e reconstrói a árvore com o catálogo atualizado |
| 3 | **Receber Recomendações** | Navega pela árvore de 6 níveis (Sim/Não) até a lista de sugestões |
| 4 | **Ver Histórico** | Exibe a lista duplamente encadeada em ordem decrescente de visualizações |
| 5 | **Ver Estatísticas** | Tipo/gênero mais e menos recomendado, top por categoria, títulos nunca vistos |
| 6 | **Buscar por Nome** | Busca textual case-insensitive diretamente no catálogo |
| 7 | **Listar Catálogo** | Exibe todos os títulos com tipo, gênero, ano, visualizações e avaliação |
| 8 | **Sair** | Salva automaticamente tudo no `banco_streaming.txt` e encerra |

---

## 🚀 Como Compilar e Executar

O projeto conta com um **Makefile** nativo na raiz para automatizar o processo de compilação.

**Opção 1: Usando o Makefile (Recomendado)**
```bash
# Compila o projeto e gera o executável
make all

# Compila e já executa o programa automaticamente
make run

# Limpa o arquivo executável gerado
make clean
```

**Opção 2: Compilação Manual Direta**
```bash
# Linux / macOS / Git Bash (Windows)
g++ -std=c++17 -I./include src/*.cpp -o bin/programa
./bin/programa

# Windows (PowerShell / CMD) — listar arquivos explicitamente
g++ -std=c++17 -I./include src/main.cpp src/Conteudo.cpp src/ListaRecomendacoes.cpp src/ListaHistorico.cpp src/ArvoreDecisao.cpp src/SistemaStreaming.cpp -o bin/programa
.\bin\programa.exe
```

> **Atenção:** certifique-se de que a pasta `bin/` existe antes de compilar: `mkdir -p bin`

---

## 📁 Estrutura de Arquivos

```
ED1-streaming-service-platform/
├── include/                  # Arquivos de cabeçalho (.h)
│   ├── Conteudo.h
│   ├── NoLista.h
│   ├── ListaRecomendacoes.h
│   ├── ListaHistorico.h
│   ├── NoArvore.h
│   ├── ArvoreDecisao.h
│   └── SistemaStreaming.h
├── src/                      # Implementações (.cpp)
│   ├── main.cpp
│   ├── Conteudo.cpp
│   ├── ListaRecomendacoes.cpp
│   ├── ListaHistorico.cpp
│   ├── ArvoreDecisao.cpp
│   └── SistemaStreaming.cpp
├── bin/                      # Executável gerado após compilação
├── banco_streaming.txt       # Gerado automaticamente ao sair (persistência)
├── Makefile
└── README.md
```


