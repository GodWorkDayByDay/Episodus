// NSF16Dlg : dialogues des fiches 16XX
//////////////////////////////////////////////////////

#ifndef __NSF16DLG_H
#define __NSF16DLG_H

#if defined(_DANSCPTADLL)
	#define _CLASSELEXI __export
#else
	#define _CLASSELEXI __import
#endif

#include <owl\edit.h>
#include <owl\checkbox.h>
#include <owl\groupbox.h>
#include <owl\listbox.h>
#include <owl\listwind.h>
#include <owl\scrollba.h>
#include <owl\combobox.h>

#include "nsbb\nsednum.h"
#include "nscompta\nscpta.h"     // classes NSCompt et NSFact
#include "nscompta\nsfsedlg.h"

//
// Dialogue de la fiche FSE1610
//
class _CLASSELEXI CreerFse1610Dialog : public NSUtilDialog
{
  public:

    NSFse1610Data*		pData;
    NSVarCompta*			pVar;

    NSCodPrestArray* pCodeArray ;
    int              nbCode ;
    NSComboArray*		 pLieuArray ;
    NSComboArray*		 pComplArray ;
    NSComboArray*		 pQualifArray ;

    // variables de saisie
    NSUtilEditDate*  pDateExe ;
    NSUtilEditHeure* pHeureExe ;
    TComboBox*			 pLieuExe ;
    TComboBox*			 pQualif ;
    TComboBox*			 pCode ;
    NSUtilEditSomme* pCoeff ;
    NSUtilEdit2*		 pDivis ;
    NSUtilEdit2*		 pQuantite ;
    TComboBox*			 pCompl ;
    NSUtilEdit2*		 pDenombr ;
    NSUtilEditSomme* pMontant ;
    TStatic*				 pSigle ;

    CreerFse1610Dialog(TWindow* pere, NSContexte* pCtx, NSVarCompta* pVarCompt) ;
    ~CreerFse1610Dialog() ;

    void SetupWindow() ;
    bool InitCodeArray() ;
    void CalculMontant() ;

    void CmOk() ;
    void CmCancel() ;

  DECLARE_RESPONSE_TABLE(CreerFse1610Dialog) ;
};
//
//
class _CLASSELEXI InitFse1610Dialog : public NSUtilDialog
{
	public:

   NSFse1610Data*		pData ;
   NSVarCompta*			pVar ;
   string           sCodeExamen ;

   NSCodPrestArray* pCodeArray ;
   int					    nbCode ;

   // variables de saisie
   NSUtilEditDate*	pDateExe ;
   NSUtilEditHeure*	pHeureExe ;
   NSUtilLexique*		pExamen ;
   TComboBox*			  pCode ;
   NSUtilEditSomme* pCoeff ;
   NSUtilEdit2*			pDivis ;
   NSUtilEditSomme* pMontant ;
   TStatic*				  pSigle ;

   InitFse1610Dialog(TWindow* pere, NSContexte* pCtx, string sCodeExam) ;
   ~InitFse1610Dialog() ;

   void SetupWindow() ;
   bool InitCodeArray() ;
   void CalculMontant() ;

   void CmOk() ;
   void CmCancel() ;

  DECLARE_RESPONSE_TABLE(InitFse1610Dialog) ;
};

//
//
class _CLASSELEXI CreerFse1620Dialog : public NSUtilDialog
{
	public:

   NSFse1620Data*		pData;
   NSVarCompta*			pVar;

   NSCodPrestArray* pCodeIfdArray;
   int					    nbCode;

   // variables de saisie
   NSUtilEditDate*	pDate;
   NSUtilEditHeure*	pHeure;
   TComboBox*			  pCodeIfd;
   NSUtilEdit2*			pQuantite;
   NSUtilEditSomme*	pMontant;
   TStatic*				  pSigle;

   CreerFse1620Dialog(TWindow* pere, NSContexte* pCtx, NSVarCompta* pVarCompt);
   ~CreerFse1620Dialog();

   void SetupWindow();
   bool InitCodeArray();
   void CalculMontantIfd();

   void CmOk();
   void CmCancel();

   DECLARE_RESPONSE_TABLE(CreerFse1620Dialog);
};

//
//
class _CLASSELEXI CreerFse1630Dialog : public NSUtilDialog
{
	public:

   NSFse1630Data*		pData;
   NSVarCompta*			pVar;

   NSCodPrestArray* pCodeIkArray;
   int					    nbCode;

   // variables de saisie
   NSUtilEditDate*	pDate;
   NSUtilEditHeure*	pHeure;
   TComboBox*			  pCodeIk;
   NSUtilEdit2*			pNbreKm;
   NSUtilEditSomme* pMontant;
   TStatic*				  pSigle;

   CreerFse1630Dialog(TWindow* pere, NSContexte* pCtx, NSVarCompta* pVarCompt);
   ~CreerFse1630Dialog();

   void SetupWindow();
   bool InitCodeArray();
   void CalculMontantIk();

   void CmOk();
   void CmCancel();

   DECLARE_RESPONSE_TABLE(CreerFse1630Dialog);
};

//

class _CLASSELEXI CreerFseCCAMDialog : public NSUtilDialog
	public :

  	string           sExam ;

  	NSFseCCAMData*	 pData ;
   	NSVarCompta*		 pVar ;

   	// variables de saisie
   	NSUtilEditDate*	 pDate ;
   	NSUtilEdit2*     pPourcent ;
   	TStatic*				 pSigle ;
   	NSCcamInfo*      pCcamSelect ;
   	CreerFseCCAMDialog(TWindow* pere, NSContexte* pCtx, NSVarCompta* pVarCompt, string sExamen = "") ;
   	~CreerFseCCAMDialog() ;

   	void SetupWindow() ;
   	void RechercheLibelle(string sCode, string* pLibelle) ;
   	void CmCalculMontant() ;

	DECLARE_RESPONSE_TABLE(CreerFseCCAMDialog) ;
};

class _CLASSELEXI CreerFseLibreDialog : public NSUtilDialog
{
	public :

  	string           sExam ;

  	NSFseLibreData*	 pData ;
   	NSVarCompta*		 pVar ;

   	// variables de saisie
   	NSUtilEditDate*	 pDate ;
    NSUtilEditSomme* pMontantF ;
   	NSUtilEdit2*     pPourcent ;
    TStatic*				 pSigleF ;
   	NSLibreInfo*     pLibreSelect ;
   	CreerFseLibreDialog(TWindow* pere, NSContexte* pCtx, NSVarCompta* pVarCompt, string sExamen = string("")) ;
   	~CreerFseLibreDialog() ;

   	void SetupWindow() ;
   	void RechercheLibelle(string sCode, string* pLibelle) ;
   	void CmCalculMontant() ;

	DECLARE_RESPONSE_TABLE(CreerFseLibreDialog) ;
} ;

class NSLotsWindow ;

class _CLASSELEXI CreerFseMatDialog : public NSUtilDialog
{
	public :

  	string           _sExam ;

  	NSFseMatData*	   _pData ;
   	NSVarCompta*		 _pVar ;

    NSLotsWindow*    _pChoixMatBox ;
		NSLotArray       _aChoixMatArray ;
    NSLotsWindow*    _pSelectMatBox ;
		NSLotArray       _aSelectMatArray ;

   	// variables de saisie
   	NSUtilEditSomme* _pMontantE ;
   	TStatic*				 _pSigleE ;
    OWL::TButton*    _pChoiceButton ;

    bool             _bGlobalList ;

   	NSLotInfo*       _pMatSelect ;
   	CreerFseMatDialog(TWindow* pere, NSContexte* pCtx, NSVarCompta* pVarCompt) ;
   	~CreerFseMatDialog() ;

   	void SetupWindow() ;
   	void RechercheLibelle(string sCode, string* pLibelle) ;
    bool InitLotArray() ;
    bool InitGlobalLotArray() ;
    void LVNColumnclickChoix(TLwNotify& lwn) ;
    void LVNColumnclickSelected(TLwNotify& lwn) ;
    void CmElargir() ;

	DECLARE_RESPONSE_TABLE(CreerFseMatDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les codes CLAM)
//
class _CLASSELEXI NSLotsWindow : public TListWindow
{
	public:

		NSLotsWindow(CreerFseMatDialog* pere, int resId) ;
		~NSLotsWindow() {}

    void SetupWindow() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

    bool IsNaturalySorted() const { return _bNaturallySorted ; }
    int  GetSortedColumn()  const { return _iSortedColumn ; }

    void SetNaturalySorted(bool bS) { _bNaturallySorted = bS ;   }
    void SetSortedColumn(int iCol)  { _iSortedColumn    = iCol ; }

  protected:

    CreerFseMatDialog* _pDlg ;

    bool _bNaturallySorted ;
    int  _iSortedColumn ;

	DECLARE_RESPONSE_TABLE(NSLotsWindow) ;
};

#endif // fin de NSF16Dlg.h
