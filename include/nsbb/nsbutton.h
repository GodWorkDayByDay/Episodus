//-----------------------------------------------------------------
// NSButn d�riv� de TButton
// Quand on appuie sur un  bouton, il faut pouvoir :
//   - lancer une fonction
//   - lancer une bo�te de dialogue
//   - d�s�lectionner ou s�lectionner d'autres boutons 
//-----------------------------------------------------------------
_CLASSDEF(NSButn);
class NSButn : public TButton {
  // Constructeurs
  static PNSButton getButton(PNSWindow pwin, int id);

  // Destructeurs

  // R�ponses au messages
  virtual void DefNotificationProc(RTMESSAGE Msg);

  // Transfert
  virtual WORD Transfer(int iTransferIndice, WORD TransferFlag);
};
//-----------------------------------------------------------------
// NSODBtutn d�riv� de NSButton et de NSOwnerDrawItem
// Owner-draw bouton
//-----------------------------------------------------------------
_CLASSDEF(NSODButn);
class NSODButn : public NSButn, public NSOwnerDrawItem {

};