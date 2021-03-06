#include "nautilus\nsdochis.h"#include "nautilus\nssuper.h"#include "nsdn\nsdocnoy.h"#include "nsbb\nsbbtran.h"#include "nsbb\nspatpat.h"
//---------------------------------------------------------------------------//  Fonction:		NSDocumentHisto::NSDocumentHisto(NSContexte* pCtx)
//  Description:	Constructeur avec contexte (pour l'acc�s � la base des chemins)
//  Retour:			Rien
//---------------------------------------------------------------------------
NSDocumentHisto::NSDocumentHisto(NSContexte* pCtx) : NSDocumentInfo(pCtx)
{
	// Cr�e l'objet de donn�es
	pDocNoy = 0 ;
	pPatPathoArray = new NSPatPathoArray(pContexte->getSuperviseur()) ;
	strcpy(dateDoc, "") ;
}

NSDocumentHisto::NSDocumentHisto(NSDocumentInfo* pNSDocument, bool bNoDocnoy)
                :NSDocumentInfo(*pNSDocument)
{
	// Cr�e l'objet de donn�es
	pDocNoy = 0 ;
	pPatPathoArray = new NSPatPathoArray(pContexte->getSuperviseur()) ;
	strcpy(dateDoc, "") ;
}

//-----------------------------------------------------------------------------------//  Fonction:		NSDocumentHisto::NSDocumentHisto(NSDocumentInfo* pNSDocumentInfo)
//  Description:	Constructeur avec documentInfo (sans pHtmlInfo) et pDocNoy
//  Retour:			Rien
//-----------------------------------------------------------------------------------
NSDocumentHisto::NSDocumentHisto(NSDocumentInfo* pNSDocumentInfo, NSNoyauDocument* pDoc)
                :NSDocumentInfo(*pNSDocumentInfo)
{
	// Cr�e l'objet de donn�es
	pDocNoy = pDoc ;
	pPatPathoArray = new NSPatPathoArray(pContexte->getSuperviseur()) ;
	strcpy(dateDoc, "") ;
}

//---------------------------------------------------------------------------//  Function:		NSDocumentHisto::~NSDocumentHisto()
//  Description:	Constructeur.
//  Retour:			Aucun
//---------------------------------------------------------------------------
NSDocumentHisto::~NSDocumentHisto()
{
	// surtout ne pas deleter le pDocNoy car ce pointeur est d�truit
	// par la derni�re vue associ�e (mod�le document / vue)
	if (NULL != pPatPathoArray)
		delete pPatPathoArray ;
}

//---------------------------------------------------------------------------
//  Fonction:		NSDocumentHisto::NSDocumentHisto(NSDocumentHisto& rv)
//  Description:	Constructeur copie
//  Retour:			Rien
//---------------------------------------------------------------------------
NSDocumentHisto::NSDocumentHisto(NSDocumentHisto& rv)
                :NSDocumentInfo(rv.pContexte)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDocNoy = rv.pDocNoy ;
	pPatPathoArray = new NSPatPathoArray(pContexte->getSuperviseur()) ;
	*pDonnees = *(rv.pDonnees) ;
	// strcpy(dateDoc, rv.dateDoc);
	strcpy(dateDoc, "") ;    // pour forcer la relecture de la date dans la PatPatho
	//
	// Copie les valeurs du NSDocumentHisto d'origine
	//
	*pPatPathoArray = *(rv.pPatPathoArray) ;
}

NSDocumentHisto&
NSDocumentHisto::operator=(NSDocumentHisto src)
{
	if (this == &src)
		return *this ;

	pDocNoy = src.pDocNoy ;
	*pDonnees = *(src.pDonnees) ;

	// strcpy(dateDoc, rv.dateDoc);
	strcpy(dateDoc, "") ;    // pour forcer la relecture de la date dans la PatPatho
	//
	// Copie les valeurs du NSDocumentHisto d'origine
	//
  if (NULL != pPatPathoArray)
  	delete pPatPathoArray ;
  pPatPathoArray = new NSPatPathoArray(pContexte->getSuperviseur()) ;
	*pPatPathoArray = *(src.pPatPathoArray) ;

	return *this ;
}

//---------------------------------------------------------------------------//  Description:	Op�rateur de comparaison
//  Retour:			0 ou 1
//---------------------------------------------------------------------------
int NSDocumentHisto::operator == ( const NSDocumentHisto& o )
{
	return ((*pPatPathoArray == *(o.pPatPathoArray)) &&
	        (*pDonnees == *(o.pDonnees))) ;
}

//---------------------------------------------------------------------------//  Description:	R�cup�ration de la date du document
//					date de cr�ation ou date patpatho si non vide
//  Retour:			La date au format AAAAMMJJ (char*)
//---------------------------------------------------------------------------
char*
NSDocumentHisto::GetDateDoc()
{
	string sDate = "" ;

	// si la date n'est pas initialis�e on cherche d'abord dans la patpatho	if (!strcmp(dateDoc, ""))
		TrouveDateDoc() ;

	return dateDoc ;
}

//---------------------------------------------------------------------------
//  Description:	R�cup�ration de la date du document
//					date de cr�ation ou date patpatho si non vide
//  		        stockage au format AAAAMMJJ dans dateDoc
//---------------------------------------------------------------------------
void
NSDocumentHisto::TrouveDateDoc()
{
	string sDate = "";

	// on cherche d'abord dans la patpatho	if (false == pPatPathoArray->empty())
	{
  	// First, check if first element is a KCHIR
    //
  	PatPathoIter iterPpt = pPatPathoArray->begin() ;
    iterPpt++ ;
    if (iterPpt != pPatPathoArray->end())
    	if ((*iterPpt)->getLexiqueSens(pContexte->getSuperviseur()) == "KCHIR")
      	pPatPathoArray->CheminDansPatpatho(0, "KCHIR", &sDate) ;

    if (sDate == "")
			pPatPathoArray->CheminDansPatpatho(0, "LADMI/KCHIR", &sDate) ;
	}

	if (sDate != "")		strcpy(dateDoc, sDate.c_str()) ;

	// S'il n'y a pas de date dans la patpatho, on prend la date de cr�ation	// du document
	else
		strcpy(dateDoc, pDonnees->sDateCreation.c_str()) ;
}

//---------------------------------------------------------------------------//  Description:	Remet � vide la date du document
//---------------------------------------------------------------------------
void
NSDocumentHisto::ResetDateDoc()
{
	dateDoc[0] = '\0';
}

bool
NSDocumentHisto::checkPptConsistency()
{
	if (NULL == pPatPathoArray)
		return false ;

	if (true == pPatPathoArray->empty())
		return true ;

  string sLang = "" ;
  if (pContexte->getUtilisateur())
  	sLang = pContexte->getUtilisateur()->donneLang() ;

	// Check if there is a line 0 column 0 node
  //
  PatPathoIter rootIt = pPatPathoArray->ChercherItem(0, 0) ;
  if ((NULL == rootIt) || (pPatPathoArray->end() == rootIt))
  {
  	// Error message
    //
  	string sErrorText = getDocTitleWithDate() + string(" -> ") ;
  	sErrorText += pContexte->getSuperviseur()->getText("documentManagementErrors", "thisDocumentHasNoRootNode") ;
    pContexte->getSuperviseur()->trace(&sErrorText, 1, NSSuper::trError) ;
		erreur(sErrorText.c_str(), standardError, 0) ;

    // Automatic fixing proposal
    //
    if (string("") != getContent())
    {
    	string sCaption = pContexte->getSuperviseur()->getAppName().c_str() ;
    	string sMesgText = pContexte->getSuperviseur()->getText("generalLanguage", "tryAnAutomaticFixing?") ;
    	int retVal = ::MessageBox(pContexte->GetMainWindow()->HWindow, sMesgText.c_str(), sCaption.c_str(), MB_YESNO) ;
    	if (retVal != IDYES)
    	{
    		sErrorText = string("No automatic fixing") ;
    		pContexte->getSuperviseur()->trace(&sErrorText, 1, NSSuper::trError) ;
      	return false ;
    	}

    	sErrorText = string("Automatic fixing") ;
    	pContexte->getSuperviseur()->trace(&sErrorText, 1, NSSuper::trError) ;

      NSPatPathoArray PatPatho(pContexte->getSuperviseur()) ;
			PatPatho.ajoutePatho(getContent(), 0) ;

      // We don't do this, because we suppose that other nodes already have
      // the proper line and column
			// PatPatho.InserePatPathoFille(PatPatho.begin(), pPatPathoArray) ;

      PatPathoIter it = pPatPathoArray->begin() ;
      for ( ; pPatPathoArray->end() != it ; it++)
      	PatPatho.push_back(new NSPatPathoInfo(**it)) ;

      *pPatPathoArray = PatPatho ;

      // Can't do this because it starts an infinite loop (this constructor
      // will look into the history to find the pPT
      // NSNoyauDocument noyauDoc(0, (NSDocumentInfo*)this, 0, pContexte, false) ;

      NSNoyauDocument noyauDoc((TDocument*) 0, pContexte, true) ;
      noyauDoc.pDocInfo = new NSDocumentInfo(*((NSDocumentInfo*)this)) ;
      *(noyauDoc.pPatPathoArray) = *pPatPathoArray ;
      noyauDoc.bDocumentValide   = true ;
      noyauDoc.setReadOnly(false) ;

      // Before saving the document, we have to check that traits are in the ppt
      //
      it = noyauDoc.pPatPathoArray->begin() ;
      string sRoot = (*it)->getLexiqueSens(pContexte->getSuperviseur()) ;
      if (string("ZADMI") == sRoot)
      {
      	// Sometimes this information disappears and let "holes" in lines
        // numbers... it is better not to make any correction to lines
        // numbers because it could also come from hidden nodes

      	// Familly Name
        //
        Message Msg ;
        Msg.SetLexique(string("�CL000")) ;
        Msg.SetTexteLibre(pContexte->getPatient()->getNom()) ;
      	noyauDoc.pPatPathoArray->AjouterChemin(string("ZADMI1/LIDET1/LNOM01"), &Msg, false /* bEcraser */) ;

        // First Name
        //
        Msg.Reset() ;
        Msg.SetLexique(string("�CL000")) ;
        Msg.SetTexteLibre(pContexte->getPatient()->getPrenom()) ;
      	noyauDoc.pPatPathoArray->AjouterChemin(string("ZADMI1/LIDET1/LNOM21"), &Msg, false /* bEcraser */) ;

        // Birthdate
        //
        Msg.Reset() ;
        Msg.SetLexique(string("�D0;10")) ;
        Msg.SetUnit("2DA011") ;
        Msg.SetComplement(pContexte->getPatient()->getNaissance()) ;
      	noyauDoc.pPatPathoArray->AjouterChemin(string("ZADMI1/LIDET1/KNAIS1"), &Msg, false /* bEcraser */) ;

        // Gender
        //
        Msg.Reset() ;
        Msg.SetLexique(pContexte->getPatient()->getSexe()) ;
      	noyauDoc.pPatPathoArray->AjouterChemin(string("ZADMI1/LIDET1/LSEXE1"), &Msg, false /* bEcraser */) ;
      }

      bool bSaved = noyauDoc.enregistrePatPatho() ;

      if (true == bSaved)
      	*pPatPathoArray = *(noyauDoc.pPatPathoArray) ;

      return bSaved ;
    }
  }
  return true ;
}

//***************************************************************************// 					Impl�mentation des m�thodes NSDocHistoArray
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur copie
//---------------------------------------------------------------------------
NSDocHistoArray::NSDocHistoArray(NSDocHistoArray& rv)
					 :NSDocumentHistoArray()
{
	if (empty())
		return ;

	for (DocumentIter i = rv.begin(); i != rv.end(); i++)
		push_back(new NSDocumentHisto(*(*i))) ;
}

//---------------------------------------------------------------------------//  Destructeur
//---------------------------------------------------------------------------
void
NSDocHistoArray::vider()
{
	if (empty())
		return ;

	for (DocumentIter i = begin(); i != end(); )	{
		delete *i ;
		erase(i) ;
	}
}

NSDocHistoArray::~NSDocHistoArray(){
	vider() ;
}

