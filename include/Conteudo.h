#ifndef CONTEUDO_H
#define CONTEUDO_H

#include <string> // Biblioteca padrão para manipulação de textos
using namespace std; // Permite usar 'string' diretamente, sem o prefixo 'std::'

class Conteudo {
private:
    // Atributos privados do conteúdo (Encapsulamento puro!)
    string nome;         // Guarda o nome do filme/série/anime/doc
    string tipo;         // Tipo do conteúdo: "Filme", "Serie", etc.
    string genero;       // Gênero: "Acao", "Comedia", "Drama", etc.
    int anoLancamento;   // Ano de publicação do título
    int numVisualizacoes;// Contador acumulado de quantas vezes foi assistido
    
    // Atributos de controle da funcionalidade extra de estrelas
    int somaAvaliacoes;  // Soma acumulada de todas as notas recebidas (ex: 5 + 4 + 5 = 14)
    int qtdAvaliacoes;   // Quantidade total de pessoas que votaram (ex: 3 votos)

public:
    // ==========================================
    //               CONSTRUTORES
    // ==========================================
    
    // Construtor padrão (Sem parâmetros): Inicializa um conteúdo zerado/vazio
    Conteudo();
    
    // Construtor parametrizado: Inicializa o conteúdo com dados reais logo na criação.
    // O parâmetro 'viz' tem valor padrão 0 se não for fornecido (útil na persistência)
    Conteudo(string n, string t, string g, int ano, int viz = 0);
    
    // ==========================================
    //                 GETTERS
    // ==========================================
    // (Métodos 'const' garantem que a função apenas lê, sem alterar as variáveis)
    
    string getNome() const;            // Retorna o nome do título
    string getTipo() const;            // Retorna o tipo
    string getGenero() const;          // Retorna o gênero
    int getAnoLancamento() const;      // Retorna o ano
    int getNumVisualizacoes() const;   // Retorna o número de visualizações
    
    // Getters específicos da funcionalidade de avaliação (estrelas)
    float getAvaliacaoMedia() const;   // Calcula e retorna a nota média (soma / quantidade)
    int getSomaAvaliacoes() const;     // Retorna a soma bruta das notas (usado para salvar no TXT)
    int getQtdAvaliacoes() const;      // Retorna a quantidade bruta de votos (usado para salvar no TXT)
    
    // ==========================================
    //                 SETTERS
    // ==========================================
    // (Permitem alterar os atributos privados com controle e segurança)
    
    void setNome(string n);            // Altera o nome
    void setTipo(string t);            // Altera o tipo
    void setGenero(string g);          // Altera o gênero
    void setAnoLancamento(int ano);    // Altera o ano
    
    // Setter específico da funcionalidade de avaliação
    // (Injeta notas e votos acumulados ao carregar os dados do arquivo TXT)
    void setAvaliacoes(int soma, int qtd);
    
    // ==========================================
    //             MÉTODOS DE NEGÓCIO
    // ==========================================
    
    void incrementarVisualizacoes();   // Adiciona +1 ao contador de visualizações do título
    void avaliar(int nota);            // Soma uma nova nota (1 a 5) e incrementa a contagem de votos
    
    void exibir() const;               // Imprime a ficha técnica completa do conteúdo formatada no terminal
};

#endif