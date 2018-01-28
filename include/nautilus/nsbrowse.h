// NSBROWSE.H : D�finition des objets dialogues contenant ie4
#if !defined(__NSBROWSE_H)
#include <owl\edit.h>

class NSContexte ;

class NSRefDocument ;
class TWebCompos ;
// #include "nautilus\nssuper.h"
#include "partage\NTArray.h"
#include "nsbb\nsutidlg.h"
#include "nssavoir\nscaptur.h"

#ifndef __EPIPUMP__
   navNoHistory         = 2,
   navNoReadFromCache   = 4,
   navNoWriteToCache    = 8
} BrowserNavConstants ;
class NSComposView : public TWindowView

		string 				 fichCompo ;

		NSComposView(NSRefDocument& doc, TWindow *parent = 0) ;
    ~NSComposView() ;

    // Red�finiton des fonctions virtuelles de TView
    static LPCSTR StaticName() { return "NSComposView" ; }
    const char*   GetViewName() { return StaticName() ; }
    TWindow*      GetWindow() ;
    void          EvClose() ;

    void PerformCreate(int menuOrId) ;
    void MakeVisible() ;
    void SetupWindow() ;
    void Navigate(string url) ;
    void NavigateErrorEvent(int iStatusCode, string sURL) ;
    void CmOk() ;
  	void CmCancel() ;

	protected:

		bool IsTabKeyMessage(MSG &msg);

	private:

		TWebCompos* Form ;
	DECLARE_RESPONSE_TABLE(NSComposView);

// Classe TWindow permettant de visualiser les fichiers avant importation
/////////////////////////////////////////////////////////////////////////////////
class NSImportWindow : public TWindow
{
	public:

  	bool           _bNavOk ;
    bool           _bCanClose ;
    string				 _sHtml ;
    string				 _sFileName ;     // path + nom + ext
    string				 _sPathName ;     // path
    string				 _sNomFichier ;   // nom + ext
    string				 _sExtension ;    // ext
    string				 _sNomSeul ;      // nom
    NSRefDocument* _pNewDoc ;       // Document � cr�er dans nautilus
    string				 _sTypeNautilus ; // Type nautilus
    NSContexte* 	 _pContexte ;

    NSImportWindow(TWindow* parent, string sFichier, NSContexte* pCtx, bool bAutoMode = false) ;
    ~NSImportWindow() ;

    bool   CanClose() ;
    void   EvClose() ;
    void   PerformCreate(int menuOrId) ;
    void   MakeVisible() ;
    void   SetupWindow() ;
    void   Navigate() ;
    void   NavigateErrorEvent(int iStatusCode, string sURL) ;
    bool   InitInfosFichier() ;
    bool   InitNautilusType() ;
    bool   GenereHtml() ;
    void   CmImporter() ;
    void   CmReferencer() ;
    void   CmCapturer() ;
    void   CmAnnuler() ;
    bool   convertGdata(string* psFichier) ;
    bool   importHPRIM2(NSCaptureArray* pCaptureArray, NSPatPathoArray* pPPT) ;
    bool   importHPRIM1(NSCaptureArray* pCaptureArray, NSPatPathoArray* pPPT) ;
    bool   parseHPRIM1header(ifstream* pInFile, NSCaptureArray* pCaptureArray, NSPatPathoArray* pPPT) ;
    string getDateFromHPRIM1date(string sHPRIMdate, string s2kTreshold) ;

    bool   okToClose()       { return _bCanClose ; }
    bool   isNavOk()         { return _bNavOk ; }
    string getExtension()    { return _sExtension ; }
    string getNautilusType() { return _sTypeNautilus ; }

    void   ClosingPatch() ;

	protected:

    bool _bAutomaticImportMode ;
    bool _bImportSuccessful ;

		bool IsTabKeyMessage(MSG &msg) ;

	private:

		TWebImport* _Form ;
	DECLARE_RESPONSE_TABLE(NSImportWindow) ;
};

// Classe TMDIChild pour la red�finition de EvClose
class NSImportChild : public TMDIChild, public NSRoot
{
	public :

		NSImportWindow* pClient ;

		NSImportChild(NSContexte* pCtx, TMDIClient& parent, const char far* title = 0, NSImportWindow* clientWnd = 0) ;
		~NSImportChild() ;

		void EvClose() ;

	DECLARE_RESPONSE_TABLE(NSImportChild) ;
};

// Classe TWindow permettant de visualiser les r�sultats de DPIO
/////////////////////////////////////////////////////////////////////////////////
class NSLogWindow : public TWindow
{
 public:
	NSLogWindow(TWindow *parent, string sFichier, NSContexte *pCtx) ;
	~NSLogWindow() ;

	void					EvClose() ;
	void					PerformCreate(int menuOrId) ;
	void					MakeVisible() ;
	void					SetupWindow() ;
	void					Navigate() ;
  void          NavigateErrorEvent(int iStatusCode, string sURL) ;
	void					Refresh() ;
	void					CmClipCopy() ;
	void					CmFermer() ;
  void          CmImprimer();
	bool					convertGdata(string *psFichier) ;

	bool          bNavOk ;
	bool          bCanClose ;
	string				sHtml ;
	string				sFileName ;			// path + nom + ext
	string				sPathName ;     // path
	string				sNomFichier ;		// nom + ext
	string				sExtension ;		// ext
	string				sNomSeul ;			// nom
	NSRefDocument	*pNewDoc ;			// Document � cr�er dans nautilus
	string				sTypeNautilus ;	// Type nautilus
	NSContexte		*pContexte ;

 protected:
	bool					IsTabKeyMessage(MSG& msg) ;
	bool					PreProcessMsg(MSG& msg) ;
	string				html2string(string s2convert) ;

 private:
 	TWebLog				*Form ;
  HACCEL        hAccelerator ;

 	DECLARE_RESPONSE_TABLE(NSLogWindow) ;
} ;

// Classe TMDIChild pour la red�finition de EvClose
class NSLogChild : public TMDIChild, public NSRoot
{
	public :

		NSLogWindow* pClient ;

		NSLogChild(NSContexte* pCtx, TMDIClient& parent, const char far* title = 0, NSLogWindow* clientWnd = 0) ;
		~NSLogChild() ;

		void EvClose() ;

	DECLARE_RESPONSE_TABLE(NSLogChild) ;
};

//
// D�finition d'une classe NSImage contenant chaque image import�e
class NSImage
    string fichier ;        // nom du fichier image source
    NSImage() ;
    NSImage(const NSImage& rv) ;

typedef vector<NSImage*> NSImgVector;
/*
class NSImgArray : public NSImgVector    // TODO DELETE IF NO PROBLEM
		// Constructeurs
		// Destructeur
        void vider();

// Classe TWindow permettant l'importation en s�rie des images
class NSImpImgWindow : public TWindow
    NSImpImgWindow(TWindow* parent, NSContexte* pCtx, AssistCaptureDialog* pAssistDlg = 0) ;
		void EvClose() ;
	protected:
		bool IsTabKeyMessage(MSG &msg) ;
	private:
	DECLARE_RESPONSE_TABLE(NSImpImgWindow) ;
};
// Classe TMDIChild pour la red�finition de EvClose
class NSImpImgChild : public TMDIChild, public NSRoot
{
	public :

		NSImpImgWindow* pClient ;

		NSImpImgChild(NSContexte* pCtx, TMDIClient& parent, const char far* title = 0, NSImpImgWindow* clientWnd = 0) ;
		~NSImpImgChild() ;

		void EvClose() ;

	DECLARE_RESPONSE_TABLE(NSImpImgChild) ;
};

#endif
// fin de nsbrowse.h
