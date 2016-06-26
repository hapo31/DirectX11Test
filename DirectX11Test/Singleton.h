#pragma once


template<class T>
class Singleton
{
public:
	static T& get_instance()
	{
		static T object;
		return object;
	}
protected:
	Singleton() = default;
private:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
};