#include "stdafx.h"
#include "Character.h"

void CCharacter::setCharName(CString name)
{
	char_name = name;
}

CString CCharacter::getCharName()
{
	return char_name;
}

void CCharacter::setProName(int id)
{
	switch (id){
		case 1: pro_name = _T("Ìì²ß"); break;
		case 2: pro_name = _T("²Ø½£"); break;
		default:
			break;
	}
}

CString CCharacter::getProName()
{
	return pro_name;
}

void CCharacter::setCharId(int id)
{
	char_id = id;
}

int CCharacter::getCharId()
{
	return char_id;
}

void CCharacter::setCamp(int cp)
{
	camp = cp;
}

int CCharacter::getCamp()
{
	return camp;
}

void CCharacter::setHp(int s_hp)
{
	hit_point = s_hp;
}

void CCharacter::addHp(int a_hp)
{
	hit_point += a_hp;
}

void CCharacter::subHp(int s_hp)
{
	hit_point -= s_hp;
}

int CCharacter::getHp()
{
	if (hit_point > 30)
		return 30;
	else if (hit_point < 0)
		return 0;
	else
		return hit_point;
}

void CCharacter::setAct(float c_act)
{
	act_point = c_act;
}

void CCharacter::addAct(float c_act)
{
	act_point = act_point + c_act;
}

void CCharacter::subAct(float c_act)
{
	act_point = act_point - c_act;
}

float CCharacter::getAct()
{
	if (act_point >= 0)
		return act_point;
	else
		return 0;
}

void CCharacter::setActRight(int i)
{
	act_right = i;
}

int CCharacter::getActRight()
{
	return act_right;
}

void CCharacter::setCounterDamage(int d)
{
	counter_damage = d;
}

void CCharacter::addCounterDamage(int d)
{
	counter_damage += d;
}

void CCharacter::subCounterDamage(int d)
{
	counter_damage -= d;
}

int CCharacter::getCounterDamage()
{
	return counter_damage;
}

void CCharacter::setSufferDamage(int d)
{
	suffer_damage = d;
}

void CCharacter::addSufferDamage(int d)
{
	suffer_damage += d;
}

void CCharacter::subSuferDamage(int d)
{
	suffer_damage -= d;
}

int CCharacter::getSufferDamage()
{
	return suffer_damage;
}