#pragma once

template <class T>
class Singleton
{
public:
	static T* Instance()
	{
		static T instance;
		return &instance;
	}

protected:
	Singleton() {}
	virtual ~Singleton() {}

private:
	Singleton(const Singleton& other);
	Singleton& operator=(const Singleton& other);
};
