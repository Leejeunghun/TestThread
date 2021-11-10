
// TestThreadDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "TestThread.h"
#include "TestThreadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestThreadDlg 대화 상자

void Wait_3(DWORD dwMillisecond)
{
	MSG msg_1;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg_1, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg_1);
			DispatchMessage(&msg_1);
		}
	}
}

CTestThreadDlg::CTestThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTTHREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ED_test);
	DDX_Control(pDX, IDC_EDIT2, m_Edit_2);
}
BEGIN_MESSAGE_MAP(CTestThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_Thread1, &CTestThreadDlg::OnBnClickedBtnThread1)
	ON_BN_CLICKED(IDC_BTN_Shutdown1, &CTestThreadDlg::OnBnClickedBtnShutdown1)
	ON_BN_CLICKED(IDC_BTN_Thread2, &CTestThreadDlg::OnBnClickedBtnThread2)
	ON_BN_CLICKED(IDC_BTN_Shutdown2, &CTestThreadDlg::OnBnClickedBtnShutdown2)
	ON_BN_CLICKED(IDC_BTN_SLEEP, &CTestThreadDlg::OnBnClickedBtnSleep)
	ON_BN_CLICKED(IDC_BTN_WAIT, &CTestThreadDlg::OnBnClickedBtnWait)
	ON_BN_CLICKED(IDC_BUTTON_AfxBeginThread_2, &CTestThreadDlg::OnBnClickedButtonAfxbeginthread2)
	ON_MESSAGE(MESSAGE_Thread_1, &CTestThreadDlg::WriteThreadTest_1)
	ON_MESSAGE(MESSAGE_Thread_2, &CTestThreadDlg::WriteThreadTest_2)
	ON_MESSAGE(MESSAGE_Thread_Para, &CTestThreadDlg::WriteThreadTest_1_Parameter)
	ON_MESSAGE(MESSAGE_Thread_Para_2, &CTestThreadDlg::WriteThreadTest_2_Parameter)
	ON_BN_CLICKED(IDC_BUTTON_AfxBeginThread_1, &CTestThreadDlg::OnBnClickedButtonAfxbeginthread1)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETER, &CTestThreadDlg::OnBnClickedButtonParameter)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETER_2, &CTestThreadDlg::OnBnClickedButtonParameter2)
	ON_BN_CLICKED(IDC_BUTTON_Thread_END, &CTestThreadDlg::OnBnClickedButtonThreadEnd)
	ON_BN_CLICKED(IDC_BTN_Clear, &CTestThreadDlg::OnBnClickedBtnClear)

	ON_BN_CLICKED(IDC_BUTTON2, &CTestThreadDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTN_Shutdown, &CTestThreadDlg::OnBnClickedBtnShutdown)
END_MESSAGE_MAP()


// CTestThreadDlg 메시지 처리기

CTestThreadDlg* pTestThead = NULL;

BOOL CTestThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	pTestThead = this;
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.





void CTestThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI ThreadFunc(PVOID pvParam)
{
	DWORD dwResult = 0;
	CString str;
	while (1)
	{
		str = "1 번 A \r\n";
		pTestThead->m_ED_test.ReplaceSel(str);
		pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

	//	Wait_3(10000);
		Sleep(1000);
		str = "1 번 B \r\n";
		pTestThead->m_ED_test.ReplaceSel(str);
		pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

	}

	return (dwResult);
}

void CTestThreadDlg::OnBnClickedBtnThread1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bThraed1 = true;
	DWORD dwThreadID =1;
	HANDLE hThread = CreateThread(NULL, 0, ThreadFunc,this,0,&dwThreadID);

}




void CTestThreadDlg::OnBnClickedBtnShutdown1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bThraed1 = false;
	//TerminateThread(ThreadFunc, -1);
}



DWORD WINAPI ThreadFunc2(PVOID pvParam)
{
	DWORD dwResult = 0;
	CString str;

	while (1)
	{
		str = "2 번 C \r\n";
		pTestThead->m_ED_test.ReplaceSel(str);
		pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
	//	Wait_3(10000);
		Sleep(1000);

		str = "2 번 D \r\n";
		pTestThead->m_ED_test.ReplaceSel(str);
		pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

	}
	return (dwResult);
}

HANDLE hThread_2;
void CTestThreadDlg::OnBnClickedBtnThread2()
{
	m_bThraed1 = true;
	DWORD dwThreadID = 1;
	m_bThraed2 = true;
	while (m_bThraed2)
	{
//		hThread_2 = CreateThread(NULL, 0, ThreadFunc2, this, 0, &dwThreadID);
//		Sleep(20000);
		break;
	}
	hThread_2 = CreateThread(NULL, 0, ThreadFunc2, this, 0, &dwThreadID);
}


void CTestThreadDlg::OnBnClickedBtnShutdown2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bThraed2 = false;
	::TerminateThread(ThreadFunc2, -1);
}


void CTestThreadDlg::OnBnClickedBtnSleep()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	str = "1 번 A \r\n";
	pTestThead->m_ED_test.ReplaceSel(str);
	pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

	Wait(10000);

	str = "1 번 B \r\n";
	pTestThead->m_ED_test.ReplaceSel(str);
	pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

}


void CTestThreadDlg::OnBnClickedBtnWait()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	str = "2 번 C \r\n";
	pTestThead->m_ED_test.ReplaceSel(str);
	pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

	Wait_2(10000);
	str = "2 번 D \r\n";
	pTestThead->m_ED_test.ReplaceSel(str);
	pTestThead->m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
}

void CTestThreadDlg::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount64();

	while (GetTickCount64() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}




void CTestThreadDlg::Wait_2(DWORD dwMillisecond)
{
	MSG msg_1;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg_1, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg_1);
			DispatchMessage(&msg_1);
		}
	}
}


UINT ThreadTest_1(LPVOID param)
{
	CTestThreadDlg* pMain = (CTestThreadDlg*)param;

	PostMessage(pMain->m_hWnd, MESSAGE_Thread_1, NULL, NULL);

	return true;
}


UINT ThreadTest_1_Parameter(LPVOID param)
{
	SEARCHNVTTHREADARGUMENT* item = (SEARCHNVTTHREADARGUMENT*)param;
	CTestThreadDlg* pDlg = (CTestThreadDlg*)item->param;

	int n = item->index;

	int* piNumber = new int(n); //new 해야함.

	pDlg->TestThread(n);
//	PostMessage(pDlg->m_hWnd, MESSAGE_Thread_1, NULL, NULL);
	
	return true;
}


UINT ThreadTest_1_Parameter_Post(LPVOID param)
{
	SEARCHNVTTHREADARGUMENT* item = (SEARCHNVTTHREADARGUMENT*)param;
	CTestThreadDlg* pDlg = (CTestThreadDlg*)item->param;

	int n = item->index;

	int* piNumber = new int(n); //new 해야함.

//	pDlg->TestThread(n);
//	PostMessage(pDlg->m_hWnd, MESSAGE_Thread_Para, NULL, NULL);
	::PostMessage(pDlg->m_hWnd, MESSAGE_Thread_Para, (WPARAM)0, (LPARAM)item);      //WPARAM 핸들 또는 정수를 받아들일떄 사용     //LPARAM 포인터 전달할떄 사용하는 함수

	return true;
}

UINT ThreadTest_End(LPVOID param)
{
	SEARCHNVTTHREADARGUMENT* item = (SEARCHNVTTHREADARGUMENT*)param;
	CTestThreadDlg* pDlg = (CTestThreadDlg*)item->param;

	int n = item->index;

	int* piNumber = new int(n); //new 해야함.

	pDlg->TestTheadSync(n);
	//	PostMessage(pDlg->m_hWnd, MESSAGE_Thread_1, NULL, NULL);

	return true;
}

UINT ThreadTest_2_Parameter(LPVOID param)
{
	SEARCHNVTTHREADARGUMENT* item = (SEARCHNVTTHREADARGUMENT*)param;
	CTestThreadDlg* pDlg = (CTestThreadDlg*)item->param;

	int n = item->index;

	int* piNumber = new int(n); //new 해야함.

	pDlg->TestThread(n);

	//	PostMessage(pDlg->m_hWnd, MESSAGE_Thread_1, NULL, NULL);

	return true;
}

UINT ThreadTest_2(LPVOID param)
{
	CTestThreadDlg* pMain = (CTestThreadDlg*)param;

	PostMessage(pMain->m_hWnd, MESSAGE_Thread_2, NULL, NULL);

	return true;
}


void CTestThreadDlg::OnBnClickedButtonAfxbeginthread1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pThread_1 = AfxBeginThread(ThreadTest_1, this);
}


void CTestThreadDlg::OnBnClickedButtonAfxbeginthread2()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pThread_2 = AfxBeginThread(ThreadTest_2, this);
}



LRESULT CTestThreadDlg::WriteThreadTest_1(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str = "1 번 C \r\n";
	m_ED_test.ReplaceSel(str);
	m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
	return 0;
}


LRESULT CTestThreadDlg::WriteThreadTest_2(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str = "2번 C \r\n";
	m_ED_test.ReplaceSel(str);
	m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
	return 0;
}

LRESULT CTestThreadDlg::WriteThreadTest_1_Parameter(WPARAM wParam, LPARAM lParam)
{

	int* pstrString = (int*)lParam;
	int strString = *pstrString;

	CString str;
	str.Format("%d \r\n", strString);
	while (m_flag_threadrun_1)
	{
		if (strString == 10)
		{
			m_Edit_2.ReplaceSel(str);
			m_Edit_2.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
		}
		else
		{
			m_ED_test.ReplaceSel(str);
			m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

		}

		Wait(300);
	}
	return 0;
}

LRESULT CTestThreadDlg::WriteThreadTest_2_Parameter(WPARAM wParam, LPARAM lParam)
{

	int* pstrString = (int*)lParam;
	int strString = *pstrString;

	CString str;
	str.Format("%d \r\n", strString);
	while (1)
	{
		if (strString == 10)
		{
			m_Edit_2.ReplaceSel(str);
			m_Edit_2.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
		}
		else
		{
			m_ED_test.ReplaceSel(str);
			m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

		}

		Wait(300);
	}
	return 0;
}

void CTestThreadDlg::TestThread(int n)
{

	CString str;
	str.Format("%d \r\n", n);
	while (1)
	{
		if (n == 10)
		{
			m_Edit_2.ReplaceSel(str);
			m_Edit_2.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
		}
		else
		{
			m_ED_test.ReplaceSel(str);
			m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

		}

		Wait(300);
	}
	return ;
}

void CTestThreadDlg::TestTheadSync(int n)
{

	CString str;
	str.Format("%d \r\n", n);

	if (n == 10)
	{
		m_flag_threadrun_1 = true;
	}
	else if(n == 20)
	{
		m_flag_threadrun_2 = true;
	}

	for (int i = 0; i < n; i++)
	{
		if (n == 10)
		{
			m_Edit_2.ReplaceSel(str);
			m_Edit_2.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동
		}
		else
		{
			m_ED_test.ReplaceSel(str);
			m_ED_test.SetSel(-2, -1);  // 커서를 에디트박스 끝으로 이동

		}

		Wait(300);

	}

	if (n == 10)
	{
		m_flag_threadrun_1 = false;
	}
	else if(n == 20)
	{
		m_flag_threadrun_2 = false;
	}

	return;
}




void CTestThreadDlg::OnBnClickedButtonParameter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SEARCHNVTTHREADARGUMENT* test = new SEARCHNVTTHREADARGUMENT;
	test->index = 10;
	test->param = this;

	m_pThread_1 = AfxBeginThread(ThreadTest_1_Parameter, (LPVOID)test);
	m_pThread_1->m_bAutoDelete = FALSE;




}


void CTestThreadDlg::OnBnClickedButtonParameter2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SEARCHNVTTHREADARGUMENT* test_2 = new SEARCHNVTTHREADARGUMENT;
	test_2->index = 7;
	test_2->param = this;

	m_pThread_2 = AfxBeginThread(ThreadTest_2_Parameter, (LPVOID)test_2);
	m_pThread_2->m_bAutoDelete = FALSE;
}


void CTestThreadDlg::OnBnClickedButtonThreadEnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SEARCHNVTTHREADARGUMENT* test = new SEARCHNVTTHREADARGUMENT;
	test->index = 10;
	test->param = this;

	m_pThread_1 = AfxBeginThread(ThreadTest_End, (LPVOID)test);
	m_flag_threadrun_1 == true;

	SEARCHNVTTHREADARGUMENT* test_2 = new SEARCHNVTTHREADARGUMENT;
	test_2->index = 20;
	test_2->param = this;

	m_pThread_2 = AfxBeginThread(ThreadTest_End, (LPVOID)test_2);
	m_flag_threadrun_2 == true;

	DWORD dwexitcode = 0;
	static TCHAR szTextBuffer[4096];
	DWORD dwErrorCode = 0;
	/* ... */

	while (1)
	{
		//bool result = GetExitCodeThread(m_pThread_1, &dwErrorCode);

		//if (dwErrorCode == STILL_ACTIVE) {
		//	_stprintf(szTextBuffer, TEXT("WM_USER: hThread = %08p, dwErrorCode = STILL_ACTIVE  Flag = %d \n"), m_pThread_1, result);
		//}
		//else {
		//	_stprintf(szTextBuffer, TEXT("WM_USER: hThread = %08p, dwErrorCode = %08lx Flag = %d  \n"), m_pThread_1, dwErrorCode, result);
		//}
		//Wait(300);
		//OutputDebugString(szTextBuffer);

		if (m_flag_threadrun_1 == true || m_flag_threadrun_2 ==true ) {
			_stprintf(szTextBuffer, TEXT("WM_USER: hThread = %08p, dwErrorCode = STILL_ACTIVE  \n"), m_pThread_1);
			OutputDebugString(szTextBuffer);
			Wait(300);
		}
		else
		{
			_stprintf(szTextBuffer, TEXT("WM_USER: hThread = %08p,  \n"), m_pThread_1);
			OutputDebugString(szTextBuffer);
			AfxMessageBox("완료");
			break;
		}

	}
}


void CTestThreadDlg::OnBnClickedBtnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Edit_2.SetSel(0, -1, TRUE);
	m_Edit_2.Clear();
	m_ED_test.SetSel(0, -1, TRUE);
	m_ED_test.Clear();
}




void CTestThreadDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SEARCHNVTTHREADARGUMENT* test = new SEARCHNVTTHREADARGUMENT;
	test->index = 10;
	test->param = this;

	m_pThread_1 = AfxBeginThread(ThreadTest_1_Parameter_Post, (LPVOID)test); // LPVOID 란 long pointer void 형이 정해지지 않은 타비
	m_flag_threadrun_1 = true;
}


void CTestThreadDlg::OnBnClickedBtnShutdown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_flag_threadrun_1 = false;
	WaitForSingleObject(m_pThread_1->m_hThread, 5000);
	
}
