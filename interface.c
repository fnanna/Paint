#include <GL/glut.h>
#include "texturas.h"
#include "interface.h"
#include "entrada.h"

#define NUM_BOTOES 5

GLuint texturaGui;
int guiW, guiH;

extern Estado estadoAtual;
extern int totalPontosPoligono;

BotaoGui botoes[] = {
    {18, 541, 47, 570,CRIAR_PONTO},
    {18, 512, 47, 541,CRIAR_LINHA_P1},
    {18, 483, 47, 512,CRIAR_POLIGONO},
    {18, 454, 47, 483,SELECAO},
    {18, 425, 47, 454,DELETAR},
};

void carregarGui(void) {
    texturaGui = carregarTextura("assets/gui.png", &guiW, &guiH);
}

void desenhaGui(void) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaGui);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(0,      0);
        glTexCoord2f(1, 1); glVertex2f(guiW,   0);
        glTexCoord2f(1, 0); glVertex2f(guiW,   guiH);
        glTexCoord2f(0, 0); glVertex2f(0,      guiH);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // destaque do botao ativo
    for (int i = 0; i < NUM_BOTOES; i++) {
        if (botoes[i].estado == estadoAtual || botoes[i].estado == CRIAR_LINHA_P1 && estadoAtual == CRIAR_LINHA_P2) {
            glColor3f(1, 1, 1);
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
                glVertex2f(botoes[i].x1, botoes[i].y1);
                glVertex2f(botoes[i].x2, botoes[i].y1);
                glVertex2f(botoes[i].x2, botoes[i].y2);
                glVertex2f(botoes[i].x1, botoes[i].y2);
            glEnd();
        }
    }
}

int verificarCliqueGui(float mx, float my){
    for (int i = 0; i < NUM_BOTOES; i++) {
        if (mx >= botoes[i].x1 && mx <= botoes[i].x2 &&
            my >= botoes[i].y1 && my <= botoes[i].y2) {
            estadoAtual = botoes[i].estado;
            if (botoes[i].estado == CRIAR_POLIGONO) totalPontosPoligono = 0;
            return 1;
        }
    }
    return 0;
}
