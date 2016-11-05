#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include "unit.h"
template <class Product, class ID, class Creator>
class Factory { //заточена на unit * --- должна быть шаблонной, обощаться на методы
	public:
		typedef Product * (*creator_t)();

		
		Factory(const Factory&) = delete;
		Factory& operator=(const Factory&) = delete;

		static Factory* getInstance()
		{
			//mayer's singleton -- не подменим для тестов, неудобно (т.к. фабрика глобальная)
			static Factory f;
			return &f;
		}
		Product * create(const ID& id)
		{
			//??????? обработка ошибки - работа с отсутствующим id
			return creatorz.at(id)();
		}
		bool regist3r(const ID& id, const creator_t& creator)
		{
			creatorz[id] = creator;
			return true;
		}
	private:
		Factory() {}
		std::unordered_map<
			ID,
			creator_t> creatorz;
};


// для лабы :
// Андрей Александреску - "Современное проектирование на с++" (~229)

#endif