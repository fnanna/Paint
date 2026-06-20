#include <windows.h>
#include <GL/glut.h>

#include "objetos.h"
#include "listaEncadeada.h"
#include "selecao.h"
#include "transformacoes.h"
#include "salvar.h"
#include "animacao.h"
#include "entrada.h"
#include "interface.h"

extern int larguraTela;
extern int alturaTela;
extern Estado estadoAtual;

extern No* lista;

extern EstadoCachorro estadoCachorro;
extern float cachorroX, cachorroY;

extern Objeto* objetoSelecionado;

//------ funcoes de desenhar
void desenhaObjeto(Objeto* objeto){
    if (objetoSelecionado!=NULL && estadoAtual == SELECAO && objetoSelecionado == objeto ){
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
    desenhaGui();

    glutSwapBuffers();
}

void init(void) {
    larguraTela = 1000;
    alturaTela = 600;

    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(0, larguraTela, 0, alturaTela);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    carregarFramesCachorro();
    carregarGui();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("paint");

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseClick);

    init();
    glutMainLoop();
    return 0;
}
