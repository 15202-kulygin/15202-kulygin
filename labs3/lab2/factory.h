#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include <memory>
#include <iostream>
#include "strategy.h"

class Factory { 
	public:
		typedef Strategy * (*creator_t)();

		
		Factory(const Factory&) = delete;
		Factory& operator=(const Factory&) = delete;

		static Factory *  getInstance()
		{
			//mayer's singleton -- не подменим для тестов, неудобно (т.к. фабрика глобальная)
			static Factory f;
			
			return &f;
		}
		Strategy * create(const std::string& id)
		{
			auto iter = creatorz.find(id);
        	if(creatorz.end() == iter)
        	{
            	return nullptr;
        	}
			return creatorz.at(id)();
		}
		bool regist3r(const std::string& id, const creator_t& creator)
		{
			creatorz[id] = creator;
			return true;
		}
		
		~Factory() {}
		Factory() {}
	private:
		
		std::unordered_map<
			std::string,
			creator_t> creatorz;
		

};

#endif

// для лабы :
// Андрей Александреску - "Современное проектирование на с++"
