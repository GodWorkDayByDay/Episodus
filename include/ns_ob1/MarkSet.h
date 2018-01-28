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

#ifndef   MARKSET_H_
# define   MARKSET_H_

#include <vector>
#include <string>
#include "ns_ob1\Marker.h"

/**
* \brief Decorator set for node
*/
/**
* Decorator set for node <BR>
* Ensemble de noeud de decoration
*/
class MarkSet
{
  protected:

    ValeurArray _Marks ;

    static long _lObjectCount ;

  public:

    /**
     * \brief Constructor
     */
    /**
     * Constructor
     */
    MarkSet() ;
    MarkSet(const MarkSet& rv) ;

    /**
     * \brief Destructor
     */
    /**
     * Destructor
     */
    ~MarkSet() ;

    void reset() ;

    /**
     * \brief Say if a var exist in the set
     */
    /**
     * Say if a var exist in the set   <BR>
     * Indique si il y a un decorateur de ce nom dans l'ensemble
     * @return true if temp exist, false else
     */
    bool Exist(std::string& temp) ;

    /**
     * \brief Insert the key and the object if they don't exist
     */
    /**
     *  Insert the key and the object if they don't exist
     *  Insere une marque dans l'ensemble si elle n'existe pas deja
     *  @param key Identifiant of mark to insert
     *  @param temp OBject to insert
     */
    void insert(std::string& key, MarkerObject* temp) ;

    /**
     * \brief set parameter string as key and put the Marker'objecct parameter as value.
     */
    /**
     * \brief set parameter string as key and put the Marker'objecct parameter as value.  <BR>
     * Insere un nouveau marker dans l'objet si il  d�ja
     *  @param key Identifiant of mark to set
     *  @param temp OBject to set
     */
    void set(std::string& key, MarkerObject* temp) ;

    /**
     * \brief get the number of object in the markset
     */
    /**
     * get the number of object in the markset  <BR>
     * Renvoie le nombre de mark pr�sent dans l'ensemble
     * @return number of object in the markset
     */
    const int DecorateurSize()const { return _Marks.size() ; }

    /**
     * \brief Test if a marker with name anf and value vla exist
     */
    /**
     * Test if a marker with name anf and value vla exist <BR>
     * Test si une chaine dont le nom est name et la valeur est vla exist
     * @param name key name
     * @param  vla value of the object
     * @return true if the mark exist and false else
     */
    bool hasStringAttributes(std::string name, std::string vla) ;

    /**
     * \brief Test if a marker with substring name anf and value vla exist
     */
    /**
     * Test if a marker with substring name anf and value vla exist <BR>
     * Test si un marker de type string contient une sous string ayant une value vla existe
     * \todothe test seem to have in error != == npos
     * @param name first substring to find in key
     * @param  vla value of the object
     * @return true if the mark exist and false else
     */
    bool hasSubStringAttributes(std::string name, std::string vla) ;

    /**
     * \brief get Value from index
     */
    /**
     * get Value from index <BR>
     * Renvoie la valeur d'une mark pr�sent en fonction de son index
     * @param i index
     * @return wanted value
     */
    Valeur* operator[] (unsigned int i) const ;

    /**
     *  \brief get the value of the key key_to_find
     */
    /**
     * get the value of the key key_to_find
     * @param key_to_find value to find
     */
    MarkerObject* get(std::string& key_to_find) ;

    /**
     * \brief Remove a marker
     */
    /**
     * Remove a marker
     * @param key key to remove
     */
    void Remove(std::string& key) ;

    MarkSet& operator=(const MarkSet& src) ;

    static long getNbInstance()  { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }
};

/**
* \brief overloading of  << operator for MarkSet
*/
std::ostream&	operator<< (std::ostream& ostr, const MarkSet& m);

#endif /* MARKSET_H_ */
