//---------------------------------------------------------------------------

#ifndef UUtilsH
#define UUtilsH
//---------------------------------------------------------------------------
 #include <IdHTTPServer.hpp>
 #include <System.hpp>
 #include <string.h>
 #include <vector>
 #include <Data.DB.hpp>
  #include <FireDAC.Comp.Client.hpp>
 #include <FireDAC.Comp.DataSet.hpp>
 //#include <REST.Response.Adapter.hpp>
#include <System.JSON.hpp>
String __fastcall GenerateUUID();


BOOL __fastcall CheckAuthentication(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res);

String __fastcall GetValueBefore(String  &aStr, String &aSearch);
String __fastcall GetValueAfter(String &aStr, String &aSearch);

String __fastcall GetJsonValue(TJSONObject * aJsonObj, String aKey);


#endif
