#include <windows.h>
#include <GL/glut.h>

#include "objetos.h"
#include "listaEncadeada.h"

//------ variaveis globais e estados
int larguraTela;
int alturaTela;

typedef enum{
    CRIAR_PONTO,
    CRIAR_LINHA_P1,
    CRIAR_LINHA_P2,
    CRIAR_POLIGONO,
}Estado;
Estado estadoAtual;
Ponto inicioLinha;

extern No* lista;
float mouse_x;
float mouse_y;

// ------ funcoes do mouse e teclado (posteriormente podem ser outro arquivo)
void mouseClick(int botao, int state, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       mouse_x = (float)x;
       mouse_y = (float)alturaTela - y;

       switch(estadoAtual){
           case CRIAR_PONTO:{
               Objeto ponto = criaPonto(mouse_x,mouse_y);
               inserir(ponto); //insere na lista
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
               inserir(linha);
               glutPostRedisplay();
               estadoAtual= CRIAR_LINHA_P1;
               break;
           }

       }
    }
}


void teclado(unsigned char key, int x, int y) {
    if (key == 27) { //aperta esc pra sair
        exit(0);
    }
}

//------ funcoes de desenhar chamadas pelo display (posteriormente podem ser outro arquivo)
void desenhaObjeto(Objeto* objeto){
    switch (objeto->tipo){
        case PONTO:
            glColor3f(0,0,0); //isso aqui pode virar um campo da struct Objeto dps
            glPointSize(3);
            glBegin(GL_POINTS);
                glVertex2f(objeto->ponto.x, objeto->ponto.y);
            glEnd();
        break;
        case LINHA:
            glColor3f(0,0,0);
            glLineWidth(2);
            glBegin(GL_LINES);
                glVertex2f(objeto->linha.ponto_a.x, objeto->linha.ponto_a.y);
                glVertex2f(objeto->linha.ponto_b.x, objeto->linha.ponto_b.y);
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

    glFlush();
}

void menuPaint(int opcao) {
    estadoAtual = (Estado) opcao; // muda o estado de acordo com a entry do menu
    glutPostRedisplay();
}

void criaMenu(void) {
    int menu = glutCreateMenu(menuPaint);
    glutAddMenuEntry("Desenhar Ponto",CRIAR_PONTO);
    glutAddMenuEntry("Desenhar Linha",CRIAR_LINHA_P1);
    glutAddMenuEntry("Desenhar Poligono",CRIAR_POLIGONO);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(void) {
    larguraTela = glutGet(GLUT_SCREEN_WIDTH);
    alturaTela = glutGet(GLUT_SCREEN_HEIGHT);

    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(0, larguraTela, 0, alturaTela);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("paint");
    glutFullScreen();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseClick);

    init();
    criaMenu();
    glutMainLoop();
    return 0;
}
