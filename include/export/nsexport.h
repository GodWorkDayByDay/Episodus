#ifndef __NSEXPORT_H
bool _export exporter(NSContexte far *pCtx, NSCRDocument far *pCRDoc, string far *psExportedFile, NSDocStatus far *pDocStatus) ;
string donneNumSejour(NSContexte* pCtx, string sDocument);
string creeFichier(NSContexte* pCtx, string sFichier);
string creeFichierTxt(NSContexte* pCtx, string sFichier, string sPrefixe, string sSuffixe = ".txt");

#endif
