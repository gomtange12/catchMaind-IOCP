#pragma once

template < typename T >
class Singleton
{
private:
	static T * Instance;

	Singleton(Singleton const&) {};
	Singleton& operator=(Singleton const&) {};
protected:
	Singleton() { };
	virtual ~Singleton() {  };
public:
	static T * getInstance()
	{
		if (!Instance)
			Instance = new T;
		return Instance;
	};
	static void releaseInstance()
	{
		if (Instance) {
			delete Instance;
			Instance = NULL;
		}
	};

};
template <typename T> T* Singleton<T>::Instance = NULL;

