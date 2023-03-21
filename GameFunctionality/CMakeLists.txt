set (SOURCE_FILES 
			Game.cpp
			Server.cpp
			Client.cpp
			CommandParser.cpp)

set (HEADER_FILES 
			Game.h
			Server.h
			Client.h
			CommandParser.h)
			

add_library(GameFunctionality ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(GameFunctionality PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GameFunctionality GameCommands GameObjects NetworkLib)


