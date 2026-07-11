#include "Conteudo.h"
#include <iostream>
#include <iomanip> // Necessário para formatar as casas decimais da nota

Conteudo::Conteudo() // vai ser inicializado no core como catalogo geral mesmo
    : nome(""), tipo(""), genero(""), anoLancamento(), numVisualizacoes() {}

// Atualizamos o construtor para iniciar as avaliações a zero
Conteudo::Conteudo(string n, string t, string g, int ano, int viz)
    : nome(n), tipo(t), genero(g), anoLancamento(ano), numVisualizacoes(viz), somaAvaliacoes(0), qtdAvaliacoes(0) {}

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

// --- LÓGICA DE AVALIAÇÃO ---
void Conteudo::avaliar(int nota) {
    somaAvaliacoes += nota;
    qtdAvaliacoes++;
}

float Conteudo::getAvaliacaoMedia() const {
    if (qtdAvaliacoes == 0) return 0.0f; // Evita divisão por zero
    return (float)somaAvaliacoes / qtdAvaliacoes;
}

// --- EXIBIÇÃO ATUALIZADA COM ESTRELAS ---
void Conteudo::exibir() const {
    cout << "► " << nome << " | Tipo: " << tipo << " | Gênero: " << genero 
         << " | Ano: " << anoLancamento << " | Visualizações: " << numVisualizacoes;
         
    if (qtdAvaliacoes > 0) {
        cout << " | Avaliação: " << fixed << setprecision(1) << getAvaliacaoMedia() << " ⭐ (" << qtdAvaliacoes << " votos)" << endl;
    } else {
        cout << " | Avaliação: N/A ⭐ (0 votos)" << endl;
    }
}