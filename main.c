#include <windows.h>
#include <GL/glut.h>

void teclado(unsigned char key, int x, int y){
    if (key==27){
        exit(0);
    }
}

int init(void){
    glClearColor(1,1,1,0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,1366,0,768);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

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

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

