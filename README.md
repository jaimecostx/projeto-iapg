# **Projeto de Software IAPG PL 2020/2021**
1º Ano, 1º Semestre

Grupo:
* Jaime Costa, 41181
* Nuno Amaro, 41173
---  
Lista de requisitos:

1. ( **Implementado** ) : Todas as perguntas e respetivas respostas são armazenadas num ficheiro ( ..dados/perguntas.csv ).
2. ( **Implementado** ) : No Inicio do jogo é pedido o número dos jogadores, não podendo este exceder quatro. ( A quantidade de jogadores é armazenada numa estrutura `quant.nPlayer` ).
   ```c
    struct data_quant{
        int nPlayer;    //numero de jogadores
        int nCat;       //numero de categorias
        int nRondas;    //numero de rondas
    }quant;
    ```
    ```c
    printf("Numero de Jogadores:");
    scanf("%d", &quant.nPlayer);
    if (quant.nPlayer > 4) {
        printf("Maximo de jogadores e 4\n");
        while (quant.nPlayer >= 5) {
            printf("Insira um numero valido de jogadores: ");
            scanf("%d", &quant.nPlayer);
        }
    }
    ````
3. ( **Implementado** ) : Após inserir o número de jogadores, é pedido o nome dos jogadores através de um ciclo for. ( O nome dos jogadores é armazenado numa estrutura `player[].nome` ).
    ```c
    struct data_player {
        char nome[MAX_SIZE];    //nome do jogador
        int pontos;             //pontos do jogador
        int token;              //token do jogador
    }player[4];
    ```
    ```c
    for (int i = 0; i < quant.nPlayer; i++) {
        printf("Insira o Nome do jogador %d:", i + 1);
        scanf("%s", player[i].nome);
        fflush(stdin);
    }
    ```

4. ( **Implementado** ) : Após cada resposta certa o jogador terá um ponto somado, atraves da função `player[].pontos++`.
    ```c
    if (dados[idPer + 1][0] == rJogador || acertar == 1) {
        printf("Acertaste\n");
        player[j].pontos++;
        printf("%s tens agora %d pontos! ", player[j].nome, player[j].pontos);
    }else{
        printf("Erraste\n");
        printf("%s continuas com %d pontos!\n", player[j].nome, player[j].pontos);
    }
     ```     
5. ( **Parcialmente Implementado** ) : Cada resposta certa vale um ponto e cada errado vale zero pontos, logo o somatório de todas os pontos será o somatório de todas as perguntas certas. 

6. ( **Implementado** ) : No final do jogo a data e hora, o nome dos jogadores e os respetivos pontos, tanto como o melhor score da partida são exportados para o ficheiro ( ..dados/stats.txt ).
    ```
    DATA: Jan 16 2021 
    HORA: 11:34:26

    player 1 : jaime
        pontos : 1 
    player 2 : pedro
        pontos : 2 
    player 3 : maria
        pontos : 1 

    x--HIGHSCORE--x
    player : pedro
        pontos : 2
    ```
7. ( **Implementado** ) : Após escolher a quantidade de jogadores e os respetivos nomes, é pedido ao jogador para escolher a quantidade de rondas que quer jogar, não podendo este ser superior a cinco. ( Uma ronda será um ciclo de uma pergunta que passará por todos os jogadores. A quantidade de rondas é armazenada na estrtura `quant.nRondas`).
    ```c
    printf("Escolha quantas rondas quer: ");
    scanf("%d", &quant.nRondas);
    if (quant.nRondas > 5) {
        printf("Maximo de Rondas e 5\n");
        while (quant.nRondas >= 6) {
            printf("Insira um numero valido de rondas: ");
            scanf("%d", &quant.nRondas);
        }
    }
    ```    
8. ( **Implementado** ) : Se o jogador selecionar a opção "Todas as perguntas" todas as perguntas serão tidas em conta e serão aleatórias, se a opção selecionada for a das categorias as mesmas serão tidas em conta e serão aleatórias dentro da categoria. ( Para este efeito usamos o `srand`).

9. ( **Implementado** ) : Se no menu o jogador selecionar a opção "Selecionar Categoria", será lhe perguntado quantas categorias deseja jogar, onde depois poderá escolher entre quatro categorias (Historia, Geografia, Desporto, Ciencia).

10. ( **Implementado** ) : Ao responder a uma pergunta o jogador tem também a opção de usar o seu "Token", que fará com que essa pergunta seja imediatamente assinalada como certa, e eventualmente ganhe os respetivos pontos. O Token apenas poderá ser usado uma vez no jogo.
