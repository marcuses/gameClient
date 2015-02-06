#pragma  once

const static enum TYPE
{
	NOTHING = 0x00,
	MONSTER = 0x01,
	HERO = 0x02,
	BRICK = 0x04,
	GROUND = 0x08,
	TANGH = 0x10
};

const static char strLeftButtonDown[] = "leftButtonDown";
const static char strRightButtonDown[] = "rightButtonDown";
const static char strJumpButtonDown[] = "jumpButtonDown";

const static char strLeftButtonUp[] = "leftButtonUp";
const static char strRightButtonUp[] = "rightButtonUp";
const static char strJumpButtonUp[] = "jumpButtonUp";