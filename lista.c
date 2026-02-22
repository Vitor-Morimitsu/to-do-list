#include "lista.h"

typedef struct CelLista{
    struct CelLista* proxima;
    struct CelLista* anterior;
    void* conteudo;
    int id;
}stCelLista;

typedef stCelLista* pont;

typedef struct list{
    pont primeiraTarefa;
    pont ultimaTarefa;
    int tamanho;
}stLista;


Lista criarLista(){
    stLista* list = malloc(sizeof(stLista));
    if(list == NULL){
        printf("Erro ao gerar a lista\n");
        return NULL;
    }

    list->primeiraTarefa = NULL;
    list->ultimaTarefa = NULL;
    list->tamanho = 0;

    return list;
}

void setConteudoCel(CelulaLista cel, void* cont){
    if(cel == NULL){
        printf("Erro em setConteudoCel\n");
        return;
    }

    stCelLista* c = (stCelLista*)cel;
    c->conteudo = cont;
} 

CelulaLista criarCelulaLista(void* conteudo, int id){
    stCelLista* nova = malloc(sizeof(stCelLista));
    if(nova == NULL){
        printf("Erro em criarCelulaLista");
        return NULL;
    }
    nova->conteudo = conteudo;
    nova->anterior = NULL;
    nova->proxima = NULL;
    nova->id = id;

    return (CelulaLista)nova;
}

CelulaLista buscarCelula(Lista lista,int idCelula){
    if(lista == NULL){
        printf("Erro em buscarCelula\n");
        return NULL;
    }
    stLista* list = (stLista*)lista;
    pont temp = list->primeiraTarefa;
    while(temp != NULL){
        if(temp->id == idCelula){
            return temp;            
        }else{
            temp = temp->proxima;
        }
    }    
    //se saiu do loop e não retornou nada, não achou
    return NULL;
}

CelulaLista getPrimeiraCelulaLista(Lista lista){
    if(lista == NULL){
        printf("Erro em getPrimeiraCelulaLista\n");
        return NULL;
    }

    return ((stLista*)lista)->primeiraTarefa;
}

CelulaLista getProximaCelulaLista(CelulaLista atual){
    if(atual == NULL){
        printf("Erro em getProximaCelulaLista\n");
        return NULL;
    }

    return ((stCelLista*)atual)->proxima;
}

void* getConteudoCelula(CelulaLista cel){
    if(cel == NULL){
        printf("Erro em getConteudoCelula\n");
        return NULL;
    }

    return ((stCelLista*)cel)->conteudo;
}

int getIDCelula(CelulaLista cel){
    if(cel == NULL){
        printf("Erro em getIDCelula\n");
        return -1;
    }

    return((stCelLista*)cel)->id;
}

void adicionarLista(Lista lista, void* conteudo, int id){
    if(lista == NULL || conteudo == NULL){
        printf("Erro ao adicionar um novo compromisso na lista\n");
        return;
    }
    //casting 
    stLista* list = (stLista*)lista;

    pont novo = malloc(sizeof(stCelLista));
    if(novo == NULL){
        printf("Erro em adicionarLista\n");
        return;
    }
    novo->conteudo = conteudo;
    novo->proxima = NULL;
    novo->id = id;  // CORREÇÃO: Define o ID imediatamente
    
    if(list->primeiraTarefa == NULL){
        //lista estava vazia, ou seja, o elemento adicionado é o primeiro elemento da lista
        list->primeiraTarefa = novo;
        novo->anterior = NULL;
        list->ultimaTarefa = novo;  // CORREÇÃO: Define ultimaTarefa também

    }else {
        //lista não estava vazia
        list->ultimaTarefa->proxima = novo;
        novo->anterior = list->ultimaTarefa;
        list->ultimaTarefa = novo;
    }
    
    list->tamanho++;
}

void removerLista(Lista lista, int idRemov){
    if(lista == NULL){
        printf("Erro em removerLista\n");
        return;
    }

    stLista* l = (stLista*)lista;
    pont temp =(pont)buscarCelula(lista,idRemov);
    if(temp == NULL){
        printf("Célula com ID %i não encontrada\n", idRemov);
        return;
    }

    //temp contém a célula a ser removida

    //ver se é a primeira célula, ultima ou do meio
    if(l->primeiraTarefa == temp){
        l->primeiraTarefa = temp->proxima;
        if(l->primeiraTarefa != NULL){
            l->primeiraTarefa->anterior = NULL;  // CORREÇÃO: atualiza o ponteiro anterior
        }else{
            l->ultimaTarefa = NULL;  // Lista ficou vazia
        }
        l->tamanho--;
        free(temp->conteudo);
        free(temp);

    }else if ( l->ultimaTarefa == temp){
        l->ultimaTarefa = temp->anterior;
        if(l->ultimaTarefa != NULL){
            l->ultimaTarefa->proxima = NULL;  // CORREÇÃO: atualiza o ponteiro proxima
        }
        l->tamanho--;
        free(temp->conteudo);
        free(temp);

    }else{
        // Célula do meio
        temp->anterior->proxima = temp->proxima;
        temp->proxima->anterior = temp->anterior;  // CORREÇÃO: atualiza ambos os lados
        l->tamanho--;
        free(temp->conteudo);
        free(temp);
    }

}


