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

#include "ns_ob1\OB1Token.h"
#include "ns_ob1\BB1Object.h"
#include "ns_ob1\BB1Class.h"
#include "ns_ob1\BB1Link.h"
#include "ns_ob1\OB1Node.h"
#include "ns_ob1\OB1Controler.h"
#include "ns_ob1\BB1KB.h"

long OB1Token::_lTokenCount = 0 ;

OB1Token::OB1Token()
{
  _lTokenCount++ ;

  _type              = ADD ;
  _pObject           = NULL ;
  _pAttributesChange = (AVPSet *)   0 ;
  _pLinkChange       = (LinkSet *)  0 ;
  _pWhere_I_am       = NULL ;
  _pLauncherToken    = NULL ;
  _iTokenState       = tokenFree ;
  _interfaceOpened   = false ;
  _hInterfaceHandle  = 0 ;
  _class             = -42 ; /* not assigned */

  incNumero() ;
}

OB1Token::OB1Token(EventType /* type */, BB1Object* pTr)
{
  _lTokenCount++ ;

  _type              = ADD ;
  _pObject           = pTr ;
  _pAttributesChange = (AVPSet *)   0 ;
  _pLinkChange       = (LinkSet *)  0 ;
  _pWhere_I_am       = (OB1Node *)  0 ;
  _pLauncherToken    = (OB1Token *) 0 ;
  _iTokenState       = tokenFree ;
  _interfaceOpened   = false ;
  _hInterfaceHandle  = 0 ;
  _class             = -42 ; /* not assigned */

  incNumero() ;
}

OB1Token::OB1Token(EventType /* type */, BB1Object* pTr, AVPSet* Change, LinkSet*  chan)
{
  _lTokenCount++ ;

  _type              = ADD ;
  _pObject           = pTr ;
  _pLinkChange       = chan ;
  _pAttributesChange = Change ;
  _pWhere_I_am       = (OB1Node *)  0 ;
  _pLauncherToken    = (OB1Token *) 0 ;
  _iTokenState       = tokenFree ;
  _interfaceOpened   = false ;
  _hInterfaceHandle  = 0 ;
  _class             = -42 ; /* not assigned */

  incNumero() ;
}

OB1Token::OB1Token(const OB1Token& tok)
{
  _lTokenCount++ ;

  _type            = tok._type ;
  _pObject         = tok._pObject ;

	if (NULL == tok._pLinkChange)
  	_pLinkChange = (LinkSet*) 0 ;
  else
  	_pLinkChange = new LinkSet(*(tok._pLinkChange)) ;

	if (NULL == tok._pAttributesChange)
  	_pAttributesChange = (AVPSet *) 0 ;
  else
  	_pAttributesChange = new AVPSet(*(tok._pAttributesChange)) ;

  _pWhere_I_am      = tok._pWhere_I_am ;
  _pLauncherToken   = tok._pLauncherToken ;
  _iTokenState      = tok._iTokenState ;
  _interfaceOpened  = tok._interfaceOpened ;
  _hInterfaceHandle = tok._hInterfaceHandle ;
  _class            = tok._class ;

  incNumero() ;
}

OB1Token::~OB1Token()
{
  if (_pWhere_I_am)
    _pWhere_I_am->removeToken(this) ;

  if (_pAttributesChange)
    delete (_pAttributesChange) ;
  if (_pLinkChange)
    delete (_pLinkChange) ;

  _lTokenCount-- ;
}

EventType
OB1Token::getEventType()
{
  return _type ;
}

AVPSet*
OB1Token::getAttributesChange()
{
  return _pAttributesChange ;
}

LinkSet*
OB1Token::getChangeLinks()
{
  return _pLinkChange ;
}

/*
** Return -42 if it not exist
** else return the number of the class
*/

int
OB1Token::Class()
{
  return _class ;
}

void
OB1Token::PutStorageNode(OB1Node* input)
{
	_pWhere_I_am = input ;
	if (_pObject && input && input->Controler())
  {
    std::string clasName = _pObject->Class()->Name() ;
    _class = input->Controler()->getClassName(clasName) ;
  }
}

Cycle
OB1Token::getCreatedCycle()
{
  return _pObject->CycleCreated() ;
}

BB1Object*
OB1Token::getStatusObject()
{
	if (NULL == _pObject)
		return (BB1Object*) 0 ;

	string sObjectKbName = _pObject->KB().Name() ;

  if (string("QuestionKB") == sObjectKbName)
		return getAnswerObject() ;

  if (string("InformationKB") == sObjectKbName)
  	return _pObject ;

	if (string("NautilusEventKB") == sObjectKbName)
  	return _pObject ;

	return (BB1Object*) 0 ;
}

BB1Object*
OB1Token::getAnswerObject()
{
	if (NULL == _pObject)
		return (BB1Object*) 0 ;

	TypedVal* pDispinf = _pObject->PathAttributes() ;
  if (NULL == pDispinf)
  	return (BB1Object*) 0 ;

  return _pObject->BB().searchAnswerInKB(*pDispinf, _pObject->SearchParams()) ;
}

bool
OB1Token::bIsValidInterface()
{
	if (0 == _hInterfaceHandle)
		return false ;

	return ::IsWindow(_hInterfaceHandle) ;
}

OB1Token&
OB1Token::operator=(const OB1Token& src)
{
	if (this == &src)
		return *this ;

  _type    = src._type ;
  _pObject = src._pObject ;

	if (_pLinkChange)
		delete _pLinkChange ;

	if (NULL == src._pLinkChange)
  	_pLinkChange = (LinkSet*) 0 ;
  else
  	_pLinkChange = new LinkSet(*(src._pLinkChange)) ;

	if (_pAttributesChange)
		delete _pAttributesChange ;

	if (NULL == src._pAttributesChange)
  	_pAttributesChange = (AVPSet*) 0 ;
  else
  	_pAttributesChange = new AVPSet(*(src._pAttributesChange)) ;

  _pWhere_I_am      = src._pWhere_I_am ;
  _pLauncherToken   = src._pLauncherToken ;
  _iTokenState      = src._iTokenState ;
  _interfaceOpened  = src._interfaceOpened ;
  _hInterfaceHandle = src._hInterfaceHandle ;
  _class            = src._class ;

  incNumero() ;

	return *this ;
}

