//-------------------------------------------------------------------------
//                    BIBLIOTHEQUE : NSDIVFCT.C
//
//                     Pot-pourri de fonctions
//
//             D�but d'�criture : 30 Juin 1988 (PA)
//             Derni�re version : 28 Juillet 1994 (PA)
//-------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
// #include <string.stl>
// #include <sysutils.hpp>		// pour FileExists de nom_sans_doublons

#include "nsglobal.h"

#include "nsdivfct.h"

#include <fstream>

//---------------------------------------------------------------------------
//  Function: erreur(Pchar texte, int gravite, Retcode ErrPx)
//
//  Arguments:
//            texte   -> texte affich� en cas d'erreur
//            gravit� -> niveau de gravit�
//
//  Description:
//            Affiche les messages d'erreur et sort si le niveau de
//            gravit� est 1.
//  Returns:
//            Retourne 0 si le probl�me rencontr� est surmontable.
//---------------------------------------------------------------------------
/*
int 		erreur(const char *texte, int gravite, int DatabaseError, string sHelp = "")
{	
	//struct date dateSys;
    //struct time heureSys
    struct tm *tp;

    long t;
    char msg[255];

	ofstream outFile;
    outFile.open("/home/sosinf/test/error.log", ios::app);
	if (!outFile)
		return;

    // calcul de l'heure syst�me
    //getdate(&dateSys);
    //gettime(&heureSys);
    //sprintf(msg, "%02d/%02d/%4d - %02d:%02d:%02d,%02d>\n", dateSys.da_day, dateSys.da_mon,
              //  dateSys.da_year, heureSys.ti_hour, heureSys.ti_min,
               // heureSys.ti_sec, heureSys.ti_hund);

	time (&t);
	tp = localtime (&t);
	strcpy (msg, asctime (tp));
	
    outFile << string(msg,0,strlen(msg)-1) + string(" : ") + string(texte) ;
    outFile << string("\n");
    outFile.close();

	// int erreur(const char *texte, int gravite, DBIResult ErrPx, HWND parent, string sHelp)
	// NOTE : Si parent == NULL (cas par d�faut)
    // La MessageBox ne sera pas modale !!!
    // Comme on ne peut acc�der au contexte, il faut passer un GetHandle()
    // pour ce param�tre � l'appel de la fonction.
    // Attention GetMainWindow()->GetHandle() ne vaut pas NULL...

    /*
  	char buffer[2048];

  	if ((texte[0] == '\0') && (ErrPx == DBIERR_NONE))
   		return(0);

    strcpy(buffer, texte);

	if ((ErrPx != 0) && (ErrPx != DBIERR_NONE))
   	{
    	char        dbi_status[DBIMAXMSGLEN * 5] = {'\0'};
   		DBIMSG      dbi_string = {'\0'};
   		DBIErrInfo  ErrInfo;

   		if (ErrPx != DBIERR_NONE)
   		{
      		DbiGetErrorInfo(TRUE, ErrInfo);

      		if (ErrInfo.iError == ErrPx)
      		{
         		wsprintf(dbi_status, "  ERROR %s", ErrInfo.szErrCode);

         		if (strcmp(ErrInfo.szContext[0], ""))
            		wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext[0]);

         		if (strcmp(ErrInfo.szContext[1], ""))
            		wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext[1]);
         		if (strcmp(ErrInfo.szContext[2], ""))
            		wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext[2]);
         		if (strcmp(ErrInfo.szContext[3], ""))
            		wsprintf(dbi_status, "%s\r\n    %s", dbi_status, ErrInfo.szContext[3]);
      		}
      		else
      		{
         		DbiGetErrorString(ErrPx, dbi_string);
         		wsprintf(dbi_status, "  ERROR %s", dbi_string);
      		}
			if (buffer[0] != '\0')
        		strcat(buffer, "\r\n\r\n");
            strcat(buffer, dbi_status);
   		}
   		//return ErrorValue;
	}

    if (getModeFileErr() == true)
    	fileError(buffer);
    else
    {
        if (sHelp == "")
    	    MessageBox(parent, buffer, "Erreur NAUTILUS", MB_ICONEXCLAMATION|MB_OK);
        else
        {
        	strcat(buffer, "\r\n\r\nSouhaitez vous consulter la marche � suivre face � une telle erreur ?");
            int iRetour = MessageBox(parent, buffer, "Erreur NAUTILUS", MB_YESNO);
            if (iRetour == IDYES)
                ::ShellExecute(parent,
                               "open",
                               sHelp.c_str(),
                               "",
                               "",
                               SW_SHOWNORMAL);
        }
    }
    */
  /*
  	if (gravite == 1)
    	exit(1);

  	return 0;
  	
}



/*
// fonctions de gestion des messages d'erreur
bool getModeFileErr()
{
    return bModeFile;
}

void setModeFileErr(bool bMode)
{
    bModeFile = bMode;
}

void fileError(string sError)
{
    ifstream inFile;
    ofstream outFile;
    string line;
    string sLastError;

    inFile.open("ferror.log");
    if (inFile)
    {
   	    while (!inFile.eof())
        {
            getline(inFile,line);
            if (line != "")
                sLastError += line + "\n";
        }

        inFile.close();
    }
    else // cas fichier vide
        sLastError = "";

    // on ajoute la nouvelle erreur
    sLastError += sError + "\n";

    // On �crit le nouveau fichier reqerror.log
   	outFile.open("ferror.log");
	if (!outFile)
   	{
        // cas d'erreur bloquant...
        MessageBox(NULL, "Erreur d'ouverture en �criture du fichier ferror.log.", "Erreur NAUTILUS", MB_ICONEXCLAMATION);
   		return;
   	}

   	for (int i = 0; i < sLastError.length(); i++)
     	 outFile.put(sLastError[i]);

    outFile.close();
}

*/
string
texteHtml(string texte)
{
	int i;
  string sHtml("") ;

	for (i = 0; i < strlen(texte.c_str()); i++)
  {
  	switch (texte[i])
    {
    	case '�':
      	sHtml = sHtml + "&acirc;";  break ;
      case '�':
      	sHtml = sHtml + "&agrave;"; break ;
      case '�':
      	sHtml = sHtml + "&aelig;";  break ;
      case '�':
      	sHtml = sHtml + "&ccedil;"; break ;
      case '�':
      	sHtml = sHtml + "&Ccedil;"; break ;
      case '�':
      	sHtml = sHtml + "&eacute;"; break ;
      case '�':
      	sHtml = sHtml + "&ecirc;";  break ;
      case '�':
      	sHtml = sHtml + "&egrave;"; break ;
      case '�':
      	sHtml = sHtml + "&euml;";   break ;
      case '�':
      	sHtml = sHtml + "&icirc;";  break ;
      case '�':
      	sHtml = sHtml + "&iuml;";   break ;
      case '�':
      	sHtml = sHtml + "&ocirc;";  break ;
      case '�':
      	sHtml = sHtml + "&ouml;";   break ;
      case '�':
      	sHtml = sHtml + "&Ouml;";   break ;
      case '':
      	sHtml = sHtml + "&ouml;";   break ;
      case '�':
      	sHtml = sHtml + "&uacute;"; break ;
      case '�':
      	sHtml = sHtml + "&ugrave;"; break ;
      case '�':
      	sHtml = sHtml + "&ucirc;";  break ;
      case '�':
      	sHtml = sHtml + "&uuml;";   break ;
      case '�':
      	sHtml = sHtml + "&Uuml;";   break ;
      case '<':
      	sHtml = sHtml + "&lt;"; break;
      case '>':
      	sHtml = sHtml + "&gt;"; break;
      case '&':
      	sHtml = sHtml + "&ramp;"; break;
      case '"':
      	sHtml = sHtml + "&quot;"; break;
      case '|':
      	sHtml = sHtml + "&#124;"; break;
      default :
      	sHtml = sHtml + texte[i];
    }
	}
	return sHtml;
}

string
texteCourant(string textHtml)
{
	string textOut = textHtml;
   	int    pos = textOut.find("&");
   	int    len;

   	while (pos != string::npos)
   	{
    	len = strlen(textOut.c_str()) - pos;

   		if 		((len >= 7) && (string(textOut,pos,7) == "&acirc;"))
      		textOut.replace(pos, 7, "�");
      	else if ((len >= 8) && (string(textOut,pos,8) == "&agrave;"))
      		textOut.replace(pos, 8, "�");
        else if ((len >= 8) && (string(textOut,pos,7) == "&aelig;"))
      		textOut.replace(pos, 7, "�");
      	else if ((len >= 8) && (string(textOut,pos,8) == "&ccedil;"))
      		textOut.replace(pos, 8, "�");
        else if ((len >= 8) && (string(textOut,pos,8) == "&Ccedil;"))
      		textOut.replace(pos, 8, "�");
      	else if ((len >= 8) && (string(textOut,pos,8) == "&eacute;"))
      		textOut.replace(pos, 8, "�");
      	else if ((len >= 7) && (string(textOut,pos,7) == "&ecirc;"))
      		textOut.replace(pos, 7, "�");
      	else if ((len >= 8) && (string(textOut,pos,8) == "&egrave;"))
      		textOut.replace(pos, 8, "�");
      	else if ((len >= 6) && (string(textOut,pos,6) == "&euml;"))
      		textOut.replace(pos, 6, "�");
      	else if ((len >= 7) && (string(textOut,pos,7) == "&icirc;"))
        	textOut.replace(pos, 7, "�");
      	else if ((len >= 6) && (string(textOut,pos,6) == "&iuml;"))
      		textOut.replace(pos, 6, "�");
      	else if ((len >= 7) && (string(textOut,pos,7) == "&ocirc;"))
      		textOut.replace(pos, 7, "�");
        else if ((len >= 6) && (string(textOut,pos,6) == "&ouml;"))
      		textOut.replace(pos, 6, "�");
        else if ((len >= 6) && (string(textOut,pos,6) == "&Ouml;"))
      		textOut.replace(pos, 6, "�");
        else if ((len >= 8) && (string(textOut,pos,8) == "&uacute;"))
      		textOut.replace(pos, 8, "�");
        else if ((len >= 8) && (string(textOut,pos,8) == "&ugrave;"))
      		textOut.replace(pos, 8, "�");
        else if ((len >= 7) && (string(textOut,pos,7) == "&ucirc;"))
      		textOut.replace(pos, 7, "�");
        else if ((len >= 6) && (string(textOut,pos,6) == "&uuml;"))
      		textOut.replace(pos, 6, "�");
        else if ((len >= 6) && (string(textOut,pos,6) == "&Uuml;"))
      		textOut.replace(pos, 6, "�");
      	else if ((len >= 4) && (string(textOut,pos,4) == "&lt;"))
      		textOut.replace(pos, 4, "<");
      	else if ((len >= 4) && (string(textOut,pos,4) == "&gt;"))
      		textOut.replace(pos, 4, ">");
      	else if ((len >= 6) && (string(textOut,pos,6) == "&ramp;"))
      		textOut.replace(pos, 6, "&");
      	else if ((len >= 6) && (string(textOut,pos,6) == "&quot;"))
      		textOut.replace(pos, 6, "\"");
      	else if ((len >= 6) && (string(textOut,pos,6) == "&#124;"))
        	textOut.replace(pos, 6, "|");

    	pos++;

      	pos = textOut.find("&",pos);
	}
   	return textOut;
}


// void strip(string& s, int n)
// --------------------------------------------------------------------------
// Fonction : enleve les blancs d'une string
// Retour : rien
void strip(string& s, STRIPTYPE n, char c)
{
    int pos1, pos2;

    if (s == "")
        return;

    switch (n)
    {
        case stripBoth :
            pos1 = s.find_first_not_of(c);
            pos2 = s.find_last_not_of(c);

            if ((pos1 != string::npos) && (pos2 != string::npos))
                s = string(s, pos1, pos2-pos1 + 1);
            break;

        case stripLeft :
            pos1 = s.find_first_not_of(c);

            if (pos1 != string::npos)
                s = string(s, pos1, strlen(s.c_str()) - pos1);
            break;

        case stripRight :
            pos2 = s.find_last_not_of(c);

            if (pos2 != string::npos)
                s = string(s, 0, pos2+1);
            break;

//        default :
//            erreur("Fonction strip : option erronn�e", 0, 0);
    }
}

int donneDigit(char nbre)
{
	if (!isdigit(nbre))
		return -1;
	return int(nbre) - int('0');
}

char donneChar(int digit)
{
	if ((digit >= 0) && (digit < 10))
   		return char(int('0') + digit);
   	else
   		return '*';
}


double
StringToDouble(string sValeur)
{
	//
   	// Extraction de la partie enti�re et de la partie d�cimale
   	//
   	string sEntier = "";
   	string sDecima = "";
   	size_t i = sValeur.find(".");
   	if (i == string::npos)
   		i = sValeur.find(",");

   	if ((i == string::npos) || ( i > strlen(sValeur.c_str())))
   		sEntier = sValeur;
   	else
   	{
   		if (i > 0)
      		sEntier = string(sValeur, 0, i);
      	sDecima = string(sValeur, i+1, strlen(sValeur.c_str())-i-1);
   	}
   	//
   	// Calcul de la valeur
   	//
   	double dValeur = 0;
   	// Partie enti�re
   	for (i = 0; i < strlen(sEntier.c_str()); i++)
   	{
    	if (!isdigit(sEntier[i]))
        	return 0;
   		dValeur = (dValeur * double(10)) + double(donneDigit(sEntier[i]));
   	}
   	// Partie d�cimale
   	double multi = double(1);
   	for (int i = 0; i < strlen(sDecima.c_str()); i++)
   	{
   		if (!isdigit(sDecima[i]))
      		return 0;
      	multi = multi * 0.1;
      	dValeur += double(donneDigit(sDecima[i])) * multi;
   	}

   	return dValeur;
}

//-------------------------------------------------------------------
// convertit un double en une string
//-------------------------------------------------------------------
string
DoubleToString(double* pDouble, int iEntier, int iDecimal)
{
	double dVal = *pDouble;
   	if (dVal == 0)
		return "0";

   	bool bNegatif = false; //double n�gatif
   	if (dVal < 0)
   	{
   		bNegatif = true;
      	dVal = -dVal;
   	}
	double dLog = log10(dVal);
   	int	   iLog = int(dLog);
   	double dMult = pow(double(10), double(iLog));
   	double dResu;

   	string sResult = "";
   	//
   	// Assemblage de la partie enti�re
   	//
   	while (iLog >= 0)
   	{
   		dResu = floor(dVal / dMult);
      	sResult += string(1, donneChar(int(dResu)));

      	dVal = dVal - (dResu * dMult);
      	dMult = dMult / 10;
      	iLog--;
   	}
   	if ((iDecimal == 0) || ((iDecimal == -1) && (dVal == 0)))
    {
        if (bNegatif)
   			sResult = "-" + sResult;
   		return sResult;
    }
   	//
   	// Assemblage de la partie d�cimale
   	//
    if (sResult == "")
    	sResult = "0";
   	sResult += ".";
   	iLog = 0;
   	bool tourner = true;
   	while (tourner)
   	{
   		dResu = floor(10 * dVal);
        // Si on en est � inscrire le dernier chiffre significatif, il faut
        // arrondir
        if ((iDecimal > 0) && (iLog == iDecimal-1) &&
        									(10 * dVal - dResu > double(0.5)))
        {
            if (dResu < 9)
        		sResult += string(1, donneChar(int(dResu)+1));
            else
            {
                int i = strlen(sResult.c_str()) - 1;
            	bool bIncrementer = true;
                while ((i >= 0) && bIncrementer)
                {
                	if (isdigit(sResult[i]))
                    {
                    	int j = donneDigit(sResult[i]);
                        if (j < 9)
                        {
                        	j++;
                            sResult[i] = donneChar(j);
                            bIncrementer = false;
                        }
                        else
                        {
                        	sResult[i] = '0';
                            if (i == 0)
                            	sResult = string("1") + sResult;
                        }
                    }
                    i--;
                }
                sResult += string("0");
            }
        }
        else
        	sResult += string(1, donneChar(int(dResu)));

      	dVal = (10 * dVal) - dResu;
      	iLog++;
      	if ((iDecimal > 0) && (iLog >= iDecimal))
      		tourner = false;
      	if ((iDecimal == -1) && ((iLog > 10) || (dVal == 0)))
      		tourner = false;
   	}

   	if (bNegatif)
   		sResult = "-" + sResult;
   	return sResult;
}
