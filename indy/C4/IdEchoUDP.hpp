// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdEchoUDP.pas' rev: 4.00

#ifndef IdEchoUDPHPP
#define IdEchoUDPHPP

#pragma delphiheader begin
#pragma option push -w-
#include <IdComponent.hpp>	// Pascal unit
#include <IdUDPClient.hpp>	// Pascal unit
#include <IdUDPBase.hpp>	// Pascal unit
#include <IdAssignedNumbers.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Idechoudp
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TIdEchoUDP;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TIdEchoUDP : public Idudpclient::TIdUDPClient 
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	unsigned FEchoTime;
	
public:
	__fastcall virtual TIdEchoUDP(Classes::TComponent* AOwner);
	AnsiString __fastcall Echo(AnsiString AText);
	__property unsigned EchoTime = {read=FEchoTime, nodefault};
	
__published:
	__property Port ;
public:
	#pragma option push -w-inl
	/* TIdUDPBase.Destroy */ inline __fastcall virtual ~TIdEchoUDP(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------

}	/* namespace Idechoudp */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Idechoudp;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdEchoUDP
