# 1. Definimos o compilador e as flags de otimização/avisos
CXX = g++
CXXFLAGS = -Wall -Wextra -I include

# 2. Definimos onde estão os arquivos e qual será o nome do executável
SRC = src/*.cpp
EXEC = streaming.exe

# 3. Regra principal: compilar o projeto inteiro
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

# 4. Regra prática: compila tudo e já executa na sequência
run: all
	.\$(EXEC)

# 5. Regra de limpeza: apaga o .exe antigo para forçar uma compilação limpa
clean:
	del /Q $(EXEC)

	// g++ -std=c++17 -I./include src/*.cpp -o bin/programa./bin/programa