/**
 * Universidade Federal de Santa Catarina
 * Centro Tecnológico
 * Departamento de Informática e Estatística
 * Ciências da Computação
 * INE5408 - Estruturas de Dados
 *
 * Trabalho de Implementação 2 - Pesquisa de ManPages
 *
 * Alunos: José Victor Feijó de Araujo  Matrícula: 14100842
 *
 * main.cpp
 */

#include <stdio.h>
#include <cstring>
#include <deque>
using namespace std;
#include "AvlTree.h"
#include "Word.h"
#include "Index.h"

void gerarArquivosDat(int argc, char* argv[]);
deque<int> posicaoDasManPagesCom(char* palavra);
void buscaPorUmaPalavra();
void buscaPorDuasPalavras();
void buscaConteudoPorComando();

static const int wordTamMax = 100;
static const int comandoTamMax = 100;
static const int conteudoTamMax = 149900;
static const int qtdConectivos = 25;
static const char* conectivos[] = {
    "a","the","and","or","if","of","to","into","by","for","on","at","in","next",
    "then","than","more","only","always","never","all","off","with","that",
    "this",""
};

// Menu de opções

int main(int argc, char* argv[]) {
    int entrada;
    do{
        printf("Digite o número para opção\n");
        printf("(1) - Gerar arquivos .dat\n");
        printf("(2) - Buscar conteudo pelo nome da manpage\n");
        printf("(3) - Buscar manpages por uma palavra\n");
        printf("(4) - Buscar manpages por duas palavras\n");
        printf("(0) - Para sair\n");
        scanf("%d\n",entrada);
        switch (entrada) {
            case 1: gerarArquivosDat(argc, argv); break;
            case 2: buscaConteudoPorComando(); break;
            case 3: buscaPorUmaPalavra(); break;
            case 4: buscaPorDuasPalavras(); break;
        }
    }while(entrada != 0);
}

/**
 * Recebe os argumentos da execução do programa, que devem ter a quantidade de
 * argumentos e o nome dos arquivos a serem processados.
 * Gera o arquivo "manpages.dat" que contém os nomes dos arquivos originais
 * e seus conteúdos, formatados com um tamanho máximo padrão para facilitar
 * a busca utilizando um índice
 * Durante a geração de "manpages.dat":
 *      é criada a árvore de "Index"s com nome dos arquivos e posição dele
 * em "manpages.dat";
 *      e a árvore de "Word"s com cada palavra que aparece nos arquivos e
 *  os índices dos arquivos que as contém.
 * Gera o "indices.dat" que é a árvore de "Index"s organizada em níveis,
 * que facilitará a busca
 * Gera o "words.dat" que é árvore de "Words"s organizada em níveis.
 *
 * As palavras são obtidas separando o texto original pelos seguintes
 * caracteres: " \n.,|`´^~<>:;_-+=()[]\"'/*!@#"
 * Os conectivos são retirados utilizando o array de palavras "conectivos"
 */
void gerarArquivosDat(int argc, char* argv[]) {
    //Alocando árvores em memória para não demorar a geração
    AvlTree<Index> indices;
    AvlTree<Word> palavras;

    //-----------Começa MANPAGES.DAT----------------//
    FILE *manPagesDat;
    manPagesDat = fopen("..\\manpages.dat", "wb");
    printf("Gerando manpages.dat ...\n");

    for(int i=1; i<argc, i++) {
        //Abre e le cada arquivo de manpage
        File *manPageF;
        manPageF = fopen(argv[i], "r");
        if (manPageF == NULL) perror ("Erro abrindo arquivo");

        printf("%d - Abriu %s\n", i, argv[i]);

        /* Gera o nome do comando a partir do nome do arquivo, tirando
         * tirando a extensão .txt, e coloca em "comando" */
        char comando[comandoTamMax];
        *strrchr(argv[i], '.') = '\0';
        strcpy(comando, argv[i]);

        //Lê o conteudo do arquivo e coloca em "conteudo"
        char conteudo[conteudoTamMax];
        for(int a=0; a<conteudoTamMax; a++) {
            conteudo[a] = ' ';
        }
        int aa;
        for(aa=0; !feof(manPageF); aa++) {
            conteudo[aa] = fgetc(manPageF);
        }
        conteudo[aa-1] = '\0';
        //Fecha o arquivo atual
        fclose(manPageF);

        bool charFinal = false;
        //Escreve comando em manpages.dat
        for(int a=0; a<comandoTamMax; a++) {
            if(charFinal)
                fputc(' ', manPagesDat);
            else {
                if(comando[a] == '\0') {
                    charFinal = true;
                    fputc('\0', manPagesDat);
                }else
                    fputc(comando[a], manPagesDat);
            }
        }

        //Escreve conteúdo em manpages.dat
        for(int a=0; a<conteudoTamMax; a++) {
            fputc(conteudo[a], manPagesDat);
        }

        //---------Montagem da árvore de palavras-----------//
        char *word = strtok(conteudo, " \n.,|`´^~<>:;_-+=()[]\"'/*!@#");
        while(word != 0) {
            Word atual(word, i-1);
            palavras.insert(atual);
            word = strtok(0," \n.,|`´^~<>:;_-+=()[]\"'/*!@#");
        }

        /* Adiciona o arquivo e seu indice na árvore de indice principal
         * "i=1" corresponde a posição que foi savo o registro do comando
         * em manpages.dat */
        Index manPage;
        strcpy(manPage.comando, comando);
        manPage.posicao = i-1;
        indices.insert(manPage);
    }
    //Fecha manPagesDat
    fclose(manPagesDat);
    printf("Finalizado a geração de manpages.dat\n");

    ///////////////////////////////////
    ///// TERMINOU A MANPAGES.DAT
    ///////////////////////////////////
    ///// COMEÇA A INDICES.DAT
    ///////////////////////////////////

    /* A árvore "indices" deve conter todos os indices ordenados em forma
     * de árvore para serem salvos em disco, ela é retornada em ordem
     * de nível para ser escrita nessa ordem */
    int maxSize = indices.getMaxSizeByHeight();
    Index* indicesOrdenados;
    indicesOrdenados = indices.getByLevel();
    printf("Organizado por nível\n");

    //Cria o arquivo indices.dat para escrita
    File* indicesDat;
    indicesDat = fopen("..\\indices.dat", "wb");

    printf("Comçendo a gerar indices.dat ...\n", );

    //Percorre cada indice do array
    for(int i=0; i<maxSize; i++) {
        //coloca os valores que serão passados para o arquirvo em comando
        char comando[100];
        for(int c=0; c<comandoTamMax; c++) {
            comando[c] = indicesOrdenados[i].comando[c];
        }
        printf("%d - %s\n",(i+1), comando);
        int posicao = indicesOrdenados[i].posicao;
        //troca os 4 ultimos bytes de comando, guardando a posição
        *((int)&comando[96]) = posicao;

        //---------------POSSIVEL PROBLEMA COM O I-------------
        for(int i=0; i<comandoTamMax; i++) {
            fputc(comando[i], indicesDat);
        }
    }
    delete indicesOrdenados;
    fclose(indicesDat);
    printf("Finalizado a geração de indices.dat\n");

    ///////////////////////////////////
    ///// TERMINOU A INDICES.DAT
    ///////////////////////////////////
    ///// COMEÇOU O PALAVRAS.DAT
    ///////////////////////////////////

    FILE* palavrasDat;
    palavrasDat = fopen("..\\palavras.dat", "wb");
    printf("Começando a gerar palavras.dat\n");
    printf("%d|%d\n",palavras.getSize(),palavras.getMaxSizeByHeight());

    //Exclui conectivos da árvore para agilizar processo de busca
    for(int i=0; i<qtdConectivos; i++) {
        char conectivo[100];
        strcpy(conectivo, conectivos[i]);
        palavras.remove(Word(conectivo, 0));
    }

    //Gera array de palavras para inserção
    Word* palavrasOrdenadas = palavras.getByLevel();
    printf("Gerou palavras ordenadas\n");

    //Escreve quantidade de palavras
    maxSize = palavras.getMaxSizeByHeight();
    char maxSizeW[4];
    *((int*)&maxSizeW[0]) = maxSize;
    for(int i=0; i<4; i++) {
        fputc(maxSizeW[i], palavrasDat);
    }

    /* Escreve palavras seguidas do inicio de local das posicoes, e a
     * quantidade de posiçoes */
    int posicao = 0;
    for(i=0; i<maxSize; i++) {
        Word atual = palavrasOrdenadas[i];
        printf("%d - %s\n",i, atual.word);
        *((int*)&atual.word[92]) = posicao;
        int qtd = atual.posicoes.size();
        *((int*)&atual.word[96]) = qtd;
        for(int i=0; i<100; i++) {
            fputc(atual.word[i], palavrasDat);
        }
    }
    //Escreve as posições das manpages que contem as palavras
    char pos[4];
    for(int i=0; i<maxSize; i++) {
        Word atual = palavrasOrdenadas[i];
        while(!atual.posicoes.empty()) {
            *((int*)&pos[0]) = atual.posicoes.front();
            atual.posicoes.pop_front();
            for(int i=0; i<4; i++) {
                fputc(pos[i], palavrasDat);
            }
        }
    }

    fclose(palavrasDat);

    printf("Finalizado a geração de palavras.dat\n");

    ///////////////////////////////////
    ///// TERMINOU A PALAVRAS.DAT
    ///////////////////////////////////

}
