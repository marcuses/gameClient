#pragma  once
#include <vector>
const float BULLETRate = 0.3;

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
	BULLETENEMY = 1 << 9,
	PLANK = 1 << 10,
	TAI = 1 << 11,
	BUFF = 1 << 12
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
const static char showHeroLife[] = "ShowHeroLife";
const static char strQuickMove[] = "quickMove";
const static char showScore[]= "ShowScore";

static std::string heroID;
static std::string heroPSW;
static bool isTraveler;
static int   heroScore;
static float rankScore;

struct Monster_data
{
	Monster_data(float x = 0, float y = 0, float marmScale = 1)
	{

		offset_x = x;
		offset_y = y;
		armScale = marmScale;
	}
	float offset_x;
	float offset_y;
	float armScale;
};
const static Monster_data monster_data[10] = {
	Monster_data(0, 0, 1),
	Monster_data(0, 1, 0.7),
	Monster_data(0, 0, 1),
	Monster_data(0, 0, 1),
	Monster_data(0, 0, 1)
};
