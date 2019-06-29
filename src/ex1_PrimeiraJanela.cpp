#include <playAPC/playapc.h>
int main(){

    Ponto p;
    AbreJanela(800, 600, "Ola Mundo");

    PintarFundo(255, 255, 255);
    MostraPlanoCartesiano(10);

    p.x = 133;
    p.y = 0;

    CriaCirculo(3, p);
    Pintar(255, 0, 0);

    Desenha();
}

