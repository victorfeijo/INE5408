#ifndef ELEMENTO2_HPP
#define ELEMENTO2_HPP

template<typename T>
class Elemento2 {
private:
	T *info;
	Elemento2<T>* _next;
	Elemento2<T>* _before;

public:
	Elemento2(const T& info, Elemento2<T>* next, Elemento2<T>* before) : info(new T(info)), _next(next), _before(before) {}

	~Elemento2()
	{
		delete info;
	}

	Elemento2<T>* getProximo() const
	{
		return _next;
	}

	Elemento2<T>* getAnterior() const
	{
		return _before;
	}

	T getInfo() const
	{
		return *info;
	}

	void setProximo(Elemento2<T>* next)
	{
		_next = next;
	}

	void setAnterior(Elemento2<T>* before)
	{
		_before = before;
	}
};

#endif
