//---------------------------------------------------------------------------
//    NSPERSON.CPP
//    KRZISCH PH.   janvier 92
//  Impl�mentation de objets NAUTILUS
//---------------------------------------------------------------------------
#include <utility.h>
#include <mem.h>
#include <string.h>
#include <cstring.h>

//using namespace std;

#include "nautilus\nssuper.h"
#include "partage\nsdivfct.h"
#include "nscompta\nscps.h"

//***************************************************************************
// Impl�mentation des m�thodes NSTransaction
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur
//---------------------------------------------------------------------------
NSTransacData::NSTransacData()
{
	//
	// Met les champs de donn�es � z�ro
	//
	metAZero();
}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSTransacData::NSTransacData(NSTransacData& rv)
{
	strcpy(code, 		rv.code);
	strcpy(operateur, rv.operateur);
	strcpy(dateDeb,   rv.dateDeb);
   strcpy(dateFin,   rv.dateFin);
}

//---------------------------------------------------------------------------
//  Destructeur
//---------------------------------------------------------------------------
NSTransacData::~NSTransacData()
{
}

//---------------------------------------------------------------------------
//  Op�rateur =
//---------------------------------------------------------------------------
NSTransacData&
NSTransacData::operator=(NSTransacData src)
{
	strcpy(code, 		src.code);
	strcpy(operateur, src.operateur);
	strcpy(dateDeb,   src.dateDeb);
   strcpy(dateFin,   src.dateFin);

	return *this;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison
//---------------------------------------------------------------------------
int
NSTransacData::operator == ( const NSTransacData& o )
{
	if (strcmp(code, o.code) == 0)
		return 1;
	else
		return 0;
}

//---------------------------------------------------------------------------
//  Met � blanc les variables de la fiche
//---------------------------------------------------------------------------
void
NSTransacData::metABlanc()
{
	//
	// Met les champs de donn�es � blanc
	//
	memset(code, 		' ', TRAN_CODE_LEN);
	memset(operateur, ' ', TRAN_OPERATEUR_LEN);
	memset(dateDeb, 	' ', TRAN_DATE_DEB_LEN);
   memset(dateFin, 	' ', TRAN_DATE_FIN_LEN);
}

//---------------------------------------------------------------------------
//  Met � z�ro les variables de la fiche
//---------------------------------------------------------------------------
void
NSTransacData::metAZero()
{
	//
	// Met les champs de donn�es � z�ro
	//
	memset(code, 		0, TRAN_CODE_LEN + 1);
	memset(operateur, 0, TRAN_OPERATEUR_LEN + 1);
	memset(dateDeb, 	0, TRAN_DATE_DEB_LEN + 1);
   memset(dateFin, 	0, TRAN_DATE_FIN_LEN + 1);
}

//---------------------------------------------------------------------------
//  Constructeur
//---------------------------------------------------------------------------
NSTransaction::NSTransaction(NSSuper* pSuper) : NSFiche(pSuper)
{
	//
	// Cr�e un objet de donn�es
	//
	pDonnees = new NSTransacData();
}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSTransaction::NSTransaction(NSTransaction& rv) : NSFiche(rv.pSuper)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSTransacData();
	//
	// Copie les valeurs du NSTransaction d'origine
	//
	*pDonnees = *(rv.pDonnees);
}

//---------------------------------------------------------------------------
//  Destructeur
//---------------------------------------------------------------------------
NSTransaction::~NSTransaction()
{
	delete pDonnees;
}

//---------------------------------------------------------------------------
//  Fonction :  	NSTransaction::alimenteFiche()
//
//  Description : Transf�re le contenu de pRecBuff dans les variables de
//             	la fiche
//---------------------------------------------------------------------------
void
NSTransaction::alimenteFiche()
{
   alimenteChamp(pDonnees->code, 	  TRAN_CODE_FIELD, 	  	TRAN_CODE_LEN);
	alimenteChamp(pDonnees->operateur, TRAN_OPERATEUR_FIELD, TRAN_OPERATEUR_LEN);
   alimenteChamp(pDonnees->dateDeb,   TRAN_DATE_DEB_FIELD, 	TRAN_DATE_DEB_LEN);
   alimenteChamp(pDonnees->dateFin,   TRAN_DATE_FIN_FIELD, 	TRAN_DATE_FIN_LEN);
}

//---------------------------------------------------------------------------
//  Fonction :   	NSTransaction::videFiche()
//
//  Description : Transf�re le contenu des valeurs de la fiche dans pRecBuff
//---------------------------------------------------------------------------
void
NSTransaction::videFiche()
{
   videChamp(pDonnees->code, 	  	 TRAN_CODE_FIELD, 	  TRAN_CODE_LEN);
	videChamp(pDonnees->operateur, TRAN_OPERATEUR_FIELD, TRAN_OPERATEUR_LEN);
   videChamp(pDonnees->dateDeb,   TRAN_DATE_DEB_FIELD,  TRAN_DATE_DEB_LEN);
   videChamp(pDonnees->dateFin,   TRAN_DATE_FIN_FIELD,  TRAN_DATE_FIN_LEN);
}

bool
NSTransaction::fermeTransaction()
{
	bool onDoitFermer = false;

   if (!isOpen)
   {
   	lastError = open();
      if (lastError != DBIERR_NONE)
		{
			erreur("Il n'est pas possible d'ouvrir le fichier des transactions.", 0, lastError);
			return false;
		}
      onDoitFermer = true;
   }
   //
   // Recherche de la fiche transaction
   //
   lastError = chercheClef(&(pSuper->sTransaction),
   								"",
                           0,
                           keySEARCHEQ,
                           dbiWRITELOCK);
   if (lastError != DBIERR_NONE)
   {
   	erreur("Il n'est pas possible de trouver la transaction en cours au sein du fichier des transactions.", 0, lastError);
      return false;
   }
   lastError = getRecord();
   if (lastError != DBIERR_NONE)
   {
   	erreur("Le fichier des transactions est d�fectueux.", 0, lastError);
      return false;
   }
   //
   // Inscription de la date de fin
   //
   char date[9];
   donne_date_duJour(date);
   char heure[7];
   donne_heure(heure);
   strcpy(pDonnees->dateFin, date);
   strncat(pDonnees->dateFin, heure, 4);
   //
   // Mise � jour de la fiche
   //
   lastError = modifyRecord(TRUE);
   if (lastError != DBIERR_NONE)
   {
   	erreur("Il n'est pas possible de mettre � jour le fichier des transactions.", 0, lastError);
      return false;
   }

   if (onDoitFermer)
   {
   	lastError = close();
      if (lastError != DBIERR_NONE)
			erreur("Il n'est pas possible de fermer le fichier des transactions.", 0, lastError);
   }

   pSuper->sTransaction = "";

   return true;
}

bool
NSTransaction::nouvelleTransaction()
{
   bool onDoitFermer = false;

   if (pSuper->sTransaction != "")
   	fermeTransaction();

   if (!isOpen)
   {
   	lastError = open();
      if (lastError != DBIERR_NONE)
		{
			erreur("Il n'est pas possible d'ouvrir le fichier des transactions.", 0, lastError);
			return false;
		}
      onDoitFermer = true;
   }
	//
   // Prise du nouveau code
   //
   if (!DonneNouveauCode())
   	return false;
   //
   // Inscription du code de l'utilisateur
   //
   strcpy(pDonnees->operateur, pSuper->pUtilisateur->getszNss());
   //
   // Inscription de la date de d�but
   //
   char date[9];
   donne_date_duJour(date);
   char heure[7];
   donne_heure(heure);
   strcpy(pDonnees->dateDeb, date);
   strncat(pDonnees->dateDeb, heure, 4);
   //
   // Mise � jour de la fiche
   //
   lastError = modifyRecord(TRUE);
   if (lastError != DBIERR_NONE)
   {
   	erreur("Il n'est pas possible de mettre � jour le fichier des transactions.", 0, lastError);
      return false;
   }

   if (onDoitFermer)
   {
   	lastError = close();
      if (lastError != DBIERR_NONE)
			erreur("Il n'est pas possible de fermer le fichier des transactions.", 0, lastError);
   }

   pSuper->sTransaction = string(pDonnees->code);

   return true;
}

bool
NSTransaction::DonneNouveauCode()
{
   char compteur[TRAN_CODE_LEN + 1];
   //
   // Positionnement � la fin du fichier
   //
   lastError = fin(dbiREADLOCK);
   if ((lastError == DBIERR_EOF) || (lastError == DBIERR_BOF))
   {
      int i = 0;
      for (; i < TRAN_CODE_LEN - 1; i++)
      	compteur[i] = '0';
      compteur[i++] = '1';
      compteur[i]   = '\0';
   }
   else if (lastError != DBIERR_NONE)
	{
		erreur("Le fichier des transactions est endommag�.", 0, lastError);
		return false;
	}
   else
   {
   	//
		// R�cup�ration de l'enregistrement
		//
		lastError = getRecord();
   	if (lastError != DBIERR_NONE)
		{
			erreur("Le fichier des transactions est endommag�.", 0, lastError);
			return false;
		}
		strcpy(compteur, pDonnees->code);
		//
		// Incr�mentation du compteur
		//
		int j;
		bool calculer = true;
		int i = strlen(compteur) - 1;
		while (calculer)
   	{
   		j = (int) compteur[i];
      	j++;
      	if (((j >= '0') && (j <= '9')) || ((j >= 'A') && (j <= 'Z')))
      	{
      		compteur[i] = (char) j;
         	calculer = false;
      	}
      	else if ((j > '9') && (j < 'A'))
      	{
      		compteur[i] = 'A';
         	calculer = false;
      	}
      	else
      	{
      		compteur[i] = '0';
         	if (i == 0)
         	{
         		erreur("Compteur de transactions satur�.", 0, 0);
            	return false;
         	}
         	i--;
      	}
		}
   }
   pDonnees->metAZero();
   strcpy(pDonnees->code, compteur);
   //
   // On ajoute imm�diatement la fiche pour r�server le num�ro de transaction
   //
   appendRecord();
   if (lastError != DBIERR_NONE)
	{
		erreur("Le fichier des transactions ne peut plus recevoir ne nouveaux enregistrements.", 0, lastError);
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
//  Fonction :  	NSTransaction::getRecord()
//
//  Description : Prend l'enregistrement en cours et assigne la valeur des
//             	champs aux variables membres de la classe.
//
//  Returns:   	PXERR_, s'il y a lieu
//---------------------------------------------------------------------------
DBIResult
NSTransaction::getPatRecord()
{
	//
	// La table est-elle ouverte ?
	//
	if (!isOpen)
	  return(lastError = ERROR_TABLENOTOPEN);
	//
	// Appel de la classe de base pour r�cup�rer l'enregistrement.
	//
	lastError = getDbiRecord(dbiWRITELOCK);

	return(lastError);
}

//---------------------------------------------------------------------------
//  Fonction :  	NSTransaction::open()
//
//  Description :	Ouvre la table primaire et les index secondaires
//
//  Returns :		PXERR_, s'il y a lieu
//---------------------------------------------------------------------------
DBIResult
NSTransaction::open()
{
	char tableName[] = "TRANSAC.DB";
	//
	// Appelle la fonction open() de la classe de base pour ouvrir
	// l'index primaire
	//
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL);
	return(lastError);
}

//---------------------------------------------------------------------------
//  Function:  NSPatholog::Create()
//
//---------------------------------------------------------------------------
bool
NSTransaction::Create()
{
	return true;
}

//---------------------------------------------------------------------------
//  Function:  NSPatholog::Modify()
//
//---------------------------------------------------------------------------
bool
NSTransaction::Modify()
{
	return true;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSTransaction&
NSTransaction::operator=(NSTransaction src)
{
	*pDonnees = *(src.pDonnees);
	return *this;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison
//---------------------------------------------------------------------------
int
NSTransaction::operator == ( const NSTransaction& o )
{
	 return (*pDonnees == *(o.pDonnees));
}

//---------------------------------------------------------------------------
//  Fonction:		NSTransacInfo::NSTransacInfo()
//
//  Description:	Constructeur par d�faut
//---------------------------------------------------------------------------
NSTransacInfo::NSTransacInfo()
{
	// Cr�e l'objet de donn�es
	pDonnees = new NSTransacData();
}

//---------------------------------------------------------------------------
//  Fonction:		NSTransacInfo::NSTransacInfo(NSTransaction*)
//
//  Description:	Constructeur � partir d'un NSTransaction
//---------------------------------------------------------------------------
NSTransacInfo::NSTransacInfo(NSTransaction* pTransac)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSTransacData();
	//
	// Copie les valeurs du NSTransaction
	//
	*pDonnees = *(pTransac->pDonnees);
}

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSTransacInfo::NSTransacInfo(NSTransacInfo& rv)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSTransacData();
	//
	// Copie les valeurs du NSTransacInfo d'origine
	//
	*pDonnees = *(rv.pDonnees);
}

//---------------------------------------------------------------------------
//  Destructeur
//---------------------------------------------------------------------------
NSTransacInfo::~NSTransacInfo()
{
	delete pDonnees;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSTransacInfo&
NSTransacInfo::operator=(NSTransacInfo src)
{
	*pDonnees = *(src.pDonnees);
	return *this;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison
//---------------------------------------------------------------------------
int NSTransacInfo::operator == ( const NSTransacInfo& o )
{
	 return (*pDonnees == *(o.pDonnees));
}

