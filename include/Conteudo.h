#ifndef CONTEUDO_H
#define CONTEUDO_H

#include <string>
using namespace std;

class Conteudo {
private:
    string nome;
    string tipo;
    string genero;
    int anoLancamento;
    int numVisualizacoes;
    int somaAvaliacoes;
    int qtdAvaliacoes;

public:
    // construtores
    Conteudo();
    Conteudo(string n, string t, string g, int ano, int viz = 0);
    
    // getters
    string getNome() const;
    string getTipo() const;
    string getGenero() const;
    int getAnoLancamento() const;
    int getNumVisualizacoes() const;
    float getAvaliacaoMedia() const;
    int getSomaAvaliacoes() const;
    int getQtdAvaliacoes() const;
    
    // setters
    void setNome(string n);
    void setTipo(string t);
    void setGenero(string g);
    void setAnoLancamento(int ano);
    void setAvaliacoes(int soma, int qtd);
    
    // metodos
    void incrementarVisualizacoes();
    void avaliar(int nota);
    
    void exibir() const;
};

#endif