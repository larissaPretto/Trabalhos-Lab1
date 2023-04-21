// Trabalho 5 – largue o número, Larissa Cavalheiro Pretto

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

int max = 4, pontos = 0, colInicial;

int sorteio(int max)
{
    return pow(2, 1 + (rand() % (max-1)));
}

void muda_cor(int letra, int fundo)
{
    printf("%c[%d;%dm", 27, 30+letra, 40+fundo);
}

void volta_cor(void)
{
    printf("%c[0m", 27);
}

void mostra(int tab[6][5], int pontos)
{
    printf("\n        Pontos: %d\n", pontos);
    printf("\n    1   2   3   4   5");
    printf("\n  ---------------------\n  ");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            volta_cor();
            printf("|");
            if (tab[i][j] == 0) {
                printf("   ");
            } else if (tab[i][j] < 0) {
                muda_cor(7,6);
                tab[i][j] = tab[i][j]*-1;
                printf("%2d ", tab[i][j]);
            } else {
                printf("%2d ", tab[i][j]);
            }
        }
        volta_cor();
        printf("|\n  ");
    }
    printf("---------------------\n");
}

void espera_enter(void)
{
    while (true) {
        int c;
        c = getchar();
        if (c == '\n') {
            break;
        }
    }
}

int le_jogada(int val, int proxVal)
{
    char x;
    do {
        printf(" O numero atual eh %d e o proximo numero eh %d \n Digite uma coluna para colocar o numero atual: ", val, proxVal);
        scanf(" %c", &x);

        if (x == 's' || x == 'a') {
            break;
        }
    } while (x < '1' || x > '5');

    espera_enter();
    return x;
}

int cai_numero(int tab[6][5], int c, int val)
{
    for (int i = 5; i >= 0; i--) {
        for (int j = 0; j < 5; j++) {
            if (j == c && tab[i][j] == 0) {
                tab[i][j] = val;
                return i;
            }
        }
    }
    return 7;
}

void sobe_zeros(int tab[6][5])
{
    for (int j = 0; j < 5; j++ ) {
        for (int i = 5; i >= 0; i--) {
            if (tab[i][j] == 0) {
                for (int k = 1; k < 6; k++) {
                    if (tab[i-k][j] != 0 && i-k >=0) {
                        tab[i][j] = tab[i-k][j];
                        tab[i-k][j] = 0;
                        break;
                    }
                }
            }
        }
    }
}

bool num_negativos(int tab[6][5], int l, int c, int val)
{
    bool troca = false;
    if (tab[l][c-1] == val && c-1 >= 0) {
        tab[l][c] = -val;
        tab[l][c-1] = -val;
        troca = true;
        juntar_grupo(tab, l, c-1, val);
    }
    if (tab[l][c+1] == val && c+1 < 5) {
        tab[l][c] = -val;
        tab[l][c+1] = -val;
        troca = true;
        juntar_grupo(tab, l, c+1, val);
    }
    if (tab[l+1][c] == val && l+1 < 6) {
        tab[l][c] = -val;
        tab[l+1][c] = -val;
        troca = true;
        juntar_grupo(tab, l+1, c, val);
    }

    return troca;
}

int juntar_grupo(int tab[6][5], int l, int c, int val,  int trocados)
{
    if (tab[l][c-1] == val && c-1 >= 0) {
        tab[l][c] = 0;
        tab[l][c-1] = 0;
        trocados++;
        trocados = juntar_grupo(tab, l, c-1, val, trocados);
    }
    if (tab[l][c+1] == val && c+1 < 5) {
        tab[l][c] = 0;
        tab[l][c+1] = 0;
        trocados++;
        trocados = juntar_grupo(tab, l, c+1, val, trocados);
    }
    if (tab[l+1][c] == val && l+1 < 6) {
        tab[l][c] = 0;
        tab[l+1][c] = 0;
        trocados++;
        trocados = juntar_grupo(tab, l+1, c, val, trocados);
    }
    return trocados;
}

int tem_jogo(int tab[6][5])
{
     for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            if (tab[i][j] != 0 && j < 4 && tab[i][j] == tab[i][j+1] || tab[i][j] != 0 && i < 5 && tab[i][j] == tab[i+1][j]) {
                jogada(tab, j, i, tab[i][j]);
            }
        }
    }
    return 0;
}

int escolhe_coluna(int tab[6][5])
{
    int cPrimeira = 4, cUltima = 0;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            if (tab[i][j] < 0) {
                if (j < cPrimeira) {
                    cPrimeira = j;
                }
                if (j > cUltima) {
                    cUltima = j;
                }
            }
        }
    }
    if (cUltima < colInicial) {
        return cUltima;
    } else if (cPrimeira > colInicial) {
        return cPrimeira;
    } else {
        return colInicial;
    }
}

void jogada(int tab[6][5], int c, int l, int val)
{
    int trocados = 0, n, colResul;

    if (l == 7) {
        l = cai_numero(tab,c,val);
    }
    if (num_negativos(tab, l, c, val)) {
        colResul = escolhe_coluna(tab);
        mostra(tab, pontos);
        espera_enter();
    }
    n = juntar_grupo(tab, l, c, val, trocados);
    int novoValor = val * pow(2, n);

    if (n > 0){
        tab[l][colResul] = novoValor;
        sobe_zeros(tab);
        pontos += val * pow(2, n);
        if (novoValor > pow(2, max)) {
            max++;
        }
        tem_jogo(tab);
    }
}

bool gravar_tab(int tab[6][5], char nome[])
{
    FILE *arq;
    arq = fopen(nome, "w");
    if (arq == NULL) {
        return false;
    }
    fprintf(arq, "%d\n", max);
    fprintf(arq, "%d\n", pontos);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            fprintf(arq, "%d ", tab[i][j]);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
    return true;
}

bool salvar_jogo(int tab[6][5])
{
    char nome[20];
    printf(" Digite o nome do arquivo a salvar: ");
    scanf("%s", nome);
    if (!gravar_tab(tab, nome)) {
        printf(" Problema na gravacao\n");
    }
    printf("\n Jogo salvo com sucesso\n");
    return false;
}

bool abandonar_jogo(int tab[6][5])
{
    char resposta;
    printf("\n Partida encerrada!\n");
    printf(" \n Deseja jogar novamente? (s ou n) ");
    scanf(" %c", &resposta);

    if (resposta == 's') {
        printf("\n Um novo jogo foi criado!\n");
        return true;
    }
    return false;
}

bool tab_completa(int tab[6][5])
{
     for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            if (tab[i][j] == 0) {
                return true;
            }
        }
     }
     return false;
}

typedef struct
{
    char apelido[8];
    int pontosFinal;
} pontuacao;

void criar_arquivo(FILE *arq)
{
    arq = fopen("pontuacao", "w");
    if (arq == NULL) {
        printf("nao foi possivel abrir o arquivo\n");
        exit(1);
    }
    fprintf(arq, "%d\n", 1);
    fprintf(arq, "%s %d\n","larissa", 100);
    printf(" \n Nao foi encontrado o arquivo com o historico de pontuacao\n");
    printf(" Entao um arquivo de pontuacao foi criado, reinicie o programa\n");
    exit(0);
}

pontuacao *aloca(int *total_jog)
{
    int i;
    FILE *arq;

    arq = fopen("pontuacao", "r");
    if (arq == NULL) {
        criar_arquivo(arq);
    }

    int n;
    fscanf(arq, "%d", &n);
    pontuacao *v;

    v = malloc(n*sizeof(pontuacao));
    if (v == NULL) {
        printf("erro de alocacao de memoria");
        exit(1);
    }
    for (i = 0; i < n; i++) {
        fscanf(arq, "%s %d", v[i].apelido, &v[i].pontosFinal);
    }
    fclose(arq);
    *total_jog = i;
    return v;
}

void grava_pontuacao(int total_jog, pontuacao p[], char apelido[])
{
    FILE *arq;
    int aux1, i, lugar;
    char aux2[8];

    arq = fopen("pontuacao", "w");
    if (arq == NULL) {
        printf("nao consegui abrir arquivo para gravacao\n");
        return;
    }
    fprintf(arq, "%d\n", total_jog);

    for (i = total_jog-1; i >= 0; i--) {
        if (p[i].pontosFinal < pontos) {
            aux1 = p[i+1].pontosFinal;
            strcpy(aux2, p[i+1].apelido);
            p[i+1] = p[i];
            p[i].pontosFinal = aux1;
            strcpy(p[i].apelido, aux2);
            if (pontos == p[i].pontosFinal) {
                lugar = i;
            }
        } else if (p[total_jog-1].pontosFinal == pontos){
            lugar = total_jog-1;
        }
    }
    for (int k = 0; k < total_jog; k++) {
        fprintf(arq, "%s %d\n", p[k].apelido, p[k].pontosFinal);
    }

    if (lugar+1 <= 10) {
        printf("\n Parabens!! Voce conseguiu se classificar no top 10 em %d lugar no historico de pontos\n\n", lugar+1);
        for (int j = 0; j < total_jog; j++) {
            printf(" %2d - %8s | %d\n", j+1, p[j].apelido, p[j].pontosFinal);
            if (j == 9) break;
        }
    } else {
        printf(" \n Voce ficou classificado em %d lugar no historico de pontos\n", lugar+1);
    }
    fclose(arq);
}

void fim_de_jogo(int total_jog, pontuacao p[])
{
    char nome[8];

    printf("\n Fim de jogo!! Voce marcou %d pontos!\n", pontos);
    printf("\n Top 10 maiores pontuacoes do jogo:\n\n");

    for (int i = 0; i < total_jog; i++) {
         printf(" %2d - %8s | %d\n",i+1, p[i].apelido, p[i].pontosFinal);
         if (i == 9) break;
    }

    printf("\n\n Digite um apelido para salvar sua pontuacao: ");
    scanf("%s", nome);

    total_jog++;
    pontuacao *p2;
    p2 = realloc(p, total_jog*sizeof(pontuacao));

    if (p2 == NULL) {
        printf("erro na alocacao\n");
        exit(1);
    }
    p = p2;
    strcpy(p[total_jog-1].apelido, nome);
    p[total_jog-1].pontosFinal = pontos;

    grava_pontuacao(total_jog, p, nome);
}

bool carregar_jogo(int tab[6][5], char nome[])
{
    FILE *arq;
    arq = fopen(nome, "r");
    if (arq == NULL) {
        return false;
    }
    fscanf(arq, "%d", &max);
    fscanf(arq, "%d", &pontos);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(arq, "%d", &tab[i][j]);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
    return true;
}

void continuar_jogo(int tab[6][5])
{
    char resp, nome[20];

    printf("\n Gostaria de continuar algum jogo? (s ou n) ");
    scanf("%c", &resp);

    if (resp == 's') {
        printf("\n Digite o nome do jogo salvo: ");
        scanf(" %s", nome);

        if (carregar_jogo(tab, nome)) {
            printf("\n Jogo salvo em %s carregado com sucesso!\n", nome);
        } else {
            printf("\n Arquivo nao encontrado. Sera iniciado um novo jogo!\n");
        }
    } else {
        printf("\n Um novo jogo foi criado!\n");
    }
}

void zerar_jogo(int tab[6][5])
{
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            tab[i][j] = 0;
        }
    }
    pontos = 0;
    max = 4;
}

void apresentacao(void)
{
    printf(" Bem vindo ao jogo largue o numero!\n\n");
    printf(" Junte os numeros iguais e faca o maximo de pontos que conseguir.\n");
    printf(" O jogo acaba quando nao puder colocar mais numeros no tabuleiro.\n\n");
    printf(" Digite 'a' para abandonar a partida.\n");
    printf(" Digite 's' para encerrar e salvar o jogo.\n");
}

int main()
{
    int tab[6][5] = { {0} }, val, proxVal = sorteio(max), l, total_jog;
    char c, resp;
    pontuacao *p;
    srand(time(0));
    apresentacao();
    continuar_jogo(tab);

    do {
        p = aloca(&total_jog);
        do {
            l = 7;
            mostra(tab, pontos);
            val = proxVal;
            proxVal = sorteio(max);
            c = le_jogada(val, proxVal);
            if (c == 's') {
                salvar_jogo(tab);
                return 0;
            } else if (c == 'a') {
                if(abandonar_jogo(tab)) {
                    zerar_jogo(tab);
                    continue;
                } else {
                    return 0;
                }
            } else {
                colInicial = c - '0' - 1;
                jogada(tab, c - '0' - 1, l, val);
            }
        } while(tab_completa(tab));

        fim_de_jogo(total_jog, p);
        free(p);
        if (abandonar_jogo(tab)) {
            zerar_jogo(tab);
        } else {
            break;
        }
    } while(true);

    return 0;
}