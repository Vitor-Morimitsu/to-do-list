#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define NUM_LISTAS 4

typedef struct compromisso{
    char* nomeTarefa;
}Compromisso;

const char* nomesPrioridade[NUM_LISTAS] = {
    "muito importante e urgente",
    "muito importante e não urgente",
    "não importante mas deve ser feito rápido",
    "não importante e sem pressa"
};

/// @brief Libera a memória de um Compromisso (usada como callback do TAD lista)
/// @param comp Ponteiro genérico para o Compromisso
void liberarCompromisso(void* comp){
    if(comp == NULL) return;
    Compromisso* c = (Compromisso*)comp;
    free(c->nomeTarefa);
    free(c);
}

/// @brief Limpa o buffer de entrada (substituto portável do setbuf)
void limparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/// @brief Lê um inteiro do stdin com validação
/// @param valor Ponteiro para armazenar o valor lido
/// @return 1 se leu com sucesso, 0 se a entrada era inválida
int lerInteiro(int* valor){
    if(scanf("%d", valor) != 1){
        limparBuffer();
        return 0;
    }
    return 1;
}

void exibirCompromissos(Lista lista, int numeroLista){
    if(lista == NULL){
        printf("Erro em exibirCompromissos\n");
        return;
    }
    printf("Lista %d (%s):\n", numeroLista, nomesPrioridade[numeroLista - 1]);
    CelulaLista cel = getPrimeiraCelulaLista(lista);
    if(cel == NULL){
        printf("  (vazia)\n");
    }
    while(cel != NULL){
        Compromisso* compAtual = (Compromisso*)getConteudoCelula(cel);
        printf("  ID: %d  |  %s\n", getIDCelula(cel), compAtual->nomeTarefa);
        cel = getProximaCelulaLista(cel);
    }
    printf("----------------------------------------------------------------------------\n");
}

/// @brief Solicita ao usuário qual lista deseja operar
/// @param listas Array de listas
/// @param indice Ponteiro para armazenar o número da lista escolhida (1 a NUM_LISTAS)
/// @return A lista escolhida, ou NULL se a entrada for inválida
Lista escolherLista(Lista listas[], int* indice){
    int escolha = -1;
    printf("Digite o número da lista (1-%d): ", NUM_LISTAS);
    if(!lerInteiro(&escolha) || escolha < 1 || escolha > NUM_LISTAS){
        printf("Lista inválida\n");
        return NULL;
    }
    *indice = escolha;
    return listas[escolha - 1];
}

int main()
{
    int comando = 1;
    Lista listas[NUM_LISTAS];
    for(int i = 0; i < NUM_LISTAS; i++){
        listas[i] = criarLista();
    }
    int id = 0;

    while(comando >= 1){
        printf("\n\n");
        printf("O que deseja fazer?\nSelecione a opção desejada\n\n");
        printf("1 - adicionar tarefa\n2 - ver as tarefas salvas\n3 - remover tarefa\n4 - alterar tarefa\n5 - Sugestão de ação\n0 - encerrar o programa\n");

        if(!lerInteiro(&comando)){
            printf("Entrada inválida. Digite um número.\n");
            continue;
        }

        if(comando == 0){
            printf("Programa encerrado!\n");
            break;

        }else if(comando == 1){
            // Adicionar tarefa
            Compromisso *novaTarefa = malloc(sizeof(Compromisso));
            if(novaTarefa == NULL){
                printf("Erro ao alocar memória para nova tarefa\n");
                continue;
            }

            char texto[200];
            limparBuffer();
            printf("Nome da tarefa: ");
            fgets(texto, sizeof(texto), stdin);
            texto[strcspn(texto, "\n")] = '\0';

            novaTarefa->nomeTarefa = malloc(strlen(texto) + 1);
            if(novaTarefa->nomeTarefa == NULL){
                printf("Erro ao alocar memória para nome da tarefa\n");
                free(novaTarefa);
                continue;
            }
            strcpy(novaTarefa->nomeTarefa, texto);

            int escolhaPrioridade = 0;
            printf("Defina o grau de prioridade da tarefa:\n");
            for(int i = 0; i < NUM_LISTAS; i++){
                printf("    %d-> %s\n", i, nomesPrioridade[i]);
            }

            if(!lerInteiro(&escolhaPrioridade) || escolhaPrioridade < 0 || escolhaPrioridade >= NUM_LISTAS){
                printf("Prioridade inválida. Tarefa descartada.\n");
                free(novaTarefa->nomeTarefa);
                free(novaTarefa);
                continue;
            }

            adicionarLista(listas[escolhaPrioridade], novaTarefa, id);
            printf("Tarefa adicionada com sucesso! (ID: %d)\n", id);
            id++;

        }else if(comando == 2){
            // Ver tarefas salvas
            for(int i = 0; i < NUM_LISTAS; i++){
                exibirCompromissos(listas[i], i + 1);
            }

        }else if(comando == 3){
            // Remover tarefa
            int indice;
            Lista lista = escolherLista(listas, &indice);
            if(lista == NULL) continue;

            exibirCompromissos(lista, indice);

            int idTarefa = -1;
            printf("\nDigite o ID da tarefa que deseja remover: ");
            if(!lerInteiro(&idTarefa)){
                printf("Entrada inválida.\n");
                continue;
            }
            removerLista(lista, idTarefa, liberarCompromisso);

        }else if(comando == 4){
            // Alterar tarefa
            int indice;
            Lista lista = escolherLista(listas, &indice);
            if(lista == NULL) continue;

            exibirCompromissos(lista, indice);

            int idTarefa = -1;
            printf("\nDigite o ID da tarefa que deseja alterar: ");
            if(!lerInteiro(&idTarefa)){
                printf("Entrada inválida.\n");
                continue;
            }

            CelulaLista cel = buscarCelula(lista, idTarefa);
            if(cel == NULL){
                printf("Tarefa com ID %d não encontrada.\n", idTarefa);
                continue;
            }

            Compromisso* comp = (Compromisso*)getConteudoCelula(cel);
            printf("Nome atual: %s\n", comp->nomeTarefa);

            char novoTexto[200];
            limparBuffer();
            printf("Novo nome da tarefa: ");
            fgets(novoTexto, sizeof(novoTexto), stdin);
            novoTexto[strcspn(novoTexto, "\n")] = '\0';

            free(comp->nomeTarefa);
            comp->nomeTarefa = malloc(strlen(novoTexto) + 1);
            if(comp->nomeTarefa == NULL){
                printf("Erro ao alocar memória\n");
                continue;
            }
            strcpy(comp->nomeTarefa, novoTexto);
            printf("Tarefa alterada com sucesso!\n");

        }else if(comando == 5){
            // Sugestão de ação (Matriz de Eisenhower)
            // Percorre as listas em ordem de prioridade e sugere a primeira tarefa encontrada
            int sugerido = 0;
            for(int i = 0; i < NUM_LISTAS && !sugerido; i++){
                CelulaLista cel = getPrimeiraCelulaLista(listas[i]);
                if(cel != NULL){
                    Compromisso* comp = (Compromisso*)getConteudoCelula(cel);
                    printf("\n>>> Sugestão: faça agora a tarefa \"%s\"\n", comp->nomeTarefa);
                    printf("    (Lista %d - %s)\n", i + 1, nomesPrioridade[i]);
                    sugerido = 1;
                }
            }
            if(!sugerido){
                printf("\nNenhuma tarefa cadastrada. Aproveite o tempo livre!\n");
            }

        }else{
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    // Liberar toda a memória antes de encerrar
    for(int i = 0; i < NUM_LISTAS; i++){
        destruirLista(listas[i], liberarCompromisso);
    }

    return 0;
}
