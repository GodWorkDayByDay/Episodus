#ifndef __NS_MULTIDIALOG_H#define __NS_MULTIDIALOG_H

#include <classlib\arrays.h>

#include <owl\dialog.h>
#include <owl\listbox.h>
#include <owl\combobox.h>
#include <owl\groupbox.h>
#include <owl\checkbox.h>
#include <owl\edit.h>
#include <owl\scrollba.h>

#include "partage\ns_vector.h"
#include "nsbb\nsdlg.h"

class NSDialog;

//VECTEUR DE NSDialog
typedef vector<NSDialog*>                 NSVecteurNSDialog ;
typedef NSVecteurNSDialog::iterator       NSDialogIterVect ;
typedef NSVecteurNSDialog::const_iterator NSDialogConstIterVect ;

class  NSVectNSDialog : public NSVecteurNSDialog
{
  public :

    TResId   ressource ;
    TWindow* AParent ;
    //
    // Constructeurs
    //
    NSVectNSDialog() ;
    NSVectNSDialog(const NSVectNSDialog& rv) ;
    //
    // Destructeur
    //
    virtual ~NSVectNSDialog() ;

    void vider() ;
    NSVectNSDialog& operator=(const NSVectNSDialog& src) ;
};
//-----------------------------------------------------------------------// classe pour le dialogue multiple
//-----------------------------------------------------------------------
class NsMultiDialog : public TDialog
{
	public :

   	NSVectNSDialog* _pMultiDialog ;       // pointeur sur des bo�tes de dialogues
   	NSVectNSDialog* _pAjoutMultiDialog ;  // vecteurs des bo�tes ajout�es
   	NSVectNSDialog* _pDeleteMultiDialog ; // vecteurs des bo�tes supprim�es
   	TResId          _ressource ;
   	TWindow*        _AParent ;
   	BBFilsItem*     _pBBItemFilsMultiDialog ; // pointeur sur BBItem lanceur de la bo�te de dialogue
    NSToolTip*      _pToolTip ;

   	NSDialog*       _pActive ;
   	int             _iDlgCount ;						//num�ro de la fen�tre
		//
		// Constructeurs 		Destructeur
		//
		NsMultiDialog(TWindow* parent, TResId resId, BBFilsItem* pBBitemFils, TModule* module = (TModule*) 0) ;
    ~NsMultiDialog() ;

   	NsMultiDialog(const NsMultiDialog& src) ;
   	// Surcharge de l'op�rateur d'affectation
		NsMultiDialog& operator=(const NsMultiDialog& src) ;

		void setActive(NSDialog* pFocus) { _pActive = pFocus ; }
		void idOk(NSDialog* pFocus, NSDialog::ACTIONTYPE iPreviousAction) ;
    void idCancel(NSDialog* pFocus, NSDialog::ACTIONTYPE iPreviousAction) ;

		//
   	// Op�rateurs
   	//
   	void EvAjouter() ;
   	void EvDetruire() ;
    void EvTimer(uint id) ;
   	void CmOk() ;
   	void CmCancel() ;
   	void referenceDialogue(NSDialog* pNSDialog) ;
   	void CmOkFermer(NSDialog* pDialog) ;
   	void setPosition(NSDialog* pDialog) ;
   	void setTitre(NSDialog* pDialog, int cardinal) ;
   	void DetruireNSDialog(NSDialog* pNSDialog, NSVectNSDialog* pMulti) ;
   	void SetupWindow() ;
    bool PreProcessMsg(MSG &msg) ;
    void ShowOkTooltip() ;
    void ShowCancelTooltip() ;

  protected :

    uint _iToolTipID ;

  // table de r�ponses
	DECLARE_RESPONSE_TABLE(NsMultiDialog) ;};

#endif

