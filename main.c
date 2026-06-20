#include <windows.h>
#include <GL/glut.h>

#include "objetos.h"
#include "listaEncadeada.h"
#include "selecao.h"
#include "transformacoes.h"
#include "animacao.h"

//------ variaveis globais e estados
int larguraTela;
int alturaTela;
Ponto pontosPoligono[100]; // vetor de pontos que foram clicados
int totalPontosPoligono = 0;

typedef enum{
    CRIAR_PONTO,
    CRIAR_LINHA_P1,
    CRIAR_LINHA_P2,
    CRIAR_POLIGONO,
    SELECAO,
}Estado;
Estado estadoAtual;
Ponto inicioLinha;
Objeto* objetoSelecionado;

extern No* lista;
extern EstadoCachorro estadoCachorro;
extern float cachorroX, cachorroY;

float mouse_x;
float mouse_y;

// ------ funcoes do mouse e teclado (posteriormente podem ser outro arquivo)
void mouseClick(int botao, int state, int x, int y) {
    if (botao == GLUT_RIGHT_BUTTON) return; // ignora clique direito
    if (botao == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       mouse_x = (float)x;
       mouse_y = (float)alturaTela - y;

       switch(estadoAtual){
           case CRIAR_PONTO:{
               Objeto ponto = criaPonto(mouse_x,mouse_y);
               inserirLista(ponto);
               glutPostRedisplay();
               break;
           }
           case CRIAR_LINHA_P1:{ //aguardando segundo pontp
               inicioLinha.x = mouse_x;
               inicioLinha.y = mouse_y;
               estadoAtual= CRIAR_LINHA_P2;
               break;
           }
           case CRIAR_LINHA_P2:{
               Objeto linha = criaLinha(inicioLinha.x,inicioLinha.y,mouse_x,mouse_y);
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
       }
    }
}


void teclado(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }else if (key == 'p'){
        estadoAtual=CRIAR_PONTO;
    }else if (key == 'l'){
        estadoAtual=CRIAR_LINHA_P1;
    }else if (key == 'f'){
        estadoAtual=CRIAR_POLIGONO;
    }else if (key == 's'){
        estadoAtual=SELECAO;
    }else if (key == 13 && estadoAtual == CRIAR_POLIGONO && totalPontosPoligono >= 3) {
        Objeto poligono = criaPoligono(pontosPoligono, totalPontosPoligono);
        inserirLista(poligono);
        totalPontosPoligono = 0;
        glutPostRedisplay();
    } else if (key == 127 && objetoSelecionado != NULL && estadoAtual == SELECAO) {
        removerPorPonteiro(objetoSelecionado);
        objetoSelecionado = NULL;
        glutPostRedisplay();
    } else if (key == 'j' && objetoSelecionado != NULL && estadoAtual == SELECAO) {
        iniciarAnimacaoCachorro(objetoSelecionado);
        objetoSelecionado = NULL;
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

//------ funcoes de desenhar chamadas pelo display (posteriormente podem ser outro arquivo)
void desenhaObjeto(Objeto* objeto){
    if (objetoSelecionado!=NULL && estadoAtual == SELECAO && objetoSelecionado == objeto){
            glColor3f(1,0,0);
    }else{glColor3f(0,0,0);}

    switch (objeto->tipo){
        case PONTO:
            glPointSize(3);
            glBegin(GL_POINTS);
                glVertex2f(objeto->ponto.x, objeto->ponto.y);
            glEnd();
        break;
        case LINHA:
            glLineWidth(2);
            glBegin(GL_LINES);
                glVertex2f(objeto->linha.ponto_a.x, objeto->linha.ponto_a.y);
                glVertex2f(objeto->linha.ponto_b.x, objeto->linha.ponto_b.y);
            glEnd();
        break;
        case POLIGONO:
            glLineWidth(2);
            glBegin(GL_POLYGON);
            for (int i = 0; i < objeto->poligono.total; i++) {
            glVertex2f(objeto->poligono.pontos[i].x, objeto->poligono.pontos[i].y);
        }
            glEnd();
        break;
    }
}

void desenhaLista(){ //percorre a lista desenhando todos os objetos
    No* atual = lista;
    while (atual != NULL){
        desenhaObjeto(&atual->objeto);
        atual = atual->proximo;
    }
}

//------ main do opengl
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaLista();
    if (estadoCachorro == CACHORRO_ANDANDO) {
        desenhaCachorro(cachorroX, cachorroY);
    }

    glutSwapBuffers();
}

void init(void) {
    larguraTela = glutGet(GLUT_SCREEN_WIDTH);
    alturaTela = glutGet(GLUT_SCREEN_HEIGHT);

    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(0, larguraTela, 0, alturaTela);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    carregarFramesCachorro();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("paint");
    glutFullScreen();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseClick);

    init();
    glutMainLoop();
    return 0;
}
