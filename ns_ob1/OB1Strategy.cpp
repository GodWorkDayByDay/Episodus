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
#include "ns_ob1\OB1Strategy.h"
#include "ns_ob1\OB1Controler.h"
#include "ns_ob1\BB1BB.h"
#include "ns_ob1\OB1Token.h"

OB1Strategy::OB1Strategy(OB1Controler* pCtrler, std::string id, int pass_clas) : OB1SubStrategy(pCtrler, this, NULL, -42,pass_clas)
{
  _controlers   = pCtrler ;

  id            = id ;
  _node         = NULL ;
  _count        = 0 ;
  _last         = -1 ;
  _priority     = 0 ;
  _StratType    = DETERMINISTIC ;
  _isAnswer     = IN_EXECUTION ;
  _delete       = false ;
  _lastStrategy = NULL ;
}

OB1Strategy::OB1Strategy(OB1Controler* pCtrler, std::string id, int clas, TStrategyType temp, int prior)
            :OB1SubStrategy(pCtrler, this, NULL, -42 ,clas)
{
	_controlers   = pCtrler ;

  _id           = id ;
  _node         = NULL ;
  _count        = 0 ;
  _last         = -1 ;
  _priority     = prior ;
  _StratType    = temp ;
  _isAnswer     = IN_EXECUTION ;
  _delete       = false ;
  _lastStrategy = NULL ;
}

OB1Strategy::OB1Strategy(OB1Controler* pCtrler, std::string id, int clas, int priority, Cycle begin_cycle)
            :OB1SubStrategy(pCtrler, this, NULL, 0, clas)
{
	_controlers   = pCtrler ;

  _id           = id ;
  _node         = NULL ;
  _count        = 0 ;
  _last         = -1 ;
  _isAnswer     = IN_EXECUTION ;
  _priority     = priority ;
  _beginCycle   = begin_cycle ;
  _StratType    = DETERMINISTIC ;
  _delete       = false ;
  _lastStrategy = NULL ;
}

OB1Strategy::OB1Strategy(OB1Controler* pCtrler, std::string id, int /* clas */, OB1Token *head, int priority, Cycle begin_cycle)
            :OB1SubStrategy(pCtrler, this, NULL, 0, head->Class())
{
	_controlers   = pCtrler ;

  _id           = id ;
  _run          = head ;
  _priority     = priority ;
  _beginCycle   = begin_cycle ;
  _count        = 0 ;
  _last         = -1 ;
  _StratType    = DETERMINISTIC ;
  _isAnswer     = IN_EXECUTION ;
  _delete       = false ;
  _lastStrategy = this ;
}

void
OB1SubStrategy::putComputationState(StrategyState i)
{
  _isAnswer = i ;
}

StrategyState
OB1SubStrategy::getStrategyState()
{
  return (_isAnswer) ;
}

OB1Strategy::~OB1Strategy()
{
 /// if (NULL != _StratPath)
   // delete(_StratPath);
}

/*
** retourne la priorit� de la question
*/
int
OB1Strategy::Priority()
{
  return _priority ;
}

/*
** Nous indique a quel cycle a �t� cr�e la strat�gie
*/
Cycle
OB1Strategy::getBeginCycle()
{
  return _beginCycle ;
}

/*
** Nous inqique le nombre de cycle pass� depuis la derniere execution
*/
int
OB1Strategy::getLastExecution()
{
  return _last ;
}

/*
** Incremente les conteurs, signifie q'un tour est pass�
*/
void
OB1Strategy::inc()
{
  _last++ ;
}

int
OB1Strategy::getCountCycle()
{
  return _count ;
}

/*----------------------------- Sub Strategy ---------------------------------*/
/* FIXME */

bool
OB1SubStrategy::hasAnswer()
{
  return false ;
}

// FIXME OB1Strategy
//OB1SubStrategy::OB1SubStrategy(OB1SubStrategy* root,OB1SubStrategy* father, int wanted_clas, int pass_class)
OB1SubStrategy::OB1SubStrategy(OB1Controler* pCtrler, OB1Strategy* root, OB1SubStrategy* father, int wanted_clas, int pass_class)
{
	_controlers   = pCtrler ;

  _root         = root ;
  _father       = father ;
  _run          = (OB1Token *) 0 ;
  _node         = (OB1Node *) 0 ;
  _wanted_class = wanted_clas ;
  _pass_class   = pass_class ;
	_isAnswer     = IN_EXECUTION ;
}

OB1SubStrategy::~OB1SubStrategy()
{
}

int
OB1SubStrategy::Class()
{
  //if (NULL != _run)
    //return   _run->Class();
  return _pass_class ;
}

OB1Strategy*
OB1SubStrategy::Root()
{
	return _root ;
}

void
OB1SubStrategy::RemoveLastSonStrategy()
{
	if (_subStrategy.empty())
  	return ;

  NTArray<OB1SubStrategy>::reverse_iterator itReverse ;
	itReverse = _subStrategy.rbegin() ;
  // delete *itReverse ;
  //if (_controlers)
	//	_controlers->BB()->addToSubStratGarbage(*itReverse) ;
  _subStrategy.pop_back() ;

  if (_subStrategy.empty())
		_root->putLastSubStrategy(NULL) ;

  //itReverse = _subStrategy.rbegin() ;
  //_root->putLastSubStrategy(*itReverse) ;
}

void
OB1SubStrategy::SkipToNextNode()
{
	if (NULL == _father)
		return ;

	_father->RemoveLastSonStrategy() ;
}

bool
OB1SubStrategy::HasWantedClass()
{
	if ((NULL == _node) || (_node->getType() != OTHER_NODE))
		return false ;

	OB1Token* temp = _node->getLastToken(_wanted_class) ;
	if (temp)
		return true ;

	return false ;
}

void
OB1SubStrategy::WantedClass(int clas)
{
  _wanted_class = clas ;
}

// std::vector<OB1SubStrategy* >&  OB1SubStrategy::getSubStrategy()
NTArray<OB1SubStrategy>&
OB1SubStrategy::getSubStrategy()
{
  return _subStrategy ;
}

OB1SubStrategy::OB1SubStrategy(OB1SubStrategy& temp)
{
	_controlers   = temp._controlers ;
  _run          = temp._run ;
  _node         = temp._node ;
  _root         = temp._root ;
  _father       = temp._father ;
  _subStrategy  = temp._subStrategy ;
  _isAnswer     = temp._isAnswer ;
	_wanted_class = temp._wanted_class ;
  _pass_class   = temp._pass_class ;
}

void
OB1SubStrategy::putNode(OB1Node* temp)
{
	_node = temp ;
}

OB1Node*
OB1SubStrategy::Node()
{
  return _node ;
}

void
OB1SubStrategy::AddSubStrategy(OB1SubStrategy* temp)
{
  _subStrategy.push_back(temp) ;
  ((OB1Strategy*)_root)->putLastSubStrategy(temp) ;
}

OB1Token*
OB1SubStrategy::Token()
{
  return _run ;
}

void
OB1SubStrategy::putToken(OB1Token* tok)
{
  _run = tok ;
}

OB1NKS*
OB1SubStrategy::getKSNode()
{
  OB1NKS* pKSNode = dynamic_cast<OB1NKS*>(_node) ;
	if (pKSNode)
  	return pKSNode ;

	if (false == _subStrategy.empty())
	{
  	NTArray<OB1SubStrategy>::iterator itStrat = _subStrategy.begin() ;
    for ( ; _subStrategy.end() != itStrat ; itStrat++)
    {
    	pKSNode = (*itStrat)->getKSNode() ;
      if (pKSNode)
  			return pKSNode ;
    }
  }

	return (OB1NKS *) 0 ;
}

string
OB1SubStrategy::describe()
{
  OB1NKS* pKSNode = getKSNode() ;
  if (pKSNode)
    return pKSNode->getKSName() ;

  return _node->getString() ;
}

