//Trabalho 2 – Adivinha 2, Larissa Cavalheiro Pretto

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

/*A função sorteio() vai sortear um número e retorná-lo. O intervalo do número a ser sorteado é definido
pelos argumetos, (de sort1 ate sort2).*/
int sorteio(int sort1, int sort2)
{
    return sort1 + (rand() % sort2);
}

/*A função novo() pergunta ao usuário se ele quer jogar novamente e se a resposta for 's' ela
retorna true, se não ela retorna false. Ela não recebe nenhum argumento.*/
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

/*A função maior() vai testar se o número sorteado é maior que o número escolhido. Se for, vai sortear um novo
número entre o último número sorteado menor que o escolhido e o novo número sorteado, e retorná-lo. Se não for
vai responder ao usuário que ele está mentindo e vai retornar 0. Os argumentos são: num = número digitado pelo
usuário, sort = número sorteado, anterior1 = último menor número sorteado, posAnteriorMa[] = armazenar os valores
de anterior2, posAnteriorMe[] = armazenar os valores de anterior1, i = contador.*/
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

/*A função menor() vai testar se o número sorteado é menor que o número escolhido. Se for, vai sortear um novo
número entre o novo número sorteado + 1(+1 porque o número sorteado já foi dito que não é o correto pelo usuário)
e último número sorteado maior que o escolhido, e retorná-lo. Se não for vai responder ao usuário que ele está mentindo
e vai retornar 0. Os argumentos são: num = número digitado pelo usuário, sort = número sorteado, anterior1 = último menor
número sorteado, anterior2 = último maior número sorteado,posAnteriorMa[] = armazenar os valores de anterior2,
posAnteriorMe[] = armazenar os valores de anterior1, i = contador.*/
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

/*A função igual() vai testar se o número sorteado é igual ao número escolhido. Se for vai escrever na tela para o usuário
que está correto. Se não for vai escrever que o usuário está mentindo e vai retornar 0. Os argumentos são: num = número
digitado pelo usuário, sort = número sorteado*/
int igual(int sort, int num)
{
    if (sort == num) {
        printf("Correto!!\n");
    } else {
        printf("Mentira!!\n");
        return 0;
    }
}

/*A função escolher() vai testar o número sorteado de acordo com opção escolhida pelo usuário e retornar o resultado.
Se a opcao não for encontrada vai retornar 0. Os argumentos são: resul = opção digitada pelo usuário, o restante é igual
as da funcão menor(). */
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

/*A função verificar() vai pedir ao usuário para digitar se o número sorteado é maior, menor ou igual ao escolhido
e vai testar o sorteado de acordo com a opção digitada. Se o sorteado for igual 0 significa que o usuário mentiu.
Quando o usuário digitar 3 ou sorteado == 0, o laço vai acabar e vai retornar o true ou false da função novo().
O argumento é o número escolhido pelo usuário.*/
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
