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
 * AvlTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <cmath>
using std::pow;

#include <string>
using std::string;

#include "Word.h"

template <typename T>
class AvlTree {
public:

    struct Node {
        Node *left, *right;
        T data;

        int getHeight() const {
            if (this == 0) return -1;
            return height;
        }

        Node() : left(0), right(0), data(), height(0){}

        Node(const T& t) : left(0), right(0), data(t), height(0){}

        void updateHeight() {
            height = max(left->getHeight, right->getHeight()) + 1;
        }
        //Biggest node of the subtree
        Node* rightMost() {
            if (right == 0) return this;
            return right->rightMost();
        }

        Node* rotateLeft() {
            Node* root = right;
            right = right->left;
            root->left = this;
            updateHeight();
            root->updateHeight();
            return root;
        }

        Node* rotateRight() {
            Node* root = left;
            left = left->right;
            root->right = this;
            updateHeight();
            root->updateHeight();
            return root;
        }

        Node* doubleRotateLeft() {
            right = right->rotateRight();
            return rotateLeft();
        }

        Node* doubleRotateRight() {
            left = left->rotateLeft();
            return rotateRight();
        }

        string toString() {
            if (this == 0) return "@";
            return "(" + left->toString() + ")" + data + "(" + right->toString() + ")";
        }
    private:
        int height;
        int max(int a, int b) {
            if (a > b) return a;
            return b;
        }
    };
public:
    AvlTree(): root(0){}

    void insert(const T& t) {
        root = insert(t, root);
    }

    void remove(const T& t) {
        root = remove(t, root);
    }

    string toString() {
        return root->toString();
    }

    int getSize() const {
        return size;
    }

    int getHeight() const {
        return root->getHeight();
    }

    int getMaxSizeByHeight() const {
        int h = root->getHeight();
        h = h + 1;
        return getMaxSizeByHeight(h);
    }

    /**
     * Retorna um array dos objetos da árvore organizados por níveis
     * @return
     */
     T* getByLevel() {
         //Make a array of the nodes
         int maxSize = getMaxSizeByHeight();
         Node* *arrayN = new Node*[maxSize];
         arrayN[0] = root;
         aaa = 0;
         int maxSizeFor = getMaxSizeByHeight(root->getHeight());
         for (int i=0; i < maxSizeFor; i++) {
             if (arrayN[i] != 0) {
                 aaa = (2 * (i + 1)) - 1;
                 arrayN[aaa] = arrayN[i]->left;
                 aaa++;
                 arrayN[aaa] = arrayN[i]->right;
             } else {
                 aaa = (2 * (i + 1)) - 1;
                 arrayN[aaa] = 0;
                 aaa++;
                 arrayN[aaa] = 0;
             }
         }
         T* arrayT = new T[maxSize];
         for (int i=0; i<maxSize; i++) {
             if (arrayN[i] == 0) arrayT[i] = *(new T());
             else arrayT[i] = arrayN[i]->data;
         }

         delete [] arrayN;

         return arrayT;
     }
private:
    Node* root;
    int size;
    int aaa;

    int getMaxSizeByHeight(int h) const {
        return (pow(2,h) - 1);
    }

    Node* insert(const T& t, Node* root) {
        if (root == 0) {
            ++size;
            return new Node(t);
        }
        if (t < root->data) {//left
            root->left = insert(t, root->left);
            if (root->left->getHeight() - root->right->getHeight() > 1)
                if (t < root->left->data)//"/"
                    root = root->rotateRight();
                else//"<"
                    root = root->doubleRotateRight();
        } else if (t > root->data) {//right
            root->right = insert(t, root->right);
            if (root->right->getHeight() - root->left->getHeight() > 1)
                if (t > root->right->data) //"\"
                    root = root->rotateLeft();
                else //">"
                    root = root->doubleRotateLeft();
        }
        root->updateHeight();
        return root;
    }

    Node* remove(const T& t, Node* root) {
        if (root == 0)//data not on the tree
            return root;

        if (t < root->data) //left
            root->left = remove(t, root->left);
        else if (t > root->data) //right
            root->right = remove(t, root->right);
        else {//delete root
            --size;
            if (root->left == 0 && root->right == 0) {//no child
                delete root;
                return 0;
            } else if (root->left == 0 || root->right == 0) {//one child
                Node* aux = (root->left ? root->left : root->right);
                delete root;
                root = aux;
            } else {//two children
                Node* aux = root->left->rightMost();
                root->data = aux->data;
                root->left = remove(aux->data, root->left);
                root->updateHeight();
            }
        }
        if (root->left->getHeight() - root->right->getHeight() > 1)
            if (t > root->left->data)//"/"
                root = root->rotateRight();
            else//"<"
                root = root->doubleRotateRight();
        else if (root->right->getHeight() - root->left->getHeight() > 1)
            if (t < root->right->data) //"\"
                root = root->rotateLeft();
            else //">"
                root = root->doubleRotateLeft();
        root->updateHeight();
        return root;
    }
};

/**
 * Especialização da inserção para a struct Palavra
 * Ao inserir uma Palavra que já está na árvore, em vez de
 * não fazer nada, adiciona as posições da palavra inserida aquela que
 * já está na árvore
 */
template<>
AvlTree<Word>::Node* AvlTree<Word>::insert(const Word& t, Node* root) {
    if (root == 0) {
        ++size;
        return new Node(t);
    }
    if (t < root->data) {//left
        root->left = insert(t, root->left);
        if (root->left->getHeight() - root->right->getHeight() > 1)
            if (t < root->left->data)//"/"
                root = root->rotateRight();
            else//"<"
                root = root->doubleRotateRight();
    } else if (t > root->data) {//right
        root->right = insert(t, root->right);
        if (root->right->getHeight() - root->left->getHeight() > 1)
            if (t > root->right->data) //"\"
                root = root->rotateLeft();
            else //">"
                root = root->doubleRotateLeft();
    } else {//==
        int posicao = t.posicoes.front();
        if(root->data.posicoes.back() != posicao)
            root->data.posicoes.push_back(posicao);
    }
    root->updateHeight();
    return root;
}

#endif /* AVLTREE_H */
