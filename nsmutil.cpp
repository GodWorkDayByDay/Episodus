//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
//   Note importante � propos de la gestion de m�moire DLL quand votre DLL
//   utilise la version statique de la biblioth�que d'ex�cution :
//
//   Si votre DLL exporte des fonctions qui passent des objets cha�nes (ou des
//   structures/classes contenant des cha�nes imbriqu�es) comme param�tres ou
//   r�sultats de fonction, vous devrez ajouter la biblioth�que MEMMGR.LIB � la fois
//   au projet DLL et � tout autre projet qui utilise la DLL. Vous devrez aussi utiliser
//   MEMMGR.LIB si un autre projet qui utilise la DLL effectue des op�rations de cr�ation
//   ou de suppression sur des classes non d�riv�es de TObject qui sont export�es depuis
//   la DLL. Ajouter MEMMGR.LIB � votre projet forcera la DLL et ses EXE appelants �
//   utiliser BORLNDMM.DLL comme gestionnaire de m�moire. Dans ce cas, le fichier
//   BORLNDMM.DLL devra �tre d�ploy� avec votre DLL.
//
//   Pour �viter d'utiliser BORLNDMM.DLL, passez les informations
//   de cha�nes en utilisant "char *" ou des param�tres ShortString.
//
//   Si votre DLL utilise la version dynamique de la RTL, vous n'avez pas besoin d'ajouter
//   explicitement MEMMGR.LIB �tant donn� que c'est effectu� implicitement pour vous.
//---------------------------------------------------------------------------

#include <shellapi.h>
#include <owl\applicat.h>
#include <owl\window.h>
#include <owl\owlpch.h>

#define _MAIN
#define __MAIN

#include "partage\nsglobal.h"
#include "nsutil\nsutil.h"

USEUNIT("nsutil\nscache.cpp");
USEUNIT("nsutil\nsdivers.cpp");
USEUNIT("nsutil\Nsutifct.cpp");
USEUNIT("partage\nsdivfct.cpp");
USEUNIT("apicrypt\cryptinterface.cpp");
USEUNIT("apicrypt\crypto.cpp");
USEUNIT("apicrypt\cryptounix.cpp");
USELIB("memmgr.lib");
USELIB("cp32mti.lib");
USELIB("bidsvi.lib");
USELIB("owlwvi.lib");
USEUNIT("nsutil\md5c.cpp");
USEUNIT("nsutil\tinyxmlparser.cpp");
USEUNIT("nsutil\tinyxml.cpp");
USEUNIT("nsutil\tinyxmlerror.cpp");
USEUNIT("nsutil\tinystr.cpp");
USEUNIT("nsutil\csvparser.cpp");
USELIB("nsmbb.lib");
USELIB("nsm_sgbd.lib");
USELIB("nsmsavoir.lib");
USEUNIT("nsutil\attvalelem.cpp");
USEUNIT("nsutil\nsstructure.cpp");
USERES("nsmutil.res");
USEUNIT("partage\nsdivfile.cpp");
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinstDll, unsigned long fdwReason, void*)
{
    switch (fdwReason)
    {
   	    case DLL_THREAD_ATTACH :
        case DLL_THREAD_DETACH :
      	    // cas des threads : on ne fait rien
      	    break;

        case DLL_PROCESS_ATTACH :
      	    // 1er appel : on instancie pResMod
      	    if (!pResMod)
   			    pResMod = new TModule(0, hinstDll);

            // si le new echoue : on renvoie false
      	    if (!pResMod)
      		    return 0;

            break;

        case DLL_PROCESS_DETACH :
      	    // dernier appel : on libere pResMod
       	    if (pResMod)
      	    {
      		    delete pResMod;
         	    pResMod = 0;
      	    }
            break;

        default :
      	    return 0;
    }

	return 1;
}
//---------------------------------------------------------------------------



