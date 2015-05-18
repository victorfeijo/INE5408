// Copyright [2015] <José Victor Feijó de Araujo [14100842]>
#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <cstdlib>
#include <vector>

template <typename T>
class NoBinario {
 protected:
     T* dado;
     NoBinario<T>* esquerda;
     NoBinario<T>* direita;
     std::vector<NoBinario<T>*> elementos;  //!< Elementos acessados durante
                                            // o percurso realizado
 public:
     NoBinario<T>(const T& info) {
         esquerda = NULL;
         direita = NULL;
         dado = new T(info);
         elementos.clear();
     }

     virtual ~NoBinario() {};

     T* getDado() {
         return dado;
     }
     std::vector< NoBinario<T>* > getElementos() {
         return elementos;
     }
     NoBinario<T>* getEsquerda() {
         return esquerda;
     }
     NoBinario<T>* getDireita() {
         return direita;
     }
     T* busca(const T& dado, NoBinario<T>* arv) {
         while(arv != NULL) {
             if (*arv->getDado() != dado) {
                 if (*arv->getDado() < dado)
                    arv = arv->getDireita();
                 else
                    arv = arv->getEsquerda();
              } else {
                  return arv->getDado();
              }
         }
         throw 20;
     }
     NoBinario<T>* inserir(const T& dado, NoBinario<T>* arv) {
         if (dado < *arv->getDado()) {
             if (arv->getEsquerda() == NULL) {
                 arv->esquerda = new NoBinario<T>(dado);
                 return arv->getEsquerda();
             } else {
                 inserir(dado, arv->getEsquerda());
             }
         } else {
             if (arv->getDireita() == NULL) {
                 arv->direita = new NoBinario(dado);
                 return arv->getDireita();
             } else {
                 inserir(dado, arv->getDireita());
             }
         }
         return NULL;
     }
     NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
         NoBinario<T> *tmp, *filho;
         if (arv == NULL) {
             return arv;
         } else {
             if (dado < *arv->getDado()) {
                 //Como atributo é protected eu posso chama-lo direto
                 arv->esquerda = remover(arv->getEsquerda(), dado);
                 return arv;
             } else {
                 if (dado > *arv->getDado()) {
                     //Como atributo é protected eu posso chama-lo direto
                     arv->direita = remover(arv->getDireita(), dado);
                     return arv;
                 } else {
                     if (arv->getDireita() != NULL && arv->getEsquerda() != NULL) {
                         tmp = minimo(arv->getDireita());
                         arv->dado = tmp->getDado();
                         arv->direita = remover(arv->getDireita(), *arv->getDado());
                         return arv;
                     } else {
                         tmp = arv;
                         if (arv->getDireita() != NULL) {
                             filho = arv->getDireita();
                             return filho;
                         } else {
                             if (arv->getEsquerda() != NULL) {
                                 filho = arv->getEsquerda();
                                 return filho;
                             } else {
                                 delete arv;
                                 return NULL;
                             }
                         }
                     }
                 }
             }
         }
     }
     NoBinario<T>* minimo(NoBinario<T>* nodo) {
         while (nodo->getEsquerda() != NULL) {
             nodo = nodo->getEsquerda();
         }
         return nodo;
     }
     void preOrdem(NoBinario<T>* nodo) {
         if (nodo != NULL) {
             elementos.push_back(nodo);
             preOrdem(nodo->getEsquerda());
             preOrdem(nodo->getDireita());
         }
     }
     void emOrdem(NoBinario<T>* nodo) {
         if (nodo != NULL) {
             emOrdem(nodo->getEsquerda());
             elementos.push_back(nodo);
             emOrdem(nodo->getDireita());
         }
     }
     void posOrdem(NoBinario<T>* nodo) {
         if (nodo != NULL) {
             posOrdem(nodo->getEsquerda());
             posOrdem(nodo->getDireita());
             elementos.push_back(nodo);
         }
     }
};

#endif /* NO_BINARIO_HPP */
