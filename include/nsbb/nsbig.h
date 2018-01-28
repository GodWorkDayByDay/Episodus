//---------------------------------------------------------------------------
//    NSBigBro.H
//
//  Contient la d�claration de NSBigBrother, gestionnaire g�n�ral des
//  applications NAUTILUS.
//  KP
//  Cr�ation : sept 93         Derni�re mise � jour : mars 94
//---------------------------------------------------------------------------
#ifndef __NSBIGBROTHER_H
#define __NSBIGBROTHER_H

#include <windows.h>
#include <classlib\arrays.h>
#include <cstring.h>

#include "partage\nsglobal.h"
#include "ns_sgbd\nsfiche.h"
#include "nssavoir\nsguide.h"
//#include "nsdlg.h"
//#include "nslesion.h"
//#include "nslesarr.h"
#include "nautilus\nsrechd2.h"

//#if defined(_DANSNSBBDLL)
#if defined(_DANSDLL)
	#define _NSBBCLASSE __import
#else
	#define _NSBBCLASSE __export
#endif

//---------------------------------------------------------------------------
//  Objet Big-Brother
//  Big-Brother n'est habilit� qu'� manipuler ce type d'objet pour la
//  cr�ation des objets d'interface. Il faut donc qu'il y trouve toutes les
//  informations n�cssaires. Si toutefois il y a ajout d'information, elle ne
//  peut-�tre comprise que par la modification de la structure NSBBObj.
//  Il maintient �galement une liste cha�n�e de NSLesion (NSMonoLesion et
//  NSMultiLesion). Il est le seul � pouvoir manipuler les informations.
//---------------------------------------------------------------------------
/*class BBObj {
  public :
//  NSWindow*          pWnd;        // Pointeur sur la fen�tre OWL associ�e
//  BBItemArray*    pBBTranfert;    // Pointeur sur l'objet BB concern�
//  BBTransfertObj*    pBBParent;   // Pointeur sur l'objet BB parent
  WNDTYPE            iWndType;    // Indicateur de type de fen�tre associ�e

// Constructeurs
  BBObj(BBTransfertObj* parent = NULL, WNDTYPE type = isDlg)
  : pBBParent(parent), iWndType(type) {
	 pBBTransfert = new BBItemArray();
  }

  BBObj(RBBObj src)
  : pWnd(src.pWnd), pBBTransfert(src.pBBTransfert), pBBParent(src.pBBPparent),
	 iWndType(src.iWndType) {}

// Destructeur
//  ~BBObj() { delete pBBTransfert; }

// Surcharge de l'op�rateur =
	BBObj& operator=(BBObj src) {
	pWnd         = src.pWnd;
	pBBTransfert = src.pBBTransfert;
	pBBParent    = src.pBBPparent;
	iWndType     = src.iWndType;
	return *this;
  }

// Acc�s aux donn�es membres
  NSWindow* window()              { return pWnd; }
  void      window(NSWindow* src) { pWnd = src;}
  BBObj*    transfert()           { return pBBTransfert; }
  void      transfert(BBObj* src) { pBBTransfert = src; }
  BBObj*    parent()              { return pBBParent; }
  void      parent(BBObj* src)    { pBBParent = src; }
  WNDTYPE   type()                { return iWndType; }
  void      type(WNDTYPE src)     { iWndType = src; }
}; */

//---------------------------------------------------------------------------
//  Classe NSBIGBROTHER
//         ANCETRE   :
//         SURCHARGE :
// Cette classe sert � mettre en place le gestionnaire global de cr�ation
// des fen�tres NAUTILUS.
// Il est le seul habilit� � manipuler les BBObj et les NSLesion.
//---------------------------------------------------------------------------
//class _NSBBCLASSE NSBigBrother
class NSBigBrother
{

	public :

	//NSSuper* pSuperviseur;
	//TWindow* pFenetreMere;
	//TModule* pNSResModule;

	BBFiche*	pBBFiche;

	char 		contexteModule;
	char		codeModule[3], bigModule[9];

	string* 	psCRString;             	// Eventuelle phrase cod�e

	//BBLesionsArray*   paLesions;      // Array de NSLesion
	//BBVariablesArray* paVariables;    // Array de NSVariable
	//unsigned int 	  	numeroLesion;   // Num�roteur de l�sions
	//unsigned int 	  	numeroVariable; // Num�roteur de variables

	// Constructeur
	NSBigBrother(/*NSSuper* pSuper*/);
	NSBigBrother(const NSBigBrother& rv);
	// Destructeur
	~NSBigBrother();
	// Op�rateur =
	NSBigBrother& operator=(const NSBigBrother& src);

	// D�marrage d'un script
	BOOL lanceModule();
	lanceScript();
	generePhrase();

	// Maintenance et sauvegarde des l�sions
/*	int ajouteLesion(NSLesion* pLesion);  // Ajoute une l�sion � l'array
	int remplaceLesion(NSLesion* pLesion);

	int litLesion(string sLocali, NSLesion* pLesion); // l�sion de l'array
	int litLesionAmmorce(string sLocali, NSLesion* pLesion);

	int litLesionPrec(NSLesion* pLesion);
	int litLesionSuiv(NSLesion* pLesion);
	int litLesionAmmorceSuiv(int tailleAmmorce, NSLesion* pLesion);

	int detruitLesion(NSLesion* pLesion);

	int compteLesion(string sLocali);

	int compteLesionAmmorce(string sLocali);

	// Maintenance et sauvegarde des variables
	int ajouteVariable(NSVariable* pVariable);  // Ajoute une variable � l'array
	int remplaceVariable(NSVariable* pVariable);

	protected :

	//
	// L'acc�s normal � une l�sion se fait par son num�ro, toutes les m�thodes
	// qui utilisent l'indice au sein de l'array doivent �tre d�clar�es
	// en acc�s prot�g�
	//
	int donneLesionNumero(int iNumero);
	int remplaceLesion(int iNumLesion, NSLesion* pLesion);
	int litLesion(int iNumLesion, NSLesion* pLesion);
	int litLesionPrec(int iNumLesion, string sLocali, NSLesion* pLesion);
	int litLesionSuiv(int iNumLesion, string sLocali, NSLesion* pLesion);
	int litLesionAmmorceSuiv(int iNumLesion, string sLocali, NSLesion* pLesion);
	int detruitLesion(int iNumLesion);

	int donneVariableNumero(int iNumero);
	int remplaceVariable(int iNumVariable, NSVariable* pVariable); */
};
//extern NSBigBrother BigBoss;

#endif