#include <stdio.h>
#include <playAPC/playapc.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int grupo, largura;
    char torre;
}tipoDisco;

void geraDiscos(tipoDisco discos[], int numDiscos){
    Ponto p;
    int base, altura;

    for(int i = 0; i < 5; i++){
        discos[i].torre = '0';
        discos[i].grupo = -1;
        discos[i].largura = -1;
    }

    p.y = -90;
    p.x = -100;

    base = 80;
    altura = 10;
    for(int i = numDiscos - 1; i >= 0; i--){
        discos[i].torre = 'A';
        discos[i].grupo = CriaGrupo();
        discos[i].largura = base;

        CriaRetangulo(base, altura, p);
        Pintar(rand()%255, rand()%255, rand()%255);

        base -= 16;
        p.x += 8;
        p.y += 10;

    }
}

int geraFundo(){
    Ponto p;
    int fundo;

    fundo = CriaGrupo();

    p.x = -100;
    p.y = -100;
    CriaRetangulo(200, 10, p);
    Pintar(185, 122, 87);

    p.y = -90;
    //Torre A
    p.x = -66;
    CriaRetangulo(10, 100, p);
    Pintar(0, 128, 255);

    //Torre B
    p.x = -5;
    CriaRetangulo(10, 100, p);
    Pintar(255, 0, 0);

    //Torre C
    p.x = 66;
    CriaRetangulo(10, 100, p);
    Pintar(255, 255, 0);

    return fundo;
}

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
    int grupofundo;
    tipoDisco discos[5];

    srand(time(NULL));

    do{
        printf("\nDigite uma quantidade de discos menor ou igual a 5: ");
        scanf("%d", &numDiscos);
    }while(numDiscos > 5 || numDiscos <= 0);

    AbreJanela(400, 400, "Torre de Hanoi");
    PintarFundo(255, 255, 255);
    MostraPlanoCartesiano(10);

    grupofundo = geraFundo();
    geraDiscos(discos, numDiscos);

    hanoi(numDiscos, 'A', 'B', 'C');

    printf("\nPronto! E assim que se resolve esta torre!");

    Desenha();

    return 0;
}
