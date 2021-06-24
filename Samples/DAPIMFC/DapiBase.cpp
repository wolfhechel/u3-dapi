#include "StdAfx.h"
#include ".\dapibase.h"


CDapiBase::CDapiBase(void)
{
m_hCallBack = ILLEGAL_HCALLBACK;
m_hSession  = ILLEGAL_HSESSION;
}

CDapiBase::~CDapiBase(void)
{
	UnregisterForEvents();
}

// This functions creates a DAPI session and registers the callback function.
// The hWnd of the parent main window should be passed. 
// pszConnectionString can be passed to lock to events for a specific device,
// or NULL for all devices. 
HRESULT CDapiBase::RegisterForEvents(HWND hWnd, wchar_t* pszConnctionString)
{ 
	HRESULT res = S_FALSE;
	
		// make sure that the session or callback does not exist
	if(ILLEGAL_HSESSION != m_hSession || ILLEGAL_HCALLBACK != m_hCallBack)
		return res;

	//create a session 
	if((res = dapiCreateSession(&m_hSession)) == S_OK)
	{
		//register a callback on our session
        if(S_OK != (res =  dapiRegisterCallback(m_hSession,	pszConnctionString,
									(DAPI_CALLBACK)(Callback),(void *) hWnd,
									&m_hCallBack)))
			{ 
			UnregisterForEvents();
			}
     }
	return res;
}

	// unregisters any open callbacks and sessions
void CDapiBase::UnregisterForEvents()
	{
	if(ILLEGAL_HCALLBACK != m_hCallBack)
		dapiUnregisterCallback(m_hCallBack);
	m_hCallBack = ILLEGAL_HCALLBACK;

	if(ILLEGAL_HSESSION != m_hSession)
		dapiDestroySession(m_hSession);
	m_hSession = ILLEGAL_HSESSION;
	}


 // This will reflect the event as a message back to the application whose
 // hWnd was supplied at registration time
void _stdcall CDapiBase::Callback(HDEVICE hDev, DWORD eventType, void* pEx)
{
	if(NULL != pEx)
		PostMessage((HWND)pEx, WM_USER + eventType, hDev, 0);
}