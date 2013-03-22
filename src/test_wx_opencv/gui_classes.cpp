///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "graph_canvas.h"
#include "ocv_cam_canvas.h"
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
	wxMenuItem* m_calc_MTF;
	m_calc_MTF = new wxMenuItem( mImageMenu, wxID_ANY, wxString( wxT("Calculate MTF") ) , wxEmptyString, wxITEM_NORMAL );
	mImageMenu->Append( m_calc_MTF );
	
	wxMenuItem* m_calc_histogram;
	m_calc_histogram = new wxMenuItem( mImageMenu, wxID_ANY, wxString( wxT("Calculate Histogram") ) , wxEmptyString, wxITEM_NORMAL );
	mImageMenu->Append( m_calc_histogram );
	
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
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( ImageFrame::on_paint ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( ImageFrame::on_size ) );
	m_ocv_canvas->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( ImageFrame::on_leave_window ), NULL, this );
	this->Connect( mMenuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_open ) );
	this->Connect( mMenuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_exit ) );
	this->Connect( m_calc_MTF->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_calc_mtf ) );
	this->Connect( m_calc_histogram->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_calc_histogram ) );
}

ImageFrame::~ImageFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( ImageFrame::on_paint ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( ImageFrame::on_size ) );
	m_ocv_canvas->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( ImageFrame::on_leave_window ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_open ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_menu_exit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_calc_mtf ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ImageFrame::on_calc_histogram ) );
	
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
	
	// Connect Events
	this->Connect( mSaveMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( OverviewFrame::on_save_report ) );
}

OverviewFrame::~OverviewFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( OverviewFrame::on_save_report ) );
	
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
	m_img_canvas_left->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_left_img_thunmnail_double_click ), NULL, this );
	m_img_canvas_mid->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_mid_img_thunmnail_double_click ), NULL, this );
	m_img_canvas_right->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_right_img_thunmnail_double_click ), NULL, this );
}

OverviewImgSubPanel::~OverviewImgSubPanel()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_left_dbl_clk ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( OverviewImgSubPanel::on_paint ) );
	m_img_canvas_left->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_left_img_thunmnail_double_click ), NULL, this );
	m_img_canvas_mid->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_mid_img_thunmnail_double_click ), NULL, this );
	m_img_canvas_right->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OverviewImgSubPanel::on_right_img_thunmnail_double_click ), NULL, this );
	
}

OverviewGraphSubPanel ::OverviewGraphSubPanel ( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxStaticBoxSizer* graphSubPanelBoxSizer;
	graphSubPanelBoxSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("graphs") ), wxHORIZONTAL );
	
	m_graph_wnd_left = new c_graph_canvas( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	graphSubPanelBoxSizer->Add( m_graph_wnd_left, 1, wxEXPAND | wxALL, 5 );
	
	m_graph_wnd_mid = new c_graph_canvas( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	graphSubPanelBoxSizer->Add( m_graph_wnd_mid, 1, wxEXPAND | wxALL, 5 );
	
	m_graph_wnd_right = new c_graph_canvas( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	graphSubPanelBoxSizer->Add( m_graph_wnd_right, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( graphSubPanelBoxSizer );
	this->Layout();
	graphSubPanelBoxSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( OverviewGraphSubPanel ::on_paint ) );
}

OverviewGraphSubPanel ::~OverviewGraphSubPanel ()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( OverviewGraphSubPanel ::on_paint ) );
	
}

OverviewVideoSubPanel::OverviewVideoSubPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxStaticBoxSizer* videoSubPanelBoxSizer;
	videoSubPanelBoxSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Cameras") ), wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizerCamLeft;
	sbSizerCamLeft = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Left") ), wxVERTICAL );
	
	m_cam_canvas_left = new c_ocv_cam_canvas( this, wxID_CAM_CANVAS_LEFT, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxSIMPLE_BORDER|wxVSCROLL );
	m_cam_canvas_left->SetScrollRate( 5, 5 );
	sbSizerCamLeft->Add( m_cam_canvas_left, 1, wxEXPAND | wxALL, 5 );
	
	m_btn_open_cam_left = new wxButton( this, wxID_ANY, wxT("Open Camera"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCamLeft->Add( m_btn_open_cam_left, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_btn_capture_left = new wxButton( this, wxID_BTN_CAPTURE_LEFT, wxT("Capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btn_capture_left->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	sbSizerCamLeft->Add( m_btn_capture_left, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	videoSubPanelBoxSizer->Add( sbSizerCamLeft, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerCamMid;
	sbSizerCamMid = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Mid") ), wxVERTICAL );
	
	m_cam_canvas_mid = new c_ocv_cam_canvas( this, wxID_CAM_CANVAS_MID, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxSIMPLE_BORDER|wxVSCROLL );
	m_cam_canvas_mid->SetScrollRate( 5, 5 );
	sbSizerCamMid->Add( m_cam_canvas_mid, 1, wxEXPAND | wxALL, 5 );
	
	m_btn_open_cam_mid = new wxButton( this, wxID_ANY, wxT("Open Camera"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCamMid->Add( m_btn_open_cam_mid, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_btn_capture_mid = new wxButton( this, wxID_BTN_CAPTURE_MID, wxT("Capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btn_capture_mid->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	sbSizerCamMid->Add( m_btn_capture_mid, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	videoSubPanelBoxSizer->Add( sbSizerCamMid, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerCamRight;
	sbSizerCamRight = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Right") ), wxVERTICAL );
	
	m_cam_canvas_right = new c_ocv_cam_canvas( this, wxID_CAM_CANVAS_RIGHT, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxSIMPLE_BORDER|wxVSCROLL );
	m_cam_canvas_right->SetScrollRate( 5, 5 );
	sbSizerCamRight->Add( m_cam_canvas_right, 1, wxEXPAND | wxALL, 5 );
	
	m_btn_open_cam_right = new wxButton( this, wxID_ANY, wxT("Open Camera"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCamRight->Add( m_btn_open_cam_right, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_btn_capture_right = new wxButton( this, wxID_BTN_CAPTURE_RIGHT, wxT("Capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btn_capture_right->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	sbSizerCamRight->Add( m_btn_capture_right, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	videoSubPanelBoxSizer->Add( sbSizerCamRight, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( videoSubPanelBoxSizer );
	this->Layout();
	videoSubPanelBoxSizer->Fit( this );
	
	// Connect Events
	m_btn_open_cam_left->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_open_cam_left_click ), NULL, this );
	m_btn_capture_left->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_capture_left_click ), NULL, this );
	m_btn_open_cam_mid->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_open_cam_mid_click ), NULL, this );
	m_btn_capture_mid->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_capture_mid_click ), NULL, this );
	m_btn_open_cam_right->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_open_cam_right_click ), NULL, this );
	m_btn_capture_right->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_capture_right_click ), NULL, this );
}

OverviewVideoSubPanel::~OverviewVideoSubPanel()
{
	// Disconnect Events
	m_btn_open_cam_left->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_open_cam_left_click ), NULL, this );
	m_btn_capture_left->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_capture_left_click ), NULL, this );
	m_btn_open_cam_mid->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_open_cam_mid_click ), NULL, this );
	m_btn_capture_mid->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_capture_mid_click ), NULL, this );
	m_btn_open_cam_right->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_open_cam_right_click ), NULL, this );
	m_btn_capture_right->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverviewVideoSubPanel::on_capture_right_click ), NULL, this );
	
}

ToolsFrame::ToolsFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0|wxTAB_TRAVERSAL );
	m_save_page = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_static_lens_name = new wxStaticText( m_save_page, wxID_ANY, wxT("Lens Name: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_static_lens_name->Wrap( -1 );
	fgSizer1->Add( m_static_lens_name, 0, wxALL, 5 );
	
	m_txt_lens_name = new wxTextCtrl( m_save_page, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_txt_lens_name, 0, wxALL, 5 );
	
	m_btn_save = new wxButton( m_save_page, wxID_ANY, wxT("Save Report"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_btn_save, 0, wxALL, 5 );
	
	
	m_save_page->SetSizer( fgSizer1 );
	m_save_page->Layout();
	fgSizer1->Fit( m_save_page );
	m_notebook->AddPage( m_save_page, wxT("Save"), false );
	
	bSizer4->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_btn_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolsFrame::on_save_report ), NULL, this );
}

ToolsFrame::~ToolsFrame()
{
	// Disconnect Events
	m_btn_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ToolsFrame::on_save_report ), NULL, this );
	
}
