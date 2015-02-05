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

const static char strGoLeft[] = "goLeft";
const static char strGoRight[] = "goRight";
const static char strJump[] = "Jump";
const static char strStop[] = "Stop";