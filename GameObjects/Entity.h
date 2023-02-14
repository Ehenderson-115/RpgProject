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
	Entity(ClassType classType, bool holdable, bool item);
	
	//Getters
	bool isHoldable() const;
	bool isItem() const;
	std::string Descript() const;
	std::string Name() const;
	int Id() const;
	ClassType classType() const;

	//Setters
	void Descript(const std::string& input);
	void Name(const std::string& input);
	void Id(const int& input);

	
protected:
	int mId;
	bool mHoldable;
	bool mItem;
	std::string mName;
	std::string mDescript;
	ClassType mClassType;

};

#endif