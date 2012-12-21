///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ocv_canvas.h"

#include "gui_classes.h"

///////////////////////////////////////////////////////////////////////////

ImageFrame::ImageFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* boxSizer1;
	boxSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_ocv_canvas = new c_ocv_canvas( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_ocv_canvas->SetScrollRate( 5, 5 );
	boxSizer1->Add( m_ocv_canvas, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( boxSizer1 );
	this->Layout();
	mImageFrameMenuBar = new wxMenuBar( 0 );
	mFileMenu = new wxMenu();
	wxMenuItem* mMenuItemOpen;
	mMenuItemOpen = new wxMenuItem( mFileMenu, wxID_ANY, wxString( wxT("Open...") ) , wxEmptyString, wxITEM_NORMAL );
	mFileMenu->Append( mMenuItemOpen );
	
	mFileMenu->AppendSeparator();
	
	wxMenuItem* mMenuItemExit;
	mMenuItemExit = new wxMenuItem( mFileMenu, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	mFileMenu->Append( mMenuItemExit );
	
	mImageFrameMenuBar->Append( mFileMenu, wxT("File") ); 
	
	mViewMenu = new wxMenu();
	mImageFrameMenuBar->Append( mViewMenu, wxT("View") ); 
	
	mImageMenu = new wxMenu();
	mImageFrameMenuBar->Append( mImageMenu, wxT("Image") ); 
	
	mToolsMenu = new wxMenu();
	mImageFrameMenuBar->Append( mToolsMenu, wxT("Tools") ); 
	
	mHelpMenu = new wxMenu();
	mImageFrameMenuBar->Append( mHelpMenu, wxT("Help") ); 
	
	this->SetMenuBar( mImageFrameMenuBar );
	
	mImageFrameStatusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	mImageFrameToolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	mImageFrameToolBar->Realize(); 
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( ImageFrame::on_erase_background ) );
	this->Connect( mMenuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_open ) );
	this->Connect( mMenuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_exit ) );
}

ImageFrame::~ImageFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( ImageFrame::on_erase_background ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_open ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_exit ) );
	
}

GraphFrame::GraphFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* graphFrameBoxSizer;
	graphFrameBoxSizer = new wxBoxSizer( wxVERTICAL );
	
	
	this->SetSizer( graphFrameBoxSizer );
	this->Layout();
	mGraphFrameMenuBar = new wxMenuBar( 0 );
	mFileMenu = new wxMenu();
	wxMenuItem* mSaveMenuItem;
	mSaveMenuItem = new wxMenuItem( mFileMenu, wxID_ANY, wxString( wxT("Save...") ) , wxEmptyString, wxITEM_NORMAL );
	mFileMenu->Append( mSaveMenuItem );
	
	mFileMenu->AppendSeparator();
	
	wxMenuItem* mQuitMenuItem;
	mQuitMenuItem = new wxMenuItem( mFileMenu, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	mFileMenu->Append( mQuitMenuItem );
	
	mGraphFrameMenuBar->Append( mFileMenu, wxT("File") ); 
	
	mHelpMenu = new wxMenu();
	wxMenuItem* mAboutMenuItem;
	mAboutMenuItem = new wxMenuItem( mHelpMenu, wxID_ANY, wxString( wxT("About...") ) , wxEmptyString, wxITEM_NORMAL );
	mHelpMenu->Append( mAboutMenuItem );
	
	mGraphFrameMenuBar->Append( mHelpMenu, wxT("Help") ); 
	
	this->SetMenuBar( mGraphFrameMenuBar );
	
	mGraphFrameToolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	mGraphFrameToolBar->Realize(); 
	
	
	this->Centre( wxBOTH );
}

GraphFrame::~GraphFrame()
{
}

OverviewFrame::OverviewFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* overviewFrameBoxSizer;
	overviewFrameBoxSizer = new wxBoxSizer( wxVERTICAL );
	
	
	this->SetSizer( overviewFrameBoxSizer );
	this->Layout();
	mOverviewFrameMenuBar = new wxMenuBar( 0 );
	mFileMenu = new wxMenu();
	wxMenuItem* mSaveMenuItem;
	mSaveMenuItem = new wxMenuItem( mFileMenu, wxID_ANY, wxString( wxT("Save...") ) , wxEmptyString, wxITEM_NORMAL );
	mFileMenu->Append( mSaveMenuItem );
	
	mFileMenu->AppendSeparator();
	
	wxMenuItem* mQuitMenuItem;
	mQuitMenuItem = new wxMenuItem( mFileMenu, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	mFileMenu->Append( mQuitMenuItem );
	
	mOverviewFrameMenuBar->Append( mFileMenu, wxT("File") ); 
	
	mHelpMenu = new wxMenu();
	wxMenuItem* mAboutMenuItem;
	mAboutMenuItem = new wxMenuItem( mHelpMenu, wxID_ANY, wxString( wxT("About...") ) , wxEmptyString, wxITEM_NORMAL );
	mHelpMenu->Append( mAboutMenuItem );
	
	mOverviewFrameMenuBar->Append( mHelpMenu, wxT("Help") ); 
	
	this->SetMenuBar( mOverviewFrameMenuBar );
	
	
	this->Centre( wxBOTH );
}

OverviewFrame::~OverviewFrame()
{
}

OverviewImgSubPanel::OverviewImgSubPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxStaticBoxSizer* imgSubPanelBoxSizer;
	imgSubPanelBoxSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Images") ), wxHORIZONTAL );
	
	m_img_canvas_left = new c_ocv_canvas( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxSIMPLE_BORDER|wxVSCROLL );
	m_img_canvas_left->SetScrollRate( 5, 5 );
	imgSubPanelBoxSizer->Add( m_img_canvas_left, 1, wxEXPAND | wxALL, 5 );
	
	m_img_canvas_mid = new c_ocv_canvas( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxSIMPLE_BORDER|wxVSCROLL );
	m_img_canvas_mid->SetScrollRate( 5, 5 );
	imgSubPanelBoxSizer->Add( m_img_canvas_mid, 1, wxEXPAND | wxALL, 5 );
	
	m_img_canvas_right = new c_ocv_canvas( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxSIMPLE_BORDER|wxVSCROLL );
	m_img_canvas_right->SetScrollRate( 5, 5 );
	imgSubPanelBoxSizer->Add( m_img_canvas_right, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( imgSubPanelBoxSizer );
	this->Layout();
	imgSubPanelBoxSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_left_dbl_clk ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( OverviewImgSubPanel::on_paint ) );
}

OverviewImgSubPanel::~OverviewImgSubPanel()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_left_dbl_clk ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( OverviewImgSubPanel::on_paint ) );
	
}

OverviewGraphSubPanel ::OverviewGraphSubPanel ( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("label") ), wxVERTICAL );
	
	
	this->SetSizer( sbSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( OverviewGraphSubPanel ::on_paint ) );
}

OverviewGraphSubPanel ::~OverviewGraphSubPanel ()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( OverviewGraphSubPanel ::on_paint ) );
	
}
