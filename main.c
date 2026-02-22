#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct compromisso{
    char* nomeTarefa;
    int prioridade;
}Compromisso;

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
            printf("Lista 1:\n");
            CelulaLista cel = getPrimeiraCelulaLista(listaP0);
            while(cel != NULL){
                void* atual = getConteudoCelula(cel);
                Compromisso* compAtual = atual;
                printf("%s\n", compAtual->nomeTarefa);
                cel = getProximaCelulaLista(cel);
            }
            printf("----------------------------------------------------------------------------\n");

            printf("Lista 2:\n");
            CelulaLista cel2 = getPrimeiraCelulaLista(listaP1);
            while(cel2 != NULL){
                void* atual = getConteudoCelula(cel2);
                Compromisso* compAtual = atual;
                printf("%s\n", compAtual->nomeTarefa);
                cel2 = getProximaCelulaLista(cel2);
            }
             printf("----------------------------------------------------------------------------\n");

             printf("Lista 3:\n");
            CelulaLista cel3 = getPrimeiraCelulaLista(listaP2);
            while(cel3 != NULL){
                void* atual = getConteudoCelula(cel3);
                Compromisso* compAtual = atual;
                printf("%s\n", compAtual->nomeTarefa);
                cel3 = getProximaCelulaLista(cel3);
            }
             printf("----------------------------------------------------------------------------\n");

             printf("Lista 4:\n");
            CelulaLista cel4 = getPrimeiraCelulaLista(listaP3);
            while(cel4 != NULL){
                void* atual = getConteudoCelula(cel4);
                Compromisso* compAtual = atual;
                printf("%s\n", compAtual->nomeTarefa);
                cel4 = getProximaCelulaLista(cel4);
            }
             printf("----------------------------------------------------------------------------\n");

        }else if(comando == 3){
            //remover tarefa
            int escolhaLista = -1;
            int idTarefa = -1;
            //EEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOOOOOOOOO ta removendo um item que não é o escolhido
            
            printf("Digite a lista em que a tarefa que deseja remover está: ");
            scanf("%i", &escolhaLista);
            if(escolhaLista == 1){
                //printar as tarefas com os ids
                CelulaLista cel = getPrimeiraCelulaLista(listaP0);
                while(cel != NULL){
                    void* atual = getConteudoCelula(cel);
                    Compromisso* compAtual = atual;
                    printf("ID: %i -- Nome da tarefa: %s\n",getIDCelula(cel) ,compAtual->nomeTarefa);
                    cel = getProximaCelulaLista(cel);
                }

                printf("\nDigite o Id da tarefa que deseja remover: ");
                scanf("%i", &idTarefa);
                removerLista(listaP0, idTarefa);

            }else if(escolhaLista == 2){
                CelulaLista cel = getPrimeiraCelulaLista(listaP1);
                while(cel != NULL){
                    void* atual = getConteudoCelula(cel);
                    Compromisso* compAtual = atual;
                    printf("ID: %i -- Nome da tarefa: %s\n",getIDCelula(cel) ,compAtual->nomeTarefa);
                    cel = getProximaCelulaLista(cel);
                }
                printf("\nDigite o Id da tarefa que deseja remover: ");
                scanf("%i", &idTarefa);
                removerLista(listaP1, idTarefa);

            }else if(escolhaLista == 3){
                CelulaLista cel = getPrimeiraCelulaLista(listaP2);
                while(cel != NULL){
                    void* atual = getConteudoCelula(cel);
                    Compromisso* compAtual = atual;
                    printf("ID: %i -- Nome da tarefa: %s\n",getIDCelula(cel) ,compAtual->nomeTarefa);
                    cel = getProximaCelulaLista(cel);
                }
                printf("\nDigite o Id da tarefa que deseja remover: ");
                scanf("%i", &idTarefa);
                removerLista(listaP2, idTarefa);

            }else if(escolhaLista == 4){
                CelulaLista cel = getPrimeiraCelulaLista(listaP3);
                while(cel != NULL){
                    void* atual = getConteudoCelula(cel);
                    Compromisso* compAtual = atual;
                    printf("ID: %i -- Nome da tarefa: %s\n",getIDCelula(cel) ,compAtual->nomeTarefa);
                    cel = getProximaCelulaLista(cel);
                }
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
