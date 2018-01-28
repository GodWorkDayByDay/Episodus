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
#include "ns_ob1\BB1Object.h"
#include "ns_ob1\BB1Ks.h"
#include "ns_ob1\OB1Token.h"
#include "ns_ob1\OB1Node.h"
#include "ns_ob1\OB1Heuristix.h"
#include "ns_ob1\OB1Strategy.h"

HeuristixGenerator::HeuristixGenerator(OB1Controler* control)
                   :_createStrategy(control)
{
  _controler = control ;
}

OB1Controler*
HeuristixGenerator::Controler()
{
  return _controler ;
}

HeuristixGenerator::~HeuristixGenerator()
{
}

Heuristix*
HeuristixGenerator::getHeuristix()
{
  return &_createStrategy ;
}

DFSHeuristix::DFSHeuristix(OB1Controler* control)
             :Heuristix(control)
{
}

OB1Node*
DFSHeuristix::NextNode(std::vector<OB1Node*>& explore, OB1Strategy* pRootStrat)
{
	if (explore.empty())
		return (OB1Node*) 0 ;

	sortPossibleNodes(explore, pRootStrat) ;

  return chooseBestNode(explore, pRootStrat) ;

  // Ancien algo :)
  // if (explore.size() > 0)
  //  return (explore[0]);
}

// eliminates nodes from already tried KSs
//
void
DFSHeuristix::sortPossibleNodes(std::vector<OB1Node* >& explore, OB1Strategy* pRootStrat)
{
	OB1Token* pToken = pRootStrat->Token() ;
  if (NULL == pToken)
  	return ;

	BB1Object* pAnswer = pToken->getStatusObject() ;
  if (NULL == pAnswer)
  	return ;

  AnswerStatus* pAnswerStatus = pAnswer->Value("answerStatus", NULLLANSWERSTATUS) ;
  if (NULL == pAnswerStatus)
		return ;

	std::vector<OB1Node*>::iterator nodesIter = explore.begin() ;
  for ( ; explore.end() != nodesIter ; )
	{
  	bool bKeepIt = false ;

    OB1NKS* pKsNode = (OB1NKS*) 0 ;

    OB1Node* pTheNode = *nodesIter ;

    // Processing intermediate NAnd node
    //
    OB1NAnd* pNand = dynamic_cast<OB1NAnd*>(pTheNode) ;
    if (pNand)
    {
      std::vector<OB1NodeLink*>* pParents = &(pNand->getParent()) ;
      pTheNode = (*pParents)[0]->Node() ;
    }

  	// First step, we only accept OB1NResult or OB1NTrigger nodes
    //
    OB1NResult* pResult = dynamic_cast<OB1NResult*>(pTheNode) ;
    if (pResult)
    	pKsNode = pResult->KS() ;
    else
    {
    	OB1NTrigger* pTrigger = dynamic_cast<OB1NTrigger*>(pTheNode) ;
    	if (pTrigger)
      	pKsNode = pTrigger->KS() ;
    }


		// Second step, we check if this KS has already been tried during the
    // current cycle
    //
    if (pKsNode)
    {
    	std::string sKsName = pKsNode->getKSName() ;
      KSAttemptHistoryElement* pHistoElement = pAnswerStatus->getHistoryElement(sKsName) ;
      if (NULL == pHistoElement)
      	bKeepIt = true ;
    }

    if (bKeepIt)
    	nodesIter++ ;
    else
    	explore.erase(nodesIter) ;
  }
}

OB1Node*
DFSHeuristix::chooseBestNode(std::vector<OB1Node* >& explore, OB1Strategy* /* pRootStrat */)
{
	if (explore.empty())
		return (OB1Node*) 0 ;

	OB1Node* pBestCandidate   = (OB1Node*) 0 ;
  int      iCurrentPriority = 0 ;

  std::vector<OB1Node*>::iterator nodesIter = explore.begin() ;
  for ( ; explore.end() != nodesIter ; nodesIter++)
	{
		OB1NKS* pKsNode = (OB1NKS*) 0 ;

    OB1Node* pTheNode = *nodesIter ;

    // Processing intermediate NAnd node
    //
    OB1NAnd* pNand = dynamic_cast<OB1NAnd*>(pTheNode) ;
    if (pNand)
    {
      std::vector<OB1NodeLink*>* pParents = &(pNand->getParent()) ;
      pTheNode = (*pParents)[0]->Node() ;
    }

  	// First step, we only accept OB1NResult or OB1NTrigger nodes
    //
    OB1NResult* pResult = dynamic_cast<OB1NResult*>(pTheNode) ;
    if (pResult)
    	pKsNode = pResult->KS() ;
    else
    {
    	OB1NTrigger* pTrigger = dynamic_cast<OB1NTrigger*>(pTheNode) ;
    	if (pTrigger)
      	pKsNode = pTrigger->KS() ;
    }

    if (pKsNode)
    {
    	BB1KS* pCurrentKs = pKsNode->getKS() ;

      if (pCurrentKs)
      {
      	int iKsPriority = pCurrentKs->getPriority() ;

        if ((NULL == pBestCandidate) || (iKsPriority > iCurrentPriority))
        {
        	pBestCandidate   = *nodesIter ;
          iCurrentPriority = iKsPriority ;
				}
      }
    }
  }

  return pBestCandidate ;
}

