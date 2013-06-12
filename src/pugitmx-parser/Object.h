#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <map>
#include "../lib/stringh.h"
#include "square.h"

namespace pugitmx
{
	class Object
	{
		public:
			Object(std::string nme, std::string typ, int x, int y, int wd, int ht) : name(nme), type(typ), _object(x, y, wd, ht) {};
			std::string getName() const;
			std::string getType() const;
			int getObjectX() const;
			int getObjectY() const;
			int getObjectWidth() const;
			int getObjectHeight() const;
			void registerProperty(std::string, std::string);
			std::string getProperty(std::string) const;
		private:
			std::string name;
			std::string type;
			Square _object;
			std::map<std::string, std::string> properties;
	};
};

#endif // __OBJECT_H_
