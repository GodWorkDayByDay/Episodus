// -----------------------------------------------------------------------------
// RVDB_CardioVasculaireKS.h
// -----------------------------------------------------------------------------
// $Revision: 1.3 $
// $Author: philippe $
// $Date: 2005/05/13 17:56:03 $
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// FLP  - d�cembre 2003
// -----------------------------------------------------------------------------

#ifndef __DETECT_IR_H__
#define __DETECT_IR_H__

#include <bwcc.h>

class NSHistoryValManagementArray ;

#include "ns_ob1\nsbbk.h"
#include "ns_ob1\InitStructure.h"  // for KSInitStructure
#include "ns_ob1\abstractKS.h"     // for Abtract
#include "ns_ob1\Transfer.h"        // for TRansfert

class DetectIR : public AbstractKS
{
 public:

 	DetectIR() ;
	~DetectIR() ;

	bool                TriggerCondition(const BB1Event& event) ;
  KsInitStructure*    Publication() ;
  ValidityContextType ContextValidity(const BB1BB& bb, Transfert* trans) ;
  bool                Precondition(const BB1BB& bb, Transfert* ksar) ;
	bool                ObviationCondition(const BB1BB& bb, BB1KSAR& ksar) ;
  Errcode             Action(BB1BB& bb, Transfert* trans,bool isOpportuniste) ;

 protected:

  bool             fillHistoryForValue(NSHistoryValManagementArray *pHistoryTank, string sValuePath, const NSPatPathoArray *pPT, PatPathoConstIter iterFrom, NVLdVTemps tpsDefaultDate) ;
  void             createPS(string sConcept, string sText, BB1BB& bb, Transfert* trans) ;

  double           getCockcroftForMmol(double dCreatValue, int iAgePat, double dPoidsPat, int iSexePat) ;
  double           getCockcroftForGpl(double dCreatValue, int iAgePat, double dPoidsPat, int iSexePat) ;

  double           getMdrdForMmol(double dCreatValue, int iAgePat, int iSexePat) ;
  double           getMdrdForGpl(double dCreatValue, int iAgePat, int iSexePat) ;
} ;

bool                _export init(string *pInit) ;
KsInitStructure*    _export Publication() ;
ValidityContextType _export ContextValidity(const BB1BB& bb, Transfert* trans) ;
bool                _export KSTriggerCondition(const BB1Event& event) ;
bool                _export KSPrecondition(const BB1BB& bb, Transfert* ksar) ;
bool                _export KSObviationCondition(const BB1BB& bb, BB1KSAR& ksar) ;
Errcode             _export KSAction(BB1BB& bb, Transfert* trans, bool isOpportuniste) ;

# ifdef _MAIN
#  ifndef __MAIN
  extern TModule   *pNSResModule ;
#  else
  static TModule   *pResMod ;
  TModule          *pNSResModule ;
  DetectIR         ks ;
#  endif
# else
  extern TModule*  pNSResModule ;
  extern DetectIR  ks ;
# endif


#endif  // __DETECT_IR_H__
