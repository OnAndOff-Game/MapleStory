#pragma once

template <class T>
class Singleton 
{
protected:
	Singleton() {}
	~Singleton() {}

public:
	static T* GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new T;
		}
		return m_Instance;
	}
	static void DestoryInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

private:
	static T* m_Instance;
};

template <class T> T* Singleton<T>::m_Instance = nullptr;