#include "Character.h"

class CCangJian :public CCharacter
{
	int max_jianqi = MAX_JIANQI;
	int cur_jianqi = 0;
	int sword_status = 0;//0��ˮ����1ɽ�ӽ���
	int shield = 0;//Ȫ���µĶ�
public:
	CCangJian(CString name, CString pro, int char_id_, int pro_id_, int camp_);
	void setJianQi(int);//���ý���
	void addJianQi(int);//���ӽ���
	void subJianQi(int);//���ٽ���
	int getJianQi();//��ȡ����
	void setStatus(int);//����״̬
	int getStatus();//��ȡ״̬
	void setShield(int);//����Ȫ���µĶ�
	void subShield(int);//����Ȫ���µĶ�
	int getShield();//��ȡȪ���µĶ�
};