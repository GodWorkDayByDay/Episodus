// --------------------------------------------------------------------------// nscapelements.h// -----------------------------------------------------------------------------
// Document/Vues Capture Donn�es Utilisateur
// -----------------------------------------------------------------------------
// $Revision: 1.2 $
// $Author: fabrice $
// $Date: 2005/05/24 17:41:04 $
// -----------------------------------------------------------------------------
// FLP - Aout 2001
// --------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Copyright Nautilus, 2005
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


#ifndef __NSCAPELEMENTS_H__
# define __NSCAPELEMENTS_H__

# include <owl\dialog.h>
# include <vector>
# include <string>

//# include "partage\nsglobal.h"
//# include "partage\NTArray.h"
# include "ns_capture\nscaptexport.h"
# include "ns_capture\nscaptbitmap.h"

// -----------------------------------------------------------------------------
// Objets de capture Episodus
// -----------------------------------------------------------------------------
class _NSCAPTURECLASSE NSCapture
{
 public:
  string sChemin ;
  string sLibelle ;
  string sUnit ;
  string sClassifier ;
  string sClassifResultO ;
  string sClassifResultP ;
  string sClassifResultI ;

  NSOCRbloc * pOCRBloc ;

  // Constructeurs
  NSCapture() ;
  NSCapture(string sChem, string sLibel, string sClassif = "", string sUnite = "") ;
  NSCapture(NSOCRbloc * pBloc) ;
  NSCapture(const NSCapture& rv) ;

  // Destructeur
  virtual ~NSCapture() {}

  bool prendChemin() ;

  NSCapture& operator=(const NSCapture& src) ;
} ;


typedef vector<NSCapture *>             NSCaptureVector ;
typedef NSCaptureVector::iterator       CaptureIter ;
typedef NSCaptureVector::const_iterator CaptureCIter ;


class _NSCAPTURECLASSE NSCaptureArray : public NSCaptureVector
{
 public:
  // Constructeurs
  NSCaptureArray() : NSCaptureVector() {}
  NSCaptureArray(const NSCaptureArray& rv) ;

  // Destructeur
  virtual ~NSCaptureArray() ;

  int trouveChemin(string sChem, string * pLib, int pos = 0) ;

  void vider() ;
  void ajouter(NSCapture* pNew) ;
  void append(NSCaptureArray* pNewCapture) ;

  NSCaptureArray& operator=(const NSCaptureArray& src) ;
} ;


// --------------------------------------------------------------------------
//CONTEXTE DE CAPTURE (Chemin)
// --------------------------------------------------------------------------
class NSCaptureContexte
{ public:
  string sChemin ;
  string sLibelle ;
  string sClassifier ;

  NSCaptureContexte(string sChem = "", string sLib = "", string sClassif = "") ;
  NSCaptureContexte(const NSCaptureContexte& rv) ;

  // Destructeur
  ~NSCaptureContexte() ;

  NSCaptureContexte& operator=(const NSCaptureContexte& src) ;
} ;


// --------------------------------------------------------------------------
// D�finition de NSProtocoleArray (Array de NSProtocole(s))
// --------------------------------------------------------------------------
typedef vector<NSCaptureContexte *>     NSCaptCtxArray ;
typedef NSCaptCtxArray::iterator        IterCaptCtx ;
typedef NSCaptCtxArray::const_iterator  CIterCaptCtx ;


class _NSCAPTURECLASSE NSCaptureCtxArray : public NSCaptCtxArray
{
 public:
  // Constructeurs
  NSCaptureCtxArray() : NSCaptCtxArray() {}
  NSCaptureCtxArray(const NSCaptureCtxArray& rv) ;
  //
  // Destructeur
  virtual ~NSCaptureCtxArray() ;
  void vider() ;

  bool charger(string sFichierTempo) ;
} ;


#endif // !__NSCAPELEMENTS_H__

