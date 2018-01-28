// nsvisual.cpp : Objet de visualisation des fichiers html statiques - RS Fevrier 1998
////////////////////////////////////////////////////////////////////////////////////////

#define __NSVISUAL_CPP

#include "nautilus\nsvisual.h"
#include "nautilus\ns_html.h"
#include "nautilus\nssuper.h"
#include "partage\nsdivfct.h"
#include "nautilus\nautilus.rh"
#include <string.h>
#include <winsys\geometry.h>

const TString progIdIE = "Shell.Explorer"; // Controle OCX (Version independant progid)
GUID  guidIE = CLSID_NULL;
const TString progIdAppIE = "InternetExplorer.Application.1";
GUID  guidAppIE = CLSID_NULL;

NSVisualDocument::NSVisualDocument(TDocument* parent, NSDocumentInfo* pDocumentInfo,
      										NSDocumentInfo* pDocHtmlInfo, NSSuper* pSup) :
	TOleDocument(parent)
{
	pDocRef = new NSRefDocument(parent,pDocumentInfo,pDocHtmlInfo,pSup);
   SetOcDoc(new TOcDocument(*GetOcApp()));
}

NSVisualDocument::NSVisualDocument(TDocument* parent, NSSuper* pSup) :
	TOleDocument(parent)
{
	pDocRef = new NSRefDocument(parent,pSup);
   SetOcDoc(new TOcDocument(*GetOcApp()));
}

NSVisualDocument::~NSVisualDocument()
{
	delete pDocRef;
}

// Table de r�ponses de la classe NSVisualView
////////////////////////////////////////////////////////////////
DEFINE_RESPONSE_TABLE1(NSVisualView, TOleView)
  EV_WM_CLOSE,
  // EV_WM_SIZE,
  EV_COMMAND(CM_IMPRIME, CmPublier),
END_RESPONSE_TABLE;

// Constructeur NSVisualView
////////////////////////////////////////////////////////////////
NSVisualView::NSVisualView(NSVisualDocument& doc, TWindow *parent) :
	TOleView(doc,parent),pDoc(&doc)
{
	// n�c�ssaire pour Ole
	SetViewMenu(new TMenuDescr(IDM_MDICMNDS));

	if (pDoc->pDocRef->sTemplate != "")	// le document a une template associ�e
   {
   	// on r�cup�re l'url du serveur nautilus
   	sUrl = pDoc->pDocRef->pSuper->PathName("USRV");
      // on g�n�re le fichier � visualiser
   	GenereHtml();
   }
   else
   {
   	// l'url est contenue dans le champ fichier du document
   	sUrl = "";
      sHtml = string(pDoc->pDocRef->pDocInfo->pDonnees->fichier);
   }
}

// Destructeur NSVisualView
////////////////////////////////////////////////////////////////
NSVisualView::~NSVisualView()
{
	// destruction des fichiers temporaires de visualisation
   if (sUrl != "") // si un fichier a �t� g�n�r�
   {
   	NSBaseImages* pBase;
      string sFichVisual;

   	// destruction de la base d'images (cad des fichiers temporaires)
   	if (pDoc->pDocRef->sBaseImages != "")		// si la base a �t� initialis�e
   	{
   		pBase = new NSBaseImages(pDoc->pDocRef->sBaseImages,pDoc->pDocRef->pSuper->PathName("SIMG"));
      	pBase->lire();
      	pBase->detruire();
      	delete pBase;
   	}

		// destruction du fichier de visualisation
      sFichVisual = pDoc->pDocRef->pSuper->PathName("SHTM") + sHtml;

   	if (!DeleteFile(sFichVisual.c_str()))
   		erreur("Pb de destruction du fichier temporaire de visualisation",0,0);
   }

   // unbind du browser
	if (Control.IsBound())
   {
   	// Control.Quit();
   	Control.Unbind(false);
   }
}

// GetWindow renvoie this
////////////////////////////////////////////////////////////////
TWindow*
NSVisualView::GetWindow()
{
   return (TWindow*) this;
}

// Fonction SetupWindow
////////////////////////////////////////////////////////////////
void
NSVisualView::SetupWindow()
{
	TRect* pos;
   TOcPart* part;
	TRect rectClient;

	TOleWindow::SetupWindow();

   pos = new TRect(0,0,0,0);

   // on ins�re le controle ocx internet explorer
   Ocx = InsertControl(progIdIE,pos);
   delete pos;

   // on r�cup�re les coordonn�es de la zone client de la TMDIChild
   rectClient = Parent->GetClientRect();

	Control.Bind(Ocx->GetCtlDispatch());

   // on navigue vers le fichier html � visualiser
   Navigate();

   if (sHtml != "")
   	TWindow::SetDocTitle(pDoc->pDocRef->GetTitle(),0);
   else
   	TWindow::SetDocTitle("Erreur",0);

   // on r�ajuste la taille du controle
   SetSizeOcx(rectClient.Size());

   TOcPartCollectionIter i(GetOcDoc()->GetParts());
   part = i.Current();
}

// Fonction SetSizeOcx(TSize newSize)
////////////////////////////////////////////////////////////////
void
NSVisualView::SetSizeOcx(TSize newSize)
{
	TRect newRect;
   TSize* pSize;

	Ocx->SetSize(newSize);
   newRect = TRect(Ocx->GetPos(),newSize); // !! GetSize() renvoie la taille de BPartI
   EvOcViewGetSiteRect(&newRect);
   pSize = new TSize(newRect.Size());

   // On met � jour l'�l�ment d'interface
   Ocx->GetBPartI()->SetPartPos(&newRect);
   Ocx->GetBPartI()->SetPartSize(pSize);
   delete pSize;

   SetSelection(Ocx);
}

// Fonction Navigate
////////////////////////////////////////////////////////////////
void
NSVisualView::Navigate()
{
	TAutoVal flags(0), target(0), data(0), headers(0);
   TAutoString URL;

   URL = (TAutoString) (sUrl + sHtml);
   Control.Navigate(URL,&flags,&target,&data,&headers);
}

// Fonction GenereHtml
////////////////////////////////////////////////////////////////
bool
NSVisualView::GenereHtml()
{
	string codeDoc;
   string sServeurHtml, sUniteHtml;
   string sPathHtml = pDoc->pDocRef->pSuper->PathName("SHTM", &sUniteHtml, &sServeurHtml);

   // on r�cup�re le code du document � visualiser
   codeDoc = string(pDoc->pDocRef->pDocInfo->pDonnees->codePatient) + string(pDoc->pDocRef->pDocInfo->pDonnees->codeDocument);

   NSModHtml html(pDoc->pDocRef,pDoc->pDocRef->pSuper);

   // on trouve le nom du fichier temporaire � visualiser
   sHtml = html.nomSansDoublons(sServeurHtml,sUniteHtml,sPathHtml,codeDoc,"htm");
   sPathHtml += sHtml;

   // generation du fichier html (dans le repertoire du serveur)
   // on fournit ici le pDocInfo car le document brut est un html statique
   if (!html.genereHtml(pDoc->pDocRef->sTemplate,sPathHtml,pDoc->pDocRef->sBaseImages,pDoc->pDocRef->pDocInfo))
   {
   	erreur("Impossible de g�n�rer le fichier html � visualiser",0,0);
      sHtml = "";
   	return false;
   }

   return true;
}

// Fonction de r�ponse � la commande Imprimer (publier)
////////////////////////////////////////////////////////////////
void
NSVisualView::CmPublier()
{
	pDoc->pDocRef->Publier();
}

// fin de nsvisual.cpp
/////////////////////////////////////////////////////////////////

