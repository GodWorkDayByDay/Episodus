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

#ifndef   BB1CLASINDEX_H_
# define   BB1CLASINDEX_H_

#include <string>
#include <map>

/**
* \brief Class used to optimize the test of the class
*/
/**
* Class used to optimize the test of the class
* Annuaire des classes.
* \todo Retirer Comlpique les choses et n'apporte pas reelement d'am�lioration des performances
*/
class BB1ClassIndex
{
  std::map<std::string, int> _index ;  /**< Map beetween name and id \brief Map beetween name and id */
  int _max ;  												/**< Map beetween name and id \brief Map beetween name and id */

  public:
  /**
  * \brief Constructor
  */
  /**
  *Constructor
  */
  BB1ClassIndex() ;

  /**
  * \brief Destructor
  */
  /**
  *  Destructor
  */
  ~BB1ClassIndex() ;

  /**
  * \brief new class item to insert
  */
  /**
  * new class item to insert
  */
  void insertItem(std::string& key) ;

  /**
  * \brief return the id in function of the name
  */
  /**
  * return the id in function of the name <BR>
  * Renvoie l'identifiant entier en fonction du nom de la classe
  * @param clas Class name
  * @return id of the class
  */
  int operator[] (std::string& clas) const;

  /**
  * \brief summarize index in a string
  */
  /**
  * summarize index in a string
  * R�sume le dico dans une string
  * @resume summaray
  */
  std::string toHTML() ;
};

#endif /* Finde BB1ClassIndex.h */

