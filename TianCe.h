#include "Character.h"

class CTianCe :public CCharacter
{
	int horse_status = 1;//δ���0�����1
public:
	CTianCe(CString name, CString pro, int char_id_, int pro_id_, int camp_);
	void setStatus(int);
	int getStatus();
};