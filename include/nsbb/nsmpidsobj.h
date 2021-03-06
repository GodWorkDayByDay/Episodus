#ifndef nsmpidsobjH
#define nsmpidsobjH

# include <cstring.h>
# include <owl\window.h>
# include "nsbb\nsexport.h"
# include "ns_sgbd\nsfiche.h"

// Classe NSPidsObj pour le pids d'objets
//////////////////////////////////////////

//
// Taille des champs du fichier PIDSOBJ
//
#define PIDSOBJ_OBJET_LEN      13
#define PIDSOBJ_TYPE_LEN        6
#define PIDSOBJ_CLEF_LEN      255

//
// Indice des champs du fichier PIDS
//
#define PIDSOBJ_OBJET_FIELD     1
#define PIDSOBJ_TYPE_FIELD      2
#define PIDSOBJ_CLEF_FIELD      3

//---------------------------------------------------------------------------
//  Classe NSPidsObj
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//
class _NSBBCLASSE NSPidsObjData
{
 public:
	//
	// Variables de stockage des valeurs
	//
	char objet[PIDSOBJ_OBJET_LEN + 1] ;
  char type[PIDSOBJ_TYPE_LEN + 1] ;
	char clef[PIDSOBJ_CLEF_LEN + 1] ;

	NSPidsObjData();
	NSPidsObjData(const NSPidsObjData& rv);

	NSPidsObjData& operator=(const NSPidsObjData& src);
	int            operator==(const NSPidsObjData& o);
	void 			metABlanc();
	void 			metAZero();
};

//---------------------------------------------------------------------------
//  Classe NSPidsObjInfo  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------

class _NSBBCLASSE NSPidsObjInfo : public NSRoot
{
 public:
	//
	// Objet qui contient les donn�es
	//
	NSPidsObjData* 	pDonnees;

	NSPidsObjInfo(NSContexte* pCtx);
	NSPidsObjInfo(const NSPidsObjInfo& rv);
	~NSPidsObjInfo();

	NSPidsObjInfo& operator=(const NSPidsObjInfo& src);
	int 		       operator==(const NSPidsObjInfo& o);
};

#endif
