#ifndef __NSBB_MSG_H#define __NSBB_MSG_H

#define NSDLG_SORTIE_HAUT -4#define NSDLG_SORTIE_BAS  -3
#define NSDLG_RETOUR 	    -1
#define NSDLG_SUITE 	     0

//
// Pour r�initialiser les arch�types
//
#define NSDLGSTATUS_REINIT  -1
#define NSDLGSTATUS_NORMAL   0

//// Entre NSDLG_SUITE et NSDLGRETOUR_DIRECT : acc�s direct au ni�me fils
//
#define NSDLGRETOUR_DIRECT     10
#define NSDLGRETOUR_SEPARATOR  20   // (max) Size of a return set  
#define NSDLGRETOUR_FIN        60
#define NSDLGRETOUR_DEBUT      65
#define NSDLGMULTI		         70
#define NSDLG_ALLER_A 	      100
#define NSDLG_AUCUN 	        200
#define NSDLG_ERREUR 	        201

//// Messages sp�cifiques aux l�sions multiples
//
#define NSDLGMULTI_PREC	   NSDLGMULTI+1   // L�sion pr�c�dente
#define NSDLGMULTI_SUIV	   NSDLGMULTI+2   // L�sion suivante
#define NSDLGMULTI_FIN	   NSDLGMULTI+3   // Fin
#define NSDLGMULTI_SUPP	   NSDLGMULTI+4   // Suppression de la l�sion
#define NSDLGMULTI_NEW	   NSDLGMULTI+5   // Nouvelle l�sion
#define NSDLGMULTI_DERN	   NSDLGMULTI+6   // D�but des messages sp�cifiques

#endif
