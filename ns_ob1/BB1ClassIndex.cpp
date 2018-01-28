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
#include "ns_ob1\OB1ClassIndex.h"

BB1ClassIndex::BB1ClassIndex()
{
  _max = 1 ;
}

BB1ClassIndex::~BB1ClassIndex()
{
}

void BB1ClassIndex::insertItem(std::string& key)
{
  _index[key] = _max ;
  _max *= 2 ;
}

int
BB1ClassIndex::operator[] (std::string& clas) const
{
  std::map<std::string, int>::const_iterator ite = _index.find(clas) ;
  if (_index.end() != ite)
    return (*ite).second ;
  return -42 ;
}

std::string BB1ClassIndex::toHTML()
{
  std::string temp = "[Dictionnaire des classes <br /><ul>\n" ;

  std::map<std::string, int>::iterator ite ;
  if (false == _index.empty())
    for (ite = _index.begin() ; _index.end() != ite ; ite++)
    {
      temp += "<li>(" + (*ite).first +"," ;
      char ty[10] ;
      itoa((*ite).second , ty, 10) ;
      temp.append(ty) ;
      temp += ")</li>" ;
    }
  temp += "</ul>" ;
  return temp ;
}
