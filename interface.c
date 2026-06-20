#include <GL/glut.h>
#include "texturas.h"
#include "interface.h"
#include "entrada.h"

#define NUM_BOTOES 5
#define NUM_CORES 11

GLuint texturaGui;
int guiW, guiH;

extern Estado estadoAtual;
extern int totalPontosPoligono;
extern float corAtual[3];

BotaoGui botoes[] = {
    {18, 541, 47, 570,CRIAR_PONTO},
    {18, 512, 47, 541,CRIAR_LINHA_P1},
    {18, 483, 47, 512,CRIAR_POLIGONO},
    {18, 454, 47, 483,SELECAO},
    {18, 425, 47, 454,DELETAR},
};

BotaoCor botoesCor[] = {
    {18, 600-218, 47, 600-189, 42/255.0f, 42/255.0f, 42/255.0f}, // preto
    {18, 600-253, 47, 600-224, 195/255.0f, 186/255.0f, 188/255.0f}, // cinza claro
    {18, 600-288, 47, 600-259, 253/255.0f, 249/255.0f, 0/255.0f}, // amarelo
    {18, 600-323, 47, 600-294, 60/255.0f, 235/255.0f, 60/255.0f}, // verde
    {18, 600-358, 47, 600-329, 35/255.0f, 33/255.0f, 232/255.0f}, // azul
    {18, 600-393, 47, 600-364, 227/255.0f, 45/255.0f, 218/255.0f}, // magenta
    {18, 600-428, 47, 600-399, 240/255.0f, 203/255.0f, 124/255.0f}, // bege
    {18, 600-463, 47, 600-434, 0/255.0f, 243/255.0f, 253/255.0f}, // ciano
    {18, 600-498, 47, 600-469, 112/255.0f, 145/255.0f, 212/255.0f}, // azul claro
    {18, 600-533, 47, 600-504, 245/255.0f, 121/255.0f, 157/255.0f}, // rosa
    {18, 600-568, 47, 600-539, 254/255.0f, 123/255.0f, 53/255.0f}, // laranja
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
     // destaque da cor ativa
    for (int i = 0; i < NUM_CORES; i++) {
        if (botoesCor[i].r == corAtual[0] &&
            botoesCor[i].g == corAtual[1] &&
            botoesCor[i].b == corAtual[2]) {
            glColor3f(1, 1, 1);
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
                glVertex2f(botoesCor[i].x1, botoesCor[i].y1);
                glVertex2f(botoesCor[i].x2, botoesCor[i].y1);
                glVertex2f(botoesCor[i].x2, botoesCor[i].y2);
                glVertex2f(botoesCor[i].x1, botoesCor[i].y2);
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
    for (int i = 0; i < NUM_CORES; i++) {
        if (mx >= botoesCor[i].x1 && mx <= botoesCor[i].x2 &&
            my >= botoesCor[i].y1 && my <= botoesCor[i].y2) {
            corAtual[0] = botoesCor[i].r;
            corAtual[1] = botoesCor[i].g;
            corAtual[2] = botoesCor[i].b;
            return 1;
        }
    }
    return 0;
}
