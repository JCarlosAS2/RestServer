//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdContext.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdHTTPServer.hpp>
#include <string.h>
#include <REST.Response.Adapter.hpp>


#include <UContact.h>
#include <UUtils.h>
#include <Vcl.ExtCtrls.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TIdHTTPServer *IdHTTPServer1;
	TStaticText *lblinfo;
	TLabel *lblNome;
	TGroupBox *GroupBox1;
	TButton *btnAtivar;
	TButton *btnStop;
	TGroupBox *GroupBox2;
	TMemo *memLogReq;
	TGroupBox *GroupBox3;
	TMemo *memLogRes;
	TSplitter *Splitter1;
	TLabel *Label1;
	TCSpinEdit *sePort;
	void __fastcall btnAtivarClick(TObject *Sender);
	void __fastcall btnStopClick(TObject *Sender);
	void __fastcall IdHTTPServer1CommandGet(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall IdHTTPServer1CommandOther(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo);
private:	// User declarations
	TContact * Contact;

	void __fastcall LogLastRequest(TIdHTTPRequestInfo *req);
	void __fastcall LogLastResponse(TIdHTTPResponseInfo *res);
	BOOL __fastcall CheckAuthentication(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res);

	void __fastcall GetClientes(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res);
	void __fastcall InsertCliente(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res);
	void __fastcall UpdateCliente(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res);
	void __fastcall DeleteCliente(TIdHTTPRequestInfo *req, TIdHTTPResponseInfo *res);


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
