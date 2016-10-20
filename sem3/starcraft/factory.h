#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include "unit.h"

class Factory { //заточена на unit * --- должна быть шаблонной, обощаться на методы
	public:
		typedef Unit * (*creator_t)();

		
		Factory(const Factory&) = delete;
		Factory& operator=(const Factory&) = delete;

		static Factory* getInstance()
		{
			//mayer's singleton -- не подменим для тестов, неудобно (т.к. фабрика глобальная)
			static Factory f;
			return &f;
		}
		Unit * create(const std::string& id)
		{
			return creatorz.at(id)();
		}
		bool regist3r(const std::string& id, const creator_t& creator)
		{
			creatorz[id] = creator;
			return true;
		}
	private:
		Factory() {}
		std::unordered_map<
			std::string,
			creator_t> creatorz;
};


// для лабы :
// Андрей Александреску - "Современное проектирование на с++"

#endif