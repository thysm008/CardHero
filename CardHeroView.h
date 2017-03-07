
// CardHeroView.h : CCardHeroView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#define SEL1 "ѡ��1"
#define SEL2 "ѡ��2"

class CCardHeroView : public CFormView
{
protected: // �������л�����
	CCardHeroView();
	DECLARE_DYNCREATE(CCardHeroView)

public:
	enum{ IDD = IDD_CARDHERO_FORM };

// ����
public:
	CCardHeroDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CCardHeroView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//ս����ʼ��
	afx_msg void OnSingleVs();
	CString m_charid1;
	// ���1Ѫ��
	CString m_player1_hp;
	// ���1�ж�����
	CString m_player1_act;
	// ���1ְҵ��ɫ����ֵ��-1��ʾ��ְҵ����ɫ����
	CString m_player1_power;
	// ���2�ж���
//	CString m_player2_act;
	// ���2Ѫ��ֵ
	CString m_player2_hp;
	CString m_charid2;
	// ���2���״̬
	CString m_player2_horse_status;
	// ���1�����б�
	CListBox player1_skillbox;
	// ���2������
	CListBox player2_skillbox;
	afx_msg void OnLbnSelchangeSkillList();
	afx_msg void OnLbnSelchangeSkillList2();
	// ����˵����ӡ
	CString m_skill_comment;
	// ���1��������
	CString m_player1_skill_cost;
	// ���1�����ж�������
	CString m_player1_act_cost;
	// ���1������ȴʱ��
	CString m_player1_skill_cd;
	// ���1�����ͷ�Ҫ��
	CString m_player1_skill_status;
	// ���2����cd
	CString m_player2_skill_cd;
	// ���2����״̬
	CString m_player2_status;
	// ���2�����ж�������
	CString m_player2_act_cost;
	// ���2����˵��
	CString m_skill2_comment;
	int nSel_player1;
	int nSel_player2;
	int round;
	int fight_dairy_count = 0;
	CString fight_round;
	CString round_temp;
	afx_msg void OnBnClickedAction();
	afx_msg void OnBnClickedAction2();
	// ս����־
	CListBox fight_dairybox;
	// ���1״̬˵��
//	CEdit m_player1_buff_comment;
	// ���2״̬˵��
//	CEdit m_player2_buff_comment;
	// ���1״̬�б�
	CListBox m_player1_buff_list;
	// ���2״̬�б�
	CListBox m_player2_buff_list;
	//���1״̬����
	int m_player1_buff_count;
	//���2״̬����
	int m_player2_buff_count;
	//Х��λ��
	int index_xiaori;
	//����λ��
	int index_fengming;
	//���1�����ͷż�¼
	int player1_skill_record[12];
	//���2�����ͷż�¼
	int player2_skill_record[12];
	//�����仯
	int c_jianqi;
	//��������buffʱ��
	//buffʹ�ô���
	int buff_times;
	//����
	int buff_fengming;
	//���1buff�б�
	int player_bufflist1[20];
	//���2buff�б�
	int player_bufflist2[20];
	afx_msg void OnBnClickedEnd();
	afx_msg void OnBnClickedEnd2();
	// ս����־�����count_damage:����Ϊ�˺����⣬����Ϊ�˺�����
	void outFightDairy(int player1_id, int player2_id, CString skill_name, int basic_damage, int count_damage, int suff_damage,int line_dairy);
	// ˢ�����1��buff�б�
	void refreshBuffList1();
	// ˢ�����2��buff�б�
	void refreshBuffList2();
	// ���1����ʣ����ȴʱ��
	CString m_remain_cd1;
	// ��ʾ���1�ļ���ʣ��cd
	void skillRemainCD1(int skill_id);
	int player1_cd_record[12];
	int player2_cd_record[13];
	// �Խ�ɫ״̬����˵��
	void showBuffComment(CString);
	afx_msg void OnLbnSelchangeBuffList1();
	// ���1buff˵��
	CString m_player1_buff_comment;
	void skillRemainCD2(int skill_id);
	CString m_remain_cd2;
	CString m_player2_act;
	bool Damage;
	int toDamage;
	int boolDamage;
};

#ifndef _DEBUG  // CardHeroView.cpp �еĵ��԰汾
inline CCardHeroDoc* CCardHeroView::GetDocument() const
   { return reinterpret_cast<CCardHeroDoc*>(m_pDocument); }
#endif
