// NSgenDlg : dialogues de compta generale (depenses)
#ifndef __NSGENDLG_H
#if defined(_DANSCPTADLL)
class NSAffDepensArray ;

class NSUtilEdit ;
class NSUtilEditSomme ;

#include <owl\edit.h>
// #include "nsbb\nsednum.h"
//
class _CLASSECPTA NSDepensDocument : public NSNoyauDocument
   	    NSVarCompta*			pVar;
        NSEncaissData*			pTotaux;
        bool					bImprimer;

        NSAffDepensArray*		pDepensArray;

        NSDepensDocument(TDocument *parent, NSDocumentInfo *pDocumentInfo,

        NSDepensDocument(TDocument *parent = 0, NSContexte *pCtx = 0);
   	    ~NSDepensDocument();
        // M�thodes virtuelles de TDocument
        bool 		Close();

        bool 		InitDepensArray();
        bool        ChercheEcriture(string sNumEcriture, NSEcritureArray* pEcritureArray);
        void		CalculeTotaux();
};

class _CLASSECPTA NSListDepensWindow;
class _CLASSECPTA NSListDepensDialog : public NSUtilDialog

    NSDepensDocument*		pDoc;
    NSListDepensWindow* 	pListeDepens;
    OWL::TListBox*          pListeDetail;
    OWL::TEdit*             pEditTotal;

	NSListDepensDialog(TWindow* pere, NSContexte* pCtx, NSDepensDocument* pDepDoc);

    void 		SetupWindow();
    void 		AfficheListeDepens();
    void 		DispInfoListeDepens(TLwDispInfoNotify& dispInfo);
    void        InitListesTotaux();

    void 		CmModifDepens();
    void		CmImprimer();
    void 		CmOk();
    void 		CmCancel();

   DECLARE_RESPONSE_TABLE(NSListDepensDialog);

//
//

class _CLASSECPTA NSListDepensWindow : public TListWindow
	public:

	NSListDepensDialog* pDlg;
	NSListDepensWindow(NSListDepensDialog* pere, int resId) : TListWindow(pere, resId)
   	    pDlg = pere;
    }

    ~NSListDepensWindow() {}
	void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point);

   DECLARE_RESPONSE_TABLE(NSListDepensWindow);

// Dialogue de lancement de la d�claration 2035

class _CLASSECPTA NSAnnee2035Dialog : public NSUtilDialog
{
    public:

    NSUtilEdit*     pAnnee;
    string          sAnnee;

    NSAnnee2035Dialog(TWindow* pere, NSContexte* pCtx);
    ~NSAnnee2035Dialog();

    void SetupWindow();
    void CmOk();
    void CmCancel();

    DECLARE_RESPONSE_TABLE(NSAnnee2035Dialog);
};

class _CLASSECPTA NS2035Dialog : public NSUtilDialog
{
    public:

    NSUtilEditSomme*    p2035_1;
    NSUtilEditSomme*    p2035_2;
    NSUtilEditSomme*    p2035_3;
    NSUtilEditSomme*    p2035_4;
    NSUtilEditSomme*    p2035_5;
    NSUtilEditSomme*    p2035_6;
    NSUtilEditSomme*    p2035_7;
    NSUtilEditSomme*    p2035_8;
    NSUtilEditSomme*    p2035_9;
    NSUtilEditSomme*    p2035_10;
    NSUtilEditSomme*    p2035_11;
    NSUtilEditSomme*    p2035_12;
    NSUtilEditSomme*    p2035_13;
    NSUtilEditSomme*    p2035_14;
    NSUtilEditSomme*    p2035_15;
    NSUtilEditSomme*    p2035_16;
    NSUtilEditSomme*    p2035_17;
    NSUtilEditSomme*    p2035_18;
    NSUtilEditSomme*    p2035_19;
    NSUtilEditSomme*    p2035_20;
    NSUtilEditSomme*    p2035_21;
    NSUtilEditSomme*    p2035_22;
    NSUtilEditSomme*    p2035_23;
    NSUtilEditSomme*    p2035_24;
    NSUtilEditSomme*    p2035_25;
    NSUtilEditSomme*    p2035_26;
    NSUtilEditSomme*    p2035_27;
    NSUtilEditSomme*    p2035_28;
    NSUtilEditSomme*    p2035_29;
    NSUtilEditSomme*    p2035_30;
    NSUtilEditSomme*    p2035_31;
    NSUtilEditSomme*    p2035_32;
    NSUtilEditSomme*    p2035_BH;
    NSUtilEditSomme*    p2035_BJ;
    NSUtilEditSomme*    p2035_BM;

    NSEcritureArray*    pCptsArray;
    string              sAnnee2035;

    NS2035Dialog(TWindow* pere, NSContexte* pCtx, string sAnnee);
    ~NS2035Dialog();

    void SetupWindow();
    bool InitCptsArray();
    int  LigneCompte(string sCompte);
    void AfficheLigne(string somme, int ligne);
    string GetAnneeDepense(string sNumDep);
    string GetAnneeRecette(string sNumRec);
    void AfficheTotaux();
    void CmFermer();
    void CmImprimer();

    DECLARE_RESPONSE_TABLE(NS2035Dialog);
};


#endif
// fin de Nsgendlg.h
