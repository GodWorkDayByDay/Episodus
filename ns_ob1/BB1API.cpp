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

#include <iostream>      // for BB1BB::BB1BB(...)
#include <string>        // for BB1BB::Send(...)

#ifndef FOR_WINDOWS

#include "AttValPair.h"    // for BB1BB::~BB1BB()
#include "BB1BB.h"
#include "BB1KB.h"         // for BB1BB::BB1BB(...)
#include "BB1KSKB.h"       // for BB1BB::BB1BB(...)
#include "ClassKB.h"       // for BB1BB::BB1BB(...)
#include "BB1Exception.h"    // add fab

#else

#include "ns_ob1/AttValPair.h"    // for BB1BB::~BB1BB()
#include "ns_ob1/BB1BB.h"
#include "ns_ob1/BB1KB.h"         // for BB1BB::BB1BB(...)
#include "ns_ob1/BB1KSKB.h"       // for BB1BB::BB1BB(...)
#include "ns_ob1/ClassKB.h"       // for BB1BB::BB1BB(...)
#include "ns_ob1/BB1Exception.h"    // add fab
#include "ns_ob1/OB1Token.h"
#include "ns_ob1/OB1Controler.h"
#include "ns_ob1/NSKS.h"

  #ifdef _ENTERPRISE_DLL
    # include <owl/applicat.h>
    #include "enterpriseLus\superLus.h"
  #else
    #include "nsepisod/nsToDo.h"
    #include "nautilus\nssuper.h"
  #endif

#endif

// from /a/bb1/ipc/io.h
//extern Controler* _globalControler;

/*
#ifdef __IPC__
extern "C"
{
  char 	*get_unique_id() ;
  int 	gethostname(char *name, int namelen) ;
  int 	net_connect(const char	*contact_name,
										char				*hostname,
										char				*unique_id,
										int					connect_block,
										int					comm_block,
										int					nohang) ;
	int 	send_buf(int sock, char *buf) ;
}
#endif     */

// -----------------------------------------------------------------------------
//  This file contains the Application Programmer's Interface methods. The
//  non-exported methods are defined in "BB1BB.c".
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//  Construct a blackboard. It may be a restriction that the initialization
//  function take no arguments. This is not part of the API.
// -----------------------------------------------------------------------------

BB1BB::BB1BB(	NSContexte*                 pCtx,
							const InitFunctionT         initFn,
							const TerminationConditionT terminationCond,
							int                         /* argc */,
							char**                      /* argv */)
      :_initFunction(initFn),
      _terminationCondition(terminationCond),
      _BB1BBphase(INITIALIZATION),
      _cycle(PRECYCLE),
      _eventCount(0),
      _messageCount(0),
      _triggerEvent((BB1Event *) NULL),
      _traceCycle(false),
      _traceEvent(false),
      _traceKSAR(false),
      _traceMessage(false),
      _errorAction(ABORT_ANY),
      _errorNotify(WARN),
      _errorHandler(DefaultErrorHandler),
      _trout(cout),
      _cycles2add(0),
      NSRoot(pCtx),
      _kenoby(this)
{
  OB1Token::_token_counter = 1 ; // start with 1 since 0 means "no token"

  _nbObject = 0 ;
  //_globalControler =  &_controler;
	_classKB = DefineKB("Class") ;
  _cycle   = 0 ;

  loadClassKB(*this) ;
  _classKB->SetProtected(true) ;

  DefineRelation("Implements", "ImplementedBy", "Decision", "Strategy") ;

	// ---------------------------------------------------------------------------
	// Built-in classes
	// Control-plan stuff
	// Communication interface stuff
	// ---------------------------------------------------------------------------
}

BB1BB::BB1BB(const BB1BB& bb)
      :_initFunction(bb._initFunction),
       _terminationCondition(bb._terminationCondition),
       _BB1BBphase(bb._BB1BBphase),
       _cycle(bb._cycle),
       _eventCount(bb._eventCount),
       _messageCount(bb._messageCount),
       _triggerEvent(bb._triggerEvent),
       _traceCycle(bb._traceCycle),
       _traceEvent(bb._traceEvent),
       _traceKSAR(bb._traceKSAR),
       _traceMessage(bb._traceMessage),
       _errorAction(bb._errorAction),
       _errorNotify(bb._errorNotify),
       _errorHandler(bb._errorHandler),
       _trout(bb._trout),
       _cycles2add(bb._cycles2add),
       NSRoot(bb.pContexte),
       _kenoby(this),
       _kbs(bb._kbs),
       _Akss(bb._Akss)
{
  OB1Token::_token_counter = 0 ; // start with 1 since 0 means "no token"

	_ks						= bb._ks ;
  _cycle = 0 ;

	_BB1BBphase		= bb._BB1BBphase ;
  /*#ifndef __TCONTROLER__
	kss						= new KSSet(*(bb.kss)) ;
  #endif  */
	_linkPairs		= bb._linkPairs ;
	_classKB			= bb._classKB ;

  if (false == bb._nskss.empty())
	  for (vector<NSKS *>::const_iterator iter = bb._nskss.begin() ; iter != bb._nskss.end() ; iter++)
		  _nskss.push_back(new NSKS(**iter)) ;
}

// -----------------------------------------------------------------------------
// Destroy a blackboard. This is not part of the API.
// -----------------------------------------------------------------------------
BB1BB::~BB1BB()
{
  // _controler.ConstructNetWork();

	// Delete KB instances. The destructor will delete the objects
  //
	if (false == _kbs.empty())
	{
    KBIter cp = NULL ;

		for (KBIter p = _kbs.begin() ; _kbs.end() != p ; )
		{
			if ((*p)->Name() == "Class")
			{
				// Save to delete Class KB last
				cp = p ;
				p++ ;
			}
			else
			{
        delete (*p) ;
				_kbs.erase(p) ;
			}
		}

		// Delete the Class KB
    if (cp)
    {
		  delete (*cp) ;
		  _kbs.erase(cp) ;
    }
	}

	// Delete the interned function pointers
	ClearLinkPairs() ;

/*	for (vector<NSKS *>::iterator iter = nskss->begin() ; iter != nskss->end() ; )
	{
		//delete (*iter) ;
		//nskss->erase(iter) ;
	}  */
 //	delete nskss ;
}

void
BB1BB::createConcern(NSConcernToDoInformation *pConcernInfo)
{
  if (NULL == pConcernInfo)
    return ;

  NSToDoTask* pTask = new NSToDoTask ;

  pTask->setWhatToDo(string("NewPreoccupProposal")) ;
  pTask->setPointer1((void*) pConcernInfo, true) ;

  pTask->sendMe(pContexte->getSuperviseur()) ;
}

void
BB1BB::sendMessage(string sText, string sUrl, NsStripe::STRIPETYPE iStripeType)
{
  NSToDoTask* pTask = new NSToDoTask ;

  pTask->setParam1(sText) ;
  pTask->setParam2(sUrl) ;

  if      (NsStripe::isAlert   == iStripeType)
    pTask->setWhatToDo(string("DisplayAlert")) ;
  else if (NsStripe::isWarning == iStripeType)
    pTask->setWhatToDo(string("DisplayWarning")) ;
  else
    pTask->setWhatToDo(string("DisplayMessage")) ;

  pTask->sendMe(pContexte->getSuperviseur()) ;
}

