template <typename T>
class Fila {
private:
    int fim;
    T* m_DADOS;
    int max_fila;
public:
 	Fila<T>(int tam):
        max_fila(tam)
    {
        inicializaFila();
    }
    ~Fila()
    {
        delete m_DADOS;
    }
 	void inclui(T dado)
     {
         if(filaCheia())
            throw 20;
        else
            fim = fim + 1;
            m_DADOS[fim] = dado;
     }
 	T retira()
    {
         if (filaVazia())
            throw 20;
        else
            fim = fim - 1;
            T retorno = m_DADOS[0];
            for (int i = 0; i < fim; i++){
                m_DADOS[i] = m_DADOS[i+1];
            }
            return retorno;
     }
 	T ultimo()
    {
        if (filaVazia())
            throw 20;
        else
            return m_DADOS[fim];
     }
 	int getUltimo()
    {
         if (filaVazia())
            throw 20;
        else
            return fim;
     }
 	bool filaCheia() {
         return (fim == max_fila - 1);
     }
 	bool filaVazia() {
         return (fim == -1);
     }
 	void inicializaFila() {
         m_DADOS = new T[max_fila];
         fim = -1;
     }
     void LimpaFila() {
         fim = -1;
     }
};
