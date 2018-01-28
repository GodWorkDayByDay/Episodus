// -----------------------------------------------------------------------------
// nsTeamDefs.h
// -----------------------------------------------------------------------------
// Gestion l'Equipe de Sant�
// -----------------------------------------------------------------------------
// $Revision: 1.2 $
// $Author: pameline $
// $Date: 2009/07/23 17:05:29 $
// -----------------------------------------------------------------------------
// FLP - juin 2004
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Copyright Nautilus, 2004
// http://www.nautilus-info.com
// -----------------------------------------------------------------------------
// Ce logiciel est un programme informatique servant � g�rer et traiter les
// informations de sant� d'une personne.
//
// Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
// respectant les principes de diffusion des logiciels libres. Vous pouvez
// utiliser, modifier et/ou redistribuer ce programme sous les conditions de la
// licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA sur le site
// "http://www.cecill.info".
//
// En contrepartie de l'accessibilit� au code source et des droits de copie, de
// modification et de redistribution accord�s par cette licence, il n'est offert
// aux utilisateurs qu'une garantie limit�e. Pour les m�mes raisons, seule une
// responsabilit� restreinte p�se sur l'auteur du programme, le titulaire des
// droits patrimoniaux et les conc�dants successifs.
//
// A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
// associ�s au chargement, � l'utilisation, � la modification et/ou au
// d�veloppement et � la reproduction du logiciel par l'utilisateur �tant donn�
// sa sp�cificit� de logiciel libre, qui peut le rendre complexe � manipuler et
// qui le r�serve donc � des d�veloppeurs et des professionnels avertis
// poss�dant des connaissances informatiques approfondies. Les utilisateurs sont
// donc invit�s � charger et tester l'ad�quation du logiciel � leurs besoins
// dans des conditions permettant d'assurer la s�curit� de leurs syst�mes et ou
// de leurs donn�es et, plus g�n�ralement, � l'utiliser et l'exploiter dans les
// m�mes conditions de s�curit�.
//
// Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez pris
// connaissance de la licence CeCILL, et que vous en avez accept� les termes.
// -----------------------------------------------------------------------------
// This software is a computer program whose purpose is to manage and process
// a person's health data.
//
// This software is governed by the CeCILL  license under French law and abiding
// by the rules of distribution of free software. You can use, modify and/ or
// redistribute the software under the terms of the CeCILL license as circulated
// by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
//
// As a counterpart to the access to the source code and  rights to copy, modify
// and redistribute granted by the license, users are provided only with a
// limited warranty and the software's author, the holder of the economic
// rights, and the successive licensors have only limited liability.
//
// In this respect, the user's attention is drawn to the risks associated with
// loading, using, modifying and/or developing or reproducing the software by
// the user in light of its specific status of free software, that may mean that
// it is complicated to manipulate, and that also therefore means that it is
// reserved for developers and experienced professionals having in-depth
// computer knowledge. Users are therefore encouraged to load and test the
// software's suitability as regards their requirements in conditions enabling
// the security of their systems and/or data to be ensured and, more generally,
// to use and operate it in the same conditions as regards security.
//
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
// -----------------------------------------------------------------------------

#ifndef __TEAMDEFS_H__
# define __TEAMDEFS_H__


// -----------------------------------------------------------------------------
// D�finitions des termes Lexique utilis�s.
// --
// Definition of Lexical Terms that we use.
// -----------------------------------------------------------------------------


# define HEALTHTEAM								"LEQUI1"																			// code lexique correspondant � "Equipe de Sant�"
# define HTTEAM										"LEQUM1"																			// code lexique correspondant � "Equipe (personne morale)"

# define TEAMADMIN								"LADMI1"																			// code lexique correspondant � "donn�es administratives"
# define TEAMLABEL								"LNOMA1"																			// code lexique correspondant � "nom {chose}"
# define TEAMSPEC									"LSPEC1"																			// code lexique correspondant � "sp�cialit�"
# define TEAMADDRS								"LCADR1"																			// code lexique correspondant � "carnet d'adresses"
# define TEAMADDRESS							"LADRE1"																			// code lexique correspondant � "adresse"

# define HTMEMBER									"HMEMB1"																			// code lexique correspondant � "membre (au sein de l'Equipe de Sant�)"

// role
# define HTMEMBERPROFESSION				"LMETI1"																			// code lexique correspondant � "m�tier"
# define HTMEMBERSPECIALITY				"LSPEC1"																			// code lexique correspondant � "sp�cialit� [m�dicale]"

// mandat dur�e
# define HTMEMBERUSERMANDATE			"LMAND1"																			// code lexique correspondant � un "Mandat d'Utilisation"
# define HTMEMBERROOTMANDATE			"LROOT1"																			// code lexique correspondant � un "Mandat d'Administration"
# define HTMEMBERMANDATEBEGIN			"KOUVR1"																			// code lexique correspondant � "date d'ouverture"
# define HTMEMBERMANDATEEND				"KFERM1"																			// code lexique correspondant � "date de fermeture"
# define HTMEMBERMANDATEDURATION	"VDURE1"																			// code lexique correspondant � "dur�e"

// position
# define HTMEMBERPOSITION					"LPOSI1"																			// code lexique correspondant � "position (au sein de l'Equipe de Sant�)"
# define HTMEMBERDISTANCE					"VDIPA1"																			// code lexique correspondant � "distance (au patient)"
# define HTMEMBERANGLE						"VANPA1"																			// code lexique correspondant � "angle (dans le sens rosace du terme)"

// valeur
# define HTTEAMFREETEXT						"�CL000"
# define HTTEAMLEXIVAL						"�C;020"
# define HTMEMBERID								"�SPID1"																			// code lexique correspondant � "id (nss)" (PIDS)
# define HTOBJECTID								"�OBJE1"																			// code lexique correspondant � l'ID d'un objet (OIDS)
# define HTVALDATE               	"�T0;19"
# define HTVALNUM									"�N"                                        	// "valeur num�rique (sur 2 digits)"
# define HTVALNUM2								"�N0;02"                                      // code lexique correspondant � une "valeur num�rique (sur 2 digits)"
// #define HTVALNUM3								"�N0;03"                                    // code lexique correspondant � une "valeur num�rique (sur 3 digits)"

// unit�
# define HTNOUNIT								"200001"																				// code lexique correspondant � "pas d'unit�"
# define HTDATE									"2DA021"																				// code lexique d'une valeur correspondant � "une date"
# define HTANGUNIT								"2RODE1"																				// code lexique correspondant � "degr� d'angle de rosace"

#endif // __TEAMDEFS_H__
