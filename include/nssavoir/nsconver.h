#if !defined(NSCONVER_H)
#define NSCONVER_H

#include <vector>
#include "partage/ns_vector.h"

#ifndef __linux__
#if defined(_DANSLEXIDLL)
	#define _CLASSELEXI __export
#else
	#define _CLASSELEXI __import
#endif
#endif

//
// Taille des champs du fichier CONVERT
//
#define CV_RESULTAT_LEN         5
#define CV_OPERATION_LEN        2
#define CV_APARTIRDE_LEN        5
#define CV_LIEALAQUANTITE_LEN   5
#define CV_FORMULE_LEN        100
#define CV_METHODE_LEN          5
#define CV_UNITE_LEN            5

//
// Ordre des champs du fichier
//
#define CV_RESULTAT_FIELD        1
#define CV_OPERATION_FIELD       2
#define CV_APARTIRDE_FIELD       3
#define CV_LIEALAQUANTITE_FIELD  4
#define CV_FORMULE_FIELD         5
#define CV_METHODE_FIELD         6
#define CV_UNITE_FIELD           7

class NSPatPathoArray ;

//---------------------------------------------------------------------------
// Classe NSCVData
//---------------------------------------------------------------------------

#ifndef __linux__
class _CLASSELEXI NSCVData
#else
class NSCVData
#endif
{
	public :

    //
    // Variables de stockage des valeurs
    //
#ifndef _ENTERPRISE_DLL

    char resultat[CV_RESULTAT_LEN + 1] ;
    char operation[CV_OPERATION_LEN + 1] ;
    char apartir[CV_APARTIRDE_LEN + 1] ;
    char quantite[CV_LIEALAQUANTITE_LEN + 1] ;
    char formule[CV_FORMULE_LEN + 1] ;
    char methode[CV_METHODE_LEN + 1] ;
    char unite[CV_UNITE_LEN + 1] ;

    string getResult()   const { return string(resultat) ; }
    string getOperator() const { return string(operation) ; }
    string getFrom()     const { return string(apartir) ; }
    string getConcept()  const { return string(quantite) ; }
    string getFormula()  const { return string(formule) ; }
    string getMethod()   const { return string(methode) ; }
    string getUnit()     const { return string(unite) ; }

#else

    string _sResult ;
    string _sOperator ;
    string _sFrom ;
    string _sForConcept ;
    string _sFormula ;
    string _sMethod ;
    string _sUnit ;

    string getResult()   const { return _sResult ; }
    string getOperator() const { return _sOperator ; }
    string getFrom()     const { return _sFrom ; }
    string getConcept()  const { return _sForConcept ; }
    string getFormula()  const { return _sFormula ; }
    string getMethod()   const { return _sMethod ; }
    string getUnit()     const { return _sUnit ; }

    void setResult(string sV)   { _sResult = sV ; }
    void setOperator(string sV) { _sOperator = sV ; }
    void setFrom(string sV)     { _sFrom = sV ; }
    void setConcept(string sV)  { _sForConcept = sV ; }
    void setFormula(string sV)  { _sFormula = sV ; }
    void setMethod(string sV)   { _sMethod = sV ; }
    void setUnit(string sV)     { _sUnit = sV ; }

#endif

    NSCVData(const NSCVData& rv) ;
    NSCVData() { metAZero() ; }
    ~NSCVData() ;

    NSCVData& operator=(const NSCVData& src);
    int       operator==(const NSCVData& o);

    //methodes
    void metAZero() ;
};

//---------------------------------------------------------------------------
// Classe NSCV
//---------------------------------------------------------------------------
#ifndef _ENTERPRISE_DLL
class _CLASSELEXI NSCV : public NSFiche
#else
#ifndef __linux__
class _CLASSELEXI NSCV : public NSSuperRoot
#else
class NSCV : public NSSuperRoot
#endif
#endif
{
  protected:

    bool     _isOpened ;  // Is table opened

  public :

    NSCVData _Donnees ;   // Objet qui contient les donnees

    NSCV(NSSuper* pSuper) ;
    ~NSCV() ;

#ifndef _ENTERPRISE_DLL
    DBIResult open() ;
    void      alimenteFiche() ;
    void      videFiche() ;
#endif

#ifndef _ENTERPRISE_DLL
    void   CalculValeur(string sLexique, string* pLabel, string* pUnite,
     					          string* pMethodeCalcul,
                        const NSPatPathoArray* pNSPatPathoEnCours) ;
#else
    void   CalculValeur(string sLexique, string* pLabel, string* pUnite,
     					          string* pMethodeCalcul,
                        const NSPatPathoArray* pNSPatPathoEnCours,
                        const NSContexte* pCtx) ;
#endif
    void   AnalyseurSyntaxique(string sFormule, double* pValeur) ;
    bool   ConvertirUnite(double* pValeur,
                          const string& sResultat,
                          const string& sUnite,
                          const string& sLieA = string("")) const ;
    double Operation(const double dOperande, const double dOperateur, const string sOperation) const ;
    bool   isOperator(const char cChar) const ;

    bool   isOpened() const { return _isOpened ; }
};

//---------------------------------------------------------------------------
// Classe NSCVInfo
//---------------------------------------------------------------------------
class NSCVInfo
{
	public :
		//
    // Objet qui contient les donnees
		//
		NSCVData _Donnees ;

		NSCVInfo() ;
		NSCVInfo(NSCV* pNSCV) ;
		NSCVInfo(const NSCVInfo& rv) ;
		~NSCVInfo() ;

		NSCVInfo& operator=(const NSCVInfo& src) ;
		int       operator==(const NSCVInfo& o) ;
};

//********************************************************************
// code lexique et valeur chiffree : Exemple (VPOIDS, 70)
//********************************************************************
class CodeStructure
{
  public:

    CodeStructure(string sChaine, double dVal = -11111111, string sUnite = string("")) ;
    CodeStructure(const CodeStructure& src) ;
    ~CodeStructure() { lObjectCount-- ; }
    CodeStructure& operator=(const CodeStructure& src) ;

    double getValue() { return _dValeur ; }
    string getCode()  { return _sCode ;   }
    string getUnit()  { return _sUnite ;  }

    void setValue(double dV) { _dValeur = dV ; }
    void setCode(string sC)  { _sCode   = sC ; }
    void setUnit(string sU)  { _sUnite  = sU ; }

    static long getNbInstance()  { return lObjectCount ; }
    static void initNbInstance() { lObjectCount = 0 ; }

  protected:

    double _dValeur ;
    string _sCode ;
    string _sUnite ;

  private:

    static long lObjectCount ;
};

typedef vector<CodeStructure*> vectClass ;
typedef vectClass::iterator       iterCode ;
typedef vectClass::const_iterator iterCodeConst ;

class VectorCodeStructure : public vectClass
{
  public:

    VectorCodeStructure() ;
    ~VectorCodeStructure() ;
    VectorCodeStructure(const VectorCodeStructure& src) ;

    VectorCodeStructure& operator=(const VectorCodeStructure& src) ;

    void   vider() ;
    bool   Appartient(string sItem, CodeStructure* pResultat) const ;
    double donneValeur(string sItem) const ;
};

#endif

