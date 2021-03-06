/*
** Copyright Nautilus, (10/9/2004)
** fabrice.le_perru@nautilus-info.com
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

#ifndef __ATTVALPAIR_H__
#define __ATTVALPAIR_H__ 1

#ifdef __GNUC__
//#  pragma interface
#endif // __GNUC__

class TypedVal ;
class BB1Object ;
class BB1Event ;

// #include "nsbb\nspatpat.h"
#include "ns_ob1\TypedVal.h"

//class ostream;   // for operator<<(...)

/**
* \brief Variable of a \relates BB1Object
*/
/**
*  Variable of a \relates BB1Object   <BR>
* Variable d'un objet de type   \relates BB1Object
*/
class _BBKEXPORT AttValPair
{
  // Allowed to call setValue(...)
	friend class BB1Object ;

  public: // API

	  //AttValPair() : att(NULLSTRING), val(NULL) {} ;

	  AttValPair(const AttValPair& avp) ;

    AttValPair(const string& a, const TypedVal&   tv) ;
    AttValPair(const string& a, const bool				b ) : _att(a), _val(b) { _lAVPCount++ ; } ;
    AttValPair(const string& a, const int         i ) : _att(a), _val(i) { _lAVPCount++ ; } ;
    AttValPair(const string& a, const double      d ) : _att(a), _val(d) { _lAVPCount++ ; } ;
    AttValPair(const string& a, const long        l ) : _att(a), _val(l) { _lAVPCount++ ; } ;
    AttValPair(const string& a, const string&     s ) : _att(a), _val(s) { _lAVPCount++ ; } ;
    AttValPair(const string& a, const Voidptr     p ) : _att(a), _val(p) { _lAVPCount++ ; } ;
    AttValPair(const string& a, NautilusQuestion  *quest) : _att(a), _val(quest) { _lAVPCount++ ; } ;
    AttValPair(const string& a, AnswerStatus      *statu) : _att(a), _val(statu) { _lAVPCount++ ; } ;
  //	AttValPair(const string& a, NSPatPathoArray					*patho)                     : att(a), val(patho) 	      {} ;
    AttValPair(const string& a, NSPatPathoArray		*patho, bool bExt = false)  : _att(a), _val(patho, bExt) 	{ _lAVPCount++ ; } ;
    AttValPair(const string& a, BB1Object					*objet)                     : _att(a), _val(objet)	      { _lAVPCount++ ; } ;
    AttValPair(const string& a, NautilusEvent			*event, bool bExt = false)  : _att(a), _val(event, bExt)	{ _lAVPCount++ ; } ;
    AttValPair(const string& a, vector<HANDLE>		*handles, bool bExt = false): _att(a), _val(handles)	    { _lAVPCount++ ; } ;
    AttValPair(const string& a, NSSearchStruct		*search) : _att(a), _val(search) { _lAVPCount++ ; } ;

    #ifdef __OB1__UNOPTIM__
    AttValPair(const string& a, const float          				f ) : _att(a), _val(f )		 { _lAVPCount++ ; } ;
    AttValPair(const string& a, PathsList 							*paths) : _att(a), _val(paths) { _lAVPCount++ ; } ;
    AttValPair(const string& a, const short          				s ) : _att(a), _val(s )		 { _lAVPCount++ ; } ;
    AttValPair(const string& a, const char           				c ) : _att(a), _val(c )		 { _lAVPCount++ ; } ;
    AttValPair(const string& a, const unsigned char  				uc) : _att(a), _val(uc)		 { _lAVPCount++ ; } ;
    AttValPair(const string& a, const unsigned int   				ui) : _att(a), _val(ui)		 { _lAVPCount++ ; } ;
    AttValPair(const string& a, const unsigned long  				ul) : _att(a), _val(ul)		 { _lAVPCount++ ; } ;
    AttValPair(const string& a, const unsigned short 				us) : _att(a), _val(us)		 { _lAVPCount++ ; } ;
    #endif

    ~AttValPair() { _lAVPCount-- ; } ;

    void swapPatho(NSPatPathoArray *patho, bool bExt = false) ;

    // Attribute name accessor
    const string& AttributeName() const				 { return _att ; }

    // Attribute value accessor
    const TypedVal& AttributeValue(void) const { return _val ; }
    TypedVal*       AttributeValuePtr()        { return &_val ; }

    AttValPair&	operator=(const AttValPair& avp) ;
    // Equal relop
    bool operator==(const AttValPair& avp) const { return ((_att == avp._att) && (_val == avp._val)) ; }

    // Not-equal relop
    bool operator!=(const AttValPair& avp) const { return !((*this) == avp) ; }

    static long getNbInstance()  { return _lAVPCount ; }
    static void initNbInstance() { _lAVPCount = 0 ; }

  private:

	  // Value write accessor; operator= is overloaded for TypedVal
	  Errcode setValue(const AttValPair& avp) { _val = avp.AttributeValue() ; return SUCCESS ; }

 private:

    std::string _att ;  // attribute internal representation
    TypedVal    _val ;  // value internal representation

    static long _lAVPCount ;
};


typedef AttValPair* AVPptr ;

std::ostream& operator <<(std::ostream& os, const AttValPair& avp) ;

void ClearSetOfAVP(AVPSet *avpset) ;

#endif // __ATTVALPAIR_H__

