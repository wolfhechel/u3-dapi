#pragma once

#include "u3dapi10.h"

class CDapiBase
{
public:

	CDapiBase();
	~CDapiBase();

	// Creates a DAPI session and registers the callback function.
	// szConnectionString - pass serial number of the device or NULL for all devices
	// hWnd - handle of the applications main window
	HRESULT RegisterForEvents(HWND hWnd, wchar_t* pszConnctionString); 
	void    UnregisterForEvents(); 

private:
	// This callback method that will be registered with DAPI to receive events on devices
	// Events will be send back as send window messages to it's HWND which is passed in as the
	// pEx param.
	static void _stdcall Callback(HDEVICE hDev, DWORD eventType, void* pEx);
    
	HSESSION	m_hSession;
	HCALLBACK	m_hCallBack;

};

//user should define messages to map device events
#define WM_UFD_CONNECTED			(WM_USER + DAPI_EVENT_DEVICE_CONNECT)
#define WM_UFD_DISCONNECTED			(WM_USER + DAPI_EVENT_DEVICE_DISCONNECT)
#define WM_UFD_UPDATED				(WM_USER + DAPI_EVENT_DEVICE_UPDATE)
#define WM_UFD_LOGIN				(WM_USER + DAPI_EVENT_DEVICE_LOGIN)
#define WM_UFD_LOGOUT				(WM_USER + DAPI_EVENT_DEVICE_LOGOUT)
#define WM_UFD_WRPT_ON				(WM_USER + DAPI_EVENT_DEVICE_WRITE_PROTECT_ON)
#define WM_UFD_WRPT_OFF				(WM_USER + DAPI_EVENT_DEVICE_WRITE_PROTECT_OFF)
#define WM_UFD_RECONNECT			(WM_USER + DAPI_EVENT_DEVICE_RECONNECT)
#define WM_UFD_NEW_CONFIG			(WM_USER + DAPI_EVENT_DEVICE_NEW_CONFIG)


