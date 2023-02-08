#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity 
{
public:	
	Entity();
	std::string GetDescript();
	std::string GetName();
	std::string GetClassType();
	bool isHoldable();
	int GetId();

	void SetDescript(std::string input);
	void SetName(std::string input);
	void SetId(int input);

	
protected:
	int mId;
	bool mHoldable;
	std::string mName;
	std::string mDescript;
	std::string mClassType;

};

#endif