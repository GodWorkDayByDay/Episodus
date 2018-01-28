// -----------------------------------------------------------------------------// NsMailManager.cpp
// -----------------------------------------------------------------------------
// Outil de gestion des mails
// -----------------------------------------------------------------------------
// $Revision: 1.2 $
// $Author: pameline $
// $Date: 2015/02/07 13:03:30 $
// -----------------------------------------------------------------------------
// PA - 06/2012
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

#include "nsepisod\nsMailManager.h"

#include "nsdn\nsdocum.h"

// -----------------------------------------------------------------------------
//
// Classe NSPapyrus
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSMailManager::NSMailManager(NSContexte *pCtx)
              :NSRoot(pCtx)
{
}

NSMailManager::~NSMailManager()
{
}

void
NSMailManager::getUrlsForDomain(string sDomain, string &sUrlSmtp, string &sUrlPop, string &sUrlImap)
{
  sUrlSmtp = string("") ;
  sUrlPop  = string("") ;
  sUrlImap = string("") ;

  if (string("") == sDomain)
    return ;

  NSLocalChapterArray faiDescriptors ;

  string sFileName = pContexte->PathName("FPER") + string("fai.dat") ;
  string sErrorMsg = string("") ;
  faiDescriptors.init(sFileName, &sErrorMsg) ;

  if (string("") != sErrorMsg)
  {
    string sErrorText = string("NSMailManager::getUrlsForDomain error: ") + sErrorMsg ;
    pContexte->getSuperviseur()->trace(&sErrorText, 1, NSSuper::trError) ;
    erreur(sErrorText.c_str(), standardError) ;
    return ;
  }

  NSLocalisedChapter* pChapter = faiDescriptors.getChapterWhereText(string("domain"), sDomain) ;

  // Unknown domain... try to guess
  //
  if (NULL == pChapter)
  {
    sUrlSmtp = string("smtp.") + sDomain ;
    sUrlPop  = string("pop.") + sDomain ;
    sUrlImap = string("imap.") + sDomain ;

    return ;
  }

  // Known domain, set information
  //
  sUrlSmtp = pChapter->getLocalText(string("SMTP")) ;
  sUrlPop  = pChapter->getLocalText(string("POP")) ;
  sUrlImap = pChapter->getLocalText(string("IMAP")) ;
}

NSMailManager&
NSMailManager::operator=(const NSMailManager& src)
{
  if (this == &src)
  	return *this ;

  return (*this) ;
}

int
NSMailManager::operator==(const NSMailManager& o)
{
  // if (_sIndex == o._sIndex)
    return 1 ;

  // return 0 ;
}

