
/* ************************************************************************ */
/* Module : HmkMacConst.H     PROJET : Tous projets li�s � HMKMAC.DLL       */
/* ************************************************************************ */
/* FONCTIONNALITES                                                          */
/* D�claration des constantes d'API HMKMAC.DLL                              */
/* ************************************************************************ */
/* Auteur : (g�n�r� par MakeIncude.exe)                                     */
/* Compatible avec HMKMAC.DLL version 1.4.1                                 */
/* ************************************************************************ */


#if !defined(_INC_HMKMACCONST_H)
	#define _INC_HMKMACCONST_H

	//  Niveaux de gravit�
	//  -----------------------------------------------
	// Liste_G
	#define G_AprendreEnCompte		2		// � prendre en compte
	#define G_PrecautionEmploi		4		// pr�caution d'emploi
	#define G_AssociationDeconseillee		6		// association d�conseill�e
	#define G_ContreIndication		8		// contre-indication

	//  Types de champ
	//  -----------------------------------------------
	// Liste_C
	#define C_Aucun		0		// aucun
	#define C_Reduit		1		// nom r�duit
	#define FormeGalenique		2		// forme gal�nique
	#define C_Hopital		3		// code Ville / H�pital
	#define C_Prix		4		// prix public TTC
	#define C_Descriptif		5		// nom complet

	//  Types d'index
	//  -----------------------------------------------
	// Liste_I
	#define I_Direct		0		// direct
	#define I_Etendu		1		// �tendu
	#define I_MiniDirect		2		// minimum direct
	#define I_MiniEtendu		3		// minimum �tendu
	#define I_Complet		1		// complet
	#define I_Minimum		2		// minimum

	//  Fonds documentaires
	//  -----------------------------------------------
	// Liste_D
	#define D_GuideNational		0		// Guide National de Prescription
	#define D_VidalParticulier		1		// Vidal de la Famille
	#define D_Vidal		2		// Dictionnaire Vidal

	//  Rubriques de monographies
	//  -----------------------------------------------
	// Liste_R
	#define R_Toutes		0		// toutes
	#define R0_CI		1		// contre-indications
	#define R_Composition		2		// composition
	#define R_EffetsInd		3		// effets ind�sirables
	#define R_MiseEnGarde		4		// mise en garde et pr�cautions d'emploi
	#define R_Grossesse		5		// grossesse
	#define R_Indications		6		// indications
	#define R_Interactions		7		// interactions
	#define R_Posologie		8		// posologie
	#define R_Formes		9		// formes et pr�sentations
	#define R_RMO		10		// RMO

	//  Codes hospitaliers
	//  -----------------------------------------------
	// Liste_H
	#define H_ResHop		0		// r�serv� � l'usage hospitalier
	#define H_IniHop		1		// prescription initiale hospitali�re
	#define H_IniHopAR		2		// prescription initiale hospitali�re, � renouveler

	//  Codes mise � jour
	//  -----------------------------------------------
	// Liste_J
	#define J_Ok		0		// m�dicament sur le march�
	#define J_Supprime		1		// m�dicament supprim�
	#define J_Vigilence		2		// m�dicament en pharmacovigilence

	//  R�sultats d'initialisation
	//  -----------------------------------------------
	// Liste_INI
	#define INI_BASE_ERR		0		// la base est corrompue
	#define INI_TVS_OK		1		// base TVS, initialisation r�ussie
	#define INI_TVS_DATEINVALIDE		-1		// base TVS, date limite d'utilisation d�pass�e
	#define INI_VCD_OK		8		// base VCD, initialisation r�ussie
	#define INI_VCD_DATEINVALIDE		-8		// base Vidal CD, date limite d'utilisation d�pass�e
	#define INI_TVS_FINDEMO		-101		// base TVS D�monstration, �ch�ance d�pass�e
	#define INI_TVS_FULLACCESS		-1004		// base TVS, nombre maximal de connexions r�seau att
	#define INI_TVS_LICENCE		-1008		// base TVS, num�ro de licence invalide
	#define INI_TVS_LOCK		-1016		// base TVS, v�rouill�e
	#define INI_TVS_LOAD		-1003		// base TVS, erreur de chargement de la librairie
	#define INI_TVS_SERVER		-1014		// base TVS, impossible d'acc�der au serveur

	//  Types de qualifiant
	//  -----------------------------------------------
	// Liste_Q
	#define Q_Nom		1		// nom
	#define Q_Substance		2		// substance
	#define Q_Classe		3		// classe th�rapeutique
	#define Q_Labo		4		// laboratoire
	#define Q_Tous		5		// tous
	#define Q_Cip		6		// code cip
	#define Q_Excipient		7		// excipient
	#define Q_Ci		8		// contre indication
	#define Q_Hopital		9		// code hospitalier
	#define Q_CodeMarche		10		// code march�
	#define Q_RMO		11		// RMO
	#define Q_CodeDopant		12		// code dopant
	#define Q_Voie		13		// voie d'administration
	#define Q_FormeGal		14		// forme gal�nique
	#define Q_CodeRem		15		// code remboursement
	#define Q_CodeGenerique		16		// code g�n�rique
	#define Q_Collectivite		17		// collectivit�
	#define Q_Duree		18		// dur�e de prescription
	#define Q_Liste		19		// liste
	#define Q_Categorie		20		// cat�gorie
	#define Q_NomReduit		21		// nom r�duit
	#define Q_Monograhie		22		// monographie
	#define Q_Composition		23		// composition
	#define Q_ClassifSemp		24		// classification des produits SEMP
	#define Q_Saumon		25		// pages Saumon du dictionnaire Vidal
	#define Q_indication		27		// Indications
	#define Q_SituPresc		28		// Groupes d'indications
	#define Q_CIM10		29		// Classification Internationale des Maladies et sym
	#define Q_EPhMRA		30		// Classification de l'European Pharmaceutical Marke
	#define Q_ATC		31		// Classification ATC (Anatomique - Th�rapeutique - 

	//  Cat�gories de produits
	//  -----------------------------------------------
	// Liste_P
	#define P_Tous		127		// tous les produits
	#define P_Vidal		64		// m�dicaments Vidal
	#define P_Diet		32		// produits di�t�tiques Semp
	#define P_Veto		16		// produits v�t�rinaires Semp
	#define P_Para		8		// produits de parapharmacie Semp
	#define P_Acces		4		// accessoires Semp
	#define P_Divers		2		// divers Semp
	#define P_Homeo		1		// produits hom�opathiques

	//  Erreurs d'ex�cution
	//  -----------------------------------------------
	// Liste_ERR
	#define ERR_OK		0		// ok
	#define ERR_DATEINVALIDE		1		// date invalide
	#define ERR_ENDUSE		2		// fin d'exploitation
	#define ERR_MEMORYOVERFLOW		3		// d�passement m�moire
	#define ERR_OPENFILE		4		// erreur ouverture fichier
	#define ERR_NODOCUMENT		6		// non document�
	#define ERR_NOANSWER		7		// pas de r�ponse
	#define ERR_NOMINIGRAPHIE		8		// pas de minigraphie
	#define ERR_NOINTERACTION		9		// pas d'interaction
	#define ERR_NOCONTREINDIC		10		// pas de contre-indication
	#define ERR_NOCLASSIF		11		// pas de classification
	#define ERR_NOMED		12		// pas de m�dicament sans interaction
	#define ERR_BASE		13		// base corrompue
	#define ERR_FULLACCESS		14		// nombre d'acc�s au r�seau d�pass�
	#define ERR_VERSIONFILE		15		// fichier version corrompu
	#define ERR_VERSIONDATA		16		// donn�es inadapt�es � cette version de la librairi
	#define ERR_INDEXNONSUPPORTE		17		// Type d�index non support�

#endif

