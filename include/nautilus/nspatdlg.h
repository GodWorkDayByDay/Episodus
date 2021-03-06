#ifndef __NSPATDLG_H#define __NSPATDLG_H

class NSUtilUpDownEdit ;
class NSComboBoxClassif ;

#include <owl\dialog.h>#include <owl\radiobut.h>
#include <owl\edit.h>
#include <owl\checkbox.h>
#include <owl\groupbox.h>
#include <owl\listbox.h>
#include <owl\listwind.h>
#include <owl\scrollba.h>

// #include "nsbb\nsednum.h"// #include "nsbb\nscomboutil.h"// #include "nautilus\nsannexe.h"
#include "nautilus\nsperary.h"
#include "nsbb\nslistwind.h"
#include "nsepisod\nspatdlgknl.h"

const char GlobalPatient = '-';

class NSBloques;
//
// Cr�ation / Modification des correspondants
//

/*
class CreerCorrespDialog : public NSUtilDialog
{
    public:

	    NSCorrespondantData* 	pData;
        NSAdressesInfo*		 	pAdresseInfo;

        OWL::TGroupBox*			pSexe;
        OWL::TGroupBox*			pTitre;

        NSUtilEdit*			 	pNom;
        NSUtilEdit*			 	pPrenom;
        OWL::TRadioButton*	  	pSexeM;
        OWL::TRadioButton*    	pSexeF;

        OWL::TCheckBox*			pAdresse;

        OWL::TRadioButton*      pSansTitre;
        OWL::TRadioButton*		pTitre1;        OWL::TRadioButton*		pTitre2;
        OWL::TRadioButton*		pTitre3;
        OWL::TRadioButton*		pTitre4;
        OWL::TRadioButton*		pTitre5;
        OWL::TRadioButton*		pTitre6;

        NSEditNumTel*		 	pTelPor;
        NSEditNumTel*		 	pTelBur;
        NSEditNum*			 	pNbExpl;
        NSUtilEdit*			 	pEMail;

        // NSUtilEdit*				pFonction;
        NSUtilLexique*		 	pFonction;
        OWL::TRadioButton*	  	pActif;
        bool                 	bActif;

		CreerCorrespDialog(TWindow*, NSContexte* pCtx, TModule* module = 0);
        ~CreerCorrespDialog();

        void SetupWindow();
        void EvClose();

        void CmAdresse();
        void CmActif();
        void CmOk();
        void CmCancel();

        void repercuteActif();

    DECLARE_RESPONSE_TABLE(CreerCorrespDialog);
};

*/

// -----------------------------------------------------------------------------
//
// Code utilisateur
//
// -----------------------------------------------------------------------------
class CodeUtilisateurDialog : public NSUtilDialog
{
 public:
  string      sCodeUtil ;

  NSUtilEdit   *pCode ;
  NSUtilEdit   *pConfirm ;

  OWL::TStatic *pPassText ;
  OWL::TStatic *pConfirmText ;

  CodeUtilisateurDialog(TWindow *, string sCode, NSContexte *pCtx) ;
  ~CodeUtilisateurDialog() ;

  void        SetupWindow() ;
  void        CmOk() ;
  void        CmCancel() ;

  DECLARE_RESPONSE_TABLE(CodeUtilisateurDialog);
} ;

// -----------------------------------------------------------------------------
//
// Modification du Code utilisateur
//
// -----------------------------------------------------------------------------
class ModifCodeUtilisateurDialog : public NSUtilDialog
{
    public:

        string      sCodeUtil ;
        NSUtilEdit  *pCode ;

        ModifCodeUtilisateurDialog(TWindow *, NSContexte *pCtx) ;
        ~ModifCodeUtilisateurDialog() ;

        void        SetupWindow() ;
        void        CmOk() ;
        void        CmCancel() ;

    DECLARE_RESPONSE_TABLE(ModifCodeUtilisateurDialog);
} ;

// -----------------------------------------------------------------------------
//// Cr�ation / Modification des utilisateurs
//
// -----------------------------------------------------------------------------

class CreerUtilisateurDialog : public NSUtilDialog
{
	public:

		NSUtilisateurData   *pData ;

		string              sLogin ;
    string              sPasswd ;
    string              sUserType ;
    string              sPasswordType ;
    string              sDatePasswordCreation ;
    string              sValidityDuration ;
    string              sLang ;

    OWL::TGroupBox      *pTitre ;
    OWL::TGroupBox      *pCivilProf ;
    OWL::TGroupBox      *pCivil ;
    int                 iTitre ;
    string              sTitre ;
    string              sCivilProf ;
    string              sCivil ;

    OWL::TStatic        *pNameText ;
    NSUtilEdit          *pNom ;
    OWL::TStatic        *pFirstNameText ;
    NSUtilEdit          *pPrenom ;
    OWL::TStatic        *pAdeliText ;
    NSUtilEdit          *pAdeli ;
    OWL::TStatic        *pRppsText ;
    NSUtilEdit          *pRpps ;

    // le login existe qu'en version MUE
    OWL::TStatic        *pUserIdText ;
    NSUtilEdit          *pLogin ;
    OWL::TStatic        *pJobText ;
    NSUtilLexique       *pMetier ;
    OWL::TStatic        *pSpecText ;
    NSUtilLexique       *pSpec ;
    OWL::TGroupBox      *pSexe ;
    OWL::TRadioButton   *pSexe1 ;
    OWL::TRadioButton   *pSexe2 ;

    // Password
    OWL::TButton        *pCode ;

    // Role
    OWL::TGroupBox      *pRole ;
    OWL::TRadioButton   *pUserRole ;
    OWL::TRadioButton   *pAdminRole ;

    // Compte utilisateur
    OWL::TGroupBox      *pAccount ;
    OWL::TRadioButton   *pPwdTemp ;
    OWL::TRadioButton   *pPwdChange ;
    OWL::TStatic        *pDaysText ;
    NSUtilUpDownEdit    *pPwdChangeUpDown ;
    OWL::TRadioButton   *pPwdFix ;
    OWL::TRadioButton   *pPwdNoChange ;
    OWL::TRadioButton   *pPwdCancel ;
    OWL::TRadioButton   *pPwdLock ;

    OWL::TStatic        *pLanguageText ;
    NSComboBoxClassif   *pLangues ;

    // Messagerie et titres
    OWL::TStatic        *pMailText ;
    NSUtilEdit          *pEMail ;
    OWL::TRadioButton   *pTitre1 ;
    OWL::TRadioButton   *pTitre2 ;
    OWL::TRadioButton   *pTitre3 ;
    OWL::TRadioButton   *pTitre4 ;
    OWL::TRadioButton   *pTitre5 ;
    OWL::TRadioButton   *pTitre6 ;
    OWL::TRadioButton   *pTitre7 ;
    OWL::TRadioButton   *pTitre8 ;
    OWL::TRadioButton   *pTitre9 ;

    CreerUtilisateurDialog(TWindow *, NSContexte *pCtx, OWL::TModule *module = 0) ;
    ~CreerUtilisateurDialog() ;

    void                SetupWindow() ;
    void                initTexts() ;
    void                EvClose() ;

    void                CmTitre() ;
    void                CmCivilProf() ;
    void                CmCivil() ;
    void                CmRole() ;
    void                CmAccount() ;
    void                CmCode() ;
    void                CmOk() ;
    void                CmCancel() ;
    void                ajouteDroit(string& sTypeDroit, char droit) ;
    void                enleveDroit(string& sTypeDroit, char droit) ;
    void                initRole() ;
    void                initAccount() ;

    string getLogin()    { return sLogin ; }
    string getPasswd()   { return sPasswd ; }
    string getUserType() { return sUserType ; }
    string getPassType() { return sPasswordType ; }
    string getPassDate() { return sDatePasswordCreation ; }
    string getValidity() { return sValidityDuration ; }
    string getTitre()    { return sTitre ; }
    string getCivilPro() { return sCivilProf ; }
    string getCivil()    { return sCivil ; }

    void   setLogin(string sVal)    { sLogin = sVal ; }
    void   setPasswd(string sVal)   { sPasswd = sVal ; }
    void   setUserType(string sVal) { sUserType = sVal ; }
    void   setPassType(string sVal) { sPasswordType = sVal ; }
    void   setPassDate(string sVal) { sDatePasswordCreation = sVal ; }
    void   setValidity(string sVal) { sValidityDuration = sVal ; }
    void   setTitre(string sVal)    { sTitre = sVal ; }
    void   setCivilPro(string sVal) { sCivilProf = sVal ; }
    void   setCivil(string sVal)    { sCivil = sVal ; }

  DECLARE_RESPONSE_TABLE(CreerUtilisateurDialog) ;
} ;

class CreerUtilSimpleDialog : public NSUtilDialog
{
    public:

        NSUtilisateurData   *pData ;

        string              sLogin;
        string              sPasswd;
        string              sRole;
        string              sPasswordType;
        string              sDatePasswordCreation;
        string              sValidityDuration;

        OWL::TGroupBox      *pTitre ;
        OWL::TGroupBox      *pCivilProf ;
        OWL::TGroupBox      *pCivil ;
        int                 iTitre ;
        string              sTitre ;
        string              sCivilProf ;
        string              sCivil ;

        NSUtilEdit          *pNom ;
        NSUtilEdit          *pPrenom ;

        // infos diverses
        NSUtilLexique       *pMetier ;
        NSUtilLexique       *pSpec ;
        OWL::TGroupBox      *pSexe ;
        OWL::TRadioButton   *pSexe1 ;
        OWL::TRadioButton   *pSexe2 ;

        // Password
        OWL::TButton        *pCode ;

        // Messagerie et titres
        NSUtilEdit          *pEMail ;
        OWL::TRadioButton   *pTitre1 ;
        OWL::TRadioButton   *pTitre2 ;
        OWL::TRadioButton   *pTitre3 ;
        OWL::TRadioButton   *pTitre4 ;
        OWL::TRadioButton   *pTitre5 ;
        OWL::TRadioButton   *pTitre6 ;
        OWL::TRadioButton   *pTitre7 ;
        OWL::TRadioButton   *pTitre8 ;
        OWL::TRadioButton   *pTitre9 ;

        CreerUtilSimpleDialog(TWindow *, NSContexte *pCtx, OWL::TModule *module = 0) ;
        ~CreerUtilSimpleDialog() ;

        void                SetupWindow() ;
        void                EvClose() ;

        void                CmTitre() ;
        void                CmCivilProf() ;
        void                CmCivil() ;
        void                CmCode() ;
        void                CmOk() ;
        void                CmCancel() ;

  DECLARE_RESPONSE_TABLE(CreerUtilSimpleDialog) ;
} ;

//
// Importation utilisateur depuis ligne de vie
//
class NSUserImportDialog : public NSUtilDialog
{
  public :

    NSUtilEdit* pLogin ;
    NSUtilEdit* pPasswd ;
    // NSUtilEdit*         pAdeli;
    // NSUtilEdit*         pNumLdv;
    bool 				isHached ;

    string      sLogin ;
    string      sPasswd ;
    // string              sAdeli;
    // string              sNumLdv;

    NSUserImportDialog(TWindow *, NSContexte *pCtx, OWL::TModule *module = 0) ;
    ~NSUserImportDialog() ;

    void SetupWindow() ;
    void CmOk() ;
    void CmCancel() ;
    void PasswordChange();

  DECLARE_RESPONSE_TABLE(NSUserImportDialog) ;
};

//
// Importation correspondant depuis ligne de vie
//
class NSCorrespImportDialog : public NSUtilDialog
{
	public :

		NSUtilEdit* pLogin ;
		NSUtilEdit* pPasswd ;
		NSUtilEdit* pAdeli ;
		NSUtilEdit* pNumLdv ;
		bool 		isHached ;

		string      sLogin ;
		string      sPasswd ;
		string      sAdeli ;
		string      sNumLdv ;

		NSCorrespImportDialog(TWindow *, NSContexte *pCtx, OWL::TModule *module = 0) ;
		~NSCorrespImportDialog() ;

		void        SetupWindow() ;
		void        CmOk() ;
		void        CmCancel() ;
		void		PasswordChange() ;

	DECLARE_RESPONSE_TABLE(NSCorrespImportDialog) ;
};

class NSPatientImportDialog : public NSUtilDialog
{
  public :

    NSUtilEdit* pLogin ;
    NSUtilEdit* pPasswd ;
    NSUtilEdit* pNumLdv ;
    // OWL::TButton*  		pMandat;

    string      sLogin ;
    string      sPasswd ;
    bool				isHached ; // Indique si le pasword est hache ou pas
    string      sNumLdv ;
    // bool                bMandat;

    NSPatientImportDialog(TWindow *, NSContexte *pCtx, OWL::TModule *module = 0) ;
    ~NSPatientImportDialog() ;

    void        SetupWindow() ;
    void        CmOk() ;
    // void 				CmCreateMandat();
    void        CmCancel() ;
    void				GetData(bool check);
    void				PasswordChange();

  DECLARE_RESPONSE_TABLE(NSPatientImportDialog) ;
};


//
// Classe ChercheListeUtilDialog -> pour la s�lection d'un utilisateur
//
class NSListUtilWindow;

class ChercheListeUtilDialog : public NSUtilDialog{
  public:

    NSListUtilWindow* pListeUtil ;
    NSUtiliArray*		  pUtilArray ;
    NSUtiliInfo*      pUtilSelect ;

    int					      nbUtil ;
    int					      UtilChoisi ;

    ChercheListeUtilDialog(TWindow* pere, NSContexte* pCtx, OWL::TModule* module = 0);
    ~ChercheListeUtilDialog();

    void SetupWindow();
    bool InitUtilArray();
    void InitListe();
    void AfficheListe();
    void LvnGetDispInfo(TLwDispInfoNotify& dispInfo);

    void CmOk();
    void CmCancel();

  DECLARE_RESPONSE_TABLE(ChercheListeUtilDialog);
};

//// Objet "ListWindow" avec gestion du double-click (pour les utilisateurs)
//
class NSListUtilWindow : public TListWindow
{
  public:

    ChercheListeUtilDialog* pDlg;

    NSListUtilWindow(ChercheListeUtilDialog* pere, int resId, OWL::TModule* module = 0);
    ~NSListUtilWindow();

    void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point);
    int  IndexItemSelect();

  DECLARE_RESPONSE_TABLE(NSListUtilWindow);
};

//// Classe PatCorDialog -> Correspondants du patient
//

class PatCorDialog : public NSUtilDialog
{
  public:

    NSUtilEdit*			pNomPatient ;
    NSCorrespArray* pCorrespBaseArray ;	// tableau initial, mis � jour par CmOk()
    NSCorrespArray*	pCorrespArray ;			// tableau tampon, contenant les modifs
    OWL::TListBox*	pListeCorresp ;
    bool					  bAjouter ;

    int					    CorrespChoisi ;
    string				  sNomPatient ;

		PatCorDialog(TWindow* pere, NSContexte* pCtx, string sNomLong, OWL::TModule* pModule = 0);
    ~PatCorDialog() ;

    void SetupWindow();
    void InitCorrespArray();
    void AfficheCorresp();
    bool ExisteCode(char* code);
    void EvPaint();

    void CmOk();
    void CmCancel();
    void CmAjouter();
    void CmSupprimer();
    void CmCreer();
    void CmModifier();
    void CmSelectCorresp();
    void CmCorrespDblClk();

  DECLARE_RESPONSE_TABLE(PatCorDialog);
};

/*
//// Classe ChercheListePatCorDialog -> pour la s�lection d'un correspondant parmi
//													les correspondants du patient
//

class NSListPatCorWindow;
class ChercheListePatCorDialog : public NSUtilDialog{
	public:

		NSListPatCorWindow* pListeCorresp ;
    NSPersonArray*      pCorrespArray ;
    NSPersonInfo*       pCorrespSelect ;

    int					 nbCorresp;
    int					 CorrespChoisi;

    ChercheListePatCorDialog(TWindow* pere, NSContexte* pCtx, TModule* module = 0) ;
    ~ChercheListePatCorDialog() ;

    void SetupWindow() ;
    bool InitPatCorArray() ;
    void InitListe() ;
    void AfficheListe() ;
    void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
    void CmAutreCorresp() ;

    void CmOk() ;
    void CmCancel() ;

  DECLARE_RESPONSE_TABLE(ChercheListePatCorDialog) ;
};

//// Objet "ListWindow" avec gestion du double-click (pour les correspondants)
//
class NSListPatCorWindow : public TListWindow
{	public:

		ChercheListePatCorDialog* pDlg ;

    NSListPatCorWindow(ChercheListePatCorDialog* pere, int resId, TModule* module = 0) ;
    ~NSListPatCorWindow() ;

    void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSListPatCorWindow) ;};
*/

/***************************************************************************/
class NSLVScrollBar;class NSRechNomEdit;
class NSRechPreEdit;
class NSRechNumEdit;
class NSRechCodeEdit;
class NSListPatWindow;
class NSListGroupWindow;
class NSNTiersListPatWindow;
class NSPersonsAttributesArray;

enum MODELISTEACT { todoNothing = 0, todoSearch, todoSynchro, todoMerge, todoImport };

//
// Objet "Boite de dialogue" root utilis� pour s�lectionner un patient au sein
// d'une liste (pour la recherche sur le serveur de groupe)
//
class NSListeClientGroupDialog : public NSUtilDialog
{
	public:

		int                nbNom ;
		bool               bVScroll ;
		string             sNssSelect ;
		DBIResult          ErrDBI ;

		string             _sNomPat ;
		string             _sPrenomPat ;

		NSBloques*         pBloques ;
		bool               verifBloque, donneMessage ;
		const char*        serviceName ;
		bool               bMustInit ;

		NSPatInfo*         pPatEnCours ;
		NSPatientArray*    pPatientsArray ;

		NSUtilEdit*        pNom ;              // recherche par nom
		NSUtilEdit*        pPrenom ;           // et pr�nom
		NSUtilEdit*        pIEP ;
		TStatic*           pTexte ;

		TStatic*           pCancel ;
		TStatic*           pReturn ;
		TStatic*           pButtonNom ;
		TStatic*           pButtonIep ;

		TStatic*           pButtonImport ;
		TStatic*           pButtonBack ;
		TStatic*           pButtonGrpSrch ;
		TStatic*           pButtonOpen ;
    TStatic*           pButtonMerge ;

		OWL::TRadioButton* pExactButton ;
		OWL::TRadioButton* pStartByButton ;

		NSListGroupWindow* pListe ;
		NSLVScrollBar*     pVScroll ;

		int                iSortedColumn ;
    bool               bNaturallySorted ;

		int                etat ;
    int                mode ;
		bool               bTrouveLocal ;
		bool               bTrouveGlobal ;
		bool               bListeLocal ;
		string             sIPPTrouve ;
		string             sIdLocal ;
		string             sIdGlobal ;
    string			       sPatientLocal ;
    string			       sPatientGlobal ;

    NSPersonsAttributesArray *pLastList ;

		NSListeClientGroupDialog(TWindow* parent, NSContexte* pCtx, NSPatInfo* pPat) ;
		~NSListeClientGroupDialog() ;

		void SetupWindow() ;
		void PrepareNomPrenom(string& sNomToCall, string& sPrenomToCall) ;
		void RechercheParIEP() ;
		void RechercheParNomPrenom() ;
    void Importation() ;
		void Importer() ;

		void InitListe() ;
		void AfficheListe(bool bLocal = true) ;
		void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
		void InitPatArray(NSPersonsAttributesArray *pList) ;

		void RechercheIEP(string sIEP) ;
		bool importPatientGroup(string sIPP) ;

		void GardeNss(int index) ;
		void RetrouvePatSelect() ;

		void setResearchOn() ;
		void setResearchOff() ;

		bool CanClose() ;
		void CmOk() ;
		void CmCancel() ;
    void CmBack() ;

    void LVNColumnclick(TLwNotify& lwn) ;
    void sortByName() ;
    void sortByBirthday() ;
    void sortBySex() ;

	DECLARE_RESPONSE_TABLE(NSListeClientGroupDialog) ;
};

class NSNTiersRechNomEdit ;

//
// Objet "Boite de dialogue" root utilis� pour s�lectionner un patient au sein
// d'une liste en mode NTiers
//
class NSNTiersRechPatDialog : public NSNTiersListePatDialog
{
	public:

		NSNTiersRechPatDialog(TWindow* parent, NSContexte* pCtx, NSPatInfo* pPat,
                         char* cResId = "IDD_NTLISTPA") ;
		~NSNTiersRechPatDialog() ;

		void SetupWindow() ;

		void Creer() ;
		void CmOk() ;

    void setDontEvenTryToOpen(bool bDETTO) { _bDontEvenTryToOpen = bDETTO ; }

  protected:

    bool _bDontEvenTryToOpen ;

	DECLARE_RESPONSE_TABLE(NSNTiersRechPatDialog);
};

//// Objet "Boite de dialogue" root utilis� pour s�lectionner un patient au sein
// d'une liste
//
class NSListePatDialog : public NSUtilDialog
{
    public:

   	    int				 nbNom;
        bool			 bVScroll;
        string			 sNssSelect;
        DBIResult 		 ErrDBI;

        char			 nomPat[PAT_NOM_LEN + 1];
        char			 prenomPat[PAT_PRENOM_LEN + 1];

        NSBloques* 		 pBloques;
        bool 			 verifBloque, donneMessage;

        NSPids*          pPatEnCours;
		NSPatientArray*  pPatientsArray;

		NSRechNomEdit*	 pNom;              // recherche par nom
		NSRechPreEdit*	 pPrenom;           // et pr�nom

        NSListPatWindow* pListe;
        NSLVScrollBar*   pVScroll;

        NSListePatDialog(TWindow* parent, NSContexte* pCtx, NSPids* pPat,
                         char* cResId = "IDD_LISTPA2");
		~NSListePatDialog();

		void SetupWindow();

        void InitListe();
        void AfficheListe();
        void LvnGetDispInfo(TLwDispInfoNotify& dispInfo);
        void InitPatArray();
        void PosLastPatient();
        void ScrollPatient();

        void GardeNss(int index);
        void RetrouvePatSelect();

		bool LineDown();
		bool LineUp();

        bool CanClose();
        void CmOk();

    DECLARE_RESPONSE_TABLE(NSListePatDialog);
};

/***************************************************************************///
// Objet "Boite de dialogue" utilis� pour s�lectionner un patient au sein
// d'une liste + recherche par num�ro et code + cr�ation nouveau patient
//
class ChercheListePatDialog : public NSListePatDialog
{
  public:

    bool            bPatientCree ;
    int             iModeImporter ;

    NSRechNumEdit*  pNum ;              // recherche par num�ro
    NSRechCodeEdit* pCode ;             // recherche par code
    TStatic*        pCreer ;
    // TStatic*      pImporter;
    // TStatic*		   pCaptionCode;

    string          _sCodePat ;

    ChercheListePatDialog(TWindow* parent, NSContexte* pCtx, NSPids* pPat) ;
		~ChercheListePatDialog() ;

		void SetupWindow() ;
    void CmCreer() ;
        // void CmImporter();

    DECLARE_RESPONSE_TABLE(ChercheListePatDialog);
};

/***************************************************************************/
//// Objet "ListWindow" avec gestion du double-click et du scroll (pour les patients)
//
class NSListPatWindow : public NSSkinableListWindow
{
    public:

	    NSListePatDialog* pDlg ;

	    NSListPatWindow(NSListePatDialog* pere, NSContexte* pCtx, int resId) ;
        ~NSListPatWindow() {}

        void    SetupWindow() ;
        void    EvKeyDown(uint key, uint repeatCount, uint flags) ;
        void    EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;
        void    EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
        int     IndexItemSelect() ;
        void    EvSetFocus(HWND hWndLostFocus) ;        void    EvKillFocus(HWND hWndGetFocus) ;
    DECLARE_RESPONSE_TABLE(NSListPatWindow) ;};

//
// Objet "ListWindow" avec gestion du double-click et du scroll (pour les patients)
//
class NSListGroupWindow : public NSSkinableListWindow
{
    public:

	    NSListeClientGroupDialog* 	pDlg ;
        OWL::TImageList*    		Images ;

	    NSListGroupWindow(NSListeClientGroupDialog* pere, NSContexte* pCtx, int resId) ;
        ~NSListGroupWindow();

        void    SetupWindow() ;
        void    EvKeyDown(uint key, uint repeatCount, uint flags) ;
        void    EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;
        void    EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
        int     IndexItemSelect() ;
        void    EvSetFocus(HWND hWndLostFocus) ;        void    EvKillFocus(HWND hWndGetFocus) ;
    DECLARE_RESPONSE_TABLE(NSListGroupWindow) ;};

/*
//
// Objet "ListWindow" avec gestion du double-click et du scroll (pour les patients)
//
class NSNTiersListPatWindow : public NSSkinableListWindow
{
    public:

	    NSNTiersListePatDialog* pDlg ;

	    NSNTiersListPatWindow(NSNTiersListePatDialog* pere, NSContexte* pCtx, int resId) ;
        ~NSNTiersListPatWindow() {}

        void    SetupWindow() ;
        void    EvKeyDown(uint key, uint repeatCount, uint flags) ;
        void    EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;
        void    EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
        int     IndexItemSelect() ;
        void    EvSetFocus(HWND hWndLostFocus) ;        void    EvKillFocus(HWND hWndGetFocus) ;
    DECLARE_RESPONSE_TABLE(NSNTiersListPatWindow) ;};

class NSNTiersRechNomEdit : public NSUtilEdit
{
	public:

		NSNTiersListePatDialog* pDlg ;

		// on bloque le premier Return (booleen false dans NSUtilEdit)
		NSNTiersRechNomEdit(NSContexte *pCtx, NSNTiersListePatDialog* pere, int resId, UINT iTextLen)
                      :NSUtilEdit(pCtx, pere, resId, iTextLen, false) { pDlg = pere ; }

		~NSNTiersRechNomEdit() {}

		void EvChar(uint key, uint repeatCount, uint flags) ;
		void EvKeyUp(uint key, uint repeatCount, uint flags) ;

	DECLARE_RESPONSE_TABLE(NSNTiersRechNomEdit) ;
};
*/

//// Classe NSRechNomEdit -> pour scroller quand on change le nom
//
class NSRechNomEdit : public NSUtilEdit
{
	public:

		NSListePatDialog* pDlg ;

		// on bloque le premier Return (booleen false dans NSUtilEdit)
		NSRechNomEdit(NSContexte *pCtx, NSListePatDialog* pere, int resId, UINT iTextLen)
                 :NSUtilEdit(pCtx, pere, resId, iTextLen, false) { pDlg = pere ; }

		~NSRechNomEdit() {}

		void EvChar(uint key, uint repeatCount, uint flags) ;
		void EvKeyUp(uint key, uint repeatCount, uint flags) ;

	DECLARE_RESPONSE_TABLE(NSRechNomEdit) ;
};

//
// Classe NSRechPreEdit -> pour scroller quand on change le pr�nom
//
class NSRechPreEdit : public NSUtilEdit
{
  public:

    NSListePatDialog* pDlg;

    NSRechPreEdit(NSContexte *pCtx, NSListePatDialog* pere, int resId, UINT iTextLen)
                :NSUtilEdit(pCtx, pere, resId, iTextLen) { pDlg = pere ; }

    ~NSRechPreEdit() {}

    void EvChar(uint key, uint repeatCount, uint flags) ;
    void EvKeyUp(uint key, uint repeatCount, uint flags) ;

  DECLARE_RESPONSE_TABLE(NSRechPreEdit) ;
};

//
// Classe NSRechNumEdit -> pour scroller quand on change de num�ro
//
class NSRechNumEdit : public NSUtilEdit
{
  public:

    ChercheListePatDialog* pDlg;

    NSRechNumEdit(NSContexte *pCtx, ChercheListePatDialog* pere, int resId, UINT iTextLen)
                 :NSUtilEdit(pCtx, pere, resId, iTextLen) { pDlg = pere ; }

    ~NSRechNumEdit() {}

    void EvChar(uint key, uint repeatCount, uint flags) ;

  DECLARE_RESPONSE_TABLE(NSRechNumEdit) ;
};

//
// Classe NSRechCodeEdit -> pour scroller quand on change de code
//
class NSRechCodeEdit : public NSUtilEdit
{
  public:

    ChercheListePatDialog* pDlg ;

    NSRechCodeEdit(NSContexte *pCtx, ChercheListePatDialog* pere, int resId, UINT iTextLen)
                   :NSUtilEdit(pCtx, pere, resId, iTextLen) { pDlg = pere ; }

    ~NSRechCodeEdit() {}

    void EvKeyUp(uint key, uint repeatcount, uint flags) ;
    void EvChar(uint key, uint repeatCount, uint flags) ;

  DECLARE_RESPONSE_TABLE(NSRechCodeEdit) ;
};

/***************************************************************************/

//
// Objet "ScrollBar" utilis� pour faire d�filer verticalement la liste des
// patients
//
class NSLVScrollBar : public OWL::TScrollBar
{
  public:

    NSListePatDialog* pListeDlg ;

    NSLVScrollBar(NSListePatDialog* parent, int resourceId, OWL::TModule* module = 0) ;

    void FixeRange(int max, int taille) ;
    void SBLineDown() ;
    void SBLineUp() ;
    void SBPageDown() ;
    void SBPageUp() ;
    void PositionneCurseur() ;
};

/***************************************************************************/
//
// Classe ChercheListeCorDialog -> pour la s�lection d'un correspondant dans la base
//
/***************************************************************************/

class NSLCScrollBar;
class NSRechCorEdit;
class NSListCorWindow;

//
// Objet "Boite de dialogue" utilis� pour s�lectionner un patient au sein
// d'une liste
//
/*
class ChercheListeCorDialog : public NSUtilDialog
{
  public:

    int				  	 nbNom;
    bool				 bVScroll;
    string			  	 sNumSelect;
    DBIResult 		  	 ErrDBI;
    int				  	 CorrespChoisi;

    NSCorrespondantInfo* pCorrespSelect;

    char				 nomCor[PAT_NOM_LEN + 1];
    char				 prenomCor[PAT_PRENOM_LEN + 1];

		NSCorrespArray*  	 pCorrespArray;

		NSRechCorEdit*	  	 pNom;
		NSRechCorEdit*	  	 pPrenom;

    NSListCorWindow* 	 pListe;
    NSLCScrollBar*   	 pVScroll;

		ChercheListeCorDialog(TWindow* pere, NSContexte* pCtx, TModule* module = 0);
   	    ~ChercheListeCorDialog();

		void SetupWindow();

    bool InitRecherche();
    void InitListe();
    void AfficheListe();
    void LvnGetDispInfo(TLwDispInfoNotify& dispInfo);
    void InitCorArray();
    void PosLastCorresp();
    void ScrollCorresp();
    void GardeNum(int index);
    void RetrouveCorSelect();

		bool LineDown();
		bool LineUp();

        bool CanClose();
        void CmOk();

    DECLARE_RESPONSE_TABLE(ChercheListeCorDialog);
};
*/

/***************************************************************************/

//// Objet "ListWindow" avec gestion du double-click et du scroll (pour les correspondants)
//
/*
class NSListCorWindow : public TListWindow
{
    public:

	    ChercheListeCorDialog* pDlg;

	    NSListCorWindow(ChercheListeCorDialog* pere, int resId, TModule* module = 0);
        ~NSListCorWindow() {}

        void EvKeyDown(uint key, uint repeatCount, uint flags);
        void EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point);
        void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point);
        int  IndexItemSelect();

    DECLARE_RESPONSE_TABLE(NSListCorWindow);
};
*/

//// Classe NSRechCorEdit -> pour scroller quand on change le nom ou le pr�nom
//
/*
class NSRechCorEdit : public NSUtilEdit
{
    public:

        ChercheListeCorDialog* pDlg;

        NSRechCorEdit(ChercheListeCorDialog* pere, int resId, UINT iTextLen) :
        NSUtilEdit(pere, resId, iTextLen) { pDlg = pere; }

        ~NSRechCorEdit() {}

        void EvChar(uint key, uint repeatCount, uint flags);

    DECLARE_RESPONSE_TABLE(NSRechCorEdit);
};
*/

/***************************************************************************/

//
// Objet "ScrollBar" utilis� pour faire d�filer verticalement la liste des
// patients
//
/*
class NSLCScrollBar : public OWL::TScrollBar
{
    public:

	    ChercheListeCorDialog* pListeDlg;

	    NSLCScrollBar(ChercheListeCorDialog* parent, int resourceId, TModule* module = 0);

        void FixeRange(int max, int taille);
	    void SBLineDown();
	    void SBLineUp();
        void SBPageDown();
        void SBPageUp();
        void PositionneCurseur();
};
*/
// Dialogue d'enregistrement des documents du patient (modal style)class NSEnregDocPatientDlg : public NSUtilDialog{    public :        OWL::TCheckBox*     pChemBox;        OWL::TCheckBox*     pIndexBox;        OWL::TCheckBox*     pSynthBox;        NSEnregDocPatientDlg(TWindow* pere, NSContexte* pCtx, OWL::TModule* module = 0);        ~NSEnregDocPatientDlg();        void    SetupWindow();        void    CheckChem();        void    CheckIndex();        void    CheckSynth();    DECLARE_RESPONSE_TABLE(NSEnregDocPatientDlg);};// Dialogue d'enregistrement du patient (modal style)class NSEnregPatientDlg : public NSUtilDialog{  public :    OWL::TCheckBox* pAdminBox ;    OWL::TCheckBox* pHistoBox ;    OWL::TCheckBox* pSynthBox ;    OWL::TCheckBox* pCorrsBox ;    OWL::TCheckBox* pLDVBox ;    NSEnregPatientDlg(TWindow* pere, NSContexte* pCtx, OWL::TModule* module = 0) ;    ~NSEnregPatientDlg() ;    void SetupWindow() ;    void CheckAdmin() ;    void CheckHisto() ;    void CheckSynth() ;    void CheckCorrs() ;    void CheckLDV() ;  DECLARE_RESPONSE_TABLE(NSEnregPatientDlg) ;};
/***************************************************************************/
#endif  // __NSPATDLG_H
