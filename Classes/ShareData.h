#pragma once
#include <string>
class ShareData{
public:
	static ShareData* getInstance();
	std::string heroID;
	std::string heroPSW;
	bool isTraveler;
	int heroScore;
	int rankScore;
private:
	static ShareData* shareData;
};