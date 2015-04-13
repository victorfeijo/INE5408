//Copyright [2015] <José Victor Feijó de Araujo>
/*
*  \author José Victor Feijó de Araujo
*  \sice 25/03/2015
*  \version 1.0
*/

template<typename T>
class Lista
{
 private:
     int tamanho;
     int ultimo;
     T *dados;

 public:
  //comentário
  Lista(){}
  //
  explicit Lista<T>(int tam):
    tamanho(tam),
    ultimo(-1)
  {
    dados = new T[tamanho];
  }
  //comentário
  ~Lista()
  {
      delete dados;
  }
  //comentário
  void adiciona(T dado)
  {
      if(listaCheia())
        throw 20;
      ultimo++;
      dados[ultimo] = dado;
  }
  //comentário
  void adicionaNoInicio(T dado)
  {
      if(listaCheia())
        throw 20;
      ultimo++;
      int pos = ultimo;
      while (pos > 0)
      {
          dados[pos] = dados[pos - 1];
          pos--;
      }
      dados[0] = dado;
  }
  //comentário
  void adicionaNaPosicao(T dado, int posicao)
  {
      if(listaCheia())
        throw 20;
      if(posicao > ultimo+1 || posicao < 0)
        throw 20;
      ultimo++;
      int pos = ultimo;
      while (pos > posicao)
      {
          dados[pos] = dados[pos - 1];
          pos--;
      }
      dados[posicao] = dado;
  }
  //comentário
  void adicionaEmOrdem(T dado)
  {
      if(listaCheia())
        throw 20;
      int pos = 0;
      while(pos <= ultimo && (dado > dados[pos]))
      {
        pos++;
        adicionaNaPosicao(dado, pos);
      }
  }
  //comentário
  T retira()
  {
      if(listaVazia())
        throw 20;
      return retiraDaPosicao(ultimo);
  }
  //comentário
  T retiraDoInicio()
  {
      if(listaVazia())
        throw 20;
      return retiraDaPosicao(0);
  }
  //comentário
  T retiraDaPosicao(int posicao)
  {
      if(posicao > ultimo || posicao < 0)
        throw 20;
      ultimo--;
      int auxiliar = dados[posicao];
      while (posicao <= ultimo)
      {
          dados[posicao] = dados[posicao + 1];
          posicao++;
      }
      return auxiliar;
  }
  //comentário
  T retiraEspecifico(T dado)
  {
      if(listaVazia())
        throw 20;
      int pos = posicao(dado);
      if (pos < 0)
        throw 20;
      return retiraDaPosicao(pos);
  }
  //comentário
  int posicao(T dado)
  {
      int pos = 0;
      while (pos <= ultimo && !(igual(dado, dados[pos])))
      {
        pos++;
      }
      if (pos > ultimo)
        throw 20;
      return pos;
  }
  //comentário
  bool contem(T dado)
  {
      int pos = 0;
      while (pos <= ultimo && !(igual(dado, dados[pos])))
      {
        pos++;
      }
      if (pos > ultimo)
        return false;

      return true;
  }
  //comentário
  bool igual(T dado1, T dado2)
  {
      return dado1 == dado2;
  }
  //comentário
  bool maior(T dado1, T dado2)
  {
      return dado1 > dado2;
  }
  //comentário
  bool menor(T dado1, T dado2)
  {
      return dado1 < dado2;
  }
  //comentário
  bool listaCheia()
  {
      return ultimo == tamanho -1;
  }
  //comentário
  bool listaVazia()
  {
      return ultimo == -1;
  }
  //comentário
  void destroiLista()
  {
      ultimo = -1;
  }
};
