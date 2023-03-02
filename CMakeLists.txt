cmake_minimum_required(VERSION 3.10)

project(RpgGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header File for cmake defines
configure_file(RpgGameConfig.h.in RpgGameConfig.h)

add_subdirectory(GameObjects)

list(APPEND GAME_OBJECTS GameObjects)

add_subdirectory(GameCommands)

list(APPEND GAME_COMMANDS GameCommands)

add_subdirectory(ThirdPartyLibraries)

list(APPEND THIRD_PARTY_LIBS ThirdPartyLibraries)

add_executable(${PROJECT_NAME} rpgGame.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_OBJECTS} ${GAME_COMMANDS} ${THIRD_PARTY_LIBS})

install(FILES config.txt DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets)
install(TARGETS ThirdPartyLibraries DESTINATION ${CMAKE_INSTALL_PREFIX}/SharedLibraries)

install(FILES config.txt DESTINATION ${CMAKE_DEBUG_LOC}/Assets)
install(TARGETS ThirdPartyLibraries DESTINATION ${CMAKE_DEBUG_LOC}/SharedLibraries)

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
