# Name of the project
PROJ_NAME=APP

# wildcard pega todos os arquivos com .cpp
CPP_SOURCE=$(wildcard *.cpp)

# wildcard pega todos os arquivos com .h
H_SOURCE=$(wildcard *.h)

# É copiado todos os nomes da variável C_SOURCE para OBJ,
# mas com a substituição da extensão .cpp para .o. 
# Fazemos isso pois inicialmente os arquivos-objeto não existem,
# então a função wildcard seria ineficiente nesse caso.
OBJ=$(CPP_SOURCE:.cpp=.o)

# Compiler
CC=g++

# Flags for compiler
CC_FLAGS=-c -W -Wall

INSTANCE=../instances/p1.2.c.txt
SEED=1
#PROGRAM_ARGS=--algorithm grasp --alpha 0.9 --iterations 4500 --margin 1.9 --removeOperator random --removePercentage 0.15 --shuffleOperator exchange --addOperator best
PROGRAM_ARGS=--algorithm genetic --alpha 0.9 --margin 1.0 --iterations 5000 --populationSize 30 --rate 0.3

all: $(PROJ_NAME)

build: clean $(PROJ_NAME)

test: $(PROJ_NAME) run_test

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^
	
# o simbolo '%' pega o nome do arquivo
# $@ pega o nome o target
# $< pega o nome do pré-requisito 
%.o: %.cpp %.h
	$(CC) -o $@ $< $(CC_FLAGS)

# Esse é caso especial para main.c
main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~

run_test:
	./$(PROJ_NAME)

run:
	./$(PROJ_NAME) 1 1 $(SEED) $(INSTANCE) $(PROGRAM_ARGS)
