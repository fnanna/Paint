#include <GL/glut.h>
#include "texturas.h"
#include "interface.h"
#include "entrada.h"

GLuint texturaGui;
int guiW=1000, guiH=600;

extern Estado estadoAtual;
extern int totalPontosPoligono;

BotaoGui botoes[] = {
    { 0, 0, 0, 0, CRIAR_PONTO    },
    { 0, 0, 0, 0, CRIAR_LINHA_P1 },
    { 0, 0, 0, 0, CRIAR_POLIGONO },
    { 0, 0, 0, 0, SELECAO        },
};
#define NUM_BOTOES (sizeof(botoes) / sizeof(BotaoGui))

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

    // destaque do botao ativo (placeholder, ajustar depois)
    /*for (int i = 0; i < NUM_BOTOES; i++) {
        if (botoes[i].estado == estadoAtual) {
            glColor3f(1, 1, 0);
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
                glVertex2f(botoes[i].x1, botoes[i].y1);
                glVertex2f(botoes[i].x2, botoes[i].y1);
                glVertex2f(botoes[i].x2, botoes[i].y2);
                glVertex2f(botoes[i].x1, botoes[i].y2);
            glEnd();
        }
    }*/
}

int verificarCliqueGui(float mx, float my) {
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
