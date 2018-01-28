// -----------------------------------------------------------------------------
// NSHTMemberControls.h
// -----------------------------------------------------------------------------
// Contr�les G�n�riques pour les liste de Membres de l'Equipe de Sant�
// -----------------------------------------------------------------------------
// $Revision: 1.2 $
// $Author: pameline $
// $Date: 2009/07/23 17:03:17 $
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


#ifndef __NSHTMEMBERCONTROL_H__
# define __NSHTMEMBERCONTROL_H__

# include "nsbb\nslistwind.h"


/*
class NSHTMemberListEdit ;
class NSHTMemberListWindow ;
class NSHTMemberListScrollBar ;
*/

class _NSBBCLASSE NSHTMemberListDialog : public NSUtilDialog
{
 public:
  NSHTMemberListDialog(TWindow *pere, string sRes, NSContexte *pCtx, TModule *module = 0) ;
  ~NSHTMemberListDialog() ;

//  virtual void								SetupWindow()	= 0 ;//  bool InitRecherche() ;
//  void InitListe() ;
//  void AfficheListe() ;
//  void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
//  void InitPersonArray() ;
//  void PosLastPerson() ;
  virtual void								scrolling()		= 0 ;
  virtual void								sbLineDown()		= 0 ;
  virtual void								sbLineUp()			= 0 ;
  virtual void								sbPageDown()		= 0 ;
  virtual void								sbPageUp()			= 0 ;
  virtual void								saveSelectedMember(size_t index) = 0 ;	// replace GardeNum(int index)
//  void GardeNum(int index) ;
//  void RetrouvePersonSelect() ;
//  void CmSelectPids() ;
//  void CmCreer() ;

//  bool LineDown() ;
//  bool LineUp() ;

  virtual bool								CanClose() 		= 0 ;  virtual void								CmOk()				= 0 ;
// DECLARE_RESPONSE_TABLE(NSHTMemberListDialog) ;
} ;


// -----------------------------------------------------------------------------
// Objet "ScrollBar" utilis� pour faire d�filer verticalement la liste des// correspondants
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSHTMemberListScrollBar : public OWL::TScrollBar
{
 public:

  NSHTMemberListScrollBar(NSHTMemberListDialog *parent, int resourceId, TModule *module = 0) ;

  void 									FixeRange(int max, int taille) ;  void 									SBLineDown() ;
  void 									SBLineUp() ;
  void 									SBPageDown() ;
  void 									SBPageUp() ;
  void									PositionneCurseur() ;

	// variables
 	NSHTMemberListDialog	*pListeDlg ;
} ;


// -----------------------------------------------------------------------------
// Objet "ListWindow" avec gestion du double-click et du scroll (pour les correspondants)// -----------------------------------------------------------------------------
class _NSBBCLASSE NSHTMemberListWindow : public TListWindow
{
 public:

 	NSHTMemberListDialog	*pDlg ;

  NSHTMemberListWindow(NSHTMemberListDialog *pere, int resId, TModule *module = 0) ;  ~NSHTMemberListWindow() {}

  void    							SetupWindow() ;
  void    							EvSetFocus(HWND hWndLostFocus) ;
  void    							EvKillFocus(HWND hWndGetFocus) ;
  void    							EvKeyDown(uint key, uint repeatCount, uint flags) ;  void    							EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;
  void    							EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
  int     							IndexItemSelect() ;

 DECLARE_RESPONSE_TABLE(NSHTMemberListWindow) ;} ;

// -----------------------------------------------------------------------------// Classe NSTTeamListEdit// pour scroller quand on change le nom ou le pr�nom// -----------------------------------------------------------------------------
class _NSBBCLASSE NSHTMemberListEdit : public NSUtilEdit
{
 public:

 	NSHTMemberListDialog	*pDlg ;

  NSHTMemberListEdit(NSContexte *pCtx, NSHTMemberListDialog* pere, int resId, UINT iTextLen)                    :NSUtilEdit(pCtx, pere, resId, iTextLen) { pDlg = pere ; }
  ~NSHTMemberListEdit() {}

  void									EvChar(uint key, uint repeatCount, uint flags) ;
 DECLARE_RESPONSE_TABLE(NSHTMemberListEdit) ;} ;


#endif // __NSHTMEMBERCONTROL_H__

