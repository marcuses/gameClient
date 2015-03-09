#pragma  once

const static enum TYPE
{
	NOTHING = 0x00,
	MONSTER = 0x01,
	HERO = 1 << 1,
	BRICK = 1 << 2,
	GROUND = 1 << 3,
	TANGH = 1 << 4,
	BULLET = 1 << 5,
	TRAP = 1 << 6,
	BOSS = 1 << 7,
	BOSSWEAKNESS = 1 << 8,
	BULLETENEMY = 1 << 9
};

const static char strLeftButtonDown[] = "leftButtonDown";
const static char strRightButtonDown[] = "rightButtonDown";
const static char strJumpButtonDown[] = "jumpButtonDown";

const static char strLeftButtonUp[] = "leftButtonUp";
const static char strRightButtonUp[] = "rightButtonUp";
const static char strJumpButtonUp[] = "jumpButtonUp";

const static char strHeroShoot[] = "heroShoot";
const static char strEnemyShoot[] = "enemyShoot";
const static char strWin[] = "win";