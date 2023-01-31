#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity 
{
public:	
	std::string GetDescript();
	std::string GetName();
	int GetId();

	void SetDescript();
	void SetName();
	void SetId();
	
protected:
	int mId;
	std::string mName;
	std::string mDescript;
	
};

#endif