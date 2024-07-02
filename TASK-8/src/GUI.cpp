///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  8 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	//this->SetSizeHints( wxSize( 600,400 ), wxDefaultSize );
	this->SetClientSize(this->FromDIP(wxSize(1000, 533)));

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

    m_wxPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    m_wxPanel->SetInitialSize(wxSize(800,533));
	bSizer1->Add( m_wxPanel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );

    m_b_load = new wxButton(this, wxID_ANY, _("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add(m_b_load, 0, wxALL, 5 );

    m_b_erode = new wxButton(this, wxID_ANY, _("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add(m_b_erode, 0, wxALL, 5 );

    m_b_censor = new wxButton(this, wxID_ANY, ("Censor"), wxDefaultPosition, wxDefaultSize, 0);
    gSizer1->Add(m_b_censor, 0, wxALL, 5);

    m_b_animate = new wxButton(this, wxID_ANY, _("Animate"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add(m_b_animate, 0, wxALL, 5 );




	bSizer2->Add( gSizer1, 1, wxEXPAND, 5 );

    m_exif_panel = new ExifPanel(this);
    bSizer2->Add(m_exif_panel,1,wxEXPAND,5);

	bSizer1->Add( bSizer2, 0, wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
    m_wxPanel->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_wxPanel_update), NULL, this);
    m_exif_panel->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_exif_panel_update), NULL, this);
    m_b_load->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_load_click), NULL, this);
    m_b_animate->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_animate_click), NULL, this);
    m_b_erode->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_erode_click), NULL, this);
    m_b_censor->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_censor_click), NULL, this);
    this->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::On_Window_Resize), NULL, this);

}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
    m_wxPanel->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_wxPanel_update), NULL, this);
    m_exif_panel->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_exif_panel_update), NULL, this);
    m_b_load->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_load_click), NULL, this);
    m_b_animate->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_animate_click), NULL,this);
    m_b_erode->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_erode_click), NULL, this);
    m_b_censor->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_b_censor_click), NULL, this);
    this->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::On_Window_Resize), NULL, this);


}
