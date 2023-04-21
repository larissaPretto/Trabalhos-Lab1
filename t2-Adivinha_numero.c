//Trabalho 2 � Adivinha 2, Larissa Cavalheiro Pretto

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

/*A fun��o sorteio() vai sortear um n�mero e retorn�-lo. O intervalo do n�mero a ser sorteado � definido
pelos argumetos, (de sort1 ate sort2).*/
int sorteio(int sort1, int sort2)
{
    return sort1 + (rand() % sort2);
}

/*A fun��o novo() pergunta ao usu�rio se ele quer jogar novamente e se a resposta for 's' ela
retorna true, se n�o ela retorna false. Ela n�o recebe nenhum argumento.*/
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

/*A fun��o maior() vai testar se o n�mero sorteado � maior que o n�mero escolhido. Se for, vai sortear um novo
n�mero entre o �ltimo n�mero sorteado menor que o escolhido e o novo n�mero sorteado, e retorn�-lo. Se n�o for
vai responder ao usu�rio que ele est� mentindo e vai retornar 0. Os argumentos s�o: num = n�mero digitado pelo
usu�rio, sort = n�mero sorteado, anterior1 = �ltimo menor n�mero sorteado, posAnteriorMa[] = armazenar os valores
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

/*A fun��o menor() vai testar se o n�mero sorteado � menor que o n�mero escolhido. Se for, vai sortear um novo
n�mero entre o novo n�mero sorteado + 1(+1 porque o n�mero sorteado j� foi dito que n�o � o correto pelo usu�rio)
e �ltimo n�mero sorteado maior que o escolhido, e retorn�-lo. Se n�o for vai responder ao usu�rio que ele est� mentindo
e vai retornar 0. Os argumentos s�o: num = n�mero digitado pelo usu�rio, sort = n�mero sorteado, anterior1 = �ltimo menor
n�mero sorteado, anterior2 = �ltimo maior n�mero sorteado,posAnteriorMa[] = armazenar os valores de anterior2,
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

/*A fun��o igual() vai testar se o n�mero sorteado � igual ao n�mero escolhido. Se for vai escrever na tela para o usu�rio
que est� correto. Se n�o for vai escrever que o usu�rio est� mentindo e vai retornar 0. Os argumentos s�o: num = n�mero
digitado pelo usu�rio, sort = n�mero sorteado*/
int igual(int sort, int num)
{
    if (sort == num) {
        printf("Correto!!\n");
    } else {
        printf("Mentira!!\n");
        return 0;
    }
}

/*A fun��o escolher() vai testar o n�mero sorteado de acordo com op��o escolhida pelo usu�rio e retornar o resultado.
Se a opcao n�o for encontrada vai retornar 0. Os argumentos s�o: resul = op��o digitada pelo usu�rio, o restante � igual
as da func�o menor(). */
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

/*A fun��o verificar() vai pedir ao usu�rio para digitar se o n�mero sorteado � maior, menor ou igual ao escolhido
e vai testar o sorteado de acordo com a op��o digitada. Se o sorteado for igual 0 significa que o usu�rio mentiu.
Quando o usu�rio digitar 3 ou sorteado == 0, o la�o vai acabar e vai retornar o true ou false da fun��o novo().
O argumento � o n�mero escolhido pelo usu�rio.*/
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
