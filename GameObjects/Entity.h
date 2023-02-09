#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity 
{
public:	
	enum class ClassType { Entity, Player, Room, Character, Enemy, Item, Weapon };
	
	Entity();
	Entity(ClassType classType);
	Entity(bool holdable);
	Entity(ClassType classType, bool holdable);
	
	//Getters
	bool isHoldable() const;
	std::string Descript() const;
	std::string Name() const;
	int Id() const;

	//Setters
	void Descript(std::string input);
	void Name(std::string input);
	void Id(int input);

	
protected:
	int mId;
	bool mHoldable;
	std::string mName;
	std::string mDescript;
	ClassType mClassType;

};

#endif