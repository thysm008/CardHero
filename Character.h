#include "stdafx.h"
#pragma once

class CCharacter :public CObject
{
protected:
	CString char_name;//角色名称
	CString pro_name;//角色职业名称
	int counter_damage = 0;//打出的伤害变化
	int suffer_damage = 0;//受到的伤害变化
	int char_id;//角色id
	int pro_id;//职业id
	int camp;//阵营
	int hit_point = 0;//角色基础血量
	float act_point = 0;//角色基础行动力
	int act_right = 0;//角色行动权限
public:
	void setCharName(CString);//设置角色名称
	CString getCharName();//获取角色名称
	void setProName(int);//设置职业名称
	CString getProName();//获取职业名称
	void setCharId(int);//设置角色ID
	int getCharId();//获取角色ID
	void setCamp(int);//设置角色阵营
	int getCamp();//获取角色阵营
	void setHp(int);//设置角色血量
	void addHp(int);//增加角色血量
	void subHp(int);//减少角色血量
	int getHp();//获取角色血量
	void setAct(float);//角色行动点数变化
	void addAct(float);//增加行动点
	void subAct(float);//减少行动点
	float getAct();//获取角色行动点数
	void setActRight(int);//设置角色行动权限
	int getActRight();//获取角色行动权限
	void setCounterDamage(int);//设置角色的伤害增加量
	void addCounterDamage(int);//增加角色的伤害增加量
	void subCounterDamage(int);//减少角色的伤害增加量
	int getCounterDamage();//获取角色的伤害增加量
	void setSufferDamage(int);//设置角色所受的伤害增加量
	void addSufferDamage(int);//增加角色所受的伤害增加量
	void subSuferDamage(int);//减少角色所受的伤害增加量
	int getSufferDamage();//获取角色所受的伤害增加量
};