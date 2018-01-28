/*
** Copyright Nautilus, (10/9/2004)
** fabrice.le_perru@nautilus-info.com
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

#ifdef __GNUC__
# pragma implementation
#endif

#include <iostream.h>  // for operator<<(...)

#ifndef FOR_WINDOWS
# include "BB1Link.h"
# include "BB1Object.h" // for BB1Link::operator<<(...)
# include "BB1KB.h"     // for BB1Link::OppositeLinkName(...)
# include "BB1BB.h"     // for BB1Link::OppositeLinkName(...)
#else
# include "ns_ob1\BB1Link.h"
# include "ns_ob1\BB1Object.h" // for BB1Link::operator<<(...)
# include "ns_ob1\BB1KB.h"     // for BB1Link::OppositeLinkName(...)
# include "ns_ob1\BB1BB.h"     // for BB1Link::OppositeLinkName(...)
#endif

BB1LinkPair::BB1LinkPair(const string& ForwardLink,
                         const string& InverseLink,
                         const string& FromClassName,
                         const string& ToClassName)
            :m_ForwardLink(ForwardLink),
             m_InverseLink(InverseLink),
             m_FromClassName(FromClassName),
             m_ToClassName(ToClassName)
{
#ifdef _DEBUG_
  cout << "-- DEBUG:: BB1LinkPair::BB1LinkPair("
       << "\"" << ForwardLink << "\", "
       << "\"" << InverseLink << "\", "
       << "\"" << FromClassName << "\""
       << "\"" << ToClassName << "\")\n\n" ;
#endif
}

// -----------------------------------------------------------------------------
// constructeur copie -- add fab
// -----------------------------------------------------------------------------
BB1LinkPair::BB1LinkPair(const BB1LinkPair& src)
            :m_ForwardLink(src.m_ForwardLink),
             m_InverseLink(src.m_InverseLink),
             m_FromClassName(src.m_FromClassName),
             m_ToClassName(src.m_ToClassName)
{
}

// -----------------------------------------------------------------------------
// destructeur -- add fab
// -----------------------------------------------------------------------------
BB1LinkPair::~BB1LinkPair()
{
}

long BB1Link::_lBB1LinkCount = 0 ;

// -----------------------------------------------------------------------------
// The application program's version
// -----------------------------------------------------------------------------
BB1Link::BB1Link(const string sName, BB1Object* pToObject)
        :_sName(sName),
         _pToObject(pToObject),
         _CycleCreated(PRECYCLE),
         _bHandledP(false),
         _bReflexiveP(false)
{
  _lBB1LinkCount++ ;

#ifdef _DEBUG_
  cout << "-- DEBUG:: BB1Link::BB1Link(\"" << Name << "\", ToObject)\n\n" ;
#endif
};

// -----------------------------------------------------------------------------
// The internal version
// -----------------------------------------------------------------------------
BB1Link::BB1Link(const string sName, BB1Object* pToObject, const Cycle cycle, bool bReflexiveP)
        :_sName(sName),
         _pToObject(pToObject),
         _CycleCreated(cycle),
         _bHandledP(false),
         _bReflexiveP(bReflexiveP)
{
  _lBB1LinkCount++ ;

#ifdef _DEBUG_
  cout << "-- DEBUG:: BB1Link::BB1Link(\"" << Name << ", *pToObject, cycle, <" << ReflexiveP << ">)\n\n" ;
#endif
};

// -----------------------------------------------------------------------------
// constructeur copie -- add fab
// -----------------------------------------------------------------------------
BB1Link::BB1Link(const BB1Link& src)
        :_sName(src._sName),
         _pToObject(src._pToObject),
         _CycleCreated(src._CycleCreated),
         _bHandledP(src._bHandledP),
         _bReflexiveP(src._bReflexiveP)
{
  _lBB1LinkCount++ ;
}

// -----------------------------------------------------------------------------
// destructeur -- add fab
// -----------------------------------------------------------------------------
BB1Link::~BB1Link()
{
  _lBB1LinkCount-- ;
}

// -----------------------------------------------------------------------------
// Given the name of a link, return the name of its opposite link.
// -----------------------------------------------------------------------------
const string
BB1Link::OppositeLinkName(const BB1Class* pC) const
{
#ifdef _DEBUG_
  cout << "-- DEBUG:: BB1Link::OppositeLinkName(c) const\n\n" ;
#endif

  if (_pToObject)
    return (_pToObject->KB().BB().OppositeLinkName(_sName, pC)) ;

  return string("") ;
}

// -----------------------------------------------------------------------------
// Send to the output stream a textual representation of the link
// -----------------------------------------------------------------------------
std::ostream& operator <<(std::ostream& os, const BB1Link& link)
{
  os << "  ("
     << link.Name()
     << " " ;

  if (link.ToObject())
     os << link.ToObject()->LongName() ;

  os << ")\n" ;

  return (os) ;
}

// -----------------------------------------------------------------------------
// Empty out a set of BB1Link
// -----------------------------------------------------------------------------
void
ClearSetOfBB1Link(LinkSet *pLinkset)
{
  if (NULL == pLinkset)
    return ;

#ifdef _DEBUG_
  cout << "-- DEBUG:: ClearSetOfBB1Link(LinkSet)\n\n" ;
#endif

  if (false == pLinkset->empty())
    for (LinkIter p = pLinkset->begin() ; pLinkset->end() != p ; )
    {
      delete (*p) ;
      pLinkset->erase(p) ;
    }
}

