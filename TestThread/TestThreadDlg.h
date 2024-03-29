﻿
// TestThreadDlg.h: 헤더 파일
//

#pragma once

#define MESSAGE_Thread_1 WM_USER
#define MESSAGE_Thread_2 WM_USER+1
#define MESSAGE_Thread_Para WM_USER+2
#define MESSAGE_Thread_Para_2 WM_USER+3
// CTestThreadDlg 대화 상자

typedef struct
{
	int index;
	HANDLE param;
}SEARCHNVTTHREADARGUMENT;




class CTestThreadDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestThreadDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTTHREAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnThread1();
	
	CEdit m_ED_test;
	afx_msg void OnBnClickedBtnShutdown1();
	bool m_bThraed1 = false;
	afx_msg void OnBnClickedBtnThread2();

	bool m_bThraed2 = false;

	afx_msg void OnBnClickedBtnShutdown2();
	afx_msg void OnBnClickedBtnSleep();
	afx_msg void OnBnClickedBtnWait();

	void Wait(DWORD dwMillisecond);                 //https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=tipsware&logNo=221651145302
	void Wait_2(DWORD dwMillisecond);               //시스템이 시작한 지 49.7일이 지나는 시점에 오버플로가 발생하여 문제가 생기기 때문에 GetTickCount64 함수

	CWinThread* m_pThread_1;
	bool m_flag_threadrun_1;
	bool m_flag_threadrun_2;
	CWinThread* m_pThread_2;

	afx_msg void OnBnClickedButtonAfxbeginthread2();


	LRESULT WriteThreadTest_1(WPARAM wParam, LPARAM lParam);

	LRESULT WriteThreadTest_2(WPARAM wParam, LPARAM lParam);

	LRESULT WriteThreadTest_1_Parameter(WPARAM wParam, LPARAM lParam);
	LRESULT WriteThreadTest_2_Parameter(WPARAM wParam, LPARAM lParam);

	void TestThread(int n);

	void TestTheadSync(int n);

	afx_msg void OnBnClickedButtonAfxbeginthread1();
	afx_msg void OnBnClickedButtonParameter();
	afx_msg void OnBnClickedButtonParameter2();
	CEdit m_Edit_2;
	afx_msg void OnBnClickedButtonThreadEnd();
	afx_msg void OnBnClickedBtnClear();

	bool m_isWorkingThread;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBtnShutdown();
};

extern  CTestThreadDlg *pTestThead;