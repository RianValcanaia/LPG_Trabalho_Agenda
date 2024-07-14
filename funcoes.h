#ifndef FUNCOES_H
#define FUNCOES_H

// FUNCOES SECUNDARIAS 

void limpaTela() {
    #ifdef _WIN32
        system("cls");   // Comando para Windows
    #else
        system("clear"); // Comando para Linux
    #endif
}

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void telaInicial() {
    limpaTela();
    printf("   _____          _      ______ _   _ _____          _____  _____ ____  \n");
    printf("  / ____|   /\\   | |    |  ____| \\ | |  __ \\   /\\   |  __ \\|_   _/ __ \\ \n");
    printf(" | |       /  \\  | |    | |__  |  \\| | |  | | /  \\  | |__) | | || |  | |\n");
    printf(" | |      / /\\ \\ | |    |  __| | . ` | |  | |/ /\\ \\ |  _  /  | || |  | |\n");
    printf(" | |____ / ____ \\| |____| |____| |\\  | |__| / ____ \\| | \\ \\ _| || |__| |\n");
    printf("  \\_____/_/    \\_\\______|______|_| \\_|_____/_/    \\_\\_|  \\_\\_____\\____/ \n\n");
    printf("                                  Desenvolvido por Rian Carlos Valcanaia\n\n");
    printf("\n");
}

void menuInicial() {
    limpaTela();
    printf("MENU:\n\n");
    printf("1 - Cadastrar\n");
    printf("2 - Mostrar todos os eventos da agenda\n");
    printf("3 - Pesquisar eventos por data\n");
    printf("4 - Pesquisar eventos por descrição\n");
    printf("5 - Remover um evento\n");
    printf("6 - Sair\n");
    printf("\nDigite uma opcao: ");
}

int entradaUsuario(int inicioIntervalo, int fimIntervalo, int *entradaNum) {
    while (1) {
        if (scanf("%i", entradaNum) == 1 && *entradaNum >= inicioIntervalo && *entradaNum <= fimIntervalo) {
            break;
        } else {
            if (inicioIntervalo == fimIntervalo) {
                printf("Opcao invalida. Unica opcao disponível é %i.\n", fimIntervalo);
                limpaBuffer();
            } else {
                printf("Opcao invalida. Digite um numero de %i a %i.\n", inicioIntervalo, fimIntervalo);
                limpaBuffer();
            }
        }
    }
    return *entradaNum;
}

int dataValida(int dia, int mes, int ano) {
    if (ano < 1900 || ano > 2100)
        return 0;

    if (mes < 1 || mes > 12)
        return 0;

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
        diasNoMes[1] = 29;

    if (dia < 1 || dia > diasNoMes[mes - 1])
        return 0;

    return 1;
}

int horarioValido(int hora, int minuto) {
    if (hora < 0 || hora > 23)
        return 0;

    if (minuto < 0 || minuto > 59)
        return 0;

    return 1;
}

#endif 