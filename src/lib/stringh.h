#ifndef __STRINGH_H_
#define __STRINGH_H_

#include <string>
#include <sstream>
#include <falcon/string.h>
#ifdef DEBUG
	#include <iostream>
#endif

template<class N>
class String
{
	public:
		static std::string toString(N a)
		{
			std::stringstream n;
			n << a;
			return n.str();
		}

		static N toElse(std::string a)
		{
			std::stringstream n;
			n << a;
			N x;
			n >> x;
			return x;
		}
};

class FString
{
	public:
		static std::string fromCoreString(Falcon::CoreString cstr)
		{
			std::string xan;
			for(int x = 0; x < cstr.size(); x++)
			{
				xan += cstr[x];
			}
			return xan;
		}

		static Falcon::CoreString fromString(std::string str)
		{
			Falcon::CoreString xan;
			for(int x = 0; x < str.size(); x++)
			{
				xan.append(int(str[x]));
			}
			return xan;
		}

		static Falcon::CoreString fromString(Falcon::String str)
		{
			Falcon::CoreString xan;
			for(int x = 0; x < str.size(); x++)
			{
				xan.append(int(str[x]));
			}
			return xan;
		}

		static std::string fromStringS(Falcon::String str)
		{
			std::string xan;
			for(int x = 0; x < str.size(); x++)
			{
				xan += str[x];
			}
			return xan;
		}
};

#endif // __STRINGH_H_
