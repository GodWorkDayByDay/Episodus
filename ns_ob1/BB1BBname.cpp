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
#include <stdio.h>      // for GenerateName(...)

#ifndef FOR_WINDOWS
#include "BB1BB.h"
#else
#include "ns_ob1\BB1BB.h"
#endif

// -----------------------------------------------------------------------------
// Return a copy of a unique name whose prefix is "Event-" and whose suffix is a
// serial enumerator.
// -----------------------------------------------------------------------------

string
BB1BB::GenerateEventName()
{
#ifdef _DEBUG_
  _trout << "-- DEBUG:: BB1BB::GenerateEventName()\n\n" ;
#endif

  return (GenerateName(EventPrefix, ++_eventCount)) ; // EventPrefix: global const BB1String
}



// -----------------------------------------------------------------------------
// Return a unique name whose prefix is "KSAR-" and whose suffix is a serial
// enumerator.
// -----------------------------------------------------------------------------

#ifndef __TCONTROLER__
string	BB1BB::GenerateKSARName()
{

#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::GenerateKSARName()\n\n" ;
#endif

  return (GenerateName(KSARPrefix, ++BB1BBKSARCount)) ; // KSARPrefix: global const BB1String
}
#endif



// -----------------------------------------------------------------------------
// Return a unique name whose prefix is "MESSAGE-" and whose suffix is a serial
// enumerator.
// -----------------------------------------------------------------------------

string	BB1BB::GenerateMessageName()
{
#ifdef _DEBUG_
  _trout << "-- DEBUG:: BB1BB::GenerateMessageName()\n\n" ;
#endif

  return (GenerateName(MessagePrefix, ++_messageCount)) ; // MessagePrefix: global const BB1String
}


// -----------------------------------------------------------------------------
// Construct and return a BB1String of the form <prefix>-<count>, where <prefix>
// is a BB1String and <count> is an integer.
// -----------------------------------------------------------------------------

string	GenerateName(const string& prefix, const int count)
{
  char	countStr[7] ;
  // sprintf() may return char * or int
  (void) sprintf(countStr, "%d", count) ;

  return (prefix + string(countStr)) ;
}
