/*
** Copyright Nautilus, (10/9/2004)
** david.giocanti@nautilus-info.com

** Ce logiciel est un programme informatique servant � [rappeler les
** caract�ristiques techniques de votre logiciel].

** Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
** respectant les principes de diffusion des logiciels libres. Vous pouvez
** utiliser, modifier et/ou redistribuer ce programme sous les conditions
** de la licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA
** sur le site "http://www.cecill.info".

** En contrepartie de l'accessibilit� au code source et des droits de copie,
** de modification et de redistribution accord�s par cette licence, il n'est
** offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
** seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
** titulaire des droits patrimoniaux et les conc�dants successifs.

** A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
** associ�s au chargement,  � l'utilisation,  � la modification et/ou au
** d�veloppement et � la reproduction du logiciel par l'utilisateur �tant
** donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
** manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
** avertis poss�dant  des  connaissances  informatiques approfondies.  Les
** utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
** logiciel � leurs besoins dans des conditions permettant d'assurer la
** s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
** � l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.

** Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez
** pris connaissance de la licence CeCILL, et que vous en avez accept� les
** termes.
*/

#include <iostream>
#include "ns_ob1\Marker.h"

long Valeur::_lObjectCount        = 0 ;
long MarkerInteger::_lObjectCount = 0 ;
long MarkerString::_lObjectCount  = 0 ;

/* Return an int  */
int
MarkerObject::intValue() const throw(std::string)
{
  return 0 ;
}

/* return an string */
std::string
MarkerObject::stringValue() const throw (std::string)
{
  const MarkerString* p = dynamic_cast<const MarkerString* >(this) ;
  if ((MarkerString*) NULL == p)
    throw std::string("bad cast") ;
  else
    return (p->getValue()) ;
}

/* Print teh information in a MarkerString Class */
void
MarkerString::print(std::ostream& ostr) const
{
  ostr << "MarkerString : " << _value << std::endl ;
}

/* Print the information present in MarkerInteger */
void
MarkerInteger::print(std::ostream& ostr) const
{
  ostr << "MarkerInteger: " << _value << std::endl ;
}

void
MarkerInteger::htmlPrint(std::string& input)
{
  char taille[16] ;
  itoa(_value, taille, 10) ;
  input += "{<b>Marker (int) :</b>" ;
  input.append(taille) ;
  input += "}\n" ;
}

void
MarkerString::htmlPrint(std::string& input)
{
  input += "{<b>Marker (string) :</b>" + _value ;
  input += "} \n" ;
}

//------------------------------------------------------------------------------
/*
** Valeur Class
*/

Valeur::Valeur(std::string keys, MarkerObject* val)
{
  _lObjectCount++ ;

  _key  = keys ;
  _data = val ;
}

Valeur::Valeur(const Valeur& rv)
{
  _lObjectCount++ ;

  _key = rv._key ;

  _data = (MarkerObject*) 0 ;
  if (rv._data)
    putValue(rv._data, true) ;
}

Valeur::~Valeur()
{
  if (_data)
    delete _data ;

  _lObjectCount-- ;
}

Valeur&
Valeur::operator=(const Valeur& src)
{
  if (&src == this)
		return *this ;

  _key = src._key ;

  if (_data)
  {
    delete _data ;
    _data = (MarkerObject*) 0 ;
  }

  if (src._data)
    putValue(src._data, true) ;

  return *this ;
}

void
Valeur::htmlPrint(std::string& input)
{
  input += "[KEY : " + _key ;
  _data->htmlPrint(input) ;
  input += "] <br /> \n" ;
}

/* Put a value in MarkerObject */
/* Rule is that a king of MarkerObject can only be replaced by the same kind */
void Valeur::putValue(MarkerObject* temp, bool bDuplicate)
{
  // is temp a MarkerString object?
  //
  MarkerString* p1 = dynamic_cast<MarkerString *>(temp) ;
  if (p1)
  {
    putStringValue(p1, bDuplicate) ;
    return ;
  }

  // is temp a MarkerInteger object?
  //
  MarkerInteger* p2 = dynamic_cast<MarkerInteger *>(temp) ;
  if (p2)
  {
    putIntValue(p2, bDuplicate) ;
    return ;
  }
}

void Valeur::putStringValue(MarkerString* temp, bool bDuplicate)
{
  // bool bContentIsString = false ;

  if (_data)
  {
/*
    MarkerString* p = dynamic_cast<MarkerString *>(_data) ;
    if (p)
      bContentIsString = true ;
*/

    delete _data ;
    _data = (MarkerObject*) 0 ;

/*
    if (false == bContentIsString)
    {
      if (temp && (false == bDuplicate))
        delete temp ;
      return ;
    }
*/
  }

  if ((MarkerString*) NULL == temp)
    return ;

  if (bDuplicate)
    _data = new MarkerString(*temp) ;
  else
    _data = temp ;
}

void Valeur::putIntValue(MarkerInteger* temp, bool bDuplicate)
{
  // bool bContentIsInt = false ;

  if (_data)
  {
/*
    MarkerInteger* p = dynamic_cast<MarkerInteger *>(_data) ;
    if (p)
      bContentIsInt = true ;
*/

    delete _data ;
    _data = (MarkerObject*) 0 ;

/*
    if (false == bContentIsInt)
    {
      if (temp && (false == bDuplicate))
        delete temp ;
      return ;
    }
*/
  }

  if ((MarkerInteger*) NULL == temp)
    return ;

  if (bDuplicate)
    _data = new MarkerInteger(*temp) ;
  else
    _data = temp ;
}

std::ostream&	operator<< (std::ostream& ostr, const MarkerObject& m)
{
  m.print(ostr) ;
  return (ostr) ;
}

ValeurArray::ValeurArray(const ValeurArray& rv)
{
  if (false == rv.empty())
    for (ValeurConstIter it = rv.begin() ; rv.end() != it ; it++)
      push_back(new Valeur(**it)) ;
}

ValeurArray::~ValeurArray()
{
  vider() ;
}

void
ValeurArray::vider()
{
  if (false == empty())
    for (ValeurIter it = begin() ; end() != it ; )
    {
      delete *it ;
      erase(it) ;
    }
}

ValeurArray&
ValeurArray::operator=(const ValeurArray& src)
{
  if (&src == this)
		return *this ;

  vider() ;

  if (false == src.empty())
    for (ValeurConstIter it = src.begin() ; src.end() != it ; it++)
      push_back(new Valeur(**it)) ;

  return *this ;
}

bool
ValeurArray::Exist(std::string& sKey)
{
	if (empty())
    return false ;

  for (ValeurIter iter = begin() ; end() != iter ; iter++)
    if ((*iter)->Key() == sKey)
      return true ;

	return false ;
}

void
ValeurArray::Remove(std::string& sKey)
{
	if (empty())
		return ;

	for (ValeurIter iter = begin() ; end() != iter ; )
	{
		std::string temp = (*iter)->Key() ;
		if ((*iter)->Key() == sKey)
		{
			delete *iter ;
			erase(iter) ;
		}
    else
    	iter++ ;
	}
}

MarkerObject*
ValeurArray::get(std::string& key_to_find)
{
	if (empty())
		return (MarkerObject*) 0 ;

  for (ValeurIter iter = begin() ; end() != iter ; iter++)
    if (key_to_find == (*iter)->Key())
			return ((*iter)->Mark()) ;

	return (MarkerObject*) 0 ;
}

bool
ValeurArray::hasStringAttributes(std::string sName, std::string sVal)
{
	if (empty())
		return false ;

  for (ValeurIter iter = begin() ; end() != iter ; iter++)
  {
		if ((*iter)->Key() == sName)
		{
      MarkerString* pStringObj = dynamic_cast<MarkerString*>((*iter)->Mark()) ;
			if (pStringObj && (pStringObj->stringValue() == sVal))
				return true ;
		}
	}
	return false ;
}

bool
ValeurArray::hasSubStringAttributes(std::string sName, std::string sVal)
{
	if (empty())
		return false ;

  for (ValeurIter iter = begin() ; end() != iter ; iter++)
  {
		if ((*iter)->Key() == sName)
		{
      MarkerString* pStringObj = dynamic_cast<MarkerString*>((*iter)->Mark()) ;
			if (pStringObj && (pStringObj->stringValue().find(sVal) == std::string::npos))
				return true ;
		}
	}
	return false ;
}

