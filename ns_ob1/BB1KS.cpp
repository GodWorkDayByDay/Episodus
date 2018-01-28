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

#ifdef __GNUC__
# pragma implementation
#endif

#ifndef FOR_WINDOWS
# include "BB1KS.h"
#else
# include "ns_ob1\BB1KS.h"
#endif

BB1KS::BB1KS(const string&							oname,
        BB1KB&													kb,
        BB1Class												*c,
        const FunctorPublication* 			tdef,
        const FunctorValidity*         	tVal,
				const FunctorPrecondition*			pc,
				const FunctorAction*						ac,
        const FunctorObviation*				  oc,
				const AVPSet*										attSpec)
      :BB1Object(oname, AttValPair("explication", std::string(oname)) , kb, c),
       _tPublication(tdef),
       _tValidity(tVal),
       _preCondition(pc),
       _action(ac),
       _obviationCondition(oc)
{
  ProcessAttributes(attSpec) ;

  _iPriority = 0 ;
}

BB1KS::BB1KS(const BB1KS& src)
  : BB1Object(src),
    _tPublication(src._tPublication),
    _tValidity(src._tValidity),
    _preCondition(src._preCondition),
    _action(src._action),
    _obviationCondition(src._obviationCondition),
    _iPriority(src._iPriority)
{
}

void BB1KS::Save(ofstream& /* KBstream */)
{
}

AKS::AKS(BB1KS *dpioKS, APConditionT dpioAPCond)
{
	ks					= dpioKS ;
	apCondition	= dpioAPCond ;
}

AKS::AKS(const AKS& src)
{
	ks					= src.ks ;
	apCondition	= src.apCondition ;
}

AKS::~AKS()
{
	ks					= NULL ;
	apCondition	= NULL ;
}

AKS&		AKS::operator=(const AKS& src)
{
  if (this == &src)
		return *this ;

	ks					= src.ks ;
	apCondition	= src.apCondition ;

	return *this ;
}

