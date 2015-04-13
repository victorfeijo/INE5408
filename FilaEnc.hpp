/* Copyright[2015] José Victor Feijó de Araujo
 * author José Victor Feijó de Araujo
 * version 1.0
 */

#include "Elemento.hpp"

template <typename T>
class FilaEnc{
 public:
	FilaEnc<T>() {
        size = 0;
        inicio = NULL;
        final = NULL;
    }
	~FilaEnc() {
        delete inicio;
    }
	void inclui(const T& dado) {
        Elemento<T> *novo;
        novo = new Elemento<T>(dado, NULL);
        if (novo == NULL) {
            throw 20;
        }
        if (filaVazia()) {
            inicio = novo;
        }
        else {
            final->setProximo(novo);
        }
        final = novo;
        size ++;
    }
	T retira() {
        Elemento<T> *saiu;
        T *retorno;
        if (filaVazia()) {
            throw 20;
        }
        saiu = inicio;
        retorno = saiu->getInfo();
        inicio = saiu->getProximo();
        if (size == 1) {
            final = NULL;
        }
        size--;
        delete saiu;

        return retorno;

    }
	T ultimo() {
        if (filaVazia()) {
            throw 20;
        }
        return final->getInfo();
    }
	T primeiro() {
        if (filaVazia()) {
            throw 20;
        }
        return inicio->getInfo();
    }
	bool filaVazia() {
        return size == 0;
    }
	void limparFila() {
        size = 0;
        inicio = NULL;
    }
private:
    Elemento<T>* inicio;
    Elemento<T>* final;
    int size;
};
