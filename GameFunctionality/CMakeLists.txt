set (SOURCE_FILES 
			Game.cpp
			NetworkFunctions.cpp
			CommandParser.cpp)

set (HEADER_FILES 
			Game.h
			NetworkFunctions.h
			CommandParser.h)
			

add_library(GameFunctionality ${SOURCE_FILES} ${HEADER_FILES})
target_compile_definitions(GameFunctionality PUBLIC ASIO_STANDALONE)
target_include_directories(GameFunctionality PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../ThirdPartyLibraries/asio-1.24.0/include)
target_link_libraries(GameFunctionality GameCommands GameObjects)

