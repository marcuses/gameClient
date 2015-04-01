#include "ShareData.h"

ShareData* ShareData::shareData = nullptr;

ShareData* ShareData::getInstance()
{
	if(shareData == NULL)
	{
		shareData = new ShareData();
		shareData->heroID  = "123";
		shareData->heroPSW = "456";
		shareData->isTraveler = true;
		shareData->heroScore = 0;
		shareData->rankScore = 0;
	} 
	return shareData;
}
