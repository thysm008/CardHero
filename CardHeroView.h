
// CardHeroView.h : CCardHeroView 类的接口
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#define SEL1 "选择1"
#define SEL2 "选择2"

class CCardHeroView : public CFormView
{
protected: // 仅从序列化创建
	CCardHeroView();
	DECLARE_DYNCREATE(CCardHeroView)

public:
	enum{ IDD = IDD_CARDHERO_FORM };

// 特性
public:
	CCardHeroDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CCardHeroView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//战斗初始化
	afx_msg void OnSingleVs();
	CString m_charid1;
	// 玩家1血量
	CString m_player1_hp;
	// 玩家1行动点数
	CString m_player1_act;
	// 玩家1职业特色能量值，-1表示该职业无特色能量
	CString m_player1_power;
	// 玩家2行动力
//	CString m_player2_act;
	// 玩家2血量值
	CString m_player2_hp;
	CString m_charid2;
	// 玩家2骑乘状态
	CString m_player2_horse_status;
	// 玩家1技能列表
	CListBox player1_skillbox;
	// 玩家2技能栏
	CListBox player2_skillbox;
	afx_msg void OnLbnSelchangeSkillList();
	afx_msg void OnLbnSelchangeSkillList2();
	// 技能说明打印
	CString m_skill_comment;
	// 玩家1技能消耗
	CString m_player1_skill_cost;
	// 玩家1技能行动力消耗
	CString m_player1_act_cost;
	// 玩家1技能冷却时间
	CString m_player1_skill_cd;
	// 玩家1技能释放要求
	CString m_player1_skill_status;
	// 玩家2技能cd
	CString m_player2_skill_cd;
	// 玩家2技能状态
	CString m_player2_status;
	// 玩家2技能行动力消耗
	CString m_player2_act_cost;
	// 玩家2技能说明
	CString m_skill2_comment;
	int nSel_player1;
	int nSel_player2;
	int round;
	int fight_dairy_count = 0;
	CString fight_round;
	CString round_temp;
	afx_msg void OnBnClickedAction();
	afx_msg void OnBnClickedAction2();
	// 战斗日志
	CListBox fight_dairybox;
	// 玩家1状态说明
//	CEdit m_player1_buff_comment;
	// 玩家2状态说明
//	CEdit m_player2_buff_comment;
	// 玩家1状态列表
	CListBox m_player1_buff_list;
	// 玩家2状态列表
	CListBox m_player2_buff_list;
	//玩家1状态数量
	int m_player1_buff_count;
	//玩家2状态数量
	int m_player2_buff_count;
	//啸日位置
	int index_xiaori;
	//凤鸣位置
	int index_fengming;
	//玩家1技能释放记录
	int player1_skill_record[12];
	//玩家2技能释放记录
	int player2_skill_record[12];
	//剑气变化
	int c_jianqi;
	//控制增益buff时间
	//buff使用次数
	int buff_times;
	//凤鸣
	int buff_fengming;
	//玩家1buff列表
	int player_bufflist1[20];
	//玩家2buff列表
	int player_bufflist2[20];
	afx_msg void OnBnClickedEnd();
	afx_msg void OnBnClickedEnd2();
	// 战斗日志输出，count_damage:正数为伤害减免，负数为伤害加深
	void outFightDairy(int player1_id, int player2_id, CString skill_name, int basic_damage, int count_damage, int suff_damage,int line_dairy);
	// 刷新玩家1的buff列表
	void refreshBuffList1();
	// 刷新玩家2的buff列表
	void refreshBuffList2();
	// 玩家1技能剩余冷却时间
	CString m_remain_cd1;
	// 显示玩家1的技能剩余cd
	void skillRemainCD1(int skill_id);
	int player1_cd_record[12];
	int player2_cd_record[13];
	// 对角色状态进行说明
	void showBuffComment(CString);
	afx_msg void OnLbnSelchangeBuffList1();
	// 玩家1buff说明
	CString m_player1_buff_comment;
	void skillRemainCD2(int skill_id);
	CString m_remain_cd2;
	CString m_player2_act;
	bool Damage;
	int toDamage;
	int boolDamage;
};

#ifndef _DEBUG  // CardHeroView.cpp 中的调试版本
inline CCardHeroDoc* CCardHeroView::GetDocument() const
   { return reinterpret_cast<CCardHeroDoc*>(m_pDocument); }
#endif
