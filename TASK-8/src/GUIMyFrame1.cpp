#include "GUIMyFrame1.h"
#include "iostream"
#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colourdata.h>

wxImage ConvertCImgToWxImage(const  cimg_library::CImg<unsigned char>& cimg) {
    const int width = cimg.width();
    const int height = cimg.height();
    const int channels = cimg.spectrum(); // Typically 3 for RGB, 4 for RGBA

    // Create a wxImage with the right size
    wxImage wximg(width, height, false);

    // Copy the data from CImg to wxImage
    if (channels >= 3) {
        // Assuming RGB or RGBA data in CImg

        for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
                unsigned char r = cimg(x, y, 0, 0); // Red
                unsigned char g = cimg(x, y, 0, 1); // Green
                unsigned char b = cimg(x, y, 0, 2); // Blue
                wximg.SetRGB(x, y, r, g, b);
                if (channels == 4) {
                    unsigned char a = cimg(x, y, 0, 3); // Alpha
                    wximg.SetAlpha(x, y, a);
                }
            }
        }
    }

    // Convert wxImage to wxBitmap
    return wximg;
}
//----------------------------



GUIMyFrame1::GUIMyFrame1( wxWindow* parent ):MyFrame1( parent )
{
    isAnimating = false;

    m_wxPanel->Bind(wxEVT_PAINT, &GUIMyFrame1::OnPaint, this);
    this->SetBackgroundColour(wxColor(70,70,70));
    m_wxPanel->SetBackgroundColour(wxColor(192, 192, 192));

    LoadCImg("/Users/bartek/Documents/Grafika Komputerowa/lab8-nowelibki/test.jpg");
    LoadFreeImage("/Users/bartek/Documents/Grafika Komputerowa/lab8-nowelibki/test.jpg");

}

void GUIMyFrame1::m_b_load_click(wxCommandEvent& event) {
    if (isAnimating) {
        isAnimating = false;
    }

    wxFileDialog wxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""),
                                  wxT("JPEG file (*.jpg)|*.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (wxOpenFileDialog.ShowModal() == wxID_OK) {
        wxString fileName = wxOpenFileDialog.GetPath();

        // Load images using the separate functions
        LoadFreeImage(fileName);  // Load FreeImage for EXIF or other purposes
        LoadCImg(fileName);       // Load CImg for processing and display

        // Clear animation frames
        std::fill(std::begin(_animationFrames), std::end(_animationFrames), wxBitmap());

        // Refresh the panel
        m_wxPanel->Refresh();
        m_wxPanel->Update();
    }
}

void GUIMyFrame1::m_b_censor_click(wxCommandEvent& event) {
    if (isAnimating) {
        event.Skip();
        return;
    }
    image_cimg_process = image_cimg;
    int width = image_cimg_process.width();
    int height = image_cimg_process.height();

    int x1 = width / 2;
    int y1 = static_cast<int>(0.05 * height);
    int x2 = std::min(x1 + width / 4, width - 1); // Ensure x2 is within image width
    int y2 = static_cast<int>(0.2 * height);
    y2 = std::min(y2, height - 1); // Ensure y2 is within image height

    if (x1 < x2 && y1 < y2) {
        cimg_library::CImg<unsigned char> region = image_cimg_process.get_crop(x1, y1, x2, y2);
        region.blur(5);
        image_cimg_process.draw_image(x1, y1, region);
        WX_Image = ConvertCImgToWxImage(image_cimg_process);
    }

    m_wxPanel->Refresh();
    m_wxPanel->Update();
}

void GUIMyFrame1::m_b_erode_click(wxCommandEvent& event) {
    if (isAnimating) {
        event.Skip();
        return;
    }
    image_cimg_process = image_cimg;
    auto erodeValue = image_cimg_process.width() / 150;
    image_cimg_process.erode(erodeValue);
    WX_Image = ConvertCImgToWxImage(image_cimg_process);

    m_wxPanel->Refresh();
    m_wxPanel->Update();
}


void GUIMyFrame1::m_wxPanel_update(wxUpdateUIEvent& event )
{
        m_wxPanel->Refresh();
        m_wxPanel->Update();
}

void GUIMyFrame1::m_exif_panel_update(wxUpdateUIEvent &event)
{
    m_exif_panel->Refresh();
    m_exif_panel->Update();
}

void GUIMyFrame1::LoadFreeImage(const wxString& fileName) {


    FreeImage_Initialise();
    image_freeimg = FreeImage_Load(FIF_JPEG, fileName.ToStdString().c_str(), JPEG_DEFAULT);

    exif_info.clear();
    FITAG *tag = nullptr;
    FIMETADATA *mdhandle = nullptr;
    mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, image_freeimg, &tag);

    if (mdhandle) {
        do {
            const char* tagKey = FreeImage_GetTagKey(tag);
            const char* tagValue = FreeImage_TagToString(FIMD_EXIF_MAIN, tag);
            // Save the key-value pair in the vector
            exif_info.push_back({tagKey, tagValue});
        } while (FreeImage_FindNextMetadata(mdhandle, &tag));
        FreeImage_FindCloseMetadata(mdhandle);
    }

    m_exif_panel->UpdateExif(exif_info);


}

void GUIMyFrame1::LoadCImg(const wxString& fileName) {
    try {
        image_cimg = cimg_library::CImg<unsigned char>(fileName.ToStdString().c_str());

        // Check and correct orientation
        // Correct the orientation




        FreeImage_Unload(image_freeimg);
        FreeImage_DeInitialise();

        int maxWidth = 1200;
        int maxHeight = 800;
        int panelWidth = 150;

        int imgWidth = image_cimg.width();
        int imgHeight = image_cimg.height();

        double aspectRatio = static_cast<double>(imgWidth) / imgHeight;
        if (imgWidth > maxWidth || imgHeight > maxHeight) {
            if (aspectRatio > 1) { // Width is the limiting factor
                imgWidth = maxWidth;
                imgHeight = static_cast<int>(maxWidth / aspectRatio);
            } else {  // Height is the limiting factor
                imgHeight = maxHeight;
                imgWidth = static_cast<int>(maxHeight * aspectRatio);
            }
        }

        // Resize the CImg image
        image_cimg.resize(imgWidth, imgHeight);
        image_cimg_process = image_cimg;
        WX_Image = ConvertCImgToWxImage(image_cimg_process);

        m_wxPanel->SetSize(wxSize(imgWidth, imgHeight));
        this->SetSize(wxSize(imgWidth + panelWidth, imgHeight));
        this->Layout();
        this->Center();

    } catch (const cimg_library::CImgException& e) {
        std::cerr << "Failed to load image with CImg: " << e.what() << std::endl;
        return;
    }
}







void GUIMyFrame1::m_b_animate_click(wxCommandEvent& event) {
    if (isAnimating) {
        isAnimating = false;
        this->SetMinSize(wxSize(-1, -1));
        this->SetMaxSize(wxSize(-1, -1));
    } else {
        isAnimating = true;
        this->SetMinSize(this->GetSize());
        this->SetMaxSize(this->GetSize());
        Animate();
    }

    event.Skip();
}
void GUIMyFrame1::Animate() {
    image_cimg_process = image_cimg;

    const int height = image_cimg_process.height();
    const int width = image_cimg_process.width();

    float color[3] = { 1, 1, 1 };

    auto gauss = cimg_library::CImg<float>(width, height, 1, 3);
    auto gauss2 = cimg_library::CImg<float>(width, height, 1, 3);
    cimg_library::CImg<float> tmp;

    for (int i = 0; i < 60; i++) {
        gauss.fill(0).draw_gaussian(
                (width / 2.) + (width * 0.3) * cos(i * M_PI / 60.f),
                (height / 2.) + (height * 0.3) * sin(i * M_PI / 60.f),
                120.0f,
                color,
                1.0f
        );

        gauss2.fill(0).draw_gaussian(
                (width / 2.) + (width * 0.3) * cos((i + 60.f) * M_PI / 60.f),
                (height / 2.) + (height * 0.3) * sin((i + 60.f) * M_PI / 60.f),
                120.0f,
                color,
                1.0f
        );

        gauss += gauss2;

        tmp = image_cimg_process;
        tmp.mul(gauss);
        auto frame = ConvertCImgToWxImage(tmp);

        _animationFrames[59 - i] = wxBitmap(frame);
    }
}





void GUIMyFrame1::ToglleIsAnimating()
{
    if (isAnimating) {
        isAnimating = false;
    } else {
        isAnimating = true;
    }
}

void GUIMyFrame1::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(m_wxPanel);
    Repaint(dc);
}



void GUIMyFrame1::Repaint(wxDC& dc)
{
    static unsigned frame_index = 0;
    static unsigned tick_delay = 0;

    dc.Clear();

    if (WX_Image.IsOk())
    {
        if (isAnimating)
        {
            dc.DrawBitmap(_animationFrames[frame_index], 0, 0);
            tick_delay = (tick_delay + 1) % 8;
            if (tick_delay >= 7) frame_index = (frame_index + 1) % 60;
            RefreshRect(wxRect(1, 1, 1, 1), false);

            return;
        }
        wxSize panelSize = m_wxPanel->GetSize();
        wxImage scaledImage = WX_Image.Scale(panelSize.GetWidth(), panelSize.GetHeight(), wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(scaledImage);
        dc.DrawBitmap(bitmap, 0, 0);



    }
}
