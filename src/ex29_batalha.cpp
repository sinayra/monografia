#include <playAPC/playapc.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    Ponto esq;
    int index;
}tipoVisu;

//Legenda para mLog
// -2: água atingida
// -1: navio afundado
// 0 : água
// 1 : navio escondido
// 2 : navio atingido, mas não afundado
// 3: água ao redor do navio (auxiliar, depois será substituído por 0)

int main(){
    int gfundo, gclicavel, gbalao, aberta = 1, contnavio = 0, pedaco;
    Ponto p, p2;
    int mLog[9][9];
    tipoVisu mVisu[9][9];
    int xtab = 0, ytab = 0, xpos, ypos, x, y;
    int imgponteiro, imgaviso, imgtransparente, imgagua, imgfogo, imgdestrocos, imgmar, imgtelabatalha;
    int tam, qtd, sentido, valido;

    srand(time(NULL));


    AbreJanela(850, 666, "Batalha Naval");
    MostraPlanoCartesiano(10);

    imgponteiro = AbreImagem("batalha/selecao.png");
    imgtransparente = AbreImagem("batalha/areanada.png");
    imgagua = AbreImagem("batalha/agua.png");
    imgfogo = AbreImagem("batalha/Fogo.png");
    imgdestrocos = AbreImagem("batalha/destrocos.png");

    //cria fundo
    gfundo = CriaGrupo();

    imgmar = AbreImagem("batalha/mar12x12.png");
    imgtelabatalha = AbreImagem("batalha/TelaBatalha.png");

    p.x = -120;
    p.y = -80;
    CriaRetangulo(230, 170, p);
    Pintar(255, 255, 255);
    AssociaImagem(imgmar);

    p.y = 80;
    p2.y = -80;
    p.x = -120;
    p2.x = -120;
    for(int i = 0; i < 10; i++){
        CriaReta(p, p2);
        Pintar(255, 255, 255);
        Grafite(5);

        p.x += 25.1;
        p2.x += 25.1;
    }

    p.y = -80;
    p2.y = -80;
    p.x = 107;
    p2.x = -120;
    for(int i = 0; i < 10; i++){
        CriaReta(p, p2);
        Pintar(255, 255, 255);
        Grafite(5);

        p.y += 17.8;
        p2.y += 17.8;
    }

    p.x = -127.62;
    p.y = -100;
    CriaRetangulo(255, 200, p);
    Pintar(255, 255, 255);
    AssociaImagem(imgtelabatalha);
    //fim de criafundo

    //cria tabuleiro
    gclicavel = CriaGrupo();
    p.y = 63.5;
    for(int i = 0; i < 9; i++){
        p.x = -119.5;
        for(int j = 0; j < 9; j++){

            mLog[i][j] = 0;
            mVisu[i][j].index = CriaRetangulo(24, 17, p);
            mVisu[i][j].esq = p;
            Pintar(255, 255, 255);
            AssociaImagem(imgtransparente);

            p.x += 25;

        }
        p.y -= 18;
    }

    //comeco de sorteiaBarcos
     for(tam = 3; tam > 0; tam--){

        qtd = (tam == 1 ? 4 : 3); //se barco for de tamanho 1, então há 4 barcos. Se não, há 3 barcos

        for(int q = 0; q < qtd; q++){
            do{
                x = rand()%9;
                y = rand()%9;
                sentido = rand()%2;

                switch(sentido){
                    case 0: //horizontal
                        if(x > 9 - tam)
                            x = 9 - tam;
                    break;
                    case 1: //vertical
                        if(y > 9 - tam)
                            y = 9 - tam;
                    break;
                }
                valido = 1;
                //inicio de posição válida
                switch(sentido){
                    case 0: //horizontal
                        for(int i = 0; i < tam; i++){
                             //verifica os vizinhos
                            for(int j = -1; j <= 1; j++){ //x
                                for(int k = -1; k <= 1; k++){ //y
                                    if(((x + i + j < 9)  && (x + i + j >= 0))&& ( ((y + k) < 9) && ((y + k) >= 0))){ //se posicao existe
                                        if(mLog[y + k][x + i + j] == 1) //se tiver um barco
                                            valido = 0; //nao é posição válida
                                    }
                                }
                            }

                        }
                    break;
                    case 1: //vertical
                        for(int i = 0; i < tam; i++){
                             //verifica os vizinhos
                            for(int j = -1; j <= 1; j++){ //x
                                for(int k = -1; k <= 1; k++){ //y
                                    if(((x + j < 9)  && (x + j >= 0))&& ( ((y + i + k) < 9) && ((y + i + k) >= 0))){ //se posicao existe
                                        if(mLog[y + i + k][x + j] == 1) //se tiver um barco
                                            valido = 0; //nao é posição válida
                                    }
                                }
                            }
                        }
                    break;
                }
                //fim de posição válida
            }while(!valido);

            switch(sentido){
                case 0: //horizontal
                    for(int i = 0; i < tam; i++){
                        mLog[y][x + i] = 1; //barco

                        for(int j = -1; j <= 1; j++){ //x
                            for(int k = -1; k <= 1; k++){ //y
                                if(((x + i + j < 9) && (x + i + j >= 0)) && ((y + k) < 9) && (y + k >= 0)){
                                    if(mLog[y + k][x + i + j] == 0)
                                        mLog[y + k][x + i + j] = 3; //agua espaçada
                                }
                            }
                        }
                    }
                break;

                case 1: //vertical
                    for(int i = 0; i < tam; i++){
                        mLog[y + i][x] = 1; //barco

                        for(int j = -1; j <= 1; j++){ //x
                            for(int k = -1; k <= 1; k++){ //y
                                if(((x + j < 9) && (x + j >= 0)) && ((y + i + k) < 9) && (y + i + k >= 0)){
                                    if(mLog[y + i + k][x + j] == 0)
                                        mLog[y + i + k][x + j] = 3; //agua espaçada
                                }
                            }
                        }
                    }
                break;
            }

        }
    }
    //fim de sorteia barcos
    //inicio de limpa água Aux
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(mLog[i][j] == 3)
                mLog[i][j] = 0;
        }
    }
    //fim de limpa água Aux

    //início de imprimeMatriz da resposta
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            switch(mLog[i][j]){
                case 0:
                    printf("%c ", 176);
                break;

                case 1:
                    printf(". ");
                break;
            }
        }
        printf("\n");
    }
    //fim de imprimeMatriz da resposta
    //fim de cria tabuleiro

    gbalao = CriaGrupo();
    imgaviso = AbreImagem("batalha/playapc.png");
    p.x = -105;
    p.y = -20;
    CriaRetangulo(200, 77, p);
    Pintar(255, 255, 255);
    AssociaImagem(imgaviso);

    while(!ApertouBotaoMouse(GLFW_MOUSE_BUTTON_LEFT))
        Desenha1Frame();

    ApagaGrupo(gbalao);

    while(aberta && contnavio != 19){
        //pega posição do tabuleiro
       PosicaoMouse(&xpos, &ypos);

        //descobrindo posição ytab
        for(int i = 0; i < 9; i++){

            if(mVisu[i][0].esq.y <= ypos && mVisu[i][0].esq.y + 18 >= ypos){
                ytab = i;
                break;
            }
        }

        //descobrindo posição xtab
        for(int j = 0; j < 9; j++){

            if(mVisu[0][j].esq.x <= xpos && mVisu[0][j].esq.x + 25 >= xpos){
                xtab = j;
                break;
            }
        }
        //fim de pega posição do tabuleiro

        //inicio de muda cursor
        pedaco = 0;

        if(mLog[ytab][xtab] == 0 || mLog[ytab][xtab] == 1) //Se não tiver preenchido
            AssociaImagem(imgponteiro, RETANGULO, mVisu[ytab][xtab].index);

        if(ApertouBotaoMouse(GLFW_MOUSE_BUTTON_LEFT)){
            if(mLog[ytab][xtab] == 0){
                mLog[ytab][xtab] = -2;
                AssociaImagem(imgagua, RETANGULO, mVisu[ytab][xtab].index);
            }
            else if(mLog[ytab][xtab] == 1){

                int vizinho = ytab - 1;

                //esquerda
                while(vizinho >= 0 && mLog[vizinho][xtab] > 0){
                    if(mLog[vizinho][xtab] == 1)
                        pedaco++;
                    vizinho--;
                }

                vizinho = ytab + 1;
                //direita
                while(vizinho < 10 && mLog[vizinho][xtab] > 0){
                    if(mLog[vizinho][xtab] == 1)
                        pedaco++;
                    vizinho++;
                }

                vizinho = xtab - 1;
                //cima
                while(vizinho >= 0 && mLog[ytab][vizinho] > 0){
                    if(mLog[ytab][vizinho] == 1)
                        pedaco++;
                    vizinho--;
                }

                vizinho = xtab + 1;
                //baixo
                while(vizinho < 10 && mLog[ytab][vizinho] > 0){
                    if(mLog[ytab][vizinho] == 1)
                        pedaco++;
                    vizinho++;
                }

                if(pedaco > 0){
                    AssociaImagem(imgfogo, RETANGULO, mVisu[ytab][xtab].index);
                    mLog[ytab][xtab] = 2;
                }
                else{
                    AssociaImagem(imgdestrocos, RETANGULO, mVisu[ytab][xtab].index);
                    mLog[ytab][xtab] = -1;

                    //esquerda
                    vizinho = ytab - 1;
                    while(vizinho >= 0 && mLog[vizinho][xtab] == 2){
                        AssociaImagem(imgdestrocos, RETANGULO, mVisu[vizinho][xtab].index);
                        mLog[vizinho][xtab] = -1;

                        vizinho--;
                    }

                    vizinho = ytab + 1;
                    //direita
                    while(vizinho < 10 && mLog[vizinho][xtab] == 2){
                        AssociaImagem(imgdestrocos, RETANGULO, mVisu[vizinho][xtab].index);
                        mLog[vizinho][xtab] = -1;

                        vizinho++;
                    }

                    vizinho = xtab - 1;
                    //cima
                    while(vizinho >= 0 && mLog[ytab][vizinho] == 2){
                        AssociaImagem(imgdestrocos, RETANGULO, mVisu[ytab][vizinho].index);
                        mLog[ytab][vizinho] = -1;

                        vizinho--;
                    }

                    vizinho = xtab + 1;
                    //baixo
                    while(vizinho < 10 && mLog[ytab][vizinho] == 2){
                        AssociaImagem(imgdestrocos, RETANGULO, mVisu[ytab][vizinho].index);
                        mLog[ytab][vizinho] = -1;

                        vizinho++;
                    }

                }
            }
        }
        //fim de muda cursor

        contnavio = 0;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(mLog[i][j] == -1)
                    contnavio++;
            }
        }
        aberta = Desenha1Frame();

        //inicio de muda cursor
        pedaco = 0;

        if(mLog[ytab][xtab] == 0 || mLog[ytab][xtab] == 1) //Se não tiver preenchido
            AssociaImagem(imgtransparente, RETANGULO, mVisu[ytab][xtab].index);

        //fim de muda cursor
    }

    gbalao = CriaGrupo();
    imgaviso = AbreImagem("batalha/playapc_youwin.png");
    p.x = -105;
    p.y = -20;
    CriaRetangulo(200, 77, p);
    Pintar(255, 255, 255);
    AssociaImagem(imgaviso);

    Desenha();

    return 0;
}
