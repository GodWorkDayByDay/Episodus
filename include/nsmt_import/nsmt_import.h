//----------------------------------------------------------------------------
#ifndef __NSM_IMPORT_H
#include <bwcc.h>
void _export nsmtoolsInformation(string far *psToolName, string far *psDescription) ;
	#ifndef __MAIN
	#else
		static TModule *pResMod;
		TModule *pNSResModule;
	#endif
#else
	extern TModule *pNSResModule;
#endif

#endif  // __NSM_IMPORT_H
