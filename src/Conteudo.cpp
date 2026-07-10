#include "Conteudo.h"
#include <iostream>

Conteudo::Conteudo() // vai ser inicializado no core como catalogo geral mesmo
    : nome(""), tipo(""), genero(""), anoLancamento(), numVisualizacoes() {}

Conteudo::Conteudo(string n, string t, string g, int ano, int viz)
    : nome(n), tipo(t), genero(g), anoLancamento(ano), numVisualizacoes(viz) {}

string Conteudo::getNome() const { return nome; }
string Conteudo::getTipo() const { return tipo; }
string Conteudo::getGenero() const { return genero; }
int Conteudo::getAnoLancamento() const { return anoLancamento; }
int Conteudo::getNumVisualizacoes() const { return numVisualizacoes; }

void Conteudo::setNome(string n) { nome = n; }
void Conteudo::setTipo(string t) { tipo = t; }
void Conteudo::setGenero(string g) { genero = g; }
void Conteudo::setAnoLancamento(int ano) { anoLancamento = ano; }

void Conteudo::incrementarVisualizacoes() { 
    numVisualizacoes++; 
}

void Conteudo::exibir() const {
    cout << "► " << nome << " | Tipo: " << tipo << " | Gênero: " << genero 
         << " | Ano: " << anoLancamento << " | Visualizações: " << numVisualizacoes << endl;
}