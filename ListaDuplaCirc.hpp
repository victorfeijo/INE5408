/* Copyright[2015] José Victor Feijó de Araujo
 * author José Victor Feijó de Araujo
 * version 1.0
 */

#include "Elemento2.hpp"

template<typename T>
class ListaDuplaCirc {
 public:
	ListaDuplaCirc() {
        head = NULL;
        tail = NULL;
        size = 0;
    }
	~ListaDuplaCirc() {
        destroiListaDuplo();
    }
	void adicionaNoInicioDuplo(const T& dado) {
        Elemento2<T> *novo;
        novo = new Elemento2<T>(dado, head, tail);
        if (novo == NULL) {
            throw 20;
        }
        if (listaVazia()) {
            tail = novo;
        }
        head = novo;
        if (novo->getProximo() != NULL) {
            novo->getProximo()->setAnterior(novo);
        }
        size++;
    }
	T retiraDoInicioDuplo() {
        Elemento2<T> *saiu;
        T retorno;
        if (listaVazia()) {
            throw 20;
        }
        saiu = head;
        retorno = saiu->getInfo();
        head = saiu->getProximo();
        if (head != NULL) {
            head->setAnterior(NULL);
        }
        size--;
        delete saiu;
        return retorno;
    }
	void eliminaDoInicioDuplo() {
        Elemento2<T> *saiu;
        if (listaVazia()) {
            throw 20;
        }
        saiu = head;
        head = saiu->getProximo();
        if (head != NULL) {
            head->setAnterior(NULL);
        }
        size--;
        delete saiu;
    }
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
        //verificar size ou size+1
        Elemento2<T> *novo, *anterior;
        if (pos > size || pos < 0) {
            throw 20;
        }
        if (pos == 0) {
            adicionaNoInicioDuplo(dado);
            return;
        }
        novo = new Elemento2<T>(dado, NULL, NULL);
        if (novo == NULL) {
            throw 20;
        }
        anterior = head;
        for (int i = 0; i < pos-1; i++) {
            anterior = anterior->getProximo();
        }
        novo->setProximo(anterior->getProximo());
        if (novo->getProximo() != NULL) {
            novo->getProximo()->setAnterior(novo);
        }
        anterior->setProximo(novo);
        novo->setAnterior(anterior);
        size++;
    }
	int posicaoDuplo(const T& dado) const {
        Elemento2<T> *auxiliar;
        if (listaVazia()) {
            throw 20;
        }
        auxiliar = head;
        for (int i = 0; i < size; i++) {
            if (auxiliar->getInfo() == dado) {
                return i;
            }
            auxiliar = auxiliar->getProximo();
        }
        throw 20;
    }
	T* posicaoMemDuplo(const T& dado) const {
        Elemento2<T> *auxiliar;
        if (listaVazia()) {
            throw 20;
        }
        auxiliar = head;
        for (int i = 0; i < size; i++) {
            if (auxiliar->getInfo() == dado) {
                return &auxiliar->getInfo();
            }
            auxiliar = auxiliar->getProximo();
        }
        throw 20;
    }
	bool contemDuplo(const T& dado) {
        Elemento2<T> *auxiliar;
        if (listaVazia()) {
            throw 20;
        }
        auxiliar = head;
        for (int i = 0; i < size; i++) {
            if (auxiliar->getInfo() == dado) {
                return true;;
            }
            auxiliar = auxiliar->getProximo();
        }
        return false;
    }
	T retiraDaPosicaoDuplo(int pos) {
        //verificar size >=
        Elemento2<T> *anterior, *eliminar;
        T retorno;
        if (pos >= size || pos < 0) {
            throw 20;
        }
        if (pos == 0) {
            return retiraDoInicioDuplo();
        }
        anterior = head;
        for (int i = 0; i < pos - 1; i++) {
            anterior = anterior->getProximo();
        }
        eliminar = anterior->getProximo();
        retorno = eliminar->getInfo();
        anterior->setProximo(eliminar->getProximo());
        if (eliminar->getProximo() != NULL) {
            eliminar->getProximo()->setAnterior(anterior);
        }
        size--;
        delete eliminar;

        return retorno;
    }
	void adicionaDuplo(const T& dado) {
        adicionaNaPosicaoDuplo(dado, size);
    }
	T retiraDuplo() {
        if(listaVazia()) {
            throw 20;
        }
        return retiraDaPosicaoDuplo(size-1);
    }
	T retiraEspecificoDuplo(const T& dado) {
        //caso erro refazer este método
        return retiraDaPosicaoDuplo(posicaoDuplo(dado));
    }
	T mostra(int pos) {
        Elemento2<T> *auxiliar;
        if (listaVazia()) {
            throw 20;
        }
        head = auxiliar;
        for (int i = 0; i < pos; i++) {
            auxiliar = auxiliar->getProximo();
        }
        return auxiliar->getInfo();
    }
	void adicionaEmOrdem(const T& data) {
        Elemento2<T> *atual;
        int pos;
        if (listaVazia()) {
            return adicionaNoInicioDuplo(data);
        }
        atual = head;
        pos = 0;
        while (atual->getProximo() != NULL && maior(data, atual->getInfo())) {
            atual = atual->getProximo();
            pos++;
        }
        if (maior(data, atual->getInfo())) {
            adicionaNaPosicaoDuplo(data, pos+1);
        }
        else {
            adicionaNaPosicaoDuplo(data, pos);
        }
    }
	int verUltimo() {
        return size;
    }
	bool listaVazia() const {
        return size == 0;
    }
	bool igual(T dado1, T dado2) {
        return dado1 == dado2;
    }
	bool maior(T dado1, T dado2) {
        return dado1 > dado2;
    }
	bool menor(T dado1, T dado2) {
        return dado1 < dado2;
    }
	void destroiListaDuplo() {
        Elemento2<T> *atual;
        if (listaVazia()) {
            delete head;
            return;
        }
        atual = head;
        while(atual != NULL) {
            atual = atual->getProximo();
            eliminaDoInicioDuplo();
        }
    }

private:
    Elemento2<T> *head;
    Elemento2<T> *tail;
    int size;
};
