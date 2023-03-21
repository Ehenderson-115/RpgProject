set (SOURCE_FILES 
			NetworkFunctions.cpp)

set (HEADER_FILES 
			NetworkFunctions.h)
			


add_library(NetworkLib NetworkFunctions.cpp NetworkFunctions.h)
target_compile_definitions(NetworkLib PUBLIC ASIO_STANDALONE)
target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../ThirdPartyLibraries/asio-1.24.0/include ../GameObjects ../GameFunctionality)
target_link_libraries(NetworkLib GameFunctionality GameObjects)
#set_target_properties(NetworkLib PROPERTIES PUBLIC_HEADER NetworkFunctions.h)


