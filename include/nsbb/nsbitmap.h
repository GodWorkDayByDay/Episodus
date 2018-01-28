//**************************************************************************
//  NOM du FICHIER  NSBITMAP.H
//
//  Mise en place de la classe NSBitmap qui correspond aux bitmaps
//  interactifs contenus dans les bo�te de dialogue
//
//  Auteur : KRZISCH Ph.
// Date de cr�ation :                  mise � jour :
//**************************************************************************
#ifndef __NSBITMAP_H
#define __NSBITMAP_H


#ifndef __CONTROL_H
#include <owl\control.h>
#endif

#ifndef __POINT_H
#include <owl\point.h>
#endif

#ifndef __ARRAYS_H
#include <classlib\arrays.h>
#endif

#ifndef __DC_H
#include <owl\dc.h>
#endif

#ifndef __GDIOBJEC_H
#include <owl\gdiobjec.h>
#endif


#include "nsbb\nsbb_dlg.h"

/*#ifndef __WINGDI_H
#include <owl\wingdi.h>
#endif
*/
// Fonction qui sert � enregistrer la classe NSBitmap
BOOL NSBitmapRegister();
BOOL NSBitmapButRegister();


//--------------------------------------------------------------------------
// D�claration de DefRegion
// Struct qui sert � initialiser une r�gion d'un NSBitmap.
// Son principal int�r�t est son constructeur qui � partir d'une string
// construit tous les arguments n�cessaire � la d�finition d'une TRegion.
//--------------------------------------------------------------------------
struct DefRegion {
  string                szName;           // Nom de la r�gion
  NS_CLASSLIB::TPoint*  pVertices;      // Matrice des diff�rents sommets
  int                   nbVertices;         // Nb. de sommets

 // Constructeurs
  DefRegion(const char* name="", const NS_CLASSLIB::TPoint* pPoints = NULL);
  DefRegion(const string info, const char* separateurs = "/:(,)");

 // Destructeur
  ~DefRegion();
  void AnalyseChaine(string sChaine, string* pNom, int* pNbVert, const char* separateurs);
  void RemplirMatrice(string sChaine, const char* separateurs);

 // Surcharge d'op�rateurs
  DefRegion& operator=(const DefRegion& src);
  int operator==(const DefRegion& x);
};
//--------------------------------------------------------------------------
// D�claration de DefRegionArray
// Classe qui sert � d�finir les r�gions d'un NSBitmap sous forme de matrice
// dynamique de DefRegion.
//--------------------------------------------------------------------------
typedef vector <DefRegion*> DefArray;
typedef DefArray::iterator IterDefRegion;

class DefRegionArray : public DefArray
{
	public :
	// Constructeurs
	DefRegionArray() : DefArray() {}
	DefRegionArray(DefRegionArray& rv);
	// Destructeur
	virtual ~DefRegionArray();
   void vider();
};



//--------------------------------------------------------------------------
// D�claration de NSRegion
// Classe qui sert de r�gion pour un NSBitmap. Elle est initalis�e
// gr�ce � une DefRegion.
//--------------------------------------------------------------------------
class NSBitmap;      // D�finition de type forward

class NSBitmapRegion : public TRegion {

  NSBitmap* pBitmap;   // Adresse de la fen�tre NSBitmap
  string szName;        // Nom de la r�gion
  int iState;          // Etat coch� ou non ou gray

  public :

 // Constructeurs
  NSBitmapRegion(NSBitmap* Aparent, DefRegion& defRegion, int fillMode =
					  ALTERNATE);
 // Destructeur
  ~NSBitmapRegion() {}
};
//--------------------------------------------------------------------------
// D�claration de NSRegionArray
// Classe qui sert � g�rer les r�gions d'un NSBitmap sous forme de matrice
// dynamique de NSRegions.
//--------------------------------------------------------------------------

typedef vector <NSBitmapRegion*> RegionArray;
typedef RegionArray::iterator IterNSBitmapRegion;

class NSRegionArray : public RegionArray
{
	public :
	// Constructeurs
	NSRegionArray() : RegionArray() {}
	NSRegionArray(NSRegionArray& rv);
	// Destructeur
	virtual ~NSRegionArray();
   void vider();
};



//--------------------------------------------------------------------------
// D�claration de NSBitmap
// D�riv� de TControl
// Classe NSBitmap est un bitmap qui doit � partir d'une matrice de
// "r�gions" simuler un ensemble de boutons.
// Ces r�gions d�finissent les z�nes actives du bitmap.
//--------------------------------------------------------------------------

// Messages d'obtention et de positionnement de la position courante
// du curseur sur le bitmap

#define NSB_SETPOS WM_USER+10
#define NSB_GETPOS WM_USER+11

class NSBitmap : public OWL::TControl {


   public:

	NSRegionArray* pRegionArray;  // Matrice dynamique de NSRegions

   // Position courante du curseur
   #if defined __WIN32__
		long   nXcurr, nYcurr;
   #else
   	int  	 nXcurr, nYcurr;
   #endif

	BOOL  		bCapture;               // Indicateur de capture du focus
	int   		IDBmp;                  // ID de la ressource bitmap
   TDib* 		pDib;                   // Pointeur sur un DIB
   NSControle* 	pControle;


  // Constructeurs
	NSBitmap(TWindow* Aparent, int idCtrl, int idBmp,
				DefRegionArray* regionArray,
				int xpos = 0, int ypos = 0, BOOL capture = FALSE);

   //copie
   NSBitmap(const NSBitmap& src);
   // Surcharges des op�rateurs
   NSBitmap& operator=(const NSBitmap& src) ;



  // Destructeur
	~NSBitmap();
   WNDTYPE donneType() { return(isBtn); };
  // Fonctions diverses
	 virtual UINT Transfer(void* buffer, TTransferDirection direction);


	protected :
	// virtual void InvertRgn(NSBitmapRegion& region);
	 virtual void Affiche(TDC& Dc);

  // Chargement du bitmap
	 BOOL LoadBitmapResource(TResId ResId);
	 BOOL LoadBitmapFile(const char* name);

  // R�ponses aux messages
	 void EvKeyDown(UINT key, UINT repeatCount, UINT flags);
	 void EvSetFocus(HWND hWndLostFocus);
	 void EvKillFocus(HWND hWndGetFocus);
	 void EvPaint();
	 void EvMouseMove(UINT modKeys, NS_CLASSLIB::TPoint& point);
	 void EvLButtonDown(UINT modKeys, NS_CLASSLIB::TPoint& point);
	 void EvLButtonUp(UINT modKeys, NS_CLASSLIB::TPoint& point);
	 void EvLButtonDblClk(UINT modKeys, NS_CLASSLIB::TPoint& point);
	 UINT EvGetDlgCode(MSG far* msg);
  DECLARE_RESPONSE_TABLE(NSBitmap) ;};
#endif
