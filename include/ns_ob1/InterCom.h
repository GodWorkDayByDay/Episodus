/*
** Copyright Nautilus, (10/9/2004)
** david.giocanti@nautilus-info.com

** Ce logiciel est un programme informatique servant � [rappeler les
** caract�ristiques techniques de votre logiciel].

** Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
** respectant les principes de diffusion des logiciels libres. Vous pouvez
** utiliser, modifier et/ou redistribuer ce programme sous les conditions
** de la licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA
** sur le site "http://www.cecill.info".

** En contrepartie de l'accessibilit� au code source et des droits de copie,
** de modification et de redistribution accord�s par cette licence, il n'est
** offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
** seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
** titulaire des droits patrimoniaux et les conc�dants successifs.

** A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
** associ�s au chargement,  � l'utilisation,  � la modification et/ou au
** d�veloppement et � la reproduction du logiciel par l'utilisateur �tant
** donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
** manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
** avertis poss�dant  des  connaissances  informatiques approfondies.  Les
** utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
** logiciel � leurs besoins dans des conditions permettant d'assurer la
** s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
** � l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.

** Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez
** pris connaissance de la licence CeCILL, et que vous en avez accept� les
** termes.
*/

#ifndef __INTERPERTER__COMMUNICATION__
#define 		__INTERPERTER__COMMUNICATION__
/**
* Ce fichier sert a cr�er une interface pour pouvoir permettre de se relier
* � un interpreteur.
* Le role de cette interface est d'assurer une possibilit� de changer
* d'interpreteur si on le d�sire
*
* Son r�le principale est d�finir un ensemble de fonction minimale �
* implementer pour pouvoir assurer une compatibilit�.
*/

#include <string>

class InterCom
{
	protected:
  	std::string _fileToInterpret;

	public:
    InterCom(const InterCom& temp);
    InterCom& operator=(const InterCom& tmp);

  public:
  	/*
    ** Load file, parser and make what you have to do
    */
    void Load() = 0;

  	/*
    ** Renvoie le nom de fichier
    */
  	inline std::string getFileName();

    /*
    ** Indique le nom de fichier
    */
    inline void setFileName(std::string nam);

  public:
    void  ExecuteFunction(std::string funcName) = 0;

};

/*
** Renvoie le nom de fichier
*/
inline std::string  getFileName()
{
	return fileToInterpret;
}

/*
** Indique le nom de fichier
*/
inline void setFileName(std::string name)
{
	_fileToInterpret = name;
}


#endif
