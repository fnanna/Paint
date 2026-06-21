#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "salvar.h"
#include "objetos.h"
#include "listaEncadeada.h"

extern No* lista;

void salvarArquivo(const char* caminho) {
    char path[500];
    GetModuleFileNameA(NULL, path, 500); // pega caminho do executável


    char* ultima_barra = strrchr(path, '\\'); // remove o nome do executável para ficar só a pasta
    if (ultima_barra) *(ultima_barra + 1) = '\0';
    strcat(path, caminho); // adiciona o nome do arquivo
    FILE* f = fopen(path, "wb");
    if (!f) {
        perror("Erro");
        return;
    }
    No* atual = lista;
    while (atual != NULL) {
        Objeto* obj = &atual->objeto;
        fwrite(&obj->tipo, sizeof(TipoObjeto), 1, f); // salva o tipo do objeto como bytes
        fwrite(obj->cor, sizeof(float), 3, f);
        if (obj->tipo == PONTO) {
            fwrite(&obj->ponto, sizeof(Ponto), 1, f); // salva os dados do ponto
        } else if (obj->tipo == LINHA) {
            fwrite(&obj->linha, sizeof(Linha), 1, f); // salva os dados da linha (ponto_a e ponto_b)
        } else if (obj->tipo == POLIGONO) {
            fwrite(&obj->poligono.total, sizeof(int), 1, f); // salva a quantidade de pontos do polígono
            fwrite(obj->poligono.pontos, sizeof(Ponto), obj->poligono.total, f); // salva todos os pontos do polígono em sequência
        }
        atual = atual->proximo;
    }
    fclose(f);
    printf("Salvo \n");
}
