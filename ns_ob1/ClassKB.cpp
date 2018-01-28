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
#include "ClassKB.h"
#include "BB1BB.h"
#include "AttValPair.h"
#else
#include "ns_ob1\ClassKB.h"
#include "ns_ob1\BB1BB.h"
#include "ns_ob1\AttValPair.h"
#endif

void loadClassKB(BB1BB& bb)
{
#ifdef _DEBUG_
  cout << "-- DEBUG:: loadClassKB(bb)\n\n" ;
#endif
	AttValPair		dialog			   ("label-dialog",				std::string("")) ;
	AttValPair		archetype		   ("archetype",					std::string("")) ;
	AttValPair		arcForceOui	   ("archetype-ouiforce",	std::string("")) ;
	AttValPair		arcRefus		   ("archetype-refus",		std::string("")) ;
	AttValPair		formulaire	   ("formulaire",					std::string("")) ;
  AttValPair    explication    ("Explication",        std::string("")) ;
  AttValPair    explication_ks ("Explication",        std::string("ks")) ;

	// The Class kb is already defined
	// This class meta-object must come first -- it is the followers' parent
	bb.DefineClass("Class",  explication) ; // metaclass must be defined first
	bb.DefineClass("Object", explication) ;

  //	bb.DefineClass("Decision",new AttValPair("Explication", string("")), List("Object")) ;
  //	bb.DefineClass("Focus",new AttValPair("Explication", string("")),    List("Decision")) ;
  //	bb.DefineClass("Strategy",new AttValPair("Explication", string("")), List("Decision")) ;
	//  bb.DefineClass("Event",new AttValPair("Explication", string("")),    List("Object")) ;

  StringList* pDirectSuperclassesForKs = List("Object") ;
  AVPSet*     pAllowedAttributesForKS  = Collect(&dialog, &archetype, &arcForceOui, &arcRefus, &formulaire) ;

	bb.DefineClass("KS", explication_ks, pDirectSuperclassesForKs, pAllowedAttributesForKS) ;

  delete pDirectSuperclassesForKs ;
  delete pAllowedAttributesForKS ;

  // bb.DefineClass("KSAR", new AttValPair("Explication", string("")),    List("Object")) ;

  StringList *pDirectSuperclassesForMsg = List("Object") ;

  bb.DefineClass("Message", explication, pDirectSuperclassesForMsg) ;

  delete pDirectSuperclassesForMsg ;
}

