//Trabalho 2 – Adivinha 2, Larissa Cavalheiro Pretto

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int sorteio(int sort1, int sort2)
{
    return sort1 + (rand() % sort2);
}

bool novo(void)
{
    char resposta;

    printf("\nGostaria de jogar novamente?(s ou n) ");
    scanf(" %c", &resposta);

    if (resposta == 's') {
        printf("\nO jogo comecara novamente!\n");
        return true;
    }

    return false;
}

int maior(int num, int sort, int anterior1, int posAnteriorMa[], int posAnteriorMe[], int i)
{
    int sorteado;

    if (sort > num) {
        sorteado = sorteio(anterior1, (sort-anterior1));
        posAnteriorMa[i] = sort-anterior1;
        posAnteriorMe[i] = anterior1;
        return sorteado;
    } else {
        printf("Mentira!!\n");
        return 0;
    }
}

int menor(int num, int sort, int anterior1, int anterior2, int posAnteriorMa[], int posAnteriorMe[], int i)
{
    int sorteado;

    if (sort < num) {
        if (i == 0 ) {
            sorteado = sorteio(sort+1, (anterior2-(sort+1)));
        } else {
            sorteado = sorteio(sort+1, (anterior2-((sort+1)-anterior1)));
        }
        posAnteriorMa[i] = anterior2-((sort+1)-anterior1);
        posAnteriorMe[i] = sort+1;
        return sorteado;
    } else {
        printf("Mentira!!\n");
        return 0;
    }
}

int igual(int sort, int num)
{
    if (sort == num) {
        printf("Correto!!\n");
    } else {
        printf("Mentira!!\n");
        return 0;
    }
}

int escolher(int resul, int num, int sort, int anterior1, int anterior2, int posAnteriorMa[], int posAnteriorMe[], int i)
{
    switch (resul) {
        case 1:
            return maior(num, sort, anterior1, posAnteriorMa, posAnteriorMe, i);
            break;
        case 2:
            return menor(num, sort, anterior1, anterior2, posAnteriorMa, posAnteriorMe, i);
            break;
        case 3:
            return igual(sort, num);
            break;
        default:
            printf("Opcao nao encontrada");
            return 0;
    }
}

bool verificar(int num)
{
    int resul, sorteado = sorteio(1, 100), anterior1 = 1, anterior2 = 100, posAnteriorMa[30], posAnteriorMe[30], i = 0;

    do {
        printf("\nDigite se o numero %d eh maior(1), menor(2) ou igual(3) ao numero escolhido: \n", sorteado);
        scanf("%d", &resul);
        sorteado = escolher(resul, num, sorteado, anterior1, anterior2, posAnteriorMa, posAnteriorMe, i);
        if (sorteado == 0) {
            break;
        }
        anterior1 = posAnteriorMe[i];
        anterior2 = posAnteriorMa[i];
        i++;
    } while (resul != 3);

    return novo();
}

int main()
{
    int num;
    bool novo;

    srand(time(NULL));

    do {
        printf("Digite um numero entre 1 e 100 para o programa acertar: ");
        scanf("%d", &num);

        novo = verificar(num);
    } while (novo);

    return 0;
}
