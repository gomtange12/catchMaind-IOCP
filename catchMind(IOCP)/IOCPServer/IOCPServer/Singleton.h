#pragma once
#include <atomic>
#include <mutex>

template < typename T >
class Singleton
{
private:
	static std::atomic<T*> Instance;
	static std::mutex mtx;

	Singleton(Singleton const&) {};
	Singleton& operator=(Singleton const&) {};
protected:
	Singleton() { };
	virtual ~Singleton() {  };
public:
	static T* getInstance()
	{
		if (Instance == nullptr) {
			std::lock_guard<std::mutex> lock(mtx);
			if (Instance == nullptr) {
				Instance = new T();
			}
		}
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
template <typename T> std::atomic<T*> Singleton<T>::Instance{ nullptr };
template <typename T> std::mutex Singleton<T>::mtx;

