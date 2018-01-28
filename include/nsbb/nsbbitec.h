//---------------------------------------------------------------------------
//    NSBigBro.H
//
//  Contient la d�claration de NSBigBrother, gestionnaire g�n�ral des
//  applications NAUTILUS.
//  KP
//  Cr�ation : sept 93         Derni�re mise � jour : mars 94
//---------------------------------------------------------------------------
#ifndef __NSBBITEC_H
#define __NSBBITEC_H

#include <classlib\arrays.h>
#include <cstring.h>

#include "partage\nsglobal.h"
#include "ns_sgbd\nsfiche.h"
#include "nssavoir\nsguide.h"
//#include "nsbb\nsbig.h"
//#include "nslesion.h"

#ifndef __NSDLG_H
	class NSBBFonction;
#endif

//---------------------------------------------------------------------------
//
// Structure de classement des BBItem fils d'un BBItem donn�
//
//---------------------------------------------------------------------------
class BBFilsPhraseItem {

	  public :

	  //NSSuper*			pSuperviseur;
	  NSSmallBrother*	pBigBoss;
     BOOL				bTemporaire;	// Constitution d'un code avec marqueurs de l�sions

	  char				szNom[BB_CODE_LEN+1]; // Code de la fiche Paradox

	  string 			sEtiquette; 			 // Etiquette de la branche

	  string 			sCode;     				 // Codage de l'item
	  string 			sPonct;    				 // Ponctuation terminale

	  // constructeurs
	  BBFilsPhraseItem(NSSmallBrother*	pBig = 0);
	  BBFilsPhraseItem(const BBFilsPhraseItem& src);

	  BBFilsPhraseItem& operator=(BBFilsPhraseItem src);
	  int operator == ( const BBFilsPhraseItem& o );
};

//---------------------------------------------------------------------------
// Matrice dynamique de BBFilsPhraseItem
//---------------------------------------------------------------------------
typedef TArrayAsVector<BBFilsPhraseItem> BBFilsPhraseItemArray;




class BBFilsPhraseArray : public BBFilsPhraseItemArray
{
public :
	// Constructeurs
  	BBFilsPhraseArray() : BBFilsPhraseItemArray(0, 0, 1) {}
	BBFilsPhraseArray(BBFilsPhraseArray& rv);
	// Destructeur
	virtual ~BBFilsPhraseArray();
};

//---------------------------------------------------------------------------
// Class BBPhraseItem
//
// Cette structure sert � construire la phrase cod�e
//---------------------------------------------------------------------------
class BBPhraseItem {

	public :

	//NSSuper*			pSuperviseur;
	NSSmallBrother*	pBigBoss;
	BOOL				bTemporaire;	// Constitution d'un code avec marqueurs de l�sions

 //	NSLesion* 		pLesion;       // Pointeur sur la l�sion de travail

	string 			sCode;     		// Codage de l'item
	string 			sPonct;    		// Ponctuation terminale

	string 			sLocalisation; // Position dans l'arbre
	string 			sPhraseLocali; // Position pour la phrase cod�e

	BBItemData* 	pDonnees;		// Donn�es de la fiche PARADOX

	BBPhraseItem*  pBBItemPere;  	// Pointeur sur le BBPhraseItem p�re
	BBPhraseItem*	pBBItemFils;  	// Pointeur sur le BBPhraseItem fils

	BBFilsPhraseArray	aBBPhraseItemFils;  	// Pointeurs sur les fils

	int				iFilsActif;		// Num�ro du BBPhraseItem fils qui a la main

	NSBBFonction*	pNSFonction;	// Pointeur sur l'�ventuelle NSFonction

	int				iAvantLes;		// Vrai lorsqu'on est en aval de la l�sion

	// Constructeurs et destructeur
	BBPhraseItem(BBPhraseItem* pere = 0, NSSmallBrother* pBig = 0);

	BBPhraseItem(const BBPhraseItem& src);
	~BBPhraseItem();

	// Fonctions de mise en place de l'arborescence des BBItems
	int creer(char* codeFiche);			// Cr�e les fils, rempli aBBItemFils
	int creer(BBFilsPhraseItem* pFilsPhraseItem);

	int activer();								// Lance la BBItem

	int appeler(char* szNom);				// Appelle la fiche BB

	int  createurLesion(); 	 // Indique si le BBItem est ou non cr�ateur de Lesion
	int  uniciteLesion();  	 // Indique si la Lesion est unique ou non
	int  lienFonction();	  	 // Indique si le BBItem est rattach� � une fonction
	int  triComplet();
	int  tri();

	// Surcharge de l'op�rateur d'affectation
	BBPhraseItem& operator=(BBPhraseItem src);

};

//---------------------------------------------------------------------------
//  Classe des fonctions Big Brother
//
//  Cette classe sert � mettre en place les fonctions qui interviennent au
//  sein de l'arborescence Big Brother
//  Elle est homog�ne � NSDialog
//----------------------------------------------------------------------------
/*class NSBBPhraseFonction
{
	public :

	BBPhraseItem*		pBBItem;			// BBPhraseItem cr�ateur de la fonction
	string				sNomFonction;
	BOOL (FAR *pAdresseFct) (NSBBFonction far *, NSSuper far*, int, int far*);

	// Constructeurs
	NSBBFonction(string sNomFonct, BBPhraseItem* pBBItemPere);

	// Destructeur
	virtual ~NSBBFonction();

	int execute(int iParam, int* piValeur, string sEtiquette = "", NSControle* pNSCtrl = 0);
}; */

#endif