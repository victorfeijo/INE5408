template<typename T>
class Pilha {
private:
    int max_pilha;
    int o_topo;
    T* m_DADOS;
public:
    Pilha<T>(int t):
        max_pilha(t),
        o_topo(-1)
    {
    m_DADOS = new T[max_pilha];
    }
    ~Pilha(){
            delete m_DADOS;
    }
	void empilha(T dado){
        if(PilhaCheia())
            throw 20;
        else{
            o_topo = o_topo + 1;
            m_DADOS[o_topo] = dado;
        }
    }
 	T desempilha(){
        if (PilhaVazia())
            throw 20;
        else{
            o_topo = o_topo - 1;
            return m_DADOS[o_topo + 1];
        }
     }
 	T topo(){
         if (PilhaVazia())
            throw 20;
        else
            return m_DADOS[o_topo];
     }
 	int getPosTopo(){
        if(o_topo <= -1)
            throw 20;
        else
            return o_topo;
     }
 	void limparPilha(){
         o_topo = -1;
     }
 	bool PilhaVazia(){
         return (o_topo == -1);
     }
    bool PilhaCheia(){
        return (o_topo == max_pilha - 1);
    }
};
