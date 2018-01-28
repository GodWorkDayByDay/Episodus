// -----------------------------------------------------------------------------// nsdivfct.cpp
// -----------------------------------------------------------------------------
// Pot-pourri de fonctions
// -----------------------------------------------------------------------------
// $Revision: 1.6 $
// $Author: pameline $
// $Date: 2016/08/19 06:35:59 $
// -----------------------------------------------------------------------------
// PA  - 3 octobre 2010
// -----------------------------------------------------------------------------

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

#include <stdio.h>

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/superLus.h"
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage\nsglobal.h"
  #include "nautilus\nssuper.h"
#endif

#include "partage\nsdivfile.h"

// -----------------------------------------------------------------------------
// Function    : NsFileExists(const char *ammorce, const char* suffixe)
// Arguments   :	ammorce  : premiers caract�res du pr�fixe du nom DOS
//				  			suffixe  : suffixe du nom de fichier DOS
//				  			chemin   : r�pertoire o� chercher
//				  			nomLibre : nom du fichier trouv� sous forme PPPPPPPP.SSS
// Description : Cherche le premier nom de fichier libre
// Returns     : RIEN
// -----------------------------------------------------------------------------
bool
NsFileExists(const std::string sFileName)
{
	DWORD fileAttr = GetFileAttributes(sFileName.c_str()) ;

  if (0xFFFFFFFF == fileAttr)
    return false ;

  return true ;
}
boolNsFileExists2(const string sFileNameAndPath){
  WIN32_FIND_DATA findFileData ;
	HANDLE hFileFound = FindFirstFile(sFileNameAndPath.c_str(), &findFileData) ;

  if (INVALID_HANDLE_VALUE == hFileFound)
    return false ;

  FindClose(hFileFound) ;
  return true ;
}voidNsParseFileName(const string sCompleteFileName, string &sPath, string &sName){  sPath = string("") ;  sName = string("") ;  size_t iLen = strlen(sCompleteFileName.c_str()) ;  if (0 == iLen)    return ;  // R�cup�ration du path  //
	size_t pos1 = sCompleteFileName.find_last_of(FILESLASH) ;

	if ((NPOS == pos1) || (iLen - 1 == pos1))
		return ;

	sPath = string(sCompleteFileName, 0, pos1 + 1) ;
  sName = string(sCompleteFileName, pos1 + 1, iLen - pos1 - 1) ;}voidNsParseExtension(const string sCompleteFileName, string &sRoot, string &sExtension){  sRoot      = string("") ;  sExtension = string("") ;  size_t iLen = strlen(sCompleteFileName.c_str()) ;  if (0 == iLen)    return ;  // R�cup�ration du path  //
	size_t pos1 = sCompleteFileName.find_last_of('.') ;

	if ((NPOS == pos1) || (iLen - 1 == pos1))
		return ;

	sRoot      = string(sCompleteFileName, 0, pos1 + 1) ;
  sExtension = string(sCompleteFileName, pos1 + 1, iLen - pos1 - 1) ;}boolNsDeleteTemporaryFile(NSSuper *pSuper, const string sFileName){  if (string("") == sFileName)    return true ;  if (::DeleteFile(sFileName.c_str()))
    return true ;

  DWORD  dwErrorCode = GetLastError() ;
  string sErrorText  = pSuper->getText("fileErrors", "errorDeletingTemporaryFile") + string(" ") + sFileName ;

  if      (ERROR_FILE_NOT_FOUND == dwErrorCode)
    sErrorText += string(" (file not found)") ;
  else if (ERROR_ACCESS_DENIED == dwErrorCode)
    sErrorText += string(" (access denied)") ;

  pSuper->trace(&sErrorText, 1) ;

#ifndef _ENTERPRISE_DLL
  if (ERROR_FILE_NOT_FOUND != dwErrorCode)
    erreur(sErrorText.c_str(), standardError, 0, pSuper->donneMainWindow()->GetHandle()) ;
#endif

  return false ;
}
//// Fournit (rapidement) le contenu fid�le d'un fichier sous forme d'une string
//stringgetFileContent(const NSSuper *pSuper, const string sFileName){
  ifstream in(sFileName.c_str(), std::ios::in | std::ios::binary) ;
  if (in)
  {
    string contents ;
    in.seekg(0, ios::end) ;
    contents.resize(in.tellg()) ;
    in.seekg(0, ios::beg) ;
    in.read(&contents[0], contents.size()) ;
    in.close() ;
    return(contents) ;
  }
  else if (pSuper)
  {
    string sErrorText = pSuper->getText("fileErrors", "errorOpeningInputFile") ;
    sErrorText += string(" ") + sFileName ;
    pSuper->trace(&sErrorText, 1, NSSuper::trError) ;
  }
  return string("") ;
}
