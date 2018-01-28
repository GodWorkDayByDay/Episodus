// -----------------------------------------------------------------------------
// valeur.h
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// $Revision: 1.4 $
// $Author: pameline $
// $Date: 2013/11/11 23:15:51 $
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Copyright Nautilus, 2004
// http://www.nautilus-info.com
// -----------------------------------------------------------------------------
// Ce logiciel est un programme informatique servant � g�rer et traiter les
// informations de sant� d'une personne.
//
// Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
// respectant les principes de diffusion des logiciels libres. Vous pouvez
// utiliser, modifier et/ou redistribuer ce programme sous les conditions de la
// licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA sur le site
// "http://www.cecill.info".
//
// En contrepartie de l'accessibilit� au code source et des droits de copie, de
// modification et de redistribution accord�s par cette licence, il n'est offert
// aux utilisateurs qu'une garantie limit�e. Pour les m�mes raisons, seule une
// responsabilit� restreinte p�se sur l'auteur du programme, le titulaire des
// droits patrimoniaux et les conc�dants successifs.
//
// A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
// associ�s au chargement, � l'utilisation, � la modification et/ou au
// d�veloppement et � la reproduction du logiciel par l'utilisateur �tant donn�
// sa sp�cificit� de logiciel libre, qui peut le rendre complexe � manipuler et
// qui le r�serve donc � des d�veloppeurs et des professionnels avertis
// poss�dant des connaissances informatiques approfondies. Les utilisateurs sont
// donc invit�s � charger et tester l'ad�quation du logiciel � leurs besoins
// dans des conditions permettant d'assurer la s�curit� de leurs syst�mes et ou
// de leurs donn�es et, plus g�n�ralement, � l'utiliser et l'exploiter dans les
// m�mes conditions de s�curit�.
//
// Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez pris
// connaissance de la licence CeCILL, et que vous en avez accept� les termes.
// -----------------------------------------------------------------------------
// This software is a computer program whose purpose is to manage and process
// a person's health data.
//
// This software is governed by the CeCILL  license under French law and abiding
// by the rules of distribution of free software. You can use, modify and/ or
// redistribute the software under the terms of the CeCILL license as circulated
// by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
//
// As a counterpart to the access to the source code and  rights to copy, modify
// and redistribute granted by the license, users are provided only with a
// limited warranty and the software's author, the holder of the economic
// rights, and the successive licensors have only limited liability.
//
// In this respect, the user's attention is drawn to the risks associated with
// loading, using, modifying and/or developing or reproducing the software by
// the user in light of its specific status of free software, that may mean that
// it is complicated to manipulate, and that also therefore means that it is
// reserved for developers and experienced professionals having in-depth
// computer knowledge. Users are therefore encouraged to load and test the
// software's suitability as regards their requirements in conditions enabling
// the security of their systems and/or data to be ensured and, more generally,
// to use and operate it in the same conditions as regards security.
//
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
// -----------------------------------------------------------------------------
#ifndef __VALEUR_H__
# define __VALEUR_H__

# ifndef FOR_WINDOWS
// #  include <stl.h>
# else
#  include <vector.h>
#  include <fstream.h>
#  include "nsbb/nsExport.h"
# endif

# include <string>

# ifndef __MAIN
extern ofstream debugFile ;
# else
ofstream debugFile ;
# endif

class Cbalise ;

#ifndef __linux__
class _NSBBCLASSE CValeur
#else
class CValeur
#endif
{
  private:

    static long lObjectCount ;

  protected:

    bool _bObjectIsCopy ;

  public:

    Cbalise* _parent ;

    string   _sLabel ;
    string   _sValue ;
    string   _sAttribute ;
    Cbalise* _pObject ;

    CValeur(Cbalise *pere) ;
    CValeur(string label, string value, string attribute, Cbalise *pere) ;
    CValeur(const CValeur& rv, Cbalise *pere) ;
    CValeur(const CValeur& rv) ;

    ~CValeur () ;

    string   getLabel()              { return _sLabel ; }
    void     setLabel(string sL)     { _sLabel = sL ; }

    string   getValue()              { return _sValue ; }
    void     setValue(string sV)     { _sValue = sV ; }

    string   getAttribute()          { return _sAttribute ; }
    void     setAttribute(string sA) { _sAttribute = sA ; }

    Cbalise* getObject()             { return _pObject ; }
    void     setObject(Cbalise* pO)  { _pObject = pO ; }

    CValeur& operator=(const CValeur& src) ;

    static long getNbInstance()  { return lObjectCount ; }
    static void initNbInstance() { lObjectCount = 0 ; }
} ;

typedef vector<CValeur *>         ValArray ;
typedef ValArray::iterator        ValIter ;
typedef ValArray::const_iterator  ValCIter ;

#ifndef __linux__
class _NSBBCLASSE Valeur_array : public ValArray
#else
class Valeur_array : public ValArray
#endif
{
  public:

    Cbalise* _parent ;

    // Constructeurs
    Valeur_array(Cbalise *pere) ;
    Valeur_array(const Valeur_array& rv) ;

    // Destructeur
    ~Valeur_array() ;

    void vider() ;

    // Op�rateurs
    Valeur_array& operator=(const Valeur_array& src) ;
    //Valeur_array    operator+(Valeur_array src) ;
} ;

#endif // !__VALEUR_H__

