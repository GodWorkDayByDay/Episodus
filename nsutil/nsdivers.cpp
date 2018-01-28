//---------------------------------------------------------------------------
//    NSDIVERS.CPP
//    PA   juillet 94
//  Utilitaires de travail sur les comptes rendus
//---------------------------------------------------------------------------
//
// #include <string.h>
#include <string.stl>
//#include <services\private\cstring.h>
#include <stdlib.h>

#include "partage\nsperson.h"
#include "nsutil\nsdivers.h"

//-------------------------------------------------------------------------
//----------------------- METHODES DE NSString ----------------------------
//-------------------------------------------------------------------------

NSString::NSString(string s)
{
	donnee = s;
}

NSString::~NSString()
{
}

NSString::NSString(NSString& rv)
{
	donnee = rv.donnee;
}

NSString&
NSString::operator=(NSString src)
{
	donnee = src.donnee;
   return *this;
}

//-------------------------------------------------------------------------
//----------------------- METHODES DE NSStringArray ---------------------
//-------------------------------------------------------------------------

// constructeur copie

NSStringArray::NSStringArray(NSStringArray& rv)
					  : NSStringVector()
{
	if (!(rv.empty()))
	   for (NSStringIter i = rv.begin(); i != rv.end(); i++)
			 	push_back(new NSString(*(*i)));
}

// fonction vider()
void
NSStringArray::vider()
{
	for (NSStringIter i = begin(); i != end(); )
   {
   	delete *i;
      erase(i);
   }
}

// destructeur
NSStringArray::~NSStringArray()
{
	vider();
}

// Op�rateur d'affectation
NSStringArray&
NSStringArray::operator=(NSStringArray src)
{
	vider();
   for (NSStringIter i = src.begin(); i != src.end(); i++)
			 	push_back(new NSString(*(*i)));
	return *this;
}

/*********************** suite : anciennes m�thodes de nsdivers.cpp *************/

// UINT valide_dernier(NSPatient* pPatient, unsigned char *message,
// 													  UINT *reparable)
//---------------------------------------------------------------------------
//  Fonction  : Le champ "dernier cr" de la fiche patient est-il valide ?
//	 Variables : message   -> message explicatif en cas de d�faut (30 car.)
//					 reparable -> d�faut r�parable ou non
//	 Retour	  : 0 -> dernier est correct
//					 1 -> dernier est correct, il n'y a pas de compte rendu
//					 2 -> dernier est incorrect
//
//  Cr�� le 19/11/1991  Derni�re mise � jour le 29/07/1994
/*UINT valide_dernier(NSPatient* pPatient, unsigned char *message,
													  UINT *reparable)
{
  unsigned int  i;
  unsigned char debfi[3], debzo[3], debch[4], finfi[3], finzo[3], finch[4];
  signed   int  ndebfi, ndebzo, ndebch, nfinfi, nfinzo, nfinch;

  // La zone "dernier cr" n'est-elle compos�e que de chiffres ?
  //
  for (i = 0; i < 14; i++) {
		if ((pPatient->pDonnees->dernier[i] < '0') || (pPatient->pDonnees->dernier[i] > '9')) {
			strcpy(message, "Champ DERNIER non num�rique");
			*reparable = 0;
			return(2);
		}
  }

  // Y-a-t-il un dernier compte-rendu ?
  //
  if (strcmp(pPatient->pDonnees->dernier, "01010000101000") == 0) return(1);

  // Position du dernier compte-rendu
  //
  debfi[0] = pPatient->pDonnees->dernier[0];  debfi[1] = pPatient->pDonnees->dernier[1];  debfi[2] = '\0';
  debzo[0] = pPatient->pDonnees->dernier[2];  debzo[1] = pPatient->pDonnees->dernier[3];  debzo[2] = '\0';
  debch[0] = pPatient->pDonnees->dernier[4];  debch[1] = pPatient->pDonnees->dernier[5];  debch[2] = pPatient->pDonnees->dernier[6];  debch[3] = '\0';
  finfi[0] = pPatient->pDonnees->dernier[7];  finfi[1] = pPatient->pDonnees->dernier[8];  finfi[2] = '\0';
  finzo[0] = pPatient->pDonnees->dernier[9];  finzo[1] = pPatient->pDonnees->dernier[10]; finzo[2] = '\0';
  finch[0] = pPatient->pDonnees->dernier[11]; finch[1] = pPatient->pDonnees->dernier[12]; finch[2] = pPatient->pDonnees->dernier[13]; finch[3] = '\0';
  ndebfi = 10 *  (debfi[0] - 48) + debfi[1] - 48;
  ndebzo = 10 *  (debzo[0] - 48) + debzo[1] - 48;
  ndebch = 100 * (debch[0] - 48) + 10 * (debch[1] - 48) + debch[2] - 48;
  nfinfi = 10 *  (finfi[0] - 48) + finfi[1] - 48;
  nfinzo = 10 *  (finzo[0] - 48) + finzo[1] - 48;
  nfinch = 100 * (finch[0] - 48) + 10 * (finch[1] - 48) + finch[2] - 48;

  // Le pointeur de d�but de CR est il plausible ?
  //
  if ((ndebfi < 1) || (ndebzo < 1) || (ndebzo > 5) || (ndebch < 1) || (ndebch > 255)) {
	  strcpy(message, "Champ DERNIER erron� (d�but)  ");
	  *reparable = 0;
	  return(2);
  }

  // Le pointeur de fin de CR est il plausible ?
  //
  if ((nfinfi < 1) || (nfinzo < 1) || (nfinzo > 5) || (nfinch < 1) || (nfinch > 255)) {
	  strcpy(message, "Champ DERNIER erron� (fin)    ");
	  *reparable = 1;
	  return(2);
  }

  // Le pointeur de fin de CR est il apr�s d�but ?
  //
  if ((nfinfi < ndebfi) ||
		((nfinfi == ndebfi) && ((nfinzo < ndebzo) ||
										((nfinzo == ndebzo) && (nfinch < ndebch))))) {
	  strcpy(message, "Champ DERNIER erron� fin < deb");
	  *reparable = 1;
	  return(2);
  }
  strcpy(message, "Champ DERNIER valide          "); 
  return(0);
} */

// UINT valide_cr(string* pCRString, unsigned char *message,
// 											 UINT *reparable)
//---------------------------------------------------------------------------
//  Fonction  : Le compte rendu contenu dans pCRString est-il valide ?
//	 Variables : message   -> message explicatif en cas de d�faut (30 car.)
//					 reparable -> d�faut r�parable ou non
//	 Retour	  : 0 -> dernier est correct
//					 1 -> dernier est correct, il n'y a pas de compte rendu
//					 2 -> dernier est incorrect
//
//  Cr�� le 19/11/1991  Derni�re mise � jour le 16/08/1994
UINT valide_cr(string* pCRString, char *message, UINT *reparable)
{
  UINT i, j, annee, mois, jour;

  if ((*pCRString)[0] != (unsigned char) 2) {
	  strcpy(message, "Ent�te de CR erron� (CHR(2))  ");
	  *reparable = 0;
	  return(10);
  }
  if (((*pCRString)[4] != 'E') && ((*pCRString)[4] != 'H') && ((*pCRString)[4] != '0')) {
	  strcpy(message, "Ent�te de CR erron� (Contexte)");
	  *reparable = 0;
	  return(10);
  }
  for (i = 5; i < 13; i++) {
		if (!isdigit((*pCRString)[i])) {
			strcpy(message, "Ent�te de CR erron� (Date)    ");
			*reparable = 0;
			return(10);
		}
  }
  annee = atoi((string(*pCRString, 5, 4)).c_str());
  mois  = atoi((string(*pCRString, 9, 2)).c_str());
  jour  = atoi((string(*pCRString, 11, 2)).c_str());
  if ((annee < 1900) || (annee > 2010)) {
	  strcpy(message, "Ent�te de CR erron� (Ann�e)   ");
	  *reparable = 1;
	  return(10);
  }
  if ((mois < 1) || (mois > 12)) {
	  strcpy(message, "Ent�te de CR erron� (Mois)    ");
	  *reparable = 1;
	  return(10);
  }
  if ((jour < 1) || (jour > 31)) {
	  strcpy(message, "Ent�te de CR erron� (Jour)    ");
	  *reparable = 1;
	  return(10);
  }
  strcpy(message, "Ent�te de CR OK               ");
  return(0);
}


