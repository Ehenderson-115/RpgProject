set (SOURCE_FILES 
			Character.cpp  
			Entity.cpp
			Enemy.cpp
			Item.cpp 
			Player.cpp
			Weapon.cpp
			Room.cpp
			Game.cpp)

set (HEADER_FILES 
			Character.h  
			Entity.h
			Enemy.h
			Item.h 
			Player.h
			Weapon.h
			Room.h
			Game.h)

add_library(GameObjects ${SOURCE_FILES} ${HEADER_FILES})

configure_file(config.txt config.txt)

target_include_directories(GameObjects INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

