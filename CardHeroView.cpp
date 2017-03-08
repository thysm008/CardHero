
// CardHeroView.cpp : CCardHeroView 类的实现
//

#include "stdafx.h"
#include "stdlib.h"
#include "CangJian.h"
#include "TianCe.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CCardHeroView 构造/析构

CCangJian *player_cangjian = new CCangJian("叶英", "藏剑", 1001, 1, 100);//初始化玩家1
CTianCe *player_tiance = new CTianCe("李承恩", "天策", 1002, 2, 101);//初始化玩家2

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
	// TODO:  在此处添加构造代码

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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

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


// CCardHeroView 诊断

#ifdef _DEBUG
void CCardHeroView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCardHeroView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCardHeroDoc* CCardHeroView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCardHeroDoc)));
	return (CCardHeroDoc*)m_pDocument;
}
#endif //_DEBUG


// CCardHeroView 消息处理程序


void CCardHeroView::OnSingleVs()
{
	// TODO:  在此添加命令处理程序代码
	//清空玩家技能表
	toDamage = 0;
	boolDamage = 0;
	round = 0;
	Damage = false;
	player_cangjian->setAct(BASIC_ACT);//将行动力设置为基础3点
	player_tiance->setAct(BASIC_ACT);
	player_cangjian->setHp(30);//设置玩家基础血量
	player_tiance->setHp(30);
	m_player1_buff_count = 0;//重置所有buff数量
	m_player2_buff_count = 0;
	player1_skillbox.ResetContent();//清空技能栏
	player2_skillbox.ResetContent();
	fight_dairybox.ResetContent();//清空战斗日志
	m_player1_buff_list.ResetContent();//清空状态列表
	m_player2_buff_list.ResetContent();
	fight_dairy_count = 0;//清空战斗日志条目
	player_cangjian->setActRight(0);//重置双方行动权限
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

	//生成随机数判断先后手
	srand(time(NULL));

	int random = rand() % 2;

	if (random){
		MessageBox("藏剑先手");
		fight_dairybox.InsertString(fight_dairy_count++, "藏剑先手");
		fight_round = "——————第";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "回合——————";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);
		player_cangjian->setActRight(1);
	}
	else{
		MessageBox("天策先手");
		fight_dairybox.InsertString(fight_dairy_count++, "天策先手");
		fight_round = "——————第";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "回合——————";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);
		player_tiance->setActRight(1);
	}

/**************对玩家1进行初始化***************/
	/****基本信息与属性信息初始化****/
	SetDlgItemText(IDC_CHAR_NAME, player_cangjian->getCharName());//玩家名称
	SetDlgItemText(IDC_CHAR_PRO, player_cangjian->getProName());//门派名称
	player_cangjian->setJianQi(0);//剑气置零
	player_cangjian->setCounterDamage(0);//增益伤害置零
	player_cangjian->setSufferDamage(0);//易伤buff置零
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
	m_charid1.Format("%d", player_cangjian->getCharId());//角色ID
	m_player1_hp.Format("%d", player_cangjian->getHp());
	m_player1_act.Format("%.1f", player_cangjian->getAct());
	m_player1_power.Format("%d", player_cangjian->getJianQi());
	

	/****技能栏初始化****/
	//0行动力技能
	player1_skillbox.InsertString(0, _T("啸日"));
	player1_skillbox.InsertString(1, _T("战意"));
	player1_skillbox.InsertString(2, _T("雪断桥"));
	player1_skillbox.InsertString(3, _T("断潮"));

	//0.5行动力技能
	//无

	//1行动力技能
	player1_skillbox.InsertString(4, _T("听雷"));
	player1_skillbox.InsertString(5, _T("夕照雷锋"));
	player1_skillbox.InsertString(6, _T("平湖断月"));
	player1_skillbox.InsertString(7, _T("梦泉虎跑"));

	//1.5行动力技能
	player1_skillbox.InsertString(8, _T("泉凝月"));
	player1_skillbox.InsertString(9, _T("云飞玉皇"));
	player1_skillbox.InsertString(10, _T("醉月"));
	player1_skillbox.InsertString(11, _T("惊涛"));

	//2行动力技能
	player1_skillbox.InsertString(12, _T("风来吴山"));



/**************对玩家2进行初始化***************/
	/****基本信息与属性信息初始化****/
	SetDlgItemText(IDC_CHAR_NAME2, player_tiance->getCharName());//玩家名称
	SetDlgItemText(IDC_CHAR_PRO2, player_tiance->getProName());//门派名称
	player_tiance->setStatus(1);
	player_tiance->setCounterDamage(0);
	player_tiance->setSufferDamage(0);
	switch (player_tiance->getStatus()){
	case 0:{
			   m_player2_horse_status.Format("未骑乘"); 
			   player_tiance->setAct(BASIC_ACT);
			   break;
	}
	case 1:{
			   m_player2_horse_status.Format("骑乘");
			   player_tiance->setAct(BASIC_ACT + 1);
			   m_player2_buff_list.InsertString(m_player2_buff_count++, "骑乘");
			   break;
	}
	}
	m_charid2.Format("%d", player_tiance->getCharId());
	m_player2_hp.Format("%d", player_tiance->getHp());
	m_player2_act.Format("%.1f", player_tiance->getAct());

	/****技能栏初始化****/
	//0行动力技能
	player2_skillbox.InsertString(0, _T("下马"));

	//0.5行动力技能
	player2_skillbox.InsertString(1, _T("疾如风"));

	//1行动力技能
	player2_skillbox.InsertString(2, _T("穿云"));
	player2_skillbox.InsertString(3, _T("破风"));
	player2_skillbox.InsertString(4, _T("徐如林"));

	//1.5行动力技能
	player2_skillbox.InsertString(5, _T("任驰骋"));
	player2_skillbox.InsertString(6, _T("龙吟"));
	player2_skillbox.InsertString(7, _T("穿"));
	player2_skillbox.InsertString(8, _T("守如山"));

	//2行动力技能
	player2_skillbox.InsertString(9, _T("龙牙"));
	player2_skillbox.InsertString(10, _T("破坚阵"));
	player2_skillbox.InsertString(11, _T("霹雳"));

	//2.5行动力技能
	player2_skillbox.InsertString(12, _T("破重围"));

	UpdateData(0);
}

//玩家1技能选择
void CCardHeroView::OnLbnSelchangeSkillList()
{
	// TODO:  在此添加控件通知处理程序代码

	nSel_player1 = player1_skillbox.GetCurSel();//获取当前选择序号
	skillRemainCD1(nSel_player1);
	switch (nSel_player1){
		case 0:{//啸日
				   m_skill_comment.Format("可在“山居剑意”与“问水诀”两种形态下切换。问水诀下行动力增加一点；山居剑意下所有所受伤害增加1点，但不受任何负面效果影响。");//技能说明
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("0");//行动力消耗
				   m_player1_skill_cd.Format("4");//技能cd
				   m_player1_skill_status.Format("无");//技能释放状态要求
				   break;
		}
		case 1:{//战意
				   m_skill_comment.Format("被动技，每回合行动开始之前损失1点剑气。");
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("0");//行动力消耗
				   m_player1_skill_cd.Format("0");//技能cd
				   m_player1_skill_status.Format("被动技");//技能释放状态要求
				   break;
		}
		case 2:{//雪断桥
				   m_skill_comment.Format("瞬间补充4点剑气。");
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("0");//行动力消耗
				   m_player1_skill_cd.Format("6");//技能cd
				   m_player1_skill_status.Format("无");//技能释放状态要求
				   break;
		}
		case 3:{//断潮
				   m_skill_comment.Format("剑气值在同一回合由玩家所造成的变化大于3点时，可释放该技能。");
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("0");//行动力消耗
				   m_player1_skill_cd.Format("0");//技能cd
				   m_player1_skill_status.Format("无");//技能释放状态要求
				   break;
		}
		case 4:{//听雷
				   m_skill_comment.Format("对目标造成1点伤害。问水诀下释放则获得1点剑气，山居剑意下释放则使自身获得“凤鸣”状态：使下一技能伤害增加1点。");
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("1");//行动力消耗
				   m_player1_skill_cd.Format("0");//技能cd
				   m_player1_skill_status.Format("无");//技能释放状态要求
				   break;
		}
		case 5:{//夕照雷锋
				   m_skill_comment.Format("对目标造成2点伤害，只可在山居剑意下释放，消耗1点剑气。");
				   m_player1_skill_cost.Format("1");//剑气消耗
				   m_player1_act_cost.Format("1");//行动力消耗
				   m_player1_skill_cd.Format("0");//技能cd
				   m_player1_skill_status.Format("山居剑意");//技能释放状态要求
				   break;
		}
		case 6:{//平湖断月
				   m_skill_comment.Format("对目标造成1点伤害，只可在问水诀下释放，并获得2点剑气。");
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("1");//行动力消耗
				   m_player1_skill_cd.Format("1");//技能cd
				   m_player1_skill_status.Format("问水诀");//技能释放状态要求
				   break;
		}
		case 7:{//梦泉虎跑
				   m_skill_comment.Format("接下来的3个回合内，受到的所有伤害均减少1点，并在状态结束的回合获得2点剑气。");
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("1");//行动力消耗
				   m_player1_skill_cd.Format("5");//技能cd
				   m_player1_skill_status.Format("问水诀");//技能释放状态要求
				   break;
		}
		case 8:{//泉凝月
				   m_skill_comment.Format("产生一个持续3回合的盾，最多可抵挡共5点伤害。");
				   m_player1_skill_cost.Format("0");//剑气消耗
				   m_player1_act_cost.Format("1.5");//行动力消耗
				   m_player1_skill_cd.Format("8");//技能cd
				   m_player1_skill_status.Format("无");//技能释放状态要求
				   break;
		}
		case 9:{//云飞玉皇
				   m_skill_comment.Format("对目标造成4点伤害，且释放该技能之后，本回合无法释放其他技能，消耗2点剑气。");
				   m_player1_skill_cost.Format("2");//剑气消耗
				   m_player1_act_cost.Format("1.5");//行动力消耗
				   m_player1_skill_cd.Format("2");//技能cd
				   m_player1_skill_status.Format("山居剑意");//技能释放状态要求
				   break;
		}
		case 10:{//醉月
				   m_skill_comment.Format("持续2回合，使对方每回合的开始阶段损失1点行动力。消耗2点剑气。");
				   m_player1_skill_cost.Format("1");//剑气消耗
				   m_player1_act_cost.Format("1.5");//行动力消耗
				   m_player1_skill_cd.Format("5");//技能cd
				   m_player1_skill_status.Format("无");//技能释放状态要求
				   break;
		}
		case 11:{//惊涛
				   m_skill_comment.Format("持续3回合，使对方每回合的开始阶段损失0.5点行动力。消耗2点剑气。");
				   m_player1_skill_cost.Format("1");//剑气消耗
				   m_player1_act_cost.Format("1.5");//行动力消耗
				   m_player1_skill_cd.Format("6");//技能cd
				   m_player1_skill_status.Format("无");//技能释放状态要求
				   break;
		}
		case 12:{//风来吴山
				   m_skill_comment.Format("强制对方所有目标进行选择：1.下一回合损失1点行动力，则本回合受到2点伤害。2.受到5点伤害。消耗5点剑气，每场比赛只能使用一次");
				   m_player1_skill_cost.Format("5");//剑气消耗
				   m_player1_act_cost.Format("2");//行动力消耗
				   m_player1_skill_cd.Format("∞");//技能cd
				   m_player1_skill_status.Format("山居剑意");//技能释放状态要求
				   break;
		}
		skillRemainCD1(nSel_player1);
	}
	UpdateData(0);

}

//玩家2技能选择
void CCardHeroView::OnLbnSelchangeSkillList2()
{
	// TODO:  在此添加控件通知处理程序代码

	nSel_player2 = player2_skillbox.GetCurSel();//获取当前选择序号

	skillRemainCD2(nSel_player2);
	switch (nSel_player2){
	case 0:{//下马
			   m_skill2_comment.Format("结束骑乘状态，并结束任驰骋所带来的的行动点数加成。");//技能说明
			   m_player2_act_cost.Format("0");//行动力消耗
			   m_player2_skill_cd.Format("0");//技能cd
			   m_player2_status.Format("骑乘");//技能释放状态要求
			   break;
	}
	case 1:{//疾如风
			   m_skill2_comment.Format("由本回合开始，每回合增加1行动点，持续3回合，并移除自身所有控制状态。");//技能说明
			   m_player2_act_cost.Format("0.5");//行动力消耗
			   m_player2_skill_cd.Format("7");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 2:{//穿云
			   m_skill2_comment.Format("造成1点伤害，并且添加1层”致伤”效果，3层致伤变为致残，持续3回合。");//技能说明
			   m_player2_act_cost.Format("1");//行动力消耗
			   m_player2_skill_cd.Format("0");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 3:{//破风
			   m_skill2_comment.Format("为对方施加一个状态，该状态每回合使对方失去1点血量，持续3回合；如果对方身上已有本buff，则刷新buff持续时间。");//技能说明
			   m_player2_act_cost.Format("1");//行动力消耗
			   m_player2_skill_cd.Format("0");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 4:{//徐如林
			   m_skill2_comment.Format("为自己添加一个”徐如林”状态，从本回合开始生效，持续3回合每次你的技能对对方造成伤害，可使自己恢复1点血量值。");//技能说明
			   m_player2_act_cost.Format("1");//行动力消耗
			   m_player2_skill_cd.Format("8");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 5:{//任驰骋
			   m_skill2_comment.Format("变为骑乘状态，在接下来的3回合内每回合增加1点行动力。");//技能说明
			   m_player2_act_cost.Format("1.5");//行动力消耗
			   m_player2_skill_cd.Format("7");//技能cd
			   m_player2_status.Format("未骑乘");//技能释放状态要求
			   break;
	}
	case 6:{//龙吟
			   m_skill2_comment.Format("造成2点伤害，并且为对方添加1个“致残”状态，持续3回合。");//技能说明
			   m_player2_act_cost.Format("1.5");//行动力消耗
			   m_player2_skill_cd.Format("1");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 7:{//穿
			   m_skill2_comment.Format("为对方添加1个\"穿\"状态，持续3回合，每回合开始阶段使对方失去0.5点行动力。");//技能说明
			   m_player2_act_cost.Format("1.5");//行动力消耗
			   m_player2_skill_cd.Format("5");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 8:{//守如山
			   m_skill2_comment.Format("接下来的3个回合内所受的所有伤害均变为1点。");//技能说明
			   m_player2_act_cost.Format("1.5");//行动力消耗
			   m_player2_skill_cd.Format("10");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 9:{//龙牙
			   m_skill2_comment.Format("对目标造成4点伤害，并结束致残状态。");//技能说明
			   m_player2_act_cost.Format("2");//行动力消耗
			   m_player2_skill_cd.Format("0");//技能cd
			   m_player2_status.Format("无");//技能释放状态要求
			   break;
	}
	case 10:{//破坚阵
				m_skill2_comment.Format("令对方3回合内 无法行动，并结束“致残”。");//技能说明
				m_player2_act_cost.Format("2");//行动力消耗
				m_player2_skill_cd.Format("6");//技能cd
				m_player2_status.Format("骑乘");//技能释放状态要求
				break;
	}
	case 11:{//霹雳
				m_skill2_comment.Format("对目标造成4点伤害，并使其所受治疗数值变为原数值的一半，持续3回合。");//技能说明
				m_player2_act_cost.Format("2");//行动力消耗
				m_player2_skill_cd.Format("6");//技能cd
				m_player2_status.Format("未骑乘");//技能释放状态要求
				break;
	}
	case 12:{//破重围
				m_skill2_comment.Format("造成5点伤害。");//技能说明
				m_player2_act_cost.Format("2.5");//行动力消耗
				m_player2_skill_cd.Format("7");//技能cd
				m_player2_status.Format("骑乘");//技能释放状态要求
				break;
	}
	}
	UpdateData(0);
}

//玩家1行动释放
void CCardHeroView::OnBnClickedAction()
{
	// TODO:  在此添加控件通知处理程序代码
	if (player_cangjian->getActRight() == 1){//有行动权限
		if (nSel_player1 != -1){//技能未释放
			if (player1_skill_record[9] == 0){//没有释放云飞玉皇
				if (player1_skill_record[nSel_player1] == 0){//没有释放过这个技能
					switch (nSel_player1){
					case 0:{//啸日
							   if (player1_cd_record[nSel_player1] != 0){
								   MessageBox("技能仍在冷却之中！");
							   }
							   else{
								   player1_skill_record[nSel_player1] = 1;
								   player1_cd_record[nSel_player1] = 5;
								   if (player_cangjian->getStatus() == 1){//切换成问水诀
									   player_cangjian->setStatus(0);
									   player_cangjian->setSufferDamage(0);
									   player_bufflist1[0] = 0;
									   player_cangjian->addAct(1);
									   refreshBuffList1();
								   }
								   else{//切换成山居剑意
									   player_cangjian->setStatus(1);
									   player_cangjian->setSufferDamage(-1);//所受伤害加深一点
									   player_bufflist1[0] = 1;
									   player_cangjian->subAct(1);
									   refreshBuffList1();
								   }
								   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "啸日", 0, player_cangjian->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
							   }
							   
							   break;
					}
					case 1:{//战意
							   player1_skill_record[nSel_player1] = 1;
							   MessageBox("被动技，无法释放！");
							   break;
					}
					case 2:{//雪断桥
							   if (player1_cd_record[nSel_player1] != 0){
								   MessageBox("技能仍在冷却之中！");
							   }
							   else{
								   player1_cd_record[nSel_player1] = 7;
								   player1_skill_record[nSel_player1] = 1;
								   player_cangjian->addJianQi(4);
								   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "雪断桥", 0, player_cangjian->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   c_jianqi += 4;
								   UpdateData(FALSE);
							   }
							   break;
					}
					case 3:{//断潮
							   if (c_jianqi >= 3){
								   c_jianqi = 0;//已经释放，把剑气变化量置零
								   player1_skill_record[nSel_player1] = 1;//记录断潮的释放
								   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "断潮", 2, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//打出伤害							   
								   if (player_bufflist1[1] == 1){//判断是否有凤鸣buff
									   player_cangjian->setCounterDamage(0);//伤害已经打出来了，所以把增加的伤害归零
									   player_bufflist1[1]--;
									   refreshBuffList1();
								   }
							   }
							   else
								   MessageBox("条件不足，无法释放！");
							   break;
					}
					case 4:{//听雷
							   if (player_cangjian->getAct() < 1){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   c_jianqi += 1;
								   player1_skill_record[nSel_player1] = 1;
								   player_cangjian->addJianQi(1);//增加1点剑气
								   player_cangjian->subAct(1);
								   if (player_cangjian->getStatus() == 0){//问水诀下释放
									   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "听雷", 1, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
									   if (player_bufflist1[1] == 1){//判断是否有凤鸣buff
										   player_cangjian->setCounterDamage(0);//伤害已经打出来了，所以把增加的伤害归零
										   player_bufflist1[1]--;
										   refreshBuffList1();
									   }
								   }
								   else{//山居剑意下释放
									   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "听雷", 1, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
									   if (player_bufflist1[1] == 1){//判断是否有凤鸣buff
										   player_cangjian->setCounterDamage(0);//伤害已经打出来了，所以把增加的伤害归零
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
					case 5:{//夕照雷锋		
							   if (player_cangjian->getAct() < 1){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   if (player_cangjian->getStatus() == 0)
									   MessageBox("该技能只能在山居剑意下释放！");
								   else{
									   if (player_cangjian->getJianQi() < 1)
										   MessageBox("剑气不足，无法释放！");
									   else{//正常释放
										   c_jianqi += 1;
										   player1_skill_record[nSel_player1] = 1;//添加释放记录
										   player_cangjian->subJianQi(1);//减少1点剑气
										   player_cangjian->subAct(1);
										   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "夕照雷锋", 2, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//打出伤害							   
										   if (player_bufflist1[1] == 1){//判断是否有凤鸣buff
											   player_cangjian->setCounterDamage(0);//伤害已经打出来了，所以把增加的伤害归零
											   player_bufflist1[1]--;
											   refreshBuffList1();
										   }
									   }
								   }
							   }
							   break;
					}
					case 6:{//平湖断月
							   if (player_cangjian->getAct() < 1){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("技能仍在冷却之中！");
								   }
								   else{
									   c_jianqi += 2;
										if (player_cangjian->getStatus() == 1)
											MessageBox("该技能只能在问水诀下释放！");
										else{//正常释放
											player1_cd_record[nSel_player1] = 2;
											player1_skill_record[nSel_player1] = 1;//添加释放记录
											player_cangjian->addJianQi(2);//增加2点剑气
											player_cangjian->subAct(1);
											outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "平湖断月", 1, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//打出伤害							   
											if (player_bufflist1[1] == 1){//判断是否有凤鸣buff
												player_cangjian->setCounterDamage(0);//伤害已经打出来了，所以把增加的伤害归零
												player_bufflist1[1]--;
												refreshBuffList1();
											 }
										 }
								   }
							   }
							   break;
					}
					case 7:{//梦泉虎跑
							   if (player_cangjian->getAct() < 1){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
							       if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("技能仍在冷却之中！");
								   }
								   else{
									   if (player_cangjian->getStatus() == 1){
										   MessageBox("该技能只能在问水诀下释放！");
									   }
									   else{
										   player1_cd_record[nSel_player1] = 6;
										   player1_skill_record[nSel_player1] = 1;
										   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "梦泉虎跑", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
										   player_cangjian->subAct(1);
										   player_bufflist1[2] = 3;
										   refreshBuffList1();
										   player_cangjian->addSufferDamage(1);
									   }
								   }
							   }
							   break;
					}
					case 8:{//泉凝月
							   if (player_cangjian->getAct() < 1.5){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("技能仍在冷却之中！");
								   }
								   else{
									   player1_cd_record[nSel_player1] = 9;
									   player1_skill_record[nSel_player1] = 1;
									   outFightDairy(player_cangjian->getCharId(), player_cangjian->getCharId(), "泉凝月", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
									   player_cangjian->setShield(5);
									   player_cangjian->subAct(1.5);
									   player_bufflist1[3] = 3;
									   refreshBuffList1();
								   }
							   }
							   break;
					}
					case 9:{//云飞玉皇
							   if (player_cangjian->getAct() < 1.5){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   if (player1_cd_record[nSel_player1] != 0){
									   MessageBox("技能仍在冷却之中！");
								   }
								   else{
										   if (player_cangjian->getStatus() == 0)
										   MessageBox("该技能只能在山居剑意下释放！");
									   else{
										   if (player_cangjian->getJianQi() < 2)
											   MessageBox("剑气不足，无法释放！");
										   else{//正常释放
											   c_jianqi += 2;
											   player1_cd_record[nSel_player1] = 3;
											   player1_skill_record[nSel_player1] = 1;//添加释放记录
											   player_cangjian->subJianQi(2);//减少1点剑气
											   player_cangjian->subAct(1.5);
											   outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "云飞玉皇", 4, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);//打出伤害							   
											   if (player_bufflist1[1] == 1){//判断是否有凤鸣buff
												   player_cangjian->setCounterDamage(0);//伤害已经打出来了，所以把增加的伤害归零
												   player_bufflist1[1]--;
												   refreshBuffList1();
											   }
										   }
										}
								   }
							   }
							   break;
					}
					case 10:{//醉月
								if (player_cangjian->getAct() < 1.5){
									MessageBox("行动力不足，无法释放！");
								}
								else{
									if (player1_cd_record[nSel_player1] != 0){
										MessageBox("技能仍在冷却之中！");
									}
									else{
										if (player_cangjian->getJianQi() < 2)
										MessageBox("剑气不足，无法释放！");
										else{
											c_jianqi += 1;
											player1_cd_record[nSel_player1] = 6;
											player1_skill_record[nSel_player1] = 1;
											outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "醉月", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
											player_cangjian->subAct(1.5);
											player_cangjian->subJianQi(2);
											player_bufflist2[16] = 2;
											refreshBuffList2();
										}
									}
								}
								break;
					}
					case 11:{//惊涛
								if (player_cangjian->getAct() < 1.5){
									MessageBox("行动力不足，无法释放！");
								}
								else{
									if (player1_cd_record[nSel_player1] != 0){
										MessageBox("技能仍在冷却之中！");
									}
									else{
										if (player_cangjian->getJianQi() < 2)
										MessageBox("剑气不足，无法释放！");
										else{
											c_jianqi += 1;
											player1_cd_record[nSel_player1] = 6;
											player1_skill_record[nSel_player1] = 1;
											outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "惊涛", 0, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
											player_cangjian->subAct(1.5);
											player_cangjian->subJianQi(2);
											player_bufflist2[17] = 3;
											refreshBuffList2();
										}
									}
								}
								break;
					}
					case 12:{//风来吴山
								if (player_cangjian->getAct() < 2){
									MessageBox("行动力不足，无法释放！");
								}
								else{
									if (player_cangjian->getStatus() == 0){
										MessageBox("该技能只能在山居剑意下释放！");
									}
									else{
										if (player_cangjian->getJianQi() < 5){
											MessageBox("剑气不足，无法释放！");
										}
										else{
											if (player1_skill_record[nSel_player1] == 1){
												MessageBox("本局已释放，无法再次释放！");
											}
											else{
												c_jianqi += 5;
												player1_skill_record[nSel_player1] = 1;
												player_cangjian->subAct(2);
												player_cangjian->subJianQi(5);
												if (MessageBox("是否执行“本回合受2点伤害、下一回合损失1点行动力”？否则本回合受到5点伤害", NULL, MB_YESNO) == IDYES){
													outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "风来吴山", 2, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
													player_bufflist2[18] = 1;
													refreshBuffList2();
												}
												else
													outFightDairy(player_cangjian->getCharId(), player_tiance->getCharId(), "风来吴山", 5, player_cangjian->getCounterDamage(), player_tiance->getSufferDamage(), fight_dairy_count++);
											}
										}
									}
								}
								break;
					}
					default:MessageBox("请选择技能！");
					}
					//放在这里刷新的原因是在这个地方已经有技能进行了正确的释放，所以可以在这个地方刷新
					m_player1_power.Format("%d", player_cangjian->getJianQi());//刷新剑气
					m_player1_act.Format("%.1f", player_cangjian->getAct());//刷新行动力
					skillRemainCD1(nSel_player1);//在这个地方没有
				}
				else
					MessageBox("该技能本回合已释放，无法再次释放！");
			}
			else
				MessageBox("本回合已释放云飞玉皇，无法释放其他技能！");
		}
		else
			MessageBox("未选中技能！");
	}
	else
		MessageBox("不是你的行动回合！");

		if (player_tiance->getHp() <= 0)
			MessageBox("叶英胜利！");

	UpdateData(FALSE);
}

//玩家2行动释放
void CCardHeroView::OnBnClickedAction2()
{
	// TODO:  在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	
	// TODO:  在此添加控件通知处理程序代码
	if (player_tiance->getActRight() == 1){
		if (nSel_player2 != -1){
			if (player2_skill_record[nSel_player2] == 0){
				switch (nSel_player2){
				case 0:{//下马
						   if (player_tiance->getStatus()==1){//骑乘
							   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
							   player_bufflist2[0] = 0;//解除技能所带来的的buff
							   player_tiance->setStatus(0);
							   player_tiance->subAct(1);//释放该技能，解除任驰聘所带来的的效果行动力减少
							   if (player_bufflist2[2] != 0){
								   player_bufflist2[2] = 0;
								   player_tiance->subAct(1);
							   }
							   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "下马", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
							   refreshBuffList2();//刷新buff列表
						   }
						   else{
							   MessageBox("该技能释放需要在骑乘状态下才能释放！");
						   }
						   break;

				}
				case 1:{//疾如风
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("技能扔在冷却之中！");
						   }
						   else{
							   if (player_tiance->getAct() < 0.5){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
								   player_bufflist2[16] = 0;
								   player_bufflist2[17] = 0;
								   player_bufflist2[1] = 3;//标记技能所带来的的buff
								   player_tiance->addAct(1);//烈风buff所带来的效果，行动力加1
								   player2_cd_record[nSel_player2] = 8;//技能冷却时间
								   player_tiance->subAct(0.5);//释放该技能消耗的行动力
								   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "疾如风", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   refreshBuffList2();//刷新buff列表
							   }
						   }
						   break;

				}
				case 2:{//穿云
						   if (player_tiance->getAct() < 1){
							   MessageBox("行动力不足，无法释放！");
						   }
						   else{
							   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
							   
							   if (player_bufflist2[3] != 0){//徐如林buff的林状态，打出伤害回复1点血量
								   player_tiance->addHp(1);
								   m_player2_hp.Format("%d", player_tiance->getHp());
							   }
							   player_bufflist1[10] = 3;
							   boolDamage = 1;
							   toDamage++;
							   

							   //player_bufflist2[10] = 2;//标记技能所带来的的buff
							   
							   player_tiance->subAct(1);//释放该技能消耗的行动力
							   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "穿云", 1, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
							   if (toDamage == 3){
								   toDamage = 0;
								   player_bufflist1[11] = 3;//致残
								   player_cangjian->setSufferDamage(-1);
								   player_bufflist1[10] = 0;
							   }
							   refreshBuffList1();//刷新buff列表
						   }
						   break;
				}
				case 3:{//破风
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("技能扔在冷却之中！");
						   }
						   else{
							   if (player_tiance->getAct() < 1){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
								   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "破风", 1, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   if (player_bufflist2[3] != 0){//徐如林buff的林状态，打出伤害回复1点血量
									   player_tiance->addHp(1);
									   m_player2_hp.Format("%d", player_tiance->getHp());

								   }
								   //player_bufflist2[15] = 3;//标记技能所带来的的buff
								   player_bufflist1[15] = 3;
								   player2_cd_record[nSel_player2] = 6;//技能冷却时间
								   player_tiance->subAct(1);//释放该技能消耗的行动力
								   refreshBuffList1();//刷新buff列表
							   }
						   }
						   break;
				}
				case 4:{//徐如林
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("技能扔在冷却之中！");
						   }
						   else{
							   if (player_tiance->getAct() < 1){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
								   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "徐如林", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   //player_tiance->addHp(1);
								   player_bufflist2[3] = 2;//标记技能所带来的的buff
								   player2_cd_record[nSel_player2] = 9;//技能冷却时间
								   player_tiance->subAct(1);//释放该技能消耗的行动力
								   refreshBuffList2();//刷新buff列表
							   }
						   }
						   break;
				}
				case 5:{//任驰聘
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("技能扔在冷却之中！");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   if (player_tiance->getStatus() == 0){//未骑乘
									   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
									   player_bufflist2[0] = 1;//
									   player_tiance->setStatus(1);
									   player_bufflist2[2] = 4;//标记技能所带来的的buff
									   player2_cd_record[nSel_player2] = 8;//技能冷却时间
									   player_tiance->addAct(1);
									   player_tiance->subAct(1.5);//释放该技能消耗的行动力
									   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "任驰聘", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
									   refreshBuffList2();//刷新buff列表
								   }
								   else{
									   MessageBox("该技能释放需要在未骑乘状态下才能释放！");
								   }
							   }
						   }
						   break;
				}
				case 6:{//龙吟
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("技能扔在冷却之中！");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
								   //outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "龙吟", 2, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   //player_bufflist2[11] = 2;//标记技能所带来的的buff
								   player_bufflist1[11] = 3;
								   if (player_bufflist2[3] != 0){//徐如林buff的林状态，打出伤害回复1点血量
									   player_tiance->addHp(1);
									   
									   m_player2_hp.Format("%d", player_tiance->getHp());
								   }


								   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "龙吟", 2, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);

								   player_cangjian->setSufferDamage(-1);
								  
								   player2_cd_record[nSel_player2] = 2;//技能冷却时间
								   
								   player_tiance->subAct(1.5);//释放该技能消耗的行动力
								   refreshBuffList1();//刷新buff列表
							   }
						   }
						   break;
				}
				case 7:{//穿
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("技能扔在冷却之中！");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   if (player_tiance->getStatus() == 0){//未骑乘
									   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
									   //player_bufflist2[12] = 1;//标记技能所带来的的buff
									   player_bufflist1[12] = 1;
									   player2_cd_record[nSel_player2] = 6;//技能冷却时间
									   player_tiance->subAct(1.5);//释放该技能消耗的行动力
									   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "穿", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
									   refreshBuffList1();//刷新buff列表
								   }
								   else{
									   MessageBox("该技能释放需要在未骑乘状态下才能释放！");
								   }
							   }
						   }
						   break;
				}
				case 8:{//守如山
						   if (player2_cd_record[nSel_player2] != 0){
							   MessageBox("技能扔在冷却之中！");
						   }
						   else{
							   if (player_tiance->getAct() < 1.5){
								   MessageBox("行动力不足，无法释放！");
							   }
							   else{
								   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
								   player_bufflist2[4] = 3;//标记技能所带来的的buff
								   player2_cd_record[nSel_player2] = 11;//技能冷却时间
								   player_tiance->subAct(1.5);//释放该技能消耗的行动力
								   outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "守如山", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   refreshBuffList2();//刷新buff列表
							   }
						   }
						   break;
				}
				case 9:{//龙牙
						   if (player_tiance->getAct() < 2){
							   MessageBox("行动力不足，无法释放！");
						   }
						   else{
							   if (player_bufflist1[11] != 0){//致残状态							   
								   player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
								   outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "龙牙", 4, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
								   if (player_bufflist2[3] != 0){//徐如林buff的林状态，打出伤害回复1点血量
									   player_tiance->addHp(1);
									   m_player2_hp.Format("%d", player_tiance->getHp());
								   }
									player_bufflist1[11] = 0;//解除技能所带来的的buff
									player_cangjian->setSufferDamage(0);
								   //player_cangjian->subHp(1);
								   player_tiance->subAct(2);//释放该技能消耗的行动力
								   refreshBuffList1();//刷新buff列表
							   }
							   else{
								   MessageBox("该技能释放需要在致残状态下才能释放！");
							   }
						   }
						   break;
				}
				case 10:{//破坚阵
							if (player2_cd_record[nSel_player2] != 0){
								MessageBox("技能扔在冷却之中！");
							}
							else{
								if (player_tiance->getAct() < 1.5){
									MessageBox("行动力不足，无法释放！");
								}
								else{
									if (player_tiance->getStatus() == 1){//骑乘
										player_bufflist1[11] = 0;//解除技能所带来的的buff
										player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
										player_bufflist1[14] = 3;//标记技能所带来的的buff
										player2_cd_record[nSel_player2] = 7;//技能冷却时间
										player_tiance->subAct(2);//释放该技能消耗的行动力
										outFightDairy(player_tiance->getCharId(), player_tiance->getCharId(), "破坚阵", 0, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
										refreshBuffList2();//刷新buff列表
										refreshBuffList1();
									}
									else{
										MessageBox("该技能释放需要在骑乘状态下才能释放！");
									}
								}
							}
							break;
				}
				case 11:{//霹雳
							if (player2_cd_record[nSel_player2] != 0){
								MessageBox("技能扔在冷却之中！");
							}
							else{
								if (player_tiance->getAct() < 2){
									MessageBox("行动力不足，无法释放！");
								}
								else{
									if (player_tiance->getStatus() == 0){//未骑乘
										player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
										outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "霹雳", 4, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
										if (player_bufflist2[3] != 0){//徐如林buff的林状态，打出伤害回复1点血量
											player_tiance->addHp(1);
											m_player2_hp.Format("%d", player_tiance->getHp());
										}
										player_bufflist1[13] = 1;//标记技能所带来的的buff
										player2_cd_record[nSel_player2] = 7;//技能冷却时间
										player_tiance->subAct(2);//释放该技能消耗的行动力
										refreshBuffList2();//刷新buff列表
									}
									else{
										MessageBox("该技能释放需要在未骑乘状态下才能释放！");
									}
								}
							}
							break;
				}
				case 12:{//破重围
							if (player2_cd_record[nSel_player2] != 0){
								MessageBox("技能扔在冷却之中！");
							}
							else{
								if (player_tiance->getAct() < 2.5){
									MessageBox("行动力不足，无法释放！");
								}
								else{
									if (player_tiance->getStatus() == 1){//骑乘
										player2_skill_record[nSel_player2] = 1;//标记该技能本回合已释放
										outFightDairy(player_tiance->getCharId(), player_cangjian->getCharId(), "破重围", 5, player_tiance->getCounterDamage(), player_cangjian->getSufferDamage(), fight_dairy_count++);
										if (player_bufflist2[3] != 0){//徐如林buff的林状态，打出伤害回复1点血量
											player_tiance->addHp(1);
											m_player2_hp.Format("%d", player_tiance->getHp());
										}
										player2_cd_record[nSel_player2] = 8;//技能冷却时间
										player_tiance->subAct(2.5);//释放该技能消耗的行动力
									}
									else{
										MessageBox("该技能释放需要在骑乘状态下才能释放！");
									}
								}
							}
							break;
				}
				default:MessageBox("请选择技能！");
				}
				//放在这里刷新的原因是在这个地方已经有技能进行了正确的释放，所以可以在这个地方刷新

				//m_player2_act.Format("%.1f", player_tiance->getAct());
				skillRemainCD2(nSel_player2);
				if (player_bufflist2[0] == 1){
					m_player2_horse_status.Format("骑乘");
				}
				else
				{
					m_player2_horse_status.Format("未骑乘");
				}

			}
			else{
				MessageBox("该技能本回合已释放，无法释放其他技能！");
			}
		}
		else{
			MessageBox("没选中技能！");
		}
	}
	else{
		MessageBox("不是你的行动回合！");
	}
	m_player2_act.Format("%.1f", player_tiance->getAct());
	m_player2_hp.Format("%d", player_tiance->getHp());
	m_player1_hp.Format("%d", player_cangjian->getHp());
	
	if (player_cangjian->getHp() <= 0)
		MessageBox("李承恩胜利！");
	UpdateData(FALSE);
}

//藏剑结束回合，并对天策行动力进行补满，重置技能释放记录，重置技能选择
void CCardHeroView::OnBnClickedEnd()
{
	// TODO:  在此添加控件通知处理程序代码
	if (player_cangjian->getActRight() == 1){
		player_cangjian->setActRight(0);//取消藏剑行动权限
		player_tiance->setActRight(1);//设置天策行动权限
		if (player_tiance->getStatus() == 0)
			player_tiance->setAct(BASIC_ACT);//未骑乘则行动力为初始3点
		else
			player_tiance->setAct(BASIC_ACT + 1);//骑乘状态下补满至3点

		for (int i = 0; i < 13; i++){//对天策技能CD进行修改
			if (player2_cd_record[i] > 0){
				player2_cd_record[i]--;
			}
		}

		if (player_bufflist2[1] != 0){//对烈风进行判定
			player_tiance->addAct(1);
			//player_bufflist2[1]--;
			//refreshBuffList2();
		}

		if (player_bufflist2[16] != 0){//对醉月进行判定
			player_tiance->subAct(1);
			player_bufflist2[16]--;
			refreshBuffList2();
		}

		if (player_bufflist2[17] != 0){//对惊涛进行判定
			player_tiance->subAct(0.5);
			player_bufflist2[17]--;
			refreshBuffList2();
		}

		

		if (player_bufflist2[2] != 0){//对疾驰进行判定
			player_tiance->addAct(1);
			player_bufflist2[2]--;
			refreshBuffList2();
		}

		if (player_bufflist2[3] != 0){//对林进行判定
			player_bufflist2[3]--;
			refreshBuffList2();
		}

		if (player_bufflist2[4] != 0){//对林进行判定
			player_bufflist2[4]--;
			refreshBuffList2();
		}
		
		

		fight_round = "——————第";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "回合——————";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);
		for (int i = 0; i < 12; i++)
			player2_skill_record[i] = 0;//所有技能释放记录重置
		player2_skill_record[12] = 0;//多了一个技能，全部都重置
		nSel_player2 = -1;
		refreshBuffList2();
	}
	else
		MessageBox("不是你的回合结束什么？");
	m_player2_act.Format("%.1f", player_tiance->getAct());//刷新行动力
	UpdateData(FALSE);
}

//天策结束回合，并对藏剑行动力进行补满
void CCardHeroView::OnBnClickedEnd2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (player_tiance->getActRight() == 1){
		player_cangjian->setActRight(1);//设置藏剑行动权限
		player_tiance->setActRight(0);//取消天策行动权限

		if (player_bufflist1[2] > 0){//对藏剑的云体进行操作
			player_bufflist1[2]--;
			if (player_bufflist1[2] == 0){
				player_cangjian->setSufferDamage(0);
				player_cangjian->addJianQi(3);
				refreshBuffList1();
			}
		}
		
		if (player_bufflist2[1] != 0){//对烈风进行判定
			player_bufflist2[1]--;
			refreshBuffList2();
		}

		if (player_bufflist1[3] > 0){//对藏剑的泉凝月进行操作
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

		if (boolDamage == 0){//对致伤进行判定
			toDamage = 0;
			//
		}

		
		if (player_bufflist1[11] != 0){//对致残进行判定
			player_bufflist1[11]--;
			if (player_bufflist1[11] == 0){
				player_cangjian->setSufferDamage(0);
			}
			refreshBuffList1();
		}

		if (player_bufflist1[12] != 0){//对穿进行判定
			if (player_bufflist1[12] != 0){
				player_cangjian->subAct(1);
				player_bufflist1[12]--;
			}
			refreshBuffList1();
		}

		

		if (player_bufflist1[14] != 0){//对破坚阵进行判定
			
			player_bufflist1[14]--;
			
			refreshBuffList1();
		}

		if (player_bufflist1[15] != 0){//对破风进行判定
			player_cangjian->subHp(1);
			//player_bufflist1[15]--;
			player_bufflist1[15]--;
			refreshBuffList1();
		}

		for (int i = 0; i < 12; i++){//对藏剑技能CD进行修改
			if (player1_cd_record[i] > 0){
				player1_cd_record[i]--;
			}
		}


		if (player_tiance->getStatus() == 0)
			player_tiance->setAct(BASIC_ACT);//未骑乘则行动力为初始3点
		else
			player_tiance->setAct(BASIC_ACT + 1);//骑乘状态下补满至3点
		/*对战斗日志进行操作*/
		fight_round = "——————第";
		round_temp.Format("%d", ++round);
		if (round < 10){
			fight_round += " ";
			fight_round += round_temp;
		}
		else
			fight_round += round_temp;
		fight_round += "回合——————";
		fight_dairybox.InsertString(fight_dairy_count++, fight_round);

		/*对藏剑进行初始操作*/
		if (player_cangjian->getStatus() == 0)
			player_cangjian->setAct(BASIC_ACT + 1);//问水诀下行动力补满至4点
		else
			player_cangjian->setAct(BASIC_ACT);//山居剑意下补满至3点
		for (int i = 0; i < 12; i++)//重置藏剑技能释放记录
			player1_skill_record[i] = 0;


		c_jianqi = 0;//重置剑气变化记录
		nSel_player1 = -1;//重置技能选择
		player_cangjian->subJianQi(1);
		m_player1_power.Format("%d", player_cangjian->getJianQi());
		m_player1_act.Format("%.1f", player_cangjian->getAct());
		m_player1_hp.Format("%d", player_cangjian->getHp());
		m_player2_act.Format("%.1f", player_tiance->getAct());
		UpdateData(FALSE);
	}
	else
		MessageBox("不是你的回合结束什么？");
}


// 战斗日志输出
void CCardHeroView::outFightDairy(int player1_id, int player2_id, CString skill_name, int basic_damage, int count_damage,int suff_damage, int line_dairy)
{
	CString temp;
	CString damage_temp;
	int sub_damage;

	if (player_cangjian->getCharId() == player1_id){//判断这个技能由藏剑打出
		temp += "叶英";
		if (player_cangjian->getCharId() == player2_id){//判断对自身释放
			temp += "释放了";
			temp += skill_name;
			temp += "。";
		}
		else{
			temp += "对李承恩释放了";
			temp += skill_name;
			if (basic_damage != 0){//判断有有伤害，藏剑对天策打伤害
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
				temp += "，并造成了";
				temp += damage_temp;
				temp += "点伤害。";
			}
			else//没有伤害
				temp += "。";
		}
	}
	else{//天策打出技能
		temp += "李承恩";
		if (player_tiance->getCharId() == player2_id){//判断对自身释放
			temp += "释放了";
			temp += skill_name;
			temp += "。";
		}
		else{
			temp += "对叶英释放了";
			temp += skill_name;
			if (basic_damage != 0){//判断有伤害，天策对藏剑打伤害
				if (player_cangjian->getShield() > 0){
					if ((player_cangjian->getShield() - basic_damage + count_damage - suff_damage) > 0){//伤害全部由盾抵消
						player_cangjian->subShield(basic_damage - count_damage + suff_damage);
						temp += "，由泉凝月抵消了";
						damage_temp.Format("%d", basic_damage - count_damage + suff_damage);
						temp += damage_temp;
						temp += "点伤害。";
					}
					else {//没有全部被抵消
						sub_damage = basic_damage - count_damage + suff_damage - player_cangjian->getShield();
						player_cangjian->setShield(0);
						player_bufflist1[3] = 0;
						temp += "，由泉凝月抵消了";
						damage_temp.Format("%d", player_cangjian->getShield());
						temp += damage_temp;
						temp += "点伤害，";
						temp += "，并造成了";
						damage_temp.Format("%d", sub_damage);
						player_cangjian->subHp(basic_damage + count_damage - suff_damage);
						m_player1_hp.Format("%d", player_cangjian->getHp());
						temp += damage_temp;
						temp += "点伤害。";
					}
				}
				else{
					player_cangjian->subHp(basic_damage + count_damage - suff_damage);
					m_player1_hp.Format("%d", player_cangjian->getHp());
					damage_temp.Format("%d", basic_damage + count_damage - suff_damage);
					temp += "，并造成了";
					temp += damage_temp;
					temp += "点伤害。";
				}
			}
			else//没有伤害
				temp += "。";
		}
	}
	fight_dairybox.InsertString(line_dairy, temp);
	UpdateData(FALSE);
}


// 刷新玩家1的buff列表
void CCardHeroView::refreshBuffList1()
{
	int n = 0;
	m_player1_buff_list.ResetContent();
	for (int i = 0; i < 20; i++){
		switch (i){
		case 0:{
				   if (player_bufflist1[i] == 0)
					   m_player1_buff_list.InsertString(n++, "问水诀");
				   else
					   m_player1_buff_list.InsertString(n++, "山居剑意");
				   break;
		}
		case 1:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "凤鸣");  
				   break;
		}
		case 2:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "云体");
				   break;
		}
		case 3:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "泉凝月");
				   break;
		}
		case 4:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "空");
				   break;
		}
		case 5:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "空");
				   break;
		}
		case 6:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "空");
				   break;
		}
		case 7:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "空");
				   break;
		}
		case 8:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "空");
				   break;
		}
		case 9:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "空");
				   break;
		}
		case 10:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "致伤");
				   break;
		}
		case 11:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "致残");
				   break;
		}
		case 12:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "穿");
				   break;
		}
		case 13:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "霹雳");
				   break;
		}
		case 14:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "破坚阵");
				   break;
		}
		case 15:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "破风");
				   break;
		}
		case 16:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "醉月");
				   break;
		}
		case 17:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "惊涛");
				   break;
		}
		case 18:{
				   if (player_bufflist1[i] != 0)
					   m_player1_buff_list.InsertString(n++, "不工");
				   break;
		}
		}
	}
}



// 刷新玩家2的buff列表
void CCardHeroView::refreshBuffList2()
{
	int n = 0;
	m_player2_buff_list.ResetContent();
	for (int i = 0; i < 20; i++){
		switch (i){
		case 0:{
				   if (player_bufflist2[i] == 0)
					   m_player2_buff_list.InsertString(n++, "未骑乘");
				   else
					   m_player2_buff_list.InsertString(n++, "骑乘");
				   break;
		}
		case 1:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "烈风");
				   break;
		}
		case 2:{
				   if (player_bufflist2[i] != 0 && player_bufflist2[i] != 4)
					   m_player2_buff_list.InsertString(n++, "疾驰");
				   break;
		}
		case 3:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "林");
				   break;
		}
		case 4:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "山");
				   break;
		}
		case 5:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "空");
				   break;
		}
		case 6:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "空");
				   break;
		}
		case 7:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "空");
				   break;
		}
		case 8:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "空");
				   break;
		}
		case 9:{
				   if (player_bufflist2[i] != 0)
					   m_player2_buff_list.InsertString(n++, "空");
				   break;
		}
		case 10:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "致伤");
					break;
		}
		case 11:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "致残");
					break;
		}
		case 12:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "穿");
					break;
		}
		case 13:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "霹雳");
					break;
		}
		case 14:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "破坚阵");
					break;
		}
		case 15:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "破风");
					break;
		}
		case 16:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "醉月");
					break;
		}
		case 17:{
					if (player_bufflist2[i] != 0){
							m_player2_buff_list.InsertString(n++, "惊涛");
					}
					break;
		}
		case 18:{
					if (player_bufflist2[i] != 0)
						m_player2_buff_list.InsertString(n++, "不工");
					break;
		}
		}
	}
}


// 显示玩家1的技能剩余cd
void CCardHeroView::skillRemainCD1(int skill_id)
{
	CString temp;
	if (player1_cd_record[skill_id] - 1  == -1)
		m_remain_cd1.Format("可释放");
	else
		m_remain_cd1.Format("%d", player1_cd_record[skill_id] - 1);
}


// 对角色状态进行说明
void CCardHeroView::showBuffComment(CString skill_name)
{
	if (skill_name == "山居剑意"){
		m_player1_buff_comment.Format("所受伤害增加1点，并不受任何控制");
	}
	else if (skill_name == "问水诀"){
		m_player1_buff_comment.Format("行动力增加1点");
	}
	else if (skill_name == "云体"){
		m_player1_buff_comment.Format("所有所受伤害减少1点，在失去本状态的回合，得到2点剑气");
	}
	else if (skill_name == "凤鸣"){
		m_player1_buff_comment.Format("使下一技能增加1点伤害");
	}
	else if (skill_name == "泉凝月"){
		m_player1_buff_comment.Format("持续3回合的盾，最多可抵挡共5点伤害。");
	}
	else if (skill_name == "致伤"){
		m_player1_buff_comment.Format("3个致伤变为1个致残");
	}
	else if (skill_name == "致残"){
		m_player1_buff_comment.Format("所受伤害增加一点");
	}
	else if (skill_name == "穿"){
		m_player1_buff_comment.Format("状态消失时令对方在该回合的开始阶段损失1点行动力");
	}
	else if (skill_name == "霹雳"){
		m_player1_buff_comment.Format("使对方所受的治疗量变为50%");
	}
	else if (skill_name == "破坚阵"){
		m_player1_buff_comment.Format("令对方3回合无法行动");
	}
	else if (skill_name == "醉月"){
		m_player1_buff_comment.Format("回合的开始阶段损失1点行动力");
	}
	else if (skill_name == "惊涛"){
		m_player1_buff_comment.Format("回合的开始阶段损失0.5点行动力");
	}
}


void CCardHeroView::OnLbnSelchangeBuffList1()
{
	// TODO:  在此添加控件通知处理程序代码
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
		m_remain_cd2.Format("可释放");
	else
		m_remain_cd2.Format("%d", player2_cd_record[skill_id] - 1);
	UpdateData(false);
}
