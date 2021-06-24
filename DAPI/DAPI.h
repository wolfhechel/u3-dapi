/*!
**********************************************************************
**
** @file                DAPI.h
**
** @brief               
**
** @note                
**
** @version             
**
** @see                 
**
**                      {{MUSK export}}
**                      
**
**********************************************************************
*/

#ifndef __DAPI_H__
#define __DAPI_H__

#include <WTypes.h>


/**********************************************************/
/**********************************************************/
/**********************************************************/

/******************* Types and constants ******************/
#define DAPI_SERIAL_NUMBER_LEN	257
#define DAPI_UNIQUE_ID_LEN		20
#define DAPI_VENDOR_STRING_LEN	10
#define DAPI_PRODUCT_STRING_LEN	18
#define DAPI_HINT_SIZE			33
#define DAPI_FW_VERSION_SIZE	7

#define DAPI_MAX_PATH			260

#define DAPI_MAX_SECTION_LENGTH			256
#define DAPI_MAX_ENTRY_LENGTH			256
#define DAPI_MAX_PWD_LENGTH				512
#define DAPI_MAX_PROTECTED_DATA_LENGTH	508


typedef enum TdapiStatus
{
/*
	#define S_OK                             ((HRESULT)0x00000000L)
	#define S_FALSE                          ((HRESULT)0x00000001L)

#if defined(_WIN32) && !defined(_MAC)
	#define E_POINTER                        _HRESULT_TYPEDEF_(0x80004003L)
	#define E_HANDLE                         _HRESULT_TYPEDEF_(0x80070006L)
	#define E_INVALIDARG                     _HRESULT_TYPEDEF_(0x80070057L)
#else
	#define E_POINTER                        _HRESULT_TYPEDEF_(0x80000005L)
	#define E_HANDLE                         _HRESULT_TYPEDEF_(0x80000006L)
	#define E_INVALIDARG                     _HRESULT_TYPEDEF_(0x80000003L)
#endif

*/
	DAPI_E_STATE_ERR							= 0x80040200,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200L)
	DAPI_E_CONFIGURATION_ERR					= 0x80040201,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x201L)
	DAPI_E_PATH_ERR								= 0x80040202,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x202L)
	DAPI_E_GENERAL_ERR							= 0x80040203,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x203L)
	DAPI_E_INTERNAL_ERR							= 0x80040204,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x204L)
	DAPI_E_STRING_CONVERSION_ERR				= 0x80040205,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x205L)
	DAPI_E_DOMAIN_TYPE_ERR						= 0x80040206,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x206L)
	DAPI_E_DOMAIN_PATH_ERR						= 0x80040207,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x207L)

	DAPI_E_COMM_FAIL							= 0x80040210,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x210L)
	DAPI_E_MEDIA_LOCK_FAIL						= 0x80040212,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x212L)
	DAPI_E_FORMAT_FAIL							= 0x80040213,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x213L)
	DAPI_E_HINT_FAIL							= 0x80040214,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x214L)
	DAPI_E_FS_REFRESH_FAIL						= 0x80040216,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x216L)

	DAPI_E_NOT_CONNECTED						= 0x80040220,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x220L)
	DAPI_E_NOT_READY							= 0x80040221,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x221L)
	DAPI_E_NOT_WRITABLE							= 0x80040222,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x222L)
	DAPI_E_PA_CONFIGURED						= 0x80040223,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x223L)
	DAPI_E_CD_LOCKED							= 0x80040224,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x224L)

	DAPI_E_HIDDEN_AREA_FULL						= 0x80040230,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x230L)
	DAPI_E_DATA_NOT_FOUND						= 0x80040231,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x231L)
	DAPI_E_OPERATION_NOT_COMPLETED				= 0x80040232,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x232L)
	DAPI_E_READ_PWD_ERR							= 0x80040234,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x234L)
	DAPI_E_WRITE_PWD_ERR						= 0x80040235,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x235L)
	DAPI_E_COOKIE_EXISTS						= 0x80040236,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x236L)
	DAPI_E_COOKIE_CONFIG_ERR					= 0x80040237,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x237L)
	DAPI_E_PASSWORD_TOO_LONG					= 0x80040238,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x238L)
	DAPI_E_BUFFER_TOO_LARGE						= 0x80040239,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x239L)

	DAPI_E_BUFFER_TOO_SMALL						= 0x80040240,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x240L)
	DAPI_E_CMD_NOT_SUPPORTED					= 0x80040241,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x241L)
	DAPI_E_CMD_NOT_SUPPORTED_IN_NON_ADMIN_MODE	= 0x80040242,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x242L)

	DAPI_E_OS_NOT_SUPPORTED						= 0x80040250,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x250L)
	DAPI_E_WIN_2K_SP4_HOTFIX_MISSING			= 0x80040251,    //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x251L)

	DAPI_E_ADV_ERR 								= 0x80040260	 //MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x260L)	


}dapiStatus ;

typedef enum
{
	ILLEGAL_HDEVICE		= -1,
	ILLEGAL_HCALLBACK	= -1,
	ILLEGAL_HSESSION	= -1
};

typedef enum 
{
	DAPI_CAP_USB_HI_SPEED		= 0,
	DAPI_CAP_U3					= 1,
	DAPI_CAP_MSD				= 2,
	DAPI_CAP_U3_COOKIE			= 3,
	DAPI_CAP_U3_PCOOKIE			= 4,
	DAPI_CAP_U3_PRIVATE_AREA	= 5
};

typedef enum TeventType_t
{
	DAPI_EVENT_DEVICE_CONNECT			= 0x01 ,
	DAPI_EVENT_DEVICE_DISCONNECT		= 0x02 ,
	DAPI_EVENT_DEVICE_UPDATE			= 0x03 ,
	DAPI_EVENT_DEVICE_LOGIN				= 0x04 ,
	DAPI_EVENT_DEVICE_LOGOUT			= 0x05 ,
	DAPI_EVENT_DEVICE_WRITE_PROTECT_ON	= 0x06 ,
	DAPI_EVENT_DEVICE_WRITE_PROTECT_OFF = 0x07 ,
	DAPI_EVENT_DEVICE_RECONNECT			= 0x08 ,
	DAPI_EVENT_DEVICE_NEW_CONFIG		= 0x09 
}eventType_t;

typedef enum TpraInfoStatus
{
	DAPI_PRA_NOT_CONFIGURED = 0 ,
	DAPI_PRA_LOGGED_OUT		= 1 ,
	DAPI_PRA_LOGGED_IN		= 2
} praInfoStatus ;

typedef enum TpartitionTypeMask
{
	DAPI_PI_READ_ONLY			= 0x00000001,
	DAPI_PI_TYPE_CD				= 0x00000100,
	DAPI_PI_REMOVABLE_PUBLIC	= 0x00000200,
	DAPI_PI_REMOVABLE_PRIVATE	= 0x00000400,
	DAPI_PI_NOT_READY			= 0x40000000,
	DAPI_PI_UNKNOWN				= 0x80000000
}partitionTypeMask;

typedef DWORD	HDEVICE		; 
typedef DWORD	HCALLBACK	;
typedef DWORD	HSESSION	;

typedef void (_stdcall *DAPI_CALLBACK)(HDEVICE hDev, DWORD eventType, void* pEx);


/**********************************************************/
/**********************************************************/
/**********************************************************/

/************************ Structures **********************/

typedef struct TdevInfo
{
	wchar_t	serialNumber	[DAPI_SERIAL_NUMBER_LEN]	;
	BYTE	uniqueID		[DAPI_UNIQUE_ID_LEN]		;
	wchar_t	vendorString	[DAPI_VENDOR_STRING_LEN]	;
	wchar_t	productString	[DAPI_PRODUCT_STRING_LEN]	;
	wchar_t	FWVersion		[DAPI_FW_VERSION_SIZE]		;
	DWORD	vendorID			;
	DWORD64	deviceSize			;
}devInfo ;

typedef struct TdomainInfo
{
	wchar_t	szPath[DAPI_MAX_PATH+1]	;
	DWORD64	size					;
	DWORD	typeMask				;
}domainInfo ;


typedef struct TpraInfo
{
	DWORD	maxNOA	;
	DWORD	currNOA	;
	DWORD64	size	;
	DWORD	status	;
	wchar_t szHint [DAPI_HINT_SIZE] ;
} praInfo ;


/**********************************************************/
/**********************************************************/
/**********************************************************/

/********************    DAPI Functions *******************/

#ifdef __cplusplus
extern "C"{
#endif 

	const wchar_t * const dapiGetVersion();

	HRESULT dapiCreateSession       (HSESSION * hSession) ;


	HRESULT dapiDestroySession      (HSESSION hSession) ;

	HRESULT dapiRegisterCallback    (   HSESSION        hSession            ,
		                                wchar_t*        pszConnectionString ,
										DAPI_CALLBACK   pCallBack           ,
										void*           pEx                 ,
										HCALLBACK*      hCallback) ;

	HRESULT	dapiUnregisterCallback		(HCALLBACK hCallback) ;

	HRESULT	dapiQueryDeviceInformation	(HDEVICE hDev, devInfo* pInfo);

	HRESULT	dapiQueryDeviceCapability	(HDEVICE hDev, DWORD nCapability) ;

	HRESULT	dapiQueryDomainInformation	(HDEVICE hDev, domainInfo* pInfo, WORD* nCount) ;

	HRESULT	dapiEjectDevice				(HDEVICE hDev);

	HRESULT dapiGetPrivateAreaInfo		(HDEVICE hDev, const wchar_t* szPath, praInfo* pInfo) ;

	HRESULT	dapiLoginPrivateArea		(HDEVICE hDev, const wchar_t* szPath, const wchar_t* szPassword, BOOL bLock) ;

	HRESULT	dapiLogoutPrivateArea		(HDEVICE hDev, const wchar_t* szPath, BOOL bLock) ;

	HRESULT	dapiSetPrivateAreaPassword	(		HDEVICE		hDev			, 
										const	wchar_t*	szPath			, 
										const	wchar_t*	szOldPassword	, 
										const	wchar_t*	szNewPassword	, 
										const	wchar_t*	szNewHint		,
												BOOL		bLock)			;

	HRESULT	dapiWriteTextCookie			(		HDEVICE		hDev		, 
										const	wchar_t*	szSection	, 
										const	wchar_t*	szEntry		,
										const	wchar_t*	szValue) ;

	HRESULT	dapiWriteBinaryCookie		(		HDEVICE		hDev		, 
										const	wchar_t*	szSection	,
										const	wchar_t*	szEntry		,
										const	BYTE*		pBuffer		,  
												DWORD		nBufLength) ;

	HRESULT	dapiReadTextCookie			(		HDEVICE		hDev		, 
										const	wchar_t*	szSection	, 
										const	wchar_t*	szEntry		,
												wchar_t*	szValue		, 
												DWORD*		nBufLength) ;

	HRESULT	dapiReadBinaryCookie		(		HDEVICE		hDev		, 
										const	wchar_t*	szSection	, 
										const	wchar_t*	szEntry		,
												BYTE*		pBuffer		, 
												DWORD*		nBufLength) ;

	HRESULT	dapiDeleteCookie			(		HDEVICE		hDev	 , 
										const	wchar_t*	szSection, 
										const	wchar_t*	szEntry) ;

	HRESULT	dapiCreateProtectedCookie (			HDEVICE		hDev,
										const	wchar_t*	szSection,
										const	wchar_t*	szEntry,
										const	wchar_t*	szWritePassword,
										const	wchar_t*	szReadPassword) ;

	HRESULT	dapiWriteProtectedCookie	(		HDEVICE		hDev			, 
										const	wchar_t*	szSection		,
										const	wchar_t*	szEntry			,
										const	BYTE*		pBuffer			,  
												DWORD		nBufLength		,
										const	wchar_t*	pWritePassword)	;

	HRESULT	dapiReadProtectedCookie		(		HDEVICE		hDev		, 
										const	wchar_t*	szSection	, 
										const	wchar_t*	szEntry		,
												BYTE*		pBuffer		, 
												DWORD*		nBufLength	,
										const	wchar_t*	pReadPassword) ;

	HRESULT	dapiDeleteProtectedCookie	(		HDEVICE		hDev			, 
										const	wchar_t*	szSection		, 
										const	wchar_t*	szEntry			, 
										const	wchar_t*	pWritePassword	,
										const	wchar_t*	pReadPassword)	;

	/**********************************************************/
	/**********************************************************/
	/**********************************************************/


#ifdef __cplusplus
}
#endif 

#endif // __DAPI_H__