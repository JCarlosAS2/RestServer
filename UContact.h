//---------------------------------------------------------------------------

#ifndef UContactH
#define UContactH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <UUtils.h>
#include <UDM.h>
class TContact;

class TContact
{
private:
  String FUID;
  int    FID;
  String FFirstName;
  String FSecondName;
  String FAddr;
  String FDateBirth;
  String FPhoneNumbers;
  int FAge;
  String FPhoto;

  void __fastcall SetUID( const String Value );
  void __fastcall SetID( const int Value );
  void __fastcall SetAge( const int Value );
  void __fastcall SetFirstName( const String Value );
  void __fastcall SetSecondName( const String Value );
  void __fastcall SetAddr( const String Value );
  void __fastcall SetPhoto( const String Value );
  void __fastcall SetPhoneNumbers( const String Value );
  void __fastcall SetDateBirth( const String Value );


  protected:
	/* protected declarations */
  public:
	/* public declarations */
  __property String UID = { read = FUID, write = SetUID };
  __property int ID = { read = FID, write = SetID };
  __property int Age = { read = FAge, write = SetAge };
  __property String FirstName = { read = FFirstName, write = SetFirstName };
  __property String SecondName = { read = FSecondName, write = SetSecondName };
  __property String PhoneNumbers = { read = FPhoneNumbers, write = SetPhoneNumbers };
  __property String Addr = { read = FAddr, write = SetAddr };
  __property String Photo = { read = FPhoto, write = SetPhoto };
  __property String DateBirth = { read = FDateBirth, write = SetDateBirth };

  bool __fastcall InsertContact( String& Error );
  bool __fastcall UpdateContact( String& Error );
  bool __fastcall DeleteContact( String& Error );

 String __fastcall FindContact(String pWhere, String& Error );


};


#endif
