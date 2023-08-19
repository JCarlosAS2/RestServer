object DM: TDM
  OnCreate = DataModuleCreate
  Height = 750
  Width = 1000
  PixelsPerInch = 120
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=Contact.db'
      'ConnectionDef=SQLite_Demo')
    LoginPrompt = False
    Left = 120
    Top = 56
  end
  object FDQueryContact: TFDQuery
    Connection = FDConnection1
    SQL.Strings = (
      
        'SELECT   personal.UID,   personal.ID,   personal.FirstName,   pe' +
        'rsonal.SecondName,   personal.Addr,   personal.DateBirth,   pers' +
        'onal.PhoneNumbers,   personal.Photo FROM   personal')
    Left = 128
    Top = 168
  end
end
