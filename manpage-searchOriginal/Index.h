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
 * Index.h
 */

#ifndef INDEX_H
#define INDEX_H

/**
 * Struct utilizada para organizar os índices na árvore
 * para que possam ser retirados por níveis
 */
struct Index {
    char comando[100];
    int posicao;
    //Define os operadores para poder usar na Avl
    Index() {
        comando[0] = '\0';
        for(int i=1; i<100; i++) {
            comando[i] = ' ';
        }
        posicao = 0;
    }

    bool operator==(const Index& rhs) const {
        if (strcmp(comando, rhs.comando) == 0) return true;
        return false;
    }

    bool operator<(const Index& rhs) const {
        if (strcmp(comando, rhs.comando) < 0) return true;
        return false;
    }

    bool operator>(const Index& rhs) const {
        if (strcmp(comando, rhs.comando) > 0) return true;
        return false;
    }
};

#endif /* INDEX_H */
