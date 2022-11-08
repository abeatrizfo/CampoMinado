#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Projeto Campo Minado: ANA BEATRIZ, LAURA e MARLUS

//Tamanho Máximo do Campo Minado
#define TAM 25

int linha = 5, coluna = 5, bomba = 1; //inicializa as variaveis com o tamanho minimo

/*Define cada casa do campo
Valores:
  -1     ->  Casa que contém bomba
  0 a 4  ->  Quantidade de bombas na vizinhança
Estados:
  0      ->  Não aberto
  1      ->  Aberto
*/
typedef struct {char valor, estado;} casa;

//Coloca as bombas no campo e coloca valores nas casas sem bombas
void armarbombas(casa campominado[TAM][TAM]) {
    int v[linha*coluna], i, j, n, m, x, y, c;

    //Preenche vetor com números de 0 a linha*coluna:
    for (i=0; i < linha*coluna; i++){
        v[i] = i;
    }

    //Embaralha números no vetor usando o algoritmo Knuth Fisher-Yates:
    for (i = linha*coluna-1; i>0; i--){
        n = rand() % (i+1);
        m = v[i];
        v[i] = v[n];
        v[n] = m;
    }
    
    //Zera todas as casas do campo minado
    for (i = 0; i<linha; i++){
        for (j = 0; j<coluna; j++){
            campominado[i][j].estado = 0;
            campominado[i][j].valor = 0;
        }
    }
    
    
    //Usa os primeros números do vetor para determinar as posições onde as bombas vão
    for(i=0; i<bomba; i++){
        printf(" %d", v[i]);
        campominado[v[i]/coluna][v[i]%coluna].valor = -1; //-1 equivale a uma posição que contem uma bomba
    }
    printf("\n");

    //Define o número de cada área do campo minado que não contém uma bomba, ou seja, quantas bombas existem na vizinhança de cada casa
    for (i = 0; i<linha; i++){
        for (j = 0; j<coluna; j++){
            //se a área não tem bomba
            if (campominado[i][j].valor != -1){
                //Conta quantas bombas tem na vizinhança da área e atribui ao valor da área
                c = 0;
                for (x = i-1; x < i+2; x++){
                    for (y = j-1; y < j+2; y++){
                        if (x>=0 && x<linha && y>=0 && y<coluna && campominado[x][y].valor < 0)
                            c++;
                    }
                }
                campominado[i][j].valor = c;
            }
        }
    }
}

//Imprime na tela o campo minado
void imprimircampo(casa campominado[TAM][TAM]){
    int i, j;

    printf("Colunas  ");
    for (i = 0; i<coluna; i++){
        printf(" %c", 'A'+i);
    }
    printf("\n----------");
    for (i = 0; i<coluna; i++){
        printf("--");
    }
    printf("\nLinhas|\n");

    for (i = 0; i<linha; i++){
        printf("  %2d  |  ", i+1);
        for (j = 0; j<coluna; j++){
            if(campominado[i][j].estado == 0) printf(" %c", 254); //casas ainda não reveladas
            else if(campominado[i][j].valor < 0) printf(" %c", 15); //bombas
            else if(campominado[i][j].valor) printf(" %hhd", campominado[i][j].valor); //numero de bombas na vizinhaça
            else printf(" ."); //casa sem bombas ao redor
        }
        printf("\n");
    }
}

//Se não tiver bombas na vizinhança da casa automaticamente abre as casas da vizinhança 
void limpacasasvazias(casa campominado[TAM][TAM], int l, int c){
    int i, j;
    for (i = l-1; i<l+2; i++){
        for (j = c-1; j<c+2; j++){
            //Se a posição existe e a casa não foi aberta
            if (i>=0 && i<linha && j>=0 && j<coluna && campominado[i][j].estado == 0){
                campominado[i][j].estado = 1; //abre a casa
                //Se a nova casa também não tiver bombas na vizinhança
                if(campominado[i][j].valor == 0){
                    limpacasasvazias(campominado, i, j);
                }
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    int i, j, k, op, l;
    char c, ch, parar = 0, venceu;
    casa campominado[TAM][TAM] = {0};


    do {
        printf("\n ~~~~~~~~~~ CAMPO MINADO ~~~~~~~~~~\n\n");

        printf(" 1 - Muito facil   ->  5 x  5 : 1 bomba\n");
        printf(" 2 - Facil  -> 10 x 10 : 5 bombas\n");
        printf(" 3 - Medio -> 15 x 15 : 7 bombas\n");
        printf(" 4 - Dificil -> 20 x 20 : 10 bombas\n");
        printf(" 5 - Muito dificil -> 25 x 25 : 12 bombas\n");
        printf(" 0 - Sair\n\n");

        printf(" Informe qual dificuldade voce quer entre 1 e 5 ou 0 para sair: ");
        scanf("%d", &op);
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch(op){
            case 1:
                linha = 5;
                coluna = 5;
                bomba = 1;
                break;
            case 2:
                linha = 10;
                coluna = 10;
                bomba = 5;
                break;
            case 3:
                linha = 15;
                coluna = 15;
                bomba = 7;
                break;
            case 4:
                linha = 20;
                coluna = 20;
                bomba = 10;
                break;
            case 5:
                linha = 25;
                coluna =25;
                bomba = 12;
                break;
            case 0:
                continue;
            default:
                continue;

        }

        armarbombas(campominado);

        parar = 0;
        while(!parar){
            imprimircampo(campominado);

            printf("\nDigite a coluna e linha (ex: A 1): ");
            scanf("%c%d", &c, &l);
            while ((ch = getchar()) != '\n' && ch != EOF);
            c = toupper(c)-'A';
            l--;
            //Se não for uma posição válida
            if(c<0 || c>=coluna || l<0 || l>=linha)
                continue;

            //Se não tiver bomba
            if(campominado[l][c].valor > 0){
                campominado[l][c].estado = 1;
            }
            else if(campominado[l][c].valor == 0){
                campominado[l][c].estado = 1;
                limpacasasvazias(campominado, l, c);
            }
            //Se tem bombas
            else {
                parar = 1; //Parar
                venceu = 0; //Perdeu
                //Mostra todas as bombas:
                for (i = 0; i<linha; i++){
                    for (j = 0; j<coluna; j++){
                        if(campominado[i][j].valor < 0)
                            campominado[i][j].estado = 1;
                    }
                }
            }

            //Conta o número de casas não abertas
            k = 0;
            for(i=0; i<linha; i++){
                for(j=0; j<coluna; j++){
                    if(campominado[i][j].estado == 0)
                        k++;
                }
            }
            //Se a quantidade de casas não abertas for igual ao número de bombas
            if(k == bomba && !parar){
                parar = 1; //Parar
                venceu = 1; //Vitoria
            }
        }

        imprimircampo(campominado);
        if(venceu)
            printf("\n ### PARABENS voce VENCEU ### \n");
        else
            printf("\n !!! BOOOM voce encontrou uma BOMBA!!! \n");
        while ((ch = getchar()) != '\n' && ch != EOF);

    }while(op != 0);

    return 0;
}
