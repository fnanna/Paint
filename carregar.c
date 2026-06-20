#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "carregar.h"
#include "objetos.h"
#include "listaEncadeada.h"

extern No* lista;

void carregarArquivo(const char* caminho) {
    // monta o caminho completo igual ao salvar, pegando a pasta do executável
    char path[500];
    GetModuleFileNameA(NULL, path, 500);

    char* ultima_barra = strrchr(path, '\\');
    if (ultima_barra) *(ultima_barra + 1) = '\0';
    strcat(path, caminho);

    FILE* f = fopen(path, "rb");
    if (!f) {
        perror("Erro ao abrir arquivo para carregar");
        return;
    }

    // limpa tudo que está na tela antes de carregar
    limparLista();

    TipoObjeto tipo;

    // fread retorna 0 quando o arquivo acabar, encerrando o loop
    while (fread(&tipo, sizeof(TipoObjeto), 1, f) == 1) {

        Objeto obj;
        obj.tipo = tipo;

        if (tipo == PONTO) {
            // ponto tem tamanho fixo, lê de uma vez
            fread(&obj.ponto, sizeof(Ponto), 1, f);

        } else if (tipo == LINHA) {
            // linha também tem tamanho fixo (dois pontos), lê de uma vez
            fread(&obj.linha, sizeof(Linha), 1, f);

        } else if (tipo == POLIGONO) {
            // lê primeiro quantos pontos o polígono tem
            fread(&obj.poligono.total, sizeof(int), 1, f);

            // aloca memória para os pontos antes de ler, recriando o que existia ao salvar
            obj.poligono.pontos = (Ponto*) malloc(sizeof(Ponto) * obj.poligono.total);
            if (!obj.poligono.pontos) {
                perror("Erro ao alocar memoria para poligono");
                fclose(f);
                return;
            }

            // lê todos os pontos do polígono em sequência
            fread(obj.poligono.pontos, sizeof(Ponto), obj.poligono.total, f);
        }

        // insere o objeto reconstruído na lista
        inserirLista(obj);
    }

    fclose(f);
    printf("Carregado\n");
}
