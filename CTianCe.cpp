#include "stdafx.h"
#include "TianCe.h"
#include "Character.h"

CTianCe::CTianCe(CString name, CString pro, int char_id_, int pro_id_, int camp_)
{
	char_name = name;
	pro_name = pro;
	char_id = char_id_;
	pro_id = pro_id_;
	camp = camp_;
}

void CTianCe::setStatus(int i)
{
	horse_status = i;
}

int CTianCe::getStatus()
{
	return horse_status;
}