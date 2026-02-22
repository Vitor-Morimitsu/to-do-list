#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Arquivo .h destinado à criação de uma lista ligada e suas respectivas funções
*/

typedef void* Lista;
typedef void* CelulaLista;

/// @brief Cria e retorna a lista criada
/// @return Lista criada
Lista criarLista();

/// @brief Define o conteudo de uma célula da lista
/// @param cel Célula da lista
/// @param cont Conteúdo que será definido
void setConteudoCel(CelulaLista cel, void* cont);

/// @brief Cria uma Célula da lisat
/// @param conteudo Conteúdo que será atribuído à célula
/// @param id Id da célula
/// @return Célula criada
CelulaLista criarCelulaLista(void* conteudo, int id);

/// @brief Busca um célula da lista com base no id fornecido
/// @param lista Lista pré existente
/// @param idCelula Id da célula desejada
/// @return Céla com o id fornecido
CelulaLista buscarCelula(Lista lista,int idCelula);

/// @brief Retorna a primeira célula da lista
/// @param lista Lista pré existente
/// @return Primeira Celula
CelulaLista getPrimeiraCelulaLista(Lista lista);

/// @brief Retorna a próxima célula
/// @param atual Célula atual 
/// @return Próxima Célula
CelulaLista getProximaCelulaLista(CelulaLista atual);

/// @brief Retorna o conteudo armazenado pela célula
/// @param cel Celula da lista
/// @return Conteudo
void* getConteudoCelula(CelulaLista cel);

/// @brief Retorna o ID de uma célula
/// @param cel Celula pré existente
/// @return Id da célula
int getIDCelula(CelulaLista cel);

/// @brief Adiciona uma nova célula no final de uma lista já criada
/// @param lista Lista já existente
/// @param id Identificador que será atribuído à nova célula
/// @param novaCelula Nova célula que será adicionada
void adicionarLista(Lista lista, void* conteudo, int id);

/// @brief Remove um elemento de uma lista
/// @param lista Lista já existente
/// @param idRemov Id da célula que será removida
void removerLista(Lista lista, int idRemov);

/// @brief Busca e retorna uma Célula da lista
/// @param lista Lista já existente
/// @param idCelula Id da célula a ser buscada na lista
/// @return Celula da lista com o id correspondente
CelulaLista buscarCelula(Lista lista,int idCelula);
#endif