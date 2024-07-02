#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/splitter.h>
#include <cmath>
#include "MyFrame.h"



class MyApp : public wxApp {
public:
    virtual bool OnInit();
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxImage::AddHandler(new wxPNGHandler);

    MyFrame* frame = new MyFrame("Lab 03");
    frame->SetInitialSize(wxSize(800, 600));
    frame->Show(true);
    return true;
}
