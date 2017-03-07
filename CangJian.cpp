#include "stdafx.h"
#include "CangJian.h"
#include "Character.h"

CCangJian::CCangJian(CString name, CString pro, int char_id_, int pro_id_, int camp_)
{
	char_name = name;
	pro_name = pro;
	char_id = char_id_;
	pro_id = pro_id_;
	camp = camp_;
}

void CCangJian::setJianQi(int n)
{
	cur_jianqi = n;
}

void CCangJian::addJianQi(int n)
{
	cur_jianqi = cur_jianqi + n;
	if (cur_jianqi > MAX_JIANQI)
		cur_jianqi = 7;
}

void CCangJian::subJianQi(int n)
{
	cur_jianqi = cur_jianqi - n;
	if (cur_jianqi < 0)
		cur_jianqi = 0;
}

int CCangJian::getJianQi()
{
	if (cur_jianqi < 0)
		return 0;
	else if (cur_jianqi > MAX_JIANQI)
		return MAX_JIANQI;
	else
		return cur_jianqi;
}


void CCangJian::setStatus(int i)
{
		sword_status = i;
}

int CCangJian::getStatus()
{
	return sword_status;
}

void CCangJian::setShield(int i)
{
	shield = i;
}

void CCangJian::subShield(int i)
{
	shield -= i;

	if (shield < 0)
		shield = 0;
}

int CCangJian::getShield()
{
	return shield;
}