#ifndef ANIMACAO_H
#define ANIMACAO_H

#include "texturas.h"
#include "animacao.h"
#include "transformacoes.h"
#include "objetos.h"

typedef enum {
    CACHORRO_INATIVO,
    CACHORRO_ANDANDO,
    CACHORRO_COMEU
} EstadoCachorro;


void carregarFramesCachorro();
void desenhaCachorro(float x, float y); //desenha com a textura
void timerCachorro(int valor); //funcao callback
void iniciarAnimacaoCachorro(); //chamada pelo menu

#endif
