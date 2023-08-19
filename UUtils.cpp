//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <UUtils.h>

String __fastcall GenerateUUID()
{
 TGUID myGuid;
 CreateGUID(myGuid);
 String Result =  Sysutils::GUIDToString(myGuid);
 return(Result);

}


String __fastcall GetJsonValue(TJSONObject  * aJsonObj, String aKey)
{

 TJSONValue * jsValue;

  String Result = "";

  jsValue = aJsonObj->GetValue( aKey );
  if (( jsValue != NULL ) )
	Result = jsValue->Value();
  return Result;
}



 String __fastcall GetValueBefore(String & aStrSrc, String &aSearch)
 {
 int Position, NumCharacterToCopy;
  Position = aStrSrc.Pos(aSearch) -1;
  String Result="";
  if (Position >0) {
	 Result = aStrSrc.SubString(1,Position);
  }
  return(Result);
 }

String __fastcall GetValueAfter(String &aStr, String &aSearch)
{
  int Position, NumCharacterToCopy;
  Position = aStr.Pos(aSearch);
  NumCharacterToCopy = aStr.Length() - Position;

  String Result="";
  if (Position >0) {
	 Result =  aStr.SubString(Position +1, NumCharacterToCopy );
  }
  return(Result);

}


