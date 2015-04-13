#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

template<typename T>
class Elemento {
private:
	T *info;
	Elemento<T>* _next;

public:
	Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {}

	~Elemento()
	{
		delete info;
	}

	Elemento<T>* getProximo() const
	{
		return _next;
	}

	T getInfo() const
	{
		return *info;
	}

	void setProximo(Elemento<T>* next)
	{
		_next = next;
	}
};

#endif
