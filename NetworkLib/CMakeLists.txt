set (SOURCE_FILES 
		NetworkHandler.cpp)

set (HEADER_FILES 
		NetworkHandler.h)
			


add_library(NetworkLib NetworkHandler.cpp NetworkHandler.h)
target_compile_definitions(NetworkLib PUBLIC ASIO_STANDALONE)
if(UNIX)
add_compile_options(-lpthread)
endif()
target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../ThirdPartyLibraries/asio-1.24.0/include ../GameObjects ../GameFunctionality)
target_link_libraries(NetworkLib GameFunctionality GameObjects)
#set_target_properties(NetworkLib PROPERTIES PUBLIC_HEADER NetworkFunctions.h)


