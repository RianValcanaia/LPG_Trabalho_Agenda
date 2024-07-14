#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"
#include "funcoes.h"

int main() {
    int opcao, continuar = 1, qtEventos = 0, MaxEventos;
    struct Evento *calendario = NULL;

    telaInicial();
    carrega_arquivo(&calendario, &qtEventos, &MaxEventos, "calendario.txt");
    
    while (continuar) {
        menuInicial();
        entradaUsuario(1, 6, &opcao);
        switch (opcao) {
            case 1:
                cadastrar(&calendario, &qtEventos, &MaxEventos);
                selectionSort(calendario, qtEventos);
                break;
            case 2:
                mostraEventos(calendario, qtEventos);
                break;
            case 3:
                mostraData(calendario, qtEventos);
                break;
            case 4:
                mostraDescricao(calendario, qtEventos);
                break;
            case 5:
                removerEventos(&calendario, &qtEventos);
                break;
            case 6:
                continuar = 0;
                break;
        }
    }

    salva_arquivo(calendario, qtEventos, "calendario.txt");
    free(calendario);
    limpaTela();
    return 0;
}