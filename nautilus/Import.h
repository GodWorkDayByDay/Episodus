//---------------------------------------------------------------------------
#define ImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
#include "SHDocVw_OCX.h"

class NSImportWindow ;
//---------------------------------------------------------------------------
{

__published:	// Composants g�r�s par l'EDI
  TPanel *Panel ;

  TButton *ImpButton ;
  TButton *RefButton ;
  TButton *AnnButton ;
  TButton *CaptButton ;

  TWebBrowser *Control ;

  void __fastcall ImpButtonClick(TObject *Sender);
  void __fastcall AnnButtonClick(TObject *Sender);
	void __fastcall CaptButtonClick(TObject *Sender);
          TVariant *URL, TVariant *Frame, TVariant *StatusCode,
          TOLEBOOL *Cancel);
private:	// D�clarations de l'utilisateur
  NSImportWindow* pImport ;
  __fastcall TWebImport(TComponent* Owner);

  __fastcall ~TWebImport() ;

  void Close() ;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#endif