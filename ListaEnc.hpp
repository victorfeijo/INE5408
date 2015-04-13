/* Copyright[2015] José Victor Feijó de Araujo
 * author José Victor Feijó de Araujo
 * version 1.0
 */

#include "Elemento.hpp"

template<typename T>
class ListaEnc {

public:
    // Construtor inicializa as variáveis size = 0, head = NULL
	ListaEnc() : size(0), head(NULL) {}
	// Destrutor chama o método destroiLista();
	~ListaEnc()
	{
		destroiLista();
	}
	//Adiciona um dado no início da lista, modificando o head
	void adicionaNoInicio(const T& dado)
	{
		Elemento<T> *novo;
		novo = new Elemento<T>(dado, head);
		if (novo == NULL)
		{
			throw 20;
		}
			head = novo;
			size++;
	}
	T retiraDoInicio()
	{
		Elemento<T> *saiu;
		T retorno;
		if (listaVazia())
		{
			throw 20;
		}
		saiu = head;
		retorno = saiu->getInfo();
		head = saiu->getProximo();
		size--;
		delete saiu;

		return retorno;
	}
	void eliminaDoInicio()
	{
		Elemento<T> *saiu;
		if (listaVazia())
		{
			throw 20;
		}
		saiu = head;
		head = saiu->getProximo();
		size--;
		delete saiu;
	}
	// posicao
	void adicionaNaPosicao(const T& dado, int pos)
	{
		Elemento<T> *novo;
		Elemento<T> *anterior;
		if (pos > size )
		{
			throw 20;
		}
		if (pos == 0)
		{
			adicionaNoInicio(dado);
			return;
		}
		novo = new Elemento<T>(dado, NULL);
		if (novo == NULL)
		{
			throw 20;
		}
		anterior = head;
		for (int i = 0; i < pos - 1; i++)
		{
			anterior = anterior->getProximo();
		}
		novo->setProximo(anterior->getProximo());
		anterior->setProximo(novo);
		size++;
	}
	// Retorna a posição do dado na lista
	int posicao(const T& dado) const
	{
		Elemento<T> *auxiliar;
		if (listaVazia())
		{
			throw 20;
		}
		auxiliar = head;
		for (int i = 0; i < size; i++)
		{
			if (auxiliar->getInfo() == dado)
			{
				return i;
			}
			auxiliar = auxiliar->getProximo();
		}
		throw 20;
	}
	// Retorna a posição de memória do dado
	T* posicaoMem(const T& dado) const
	{
		Elemento<T> *auxiliar;
		auxiliar = head;
     	for (int i = 0; i < size; i++)
		{
        	if (auxiliar->getInfo() == dado)
			{
				return &auxiliar->getInfo();
			}
       auxiliar = auxiliar->getProximo();
     	}
     throw 20;
	}
	bool contem(const T& dado)
	{
		Elemento<T> *auxiliar;
		if (listaVazia())
		{
			throw 20;
		}
		auxiliar = head;
		for (int i = 0; i < size; i++)
		{
			if (auxiliar->getInfo() == dado)
			{
				return true;
			}
			auxiliar = auxiliar->getProximo();
		}
		return false;
	}
	T retiraDaPosicao(int pos)
	{
		T retorno;
		Elemento<T> *anterior;
		Elemento<T> *eliminar;
		if (pos >= size)
		{
			throw 20;
		}
		if (pos == 0)
		{
			return retiraDoInicio();
		}
		anterior = head;
		for (int i = 0; i < pos - 1; i++)
		{
			anterior = anterior->getProximo();
		}
		eliminar = anterior->getProximo();
		retorno = eliminar->getInfo();
		anterior->setProximo(eliminar->getProximo());
		size--;
		delete eliminar;

		return retorno;
	}
	// Adiciona no fim
	void adiciona(const T& dado)
	{
		adicionaNaPosicao(dado, size);
	}
	// Retira o dado do fim da lista
	T retira()
	{
		if (listaVazia())
		{
			throw 20;
		}
		return retiraDaPosicao(size - 1);
	}
	T retiraEspecifico(const T& dado)
	{
		Elemento<T> *atual;
		Elemento<T> *anterior;
		atual = head;
		anterior = head;
		for (int i =0; i < size - 1; i++)
		{
			if (atual->getInfo() == dado)
			{
				T volta = atual->getInfo();
				anterior->setProximo(atual->getProximo());
				delete atual;
				return volta;
			}
			anterior = atual;
			atual = atual->getProximo();
		}
		throw 20;
	}
	void adicionaEmOrdem(const T& data)
	{
		Elemento<T> *atual;
		int pos;
		if (listaVazia())
		{
			return adicionaNoInicio(data);
		}
		atual = head;
		pos = 0;
		while (atual->getProximo() != NULL && maior(data, atual->getInfo()))
		{
			atual = atual->getProximo();
			pos++;
		}
		if (maior(data, atual->getInfo()))
		{
			adicionaNaPosicao(data, pos + 1);
		}
		else
		{
			adicionaNaPosicao(data, pos);
		}
	}
	bool listaVazia() const
	{
		return size == 0;
	}
	bool igual(T dado1, T dado2)
	{
		return dado1 == dado2;
	}
	bool maior(T dado1, T dado2)
	{
		return dado1 > dado2;
	}
	bool menor(T dado1, T dado2)
	{
		return dado1 < dado2;
	}
	void destroiLista()
	{
		Elemento<T> *atual;
		if (listaVazia())
		{
			delete head;
			return;
		}
		atual = head;
		while (atual != NULL)
		{
			atual = atual->getProximo();
			eliminaDoInicio();
		}
	}
// head = primeiro elemento da lista
// size = tamanho da lista
private:
	Elemento<T>* head;
	int size;
};
