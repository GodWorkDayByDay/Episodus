#include <checks.h>
#include <owl\control.h>
#include <owl\gdiobjec.h>

#include "nsoutil/nsDicoBdm.h"
#include "nsoutil/nsPathorBdm.h"
#include "nsoutil/nsOutil.h"
#include "partage/nsdivfct.h"
#include "nautilus/nssuper.h"
#include "nautilus/nsepicap.h"

//
// General Controls diagnostic group
//
// DIAG_DEFINE_GROUP_INIT(OWL_INI, OwlControl, 1, 0);

DEFINE_RESPONSE_TABLE1(NSEditBdm, TEdit)
   EV_WM_KILLFOCUS,
   EV_WM_SETFOCUS,//le lexique r�cup�re le focus et ref�rence NSEditBdm
                  //comme controle edit
   EV_WM_GETDLGCODE,
   EV_WM_CHAR,
   EV_WM_KEYDOWN,
END_RESPONSE_TABLE;

//
// Constructeur
//
NSEditBdm::NSEditBdm(NSContexte* pCtx, TWindow* parent, int resId,
                     NSBdmDriver::BAMTABLETYPE iTableType,
                     uint textLen, TModule* module)
          :TEdit(parent, resId, textLen, module), NSRoot(pCtx)
{
  _iTableType     = iTableType ;
	_bGardeFocus    = false ;
	_bValidContent  = true ;
  _bWinStd        = false ;

  _sSelectedLabel = string("") ;
  _sSelectedCode  = string("") ;

  _bYouMustAcceptToLooseFocus = false ;

  _pLostFocusFunctor = (Functor*) 0 ;
  _pGotCodeFunctor   = (Functor*) 0 ;

	// Attr.Style |= ES_MULTILINE | ES_WANTRETURN;
	// Attr.Style &= ~ES_AUTOHSCROLL ;
	Attr.Style &= ~ES_AUTOVSCROLL ;
}

NSEditBdm::NSEditBdm(NSContexte* pCtx, TWindow* parent, int resourceId,
                     NSBdmDriver::BAMTABLETYPE iTableType,
                     const char far* text, int x, int y, int w, int h,
                     uint textLimit, bool multiline, TModule* module)
          :TEdit(parent, resourceId, text, x, y, w, h, textLimit, multiline, module), NSRoot(pCtx)
{
  _iTableType    = iTableType ;
  _bGardeFocus   = false ;
  _bValidContent = true ;

  _bWinStd       = false ;
  if (pContexte && pContexte->getPredi() && pContexte->getPredi()->_bReturnCloses)
    _bWinStd = true ;

  _bYouMustAcceptToLooseFocus = false ;

  _pLostFocusFunctor = (Functor*) 0 ;
  _pGotCodeFunctor   = (Functor*) 0 ;

  //pour sp�cifier le return pour un champ edit il faut pr�ciser tout d'abord ES_MULTILINE
  Attr.Style |= ES_WANTRETURN ;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void
NSEditBdm::SetupWindow()
{
try
{
	TEdit::SetupWindow() ;

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
  {
    pBdmDialog->setEdit(this) ;
    return ;
  }

  NSBdmDriver* pBdmDriver = pContexte->getBdmDriver() ;
  if (pBdmDriver)
    pBdmDriver->setBdmDialog(new ChoixBdmDialog(pContexte->GetMainWindow(), pBdmDriver, this, _iTableType, pNSResModule)) ;
}
catch (...)
{
	erreur("Exception NSEditDicoGlobal::SetupWindow;", standardError, 0) ;
}
}

/**
 *  Get the selection dialog from the Bdm driver
 */
ChoixBdmDialog*
NSEditBdm::getBdmDialog()
{
  if (pContexte->getBdmDriver())
    return pContexte->getBdmDriver()->getBdmDialog() ;
  return (ChoixBdmDialog*) 0 ;
}

//
// Destructor
//
NSEditBdm::~NSEditBdm()
{
  // Hiding the dialog
  //
  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
    pBdmDialog->hideDialog() ;
}

//-------------------------------------------------------------------------
// enlever les beeps
//-------------------------------------------------------------------------
void
NSEditBdm::EvChar(uint key, uint repeatCount, uint flags)
{
	TEdit::EvChar(key, repeatCount, flags);

  //
  // Transmission du contenu � la boite de dialogue
  //
  if (VK_RETURN == key)
    return ;

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if ((ChoixBdmDialog*) NULL == pBdmDialog)
    return ;

  // fl�che basse
  if (VK_DOWN == key)
  {
    if (pBdmDialog->getAmmorce() == string(""))
      return ;

    // sinon r�cup�rer un �l�ment dans le lexique
    pBdmDialog->NextElement() ;
  }

  // fl�che haut
  else if (VK_UP == key)
  {
    //si ammorce vide alors passer au NStrreNode suivant
    if (pBdmDialog->getAmmorce() == string(""))
      return ;

    //sinon r�cup�rer un �l�ment dans le lexique
    pBdmDialog->FormerElement() ;
  }
  else if (VK_INSERT == key)
    InsererElementLexique() ;
  else
    UpdateDico() ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void
NSEditBdm::EvKeyDown(uint key, uint repeatCount, uint flags)
{
  TEdit::EvKeyDown(key, repeatCount, flags) ;
  Parent->SendNotification(Attr.Id, 200, HWindow) ;
  //
  // Transmission du contenu � la boite de dialogue
  //

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if ((ChoixBdmDialog*) NULL == pBdmDialog)
    return ;

  // fl�che basse
  //
  if (VK_DOWN == key)
  {
    if (string("") == pBdmDialog->getAmmorce())
      return ;
    else
      pBdmDialog->NextElement() ;
  }
  //
  // fl�che haute
  //
  else if (VK_UP == key)
  {
    //si ammorce vide alors passer au NStrreNode suivant
    if (string("") == pBdmDialog->getAmmorce())
      return ;
    else
      pBdmDialog->FormerElement() ;
  }
  else if ((VK_INSERT == key) || (VK_RETURN == key))
    InsererElementLexique() ;
  else if (VK_TAB == key)
  {
    if (_bWinStd)
    {
      THandle hNextTab ;
      if (GetKeyState(VK_SHIFT) < 0)
        hNextTab = Parent->GetNextDlgTabItem(((TWindow*)this)->GetHandle(), /*bool previous=*/ true) ;
      else
        hNextTab = Parent->GetNextDlgTabItem(((TWindow*)this)->GetHandle(), /*bool previous=*/ false) ;
      _bGardeFocus = false ;
      ::SetFocus(hNextTab) ;
    }
  }
  else
    UpdateDico() ;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void
NSEditBdm::UpdateDico()
{
  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if ((ChoixBdmDialog*) NULL == pBdmDialog)
    return ;

  //
  // R�cup�ration du contenu du contr�le
  //
  string sContenu = getTextAsString() ;
  strip(sContenu) ;
  //
  // Transmission du contenu � la boite de dialogue
  //
	int iOouF = pBdmDialog->DonneAmmorce(&sContenu) ;
  if (1 == iOouF)
  {
    // bGardeFocus = true ;
    //
    // fixer la position du lexique
    //
    SetPositionLexique() ;
		pBdmDialog->showDialog() ;
    SetFocus() ;
  }
  else if (2 == iOouF)
    pBdmDialog->hideDialog() ;
}

//fonction permettant de voir passer toutes les touches
uint
NSEditBdm::EvGetDlgCode(MSG far* msg)
{
  uint retVal = (uint) DefaultProcessing() ;

  if (msg && (VK_RETURN == msg->wParam))
  {
    ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
    if (pBdmDialog && pBdmDialog->IsWindow())
      InsererElementLexique() ;
      
    // retVal |= DLGC_WANTCHARS ;
    retVal |= DLGC_WANTALLKEYS ;
  }
  return retVal ;
}

void
NSEditBdm::InsererElementLexique()
{
  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if ((ChoixBdmDialog*) NULL == pBdmDialog)
    return ;

  pBdmDialog->InsererElementLexique() ;
}

//----------------------------------------------------------------------------
bool
NSEditBdm::WakeUp(string* sTexteInitial, RECT* rectEdit)
{
	if (((string*) NULL == sTexteInitial) || ((RECT*) NULL == rectEdit))
		return false ;

	strip(*sTexteInitial) ;

	RECT rectEditeur = *rectEdit ;
	//
	// Calcul des dimensions et de la position � donner au contr�le Edit
	//
	if (rectEditeur.right - rectEditeur.left < 50)
		rectEditeur.right = rectEditeur.left + 40 ;
  //if (rectEditeur.bottom - rectEditeur.top < 50)
  //	rectEditeur.bottom = rectEditeur.top + 30;

  _rect = rectEditeur ;

  //position du lexique
  NS_CLASSLIB::TRect rectPere = Parent->GetWindowRect();
  // rect.left= rectEdit->left (Edit) par rapport � la bo�te de dialogue
  // rectPere.left (la bo�te de dialogue ) par rapport � l'�cran
  // pTree->Attr.X
  NS_CLASSLIB::TRect rectEdition = GetWindowRect();
  int x = _rect.left + _rect.Width() + rectPere.left  + 100 ;
  int y = rectEdition.top ;

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
  {
    NS_CLASSLIB::TRect rectLex = pBdmDialog->GetWindowRect() ;
    pBdmDialog->SetWindowPos(0, x, y, rectLex.Width(), rectLex.Height(), SWP_NOZORDER) ;
  }
  //
  // Positionnement du contr�le Edit
  //
  MoveWindow(rectEditeur, /*bool repaint*/ false) ;
  //
  // Initialisation du contr�le
  //
  SetText(sTexteInitial->c_str()) ;
  // pDico->pDicoDialog->SetFenetreAppel(this);

  //
  // Visualisation du contr�le
  //
	Show(SW_SHOWNORMAL) ;

	return true ;
}

//----------------------------------------------------------------------------// masquer le lexique et le rectangle d'�dition
//----------------------------------------------------------------------------
void
NSEditBdm::SleepNow()
{
	Show(SW_HIDE) ;

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
    pBdmDialog->hideDialog() ;
}

/**
 *  The user selected an item in the selection dialog
 */
void
NSEditBdm::ElementWasSelected()
{
  _sSelectedLabel = GetSelectedLabel() ;
  _sSelectedCode  = GetSelectedCode() ;

	SetText(_sSelectedLabel.c_str()) ;

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
	  pBdmDialog->hideDialog() ;

  if (_pGotCodeFunctor)
    (*_pGotCodeFunctor)() ;
}

//-------------------------------------------------------------------------//-------------------------------------------------------------------------
string
NSEditBdm::GetSelectedLabel()
{
  string sLabel = string("") ;

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
    pBdmDialog->GetSelectedLabel(&sLabel) ;

  return sLabel ;
}

//-------------------------------------------------------------------------//-------------------------------------------------------------------------
string
NSEditBdm::GetSelectedCode()
{
  string sCode = string("") ;

	ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
    sCode = pBdmDialog->GetCode() ;

  return sCode ;
}

//-------------------------------------------------------------------------
//le control edit gagne le focus
//-------------------------------------------------------------------------
void
NSEditBdm::EvSetFocus(HWND hWndLostFocus)
{
	TEdit::EvSetFocus(hWndLostFocus) ;

	ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if (pBdmDialog)
		pBdmDialog->setEdit(this) ;
}

//------------------------------------------------------------------------
// le champ edit perd son focus
//------------------------------------------------------------------------
void
NSEditBdm::EvKillFocus(HWND hWndGetFocus)
{
	//
	// R�cup�re le texte
	//
	string sContenu = getTextAsString() ;

	//
	// si le texte recup�r� est != de sContenuTransfert c'est qu'il s'agit d'un texte libre
	// mettre dans sCode string("�?????")
	//
	if (sContenu != _sSelectedLabel)
		_sSelectedCode = string("") ;

	if (hWndGetFocus != HWindow)
	{
    ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
		if (pBdmDialog && (hWndGetFocus != pBdmDialog->HWindow) &&
			  (false == pBdmDialog->IsChild(hWndGetFocus)))
    	pBdmDialog->hideDialog() ;

    TEdit::EvKillFocus(hWndGetFocus) ;

    if (_pLostFocusFunctor)
      (*_pLostFocusFunctor)() ;
	}
}

bool
NSEditBdm::canWeClose()
{
  return _bValidContent ;
}

bool
NSEditBdm::isEmpty()
{
  return (GetTextLen() == 0) ;
}

string
NSEditBdm::getTextAsString()
{
  int iBuffLen = GetTextLen() ;
  if (iBuffLen <= 0)
    return string("") ;

  char far* szBuff = new char[iBuffLen + 1] ;
  GetText(szBuff, iBuffLen + 1) ;  string sContenu = string(szBuff) ;

  delete[] szBuff ;

  return sContenu ;
}

//----------------------------------------------------------------------------
// positionner le lexique selon les coordonn�es de l'�cran et celles de la bo�te
// m�re
//----------------------------------------------------------------------------
void
NSEditBdm::SetPositionLexique()
{
try
{
	//
  // coordonn�es de l'�cran en pixels
  //
  TIC* pTic = new TIC("DISPLAY", 0, 0) ;
  int XScreen = pTic->GetDeviceCaps(HORZRES) ;
  int YScreen = pTic->GetDeviceCaps(VERTRES) ;
  delete pTic ;

	//position du lexique
  NS_CLASSLIB::TRect rectBoiteMere = Parent->GetWindowRect() ; //bo�te m�re
  NS_CLASSLIB::TRect rectEdition   = GetWindowRect() ; //rectangle d'�dition (this)

  //  // Attr : this
  //
  int x = Attr.X + Attr.W + rectBoiteMere.left  + 5 ;
  int y = rectEdition.top ;

  ChoixBdmDialog* pBdmDialog = getBdmDialog() ;
  if ((ChoixBdmDialog*) NULL == pBdmDialog)
    return ;

  NS_CLASSLIB::TRect rectLex = pBdmDialog->GetWindowRect() ; //lexique
  if ((x + rectLex.Width()) >= XScreen)
    x = rectEdition.left  - rectLex.Width() - 5 ;

  if ((y + rectLex.Height()) >= YScreen)
    y = YScreen - rectLex.bottom + rectLex.top ;

  pBdmDialog->SetWindowPos(0, x, y, rectLex.Width(), rectLex.Height(), SWP_NOZORDER) ;

  //
  // coordonn�es de l'�cran
  //
   /*   // Device metrics for screen
		HDC hDCScreen = GetDC(NULL);
		//ASSERT(hDCScreen != NULL);
		rectEdition.right = GetDeviceCaps(hDCScreen, HORZRES);
		rectEdition.bottom = GetDeviceCaps(hDCScreen, VERTRES);
		ReleaseDC(NULL, hDCScreen);
   */
}
catch(TWindow::TXWindow& e)
{
	string sErr = string("Exception NSEditLexique::SetPositionLexique : ") + e.why() ;
	erreur(sErr.c_str(), standardError, 0) ;
}
catch (...)
{
	erreur("Exception NSEditLexique::SetPositionLexique.", standardError, 0) ;
}
}

//-------------------------------------------------------------------------

