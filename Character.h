#include "stdafx.h"
#pragma once

class CCharacter :public CObject
{
protected:
	CString char_name;//��ɫ����
	CString pro_name;//��ɫְҵ����
	int counter_damage = 0;//������˺��仯
	int suffer_damage = 0;//�ܵ����˺��仯
	int char_id;//��ɫid
	int pro_id;//ְҵid
	int camp;//��Ӫ
	int hit_point = 0;//��ɫ����Ѫ��
	float act_point = 0;//��ɫ�����ж���
	int act_right = 0;//��ɫ�ж�Ȩ��
public:
	void setCharName(CString);//���ý�ɫ����
	CString getCharName();//��ȡ��ɫ����
	void setProName(int);//����ְҵ����
	CString getProName();//��ȡְҵ����
	void setCharId(int);//���ý�ɫID
	int getCharId();//��ȡ��ɫID
	void setCamp(int);//���ý�ɫ��Ӫ
	int getCamp();//��ȡ��ɫ��Ӫ
	void setHp(int);//���ý�ɫѪ��
	void addHp(int);//���ӽ�ɫѪ��
	void subHp(int);//���ٽ�ɫѪ��
	int getHp();//��ȡ��ɫѪ��
	void setAct(float);//��ɫ�ж������仯
	void addAct(float);//�����ж���
	void subAct(float);//�����ж���
	float getAct();//��ȡ��ɫ�ж�����
	void setActRight(int);//���ý�ɫ�ж�Ȩ��
	int getActRight();//��ȡ��ɫ�ж�Ȩ��
	void setCounterDamage(int);//���ý�ɫ���˺�������
	void addCounterDamage(int);//���ӽ�ɫ���˺�������
	void subCounterDamage(int);//���ٽ�ɫ���˺�������
	int getCounterDamage();//��ȡ��ɫ���˺�������
	void setSufferDamage(int);//���ý�ɫ���ܵ��˺�������
	void addSufferDamage(int);//���ӽ�ɫ���ܵ��˺�������
	void subSuferDamage(int);//���ٽ�ɫ���ܵ��˺�������
	int getSufferDamage();//��ȡ��ɫ���ܵ��˺�������
};