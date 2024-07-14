#ifndef ESTRUTURA_H
#define ESTRUTURA_H
#include "funcoes.h"

//DECLARACAO DA STRUCT
struct Sdata {
    int dia;
    int mes;
    int ano;
};

struct SHorario {
    int hora;
    int minuto;
};

struct Evento {
    struct Sdata data;
    struct SHorario inicio;
    struct SHorario fim;
    char descricao[100];
    char local[100];
};

void carrega_arquivo(struct Evento **pv, int *qtEventos, int *maxEventos, char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rt");
    if (f == NULL) {
        printf("\nArquivo de Calendario não encontrado. Criando novo arquivo. Aperte enter para continuar.");
        *qtEventos = 0;
        *maxEventos = 10;
        *pv = malloc(sizeof(struct Evento) * (*maxEventos));
        getchar();

        return;
    }
    
    fscanf(f, "%d", qtEventos);
    *maxEventos = ((*qtEventos / 10) + 1) * 10; 
    *pv = malloc(sizeof(struct Evento) * (*maxEventos));

    for (int i = 0; i < *qtEventos; i++) {
        fscanf(f, "%d/%d/%d", &(*pv)[i].data.dia, &(*pv)[i].data.mes, &(*pv)[i].data.ano);
        fscanf(f, "%d:%d", &(*pv)[i].inicio.hora, &(*pv)[i].inicio.minuto);
        fscanf(f, "%d:%d", &(*pv)[i].fim.hora, &(*pv)[i].fim.minuto);
        fscanf(f, " %[^\n]", (*pv)[i].descricao);
        fscanf(f, " %[^\n]", (*pv)[i].local);
    }
    fclose(f);

    printf("\nArquivo de Calendario carregado com sucesso. Aperte enter para continuar.");
    getchar();
}

void salva_arquivo(struct Evento *pv, int qtEventos, char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "wt");
    fprintf(f, "%d\n", qtEventos);
    for (int i = 0; i < qtEventos; i++) {
        fprintf(f, "%02d/%02d/%04d\n", pv[i].data.dia, pv[i].data.mes, pv[i].data.ano);
        fprintf(f, "%02d:%02d\n", pv[i].inicio.hora, pv[i].inicio.minuto);
        fprintf(f, "%02d:%02d\n", pv[i].fim.hora, pv[i].fim.minuto);
        fprintf(f, "%s\n", pv[i].descricao);
        fprintf(f, "%s\n", pv[i].local);
    }
    fclose(f);
}

// FUNCAO QUE FAZ A ORDENACAO DO CALENDARIO
int comparaEventos(struct Evento a, struct Evento b) {
    if (a.data.ano != b.data.ano)
        return a.data.ano - b.data.ano;

    if (a.data.mes != b.data.mes)
        return a.data.mes - b.data.mes;

    if (a.data.dia != b.data.dia)
        return a.data.dia - b.data.dia;

    if (a.inicio.hora != b.inicio.hora)
        return a.inicio.hora - b.inicio.hora;

    if (a.inicio.minuto != b.inicio.minuto)
        return a.inicio.minuto - b.inicio.minuto;

    return 0;
}

void selectionSort(struct Evento *calendario, int qtEventos) {
    int i, j, min_idx;
    struct Evento temp;

    for (i = 0; i < qtEventos - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < qtEventos; j++) {
            if (comparaEventos(calendario[j], calendario[min_idx]) < 0) {
                min_idx = j;
            }
        }

        temp = calendario[min_idx];
        calendario[min_idx] = calendario[i];
        calendario[i] = temp;
    }
}

int verificaCriacao(struct Evento *calendario, int qtEventos, struct Evento aux) {
    for (int i = 0; i < qtEventos; i++) {
        if (calendario[i].data.ano == aux.data.ano && calendario[i].data.mes == aux.data.mes && calendario[i].data.dia == aux.data.dia) {
            if (!(aux.fim.hora < calendario[i].inicio.hora || (aux.fim.hora == calendario[i].inicio.hora && aux.fim.minuto <= calendario[i].inicio.minuto) ||(aux.inicio.hora > calendario[i].fim.hora || (aux.inicio.hora == calendario[i].fim.hora && aux.inicio.minuto >= calendario[i].fim.minuto)))){
            return 0; // conflito de horario
            // printf("to aqui.");
            }
        }
    }
    return 1; // Sem conflito de horario
}

//FUNCOES SECUNDARIAS DAS FUNCOES PRIMARIAS
void le_Data (struct Evento *aux){
    char strAux[20];
    int dataOk = 0;

    while(!dataOk){
        printf("Digite o dia do evento (dd/mm/aaaa): ");
        limpaBuffer();
        scanf("%s", strAux);
        sscanf(strAux, "%d/%d/%d", &aux->data.dia, &aux->data.mes, &aux->data.ano);
        
        if (dataValida(aux->data.dia, aux->data.mes, aux->data.ano)){
            dataOk = 1;
        }else{
            printf("Data inválida. Por favor, digite novamente.\n");
        }
    }
}

void le_Horario_Inicio(struct Evento *aux){
    int inicioOk = 0;
    char strAux[20];

    while(!inicioOk){
        printf("Digite o horario de inicio no formato (hh:mm): ");
        scanf("%s", strAux);
        sscanf(strAux, "%d:%d", &aux->inicio.hora, &aux->inicio.minuto);

        if (horarioValido(aux->inicio.hora, aux->inicio.minuto)){
            inicioOk = 1;
        }else {
            printf("Horário de início inválido. Por favor, digite novamente.\n");
        }
    }
}

void le_Horario_Fim(struct Evento *aux){
    int fimOk = 0;
    char strAux[20];
    while (!fimOk){
        printf("Digite o horario de termino no formato (hh:mm): ");
        limpaBuffer();
        scanf("%s", strAux);
        sscanf(strAux, "%d:%d", &aux->fim.hora, &aux->fim.minuto);

        if (horarioValido(aux->fim.hora, aux->fim.minuto)) {
            fimOk = 1;
        }
        else {
            printf("Horário de término inválido. Por favor, digite novamente.\n");
        }
    }
}

int validaHorario(struct Evento aux){
   if(aux.fim.hora < aux.inicio.hora || (aux.inicio.hora == aux.fim.hora && aux.fim.minuto <= aux.inicio.minuto)) return 0;
   else return 1;
}

// FUNCOES PRINCIPAIS DA MAIN
void cadastrar(struct Evento **calendario, int *qtEventos, int *MaxEventos) {
    struct Evento aux;
    char strAux[20];
    int ok = 0, sair = 0;
    
    limpaTela();
    printf("INSERIR EVENTO\n");
    printf("--------------\n\n");
    while (!ok && !sair) { 
        
        le_Data(&aux);
        le_Horario_Inicio(&aux);
        le_Horario_Fim(&aux);

        if (verificaCriacao(*calendario, *qtEventos, aux)) {
            ok = 1;
            if(!validaHorario(aux)){
                limpaTela();
                printf("\nHorario final menor que o inicial.\n");
                limpaBuffer();
                getchar();
                sair = 1;
            }

        } else {
            limpaTela();
            printf("\nHorário conflitante com outro evento. Aperte enter para voltar.");
            limpaBuffer();
            getchar();
            sair = 1;
        }
    }
    if (!sair){
        printf("Digite a descricao do evento: ");
        limpaBuffer();
        scanf("%[^\n]", aux.descricao);

        printf("Digite o local do evento: ");
        limpaBuffer();
        scanf("%[^\n]", aux.local);

        (*qtEventos)++;
        if (*qtEventos > *MaxEventos) {
            *MaxEventos += 10;
            *calendario = realloc(*calendario, (*MaxEventos) * sizeof(struct Evento));
        }

        (*calendario)[*qtEventos - 1] = aux;

        printf("\nEvento adicionado ao calendário com sucesso. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
    }
}

void mostraEventos(struct Evento *calendario, int qtEventos) {
    limpaTela();
    printf("MOSTRAR TODOS OS EVENTOS\n");
    printf("------------------------\n\n");
    
    if (qtEventos == 0) {
        printf("Nenhum evento cadastrado.\n");
        limpaBuffer();
        getchar();
        return;
    }

    for (int i = 0; i < qtEventos; i++) {
        printf("Evento %d:\n", i + 1);
        printf("\t| Data: %02d/%02d/%04d\n", calendario[i].data.dia, calendario[i].data.mes, calendario[i].data.ano);
        printf("\t| Inicio: %02d:%02d\n", calendario[i].inicio.hora, calendario[i].inicio.minuto);
        printf("\t| Fim: %02d:%02d\n", calendario[i].fim.hora, calendario[i].fim.minuto);
        printf("\t| Descricao: %s\n", calendario[i].descricao);
        printf("\t| Local: %s\n", calendario[i].local);
        printf("\n");
    }
    printf("Aperte enter para voltar.");
    limpaBuffer();
    getchar();
}

void mostraData(struct Evento *calendario, int qtEventos) {   
    limpaTela();
    printf("MOSTRA EVENTOS PELA DATA\n");
    printf("------------------------\n\n");
    
    if (qtEventos == 0) {
        printf("Nenhum evento cadastrado.\n");
        limpaBuffer();
        getchar();
        return;
    }

    char dataStr[15];
    int dia, mes, ano, ok = 0, temEvento = 0;
    while (!ok) {
        
        limpaBuffer();
        printf("Digite a Data que deseja procurar os Eventos (dd/mm/aaaa): ");
        scanf("%s", dataStr);
        sscanf(dataStr, "%d/%d/%d", &dia, &mes, &ano);
        if (dataValida(dia, mes, ano)) {
            ok = 1;
        } else {
            printf("Data inválida. Por favor, digite novamente.\n");
        }
    }

    for (int i = 0; i < qtEventos; i++) {
        if (calendario[i].data.ano == ano && calendario[i].data.mes == mes && calendario[i].data.dia == dia) {
            printf("Evento %d:\n", i + 1);
            printf("\t| Data: %02d/%02d/%04d\n", calendario[i].data.dia, calendario[i].data.mes, calendario[i].data.ano);
            printf("\t| Inicio: %02d:%02d\n", calendario[i].inicio.hora, calendario[i].inicio.minuto);
            printf("\t| Fim: %02d:%02d\n", calendario[i].fim.hora, calendario[i].fim.minuto);
            printf("\t| Descricao: %s\n", calendario[i].descricao);
            printf("\t| Local: %s\n", calendario[i].local);
            printf("\n");
            temEvento = 1;
        }
    }

    if (!temEvento) {
        printf("Nenhum evento neste dia. Aperte enter para voltar.");
    } else printf("Aperte enter para voltar.");

    limpaBuffer();
    getchar();
}

void mostraDescricao(struct Evento *calendario, int qtEventos){
    int temEvento = 0;
    char aux[100];

    if (qtEventos == 0) {
        limpaTela();
        printf("MOSTRA DESCRICAO\n");
        printf("----------------\n\n");
        printf("Nenhum evento cadastrado.\n");
        limpaBuffer();
        getchar();
        return;
    }
    
    limpaTela();
    printf("MOSTRA DESCRICAO\n");
    printf("----------------\n\n");
    printf("Digite a descricao dos eventos que deseja procurar: ");
    limpaBuffer();
    scanf(" %[^\n]", aux);

    for (int i = 0; i < qtEventos; i++){
        if (strcmp(calendario[i].descricao, aux) == 0){
            printf("Evento %d:\n", i + 1);
            printf("\t| Data: %02d/%02d/%04d\n", calendario[i].data.dia, calendario[i].data.mes, calendario[i].data.ano);
            printf("\t| Inicio: %02d:%02d\n", calendario[i].inicio.hora, calendario[i].inicio.minuto);
            printf("\t| Fim: %02d:%02d\n", calendario[i].fim.hora, calendario[i].fim.minuto);
            printf("\t| Descricao: %s\n", calendario[i].descricao);
            printf("\t| Local: %s\n", calendario[i].local);
            printf("\n");
            temEvento = 1;
        }
    }

    if (!temEvento){
        printf("Nenhum evento com esta descricao. Aperte enter para voltar.");
    }else printf("Aperte enter para voltar.");
    limpaBuffer();
    getchar();
}

void removerEventos(struct Evento **calendario, int *qtEventos) {
    int dia, mes, ano, hora, minutos, dataOk = 0, horaOk = 0, j, removido = 0;
    char dataStr[15], horaStr[10];
    
    limpaTela();
    printf("REMOVER EVENTO\n");
    printf("--------------\n\n");

    if (*qtEventos == 0) {   
        printf("Nenhum evento cadastrado.\n");
        limpaBuffer();
        getchar();
        return;
    }
    
    while (!dataOk) {
        printf("Digite a data do evento que deseja remover no formato (dd/mm/aaaa): ");
        scanf("%s", dataStr);
        sscanf(dataStr, "%d/%d/%d", &dia, &mes, &ano);

        if (dataValida(dia, mes, ano)) {
            dataOk = 1;
        } else {
            printf("Data inválida. Por favor, digite novamente.\n");
        }
    }

    while (!horaOk) {
        printf("Digite a hora do evento que deseja remover no formato (hh:mm): ");
        scanf("%s", horaStr);
        sscanf(horaStr, "%d:%d", &hora, &minutos);
        if (horarioValido(hora, minutos)) {
            horaOk = 1;
        } else {
            printf("\nHorário inválido. Por favor, digite novamente.\n");
        }
    }

    for (int i = 0; i < *qtEventos; i++) {
        if ((*calendario)[i].data.ano == ano && (*calendario)[i].data.mes == mes && (*calendario)[i].data.dia == dia && (*calendario)[i].inicio.hora == hora && (*calendario)[i].inicio.minuto == minutos) {
            for (j = i; j < *qtEventos - 1; j++) {
                (*calendario)[j] = (*calendario)[j + 1];
            }

            (*qtEventos)--;
            *calendario = (struct Evento *)realloc(*calendario, (*qtEventos) * sizeof(struct Evento));
            removido = 1;
        }
    }

    if (!removido){
        printf("Evento nao encontrado. Aperte enter para voltar.");
    }else printf("Evento removido com sucesso. Aperte enter para voltar.");
    limpaBuffer();
    getchar();
}

#endif 