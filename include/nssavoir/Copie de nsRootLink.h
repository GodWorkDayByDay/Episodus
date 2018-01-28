// -----------------------------------------------------------------------------
// nsRootLink.h
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Copyright Nautilus, 2004
// http://www.nautilus-info.com
// -----------------------------------------------------------------------------
// Ce logiciel est un programme informatique servant � [rappeler les
// caract�ristiques techniques de votre logiciel].
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
// This software is a computer program whose purpose is to [describe
// functionalities and technical features of your software].
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

#ifndef __NSROOTLINK_H__
# define __NSROOTLINK_H__

# if defined(_DANSLEXIDLL)
#  define _CLASSELEXI __export
# else
#  define _CLASSELEXI __import
# endif


// -----------------------------------------------------------------------------
// Important note about Doxygen tag
// -----------------------------------------------------------------------------
// All comments begining with "//!" or "//!<" must not be deleted, they concerns
// Doxygen doc generator.
// If you modify some classes and/or methods and/or variables please modify also
// the doxygen available informations.
// -----------------------------------------------------------------------------


//! \brief NSRootLink is the root class for all operations about links. It
//!        contains the enum that define all types of links

//! problemRelatedTo         : lien entre une pr�occupation et un objet                              1
//! problemContactElement    : lien entre l'Assesment et sa pr�occupation                            2
//! soapRelatedTo            : lien entre un �l�ment du SOAP et son Assesment                        3
//! problemGoals             : lien entre un objectif et la pr�occupation � laquelle il est li�      4
//! goalOpener               : �v�nement qui d�clenche un objectif                                   5
//! goalReseter              : �v�nement qui red�marre un nouveau cycle, si cyclique                 6
//! goalAlarm                : pour les objectifs "existence de", signal de disparition              7
//! goalCloser               : �v�nement qui ferme un objectif                                       8
//! archetype                : lien entre un noeud et l'Archetype dont il est lanceur                9
//! refCreator               : document qui a initi� un noeud au sein d'un autre document           10
//! referentialOf            : lien entre un r�f�rentiel et le noeud qui a �t� cr�� en l'appliquant 11
//! guidelineOf              : lien entre un arbre d�cisionnel et le noeud qui a �t� cr��           12
//! drugOf                   : lien entre un ttt et la pr�occupation � laquelle il est li�          13
//! treatmentOf                                                                                     14
//! prescriptionElement      : arbre de prescription, en dehors de l'arbre d'index de sant�         15
//! personDocument           : meta-document appartenant � la personne                              16
//! personHealthIndex        : lien entre Personne et l'index de sant�                              17
//! personSynthesis          : lien entre Personne et la synth�se                                   18
//! personIndexExtension     : lien entre Personne et une extension d'index (concern, ttt, goal)    19
//! personAdminData          : lien entre Personne et ses donn�es administratives                   20
//! personHealthTeam         : lien entre Personne et son �quipe de sant�                           21
//! personContribution       : contribution pour cette personne                                     22
//! personFolderLibrary      : biblioth�que de dossiers pour cette personne                         23
//! personHealthProData      : donn�es de professionnel de sant� pour cette personne                24
//! personRiskManager        : arbre de pr�occupations de sant� de "risque de..."                   25
//! docData                  : donn�es du document                                                  26
//! docFolder                : chemise (dossier) auquel appartient le document                      27
//! docPilot                 : service Pilot qui permet l'acc�s aux data du document                28
//! contribElement           : arbre modifi�/cr�� lors de cette contribution                        29
//! indexConcerns            : extension d'index contenant les pr�occupations                       30
//! indexGoals               : extension d'index contenant les objectifs                            31
//! docComposition           : description des �l�ments de document compos�                         32
//! compositionTag           : lien entre un tag et le document qui prend sa place                  33
//! processWaitingFor        : lien entre un noeud patient et une pr�occupation en attente          34     // modif fab - 06/08/2003
//! processResultFrom        : lien entre un noeud r�sultat d'une pr�occupation et la pr�occupation 35     // modif fab - 06/08/2003
//! objectIn                 : lien entre un objet et son objet pere                                36     // modif rem - 17/10/2003
//! hiddenBy                 : noeud masqu� par un autre noeud                                      37
//! contributionAdded        : lien entre une contribution et un document qui y a �t� cr��          38
//! contributionModified     : lien entre une contribution et un document qui y a �t� modifi�       39
//! contributionOpened       : lien entre une contribution et un document qui a �t� ouvert          40
//! copyOf                   : lien entre un noeud et sa copie                                      41
//! fonctionalUnitStay       : lien entre le s�jour et le noeud root d'un patient                   42
//! stayContribution         : lien entre le s�jour et la contribution                              43
//! personIdentifiers        : lien entre un identifiant et le noeud root d'un patient              44
//! OCRizedDocument          : lien entre un document image et son document OCRis�                  45
//! semantizedDocument       : lien entre un document texte et son document arbre                   46
//! viewOfDocument           : lien entre un document texte type et le document arbre maitre        47
//! letterOfDocument         : lien entre un document et une lettre d'accompagnement                48
//! appointment              : lien entre le noeud root et l'arbre des rendez-vous                  49

# define NBGRAPHLINKTYPES 36

class _CLASSELEXI NSRootLink
{
 public:
	enum NODELINKTYPES {	badLink = 0,
                        problemRelatedTo = 1, problemContactElement,
                        soapRelatedTo, problemGoals,
                        goalOpener, goalReseter, goalAlarm, goalCloser,
                        archetype, refCreator, referentialOf, guidelineOf,
                        drugOf, treatmentOf, prescriptionElement,
                        personDocument, personHealthIndex, personSocialIndex,
                        personSynthesis, personIndexExtension,
                        personAdminData, personHealthTeam, personContribution,
                        personFolderLibrary, personHealthProData, personRiskManager,
                        docData, docFolder, docPilot, contribElement,
                        indexConcerns, indexGoals,
                        docComposition, compositionTag,
                        processWaitingFor, processResultFrom, objectIn, hiddenBy,
                        contributionAdded, contributionModified, contributionOpened,
                        copyOf,
                        fonctionalUnitStay, stayContribution, personIdentifiers,
                        OCRizedDocument, semantizedDocument, viewOfDocument, letterOfDocument, externViewOfDocument, structuredVersionOfDocument,
                        appointment } ;

  int iTypeGraphe ;   //!< Type de graphe (graphPerson / graphObject) - pour mode MUE uniquement -

  //! constructor
  NSRootLink() ;

  //! destructor
  ~NSRootLink() ;

  //! Transformation d'une relation en code
	std::string     donneString(NODELINKTYPES iRelation) ;

  //! Transformation d'un code en relation
	NODELINKTYPES   donneRelation(std::string sRelation) ;

  //! Changement du type de graphe
  void            setTypeGraphe(int iType)    { iTypeGraphe = iType ; }
} ;

#endif // !__NSROOTLINK_H__

