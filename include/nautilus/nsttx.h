#if !defined(__NS_TTX_H)

class NSTtxDocument ;        // classe g�n�rique de documents texte nautilus
// class TWordBasicProxy ;   // classe d'automation Word.Basic (par ProxyWizard)
class T_ApplicationProxy ;   // classe d'automation Word.Basic (par ProxyWizard)
class TDocumentsProxy ;      // classe d'automation Word.Basic (par ProxyWizard)
class T_DocumentProxy ;
class TAutoWordForm ;        // classe "Form" permettant de faire une vue - dialogue

class NSUtilDialog ;
class NSUtilEdit ;
class TRangeProxy ;

#include <owl\docmanag.h>
#include <owl\docview.h>
#include <owl\mdichild.h>
#include <owl\decframe.h>
#include <owl\statusba.h>
#include <owl\controlb.h>
#include <owl\buttonga.h>
#include <owl\applicat.h>
#include <owl\richedit.h>
#include <owl\richedpr.h>
#include <owl\choosefo.h>
#include <owl\richedit.h>
// #include <ocf\occtrl.h>

#include "nautilus\nsdocref.h"
#include "nautilus\nsmodhtm.h"
#include "nsbb\nsRichEdit.h"
// #include "nautilus\richedap.h"
// #include "nsbb\nsednum.h"

#define MAXCARS 100000      // Limite du texte pour RichEdit
// #if defined(_DANSTXTDLL)
// #else
// #define _NSTTXCLASS __import
// #endif

// Constantes
const int UnChk    = TCommandEnabler::Unchecked;
const int Chk	   = TCommandEnabler::Checked;

#define _NSTTXCLASS _USERCLASS
// Vue pour les documents Word : windowview - dialogue d'automation
class NSAutoWordView : public TWindowView
{
  public :

    NSAutoWordView(NSTtxDocument& doc, TWindow *parent = 0) ;

    // fonction virtuelles de TView
    const char*   GetViewName() { return StaticName() ; }
    TWindow*      GetWindow()   { return (TWindow*) this ; }

    void PerformCreate(int menuOrId) ;
    void SetupWindow() ;
    void EvClose() ;
    void EvTimer(uint timerId) ;
    bool CanClose() ;
    void FillStartupInfo(LPSTARTUPINFO psi) ;

    void CmLancer() ;
    void CmArchiver() ;
    void CmPublier() ;
    void CmVisualiser() ;
    void CmEditer() ;
    void CmComposer() ;
    void CmFormules() ;
    void CmFileOpen() ;

    void ReplaceTags(TRangeProxy *pRangeProxy) ;

    bool GotoBookmark(string sBookmarkName) ;
    bool GotoStartOfDoc() { return GotoBookmark("\\StartOfDoc") ; }
    bool GotoEndOfDoc()   { return GotoBookmark("\\EndOfDoc") ; }

    short GetSelInfo(short iType) ;
    short GetSelStartRow()  { return GetSelInfo(13) ; }
    short GetSelStartCol()  { return GetSelInfo(16) ; }
    short GetSelEndRow()    { return GetSelInfo(14) ; }
    short GetSelEndCol()    { return GetSelInfo(17) ; }

    bool saveHTMLtoWORD(string sWordName) ;

  protected:
    bool                _bSessionEnCours ;
    NSTtxDocument*      _pDocTtx ;

    T_ApplicationProxy* _pApplicationProxy ;
    string              _sWordVersion ;
    TDocumentsProxy*    _pDocumentsProxy ;
    T_DocumentProxy*    _pCurrentDocument ;

    bool IsTabKeyMessage(MSG &msg) ;

    // bool EvOcCtrlCustomEvent(TCtrlCustomEvent* pev) ;
    TResult EvOcEvent(TParam1 param1, TParam2 param2) ;

	private:
    TAutoWordForm* _Form ;
  DECLARE_RESPONSE_TABLE(NSAutoWordView) ;

class NSTtxDocument : public NSRefDocument
{
	protected:

		string _sFileName ;       // fichier texte associ�

    string _sDocTitle ;
    string _sDocLexique ;

    bool   _bMustReplaceTagsWhenOpening ;

  public:

		NSTtxDocument(TDocument *parent, bool bROnly, NSDocumentInfo *pDocumentInfo,

		NSTtxDocument(TDocument *parent = 0, NSContexte *pCtx = 0) ;

		void   SetNomFichier(string sFich) ;
    string GetDocTitle()    { return _sDocTitle ; }
    string GetDocLexique()  { return _sDocLexique ; }
    string GetFileName()    { return _sFileName ; }
    string GetExtFileName() { return _sExternalFileName ; }

		// M�thodes virtuelles de TDocument
		bool Close() ;

		// G�n�ration du html correspondant au document
      						string sAdresseCorresp = "", string sPathDest = "") ;
    bool GenereHtmlText(string& sHtmlText) ;
    bool GenereRawText(string& sRawText) ;

		bool IsOpen() ;
    bool HaveToReplaceTags()          { return _bMustReplaceTagsWhenOpening ; }

		// Fonctions de gestion du document Nautilus

class NSTtxView : public TView, public NSRichEdit
	public:

		NSTtxView(NSTtxDocument& doc, TWindow *parent = 0) ;

    // Red�finiton des fonctions virtuelles de TView et TRichEdit
    const char*   GetViewName() { return StaticName() ; }
    TWindow*      GetWindow() ;
    bool 	        CanClose() ;           // de TEditFile
    bool	        CanClear() ;           // de TEditFile
    bool	        SetDocTitle(const char far* docname, int index)
    {
    	return NSRichEdit::SetDocTitle(docname, index) ;
    }

  protected:
  	bool bSetupToolBar ;
    // Remplissage de la vue
    void   SetupWindow() ;
    void   SetupTxtBar() ;
    void   InitDefaultFont() ;
    void   SetFormatFont(LOGFONT lf) ;
    void   RemplaceTagsRTF() ;
    string getText() ;

    // view event handlers

    // Fonctions de r�ponse aux evts
    void EvChar(uint key, uint repeatCount, uint flags) ;
    void EvSetFocus(THandle hWndLostFocus) ;
    void EvKillFocus(THandle hWndGetFocus) ;
    bool EvQueryEndSession() ;
    void EvDestroy() ;

    // Overrides TWindows' in order to process our accelerators table
    bool PreProcessMsg(MSG &msg) ;

    // Fonctions d'appel des m�thodes de NSRefDocument
    void CmPublier() ;
    void CmVisualiser() ;

    // Fonction d'appel des formules pr�-enregistr�es

    // Fonction d'appel des CR Nautidos
    void CmNautidos() ;

    // Red�finition de ces fonctions pour g�rer le flag Dirty
    void CmEditCut() ;
    void CmEditPaste() ;

    // Fonctions de sauvegarde
    bool EnregistrerSous() ;

    // File Command handlers
    void CmFileOpen() ;
    void CmFileSave() ;
    void CmFileSaveAs() ;
    void CmFilePrint() ;
    void CmFilePrintPreview() ;
    void CmOuvrir() ;
    void CmAutoFilling() ;

    // Format Command handlers
    void CmFormatPara() ;
    void CmFormatTabs() ;
    void CmFormatBold() ;
    void CmFormatItalic() ;
    void CmFormatUnderline() ;
    void CmFormatStrikeout() ;
    void CmFormatTextData() ;
    void CmFormatRTFData() ;

    void CeFormatFont(TCommandEnabler&) ;
    void CeFormatTabs(TCommandEnabler&) ;
    void CeFormatBold(TCommandEnabler&) ;
    void CeFormatItalic(TCommandEnabler&) ;
    void CeFormatUnderline(TCommandEnabler&) ;
    void CeFormatStrikeout(TCommandEnabler&) ;
    void CeFormatTextData(TCommandEnabler&) ;
    void CeFormatRTFData(TCommandEnabler&) ;

    bool EnDropFiles(TEnDropFiles&)	   { return false ; }
    bool EnProtected(TEnProtected&)	   { return false ; }
    void EnReqResize(TReqResize&)	{}

    void initMUEViewMenu(string sMenuName) ;
    void activateMUEViewMenu() ;

    // Variables
    OWL::TControlBar *pToolBar ; // Barre d'outils
    OWL::TPrinter	   *pPrinter ; // Printer

    TMenuDescr       *pMUEViewMenu ;
    HACCEL           hAccelerator ;

    LOGFONT          _defaultFont ;

  DECLARE_RESPONSE_TABLE(NSTtxView) ;

//	DEFINE_DOC_TEMPLATE_CLASS(NSTtxDocument,NSTtxView,TtxDlgViewTmpl);

// Classe NSSimpleTxtDocument : document pour les fichiers txt (bloc-note)
class  NSSimpleTxtDocument : public NSRefDocument
{
	public:

  	string _sFileName ;       // fichier texte associ�
    NSSimpleTxtDocument(TDocument *parent, bool bROnly, NSDocumentInfo *pDocumentInfo,

    NSSimpleTxtDocument(TDocument *parent = 0, NSContexte *pCtx = 0) ;
    ~NSSimpleTxtDocument() {}

    void   SetNomFichier(string sFich) ;

    // M�thodes virtuelles de TDocument
    bool Close() ;

    // G�n�ration du html correspondant au document
      						string sAdresseCorresp = "", string sPathDest = "") ;
    bool GenereHtmlText(string& sHtmlText) ;

    bool IsOpen() ;
    // Fonctions de gestion du document Nautilus
};

// Classe NSSimpleTxtView : vue pour les fichiers txt (bloc-note)
class NSSimpleTxtView : public TView, public OWL::TEditFile
{
	public:

  	NSSimpleTxtView(NSSimpleTxtDocument& doc, TWindow *parent = 0) ;

    // Red�finiton des fonctions virtuelles de TView et TRichEdit
    const char*   GetViewName() { return StaticName(); }
    TWindow*      GetWindow();
    bool 	        CanClose();           // de TEditFile
    bool	        CanClear();           // de TEditFile
    // bool	      SetDocTitle(const char far* docname, int index);

  protected:
  	bool bSetupToolBar;

    // Remplissage de la vue
    void SetupWindow();
    void SetupTxtBar();

    // view event handlers

    // Fonctions de r�ponse aux evts
    void EvChar(uint key, uint repeatCount, uint flags);
    void EvSetFocus(THandle hWndLostFocus);
    void EvKillFocus(THandle hWndGetFocus);
    bool EvQueryEndSession();

    // Overrides TWindows' in order to process our accelerators table
    bool PreProcessMsg(MSG &msg) ;

    // Fonctions d'appel des m�thodes de NSRefDocument
    void CmPublier();
    void CmVisualiser();

    // Fonction d'appel des formules pr�-enregistr�es

    // Red�finition de ces fonctions pour g�rer le flag Dirty
    void CmEditCut();
    void CmEditPaste();

    // Fonctions de sauvegarde
    bool EnregistrerSous();

    // File Command handlers
    void CmFileOpen();
    void CmFileSave();
    void CmFileSaveAs();

    bool EnDropFiles(TEnDropFiles&)	{ return false; }
    bool EnProtected(TEnProtected&)	{ return false; }
    void EnReqResize(TReqResize&)	{}

    void initMUEViewMenu(string sMenuName) ;
    void activateMUEViewMenu() ;

    // Variables
    OWL::TControlBar    *pToolBar ;	// Barre d'outils

    TMenuDescr          *pMUEViewMenu ;
    HACCEL              hAccelerator ;

  DECLARE_RESPONSE_TABLE(NSSimpleTxtView) ;

#endif		// __NS_TTX_H