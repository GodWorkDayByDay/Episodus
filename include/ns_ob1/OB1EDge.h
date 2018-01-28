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
#ifndef   OB1EDGE_H_
# define   OB1EDGE_H_

#include "ns_ob1\OB1Types.h"

/**
* \brief Represent the condition value beetwen two controler's node
*/
/**
*  Represent the condition value beetwen two controler's node <BR>
*  Represente les conditions de parcours entre deux noeud
*/
class OB1Edge
{
  protected:

    OB1EdgeType _KindOf ;     /**< type of the edge */
    int         _Class_mask ; /**< class alloweed : it can be a combinaison of class */
    int         _complexity ; /**< Complexity of the KS */
    int         _fiability ;  /**< fiability of the result */

    static long _lObjectCount ;

  public:

    OB1Edge() ;
    OB1Edge(OB1EdgeType TE) ;
    OB1Edge(OB1EdgeType ter, int clas_mask, int _comple = 0, int _fiabil = 0) ;
    ~OB1Edge() ;

    OB1EdgeType TypeOf() ;
    void ChangeType(OB1EdgeType TE) ;

    /*
    ** Test if classes is allowed
    */
    bool  CompareClassMask() ;   /* test if the token is allowed */
    int   getComplexity() ;      /* return the complexity of the node */
    int   getFiability() ;       /* get the fiability of the result */

    inline int Class() { return _Class_mask ; }  /* return the mask */

    static long getNbInstance()  { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }
};

/**
* \brief Represent the condition value beetwen two controler's node (with precision)
*/
/**
*  Represent the condition value beetwen two controler's node (with precision) <BR>
*  Represente les conditions de parcours entre deux noeud en tenant compte des niveaux
*  de precision  voulue
*/
class OB1EdgeLevel : public OB1Edge
{
  private :

    int _level ;

  public :

    OB1EdgeLevel(OB1EdgeType TE, int level) : OB1Edge(TE)
    {
      _level = level ;
    }

    OB1EdgeLevel(OB1EdgeType ter, int clas_mask, int comple, int fiabil, int level) ;
};

#endif  /* End of BB1TEdge */

