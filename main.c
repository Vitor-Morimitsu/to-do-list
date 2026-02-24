#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct compromisso{
    char* nomeTarefa;
    int prioridade;
}Compromisso;

void exibirCompromissos(Lista lista, int numeroLista){
    if(lista == NULL){
        printf("Erro em exibirCompromissos\n");
        return;
    }
    if(numeroLista == 1){
        printf("Lista 1 (muito importante e urgente):\n");
    }else if(numeroLista == 2){
        printf("Lista 2 ( muito importante e não urgente):\n");
    }else if(numeroLista == 3){
        printf("Lista 3 (não importante mas deve ser feito rápido):\n");
    }else if(numeroLista == 4){
        printf("Lista 4 (não importante e sem pressa):\n");
    }
    CelulaLista cel = getPrimeiraCelulaLista(lista);
    while(cel != NULL){
        void* atual = getConteudoCelula(cel);
        Compromisso* compAtual = atual;
        printf("ID: %i,     %s\n",getIDCelula(cel), compAtual->nomeTarefa);
        cel = getProximaCelulaLista(cel);
    }
    printf("----------------------------------------------------------------------------\n");
}

int main()
{
    int comando = 1;
    Lista listaP0 = criarLista();
    Lista listaP1 = criarLista();
    Lista listaP2 = criarLista();
    Lista listaP3 = criarLista();
    int id = 0;
    while(comando >= 1){
        printf("\n");
        printf("\n");

        printf("O que deseja fazer?\nSelecione a opção desejada\n");

        printf("\n");

        printf("1 - adicionar tarefa\n2 - ver as tarefas salvas\n3 - remover tarefa\n4 - alterar tarefa\n5 - Sugestão de ação\n0 - encerrar o programa\n");
        scanf("%d", &comando);

        if(comando == 0){
            printf("Programa encerrado!\n");
            break;
        }else if (comando == 1){
            Compromisso *novaTarefa = malloc(sizeof(Compromisso));
            
            char texto[200];
            setbuf(stdin,NULL);
            printf("Nome da tarefa: ");
            fgets(texto,sizeof(texto), stdin);
            novaTarefa->nomeTarefa = malloc(strlen(texto) + 1);
            strcpy(novaTarefa->nomeTarefa, texto);
            
            int escolhaPrioridade = 0;
            printf("Defina o grau de prioridade da tarefa: \n    0-> muito importante e urgente\n    1-> muito importante e não urgente\n    2-> não importante mas deve ser feito rápido\n    3-> não importante e sem pressa\n");
            scanf("%d", &escolhaPrioridade);

            if(escolhaPrioridade == 0){
                adicionarLista(listaP0,novaTarefa,id);
                
            }else if(escolhaPrioridade == 1){ 
                adicionarLista(listaP1, novaTarefa,id);
            
            }else if(escolhaPrioridade == 2){
                adicionarLista(listaP2, novaTarefa,id);
                
            }else if( escolhaPrioridade == 3){
                adicionarLista(listaP3,novaTarefa,id);
            }
            id++;
        }else if(comando == 2){
            //ver as tarefas salvas
            exibirCompromissos(listaP0,1);
            exibirCompromissos(listaP1,2);
            exibirCompromissos(listaP2,3);
            exibirCompromissos(listaP3,4);

        }else if(comando == 3){
            //remover tarefa
            int escolhaLista = -1;
            int idTarefa = -1;            
            printf("Digite a lista em que a tarefa que deseja remover está: ");
            scanf("%i", &escolhaLista);
            if(escolhaLista == 1){
                //printar as tarefas com os ids da lista p0
                exibirCompromissos(listaP0,1);

                printf("\nDigite o Id da tarefa que deseja remover: ");
                scanf("%i", &idTarefa);
                removerLista(listaP0, idTarefa);

            }else if(escolhaLista == 2){
                exibirCompromissos(listaP1,2);

                printf("\nDigite o Id da tarefa que deseja remover: ");
                scanf("%i", &idTarefa);
                removerLista(listaP1, idTarefa);

            }else if(escolhaLista == 3){
                exibirCompromissos(listaP2,3);

                printf("\nDigite o Id da tarefa que deseja remover: ");
                scanf("%i", &idTarefa);
                removerLista(listaP2, idTarefa);

            }else if(escolhaLista == 4){
                exibirCompromissos(listaP3,4);

                printf("\nDigite o Id da tarefa que deseja remover: ");
                scanf("%i", &idTarefa);
                removerLista(listaP3, idTarefa);

            }else{
                printf("Lista inexistente\n");
            }

        }else if(comando == 4){
            //alterar a tarefa
            int lista = -1;
            printf("Em qual lista está a tarefa que deseja alterar?\n");
            scanf("%i", &lista);
            if(lista == 1){

            }else if(lista == 2){

            }else if(lista == 3){

            }else if(lista == 4){

            }else{
                printf("Lista inválida\n");
            }

        }else if(comando == 5){
            //sugestão de ação
        }
    }

}
