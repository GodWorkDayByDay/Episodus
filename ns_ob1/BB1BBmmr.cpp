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

#ifndef FOR_WINDOWS
# include "BB1BB.h"
# include "BB1AppInst.h"   // for BB1BB::NewAppInst(...)
# include "BB1Class.h"     // for BB1BB::NewAppInst(...)
# include "BB1KB.h"        // for BB1BB::CheckDirectSuperclasses(...)
# include "BB1Exception.h"    // add fab
#else
# include "ns_ob1\BB1BB.h"
# include "ns_ob1\BB1AppInst.h"   // for BB1BB::NewAppInst(...)
# include "ns_ob1\BB1Class.h"     // for BB1BB::NewAppInst(...)
# include "ns_ob1\BB1KB.h"        // for BB1BB::CheckDirectSuperclasses(...)
# include "ns_ob1\BB1Exception.h"    // add fab
# include "ns_ob1\BB1types.h"
#endif

// Make, Modify, Remove

// -----------------------------------------------------------------------------
// Auxiliary to BB1Class:MakeInstance(...). Not a member function. Instantiate
// the class and create an "Exemplifies" link to the class object.
// -----------------------------------------------------------------------------

BB1AppInst *MakeAppInst(BB1Class& c, const string sName, AttValPair& dispatch, BB1KB& kb, /*const*/ AVPSet *pAttSpec, const LinkSet *pLinkSpec, bool bCreateEvent, bool bCreateStrat)
{
  BB1BB& bb = c.BB() ;
  try
  {
    if (bb.CreatePhaseCheck("BB1BB::MakeInstance(...)"))
    {
      // might throw
      return bb.NewAppInst(sName, dispatch , kb, c, pAttSpec, pLinkSpec, (bb.Phase() != INITIALIZATION), bCreateEvent, bCreateStrat) ;
    }
  } // end try
  catch (CreatePhaseError& cpe)
    { return((BB1AppInst *) NULL) ; }
  catch (UnknownPhase& up)
    { } // constructor aborts

  return (BB1AppInst *) 0 ;
};

// -----------------------------------------------------------------------------
// Auxiliary to ::ModifyObject(...). Split off from ModifyObject to track down a
// bug.
// -----------------------------------------------------------------------------

void
BB1Object::CreateToken(const EventType et, const AVPSet *attSpec, const LinkSet *linkSpec, const AVPSet *delAttSpec, const LinkSet *delLinkSpec,bool createStrat)
{
	AVPSet chAtt ;
  if (attSpec)
    chAtt |= *attSpec ;
  if (delAttSpec)
    chAtt |= *delAttSpec ;

  LinkSet	chLink ;
  if (linkSpec)
    chLink |= *linkSpec ;
  if (delLinkSpec)
    chLink |= *delLinkSpec ;

  BB().CreateToken(et, *this, &chAtt, &chLink, createStrat) ;
}

Errcode		ModifyObject(	BB1Object&		object,
												const AVPSet	*attSpec,
												const LinkSet	*linkSpec,
												const AVPSet	*delAttSpec,
												const LinkSet	*delLinkSpec,
												const int			eventP,
                        bool createEve)
{
  try
  {
    BB1BB& bb = object.BB() ;                              // retrieve the blackboard
    const BB1KB& kb = object.KB() ;                        // retrieve the knowledge base
    if (bb.CreatePhaseCheck("BB1Object::Modify(...)"))
    {
      // might throw
      if (kb.ProtectedP())
      {
				// taboo!
				ProtectedKB pkb(bb, "BB1Object::Modify(...)", kb.Name()) ; // throw pkb;
      }
      else
      {
				// Perform the modifications
				if (object.ProcessAttributes(attSpec, delAttSpec) == SUCCESS)
				{
					if (object.ProcessLinksNN(linkSpec, delLinkSpec) == SUCCESS)
					{
						// If specified, create an event object
						if (eventP)
						{
              if (createEve)
                object.CreateToken(MODIFY, attSpec, linkSpec, delAttSpec, delLinkSpec, true) ;
						}
						return (SUCCESS) ;
					}
					else
						return (INVALIDLINK) ;
				}
				else
					return (INVALIDATTRIBUTE) ;
			}
		}     
	} // end try
	catch (CreatePhaseError& cpe)
		{ return (BADPHASE) ; }
	catch (UnknownPhase& up)
		{ } // constructor aborts
	catch (ProtectedKB& pkb)
		{ return (PROTECTEDKB) ; }

	return (FAILURE) ;
}

BB1AppInst*
BB1BB::NewAppInst(const string      sObjName,
                  AttValPair&       dispatch,
                  BB1KB&				    kb,
                  BB1Class&			    c,
                  /*const*/ AVPSet* pAttSpec,
                  const LinkSet*    pLinkSpec,
                  const int			   /* eventP */,
                  bool              bCreateTok,
                  bool              bCreateStrat)
{
try
{
  BB1AppInst *appInst = (BB1AppInst *) 0 ;
  if (kb.ProtectedP())
    // throw pkb;
    ProtectedKB pkb(kb.BB(), "BB1Class::MakeInstance(...)", kb.Name()) ;
  else if (kb.ObjectNamed(sObjName))
  {
    // throw aiae;
    AppInstAlreadyExists aiae(kb.BB(), "BB1Class::MakeInstance(...)", kb.Name() + "." + sObjName) ;
    return (BB1AppInst *) 0 ;
  }
  else
  {
    // Allocate and initialize the object.  The constructor installs it in the KB.
    // Memory freed in BB1KB::~BB1KB
    appInst = new BB1AppInst(sObjName, dispatch, kb, &c, pAttSpec, pLinkSpec) ;
    if (appInst)
    {
      if (bCreateTok)
        CreateToken(ADD, *appInst, NULL, NULL, bCreateStrat) ;
      else
        { } // There may be no event
    }
    else
    {
      // throw cf;
      ConstructFailure cf(*this, "BB1BB::NewAppInst(...)", "BB1AppInst") ;
      return (BB1AppInst *) 0 ;
    }
  }
  return (appInst) ;
}
catch (ProtectedKB& pkb)
{
  return (BB1AppInst*) 0 ;
}
catch (AppInstAlreadyExists& aiae)
{
  return (BB1AppInst* ) 0 ;
}
catch (ConstructFailure& cf)
{ } // constructor aborts

  return  (BB1AppInst*) 0 ;
}




