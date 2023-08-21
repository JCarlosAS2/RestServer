//---------------------------------------------------------------------------

#pragma hdrstop

#include "UContact.h"
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

////--------------------Sets-------------------------------------------------------



void __fastcall TContact::SetUID( const String Value )
{
  FUID = Value;
}

void __fastcall TContact::SetID( const int Value )
{
  FID = Value;
}

void __fastcall TContact::SetAge( const int Value )
{
  FAge = Value;
}

void __fastcall TContact::SetAddr( const String Value )
{
  FAddr = Value;
}


void __fastcall TContact::SetSecondName( const String Value )
{
  FSecondName = Value;
}

void __fastcall TContact::SetFirstName( const String Value )
{
  FFirstName = Value;
}


void __fastcall TContact::SetPhoto( const String Value )
{
  FPhoto = Value;
}



void __fastcall TContact::SetDateBirth( const String Value )
{
  FDateBirth = Value;
}


void __fastcall TContact::SetPhoneNumbers( const String Value )
{
  FPhoneNumbers = Value;
}


String __fastcall TContact::FindContact(String pWhere, String & Error )
{
 String Result;
 DM->FDQueryContact->Close();

 try {
   String sSqlCmd = "SELECT  UID, ID, FirstName, SecondName, Addr, DateBirth, PhoneNumbers, Photo, CAST((julianday('now') - julianday(DateBirth)) / 365.25 AS INTEGER) AS Age   FROM   personal ";
   DM->FDQueryContact->SQL->Text = sSqlCmd;

   if (Trim(pWhere).Length() > 0 ) {
	DM->FDQueryContact->Filter = pWhere;// DM->FDQueryContact->SQL->Add(" Where " + pWhere);
    DM->FDQueryContact->Filtered = true;
   }

   //Error = DM->FDQueryContact->SQL->Text;
   DM->FDQueryContact->SQL->SaveToFile("E:\\SQL.txt")  ;
   DM->FDQueryContact->Open();
   TJSONObject * JObj   = new TJSONObject();
   TJSONArray  * JArray = new TJSONArray();
   int  i;

   BOOL Act    = DM->FDQueryContact->Active;
   BOOL Empty  = DM->FDQueryContact->IsEmpty();
   int RowCont = DM->FDQueryContact->RecordCount;

   try
	{
	  TField * TFDS;
	  TJSONBool * JSONBool;
	  TJSONNumber * JSONNumber;
	  TJSONString * JSONString;

	  int iNumero, tmp;
	  float fNumero;
	  double dNumero;
	  String sFieldName, sValue;

	  DM->FDQueryContact->DisableControls();
	  DM->FDQueryContact->First();
	  //tmp = DM->FDQueryContact->RecordCount;
	  while (!DM->FDQueryContact->Eof)
	  {
	   for (i = 0; i< DM->FDQueryContact->FieldCount; i++)
	   {
		TFDS  = new TField(NULL);
		TFDS =  DM->FDQueryContact->Fields[0][i];
		sFieldName = DM->FDQueryContact->Fields[0][i]->FieldName;

		switch (TFDS->DataType) {
		  case ftBoolean:
			   JSONBool = new TJSONBool(TFDS->AsBoolean);
			   JObj->AddPair(sFieldName,	 JSONBool);
		  break;

		  case ftFloat:
		  case ftCurrency:
		  case ftBCD:
		  case ftFMTBcd:
			   dNumero = DM->FDQueryContact->FieldByName(sFieldName)->AsExtended;
			   JSONNumber = new TJSONNumber(fNumero);
			   JObj->AddPair(sFieldName, JSONNumber);
			  // delete JSONNumber;
		 break;

		 case ftAutoInc:
		 case ftSmallint:
		 case ftInteger:
		 case ftWord:
		 case ftLongWord:
		 case ftShortint:
			  iNumero = DM->FDQueryContact->FieldByName(sFieldName)->AsInteger;
			  JSONNumber = new TJSONNumber(iNumero);
			  JObj->AddPair(sFieldName, JSONNumber);
			  //delete JSONNumber;
		  break;

	   default:
			  sValue = DM->FDQueryContact->FieldByName(sFieldName)->AsString;
			  JSONString = new TJSONString(sValue);
			  JObj->AddPair(sFieldName, JSONString);
			 // delete JSONString;
	   }
	  }

	 DM->FDQueryContact->Next();
	}

   JArray->AddElement(JObj);
   Result = JArray->ToString();
  }
  __finally
  {
	DM->FDQueryContact->EnableControls();
	delete JObj;
   //	delete JArray;
   //	JArray->Free();
  }

  } catch(const Exception& E) {
  Error += Format(" Error finding Contact(s): %s", E.Message) ;
  }
 return (Result);
 }

 //--------------------------------------------------------------------
 bool __fastcall TContact::InsertContact( String & Error )
{
  bool result = false;
  result = false;
  Error = "";

  String stmp="1";
  FUID =GenerateUUID ();
  try
  { // personal.UID, personal.ID, personal.FirstName, personal.SecondName, personal.Addr,  personal.DateBirth,  personal.PhoneNumbers,
	DM->FDQueryContact->Close();
	DM->FDQueryContact->SQL->Clear();

	DM->FDQueryContact->SQL->Add( "insert into personal( " );
	DM->FDQueryContact->SQL->Add( "  UID, " );
	DM->FDQueryContact->SQL->Add( "  ID, " );
	DM->FDQueryContact->SQL->Add( "  FirstName, " );
	DM->FDQueryContact->SQL->Add( "  SecondName, " );
	DM->FDQueryContact->SQL->Add( "  PhoneNumbers, " );
	DM->FDQueryContact->SQL->Add( "  Addr, " );
	DM->FDQueryContact->SQL->Add( "  DateBirth, " );

	DM->FDQueryContact->SQL->Add( "  Photo )" );
	DM->FDQueryContact->SQL->Add( "values( " );

	DM->FDQueryContact->SQL->Add( Format( "%s, ", ARRAYOFCONST(( QuotedStr( FUID ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "%s, ", ARRAYOFCONST(( IntToStr( FID ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "%s, ", ARRAYOFCONST(( QuotedStr( FFirstName ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "%s, ", ARRAYOFCONST(( QuotedStr( FSecondName ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "%s, ", ARRAYOFCONST(( QuotedStr( FPhoneNumbers ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "%s, ", ARRAYOFCONST(( QuotedStr( FAddr ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "%s, ", ARRAYOFCONST(( QuotedStr( FDateBirth ) )) ) );

	DM->FDQueryContact->SQL->Add( Format( "%s) ", ARRAYOFCONST(( QuotedStr( FPhoto ) )) ) );

	stmp = DM->FDQueryContact->SQL->Text;
	// DM->FDQueryContact->SQL->SaveToFile("E:\\SQL.txt")  ;
	DM->FDQueryContact->ExecSQL();
	result = DM->FDQueryContact->RowsAffected > 0;
    if ( ! result )
	  Error = "Contact was not inserted. Try again Later.";
  }
  catch( Exception & E )
  {
	Error = Format( "Error to try insert Contact: %s",  E.Message  );
  }
  return result;
}


bool __fastcall TContact::UpdateContact( String& Error )
{
  bool result = false;
  result = false;
  Error = "";
  try
  {
	DM->FDQueryContact->Close();
	DM->FDQueryContact->SQL->Clear();
	DM->FDQueryContact->SQL->Add( "update personal set " );

	DM->FDQueryContact->SQL->Add( Format( "  FirstName = %s, ", ARRAYOFCONST(( QuotedStr( FFirstName ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "  SecondName = %s, ", ARRAYOFCONST(( QuotedStr( FSecondName ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "  PhoneNumbers = %s, ", ARRAYOFCONST(( QuotedStr( FPhoneNumbers ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "  Addr = %s, ", ARRAYOFCONST(( QuotedStr( FAddr ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "  DateBirth = %s, ", ARRAYOFCONST(( QuotedStr( FDateBirth ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( "  Photo = %s  ", ARRAYOFCONST(( QuotedStr( FPhoto ) )) ) );
	DM->FDQueryContact->SQL->Add( Format( " where id = %d;", ARRAYOFCONST(( FID )) ) );

	//  DM->FDQueryContact->SQL->SaveToFile("E:\\SQL.txt")  ;

	DM->FDQueryContact->ExecSQL();
    result = DM->FDQueryContact->RowsAffected > 0;
	if ( ! result )
	  Error = "Can not Update the Contact";
  }
  catch( Exception & E )
  {
	Error = Format( "Can not Update the Contact: %s", ARRAYOFCONST(( E.Message )) );
  }
  return result;
}

//------------------------------------------------------------------
bool __fastcall TContact::DeleteContact( String& Err )
{
  bool result = false;
  result = false;
  Err = "";
  try
  {
	DM->FDQueryContact->Close();
	DM->FDQueryContact->SQL->Clear();
	DM->FDQueryContact->SQL->Add( "delete from personal " );
	DM->FDQueryContact->SQL->Add( Format( "where id = %d;", ARRAYOFCONST(( FID )) ) );
	DM->FDQueryContact->ExecSQL();
	result = DM->FDQueryContact->RowsAffected > 0;
	if ( ! result )
	  Err = "Can not delete the Contact";
  }
  catch( Exception & E )
  {
	Err = Format( "Error trying delete incluir contact: %s", ARRAYOFCONST(( E.Message )) );
  }
  return result;
}



