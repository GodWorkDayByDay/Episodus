// -----------------------------------------------------------------------------
// NSHTMemberControls.cpp// -----------------------------------------------------------------------------// Contr�les G�n�riques pour les liste de Membres de l'Equipe de Sant�
// -----------------------------------------------------------------------------
// $Revision: 1.2 $
// $Author: pameline $
// $Date: 2009/07/04 09:15:49 $
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
#include "nsbb\nsbb.h"
#include "nsbb\NSHTMemberControls.h"


NSHTMemberListDialog::NSHTMemberListDialog(TWindow *pere, string sRes, NSContexte *pCtx, TModule *module)
                     :NSUtilDialog(pere, pCtx, sRes.c_str(), pNSDLLModule)
{
/*
	// Cr�ation de tous les "objets de contr�le"
  pNom						= new NSHTMemberListEdit(this, IDC_LC_NOM, COR_NOM_LEN) ;
  pListe					= new NSHTMemberListWindow(this, IDC_LC_LW, module) ;

#ifndef N_TIERS
	pVScroll				= new NSHTMemberListScrollBar(this, IDC_LC_VSCROLL) ;
#endif
	pCreer					= new TButton(this, IDC_LC_CREER) ;

  sNumSelect			= "" ;  bCreer					= false ;  bAvecCreer			= avecCreer ;*/}


NSHTMemberListDialog::~NSHTMemberListDialog()
{
}


// -----------------------------------------------------------------------------
// classe NSHTMemberListWindow
// -----------------------------------------------------------------------------

DEFINE_RESPONSE_TABLE1(NSHTMemberListWindow, TListWindow)
	EV_WM_KEYDOWN,
  EV_WM_LBUTTONDBLCLK,
  EV_WM_LBUTTONDOWN,
END_RESPONSE_TABLE ;


// -----------------------------------------------------------------------------
// Constructeurs
// -----------------------------------------------------------------------------
NSHTMemberListWindow::NSHTMemberListWindow(NSHTMemberListDialog *pere, int resId, TModule *module)
	: TListWindow(pere, resId, module)
{
	pDlg					= pere ;
  Attr.Style		|= LVS_REPORT | LVS_SHOWSELALWAYS ;
  Attr.ExStyle	|= WS_EX_NOPARENTNOTIFY ;
}


// -----------------------------------------------------------------------------
// setupwindow// -----------------------------------------------------------------------------voidNSHTMemberListWindow::SetupWindow()
{
	ListView_SetExtendedListViewStyle(this->HWindow, LVS_EX_FULLROWSELECT) ;
  TListWindow::SetupWindow() ;
}


// -----------------------------------------------------------------------------
// setFocus
// -----------------------------------------------------------------------------
/*
void
NSHTMemberListWindow::EvSetFocus(HWND hWndLostFocus)
{
}
*/


// -----------------------------------------------------------------------------
// killFocus
// -----------------------------------------------------------------------------
/*
void
NSHTMemberListWindow::EvKillFocus(HWND hWndGetFocus)
{
}
*/


// -----------------------------------------------------------------------------// keyDown// -----------------------------------------------------------------------------voidNSHTMemberListWindow::EvKeyDown(uint key, uint repeatCount, uint flags){	int count, itemSel ;
  switch (key)  {
  	case VK_DOWN	:	count = GetItemCount() ;
            				itemSel = IndexItemSelect() ;
            				if			(itemSel == (count - 1))
            				{
                			pDlg->sbLineDown() ;
                			SetSel(itemSel, true) ;
            				}
            				else if (itemSel != -1)
                			SetSel(itemSel + 1, true) ;
            				break ;

    case VK_UP		:	itemSel = IndexItemSelect() ;            				if (itemSel == 0)
            				{
                			pDlg->sbLineUp() ;
                			SetSel(itemSel, true) ;
            				}
            				else if (itemSel != -1)
                			SetSel(itemSel - 1, true) ;
            				break ;

    case VK_NEXT	:	itemSel = IndexItemSelect() ;            				if (itemSel != -1)
            				{
                			pDlg->sbPageDown();
                			SetSel(itemSel, true);
            				}
            				break ;

    case VK_PRIOR	:	itemSel = IndexItemSelect() ;            				if (itemSel != -1)
            				{
                			pDlg->sbPageUp() ;
                			SetSel(itemSel, true) ;
            				}
            				break ;

    default			:	TListWindow::EvKeyDown(key, repeatCount, flags) ;  }
}// -----------------------------------------------------------------------------
// lButtonDown
// -----------------------------------------------------------------------------
void
NSHTMemberListWindow::EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point)
{
  // int count = GetItemCount() ;
	TLwHitTestInfo info(point) ;

  int index = HitTest(info) ;

  if (info.GetFlags() & LVHT_ONITEM)
  	pDlg->saveSelectedMember(index) ;

  // On appelle le Button Down de la classe m�re
  TListWindow::EvLButtonDown(modKeys, point) ;
}


// -----------------------------------------------------------------------------
// lButtonSblClk
// -----------------------------------------------------------------------------
void
NSHTMemberListWindow::EvLButtonDblClk(uint /* modKeys */, NS_CLASSLIB::TPoint& point)
{
	TLwHitTestInfo info(point) ;

  HitTest(info) ;
  if (info.GetFlags() & LVHT_ONITEM)  	pDlg->CmOk() ;
}


// -----------------------------------------------------------------------------
// indexItemSelect
// -----------------------------------------------------------------------------
int
NSHTMemberListWindow::IndexItemSelect()
{
	int count = GetItemCount() ;
  int index = -1 ;

  for (int i = 0 ; i < count ; i++)  	if (GetItemState(i, LVIS_SELECTED))
    {
    	index = i ;
      break ;
    }
  return index ;
}


// -----------------------------------------------------------------------------
// NSHTMemberListEdit
// -----------------------------------------------------------------------------

DEFINE_RESPONSE_TABLE1(NSHTMemberListEdit, NSUtilEdit)
	EV_WM_CHAR,
END_RESPONSE_TABLE ;

voidNSHTMemberListEdit::EvChar(uint key, uint repeatCount, uint flags)
{
	NSUtilEdit::EvChar(key, repeatCount, flags) ;

  if ((key != VK_RETURN) && (key != VK_TAB))  	pDlg->scrolling() ;
}
