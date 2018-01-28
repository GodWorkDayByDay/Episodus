//---------------------------------------------------------------------------
//     NSCACHE.H
//
//  Contient les d�finitions des matrices dynamiques utilis�es pour
//  l'analyse de cha�nes de configuration.
//
//  D�finit les CacheElement qui sont des vecteurs non dynamiques,
//  dont on pr�cise la taille dans le constructeur.
//
//  KP
//  Cr�ation : janv.92         Derni�re mise � jour : sept 93
//---------------------------------------------------------------------------
#ifndef __NSCACHE_H
#define __NSCACHE_H

/*#ifndef __NSWPARAM_H
#include "nswparam.h"
#endif */

#ifndef __NSDEBUG_H
#include "partage\nsdebug.h"
#endif

#include "partage\ns_vector.h"
#ifndef __ARRAYS_H
#include <classlib\arrays.h>
#endif

#ifndef __CSTRING_H
#include <cstring.h>
#endif


#if defined(_NSUTILDLL)
	#define _CLASSUTIL __export
#else
	#define _CLASSUTIL __import
#endif



//---------------------------------------------------------------------------
// D�finition du CacheElement
//---------------------------------------------------------------------------
typedef TArrayAsVector<string> ChaineArray;

/*typedef vector<string*> ChaineArray;
typedef ChaineArray::iterator ChaineArrayIter;

class CChaineArray : public ChaineArray
{
public :
	// Constructeurs
	CChaineArray() : ChaineArray() {}
	CChaineArray(CChaineArray& rv);
	// Destructeur
	virtual ~CChaineArray();
	// Op�rateur =
	CChaineArray& operator=(CChaineArray src);
   void vider();
};
*/

class _CLASSUTIL CacheElement
{
	public :

	ChaineArray *listItems;   // Pointeur sur un vecteur de Chaines
	int nbItems;              // Nombre d'items

	// Constructeurs
	CacheElement(int nb = 1)
	: nbItems(nb), listItems(new ChaineArray(0, nb-1, 0)){}

/*	CacheElement(int nb = 1)
	: nbItems(nb), listItems(new CChaineArray()){}
*/
	CacheElement(CacheElement& src);
	CacheElement(ChaineArray& src, int indexBegin, int nb = 1);

	// Destructeur
	virtual ~CacheElement() { delete listItems;}

	// Surcharges de l'op�rateur = et de == (Obligatoire pour le bon
	// fonctionnement de classlib
	CacheElement& operator=(CacheElement src);
	int operator==(const CacheElement& x);

	// Acc�s aux donn�es membres
	string&  getItem(int index = 0) { return (*listItems)[index]; }
};
//---------------------------------------------------------------------------
// D�finition du CacheArray
//---------------------------------------------------------------------------
//typedef TArrayAsVector<CacheElement> CacheElementArray;

typedef vector<CacheElement*> CacheElementArray;
typedef CacheElementArray::iterator CacheElementArrayIter;

class _CLASSUTIL CacheArray : public CacheElementArray
{
	int nIndexCurr;    // Index de transit, car cette classe est utilis�e
							 // dans une fonction membre static de NSDialog
	public :

	// Constructeurs
	CacheArray() : CacheElementArray(), nIndexCurr(0) {}
	CacheArray(CacheArray& rv);

	// Destructeur
	virtual ~CacheArray();

	// Manipulation de l'index, incr�mentation
	void IncIndex(int nIncr) { nIndexCurr += nIncr;}
	int index() { return nIndexCurr; }
   void vider();
};

#endif   // #ifndef __NSCACHE