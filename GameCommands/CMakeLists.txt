set (SOURCE_FILES 
			CommandParser.cpp  
			GameCommand.cpp
			MainMove.cpp
			MainLook.cpp 
			MainSearch.cpp
			MainStartCombat.cpp
			MainOpen.cpp
			MainClose.cpp
			MainGrabItem.cpp
			MenuListItems.cpp
			MenuInspect.cpp
			MenuEquip.cpp
			MenuClose.cpp
			CombatAttackPlayer.cpp
			CombatAttackAdversary.cpp
			CombatDefendPlayer.cpp
			CombatDefendAdversary.cpp)

set (HEADER_FILES 
			CommandParser.h  
			GameCommand.h
			MainMove.h
			MainLook.h 
			MainSearch.h
			MainStartCombat.h
			MainOpen.h
			MainClose.h
			MainGrabItem.h
			MenuListItems.h
			MenuInspect.h
			MenuEquip.h
			MenuClose.h
			CombatAttackPlayer.h
			CombatAttackAdversary.h
			CombatDefendPlayer.h
			CombatDefendAdversary.h)
			

add_library(GameCommands ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(GameCommands PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GameCommands GameObjects)
