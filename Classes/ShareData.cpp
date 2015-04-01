#include "ShareData.h"

ShareData* ShareData::shareData = nullptr;

ShareData* ShareData::getInstance()
{
	if(shareData == NULL)
	{
		shareData = new ShareData();
	}
	return shareData;
}
