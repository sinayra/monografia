#include <playAPC/playapc.h>

int main(){

    Ponto p;

    AbreJanela(800, 600, "Mantendo proporção da janela");

    PintarFundo(255, 255, 255);
    MostraPlanoCartesiano(10);

    p.x = 132;
    p.y = 0;

    CriaPonto(p);
    Pintar(255, 0, 0);
    Grafite(5);

    Desenha();
    return 0;
}
