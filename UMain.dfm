object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Rest WebService Juan Carlos Sepulveda'
  ClientHeight = 550
  ClientWidth = 530
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 15
  object lblNome: TLabel
    Left = 0
    Top = 0
    Width = 530
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alTop
    Alignment = taCenter
    Caption = 'Rest WebService Application'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
    ExplicitWidth = 292
  end
  object Label3: TLabel
    Left = 0
    Top = 51
    Width = 530
    Height = 19
    Align = alTop
    Caption = 
      '  Username: user   Password: pass     Methodo Authenctication: B' +
      'asic'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -14
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    ExplicitWidth = 421
  end
  object Splitter1: TSplitter
    Left = 0
    Top = 235
    Width = 530
    Height = 0
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 241
    ExplicitWidth = 536
  end
  object lblinfo: TStaticText
    Left = 0
    Top = 24
    Width = 530
    Height = 27
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alTop
    Alignment = taCenter
    AutoSize = False
    Caption = 'WebService Stoped.'
    Color = clMedGray
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clInfoBk
    Font.Height = -14
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 479
    Width = 530
    Height = 71
    Align = alBottom
    TabOrder = 1
    object Label1: TLabel
      Left = 197
      Top = 11
      Width = 28
      Height = 19
      Caption = 'Port:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object btnAtivar: TButton
      Left = 30
      Top = 5
      Width = 83
      Height = 29
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Activate WS'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnAtivarClick
    end
    object btnStop: TButton
      Left = 30
      Top = 38
      Width = 83
      Height = 26
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Stop WS'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnStopClick
    end
    object sePort: TCSpinEdit
      Left = 234
      Top = 6
      Width = 121
      Height = 29
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = []
      MaxValue = 999999
      ParentFont = False
      TabOrder = 2
      Value = 8080
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 70
    Width = 530
    Height = 165
    Align = alTop
    Caption = 'Request'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    ExplicitLeft = -8
    ExplicitTop = 102
    ExplicitWidth = 536
    object memLogReq: TMemo
      Left = 2
      Top = 21
      Width = 532
      Height = 142
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alClient
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
      ExplicitWidth = 526
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 235
    Width = 530
    Height = 244
    Align = alClient
    Caption = 'Respon'
    TabOrder = 3
    object memLogRes: TMemo
      Left = 2
      Top = 17
      Width = 532
      Height = 234
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alClient
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
      ExplicitWidth = 526
      ExplicitHeight = 225
    end
  end
  object IdHTTPServer1: TIdHTTPServer
    Bindings = <>
    DefaultPort = 8080
    OnCommandOther = IdHTTPServer1CommandOther
    OnCommandGet = IdHTTPServer1CommandGet
    Left = 352
    Top = 120
  end
end
