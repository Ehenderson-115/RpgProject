set (SOURCE_FILES 
			CommandParser.cpp  
			GameCommand.cpp
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
			ClientData.cpp
			World.cpp
			RoomConnection.cpp
			PlayerLocation.cpp
			OutputManager.cpp
			Client.cpp
			Server.cpp)

set (HEADER_FILES 
			CommandParser.h  
			GameCommand.h
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
			ClientData.h
			World.h
			RoomConnection.h
			PlayerLocation.h
			OutputManager.h
			Client.h
			Server.h)


add_library(GameObjects  ${SOURCE_FILES} ${HEADER_FILES})
target_compile_definitions(GameObjects PUBLIC ASIO_STANDALONE)
target_include_directories(GameObjects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../ThirdPartyLibraries/asio-1.24.0/include)


