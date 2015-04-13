#include "Elemento.hpp"

template<typename T>
class PilhaEnc{
   public:
      PilhaEnc() {
          size = 0;
          head = NULL;
      }

      ~PilhaEnc() {
          delete head;
      }
      void empilha(const T& dado) {
          Elemento<T> *novo;
          novo = new Elemento<T>(dado, head);
          if (novo == NULL) {
              throw 20;
          }
          head = novo;
          size++;
      }
      T desempilha() {
          Elemento<T> *saiu;
          T retorno;
          if (PilhaVazia()) {
              throw 20;
          }
          saiu = head;
          retorno = saiu->getInfo();
          head = saiu->getProximo();
          size--;
          delete saiu;

          return retorno;
      }
	  T topo() {
          return head->getInfo();
      }
	  void limparPilha() {
        size = 0;
        head = NULL;
      }
	  bool PilhaVazia() {
          return size == 0;
      }

  private:
      Elemento<T>* head;
      int size;
};
