//---------------------------------------------------------------------------//     NSPERSON.H
//
//  Contient les d�finitions des objets PATIENT et UTILISATEUR de NAUTILUS
//
//  1ere version : KRZISCH Ph. janvier 92   Derni�re modif : 12/08/93
//---------------------------------------------------------------------------
#ifndef __NSLANGUE_H
#define __NSLANGUE_H

#include <cstring.h>
#include "ns_sgbd\nsfiche.h"

#if defined(_DANSLEXIDLL)
	#define _CLASSELEXI __export
#else
	#define _CLASSELEXI __import
#endif

//// Taille des champs du fichier LANGUES
//
#define LANGUES_CODE_LEN    2
#define LANGUES_LIBEL_LEN  65

//// Indice des champs du fichier LANGUES
//
#define LANGUES_CODE_FIELD  1
#define LANGUES_LIBEL_FIELD 2

//---------------------------------------------------------------------------//  Classe NSLangues
//---------------------------------------------------------------------------

//
// Objet contenant les donn�es
//
class NSLanguesData
{
  public :

    //
    // Variables de stockage des valeurs
    //
    char code[LANGUES_CODE_LEN + 1] ;
    char libelle[LANGUES_LIBEL_LEN + 1] ;

    NSLanguesData() ;
    NSLanguesData(const NSLanguesData& rv) ;
    ~NSLanguesData() ;

    NSLanguesData& operator=(const NSLanguesData& src) ;
    int 		       operator==(const NSLanguesData& o) ;
};

//// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSLangues : public NSFiche
{
  public :

    //
    // Objet qui contient les donn�es
    //
    NSLanguesData* pDonnees ;

    NSLangues(NSSuper* pSuper) ;
    NSLangues(const NSLangues& rv) ;
    ~NSLangues() ;

    void alimenteFiche() ;
    void videFiche() ;
    DBIResult open() ;

    NSLangues& operator=(const NSLangues& src) ;    int        operator==(const NSLangues& o) ;};

//---------------------------------------------------------------------------//  Classe NSLanguesInfo  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSLanguesInfo
{
  public :

    //		// Objet qui contient les donn�es
		//
		NSLanguesData* pDonnees ;

		NSLanguesInfo() ;
		NSLanguesInfo(const NSLangues*) ;
		NSLanguesInfo(const NSLanguesInfo& rv) ;
    ~NSLanguesInfo() ;

		NSLanguesInfo& operator=(const NSLanguesInfo& src) ;
		int            operator==(const NSLanguesInfo& o) ;
};

#endif
