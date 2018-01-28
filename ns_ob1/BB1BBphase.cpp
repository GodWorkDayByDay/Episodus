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
# include "BB1Exception.h" // add fab
#else
# include "ns_ob1\BB1BB.h"
# include "ns_ob1\BB1Exception.h" // add fab
#endif


// -----------------------------------------------------------------------------
// Allow knowledge bases, blackboard objects, and links to be created (defined)
// only during certain phases
// -----------------------------------------------------------------------------

bool	BB1BB::CreatePhaseCheck(const string& method) const
{
#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::CreatePhaseCheck(\"" << method << "\") const\n\n" ;
#endif
  switch (Phase())
  {
		case INITIALIZATION		:
		case CYCLE_0					:
		case INTERPRETER			:
		case AGENDA_MANAGER		:
		case KSARS_MANAGMENT	:
		case BETWEEN_CYCLES		:
		case POST_TERMINATION	:	return (true) ;

		case CHECK_MESSAGES		:
		case TRIGGERING				:
		case SCHEDULER				:
		case TERMCOND					:
		{
			CreatePhaseError	cpe(*this,
														method,
														"", // don't know entity type yet
														"Call only outside cycle or from KS actions") ;
			return (false) ; // throw cpe;
		}

		default								:
		{
			UnknownPhase up(*this, "BB1BB::CreatePhaseCheck(...)") ;
			return (false) ; // throw up;
		}
	}
}



// -----------------------------------------------------------------------------
// Allow GoNCycles only during certain phases
// -----------------------------------------------------------------------------

bool	BB1BB::GoNCyclesPhaseCheck() const
{

#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::GoNCyclesPhaseCheck() const\n\n" ;
#endif

  switch (Phase())
  {
		case INITIALIZATION 	:
		case BETWEEN_CYCLES 	:	return (true) ;

		case POST_TERMINATION :
		{
			GoPhaseError gpe(	*this,
												"BB1BB::GoNCycles(...)",
												"The run has terminated; initialize a new bb before trying to execute again") ;
			return (false) ; // throw gpe;
		}

		case CYCLE_0					:
		case INTERPRETER			:
		case TRIGGERING				:
		case AGENDA_MANAGER		:
		case KSARS_MANAGMENT	:
		case SCHEDULER				:
		case TERMCOND 				:
		{
			GoPhaseError gpe(	*this,
												"BB1BB::GoNCycles()",
												"Don't call from termination condition, KS conditions or actions") ;
			return (false) ; // throw gpe;
		}

		case CHECK_MESSAGES 	:
		{
			GoPhaseError gpe(	*this,
												"BB1BB::GoNCyclesPhaseCheck()",
												"Called during CHECK_MESSAGES") ; // this is a BBK error
			return (false) ; // throw gpe;
		}

		default 							:
		{
			UnknownPhase up(*this, "BB1BB::GoNCyclesPhaseCheck()") ;
			return (false) ; // throw up;
		}
	}
}



// -----------------------------------------------------------------------------
// Allow KB only during certain phases
// -----------------------------------------------------------------------------
                 /*
bool	BB1BB::KSPhaseCheck() const
{

#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::KSPhaseCheck() const\n\n" ;
#endif

  switch (Phase())
  {
    case TRIGGERING				:
		case AGENDA_MANAGER		:
		case KSARS_MANAGMENT	:
		case INTERPRETER			: return (true) ;

		case CYCLE_0					:
		{
			KSUndefined ksu(*this, "BB1BB::KS()", "There is no KS on cycle 0") ;
			return (false) ; // throw ksu;
		}

		case INITIALIZATION		:
		case CHECK_MESSAGES		:
		case SCHEDULER				:
		case BETWEEN_CYCLES		:
		case POST_TERMINATION	:
		case TERMCOND					:
		{
			KSUndefined ksu(*this, "BB1BB::KS()", "Call only from KS conditions and actions") ;
			return (false) ; // throw ksu;
		}

		default								:
		{
			UnknownPhase up(*this, "BB1BB::KSPhaseCheck()") ;
			return (false) ; // throw up;
		}
	}
}            */

      /*
// -----------------------------------------------------------------------------
// Allow KSAR only during certain phases
// -----------------------------------------------------------------------------

bool	    BB1BB::KSARPhaseCheck() const
{

#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::KSARPhaseCheck() const\n\n" ;
#endif

  switch (Phase())
  {
    case AGENDA_MANAGER		:
		case INTERPRETER			: return (true) ;

		case CYCLE_0					:
		{
			KSARUndefined ksaru(*this, "BB1BB::KSAR()", "There is no KSAR on cycle 0") ;
			return (false) ; // throw ksaru;
		}

		case INITIALIZATION		:
		case CHECK_MESSAGES		:
		case TRIGGERING				:
		case SCHEDULER				:
		case KSARS_MANAGMENT	:
		case BETWEEN_CYCLES		:
		case POST_TERMINATION	:
		case TERMCOND					:
		{
			KSARUndefined ksaru(*this,
													"BB1BB::KSAR()",
													"Call only from KS conditions (except trigger) and actions") ;
			return (false) ; // throw ksaru;
		}

		default								:
		{
			UnknownPhase up(*this, "BB1BB::KSARPhaseCheck()") ;
			return (false) ; // throw up;
		}
	}
}        */


// -----------------------------------------------------------------------------
// Allow OpenSocket and CloseSocket only during certain phases
// -----------------------------------------------------------------------------





// -----------------------------------------------------------------------------
// Allow SetTraceCycle only during certain phases
// -----------------------------------------------------------------------------

       /*
bool	BB1BB::TracePhaseCheck() const
{

#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::TracePhaseCheck() const\n\n" ;
#endif

  switch (Phase())
  {
		case INITIALIZATION		:
		case BETWEEN_CYCLES		:
		case POST_TERMINATION	: return (true) ;

		case CYCLE_0					:
		case AGENDA_MANAGER		:
		case INTERPRETER			:
		case KSARS_MANAGMENT	:
		case TRIGGERING				:
		case CHECK_MESSAGES		:
		case SCHEDULER				:
		case TERMCOND					:
		{
			TracePhaseError tpe(*this, "BB1BB::SetTrace*()") ;
			return (false) ; // throw tpe;
		}

		default								:
		{
			UnknownPhase up(*this, "BB1BB::TracePhaseCheck()") ;
			return (false) ; // throw up;
		}
	}
}  */


#ifndef __TCONTROLER__
// -----------------------------------------------------------------------------
// Allow TriggerEvent only during certain phases
// -----------------------------------------------------------------------------

bool	BB1BB::TriggerEventPhaseCheck() const
{

#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::TriggerEventPhaseCheck() const\n\n" ;
#endif

  switch (Phase())
	{
		case TRIGGERING				:
		case AGENDA_MANAGER		:
		case KSARS_MANAGMENT	:
		case INTERPRETER			: return (true) ;

		case CYCLE_0					:
		{
			TriggerEventUndefined teu(*this,
																"BB1BB::TriggerEvent(...)",
																"There is no trigger event on cycle 0") ;
			return (false) ; // throw teu;
		}

		case INITIALIZATION		:
		case CHECK_MESSAGES		:
		case SCHEDULER				:
		case BETWEEN_CYCLES		:
		case TERMCOND					:
		case POST_TERMINATION	:
		{
			TriggerEventUndefined teu(*this,
																"BB1BB::TriggerEvent()",
																"Call only from KS trigger condition, preconditions, obviation conditions, context generators, and actions") ;
			return (false) ; // throw something
		}

		default								:
		{
			UnknownPhase up(*this, "BB1BB::TriggerEventPhaseCheck()") ;
			return (false) ; // throw up;
		}
	}
}


// -----------------------------------------------------------------------------
// Allow TriggerObject only during certain phases
// -----------------------------------------------------------------------------

bool	BB1BB::TriggerObjectPhaseCheck() const
{

#ifdef _DEBUG_
  trout << "-- DEBUG:: BB1BB::TriggerObjectPhaseCheck() const\n\n" ;
#endif

  switch (Phase())
  {
		case TRIGGERING				:
		case AGENDA_MANAGER		:
		case KSARS_MANAGMENT	:
		case INTERPRETER			:	return (true) ;

		case CYCLE_0					:
		{
			TriggerObjectUndefined tou(	*this,
																	"BB1BB::TriggerObject(...)",
																	"There is no trigger object on cycle 0") ;
			return (false) ; // throw tou;
		}

		case INITIALIZATION		:
		case CHECK_MESSAGES		:
		case SCHEDULER				:
		case BETWEEN_CYCLES		:
		case TERMCOND					:
		case POST_TERMINATION	:
		{
			TriggerObjectUndefined tou(	*this,
																	"BB1BB::TriggerObject()",
																	"Call only from KS trigger condition, preconditions, obviation conditions, and actions") ;
			return (false) ; // throw tou;
		}

		default								:
		{
			UnknownPhase up(*this, "BB1BB::TriggerObjectPhaseCheck()") ;
			return (false) ; // throw up;
		}
	}
}

#endif
