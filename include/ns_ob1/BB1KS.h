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

#ifndef _BB1KS_H
# define _BB1KS_H 1

class BB1BB ;
class BB1KB ;
class BB1KSAR ;

// D�claration des fonctor
class FunctorPublication;
class FunctorValidity;
class FunctorPrecondition;
class FunctorAction;
class FunctorObviation;

# ifdef __GNUC__
#  pragma interface
# endif

# include "BB1Object.h" // base type

/**
* \brief Represention of the Knowledge Source in the Blackboard
*/
/**
* Represention of the Knowledge Source in the Blackboard
* Repr�senation d'un KS sur le Blackboard
*/
class BB1KS  : public BB1Object
{
	friend class BB1BB ;
  friend class Controler;
	friend class KSSet ;
	friend class ObjectSet ;

 public:

  /**
  * \brief Constructor
  */
  /**
  * constructor
  * @param oname Name of the KS (Must be unique)
  * @param kb  KB were is stored the object
  * @param c Class of the object
  * @param tdef  Publication functor
  * @param tVal  Validity functor
  * @param ac  Action functor
  * @param oc  Obviation functor
  * @param attSpec Set of Attributes
  */
  BB1KS(const string&										oname,
        BB1KB&													kb,
        BB1Class												*c,
        const FunctorPublication* 			tdef,
        const FunctorValidity*         	tVal,
        const FunctorPrecondition*			pc,
        const FunctorAction*						ac,
        const FunctorObviation*				  oc,
        const AVPSet							*attSpec) ;

  /**
  * \brief Copy Constructor
  */
  /**
  * Copy constructor
  */
	BB1KS(const BB1KS& src) ;

  /**
  * \brief Destructor
  */
  /**
  * Destructor
  */
	~BB1KS() { } ;

	/**
	* Fonction retournant une condition d'abandon du KS
	*/
	inline
	const FunctorObviation*   ObviationCondition() const ;

	/**
	* Fonction retournant la fonction permttant de r�cup�rer la d�claration
	*/
	inline
	const FunctorPublication*  Publication() const ;

	/**
	* Fonction d�clenchant le functor declarant l'action
	*/
	inline
	const FunctorAction*       Action() const ;

	/**
	* Fonction retournant la validit� du contexte
	*/
	inline
	const FunctorValidity*     ValidityContext() const ;

	/**
	* Fonction retournant les pr�conditions
	*/
	inline
	const FunctorPrecondition* PreCondition() const ;

  int   getPriority() { return _iPriority ; }

	void  Save(ofstream& KBstream) ;

private:

  const FunctorPublication*  _tPublication ;  		 /**< Publication Functor \brief Publication Functor */
  const FunctorValidity*     _tValidity ;      		 /**< Validity Functor \brief Validity Functor  */
  const FunctorPrecondition* _preCondition ;    	 /**< Precondition Functor \brief Precondition Functor  */
  const FunctorAction*			 _action ;             /**< Action Functor \brief  Action Functor*/
  const FunctorObviation*		 _obviationCondition ; /**< Obviation Functor \brief Obviation Functor */

  int                        _iPriority ;
} ;

/*
** Fonction retournant une condition d'abandon du KS
*/
inline
const FunctorObviation*	BB1KS::ObviationCondition() const { return (_obviationCondition) ; }

/*
** Fonction retournant la fonction permttant de r�cup�rer la d�claration
*/
inline
const FunctorPublication*  BB1KS::Publication() const { return (_tPublication); }

/*
** Fonction d�clenchant le functor declarant l'action
*/
inline
const FunctorAction*	 BB1KS::Action() const { return (_action) ; }

/*
** Fonction retournant la validit� du contexte
*/
inline
const FunctorValidity*   BB1KS::ValidityContext() const { return (_tValidity); }

/*
** Fonction retournant les pr�conditions
*/
inline
const FunctorPrecondition*	 BB1KS::PreCondition() const { return (_preCondition) ; }

typedef BB1KS* KSptr ;

class AKS
{
 public:

	AKS(BB1KS *dpioKS, APConditionT dpioAPCond) ;
	AKS(const AKS& src) ;
	~AKS() ;

	AKS&					operator=(const AKS& src) ;

	BB1KS					*ks ;
	APConditionT	apCondition ;
} ;

#endif // _BB1KS_h

