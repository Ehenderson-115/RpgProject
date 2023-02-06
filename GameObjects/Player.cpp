#include "Player.h"

void Player::SetCurrRoomId(int inRoomId)
{
	currRoomId = inRoomId;
}

int Player::GetCurrRoom()
{
	return currRoomId;
}
