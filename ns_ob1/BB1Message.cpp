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

#ifdef __GNUC__
# pragma implementation
#endif

#include <iostream.h>   // for operator<<(...)

#ifndef FOR_WINDOWS
# include "BB1Message.h"
#else
# include "ns_ob1\BB1Message.h"
#endif


#ifdef __TCONTROLER__
BB1Message::BB1Message(const string&	oname,
           AttValPair&   dispatch,
		       BB1KB&		kb,
		       BB1Class		*c,
		       const AVPSet	*attSpec,
		       const LinkSet	*linkSpec)
  : BB1Object(oname,dispatch, kb, c)
{
  ProcessAttributes(attSpec) ; // Messages can take any attributes
  ProcessLinksNN(linkSpec) ;
}
#else
BB1Message::BB1Message(const string&	oname,
		       BB1KB&		kb,
		       BB1Class		*c,
		       const AVPSet	*attSpec,
		       const LinkSet	*linkSpec)
  : BB1Object(oname, kb, c)
{
  ProcessAttributes(attSpec) ; // Messages can take any attributes
  ProcessLinksNN(linkSpec) ;
}
#endif


// -----------------------------------------------------------------------------
// constructeur copie -- add fab
// -----------------------------------------------------------------------------

BB1Message::BB1Message(const BB1Message& src)
  : BB1Object(src)
{
}


// -----------------------------------------------------------------------------
// Send to the output stream a textual representation of the message.
// -----------------------------------------------------------------------------

std::ostream& operator <<(std::ostream& os, const BB1Message& message)
{
  string messageString = message.Value("message", NULLSTRING) ;
  os << message.Name() << "(" << messageString << ")" ;
  return (os) ;
}
