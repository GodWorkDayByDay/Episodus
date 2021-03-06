// -----------------------------------------------------------------------------
//    EPTABLES.CPP
//    NAUTILUS juillet 2001
//
//    Implementation des objets de base de donnees
// -----------------------------------------------------------------------------

#include <cstring>
#include <fstream>

#include "nsepisod/eptables.h"

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/superLus.h"
#else
  #include "nautilus\nssuper.h"
#endif

#include "nssavoir/nspatbas.h"

/*
// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiContact
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContactData::NSEpiContactData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContactData::NSEpiContactData(NSEpiContactData& rv)
{
	strcpy(patient, 		  rv.patient) ;
	strcpy(code,  		    rv.code) ;
	strcpy(dateHeureDeb, 	rv.dateHeureDeb) ;
	strcpy(dateHeureFin,  rv.dateHeureFin) ;
	strcpy(session,  		  rv.session) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContactData::~NSEpiContactData()
{
}


// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiContactData&
NSEpiContactData::operator=(NSEpiContactData src)
{
  if (this == &src)
    return *this ;

	strcpy(patient, 		  src.patient) ;
	strcpy(code,  		    src.code) ;
	strcpy(dateHeureDeb, 	src.dateHeureDeb) ;
	strcpy(dateHeureFin,  src.dateHeureFin) ;
	strcpy(session,  		  src.session) ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContactData::operator==(const NSEpiContactData& o)
{
	if ((strcmp(patient, o.patient) == 0) &&
      (strcmp(code,    o.code)    == 0))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContactData::metAZero()
{
	// Met les champs de donn�es � z�ro
	memset(patient, 	  	0, CONTACT_PATIENT_LEN + 1) ;
	memset(code,   		    0, CONTACT_CODE_LEN + 1) ;
	memset(dateHeureDeb, 	0, CONTACT_DATEHEURE_DEB_LEN + 1) ;
	memset(dateHeureFin,  0, CONTACT_DATEHEURE_FIN_LEN + 1) ;
	memset(session,  		  0, CONTACT_SESSION_LEN + 1) ;
}

// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContact::NSEpiContact(NSContexte *pCtx)
  : NSEpiContactInfo(),
    NSFiche(pCtx)
{
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContact::NSEpiContact(NSEpiContact& rv)
  : NSEpiContactInfo(rv),
    NSFiche(rv.pContexte)
{
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContact::~NSEpiContact()
{
}


// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContact::alimenteFiche()
{
  alimenteChamp(pDonnees->patient, 	    CONTACT_PATIENT_FIELD,  	    CONTACT_PATIENT_LEN) ;
  alimenteChamp(pDonnees->code, 		    CONTACT_CODE_FIELD, 	        CONTACT_CODE_LEN) ;
  alimenteChamp(pDonnees->dateHeureDeb, CONTACT_DATEHEURE_DEB_FIELD,  CONTACT_DATEHEURE_DEB_LEN) ;
  alimenteChamp(pDonnees->dateHeureFin, CONTACT_DATEHEURE_FIN_FIELD,  CONTACT_DATEHEURE_FIN_LEN) ;
  alimenteChamp(pDonnees->session,  	  CONTACT_SESSION_FIELD, 	      CONTACT_SESSION_LEN) ;
}


// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiContact::videFiche()
{
	videChamp(pDonnees->patient, 	    CONTACT_PATIENT_FIELD,  	    CONTACT_PATIENT_LEN) ;
  videChamp(pDonnees->code, 		    CONTACT_CODE_FIELD, 	        CONTACT_CODE_LEN) ;
  videChamp(pDonnees->dateHeureDeb, CONTACT_DATEHEURE_DEB_FIELD,  CONTACT_DATEHEURE_DEB_LEN) ;
  videChamp(pDonnees->dateHeureFin, CONTACT_DATEHEURE_FIN_FIELD,  CONTACT_DATEHEURE_FIN_LEN) ;
  videChamp(pDonnees->session,  	  CONTACT_SESSION_FIELD, 	      CONTACT_SESSION_LEN) ;
}


// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiContact::open()
{
	char tableName[] = "CONTACT.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
  lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return(lastError) ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContact::Create()
{
	return true ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContact::Modify()
{
	return true ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContact&
NSEpiContact::operator=(NSEpiContact src)
{
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContact::operator==(const NSEpiContact& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiContactInfo::NSEpiContactInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContactData() ;
}


// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiContact
// -----------------------------------------------------------------------------
NSEpiContactInfo::NSEpiContactInfo(NSEpiContact *pContact)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContactData() ;

	// Copie les valeurs du NSEpiContact
	*pDonnees = *(pContact->pDonnees) ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContactInfo::NSEpiContactInfo(NSEpiContactInfo& rv)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContactData() ;

	// Copie les valeurs du NSEpiContactInfo d'origine
	*pDonnees = *(rv.pDonnees) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContactInfo::~NSEpiContactInfo()
{
	delete pDonnees ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContactInfo&
NSEpiContactInfo::operator=(NSEpiContactInfo src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContactInfo::operator==(const NSEpiContactInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiContElmt
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContElmtData::NSEpiContElmtData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContElmtData::NSEpiContElmtData(NSEpiContElmtData& rv)
{
	strcpy(contact, 	rv.contact) ;
	strcpy(code,  		rv.code) ;
	strcpy(preoccup,  rv.preoccup) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContElmtData::~NSEpiContElmtData()
{
}


// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiContElmtData&
NSEpiContElmtData::operator=(NSEpiContElmtData src)
{
  if (this == &src)
    return *this ;

	strcpy(contact, 	src.contact) ;
	strcpy(code,  		src.code) ;
	strcpy(preoccup,  src.preoccup) ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContElmtData::operator==(const NSEpiContElmtData& o)
{
	if ((strcmp(contact, o.contact) == 0) &&
      (strcmp(code,    o.code)    == 0))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContElmtData::metAZero()
{
	// Met les champs de donn�es � z�ro
	memset(contact, 	0, CONTELMT_CONTACT_LEN + 1) ;
	memset(code,   		0, CONTELMT_CODE_LEN + 1) ;
	memset(preoccup, 	0, CONTELMT_PREOCCUP_LEN + 1) ;
}


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContElmt::NSEpiContElmt(NSContexte *pCtx)
  : NSEpiContElmtInfo(),
    NSFiche(pCtx)
{
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContElmt::NSEpiContElmt(NSEpiContElmt& rv)
  : NSEpiContElmtInfo(rv),
    NSFiche(rv.pContexte)
{
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContElmt::~NSEpiContElmt()
{
}


// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContElmt::alimenteFiche()
{
  alimenteChamp(pDonnees->contact,  CONTELMT_CONTACT_FIELD,   CONTELMT_CONTACT_LEN) ;
  alimenteChamp(pDonnees->code, 	  CONTELMT_CODE_FIELD, 	    CONTELMT_CODE_LEN) ;
  alimenteChamp(pDonnees->preoccup, CONTELMT_PREOCCUP_FIELD,  CONTELMT_PREOCCUP_LEN) ;
}


// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiContElmt::videFiche()
{
	videChamp(pDonnees->contact,  CONTELMT_CONTACT_FIELD,   CONTELMT_CONTACT_LEN) ;
  videChamp(pDonnees->code, 	  CONTELMT_CODE_FIELD, 	    CONTELMT_CODE_LEN) ;
  videChamp(pDonnees->preoccup, CONTELMT_PREOCCUP_FIELD,  CONTELMT_PREOCCUP_LEN) ;
}


// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiContElmt::open()
{
	char tableName[] = "CON_ELMT.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir
	// l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
  return (lastError) ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContElmt::Create()
{
	return true ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContElmt::Modify()
{
	return true ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContElmt&
NSEpiContElmt::operator=(NSEpiContElmt src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContElmt::operator==(const NSEpiContElmt& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiContElmtInfo::NSEpiContElmtInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContElmtData() ;
}


// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiContElmt
// -----------------------------------------------------------------------------
NSEpiContElmtInfo::NSEpiContElmtInfo(NSEpiContElmt *pContact)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContElmtData() ;

	// Copie les valeurs du NSEpiContElmt
	*pDonnees = *(pContact->pDonnees) ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContElmtInfo::NSEpiContElmtInfo(NSEpiContElmtInfo& rv)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContElmtData() ;

	// Copie les valeurs du NSEpiContElmtInfo d'origine
	*pDonnees = *(rv.pDonnees) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContElmtInfo::~NSEpiContElmtInfo()
{
	delete pDonnees ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContElmtInfo&
NSEpiContElmtInfo::operator=(NSEpiContElmtInfo src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContElmtInfo::operator==(const NSEpiContElmtInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiContClass
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContClasData::NSEpiContClasData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContClasData::NSEpiContClasData(NSEpiContClasData& rv)
{
	strcpy(contElement, rv.contElement) ;
	strcpy(numero,      rv.numero) ;
	strcpy(position,    rv.position) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContClasData::~NSEpiContClasData()
{
}


// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiContClasData&
NSEpiContClasData::operator=(NSEpiContClasData src)
{
  if (this == &src)
    return *this ;

	strcpy(contElement, src.contElement) ;
	strcpy(numero,      src.numero) ;
	strcpy(position,    src.position) ;

	return *this ;
}


// -----------------------------------------------------------------------------
//  Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContClasData::operator==(const NSEpiContClasData& o)
{
	if ((strcmp(contElement, o.contElement) == 0) &&
      (strcmp(numero,      o.numero)      == 0))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContClasData::metAZero()
{
	// Met les champs de donn�es � z�ro
	memset(contElement, 0, CONTCLAS_CONTELMT_LEN + 1) ;
	memset(numero,   	  0, CONTCLAS_NUMERO_LEN + 1) ;
	memset(position, 	  0, CONTCLAS_POSITION_LEN + 1) ;
}

// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContClass::NSEpiContClass(NSContexte *pCtx)
  : NSEpiContClasInfo(),
    NSFiche(pCtx)
{
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContClass::NSEpiContClass(NSEpiContClass& rv)
  : NSEpiContClasInfo(rv),
    NSFiche(rv.pContexte)
{
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContClass::~NSEpiContClass()
{
}

// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContClass::alimenteFiche()
{
  alimenteChamp(pDonnees->contElement,  CONTCLAS_CONTELMT_FIELD,  CONTCLAS_CONTELMT_LEN) ;
  alimenteChamp(pDonnees->numero, 		  CONTCLAS_NUMERO_FIELD, 	  CONTCLAS_NUMERO_LEN) ;
  alimenteChamp(pDonnees->position,     CONTCLAS_POSITION_FIELD,  CONTCLAS_POSITION_LEN) ;
}

// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiContClass::videFiche()
{
	videChamp(pDonnees->contElement,  CONTCLAS_CONTELMT_FIELD,  CONTCLAS_CONTELMT_LEN) ;
  videChamp(pDonnees->numero, 		  CONTCLAS_NUMERO_FIELD,    CONTCLAS_NUMERO_LEN) ;
  videChamp(pDonnees->position,     CONTCLAS_POSITION_FIELD,  CONTCLAS_POSITION_LEN) ;
}


// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiContClass::open()
{
	char tableName[] = "CON_CLAS.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return (lastError) ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContClass::Create()
{
  return true ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContClass::Modify()
{
	return true ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContClass&
NSEpiContClass::operator=(NSEpiContClass src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContClass::operator==(const NSEpiContClass& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiContClasInfo::NSEpiContClasInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContClasData() ;
}


// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiContClass
// -----------------------------------------------------------------------------
NSEpiContClasInfo::NSEpiContClasInfo(NSEpiContClass *pContact)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContClasData() ;

	// Copie les valeurs du NSEpiContClass
	*pDonnees = *(pContact->pDonnees) ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContClasInfo::NSEpiContClasInfo(NSEpiContClasInfo& rv)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContClasData() ;

	// Copie les valeurs du NSEpiContClasInfo d'origine
	*pDonnees = *(rv.pDonnees) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContClasInfo::~NSEpiContClasInfo()
{
	delete pDonnees ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContClasInfo&
NSEpiContClasInfo::operator=(NSEpiContClasInfo src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int

NSEpiContClasInfo::operator==(const NSEpiContClasInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Impl�mentation des m�thodes NSEpiContCode
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContCodeData::NSEpiContCodeData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContCodeData::NSEpiContCodeData(NSEpiContCodeData& rv)
{
	strcpy(contElement,     rv.contElement) ;
	strcpy(numero,          rv.numero) ;
	strcpy(classification,  rv.classification) ;
	strcpy(code,            rv.code) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContCodeData::~NSEpiContCodeData()
{
}


// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiContCodeData&
NSEpiContCodeData::operator=(NSEpiContCodeData src)
{
  if (this == &src)
    return *this ;

	strcpy(contElement,     src.contElement) ;
	strcpy(numero,          src.numero) ;
	strcpy(classification,  src.classification) ;
	strcpy(code,            src.code) ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContCodeData::operator==(const NSEpiContCodeData& o)
{
	if ((strcmp(contElement, o.contElement) == 0) &&
      (strcmp(numero,      o.numero)      == 0))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContCodeData::metAZero()
{
	// Met les champs de donn�es � z�ro
	memset(contElement, 	  0, CONTCODE_CONTELMT_LEN + 1) ;
	memset(numero,   		    0, CONTCODE_NUMERO_LEN + 1) ;
	memset(classification,  0, CONTCODE_CLASSIF_LEN + 1) ;
	memset(code,  		      0, CONTCODE_CODE_LEN + 1) ;
}

// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiContCode::NSEpiContCode(NSContexte *pCtx)
              : NSEpiContCodeInfo(), NSFiche(pCtx)
{
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContCode::NSEpiContCode(NSEpiContCode& rv)
              : NSEpiContCodeInfo(rv), NSFiche(rv.pContexte)
{
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContCode::~NSEpiContCode()
{
}

// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiContCode::alimenteFiche()
{
  alimenteChamp(pDonnees->contElement, 	  CONTCODE_CONTELMT_FIELD,  CONTCODE_CONTELMT_LEN) ;
  alimenteChamp(pDonnees->numero, 		    CONTCODE_NUMERO_FIELD, 	  CONTCODE_NUMERO_LEN) ;
  alimenteChamp(pDonnees->classification, CONTCODE_CLASSIF_FIELD,   CONTCODE_CLASSIF_LEN) ;
  alimenteChamp(pDonnees->code,  	        CONTCODE_CODE_FIELD, 	    CONTCODE_CODE_LEN) ;
}

// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiContCode::videFiche()
{
	videChamp(pDonnees->contElement, 	  CONTCODE_CONTELMT_FIELD,  CONTCODE_CONTELMT_LEN) ;
  videChamp(pDonnees->numero, 		    CONTCODE_NUMERO_FIELD,    CONTCODE_NUMERO_LEN) ;
  videChamp(pDonnees->classification, CONTCODE_CLASSIF_FIELD,   CONTCODE_CLASSIF_LEN) ;
  videChamp(pDonnees->code,  	        CONTCODE_CODE_FIELD,      CONTCODE_CODE_LEN) ;
}

// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiContCode::open()
{
	char tableName[] = "CON_CODE.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return (lastError) ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContCode::Create()
{
	return true ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiContCode::Modify()
{
	return true ;
}

// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContCode&
NSEpiContCode::operator=(NSEpiContCode src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContCode::operator==(const NSEpiContCode& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiContCodeInfo::NSEpiContCodeInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContCodeData() ;
}


// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiContCode
// -----------------------------------------------------------------------------
NSEpiContCodeInfo::NSEpiContCodeInfo(NSEpiContCode *pContact)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContCodeData() ;

	// Copie les valeurs du NSEpiContCode
	*pDonnees = *(pContact->pDonnees) ;
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiContCodeInfo::NSEpiContCodeInfo(NSEpiContCodeInfo& rv)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiContCodeData() ;

	// Copie les valeurs du NSEpiContCodeInfo d'origine
	*pDonnees = *(rv.pDonnees) ;
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiContCodeInfo::~NSEpiContCodeInfo()
{
	delete pDonnees ;
}

// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiContCodeInfo&
NSEpiContCodeInfo::operator=(NSEpiContCodeInfo src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiContCodeInfo::operator==(const NSEpiContCodeInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiPreoccup
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiPreoccupData::NSEpiPreoccupData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiPreoccupData::NSEpiPreoccupData(NSEpiPreoccupData& rv)
{
	strcpy(patient,     rv.patient) ;
	strcpy(code,        rv.code) ;
	strcpy(revision,    rv.revision) ;
	strcpy(session,     rv.session) ;
	strcpy(lexique,  	  rv.lexique) ;
	strcpy(complement,  rv.complement) ;
	strcpy(dateCree,    rv.dateCree) ;
	strcpy(dateFerme,  	rv.dateFerme) ;
	strcpy(actif,  		  rv.actif) ;
	strcpy(recurrent,   rv.recurrent) ;
	strcpy(mere,  		  rv.mere) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiPreoccupData::~NSEpiPreoccupData()
{
}


// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiPreoccupData&
NSEpiPreoccupData::operator=(NSEpiPreoccupData src)
{
  if (this == &src)
    return *this ;

	strcpy(patient,     src.patient) ;
	strcpy(code,        src.code) ;
	strcpy(revision,    src.revision) ;
	strcpy(session,     src.session) ;
	strcpy(lexique,  	  src.lexique) ;
	strcpy(complement,  src.complement) ;
	strcpy(dateCree,    src.dateCree) ;
	strcpy(dateFerme,  	src.dateFerme) ;
	strcpy(actif,  		  src.actif) ;
	strcpy(recurrent,  	src.recurrent) ;
	strcpy(mere,  		  src.mere) ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiPreoccupData::operator==(const NSEpiPreoccupData& o)
{
	if ((strcmp(patient,  o.patient)  == 0) &&
      (strcmp(code,     o.code)     == 0) &&
      (strcmp(revision, o.revision) == 0))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiPreoccupData::metAZero()
{
	// Met les champs de donn�es � z�ro
	memset(patient,     0, PREOCCUP_PATIENT_LEN + 1) ;
	memset(code,   		  0, PREOCCUP_CODE_LEN + 1) ;
	memset(revision, 	  0, PREOCCUP_REVISION_LEN + 1) ;
	memset(session,     0, PREOCCUP_SESSION_LEN + 1) ;
	memset(lexique,  	  0, PREOCCUP_LEXIQUE_LEN + 1) ;
	memset(complement,  0, PREOCCUP_COMPLEMENT_LEN + 1) ;
	memset(dateCree,    0, PREOCCUP_DATE_CREE_LEN + 1) ;
	memset(dateFerme,  	0, PREOCCUP_DATE_FERME_LEN + 1) ;
	memset(actif,  		  0, PREOCCUP_ACTIF_LEN + 1) ;
	memset(recurrent,  	0, PREOCCUP_RECURRENT_LEN + 1) ;
	memset(mere,  		  0, PREOCCUP_MERE_LEN + 1) ;
}

// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiPreoccup::NSEpiPreoccup(NSContexte *pCtx)
  : NSEpiPreoccupInfo(),
    NSFiche(pCtx)
{
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiPreoccup::NSEpiPreoccup(NSEpiPreoccup& rv)
  : NSEpiPreoccupInfo(rv),
    NSFiche(rv.pContexte)
{
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiPreoccup::~NSEpiPreoccup()
{
}


// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiPreoccup::alimenteFiche()
{
  alimenteChamp(pDonnees->patient,    PREOCCUP_PATIENT_FIELD,     PREOCCUP_PATIENT_LEN) ;
  alimenteChamp(pDonnees->code, 		  PREOCCUP_CODE_FIELD, 	      PREOCCUP_CODE_LEN) ;
  alimenteChamp(pDonnees->revision,   PREOCCUP_REVISION_FIELD,    PREOCCUP_REVISION_LEN) ;
  alimenteChamp(pDonnees->session,    PREOCCUP_SESSION_FIELD,     PREOCCUP_SESSION_LEN) ;
  alimenteChamp(pDonnees->lexique,  	PREOCCUP_LEXIQUE_FIELD, 	  PREOCCUP_LEXIQUE_LEN) ;
  alimenteChamp(pDonnees->complement, PREOCCUP_COMPLEMENT_FIELD,  PREOCCUP_COMPLEMENT_LEN) ;
  alimenteChamp(pDonnees->dateCree,   PREOCCUP_DATE_CREE_FIELD,   PREOCCUP_DATE_CREE_LEN) ;
  alimenteChamp(pDonnees->dateFerme,  PREOCCUP_DATE_FERME_FIELD,  PREOCCUP_DATE_FERME_LEN) ;
  alimenteChamp(pDonnees->actif,  	  PREOCCUP_ACTIF_FIELD,       PREOCCUP_ACTIF_LEN) ;
  alimenteChamp(pDonnees->recurrent,  PREOCCUP_RECURRENT_FIELD,   PREOCCUP_RECURRENT_LEN) ;
  alimenteChamp(pDonnees->mere,  	    PREOCCUP_MERE_FIELD,        PREOCCUP_MERE_LEN) ;
}


// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiPreoccup::videFiche()
{
  videChamp(pDonnees->patient,    PREOCCUP_PATIENT_FIELD,     PREOCCUP_PATIENT_LEN) ;
  videChamp(pDonnees->code, 		  PREOCCUP_CODE_FIELD, 	      PREOCCUP_CODE_LEN) ;
  videChamp(pDonnees->revision,   PREOCCUP_REVISION_FIELD,    PREOCCUP_REVISION_LEN) ;
  videChamp(pDonnees->session,    PREOCCUP_SESSION_FIELD,     PREOCCUP_SESSION_LEN) ;
  videChamp(pDonnees->lexique,  	PREOCCUP_LEXIQUE_FIELD, 	  PREOCCUP_LEXIQUE_LEN) ;
  videChamp(pDonnees->complement, PREOCCUP_COMPLEMENT_FIELD,  PREOCCUP_COMPLEMENT_LEN) ;
  videChamp(pDonnees->dateCree,   PREOCCUP_DATE_CREE_FIELD,   PREOCCUP_DATE_CREE_LEN) ;
  videChamp(pDonnees->dateFerme,  PREOCCUP_DATE_FERME_FIELD,  PREOCCUP_DATE_FERME_LEN) ;
  videChamp(pDonnees->actif,  	  PREOCCUP_ACTIF_FIELD,       PREOCCUP_ACTIF_LEN) ;
  videChamp(pDonnees->recurrent,  PREOCCUP_RECURRENT_FIELD,   PREOCCUP_RECURRENT_LEN) ;
  videChamp(pDonnees->mere,  	    PREOCCUP_MERE_FIELD,        PREOCCUP_MERE_LEN) ;
}


// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiPreoccup::open()
{
	char tableName[] = "PREOCCUP.DB";

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return (lastError) ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiPreoccup::Create()
{
	return true ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiPreoccup::Modify()
{
	return true ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiPreoccup&
NSEpiPreoccup::operator=(NSEpiPreoccup src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiPreoccup::operator==(const NSEpiPreoccup& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiPreoccupInfo::NSEpiPreoccupInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiPreoccupData() ;
}


// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiPreoccup
// -----------------------------------------------------------------------------
NSEpiPreoccupInfo::NSEpiPreoccupInfo(NSEpiPreoccup *pContact)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiPreoccupData() ;

	// Copie les valeurs du NSEpiPreoccup
	*pDonnees = *(pContact->pDonnees) ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiPreoccupInfo::NSEpiPreoccupInfo(NSEpiPreoccupInfo& rv)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiPreoccupData() ;

	// Copie les valeurs du NSEpiPreoccupInfo d'origine
	*pDonnees = *(rv.pDonnees) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiPreoccupInfo::~NSEpiPreoccupInfo()
{
	delete pDonnees ;
}


void
NSEpiPreoccupInfo::initActif(bool bActif)
{
  if (bActif)
    pDonnees->actif[0] = '1' ;
  else
    pDonnees->actif[0] = '0' ;
}


void
NSEpiPreoccupInfo::initRecurrent(bool bRecurrent)
{
  if (bRecurrent)
    pDonnees->recurrent[0] = '1' ;
  else
    pDonnees->recurrent[0] = '0' ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiPreoccupInfo&
NSEpiPreoccupInfo::operator=(NSEpiPreoccupInfo src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiPreoccupInfo::operator==(const NSEpiPreoccupInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiProbleme
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiProblemeData::NSEpiProblemeData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiProblemeData::NSEpiProblemeData(NSEpiProblemeData& rv)
{
	strcpy(preoccupation, rv.preoccupation) ;
	strcpy(code,          rv.code) ;
	strcpy(revision,      rv.revision) ;
	strcpy(session,       rv.session) ;
	strcpy(signifiant,    rv.signifiant) ;
	strcpy(severite,      rv.severite) ;
	strcpy(lexique,  		  rv.lexique) ;
	strcpy(complement,    rv.complement) ;
	strcpy(certitude,     rv.certitude) ;
	strcpy(origine,       rv.origine) ;
	strcpy(fin,           rv.fin) ;
	strcpy(dateDebut,     rv.dateDebut) ;
	strcpy(dateCree,      rv.dateCree) ;
	strcpy(dateFerme,  		rv.dateFerme) ;
	strcpy(dateObso,  		rv.dateObso) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiProblemeData::~NSEpiProblemeData()
{
}


// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiProblemeData&
NSEpiProblemeData::operator=(NSEpiProblemeData src)
{
  if (this == &src)
    return *this ;

	strcpy(preoccupation, src.preoccupation) ;
	strcpy(code,          src.code) ;
	strcpy(revision,      src.revision) ;
	strcpy(session,       src.session) ;
	strcpy(signifiant,    src.signifiant) ;
	strcpy(severite,      src.severite) ;
	strcpy(lexique,  		  src.lexique) ;
	strcpy(complement,    src.complement) ;
	strcpy(certitude,     src.certitude) ;
	strcpy(origine,       src.origine) ;
	strcpy(fin,           src.fin) ;
	strcpy(dateDebut,     src.dateDebut) ;
	strcpy(dateCree,      src.dateCree) ;
	strcpy(dateFerme,  		src.dateFerme) ;
	strcpy(dateObso,  		src.dateObso) ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiProblemeData::operator==(const NSEpiProblemeData& o)
{
	if ((strcmp(preoccupation, o.preoccupation) == 0) &&
      (strcmp(code,          o.code)          == 0) &&
      (strcmp(revision,      o.revision)      == 0))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiProblemeData::metAZero()
{
	// Met les champs de donn�es � z�ro
	memset(preoccupation, 0, PROBLEME_PREOCCUP_LEN + 1) ;
	memset(code,   		    0, PROBLEME_CODE_LEN + 1) ;
	memset(revision, 	    0, PROBLEME_REVISION_LEN + 1) ;
	memset(session,       0, PROBLEME_SESSION_LEN + 1) ;
	memset(signifiant,  	0, PROBLEME_SIGNIFIANT_LEN + 1) ;
	memset(severite,      0, PROBLEME_SEVERITE_LEN + 1) ;
	memset(lexique,  		  0, PROBLEME_LEXIQUE_LEN + 1) ;
	memset(complement, 	  0, PROBLEME_COMPLEMENT_LEN + 1) ;
	memset(certitude,   	0, PROBLEME_CERTITUDE_LEN + 1) ;
	memset(origine, 	    0, PROBLEME_ORIGINE_LEN + 1) ;
	memset(fin,           0, PROBLEME_FIN_LEN + 1) ;
	memset(dateDebut,  		0, PROBLEME_DATE_DEBUT_LEN + 1) ;
	memset(dateCree,      0, PROBLEME_DATE_CREE_LEN + 1) ;
	memset(dateFerme,  		0, PROBLEME_DATE_FERME_LEN + 1) ;
	memset(dateObso,  		0, PROBLEME_DATE_OBSO_LEN + 1) ;
}


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiProbleme::NSEpiProbleme(NSContexte *pCtx)
  : NSEpiProblemeInfo(),
    NSFiche(pCtx)
{
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiProbleme::NSEpiProbleme(NSEpiProbleme& rv)
  : NSEpiProblemeInfo(rv),
    NSFiche(rv.pContexte)
{
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiProbleme::~NSEpiProbleme()
{
}


// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiProbleme::alimenteFiche()
{
  alimenteChamp(pDonnees->preoccupation,  PROBLEME_PREOCCUP_FIELD,    PROBLEME_PREOCCUP_LEN) ;
  alimenteChamp(pDonnees->code, 		      PROBLEME_CODE_FIELD, 	      PROBLEME_CODE_LEN) ;
  alimenteChamp(pDonnees->revision,       PROBLEME_REVISION_FIELD,    PROBLEME_REVISION_LEN) ;
  alimenteChamp(pDonnees->session,        PROBLEME_SESSION_FIELD,     PROBLEME_SESSION_LEN) ;
  alimenteChamp(pDonnees->signifiant,     PROBLEME_SIGNIFIANT_FIELD,  PROBLEME_SIGNIFIANT_LEN) ;
  alimenteChamp(pDonnees->severite,       PROBLEME_SEVERITE_FIELD,    PROBLEME_SEVERITE_LEN) ;
  alimenteChamp(pDonnees->lexique,  	    PROBLEME_LEXIQUE_FIELD,     PROBLEME_LEXIQUE_LEN) ;
  alimenteChamp(pDonnees->complement,     PROBLEME_COMPLEMENT_FIELD,  PROBLEME_COMPLEMENT_LEN) ;
  alimenteChamp(pDonnees->certitude, 	    PROBLEME_CERTITUDE_FIELD,   PROBLEME_CERTITUDE_LEN) ;
  alimenteChamp(pDonnees->origine,        PROBLEME_ORIGINE_FIELD,     PROBLEME_ORIGINE_LEN) ;
  alimenteChamp(pDonnees->fin,            PROBLEME_FIN_FIELD,         PROBLEME_FIN_LEN) ;
  alimenteChamp(pDonnees->dateDebut,      PROBLEME_DATE_DEBUT_FIELD,  PROBLEME_DATE_DEBUT_LEN) ;
  alimenteChamp(pDonnees->dateCree,       PROBLEME_DATE_CREE_FIELD,   PROBLEME_DATE_CREE_LEN) ;
  alimenteChamp(pDonnees->dateFerme,      PROBLEME_DATE_FERME_FIELD,  PROBLEME_DATE_FERME_LEN) ;
  alimenteChamp(pDonnees->dateObso,  	    PROBLEME_DATE_OBSO_FIELD,   PROBLEME_DATE_OBSO_LEN) ;
}


// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiProbleme::videFiche()
{
  videChamp(pDonnees->preoccupation,  PROBLEME_PREOCCUP_FIELD,    PROBLEME_PREOCCUP_LEN) ;
  videChamp(pDonnees->code, 		      PROBLEME_CODE_FIELD, 	      PROBLEME_CODE_LEN) ;
  videChamp(pDonnees->revision,       PROBLEME_REVISION_FIELD,    PROBLEME_REVISION_LEN) ;
  videChamp(pDonnees->session,        PROBLEME_SESSION_FIELD,     PROBLEME_SESSION_LEN) ;
  videChamp(pDonnees->signifiant,     PROBLEME_SIGNIFIANT_FIELD,  PROBLEME_SIGNIFIANT_LEN) ;
  videChamp(pDonnees->severite,       PROBLEME_SEVERITE_FIELD,    PROBLEME_SEVERITE_LEN) ;
  videChamp(pDonnees->lexique,  	    PROBLEME_LEXIQUE_FIELD, 	  PROBLEME_LEXIQUE_LEN) ;
  videChamp(pDonnees->complement,     PROBLEME_COMPLEMENT_FIELD,  PROBLEME_COMPLEMENT_LEN) ;
  videChamp(pDonnees->certitude, 	    PROBLEME_CERTITUDE_FIELD,   PROBLEME_CERTITUDE_LEN) ;
  videChamp(pDonnees->origine,        PROBLEME_ORIGINE_FIELD,     PROBLEME_ORIGINE_LEN) ;
  videChamp(pDonnees->fin,            PROBLEME_FIN_FIELD,         PROBLEME_FIN_LEN) ;
  videChamp(pDonnees->dateDebut,      PROBLEME_DATE_DEBUT_FIELD,  PROBLEME_DATE_DEBUT_LEN) ;
  videChamp(pDonnees->dateCree,       PROBLEME_DATE_CREE_FIELD,   PROBLEME_DATE_CREE_LEN) ;
  videChamp(pDonnees->dateFerme,      PROBLEME_DATE_FERME_FIELD,  PROBLEME_DATE_FERME_LEN) ;
  videChamp(pDonnees->dateObso,  	    PROBLEME_DATE_OBSO_FIELD,   PROBLEME_DATE_OBSO_LEN) ;
}


// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiProbleme::open()
{
	char tableName[] = "PROBLEME.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return (lastError) ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiProbleme::Create()
{
	return true ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiProbleme::Modify()
{
	return true ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiProbleme&
NSEpiProbleme::operator=(NSEpiProbleme src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiProbleme::operator==(const NSEpiProbleme& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiProblemeInfo::NSEpiProblemeInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiProblemeData() ;
}


// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiProbleme
// -----------------------------------------------------------------------------
NSEpiProblemeInfo::NSEpiProblemeInfo(NSEpiProbleme *pContact)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiProblemeData() ;

	// Copie les valeurs du NSEpiProbleme
	*pDonnees = *(pContact->pDonnees) ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiProblemeInfo::NSEpiProblemeInfo(NSEpiProblemeInfo& rv)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiProblemeData() ;

	// Copie les valeurs du NSEpiProblemeInfo d'origine
	*pDonnees = *(rv.pDonnees) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiProblemeInfo::~NSEpiProblemeInfo()
{
	delete pDonnees ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiProblemeInfo&
NSEpiProblemeInfo::operator=(NSEpiProblemeInfo src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiProblemeInfo::operator==(const NSEpiProblemeInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiProbEven
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiProbEvenData::NSEpiProbEvenData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiProbEvenData::NSEpiProbEvenData(NSEpiProbEvenData& rv)
{
	strcpy(probleme,    rv.probleme) ;
	strcpy(code,        rv.code) ;
	strcpy(revision,    rv.revision) ;
	strcpy(session,     rv.session) ;
	strcpy(lexique,  	  rv.lexique) ;
	strcpy(complement,  rv.complement) ;
	strcpy(certitude,   rv.certitude) ;
	strcpy(severite,    rv.severite) ;
	strcpy(dateHeure,   rv.dateHeure) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiProbEvenData::~NSEpiProbEvenData()
{
}


// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiProbEvenData&
NSEpiProbEvenData::operator=(NSEpiProbEvenData src)
{
  if (this == &src)
    return *this ;

	strcpy(probleme,    src.probleme) ;
	strcpy(code,        src.code) ;
	strcpy(revision,    src.revision) ;
	strcpy(session,     src.session) ;
	strcpy(lexique,  	  src.lexique) ;
	strcpy(complement,  src.complement) ;
	strcpy(certitude,   src.certitude) ;
	strcpy(severite,    src.severite) ;
	strcpy(dateHeure,   src.dateHeure) ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiProbEvenData::operator == ( const NSEpiProbEvenData& o )
{
	if ((strcmp(probleme, o.probleme) == 0) &&
      (strcmp(code,     o.code)     == 0) &&
      (strcmp(revision, o.revision) == 0))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
//  Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiProbEvenData::metAZero()
{
	// Met les champs de donn�es � z�ro
	memset(probleme,    0, PROBEVEN_PROBLEME_LEN + 1) ;
	memset(code,   		  0, PROBEVEN_CODE_LEN + 1) ;
	memset(revision, 	  0, PROBEVEN_REVISION_LEN + 1) ;
	memset(session,     0, PROBEVEN_SESSION_LEN + 1) ;
	memset(lexique,  	  0, PROBEVEN_LEXIQUE_LEN + 1) ;
	memset(complement,  0, PROBEVEN_COMPLEMENT_LEN + 1) ;
  memset(certitude,   0, PROBEVEN_CERTITUDE_LEN + 1) ;
	memset(severite, 	  0, PROBEVEN_SEVERITE_LEN + 1) ;
	memset(dateHeure,   0, PROBEVEN_DATE_HEURE_LEN + 1) ;
}

// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiProbEven::NSEpiProbEven(NSContexte *pCtx)
  : NSEpiProbEvenInfo(),
    NSFiche(pCtx)
{
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiProbEven::NSEpiProbEven(NSEpiProbEven& rv)
  : NSEpiProbEvenInfo(rv),
    NSFiche(rv.pContexte)
{
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiProbEven::~NSEpiProbEven()
{
}


// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiProbEven::alimenteFiche()
{
  alimenteChamp(pDonnees->probleme,   PROBEVEN_PROBLEME_FIELD,    PROBEVEN_PROBLEME_LEN) ;
  alimenteChamp(pDonnees->code, 		  PROBEVEN_CODE_FIELD, 	      PROBEVEN_CODE_LEN) ;
  alimenteChamp(pDonnees->revision,   PROBEVEN_REVISION_FIELD,    PROBEVEN_REVISION_LEN) ;
  alimenteChamp(pDonnees->session,    PROBEVEN_SESSION_FIELD,     PROBEVEN_SESSION_LEN) ;
  alimenteChamp(pDonnees->lexique,  	PROBEVEN_LEXIQUE_FIELD,     PROBEVEN_LEXIQUE_LEN) ;
  alimenteChamp(pDonnees->complement, PROBEVEN_COMPLEMENT_FIELD,  PROBEVEN_COMPLEMENT_LEN) ;
  alimenteChamp(pDonnees->certitude, 	PROBEVEN_CERTITUDE_FIELD,   PROBEVEN_CERTITUDE_LEN) ;
  alimenteChamp(pDonnees->severite,   PROBEVEN_SEVERITE_FIELD,    PROBEVEN_SEVERITE_LEN) ;
  alimenteChamp(pDonnees->dateHeure,  PROBEVEN_DATE_HEURE_FIELD,  PROBEVEN_DATE_HEURE_LEN) ;
}


// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiProbEven::videFiche()
{
  videChamp(pDonnees->probleme,   PROBEVEN_PROBLEME_FIELD,    PROBEVEN_PROBLEME_LEN) ;
  videChamp(pDonnees->code, 		  PROBEVEN_CODE_FIELD, 	      PROBEVEN_CODE_LEN) ;
  videChamp(pDonnees->revision,   PROBEVEN_REVISION_FIELD,    PROBEVEN_REVISION_LEN) ;
  videChamp(pDonnees->session,    PROBEVEN_SESSION_FIELD,     PROBEVEN_SESSION_LEN) ;
  videChamp(pDonnees->lexique,  	PROBEVEN_LEXIQUE_FIELD,     PROBEVEN_LEXIQUE_LEN) ;
  videChamp(pDonnees->complement, PROBEVEN_COMPLEMENT_FIELD,  PROBEVEN_COMPLEMENT_LEN) ;
  videChamp(pDonnees->certitude, 	PROBEVEN_CERTITUDE_FIELD,   PROBEVEN_CERTITUDE_LEN) ;
  videChamp(pDonnees->severite,   PROBEVEN_SEVERITE_FIELD,    PROBEVEN_SEVERITE_LEN) ;
  videChamp(pDonnees->dateHeure,  PROBEVEN_DATE_HEURE_FIELD,  PROBEVEN_DATE_HEURE_LEN) ;
}


// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiProbEven::open()
{
	char tableName[] = "PROBEVENT.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return (lastError) ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiProbEven::Create()
{
	return true ;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiProbEven::Modify()
{
	return true ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiProbEven&
NSEpiProbEven::operator=(NSEpiProbEven src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiProbEven::operator==(const NSEpiProbEven& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}


// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiProbEvenInfo::NSEpiProbEvenInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiProbEvenData() ;
}


// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiProbEven
// -----------------------------------------------------------------------------
NSEpiProbEvenInfo::NSEpiProbEvenInfo(NSEpiProbEven *pContact)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiProbEvenData() ;

	// Copie les valeurs du NSEpiProbEven
	*pDonnees = *(pContact->pDonnees) ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiProbEvenInfo::NSEpiProbEvenInfo(NSEpiProbEvenInfo& rv)
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSEpiProbEvenData() ;

	// Copie les valeurs du NSEpiProbEvenInfo d'origine
	*pDonnees = *(rv.pDonnees) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiProbEvenInfo::~NSEpiProbEvenInfo()
{
	delete pDonnees ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiProbEvenInfo&
NSEpiProbEvenInfo::operator=(NSEpiProbEvenInfo src)
{
  if (this == &src)
    return *this ;
	*pDonnees = *(src.pDonnees) ;
	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiProbEvenInfo::operator==(const NSEpiProbEvenInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}

*/

// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiClasser
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiClasserData::NSEpiClasserData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiClasserData::NSEpiClasserData(const NSEpiClasserData& rv)
{
	_sCode           = rv._sCode ;
	_sClassification = rv._sClassification ;
	_sCriteria       = rv._sCriteria ;
	_sRelation       = rv._sRelation ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiClasserData::~NSEpiClasserData()
{
}

// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiClasserData&
NSEpiClasserData::operator=(const NSEpiClasserData& src)
{
  if (this == &src)
    return *this ;

	_sCode           = src._sCode ;
	_sClassification = src._sClassification ;
	_sCriteria       = src._sCriteria ;
	_sRelation       = src._sRelation ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiClasserData::operator==(const NSEpiClasserData& o)
{
	if ((_sCode           == o._sCode)           &&
      (_sClassification == o._sClassification) &&
      (_sCriteria       == o._sCriteria)       &&
      (_sRelation       == o._sRelation)       )
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiClasserData::metAZero()
{
	_sCode           = string("") ;
	_sClassification = string("") ;
	_sCriteria       = string("") ;
	_sRelation       = string("") ;
}

#ifndef _ENTERPRISE_DLL
// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiClasser::NSEpiClasser(NSSuper *pSuper)
             :NSEpiClasserInfo(),
              NSFiche(pSuper)
{
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiClasser::NSEpiClasser(const NSEpiClasser& rv)
             :NSEpiClasserInfo(rv),
              NSFiche(rv._pSuper)
{
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiClasser::~NSEpiClasser()
{
}

// -----------------------------------------------------------------------------
// Donne l'ensemble des relations pour un code, une relation, un crit�re
// -----------------------------------------------------------------------------
DBIResult
NSEpiClasser::donneRelations(string *pResult, string sCode, string sClassification, string sCritere)
{
  if (NULL == pResult)
    return DBIERR_NONE ;

  *pResult = string("") ;

  bool bOpenClose = false ;
  if (false == _isOpen)
    bOpenClose = true ;

  // Ouverture de la table - Open the table
  if (bOpenClose)
  {
    lastError = open() ;
    if (lastError != DBIERR_NONE)
      return lastError ;
  }

  // Recherche de la premi�re relation - Looking for the first proper relation
  string cle = sCode + sClassification ;

  CURProps  curProps ;
  DBIResult lastError   = DbiGetCursorProps(PrendCurseur(), curProps) ;
  Byte      *pIndexRec  = new Byte[curProps.iRecBufSize] ;
  memset(pIndexRec, 0, curProps.iRecBufSize) ;
  DbiPutField(PrendCurseur(), CLASSER_CODE_FIELD,    pIndexRec, (Byte *)sCode.c_str()) ;
  DbiPutField(PrendCurseur(), CLASSER_CLASSIF_FIELD, pIndexRec, (Byte *)sClassification.c_str()) ;

  lastError = chercheClefComposite("CODAGE", NODEFAULTINDEX, keySEARCHGEQ, dbiWRITELOCK, pIndexRec) ;
  delete[] pIndexRec ;

  if ((lastError != DBIERR_NONE) && (lastError != DBIERR_EOF))
	{
    if (bOpenClose)
      close() ;
		return lastError ;
  }

  if (lastError == DBIERR_EOF)
	{
    if (bOpenClose)
      close() ;
		return DBIERR_NONE ;
  }

  lastError = getRecord() ;
  if (lastError != DBIERR_NONE)
	{
    if (bOpenClose)
      close() ;
		return lastError ;
  }

  // On v�rifie que la fiche trouv�e appartient bien au document
  if ((_Donnees.getCode()           != sCode)           ||
      (_Donnees.getClassification() != sClassification))
  {
    if (bOpenClose)
      close() ;
		return DBIERR_NONE ;
	}

  // On avance dans le fichier tant que les fiches trouv�es sont OK
  while ( (lastError                    != DBIERR_EOF)  &&
          (_Donnees.getCode()           == sCode)       &&
          (_Donnees.getClassification() == sClassification))
  {
    if ((_Donnees.getCriteria() == sCritere) &&
        (_Donnees.getRelation() != string("")))
    {
      if (string("") != *pResult)
        *pResult += string(";") ;
      *pResult += _Donnees.getRelation() ;
    }

    lastError = suivant(dbiWRITELOCK) ;
    if ((lastError != DBIERR_NONE) && (lastError != DBIERR_EOF))
		{
      if (bOpenClose)
        close() ;
      return lastError ;
		}

    if (lastError != DBIERR_EOF)
    {
      lastError = getRecord() ;
      if (lastError != DBIERR_NONE)
			{
        if (bOpenClose)
          close() ;
        return lastError ;
			}
    }
  }

  // Fermeture du fichier
  if (bOpenClose)
    return close() ;

  return DBIERR_NONE ;
}

// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiClasser::alimenteFiche()
{
  char code[CLASSER_CODE_LEN + 1] ;
  char classification[CLASSER_CLASSIF_LEN + 1] ;  char critere[CLASSER_CRITERE_LEN + 1] ;  char relation[CLASSER_RELATION_LEN + 1] ;

  alimenteChamp(code, 		      CLASSER_CODE_FIELD,     CLASSER_CODE_LEN) ;
  alimenteChamp(classification, CLASSER_CLASSIF_FIELD,  CLASSER_CLASSIF_LEN) ;
  alimenteChamp(critere,        CLASSER_CRITERE_FIELD,  CLASSER_CRITERE_LEN) ;
  alimenteChamp(relation,  	    CLASSER_RELATION_FIELD, CLASSER_RELATION_LEN) ;

  _Donnees.setCode(code) ;
  _Donnees.setClassification(classification) ;
  _Donnees.setCriteria(critere) ;
  _Donnees.setRelation(relation) ;
}

// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiClasser::videFiche()
{
  videChamp((char*)(_Donnees.getCode().c_str()),           CLASSER_CODE_FIELD,     CLASSER_CODE_LEN) ;
  videChamp((char*)(_Donnees.getClassification().c_str()), CLASSER_CLASSIF_FIELD,  CLASSER_CLASSIF_LEN) ;
  videChamp((char*)(_Donnees.getCriteria().c_str()),       CLASSER_CRITERE_FIELD,  CLASSER_CRITERE_LEN) ;
  videChamp((char*)(_Donnees.getRelation().c_str()),       CLASSER_RELATION_FIELD, CLASSER_RELATION_LEN) ;
}

// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiClasser::open()
{
	char tableName[] = "CLASSER.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return (lastError) ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiClasser::Create()
{
	return true ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiClasser::Modify()
{
	return true ;
}


// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiClasser&
NSEpiClasser::operator=(const NSEpiClasser& src)
{
  if (this == &src)
    return *this ;

	_Donnees = src._Donnees ;

	return *this ;
}

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiClasser::operator==(const NSEpiClasser& o)
{
  return (_Donnees == o._Donnees) ;
}
#endif

// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiClasserInfo::NSEpiClasserInfo()
{
}

#ifndef _ENTERPRISE_DLL
// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiClasser
// -----------------------------------------------------------------------------
NSEpiClasserInfo::NSEpiClasserInfo(NSEpiClasser *pContact)
{
	_Donnees = pContact->_Donnees ;
}
#endif

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiClasserInfo::NSEpiClasserInfo(const NSEpiClasserInfo& rv)
{
	_Donnees = rv._Donnees ;
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiClasserInfo::~NSEpiClasserInfo()
{
}

// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiClasserInfo&
NSEpiClasserInfo::operator=(const NSEpiClasserInfo& src)
{
  if (this == &src)
    return *this ;

	_Donnees = src._Donnees ;

  return *this ;
}

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiClasserInfo::operator==(const NSEpiClasserInfo& o)
{
  return (_Donnees == o._Donnees) ;
}

#ifdef _ENTERPRISE_DLL

void
NSEpiClasserInfo::alimenteFiche(MYSQL_ROW *pRow)
{
  if ((MYSQL_ROW*) NULL == pRow)
    return ;

  _Donnees.metAZero() ;

  if ((*pRow)[CLASSER_CODE_FIELD - 1])
    _Donnees.setCode((*pRow)[CLASSER_CODE_FIELD - 1]) ;
  if ((*pRow)[CLASSER_CLASSIF_FIELD - 1])
    _Donnees.setClassification((*pRow)[CLASSER_CLASSIF_FIELD - 1]) ;
  if ((*pRow)[CLASSER_CRITERE_FIELD - 1])
	  _Donnees.setCriteria((*pRow)[CLASSER_CRITERE_FIELD - 1]) ;
  if ((*pRow)[CLASSER_RELATION_FIELD - 1])
    _Donnees.setRelation((*pRow)[CLASSER_RELATION_FIELD - 1]) ;
}

// -----------------------------------------------------------------------------
// Get every existing relations for a code, a relation, a criteria
// -----------------------------------------------------------------------------
bool
NSEpiClasserInfo::donneRelations(string *pResult, string sCode, string sClassification, string sCritere, ontologyBaseManager* pOntologyManager)
{
  if ((NULL == pOntologyManager) || (NULL == pResult))
    return false ;

  *pResult = string("") ;

  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM classer WHERE CODE = \"") + sCode + string("\" AND CLASSIFICATION = \"") + sClassification + string("\"") ;
  if (string("") != sCritere)
    sQuery += string(" AND CRITERE = \"") + sCritere + string("\"") ;

  MYSQL_RES *pSqlResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pSqlResult)
    return false ;

  MYSQL_ROW Row = mysql_fetch_row(pSqlResult) ;
  while (Row)
  {
    _Donnees.metAZero() ;
    alimenteFiche(&Row) ;

    if (string("") != *pResult)
      *pResult += string(";") ;
    *pResult += _Donnees.getRelation() ;

    Row = mysql_fetch_row(pSqlResult) ;
  }

  mysql_free_result(pSqlResult) ;

  return true ;
}
#endif

//******************** THESAURUS ********************

// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSThesaurus
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSThesaurusData::NSThesaurusData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}


// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSThesaurusData::NSThesaurusData(const NSThesaurusData& rv)
{
  _iId      = rv._iId ;
  _sOrigine = rv._sOrigine ;
  _ibui     = rv._ibui ;
  _labelFr  = rv._labelFr ;
  _labelNl  = rv._labelNl ;
  _icpc2    = rv._icpc2 ;
  _icd10    = rv._icd10 ;
  _icpc2_2  = rv._icpc2_2 ;
  _icd10_2  = rv._icd10_2 ;
  _icpc2_1X = rv._icpc2_1X ;
  _icd10_1X = rv._icd10_1X ;
  _icpc2_2X = rv._icpc2_2X ;
  _icd10_2X = rv._icd10_2X ;
  _icpc2_1Y = rv._icpc2_1Y ;
  _icd10_1Y = rv._icd10_1Y ;
  _icpc2_2Y = rv._icpc2_2Y ;
  _icd10_2Y = rv._icd10_2Y ;
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSThesaurusData::~NSThesaurusData()
{
}

// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSThesaurusData&
NSThesaurusData::operator=(const NSThesaurusData& src)
{
  if (this == &src)
    return *this ;

  _iId      = src._iId ;
  _sOrigine = src._sOrigine ;
	_ibui     = src._ibui ;
  _labelFr  = src._labelFr ;
  _labelNl  = src._labelNl ;
  _icpc2    = src._icpc2 ;
  _icd10    = src._icd10 ;
  _icpc2_2  = src._icpc2_2 ;
  _icd10_2  = src._icd10_2 ;
  _icpc2_1X = src._icpc2_1X ;
  _icd10_1X = src._icd10_1X ;
  _icpc2_2X = src._icpc2_2X ;
  _icd10_2X = src._icd10_2X ;
  _icpc2_1Y = src._icpc2_1Y ;
  _icd10_1Y = src._icd10_1Y ;
  _icpc2_2Y = src._icpc2_2Y ;
  _icd10_2Y = src._icd10_2Y ;

	return *this ;
}

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSThesaurusData::operator==(const NSThesaurusData& o)
{
	if (_ibui == o._ibui)
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSThesaurusData::metAZero()
{
  _iId      = -1 ;
  _sOrigine = string("") ;
	_ibui     = string("") ;
  _labelFr  = string("") ;
  _labelNl  = string("") ;
  _icpc2    = string("") ;
  _icd10    = string("") ;
  _icpc2_2  = string("") ;
  _icd10_2  = string("") ;
  _icpc2_1X = string("") ;
  _icd10_1X = string("") ;
  _icpc2_2X = string("") ;
  _icd10_2X = string("") ;
  _icpc2_1Y = string("") ;
  _icd10_1Y = string("") ;
  _icpc2_2Y = string("") ;
  _icd10_2Y = string("") ;
}

#ifndef _ENTERPRISE_DLL
// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSThesaurus::NSThesaurus(NSSuper *pSuper)
            :NSThesaurusInfo(), NSFiche(pSuper)
{
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSThesaurus::NSThesaurus(const NSThesaurus& rv)
            :NSThesaurusInfo(rv), NSFiche(rv._pSuper)
{
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSThesaurus::~NSThesaurus()
{
}

// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSThesaurus::alimenteFiche()
{
  char ibui[THESAURUS_IBUI_LEN + 1] ;
  char labelFr[THESAURUS_LABEL_LEN + 1] ;  char labelNl[THESAURUS_LABEL_LEN + 1] ;  char icpc2[THESAURUS_ICPC2_LEN + 1] ;
  char icd10[THESAURUS_ICD10_LEN + 1] ;
  char icpc2_2[THESAURUS_ICPC2_LEN + 1] ;  char icd10_2[THESAURUS_ICD10_LEN + 1] ;  char icpc2_1X[THESAURUS_ICPC2_LEN + 1] ;
  char icd10_1X[THESAURUS_ICD10_LEN + 1] ;
  char icpc2_2X[THESAURUS_ICPC2_LEN + 1] ;  char icd10_2X[THESAURUS_ICD10_LEN + 1] ;
  char icpc2_1Y[THESAURUS_ICPC2_LEN + 1] ;
  char icd10_1Y[THESAURUS_ICD10_LEN + 1] ;  char icpc2_2Y[THESAURUS_ICPC2_LEN + 1] ;  char icd10_2Y[THESAURUS_ICD10_LEN + 1] ;

  alimenteChamp(ibui,			THESAURUS_IBUI_FIELD,     THESAURUS_IBUI_LEN) ;
  alimenteChamp(labelFr,	THESAURUS_FR_LABEL_FIELD,	THESAURUS_LABEL_LEN) ;
  alimenteChamp(labelNl,	THESAURUS_NL_LABEL_FIELD,	THESAURUS_LABEL_LEN) ;
  alimenteChamp(icpc2,		THESAURUS_ICPC2_FIELD,		THESAURUS_ICPC2_LEN) ;
  alimenteChamp(icd10,		THESAURUS_ICD10_FIELD,		THESAURUS_ICD10_LEN) ;
  alimenteChamp(icpc2_2,  THESAURUS_ICPC2_2_FIELD,  THESAURUS_ICPC2_LEN) ;
  alimenteChamp(icd10_2,  THESAURUS_ICD10_2_FIELD,  THESAURUS_ICD10_LEN) ;
  alimenteChamp(icpc2_1X, THESAURUS_ICPC2_1X_FIELD, THESAURUS_ICPC2_LEN) ;
  alimenteChamp(icd10_1X, THESAURUS_ICD10_1X_FIELD, THESAURUS_ICD10_LEN) ;
  alimenteChamp(icpc2_2X, THESAURUS_ICPC2_2X_FIELD, THESAURUS_ICPC2_LEN) ;
  alimenteChamp(icd10_2X, THESAURUS_ICD10_2X_FIELD, THESAURUS_ICD10_LEN) ;
  alimenteChamp(icpc2_1Y, THESAURUS_ICPC2_1Y_FIELD, THESAURUS_ICPC2_LEN) ;
  alimenteChamp(icd10_1Y, THESAURUS_ICD10_1Y_FIELD, THESAURUS_ICD10_LEN) ;
  alimenteChamp(icpc2_2Y, THESAURUS_ICPC2_2Y_FIELD, THESAURUS_ICPC2_LEN) ;
  alimenteChamp(icd10_2Y, THESAURUS_ICD10_2Y_FIELD, THESAURUS_ICD10_LEN) ;

  _Donnees._ibui     = string(ibui) ;
  _Donnees._labelFr  = string(labelFr) ;
  _Donnees._labelNl  = string(labelNl) ;
  _Donnees._icpc2    = string(icpc2) ;
  _Donnees._icd10    = string(icd10) ;
  _Donnees._icpc2_2  = string(icpc2_2) ;
  _Donnees._icd10_2  = string(icd10_2) ;
  _Donnees._icpc2_1X = string(icpc2_1X) ;
  _Donnees._icd10_1X = string(icd10_1X) ;
  _Donnees._icpc2_2X = string(icpc2_2X) ;
  _Donnees._icd10_2X = string(icd10_2X) ;
  _Donnees._icpc2_1Y = string(icpc2_1Y) ;
  _Donnees._icd10_1Y = string(icd10_1Y) ;
  _Donnees._icpc2_2Y = string(icpc2_2Y) ;
  _Donnees._icd10_2Y = string(icd10_2Y) ;
}

// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSThesaurus::videFiche()
{
  videChamp((char*)(_Donnees._ibui.c_str()),		 THESAURUS_IBUI_FIELD,     THESAURUS_IBUI_LEN) ;
  videChamp((char*)(_Donnees._labelFr.c_str()),	 THESAURUS_FR_LABEL_FIELD, THESAURUS_LABEL_LEN) ;
  videChamp((char*)(_Donnees._labelNl.c_str()),	 THESAURUS_NL_LABEL_FIELD, THESAURUS_LABEL_LEN) ;
  videChamp((char*)(_Donnees._icpc2.c_str()),		 THESAURUS_ICPC2_FIELD,		 THESAURUS_ICPC2_LEN) ;
  videChamp((char*)(_Donnees._icd10.c_str()),		 THESAURUS_ICD10_FIELD,		 THESAURUS_ICD10_LEN) ;
  videChamp((char*)(_Donnees._icpc2_2.c_str()),  THESAURUS_ICPC2_2_FIELD,  THESAURUS_ICPC2_LEN) ;
  videChamp((char*)(_Donnees._icd10_2.c_str()),  THESAURUS_ICD10_2_FIELD,  THESAURUS_ICD10_LEN) ;
  videChamp((char*)(_Donnees._icpc2_1X.c_str()), THESAURUS_ICPC2_1X_FIELD, THESAURUS_ICPC2_LEN) ;
  videChamp((char*)(_Donnees._icd10_1X.c_str()), THESAURUS_ICD10_1X_FIELD, THESAURUS_ICD10_LEN) ;
  videChamp((char*)(_Donnees._icpc2_2X.c_str()), THESAURUS_ICPC2_2X_FIELD, THESAURUS_ICPC2_LEN) ;
  videChamp((char*)(_Donnees._icd10_2X.c_str()), THESAURUS_ICD10_2X_FIELD, THESAURUS_ICD10_LEN) ;
  videChamp((char*)(_Donnees._icpc2_1Y.c_str()), THESAURUS_ICPC2_1Y_FIELD, THESAURUS_ICPC2_LEN) ;
  videChamp((char*)(_Donnees._icd10_1Y.c_str()), THESAURUS_ICD10_1Y_FIELD, THESAURUS_ICD10_LEN) ;
  videChamp((char*)(_Donnees._icpc2_2Y.c_str()), THESAURUS_ICPC2_2Y_FIELD, THESAURUS_ICPC2_LEN) ;
  videChamp((char*)(_Donnees._icd10_2Y.c_str()), THESAURUS_ICD10_2Y_FIELD, THESAURUS_ICD10_LEN) ;
}

// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSThesaurus::open()
{
	char tableName[] = "Clinical_Labels.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return (lastError) ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSThesaurus::Create()
{
	return true ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSThesaurus::Modify()
{
	return true ;
}

// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSThesaurus&
NSThesaurus::operator=(const NSThesaurus& src)
{
  if (this == &src)
    return *this ;

	_Donnees = src._Donnees ;

	return *this ;
}

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSThesaurus::operator==(const NSThesaurus& o)
{
  return (_Donnees == o._Donnees) ;
}
#endif

// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSThesaurusInfo::NSThesaurusInfo()
{
}

#ifndef _ENTERPRISE_DLL
// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiClasser
// -----------------------------------------------------------------------------
NSThesaurusInfo::NSThesaurusInfo(NSThesaurus *pContact)
{
	_Donnees = pContact->_Donnees ;
}
#endif

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSThesaurusInfo::NSThesaurusInfo(const NSThesaurusInfo& rv)
{
	_Donnees = rv._Donnees ;
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSThesaurusInfo::~NSThesaurusInfo()
{
}

// -----------------------------------------------------------------------------
// arrange the result "as a" Classer record for a given classification
// -----------------------------------------------------------------------------
string
NSThesaurusInfo::getClasserString(string sClassif)
{
  if (string("") == sClassif)
    sClassif = string("6CISP") ;

  string sReturn = string("") ;

  if (strlen(sClassif.c_str()) < BASE_SENS_LEN)
    return sReturn ;

  if (string("6CISP") == string(sClassif, 0, BASE_SENS_LEN))
  {
    addALaClasser(&sReturn, string(_Donnees._icpc2)) ;
    addALaClasser(&sReturn, string(_Donnees._icpc2_2)) ;
    addALaClasser(&sReturn, string(_Donnees._icpc2_1X)) ;
    addALaClasser(&sReturn, string(_Donnees._icpc2_2X)) ;
    addALaClasser(&sReturn, string(_Donnees._icpc2_1Y)) ;
    addALaClasser(&sReturn, string(_Donnees._icpc2_2Y)) ;
  }
  else if (string("6CIMA") == string(sClassif, 0, BASE_SENS_LEN))
  {
    addALaClasser(&sReturn, string(_Donnees._icd10)) ;
    addALaClasser(&sReturn, string(_Donnees._icd10_2)) ;
    addALaClasser(&sReturn, string(_Donnees._icd10_1X)) ;
    addALaClasser(&sReturn, string(_Donnees._icd10_2X)) ;
    addALaClasser(&sReturn, string(_Donnees._icd10_1Y)) ;
    addALaClasser(&sReturn, string(_Donnees._icd10_2Y)) ;
  }
  return sReturn ;
}

void
NSThesaurusInfo::addALaClasser(string* pResult, string sCode)
{
  if ((NULL == pResult) || (string("") == sCode))
    return ;

  string sAdaptedCode = sCode ;

  // Procedure codes start by '*' and are more than 3 chars long
  //
  if ('*' == sAdaptedCode[0])
  {
    sAdaptedCode[0] = '?' ;
    sAdaptedCode = string(sAdaptedCode, 0, 3) ;
  }

  if (string("") != *pResult)
    *pResult += string(";") ;

  *pResult += sAdaptedCode ;
}

// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSThesaurusInfo&
NSThesaurusInfo::operator=(const NSThesaurusInfo& src)
{
  if (this == &src)
    return *this ;

	_Donnees = src._Donnees ;

  return *this ;
}

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSThesaurusInfo::operator==(const NSThesaurusInfo& o)
{
  return (_Donnees == o._Donnees) ;
}

#ifdef _ENTERPRISE_DLL
void
NSThesaurusInfo::alimenteFiche(MYSQL_ROW *pRow)
{
  if ((MYSQL_ROW*) NULL == pRow)
    return ;

  _Donnees.metAZero() ;

  if ((*pRow)[THESAURUS_ID_FIELD - 1])
    _Donnees._iId		   = StringToInt((*pRow)[THESAURUS_ID_FIELD - 1]) ;
  if ((*pRow)[THESAURUS_ORIGIN_FIELD - 1])
    _Donnees._sOrigine = (*pRow)[THESAURUS_ORIGIN_FIELD - 1] ;
  if ((*pRow)[THESAURUS_IBUI_FIELD - 1])
    _Donnees._ibui		 = (*pRow)[THESAURUS_IBUI_FIELD - 1] ;
  if ((*pRow)[THESAURUS_FR_LABEL_FIELD - 1])
    _Donnees._labelFr	 = (*pRow)[THESAURUS_FR_LABEL_FIELD - 1] ;
  if ((*pRow)[THESAURUS_NL_LABEL_FIELD - 1])
    _Donnees._labelNl	 = (*pRow)[THESAURUS_NL_LABEL_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICPC2_FIELD - 1])
    _Donnees._icpc2		 = (*pRow)[THESAURUS_ICPC2_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICD10_FIELD - 1])
    _Donnees._icd10		 = (*pRow)[THESAURUS_ICD10_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICPC2_2_FIELD - 1])
    _Donnees._icpc2_2  = (*pRow)[THESAURUS_ICPC2_2_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICD10_2_FIELD - 1])
    _Donnees._icd10_2  = (*pRow)[THESAURUS_ICD10_2_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICPC2_1X_FIELD - 1])
    _Donnees._icpc2_1X = (*pRow)[THESAURUS_ICPC2_1X_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICD10_1X_FIELD - 1])
    _Donnees._icd10_1X = (*pRow)[THESAURUS_ICD10_1X_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICPC2_2X_FIELD - 1])
    _Donnees._icpc2_2X = (*pRow)[THESAURUS_ICPC2_2X_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICD10_2X_FIELD - 1])
    _Donnees._icd10_2X = (*pRow)[THESAURUS_ICD10_2X_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICPC2_1Y_FIELD - 1])
    _Donnees._icpc2_1Y = (*pRow)[THESAURUS_ICPC2_1Y_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICD10_1Y_FIELD - 1])
    _Donnees._icd10_1Y = (*pRow)[THESAURUS_ICD10_1Y_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICPC2_2Y_FIELD - 1])
    _Donnees._icpc2_2Y = (*pRow)[THESAURUS_ICPC2_2Y_FIELD - 1] ;
  if ((*pRow)[THESAURUS_ICD10_2Y_FIELD - 1])
    _Donnees._icd10_2Y = (*pRow)[THESAURUS_ICD10_2Y_FIELD - 1] ;
}

void
NSThesaurusInfo::alimenteFicheSentinelle(MYSQL_ROW *pRow)
{
  if ((MYSQL_ROW*) NULL == pRow)
    return ;

  _Donnees.metAZero() ;

  if ((*pRow)[1])
    _Donnees._labelFr = (*pRow)[1] ;
  if ((*pRow)[2])
    _Donnees._icpc2   = (*pRow)[2] ;
}

#endif

// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSEpiClassif
//
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Constructeur
// -----------------------------------------------------------------------------
NSEpiClassifData::NSEpiClassifData()
{
	// Met les champs de donn�es � z�ro
	metAZero() ;
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiClassifData::NSEpiClassifData(const NSEpiClassifData& rv)
{
  _sClassification = rv._sClassification ;
	_sCode           = rv._sCode ;
	_sLabel          = rv._sLabel ;
	_sChapter        = rv._sChapter ;
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiClassifData::~NSEpiClassifData()
{
}

// -----------------------------------------------------------------------------
// Op�rateur =
// -----------------------------------------------------------------------------
NSEpiClassifData&
NSEpiClassifData::operator=(const NSEpiClassifData& src)
{
  if (this == &src)
    return *this ;

	_sClassification = src._sClassification ;
	_sCode           = src._sCode ;
	_sLabel          = src._sLabel ;
	_sChapter        = src._sChapter ;

	return *this ;
}

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiClassifData::operator==(const NSEpiClassifData& o)
{
	if ((_sCode           == o._sCode)           &&
      (_sClassification == o._sClassification) &&
      (_sLabel          == o._sLabel)          &&
      (_sChapter        == o._sChapter))
		return 1 ;
	else
		return 0 ;
}

// -----------------------------------------------------------------------------
// Met � z�ro les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiClassifData::metAZero()
{
	_sClassification = string("") ;
	_sCode           = string("") ;
	_sLabel          = string("") ;
	_sChapter        = string("") ;
}

#ifndef _ENTERPRISE_DLL
// -----------------------------------------------------------------------------
//  Constructeur
// -----------------------------------------------------------------------------
NSEpiClassif::NSEpiClassif(NSSuper *pSuper)
             :NSEpiClassifInfo(), NSFiche(pSuper)
{
}

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiClassif::NSEpiClassif(const NSEpiClassif& rv)
             :NSEpiClassifInfo(rv), NSFiche(rv._pSuper)
{
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiClassif::~NSEpiClassif()
{
}

#ifdef _ENTERPRISE_DLL

void
NSEpiClassif::alimenteFiche(MYSQL_ROW *pRow)
{
  if ((MYSQL_ROW*) NULL == pRow)
    return ;

  _Donnees.metAZero() ;

  if ((*pRow)[CLASSIF_CLASSIF_FIELD - 1])
    _Donnees.setClassification((*pRow)[CLASSIF_CLASSIF_FIELD - 1]) ;
  if ((*pRow)[CLASSIF_CODE_FIELD - 1])
    _Donnees.setCode((*pRow)[CLASSIF_CODE_FIELD - 1]) ;
  if ((*pRow)[CLASSIF_LIBELLE_FIELD - 1])
	  _Donnees.setLabel((*pRow)[CLASSIF_LIBELLE_FIELD - 1]) ;
  if ((*pRow)[CLASSIF_CHAPITRE_FIELD - 1])
    _Donnees.setChapter((*pRow)[CLASSIF_CHAPITRE_FIELD - 1]) ;
}

#else

// -----------------------------------------------------------------------------
// Transf�re le contenu de pRecBuff dans les variables de la fiche
// -----------------------------------------------------------------------------
void
NSEpiClassif::alimenteFiche()
{
  char classification[CLASSIF_CLASSIF_LEN + 1] ;
  char code[CLASSIF_CODE_LEN + 1] ;  char libelle[CLASSIF_LIBELLE_LEN + 1] ;  char chapitre[CLASSIF_CHAPITRE_LEN + 1] ;

  alimenteChamp(classification, CLASSIF_CLASSIF_FIELD,  CLASSIF_CLASSIF_LEN) ;
  alimenteChamp(code, 		      CLASSIF_CODE_FIELD,     CLASSIF_CODE_LEN) ;
  alimenteChamp(libelle,        CLASSIF_LIBELLE_FIELD,  CLASSIF_LIBELLE_LEN) ;
  alimenteChamp(chapitre,  	    CLASSIF_CHAPITRE_FIELD, CLASSIF_CHAPITRE_LEN) ;

  _Donnees.setClassification(classification) ;
  _Donnees.setCode(code) ;
  _Donnees.setLabel(libelle) ;
  _Donnees.setChapter(chapitre) ;
}

// -----------------------------------------------------------------------------
// Transf�re le contenu des valeurs de la fiche dans pRecBuff
// -----------------------------------------------------------------------------
void
NSEpiClassif::videFiche()
{
  videChamp((char*)(_Donnees.getClassification().c_str()), CLASSIF_CLASSIF_FIELD,  CLASSIF_CLASSIF_LEN) ;
  videChamp((char*)(_Donnees.getCode().c_str()),           CLASSIF_CODE_FIELD,     CLASSIF_CODE_LEN) ;
  videChamp((char*)(_Donnees.getLabel().c_str()),          CLASSIF_LIBELLE_FIELD,  CLASSIF_LIBELLE_LEN) ;
  videChamp((char*)(_Donnees.getChapter().c_str()),        CLASSIF_CHAPITRE_FIELD, CLASSIF_CHAPITRE_LEN) ;
}

// -----------------------------------------------------------------------------
// Ouvre la table primaire et les index secondaires
// -----------------------------------------------------------------------------
DBIResult
NSEpiClassif::open()
{
	char tableName[] = "CLASSIF.DB" ;

	// Appelle la fonction open() de la classe de base pour ouvrir l'index primaire
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return(lastError) ;
}

#endif

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiClassif::Create()
{
	return true ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool
NSEpiClassif::Modify()
{
	return true ;
}

// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiClassif&
NSEpiClassif::operator=(const NSEpiClassif& src)
{
  if (&src == this)
    return *this ;

	_Donnees = src._Donnees ;

	return *this ;
}


// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiClassif::operator==(const NSEpiClassif& o)
{
  return (_Donnees == o._Donnees) ;
}


bool
NSEpiClassif::initArrayFromCodeList(string sClassification, ClasseStringVector* pVectCodes, NSEpiClassifArray* pResultArray)
{
  if (((ClasseStringVector*) NULL == pVectCodes) ||
      ((NSEpiClassifArray*)  NULL == pResultArray))
    return false ;

  pResultArray->vider() ;

  if (pVectCodes->empty())
    return true ;

  for (iterClassString itCodes = pVectCodes->begin() ; pVectCodes->end() != itCodes ; itCodes++)
  {
    bool bSuccess = false ;

    if (strlen((*itCodes)->getItem().c_str()) <= CLASSIF_CODE_LEN)
    {
      CURProps curProps ;
      /* DBIResult lastError = */ DbiGetCursorProps(PrendCurseur(), curProps) ;
      Byte* pIndexRec = new Byte[curProps.iRecBufSize] ;
      memset(pIndexRec, 0, curProps.iRecBufSize) ;
      DbiPutField(PrendCurseur(), CLASSIF_CLASSIF_FIELD, pIndexRec, (Byte*) sClassification.c_str()) ;
      DbiPutField(PrendCurseur(), CLASSIF_CODE_FIELD,    pIndexRec, (Byte*) (*itCodes)->getItem().c_str()) ;

      lastError = chercheClefComposite("",
                                       0,
                                       keySEARCHEQ,
                                       dbiWRITELOCK,
                                       pIndexRec) ;
      delete[] pIndexRec ;

      if (lastError != DBIERR_NONE)
      {
        string sErrorText = string("Cannot find ") + (*itCodes)->getItem() + string(" in Classif.db") ;
        _pSuper->trace(&sErrorText, 1, NSSuper::trError) ;
      }
      else
      {
        lastError = getRecord() ;
        if (lastError != DBIERR_NONE)
        {
          string sErrorText = string("Problem reading ") + (*itCodes)->getItem() + string(" in Classif.db") ;
          _pSuper->trace(&sErrorText, 1, NSSuper::trError) ;
        }
        else
          bSuccess = true ;
      }
    }

    if (bSuccess)
      pResultArray->push_back(new NSEpiClassifInfo(this)) ;
    else
      pResultArray->push_back(new NSEpiClassifInfo()) ;
  }

  return true ;
}
#endif // #ifndef _ENTERPRISE_DLL

// -----------------------------------------------------------------------------
// Constructeur par d�faut
// -----------------------------------------------------------------------------
NSEpiClassifInfo::NSEpiClassifInfo()
{
}

#ifndef _ENTERPRISE_DLL
// -----------------------------------------------------------------------------
// Constructeur � partir d'un NSEpiClasser
// -----------------------------------------------------------------------------
NSEpiClassifInfo::NSEpiClassifInfo(const NSEpiClassif *pContact)
{
	_Donnees = pContact->_Donnees ;
}
#endif

// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSEpiClassifInfo::NSEpiClassifInfo(const NSEpiClassifInfo& rv)
{
	_Donnees = rv._Donnees ;
}

// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
NSEpiClassifInfo::~NSEpiClassifInfo()
{
}

// -----------------------------------------------------------------------------
// Get ICPC category
// Based ICPC's design : symptoms < 30, pathologies >= 70, procedures in-between
// -----------------------------------------------------------------------------
ICPC_CATEGORY
NSEpiClassifInfo::getIcpcCategory()
{
  // Valid ICPC codes must be in the form Char Digit Digit (ex : R05)
  //
  if (strlen(_Donnees.getCode().c_str()) < 3)
    return IcpcUndefined ;

  if (!isdigit(_Donnees.getCode()[1]) || !isdigit(_Donnees.getCode()[2]))
    return IcpcUndefined ;

  if (_Donnees.getCode()[1] < '3')
    return IcpcSymptom ;

  if (_Donnees.getCode()[1] >= '7')
    return IcpcPathology ;

  return IcpcProcedure ;
}

ICPC_PATHOLOGY
NSEpiClassifInfo::getIcpcPathology()
{
  return IcpcUndefinedPatho ;
}

// -----------------------------------------------------------------------------
// Op�rateur d'affectation
// -----------------------------------------------------------------------------
NSEpiClassifInfo&
NSEpiClassifInfo::operator=(const NSEpiClassifInfo& src)
{
  if (&src == this)
    return *this ;

	_Donnees = src._Donnees ;

	return *this ;
}

#ifndef _ENTERPRISE_DLL
NSEpiClassifInfo&
NSEpiClassifInfo::operator=(const NSEpiClassif& src)
{
  _Donnees = src._Donnees ;

	return *this ;
}
#endif

// -----------------------------------------------------------------------------
// Op�rateur de comparaison
// -----------------------------------------------------------------------------
int
NSEpiClassifInfo::operator==(const NSEpiClassifInfo& o)
{
  return (_Donnees == o._Donnees) ;
}

#ifdef _ENTERPRISE_DLL
void
NSEpiClassifInfo::alimenteFiche(MYSQL_ROW *pRow)
{
  if ((MYSQL_ROW*) NULL == pRow)
    return ;

  _Donnees.metAZero() ;

  if ((*pRow)[CLASSIF_CLASSIF_FIELD - 1])
    _Donnees.setClassification((*pRow)[CLASSIF_CLASSIF_FIELD - 1]) ;
  if ((*pRow)[CLASSIF_CODE_FIELD - 1])
    _Donnees.setCode((*pRow)[CLASSIF_CODE_FIELD - 1]) ;
  if ((*pRow)[CLASSIF_LIBELLE_FIELD - 1])
	  _Donnees.setLabel((*pRow)[CLASSIF_LIBELLE_FIELD - 1]) ;
  if ((*pRow)[CLASSIF_CHAPITRE_FIELD - 1])
    _Donnees.setChapter((*pRow)[CLASSIF_CHAPITRE_FIELD - 1]) ;
}
#endif

NSEpiClassifInfoArray::~NSEpiClassifInfoArray()
{
  vider() ;
}

bool
NSEpiClassifInfoArray::ajouteElement(NSEpiClassifInfo *pElement)
{
  // Si l'�l�ment existe d�j�, on ne fait rien
  if (false == empty())
    for (NSEpiClassifInfoIter i = begin() ; end() != i ; i++)
      if (*(*i) == *pElement)
        return false ;

  push_back(pElement) ;

  return true ;
}

void
NSEpiClassifInfoArray::vider()
{
  if (empty())
    return ;

  for (NSEpiClassifInfoIter i = begin() ; end() != i ; )
  {
    delete (*i) ;
    erase(i) ;
  }
}

// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes de NSEpiClassifArray
//
// -----------------------------------------------------------------------------
NSEpiClassifArray::NSEpiClassifArray()
                  :NSEpiClassifInfoVector()
{
  _sFileName = string("") ;
}

NSEpiClassifArray::NSEpiClassifArray(string sFile)
  : NSEpiClassifInfoVector()
{
  _sFileName = sFile ;
}

NSEpiClassifArray::~NSEpiClassifArray()
{
  vider() ;
}

bool
NSEpiClassifArray::fillArray()
{
  ifstream  inFile ;
  string    line ;

  inFile.open(_sFileName.c_str()) ;
  if (!inFile)
    return false ;

  while (!inFile.eof())
  {
    getline(inFile, line) ;
    if (line != "")
    {
      // on ajoute dans l'EpiClassifArray ce qu'on vient de lire dans le fichier
      string  sClassif  = "" ;
      string  sCode     = "" ;
      string  sLibelle  = "" ;
      string  sChapitre = "" ;

      // recherche de la classif
      // le premier param�tre est l'ID dans la table, c'est pour cela qu'on
      // commence � partir de la premi�re tabulation
      size_t  posBeg = line.find("\t") ;
      size_t  posEnd = line.find("\t", posBeg + 1) ;
      if ((posEnd != string::npos) && (posBeg != string::npos) && (posBeg < posEnd))
        sClassif = string(line, posBeg + 1, posEnd - (posBeg + 1)) ;
      else
        return false ;

      // recherche du code
      posBeg  = posEnd ;
      posEnd  = line.find("\t", posBeg + 1) ;
      if ((posEnd != string::npos) && (posBeg != string::npos) && (posBeg < posEnd))
        sCode = string(line, posBeg + 1, posEnd - (posBeg + 1)) ;
      else
        return false ;

      // recherche du libelle
      posBeg  = posEnd ;
      posEnd  = line.find("\t", posBeg + 1) ;
      if ((posEnd != string::npos) && (posBeg != string::npos) && (posBeg < posEnd))
        sLibelle = string(line, posBeg + 1, posEnd - (posBeg + 1)) ;
      else
        return false ;

      // recherche du chapitre
      posBeg  = posEnd ;
      posEnd  = strlen(line.c_str()) ;
      if ((posEnd != string::npos) && (posBeg != string::npos) && (posBeg < posEnd))
        sChapitre = string(line, posBeg + 1, posEnd - (posBeg + 1)) ;
      else
        return false ;

      if ((sClassif != "") && (sCode != "") && (sLibelle != ""))
      {
        NSEpiClassifInfo *pEpiClassifInfoTemp = new NSEpiClassifInfo() ;

        pEpiClassifInfoTemp->setClassification(sClassif) ;
        pEpiClassifInfoTemp->setCode(sCode) ;
        pEpiClassifInfoTemp->setLabel(sLibelle) ;
        pEpiClassifInfoTemp->setChapter(sChapitre) ;

        push_back(pEpiClassifInfoTemp) ;
      }
      else
        return false ;
    }
  }
  inFile.close() ;
  return true ;
}

bool
NSEpiClassifArray::searchKey(string sClassif, string sCode)
{
  for (NSEpiClassifInfoIter iter = begin() ; end() != iter ; iter++)
  {
    if (((*iter)->getClassification() == sClassif)  &&
        ((*iter)->getCode()           == sCode))
    {
      _Donnees = (*iter)->_Donnees ;
      return true ;
    }
  }
  return false ;
}

bool
NSEpiClassifArray::vider()
{
  if (empty())
    return true ;

  for (NSEpiClassifInfoIter iter = begin() ; end() != iter ; )
  {
    delete (*iter) ;
    erase(iter) ;
  }

  return true ;
}


// -----------------------------------------------------------------------------
//
// Impl�mentation des m�thodes NSCodPrestArray
//
// -----------------------------------------------------------------------------


/*
// -----------------------------------------------------------------------------
// Constructeur copie
// -----------------------------------------------------------------------------
NSCodPrestArray::NSCodPrestArray(NSCodPrestArray& rv)
  : NSFicheCodPrestArray()
{
  for (NSCodPrestIter i = rv.begin() ; i != rv.end() ; i++)
    push_back(new NSCodPrestInfo(*(*i))) ;
}


// -----------------------------------------------------------------------------
// Destructeur
// -----------------------------------------------------------------------------
void
NSCodPrestArray::vider()
{
  for (NSCodPrestIter i = begin() ; i != end() ; )
  {
    delete (*i) ;
    erase(i) ;
  }
}


NSCodPrestArray::~NSCodPrestArray()
{
	vider() ;
}
*/

//////////////////////////// fin du fichier EpTables.cpp

