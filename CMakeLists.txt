cmake_minimum_required(VERSION 3.10)

project(RpgGame VERSION 1.0)

set(SERVER_EXE RpgGameServer)
set(CLIENT_EXE RpgGameClient)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header File for cmake defines
configure_file(RpgGameConfig.h.in RpgGameConfig.h)

add_subdirectory(GameObjects)

list(APPEND GAME_OBJECTS GameObjects)

add_subdirectory(GameCommands)

list(APPEND GAME_COMMANDS GameCommands)

add_subdirectory(GameFunctionality)

list(APPEND GAME_FUNCTIONALITY GameFunctionality)

add_library(Server Server.h Server.cpp)
add_library(Client CLient.h Client.cpp)

add_executable(${SERVER_EXE} RpgGameServer.cpp)
add_executable(${CLIENT_EXE} RpgGameClient.cpp)

target_link_libraries(${SERVER_EXE} PUBLIC ${GAME_FUNCTIONALITY} Server)
target_link_libraries(${CLIENT_EXE} PUBLIC ${GAME_OBJECTS} Client)

install(FILES config.txt DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets)
install(FILES config.txt DESTINATION ${CMAKE_DEBUG_LOC}/Assets)

target_include_directories(${SERVER_EXE} PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(${CLIENT_EXE} PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS ${SERVER_EXE} ${CLIENT_EXE} DESTINATION ${CMAKE_INSTALL_PREFIX})