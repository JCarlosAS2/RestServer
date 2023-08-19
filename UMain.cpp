//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMain.h"
//---------------------------------------------------------------------------


#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnAtivarClick(TObject *Sender)
{
  IdHTTPServer1->Active 		= false;
  IdHTTPServer1->Bindings->Clear();
  IdHTTPServer1->DefaultPort 	= sePort->Value;
  IdHTTPServer1->Active 		= true;
  sePort->Enabled 				= false;
  lblinfo->Caption      		= "Whating for request...";
  btnAtivar->Enabled    		= false;
  btnStop->Enabled      		= true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnStopClick(TObject *Sender)
{
  IdHTTPServer1->Active = false;
  lblinfo->Caption      = "WebService Stoped.";
  btnAtivar->Enabled    = true;
  btnStop->Enabled      = false;
  sePort->Enabled 	  	= true;
}

void __fastcall TForm1::LogLastRequest(TIdHTTPRequestInfo *req)
{
	memLogReq->Lines->Add(Trim(req->UserAgent + sLineBreak +
						   req->RawHTTPCommand));
}

 //---------------------------------------------------------------------------
void __fastcall TForm1::LogLastResponse(TIdHTTPResponseInfo *res)
{
	   memLogRes->Lines->Add(Trim("Status: "+
	   IntToStr(res->ResponseNo) +" ("+
						   res->ResponseText +")" + sLineBreak +
						   res->ContentText));
}

 //---------------------------------------------------------------------------
 BOOL __fastcall TForm1::CheckAuthentication(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res)
{
const
 String user = "user";
 String pass = "pass";


 BOOL Result = (req->AuthUsername == user) && (req->AuthPassword == pass);

  if (!Result)
  {
	res->ResponseNo = 401;
	LogLastRequest(req);
	LogLastResponse(res);
	 memLogRes->Lines->Add("Authentication Error. User: " + req->AuthUsername);
	res->AuthRealm = res->ResponseText;

  }
   else memLogRes->Lines->Add("Authentication OK. User: " + req->AuthUsername);
  return (Result) ;

}

//---------------------------------------------------------------------------


void __fastcall TForm1::GetClientes(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res)
{

int i, id;
String ret, error, param1, stTmp1, stTmp2; 
//System::UnicodeString param1;

std::auto_ptr<TStringList> st(new TStringList());

String equalChar= "=";
String moreChar="<" ;
String lessChar=">" ;





		  if (req->Params->Count > 0)
		  { String OperSig;
			int Counter = req->Params[0].Count;
			for (i = 0; i< Counter; i++)
			{
			  param1 = req->Params[0].Strings[i];
			  stTmp1 = GetValueBefore(param1, equalChar);
			  stTmp2 = GetValueAfter(param1, equalChar);
			  OperSig = equalChar;

			  if (stTmp1.IsEmpty()) {
				stTmp1 = GetValueBefore(param1, moreChar);
				stTmp2 = GetValueAfter(param1, moreChar);
				OperSig = moreChar;
			  }

			  if (stTmp1.IsEmpty()) {
				stTmp1 = GetValueBefore(param1, lessChar);
				stTmp2 = GetValueAfter(param1, lessChar);
				OperSig = lessChar;
			  }
			  if (i == 0)
				st->Add(Format(" %s %s %s", (String) stTmp1, OperSig, QuotedStr(stTmp2)));
			  else
				st->Add(Format(" and %s %s %s", (String) stTmp1, OperSig, QuotedStr(stTmp2)));
			}
		  }
		  else
		   if (req->URI != "/")
			{
			String 	slashChar = "/";

			if (TryStrToInt(GetValueAfter(req->URI, slashChar), id))

			  st->Add(Format(" id = %d", id));

			}

		  ret = Contact->FindContact(st->Text, error);

	  if (error == EmptyStr)
	   {
		res->ContentText = ret;
		res->ResponseNo  = 200;
	   }
	   else {
			 res->ContentText = error ;
			 res->ResponseNo  = 500;
			}


}

 //---------------------------------------------------------------------------

void __fastcall TForm1::InsertCliente(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res)
 {

  TStringStream * st = new TStringStream( EmptyStr);

  TJSONValue * jsValue;
  TEncoding *LEncoding = NULL;
  String Error;

  st->CopyFrom( req->PostStream, req->PostStream->Size );
  String strTmp=  st->DataString;

  TEncoding* encoding = TEncoding::ASCII;
  TBytes bytes = encoding->GetBytes(strTmp);


  jsValue =  TJSONObject::ParseJSONValue(bytes, 0 );
  strTmp =jsValue->ToString() ;

  TJSONObject * jsObj =  dynamic_cast<TJSONObject*>(jsValue) ;

  strTmp =jsValue->ToString() ;

  Contact->ID			= StrToIntDef( GetJsonValue( jsObj, "ID" ),0);
  Contact->Age			= StrToIntDef( GetJsonValue( jsObj, "Age" ),0);

  Contact->UID 			= GetJsonValue( jsObj, "UID" );
  Contact->FirstName 	= GetJsonValue( jsObj, "FirstName" );
  Contact->SecondName 	= GetJsonValue( jsObj, "SecondName" );
  Contact->PhoneNumbers = GetJsonValue( jsObj, "PhoneNumbers" );
  Contact->Addr			= GetJsonValue( jsObj, "Addr" );
  Contact->Photo 		= GetJsonValue( jsObj, "Photo" );
  Contact->DateBirth 	= GetJsonValue( jsObj, "DateBirth" );

  if ( Contact->InsertContact(Error ) )
  {

	res->ContentText = jsObj->ToJSON();
	res->ResponseNo = 201;
  }
  else
  {
	res->ContentText = Error;
	res->ResponseNo = 500;
  }

}

 //---------------------------------------------------------------------------
void __fastcall TForm1::UpdateCliente(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res)
{

  int id;
  String Error;
  String slash ="/";
   TStringStream * st = new TStringStream( EmptyStr);

  TJSONValue * jsValue;
  TEncoding *LEncoding = NULL;


  st->CopyFrom( req->PostStream, req->PostStream->Size );
  String strTmp=  st->DataString;

  TEncoding* encoding = TEncoding::ASCII;
  TBytes bytes = encoding->GetBytes(strTmp);


  jsValue =  TJSONObject::ParseJSONValue(bytes, 0 );
  strTmp =jsValue->ToString() ;

  TJSONObject * jsObj =  dynamic_cast<TJSONObject*>(jsValue) ;

  strTmp =jsValue->ToString() ;


  if (req->URI !=slash)
	if (TryStrToInt(GetValueAfter(req->URI, slash), id) )
	{

  Contact->ID			= id; //StrToIntDef( GetJsonValue( jsObj, "ID" ),0);
  Contact->Age			= StrToIntDef( GetJsonValue( jsObj, "Age" ),0);

  Contact->UID 			= GetJsonValue( jsObj, "UID" );
  Contact->FirstName 	= GetJsonValue( jsObj, "FirstName" );
  Contact->SecondName 	= GetJsonValue( jsObj, "SecondName" );
  Contact->PhoneNumbers = GetJsonValue( jsObj, "PhoneNumbers" );
  Contact->Addr			= GetJsonValue( jsObj, "Addr" );
  Contact->Photo 		= GetJsonValue( jsObj, "Photo" );
  Contact->DateBirth 	= GetJsonValue( jsObj, "DateBirth" );


  if (Contact->UpdateContact(Error))
	  {
		res->ResponseNo  = 200;
	  }
	  else
	  {
		res->ContentText = Error;
		res->ResponseNo  = 500;
	  }

	  st->Free();
	  jsObj->Free();
	}
    else
	{
	  res->ResponseNo  = 403;
	  res->ContentText = res->ResponseText;
	}
  }

 //---------------------------------------------------------------------------

 void __fastcall TForm1::DeleteCliente(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res)
  {

  int id;
  String Error;
  String slash ="/";

  if (req->URI !=slash)
	if (TryStrToInt(GetValueAfter(req->URI, slash), id) )
	{
	  Contact->ID = id;
	  if (Contact->DeleteContact(Error))
		res->ResponseNo = 204;
	  else
	  {
		res->ContentText = Error;
		res->ResponseNo  = 500;
	  };
	}
	else
	{
	  res->ResponseNo  = 403;
	  res->ContentText = res->ResponseText;
	};
  }


 //---------------------------------------------------------------------------

void __fastcall TForm1::IdHTTPServer1CommandGet(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo)
{
 if (CheckAuthentication(ARequestInfo, AResponseInfo))

	if (ARequestInfo->CommandType==hcGET || ARequestInfo->CommandType == hcPOST)
	{
	  LogLastRequest(ARequestInfo);

	 switch (ARequestInfo->CommandType) {
		 case hcGET: GetClientes(ARequestInfo, AResponseInfo);
			  break;

		 case hcPOST: InsertCliente(ARequestInfo, AResponseInfo);
			 break;
		 ;
	 }

	}

 LogLastResponse(AResponseInfo);
 AResponseInfo->WriteContent();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 Contact = new TContact();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IdHTTPServer1CommandOther(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo)
{
   if (CheckAuthentication(ARequestInfo, AResponseInfo))

	if (ARequestInfo->CommandType==hcPUT || ARequestInfo->CommandType == hcDELETE)
	{
	  LogLastRequest(ARequestInfo);

	 switch (ARequestInfo->CommandType) {
		 case hcPUT: UpdateCliente(ARequestInfo, AResponseInfo);
			  break;

		 case hcDELETE: DeleteCliente(ARequestInfo, AResponseInfo);
			 break;
		 ;
	 }

	}

}
//---------------------------------------------------------------------------

