//----------------------------------------------------------------------------
#ifndef __NS_GRAB_H
#include <bwcc.h>
#ifdef _MAIN
	#else
		static TModule *pResMod ;
		TModule *pNSResModule ;
	#endif
#else
	extern TModule *pNSResModule ;
#endif

#endif  // __NS_GRAB_H