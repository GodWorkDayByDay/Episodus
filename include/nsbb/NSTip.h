#ifndef __NSTIP_H
#include <owl\applicat.h>
#include <owl\window.h>
#else
  #include "partage/nsglobal.h"
#endif
#define CM_TIPTIMER_ON  201
//
//
class _NSBBCLASSE NSTitleTip : public TWindow, public NSRoot
    void SetupWindow() ;
    // Affichage de la fenetre windows
    void Show(NS_CLASSLIB::TRect rectTitle, string* psText,
                    NS_CLASSLIB::TRect* pHoverRect = NULL, LPLOGFONT lpLogFont = NULL, int time = -1) ;

    // Cache la fen�tre
    void Hide() ;
    void EvMouseMove(uint modKeys, NS_CLASSLIB::TPoint& point);
    void disableTipTimer();
	protected:
		TWindow             *pParentWnd;  // Fenetre parent
    unsigned int 				time_to;

	DECLARE_RESPONSE_TABLE(NSTitleTip);

#endif // __NSTIP_H