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
#ifndef   SHEDULER_H_
# define   SHEDULER_H_

class Controler ;
class OB1Strategy ;
class OB1Controler ;

#include <vector>
// #include "ns_ob1\OB1Strategy.h"

/*
*\brief  Sheduler alogorithm type
*/
/*
* Type of algorithm used by sheduler to choice the strategie to solve at
* ech incrementation <BR>
* Type d'algorithme utiliser pour determiner la strat�gie qui va �tre lancer �
* chaque execution
*/
enum ShedulerAlgorithm
{
  STOCHASTIC = 0,   /**< Choice alogorithm based on random*/
  DETERMINIST = 1   /**< Deterministic based algorithm*/
};

/**
* \brief Choice which execute a strategy at each cycle
*/
/**
* The sheduler have to choice a strategy, and to execut it.  <BR>
* Le sheduler determine la strategie a ececut� a chaque cycle,
* La choisie et l'execute
*/
class Sheduler
{
 protected:

	int                        _during ;              /**< Number cycle allocated to BB  \brief Number cycle allocated to BB  */
	std::vector<OB1Strategy* > _Controler_History_X ; /**< Used for  strategie  : memory of deterministic mode : used for scheduling \brief Used for  strategie  : memory of deterministic mode : used for scheduling  */
	OB1Strategy*               current_problem ;      /**< Current strategy \brief Current strategy */
	OB1Controler*              control ;              /**< Link to the controler (and to the graph) \brief Link to the controler (and to the graph) */
	ShedulerAlgorithm          _shedulingAlgorithm ;  /**< type of the sheduler algorithm \brief type of the sheduler algorithm */
	int                        _totalPriority ;       /**< sum of all strategi's priority \brief sum of all strategi's priority */

 public:

	/**
	* \brief Constructor
	*/
	/**
	* Constructor
	*/
	Sheduler(OB1Controler* temp) ;

	/**
	* \brief destructor
	*/
	/**
	* Destructor
	*/
	~Sheduler();

	/**
	* \brief  create a strategy with a token and add it in the sheduler
	*/
	/**
	* create a strategy with a token and add it in the sheduler<BR>
	* Cree une strategy a partier d'un token et l'ajoute dans le sheduler
	* @param token strategy's token header
	* @param priority strategy priority
	* @param clas class of the token
	* @return Created strategy
	*/
	OB1Strategy* addStrategie(OB1Token* token, int priority, int clas) ;

	/**
	* \brief Put time for execution
	*/
	/**
	*  Put time for execution <BR>
	*	 Met le temp pour l'execution
	*  @param Time temps d'execution
	*/
	void runOppotunisticDuring(int Time) ;

	/**
	* \brief Put a new curretn problem to solve
	*/
	/**
	*  Put a new current problem to solve  <BR>
	*  Rajoute le token dans la strat�gie courrant
	*	 @param temp New strategy to solve
	*/
	void putNewCurrentProblem(OB1Strategy* temp) ;

	/**
	*  Choice next straegy to compute
	*/
	/**
	* Next Strategy to compute <BR>
	* Fonction de gestion de la crise
	* @return Curretns trategy to return
	*/
	OB1Strategy* NextStrategyToCompute() ;

	/**
	* \brief delete a strategy
	*/
	/**
	* Delete a strategy   <BR>
	* Efface une strategy
	* @param place Cursor which points on the strategy to delete
	*/
	void RemoveStrategy(std::vector<OB1Strategy* >::iterator&  place) ;

	/**
	* \clear all strategies
	*/
	void ClearAllStrategies() ;

	/**
	* \brief return index of a strategy
	*/
	/**
	* Find a strategy and return a pointer to it <BR>
	* Trouve une strategie et renvoie un curseur indiquant sa positiant  <BR>
	* Cela permet de retrouver la position d'une strategie pour l'effacer
	* @param temp Strategy to find
	* @return  Pointer to the strategy
	*/
	std::vector<OB1Strategy*>::iterator& findStrategy(OB1Strategy* temp) ;

  bool findStrategy(OB1Strategy* temp, std::vector<OB1Strategy*>::iterator& it) ;

	/**
	*  \brief get the scheduling algorithm
	*/
	/**
	* get the scheduling algorithm <BR>
	* Renvoie l'algorithme d'ordonancement
	* @return Shedulint algortihm
	*/
	ShedulerAlgorithm getAlgorithm() ;

	/**
	* \brief Put the wanted sheduling algorithm
	*/
	/**
	*  Put the wanted sheduling algorithm <BR>
	*  Choisis l'agorithme de sheduling
	*  @param temp Algoritm to apply for sheduling
	*/
	void putAlgoritm(ShedulerAlgorithm temp) ;

	/**
	* \brief get the current strategy
	*/
	/**
	*  get the current strategy   <BR>
	*  renvoie la strategy courrante
	*  @return curretn strategy
	*/
	OB1Strategy* GetCurrentStrategy() ;

	/**
	* \brief Reinit the controler
	*/
	/**
	* Clear all the strategy and add the opportunistic strategy <BR>
	* Efface toutes les strategies et rajoute la strategi opportuniste
	*/
	void ReInit() ;

	/**
	* \brief Delete all strategy that must be deleted
	*/
	/**
	* Delete all strategy that must be deleted
	* Efface toutes les strategies qui doivent �tre effac�s
	*/
	void GarbageCollecting() ;

  OB1Strategy* getStrategyForToken(OB1Token* pToken) ;

  OB1Token*    getTokenFromId(long int iTokId) ;

 protected:

	/**
	* \brief Init the path of a strategy
	*/
	/**
	*  Return sum of all strategi's priority  <BR>
	*  REnvoie la somme des priorit�s de toutes les strat�gies
	* @return sum of all strategi's priority
	*/
	int getTotalOfPriority() ;

	/**
	* \brief Init the path of a strategy
	*/
	/**
	* Init the path of a strategy <BR>
	* Remplit la strategy a partir du noeud de base
	* @param temp strategy to fill
	*/
	void createStrategyPath(OB1Strategy* temp) ;
};

#endif  /* fin du sheduler */
