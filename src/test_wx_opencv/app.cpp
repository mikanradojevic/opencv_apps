#include "wx/fileconf.h"
#include "wx/wfstream.h"
#include "app.h" 
#include "overview_frame.h"

IMPLEMENT_APP(c_wx_app) 

bool c_wx_app::OnInit()
{
	wxInitAllImageHandlers();

	// Applicaiton Information 
	SetAppName(wxT("LensCorrectionApp"));

 
	// Create the main frame
	c_overview_frame *overview_frame = new c_overview_frame(NULL, wxID_OVERVIEW_FRAME, _T("��ͷУ׼���򣨲��԰棩"), wxPoint(50, 50), wxSize(450,340));
	overview_frame->Show(true);
	
    return true; 
} 

int c_wx_app::OnExit()
{ 
	return wxApp::OnExit(); 
}