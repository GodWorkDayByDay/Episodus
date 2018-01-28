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
# include "BB1Event.h"     // for BB1BB::CreateKSAR(...)
# include "BB1KB.h"
# include "BB1KS.h"        // for BB1BB::CreateKSARs(...)

#ifndef __TCONTROLER_
# include "BB1KSAR.h"      // for BB1BB::CreateKSAR(...)
#endif

# include "BB1Link.h"      // for BB1BB::CreateKSAR(...)
# include "BB1Exception.h"    // add fab
#else
# include "ns_ob1\BB1BB.h"
# include "ns_ob1\BB1Event.h"     // for BB1BB::CreateKSAR(...)
# include "ns_ob1\BB1KB.h"
# include "ns_ob1\BB1KS.h"        // for BB1BB::CreateKSARs(...)



# include "ns_ob1\BB1Link.h"      // for BB1BB::CreateKSAR(...)
# include "ns_ob1\BB1Exception.h"    // add fab
#endif

class BB1Class ;
class BB1Event ;


// -----------------------------------------------------------------------------
// Create one KSAR
// -----------------------------------------------------------------------------

#ifndef __TCONTROLER__
Errcode BB1BB::CreateKSAR(BB1Event& te, BB1KS& ksr, const AVPSet *attSpec, const LinkSet *linkSpec)
{

#ifdef _DEBUG_
  cout << "BB1BB::CreateKSAR(BB1Event &, BB1KS &, const SetOfAVP &, const SetOfBB1Link &)\n" ;
#endif

  try
  {
    Errcode e = FAILURE ;
    BB1Class *c = ClassNamed("KSAR") ;
    if (c)
    {
      // Memory freed in BB1KB::~BB1KB
      BB1KSAR *ksarp = new BB1KSAR(GenerateKSARName(), *ksarKB, c, attSpec, NULL, te, ksr, ThisCycle()) ;
      if (ksarp)
      {
				// Increment the trigger event's KSAR reference count
				// Use the data member because the te and k.TriggerEvent() are const
				ksarp->triggerEvent.IncrementKSARCount(1) ;
				// The linkSpec is used to convey object-valued local variables
				if (linkSpec && !linkSpec->empty())
					for (LinkCIter l = linkSpec->begin() ; l != linkSpec->end() ; l++)
						ksarp->Set((*l)->Name(), (*l)->ToObject()) ;

				// Install KSAR in the triggered agenda
				InsertNewKSAR(ksarp) ;
				// Print trace message if enabled
				if (TraceKSARP())
					{ trout << "Creating ksar " << *ksarp << "\n" ; }
				e = SUCCESS ;
      }
      else
				{ ClassNotFound cnf(*this, "BB1BB::CreateKSAR(..)", "KSAR") ; /* throw cnf; */ }
    }
    else
      { ConstructFailure cf(*this, "BB1BB::CreateKSAR(...)", "BB1KSAR") ; /* throw cf; */ }
    return (e) ;
  } // end try
  catch (ConstructFailure& cf)
    { } // constructor aborts
  catch (ClassNotFound& cnf)
    { } // constructor aborts
  
  return (FAILURE) ;
}
#endif

void		BB1BB::DoOneContext(ObjectList *olist,
                            StringList *variables,
                            BB1KS&	/* ksr */,
                            BB1Event&	/* te */)
{

#ifdef _DEBUG_
  cout << "BB1BB::DoOneContext(ListOfBB1Object &, ListOfString &, BB1KS &, BB1Event &)\n" ;
#endif

  try
  {
    // Transfer each object to the KSAR's variable specification
    if (olist->empty() || variables->empty())
      return ;

    ObjectCIter	o = olist->begin() ;

    LinkSet	*varSpec = new LinkSet() ;

    for (StrCIter v = variables->begin() ; v != variables->end() && o != olist->end() ; v++)
    {
      BB1Link *l = new BB1Link(*v, *o, ThisCycle(), false) ;
      if (l)
      {
				varSpec->push_back(l) ;
				o++ ;
      }
      else
				{ ConstructFailure cf(*this, "BB1BB::DoOneContext(...)", "BB1Link") ; /* throw cf; */ }
    }

    #ifndef __TCONTROLER__
    /// FIXME
    // Create the KSAR
    CreateKSAR(te, ksr, NULL, varSpec) ;
    #endif

    // Deallocate the dynamic variable specification
    // ClearSetOfBB1Link(varSpec) ;
    varSpec->clear() ;
    delete varSpec ;

  } // end try
  catch (ConstructFailure& cf)
    { } // constructor aborts

}

#ifndef __TCONTROLER__
// -----------------------------------------------------------------------------
// Create all triggered KSARs and place them in the KSAR knowledge base.
// Initially, their state will be TRIGGERED and they will be on the triggered
// sub-agenda. Initially, their priority will be 0. The triggered cycle is the
// current cycle.
// -----------------------------------------------------------------------------
Errcode
BB1BB::CreateKSARs(BB1Event& te, BB1KS& ksr)
{
#ifdef _DEBUG_
  cout << "BB1BB::CreateKSARs(BB1Event &, BB1KS &)\n" ;
#endif

  const ContextGeneratorT	cg = ksr.ContextGenerator() ;
  if (cg)
  {
    BB1BB& bb = ksr.KB().BB() ;			// Context generator takes the BB as first argument
    StringList *variables = new StringList() ;		// to receive context variables
    ContextSet *contexts  = new ContextSet() ;		// to receive context values
    (*cg)(bb, variables, contexts) ;			// Execute the context generator

    // For each context, create a KSAR
    if (false == contexts->empty())
      for (ContextCIter c = contexts->begin() ; contexts->end() != c ; c++)
				DoOneContext(*c, variables, ksr, te) ;
  }
  else
  {
    CreateKSAR(te, ksr, NULL, NULL) ;
  } // Create one KSAR

  return (SUCCESS) ;
}

#endif

