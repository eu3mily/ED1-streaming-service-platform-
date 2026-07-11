#include <iostream>
#include "SistemaStreaming.h"

// Verifica se o sistema operacional é Windows
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

using namespace std;

// rodar tudo 
int main() {
    // Aplica a correção de acentuação APENAS se for Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    SistemaStreaming sistema;
    sistema.menuPrincipal();
    return 0;
}