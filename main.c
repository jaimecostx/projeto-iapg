#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FILE_STATS "../dados/stats.txt"
#define FILE_PERGUNTAS "../dados/perguntas.csv"
#define MAX_SIZE 200

void menu();
void expstats();
void allperguntas(char dados[MAX_SIZE][MAX_SIZE], int nLinhas);
void someperguntas(char dados[MAX_SIZE][MAX_SIZE], int nLinhas);
int rnd(int max);
int obterCategoria(const char pergunta[MAX_SIZE]);
int carregaFicheiro(char dados[MAX_SIZE][MAX_SIZE]);
int obterPerguntaRnd(char dados[MAX_SIZE][MAX_SIZE], int nLinhas, const int pergRepetidas[MAX_SIZE], int nPergtas);

struct data_quant{
    int nPlayer;
    int nCat;
    int nRondas;
}quant;

struct data_player{
    char nome[MAX_SIZE];
    int pontos;
    int token;
}player[4];

int main() {

    printf("DATA: %s \nHORA: %s\n",__DATE__,__TIME__);
    printf("---Jogo Quiz---\nMade by Jaime & Amaro\n");
    printf("Numero de Jogadores:");
    scanf("%d", &quant.nPlayer);
    if (quant.nPlayer>4){
        printf("Maximo de jogadores e 4\n");
        while (quant.nPlayer>=5){
            printf("Insira um numero valido de jogadores: ");
            scanf("%d",&quant.nPlayer);
        }
    }
    for (int i = 0; i < quant.nPlayer; i++) {
        printf("Insira o Nome do jogador %d:", i+1);
        scanf("%s", player[i].nome);
        fflush(stdin);
    }
    printf("----------------------------------\n");
    for (int i = 0; i < quant.nPlayer; i++) {
        printf("player %d: %s\n", i+1, player[i].nome);
    }
    menu();
    return 0;
}

void menu(){
    int cat[4], op;
    for (int i=0; i<4; i++){
        cat[i]=0;
    }
    char dados[MAX_SIZE][MAX_SIZE];

    int nLinhas=carregaFicheiro(dados);

    printf("-----------------------------------\n");
    printf("Escolha quantas rondas quer: ");
    scanf("%d",&quant.nRondas);
    if (quant.nRondas>5){
        printf("Maximo de rondas e 5\n");
        while (quant.nRondas>=6){
            printf("Insira um numero valido de rondas: ");
            scanf("%d",&quant.nRondas);
        }
    }
    printf("1- Todas as perguntas    2- Selecionar categoria\n");
    printf("Escolha uma opCao: ");
    scanf("%d",&op);
    printf("-----------------------------------\n");
    if (op==2) {
        someperguntas(dados, nLinhas);
    }
    else if (op==1){
        printf("Escolheu jogar com todas as perguntas\n");
        allperguntas(dados, nLinhas);
    }
}


void allperguntas(char dados[MAX_SIZE][MAX_SIZE], int nLinhas) {
    int pergRepetidas[MAX_SIZE];
    int nPergtas=0;
    char rJogador;

    for (int i = 0; i < quant.nPlayer; i++) {
        player[i].pontos = 0;
        player[i].token = 1;
    }
    for(int k=0; k<quant.nRondas; k++) {        //percorrer rondas e jogadores
        for (int j = 0; j < quant.nPlayer; j++) {
            int idPer=0;

            printf("\nx-- Ronda de %s --x\n", player[j].nome);
            idPer = obterPerguntaRnd(dados, nLinhas, pergRepetidas, nPergtas);
            pergRepetidas[nPergtas]=idPer;
            nPergtas++;
            fflush(stdin);
            printf("\n-> %s\n", (dados[idPer]+3));
            printf("[T]oken: %d\n",player[j].token);
            int aux;
            int acertar = 0;

            //obter resposta
            do {
                aux=0;
                scanf("%c", &rJogador);
                fflush(stdin);
                //minusculas para maiusculas
                if (rJogador >= 'a' && rJogador <= 'z') {
                    rJogador = rJogador + ('A' - 'a');
                }
                if (rJogador == 'T') {
                    if (player[j].token > 0) {
                        player[j].token--;
                        acertar = 1;
                    } else {
                        printf("Ja nao tens tokens\n");
                        aux=1;
                    }
                }
            }while (aux==1);


            //comparar resposta do Jogador com resposta Correta
            if (dados[idPer+1][0] == rJogador || acertar==1) {
                printf("Acertaste\n");
                player[j].pontos++;
                printf("%s tens agora %d pontos!\n", player[j].nome, player[j].pontos);
            } else {
                printf("Erraste\n");
                printf("%s continuas com %d pontos!\n", player[j].nome, player[j].pontos);
            }
        }
    }
    expstats();
}

void someperguntas(char dados[MAX_SIZE][MAX_SIZE], int nLinhas){
    int cat[4];
    int pergRepetidas[MAX_SIZE];
    int nPergtas=0;
    char rJogador;

    for (int i = 0; i < quant.nPlayer; i++) {
        player[i].pontos = 0;
        player[i].token = 1;
    }
    printf("Com quantas categorias deseja jogar? (maximo 4): ");
    scanf("%d",&quant.nCat);
    if (quant.nCat>4){
        printf("Maximo de categorias e 4\n");
        while (quant.nCat>=5){
            printf("Insira um numero valido de categorias: ");
            scanf("%d",&quant.nCat);
        }
    }
    printf("[1] - Historia\n[2] - Geografia\n[3] - Desporto\n[4] - Ciencias");
    for (int x=0; x<quant.nCat; x++){
        printf("\nSelecione uma categoria: ");
        scanf("%d",&cat[x]);
        fflush(stdin);
    }

    for(int k=0; k<quant.nRondas; k++) {        //percorrer rondas e jogadores
        for (int j = 0; j < quant.nPlayer; j++) {
            char catExiste=0;
            int idPer=0;

            printf("\n\nx-- Ronda de %s --x\n", player[j].nome);

            do {
                catExiste=0;
                idPer = obterPerguntaRnd(dados, nLinhas, pergRepetidas, nPergtas);
                int catPerg = obterCategoria(dados[idPer]);
                for (int i = 0; i < quant.nCat; i++)
                    if (catPerg == cat[i])
                        catExiste = 1;
            }while (catExiste==0);

            pergRepetidas[nPergtas]=idPer;
            nPergtas++;
            fflush(stdin);
            printf("%s\n", dados[idPer]+3);
            printf("[T]oken: %d\n",player[j].token);
            int aux;
            int acertar = 0;

            //obter resposta
            do {
                aux=0;
                scanf("%c", &rJogador);
                fflush(stdin);
                //minusculas para maiusculas
                if (rJogador >= 'a' && rJogador <= 'z') {
                    rJogador = rJogador + ('A' - 'a');
                }
                if (rJogador == 'T') {
                    if (player[j].token > 0) {
                        player[j].token--;
                        acertar = 1;
                    } else {
                        printf("Ja nao tens tokens\n");
                        aux=1;
                    }
                }
            }while (aux==1);

            //comparar resposta do Jogador com resposta Correta
            if (dados[idPer+1][0] == rJogador || acertar==1) {
                printf("Acertaste\n");
                player[j].pontos++;
                printf("%s tens agora %d pontos! ", player[j].nome, player[j].pontos);
            } else {
                printf("Erraste\n");
                printf("%s continuas com %d pontos!\n", player[j].nome, player[j].pontos);
            }
        }
    }
    expstats();
}

int rnd(int max){
    int num=0;
    srand(time(NULL));
    num = rand() % max;
    if (num % 2!= 0) {
        num++;
    }
    return num;
}

//retorna 1 se a pergunta é repetida, 0 se nâo é repetida
char perguntaRepetida(int num, const int pergRepetidas[MAX_SIZE], int nPergtas){
    char repetida=0;
    for(int i=0; i<nPergtas; i++)
    {
        if(pergRepetidas[i]==num)
        {
            repetida=1;
            break;
        }
    }
    return repetida;
}

//retorna categoria da pergunta
int obterCategoria(const char pergunta[MAX_SIZE]){
    char catCh[2];
    catCh[0]=pergunta[0];
    catCh[1]='\0';
    return atoi(catCh);
}

//obtem pergunta e resposta randoms, retorna o nº da pergunta
int obterPerguntaRnd(char dados[MAX_SIZE][MAX_SIZE], int nLinhas, const int pergRepetidas[MAX_SIZE], int nPergtas){
    int idLinha = 0;
    int repetida =0;

    do {
        idLinha = rnd(nLinhas);
        repetida = perguntaRepetida(idLinha, pergRepetidas, nPergtas);
    } while(repetida == 1);
    return idLinha;
}

//carrega dados do ficheiro e retorna o nº de linhas do ficheiro -1
int carregaFicheiro(char dados[MAX_SIZE][MAX_SIZE]){
    FILE *fp = fopen(FILE_PERGUNTAS, "r");
    int i=1;
    while (fgets(dados[i-1], MAX_SIZE, fp) != NULL){
        i++;
    }
    fclose(fp);
    return i-1;
}

//perpara o ficheiro das stats e obtem o vencedor da partida
void expstats(){
    FILE *gp = fopen(FILE_STATS, "w");
    fprintf(gp ,"DATA: %s \nHORA: %s\n",__DATE__,__TIME__);
    fprintf(gp,"\n");
    int highscore;
    char phighscore[MAX_SIZE];

    for (int i=0; i<quant.nPlayer;i++){
        fprintf(gp,"player %d : %s\n", i+1, player[i].nome);
        fprintf(gp,"   pontos : %d \n", player[i].pontos);
    }

    for (int i=0; i<quant.nPlayer;i++){
        if(player[i].pontos > player[i-1].pontos){
            highscore = player[i].pontos;
            strcpy(phighscore,player[i].nome);
        }
    }
    printf("\n\nx--HIGHSCORE--x");
    printf("\nplayer : %s",phighscore);
    printf("\n  pontos : %d", highscore);
    fprintf(gp,"\nx--HIGHSCORE--x");
    fprintf(gp,"\nplayer : %s",phighscore);
    fprintf(gp,"\n  pontos : %d", highscore);
}