//---------------------------------------------------------------------------
#include <owl\applicat.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>

#include "nsdn\nsdn.h"
#include "nautilus\nssuper.h"

#include "nsdn\nsdn_dlg.h"
#include "nsdn\nsdnres.h"

//***********************************************************************//
//***********************************************************************//
DEFINE_RESPONSE_TABLE1(NSEnregProgressDlg, NSUtilDialog)
END_RESPONSE_TABLE;

NSEnregProgressDlg::NSEnregProgressDlg(TWindow* parent, NSContexte* pCtx,
															TModule* /* module */)
                   :NSUtilDialog(parent, pCtx, "NSDN_ENREG", pNSResModule)
{
	pDataProgressBar = new TGauge(this, IDC_BAR_DATA) ;
	pLocProgressBar  = new TGauge(this, IDC_BAR_LOC) ;
}

NSEnregProgressDlg::~NSEnregProgressDlg()
	delete pDataProgressBar ;
	delete pLocProgressBar ;
}

void
{
	TDialog::SetupWindow() ;

	pDataProgressBar->SetRange(0, 100) ;
  pDataProgressBar->SetStep(1) ;

  pLocProgressBar->SetRange(0, 100) ;
  pLocProgressBar->SetLed(4, 80) ;
  pLocProgressBar->SetStep(1) ;

  resetDataGauge() ;
}

void
{
	pDataProgressBar->SetValue(0) ;
}

void
{
	pLocProgressBar->SetValue(0) ;
}
