#ifndef CONTEUDO_H
#define CONTEUDO_H

#include <string>
using namespace std;

class Conteudo {
private:
    string nome;
    string tipo;           // filme, serie, documentario e anime
    string genero;         // acao, comedia, drama, terror e ficcao cientifica
    int anoLancamento;
    int numVisualizacoes;

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
    
    // setters
    void setNome(string n);
    void setTipo(string t);
    void setGenero(string g);
    void setAnoLancamento(int ano);
    
    // metodos
    void incrementarVisualizacoes();
    void exibir() const;
};

#endif