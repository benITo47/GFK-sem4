#include <wx/wx.h>
#include "GUIMyFrame1.h"

class MyApp : public wxApp {

public:

 virtual bool OnInit();
 virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() 
{
 GUIMyFrame1 *mainFrame = new GUIMyFrame1(NULL);

 wxImage::AddHandler(new wxJPEGHandler);           // Dodajemy handlery do formatow
 wxImage::AddHandler(new wxPNGHandler);            // z jakich bedziemy korzytsac
 wxImage image;
 mainFrame->Show(true);
 SetTopWindow(mainFrame);

 return true;
}