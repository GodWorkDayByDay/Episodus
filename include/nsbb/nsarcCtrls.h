// -----------------------------------------------------------------------------
// nsarcCtrls.h
// -----------------------------------------------------------------------------
// Interface controls for Archetypes XML parser
// -----------------------------------------------------------------------------
// $Revision: 1.4 $
// $Author: pameline $
// $Date: 2013/08/24 14:14:17 $
// -----------------------------------------------------------------------------
// FLP - april 2005
// RS  - november 2002
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Copyright Nautilus, 2004
// http://www.nautilus-info.com
// -----------------------------------------------------------------------------
// Ce logiciel est un programme informatique servant � g�rer et traiter les
// informations de sant� d'une personne.
//
// Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
// respectant les principes de diffusion des logiciels libres. Vous pouvez
// utiliser, modifier et/ou redistribuer ce programme sous les conditions de la
// licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA sur le site
// "http://www.cecill.info".
//
// En contrepartie de l'accessibilit� au code source et des droits de copie, de
// modification et de redistribution accord�s par cette licence, il n'est offert
// aux utilisateurs qu'une garantie limit�e. Pour les m�mes raisons, seule une
// responsabilit� restreinte p�se sur l'auteur du programme, le titulaire des
// droits patrimoniaux et les conc�dants successifs.
//
// A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
// associ�s au chargement, � l'utilisation, � la modification et/ou au
// d�veloppement et � la reproduction du logiciel par l'utilisateur �tant donn�
// sa sp�cificit� de logiciel libre, qui peut le rendre complexe � manipuler et
// qui le r�serve donc � des d�veloppeurs et des professionnels avertis
// poss�dant des connaissances informatiques approfondies. Les utilisateurs sont
// donc invit�s � charger et tester l'ad�quation du logiciel � leurs besoins
// dans des conditions permettant d'assurer la s�curit� de leurs syst�mes et ou
// de leurs donn�es et, plus g�n�ralement, � l'utiliser et l'exploiter dans les
// m�mes conditions de s�curit�.
//
// Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez pris
// connaissance de la licence CeCILL, et que vous en avez accept� les termes.
// -----------------------------------------------------------------------------
// This software is a computer program whose purpose is to manage and process
// a person's health data.
//
// This software is governed by the CeCILL  license under French law and abiding
// by the rules of distribution of free software. You can use, modify and/ or
// redistribute the software under the terms of the CeCILL license as circulated
// by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
//
// As a counterpart to the access to the source code and  rights to copy, modify
// and redistribute granted by the license, users are provided only with a
// limited warranty and the software's author, the holder of the economic
// rights, and the successive licensors have only limited liability.
//
// In this respect, the user's attention is drawn to the risks associated with
// loading, using, modifying and/or developing or reproducing the software by
// the user in light of its specific status of free software, that may mean that
// it is complicated to manipulate, and that also therefore means that it is
// reserved for developers and experienced professionals having in-depth
// computer knowledge. Users are therefore encouraged to load and test the
// software's suitability as regards their requirements in conditions enabling
// the security of their systems and/or data to be ensured and, more generally,
// to use and operate it in the same conditions as regards security.
//
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
// -----------------------------------------------------------------------------

#ifndef __NSARCCTRLS_H__
# define __NSARCCTRLS_H__

# include <owl/dialog.h>
# include <owl/groupbox.h>
# include <owl/scrollba.h>
# include <owl/edit.h>
# include <owl/radiobut.h>
# include <vector.h>
# include <string>

class nsrefParseur ;
class nsarcParseur ;

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

# include "nsbb\nsattval.h"

# define VSCROLLID    199
# define CBUTTONID    200
# define SCROLL_WIDTH  10

# define IDC_OTHER     700
# define IDC_BBK_EVENT 701

class NSProposition ;

class nsrefButton : public OWL::TRadioButton, public NSRoot
{
	public:

  NSProposition* pProposition ;

  nsrefButton(TWindow* parent, NSContexte* pCtx, int resId, const char far* title, int x, int y, int w, int h, OWL::TGroupBox *group = 0, TModule* module = 0) ;
  ~nsrefButton() ;

  void BNClicked() ;  // BN_CLICKED

  DECLARE_RESPONSE_TABLE(nsrefButton) ;} ;

class nsrefDialog ;

class nsrefGroup : public OWL::TGroupBox
{
	public:

  	int hauteur ;
  	nsrefDialog* pDlg ;

  	nsrefGroup(nsrefDialog* pere, int Id, const char far *text, int x, int y, int w, int h, TModule* module = 0) ;
  	~nsrefGroup() ;

  	void Paint(TDC& dc, bool erase, NS_CLASSLIB::TRect& rect) ;
  	void CmHauteur() ;

	DECLARE_RESPONSE_TABLE(nsrefGroup) ;
} ;

class NSProposition
{
	public:

  	Cproposition*    propos ;
  	nsrefButton*     button ;

  	bool             bInitialStateOn ;
  	NSPatPathoArray* pReadyTree ;

  	NSProposition(Cproposition* prop, nsrefButton* butt = 0) ;
  	~NSProposition() ;
  	NSProposition(const NSProposition& rv) ;
  	NSProposition& operator=(const NSProposition& src) ;
} ;

typedef vector<NSProposition *>         NSProposVector ;
typedef NSProposVector::iterator        NSProposIter ;
typedef NSProposVector::const_iterator  NSProposCIter ;

class NSProposArray : public NSProposVector
{	public:		// Constructeurs
  	NSProposArray() : NSProposVector() {}  	NSProposArray(const NSProposArray& rv) ;  	NSProposArray& operator=(const NSProposArray& src) ;
  	// Destructeur  	virtual ~NSProposArray() ;  	void vider() ;} ;

class _NSBBCLASSE nsrefDialog : public TDialog, public NSRoot
{
	public:

  	NSProposArray*      _pProposArray ;
  	nsrefParseur*       _pParseur ;
  	bool			          _bSimplifie ;
  	OWL::TScrollBar*    _pScrollBar ;
  	NS_CLASSLIB::TRect  _usableRect ;
  	NS_CLASSLIB::TRect  _dlgRect ;
    NS_CLASSLIB::TRect  _dlgSizeRect ;
  	int                 _iVSize, _iHSize ;
  	int                 _iVBoxHeight, _iVGroupHeight ;
  	int                 _iVSizeNoScroll, _iVSizeBtnBas ;
  	int                 _iVRealSize, _iHRealSize ;
  	bool                _bVisibleScroll ;
  	int                 _iDecalageY ;
  	int                 _iOldDecalY ;

  	string              _sTitle ;
  	string              _sHelp ;

  	nsrefDialog(TWindow* Parent, NSContexte* pCtx, nsrefParseur* parseur, bool bSimple = false) ;
  	~nsrefDialog() ;

  	void					                 SetupWindow() ;
    void					                 initVars() ;
    void					                 initControls() ;
    void					                 eraseControls() ;
  	void					                 PreCochePropositions() ;
  	void                           SetSize() ;
  	void					                 CmOk() ;
  	void					                 CmCancel() ;
  	void					                 CmOther() ;
  	void					                 CmHelp() ;
    void                           CmBbkEvent() ;
    void                           CmBbkUpdate() ;
    void                           reinit() ;
  	void                           EvVScroll(UINT scrollCode, UINT thumbPos, HWND hWndCtl) ;
  	LRESULT                        EvMouseWheel(WPARAM wParam, LPARAM lParam) ;
  	static bool FAR PASCAL _export DlgScrollCtrl(HWND hWnd, LPARAM lParam) ;
  	static bool FAR PASCAL _export DlgScrollBtns(HWND hWnd, LPARAM lParam) ;

  protected:

    bool _bOngoingSetupWindow ;
    bool _bReinitCalled ;

    HWND _hWindow ;

	DECLARE_RESPONSE_TABLE(nsrefDialog) ;
} ;

class NSControlText ;

typedef vector<NSControlText *>             NSControlTextVector ;
typedef NSControlTextVector::iterator       NSControlTextIter ;
typedef NSControlTextVector::const_iterator NSControlTextCIter ;

class NSControlTextArray : public NSControlTextVector
{	public:  	// Constructeurs
  	NSControlTextArray() : NSControlTextVector() {}  	NSControlTextArray(const NSControlTextArray& rv) ;  	NSControlTextArray& operator=(const NSControlTextArray& src) ;
  	// Destructeur  	virtual ~NSControlTextArray() ;  	void vider() ;} ;

class NSControlText
{
	public:

		Citem*              item ;
  	nsrefButton*        button ;
  	OWL::TStatic*       texte ;
  	OWL::TEdit*         edit ;
  	NSControlTextArray  fils ;

  	NSControlText(Citem* pCitem) ;
  	~NSControlText() ;
  	NSControlText(const NSControlText& rv) ;
  	NSControlText& operator=(const NSControlText& src) ;
} ;

class _NSBBCLASSE nsarcDialog : public TDialog, public NSRoot
{
	public:

    int iBoxHeight ;    //!< hauteur du bouton
    int iBoxWidth ;     //!< largeur du bouton
    int iBoxInterv ;    //!< intervalle entre deux boutons
    int iBoxTop ;       //!< haut du 1er bouton
    int iBoxLeft ;      //!< d�calage gauche des boutons

    int iSeparLeft ;    //!< gauche du s�parateur
    int iGB_Separ ;     //!< intervalle entre le bas des controles et le s�parateur
    int iSepar_Btn ;    //!< intervalle entre le s�parateur et le bouton

    int iBtnHeight ;    //!< hauteur d'un bouton Borland    int iBtnWidth ;     //!< largeur d'un bouton Borland
    int iBtnLeft ;      //!< gauche du premier bouton
    int iBtn_bas ;      //!< intervalle entre le bas du bouton et le bas de la boite

    int iTotalWidth ;    int iTotalHeight ;    int iTopOfBox ;
    int iID ;

    NSControlText*  pControl ;
    nsarcParseur*   pParseur ;

    nsarcDialog(TWindow* Parent, NSContexte* pCtx, nsarcParseur* parseur) ;
    ~nsarcDialog() ;

    void SetupWindow() ;
    void InitControles(Citem* item, NSControlText* control) ;
    void SetupControles(NSControlText* control, int left, int& top) ;
    void CmOk() ;
    void CmCancel() ;

  DECLARE_RESPONSE_TABLE(nsarcDialog) ;
} ;

#endif // !__NSARCCTRLS_H__

