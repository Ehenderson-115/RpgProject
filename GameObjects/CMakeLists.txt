set (SOURCE_FILES 
			Character.cpp  
			Entity.cpp
			Enemy.cpp
			Item.cpp 
			Player.cpp
			Weapon.cpp
			Room.cpp
			Game.cpp
			HelperFunctions.cpp
			Parser.cpp
			ActiveGameData.cpp
			World.cpp
			Connection.cpp
			PlayerLocation.cpp
			OutputManager.cpp)

set (HEADER_FILES 
			Character.h  
			Entity.h
			Enemy.h
			Item.h 
			Player.h
			Weapon.h
			Room.h
			Game.h
			HelperFunctions.h
			Parser.h
			ActiveGameData.h
			World.h
			Connection.h
			PlayerLocation.h
			OutputManager.h)

add_library(GameObjects ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(GameObjects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

