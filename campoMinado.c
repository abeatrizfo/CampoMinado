#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Projeto Campo Minado | Ana Beatriz, Laura e Marlus


typedef struct {
    int bomba;
    int aberta;
    int vizinho;
} area;

//variaveis
area campoMinado [TAM][TAM];
int TAM = 0;
int linha, coluna;

//inicializar a matriz do jogo

void inicioCampominado(){
    for(linha = 0; linha < TAM; linha++){
        for(coluna = 0; coluna < TAM; coluna++){
            campoMinado[linha][coluna].bomba = 0;
            campoMinado[linha][coluna].aberta = 0;
            campoMinado[linha][coluna].vizinho = 0;
        }
    }
}

//sorteio das bombas
void sortearBombas(int BOMB){
    int i;
    srand(time(NULL));
    for(i = 1;i <= BOMB; i++){
        linha = rand() % TAM;
        coluna = rand() % TAM;
        if(campoMinado[linha][coluna].bomba == 0)
            campoMinado[linha][coluna].bomba = 1;
        else
            i--;
    }
}

//verifica se a coordenada para verificar as bombas na vizinhaça é valida ou não

int coordenadaValida(int linha, int coluna){
    if(linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM)
        return 1;
    else 
        return 0;
}

//retorno da quantidade de bombas das linhas e colunas.

int quantBombaVizinhas(int linha, int coluna){
    int quantidade = 0;
    if(coordenadaValida(linha - 1, coluna) && campoMinado[linha-1][coluna].bomba)
        quantidade++;
    if(coordenadaValida(linha + 1, coluna) && campoMinado[linha+1][coluna].bomba)
        quantidade++;
    if(coordenadaValida(linha, coluna - 1) && campoMinado[linha][coluna-1].bomba)
        quantidade++;
    if(coordenadaValida(linha, coluna + 1) && campoMinado[linha][coluna+1].bomba)
        quantidade++;
    return quantidade;
}

//contador das bombas vizinhas

void contarBombas(){
    for(linha = 0; linha < TAM; linha++)
        for(coluna = 0; coluna < TAM. coluna++)
            campoMinado[linha][coluna].vizinho = quantBombaVizinhas(linha, coluna);
}

int main(){

    inicioCampominado();
    sortearBombas(int BOMB);
    contarBombas();    
        
    return 0;
}