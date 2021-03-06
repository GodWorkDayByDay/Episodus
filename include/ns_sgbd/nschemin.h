// Fichier nschemin.h contenant la classe NSChemins - RS Janvier 1998// (cette classe doit etre accessible de ns_sgbd)

#ifndef __NSCHEMIN_H
#define __NSCHEMIN_H

#include <classlib\arrays.h>
#include "partage\ns_vector.h"
#include "ns_sgbd\nsfiche.h"

#if defined(_DANSSGBDDLL)
	#define _NSSGBDCLASSE __export
#else
	#define _NSSGBDCLASSE __import
#endif

//
// Taille des champs du fichier CHEMINS
//
#define CHM_CODE_LEN	      4
#define CHM_NOM_LEN			 35
#define CHM_CHEMIN_LEN		255
#define CHM_SUPPORT_LEN		  3
#define CHM_TYPE_DOC_LEN      5

//
// Indices des champs du fichier CHEMINS
//
#define CHM_CODE_FIELD		1
#define CHM_NOM_FIELD		2
#define CHM_CHEMIN_FIELD	3
#define CHM_SUPPORT_FIELD	4
#define CHM_TYPE_DOC_FIELD  5

//
// Taille des champs du fichier SUPPORTS
//
#define SUP_CODE_LEN	     3
#define SUP_NOM_LEN	        35
#define SUP_NOM_SERVEUR_LEN 35
#define SUP_UNITE_LEN	     2
#define SUP_FIXE_LEN		 1

//
// Indices des champs du fichier SUPPORTS
//
#define SUP_CODE_FIELD			1
#define SUP_NOM_FIELD			2
#define SUP_NOM_SERVEUR_FIELD   3
#define SUP_UNITE_FIELD			4
#define SUP_FIXE_FIELD			5

//---------------------------------------------------------------------------
//  Classe NSChemins
//---------------------------------------------------------------------------

//
// Objet donn�es
//
class _NSSGBDCLASSE NSCheminsData
{
  public :

    string _sCode ;
    string _sNom ;
    string _sChemin ;
    string _sSupport ;
    string _sType_doc ;

    NSCheminsData() ;
    NSCheminsData(const NSCheminsData& rv) ;

    NSCheminsData& operator=(const NSCheminsData& src) ;
    int 		       operator==(const NSCheminsData& o) ;

    void metAZero() ;
};

class _NSSGBDCLASSE NSCheminsInfo{
	public :
		//
    // Objet qui contient les donn�es
    //
    NSCheminsData _Donnees ;

    NSCheminsInfo() ;
		NSCheminsInfo(const NSCheminsInfo& rv) ;
    ~NSCheminsInfo() ;

    NSCheminsInfo& operator=(const NSCheminsInfo& src) ;
		int            operator==(const NSCheminsInfo& o) ;
};

//---------------------------------------------------------------------------
//  Classe NSSupports
//---------------------------------------------------------------------------

//
// Objet donn�es
//
class _NSSGBDCLASSE NSSupportsData
{
	public :
  	//
    // Variables de stockage des valeurs
    //
    string _sCode ;
    string _sNom ;
    string _sNomServeur ;
    string _sUnite ;
    string _sFixe ;

    NSSupportsData() ;
    NSSupportsData(const NSSupportsData& rv) ;

    NSSupportsData& operator=(const NSSupportsData& src) ;
    int 			      operator==(const NSSupportsData& o) ;

    void metAZero() ;
};

class _NSSGBDCLASSE NSSupportsInfo
{
	public :
  	//
    // Objet qui contient les donn�es
    //
    NSSupportsData _Donnees ;

    NSSupportsInfo() ;
		NSSupportsInfo(const NSSupportsInfo& rv) ;
    ~NSSupportsInfo() ;

    string getCode()      { return _Donnees._sCode ; }
    string getRootPath()  { return _Donnees._sNomServeur ; }
    string getRemovable() { return _Donnees._sFixe ; }

    void setCode(string sCode)     { _Donnees._sCode       = sCode ; }
    void setRootPath(string sRP)   { _Donnees._sNomServeur = sRP ; }
    void setRemovable(string sFix) { _Donnees._sFixe       = sFix ; }

    NSSupportsInfo& operator=(const NSSupportsInfo& src) ;
		int             operator==(const NSSupportsInfo& o ) ;
};
//// D�finition de NSSupportsArray
//
typedef vector<NSSupportsInfo*> NSSupportsVector ;
typedef NSSupportsVector::iterator       SupportsIter ;
typedef NSSupportsVector::const_iterator SupportsConstIter ;

class _NSSGBDCLASSE NSSupportsArray : public NSSupportsVector{
 public:

	// Constructeurs
	NSSupportsArray() : NSSupportsVector() {}
	NSSupportsArray(const NSSupportsArray& rv) ;
  NSSupportsArray& operator=(const NSSupportsArray& src) ;

	// Destructeur	virtual ~NSSupportsArray() ;
  void vider() ;

  bool initFromFile(string sFileName, NSSuper *pSuper) ;
  bool writeToFile(string sFileName, NSSuper *pSuper) ;
  bool setSupport(string sFileName, NSSuper *pSuper, string sSupportName, string sSupportValue, string sSupportRemoval = string("0")) ;

  bool addSupport(string sSupportName, string sSupportValue, string sSupportRemoval = string("0")) ;
};

//---------------------------------------------------------------------------
#endif    // __NSCHEMIN_H

