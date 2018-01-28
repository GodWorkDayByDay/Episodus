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
# include "AttValPair.h" // for NULLAVP
# include "BB1BB.h"
#else
# include "ns_ob1\AttValPair.h" // for NULLAVP
# include "ns_ob1\BB1BB.h"
#endif

const AVPSet								NULLAVPSET ;
const LinkSet								NULLLINKSET ;

const PublicationT          NULLPUB               = PublicationT(0);
const ValidityT             NULLVALI              = ValidityT(0);
const InitFunctionT		      NULLINITFN						= InitFunctionT(0) ;
const TerminationConditionT	NULLTERMCOND					= TerminationConditionT(0) ;

const Cycle			            PRECYCLE							= Cycle(-1) ;

const TriggerConditionT			NULLTC								= TriggerConditionT(0) ;
const PreconditionT					NULLPC								= PreconditionT(0) ;
const ObviationConditionT		NULLOC								= ObviationConditionT(0) ;
const ActionT								NULLAC								= ActionT(0) ;
const ContextGeneratorT			NULLCONTEXTGENERATOR	= ContextGeneratorT(0) ;

const GoalT									NULLGOAL							= GoalT(0) ;

int													DebugObjectCPT				= 0 ;















