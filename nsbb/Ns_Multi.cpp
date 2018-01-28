//Kaddachi Hafedh#include <owl\applicat.h>
#include <owl\olemdifr.h>
#include <owl\dialog.h>
#include <stdio.h>
#include <string.h>
#include <bde.hpp>
#include <owl/button.h>

#include "partage\nsdivfct.h"
#include "nautilus\nssuper.h"
#include "nsbb\ns_multi.h"
#include "nsbb\nsbbitem.h"
#include "nsbb\nstooltip.h"
#include "partage\ns_timer.h"
#include "nsbb\ns_multi.rh"

       //??????????????????????????????????????????
       // REVOIR POSITION FENETRES ET CANCEL
       //??????????????????????????????????????????

// -------------------------------------------------------------------------
// -------------------- METHODES DE NSVectNSDialog ------------------------
// -------------------------------------------------------------------------
NSVectNSDialog::NSVectNSDialog()
		           :NSVecteurNSDialog()
{}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSVectNSDialog::NSVectNSDialog(const NSVectNSDialog& rv)
               :NSVecteurNSDialog()
{
try
{
	if (false == rv.empty())
		for (NSDialogConstIterVect it = rv.begin() ; rv.end() != it ; it++)
			push_back(new NSDialog((*it)->pContexte, AParent, ressource)) ;
}
catch (...)
{
	erreur("Exception NSVectNSDialog copy ctor.", standardError, 0) ;
}
}

//---------------------------------------------------------------------------//  Destructeur
//---------------------------------------------------------------------------
void
NSVectNSDialog::vider()
{
  if (empty())
    return ;

  for (NSDialogIterVect it = begin() ; end() != it ; )
  {
    delete *it ;
    erase(it) ;
  }
}

NSVectNSDialog::~NSVectNSDialog(){
	vider() ;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSVectNSDialog&
NSVectNSDialog::operator=(const NSVectNSDialog& src)
{
try
{
  if (this == &src)
    return *this ;

  //
  // Effacement des �l�ments d�j� contenus dans le vecteur destination
  //
	vider() ;
	//
  // Copie et insertion des �l�ments de la source
  //
  if (false == src.empty())
    for (NSDialogConstIterVect it = src.begin() ; src.end() != it ; it++)
      push_back(new NSDialog((*it)->pContexte, AParent, ressource)) ;

	return *this ;
}
catch (...)
{
  erreur("Exception NSVectNSDialog = operator.", standardError, 0) ;
	return *this ;
}
}

// -----------------------------------------------------------------//
//  M�thodes de NsMultiDialog
//
// -----------------------------------------------------------------
#ifdef _INCLUS
DEFINE_RESPONSE_TABLE1(NsMultiDialog, NSDialogWrapper)
#else
DEFINE_RESPONSE_TABLE1(NsMultiDialog, TDialog)
#endif
	EV_COMMAND(IDOK,             CmOk),
	EV_COMMAND(IDCANCEL,	       CmCancel),
	EV_COMMAND(IDC_MULT_AJOUT,   EvAjouter),
	EV_COMMAND(IDC_MULT_DETRUIT, EvDetruire),
  EV_WM_TIMER,
  EV_WM_DESTROY,
END_RESPONSE_TABLE ;

NsMultiDialog::NsMultiDialog(TWindow* parent , TResId resId, BBFilsItem* pBBitemFils, TModule* module)              :TDialog(parent, resId, module)
{
try
{
  _pMultiDialog           = new NSVectNSDialog() ;
  //
  // Vecteurs des bo�tes pr�sentes � l'ouverture
  //
  _pAjoutMultiDialog      = new NSVectNSDialog() ;
  //
  // Vecteurs des bo�tes pr�sentes � l'ouverture qui ont �t� supprim�es
  //
  _pDeleteMultiDialog     = new NSVectNSDialog() ;

  _ressource              = resId ;
  _AParent 		            = parent ;
  _pBBItemFilsMultiDialog = pBBitemFils ;
  _pActive                = (NSDialog*) 0 ;
  _iDlgCount              = 1 ;

  _pToolTip               = new NSToolTip(pBBitemFils->pContexte, this) ;
  _pToolTip->Attr.Style |= TTS_BALLOON ;

  _iToolTipID             = 0 ;

  // new TButton(parent, IDC_MULT_AJOUT) ;
  // new TButton(parent, IDC_MULT_DETRUIT) ;
}
catch (...)
{
  erreur("Exception NsMultiDialog ctor.", standardError, 0) ;
}
}

NsMultiDialog::~NsMultiDialog()
{
  delete _pMultiDialog ;

  //
  // Les pointeurs pr�sents dans pAjoutMultiDialog �taient �galement
  // pr�sents dans pMultiDialog et ont donc d�j� fait l'objet d'un delete.
  // On les supprime donc de pAjoutMultiDialog avant d'appeler le destructeur
  // pour �viter un double delete
  //
  if (false == _pAjoutMultiDialog->empty())
    for (NSDialogIterVect iter = _pAjoutMultiDialog->begin() ;
                                   _pAjoutMultiDialog->end() != iter ; )
      _pAjoutMultiDialog->erase(iter) ;

  delete _pAjoutMultiDialog ;

  // Le commentaire ci-dessus s'applique � pDeleteMultiDialog puisque
  // - CmOk ent�rine la destruction en tuant la bo�te
  // - CmCancel annule la destruction en repla�ant la bo�te dans pMultiDialog
  //
  if (false == _pDeleteMultiDialog->empty())
    for (NSDialogIterVect iter = _pDeleteMultiDialog->begin() ;
                                   _pDeleteMultiDialog->end() != iter ; )
      _pDeleteMultiDialog->erase(iter) ;

  delete _pDeleteMultiDialog ;

  delete _pToolTip ;
}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NsMultiDialog::NsMultiDialog(const NsMultiDialog& src)
              :TDialog(src._AParent, src._ressource)
{
try
{
  _pMultiDialog		        = new NSVectNSDialog(*(src._pMultiDialog)) ;
  _ressource			        = src._ressource ;
  _AParent				        = src._AParent ;
  _pBBItemFilsMultiDialog = src._pBBItemFilsMultiDialog ;
  _pActive				        = src._pActive ;
  _iDlgCount			        = src._iDlgCount ;

  _pToolTip               = new NSToolTip(_pBBItemFilsMultiDialog->pContexte, this) ;
  _pToolTip->Attr.Style |= TTS_BALLOON ;
}
catch (...)
{
	erreur("Exception NsMultiDialog copy ctor.", standardError, 0) ;
}
}

//---------------------------------------------------------------------------//  Op�rateur d'affectation
//---------------------------------------------------------------------------
inline NsMultiDialog&
NsMultiDialog::operator=(const NsMultiDialog& src)
{
  if (this == &src)
  	return *this ;

	_pMultiDialog           = src._pMultiDialog ;
	_ressource              = src._ressource ;
	_AParent                = src._AParent ;
	_pBBItemFilsMultiDialog = src._pBBItemFilsMultiDialog ;
	_pActive                = src._pActive ;
	_iDlgCount               = src._iDlgCount ;

	return *this ;
}

//-------------------------------------------------------------------------//ajouter vune nouvelle bo�te dans pMultiDialog et pAjoutMultiDialog
//-------------------------------------------------------------------------
void
NsMultiDialog::referenceDialogue(NSDialog* pNSDialog)
{
	_pMultiDialog->push_back(pNSDialog) ;
}

//-----------------------------------------------------------------------
// 	ajouter une nouvelle bo�te de dialogue correspondant au BBItem en cours
// 	mettre � jour les titres des bo�tes existantes
//    mettre � jour les vecteurs des bo�tes : pMultiDialog
//-----------------------------------------------------------------------
void
NsMultiDialog::EvAjouter()
{
  _iDlgCount++ ;

  _pBBItemFilsMultiDialog->creerNouveauFils() ;

  //convertir pMultiDialog->size() en chaine : taille
  //
  char szSize[25] ;
  itoa(_pMultiDialog->size(),szSize, 10) ;

  if (_pMultiDialog->empty())
    return ;

  for (NSDialogIterVect iter = _pMultiDialog->begin() ; _pMultiDialog->end() != iter ; iter++)
  {
    // r�cup�rer le titre de la bo�te
    char szCaption[100] ;
    (*iter)->GetWindowText(szCaption, 100) ;

    string sNewCaption = string("") ;

    string sTemp = string(szCaption) ;
    if (strchr(szCaption, '/') == 0)
      sNewCaption = string(szCaption) + string("/") + string(szSize) ;
    else
    {
      string sChaine ;
      if (_pMultiDialog->size() < 10)
      {
        sChaine = string(sTemp, 0, strlen(sTemp.c_str()) - 1) ;
        sNewCaption = sChaine + string(szSize) ;
      }
      else
      {
        sChaine = string(sTemp, 0, strlen(sTemp.c_str()) - strlen(szSize)) ;
        if (sChaine.find(string("/")) == NPOS)
          sNewCaption = sChaine + string("/") + string(szSize) ;
        else
          sNewCaption = sChaine + string(szSize) ;
      }
    }
    //mettre � jour le nouveau titre
    (*iter)->SetCaption(sNewCaption.c_str()) ;
  }
}

//-----------------------------------------------------------------------// D�truire une  bo�te de dialogue correspondant au BBItem en cours
// et enlever le pPPTenCours correspondant du NSVECT du BBitemFils
// mettre � jour les titres des bo�tes existantes
// mettre � jour les vecteurs des bo�tes : pMultiDialog
//
//-----------------------------------------------------------------------
void
NsMultiDialog::EvDetruire()
{
	if (_pMultiDialog->empty()) //pas de bo�tes � deleter
		return ;

	if ((NSDialog*) NULL == _pActive)
		_pActive = _pMultiDialog->back() ;

	char valeurentiere[100], titre[100] ;
	string Nom ;

  FatheredPatPathoIterVect iterPatPatho = 0 ;
	// Vecteurs des patpatho
	NSVectFatheredPatPathoArray* pVect = _pBBItemFilsMultiDialog->getPatPatho() ;
	if (pVect && (false == pVect->empty()))
	{
		// it�rateur
    iterPatPatho = pVect->begin() ;

    //trouver la patpatho correspondante
    for ( ; (pVect->end() != iterPatPatho) &&
          ((*iterPatPatho)->getPatPatho() != _pActive->_pBBItem->_pPPTEnCours) ;
                                                            iterPatPatho++) ;
	}

  BBiterFils itBBitem = 0 ;
	// trouver le BBitem de la boite � d�truire
	if (false == _pBBItemFilsMultiDialog->VectorFils.empty())
	{
  	itBBitem = _pBBItemFilsMultiDialog->VectorFils.begin() ;

    for ( ; (_pBBItemFilsMultiDialog->VectorFils.end() != itBBitem)
                        && (*itBBitem != _pActive->_pBBItem); itBBitem++) ;
	}

	//
	// Trouver la bo�te � d�truire
	//
	NSDialogIterVect iterBoite = _pMultiDialog->begin() ;
	for ( ; (iterBoite != _pMultiDialog->end()) && (_pActive != (*iterBoite)); iterBoite++) ;
  //
  // Destruction de la boite de dialogue
  //
  if (iterBoite != _pMultiDialog->end())
  	(*iterBoite)->Destroy() ;
  //
  // ATTENTION : pDeleteMultiDialog est r�serv� aux bo�tes anciennes (qui
  //					pourront �tre ressucit�es par CANCEL) les bo�tes nouvelles
  //					(non pr�sentes dans pAjoutMultiDialog) sont ignor�es
  //
  // On cherche si la bo�te est pr�sente dans pAjoutMultiDialog
  //
  if (false == _pAjoutMultiDialog->empty())
  {
  	NSDialogIterVect iterAjout = _pAjoutMultiDialog->begin() ;
    for ( ; (_pAjoutMultiDialog->end() != iterAjout) &&
                                (_pActive != (*iterAjout)) ; iterAjout++) ;
    if (_pAjoutMultiDialog->end() != iterAjout)
    	_pDeleteMultiDialog->push_back(*iterBoite) ;
    // New box, kill bbitem and patpatho
    else
    {
    	if ((false == _pBBItemFilsMultiDialog->VectorFils.empty()) &&
                         (_pBBItemFilsMultiDialog->VectorFils.end() != itBBitem))
      	_pBBItemFilsMultiDialog->VectorFils.erase(itBBitem);

      if ((pVect) && (false == pVect->empty()) && (pVect->end() != iterPatPatho))
      {
      	delete (*iterPatPatho) ;
     		pVect->erase(iterPatPatho) ;
      }
    }
	}
	//
	// On supprime la bo�te de la liste des bo�tes actives
	//
	_pMultiDialog->erase(iterBoite) ;
	_pActive = (NSDialog*) 0 ;

 /* 	//tuer le BBitem de la boite d�truite : mettre � jour VectorFils
  	if(itBBitem != pBBItemFilsMultiDialog->VectorFils.end())
  	{
  		delete (*itBBitem);
      pBBItemFilsMultiDialog->VectorFils.erase(itBBitem);
  	}

  	//tuer la boite de dialogue
  	if(iterBoite != pMultiDialog->end())
  	{
  		pActive->Desactive();
  		(*iterBoite)->Destroy();
  		pMultiDialog->erase(iterBoite);
  		pActive = 0;
  		compteur--;
  	}

   //enlever la patpatho correspondante
   if(iterPatPtho != pVect->end() )
   {
     delete (*iterPatPtho);
     pVect->erase(iterPatPtho);
   }
*/

	// mise � jour des titres
	int i = 1 ;
	char taille[25] ;
	size_t pos ;
	itoa(_pMultiDialog->size(),taille, 10) ;
	NSDialogIterVect iter = _pMultiDialog->begin() ;
	for (iter = _pMultiDialog->begin(), i = 1; (iter != _pMultiDialog->end()) ; iter++, i++)
	{
		string titreMiseAjour ;

    //r�cup�rer le titre de la bo�te
    (*iter)->GetWindowText(titre, 100) ;
    titreMiseAjour = string(titre) ;
    pos = titreMiseAjour.find(string(": ")) ;
    itoa(i,valeurentiere, 10) ;

    if (pos != NPOS)
    	Nom = string(titreMiseAjour, 0, pos + 2) + string(valeurentiere)
            		+ string("/") + string(taille) ;
    else
    	Nom = titreMiseAjour ;

    // Mettre � jour le nouveau titre
    (*iter)->SetCaption(Nom.c_str()) ;
	}
}

//-----------------------------------------------------------------------//d�truire une bo�te de dialogue
//-----------------------------------------------------------------------
void
NsMultiDialog::DetruireNSDialog(NSDialog* pNSDialog, NSVectNSDialog* pMulti)
{
	if (((NSDialog*) NULL == pNSDialog) || ((NSVectNSDialog*) NULL == pMulti))
		return ;

	// Vecteurs des patptho
	NSVectFatheredPatPathoArray* pVect = _pBBItemFilsMultiDialog->getPatPatho() ;
	if (((NSVectFatheredPatPathoArray*) NULL == pVect) || (pVect->empty()))
		return ;

	//it�rateur
	FatheredPatPathoIterVect iterPatPatho = pVect->begin() ;
	//trouver la patpatho correspondante
	for ( ; (pVect->end() != iterPatPatho) &&
        ((*iterPatPatho)->getPatPatho() != pNSDialog->_pBBItem->_pPPTEnCours) ;
       		                                                iterPatPatho++) ;

	//trouver le BBitem de la boite � d�truire
	BBiterFils itBBitem = _pBBItemFilsMultiDialog->VectorFils.begin() ;

	for ( ; (_pBBItemFilsMultiDialog->VectorFils.end() != itBBitem)
                    && (*itBBitem != pNSDialog->_pBBItem); itBBitem++) ;

	NSDialogIterVect iterBoite = pMulti->begin() ;
	//trouver la bo�te � d�truire
	for (iterBoite = pMulti->begin() ;
           (pMulti->end() != iterBoite) && (pNSDialog != (*iterBoite)) ;
                                                                iterBoite++) ;

	//tuer le BBitem de la boite d�truite : mettre � jour VectorFils
	if (_pBBItemFilsMultiDialog->VectorFils.end() != itBBitem)
    _pBBItemFilsMultiDialog->VectorFils.erase(itBBitem) ;

	//tuer la boite de dialogue
	if (pMulti->end() != iterBoite)
	{
  	pNSDialog->Desactive() ;
    (*iterBoite)->Destroy() ;
    pMulti->erase(iterBoite) ;
    _pActive = (NSDialog*) 0 ;
    _iDlgCount-- ;
	}

	//enlever la patpatho correspondante
	if (pVect->end() != iterPatPatho)
	{
  	delete (*iterPatPatho) ;
    pVect->erase(iterPatPatho) ;
	}
}

//-----------------------------------------------------------------------// en cliquant suo OK, on  active la boite de dialogue suivante
//-----------------------------------------------------------------------
void
NsMultiDialog::idOk(NSDialog* pFocus, NSDialog::ACTIONTYPE iPreviousAction)
{
	if (((NSDialog*) NULL == pFocus) || (_pMultiDialog->empty()))
  	return ;

  if (NSDialog::actionOk == iPreviousAction)
    ShowOkTooltip() ;

	NSDialogIterVect iter     = _pMultiDialog->begin() ;
	NSDialogIterVect itertemp = _pMultiDialog->begin() ; //temporaire

	NS_CLASSLIB::TRect rect, rect2 ;
	// int x,y,h, z;

	//
	// si une seule bo�te , alors activer la bo�te multidialogue
	//
	if (_pMultiDialog->size() == 1)
	{
  	SetFocus() ;
    return ;
	}

	//chercher la bo�te activ�e
	for (iter = _pMultiDialog->begin(); (_pMultiDialog->end() != iter) &&
   		                                        ((*iter) != pFocus); iter++) ;
	if (_pMultiDialog->end() == iter)
    return ;

  itertemp = iter ;
  itertemp++ ;
  if (_pMultiDialog->end() != itertemp)
    (*itertemp)->SetFocus() ; //activer la suivante
  else
  {
    itertemp  = _pMultiDialog->begin() ;
    (*itertemp)->SetFocus() ; //activer la premi�re
  }
}

void
NsMultiDialog::idCancel(NSDialog* pFocus, NSDialog::ACTIONTYPE iPreviousAction)
{
	if (((NSDialog*) NULL == pFocus) || (_pMultiDialog->empty()))
  	return ;

  if (NSDialog::actionCancel == iPreviousAction)
    ShowCancelTooltip() ;
}

// Since this object doesn't receive PreProcessMsg notifications, it cannot
// feed its tooltip with mouse move messages. This hack uses the timer to
// have the tooltip believe that the mouse is standing at the control we want
// to show the tooltip at.
//
void
NsMultiDialog::EvTimer(uint id)
{
	if (ID_MULTI_TIMER != id)
		return ;

  if (0 == _iToolTipID)
    return ;

  THandle hButton = GetDlgItem(_iToolTipID) ;
  if (0 == hButton)
    return ;

  TWindow btwWnd(hButton) ;
  if (false == btwWnd.IsWindow())
    return ;

  ClassLib::TRect btnRect = btwWnd.GetWindowRect() ;

  if (_pToolTip && _pToolTip->IsWindow())
  {
    MSG msg ;
    memset(&msg, 0, sizeof(MSG)) ;

    msg.message = WM_MOUSEMOVE ;
    msg.lParam  = MAKELONG((short) btnRect.BottomRight().X(), (short) btnRect.BottomRight().Y()) ;

    _pToolTip->RelayEvent(msg) ;

    _iToolTipID = 0 ;
  }
}

//-----------------------------------------------------------------------// fixer la position de la bo�te  de dialogue en fonction de la bo�te pr�c�dente
//-----------------------------------------------------------------------
void
NsMultiDialog::setPosition(NSDialog* pDialog)
{
	if (((NSDialog*) NULL == pDialog) || (_pMultiDialog->empty()))
		return ;

	NSDialogIterVect iter     = _pMultiDialog->begin() ;
	NSDialogIterVect itertemp = _pMultiDialog->begin() ; //temporaire
	NS_CLASSLIB::TRect rect ;

	int x, y ;
	int lTW_X = 50 ;
	int lTW_Y = 50 ;

	for (iter = _pMultiDialog->begin() ; (_pMultiDialog->end() != iter) &&
   		                                       ((*iter) != pDialog); iter++) ;
	if (iter == _pMultiDialog->begin())
		return ;

	itertemp = iter ;
	itertemp-- ;
	rect = (*itertemp)->GetWindowRect() ;

	x = rect.left + lTW_X ;
	y = rect.top  + lTW_Y ;

	pDialog->SetWindowPos(0, x, y, rect.Width(), rect.Height(), SWP_NOZORDER) ;
}

//-----------------------------------------------------------------------// titre de la boite pDialog, cardinal est le nombre de bo�tes de dialogue
// donn� par le BBItem
// mettre � jour les titres des autres bo�tes
// et mettre � jour pMultiDialog
//-----------------------------------------------------------------------
void
NsMultiDialog::setTitre(NSDialog* pDialog, int cardinal)
{
  if ((NSDialog*) NULL == pDialog)
		return ;

  char valeurentiere[100], titre[100], taille[25] ;
  string Nom ;

  int nombreBoite = 0 ;
  if (false == _pMultiDialog->empty())
  	nombreBoite = _pMultiDialog->size() ;
  else
  	nombreBoite = 1 ;

  itoa(nombreBoite,valeurentiere, 10) ;
  itoa(cardinal,taille, 10) ;

  //titre contient le titre de la fen�tre  pDialog->GetWindowText(titre, 100 ) ;
  string Nominitial = string(titre) ;

  if (1 == cardinal)
  	Nom = Nominitial + string(" : ") + string(valeurentiere) ;
  else
  	Nom = Nominitial + string(" : ") + string(valeurentiere) + string("/")
          + string(taille) ;

  //si cette bo�te n'appartient pas � pMultiDialog , l'ajouter
  NSDialogIterVect iter = _pMultiDialog->begin() ;
  for (NSDialogIterVect iter = _pMultiDialog->begin() ;
             (_pMultiDialog->end() != iter) && (pDialog != (*iter)) ; iter++) ;

  if (_pMultiDialog->end() == iter)
  {
  	_pMultiDialog->push_back(pDialog) ;
    _iDlgCount++ ;
  }

  //mettre � jour le nouveau titre
  pDialog->SetCaption(Nom.c_str()) ;
}

//-----------------------------------------------------------------------// confirmer le choix : ok
//-----------------------------------------------------------------------
void
NsMultiDialog::CmOkFermer(NSDialog* pDialog)
{
	if (((NSDialog*) NULL == pDialog) || ((BBItem*) NULL == pDialog->_pBBItem))
		return ;

	pDialog->_pBBItem->donneRetourDlg(0) ;
	if (pDialog->_pBBItem->okFermerDialogue(true))
  	pDialog->CloseWindow(IDOK) ;

	pDialog->Desactive() ;

	pDialog = (NSDialog*) 0 ;
  // delete pDialog ;
}

void
NsMultiDialog::CmOk()
{
	//
	// confirmer la suppression des bo�tes par le bouton "D�truire"
	//
	if (false == _pDeleteMultiDialog->empty())
  	for (NSDialogIterVect iter = _pDeleteMultiDialog->begin() ;
   										                _pDeleteMultiDialog->end() != iter ; )
    	DetruireNSDialog(*iter, _pDeleteMultiDialog) ;

	if (false == _pMultiDialog->empty())
  	for (NSDialogIterVect iter = _pMultiDialog->begin() ;
                                        _pMultiDialog->end() != iter ; iter++)
  		//cette fen�tre doit fermer ses fen�tres filles si elles sont ouvertes
      //avant de se refermer elle m�me
      //(*iter)->CmOkFermer();
      CmOkFermer((*iter)) ;

	_pBBItemFilsMultiDialog->tuerFils() ;
	// pBBItemFilsMultiDialog->pNsMultiDialog = (NsMultiDialog*) 0 ;

	CloseWindow(IDOK) ;
}

//-----------------------------------------------------------------------// annuler le choix : cancel
//-----------------------------------------------------------------------
void
NsMultiDialog::CmCancel()
{
	//
  // Si on vient de rajouter une ou plusieurs bo�tes, il faut les supprimer
  //
  if ((false == _pMultiDialog->empty()) && (false == _pAjoutMultiDialog->empty()))
  {
  	for (NSDialogIterVect iter = _pMultiDialog->begin() ;
   		                                 _pMultiDialog->end() != iter ; )
    {
    	//
      // Une bo�te est nouvelle si elle n'est pas dans pAjoutMultiDialog
      //
      NSDialogIterVect jter = _pAjoutMultiDialog->begin() ;
      while ((_pAjoutMultiDialog->end() != jter) && (!(*iter == *jter)))
      	jter++ ;

      if (_pAjoutMultiDialog->end() == jter)
      	DetruireNSDialog(*iter, _pMultiDialog) ;
      else
      	iter++ ;
    }
  }
  //
  // recup�rer les bo�tes supprim�es
  //
  if (false == _pDeleteMultiDialog->empty())
  	for (NSDialogIterVect iter = _pDeleteMultiDialog->begin() ;
                                 _pDeleteMultiDialog->end() != iter ; iter++)
    	_pMultiDialog->push_back(*iter) ;

	if (false == _pMultiDialog->empty())
	{
  	for (NSDialogIterVect iter = _pMultiDialog->begin() ;
                                  _pMultiDialog->end() != iter ; iter++)
    {
    	//cette fen�tre doit fermer ses fen�tres filles si elles sont ouvertes
      //avant de se refermer elle m�me
      //(*iter)->CmCancelFermer();
      //(*iter)= 0;
      (*iter)->_pBBItem->donneRetourDlg(-1) ;
      (*iter)->_pBBItem->okFermerDialogue(false) ;
      (*iter)->Destroy(IDCANCEL) ;
    }
	}

	_pBBItemFilsMultiDialog->tuerFils() ;
	_pBBItemFilsMultiDialog->pNsMultiDialog = (NsMultiDialog*) 0 ;

	Destroy(IDCANCEL) ;
}

//-----------------------------------------------------------------------// SetupWindow
//-----------------------------------------------------------------------
void
NsMultiDialog::SetupWindow()
{
	//
	// Appel obligatoire au SetupWindow() de l'anc�tre
	//
	TDialog::SetupWindow() ;

	NS_CLASSLIB::TRect rect, rectMulti ;
  int x, y ;
  int lTW_X = 10 ;
  rectMulti = GetWindowRect() ;

  //
  // positionner la boite multidialogue par rapport � la premi�re boite NSDialog
  // pilot�e par pFilsIt en tant que BBItem
  //

	//
  //coordonn�es de l'�cran en pixels
  //
  TIC Tic("DISPLAY", 0, 0) ;
  int XScreen = Tic.GetDeviceCaps(HORZRES) ;
  int YScreen = Tic.GetDeviceCaps(VERTRES) ;

	if (false == _pMultiDialog->empty())
	{
  	NSDialogIterVect iterBoite = _pMultiDialog->begin() ;
    if (_pMultiDialog->end() != iterBoite)
    {
      rect = (*iterBoite)->GetWindowRect() ;
      x = rect.left + rect.Width() + lTW_X ;
      y = rect.top ;

      if ((x + rectMulti.Width()) >= XScreen)//si elle ne tient pas � droite
      {
      	//si elle tient � gauche
        if ( rect.left  - rectMulti.Width() -  lTW_X >= 0 )
        	x = rect.left  - rectMulti.Width() - lTW_X ;
        //si elle ne tient pas � gauche
        else
        {
        	//on la cale � droite
          if (XScreen - rect.left - rect.Width() > rect.left)
          	x = XScreen - rectMulti.Width() ;
          else
          	x = 0 ;
        }
      }
      if ((y + rectMulti.Height()) >= YScreen)
      	y = YScreen - rectMulti.bottom + rectMulti.top ;

      SetWindowPos(0, x, y, rectMulti.Width(), rectMulti.Height(), SWP_NOZORDER) ;
    }
  }
  //
  // On indique dans pAjoutMultiDialog les bo�tes pr�sentes � l'ouverture
  //
  if (false == _pMultiDialog->empty())
    for (NSDialogIterVect iter = _pMultiDialog->begin() ;
                                     _pMultiDialog->end() != iter ; iter++)
      _pAjoutMultiDialog->push_back(*iter) ;
}

bool
NsMultiDialog::PreProcessMsg(MSG &msg)
{
  // if (_pToolTip && _pToolTip->IsWindow())
  //   _pToolTip->RelayEvent(msg) ;

  return TDialog::PreProcessMsg(msg) ;
}

void
NsMultiDialog::ShowOkTooltip()
{
  string sHelpTxt = _pBBItemFilsMultiDialog->pContexte->getSuperviseur()->getText("multipleDescriptionControl", "ClickThereToCloseThisDescription") ;
  if (string("") == sHelpTxt)
    return ;

  THandle hOkButton = GetDlgItem(IDOK) ;
  if (0 == hOkButton)
    return ;

  TWindow btwWnd(hOkButton) ;
  ClassLib::TRect btnRect = btwWnd.GetWindowRect() ;

  _pToolTip->ShowTip(btnRect.BottomRight(), sHelpTxt) ;

  // _pToolTip->Attr.Style |= TTS_BALLOON ;
  // _pToolTip->ShowTipForId(IDOK, btnRect.BottomRight()) ;
  // _pToolTip->Show(hOkButton, btnRect.BottomRight()) ;
  // _pToolTip->Show(SW_SHOW) ;
}

void
NsMultiDialog::ShowCancelTooltip()
{
  string sHelpTxt = _pBBItemFilsMultiDialog->pContexte->getSuperviseur()->getText("multipleDescriptionControl", "ClickThereToCloseThisDescription") ;
  if (string("") == sHelpTxt)
    return ;

  THandle hOkButton = GetDlgItem(IDCANCEL) ;
  if (0 == hOkButton)
    return ;

  TWindow btwWnd(hOkButton) ;
  ClassLib::TRect btnRect = btwWnd.GetWindowRect() ;

  _pToolTip->ShowTip(btnRect.BottomRight(), sHelpTxt) ;
}

