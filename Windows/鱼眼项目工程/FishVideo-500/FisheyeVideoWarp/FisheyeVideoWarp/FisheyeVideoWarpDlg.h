
// FisheyeVideoWarpDlg.h : ͷ�ļ�
//

#pragma once
#include "CvvImage.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "afxcmn.h"


using namespace std;
using namespace cv;

// CFisheyeVideoWarpDlg �Ի���
class CFisheyeVideoWarpDlg : public CDialogEx
{
// ����
public:
	CFisheyeVideoWarpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FISHEYEVIDEOWARP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOpen();
	String mPath;
	double frameNumber;
	static UINT threadFunction(LPVOID pParam);
	void ShowImage(Mat img, UINT ID);
	CSliderCtrl mSlider;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
