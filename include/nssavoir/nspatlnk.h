//---------------------------------------------------------------------------//    EPTABLES.H
//    NAUTILUS juillet 2001
//
//    D�finition des objets de base de donn�e
//---------------------------------------------------------------------------
#ifndef __NSPATLNK_H
#define __NSPATLNK_H

// #include "ns_sgbd\nsfiche.h"
// #include "nssavoir\nspatbas.h"
// #include "nssavoir\nstransa.h"
// #include "nsdn\nsdocum.h"
// #include "partage\nsglobal.h"
#if defined(_DANSLEXIDLL)
	#define _CLASSELEXI __export
#else
	#define _CLASSELEXI __import
#endif

//
// Taille des champs du fichier NSPATLNK
//
#define PATLINK_QUALIFIE_LEN 	   PAT_NSS_LEN + DOC_CODE_DOCUM_LEN + PPD_NOEUD_LEN   // Arriv�e de la fl�che / Arrow end
// #define PATLINK_LIEN_LEN 	   2
#define PATLINK_LIEN_LEN 	  	   5
#define PATLINK_LIEN_LEVEL_LEN 	 2   // Niveau de certitude du lien / Link's level of certitude
#define PATLINK_QUALIFIANT_LEN   PATLINK_QUALIFIE_LEN   // Origine de la fl�che / Arrow start
#define PATLINK_TRAN_NEW_LEN     TRAN_CODE_LEN   // Session de cr�ation / Creation session
#define PATLINK_TRAN_DEL_LEN     TRAN_CODE_LEN   // Session de destruction / Delete session
#define PATLINK_CAUSE_LEN    	   1   // Cause / Reason

//
// Indice des champs du fichier NSPATLNK
//
/*
#define PATLINK_QUALIFIE_FIELD 	  	1
#define PATLINK_LIEN_FIELD 	  	    2
#define PATLINK_QUALIFIANT_FIELD    3
#define PATLINK_TRAN_NEW_FIELD      4
#define PATLINK_TRAN_DEL_FIELD    	5
#define PATLINK_CAUSE_FIELD    	    6
#define PATLINK_LIEN_LEVEL_FIELD    7
*/

// **************************** Table NSPATLNK.DB ****************************

//---------------------------------------------------------------------------
//  Classe NSPatLinkData
//
// Objet contenant les donn�es
//---------------------------------------------------------------------------
//
class _CLASSELEXI NSPatLinkData
{
	public :

		/*
		char qualifie[PATLINK_QUALIFIE_LEN + 1];
    char lien[PATLINK_LIEN_LEN + 1];
    char lien_level[PATLINK_LIEN_LEVEL_LEN + 1];
    char qualifiant[PATLINK_QUALIFIANT_LEN + 1];
    char tranNew[PATLINK_TRAN_NEW_LEN + 1];
    char tranDel[PATLINK_TRAN_DEL_LEN + 1];
    char cause[PATLINK_CAUSE_LEN + 1];
    */

    string sQualifie ;
    string sLien ;
    string sLienLevel ;
    string sQualifiant ;
    string sCause ;

    NSPatLinkData() ;    NSPatLinkData(const NSPatLinkData& rv) ;
    ~NSPatLinkData() ;

    NSPatLinkData& operator=(const NSPatLinkData& src) ;
    int 		       operator==(const NSPatLinkData& o) ;

    void metAZero() ;
};

class NSPatLink;

//---------------------------------------------------------------------------
//  Classe NSPatLinkInfo  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSPatLinkInfo
{
	public :

  	NSPatLinkData _Donnees ;
		bool          _isDirty ;

		NSPatLinkInfo() ;
		// NSPatLinkInfo(NSPatLink*) ;
		NSPatLinkInfo(const NSPatLinkInfo& rv) ;
    ~NSPatLinkInfo() ;

    string getQualifie()   { return _Donnees.sQualifie ;   }
    string getLien()       { return _Donnees.sLien ;       }
    string getLienLevel()  { return _Donnees.sLienLevel ;  }
    string getQualifiant() { return _Donnees.sQualifiant ; }
    string getCause()      { return _Donnees.sCause ;      }

    void setQualifie(string sData)   { _Donnees.sQualifie   = sData ; }
    void setLien(string sData)       { _Donnees.sLien       = sData ; }
    void setLienLevel(string sData)  { _Donnees.sLienLevel  = sData ; }
    void setQualifiant(string sData) { _Donnees.sQualifiant = sData ; }
    void setCause(string sData)      { _Donnees.sCause      = sData ; }

    void    setDirty(bool flag) { _isDirty = flag ; }
    bool    getDirty()          { return _isDirty ; }

		NSPatLinkInfo& operator=(const NSPatLinkInfo& src) ;
		int 		       operator==(const NSPatLinkInfo& o) ;
};

//---------------------------------------------------------------------------
//  Classe NSPatLink
//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//---------------------------------------------------------------------------
//
/*
class _CLASSELEXI NSPatLink : public NSPatLinkInfo, public NSFiche
{
    public :

        int iTypeLink;

	  	NSPatLink(NSContexte* pCtx, int iType = graphPerson);
     	NSPatLink(NSPatLink& rv);
	  	~NSPatLink();

	  	void alimenteFiche();
	  	void videFiche();
	  	DBIResult open();

     	NSPatLink& operator=(NSPatLink src);
     	int 	   operator==(NSPatLink& o);
};
*/

//
// D�finition de NSCodPrestArray (Array de NSCodPrestInfo(s))
//

typedef vector<NSPatLinkInfo*>       NSPatLkArray ;
typedef NSPatLkArray::iterator       NSPatLinkIter ;
typedef NSPatLkArray::const_iterator NSPatLinkConstIter ;

class _CLASSELEXI NSPatLinkArray : public NSPatLkArray
{
	public :

		// Constructeurs
  	NSPatLinkArray() : NSPatLkArray() {}
		NSPatLinkArray(const NSPatLinkArray& rv) ;
		// Destructeur
		virtual ~NSPatLinkArray() ;
    void vider() ;

    NSPatLinkArray& operator=(const NSPatLinkArray& src) ;
    int 	          operator==(const NSPatLinkArray& o) ;
};


//---------------------------------------------------------------------------
#endif    // __NSPATLNK_H

