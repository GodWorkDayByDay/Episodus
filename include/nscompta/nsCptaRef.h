//---------------------------------------------------------------------------//     NSCIM10.H
//     PA   juillet 95
//  Contient les d�finitions des objets Mat�riel
//---------------------------------------------------------------------------
#ifndef __NSCPTAREF_H
#define __NSCPTAREF_H

#include <classlib\arrays.h>
#include "partage\ns_vector.h"

#ifndef _ENTERPRISE_DLL
  #include <owl\dialog.h>
  #include <owl\listbox.h>
  #include <owl\groupbox.h>
  #include <owl\radiobut.h>
  #include <owl\button.h>
  #include <owl\listwind.h>

  #include "partage\nsdivfct.h"
  #include "ns_sgbd\nsfiche.h"
  #include "nsbb\nsutidlg.h"
  #include "nsbb\nsednum.h"
#else
  #include "enterpriseLus\superLus.h"
#endif

// #include "nssavoir\ns_medic.h"
#include "partage\ntarray.h"

#if defined(_DANSCPTADLL)
	#define _NSDKDCLASSE __export
#else
	#define _NSDKDCLASSE __import
#endif

//
// Taille des champs du fichier CLAM
//
#define CLAM_CODE_LEN          10
#define CLAM_LIBELLE_LEN      150
#define CLAM_MODULE_LEN         6
#define CLAM_PRIX_LEN           7
#define CLAM_FREQ_LEN           2
//
// Ordre des champs du fichier LIBRE
//
#define CLAM_CODE_FIELD         1
#define CLAM_LIBELLE_FIELD	    2
#define CLAM_MODULE_FIELD       3
#define CLAM_PRIX_E_FIELD       4
#define CLAM_PRIX_F_FIELD       5
#define CLAM_FREQ_FIELD         6

//---------------------------------------------------------------------------
//  Classe NSCLAM
//      ANCETRE : NSFiche
//---------------------------------------------------------------------------
//
// Objet donn�es des Objets CLAM
//
class _NSDKDCLASSE NSLibreData
{
	public :

		void metAZero() ;

		NSLibreData() { metAZero() ; }
		NSLibreData(const NSLibreData& rv) ;

    string getCode()      const { return string(code) ; }
		string getLibelle()   const { return string(libelle) ; }
		string getModule()    const { return string(module) ; }
    string getPrixF()     const { return string(prix_f) ; }
    string getPrixE()     const { return string(prix_e) ; }
    string getFrequence() const { return string(frequence) ; }

    void setCode(string sN)      { strcpy(code, sN.c_str()) ; }
		void setLibelle(string sN)   { strcpy(libelle, sN.c_str()) ; }
		void setModule(string sN)    { strcpy(module, sN.c_str()) ; }
    void setPrixF(string sN)     { strcpy(prix_f, sN.c_str()) ; }
    void setPrixE(string sN)     { strcpy(prix_e, sN.c_str()) ; }
    void setFrequence(string sN) { strcpy(frequence, sN.c_str()) ; }

		NSLibreData& operator=(const NSLibreData& src) ;
		int   		   operator==(const NSLibreData& o) const ;

  // protected:

    char code[CLAM_CODE_LEN + 1] ;
		char libelle[CLAM_LIBELLE_LEN + 1] ;
		char module[CLAM_MODULE_LEN + 1] ;
    char prix_f[CLAM_PRIX_LEN + 1] ;
    char prix_e[CLAM_PRIX_LEN + 1] ;
    char frequence[CLAM_FREQ_LEN + 1] ;
};

class NSLibreInfo ;

#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE NSClam : public NSFiche
{
	public :

		NSLibreData _Donnees ; // Donn�es de la fiche PARADOX

		NSClam(NSSuper* pSuper) ;
		~NSClam() ;

    string getCode()      const { return _Donnees.getCode() ;    }
		string getLibelle()   const { return _Donnees.getLibelle() ; }
		string getModule()    const { return _Donnees.getModule() ;  }
    string getPrixF()     const { return _Donnees.getPrixF() ;   }
    string getPrixE()     const { return _Donnees.getPrixE() ;   }
    string getFrequence() const { return _Donnees.getFrequence() ; }

		DBIResult open() ;
		void alimenteFiche() ;
		void videFiche() ;

    DBIResult getRecordByCode(string sCode, NSLibreInfo* pResult, bool bOpenClose, bool bVerbose = true) ;
};
#endif

//
// Objet "Info" correspondant � NSCim10
// (destin� � �tre utilis� dans les containers)
//
class _NSDKDCLASSE NSLibreInfo : public NSRoot
{
	public:

		NSLibreData _Donnees ;

		NSLibreInfo(NSContexte* pCtx) ;
#ifndef _ENTERPRISE_DLL
		NSLibreInfo(const NSClam* pCim, NSContexte* pCtx) ;
#endif
		NSLibreInfo(const NSLibreInfo& rv) ;
    ~NSLibreInfo() {}

    string getCode()      const { return _Donnees.getCode() ;    }
		string getLibelle()   const { return _Donnees.getLibelle() ; }
		string getModule()    const { return _Donnees.getModule() ;  }
    string getPrixF()     const { return _Donnees.getPrixF() ;   }
    string getPrixE()     const { return _Donnees.getPrixE() ;   }
    string getFrequence() const { return _Donnees.getFrequence() ; }

    int    getPriceE()    const { return atoi(_Donnees.getPrixE().c_str()) ; }
    int    getPriceF()    const { return atoi(_Donnees.getPrixF().c_str()) ; }
    int    getFrequency() const { return atoi(_Donnees.getFrequence().c_str()) ; }

    void setCode(string sN)      { _Donnees.setCode(sN) ;      }
		void setLibelle(string sN)   { _Donnees.setLibelle(sN) ;   }
		void setModule(string sN)    { _Donnees.setModule(sN) ;    }
    void setPrixF(string sN)     { _Donnees.setPrixF(sN) ;     }
    void setPrixE(string sN)     { _Donnees.setPrixE(sN) ;     }
    void setFrequence(string sN) { _Donnees.setFrequence(sN) ; }

		NSLibreInfo& operator=(const NSLibreInfo& src) ;
		int          operator==(const NSLibreInfo& o) ;

    void metAZero() { _Donnees.metAZero() ; }
};

//
// D�finition de NSMaterielArray (Array de NSMateriel(s))
//
typedef vector<NSLibreInfo*> NSLibreInfoArray ;
typedef NSLibreInfoArray::iterator         LibreIter ;
typedef NSLibreInfoArray::const_iterator   LibreConstIter ;
typedef NSLibreInfoArray::reverse_iterator LibreReverseIter ;
typedef NTArray<NSLibreInfo> NSLibreArray ;

class NSListeLibreWindow ;

//
// Objet "Boite de dialogue" utilis� pour s�lectionner un code CCAM
//
#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE ChoixLibreDialog : public TDialog, public NSRoot
{
	public:

		string			 		   _sExam ;
    bool               _bGlobalList ;

		NSLibreInfo* 	 	   _pCodeChoisi ;

		NSListeLibreWindow* _pMatBox ;
		NSLibreArray        _aMatArray ;

		UINT				 		   _iCodeChoisi ;

    OWL::TGroupBox*    _mainShade ;
    OWL::TGroupBox*    _separatorShade ;
    OWL::TButton*      _okButton ;
    OWL::TButton*      _cancelButton ;
    OWL::TButton*      _helpButton ;
    OWL::TButton*      _pChoiceButton ;

		ChoixLibreDialog(TWindow*, NSContexte* pCtx, string* pModu,
                         NSLibreInfo* pCodeChoisi) ;
		~ChoixLibreDialog() ;

		void SetupWindow() ;

    void EvSize(uint sizeType, ClassLib::TSize& size) ;
		void EvKeyDown(uint key, uint repeatCount, uint flags) ;
		void CmSelectMateriel(WPARAM Cmd) ;
		void CmCancel() ;
    void CmOk() ;
		void CmMaterielDblClk(WPARAM Cmd) ;
    void CmElargir() ;

    bool InitLibreArray() ;
    bool InitLibreArrayForCode() ;
    bool InitGlobalLibreArray() ;
		void InitListe() ;
		void AfficheListe() ;		void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
    void LVNColumnclick(TLwNotify& lwn) ;

		void OuvreDocument(int NumDoc) ;

    void sortByCode() ;
    void sortByLibelle() ;
    void sortByPriceE() ;
    void sortByPriceF() ;
    void sortByFreq() ;

	protected :

		bool _bNaturallySorted ;
		int  _iSortedColumn ;

    void swapSortOrder(int iColumn) ;

	DECLARE_RESPONSE_TABLE(ChoixLibreDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les codes CLAM)
//
class _NSDKDCLASSE NSListeLibreWindow : public TListWindow
{
	public:

		ChoixLibreDialog* pDlg ;

		NSListeLibreWindow(ChoixLibreDialog* pere, int resId) : TListWindow(pere, resId)
		{
			pDlg = pere ;
    }
		~NSListeLibreWindow() {}

    void SetupWindow() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSListeLibreWindow) ;
};

//
// Gestion des actes locaux
//

class NSMngtListeLocalActsWin ;

class _NSDKDCLASSE LocalActsManagementDialog : public TDialog, public NSRoot
{
	public:

		NSMngtListeLocalActsWin* _pMatBox ;
		NSLibreArray             _aActsArray ;

		UINT				 		         _iCodeChoisi ;

		LocalActsManagementDialog(TWindow*, NSContexte* pCtx) ;
		~LocalActsManagementDialog() ;

		void SetupWindow() ;

    void EvSize(uint sizeType, ClassLib::TSize& size) ;
		void EvKeyDown(uint key, uint repeatCount, uint flags) ;
    void CmOk() ;
    void CmNewAct() ;
    void CmNewActFrom() ;
		void CmMaterielDblClk(WPARAM Cmd) ;

    bool InitActsArray() ;
		void InitListe() ;
		void AfficheListe() ;		void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
    void LVNColumnclick(TLwNotify& lwn) ;

    void sortByCode() ;
    void sortByLibelle() ;
    void sortByExam() ;
    void sortByFrequency() ;

    bool createAct(NSLibreInfo* pActInfo) ;
    bool updateAct(NSLibreInfo* pActInfo) ;
    bool existAct(string sCode) ;

	protected :

		bool _bNaturallySorted ;
		int  _iSortedColumn ;

    void swapSortOrder(int iColumn) ;

	DECLARE_RESPONSE_TABLE(LocalActsManagementDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les codes CLAM)
//
class _NSDKDCLASSE NSMngtListeLocalActsWin : public TListWindow
{
	public:

		LocalActsManagementDialog* pDlg ;

		NSMngtListeLocalActsWin(LocalActsManagementDialog* pere, int resId) : TListWindow(pere, resId)
		{
			pDlg = pere ;
    }
		~NSMngtListeLocalActsWin() {}

    void SetupWindow() ;
    void EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;

    void CmNewAct() ;
    void CmNewActFrom() ;
    void CmEditAct() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSMngtListeLocalActsWin) ;
};

class _CLASSELEXI EditLocalActDialog : public NSUtilDialog
{
	public :

  	NSLibreInfo*               _pLibreInfo ;
    LocalActsManagementDialog* _pListMgmtDlg ;

   	// variables de saisie
    NSUtilEdit2*     _pCode ;
    NSUtilEdit2*     _pLabel ;
    NSUtilLexique*   _pExam ;
   	NSUtilEditSomme* _pMontantE ;    NSUtilEditSomme* _pMontantF ;
   	NSUtilEdit2*     _pFrequency ;
    OWL::TStatic*		 _pSigle ;   	EditLocalActDialog(TWindow* pere, NSContexte* pCtx, NSLibreInfo* pActInfo, LocalActsManagementDialog* pListMgmtDlg) ;
   	~EditLocalActDialog() ;

   	void SetupWindow() ;
   	void CmOk() ;   	void CmCancel() ;

	DECLARE_RESPONSE_TABLE(EditLocalActDialog) ;
};

#endif // #ifndef _ENTERPRISE_DLL

//
// Taille des champs du fichier PRODUIT
//
#define LOT_CODE_LEN          10
#define LOT_STATUS_LEN         1
#define LOT_DATE_LEN           8
#define LOT_BARRE_LEN         13
#define LOT_LIBELLE_LEN      150
#define LOT_MODULE_LEN         6
#define LOT_LEXIQUE_LEN        6
#define LOT_PRIX_LEN           7
#define LOT_COUNT_LEN          5
//
// Ordre des champs du fichier PRODUIT
//
#define LOT_CODE_FIELD          1
#define LOT_STATUS_FIELD        2
#define LOT_DATE_ACHAT_FIELD    3
#define LOT_BARRE_FIELD	        4
#define LOT_LIBELLE_FIELD	      5
#define LOT_LEXIQUE_FIELD       6
#define LOT_MODULE_FIELD        7
#define LOT_PRIX_VENTE_E_FIELD  8
#define LOT_PRIX_VENTE_F_FIELD  9
#define LOT_PRIX_ACHAT_E_FIELD 10
#define LOT_PRIX_ACHAT_F_FIELD 11
#define LOT_QUANTITY_FIELD     12
#define LOT_RESTE_FIELD        13
#define LOT_ALERTE_FIELD       14

//---------------------------------------------------------------------------
//  Classe NSCLAM
//      ANCETRE : NSFiche
//---------------------------------------------------------------------------
//
// Objet donn�es des Objets CLAM
//
class _NSDKDCLASSE NSLotData
{
	public :

    enum STATUSLOT { statusUndefined = 1, statusStock, statusOpen, statusEmpty } ;

		void metAZero() ;

		NSLotData() { metAZero() ; }
		NSLotData(const NSLotData& rv) ;

    string getCode()       const { return string(_code) ; }
    string getStatus()     const { return string(_status) ; }
    string getDateAchat()  const { return string(_date_achat) ; }
    string getBarre()      const { return string(_barre) ; }
		string getLibelle()    const { return string(_libelle) ; }
		string getLexique()    const { return string(_lexique) ; }
    string getModule()     const { return string(_module) ; }
    string getPrixVenteF() const { return string(_prix_vente_f) ; }
    string getPrixVenteE() const { return string(_prix_vente_e) ; }
    string getPrixAchatF() const { return string(_prix_achat_f) ; }
    string getPrixAchatE() const { return string(_prix_achat_e) ; }
    string getQuantite()   const { return string(_quantite) ; }
    string getReste()      const { return string(_reste) ; }
    string getAlerte()     const { return string(_alerte) ; }

    void setCode(string sN)       { strcpy(_code, sN.c_str()) ; }
    void setStatus(string sN)     { strcpy(_status, sN.c_str()) ; }
    void setDateAchat(string sN)  { strcpy(_date_achat, sN.c_str()) ; }
    void setBarre(string sN)      { strcpy(_barre, sN.c_str()) ; }
		void setLibelle(string sN)    { strcpy(_libelle, sN.c_str()) ; }
		void setLexique(string sN)    { strcpy(_lexique, sN.c_str()) ; }
    void setModule(string sN)     { strcpy(_module, sN.c_str()) ; }
    void setPrixVenteF(string sN) { strcpy(_prix_vente_f, sN.c_str()) ; }
    void setPrixVenteE(string sN) { strcpy(_prix_vente_e, sN.c_str()) ; }
    void setPrixAchatF(string sN) { strcpy(_prix_achat_f, sN.c_str()) ; }
    void setPrixAchatE(string sN) { strcpy(_prix_achat_e, sN.c_str()) ; }
    void setQuantite(string sN)   { strcpy(_quantite, sN.c_str()) ; }
    void setReste(string sN)      { strcpy(_reste, sN.c_str()) ; }
    void setAlerte(string sN)     { strcpy(_alerte, sN.c_str()) ; }

    STATUSLOT getStatusType() const ;
    void      setStatusType(STATUSLOT iStatus) ;

		NSLotData& operator=(const NSLotData& src) ;
		int   		 operator==(const NSLotData& o) const ;

  // protected:

    char _code[LOT_CODE_LEN + 1] ;
    char _status[LOT_STATUS_LEN + 1] ;
    char _date_achat[LOT_DATE_LEN + 1] ;
    char _barre[LOT_BARRE_LEN + 1] ;
		char _libelle[LOT_LIBELLE_LEN + 1] ;
    char _lexique[LOT_LEXIQUE_LEN + 1] ;
    char _module[LOT_MODULE_LEN + 1] ;
    char _prix_vente_f[LOT_PRIX_LEN + 1] ;
    char _prix_vente_e[LOT_PRIX_LEN + 1] ;
    char _prix_achat_f[LOT_PRIX_LEN + 1] ;
    char _prix_achat_e[LOT_PRIX_LEN + 1] ;
    char _quantite[LOT_COUNT_LEN + 1] ;
    char _reste[LOT_COUNT_LEN + 1] ;
    char _alerte[LOT_COUNT_LEN + 1] ;
};

class NSLotInfo ;

#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE NSLot : public NSFiche
{
	public :

		NSLotData _Donnees ; // Donn�es de la fiche PARADOX

		NSLot(NSSuper* pSuper) ;
		~NSLot() ;

    string getCode()       const { return _Donnees.getCode() ;       }
    string getStatus()     const { return _Donnees.getStatus() ;     }
    string getDateAchat()  const { return _Donnees.getDateAchat() ;  }
    string getBarre()      const { return _Donnees.getBarre() ;      }
		string getLibelle()    const { return _Donnees.getLibelle() ;    }
		string getLexique()    const { return _Donnees.getLexique() ;    }
    string getModule()     const { return _Donnees.getModule() ;     }
    string getPrixVenteF() const { return _Donnees.getPrixVenteF() ; }
    string getPrixVenteE() const { return _Donnees.getPrixVenteE() ; }
    string getPrixAchatF() const { return _Donnees.getPrixAchatF() ; }
    string getPrixAchatE() const { return _Donnees.getPrixAchatE() ; }
    string getQuantite()   const { return _Donnees.getQuantite() ;   }
    string getReste()      const { return _Donnees.getReste() ;      }
    string getAlerte()     const { return _Donnees.getAlerte() ;     }

    NSLotData::STATUSLOT getStatusType() const { return _Donnees.getStatusType() ; }

    void setReste(string sN)      { _Donnees.setReste(sN) ; }

		DBIResult open() ;
		void alimenteFiche() ;
		void videFiche() ;

    DBIResult getRecordByCode(string sCode, NSLotInfo* pResult, bool bOpenClose, bool bVerbose = true) ;
    bool      ChercheNumLot(string& sNumLot) ;
    void      decrementeLot(string sNumLot) ;
};
#endif

//
// Objet "Info" correspondant � NSCim10
// (destin� � �tre utilis� dans les containers)
//
class _NSDKDCLASSE NSLotInfo : public NSRoot
{
	public:

		NSLotData _Donnees ;

		NSLotInfo(NSContexte* pCtx) ;
#ifndef _ENTERPRISE_DLL
		NSLotInfo(const NSLot* pProduit, NSContexte* pCtx) ;
#endif
		NSLotInfo(const NSLotInfo& rv) ;
    ~NSLotInfo() {}

    string getCode()       const { return _Donnees.getCode() ;       }
    string getStatus()     const { return _Donnees.getStatus() ;     }
    string getDateAchat()  const { return _Donnees.getDateAchat() ;  }
    string getBarre()      const { return _Donnees.getBarre() ;      }
		string getLibelle()    const { return _Donnees.getLibelle() ;    }
		string getLexique()    const { return _Donnees.getLexique() ;    }
    string getModule()     const { return _Donnees.getModule() ;     }
    string getPrixVenteF() const { return _Donnees.getPrixVenteF() ; }
    string getPrixVenteE() const { return _Donnees.getPrixVenteE() ; }
    string getPrixAchatF() const { return _Donnees.getPrixAchatF() ; }
    string getPrixAchatE() const { return _Donnees.getPrixAchatE() ; }
    string getQuantite()   const { return _Donnees.getQuantite() ;   }
    string getReste()      const { return _Donnees.getReste() ;      }
    string getAlerte()     const { return _Donnees.getAlerte() ;     }

    int    getSellPriceE() const { return StringToInt(_Donnees.getPrixVenteE()) ; }
    int    getSellPriceF() const { return StringToInt(_Donnees.getPrixVenteF()) ; }
    int    getBuyPriceF()  const { return StringToInt(_Donnees.getPrixAchatF()) ; }
    int    getBuyPriceE()  const { return StringToInt(_Donnees.getPrixAchatE()) ; }
    int    getRemains()    const { return StringToInt(_Donnees.getReste()) ; }
    int    getAlertLevel() const { return StringToInt(_Donnees.getAlerte()) ; }

    NSLotData::STATUSLOT getStatusType() const { return _Donnees.getStatusType() ; }

    void setCode(string sN)       { _Donnees.setCode(sN) ; }
    void setStatus(string sN)     { _Donnees.setStatus(sN) ; }
    void setDateAchat(string sN)  { _Donnees.setDateAchat(sN) ; }
    void setBarre(string sN)      { _Donnees.setBarre(sN) ; }
		void setLibelle(string sN)    { _Donnees.setLibelle(sN) ; }
		void setLexique(string sN)    { _Donnees.setLexique(sN) ; }
    void setModule(string sN)     { _Donnees.setModule(sN) ; }
    void setPrixVenteF(string sN) { _Donnees.setPrixVenteF(sN) ; }
    void setPrixVenteE(string sN) { _Donnees.setPrixVenteE(sN) ; }
    void setPrixAchatF(string sN) { _Donnees.setPrixAchatF(sN) ; }
    void setPrixAchatE(string sN) { _Donnees.setPrixAchatE(sN) ; }
    void setQuantite(string sN)   { _Donnees.setQuantite(sN) ; }
    void setReste(string sN)      { _Donnees.setReste(sN) ; }
    void setAlerte(string sN)     { _Donnees.setAlerte(sN) ; }

    void setStatusType(NSLotData::STATUSLOT iStatus) { _Donnees.setStatusType(iStatus) ; }

		NSLotInfo& operator=(const NSLotInfo& src) ;
		int        operator==(const NSLotInfo& o) ;

    void metAZero() { _Donnees.metAZero() ; }
};

//
// D�finition de NSMaterielArray (Array de NSMateriel(s))
//
typedef vector<NSLotInfo*> NSLotInfoArray ;
typedef NSLotInfoArray::iterator         LotsIter ;
typedef NSLotInfoArray::const_iterator   LotsConstIter ;
typedef NSLotInfoArray::reverse_iterator LotsReverseIter ;
typedef NTArray<NSLotInfo> NSLotArray ;

class NSListeLotsWindow ;

//
// Objet "Boite de dialogue" utilis� pour s�lectionner les mat�riels
//
#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE ChoixLotsDialog : public TDialog, public NSRoot
{
	public:

		string			 		      _sExam ;
    bool                  _bGlobalList ;

		NSLotInfo* 	 	        _pLotChoisi ;

		NSListeLotsWindow*    _pMatBox ;
		NSLotArray            _aMatArray ;

		UINT				 		      _iCodeChoisi ;

    OWL::TGroupBox*       _mainShade ;
    OWL::TGroupBox*       _separatorShade ;
    OWL::TButton*         _okButton ;
    OWL::TButton*         _cancelButton ;
    OWL::TButton*         _helpButton ;
    OWL::TButton*         _pChoiceButton ;

		ChoixLotsDialog(TWindow*, NSContexte* pCtx, string* pModu,
                                                  NSLotInfo* pCodeChoisi) ;
		~ChoixLotsDialog() ;

		void SetupWindow() ;

    void EvSize(uint sizeType, ClassLib::TSize& size) ;
		void EvKeyDown(uint key, uint repeatCount, uint flags) ;
		void CmSelectMateriel(WPARAM Cmd) ;
		void CmCancel() ;
    void CmOk() ;
		void CmMaterielDblClk(WPARAM Cmd) ;
    void CmElargir() ;

    bool InitLotArray() ;
    bool InitLotArrayForCode() ;
    bool InitGlobalLotArray() ;
		void InitListe() ;
		void AfficheListe() ;		void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
    void LVNColumnclick(TLwNotify& lwn) ;

		void OuvreDocument(int NumDoc) ;

    void sortByLibelle() ;
    void sortByPriceE() ;
    void sortByPriceF() ;

	protected :

		bool _bNaturallySorted ;
		int  _iSortedColumn ;

    void swapSortOrder(int iColumn) ;

	DECLARE_RESPONSE_TABLE(ChoixLotsDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les codes CLAM)
//
class _NSDKDCLASSE NSListeLotsWindow : public TListWindow
{
	public:

		ChoixLotsDialog* pDlg ;

		NSListeLotsWindow(ChoixLotsDialog* pere, int resId) : TListWindow(pere, resId)
		{
			pDlg = pere ;
    }
		~NSListeLotsWindow() {}

    void SetupWindow() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSListeLotsWindow) ;
};

class NSMngtListeLotsWin ;

class _NSDKDCLASSE LotsManagementDialog : public TDialog, public NSRoot
{
	public:

		NSMngtListeLotsWin*   _pMatBox ;
		NSLotArray            _aMatArray ;

		UINT				 		      _iCodeChoisi ;

		LotsManagementDialog(TWindow*, NSContexte* pCtx) ;
		~LotsManagementDialog() ;

		void SetupWindow() ;

    void EvSize(uint sizeType, ClassLib::TSize& size) ;
		void EvKeyDown(uint key, uint repeatCount, uint flags) ;
    void CmOk() ;
    void CmNewLot() ;
    void CmNewLotFrom() ;
		void CmMaterielDblClk(WPARAM Cmd) ;

    bool InitLotArray() ;
		void InitListe() ;
		void AfficheListe() ;		void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
    void LVNColumnclick(TLwNotify& lwn) ;

    void sortByLibelle() ;
    void sortByStatus() ;
    void sortByLexique() ;
    void sortByExam() ;
    void sortByDate() ;

    bool updateLot(NSLotInfo* pLotInfo) ;

	protected :

		bool _bNaturallySorted ;
		int  _iSortedColumn ;

    void swapSortOrder(int iColumn) ;

	DECLARE_RESPONSE_TABLE(LotsManagementDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les codes CLAM)
//
class _NSDKDCLASSE NSMngtListeLotsWin : public TListWindow
{
	public:

		LotsManagementDialog* pDlg ;

		NSMngtListeLotsWin(LotsManagementDialog* pere, int resId) : TListWindow(pere, resId)
		{
			pDlg = pere ;
    }
		~NSMngtListeLotsWin() {}

    void SetupWindow() ;
    void EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;

    void CmNewLot() ;
    void CmNewLotFrom() ;
    void CmEditLot() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSMngtListeLotsWin) ;
};

class _CLASSELEXI EditLotDialog : public NSUtilDialog
{
	public :

  	NSLotInfo*       _pLotInfo ;

   	// variables de saisie
    NSUtilEdit2*       _pLabel ;
    NSUtilLexique*     _pLexique ;
    NSUtilLexique*     _pExam ;
   	NSUtilEditDate*	   _pDateAchat ;   	NSUtilEditSomme*   _pMontantAchatE ;
    NSUtilEditSomme*   _pMontantAchatF ;
    NSUtilEditSomme*   _pMontantVenteE ;
    NSUtilEditSomme*   _pMontantVenteF ;
   	NSUtilEdit2*       _pQuantity ;    NSUtilEdit2*       _pRemains ;    NSUtilEdit2*       _pAlert ;    OWL::TGroupBox*    _pStatusGrpe	;	  OWL::TRadioButton* _pStatusNew ;
	  OWL::TRadioButton* _pStatusOpen ;
    OWL::TRadioButton* _pStatusClose ;    OWL::TStatic*			 _pSigleAchat ;    OWL::TStatic*			 _pSigleVente ;    NSUtilEdit2*       _pCodeBarre ;   	EditLotDialog(TWindow* pere, NSContexte* pCtx, NSLotInfo* pLotInfo) ;
   	~EditLotDialog() ;

   	void SetupWindow() ;
   	void CmOk() ;   	void CmCancel() ;

	DECLARE_RESPONSE_TABLE(EditLotDialog) ;
};

#endif // #ifndef _ENTERPRISE_DLL

#endif    // __NSCPTAREF_H

