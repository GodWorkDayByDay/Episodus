// codes d'erreurs renvoy�s par les diff�rentes classes apicrypt

#ifndef __Crypto__
#define __Crypto__
#endif

#ifndef __CryptErr__
#define __CryptErr__
typedef	long TypErr;

const long kNoErr=0;		// ok
const long kFNFErr=-43;	// file not found
const long kFileClosed=-2;	// fichier ferm�

const long kCRCErr=-3;	// CRCErr lors de asciibin....
const long kPbErr=-4;	// pb lors du d�crypt....

const long kFrameTooShort=-4; // Frame too short : pendant un d�cryptage, si paquet plus petit que le minium possible !
const long KeyNotFoundErr=-5; // clef de d�cryptage not found.
const long kBadKeyHeader=-6; // header de clef corrompu !
const long kMemErr=-7; 	// pb de m�moire ou de clef en lecture seule
const long kOffsetOutOfRangeErr=-8; 	// offset clef out of range
const long kFrameTooLong=-9; // Frame too long : pendant un d�cryptage, si paquet plus long possible !
const long kAttachmentToBig=-10; 	// pi�ce jointe trop grosse pour �tre traitee !
const long kHdlNil=-11; 	// handle a decrypter = nil
const long kEncapsulationFailed=-12; 	// l'encapsulation d'une pi�ce jointe en format transport apicrypt a �chou�
const long kOtherErr=-1;	//toutes les autres erreurs
const long kNonApicryptedAttachement=-11;
const long kDEJATRANSITE=-12;//tentative de readressage d'un email crypte re�u
#endif
