// -----------------------------------------------------------------------------
// attvalelem.cpp
// -----------------------------------------------------------------------------
// Objet Attribut Valeur avec Fonctionnalit�s
// -----------------------------------------------------------------------------
// $Revision: 1.2 $
// $Author: pameline $
// $Date: 2009/07/04 13:52:09 $
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


#include "nsutil/attvalelem.h"


AttributeValueList::AttributeValueList()
	: AttributeValueVector()
{
}


AttributeValueList::AttributeValueList(const AttributeValueList& src)
	: AttributeValueVector()
{
	if (!src.empty())
  {
  	for (AttributeValueCIter avIter = src.begin() ; avIter != src.end() ; avIter++)
    	push_back(new AttributeValueElem(**avIter)) ;
  }
}


AttributeValueList::~AttributeValueList()
{
	clearContents() ;
}


void
AttributeValueList::clearContents()
{
	if (!empty())
  	for (AttributeValueIter avIter = begin() ; avIter != end() ; )
    {
    	delete (*avIter) ;
      erase(avIter) ;
    }
}


bool
AttributeValueList::addElem(string attr, string val)
{
	if (!isAttrPresent(attr))
  {
  	push_back(new AttributeValueElem(attr, val)) ;
    return true ;
  }
	return false ;
}


bool
AttributeValueList::isAttrPresent(string attr)
{
	if (!empty())
  	for (AttributeValueIter avIter = begin() ; avIter != end() ; avIter++)
    	if ((*avIter)->getAttribute() == attr)
      	return true ;
  return false ;
}


AttributeValueElem *
AttributeValueList::getAVwithAttr(string attr) const
{
	if (!empty() && (attr != ""))
  {
  	for (AttributeValueCIter avIter = begin() ; avIter != end() ; avIter++)
    	if ((*avIter)->getAttribute() == attr)
      	return (*avIter) ;
  }
  return NULL ;
}


AttributeValueList&
AttributeValueList::operator=(const AttributeValueList& src)
{
	clearContents() ;

  if (!src.empty())
  {
  	for (AttributeValueCIter avIter = src.begin() ; avIter != src.end() ; avIter++)
    	push_back(new AttributeValueElem(**avIter)) ;
  }

  return (*this) ;
}


int
AttributeValueList::operator==(const AttributeValueList& src)
{
  if ((!src.empty()) && (!empty()))
  {
  	for (AttributeValueCIter avIter = begin() ; avIter != end() ; avIter++)
    {
    	AttributeValueElem *elem = src.getAVwithAttr((*avIter)->getAttribute()) ;
      if (elem && (elem->getValue() != (*avIter)->getValue()))
      	return 0 ;
    }
  }
	else if (src.empty() && !empty())
  	return 0 ;
  return 1 ;
}

