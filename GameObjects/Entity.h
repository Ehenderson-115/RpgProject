#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity 
{
public:	
	enum class ClassType { Entity, Player, Room, Character, Enemy, Item, Weapon };
	
	Entity();
	Entity(ClassType classType);
	Entity(ClassType classType, std::string inName);
	Entity(bool holdable);
	Entity(ClassType classType, bool holdable);
	Entity(ClassType classType, bool holdable, bool item);
	
	//Getters
	bool isHoldable() const { return mHoldable; }
	bool isItem() const { return mItem; }
	std::string Descript() const { return mDescript; }
	std::string Name() const { return mName; }
	int Id() const { return mId; }
	ClassType Type() const { return mClassType; }

	//Setters
	void Descript(const std::string& inStr) { mDescript = StripQuotes(inStr); }
	void Name(const std::string& inStr) { mName = inStr; }
	void Id(int inId) { mId = inId; }

protected:
	int mId;
	bool mHoldable;
	bool mItem;
	std::string mName;
	std::string mDescript;
	ClassType mClassType;
	std::string StripQuotes(std::string inStr);
};

#endif