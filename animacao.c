#include "texturas.h"

#include "animacao.h"
#include "transformacoes.h"
#include "objetos.h"

#define SPRITE_W 48*3
#define SPRITE_H 36*3

EstadoCachorro estadoCachorro = CACHORRO_INATIVO;
float cachorroX, cachorroY;
Objeto* objetoAlvo = NULL;

GLuint frames[8];
int frameAtual = 0;

void carregarFramesCachorro() {
    int w, h;
    char nome[32];
    for (int i = 0; i < 8; i++) {
        sprintf(nome, "assets/frame%d.png", i);
        frames[i] = carregarTextura(nome, &w, &h);
    }
}

void desenhaCachorro(float x, float y) {
    float w = SPRITE_W;
    float h = SPRITE_H;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, frames[frameAtual]);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(x,y);
        glTexCoord2f(1, 1); glVertex2f(x + w, y);
        glTexCoord2f(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2f(0, 0); glVertex2f(x,y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void timerCachorro(int valor) {
    if (estadoCachorro == CACHORRO_ANDANDO) {

        cachorroX += 15;
        frameAtual = (frameAtual + 1) % 8;  //loop automatico
        float larguraSprite = SPRITE_W;

        if (objetoAlvo != NULL && cachorroX + larguraSprite >= calcularCentro(objetoAlvo).x) {
            printf("Cachorro alcançou o alvo, removendo %p\n", (void*)objetoAlvo);
            removerPorPonteiro(objetoAlvo);
            objetoAlvo = NULL;
            estadoCachorro = CACHORRO_INATIVO;
        } else {
            glutTimerFunc(50, timerCachorro, 0);
        }

        glutPostRedisplay();
    }
}

void iniciarAnimacaoCachorro(Objeto* alvo) {

    objetoAlvo= alvo;
    cachorroX = 0;
    cachorroY = calcularCentro(alvo).y - 18;       // centraliza verticalmente (sprite de 36px)
    frameAtual = 0;
    estadoCachorro = CACHORRO_ANDANDO;
    glutTimerFunc(50, timerCachorro, 0);
}
