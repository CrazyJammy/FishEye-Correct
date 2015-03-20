
// FisheyeVideoWarpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FisheyeVideoWarp.h"
#include "FisheyeVideoWarpDlg.h"
#include "afxdialogex.h"
#include "ImgWarp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ImgWarp IW;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFisheyeVideoWarpDlg �Ի���




CFisheyeVideoWarpDlg::CFisheyeVideoWarpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFisheyeVideoWarpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFisheyeVideoWarpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, mSlider);
}

BEGIN_MESSAGE_MAP(CFisheyeVideoWarpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOpen, &CFisheyeVideoWarpDlg::OnBnClickedOpen)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CFisheyeVideoWarpDlg::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CFisheyeVideoWarpDlg ��Ϣ�������

BOOL CFisheyeVideoWarpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//IW.theta = 120;
	mSlider.SetRange(120,180);
	mSlider.SetTicFreq(5);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFisheyeVideoWarpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFisheyeVideoWarpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFisheyeVideoWarpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CFisheyeVideoWarpDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CFileDialog dlg(TRUE);
	//��ͼ�񣬰�OKȷ�ϣ����򷵻�
	if(dlg.DoModal()!=IDOK)
	{
		MessageBox("��ʧ�ܣ������ԣ�");
		return;
	}
	//�رմ�����ʾ
	GetDlgItem(IDC_ORG)->ShowWindow(FALSE);
	GetDlgItem(IDC_DST)->ShowWindow(FALSE);
	//�򿪴�����ʾ,�൱�ڰѴ�������,���Picture�ؼ��Ĳ���
	GetDlgItem(IDC_ORG)->ShowWindow(TRUE); 
	GetDlgItem(IDC_DST)->ShowWindow(TRUE); 
	//��ͼ���·��
	mPath = dlg.GetPathName();
	CWinThread * pThread;
	pThread =AfxBeginThread(threadFunction,(LPVOID) this);
}

UINT CFisheyeVideoWarpDlg::threadFunction(LPVOID pParam)
{

	CFisheyeVideoWarpDlg* pDlg = (CFisheyeVideoWarpDlg*)pParam;


	//����Ƶ�ļ�����ʵ���ǽ���һ��VideoCapture�ṹ
	//VideoCapture cap(pDlg->mPath);
	//����Ƿ�������:�ɹ���ʱ��isOpened����ture
	//pDlg->frameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);
	/*if(!cap.isOpened())
	{
		pDlg->MessageBox("��ȡ��Ƶʧ�ܣ�");
		return 0;
	}
	for(int i = 0;i < pDlg->frameNumber;++i)
	{
		Mat frame;
		cap >> frame;	i	
		
	}*/
	Mat orgImg = imread(pDlg->mPath);
	pDlg->ShowImage(orgImg,IDC_ORG);
	Mat dstImg;
   // const uint theta = 120;
	CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)pDlg->GetDlgItem(IDC_SLIDER1);
	IW.theta = pSlidCtrl->GetPos();  //ȡ�õ�ǰλ��ֵ 
	uint z = orgImg.cols / tan(CV_PI*IW.theta/360);

	//z = 100;

	//IW.ImageWarp(orgImg,dstImg);
	IW.Plane2Sphere(orgImg,dstImg,z);
	pDlg->ShowImage(dstImg,IDC_DST);

	waitKey(0);
	return 0;
}

void CFisheyeVideoWarpDlg::ShowImage(Mat img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC(); 
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;  
	GetDlgItem(ID)->GetClientRect(&rect); 
	IplImage image=img;
	CvvImage cimg;  
	cimg.CopyOf(&image ); // ����ͼƬ
	cimg.DrawToHDC( hDC, &rect ); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC( pDC );
}


void CFisheyeVideoWarpDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
