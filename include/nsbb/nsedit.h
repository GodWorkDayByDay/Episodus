#ifndef __NSEDIT_H#define __NSEDIT_H

class Message ;
class NSControle ;

// #include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\edit.h>
#include <owl\validate.h>
#include <string.h>
#include <cstring.h>

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

#include "partage\ns_timer.h"
#include "nsbb\nsbbtran.h"
#include "nsbb\nsbb_glo.h"
#include "nsbb\nsexport.h"

#ifndef __DATE_SEPARATION
#define __DATE_SEPARATION
const char dateSeparationMARK = '/';
#endif

#ifndef __HEURE_SEPARATION
#define __HEURE_SEPARATION
const char heureSeparationMARK = ':';
#endif

//#define nbMARK    = 'N';   // Saisie de chiffres pour l'Edit
//#define charMARK  = 'C';   // Saisie de caract�res pour l'Edit  TStatic
//#define dateMARK  = 'D';   // Edit double bouton

class _NSBBCLASSE NSEdit : public OWL::TEdit, public NSRoot
{
  public:

    NSControle* _pControle ;
    char        _szType[25] ; // Type de contr�le EDIT
    string      _sContenuBrut, _sContenuTransfert, _sType ;
    bool        _bEncoursEdition ;
    TWindow*    _parentEdit ;
    bool        _bValidContent ;
    bool        _bCurrentlyWarning ;
    bool        _bHistoryOpen ;
    string      _sLang ;

    bool        _bWinStd ;       // Gestion standard windows

    // Constructeur et destructeur
    NSEdit(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit, string sUserLang) ;
    NSEdit(NSContexte* pCtx, TWindow* parent, int resId, string sUserLang) ;
    NSEdit(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit,
                  const char far* text, int x, int y, int w, int h, string sUserLang,
                  uint textLimit = 0, bool multiline = false, TModule* module = 0) ;
    virtual ~NSEdit() ;

    uint    Transferer(TTransferDirection direction, CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
    uint    TempTransferer(CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
    void    activeControle(int activation, Message* pMessage = 0) ;
    bool    canWeClose() ;
    void    SetupWindow() ;

    void initCommonData() ;

    WNDTYPE donneType() { return(isEdit) ; }

    virtual void donneBrut() ;        // Passe des donn�es saisies aux donn�es
    virtual void donneTransfert() ;   // codables par NAUTILUS et vice versa

    // child id notification handled at the child
    //
    void executeKillFocusBehaviour() ;

    void EvKillFocus(HWND hWndGetFocus) ;
    void EvSetFocus(HWND hWndLostFocus) ;

    //fonctions permettant � la touche ENTREE le m�me effet que TAB
    void EvKeyUp(uint key, uint repeatcount, uint flags) ;
    void EvKeyDown(uint key, uint repeatcount, uint flags) ;
    uint EvGetDlgCode(MSG far* ) ;
    void EvChar(uint key, uint repeatCount, uint flags) ;

    void   EvTimer(uint id) ;

    HBRUSH getCtlColor(HDC hdc) ;

    void        setControl(NSControle* pCtrl)  { _pControle = pCtrl ; }
    NSControle* getControl()                   { return _pControle ; }

    void        setContenuTransfert(string sC) { _sContenuTransfert = sC ; }
    string      getContenuTransfert()          { return _sContenuTransfert ; }
    void        setContenuBrut(string sC)      { _sContenuBrut = sC ; }
    string      getContenuBrut()               { return _sContenuBrut ; }

    bool isWaitingForOb1()              { return _bWaitingForOb1 ; }
    void setWaitingForOb1(bool bW) ;

    bool needUserValidation()           { return _bNeedUserValidation ; }
    void setNeedUserValidation(bool bN) { _bNeedUserValidation = bN ; }

    bool hasBeenValidated()             { return _bUserValidated ; }
    void setHasBeenValidated(bool bH)   { _bUserValidated = bH ; }

    string GetText(size_t iSizeLimit = 0) ;
    void   SetText(const string sContent) ;

  protected:

    bool _bWaitingForOb1 ;        // Are we waiting for a blackboard auto filling?
    bool _bNeedUserValidation ;   // Does user need to validate automatic entry?
    bool _bUserValidated ;        // Has it been validated by user?

    NS_CLASSLIB::TColor _StandardBackgroundColor ;
    NS_CLASSLIB::TColor _StandardTextColor ;

    NS_CLASSLIB::TColor _StartWaitingBackgroundColor ;
    NS_CLASSLIB::TColor _StartWaitingTextColor ;
    NS_CLASSLIB::TColor _EndWaitingBackgroundColor ;
    NS_CLASSLIB::TColor _EndWaitingTextColor ;
    NS_CLASSLIB::TColor _CurrentWaitingBackgroundColor ;
    NS_CLASSLIB::TColor _CurrentWaitingTextColor ;
    int  _iGlowingDeciles ;

    NS_CLASSLIB::TColor _NeedValidationBackgroundColor ;
    NS_CLASSLIB::TColor _NeedValidationTextColor ;

    void initColors() ;
    void initDefaultColors() ;
    void ChangeGlowBackground() ;
    int  getDecileInBetween(int iColor1, int iColor2, int iDecile) ;

	DECLARE_RESPONSE_TABLE(NSEdit) ;
};

class _NSBBCLASSE NSEditDate : public NSEdit
{
  public:

    // Constructeur et destructeur
    NSEditDate(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit, string sUserLang, char cRefDate = 'F') ;
    NSEditDate(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit,
                  const char far* text, int x, int y, int w, int h, string sUserLang, char cRefDate = 'F',
                  uint textLimit = 0, bool multiline = false, TModule* module = 0) ;
    ~NSEditDate() ;

    void    donneBrut() ;        // Passe des donn�es saisies aux donn�es
    void    donneTransfert() ;   // codables par NAUTILUS et vice versa

    void    EvChar(uint key, uint repeatCount, uint flags) ;
    void    EvKeyDown(uint key, uint repeatCount, uint flags) ;
    void    EvKillFocus(HWND hWndGetFocus) ;
    void    actionForKillFocus(bool &bCanLetItBe) ;
    bool    canWeClose() ;

    void    executeKillFocusBehaviour() ;

    WNDTYPE donneType() { return(isEditDate) ; }

  private :

    char    cRefYear ;
    string  sFormat ;

	DECLARE_RESPONSE_TABLE(NSEditDate) ;
};

class _NSBBCLASSE NSEditDateHeure : public NSEdit
{
  public:

    // Constructeur et destructeur
    NSEditDateHeure(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit, string sUserLang, char cRefDate = 'F') ;
    NSEditDateHeure(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit,
                  const char far* text, int x, int y, int w, int h, string sUserLang, char cRefDate = 'F',
                  uint textLimit = 0, bool multiline = false, TModule* module = 0) ;
    ~NSEditDateHeure() ;

    void    donneBrut() ;        // Passe des donn�es saisies aux donn�es
    void    donneTransfert() ;   // codables par NAUTILUS et vice versa

    void    EvChar(uint key, uint repeatCount, uint flags) ;
    void    EvKeyDown(uint key, uint repeatCount, uint flags) ;
    void    EvKillFocus(HWND hWndGetFocus) ;
    void    actionForKillFocus(bool &bCanLetItBe) ;

    void    executeKillFocusBehaviour() ;

    bool    canWeClose() ;

    WNDTYPE donneType() { return(isEditDateHeure) ; }

  private :

    char    cRefYear ;
    string  sFormat ;

  DECLARE_RESPONSE_TABLE(NSEditDateHeure) ;
};

class _NSBBCLASSE NSEditHeure : public NSEdit
{
  public:

    // Constructeur et destructeur
    NSEditHeure(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit, string sUserLang) ;
    NSEditHeure(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit,
                  const char far* text, int x, int y, int w, int h, string sUserLang,
                  uint textLimit = 0, bool multiline = false, TModule* module = 0) ;
    ~NSEditHeure() ;

    void donneBrut() ;        // Passe des donn�es saisies aux donn�es
    void donneTransfert() ;   // codables par NAUTILUS et vice versa

    void EvChar(uint key, uint repeatCount, uint flags) ;
    void EvKillFocus(HWND hWndGetFocus) ;
    void actionForKillFocus(bool &bCanLetItBe) ;

    void executeKillFocusBehaviour() ;

    string sFormat ;

	DECLARE_RESPONSE_TABLE(NSEditHeure) ;
};

class _NSBBCLASSE NSEditNoLex : public NSEdit{  public:

    // Constructeur et destructeur    NSEditNoLex(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit, string sUserLang, int iTextLimit = 15) ;
    NSEditNoLex(NSContexte* pCtx, TWindow* parent, int resId, char* szTypeEdit,
                  const char far* text, int x, int y, int w, int h, string sUserLang,
                  uint textLimit = 0, bool multiline = false, TModule* module = 0);
    ~NSEditNoLex() ;

    WNDTYPE     donneType() { return(isEditNoLexique) ; }

    uint    Transferer(TTransferDirection direction, CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
    uint    TempTransferer(CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
    void    activeControle(int activation, Message* pMessage = 0) ;

    void    donneBrut() ;        // Passe des donn�es saisies aux donn�es
    void    donneTransfert() ;   // codables par NAUTILUS et vice versa
    void    EvKillFocus(HWND hWndGetFocus) ;    void    actionForKillFocus(bool &bCanLetItBe) ;    void    executeKillFocusBehaviour() ;    string  getProperFirstName(string sInitialEntry) ;
  DECLARE_RESPONSE_TABLE(NSEditNoLex) ;};
class _NSBBCLASSE NSStatic : public OWL::TStatic, public NSRoot
{
	public:

		NSControle* pControle ;
    TWindow* 	parentEdit ;

    // Constructeur et destructeur
    NSStatic(NSContexte* pCtx, TWindow* parent, int resId) ;
    NSStatic(NSContexte* pCtx, TWindow* parent, int resId, const char far* title,
                    int x, int y, int w, int h,
                    uint textLimit = 0, TModule* module = 0) ;
    ~NSStatic() ;

    uint    Transferer(TTransferDirection direction, CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
    uint    TempTransferer(CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
    bool    canWeClose() ;
    void    SetupWindow() ;

    WNDTYPE donneType() { return(isStatic) ; }

    void    EvSetFocus(HWND hWndLostFocus) ;

	DECLARE_RESPONSE_TABLE(NSStatic) ;
};

class _NSBBCLASSE NSModeStatic : public OWL::TStatic, public NSRoot
{
	public:

    // Constructeur et destructeur
    NSModeStatic(NSContexte* pCtx, TWindow* parent, int resId) ;
    NSModeStatic(NSContexte* pCtx, TWindow* parent, int resId, const char far* title,
                    int x, int y, int w, int h,
                    uint textLimit = 0, TModule* module = 0) ;
    ~NSModeStatic() ;

    bool    canWeClose() ;
    void    SetupWindow() ;
    bool    IdleAction(long count) ;

	DECLARE_RESPONSE_TABLE(NSModeStatic) ;
};

#endif  // __NSEDIT_H
