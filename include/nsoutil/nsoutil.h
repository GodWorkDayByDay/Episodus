//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//#include <windows.h>

#ifndef __NSOUTIL_H
#define __NSOUTIL_H

#include <bwcc.h>

void _export lancerOutils(NSContexte* pCtx);

#ifdef _MAIN
	#ifndef __MAIN
		extern TModule *pNSResModule;
	#else
		static TModule *pResMod;
		TModule *pNSResModule;
	#endif
#else
	extern TModule *pNSResModule;
#endif

#endif