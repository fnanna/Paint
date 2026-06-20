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
extern float corAtual[3];
extern float mouse_x;
extern  float mouse_y;
extern Ponto inicioLinha;
extern int totalPontosPoligono;
extern Ponto pontosPoligono[50];

extern No* lista;

extern EstadoCachorro estadoCachorro;
extern float cachorroX, cachorroY;

extern Objeto* objetoSelecionado;

//------ funcoes de desenhar
void desenhaObjeto(Objeto* objeto){
    if (objetoSelecionado!=NULL && estadoAtual == SELECAO && objetoSelecionado == objeto ){
            glColor3f(1,0,0);
    }else{glColor3f(objeto->cor[0],objeto->cor[1],objeto->cor[2]);}

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

void desenhaPreview(){
    if (estadoAtual == CRIAR_LINHA_P2) {
        glColor3f(0.5,0.5,0.5);
        glLineWidth(1);
        glBegin(GL_LINES);
            glVertex2f(inicioLinha.x, inicioLinha.y);
            glVertex2f(mouse_x, mouse_y);
        glEnd();
    }

    if (estadoAtual == CRIAR_POLIGONO && totalPontosPoligono > 0) {
        glLineWidth(1);
        glColor3f(0.5,0.5,0.5);
        glBegin(GL_LINE_STRIP);
            for (int i = 0; i < totalPontosPoligono; i++) {
                glVertex2f(pontosPoligono[i].x, pontosPoligono[i].y);
            }
            glVertex2f(mouse_x, mouse_y);
        glEnd();
    }
}

//------ main do opengl
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaLista();
    desenhaPreview();
    if (estadoCachorro != CACHORRO_INATIVO) {
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

void reshape(int w, int h) {
    if (w != 1000 || h != 600) {
        glutReshapeWindow(1000, 600); // forca de volta ao tamanho original
        return;
    }
    glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("paint");

    // PROIBIR DE MINIMIZAR JANELA
    HWND hwnd = FindWindow(NULL, "Paint");
    LONG estilo = GetWindowLong(hwnd, GWL_STYLE);
    estilo &= ~WS_MAXIMIZEBOX; // remove o botao de maximizar
    SetWindowLong(hwnd, GWL_STYLE, estilo);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(mouseMove);
    glutReshapeFunc(reshape);

    init();
    glutMainLoop();
    return 0;
}
