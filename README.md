<div align="center" id="topo">

<img src="https://media.giphy.com/media/iIqmM5tTjmpOB9mpbn/giphy.gif" width="200px" alt="Gif animado"/>

# <code><strong>Calendário de eventos</strong></code>

<em>Trabalho da disciplina de Linguagem de Programação</em>

[![C Usage](https://img.shields.io/badge/C-100%25-blue?style=for-the-badge&logo=c)]()
[![Status](https://img.shields.io/badge/Status-Concluído-green?style=for-the-badge)]()
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Visite%20meu%20perfil-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/rian-carlos-valcanaia-b2b487168/)

</div>

## Índice

- [📌 Objetivos](#-objetivos)
- [📥 Entradas do sistema](#-entradas-do-sistema)
- [🧱 Estruturas de Dados](#-estruturas-de-dados)
- [🧰 Funcionalidades](#-funcionalidades)
- [📊 Exemplo de Execução](#-exemplo-de-execução)
- [📂 Como executar](#-como-executar)
- [👨‍🏫 Envolvidos](#-envolvidos)
- [📅 Curso](#-curso)
- [📄 Código-fonte](#-código-fonte)

## 📌 Objetivos
O objetivo deste projeto é desenvolver uma agenda de eventos em C, que permite ao usuário gerenciar seus compromissos de forma persistente.
* Permitir o cadastro de novos eventos com data, horários de início e fim, descrição e local.
* Garantir a persistência dos dados, salvando e carregando automaticamente os eventos de um arquivo de texto (`calendario.txt`).
* Manter os eventos organizados cronologicamente, ordenando a lista após cada nova inserção.
* Implementar funcionalidades de busca, permitindo ao usuário encontrar eventos por data ou por descrição.
* Validar as entradas do usuário, como datas e horários, e impedir a criação de eventos com horários conflitantes.
* Permitir a remoção de eventos existentes com base na sua data e horário de início.
* Gerenciar a memória de forma dinâmica para acomodar um número variável de eventos.

Precisava seguir as seguintes regras:
* Salvamento usando arquivo.
* Alocação dinâmica.
* Tratar conflitos de horários, e entrada de dados do usuário.

[⬆ Voltar ao topo](#topo)

## 📥 Entradas do sistema
O sistema interage com o usuário através de um menu e solicita as seguintes informações:
* **Opção do menu:** Um número de 1 a 6 para selecionar a funcionalidade desejada.
* **Dados do Evento:**
    * Data no formato `dd/mm/aaaa`.
    * Horário de início no formato `hh:mm`.
    * Horário de término no formato `hh:mm`.
    * Descrição do evento (texto).
    * Local do evento (texto).
* **Dados de Busca:**
    * Uma data (`dd/mm/aaaa`) para listar todos os eventos do dia.
    * Uma descrição (texto) para listar todos os eventos correspondentes.
* **Dados de Remoção:**
    * A data e o horário de início do evento a ser removido.

[⬆ Voltar ao topo](#topo)

## 🧱 Estruturas de Dados
O programa utiliza um conjunto de `structs` para modelar os dados de um evento e gerenciar o calendário de forma organizada.

### 🔸 `Sdata`
```c
struct Sdata {
    int dia;
    int mes;
    int ano;
};
```
### 🔸'SHorario'
```c
struct SHorario {
    int hora;
    int minuto;
};
```
### 🔸'Evento'
```c
struct Evento {
    struct Sdata data;
    struct SHorario inicio;
    struct SHorario fim;
    char descricao[100];
    char local[100];
};
```
## 🧰 Funcionalidades

### 🔹 Funções Principais
* `cadastrar()`: Coleta os dados de um novo evento, valida a data, os horários e verifica se não há conflito com eventos existentes antes de adicionar ao calendário.
* `mostraEventos()`: Exibe na tela a lista completa de todos os eventos cadastrados, de forma ordenada.
* `mostraData()`: Pede uma data ao usuário e exibe todos os eventos agendados para aquele dia.
* `mostraDescricao()`: Pede uma descrição ao usuário e exibe todos os eventos que correspondem exatamente àquela descrição.
* `removerEventos()`: Solicita a data e o horário de início de um evento para removê-lo do calendário.
* `carrega_arquivo()`: Carrega os eventos do arquivo `calendario.txt` para a memória ao iniciar o programa.
* `salva_arquivo()`: Salva todos os eventos da memória no arquivo `calendario.txt` ao encerrar o programa.
* `selectionSort()`: Ordena a lista de eventos por data e hora após cada inserção ou alteração.

### 🔸 Funções Secundárias
* `limpaTela()`, `limpaBuffer()`, `telaInicial()`, `menuInicial()`, `entradaUsuario()`, `dataValida()`, `horarioValido()`, `comparaEventos()`, `verificaCriacao()`, `le_Data()`, `le_Horario_Inicio()`, `le_Horario_Fim()`, `validaHorario()`

[⬆ Voltar ao topo](#topo)

## 📊 Exemplo de Execução
1. Ao iniciar, o programa tenta carregar os eventos salvos no arquivo `calendario.txt`. Se o arquivo não existir, um novo calendário vazio é criado.
2. O usuário é apresentado a um menu com 6 opções (Cadastrar, Mostrar todos, Pesquisar, etc.).
3. O usuário seleciona a opção 1 para cadastrar um novo evento. O sistema solicita data, horários, descrição e local, validando cada entrada.
4. Após o cadastro, o evento é adicionado e a lista inteira é ordenada automaticamente.
5. O usuário pode usar as opções 2, 3 ou 4 para visualizar os eventos que cadastrou.
6. Ao final do uso, o usuário seleciona a opção 6 para sair. O programa salva automaticamente todos os eventos no arquivo `calendario.txt`, garantindo que não sejam perdidos.

[⬆ Voltar ao topo](#topo)

## 📂 Como executar
Para compilar e executar o programa, que está dividido em múltiplos arquivos, utilize o seguinte comando no terminal. Ele irá gerar um executável chamado `agenda`.
```bash
gcc main.c -o agenda && ./agenda
``` 

[⬆ Voltar ao topo](#topo)

## 👨‍🏫 Envolvidos
* **Professor**: Rui Jorge Tramontin Junior
* **Estudantes**:
  * [Rian Valcanaia](https://github.com/RianValcanaia)

[⬆ Voltar ao topo](#topo)

## 📅 Curso

* **Universidade**: Universidade do Estado de Santa Catarina (UDESC)
* **Disciplina**: Linguagem de Programação
* **Semestre**: 2º

[⬆ Voltar ao topo](#topo)

## 📄 Código-fonte

🔗 [https://github.com/RianValcanaia/LPG_Trabalho_Agenda](https://github.com/RianValcanaia/LPG_Trabalho_Agenda)

[⬆ Voltar ao topo](#topo)
