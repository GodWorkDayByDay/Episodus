//-----------------------------------------------------------------
//   NSFunction d�riv�e de TObject
//   Permet de d�finir un objet-fonction qui sera lancer par un
//   contr�le ou une bo�te de dialogue. 
//-----------------------------------------------------------------
_CLASSDEF(NSFunction);
class NSFunction : public TObject {
  // Constructeurs
  // Destructeur
  // Fonction � impl�menter
};
//-----------------------------------------------------------------
//  NSControl d�riv� de TControl
//  Il faut que l'on soit capable de lancer indiff�rement soit une
//  bo�te de dialogue ou une fonction, mais �galement modifier
//  l'�tat d'autres contr�les fr�res. 
//-----------------------------------------------------------------
__CLASSDEF(NSControl);
class NSControl : public TControl {
public :
  // Constructeurs
   NSControl(PTWindowsObject AParent, int AnId, LPSTR ATitle, int X, int
	    Y, int W, int H, PTModule ATModule = NULL)
   : TControl(AParent, AnId, ATitle, X, Y, W, H, ATModule){}
   NSControl(PTWindowsObject AParent, int ResourceId, PTModule ATModule = 
	    NULL)
   : TControl(AParent, ResourceId, ATModule) {}
  // Destructeur

  // Fonctions d'utilit� g�n�rale
  virtual WORD Transfer(int iTransferIndice, WORD TransferFlag);
  virtual void DefNotificationProc(RTMESSAGE Msg);

  // Permet � NSDialog d'acc�der � ses composants protected
  friend NSDialog;
};
