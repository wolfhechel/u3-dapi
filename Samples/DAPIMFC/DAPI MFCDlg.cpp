// DAPI MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DAPI MFC.h"
#include "DAPI MFCDlg.h"
#include ".\dapi mfcdlg.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDAPIMFCDlg dialog



CDAPIMFCDlg::CDAPIMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDAPIMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDAPIMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDAPIMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UFD_CONNECTED, OnDeviceConnected)
	ON_MESSAGE(WM_UFD_DISCONNECTED, OnDeviceDisconnected)
	ON_MESSAGE(WM_UFD_UPDATED, OnDeviceUpdated)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDAPIMFCDlg message handlers

BOOL CDAPIMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	//Read environment variable to get the U3 Launchpad connection string 
    typedef CStringT< TCHAR, StrTraitMFC< TCHAR > > CMyString;
	CMyString connectionString;
	connectionString.GetEnvironmentVariable(_T("U3_DAPI_CONNECT_STRING"));
	
	// Register the callback, using the safe windows handle and the 
	// connection string. The CS will be NULL if not defined.
	// This calls the parent class CDapiBase::RegisterForEvents(...)

	RegisterForEvents(GetSafeHwnd(), connectionString.GetBuffer(256));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDAPIMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDAPIMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDAPIMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CDAPIMFCDlg::OnDeviceConnected(WPARAM hDevice, LPARAM unused)
{

	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(_T("Device Connected"));

	devInfo info;
	//get the device information
	if(dapiQueryDeviceInformation((HDEVICE)hDevice, &info) == S_OK)
	{
		CString strUnique;
		for (size_t i = 0; i < sizeof(info.uniqueID); ++i )
		{
			CString tmpStr;
			tmpStr.Format(_T("%02x "), (int)info.uniqueID[i]) ;
			strUnique += tmpStr;
		}
		GetDlgItem(IDC_EDIT_UNIQUE)->SetWindowText((LPCTSTR)strUnique);
		GetDlgItem(IDC_EDIT_SERIAL)->SetWindowText((LPCTSTR)info.serialNumber);
		GetDlgItem(IDC_EDIT_FW_VER)->SetWindowText((LPCTSTR)info.FWVersion);
		GetDlgItem(IDC_EDIT_VENDOR_STR)->SetWindowText((LPCTSTR)info.vendorString);
		GetDlgItem(IDC_EDIT_PRODUCT_STR)->SetWindowText((LPCTSTR)info.productString);
	}
	//read and display the device drive letters
	CheckandSetCookie((HDEVICE)hDevice);
	UpdateDrives((HDEVICE)hDevice);

	return 0;
}

LRESULT CDAPIMFCDlg::OnDeviceDisconnected(WPARAM hDevice, LPARAM unused)
{
		// Clear all entries
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(_T("Device Disconnected"));
	GetDlgItem(IDC_EDIT_UNIQUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_SERIAL)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_FW_VER)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_VENDOR_STR)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_PRODUCT_STR)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_DRIVES)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_COOKIE_DATA)->SetWindowText(_T(""));

	return 0;
}

LRESULT CDAPIMFCDlg::OnDeviceUpdated(WPARAM hDevice, LPARAM unused)
{
	// Thus event is generated is Windows assigns a 2nd domain a drive letter.
	// Call update drives to query the new list of associated drive letters.
	UpdateDrives((HDEVICE)hDevice);

	return 0;
}

void CDAPIMFCDlg::UpdateDrives(HDEVICE hDevice)
{
	WORD wDomains = 0;
	
	// Read the number of drives to allocate the array
	if(dapiQueryDomainInformation(hDevice, NULL, &wDomains) == S_OK)
	{
		//Allocate domains vector
		typedef std::vector<domainInfo> domain_arr;		
		domain_arr vec(wDomains);
	
		// Read information about each domain
		// if dapiQueryDomainInformation only returns S_FALSE, then not all 
		// drive letters have been assigned, wait until it returns S_OK
		// to display drive letters
		if(dapiQueryDomainInformation(hDevice, &(vec[0]), &wDomains) == S_OK)
		{
			CString strDrives;
			for(size_t n=0; n <vec.size();++n)
			{
				strDrives += vec[n].szPath;
				strDrives += _T(" ");
			}
			
			GetDlgItem(IDC_EDIT_DRIVES)->SetWindowText((LPCTSTR)strDrives);
			
		}
	}
}

	// This function checks for a cookie on the device called
	// [DAPIMFC]
	//    LastSeen=
	// 
	// NOTE According to self test criteria this cookie must be 
	// removed from the device when the application is uninstalled!!!
	// Implement in deviceUninstall an method to delete this cookie.

void CDAPIMFCDlg::CheckandSetCookie(HDEVICE hDevice)
	{

	GetDlgItem(IDC_EDIT_COOKIE_DATA)->SetWindowText(_T(""));

		// check that the device supports cookies
	if(S_OK != dapiQueryDeviceCapability(hDevice,DAPI_CAP_U3_COOKIE))
		{
		GetDlgItem(IDC_EDIT_COOKIE_DATA)->SetWindowText(_T("Device does not support cookies"));
		return;
		}

	wchar_t * pszSection = _T("DAPIMFC");
	wchar_t * pszEntry   = _T("LastSeen");

	// test to see if cookie exists
	DWORD nCookieLen = 0;
	HRESULT res = dapiReadTextCookie(hDevice,pszSection,pszEntry, NULL, &nCookieLen);
	switch(res)
		{
		case DAPI_E_BUFFER_TOO_SMALL:
		case S_OK:
			{
				// OK read cookie data
				// nCookieLen includes final NULL char
			wchar_t * pszTextBuffer = new wchar_t[nCookieLen];
			wmemset(pszTextBuffer,_TCHAR("\0"),nCookieLen);
			if(S_OK == dapiReadTextCookie(hDevice,pszSection,pszEntry, pszTextBuffer, &nCookieLen))
				{
				GetDlgItem(IDC_EDIT_COOKIE_DATA)->SetWindowText(pszTextBuffer);
				}
			delete [] pszTextBuffer;
			break;
			}
			
		case DAPI_E_DATA_NOT_FOUND:
			// cookie does not exist
			GetDlgItem(IDC_EDIT_COOKIE_DATA)->SetWindowText(
				                  _T("This is the first time we have seen the device"));
			break;
		default:
			// general error reading cookie
			GetDlgItem(IDC_EDIT_COOKIE_DATA)->SetWindowText(_T("Error reading cookie data"));
			break;
		}

	// now set the cookie with the latest time string
	CTime time(CTime::GetCurrentTime());
	dapiWriteTextCookie(hDevice,pszSection,pszEntry,(LPCTSTR)time.FormatGmt(_T("%#c")));
	}
