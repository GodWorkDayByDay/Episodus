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
# include "BB1KSAR.h"
#else
# include "ns_ob1\BB1BB.h"
# include "ns_ob1\BB1KSAR.h"
#endif


#ifndef __TCONTROLER__
///
/// FIXME : a rempalcer avec la procedure de TCOntroler
///
// The second half of the agenda manager


Errcode		BB1BB::ManageExecutableSubAgenda(void)
{

#ifdef _DEBUG_
  cout << "BB1BB::ManageExecutableSubAgenda()\n" ;
#endif

  // Obviate first, then check to see whether still executable.
  if (!agenda.ExecutableSubAgenda->empty())
    for (KSARCIter e = agenda.ExecutableSubAgenda->begin() ; e != agenda.ExecutableSubAgenda->end() ; e++)
    {
      BB1KSAR& k = *(*e) ;
      ksar = &k; // So that PC and OC can retrieve KSAR
      if (k.ExecutableCycle() == ThisCycle())
      {
				// It was just transferred from Triggered sub-agenda on this cycle
				// Avoid redundant precondition and obviation condition checks
      }
      else
				if (ObviatedP(k))
				{
					k.Obviate() ;
					agenda.ObviatedSubAgenda->push_back(&k) ;
				}
				else
					if (!ExecutableP(k))
					{
						k.Demote() ;
						agenda.TriggeredSubAgenda->push_back(&k) ;
	  			}
      ksar = KSARptr(0);
    }

  // remove the newly-obviated elements from the triggered sub-agenda
  *(agenda.ExecutableSubAgenda) -= *(agenda.ObviatedSubAgenda) ;

  // remove the newly-nonexecutable elements from the triggered sub-agenda
  *(agenda.ExecutableSubAgenda) -= *(agenda.TriggeredSubAgenda) ;

  return (SUCCESS) ;
}

#endif


#ifndef __TCONTROLER__
///
/// FIXME : a changer par les procedure du controleur
///
// The first half of the agenda manager

Errcode		BB1BB::ManageTriggeredSubAgenda()
{

#ifdef _DEBUG_
  cout << "BB1BB::ManageTriggeredSubAgenda()\n" ;
#endif

  // Obviate first, then check to see whether executable.
  if (!agenda.TriggeredSubAgenda->empty())
    for (KSARCIter t = agenda.TriggeredSubAgenda->begin() ; t != agenda.TriggeredSubAgenda->end() ; t++)
    {
      BB1KSAR& k = *(*t) ;
      ksar = &k ; // So that PC and OC can retrieve KSAR
      if (ObviatedP(k))
      {
				k.Obviate() ;
				agenda.ObviatedSubAgenda->push_back(&k) ;
      }
      else
				if (ExecutableP(k))
				{
					k.Promote() ;
					agenda.ExecutableSubAgenda->push_back(&k) ;
				}
      ksar = KSARptr(0);
    }

  // remove the newly-obviated elements from the triggered sub-agenda
  *(agenda.TriggeredSubAgenda) -= *(agenda.ObviatedSubAgenda) ;

  // remove the newly-executable elements from the triggered sub-agenda
  *(agenda.TriggeredSubAgenda) -= *(agenda.ExecutableSubAgenda) ;

  return (SUCCESS) ;
}

#endif
