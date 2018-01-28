//---------------------------------------------------------------------------
#ifndef ComposH
#define ComposH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
#include "SHDocVw_OCX.h"

class NSComposView;

//---------------------------------------------------------------------------
class TWebCompos : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TPanel *Panel;
    TButton *OKButton;
    TButton *CancelButton;
    TWebBrowser *Control;
    void __fastcall OKButtonClick(TObject *Sender);
    void __fastcall CancelButtonClick(TObject *Sender);  void __fastcall NavigateErrorEvent(TObject *Sender, LPDISPATCH pDisp,
          TVariant *URL, TVariant *Frame, TVariant *StatusCode,
          TOLEBOOL *Cancel);
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    NSComposView* pView;

    __fastcall TWebCompos(TComponent* Owner);
                TWebCompos(HWND Parent, NSComposView* View): TForm(Parent)
                { pView = View; }
};
//---------------------------------------------------------------------------
extern PACKAGE TWebCompos *WebCompos;
//---------------------------------------------------------------------------
#endif
