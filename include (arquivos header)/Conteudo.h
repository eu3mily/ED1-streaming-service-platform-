#ifndef CONTEUDO_H
#define CONTEUDO_H

#include <string>
using namespace std;

class Conteudo {
private:
    string nome;
    string tipo;           // Filme, Serie, Documentario, Anime, Outros
    string genero;         // Acao, Comedia, Drama, Terror, Ficcao, Outros
    int anoLancamento;
    int numVisualizacoes;

public:
    // Construtores
    Conteudo();
    Conteudo(string n, string t, string g, int ano, int viz = 0);
    
    // Getters
    string getNome() const;
    string getTipo() const;
    string getGenero() const;
    int getAnoLancamento() const;
    int getNumVisualizacoes() const;
    
    // Setters
    void setNome(string n);
    void setTipo(string t);
    void setGenero(string g);
    void setAnoLancamento(int ano);
    
    // Métodos especiais
    void incrementarVisualizacoes();
    void exibir() const;
};

#endif