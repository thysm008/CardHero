
// CardHeroView.cpp : CCardHeroView ���ʵ��
//

#include "stdafx.h"
#include "stdlib.h"
#include "CangJian.h"
#include "TianCe.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CardHero.h"
#endif

#include "CardHeroDoc.h"
#include "CardHeroView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCardHeroView

IMPLEMENT_DYNCREATE(CCardHeroView, CFormView)

BEGIN_MESSAGE_MAP(CCardHeroView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SINGLE_VS, &CCardHeroView::OnSingleVs)
	ON_LBN_SELCHANGE(IDC_SKILL_LIST, &CCardHeroView::OnLbnSelchangeSkillList)
	ON_LBN_SELCHANGE(IDC_SKILL_LIST2, &CCardHeroView::OnLbnSelchangeSkillList2)
	ON_BN_CLICKED(IDC_ACTION, &CCardHeroView::OnBnClickedAction)
	ON_BN_CLICKED(IDC_ACTION2, &CCardHeroView::OnBnClickedAction2)
	ON_BN_CLICKED(IDC_END, &CCardHeroView::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_END2, &CCardHeroView::OnBnClickedEnd2)
	ON_LBN_SELCHANGE(IDC_BUFF_LIST1, &CCardHeroView::OnLbnSelchangeBuffList1)
END_MESSAGE_MAP()

// CCardHeroView ����/����

CCangJian *player_cangjian = new CCangJian("ҶӢ", "�ؽ�", 1001, 1, 100);//��ʼ�����1
CTianCe *player_tiance = new CTianCe("��ж�", "���", 1002, 2, 101);//��ʼ�����2

CCardHeroView::CCardHeroView()
	: CFormView(CCardHeroView::IDD)
	, m_charid1(_T(""))
	, m_player1_hp(_T(""))
	, m_player1_act(_T(""))
	, m_player1_power(_T(""))
	, m_player2_hp(_T(""))
	, m_charid2(_T(""))
	, m_player2_horse_status(_T(""))
	, m_skill_comment(_T(""))
	, m_player1_skill_cost(_T(""))
	, m_player1_act_cost(_T(""))
	, m_player1_skill_cd(_T(""))
	, m_player1_skill_status(_T(""))
	, m_player2_skill_cd(_T(""))
	, m_player2_status(_T(""))
	, m_player2_act_cost(_T(""))
	, m_skill2_comment(_T(""))
	, m_player1_buff_count(0)
	, m_player2_buff_count(0)
	, fight_dairy_count(0)
	, buff_fengming(0)
	, buff_times(0)
	, m_remain_cd1(_T(""))
	, m_player1_buff_comment(_T(""))
	, m_remain_cd2(_T(""))
	, m_player2_act(_T(""))
{
	// TODO:  �ڴ˴���ӹ������

}

CCardHeroView::~CCardHeroView()
{
}

void CCardHeroView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHAR_ID, m_charid1);
	DDX_Text(pDX, IDC_CHAR_HP, m_player1_hp);
	DDX_Text(pDX, IDC_CHAR_ACT, m_player1_act);
	DDX_Text(pDX, IDC_CHAR_POW, m_player1_power);
	//  DDX_Text(pDX, IDC_CHAR_ACT2, m_player2_act);
	DDX_Text(pDX, IDC_CHAR_HP2, m_player2_hp);
	DDX_Text(pDX, IDC_CHAR_ID2, m_charid2);
	DDX_Text(pDX, IDC_CHAR_STATUS, m_player2_horse_status);
	DDX_Control(pDX, IDC_SKILL_LIST, player1_skillbox);
	DDX_Control(pDX, IDC_SKILL_LIST2, player2_skillbox);
	DDX_Text(pDX, IDC_SKILL_COMMENT, m_skill_comment);
	DDX_Text(pDX, IDC_COST, m_player1_skill_cost);
	DDX_Text(pDX, IDC_ACT_COST, m_player1_act_cost);
	DDX_Text(pDX, IDC_CD, m_player1_skill_cd);
	DDX_Text(pDX, IDC_ACT_COST2, m_player1_skill_status);
	DDX_Text(pDX, IDC_CD2, m_player2_skill_cd);
	DDX_Text(pDX, IDC_ACT_COST4, m_player2_status);
	DDX_Text(pDX, IDC_ACT_COST3, m_player2_act_cost);
	DDX_Text(pDX, IDC_SKILL_COMMENT2, m_skill2_comment);
	DDX_Control(pDX, IDC_FIGHT_DAIRY, fight_dairybox);
	//  DDX_Control(pDX, IDC_BUFF_COMMENT1, m_player1_buff_comment);
	//  DDX_Control(pDX, IDC_BUFF_COMMENT2, m_player2_buff_comment);
	DDX_Control(pDX, IDC_BUFF_LIST1, m_player1_buff_list);
	DDX_Control(pDX, IDC_BUFF_LIST2, m_player2_buff_list);
	DDX_Text(pDX, IDC_EDIT2, m_remain_cd1);
	DDX_Text(pDX, IDC_BUFF_COMMENT1, m_player1_buff_comment);
	DDX_Text(pDX, IDC_EDIT3, m_remain_cd2);
	DDX_Text(pDX, IDC_CHAR_ACT2, m_player2_act);
}

BOOL CCardHeroView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CCardHeroView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CCardHeroView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCardHeroView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCardHeroView ���

#ifdef _DEBUG
void CCardHeroView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCardHeroView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCardHeroDoc* CCardHeroView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCardHeroDoc)));
	return (CCardHeroDoc*)m_pDocument;
}
#endif //_DEBUG


// CCardHeroView ��Ϣ�������


void CCardHeroView::OnSingleVs()
{
	// TODO:  �ڴ���������������
	//�����Ҽ��ܱ�
	toDamage = 0;
	boolDamage = 0;
	round = 0;
	Damage = false;
	player_cangjian->setAct(BASIC_ACT);//���ж�������Ϊ����3��
	player_tiance->setAct(BASIC_ACT);
	player_cangjian->setHp(30);//������һ���Ѫ��
	player_tiance->setHp(30);
	m_player1_buff_count = 0;//��������buff����
	m_player2_buff_count = 0;
	player1_skillbox.ResetContent();//��ռ�����
	player2_skillbox.ResetContent();
	fight_dairybox.ResetContent();//���ս����־
	m_player1_buff_list.ResetContent();//���״̬�б�
	m_player2_buff_list.ResetContent();
	fight_dairy_count = 0;//���ս����־��Ŀ
	player_cangjian->setActRight(0);//����˫���ж�Ȩ��
	player_cangjian->setActRight(0);
	for (int i = 0; i < 12; i++){
		player1_skill_record[i] = 0;
		player2_skill_record[i] = 0;
		player1_cd_record[i] = 0;
		player2_cd_record[i] = 0;
	}
	player2_cd_record[12] = 0;
	player2_skill_record[12] = 0;
	for (int i = 0; i < 20; i++){
		player_bufflist1[i] = 0;
		player_bufflist2[i] = 0;
	}
	player_bufflist2[0] = 1;
	nSel_player1 = -1;
	nSel_player2 = -1;

	UpdateData(FALSE);

	//����������ж��Ⱥ���
	srand(time(NULL));

	int random = rand() % 2;

	if (random){
		MessageBox("�ؽ�����");
		fight_dairybox.InsertString(fight_dairy_count++, "�ؽ�����");
		fight_round = "��������������";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "�غϡ�����������";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);
		player_cangjian->setActRight(1);
	}
	else{
		MessageBox("�������");
		fight_dairybox.InsertString(fight_dairy_count++, "�������");
		fight_round = "��������������";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "�غϡ�����������";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);
		player_tiance->setActRight(1);
	}

/**************�����1���г�ʼ��***************/
	/****������Ϣ��������Ϣ��ʼ��****/
	SetDlgItemText(IDC_CHAR_NAME, player_cangjian->getCharName());//�������
	SetDlgItemText(IDC_CHAR_PRO, player_cangjian->getProName());//��������
	player_cangjian->setJianQi(0);//��������
	player_cangjian->setCounterDamage(0);//�����˺�����
	player_cangjian->setSufferDamage(0);//����buff����
	player_cangjian->setStatus(0);
	c_jianqi = 0;
	switch (player_cangjian->getStatus()){
	case 0:{
			   player_cangjian->setAct(BASIC_ACT + 1);
			   player_bufflist1[0] = 0;
			   refreshBuffList1();
			   break;
	}
	case 1:{
			   player_cangjian->setAct(BASIC_ACT);
			   player_bufflist1[0] = 1;
			   refreshBuffList1();
			   break;
	}
	}
	m_charid1.Format("%d", player_cangjian->getCharId());//��ɫID
	m_player1_hp.Format("%d", player_cangjian->getHp());
	m_player1_act.Format("%.1f", player_cangjian->getAct());
	m_player1_power.Format("%d", player_cangjian->getJianQi());
	

	/****��������ʼ��****/
	//0�ж�������
	player1_skillbox.InsertString(0, _T("Х��"));
	player1_skillbox.InsertString(1, _T("ս��"));
	player1_skillbox.InsertString(2, _T("ѩ����"));
	player1_skillbox.InsertString(3, _T("�ϳ�"));

	//0.5�ж�������
	//��

	//1�ж�������
	player1_skillbox.InsertString(4, _T("����"));
	player1_skillbox.InsertString(5, _T("Ϧ���׷�"));
	player1_skillbox.InsertString(6, _T("ƽ������"));
	player1_skillbox.InsertString(7, _T("��Ȫ����"));

	//1.5�ж�������
	player1_skillbox.InsertString(8, _T("Ȫ����"));
	player1_skillbox.InsertString(9, _T("�Ʒ����"));
	player1_skillbox.InsertString(10, _T("����"));
	player1_skillbox.InsertString(11, _T("����"));

	//2�ж�������
	player1_skillbox.InsertString(12, _T("������ɽ"));



/**************�����2���г�ʼ��***************/
	/****������Ϣ��������Ϣ��ʼ��****/
	SetDlgItemText(IDC_CHAR_NAME2, player_tiance->getCharName());//�������
	SetDlgItemText(IDC_CHAR_PRO2, player_tiance->getProName());//��������
	player_tiance->setStatus(1);
	player_tiance->setCounterDamage(0);
	player_tiance->setSufferDamage(0);
	switch (player_tiance->getStatus()){
	case 0:{
			   m_player2_horse_status.Format("δ���"); 
			   player_tiance->setAct(BASIC_ACT);
			   break;
	}
	case 1:{
			   m_player2_horse_status.Format("���");
			   player_tiance->setAct(BASIC_ACT + 1);
			   m_player2_buff_list.InsertString(m_player2_buff_count++, "���");
			   break;
	}
	}
	m_charid2.Format("%d", player_tiance->getCharId());
	m_player2_hp.Format("%d", player_tiance->getHp());
	m_player2_act.Format("%.1f", player_tiance->getAct());

	/****��������ʼ��****/
	//0�ж�������
	player2_skillbox.InsertString(0, _T("����"));

	//0.5�ж�������
	player2_skillbox.InsertString(1, _T("�����"));

	//1�ж�������
	player2_skillbox.InsertString(2, _T("����"));
	player2_skillbox.InsertString(3, _T("�Ʒ�"));
	player2_skillbox.InsertString(4, _T("������"));

	//1.5�ж�������
	player2_skillbox.InsertString(5, _T("�γ۳�"));
	player2_skillbox.InsertString(6, _T("����"));
	player2_skillbox.InsertString(7, _T("��"));
	player2_skillbox.InsertString(8, _T("����ɽ"));

	//2�ж�������
	player2_skillbox.InsertString(9, _T("����"));
	player2_skillbox.InsertString(10, _T("�Ƽ���"));
	player2_skillbox.InsertString(11, _T("����"));

	//2.5�ж�������
	player2_skillbox.InsertString(12, _T("����Χ"));

	UpdateData(0);
}

//���1����ѡ��
void CCardHeroView::OnLbnSelchangeSkillList()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	nSel_player1 = player1_skillbox.GetCurSel();//��ȡ��ǰѡ�����
	skillRemainCD1(nSel_player1);
	switch (nSel_player1){
		case 0:{//Х��
				   m_skill_comment.Format("���ڡ�ɽ�ӽ��⡱�롰��ˮ����������̬���л�����ˮ�����ж�������һ�㣻ɽ�ӽ��������������˺�����1�㣬�������κθ���Ч��Ӱ�졣");//����˵��
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("0");//�ж�������
				   m_player1_skill_cd.Format("4");//����cd
				   m_player1_skill_status.Format("��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 1:{//ս��
				   m_skill_comment.Format("��������ÿ�غ��ж���ʼ֮ǰ��ʧ1�㽣����");
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("0");//�ж�������
				   m_player1_skill_cd.Format("0");//����cd
				   m_player1_skill_status.Format("������");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 2:{//ѩ����
				   m_skill_comment.Format("˲�䲹��4�㽣����");
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("0");//�ж�������
				   m_player1_skill_cd.Format("6");//����cd
				   m_player1_skill_status.Format("��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 3:{//�ϳ�
				   m_skill_comment.Format("����ֵ��ͬһ�غ����������ɵı仯����3��ʱ�����ͷŸü��ܡ�");
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("0");//�ж�������
				   m_player1_skill_cd.Format("0");//����cd
				   m_player1_skill_status.Format("��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 4:{//����
				   m_skill_comment.Format("��Ŀ�����1���˺�����ˮ�����ͷ�����1�㽣����ɽ�ӽ������ͷ���ʹ�����á�������״̬��ʹ��һ�����˺�����1�㡣");
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("1");//�ж�������
				   m_player1_skill_cd.Format("0");//����cd
				   m_player1_skill_status.Format("��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 5:{//Ϧ���׷�
				   m_skill_comment.Format("��Ŀ�����2���˺���ֻ����ɽ�ӽ������ͷţ�����1�㽣����");
				   m_player1_skill_cost.Format("1");//��������
				   m_player1_act_cost.Format("1");//�ж�������
				   m_player1_skill_cd.Format("0");//����cd
				   m_player1_skill_status.Format("ɽ�ӽ���");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 6:{//ƽ������
				   m_skill_comment.Format("��Ŀ�����1���˺���ֻ������ˮ�����ͷţ������2�㽣����");
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("1");//�ж�������
				   m_player1_skill_cd.Format("1");//����cd
				   m_player1_skill_status.Format("��ˮ��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 7:{//��Ȫ����
				   m_skill_comment.Format("��������3���غ��ڣ��ܵ��������˺�������1�㣬����״̬�����Ļغϻ��2�㽣����");
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("1");//�ж�������
				   m_player1_skill_cd.Format("5");//����cd
				   m_player1_skill_status.Format("��ˮ��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 8:{//Ȫ����
				   m_skill_comment.Format("����һ������3�غϵĶܣ����ɵֵ���5���˺���");
				   m_player1_skill_cost.Format("0");//��������
				   m_player1_act_cost.Format("1.5");//�ж�������
				   m_player1_skill_cd.Format("8");//����cd
				   m_player1_skill_status.Format("��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 9:{//�Ʒ����
				   m_skill_comment.Format("��Ŀ�����4���˺������ͷŸü���֮�󣬱��غ��޷��ͷ��������ܣ�����2�㽣����");
				   m_player1_skill_cost.Format("2");//��������
				   m_player1_act_cost.Format("1.5");//�ж�������
				   m_player1_skill_cd.Format("2");//����cd
				   m_player1_skill_status.Format("ɽ�ӽ���");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 10:{//����
				   m_skill_comment.Format("����2�غϣ�ʹ�Է�ÿ�غϵĿ�ʼ�׶���ʧ1���ж���������2�㽣����");
				   m_player1_skill_cost.Format("1");//��������
				   m_player1_act_cost.Format("1.5");//�ж�������
				   m_player1_skill_cd.Format("5");//����cd
				   m_player1_skill_status.Format("��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 11:{//����
				   m_skill_comment.Format("����3�غϣ�ʹ�Է�ÿ�غϵĿ�ʼ�׶���ʧ0.5���ж���������2�㽣����");
				   m_player1_skill_cost.Format("1");//��������
				   m_player1_act_cost.Format("1.5");//�ж�������
				   m_player1_skill_cd.Format("6");//����cd
				   m_player1_skill_status.Format("��");//�����ͷ�״̬Ҫ��
				   break;
		}
		case 12:{//������ɽ
				   m_skill_comment.Format("ǿ�ƶԷ�����Ŀ�����ѡ��1.��һ�غ���ʧ1���ж������򱾻غ��ܵ�2���˺���2.�ܵ�5���˺�������5�㽣����ÿ������ֻ��ʹ��һ��");
				   m_player1_skill_cost.Format("5");//��������
				   m_player1_act_cost.Format("2");//�ж�������
				   m_player1_skill_cd.Format("��");//����cd
				   m_player1_skill_status.Format("ɽ�ӽ���");//�����ͷ�״̬Ҫ��
				   break;
		}
		skillRemainCD1(nSel_player1);
	}
	UpdateData(0);

}

//���2����ѡ��
void CCardHeroView::OnLbnSelchangeSkillList2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	nSel_player2 = player2_skillbox.GetCurSel();//��ȡ��ǰѡ�����

	skillRemainCD2(nSel_player2);
	switch (nSel_player2){
	case 0:{//����
			   m_skill2_comment.Format("�������״̬���������γ۳��������ĵ��ж������ӳɡ�");//����˵��
			   m_player2_act_cost.Format("0");//�ж�������
			   m_player2_skill_cd.Format("0");//����cd
			   m_player2_status.Format("���");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 1:{//�����
			   m_skill2_comment.Format("�ɱ��غϿ�ʼ��ÿ�غ�����1�ж��㣬����3�غϣ����Ƴ��������п���״̬��");//����˵��
			   m_player2_act_cost.Format("0.5");//�ж�������
			   m_player2_skill_cd.Format("7");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 2:{//����
			   m_skill2_comment.Format("���1���˺����������1�㡱���ˡ�Ч����3�����˱�Ϊ�²У�����3�غϡ�");//����˵��
			   m_player2_act_cost.Format("1");//�ж�������
			   m_player2_skill_cd.Format("0");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 3:{//�Ʒ�
			   m_skill2_comment.Format("Ϊ�Է�ʩ��һ��״̬����״̬ÿ�غ�ʹ�Է�ʧȥ1��Ѫ��������3�غϣ�����Է��������б�buff����ˢ��buff����ʱ�䡣");//����˵��
			   m_player2_act_cost.Format("1");//�ж�������
			   m_player2_skill_cd.Format("0");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 4:{//������
			   m_skill2_comment.Format("Ϊ�Լ����һ���������֡�״̬���ӱ��غϿ�ʼ��Ч������3�غ�ÿ����ļ��ܶԶԷ�����˺�����ʹ�Լ��ָ�1��Ѫ��ֵ��");//����˵��
			   m_player2_act_cost.Format("1");//�ж�������
			   m_player2_skill_cd.Format("8");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 5:{//�γ۳�
			   m_skill2_comment.Format("��Ϊ���״̬���ڽ�������3�غ���ÿ�غ�����1���ж�����");//����˵��
			   m_player2_act_cost.Format("1.5");//�ж�������
			   m_player2_skill_cd.Format("7");//����cd
			   m_player2_status.Format("δ���");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 6:{//����
			   m_skill2_comment.Format("���2���˺�������Ϊ�Է����1�����²С�״̬������3�غϡ�");//����˵��
			   m_player2_act_cost.Format("1.5");//�ж�������
			   m_player2_skill_cd.Format("1");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 7:{//��
			   m_skill2_comment.Format("Ϊ�Է����1��\"��\"״̬������3�غϣ�ÿ�غϿ�ʼ�׶�ʹ�Է�ʧȥ0.5���ж�����");//����˵��
			   m_player2_act_cost.Format("1.5");//�ж�������
			   m_player2_skill_cd.Format("5");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 8:{//����ɽ
			   m_skill2_comment.Format("��������3���غ������ܵ������˺�����Ϊ1�㡣");//����˵��
			   m_player2_act_cost.Format("1.5");//�ж�������
			   m_player2_skill_cd.Format("10");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 9:{//����
			   m_skill2_comment.Format("��Ŀ�����4���˺����������²�״̬��");//����˵��
			   m_player2_act_cost.Format("2");//�ж�������
			   m_player2_skill_cd.Format("0");//����cd
			   m_player2_status.Format("��");//�����ͷ�״̬Ҫ��
			   break;
	}
	case 10:{//�Ƽ���
				m_skill2_comment.Format("��Է�3�غ��� �޷��ж������������²С���");//����˵��
				m_player2_act_cost.Format("2");//�ж�������
				m_player2_skill_cd.Format("6");//����cd
				m_player2_status.Format("���");//�����ͷ�״̬Ҫ��
				break;
	}
	case 11:{//����
				m_skill2_comment.Format("��Ŀ�����4���˺�����ʹ������������ֵ��Ϊԭ��ֵ��һ�룬����3�غϡ�");//����˵��
				m_player2_act_cost.Format("2");//�ж�������
				m_player2_skill_cd.Format("6");//����cd
				m_player2_status.Format("δ���");//�����ͷ�״̬Ҫ��
				break;
	}
	case 12:{//����Χ
				m_skill2_comment.Format("���5���˺���");//����˵��
				m_player2_act_cost.Format("2.5");//�ж�������
				m_player2_skill_cd.Format("7");//����cd
				m_player2_status.Format("���");//�����ͷ�״̬Ҫ��
				break;
	}
	}
	UpdateData(0);
}

//���1�ж��ͷ�
void CCardHeroView::OnBnClickedAction()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (player_cangjian->getActRight() == 1){//���ж�Ȩ��
		if (nSel_player1 != -1){//����δ�ͷ�
			if (player1_skill_record[9] == 0){//û���ͷ��Ʒ����
				if (player1_skill_record[nSel_player1] == 0){//û���ͷŹ��������
					switch (nSel_player1){
					case 0:{//Х��
							   if (player1_cd_record[nSel_player1] != 0){
								   MessageBox("����������ȴ֮�У�");
							   }
							   else{
								   player1_skill_record[nSel_player1] = 1;
								   player1_cd_record[nSel_player1] = 5;
								   if (player_cangjian->getStatus() == 1){//�л�����ˮ��
									   player_cangjian->setStatus(0);
									   player_cangjian->setSufferDamage(0);
									   player_bufflist1[0] = 0;
									   player_cangjian->addAct(1);
									   refreshBuffList1();
								   }
								   else{//�л���ɽ�ӽ���
									   player_cangjian->setStatus(1);
									   player_cangjian->setSufferDamage(-1);//�����˺�����һ��
									   player_bufflist1[0] = 1;
									   player_cangjian->subAct(1);
									   refreshBuffList1();
								   }
								   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "Х��", 0, player_cangjian->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
							   }
							   
							   break;
					}
					case 1:{//ս��
							   player1_skill_record[nSel_player1] = 1;
							   MessageBox("���������޷��ͷţ�");
							   break;
					}
					case 2:{//ѩ����
							   if (player1_cd_record[nSel_player1] != 0){
								   MessageBox("����������ȴ֮�У�");
							   }
							   else{
								   player1_cd_record[nSel_player1] = 7;
								   player1_skill_record[nSel_player1] = 1;
								   player_cangjian->addJianQi(4);
								   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "ѩ����", 0, player_cangjian->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   c_jianqi += 4;
								   UpdateData(FALSE);
							   }
							   break;
					}
					case 3:{//�ϳ�
							   if (c_jianqi >= 3){
								   c_jianqi = 0;//�Ѿ��ͷţ��ѽ����仯������
								   player1_skill_record[nSel_player1] = 1;//��¼�ϳ����ͷ�
								   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "�ϳ�", 2, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//����˺�							   
								   if (player_bufflist1[1] == 1){//�ж��Ƿ��з���buff
									   player_cangjian->setCounterDamage(0);//�˺��Ѿ�������ˣ����԰����ӵ��˺�����
									   player_bufflist1[1]--;
									   refreshBuffList1();
								   }
							   }
							   else
								   MessageBox("�������㣬�޷��ͷţ�");
							   break;
					}
					case 4:{//����
							   if (player_cangjian->getAct() < 1){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   c_jianqi += 1;
								   player1_skill_record[nSel_player1] = 1;
								   player_cangjian->addJianQi(1);//����1�㽣��
								   player_cangjian->subAct(1);
								   if (player_cangjian->getStatus() == 0){//��ˮ�����ͷ�
									   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "����", 1, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
									   if (player_bufflist1[1] == 1){//�ж��Ƿ��з���buff
										   player_cangjian->setCounterDamage(0);//�˺��Ѿ�������ˣ����԰����ӵ��˺�����
										   player_bufflist1[1]--;
										   refreshBuffList1();
									   }
								   }
								   else{//ɽ�ӽ������ͷ�
									   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "����", 1, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
									   if (player_bufflist1[1] == 1){//�ж��Ƿ��з���buff
										   player_cangjian->setCounterDamage(0);//�˺��Ѿ�������ˣ����԰����ӵ��˺�����
										   player_bufflist1[1]--;
										   refreshBuffList1();
									   }
									   player_bufflist1[1] = 1;
									   player_cangjian->addCounterDamage(1);
									   refreshBuffList1();
								   }
							   }
							   break;
					}
					case 5:{//Ϧ���׷�		
							   if (player_cangjian->getAct() < 1){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   if (player_cangjian->getStatus() == 0)
									   MessageBox("�ü���ֻ����ɽ�ӽ������ͷţ�");
								   else{
									   if (player_cangjian->getJianQi() < 1)
										   MessageBox("�������㣬�޷��ͷţ�");
									   else{//�����ͷ�
										   c_jianqi += 1;
										   player1_skill_record[nSel_player1] = 1;//����ͷż�¼
										   player_cangjian->subJianQi(1);//����1�㽣��
										   player_cangjian->subAct(1);
										   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "Ϧ���׷�", 2, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//����˺�							   
										   if (player_bufflist1[1] == 1){//�ж��Ƿ��з���buff
											   player_cangjian->setCounterDamage(0);//�˺��Ѿ�������ˣ����԰����ӵ��˺�����
											   player_bufflist1[1]--;
											   refreshBuffList1();
										   }
									   }
								   }
							   }
							   break;
					}
					case 6:{//ƽ������
							   if (player_cangjian->getAct() < 1){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("����������ȴ֮�У�");
								   }
								   else{
									   c_jianqi += 2;
										if (player_cangjian->getStatus() == 1)
											MessageBox("�ü���ֻ������ˮ�����ͷţ�");
										else{//�����ͷ�
											player1_cd_record[nSel_player1] = 2;
											player1_skill_record[nSel_player1] = 1;//����ͷż�¼
											player_cangjian->addJianQi(2);//����2�㽣��
											player_cangjian->subAct(1);
											outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "ƽ������", 1, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//����˺�							   
											if (player_bufflist1[1] == 1){//�ж��Ƿ��з���buff
												player_cangjian->setCounterDamage(0);//�˺��Ѿ�������ˣ����԰����ӵ��˺�����
												player_bufflist1[1]--;
												refreshBuffList1();
											 }
										 }
								   }
							   }
							   break;
					}
					case 7:{//��Ȫ����
							   if (player_cangjian->getAct() < 1){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
							       if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("����������ȴ֮�У�");
								   }
								   else{
									   if (player_cangjian->getStatus() == 1){
										   MessageBox("�ü���ֻ������ˮ�����ͷţ�");
									   }
									   else{
										   player1_cd_record[nSel_player1] = 6;
										   player1_skill_record[nSel_player1] = 1;
										   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "��Ȫ����", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
										   player_cangjian->subAct(1);
										   player_bufflist1[2] = 3;
										   refreshBuffList1();
										   player_cangjian->addSufferDamage(1);
									   }
								   }
							   }
							   break;
					}
					case 8:{//Ȫ����
							   if (player_cangjian->getAct() < 1.5){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("����������ȴ֮�У�");
								   }
								   else{
									   player1_cd_record[nSel_player1] = 9;
									   player1_skill_record[nSel_player1] = 1;
									   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "Ȫ����", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
									   player_cangjian->setShield(5);
									   player_cangjian->subAct(1.5);
									   player_bufflist1[3] = 3;
									   refreshBuffList1();
								   }
							   }
							   break;
					}
					case 9:{//�Ʒ����
							   if (player_cangjian->getAct() < 1.5){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("����������ȴ֮�У�");
								   }
								   else{
										   if (player_cangjian->getStatus() == 0)
										   MessageBox("�ü���ֻ����ɽ�ӽ������ͷţ�");
									   else{
										   if (player_cangjian->getJianQi() < 2)
											   MessageBox("�������㣬�޷��ͷţ�");
										   else{//�����ͷ�
											   c_jianqi += 2;
											   player1_cd_record[nSel_player1] = 3;
											   player1_skill_record[nSel_player1] = 1;//����ͷż�¼
											   player_cangjian->subJianQi(2);//����1�㽣��
											   player_cangjian->subAct(1.5);
											   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "�Ʒ����", 4, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//����˺�							   
											   if (player_bufflist1[1] == 1){//�ж��Ƿ��з���buff
												   player_cangjian->setCounterDamage(0);//�˺��Ѿ�������ˣ����԰����ӵ��˺�����
												   player_bufflist1[1]--;
												   refreshBuffList1();
											   }
										   }
										}
								   }
							   }
							   break;
					}
					case 10:{//����
								if (player_cangjian->getAct() < 1.5){
									MessageBox("�ж������㣬�޷��ͷţ�");
								}
								else{
									if (player1_cd_record[nSel_player1] != 0){
										MessageBox("����������ȴ֮�У�");
									}
									else{
										if (player_cangjian->getJianQi() < 2)
										MessageBox("�������㣬�޷��ͷţ�");
										else{
											c_jianqi += 1;
											player1_cd_record[nSel_player1] = 6;
											player1_skill_record[nSel_player1] = 1;
											outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "����", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
											player_cangjian->subAct(1.5);
											player_cangjian->subJianQi(2);
											player_bufflist2[16] = 2;
											refreshBuffList2();
										}
									}
								}
								break;
					}
					case 11:{//����
								if (player_cangjian->getAct() < 1.5){
									MessageBox("�ж������㣬�޷��ͷţ�");
								}
								else{
									if (player1_cd_record[nSel_player1] != 0){
										MessageBox("����������ȴ֮�У�");
									}
									else{
										if (player_cangjian->getJianQi() < 2)
										MessageBox("�������㣬�޷��ͷţ�");
										else{
											c_jianqi += 1;
											player1_cd_record[nSel_player1] = 6;
											player1_skill_record[nSel_player1] = 1;
											outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "����", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
											player_cangjian->subAct(1.5);
											player_cangjian->subJianQi(2);
											player_bufflist2[17] = 3;
											refreshBuffList2();
										}
									}
								}
								break;
					}
					case 12:{//������ɽ
								if (player_cangjian->getAct() < 2){
									MessageBox("�ж������㣬�޷��ͷţ�");
								}
								else{
									if (player_cangjian->getStatus() == 0){
										MessageBox("�ü���ֻ����ɽ�ӽ������ͷţ�");
									}
									else{
										if (player_cangjian->getJianQi() < 5){
											MessageBox("�������㣬�޷��ͷţ�");
										}
										else{
											if (player1_skill_record[nSel_player1] == 1){
												MessageBox("�������ͷţ��޷��ٴ��ͷţ�");
											}
											else{
												c_jianqi += 5;
												player1_skill_record[nSel_player1] = 1;
												player_cangjian->subAct(2);
												player_cangjian->subJianQi(5);
												if (MessageBox("�Ƿ�ִ�С����غ���2���˺�����һ�غ���ʧ1���ж����������򱾻غ��ܵ�5���˺�", NULL, MB_YESNO) == IDYES){
													outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "������ɽ", 2, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
													player_bufflist2[18] = 1;
													refreshBuffList2();
												}
												else
													outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "������ɽ", 5, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
											}
										}
									}
								}
								break;
					}
					default:MessageBox("��ѡ���ܣ�");
					}
					//��������ˢ�µ�ԭ����������ط��Ѿ��м��ܽ�������ȷ���ͷţ����Կ���������ط�ˢ��
					m_player1_power.Format("%d", player_cangjian->getJianQi());//ˢ�½���
					m_player1_act.Format("%.1f", player_cangjian->getAct());//ˢ���ж���
					skillRemainCD1(nSel_player1);//������ط�û��
				}
				else
					MessageBox("�ü��ܱ��غ����ͷţ��޷��ٴ��ͷţ�");
			}
			else
				MessageBox("���غ����ͷ��Ʒ���ʣ��޷��ͷ��������ܣ�");
		}
		else
			MessageBox("δѡ�м��ܣ�");
	}
	else
		MessageBox("��������ж��غϣ�");

		if (player_tiance->getHp() <= 0)
			MessageBox("ҶӢʤ����");

	UpdateData(FALSE);
}

//���2�ж��ͷ�
void CCardHeroView::OnBnClickedAction2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(TRUE);
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (player_tiance->getActRight() == 1){
		if (nSel_player2 != -1){
			if (player2_skill_record[nSel_player2] == 0){
				switch (nSel_player2){
				case 0:{//����
						   if (player_tiance->getStatus()==1){//���
							   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
							   player_bufflist2[0] = 0;//��������������ĵ�buff
							   player_tiance->setStatus(0);
							   player_tiance->subAct(1);//�ͷŸü��ܣ�����γ�Ƹ�������ĵ�Ч���ж�������
							   if (player_bufflist2[2] != 0){
								   player_bufflist2[2] = 0;
								   player_tiance->subAct(1);
							   }
							   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "����", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
							   refreshBuffList2();//ˢ��buff�б�
						   }
						   else{
							   MessageBox("�ü����ͷ���Ҫ�����״̬�²����ͷţ�");
						   }
						   break;

				}
				case 1:{//�����
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("����������ȴ֮�У�");
						   }
						   else{
							   if (player_tiance->getAct() < 0.5){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
								   player_bufflist2[16] = 0;
								   player_bufflist2[17] = 0;
								   player_bufflist2[1] = 3;//��Ǽ����������ĵ�buff
								   player_tiance->addAct(1);//�ҷ�buff��������Ч�����ж�����1
								   player2_cd_record[nSel_player2] = 8;//������ȴʱ��
								   player_tiance->subAct(0.5);//�ͷŸü������ĵ��ж���
								   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "�����", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   refreshBuffList2();//ˢ��buff�б�
							   }
						   }
						   break;

				}
				case 2:{//����
						   if (player_tiance->getAct() < 1){
							   MessageBox("�ж������㣬�޷��ͷţ�");
						   }
						   else{
							   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
							   
							   if (player_bufflist2[3] != 0){//������buff����״̬������˺��ظ�1��Ѫ��
								   player_tiance->addHp(1);
								   m_player2_hp.Format("%d", player_tiance->getHp());
							   }
							   player_bufflist1[10] = 3;
							   boolDamage = 1;
							   toDamage++;
							   

							   //player_bufflist2[10] = 2;//��Ǽ����������ĵ�buff
							   
							   player_tiance->subAct(1);//�ͷŸü������ĵ��ж���
							   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "����", 1, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
							   if (toDamage == 3){
								   toDamage = 0;
								   player_bufflist1[11] = 3;//�²�
								   player_cangjian->setSufferDamage(-1);
								   player_bufflist1[10] = 0;
							   }
							   refreshBuffList1();//ˢ��buff�б�
						   }
						   break;
				}
				case 3:{//�Ʒ�
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("����������ȴ֮�У�");
						   }
						   else{
							   if (player_tiance->getAct() < 1){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
								   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "�Ʒ�", 1, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   if (player_bufflist2[3] != 0){//������buff����״̬������˺��ظ�1��Ѫ��
									   player_tiance->addHp(1);
									   m_player2_hp.Format("%d", player_tiance->getHp());

								   }
								   //player_bufflist2[15] = 3;//��Ǽ����������ĵ�buff
								   player_bufflist1[15] = 3;
								   player2_cd_record[nSel_player2] = 6;//������ȴʱ��
								   player_tiance->subAct(1);//�ͷŸü������ĵ��ж���
								   refreshBuffList1();//ˢ��buff�б�
							   }
						   }
						   break;
				}
				case 4:{//������
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("����������ȴ֮�У�");
						   }
						   else{
							   if (player_tiance->getAct() < 1){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
								   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "������", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   //player_tiance->addHp(1);
								   player_bufflist2[3] = 2;//��Ǽ����������ĵ�buff
								   player2_cd_record[nSel_player2] = 9;//������ȴʱ��
								   player_tiance->subAct(1);//�ͷŸü������ĵ��ж���
								   refreshBuffList2();//ˢ��buff�б�
							   }
						   }
						   break;
				}
				case 5:{//�γ�Ƹ
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("����������ȴ֮�У�");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   if (player_tiance->getStatus() == 0){//δ���
									   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
									   player_bufflist2[0] = 1;//
									   player_tiance->setStatus(1);
									   player_bufflist2[2] = 4;//��Ǽ����������ĵ�buff
									   player2_cd_record[nSel_player2] = 8;//������ȴʱ��
									   player_tiance->addAct(1);
									   player_tiance->subAct(1.5);//�ͷŸü������ĵ��ж���
									   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "�γ�Ƹ", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
									   refreshBuffList2();//ˢ��buff�б�
								   }
								   else{
									   MessageBox("�ü����ͷ���Ҫ��δ���״̬�²����ͷţ�");
								   }
							   }
						   }
						   break;
				}
				case 6:{//����
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("����������ȴ֮�У�");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
								   //outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "����", 2, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   //player_bufflist2[11] = 2;//��Ǽ����������ĵ�buff
								   player_bufflist1[11] = 3;
								   if (player_bufflist2[3] != 0){//������buff����״̬������˺��ظ�1��Ѫ��
									   player_tiance->addHp(1);
									   
									   m_player2_hp.Format("%d", player_tiance->getHp());
								   }


								   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "����", 2, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);

								   player_cangjian->setSufferDamage(-1);
								  
								   player2_cd_record[nSel_player2] = 2;//������ȴʱ��
								   
								   player_tiance->subAct(1.5);//�ͷŸü������ĵ��ж���
								   refreshBuffList1();//ˢ��buff�б�
							   }
						   }
						   break;
				}
				case 7:{//��
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("����������ȴ֮�У�");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   if (player_tiance->getStatus() == 0){//δ���
									   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
									   //player_bufflist2[12] = 1;//��Ǽ����������ĵ�buff
									   player_bufflist1[12] = 1;
									   player2_cd_record[nSel_player2] = 6;//������ȴʱ��
									   player_tiance->subAct(1.5);//�ͷŸü������ĵ��ж���
									   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "��", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
									   refreshBuffList1();//ˢ��buff�б�
								   }
								   else{
									   MessageBox("�ü����ͷ���Ҫ��δ���״̬�²����ͷţ�");
								   }
							   }
						   }
						   break;
				}
				case 8:{//����ɽ
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("����������ȴ֮�У�");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("�ж������㣬�޷��ͷţ�");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
								   player_bufflist2[4] = 3;//��Ǽ����������ĵ�buff
								   player2_cd_record[nSel_player2] = 11;//������ȴʱ��
								   player_tiance->subAct(1.5);//�ͷŸü������ĵ��ж���
								   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "����ɽ", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   refreshBuffList2();//ˢ��buff�б�
							   }
						   }
						   break;
				}
				case 9:{//����
						   if (player_tiance->getAct() < 2){
							   MessageBox("�ж������㣬�޷��ͷţ�");
						   }
						   else{
							   if (player_bufflist1[11] != 0){//�²�״̬							   
								   player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
								   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "����", 4, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   if (player_bufflist2[3] != 0){//������buff����״̬������˺��ظ�1��Ѫ��
									   player_tiance->addHp(1);
									   m_player2_hp.Format("%d", player_tiance->getHp());
								   }
									player_bufflist1[11] = 0;//��������������ĵ�buff
									player_cangjian->setSufferDamage(0);
								   //player_cangjian->subHp(1);
								   player_tiance->subAct(2);//�ͷŸü������ĵ��ж���
								   refreshBuffList1();//ˢ��buff�б�
							   }
							   else{
								   MessageBox("�ü����ͷ���Ҫ���²�״̬�²����ͷţ�");
							   }
						   }
						   break;
				}
				case 10:{//�Ƽ���
							if (player2_cd_record[nSel_player2] != 0){
								MessageBox("����������ȴ֮�У�");
							}
							else{
								if (player_tiance->getAct() < 1.5){
									MessageBox("�ж������㣬�޷��ͷţ�");
								}
								else{
									if (player_tiance->getStatus() == 1){//���
										player_bufflist1[11] = 0;//��������������ĵ�buff
										player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
										player_bufflist1[14] = 3;//��Ǽ����������ĵ�buff
										player2_cd_record[nSel_player2] = 7;//������ȴʱ��
										player_tiance->subAct(2);//�ͷŸü������ĵ��ж���
										outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "�Ƽ���", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
										refreshBuffList2();//ˢ��buff�б�
										refreshBuffList1();
									}
									else{
										MessageBox("�ü����ͷ���Ҫ�����״̬�²����ͷţ�");
									}
								}
							}
							break;
				}
				case 11:{//����
							if (player2_cd_record[nSel_player2] != 0){
								MessageBox("����������ȴ֮�У�");
							}
							else{
								if (player_tiance->getAct() < 2){
									MessageBox("�ж������㣬�޷��ͷţ�");
								}
								else{
									if (player_tiance->getStatus() == 0){//δ���
										player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
										outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "����", 4, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
										if (player_bufflist2[3] != 0){//������buff����״̬������˺��ظ�1��Ѫ��
											player_tiance->addHp(1);
											m_player2_hp.Format("%d", player_tiance->getHp());
										}
										player_bufflist1[13] = 1;//��Ǽ����������ĵ�buff
										player2_cd_record[nSel_player2] = 7;//������ȴʱ��
										player_tiance->subAct(2);//�ͷŸü������ĵ��ж���
										refreshBuffList2();//ˢ��buff�б�
									}
									else{
										MessageBox("�ü����ͷ���Ҫ��δ���״̬�²����ͷţ�");
									}
								}
							}
							break;
				}
				case 12:{//����Χ
							if (player2_cd_record[nSel_player2] != 0){
								MessageBox("����������ȴ֮�У�");
							}
							else{
								if (player_tiance->getAct() < 2.5){
									MessageBox("�ж������㣬�޷��ͷţ�");
								}
								else{
									if (player_tiance->getStatus() == 1){//���
										player2_skill_record[nSel_player2] = 1;//��Ǹü��ܱ��غ����ͷ�
										outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "����Χ", 5, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
										if (player_bufflist2[3] != 0){//������buff����״̬������˺��ظ�1��Ѫ��
											player_tiance->addHp(1);
											m_player2_hp.Format("%d", player_tiance->getHp());
										}
										player2_cd_record[nSel_player2] = 8;//������ȴʱ��
										player_tiance->subAct(2.5);//�ͷŸü������ĵ��ж���
									}
									else{
										MessageBox("�ü����ͷ���Ҫ�����״̬�²����ͷţ�");
									}
								}
							}
							break;
				}
				default:MessageBox("��ѡ���ܣ�");
				}
				//��������ˢ�µ�ԭ����������ط��Ѿ��м��ܽ�������ȷ���ͷţ����Կ���������ط�ˢ��

				//m_player2_act.Format("%.1f", player_tiance->getAct());
				skillRemainCD2(nSel_player2);
				if (player_bufflist2[0] == 1){
					m_player2_horse_status.Format("���");
				}
				else
				{
					m_player2_horse_status.Format("δ���");
				}

			}
			else{
				MessageBox("�ü��ܱ��غ����ͷţ��޷��ͷ��������ܣ�");
			}
		}
		else{
			MessageBox("ûѡ�м��ܣ�");
		}
	}
	else{
		MessageBox("��������ж��غϣ�");
	}
	m_player2_act.Format("%.1f", player_tiance->getAct());
	m_player2_hp.Format("%d", player_tiance->getHp());
	m_player1_hp.Format("%d", player_cangjian->getHp());
	
	if (player_cangjian->getHp() <= 0)
		MessageBox("��ж�ʤ����");
	UpdateData(FALSE);
}

//�ؽ������غϣ���������ж������в��������ü����ͷż�¼�����ü���ѡ��
void CCardHeroView::OnBnClickedEnd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (player_cangjian->getActRight() == 1){
		player_cangjian->setActRight(0);//ȡ���ؽ��ж�Ȩ��
		player_tiance->setActRight(1);//��������ж�Ȩ��
		if (player_tiance->getStatus() == 0)
			player_tiance->setAct(BASIC_ACT);//δ������ж���Ϊ��ʼ3��
		else
			player_tiance->setAct(BASIC_ACT + 1);//���״̬�²�����3��

		for (int i = 0; i < 13; i++){//����߼���CD�����޸�
			if (player2_cd_record[i] > 0){
				player2_cd_record[i]--;
			}
		}

		if (player_bufflist2[1] != 0){//���ҷ�����ж�
			player_tiance->addAct(1);
			//player_bufflist2[1]--;
			//refreshBuffList2();
		}

		if (player_bufflist2[16] != 0){//�����½����ж�
			player_tiance->subAct(1);
			player_bufflist2[16]--;
			refreshBuffList2();
		}

		if (player_bufflist2[17] != 0){//�Ծ��ν����ж�
			player_tiance->subAct(0.5);
			player_bufflist2[17]--;
			refreshBuffList2();
		}

		

		if (player_bufflist2[2] != 0){//�Լ��۽����ж�
			player_tiance->addAct(1);
			player_bufflist2[2]--;
			refreshBuffList2();
		}

		if (player_bufflist2[3] != 0){//���ֽ����ж�
			player_bufflist2[3]--;
			refreshBuffList2();
		}

		if (player_bufflist2[4] != 0){//���ֽ����ж�
			player_bufflist2[4]--;
			refreshBuffList2();
		}
		
		

		fight_round = "��������������";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "�غϡ�����������";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);
		for (int i = 0; i < 12; i++)
			player2_skill_record[i] = 0;//���м����ͷż�¼����
		player2_skill_record[12] = 0;//����һ�����ܣ�ȫ��������
		nSel_player2 = -1;
		refreshBuffList2();
	}
	else
		MessageBox("������ĻغϽ���ʲô��");
	m_player2_act.Format("%.1f", player_tiance->getAct());//ˢ���ж���
	UpdateData(FALSE);
}

//��߽����غϣ����Բؽ��ж������в���
void CCardHeroView::OnBnClickedEnd2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (player_tiance->getActRight() == 1){
		player_cangjian->setActRight(1);//���òؽ��ж�Ȩ��
		player_tiance->setActRight(0);//ȡ������ж�Ȩ��

		if (player_bufflist1[2] > 0){//�Բؽ���������в���
			player_bufflist1[2]--;
			if (player_bufflist1[2] == 0){
				player_cangjian->setSufferDamage(0);
				player_cangjian->addJianQi(3);
				refreshBuffList1();
			}
		}
		
		if (player_bufflist2[1] != 0){//���ҷ�����ж�
			player_bufflist2[1]--;
			refreshBuffList2();
		}

		if (player_bufflist1[3] > 0){//�Բؽ���Ȫ���½��в���
			player_bufflist1[3]--;
			if (player_bufflist1[2] == 0){
				player_cangjian->setShield(0);
				refreshBuffList1();
			}
		}

		if (player_bufflist1[10] != 0){
			player_bufflist1[10] --;
			refreshBuffList1();
		}

		if (boolDamage == 0){//�����˽����ж�
			toDamage = 0;
			//
		}

		
		if (player_bufflist1[11] != 0){//���²н����ж�
			player_bufflist1[11]--;
			if (player_bufflist1[11] == 0){
				player_cangjian->setSufferDamage(0);
			}
			refreshBuffList1();
		}

		if (player_bufflist1[12] != 0){//�Դ������ж�
			if (player_bufflist1[12] != 0){
				player_cangjian->subAct(1);
				player_bufflist1[12]--;
			}
			refreshBuffList1();
		}

		

		if (player_bufflist1[14] != 0){//���Ƽ�������ж�
			
			player_bufflist1[14]--;
			
			refreshBuffList1();
		}

		if (player_bufflist1[15] != 0){//���Ʒ�����ж�
			player_cangjian->subHp(1);
			//player_bufflist1[15]--;
			player_bufflist1[15]--;
			refreshBuffList1();
		}

		for (int i = 0; i < 12; i++){//�Բؽ�����CD�����޸�
			if (player1_cd_record[i] > 0){
				player1_cd_record[i]--;
			}
		}


		if (player_tiance->getStatus() == 0)
			player_tiance->setAct(BASIC_ACT);//δ������ж���Ϊ��ʼ3��
		else
			player_tiance->setAct(BASIC_ACT + 1);//���״̬�²�����3��
		/*��ս����־���в���*/
		fight_round = "��������������";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "�غϡ�����������";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);

		/*�Բؽ����г�ʼ����*/
		if (player_cangjian->getStatus() == 0)
			player_cangjian->setAct(BASIC_ACT + 1);//��ˮ�����ж���������4��
		else
			player_cangjian->setAct(BASIC_ACT);//ɽ�ӽ����²�����3��
		for (int i = 0; i < 12; i++)//���òؽ������ͷż�¼
			player1_skill_record[i] = 0;


		c_jianqi = 0;//���ý����仯��¼
		nSel_player1 = -1;//���ü���ѡ��
		player_cangjian->subJianQi(1);
		m_player1_power.Format("%d", player_cangjian->getJianQi());
		m_player1_act.Format("%.1f", player_cangjian->getAct());
		m_player1_hp.Format("%d", player_cangjian->getHp());
		m_player2_act.Format("%.1f", player_tiance->getAct());
		UpdateData(FALSE);
	}
	else
		MessageBox("������ĻغϽ���ʲô��");
}


// ս����־���
void CCardHeroView::outFightDairy(int player1_id, int player2_id, CString skill_name, int basic_damage, int count_damage,int suff_damage, int line_dairy)
{
	CString temp;
	CString damage_temp;
	int sub_damage;

	if (player_cangjian->getCharId() == player1_id){//�ж���������ɲؽ����
		temp += "ҶӢ";
		if (player_cangjian->getCharId() == player2_id){//�ж϶������ͷ�
			temp += "�ͷ���";
			temp += skill_name;
			temp += "��";
		}
		else{
			temp += "����ж��ͷ���";
			temp += skill_name;
			if (basic_damage != 0){//�ж������˺����ؽ�����ߴ��˺�
				if (player_bufflist2[4] != 0){
					player_tiance->subHp(1);
					m_player2_hp.Format("%d", player_tiance->getHp());
					damage_temp.Format("%d", 1);
				}
				else{
					player_tiance->subHp(basic_damage + count_damage - suff_damage);
					m_player2_hp.Format("%d", player_tiance->getHp());
					damage_temp.Format("%d", basic_damage + count_damage - suff_damage);
				}
				temp += "���������";
				temp += damage_temp;
				temp += "���˺���";
			}
			else//û���˺�
				temp += "��";
		}
	}
	else{//��ߴ������
		temp += "��ж�";
		if (player_tiance->getCharId() == player2_id){//�ж϶������ͷ�
			temp += "�ͷ���";
			temp += skill_name;
			temp += "��";
		}
		else{
			temp += "��ҶӢ�ͷ���";
			temp += skill_name;
			if (basic_damage != 0){//�ж����˺�����߶Բؽ����˺�
				if (player_cangjian->getShield() > 0){
					if ((player_cangjian->getShield() - basic_damage + count_damage - suff_damage) > 0){//�˺�ȫ���ɶܵ���
						player_cangjian->subShield(basic_damage - count_damage + suff_damage);
						temp += "����Ȫ���µ�����";
						damage_temp.Format("%d", basic_damage - count_damage + suff_damage);
						temp += damage_temp;
						temp += "���˺���";
					}
					else {//û��ȫ��������
						sub_damage = basic_damage - count_damage + suff_damage - player_cangjian->getShield();
						player_cangjian->setShield(0);
						player_bufflist1[3] = 0;
						temp += "����Ȫ���µ�����";
						damage_temp.Format("%d", player_cangjian->getShield());
						temp += damage_temp;
						temp += "���˺���";
						temp += "���������";
						damage_temp.Format("%d", sub_damage);
						player_cangjian->subHp(basic_damage + count_damage - suff_damage);
						m_player1_hp.Format("%d", player_cangjian->getHp());
						temp += damage_temp;
						temp += "���˺���";
					}
				}
				else{
					player_cangjian->subHp(basic_damage + count_damage - suff_damage);
					m_player1_hp.Format("%d", player_cangjian->getHp());
					damage_temp.Format("%d", basic_damage + count_damage - suff_damage);
					temp += "���������";
					temp += damage_temp;
					temp += "���˺���";
				}
			}
			else//û���˺�
				temp += "��";
		}
	}
	fight_dairybox.InsertString(line_dairy, temp);
	UpdateData(FALSE);
}


// ˢ�����1��buff�б�
void CCardHeroView::refreshBuffList1()
{
	int n = 0;
	m_player1_buff_list.ResetContent();
	for (int i = 0; i < 20; i++){
		switch (i){
		case 0:{
				   if (player_bufflist1[i] == 0)
					   m_player1_buff_list.InsertString(n++, "��ˮ��");
				   else
					   m_player1_buff_list.InsertString(n++, "ɽ�ӽ���");
				   break;
		}
		case 1:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "����");  
				   break;
		}
		case 2:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "����");
				   break;
		}
		case 3:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "Ȫ����");
				   break;
		}
		case 4:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "��");
				   break;
		}
		case 5:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "��");
				   break;
		}
		case 6:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "��");
				   break;
		}
		case 7:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "��");
				   break;
		}
		case 8:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "��");
				   break;
		}
		case 9:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "��");
				   break;
		}
		case 10:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "����");
				   break;
		}
		case 11:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "�²�");
				   break;
		}
		case 12:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "��");
				   break;
		}
		case 13:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "����");
				   break;
		}
		case 14:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "�Ƽ���");
				   break;
		}
		case 15:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "�Ʒ�");
				   break;
		}
		case 16:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "����");
				   break;
		}
		case 17:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "����");
				   break;
		}
		case 18:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "����");
				   break;
		}
		}
	}
}



// ˢ�����2��buff�б�
void CCardHeroView::refreshBuffList2()
{
	int n = 0;
	m_player2_buff_list.ResetContent();
	for (int i = 0; i < 20; i++){
		switch (i){
		case 0:{
				   if (player_bufflist2[i] == 0)
					   m_player2_buff_list.InsertString(n++, "δ���");
				   else
					   m_player2_buff_list.InsertString(n++, "���");
				   break;
		}
		case 1:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "�ҷ�");
				   break;
		}
		case 2:{
				   if (player_bufflist2[i] != 0 && player_bufflist2[i] != 4)
					   m_player2_buff_list.InsertString(n++, "����");
				   break;
		}
		case 3:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "��");
				   break;
		}
		case 4:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "ɽ");
				   break;
		}
		case 5:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "��");
				   break;
		}
		case 6:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "��");
				   break;
		}
		case 7:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "��");
				   break;
		}
		case 8:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "��");
				   break;
		}
		case 9:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "��");
				   break;
		}
		case 10:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "����");
					break;
		}
		case 11:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "�²�");
					break;
		}
		case 12:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "��");
					break;
		}
		case 13:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "����");
					break;
		}
		case 14:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "�Ƽ���");
					break;
		}
		case 15:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "�Ʒ�");
					break;
		}
		case 16:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "����");
					break;
		}
		case 17:{
					if (player_bufflist2[i] != 0){
							m_player2_buff_list.InsertString(n++, "����");
					}
					break;
		}
		case 18:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "����");
					break;
		}
		}
	}
}


// ��ʾ���1�ļ���ʣ��cd
void CCardHeroView::skillRemainCD1(int skill_id)
{
	CString temp;
	if (player1_cd_record[skill_id] - 1  == -1)
		m_remain_cd1.Format("���ͷ�");
	else
		m_remain_cd1.Format("%d", player1_cd_record[skill_id] - 1);
}


// �Խ�ɫ״̬����˵��
void CCardHeroView::showBuffComment(CString skill_name)
{
	if (skill_name == "ɽ�ӽ���"){
		m_player1_buff_comment.Format("�����˺�����1�㣬�������κο���");
	}
	else if (skill_name == "��ˮ��"){
		m_player1_buff_comment.Format("�ж�������1��");
	}
	else if (skill_name == "����"){
		m_player1_buff_comment.Format("���������˺�����1�㣬��ʧȥ��״̬�Ļغϣ��õ�2�㽣��");
	}
	else if (skill_name == "����"){
		m_player1_buff_comment.Format("ʹ��һ��������1���˺�");
	}
	else if (skill_name == "Ȫ����"){
		m_player1_buff_comment.Format("����3�غϵĶܣ����ɵֵ���5���˺���");
	}
	else if (skill_name == "����"){
		m_player1_buff_comment.Format("3�����˱�Ϊ1���²�");
	}
	else if (skill_name == "�²�"){
		m_player1_buff_comment.Format("�����˺�����һ��");
	}
	else if (skill_name == "��"){
		m_player1_buff_comment.Format("״̬��ʧʱ��Է��ڸûغϵĿ�ʼ�׶���ʧ1���ж���");
	}
	else if (skill_name == "����"){
		m_player1_buff_comment.Format("ʹ�Է����ܵ���������Ϊ50%");
	}
	else if (skill_name == "�Ƽ���"){
		m_player1_buff_comment.Format("��Է�3�غ��޷��ж�");
	}
	else if (skill_name == "����"){
		m_player1_buff_comment.Format("�غϵĿ�ʼ�׶���ʧ1���ж���");
	}
	else if (skill_name == "����"){
		m_player1_buff_comment.Format("�غϵĿ�ʼ�׶���ʧ0.5���ж���");
	}
}


void CCardHeroView::OnLbnSelchangeBuffList1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	int n = m_player1_buff_list.GetCurSel();
	m_player1_buff_list.GetText(n, str);

	showBuffComment(str);
	UpdateData(FALSE);
}


void CCardHeroView::skillRemainCD2(int skill_id)
{
	UpdateData(true);
	CString temp;
	if (player2_cd_record[skill_id] - 1 == -1)
		m_remain_cd2.Format("���ͷ�");
	else
		m_remain_cd2.Format("%d", player2_cd_record[skill_id] - 1);
	UpdateData(false);
}
