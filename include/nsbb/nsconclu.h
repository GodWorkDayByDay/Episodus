#ifndef __NSCONCLU_H
#define __NSCONCLU_H

#include <owl\dialog.h>
#include <owl\radiobut.h>

#include "nsbb\nsbb.rh"
#include "nsbb\nsbbitem.h"


//------------------------------------------------------------------------
// �l�ments pour la conclusion
//------------------------------------------------------------------------

#ifdef _INCLUS
class NSDialogWrapper;
#endif

#ifdef _INCLUS
class NSConclusion : public NSDialogWrapper
#else
class NSConclusion : public TDialog
#endif
{
	public :

   TResId				ressource;
   TWindow* 			AParent;
   BBItem*           pBBitemConclusion;

   TRadioButton*		pAvant;
   TRadioButton*		pApres;
   TRadioButton*		pPlace;


   //
	// Constructeurs 		Destructeur
   //
   NSConclusion(TWindow* parent, TResId resId, BBItem* pBBitem, TModule* module = 0);
    ~NSConclusion();

   NSConclusion( NSConclusion& src);
   // Surcharge de l'op�rateur d'affectation
	NSConclusion& operator=(NSConclusion src);


   //
   // Op�rateurs
   //
   void SetupWindow();
   void CmOk();
   void CmCancel();

   //table de r�ponses
   DECLARE_RESPONSE_TABLE(NSConclusion);
};



#endif
