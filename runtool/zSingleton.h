#ifndef _SINGLETON_H
#define _SINGLETON_H

//#include "syncobj.h"

template <typename T>
class SingletonFactory{
	public:
		static T* instance(){
			return new T();
		}
};

template <typename T, typename MANA = SingletonFactory<T> > 
class Singleton{
	private:
		Singleton(const Singleton&);
		const Singleton & operator= (const Singleton &);		
	protected:
		Singleton( void ){
		}
		~Singleton( void ){
		}
	protected:
		//static CIntLock m_singletonlock;
		static T* ms_Singleton;
	public:
	
		static __inline void delMe(void){
			//可以在子类的destoryMe中被调用
			if (ms_Singleton){
				//AILOCKT(m_singletonlock);
				if (ms_Singleton){
					delete ms_Singleton;
					ms_Singleton = 0;
				}
			}
		}

		static __inline T* instance( void ){
			if (!ms_Singleton){
				//AILOCKT(m_singletonlock);
				if (!ms_Singleton){
					ms_Singleton = MANA::instance();
				}
			}
			return ms_Singleton;
		}

		static __inline T* instance_readonly( void ){
			return ms_Singleton;
		}

		static __inline T& getMe(void){
			return *instance();
		}
};

template <typename T, typename MANA>
T* Singleton<T,MANA>::ms_Singleton = 0;

//template <typename T, typename MANA>
//CIntLock Singleton<T,MANA>::m_singletonlock;

#endif

