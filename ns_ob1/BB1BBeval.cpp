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
# include "BB1Event.h"
# include "BB1KS.h"
# include "BB1KSAR.h"
# include "BB1Exception.h"    // add fab
#else
# include "ns_ob1\BB1BB.h"
# include "ns_ob1\BB1Event.h"
# include "ns_ob1\BB1KS.h"
# include "ns_ob1\BB1KSAR.h"
# include "ns_ob1\BB1Exception.h"    // add fab
#endif


// -----------------------------------------------------------------------------
// Return TRUE if the KSAR's precondition is satisfied; otherwise return FALSE.
// -----------------------------------------------------------------------------

#ifndef __TCONTROLER__
bool		BB1BB::ExecutableP(BB1KSAR& k) const
{

#ifdef _DEBUG_
  cout << "BB1BB::ExecutableP(const BB1KSAR &)\n" ;
#endif

  // Get the precondition from the KSAR's KS
  const PreconditionT pc = k.KS().PreCondition() ;

  return (pc ? (*pc)(*this, k) : true) ;
}



// -----------------------------------------------------------------------------
// The ksar is the one scheduled for execution. Execute its action. Make sure
// that there is an action.
// -----------------------------------------------------------------------------

Errcode		BB1BB::ExecuteKSAR(BB1KSAR& k)
{

#ifdef _DEBUG_
  cout << "BB1BB::ExecuteKSAR(BB1KSAR &)\n" ;
#endif

  try
  {
    const ActionT action = k.KS().Action() ;
    if (action)
    {
      (*action)(*this, k) ;
      k.Execute() ;
      if (!agenda.ExecutableSubAgenda->empty())
				for (KSARIter ksarIter = agenda.ExecutableSubAgenda->begin() ; ksarIter != agenda.ExecutableSubAgenda->end() ; )
				{
					if (*ksarIter == &k)
					{
						agenda.ExecutableSubAgenda->erase(ksarIter) ;
					}
					else
						ksarIter++ ;
				}
      agenda.ExecutedSubAgenda->push_back(&k) ;
    }
    else
      {
        NullKSAction nksa(*this, "BB1BB::GoNCycles(...)", k.KS().Name()) ; /* throw nksa; */
      }
    return (SUCCESS) ;
  } // end try
  catch (NullKSAction& nksa)
    { return (SUCCESS) ; } // It's OK for an action to be null

  //return (SUCCESS) ;
}
#endif



#ifndef __TCONTROLER__
///
/// FIXME : a remplacer avec le controler
///
// -----------------------------------------------------------------------------
// Extract the trigger condition from the knowledge source and apply it to the
// event, returning the boolean int result. If there is no trigger condition
// print a warning message and return FALSE.
// -----------------------------------------------------------------------------

bool		BB1BB::Match(const BB1Event *event, const BB1KS *k)
{

#ifdef _DEBUG_
  cout << "BB1BB::Match(const BB1Event *, const BB1KS *)\n" ;
#endif

  TriggerConditionT tc = k->TriggerCondition() ;
  try
  {
    if (tc)
    {
      int b = (*tc)(*event) ;
      return (b) ;
    }
    else
      { NullKSTC nkstc(*this, "BB1BB::GoNCycles(...)", k->Name()) ; /* throw nkstc; */ }
  } // end try
  catch (NullKSTC& nkstc)
    { return (false) ; } // OK for a trigger condition to be null

  return (false) ;
}
#endif


#ifndef __TCONTROLER__

///
/// FIXME : a remplacer
///

// -----------------------------------------------------------------------------
// Return TRUE if the KSAR's obviation condition is satisfied; otherwise return
// FALSE.
// -----------------------------------------------------------------------------


bool		BB1BB::ObviatedP(BB1KSAR& k) const
{

#ifdef _DEBUG_
  cout << "BB1BB::ObviatedP(const BB1KSAR &) const\n" ;
#endif

  // Get the obviation condition from the KSAR's KS
  const ObviationConditionT	oc = k.KS().ObviationCondition() ;

  if (oc)
  {
    // Apply the obviation condition
    int b = (*oc)(*this, k) ;
    return (b) ;
  }
  else
    { return (false) ; } // It's OK to have a null obviation condition
}

#endif

