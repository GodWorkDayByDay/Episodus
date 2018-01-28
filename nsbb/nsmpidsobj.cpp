//---------------------------------------------------------------------------
// Base contenant l'identifiant objet dans le modele MUE
//---------------------------------------------------------------------------
#include "nsbb\nsmpidsobj.h"

//***************************************************************************
// Impl�mentation des m�thodes NSPidsObj
//***************************************************************************

//---------------------------------------------------------------------------
//  Function:    NSPidsObjData::NSPidsObjData()
//
//  Description: Constructeur.
//---------------------------------------------------------------------------
NSPidsObjData::NSPidsObjData()
{
	metAZero();
}

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjData::NSPidsObjData(NSPidsObjData& rv)
//  Description:	Constructeur copie
//  Retour:			Rien
//---------------------------------------------------------------------------
NSPidsObjData::NSPidsObjData(const NSPidsObjData& rv)
{
  strcpy(objet, rv.objet) ;
  strcpy(type,  rv.type) ;
  strcpy(clef,  rv.clef) ;
}

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjData::operator=(NSPidsObjData src)
//  Description:	Op�rateur =
//  Retour:			R�f�rence sur l'objet cible
//---------------------------------------------------------------------------
NSPidsObjData&
NSPidsObjData::operator=(const NSPidsObjData& src)
{
  if (this == &src)
    return *this ;

  strcpy(objet, src.objet) ;
  strcpy(type,  src.type) ;
  strcpy(clef,  src.clef) ;

  return *this;
}

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjData::operator==(NSPidsObjData src)
//  Description:	Op�rateur de comparaison
//  Retour:			0 ou 1
//---------------------------------------------------------------------------
int
NSPidsObjData::operator==(const NSPidsObjData& o)
{
	if ((strcmp(objet, o.objet) == 0) &&
      (strcmp(type,  o.type)  == 0) &&
			(strcmp(clef,  o.clef)  == 0))
    return 1 ;

  return 0 ;
}

//---------------------------------------------------------------------------
//  Function:    NSPidsObjData::metAZero()
//
//  Description: Met � z�ro les variables de la fiche
//---------------------------------------------------------------------------
void
NSPidsObjData::metAZero()
{
	//
	// Met les champs de donn�es � z�ro
	//
	memset(objet, 0, PIDSOBJ_OBJET_LEN + 1) ;
  memset(type,  0, PIDSOBJ_TYPE_LEN + 1) ;
	memset(clef,  0, PIDSOBJ_CLEF_LEN + 1) ;
}

//---------------------------------------------------------------------------
//  Function:    NSPidsObjData::metABlanc()
//
//  Description: Met � blanc les variables de la fiche
//---------------------------------------------------------------------------
void
NSPidsObjData::metABlanc()
{
	//
	// Met les champs de donn�es � blanc
	//
	memset(objet,       				' ', 	PIDSOBJ_OBJET_LEN);
    memset(type,                        ' ',    PIDSOBJ_TYPE_LEN);
	memset(clef,       					' ', 	PIDSOBJ_CLEF_LEN);
}

/*****************************************************************************/
// 							METHODES DE NSPidsObj
/*****************************************************************************/

#ifndef N_TIERS

//---------------------------------------------------------------------------
//  Function:    NSPidsObj::NSPidsObj(NSSuper* pSuper)
//
//  Description: Constructeur.
//---------------------------------------------------------------------------
NSPidsObj::NSPidsObj(NSContexte* pCtx)
          :NSPidsObjInfo(pCtx), NSFiche(pCtx)
{
}

//---------------------------------------------------------------------------
//  Function:  NSPidsObj::~NSPidsObj()
//
//  Arguments:
//
//  Description:
//             Destructeur.
//             Ferme proprement une classe de ce type.
//  Returns:
//             Aucun
//---------------------------------------------------------------------------
NSPidsObj::~NSPidsObj()
{
}

//---------------------------------------------------------------------------
//  Function:  NSPidsObj::alimenteFiche()
//
//  Arguments:
//
//  Description:
//             Transf�re le contenu de pRecBuff dans les variables de
//             la fiche
//  Returns:
//             Rien
//---------------------------------------------------------------------------
void NSPidsObj::alimenteFiche()
{
	alimenteChamp(pDonnees->objet, 			PIDSOBJ_OBJET_FIELD,		PIDSOBJ_OBJET_LEN);
    alimenteChamp(pDonnees->type,           PIDSOBJ_TYPE_FIELD,         PIDSOBJ_TYPE_LEN);
	alimenteChamp(pDonnees->clef, 			PIDSOBJ_CLEF_FIELD,		 	PIDSOBJ_CLEF_LEN);
}

//---------------------------------------------------------------------------
//  Function:  NSPidsObj::videFiche()
//
//  Description: Transf�re le contenu des valeurs de la fiche dans pRecBuff
//---------------------------------------------------------------------------
void NSPidsObj::videFiche()
{
	videChamp(pDonnees->objet, 			PIDSOBJ_OBJET_FIELD,		PIDSOBJ_OBJET_LEN);
    videChamp(pDonnees->type,           PIDSOBJ_TYPE_FIELD,         PIDSOBJ_TYPE_LEN);
	videChamp(pDonnees->clef, 			PIDSOBJ_CLEF_FIELD,		 	PIDSOBJ_CLEF_LEN);
}

//---------------------------------------------------------------------------
//  Function:  NSPidsObj::open()
//
//  Arguments:
//
//  Description:
//             Ouvre la table primaire et les index secondaires
//  Returns:
//             PXERR_, s'il y a lieu
//---------------------------------------------------------------------------
DBIResult NSPidsObj::open()
{
	char tableName[] = "NSPIDSOBJ.DB";
	//
	// Appelle la fonction open() de la classe de base pour ouvrir
	// l'index primaire
	//
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL);
    return (lastError);
}

//---------------------------------------------------------------------------
//  Function:  NSPidsObj::close()
//
//  Arguments:
//
//  Description:
//             Ferme la table primaire et l'index secondaire
//  Returns:
//             PXERR_, s'il y a lieu
//---------------------------------------------------------------------------
DBIResult NSPidsObj::close()
{
	//
	// Appelle la fonction close() de la classe de base pour fermer
	// l'index primaire
	//
	lastError = NSFiche::close();

    return (lastError);
}

#endif

//***************************************************************************
//
// Impl�mentation des m�thodes NSPidsObjInfo
//
//***************************************************************************

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjInfo::NSPidsObjInfo(NSSuper* pSuper)
//  Description:	Constructeur avec superviseur (pour les acc�s aux bases)
//  Retour:			Rien
//---------------------------------------------------------------------------
NSPidsObjInfo::NSPidsObjInfo(NSContexte* pCtx)
	:	NSRoot(pCtx)
{
	// Cr�e l'objet de donn�es
	pDonnees 	  	= new NSPidsObjData();
}

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjInfo::NSPidsObjInfo(NSPidsObj*)
//  Description:	Constructeur � partir d'un NSPidsObj
//  Retour:			Rien
//---------------------------------------------------------------------------
#ifndef N_TIERS
NSPidsObjInfo::NSPidsObjInfo(NSPidsObj* pPids)
	:	NSRoot(pPids->NSPidsObjInfo::pContexte)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees 	   		= new NSPidsObjData();

	//
	// Copie les donn�es du NSPidsObj
	//
	*pDonnees 	   	= *(pPids->pDonnees);
}
#endif

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjInfo::~NSPidsObjInfo()
//  Description:	Destructeur
//  Retour:			Rien
//---------------------------------------------------------------------------
NSPidsObjInfo::~NSPidsObjInfo()
{
	delete pDonnees;
  // pas de delete du pSuper
}

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjInfo::NSPidsObjInfo(NSPidsObjInfo& rv)
//  Description:	Constructeur copie
//  Retour:			Rien
//---------------------------------------------------------------------------
NSPidsObjInfo::NSPidsObjInfo(const NSPidsObjInfo& rv)
              :NSRoot(rv.pContexte)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees 	   		= new NSPidsObjData();
	//
	// Copie les valeurs du NSPidsObjInfo d'origine
	//
	*pDonnees 	   	= *(rv.pDonnees);
}

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjInfo::operator=(NSPidsObjInfo src)
//  Description:	Op�rateur d'affectation
//  Retour:			R�f�rence de l'objet cible
//---------------------------------------------------------------------------
NSPidsObjInfo& NSPidsObjInfo::operator=(const NSPidsObjInfo& src)
{
  if (this == &src)
    return *this ;

  *pDonnees = *(src.pDonnees);
  pContexte = src.pContexte;
  
	return *this;
}

//---------------------------------------------------------------------------
//  Fonction:		NSPidsObjInfo::operator==(NSPidsObjInfo src)
//  Description:	Op�rateur de comparaison
//  Retour:			R�f�rence de l'objet cible
//---------------------------------------------------------------------------
int NSPidsObjInfo::operator==(const NSPidsObjInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}

// fin du fichier nsmpidsobj.cpp