#include "Character.h"

class CCangJian :public CCharacter
{
	int max_jianqi = MAX_JIANQI;
	int cur_jianqi = 0;
	int sword_status = 0;//0问水诀，1山居剑意
	int shield = 0;//泉凝月的盾
public:
	CCangJian(CString name, CString pro, int char_id_, int pro_id_, int camp_);
	void setJianQi(int);//设置剑气
	void addJianQi(int);//增加剑气
	void subJianQi(int);//减少剑气
	int getJianQi();//获取剑气
	void setStatus(int);//设置状态
	int getStatus();//获取状态
	void setShield(int);//设置泉凝月的盾
	void subShield(int);//减少泉凝月的盾
	int getShield();//获取泉凝月的盾
};