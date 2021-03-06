// --------------------------------------------------------------------------// NSTEAMDOCVIEW.H		Document/Vues Capture Health Team
// --------------------------------------------------------------------------
// PA Janvier 2007
// --------------------------------------------------------------------------

#if !defined(__NSCOOPCHARTDV_H)#define __NSCOOPCHARTDV_H

#include <owl\docmanag.h>#include <owl\docview.h>

class NSRefDocument ;
class NSCoopChartView ;

#include "nautilus\nsdocref.h"#include "nsbb\nsMView.h"#include "nsbb\nsPaneSplitter.h"#include "nsbb\nspatpat.h"#include "nsepisod\nsCoopChart.h"
//
//  ------------------  DOCUMENT  ------------------
//

class NSCoopChartDocument : public NSRefDocument{
	public:

		NSCoopChartDocument(TDocument* parent, NSDocumentInfo* pDocumentInfo,    					NSDocumentInfo* pDocHtmlInfo, NSContexte* pCtx, bool bROnly,              string sFileName = string("")) ;    NSCoopChartDocument(TDocument* parent = 0, NSContexte* pCtx = 0,              string sFileName = string(""), string sConcern = string("")) ;		~NSCoopChartDocument() ;

    bool	GenereHtml(string sPathHtml, string& sNomHtml, OperationType typeOperation,
    						string sAdresseCorresp = "", string sPathDest = "") ;
    bool  GenereHtmlText(string& sHtmlText) ;

    bool   savePatpatho() ;
    bool   buildPatPatho() ;
    bool   updatePatPatho() ;

		// M�thodes virtuelles de TDocument    bool   Open(int mode, const char far *path = 0)   { return true ; }    bool   Close()                                    { return true ; }

		bool   IsOpen()                                   { return true ; }    void   invalidateViews(string sReason, string sReference = string("")) ;    string getFileName() ;    void   initCardsFromFilename(string sFileName) ;    void   initCards() ;    NSCoopCardArray* getCards() { return _pQoLInformation->getCards() ; }    NSCoopLineArray* getLines() { return _pQoLInformation->getLines() ; }    PatPathoIter     getPptLocationForScore() ;    PatPathoIter     getPptScore() ;    NSCoopCard*      getCardForLexique(string sLexique) ;    NSCoopCard*      getGenericCardForCode(string sLexique, string sCode) ;    NSCoopLine*      getLine(int iLineNumber) ;    string           getRootConcept() { return _pQoLInformation->getRootConcept() ; }  protected:    NSQualityOfLifeInformation *_pQoLInformation ;    string          _sConcern ;    string          _sTimeIntervalUnit ;    int             _iTimeIntervalDuration ;    PatPathoIter    getPptLocationForCard(NSCoopCard *pCard) ;    void            addCardToPatpatho(NSCoopCard *pCard) ;    void            addScoreToPatpatho() ;    int             calculateGlobalScore() ;};

// This is the window
//
class NSCoopCardWindow : public TWindow, public NSRoot
{
  public :

    NSCoopCardWindow(NSContexte* pCtx, NSCoopChartView* pMainView, NSCoopCard* pCard) ;
    ~NSCoopCardWindow() ;

    void    SetupWindow() ;

    void    reinit() ;

    void    Paint(TDC&, bool, NS_CLASSLIB::TRect& RectangleAPeindre) ;
	  void    EvMouseMove(uint modKeys, NS_CLASSLIB::TPoint& point) ;
	  void    EvRButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;
	  void    EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;
	  void    EvSize(uint sizeType, ClassLib::TSize& size) ;
	  void    EvSetFocus(THandle hWndLostFocus /* may be 0 */) ;
	  void    EvLButtonUp(uint modKeys, NS_CLASSLIB::TPoint& point) ;
	  void    EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
	  // void EvTimer(uint timerId) ;
	  void    EvVScroll(UINT scrollCode, UINT thumbPos, HWND hWndCtl) ;
	  LRESULT EvMouseWheel(WPARAM wparam, LPARAM lparam) ;
    void    EvKeyDown(uint key, uint repeatCount, uint flags) ;
	  void    EvSysKeyDown(uint key, uint repeatCount, uint flags) ;
	  void    CmHelp() ;

    void    setCheck(int iScore) ;
    void    setCardScore() ;

    NSCoopCardButton* hitButtonTest(NS_CLASSLIB::TPoint& point) ;

    int     getFixedWidth()  { return _iFixedWidth ;  }
    int     getFixedHeight() { return _iFixedHeight ; }
    int     getScore()       { return _iScore ;       }

  protected:

    int              _iScore ;

    NSCoopChartView* _pMainView ;

    OWL::TDib*       _pBackBmp ;

    int              _iFixedWidth ;
    int              _iFixedHeight ;

    NSCoopCard*      _pCoopCard ;

  DECLARE_RESPONSE_TABLE(NSCoopCardWindow) ;
} ;

typedef vector<NSCoopCardWindow*>        NSCoopCardWindowVector ;
typedef NSCoopCardWindowVector::iterator CoopCardWindowIter ;
typedef NTArray<NSCoopCardWindow>        NSCoopCardWindowArray ;

//
//  ------------------  VIEW  ------------------
//

class NSCoopChartView : public NSMUEView{
	public:

		// Constructeur - Destructeur		NSCoopChartView(NSCoopChartDocument& doc, TWindow *parent = 0) ;
		~NSCoopChartView() ;

    void CmOk() ;
    void CmCancel() ;
		// Red�finiton des fonctions virtuelles de TView		static LPCSTR   StaticName()   { return "NSCoopChartView" ; }
		const char      *GetViewName() { return StaticName() ; }
		TWindow*        GetWindow()    { return (TWindow*) this ; }
		bool            CanClose();           // de TEditFile
    void            EvClose() ;
		bool            SetDocTitle(const char far* docname, int index)
		{
			return OWL::TWindow::SetDocTitle(docname, index) ;
		}
    void            setViewName() ;

    void            EvDestroy();
    void            SetWindowPosit();
    void            RecordWindowPosit();

		void            EvSetFocus(HWND hWndLostFocus);    void            focusFct() ;		void            EvMouseMove(uint modKeys, NS_CLASSLIB::TPoint& point);
                        // Fonctions de r�ponse aux evts
		void            EvSize(uint sizeType, ClassLib::TSize &size);
		void            EvMove(ClassLib::TPoint& clientOrigin);
		void            EvWindowPosChanged(WINDOWPOS far& windowPos);
		void            EvPaint();
    void            EvTimer(uint timerId) ;
		void            gotMoved();
    void            CmHelp() ;
    void            cardChanged() ;

    void            reloadView(string sReason, string sReference = string("")) ;
    void            switchToNextWindow() ;
    void            switchToPreviousWindow() ;
    void            cardJustValidated() ;

    void            setCardsScores() ;

		NSCoopChartDocument* getDoc()         { return _pCoopDoc ; }    NSCoopCardWindow*    getCurrentCard() { return _pCurrentWindow ; }	protected:
		// Variables
		NSCoopChartDocument*   _pCoopDoc ; // Document pointer    NSCoopCardWindowArray* _pCardWindowsArray ;    NSCoopCardWindow*      _pCurrentWindow ;    int                    _iMaxCardWidth ;    int                    _iMaxCardHeight ;    int                    _iTopMargin ;    int                    _iLeftMargin ;    int                    _iTopDelta ;    int                    _iLeftDelta ;    bool bSetupToolBar ;
		// Remplissage de la vue    void FillViewData() ;
    void SetupWindow() ;
    void SetupToolBar() ;
    void SetupTxtBar() ;
    void InitFormatFont() ;

		// view event handlers		bool VnIsWindow(HWND hWnd) ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;		void EvChar(uint key, uint repeatCount, uint flags) ;

	DECLARE_RESPONSE_TABLE(NSCoopChartView) ;};

#endif		// __NSCOOPCHARTDV_H
