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

static const int palavraTamMax = 100;
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
        printf("\n");
        printf("Digite o número para opção\n");
        printf("(1) - Gerar arquivos .dat\n");
        printf("(2) - Buscar conteudo pelo nome da manpage\n");
        printf("(3) - Buscar manpages por uma palavra\n");
        printf("(4) - Buscar manpages por duas palavras\n");
        printf("(0) - Para sair\n");
        scanf("%d",&entrada);
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

    for(int i=1; i<argc; i++) {
        //Abre e le cada arquivo de manpage
        FILE *manPageF;
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
    FILE* indicesDat;
    indicesDat = fopen("..\\indices.dat", "wb");

    printf("Comçendo a gerar indices.dat ...\n");

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
        *((int*)&comando[96]) = posicao;

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
    for(int i=0; i<maxSize; i++) {
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

/**
 * Pede o nome do comando/manpage a ser procurado
 * Percorre o arquivo "indices.dat" que está organizado como uma árvore
 * níveis procurando pelo texto informado.
 *
 * O percorrimento por níveis é feito do seguinte modo:
 *  Estando em uma posição "x" e
 *      verificando que aquilo que é procurado é menor que atual, vá para
 *      o nodo da esquerda, no caso a posição "2(x+1)-1"
 *
 *      verificando que aquilo que é procurado é maior que atual, vá para
 *      o nodo da direita, no caso posição "2(x+1)"
 */
 void buscaConteudoPorComando() {
     //Array onde será salvo o comando a ser pesquisado
     char comandoBusca[100];
     for(int i=0; i<comandoTamMax; i++) {
         comandoBusca[i] = ' ';
     }
     //Recebe o comando
     scanf("%s",comandoBusca);
     //Abre arquivo indices.dat
     FILE* indicesDat = fopen("..\\indices.dat", "rb");

     //calcula a quantidade de itens na arvore e armazena em "tamanho"
     fseek(indicesDat, 0, SEEK_END);
     int tamanho = ftell(indicesDat);
     fseek(indicesDat, 0, SEEK_SET);
     tamanho /= comandoTamMax;

     //Percorrimento da árvore em arquivo, buscando pelo item pedido
     int pos = 0;
     bool achou = false;
     char comandoAtual[100];
     while(!achou && pos<tamanho) {
         //Posiciona o leitor no começo do registro
         fseek(indicesDat, pos*comandoTamMax, SEEK_SET);
         char comandoAtual[100];
         //le o registro do arquivo
         fgets(comandoAtual, 100, indicesDat);
         int cmpResult = strcmp(comandoBusca, comandoAtual);
         //Buscando maior que encontrado, pega o ramo da direita
         if(cmpResult < 0) {
             pos++;
             pos = (2*pos)-1;
         //Buscando menor que encontrado, pega o ramo da esquerda
         }else if(cmpResult > 0) {
             pos++;
             pos = (2*pos);
         //Encontrou
         }else {
             achou = true;
         }
     }
     //fecha indices.dat, mas deixa salvo o conteúdo pedido em "comandoAtual"
     fclose(indicesDat);

     if(achou) {
         //Retira a posição dos ultimos 4 butes de comando
         int posicao;
         posicao = *((int*)&comandoAtual[96]);

         //Abre a manpages.dat para pegar o conteúdo pedido

         FILE* manPagesDat;
         manPagesDat = fopen("..\\manpages.dat", "rb");
         //Posiciona o leitor no começo do registro
         posicao *= comandoTamMax+conteudoTamMax;
         fseek(manPagesDat, posicao, SEEK_SET);
         //Posiciona o leitor no começo do conteudo do registro
         fseek(manPagesDat,comandoTamMax, SEEK_CUR);

         char lido = ' ';
         while(lido != '\0') {
             printf("%c",lido=fgetc(manPagesDat));
         }

         fclose(manPagesDat);
     }else {
         printf("\nManPage não encontrada\n");
     }
 }

 /**
  * Pede uma palavra e pega a posicaoDasManPagesCom(palavra) a lista de
  * de índices que possuem a palavra pesquisada.
  * Traduz os índices para o nome das manpages acessando "manpages.dat" e
  * pegando o nome dos registros de índice respectivos.
  */
void buscaPorUmaPalavra(){
    //Pede a palavra a ser pesquisada
    char palavra[100];
    scanf("%s",palavra);
    //Pega a lista de índices que possuem a palavra
    deque<int> indices = posicaoDasManPagesCom(palavra);
    FILE* manPagesDat;
    manPagesDat = fopen("..\\manpages.dat", "rb");

    printf("\n\n");
    //Pega o nome dos registros a partir dos índices
    while (!indices.empty()) {
        fseek(manPagesDat, indices.front()*(comandoTamMax+conteudoTamMax), SEEK_SET);
        char comando[100];
        fgets(comando, 100, manPagesDat);
        printf("%d - %s\n",indices.front(), comando);
        indices.pop_front();
    }
    fclose(manPagesDat);
}
/**
 * Pede as duas palavras, e obtem os indices de modo semelhante a
 * buscaPorUmaPalavra, realiza as intersecção entre as listas de índices
 * Traduz os índices para o nome das manpages consultando "manpages.dat"
 */
void buscaPorDuasPalavras() {
    //Pede a primeira palavra
    char palavra1[100];
    scanf("%s", palavra1);
    //Pega a lista de índices que possuem a primeira palavra
    deque<int> indices1 = posicaoDasManPagesCom(palavra1);
    //Pede a segunda palavra
    char palavra2[100];
    scanf("%s", palavra2);
    //Pega índices da segunda palavra
    deque<int> indices2 = posicaoDasManPagesCom(palavra2);

    //Intersecção de indices1 e indices2
    deque<int> indices;
    while (!indices2.empty()) {
        int atual = indices2.front();
        bool achou = false;
        for(int i=0; i<indices1.size() && !achou; i++) {
            if(indices1.at(i) == atual) achou = true;
        }
        if(achou) indices.push_back(atual);
        indices2.pop_front();
    }

    FILE* manPagesDat;
    manPagesDat = fopen("..\\manpages.dat", "rb");
    printf("\n\n");

    while (!indices.empty()) {
        fseek(manPagesDat, indices.front()*(comandoTamMax+conteudoTamMax), SEEK_SET);
        char comando[100];
        fgets(comando, 100, manPagesDat);
        printf("%d - %s\n", indices.front(), comando);
        indices.pop_front();
    }

    fclose(manPagesDat);
}

/**
 * Recebe a palavra a ser procurada
 * Consulta o "palavras.dat", que é uma árvore por níveis, procurando pela
 * palavra pedida
 * Retorna a lista de índices que possuem a palavra pedida
 */
deque<int> posicaoDasManPagesCom(char* palavra) {
    FILE* palavrasDat;
    palavrasDat = fopen("..\\palavras.dat", "rb");

    //Lê a quantidade de palavras dos 4 bytes e guarda em "tamanho"
    char tamanhoC[4];
    for(int i=0; i<4; i++) {
        tamanhoC[i] = fgetc(palavrasDat);
    }

    int tamanho = *((int*)&tamanhoC[0]);
    int pos = 0;
    bool achou = false;
    char palavraAtual[100];
    while (!achou && pos<tamanho) {
        //Posiciona o leitor no inicio do registro da palavra
        fseek(palavrasDat, 4+(pos*palavraTamMax), SEEK_SET);
        //Pega palavra do registro
        fgets(palavraAtual, 100, palavrasDat);

        int cmpResult = strcmp(palavra, palavraAtual);
        //Buscando maior que encontrado, pega o ramo da esquerda
        if(cmpResult < 0) {
            pos++;
            pos = (2*pos)-1;
        //Buscando menor que encontrado, pega o ramo da direita
        }else if(cmpResult > 0) {
            pos++;
            pos = (2*pos);
        //Encontrado
        }else {
            achou = true;
        }
    }

    deque<int> indices;
    if(achou) {
        pos = *((int*)&palavraAtual[92]);
        int qtd = *((int*)&palavraAtual[96]);
        fseek(palavrasDat, 4+(tamanho*palavraTamMax)+pos*4, SEEK_SET);
        for(int i=0; i<qtd; i++) {
            char indiceC[4];
            for(int a=0;a<4;++a){
                indiceC[a] = fgetc(palavrasDat);
            }
            int indice = *((int*)&indiceC[0]);
            indices.push_back(indice);
        }
    }else {
        printf("Nenhum arquivo encontrado com a palavra '&s'\n", palavra);
    }

    fclose(palavrasDat);

    return indices;
}
