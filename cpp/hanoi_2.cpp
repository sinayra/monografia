#include <stdio.h>
#include <playAPC/playapc.h>

void hanoi(int n, char a, char b, char c){
 /* mova n discos do pino a para o pino b usando
   o pino c como intermediario                    */

    if (n == 1){
        printf("\nmova disco %d de %c para %c\n", n, a, b);
    }
    else
    {
        hanoi(n - 1, a, c, b);                            // H1
        printf("\nmova disco %d de %c para %c\n", n, a, b);

        hanoi(n - 1, c, b, a);                            // H2
    }
}

int main(void){
    int numDiscos;

    do{
        printf("\nDigite uma quantidade de discos menor ou igual a 5: ");
        scanf("%d", &numDiscos);
    }while(numDiscos > 5 || numDiscos <= 0);

    AbreJanela(400, 400, "Torre de Hanoi");
    PintarFundo(255, 255, 255);
    MostraPlanoCartesiano(10);

    hanoi(numDiscos, 'A', 'B', 'C');

    printf("\nPronto! E assim que se resolve esta torre!");

    Desenha();

    return 0;
}
