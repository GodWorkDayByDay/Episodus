//***************************************************************************//    NSUTIL.CPP
//    KRZISCH  Ph. janvier 92
// Impl�mentation des fonctions utiles
//***************************************************************************

//#include "ns_vector.h"

#include "nsutil\nsutifct.h"
#include "partage\nsdivfct.h"

//---------------------------------------------------------------------------
//  Function: Position(char* value, char *array[], int nbElts)
//
//  Arguments:
//            value        ->  valeur cherch�e
//            array        ->  matrice dans laquelle on recherche
//            nbElts       ->  nombre d'�l�ments
//  Description:
//            retourne la position de value dans array.
//  Returns:
//            position de value dans array si value existe
//            -1 sinon
//---------------------------------------------------------------------------
int Position(char* value, pFieldsArray array, int nbElts)
{
  int location = -1;

  for (int i = 0; (i < nbElts) && (location == -1); i++)
	 if(!strcmp(value, array[i]))
		 location = i;

  return location+1;   // Les num�ros de champs de PXEngine commencent � 1}

//---------------------------------------------------------------------------//  Function: wspf(char buffer[], char* fmt, ...)
//
//  Arguments:
//            buffer[] -> cha�ne de caract�re formatt�e
//            fmt      -> cha�ne de format
//            ...      -> liste variable d'arguments
//  Description:
//            wsprint(...) ne semble pas �tre impl�ment�e dans OWL
//            ce qui oblige � en simuler
//  Returns:
//            Le nombre de caract�res saisis
//---------------------------------------------------------------------------
int wspf(char buffer[], char* fmt, ...)
{
  va_list argptr;
  int cnt;

  va_start(argptr, fmt);
  cnt = vsprintf(buffer, fmt, argptr);
  va_end(argptr);
  return cnt;
}

//---------------------------------------------------------------------------
//  Function: SetInternational(void)
//
//  Arguments:
//            AUCUN
//  Description:
//            Va chercher dans WINI.INI les formats d'affichage des dates
//            heure, ...
//  Returns:
//            RIEN
//---------------------------------------------------------------------------/*void SetInternational(void)
{
  static char cName [] = "intl" ;

  iDate = GetProfileInt (cName, "iDate", 0) ;
  iTime = GetProfileInt (cName, "iTime", 0) ;

  GetProfileString (cName, "sDate",	"/", sDate,	2) ;
  GetProfileString (cName, "sTime",	":", sTime,	2) ;
  GetProfileString (cName, "s1159", "AM", sAMPM [0], 5) ;
  GetProfileString (cName, "s2359", "PM", sAMPM [1], 5) ;
} */

//---------------------------------------------------------------------------//  Function:  ptrInit(char* &strPtr, int length)
//
//  Arguments:
//             strPtr   ->  pointeur sur une cha�ne qu'il faut initialiser
//             length   ->  longueur de la cha�ne
//  Description:
//             Initialise un pointeur sur une cha�ne (char *)
//             Alloue un espace de longueur length
//             Initialise la cha�ne des blancs.
//  Returns:
//             TRUE   si l'initialisation s'est pass�e sans pb.
//             FALSE  sinon
//  Exemple :  ptrInit(&Essai, 5, '$');
//---------------------------------------------------------------------------
/*BOOL ptrInit(char* *strPtr, int length, char car)
{
 *strPtr = new char[length + 1];
 if (*strPtr == NULL)
	 return FALSE;
 else {
	 memset(*strPtr, car, length);
	 *(*strPtr + length) = '\0';
 }
 return TRUE;
}

//---------------------------------------------------------------------------//  Function:  ptrInit(char* &strPtr,const char* strInit)
//
//  Arguments:
//             strPtr   ->  pointeur sur une cha�ne qu'il faut initialiser
//             strInit  ->  cha�ne d'initialisation ou NULL si l'on d�sire
//                          des blancs
//  Description:
//             Initialise un pointeur sur une cha�ne (char *)
//             Initialise la cha�ne avec strInit.
//  Returns:
//             TRUE   si l'initialisation s'est pass�e sans pb.
//             FALSE  sinon
//  Exemple :  ptrInit(&Essai, "AAAAA");
//---------------------------------------------------------------------------
BOOL ptrInit(char* *strPtr,const char* strInit)
{
 *strPtr = new char[strlen(strInit) + 1];
 if (*strPtr == NULL)
	 return FALSE;
 else
	 strcpy(*strPtr, strInit);
 return TRUE;
} */

//---------------------------------------------------------------------------//  Function:  strAnalyse(const char* input, const char* separateurs, CacheArray& elts,
//                        int nb)
//
//  Arguments:
//             input      -> cha�ne � analyser
//             separateur -> cha�ne des s�parateurs
//             elts       -> array (dynamique) des tokens
//             nb         -> nombre d'�l�ment pour un cacheElement
//  Description:
//             Analyse une cha�ne contenant des s�parateurs et retourne
//             chaque �lt. trouv� dans une array elts[] de CacheElement.
//             nb sp�cifie le nombre de cha�nes que contient un cacheElement.
//  Returns:
//             RIEN
//  Exemple : strAnalyse("a bb;ccc d", " ;",...);
//---------------------------------------------------------------------------
void strAnalyse(const char* input, const char* separateurs,
					 CacheArray& elts, int nb)
{
  ChaineArray szPtr =  ChaineArray(0, 0, 1) ;
  char* szCur;
  char* copie;

  ptrInit(&copie, input);

 // strtok place un \0 � la fin de l'�l�ment si il est trouv�
  szCur = strtok(copie, separateurs);

  while (szCur != NULL) {
	 szPtr.Add(*new string(szCur));       // Le tas

	// un deuxi�me appel � strtok avec comme premier param�tre NULL
	// retourne un pointeur sur le caract�re suivant le token
	 szCur = strtok(NULL, separateurs);
  }
  for (int i = 0; i < szPtr.ArraySize(); i += nb)
	 elts.push_back(new CacheElement(szPtr, i, nb));
  delete copie;
}

//---------------------------------------------------------------------------//  Function:  strAnalyse(char* input, char* separateurs, CacheArray& elts)
//
//  Arguments:
//             input      -> cha�ne � analyser
//             separateur -> cha�ne des s�parateurs
//             elts       -> array (dynamique) des tokens
//             nb         -> nombre d'�l�ment pour un cacheElement
//  Description:
//             Analyse une cha�ne contenant des s�parateurs et retourne
//             chaque �lt. trouv� dans une array elts[] de CacheElement.
//             nb sp�cifie le nombre de cha�nes que contient un cacheElement.
//  Returns:
//             RIEN
//  Exemple : strAnalyse("a bb;ccc d", " ;",...);
//---------------------------------------------------------------------------
/*void strAnalyse(char* input, char* separateurs, CacheArray& elts, int nb)
{
  char* szPtr = NULL;

  // strtok place un \0 � la fin de l'�l�ment si il est trouv�
	szPtr = strtok(input, separateurs);
	while (szPtr != NULL)
	  for(int i = 1; i <= nb; i++) {
		 elts.Add(new CacheElement(szPtr));
		// un deuxi�me appel � strtok avec comme premier param�tre NULL
		// retourne un pointeur sur le caract�re suivant le token
		 szPtr = strtok(NULL, separateurs);
	  }
} */

//---------------------------------------------------------------------------//  Function:  strAnalyse(char* input, char* separateurs, char* elts[],
//                        int nb = 1)
//
//  Arguments:
//             input      -> cha�ne � analyser
//             separateur -> cha�ne des s�parateurs
//             elts       -> array  des tokens
//             nb         -> nombre de cha�nes attendu par un CacheElement
//  Description:
//             Analyse une cha�ne contenant des s�parateurs et retourne
//             chaque �lt. trouv� dans une array elts[] de sous-cha�nes.
//  Returns:
//             RIEN
//  Exemple : strAnalyse("a bb;ccc d", " ;",...);
//---------------------------------------------------------------------------
/*void strAnalyse(char* input, char* separateurs, char* elts[], int nb)
{
  char* szPtr = NULL;
  int nElts = sizeof elts / sizeof(char *);

  // strtok place un \0 � la fin de l'�l�ment si il est trouv�
	szPtr = strtok(input, separateurs);
	for (int i = 0; i < nElts; i++)
	  for (int j = 1; j <= nb; j++) {
		 ptrInit(&elts[i], szPtr);
	  // un deuxi�me appel � strtok avec comme premier param�tre NULL
	  // retourne un pointeur sur le caract�re suivant le token
		 szPtr = strtok(NULL, separateurs);
	}
} */

//---------------------------------------------------------------------------//  Function:
//      int firstNoWhite(char* s);
//  Arguments:
//      s  -> cha�ne � �tudier.
//  Description:
//      Retourne la position du premier caract�re qui n'est pas un
//      caract�re blanc ou une tabulation de la cha�ne s.
//  Returns:
//      -1        si la cha�ne ne contient pas de blancs au d�but.
//	strlen(s) si la cha�ne ne contient que des blancs
//      la position sinon
//---------------------------------------------------------------------------
int firstNoWhite(const char* s)
{
 	int location = -1;
   int i;
  	for (i = 0; s[i] && (location == -1); ++i)
	 	if ((s[i] != ' ') && (s[i] != '\t'))
			location = i;
  	if (!s[i])
   	return(i);
  	else
   	return location;
}

//---------------------------------------------------------------------------//  Function:
//      int lastNoWhite(char* s);
//  Arguments:
//      s -> cha�ne � �tudier
//  Description:
//      Retourne la position du dernier caract�re qui n'est pas un
//      caract�re blanc ou une tabulation de la cha�ne s.
//  Returns:
//      -1 si la cha�ne ne contient pas de blancs � la fin
//      la position du dernier carct�re qui n'est pas un blanc.
//---------------------------------------------------------------------------
int lastNoWhite(const char* s)
{
  int location = -1;

  for (int i = 0; s[i]; ++i)
	 if ((s[i] != ' ') && (s[i] != '\t'))
		location = i;
  return location;
}

//---------------------------------------------------------------------------//  Function:
//      beginPad(const char* s, char* dest, int numBlanks)
//  Arguments:
//      s         -> cha�ne � bourrer
//	dest      -> cha�ne formatt�e
//      numBlanks -> nb. de blancs de bourrage
//  Description:
//      Bourre la cha�ne s de numBlanks caract�res blancs au d�but
//      et place la cha�ne ainsi formatt�e dans dest.
//  Returns:
//      -1 si il n'y plus assez d'espace m�moire
//       0 si tout a bien march�
//---------------------------------------------------------------------------
int beginPad(const char* s, char* dest, int numBlanks)
{
    int nbChar =  strlen(s) + numBlanks;
    char* temp = new char[nbChar+1];

    if (temp == NULL)
        return -1;
    memset(temp, ' ', numBlanks);
    *(temp + numBlanks) = '\0';    strcat(temp, s);
    strcpy(dest, temp);
    delete[] temp;
    return 0;
}

//---------------------------------------------------------------------------//  Function:
//      int endPad(const char* s, char* dest, int numBlanks)
//  Arguments:
//      s         -> cha�ne � bourrer
//      dest      -> cha�ne obtenue apr�s bourrage
//      numBlanks -> nombre de caract�res blancs de bourrage
//  Description:
//      Bourre la cha�ne s de numBlanks caract�res blancs � la fin
//      et place la cha�ne bourr�e dans dest.
//  Returns:
//      -1 si la m�moire est insuffisante pour le bourrage
//       0 si le bourrage est r�ussi
//---------------------------------------------------------------------------
int endPad(const char* s, char* dest, int numBlanks)
{
    char* temp = new char[numBlanks+1];
    if (temp == NULL)
        return -1;
    memset(temp, ' ', numBlanks);
    *(temp + numBlanks) = '\0';
    strcpy(dest, s);
    strcat(dest, temp);
    delete[] temp;
    return 0;
}

//---------------------------------------------------------------------------//  Function:
//     void beginWhiteCut(char* s);
//  Arguments:
//     s  -> cha�ne � traiter
//  Description:
//     Enl�ve tous les blancs de d�but de cha�ne.
//  Returns:
//     RIEN
//---------------------------------------------------------------------------
void beginWhiteCut(char* s)
{
  	int pos = firstNoWhite(s);
  	if (pos == 0)
        return;
  	char* temp = new char[strlen(s)+1];
  	for (int i = 0; *(temp + i) = *(s+pos+i); i++);
  	strcpy(s, temp);
  	delete[] temp;
}

//---------------------------------------------------------------------------//  Function:
//      void endWhiteCut(char* s);
//  Arguments:
//      s  ->  cha�ne � tripoter
//  Description:
//      Enl�ve tous les blancs en fin de la cha�ne s.
//  Returns:
//      RIEN
//---------------------------------------------------------------------------
void endWhiteCut(char* s)
{
    int pos = lastNoWhite(s);
  	if (pos == -1)
   	    strcpy(s, "");
  	else if (pos != strlen(s))
    {   	    char* temp = new char[pos+1];        int i;
		for (i = 0; i < pos+1; i++)
	  		*(temp + i) = s[i];
		*(temp + i) = '\0';
		strcpy(s, temp);
		delete[] temp;
  	}
}

//---------------------------------------------------------------------------//  Function:
//      int centerStr(const char* s, char* dest, int maxChar);
//  Arguments:
//      s       -> cha�ne que l'on veut formatter
//      dest    -> cha�ne formatt�e
//      maxChar -> nombre de caract�res de la cha�ne d�sir�e
//  Description:
//      Centre la cha�ne s sur maxChar et place dans dest le r�sultat
//  Returns:
//      -1  si probl�me de m�moire
//       0  si OK
//       1  si le nombre de caract�res non blancs de s > maxChar
//---------------------------------------------------------------------------
int centerStr(const char* s, char* dest, int maxChar)
{
  strcpy(dest, s);
  endWhiteCut(dest);
  beginWhiteCut(dest);
  int length = strlen(dest);
  if (length > maxChar)
	 return 1;
  length = (maxChar - length) / 2;
  if (beginPad(dest, dest, length) == -1)
	 return -1;
  length = maxChar - strlen(dest);
  return endPad(dest, dest, length);
}

//---------------------------------------------------------------------------//  Function:
//     int leftStr(const char* s, char* dest, int maxChar)
//  Arguments:
//     s       -> cha�ne que le d�sire formatter
//     dest    -> cha�ne formatt�e
//     maxChar -> nombre de caract�res que l'on d�sire obtenir
//  Description:
//     Justifie � gauche une cha�ne s et place le r�sultat dans dest
//  Returns:
//     -1  si probl�me de m�moire
//      0  si OK
//      1  si le nombre de caract�res non blancs de s > maxChar
//---------------------------------------------------------------------------
int leftStr(const char* s, char* dest, int maxChar)
{
  strcpy(dest, s);
  beginWhiteCut(dest);
  endWhiteCut(dest);
  int length = strlen(dest);
  if (length > maxChar)
	 return 1;
  length = maxChar - length;
  return endPad(dest, dest, length);
}

//---------------------------------------------------------------------------//  Function:
//      int rightStr(const char* s, char* dest, int maxChar);
//  Arguments:
//      s       -> cha�ne que l'on d�sire formatter
//      dest    -> cha�ne formatt�e
//      maxChar -> nombre de caract�res d�sir�s
//  Description:
//      Justifie � droite la cha�ne s et place le r�sultat dans dest.
//  Returns:
//      -1  si probl�me de m�moire
//       0  si OK
//       1  si le nombre de caract�res non blancs de s > maxChar
//---------------------------------------------------------------------------
int rightStr(const char* s, char* dest, int maxChar)
{
  strcpy(dest, s);
  endWhiteCut(dest);
  beginWhiteCut(dest);
  int length = strlen(dest);
  if (length > maxChar)
	 return 1;
  length = maxChar - length;
  return beginPad(dest, dest, length);
}

//---------------------------------------------------------------------------//  Function: InitSousClass(HWND hWnd, WORD id_Edit, FARPROC lpChangeProc)
//
//  Arguments:
//            hWnd         -> handle de la fen�tre parent
//            id_Edit      -> ID du contr�le EDIT que l'on veut sousclasser
//            lpChangeProc -> Adresse de la nouvelle WndProc que l'on veut
//                            mettre en place.
//  Description:
//            Doit �tre appeler si l'on d�sire sousclasser un contr�le EDIT.
//            Cela suppose que l'on stocke l'adresse de l'ancienne adresse
//            de la WndProc du contr�le EDIT soit dans un champ del'objet
//            bo�te de dialogue, soit comme variable globale.
//  Returns:
//            RIEN
//---------------------------------------------------------------------------
/*
void InitSousClass(HWND hWnd, WORD id_Edit, FARPROC lpChangeProc)
{
  HWND hWndEdit = GetDlgItem(hWnd, id_Edit);
  FARPROC lpNewProc = MakeProcInstance((FARPROC)lpChangeProc, hInst);
  FARPROC lpOldProc = (WNDPROC) SetWindowLong(hWndEdit, GWL_WNDPROC, (long)lpNewProc) ;
}
*/

//---------------------------------------------------------------------------
//  Function:  FiniSousClass(HWND hWnd, WORD id_Edit, FARPROC lpPrevProc)
//
//  Arguments:
//             hWnd       -> handle de la fen�tre m�re
//             id_Edit    -> ID du contr�le EDIT que l'on a sousclass�.
//             lpPrevProc -> adresse de l'ancienne WndProc
//  Description:
//             Doit �tre appel�e pour remettre la bonne adresse de la
//             WndProc du contr�le Edit que l'on a sousclass�.
// ATTENTION : Il faut que soit stock� en variable globale lpOldProc.
//  Returns:
//             RIEN
//---------------------------------------------------------------------------
/*
void FiniSousClass(HWND hWnd, WORD id_Edit, FARPROC lpPrevProc)
{
  HWND hWndEdit = GetDlgItem(hWnd, id_Edit) ;
  FARPROC lpNewProc = (FARPROC)SetWindowLong(hWndEdit, GWL_WNDPROC, (long)lpPrevProc) ;
  FreeProcInstance(lpNewProc) ;
}
*/

//---------------------------------------------------------------------------//  Function:  EditNbWndProc(HWND hWnd, WORD wMessage,
//       		               WORD wParam, LONG lParam)
//  Arguments:
//             hWnd     -> handle du contr�le EDIT que l'on veut sousclasser
//             wMessage -> message WINDOWS que l'on veut traiter
//             wParam   -> contient le caract�re saisi
//             lParam   -> non utilis�
//  Description:
//             Permet de limiter la saisie, dans un contr�le EDIT, � des
//             chiffres.
//  ATTENTION : il faut que soit stock�e quelque part lpOldProc
//  Returns:
//             Le nombre de chiffres saisis puisque c'est la valeur
//             retourn�e par lpOldProc.
//---------------------------------------------------------------------------
/*
LRESULT FAR PASCAL _export EditNbWndProc(HWND hWnd, WORD wMessage,
						WORD wParam, LONG lParam)
{
  LRESULT lRes = 0 ;     // Valeur de retour
  bool bTraite = true ;  // Indique commande trait�e
//-------------------------------------------------
  switch(wMessage)
  {
    case WM_CHAR :
      if (((wParam < '0') || (wParam > '9')) && wParam != 0x08)
        MessageBeep(0) ;
      else
        bTraite = false ;
      break ;
    default     :
      bTraite = false ;
  }
  // Traitement par d�fault
  if (false == bTraite)
    lRes = CallWindowProc(lpOldProc, hWnd, wMessage, wParam, lParam);
  return lRes ;
}
*/

//---------------------------------------------------------------------------//  Function:  EditCharWndProc(HWND hWnd, WORD wMessage,
//				WORD wParam, LONG lParam)
//  Arguments:
//	       hWnd     -> handle du contr�le EDIT que l'on veut sousclasser
//             wMessage -> message WINDOWS que l'on veut traiter
//             wParam   -> contient le caract�re saisi
//             lParam   -> non utilis�
//  Description:
//             Permet de limiter la saisie, dans un contr�le EDIT, � des
//             caract�res autres que des chiffres.
//  ATTENTION : il faut que soit stock�e quelque part lpOldProc
//  Returns:
//             Le nombre de caract�res saisis puisque c'est la valeur
//             retourn�e par lpOldProc.
//---------------------------------------------------------------------------
/*
LRESULT FAR PASCAL _export EditCharWndProc(HWND hWnd, WORD wMessage,
				WORD wParam, LONG lParam)
{
  LRESULT lRes = 0;        // Valeur de retour
  BOOL bTraite = TRUE;  // Indique commande trait�e
//-------------------------------------------------
  switch(wMessage) {
    case WM_CHAR : if (   ((wParam < 'A')|| ((wParam > 'Z') && (wParam < 'a')))
		       || ((wParam > 'z') && (wParam < 0xC0))
		       || (wParam == 0xD7) || (wParam == 0xF7)&&(wParam != 0x08) )
		      MessageBeep(0);
		   else
		      bTraite = FALSE;
		   break;
    default     :  bTraite = FALSE;
		   break;
    }
    // Traitement par d�fault
    if(!bTraite)
       lRes = CallWindowProc(lpOldProc, hWnd, wMessage, wParam, lParam);
    return lRes;
}
*/

