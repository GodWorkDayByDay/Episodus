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

#include <iostream.h> // for BB1BB::TextualUserInterface(...)

#ifndef FOR_WINDOWS
# include "BB1BB.h"
# include "BB1Event.h" // for BB1BB::TextualUserInterface(...)
# include "BB1KB.h"    // for BB1BB::TextualUserInterface(...)
# include "BB1KS.h"    // for BB1BB::TextualUserInterface(...)
# include "BB1KSAR.h"  // for BB1BB::TextualUserInterface(...)
#else
# include "ns_ob1\BB1BB.h"
# include "ns_ob1\BB1Event.h" // for BB1BB::TextualUserInterface(...)
# include "ns_ob1\BB1KB.h"    // for BB1BB::TextualUserInterface(...)
# include "ns_ob1\BB1KS.h"    // for BB1BB::TextualUserInterface(...)
# include "ns_ob1\BB1KSAR.h"  // for BB1BB::TextualUserInterface(...)
#endif

// -----------------------------------------------------------------------------
// A rudimentary interactive text-based user interface
// -----------------------------------------------------------------------------

void	TUIHelp(std::ostream& tout)
{
  tout << "agenda:  Prompt for agenda & list its KSARs\n"
       << "cycle:   Print the cycle number\n"
       << "events:  List the names of all new events\n"
       << "exit:    Exit interactive user interface\n"
       << "go:      Run to termination\n"
       << "goN:     Prompt for N & execute N cycles\n"
       << "help:    Print this message\n"
       << "kb:      Prompt for KB name & list objects\n"
       << "kbs:     List the names of all KBs\n"
       << "ksar:    Prompt for number & display\n"
       << "kses:    List the long names of all KSes\n"
       << "next:    Identify the scheduled KSAR\n"
       << "object:  Prompt for long name & display\n"
       << "quit:    Exit interactive user interface\n"
       << "step:    Execute one cycle\n"
       << "trace:   Toggle tracing for events, cycles, & ksars\n";
}



#ifndef __TCONTROLER__
//  fonctionne en mode console, mais sinon on rentre dans une boucle infinie
Errcode	BB1BB::TextualUserInterface()
{
  std::ostream&	tout = cout;
  std::istream&	tin  = cin;
  string	command;

  tout << "BBK Command: " ;

  for (tin >> command ; command != "quit" && command != "exit" ; tin >> command)
  {
    if (command == "agenda")
    {
      tout << "Sub-agenda:\n1. Executable\n2. Triggered\n3. Obviated\n4. Executed\nSelection: " ;
      int sa ;
      tin >> sa ;
      switch (sa)
      {
        case 1:
				 	Agenda().Print(agenda.ExecutableSubAgenda, tout) ;
					break ;
        case 2:
					Agenda().Print(agenda.TriggeredSubAgenda, tout) ;
					break ;
        case 3:
					Agenda().Print(agenda.ObviatedSubAgenda, tout) ;
					break ;
        case 4:
					Agenda().Print(agenda.ExecutedSubAgenda, tout) ;
					break ;
      }
    }
    else // if (command == "agenda")
      if (command == "cycle")
				{ tout << "Cycle " << ThisCycle() << "\n" ; }
      else // if (command == "cycle")
				if (command == "events")
				{
					if (!NewEvents()->empty())
						for (EventCIter e = NewEvents()->begin() ; e != NewEvents()->end() ; e++)
							tout << *e << "\n" ;
				}
				else // if (command == "events")
					if (command == "go")
						{ GoNCycles() ; }
          else // if (command == "go")
						if (command == "goN")
            {
							int n ;
							tout << "Number of cycles: " ;
							tin >> n ;
							if (n > 0)
								{ GoNCycles(n) ; }
            }
						else // if (command == "goN")
							if (command == "help")
								TUIHelp(tout) ;
              else // if (command == "help")
              	if (command == "kb")
								{
									char KBName[128] ; // That should be big enough
									tout << "KB name: " ;
									tin >> KBName ;
									BB1KB *kb = KBNamed(KBName) ;
									if (kb)
									{
										const ObjectSet *objects = kb->ObjectsInKB() ;

										if (!objects->empty())
											for (ObjectCIter o = objects->begin() ; o != objects->end() ; o++)
												tout << (*o)->Name() << "\n" ;
									}
								}
                else // if (command == "kb")
									if (command == "kbs")
									{
										if (!AllKBs()->empty())
											for (KBCIter kb = AllKBs()->begin() ; kb != AllKBs()->end() ; kb++)
												tout << (*kb)->Name() << "\n" ;
									}
									else // if (command == "kbs")
										if (command == "ksar")
										{
											int n ;
											tout << "Number (1 to " << KSARCount() << "): " ;
											tin >> n ;
											if (0 < n && n <= KSARCount())
											{
												KSARptr k = KSARptr(ksarKB->ObjectNamed(GenerateName(KSARPrefix, n))) ;
												if (k)
													{ k->Dump(tout) ; }
												else // if (k)
													{ tout << "Unable to find KSAR\n" ; }
											}
											else // if (0 < n && n <= KSARCount())
												{ tout << "KSAR number " << n << " out of range\n" ; }
                    }
										else // if (command == "ksar")
											if (command == "kses")
											{
												if (!AllKSes()->empty())
													for (KSCIter k = AllKSes()->begin() ; k != AllKSes()->end() ; k++)
														tout << (*k)->LongName() << "\n" ;
											}
											else // if (command == "kses")
												if (command == "next")
												{
													if (NextKSAR())
														{ tout << NextKSAR()->Name() << "\n" ; }
													else // if (NextKSAR())
                            { tout << "There is no scheduled KSAR\n" ; }
                        }
												else // if (command == "next")
													if (command == "object")
													{
														char LongName[128] ; // That should be big enough

														tout << "Long name (<KB name>.<Object name>): " ;
														tin >> LongName ;

														string LongNameString = string(LongName) ;
														BB1Object *obj = ObjectNamed(LongNameString) ;

														if (obj)
															{ tout << *obj ; }
                          }
													else // if (command == "object")
														if (command == "step")
															{ GoNCycles(1) ; }
														else // if (command == "step")
															if (command == "trace")
															{
																SetTraceCycle(Not(TraceCycleP())) ;
																SetTraceEvent(Not(TraceEventP())) ;
																SetTraceKSAR(Not(TraceKSARP())) ;
																SetTraceMessage(Not(TraceMessageP())) ;
															}
															else // if (command == "trace")
																{ tout << "Command " << command << " ignored\n" ; }
    tout << "BBK Command: " ;
  }
  return (SUCCESS) ;
}
#endif
