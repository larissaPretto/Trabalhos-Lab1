//Trabalho 4 – get10, Larissa Cavalheiro Pretto

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int maior = 3;

void preenche(int m[5][5], int max)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (m[i][j] == 0) {
                m[i][j] = 1 + (rand() % max);
            }
        }
    }
}

bool tem_jogada(int m[5][5])
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (m[i][j] == m[i][j-1] || m[i][j] == m[i][j+1] || m[i][j] == m[i-1][j] || m[i][j] == m[i+1][j]) {
                return true;
            }
        }
    }
    return false;
}

void sobe_zeros(int m[5][5])
{
    for (int j = 0; j < 5; j++ ) {
        for (int i = 4; i >= 0; i--) {
            if (m[i][j] == 0) {
                for (int k = 1; k < 5; k++) {
                    if (m[i-k][j] != 0 && i-k >=0) {
                        m[i][j] = m[i-k][j];
                        m[i-k][j] = 0;
                        break;
                    }
                }
            }
        }
    }
}

int troca_regiao_por_zeros(int m[5][5], int lin, int col, int val, int trocados)
{
    if (m[lin][col-1] == val && col-1 >= 0) {
        m[lin][col-1] = 0;
        trocados++;
        trocados = troca_regiao_por_zeros(m, lin, col-1, val, trocados);
    }
    if (m[lin][col+1] == val && col+1 < 5) {
        m[lin][col+1] = 0;
        trocados++;
        trocados = troca_regiao_por_zeros(m, lin, col+1, val, trocados);
    }
    if (m[lin-1][col] == val && lin-1 >= 0) {
        m[lin-1][col] = 0;
        trocados++;
        trocados = troca_regiao_por_zeros(m, lin-1, col, val, trocados);
    }
    if (m[lin+1][col] == val && lin+1 < 5) {
        m[lin+1][col] = 0;
        trocados++;
        trocados = troca_regiao_por_zeros(m, lin+1, col, val, trocados);
    }
    return trocados;
}

int joga(int m[5][5], int lin, int col)
{
    int val = m[lin][col], trocados = 0;
    int novoval = val+1;
    int n = troca_regiao_por_zeros(m, lin, col, val, trocados);
    if (n > 1) {
        m[lin][col] = novoval;
        int pontos = n * novoval;
        sobe_zeros(m);
        if (novoval > maior) {
            maior = novoval;
            pontos *= 2;
        }
        preenche(m, maior-1);
        return pontos;
    } else {
        m[lin][col] = val;
        return 0;
    }
}

void le_jogada(int *lin, int *col)
{
    int x, y;
    do {
        printf("Digite a linha e coluna onde quer jogar: ");
        scanf("%d%d", &x, &y);
    } while (x<0 || x>4 || y<0 || y>4);
    *lin = x;
    *col = y;
}

void muda_cor(int letra, int fundo)
{
    printf("%c[%d;%dm", 27, 30+letra, 40+fundo);
}

void volta_cor(void)
{
    printf("%c[0m", 27);
}

void cores(int num)
{
    switch (num) {
        case 1: muda_cor(7,6);
            break;
        case 2: muda_cor(7,2);
            break;
        case 3: muda_cor(7,3);
            break;
        case 4: muda_cor(7,4);
            break;
        case 5: muda_cor(7,5);
            break;
        case 6: muda_cor(7,1);
            break;
        case 7: muda_cor(0,7);
            break;
        case 8: muda_cor(0,1);
            break;
        case 9: muda_cor(0,2);
            break;
        case 10: muda_cor(0,3);
            break;
        default: muda_cor(0,4);
            break;
    }
}

void mostra(int m[5][5], int pontos)
{
    printf("\n    Pontos: %d\n", pontos);
    printf("\n   0  1  2  3  4");
    printf("\n  ---------------\n0 ");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cores(m[i][j]);
            printf("|%d|", m[i][j]);
        }
            if (i+1 == 5) {
                printf("\n");
            } else {
                volta_cor();
                printf("\n%d ", i+1);
            }
    }
    volta_cor();
    printf("  ---------------\n");
}

void apresentacao_e_boas_vindas(void)
{
    printf("Bem vindo(a) ao get10!!\n\n");
    printf(">Digite a posicao do bloco em que algum dos blocos vizinhos sejam iguais\nao seu, para entao, junta-los em em um unico bloco de numero maior.\n");
    printf("\n>O objetivo do jogo eh fazer o maior numero de pontos \ne ter os maiores valores possiveis nas posicoes.\n");
    printf("\n>O jogo termina quando nao tiver mais jogadas possiveis.\n\n");
}

void despedida(int pontos)
{
    int pontuacao;
    FILE *arq;
    arq = fopen("pontuacao", "r");

    if (arq == NULL) {
        arq = fopen("pontuacao", "w");
        fprintf(arq, "0");
    }
    fscanf(arq, "%d", &pontuacao);
    fclose(arq);

    if (pontos > pontuacao) {
        printf("\nParabens!! Voce marcou %d pontos e quebrou o antigo recorde de %d pontos!\n", pontos, pontuacao);
        arq = fopen("pontuacao", "w");
        fprintf(arq, "%d", pontos);
        fclose(arq);
    } else {
        printf("\nVoce marcou %d pontos, mas nao conseguiu quebrar o antigo recorde de %d pontos!\n", pontos, pontuacao);
    }
}

int main()
{
    int tabuleiro[5][5] = { {0} };
    int pontos = 0;
    int l, c;
    srand(time(NULL));

    preenche(tabuleiro, maior);
    apresentacao_e_boas_vindas();

    while (tem_jogada(tabuleiro)) {
        mostra(tabuleiro, pontos);
        le_jogada(&l, &c);
        pontos += joga(tabuleiro, l, c);
    }

    despedida(pontos);
    return 0;
}
