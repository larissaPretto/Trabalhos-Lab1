//Trabalho 3 – Sudoku, Larissa Cavalheiro Pretto

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

bool linha(int tab[9][9], int num, int l, int c)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                if (j != k && tab[i][j] == tab[i][k] && tab[i][j] != 0) {
                    return true;
                }
            }
            if (i == l && num == tab[i][j]) {
                return true;
            }
        }
    }
    return false;
}

bool coluna(int tab[9][9], int num, int l, int c)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                if (i != k && tab[i][j] == tab[k][j] && tab[i][j] != 0) {
                    return true;
                }
            }
            if (j == c && num == tab[i][j]) {
                return true;
            }
        }
    }
    return false;
}

int setores(int l, int c)
{
    int k1 = 3, cont = 0, k2 = 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cont++;
            if (c < k1) {
                if(l < k2){
                    return cont;
                }
            }
            k2 += 3;
        }
        k1 += 3;
        k2 = 3;
     }
}

bool grupoMenor(int tabMenor[3][3], int num, int setor, int l, int c)
{
    int ok = 0;
    for(int f = 1; f <= 9; f++) {
        for (int i = 0; i <3 ; i++) {
            for (int j = 0; j < 3; j++) {
                if(tabMenor[i][j] == f) {
                    ok++;
                }
                if (ok > 1) {
                    return true;
                }
                if (num == tabMenor[i][j] && setor == setores(l, c)) {
                    return true;
                }
            }
        }
        ok = 0;
    }
    return false;
}

bool grupo(int tab[9][9], int num, int l, int c)
{
    int k1 = 0, k2 = 0, tabMenor[3][3], setor = 0;
    for (int x = 0; x < 3; x++) {
        for (int g = 0; g < 3; g++) {
            for (int i = 0+k1; i < 3+k1; i++) {
                for (int j = 0+k2; j < 3+k2; j++) {
                    tabMenor[i-k1][j-k2] = tab[i][j];
                }
            }
            setor++;
            if (grupoMenor(tabMenor, num, setor, l, c)) {
                return true;
            }
            k1 += 3;
        }
        k1 = 0;
        k2 += 3;
    }
    return false;
}

bool arqNull(FILE *arq, int tab[9][9], char nome[])
{
    if (arq == NULL) {
        if (nome == "tabuleiroInicial.txt") {
            int tabb[9][9] = {{5,3,0,0,7,0,0,0,0},{6,0,0,1,9,5,0,0,0},{0,9,8,0,0,0,0,6,0},{8,0,0,0,6,0,0,0,3},{4,0,0,8,0,3,0,0,1},{7,0,0,0,2,0,0,0,6},{0,6,0,0,0,0,2,8,0},{0,0,0,4,1,9,0,0,5},{0,0,0,0,8,0,0,7,9}};
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    tab[i][j] = tabb[i][j];
                }
            }
            return true;
        } else {
            printf("\nNao foi possivel abrir esse tabuleiro!\nDigite 'l' se quiser procurar novamente\n");
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    tab[i][j] = 0;
                }
            }
            return true;
        }
    }
    return false;
}

int ler_Tab(int tab[9][9], char nome[])
{
    FILE *arq;
    arq = fopen(nome, "r");

    if (arqNull(arq, tab, nome)) {
        salvar(tab, "tabuleiroInicial.txt", 10, 0, 0);
        return 0;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++){
            fscanf(arq, "%d", &tab[i][j]);
        }
    }
    fclose(arq);
    return 0;
}

void desenhar(int tab[9][9])
{
    printf("\n-------------------\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tab[i][j] == 0) {
                printf("| ");
            } else {
                printf("|%d", tab[i][j]);
            }
        }
        printf("|\n");
    }
    printf("-------------------\n");
}

void gravar(int tab[9][9])
{
    char nome[30];
    FILE *arq;

    do {
        printf("\nDigite o nome do novo arquivo: ");
        scanf("%s", nome);
        arq = fopen(strcat(nome,".txt"), "w");
    } while (arq == NULL);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(arq, "%d ", tab[i][j]);
        }
        fprintf(arq, "\n");
    }
    printf("Salvo com sucesso em %s\n", nome);
    fclose(arq);
    desenhar(tab);
}

int salvar(int tab[9][9], char nome[], int num, int l, int c)
{
    if (num != 10) {
        if (linha(tab, num, l,c) || coluna(tab, num, l,c) || grupo(tab, num, l,c)) {
            return 1;
        }
        if (tab[l][c] != 0) {
            return 1;
        }
    }
    FILE *arq;
    arq = fopen(nome, "w");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == l && j == c && num != 10) {
                tab[i][j] = num;
            }
            fprintf(arq, "%d ", tab[i][j]);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
    return 0;
}

bool sair(void)
{
    char resp;
    printf("\nSair do jogo? (s ou n) ");
    scanf(" %c", &resp);

    if (resp == 's') {
        return true;
    }
    return false;
}

bool tabCompleta(int tab[9][9])
{
    if (linha(tab, 10, 0, 0) || coluna(tab, 10, 0, 0) || grupo(tab, 10, 0, 0)) {
        printf("Tabuleiro incorreto\n");
        return false;
    }

    int mult = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            mult *= tab[i][j];
            if (mult == 0) {
                return false;
            }
        }
        mult = 1;
    }
    return true;
}

void carregar(int tab[9][9])
{
    char nome[30];

    printf("\nDigite o nome de um jogo salvo anteriormente: ");
    scanf("%s", nome);

    ler_Tab(tab, strcat(nome,".txt"));
    salvar(tab, "tabuleiroInicial.txt", 10, 0,0);
    desenhar(tab);
}

int opcoes(int num, int tab[9][9], int l, int c)
{
    if (num > 0 && num <= 9 ) {
        scanf("%d %d", &l, &c);
        int resul = salvar(tab, "tabuleiroInicial.txt", num, l, c);
        if(resul == 0){
            desenhar(tab);
        } else {
            printf("Errado!\n");
        }
    } else if (num == 103) {
        gravar(tab);
    } else if (num == 108) {
        carregar(tab);
    } else if (num == 115) {
        if (sair()) {
            return 1;
        }
    } else {
        printf("Opcao nao encontrada!\n");
    }
    return 0;
}

int inicial(void)
{
    int tab[9][9], l, c, sair;
    char num[5];
    ler_Tab(tab, "tabuleiroInicial.txt");
    desenhar(tab);
    while (!tabCompleta(tab)) {
        scanf("%s", num);
        if (strlen(num) == 1){
            if (isdigit(num[0])) {
                sair = opcoes((num[0] - '0'), tab, l, c);
            } else {
                sair = opcoes(num[0], tab, l, c);
            }
        } else {
            printf("Numero fora do intervalo!\n");
        }
        if (sair == 1) {
            return 1;
        }
    }
    return 0;
}

int main()
{
    printf("Bem vindo(a) ao Sudoku!!\n\nA cada rodada escolha uma das opcoes abaixo:\n");
    printf("\n>Digite 'g' para salvar\n>Digite 'l' para ler um jogo salvo anteriormente\n>Digite 's' para sair do jogo\n>Digite um numero entre 1 e 9 para ser colocado no tabuleiro e em seguida sua posicao (linha coluna)\n");

    if(inicial() == 0){
        printf("Jogo completo!!\n");
    }
    return 0;
}
