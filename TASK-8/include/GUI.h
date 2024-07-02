///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  8 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/frame.h>
#include "ExifPanel.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_wxPanel;
		wxButton* m_b_load;
		wxButton* m_b_animate;
		wxButton* m_b_erode;
        wxButton* m_b_censor;
        ExifPanel* m_exif_panel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_wxPanel_update(wxUpdateUIEvent& event ) { event.Skip(); }
        virtual void m_exif_panel_update(wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_b_load_click(wxCommandEvent& event ) { event.Skip(); }
		virtual void m_b_animate_click(wxCommandEvent& event ) { event.Skip(); }
		virtual void m_b_erode_click(wxCommandEvent& event ) { event.Skip(); }
        virtual void m_b_censor_click(wxCommandEvent& event ) { event.Skip(); }
        virtual void On_Window_Resize(wxSizeEvent& event)
        {

            wxSize size = this->GetClientSize();
            int controlsWidth = 150;
            int availableWidth = size.GetWidth() - controlsWidth;

            m_wxPanel->SetSize(wxSize(availableWidth, size.GetHeight()));
            this->Layout();
            m_wxPanel->Refresh();  // Ensure the panel is repainted
            m_wxPanel->Update();

            event.Skip();
        }


	
	public:
		wxStaticText* m_staticText1;

		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("GFK Lab 06"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

#endif //__GUI_H__
