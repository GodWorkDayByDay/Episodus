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

#ifndef   TRANSFERT_H
# define   TRANSFERT_H

#include <iostream>
#include <string>
#include <map>

#ifndef _DANSBBKDLL
#define _BBKEXPORT __import
#else
#define _BBKEXPORT __export
#endif

#include "ns_ob1\TypedVal.h"

class BB1Object;


/**
* \brief Used to give structured information to KS
*/
/**
*  TransfertClass is used to give structured information to KS  <BR>
*  This class contains the name of the information (generaly this name is a nautilus path) <BR>
*  La classe transfert sert a transmettre des informations sutructur�s au KS.  <BR>
*  Cette classe est constitu� de cl� (son nom qui est g�n�ralement, un code ou un chemin nautilus) <BR>
*/
class TransfertClass
{
  protected:

    BB1Object*      _object ; /**< Object that contains information. Information a transmettre au BB \brief  Object that contains information. Information a transmettre au BB */
    std::string     _key ;    /**< key to find. Cl� a trouver \brief key to find. Cl� a trouver */
    NSSearchStruct* _searchStruct ;
    long int        _iPersistenceHandle ; // Object persistence handle

  public:
  	/**
    * \brief Constructor
    */
    /**
    * Constructor
    * @param key Name of the information
    * @param temp I,formation to transmit
    */
    TransfertClass(std::string key, NSSearchStruct* pSearchStruct, BB1Object* temp, long int iPersistenceHandle)
    {
    	_key                = key ;
      _searchStruct       = pSearchStruct ;
      _object             = temp ;
      _iPersistenceHandle = iPersistenceHandle ;
    }

    TransfertClass(const TransfertClass& temp)
    {
    	_key                = temp._key ;
      _searchStruct       = temp._searchStruct ;
      _object             = temp._object ;
      _iPersistenceHandle = temp._iPersistenceHandle ;
    }

    ~TransfertClass() ;

    /**
    * get the name of the information
    */
    /**
    * get the name of the information  <BR>
    * Renvoie le nom de l'information contenue dans la structure
    * @return Name of the information
    */
    std::string     Key()          { return (_key) ; }
    NSSearchStruct* SearchStruct() { return _searchStruct ; }

    /**
    * \brief Return the information on the object
    */
    /**
    * Return the information on the object  <BR>
    * Renvoie l'information contenue
    * @return return the infomration that is a BB1Object
    */
    BB1Object*  OBject() {return (_object) ; }

    long int    getPersistenceHandle() { return _iPersistenceHandle ; }

    TransfertClass& operator=(const TransfertClass& src)
    {
    	if (&src == this)
      	return *this ;

    	_key                = src._key ;
      _searchStruct       = src._searchStruct ;
      _object             = src._object ;
      _iPersistenceHandle = src._iPersistenceHandle ;

      return *this ;
    }
};


/**
* \brief Transfert a collcetion of data to a KS
*/
/**
* Class permettant le transfert d'informationde BBK    <BR>
* vers les KS pour pouvoir r�aliser l'executiond 'une action
*/
class _BBKEXPORT Transfert
{
	/**
  * \todo Adapter pour retirer le friend car non supporter sur certains compilateur recent
  */
  friend class Transfert ;

  public:
  	std::string _transfer_class ;     			 /**< Seems to not be used \brief Seems to not be used */

  protected:
    std::vector<TransfertClass* > _data ;   /**< Contains all informations to transfert to KS \brief Contains all informations to transfert to KS  */

  public:
  	/**
    * \brief Constructor
    */
  	/**
    * Constructor
    */
    Transfert() ;

    /**
    * \brief Copy Constructeur
    */
    /**
    * Copy Constructeur
    * @param temp reference to clone
    */
    Transfert(const Transfert& temp) ;

    /**
    * \brief Destructor
    */
    /**
    * Destructor
    */
    ~Transfert() ;

    /**
    *  \brief Insert an information in the class
    */
    /**
    *  Insert an information in the class. This information can be acceed by his name <BR>
    *  Introduit un object dans la liste pour le transmettre au KS
    * @param key name of the information
    * @param val information to transmit
    */
    void insertItem(std::string& key, NSSearchStruct* pSearchStruct, BB1Object* val, long int iPersistenceHandle) ;

    /**
    * \brief Acces operator
    */
    /**
    *   Acces operator  <BR>
    *   Operateur d'acces
    *   @param clas name of the class to obtain
    *		@return Information to obtain . Return NULL if the insformation doe not exist
    */
    // BB1Object* operator[] (std::string& key) ;
    BB1Object* getObject(std::string& sKey, std::string& sSearchParams) ;

    /**
    * \brief Say if an information is present in the collection
    */
    /**
    *  Say if an information is present in the collection  <BR>
    *  Indique si l'information existe
    *  @param  key nom de l'information a chercher
    *  @return true if the information exist and false else
    */
    bool  exist(std::string& key, std::string& sSearchParams) ;
    bool  exist(std::string& key, NSSearchStruct* pSearchStruct) ;

    BB1Object* getAskedQuestion() ;
    void       setAskedQuestion(BB1Object* pQuest, long int iPersistenceHandle) ;

    void  vider() ;

    Transfert& operator=(const Transfert& src) ;

    std::vector<TransfertClass* >* getData() { return &_data ; }
};

#endif