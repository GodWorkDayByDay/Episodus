//---------------------------------------------------------------------------
//     NSCACHE.CPP
//
//  Impl�mentation de CacheElement.
//  Impl�mentation de NSCache.
//
//  KP
//  Cr�ation : janv.92         Derni�re mise � jour : sept 93
//---------------------------------------------------------------------------

//#include <stdio.h>



#include "nsutil\nscache.h"

//#include <cstring.h>
//--------------------------------------------------------------------------
//
// Impl�mentation de NSCacheElement
//
//--------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  Function: CacheElement::CacheElement(CacheElement& src)
//
//  Arguments:
//            src  -> CacheElement � copier
//  Description:
//            Constructeur copie. D�fini pour assurer la s�mantique copie.
//            ATTENTION : Les CacheElement ne sont pas redimensionnables.
//                        On en d�finit la taille dans le constructeur.
//  Returns:
//            RIEN
//---------------------------------------------------------------------------
CacheElement::CacheElement(CacheElement& src)
{
	nbItems = src.nbItems;

	// On alloue un tableau non redimensionnable
	listItems = new ChaineArray(nbItems, 0);

	for (int i = 0; i < nbItems; i++)
		listItems->Add(src.getItem(i));
}

//---------------------------------------------------------------------------
//  Function: CacheElement::CacheElement(ChaineArray& src, int indexBegin,
//                                       int nb)
//  Arguments:
//            src        ->  Vecteur de Chaine � partir de laquelle on veut
//                           construire un CacheElement
//            indexBegin ->  Index de d�but
//            nb         ->  Nombre d'�l�ments de src intervenant.
//  Description:
//            Ce constructeur est destin� � �tre utilis� dans strAnalyse()
//            puisque � l'aide de strtok() on peut construire un vecteur
//            de cha�nes � partir duquel on construit des CacheElement.
//  Returns:
//            RIEN
//---------------------------------------------------------------------------
CacheElement::CacheElement(ChaineArray& src, int indexBegin, int nb)
{
	nbItems = nb;
	listItems = new ChaineArray(nbItems, 0);

	for (int i = 0; i < nbItems; i++)
		listItems->Add(src[indexBegin+i]);
}

//---------------------------------------------------------------------------
//  Function: RCacheElement CacheElement::operator=(CacheElement src)
//
//  Arguments:
//            src  ->  CacheElement que l'on veut affecter
//  Description:
//            Cet op�rateur est red�fini pour pr�server la s�mantique copie.
//  Returns:
//            RIEN
//---------------------------------------------------------------------------
CacheElement& CacheElement::operator=(CacheElement src)
{
	if (listItems)
		delete listItems;

	nbItems = src.nbItems;
	listItems = new ChaineArray(nbItems, 0);

	for (int i = 0; i < nbItems; i++)
		listItems->Add(src.getItem(i));

	return *this;
}

//---------------------------------------------------------------------------
//  Function: int CacheElement::operator==(const CacheElement& src)
//
//  Arguments:
//            src  ->  CacheElement que l'on veut affecter
//  Description:
//            Cet op�rateur est red�fini pour pr�server la s�mantique copie.
//  Returns:
//            RIEN
//---------------------------------------------------------------------------
int CacheElement::operator==(const CacheElement& x) {
	bool result = true;       // R�sultat de la comparaison terme � terme

	result = (nbItems != x.nbItems);

	for ( int i = 0; (i < nbItems)&& result; i++)
		result = ((*(this->listItems))[i] == (*(x.listItems))[i]);
	return result;
}

//--------------------------------------------------------------------------
//
// Impl�mentation de CacheArray
//
//--------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  Function: CacheArray::CacheArray(RCacheArray rv)
//
//  Arguments:
//            src  -> CacheArray que l'on veut copier
//  Description:
//            Constructeur copie.
//  Returns:
//
//---------------------------------------------------------------------------
CacheArray::CacheArray(CacheArray& rv)
: CacheElementArray(), nIndexCurr(0)
{
   if (!(rv.empty()))
	   for (CacheElementArrayIter i = rv.begin(); i != rv.end(); i++)
			 	push_back(new CacheElement(*(*i)));
}
//---------------------------------------------------------------------------
//  Function: CacheArray::~CacheArray()
//
//  Arguments:
//            AUCUN
//  Description:
//            Destructeur.
//            D�truit chaque �l�ment de la CacheArray.
//  Returns:
//
//---------------------------------------------------------------------------
void
CacheArray::vider()
{
	for (CacheElementArrayIter i = begin(); i != end(); )
   {
   	delete *i;
      erase(i);
   }
}

CacheArray::~CacheArray()
{
	vider();
}


//---------------------------------------------------------------------------
//  Function: int CacheArray::null(int i)
//
//  Arguments:
//            i -> indice dont on veut tester la nullit�
//  Description:
//            Teste si l'objet plac� � l'indice i est NULL
//  Returns:
//            0 si l'objet n'est pas le pointeur NULL
//            1 si il l'est
//---------------------------------------------------------------------------
/*int CacheArray::null(int i)
{
  CacheElement test = (*this)[i];
  return (test == NULL);
} */

