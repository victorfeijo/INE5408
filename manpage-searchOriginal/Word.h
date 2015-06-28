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
 * Word.h
 */

#ifndef WORD_H
#define WORD_H

#include <deque>
using std::deque;

/**
 * Struct utilizada para conter as palavras que estão contidas no arquivo
 */
struct Word {
    char word[100];
    deque<int> posicoes;

    Word() {
        word[0] = '\0';
        for (int i=1; i<100; i++) {
            word[i] = ' ';
        }
    }

    Word(char* w, int a) {
        for (int i=1; i<100; i++) {
            word[i] = ' ';
        }
        strcpy(word, w);
        posicoes.push_back(a);
    }

    bool operator==(const Word& rhs) const {
        if (strcmp(word, rhs.word) == 0) return true;
        return false;
    }

    bool operator<(const Word& rhs) const {
        if (strcmp(word, rhs.word) < 0) return true;
        return false;
    }

    bool operator>(const Word& rhs) const {
        if (strcmp(word, rhs.word) > 0) return true;
        return false;
    }
};

#endif /* WORD_H */
