#include "texturas.h"
#include <stdio.h>
#include "listaEncadeada.h"
#include "animacao.h"
#include "transformacoes.h"
#include "objetos.h"
#include "entrada.h"

#define SPRITE_W 48*3
#define SPRITE_H 36*3

EstadoCachorro estadoCachorro = CACHORRO_INATIVO;
float cachorroX, cachorroY;
extern Objeto* objetoSelecionado;

GLuint frames[8];
GLuint frameBocaAberta;
GLuint frameGordo;

int frameAtual = 0;

void carregarFramesCachorro() {
    int w, h;
    char nome[32];
    for (int i = 0; i < 8; i++) {
        sprintf(nome, "assets/frame%d.png", i);
        frames[i] = carregarTextura(nome, &w, &h);
    }
    frameBocaAberta = carregarTextura("assets/boca_aberta.png", &w, &h);
    frameGordo = carregarTextura("assets/gordo.png", &w, &h);
}

void desenhaCachorro(float x, float y) {
    GLuint texturaAtual;

    if (estadoCachorro == CACHORRO_COMENDO) {
        texturaAtual = frameBocaAberta;
    } else if (estadoCachorro == CACHORRO_GORDO) {
        texturaAtual = frameGordo;
    } else {
        texturaAtual = frames[frameAtual];
    }

    float w = SPRITE_W;
    float h = SPRITE_H;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaAtual);
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

        if (objetoSelecionado != NULL && cachorroX + larguraSprite >= calcularCentro(objetoSelecionado).x) {
            estadoCachorro = CACHORRO_COMENDO;
            glutTimerFunc(250, timerCachorro, 0); // boca aberta visivel por 250ms
        } else {
            glutTimerFunc(60, timerCachorro, 0);
        }

        glutPostRedisplay();
    }
    else if (estadoCachorro == CACHORRO_COMENDO) {
        removerPorPonteiro(objetoSelecionado);
        objetoSelecionado = NULL;
        estadoCachorro = CACHORRO_GORDO;
        glutPostRedisplay();
        glutTimerFunc(800, timerCachorro, 0); // fica gordo
    }
    else if (estadoCachorro == CACHORRO_GORDO) {
        estadoCachorro = CACHORRO_INATIVO; //cachorro some
        glutPostRedisplay();
    }
}

void iniciarAnimacaoCachorro() {

    cachorroX = 0;
    cachorroY = calcularCentro(objetoSelecionado).y - 18;       // centraliza verticalmente (sprite de 36px)
    frameAtual = 0;
    estadoCachorro = CACHORRO_ANDANDO;
    glutTimerFunc(60, timerCachorro, 0);
}
