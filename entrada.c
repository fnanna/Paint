#include "entrada.h"
#include "objetos.h"
#include "listaEncadeada.h"
#include "selecao.h"
#include "transformacoes.h"
#include "salvar.h"
#include "animacao.h"
#include "entrada.h"
#include "interface.h"
#include "carregar.h"

Estado estadoAtual;
Objeto* objetoSelecionado;
float corAtual[3]={0.16, 0.16, 0.16};

Ponto inicioLinha;
Ponto pontosPoligono[50]; // vetor de pontos que foram clicados
int totalPontosPoligono = 0;

int larguraTela;
int alturaTela;
float mouse_x;
float mouse_y;

void mouseClick(int botao, int state, int x, int y) {
    if (botao == GLUT_RIGHT_BUTTON) return; // ignora clique direito
    if (botao == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       mouse_x = (float)x;
       mouse_y = (float)alturaTela - y;

       if (verificarCliqueGui(mouse_x, mouse_y)) {
            glutPostRedisplay();
            return;
        }

       switch(estadoAtual){
           case CRIAR_PONTO:{
               Objeto ponto = criaPonto(mouse_x,mouse_y);
               adicionarCor(&ponto,corAtual[0],corAtual[1],corAtual[2]);
               inserirLista(ponto);
               glutPostRedisplay();
               break;
           }
           case CRIAR_LINHA_P1:{ //aguardando segundo ponto
               inicioLinha.x = mouse_x;
               inicioLinha.y = mouse_y;
               estadoAtual= CRIAR_LINHA_P2;
               break;
           }
           case CRIAR_LINHA_P2:{
               Objeto linha = criaLinha(inicioLinha.x,inicioLinha.y,mouse_x,mouse_y);
               adicionarCor(&linha,corAtual[0],corAtual[1],corAtual[2]);
               inserirLista(linha);
               glutPostRedisplay();
               estadoAtual= CRIAR_LINHA_P1;
               break;
           }
           case CRIAR_POLIGONO: {
               pontosPoligono[totalPontosPoligono].x = mouse_x;
               pontosPoligono[totalPontosPoligono].y = mouse_y;
               totalPontosPoligono++;
               glutPostRedisplay();
               break;
            }
            case SELECAO:{
                objetoSelecionado = selecionaObjetos(mouse_x,mouse_y);
                glutPostRedisplay();
                break;
            }
            case DELETAR:{
                objetoSelecionado = selecionaObjetos(mouse_x,mouse_y);
                removerPorPonteiro(objetoSelecionado);
                objetoSelecionado = NULL;
                glutPostRedisplay();
                break;
            }
       }
    }
}

void teclado(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
    // ---- atalhos para trocar de modo ----
    else if (key == '1') { estadoAtual = CRIAR_PONTO; }
    else if (key == '2') { estadoAtual = CRIAR_LINHA_P1; }
    else if (key == '3') { estadoAtual = CRIAR_POLIGONO; totalPontosPoligono = 0; }
    else if (key == '4') { estadoAtual = SELECAO; }
    // ---- fechar poligono ----
    else if ((key == 'p' || key == 16 || key == 13) && estadoAtual == CRIAR_POLIGONO && totalPontosPoligono >= 3) {
        Objeto poligono = criaPoligono(pontosPoligono, totalPontosPoligono);
        adicionarCor(&poligono,corAtual[0],corAtual[1],corAtual[2]);
        inserirLista(poligono);
        totalPontosPoligono = 0;
        glutPostRedisplay();
    }
    // ---- remover objeto selecionado ----
    else if (key == 127 && objetoSelecionado != NULL && estadoAtual == SELECAO) {
        removerPorPonteiro(objetoSelecionado);
        objetoSelecionado = NULL;
        glutPostRedisplay();
    }
    // ---- salvar ----
    else if (key == 19) { // ctrl+s
        salvarArquivo("desenho.bin");
    }else if(key==15){ // ctrl+o
        carregarArquivo("desenho.bin");
    }
    // ---- animacao cachorro ----
    else if (key == 'j' && objetoSelecionado != NULL && estadoAtual == SELECAO) {
        iniciarAnimacaoCachorro();
    }
    // ----chama fecho convexo ----
    else if (key == 'k' && estadoAtual == SELECAO) {
        converterParaConvexo(objetoSelecionado);
    }

    if (estadoAtual != SELECAO || !objetoSelecionado) return;
    switch (key) {
        case 'w': case 'W': transladar(objetoSelecionado,   0,  10); break;
        case 's': case 'S': transladar(objetoSelecionado,   0, -10); break;
        case 'a': case 'A': transladar(objetoSelecionado, -10,   0); break;
        case 'd': case 'D': transladar(objetoSelecionado,  10,   0); break;
        case 'q': case 'Q': rotacionar(objetoSelecionado,  15); break;
        case 'e': case 'E': rotacionar(objetoSelecionado, -15); break;
        case '+': case '=': escalar(objetoSelecionado, 1.1, 1.1); break;
        case '-': case '_': escalar(objetoSelecionado, 0.9, 0.9); break;
        case 'z': case 'Z': escalar(objetoSelecionado, 1.1, 1); break;
        case 'x': case 'X': escalar(objetoSelecionado, 1, 1.1); break;
        case 'h': case 'H': refletirX(objetoSelecionado); break;
        case 'v': case 'V': refletirY(objetoSelecionado); break;
        case 'c': case 'C': cisalharH(objetoSelecionado,  0.1); break;
        case 'b': case 'B': cisalharH(objetoSelecionado, -0.1); break;
        case 'n': case 'N': cisalharV(objetoSelecionado,  0.1); break;
        case 'm': case 'M': cisalharV(objetoSelecionado, -0.1); break;
    }
    glutPostRedisplay();
}

void mouseMove(int x, int y) {
    mouse_x = (float)x;
    mouse_y = (float)alturaTela - y;

    if (estadoAtual == CRIAR_LINHA_P2 ||
        (estadoAtual == CRIAR_POLIGONO && totalPontosPoligono > 0)) {
        glutPostRedisplay();
    }
}
