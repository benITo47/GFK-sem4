#include "GUIMyFrame1.h"
#include "iostream"
#include "CImg.h"
#include "FreeImage.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ):MyFrame1( parent )
{

m_scrolledWindow->Bind(wxEVT_PAINT, &GUIMyFrame1::OnPaint, this);
m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
this->SetBackgroundColour(wxColor(70,70,70));
m_scrolledWindow->SetScrollbars(25, 25, 52,40);
m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));

}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
    m_scrolledWindow->Refresh();
    m_scrolledWindow->Update();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
 Img_Cpy = Img_Org.ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
    Img_Cpy = Img_Org.Blur(10);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event ) {
    Img_Cpy = Img_Org.Mirror();
}
void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
 // TO DO: Zmiana rozmiarow do 320x240
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.Rescale(320,240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
    m_scrolledWindow->Refresh();
    Img_Cpy = Img_Org.Copy();
    Img_Cpy = Img_Cpy.Rotate(30 * M_PI / 180.0, wxPoint(Img_Org.GetSize().GetWidth() / 2, Img_Org.GetSize().GetHeight() / 2));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.RotateHue(-0.5);

}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event ) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
    if(!Img_Cpy.HasAlpha())
        Img_Cpy.InitAlpha();
    m_scrolledWindow->ClearBackground();
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
    m_scrolledWindow->Refresh();
    m_scrolledWindow->Update();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
    m_scrolledWindow->Refresh();
    m_scrolledWindow->Update();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
    Img_Cpy = Img_Org.Copy();
    unsigned char* rgbData = Img_Cpy.GetData();
    uint width = Img_Cpy.GetWidth();
    uint height = Img_Cpy.GetHeight();


    for(int x =1; x < width-1; x++)
    {
        for(int y = 1; y < height-1; y++)
        {
            int areaTab[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};

            areaTab[0][0] *= (Img_Org.GetRed(x - 1, y - 1) + Img_Org.GetGreen(x - 1, y - 1) + Img_Org.GetBlue(x - 1, y - 1)) / 3;
            areaTab[1][0] *= (Img_Org.GetRed(x - 1, y) + Img_Org.GetGreen(x - 1, y) + Img_Org.GetBlue(x - 1, y)) / 3;
            areaTab[2][0] *= (Img_Org.GetRed(x - 1, y + 1) + Img_Org.GetGreen(x - 1, y + 1) + Img_Org.GetBlue(x - 1, y + 1)) / 3;
            // [0][1], [1][1], [2][1] nas nie interesuje bo maska i tak wyzeruje;
            areaTab[0][2] *= (Img_Org.GetRed(x + 1, y - 1) + Img_Org.GetGreen(x + 1, y - 1) + Img_Org.GetBlue(x + 1, y - 1)) / 3;
            areaTab[1][2] *= (Img_Org.GetRed(x + 1, y) + Img_Org.GetGreen(x + 1, y) + Img_Org.GetBlue(x + 1, y)) / 3;
            areaTab[2][2] *= (Img_Org.GetRed(x + 1, y + 1) + Img_Org.GetGreen(x + 1, y + 1) + Img_Org.GetBlue(x + 1, y + 1)) / 3;

            int gradientSUM = 0;
            for(auto& m : areaTab)
            {
                for(int n : m)
                {
                    gradientSUM += n;
                }
            }
            if(gradientSUM > 255) gradientSUM = 255;
            if(gradientSUM < 0) gradientSUM = 0;

            //rgbData to jednowymiarowa tablica zawierajaca RGBRGBRGBRGB... - dla pikseli na obrazku
            //aby dostac sie do drugiego rzedu pikseli musimy uzyc rgbData[3*GetWidth()] -> takie wywolanie operatora daje dostep do IMAGE[1][0] (traktujmy obrazek jak tablice 2D pikseli);
            //aby uzyskac dostep do IMAGE[1][1] wystarczy dodac ktory piksel w rzedzie -> rgbData[3*(GetWidth()+1)]
            //dostep do IMAGE[10][12] - rgbData[3*(10*GetWidth() + 12)]
            // oczywiscie do dostep do kanalu R, aby uzyskac dostep do kanalu G i B wystarczy dodac odpowiednio 1 lub 2
            rgbData[3*(y*Img_Cpy.GetWidth() + x)+0] = gradientSUM; // Kanal R
            rgbData[3*(y*Img_Cpy.GetWidth() + x)+1] = gradientSUM; // Kanal G
            rgbData[3*(y*Img_Cpy.GetWidth() + x)+2] = gradientSUM; // Kanal B
        }
    }
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
 // TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
    Img_Cpy = Img_Org.Copy();
    unsigned char* rgbData = Img_Cpy.GetData();
    unsigned int size = 3 * Img_Cpy.GetHeight() * Img_Cpy.GetWidth();
    for(int i = 0; i < size; i++)
    {
        if(rgbData[i] > 128)
        {
            rgbData[i] = 255;
        } else rgbData[i] = 0;
    }
}

void GUIMyFrame1::m_b_rgb_click(wxCommandEvent &event)
{
    Img_Cpy = Img_Org.Copy();
    unsigned char* rgbData = Img_Cpy.GetData();
    uint size = 3 * Img_Cpy.GetWidth() * Img_Cpy.GetHeight();


    for(int i = 0; i < size; i+=3 )
    {
        double r = static_cast<double>(rgbData[i])/255;
        double g = static_cast<double>(rgbData[i+1])/255;
        double b = static_cast<double>(rgbData[i+2])/255;

        double alpha1 = M_PI;
        double alpha2 = 2 * M_PI;
        double alpha3 = - 1.5 * M_PI;

        r = 0.5 * (sin(alpha1 * r)) + 0.5;
        g = 0.25*((sin(alpha2*g) + cos(alpha3 * r)) + 2);
        b = 0.5 * cos(alpha3 * b) + 0.5;

        r *=255;
        g *= 255;
        b *= 255;

        rgbData[i] = r;
        rgbData[i+1] = g;
        rgbData[i+2] = b;
    }
}

void GUIMyFrame1::Brightness(int value)
{
    // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
    Img_Cpy = Img_Org.Copy();
    unsigned char* rgbData = Img_Cpy.GetData();    //Zwraca array RGBRGBRGBRGBRGB (po kolei dla pikseli w rzedzie, nastepnie kolejne rzedy) - tak wynika z docsów
    unsigned int size = 3 * Img_Cpy.GetHeight() * Img_Cpy.GetWidth();

    for(int i = 0; i < size; i +=3)
    {
        auto r = rgbData[i];
        auto g = rgbData[i + 1];
        auto b = rgbData[i + 2];

        if(r + value> 255) r = 255;
        else if (r + value < 0 ) r = 0;
        else r = r + value;

        if(g + value > 255) g = 255;
        else if (g + value < 0 ) g = 0;
        else g = g + value;

        if(b + value > 255) b = 255;
        else if (b + value < 0 ) b = 0;
        else b = b + value;

        rgbData[i] = r;
        rgbData[i + 1] = g;
        rgbData[i + 2] = b;

    }

}

void GUIMyFrame1::Contrast(int value) {
    // make a copy of the original first, since Img_Cpy might've been modified already
    Img_Cpy = Img_Org.Copy();

    size_t size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;  // w * h * channels
    unsigned char* rgbData = Img_Cpy.GetData();

    for (size_t i = 0; i < size; ++i) {
        short min = 0;
        short max = 255;

        // contrast is naturally written as a number in the range [0, inf]
        // for example an OELD could have an inf contrast (division by 0 for a black pixel), while a 0 contrast means 1 color (gray)
        // we need to convert [-100, +100] into a range [0, inf)

        // a suitable mapping would be a rational function
        double contrast = (100.0 + value) / (101.0 - value);  // +1 to avoid division by 0 :/
        short colorChannelValue = (rgbData[i] - 128) * contrast + 128;
        if(colorChannelValue > 255) colorChannelValue = 255;
        else if(colorChannelValue < 0 ) colorChannelValue = 0;

        rgbData[i] = colorChannelValue;
    }
}


void GUIMyFrame1::Repaint(wxDC& dc)
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 dc.DrawBitmap(bitmap, 0, 0, false); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(m_scrolledWindow);
    m_scrolledWindow->DoPrepareDC(dc);
    Repaint(dc);
}
