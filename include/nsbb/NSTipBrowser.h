#ifndef __NSTIPBROWSER_H
#include <owl\applicat.h>
#include <owl\window.h>
#else
  #include "partage/nsglobal.h"
#endif
class TWebTip ;

//
//
class _NSBBCLASSE NSWebTipWindow : public TWindow, public NSRoot
    void PerformCreate(int menuOrId) ;
    void SetupWindow() ;
    // Affichage de la fenetre windows
    void Show(NS_CLASSLIB::TRect rectTitle, string* psURL,

    // Cache la fen�tre
    void Hide() ;
    void EvMouseMove(uint modKeys, NS_CLASSLIB::TPoint& point) ;
	protected:
		TWindow             *pParentWnd ;  // Fenetre parent
    unsigned int 				time_to ;

    TWebTip				      *Form ;

	DECLARE_RESPONSE_TABLE(NSWebTipWindow) ;

#endif // __NSTIPBROWSER_H