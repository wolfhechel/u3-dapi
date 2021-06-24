// DAPI MFCDlg.h : header file
//

#pragma once

#include "DapiBase.h"


// CDAPIMFCDlg dialog
class CDAPIMFCDlg : public CDialog, CDapiBase
{
// Construction
public:
	CDAPIMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DAPIMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// functions mapped to device events
	afx_msg LRESULT OnDeviceConnected(WPARAM hDevice, LPARAM unused);
	afx_msg LRESULT OnDeviceDisconnected(WPARAM hDevice, LPARAM unused);
	afx_msg LRESULT OnDeviceUpdated(WPARAM hDevice, LPARAM unused);

// Implementation
protected:

	void UpdateDrives(HDEVICE hDevice);
	void CheckandSetCookie(HDEVICE hDevice);

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

};
