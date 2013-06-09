#ifndef __API_H_
#define __API_H_

class System
{
	public:
		System();
		virtual ~System();
		virtual double version() const = 0;
		virtual void renderMap() = 0;
};

#endif // __API_H_
