#include <windows.h>
#include <GL/glut.h>

int larguraTela;
int alturaTela;
int mouse_x;
int mouse_y;
int mouse_click=0;

//teste desenhat ponto (nao esta usando as bibliotecas)
void mouseClick(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
       mouse_x = x;
       mouse_y = alturaTela-y;
       mouse_click = 1;

       glutPostRedisplay();
    }
}

void desenhaPonto(int x, int y){
    glColor3f(0,0,0);
    glPointSize(4);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void teclado(unsigned char key, int x, int y){
    if (key==27){
        exit(0);
    }
}

int init(void){
    larguraTela= glutGet(GLUT_SCREEN_WIDTH);
    alturaTela= glutGet(GLUT_SCREEN_HEIGHT);
    glClearColor(1,1,1,0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,larguraTela,0,alturaTela);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    if(mouse_click){
        desenhaPonto(mouse_x,mouse_y);
    }

    glFlush();
}

int main (int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("paint");


    glutFullScreen();
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseClick);

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

