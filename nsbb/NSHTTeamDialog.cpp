// -----------------------------------------------------------------------------
// NSHTTeamDialog.cpp// -----------------------------------------------------------------------------// Fen�tre de liste des Equipes
// -----------------------------------------------------------------------------
// $Revision: 1.6 $
// $Author: pameline $
// $Date: 2014/01/29 20:40:59 $
// -----------------------------------------------------------------------------
// FLP - octobre 2004
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


#include "partage\nsdivfct.h"
#include "nsbb\nsbbtran.h"
#include "nsbb\nsbbitem.h"
#include "nsbb\nsbb.h"
#include "nsbb\NSHTTeamDialog.h"
#include "nssavoir\GraphicHealthTeam.h"
#include "nsbb\NSHealthTeam.rh"

#ifdef N_TIERS
# include "pilot\NautilusPilot.hpp"
# include "nsbb\tagNames.h"
#endif

// -----------------------------------------------------------------------------
//
// M�thodes de NSTeamDisplay
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------
NSTeamDisplay::NSTeamDisplay(NSBasicAttributeArray *pAttribute, NSContexte *pCtx)
{
	_pTeamManager = new NSTeamGraphManager(pCtx->getSuperviseur()) ;

  _sID    = string("") ;
  _sLabel = string("") ;

  for(NSBasicAttributeIter iter = pAttribute->begin() ; iter != pAttribute->end() ; iter++)
  {
  	if 			((*iter)->getBalise() == OIDS)
    	_sID    = (*iter)->getText() ;
    else if ((*iter)->getBalise() == TEAM_LNOMA)
    	_sLabel = (*iter)->getText() ;
  }
}

NSTeamDisplay::NSTeamDisplay(const NSTeamDisplay& rv)
{
  _pTeamManager = new NSTeamGraphManager(*(rv._pTeamManager)) ;

  _sID    = rv._sID ;
  _sLabel = rv._sLabel ;
}

// -----------------------------------------------------------------------------
// destructor
// -----------------------------------------------------------------------------
NSTeamDisplay::~NSTeamDisplay()
{
	delete _pTeamManager ;
}

NSTeamDisplay&
NSTeamDisplay::operator=(const NSTeamDisplay& src)
{
  if (&src == this)
		return *this ;

  _sID    = src._sID ;
  _sLabel = src._sLabel ;

  return *this ;
}

// -----------------------------------------------------------------------------
// r�cup�re un objet NSTeam
// -----------------------------------------------------------------------------
NSTeam *
NSTeamDisplay::getTeam(NSContexte *pCtx)
{
	NSTeam 					*pTeamResult	= NULL ;
	NSPatPathoArray	*pPPT					= new NSPatPathoArray(pCtx->getSuperviseur()) ;
	// fabFIXME
/*
  if ((sID != "")  && (pTeamManager->getTeamGraph(sID, pPPT)))
  	pTeamResult = new NSTeam(pPPT) ;
*/
  delete pPPT ;
  return pTeamResult ;
}

// -----------------------------------------------------------------------------
//
// M�thodes de NSTTeamListDialog
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// table de r�ponses
// -----------------------------------------------------------------------------
DEFINE_RESPONSE_TABLE1(NSTTeamListDialog, NSUtilDialog)
	EV_COMMAND(IDOK, 									CmOk),
  EV_COMMAND(IDCANCEL, 							CmCancel),
  EV_COMMAND(IDC_LC_CREER, 					CmCreer),
  EV_LVN_GETDISPINFO(IDC_LC_LW,			LvnGetDispInfo),
END_RESPONSE_TABLE ;


// -----------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------NSTTeamListDialog::NSTTeamListDialog(TWindow *pere, bool avecCreer, NSContexte *pCtx, TModule *module)                  :NSHTMemberListDialog(pere, "IDD_LISTTEAMS", pCtx, pNSDLLModule)
{
	// Cr�ation de tous les "objets de contr�le"
  pNom						= new NSHTMemberListEdit(pContexte, this, IDC_LC_NOM, COR_NOM_LEN) ;
  pListe					= new NSHTMemberListWindow(this, IDC_LC_LW, module) ;

#ifndef N_TIERS
	pVScroll				= new NSHTMemberListScrollBar(this, IDC_LC_VSCROLL) ;
#endif
	pCreateTeam			= new TButton(this, IDC_LC_CREER) ;

	// Cr�ation du tableau de Patients  pSelectedTeam		= NULL ;	pTeamsDisplayed	= new NSTeamDisplayArray() ;

  teamID					= "" ;  bCreer					= false ;  bAvecCreer			= avecCreer ;}

// -----------------------------------------------------------------------------// destructor// -----------------------------------------------------------------------------NSTTeamListDialog::~NSTTeamListDialog(){
	delete pNom ;
#ifndef N_TIERS
	delete pVScroll ;
#endif
  delete pListe ;
  delete pCreateTeam ;

/*
  if (pSelectedTeam != NULL)
  	delete pSelectedTeam ;
*/
  delete pTeamsDisplayed ;
}


// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::SetupWindow()
// Arguments   : Aucun
// Description : Initialise la boite de dialogue
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::SetupWindow()
{
	// fabTODO
	TDialog::SetupWindow() ;
	SetCaption("CHOIX D'UNE EQUIPE") ;

  pNom->SetText("") ;
  if (!bAvecCreer)
  	pCreateTeam->ShowWindow(SW_HIDE) ;

  // Initialisation du tableau des personnes  InitTeamArray() ;

  // Initialisation de la liste  listDisplayInit() ;
  displayList() ;
}


// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::listDisplayInit()// Arguments   : Aucun
// Description : Initialise la ListWindow avec ses colonnes
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::listDisplayInit()
{
	TListWindColumn	nameColumn("Nom", 250, TListWindColumn::Left, 0) ;
  pListe->InsertColumn(0, nameColumn) ;
}


// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::displayList(int decal)// Arguments   : Aucun
// Description : Affiche le tableau de patients dans la liste
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::displayList()
{
  // On vide la liste et on la remplit
	pListe->DeleteAllItems() ;

	for (NSTeamDisplayRIter teamRIter = pTeamsDisplayed->rbegin() ; teamRIter != pTeamsDisplayed->rend() ; teamRIter++)
  {
		char buffer[255] ;
    sprintf(buffer, "%s", (*teamRIter)->getLabel().c_str()) ;
    TListWindItem Item(buffer, 0) ;
    pListe->InsertItem(Item) ;
  }

#ifndef N_TIERS
	pListe->ShowScrollBar(SB_VERT, FALSE) ;
#endif
}


// -----------------------------------------------------------------------------// Callback notification to handle additional column information for each item.// -----------------------------------------------------------------------------
void
NSTTeamListDialog::LvnGetDispInfo(TLwDispInfoNotify& dispInfo)
{
	// fabFIXME - perhaps not needed there is just one column for the moment
}


// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::InitTeamArray()// Arguments   : Aucun
// Description : Initialise le tableau des �quipes
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::InitTeamArray()
{
	pTeamsDisplayed->vider() ;

  serviceName	= (NautilusPilot::SERV_SEARCH_OBJECT_HAVING_TRAITS).c_str() ;

  NSBasicAttributeArray		 AttrArray ;
  AttrArray.push_back(new NSBasicAttribute("trait", TEAM_LNOMA)) ;
  AttrArray.push_back(new NSBasicAttribute(STEP, string("100"))) ;
  AttrArray.push_back(new NSBasicAttribute(NEWLIST, string("1"))) ;

  NSPersonsAttributesArray ResultList	;

  bool listOk = pContexte->getSuperviseur()->getPilot()->objectList(serviceName, &ResultList, &AttrArray) ;

  if ((listOk) && (false == ResultList.empty()))
  {
  	for (NSPersonsAttributeIter iter = ResultList.begin() ; ResultList.end() != iter ; iter++)
    {
    	NSTeamDisplay	*pTeamD = new NSTeamDisplay(*iter, pContexte) ;
			pTeamsDisplayed->push_back(pTeamD) ;
    }
  }
}

// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::ScrollPerson()// Arguments   : Aucun
// Description : Scrolle la liste en fonction du nom et du prenom
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::scrolling()
{
  if (pTeamsDisplayed->empty())
    return ;

  int			index = 0 ;

  _sTeamName = pNom->GetText() ;
  pseumaj(&_sTeamName) ;

  if (string("") == _sTeamName)
  	return ;

  size_t iTeamNameLen = strlen(_sTeamName.c_str()) ;

  for (NSTeamDisplayIter i = pTeamsDisplayed->begin() ; pTeamsDisplayed->end() != i ; i++)
  {
    string sTeamLabel = string((*i)->getLabel()) ;
    pseumaj(&sTeamLabel) ;

    size_t iTeamLabelLen = strlen(sTeamLabel.c_str()) ;

    if ((iTeamLabelLen >= iTeamNameLen) && (string(sTeamLabel, 0, iTeamNameLen) == _sTeamName))
    // if (strncmp(teamName, sTeamLabel.c_str(), strlen(teamName)) <= 0)
    {
      pListe->SetSel(index, true) ;
      pListe->EnsureVisible(index, true) ;
      break ;
    }
    index++ ;
  }
}

// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::saveMemberSelected(int index)// Arguments   : Index de la personne s�lectionn�
// Description : Conserve le nss de la personne s�lectionn�e
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::saveSelectedMember(size_t index)
{
	// fabTODO
  if (index < pTeamsDisplayed->size())
		teamID = ((*pTeamsDisplayed)[index])->getID() ;
}

// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::RetrouvePersonSelect()// Arguments   : Aucun
// Description : Retrouve le patient s�lectionn�
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::RetrouvePersonSelect()
{
  if (pTeamsDisplayed->empty())
    return ;

  int index = 0 ;
	for (NSTeamDisplayIter teamIter = pTeamsDisplayed->begin() ;  pTeamsDisplayed->end() != teamIter ; teamIter++)
  {
    if (teamID == (*teamIter)->getID())
    {
    	pListe->SetSel(index, true) ;
      break ;
    }
    index++ ;
  }
}

// -----------------------------------------------------------------------------
// Function    : NSTTeamListDialog::CmCreer()
// Arguments   : Aucun
// Description : positionne bCreer � true et sort par CmOk()
// Returns     : Rien
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::CmCreer()
{
	// fabFIXME
  bCreer        = true ;
  iSelectedTeam = -1 ;
  
  CloseWindow(IDOK) ;
}

// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::LineDown()// Arguments   : Aucun
// Description : G�re le d�filement de la liste d'une ligne vers le bas
// Returns     : True->Ok False->Echec
// -----------------------------------------------------------------------------
bool
NSTTeamListDialog::LineDown()
{
	if (false == bVScroll)
  	return false ;

	// Par convention en N_TIERS le nombre de personnes affich�es (nbNom) vaut 10  // Pour l'instant : PageDown sera �quivalent � LineDown  // Revoir la gestion des curseurs de liste (tableau tampon de 50 pers. par exple)  pTeamsDisplayed->vider() ;

  serviceName	= (NautilusPilot::SERV_SEARCH_OBJECT_HAVING_TRAITS).c_str() ;

  NSBasicAttributeArray	AttrArray ;
  AttrArray.push_back(new NSBasicAttribute("trait", TEAM_LNOMA)) ;
  AttrArray.push_back(new NSBasicAttribute(STEP, string("100"))) ;
  AttrArray.push_back(new NSBasicAttribute(NEWLIST, string("1"))) ;

  NSPersonsAttributesArray ResultList	;

  bool	listOk = pContexte->getSuperviseur()->getPilot()->objectList(serviceName, &ResultList, &AttrArray) ;

  if ((listOk) && (false == ResultList.empty()))
  {
    for (NSPersonsAttributeIter iterResult = ResultList.begin() ; ResultList.end() != iterResult ; iterResult++)
    {
    	NSTeamDisplay *pTeamD = new NSTeamDisplay(*iterResult, pContexte) ;
      pTeamsDisplayed->push_back(pTeamD) ;
    }

    displayList() ;
/*
		// fabFIXME
    RetrouvePersonSelect() ;
*/
  }

  return true ;
}


// -----------------------------------------------------------------------------// Function    : NSTTeamListDialog::LineUp()// Arguments   : Aucun
// Description : G�re le d�filement de la liste d'une ligne vers le haut
// Returns     : Rien
// -----------------------------------------------------------------------------
bool
NSTTeamListDialog::LineUp()
{
  if (!bVScroll)
  	return false ;

  // Introduire le code pour retour en arri�re
  return true ;}


// -----------------------------------------------------------------------------// NSTTeamListDialog::CanClose()// R�pond � OK. Positionne le patient sur le patient s�lectionn�.
// -----------------------------------------------------------------------------
bool
NSTTeamListDialog::CanClose()
{
	return TDialog::CanClose() ;
}


// -----------------------------------------------------------------------------// NSTTeamListDialog::CmOk()// R�pond � OK. Positionne le patient sur le patient s�lectionn�.
// -----------------------------------------------------------------------------
void
NSTTeamListDialog::CmOk()
{
	iSelectedTeam = pListe->IndexItemSelect() ;
  if ((iSelectedTeam >= 0) && (iSelectedTeam < (int) pTeamsDisplayed->size()))
  	pSelectedTeam = ((*pTeamsDisplayed)[iSelectedTeam]) ;
  else
  {
  	erreur("Vous devez choisir une Equipe.", warningError, 0, GetHandle()) ;
    return ;
  }
  CloseWindow(IDOK) ;
}

