//---------------------------------------------------------------------------//    NSANXARY.CPP
//    PA   juillet 94
//    Kaddachi Hafedh
//  Impl�mentation des Arrays d'objets annexes de NAUTILUS
//---------------------------------------------------------------------------

#include "nautilus\nssuper.h"

#include "partage\nsdivfct.h"
#include "nsbb\nspatbd.h"
#include "partage\stringar.h"
#include "nsbb\nsbbsmal.h"

// -------------------------------------------------------------------------
// -------------------- METHODES DE NSPatPaDatArray ------------------------
// -------------------------------------------------------------------------
NSPatPaDatArray::NSPatPaDatArray(NSSuper* pSuper)
                :NSPatPaDatInfoArray(), NSSuperRoot(pSuper)
{}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSPatPaDatArray::NSPatPaDatArray(const NSPatPaDatArray& rv)
                :NSPatPaDatInfoArray(), NSSuperRoot(rv._pSuper)
{
try
{
  if (false == rv.empty())
    for (PatPaDatConstIter it = rv.begin() ; rv.end() != it ; it++)
      push_back(new NSPatPaDatInfo (*(*it))) ;
}
catch (...)
{
	erreur("Exception NSPatPaDatArray ctor.", standardError, 0) ;
}
}

//---------------------------------------------------------------------------//  Destructeur
//---------------------------------------------------------------------------
void
NSPatPaDatArray::vider()
{
  if (empty())
    return ;

  for (PatPaDatIter it = begin() ; end() != it ; )
  {
    delete *it ;
    erase(it) ;
  }
}

NSPatPaDatArray::~NSPatPaDatArray()
{
	vider() ;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSPatPaDatArray&
NSPatPaDatArray::operator=(const NSPatPaDatArray& src)
{
try
{
	if (this == &src)
		return *this ;

	//
	// Effacement des �l�ments d�j� contenus dans le vecteur destination
	//
	vider() ;
	//
	// Copie et insertion des �l�ments de la source
	//
	if (false == src.empty())
		for (PatPaDatConstIter it = src.begin() ; src.end() != it ; it++)
			push_back(new NSPatPaDatInfo(*(*it))) ;

	return *this ;
}
catch (...)
{
	erreur("Exception NSPatPaDatArray = operator.", standardError, 0) ;
	return *this ;
}
}

//---------------------------------------------------------------------------//  Ajout d'un �l�ment � l'array
//---------------------------------------------------------------------------
bool
NSPatPaDatArray::ajouteElement(NSPatPaDatInfo* pPatPatho)
{
	push_back(pPatPatho) ;
  return true ;
}

//***************************************************************************
// Impl�mentation des m�thodes NSPatPaDat
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur copie de NSPatPaDatData
//---------------------------------------------------------------------------
NSPatPaDatData::NSPatPaDatData(const NSPatPaDatData& rv)
{
  strcpy(codePatient,  rv.codePatient);
  strcpy(codeDocument, rv.codeDocument);
  strcpy(noeud, 		   rv.noeud);
  strcpy(type,   	 	   rv.type);
  strcpy(lexique, 	   rv.lexique);
  strcpy(complement, 	 rv.complement);
  strcpy(certitude,  	 rv.certitude);
  strcpy(pluriel,    	 rv.pluriel);
  strcpy(tran_new, 	   rv.tran_new);
  strcpy(tran_del, 	   rv.tran_del);
  strcpy(unit, 	       rv.unit);
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation de NSPatPaDatData
//---------------------------------------------------------------------------
NSPatPaDatData&
NSPatPaDatData::operator=(const NSPatPaDatData& rv)
{
  if (this == &rv)
    return *this ;

  strcpy(codePatient,  rv.codePatient);
  strcpy(codeDocument, rv.codeDocument);
  strcpy(noeud, 		   rv.noeud);
  strcpy(type,   	 	   rv.type);
  strcpy(lexique, 	   rv.lexique);
  strcpy(complement, 	 rv.complement);
  strcpy(certitude,  	 rv.certitude);
  strcpy(pluriel,    	 rv.pluriel);
  strcpy(tran_new, 	   rv.tran_new);
  strcpy(tran_del, 	   rv.tran_del);
  strcpy(unit, 	       rv.unit);

	return *this ;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison de NSPatPaDatData
//---------------------------------------------------------------------------
int
NSPatPaDatData::operator==(const NSPatPaDatData& o)
{
	if ((strcmp(codePatient,    o.codePatient)  == 0) &&
      (strcmp(codeDocument,   o.codeDocument) == 0) &&
      (strcmp(noeud,          o.noeud)        == 0) &&
      (strcmp(type,           o.type)         == 0) &&
      (strcmp(lexique,   	    o.lexique) 	    == 0) &&
      (strcmp(complement,     o.complement)   == 0) &&
      (strcmp(unit,           o.unit)         == 0) &&
      (strcmp(certitude, 	    o.certitude)    == 0) &&
      (strcmp(pluriel,   	    o.pluriel) 	    == 0))
    return 1 ;
	else
		return 0 ;
}
//---------------------------------------------------------------------------
//  Met � 0 les variables de NSPatPaDatData//---------------------------------------------------------------------------
void
NSPatPaDatData::metAZero()
{
	//
	// Met les champs de donn�es � z�ro
	//
  memset(codePatient,	 0, PAT_NSS_LEN + 1);
  memset(codeDocument, 0, DOC_CODE_DOCUM_LEN + 1);
  memset(noeud, 		   0, PPD_NOEUD_LEN + 1);
  memset(type, 		     0, BASE_TYPE_LEN + 1);
  memset(lexique, 	   0, BASE_LEXIQUE_LEN + 1);
  memset(complement, 	 0, BASE_COMPLEMENT_LEN + 1);
  memset(certitude, 	 0, BASE_CERTITUDE_LEN + 1);
  memset(pluriel, 	   0, BASE_PLURIEL_LEN + 1);
  memset(tran_new, 	   0, TRAN_CODE_LEN + 1);
  memset(tran_del, 	   0, TRAN_CODE_LEN + 1);
  memset(unit, 	       0, BASE_UNIT_LEN + 1);
}

//---------------------------------------------------------------------------
//  Retourne le type de l'�l�ment : Actif ou Historique
//---------------------------------------------------------------------------
int
NSPatPaDatData::getType()
{
    switch (type[0])
    {
   	    case 'A' : return ppdActif;
		case 'H' : return ppdHistorique;
	}
    return ppdIndef;
}

//---------------------------------------------------------------------------
//  Instancie le type de l'�l�ment : Actif ou Historique
//---------------------------------------------------------------------------
void
NSPatPaDatData::setType(int newType)
{
    switch (newType)
    {
   	    case ppdActif      : strcpy(type, "A"); break;
		case ppdHistorique : strcpy(type, "H"); break;
    }
}

/*************************************************************************/
// NSPatPaDat
/*************************************************************************/

//---------------------------------------------------------------------------
//  Constructeur
//---------------------------------------------------------------------------
NSPatPaDat::NSPatPaDat(NSSuper* pSuper) : NSFiche(pSuper)
{
try
{
  pDonnees = new NSPatPaDatData() ;
}
catch (...)
{
  erreur("Exception NSPatPaDat ctor.", standardError, 0);
}
}

//---------------------------------------------------------------------------//  Destructeur
//---------------------------------------------------------------------------
NSPatPaDat::~NSPatPaDat()
{
	delete pDonnees;
}

//---------------------------------------------------------------------------
//  Transf�re le contenu de pRecBuff dans les variables de la fiche
//---------------------------------------------------------------------------
void
NSPatPaDat::alimenteFiche()
{
  alimenteChamp(pDonnees->codePatient,  PPD_PAT_FIELD,		    PAT_NSS_LEN);
  alimenteChamp(pDonnees->codeDocument, PPD_DOCU_FIELD,		    DOC_CODE_DOCUM_LEN);
  alimenteChamp(pDonnees->noeud, 		    PPD_NOEUD_FIELD,		  PPD_NOEUD_LEN);
  alimenteChamp(pDonnees->type,		      PPD_TYPE_FIELD,		    BASE_TYPE_LEN);
  alimenteChamp(pDonnees->lexique,	    PPD_LEXIQUE_FIELD,	  BASE_LEXIQUE_LEN);
  alimenteChamp(pDonnees->complement,	  PPD_COMPLEMENT_FIELD, BASE_COMPLEMENT_LEN);
  alimenteChamp(pDonnees->certitude,	  PPD_CERTITUDE_FIELD,  BASE_CERTITUDE_LEN);
  alimenteChamp(pDonnees->pluriel,	    PPD_PLURIEL_FIELD,	  BASE_PLURIEL_LEN);
  alimenteChamp(pDonnees->tran_new,	    PPD_TRAN_NEW_FIELD,	  TRAN_CODE_LEN);
  alimenteChamp(pDonnees->tran_del,	    PPD_TRAN_DEL_FIELD,	  TRAN_CODE_LEN);
#ifdef _MUE
  alimenteChamp(pDonnees->unit,	        PPD_UNIT_FIELD,       BASE_UNIT_LEN);
#endif
}

//---------------------------------------------------------------------------
//  Transf�re le contenu des valeurs de la fiche dans pRecBuff
//---------------------------------------------------------------------------
void
NSPatPaDat::videFiche()
{
    videChamp(pDonnees->codePatient,  PPD_PAT_FIELD,		PAT_NSS_LEN);
    videChamp(pDonnees->codeDocument, PPD_DOCU_FIELD,		DOC_CODE_DOCUM_LEN);
    videChamp(pDonnees->noeud, 		  PPD_NOEUD_FIELD,		PPD_NOEUD_LEN);
    videChamp(pDonnees->type,		  PPD_TYPE_FIELD,		BASE_TYPE_LEN);
    videChamp(pDonnees->lexique,	  PPD_LEXIQUE_FIELD,	BASE_LEXIQUE_LEN);
    videChamp(pDonnees->complement,	  PPD_COMPLEMENT_FIELD, BASE_COMPLEMENT_LEN);
    videChamp(pDonnees->certitude,	  PPD_CERTITUDE_FIELD,  BASE_CERTITUDE_LEN);
    videChamp(pDonnees->pluriel,	  PPD_PLURIEL_FIELD,	BASE_PLURIEL_LEN);
    videChamp(pDonnees->tran_new,	  PPD_TRAN_NEW_FIELD,	TRAN_CODE_LEN);
    videChamp(pDonnees->tran_del,	  PPD_TRAN_DEL_FIELD,	TRAN_CODE_LEN);
#ifdef _MUE
    videChamp(pDonnees->unit,	      PPD_UNIT_FIELD,	    BASE_UNIT_LEN);
#endif
}

//---------------------------------------------------------------------------
//  Ouvre la table
//---------------------------------------------------------------------------
DBIResult
NSPatPaDat::open()
{
#ifndef _MUE
    char tableName[] = "NSPATDAT.DB";
#else
    char tableName[] = "NSMDAT.DB";
#endif
	//
	// Appelle la fonction open() de la classe de base pour ouvrir
	// l'index primaire
	//
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL);
	return(lastError);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool
NSPatPaDat::Create()
{
	return TRUE;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool
NSPatPaDat::Modify()
{
	return TRUE;
}

//***************************************************************************
// Impl�mentation des m�thodes NSPatPaDatInfo
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur par d�faut
//---------------------------------------------------------------------------
NSPatPaDatInfo::NSPatPaDatInfo()
{
try
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSPatPaDatData();
}
catch (...)
{
    erreur("Exception NSPatPaDatInfo ctor.", standardError, 0);
}
}

//---------------------------------------------------------------------------//  Constructeur � partir d'un NSPatPatho
//---------------------------------------------------------------------------
NSPatPaDatInfo::NSPatPaDatInfo(const NSPatPaDat* pPatPaDat)
{
try
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSPatPaDatData();
	//
	// Copie les valeurs du NSDocument
	//
	*pDonnees = *(pPatPaDat->pDonnees);
}
catch (...)
{
    erreur("Exception NSPatPaDatInfo ctor(NSPatPaDat*).", standardError, 0);
}
}

//---------------------------------------------------------------------------//  Constructeur copie
//---------------------------------------------------------------------------
NSPatPaDatInfo::NSPatPaDatInfo(const NSPatPaDatInfo& rv)
{
try
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSPatPaDatData(*(rv.pDonnees));
}
catch (...)
{
    erreur("Exception NSPatPaDatInfo copy ctor.", standardError, 0);
}
}

//---------------------------------------------------------------------------//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSPatPaDatInfo&
NSPatPaDatInfo::operator=(const NSPatPaDatInfo& src)
{
  if (&src == this)
		return *this ;

	*pDonnees = *(src.pDonnees);

	return *this;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison
//---------------------------------------------------------------------------
int
NSPatPaDatInfo::operator==(const NSPatPaDatInfo& o)
{
	return (*pDonnees == *(o.pDonnees)) ;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison avec un NSPatPathoInfo
//---------------------------------------------------------------------------
int
NSPatPaDatInfo::operator==(const NSPatPathoInfo& o)
{
	if ((strcmp(pDonnees->noeud,      o.getNodeID().c_str())     == 0) &&
      (strcmp(pDonnees->lexique,    o.getLexique().c_str())    == 0) &&
      (strcmp(pDonnees->complement, o.getComplement().c_str()) == 0) &&
      (strcmp(pDonnees->certitude,  o.getCertitude().c_str())  == 0) &&
      (strcmp(pDonnees->pluriel,    o.getPluriel().c_str())    == 0))
    return 1 ;
	else
		return 0 ;
}

//---------------------------------------------------------------------------
//  Destructeur
//---------------------------------------------------------------------------
NSPatPaDatInfo::~NSPatPaDatInfo()
{
  delete pDonnees ;
}

// -------------------------------------------------------------------------
// -------------------- METHODES DE NSPatPaLocArray ------------------------
// -------------------------------------------------------------------------
NSPatPaLocArray::NSPatPaLocArray(NSSuper* pSuper)
                :NSPatPaLocInfoArray(), NSSuperRoot(pSuper)
{}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSPatPaLocArray::NSPatPaLocArray(const NSPatPaLocArray& rv)
                :NSPatPaLocInfoArray(), NSSuperRoot(rv._pSuper)
{
try
{
  if (false == rv.empty())
    for (PatPaLocConstIter i = rv.begin() ; rv.end() != i ; i++)
      push_back(new NSPatPaLocInfo(*(*i))) ;
}
catch (...)
{
  erreur("Exception NSPatPaDatInfo copy ctor.", standardError, 0) ;
}
}

//---------------------------------------------------------------------------
//  Destructeur
//---------------------------------------------------------------------------
void
NSPatPaLocArray::vider()
{
  if (empty())
    return ;

  for (PatPaLocIter i = begin(); i != end(); )
  {
    delete *i ;
    erase(i) ;
  }
}
NSPatPaLocArray::~NSPatPaLocArray(){
	vider() ;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSPatPaLocArray&
NSPatPaLocArray::operator=(const NSPatPaLocArray& src)
{
try
{
	if (this == &src)
		return *this ;

	//
	// Effacement des �l�ments d�j� contenus dans le vecteur destination
	//
	vider() ;
	//
	// Copie et insertion des �l�ments de la source
	//
	if (false == src.empty())
		for (PatPaLocConstIter it = src.begin() ; src.end() != it ; it++)
			push_back(new NSPatPaLocInfo(*(*it))) ;

	return *this ;
}
catch (...)
{
	erreur("Exception NSPatPaLocArray = operator.", standardError, 0) ;
	return *this ;
}
}

//---------------------------------------------------------------------------//  Ajout d'un �l�ment � l'array
//---------------------------------------------------------------------------
bool
NSPatPaLocArray::ajouteElement(NSPatPaLocInfo* pPatPatho)
{
  if ((NSPatPaLocInfo*) NULL == pPatPatho)
    return false ;

	push_back(pPatPatho) ;

  return true ;
}

//***************************************************************************
// Impl�mentation des m�thodes NSPatPaLoc
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur copie de NSPatPaLocData
//---------------------------------------------------------------------------
NSPatPaLocData::NSPatPaLocData(const NSPatPaLocData& rv)
{
	strcpy(codePatient, 	   rv.codePatient) ;
  strcpy(codeDocument, 	   rv.codeDocument) ;
  strcpy(transaction, 	   rv.transaction) ;
  strcpy(noeud, 			     rv.noeud) ;
  strcpy(codeLocalisation, rv.codeLocalisation) ;
  strcpy(visible, 		     rv.visible) ;
  strcpy(interet, 		     rv.interet) ;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation de NSPatPaLocData
//---------------------------------------------------------------------------
NSPatPaLocData&
NSPatPaLocData::operator=(const NSPatPaLocData& src)
{
  if (&src == this)
		return *this ;

	strcpy(codePatient, 	   src.codePatient) ;
  strcpy(codeDocument, 	   src.codeDocument) ;
  strcpy(transaction, 	   src.transaction) ;
  strcpy(noeud, 			     src.noeud) ;
  strcpy(codeLocalisation, src.codeLocalisation) ;
  strcpy(visible, 		     src.visible) ;
  strcpy(interet, 		     src.interet) ;

	return *this ;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison de NSPatPaLocData
//---------------------------------------------------------------------------
int
NSPatPaLocData::operator==(const NSPatPaLocData& o)
{
	if ((strcmp(codePatient,  		  o.codePatient) 	    == 0) &&
        (strcmp(codeDocument, 		o.codeDocument) 	  == 0) &&
        (strcmp(transaction,  		o.transaction) 	    == 0) &&
        (strcmp(noeud, 		  		  o.noeud) 			      == 0) &&
        (strcmp(codeLocalisation,	o.codeLocalisation) == 0) &&
        (strcmp(visible,   	  		o.visible) 		    	== 0))
		return 1 ;
	else
		return 0 ;
}

//---------------------------------------------------------------------------
//  Met � 0 les variables de NSPatPaLocData
//---------------------------------------------------------------------------
void
NSPatPaLocData::metAZero()
{
	//
	// Met les champs de donn�es � z�ro
	//
  memset(codePatient,		   0, PAT_NSS_LEN + 1) ;
  memset(codeDocument, 	   0, DOC_CODE_DOCUM_LEN + 1) ;
  memset(transaction, 	   0, TRAN_CODE_LEN + 1) ;
  memset(noeud, 			     0, PPD_NOEUD_LEN + 1) ;
  memset(codeLocalisation, 0, BASE_LOCALISATION_LEN + 1) ;
	memset(visible, 		     0, BASE_VISIBLE_LEN + 1) ;
  memset(interet, 	       0, BASE_INTERET_LEN + 1) ;
}

/*************************************************************************/
// NSPatPaLoc
/*************************************************************************/

//---------------------------------------------------------------------------
//  Constructeur
//---------------------------------------------------------------------------
NSPatPaLoc::NSPatPaLoc(NSSuper* pSuper)
           :NSFiche(pSuper)
{
try
{
	pDonnees = new NSPatPaLocData() ;
}
catch (...)
{
	erreur("Exception NSPatPaLoc ctor.", standardError, 0) ;
}
}

//---------------------------------------------------------------------------
//  Destructeur
//---------------------------------------------------------------------------
NSPatPaLoc::~NSPatPaLoc()
{
	delete pDonnees ;
}

//---------------------------------------------------------------------------
//  Transf�re le contenu de pRecBuff dans les variables de la fiche
//---------------------------------------------------------------------------
void
NSPatPaLoc::alimenteFiche()
{
    alimenteChamp(pDonnees->codePatient,  	  PPL_PAT_FIELD,	 PAT_NSS_LEN);
    alimenteChamp(pDonnees->codeDocument, 	  PPL_DOCU_FIELD,	 DOC_CODE_DOCUM_LEN);
    alimenteChamp(pDonnees->transaction,  	  PPL_TRAN_FIELD,	 TRAN_CODE_LEN);
    alimenteChamp(pDonnees->noeud, 		  	  PPL_NOEUD_FIELD,	 PPD_NOEUD_LEN);
    alimenteChamp(pDonnees->codeLocalisation, PPL_LOC_FIELD,	 BASE_LOCALISATION_LEN);
    alimenteChamp(pDonnees->visible,		  PPL_VISIBLE_FIELD, BASE_VISIBLE_LEN);
    alimenteChamp(pDonnees->interet,	      PPL_INTERET_FIELD, BASE_INTERET_LEN);
}

//---------------------------------------------------------------------------
//  Transf�re le contenu des valeurs de la fiche dans pRecBuff
//---------------------------------------------------------------------------
void
NSPatPaLoc::videFiche()
{
    videChamp(pDonnees->codePatient,  	  PPL_PAT_FIELD,	 PAT_NSS_LEN);
    videChamp(pDonnees->codeDocument, 	  PPL_DOCU_FIELD,	 DOC_CODE_DOCUM_LEN);
    videChamp(pDonnees->transaction,  	  PPL_TRAN_FIELD,	 TRAN_CODE_LEN);
    videChamp(pDonnees->noeud, 		  	  PPL_NOEUD_FIELD,	 PPD_NOEUD_LEN);
    videChamp(pDonnees->codeLocalisation, PPL_LOC_FIELD,	 BASE_LOCALISATION_LEN);
    videChamp(pDonnees->visible,		  PPL_VISIBLE_FIELD, BASE_VISIBLE_LEN);
    videChamp(pDonnees->interet,	      PPL_INTERET_FIELD, BASE_INTERET_LEN);
}

//---------------------------------------------------------------------------
//  Ouvre la table
//---------------------------------------------------------------------------
DBIResult
NSPatPaLoc::open()
{
#ifndef _MUE
    char tableName[] = "NSPATLOC.DB";
#else
    char tableName[] = "NSMLOC.DB";
#endif
	//
	// Appelle la fonction open() de la classe de base pour ouvrir
	// l'index primaire
	//
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL);
	return(lastError);
}

//---------------------------------------------------------------------------////---------------------------------------------------------------------------
bool
NSPatPaLoc::Create()
{
    return TRUE;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool
NSPatPaLoc::Modify()
{
    return TRUE;
}

//***************************************************************************
// Impl�mentation des m�thodes NSPatPaLocInfo
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur par d�faut
//---------------------------------------------------------------------------
NSPatPaLocInfo::NSPatPaLocInfo()
{
try
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSPatPaLocData();
}
catch (...)
{
	erreur("Exception NSPatPaLocInfo ctor.", standardError, 0) ;
}
}

//---------------------------------------------------------------------------//  Constructeur � partir d'un NSPatPaLoc
//---------------------------------------------------------------------------
NSPatPaLocInfo::NSPatPaLocInfo(const NSPatPaLoc* pPatPaLoc)
{
try
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSPatPaLocData();
	//
	// Copie les valeurs du NSDocument
	//
	*pDonnees = *(pPatPaLoc->pDonnees);
}
catch (...)
{
	erreur("Exception NSPatPaLocInfo ctor(NSPatLoc*).", standardError, 0) ;
}
}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSPatPaLocInfo::NSPatPaLocInfo(const NSPatPaLocInfo& rv)
{
try
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSPatPaLocData(*(rv.pDonnees));
}
catch (...)
{
    erreur("Exception NSPatPaLocInfo copy ctor.", standardError, 0);
}
}

//---------------------------------------------------------------------------//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSPatPaLocInfo&
NSPatPaLocInfo::operator=(const NSPatPaLocInfo& src)
{
	if (this == &src)
		return *this ;

	*pDonnees = *(src.pDonnees);

	return *this;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison
//---------------------------------------------------------------------------
int
NSPatPaLocInfo::operator==(const NSPatPaLocInfo& o)
{
	return (*pDonnees == *(o.pDonnees));
}

//---------------------------------------------------------------------------
//  Destructeur
//---------------------------------------------------------------------------
NSPatPaLocInfo::~NSPatPaLocInfo()
{
  	delete pDonnees;
}

