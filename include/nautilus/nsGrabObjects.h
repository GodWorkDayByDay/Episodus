// NsGrabObjects.h : D�finition des objets de capture d'images
#if !defined(__NSGRABOBJECTS_H)
#include <owl\edit.h>

// #include "nautilus\nssuper.h"
#include "partage\NTArray.h"
#include "nsbb\nsutidlg.h"
#include "nssavoir\nscaptur.h"

// defines pour NSGrabObject
#define M_CAPTUREIMAGE      1
#define M_CONVERTBMP        2
#define M_FREECAMERA        3
#define M_GRABFRAME         4
#define M_GRABFREE          5
#define M_GRABINIT          6
#define M_GRABONEBUFFER     7
#define M_INITCAMERA        8
#define M_NBCAMERA          9
#define M_PANIMAGE          10
#define M_STOPCAMERA        11
#define M_ZOOMIMAGE         12

#define T_CAPTUREIMAGE      13
#define T_SELECTSOURCE      14
/////////////////////////////////////////////

// id de commandes pour fenetre de capture (grabbing)


class NSGrabberObject : public NSRoot
{
	public:

    NSGrabberObject(NSContexte *pCtx) ;
    ~NSGrabberObject() ;

    virtual bool CaptureImage(string sFichier, HWND hwnd) = 0 ;
    bool FindFileName(string sNameSeed, string* pBmpFileName, string* pJpgFileName) ;
};


class NSMilGrabObject : public NSGrabberObject
{
	public:

    long lSizeX ;
    long lSizeY ;

    NSMilGrabObject(NSContexte *pCtx) ;
    ~NSMilGrabObject() ;

    bool InitCamera(HWND handleClient) ;
    bool NbCamera(int& nbCam) ;
    bool FreeCamera() ;
    bool StopCamera() ;
    bool GrabFree() ;
    bool GrabFrame() ;
    bool GrabOneBuffer() ;
};

class NSMilGrabWindow : public TWindow
{
		long                 lSizeX ;
    long                 lSizeY ;
    bool                 bCanClose ;
    NSMilGrabWindow(TWindow* parent, NSContexte* pCtx, AssistCaptureDialog* pAssistDlg = 0);
    ~NSMilGrabWindow();
    void SetupWindow() ;
	DECLARE_RESPONSE_TABLE(NSMilGrabWindow) ;
// Classe TMDIChild pour la red�finition de EvClose
/////////////////////////////////////////////////////////
		NSMilGrabWindow* pClient ;
		NSMilGrabChild(NSContexte* pCtx, TMDIClient& parent, const char far* title = 0, NSMilGrabWindow* clientWnd = 0) ;
		void EvClose() ;
	DECLARE_RESPONSE_TABLE(NSMilGrabChild) ;

// Dialogue assistant de capture d'images
/////////////////////////////////////////////////
class AssistCaptureDialog : public NSUtilDialog
{
		int phase ;

    OWL::TCheckBox* pPhase1 ;
    OWL::TCheckBox* pPhase2 ;
    OWL::TCheckBox* pPhase3 ;
    NSContexte* pContexte ;

		AssistCaptureDialog(TWindow* pere, NSContexte* pCtx) ;
		void SetupWindow() ;
		void CmSuite() ;

	DECLARE_RESPONSE_TABLE(AssistCaptureDialog) ;

// Classe TWindow pour la capture Twain
///////////////////////////////////////////////////////

class NSTwainObject : public NSGrabberObject
{
	public:

		string sBmpFileName ;
    string sJpgFileName ;

    NSTwainObject(NSContexte *pCtx) ;
    ~NSTwainObject() ;

    bool CaptureImage(string sFichier, HWND hwnd) ;
class NSTwainWindow : public TWindow
{
		long           lSizeX ;
    long           lSizeY ;
    bool           bOpenMenu ;
    ~NSTwainWindow() ;
    void SetupWindow() ;
	DECLARE_RESPONSE_TABLE(NSTwainWindow) ;
// Classe TMDIChild pour la red�finition de EvClose
/////////////////////////////////////////////////////////
		NSTwainWindow* pClient ;
		NSTwainGrabChild(NSContexte* pCtx, TMDIClient& parent, const char far* title = 0, NSTwainWindow* clientWnd = 0) ;
		void EvClose() ;
	DECLARE_RESPONSE_TABLE(NSTwainGrabChild) ;

#endif   // __NSGRABOBJECTS_H
// fin de nsbrowse.h
