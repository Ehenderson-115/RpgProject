#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity 
{
public:	
	std::string GetDescript();
	virtual std::string GetRace();
	int GetId();

	void SetDescript(std::string input);
	void SetName(std::string input);
	void SetId(int input);
	
protected:
	int mId;
	std::string mName;
	std::string mDescript;

};

#endif