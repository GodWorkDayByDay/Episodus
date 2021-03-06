//----------------------------------------------------------------------------// Fonctions non exportables de la DLL NSDKE
//----------------------------------------------------------------------------
#ifndef __DZZGLOB_H
#define __DZZGLOB_H

#include "dcodeur\nsgen.h"
#include "dzz\dzzdecod.h"

void ajout_separateur(string *phrase, unsigned int niveau);

//-----------------------------------------------------------------
// classe decLesion
//
// D�codage des l�sions
//-----------------------------------------------------------------
class decLesion : public decodage
{
  public:

    bool bInscrit ;

    decLesion(NSContexte* pCtx, int iDecoType = dcPhrase) ;
    decLesion(decodageBase* pBase, int iDecoType = dcPhrase) ;
    virtual ~decLesion() {}

    void BioLibLoc(int colonne) ;

    void initPhrase() ;
    void debutPhrase() ;
    void finPhrase() ;

    virtual void decode(int colonne) = 0 ;
    virtual void donnePhrase() = 0 ;

  protected:

    int iDcType ;
};

//-----------------------------------------------------------------
// classe decSousLesion
//
// D�codage des l�sions
//-----------------------------------------------------------------
class decSousLesion : public decodage
{
  public:

    bool bInscrit ;

    decSousLesion(NSContexte* pCtx, int iDecoType = dcPhrase) ;
    decSousLesion(decodageBase* pBase, int iDecoType = dcPhrase) ;
    virtual ~decSousLesion() {}

    void BioLibLoc(int colonne) ;

    virtual void decode(int colonne) = 0 ;
    virtual void donnePhrase() = 0 ;

    void 	 initPhrase() {}
    void 	 debutPhrase() {}
    void 	 finPhrase() {}

  protected:

    int iDcType ;
};

#endif  // __DZZGLOB_H

