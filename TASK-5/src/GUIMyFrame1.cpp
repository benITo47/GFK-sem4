#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"


struct Point {
    float x, y, z;
    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
    int R, G, B;
    Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
    Point begin, end;
    Color color;
    Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ): MyFrame1( parent )
{

    WxPanel->Bind(wxEVT_PAINT, &GUIMyFrame1::OnPaint, this);

    m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
    m_staticText25->SetLabel(_("Obr\u00F3t X:"));
    m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
    m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

    WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
    WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
    WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

    WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
    WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
    WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

    WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
    WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
    WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
    WxPanel->Refresh();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
    wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (WxOpenFileDialog.ShowModal() == wxID_OK)
    {
        double x1, y1, z1, x2, y2, z2;
        int r, g, b;

        std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
        if (in.is_open())
        {
            data.clear();
            while (!in.eof())
            {
                in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
                data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
            }
            in.close();
        }
    }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
    WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
    WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
    WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

    WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
    WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
    WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

    WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
    WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
    WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));

    WxPanel->Refresh();
}




Matrix4 ScaleTransform(double scaleX, double scaleY, double scaleZ){
    Matrix4 matrix;

    matrix.data[0][0] = scaleX;
    matrix.data[1][1] = scaleY;
    matrix.data[2][2] = scaleZ;
    matrix.data[3][3] = 1.0;

    return matrix;
}
Matrix4 RotateXTransform(double alpha) {
    Matrix4 matrix;

    matrix.data[0][0] = 1.0;
    matrix.data[1][1] = cos(alpha);
    matrix.data[1][2] = sin(alpha);
    matrix.data[2][1] = -sin(alpha);
    matrix.data[2][2] = cos(alpha);
    matrix.data[3][3] = 1.0;

    return matrix;
}
Matrix4 RotateYTransform(double alpha) {
    Matrix4 matrix;

    matrix.data[0][0] = cos(alpha);
    matrix.data[0][2] = -sin(alpha);
    matrix.data[1][1] = 1.0;
    matrix.data[2][0] = sin(alpha);
    matrix.data[2][2] = cos(alpha);
    matrix.data[3][3] = 1.0;

    return matrix;
}
Matrix4 RotateZTransform(double alpha){

    Matrix4 matrix;

    matrix.data[0][0] = cos(alpha);
    matrix.data[0][1] = sin(alpha);
    matrix.data[1][0] = -sin(alpha);
    matrix.data[1][1] = cos(alpha);
    matrix.data[2][2] = 1.0;
    matrix.data[3][3] = 1.0;

    return matrix;
};
Matrix4 TranslationTransform(double translationX, double translationY, double translationZ) {

    Matrix4 matrix;
    matrix.data[0][0] = 1.0;
    matrix.data[0][3] = translationX;
    matrix.data[1][1] = 1.0;
    matrix.data[1][3] = translationY;
    matrix.data[2][2] = 1.0;
    matrix.data[2][3] = translationZ;
    matrix.data[3][3] = 1.0;

    return matrix;
}

Matrix4 GetRotationMatrix(float dx, float dy, float dz)
{
    Matrix4 mat = RotateXTransform(dx) * RotateYTransform(dy) * RotateZTransform(dz);
    return mat;
}






void GUIMyFrame1::Repaint(wxDC& dc) {


    double scaleX = WxSB_ScaleX->GetValue()/100.0;
    double scaleY = WxSB_ScaleY->GetValue()/100.0;
    double scaleZ = WxSB_ScaleZ->GetValue()/100.0;

    Matrix4 scale = ScaleTransform(scaleX, scaleY, scaleZ); //call


    //macierze obrotu
    double alphaX = WxSB_RotateX->GetValue() * M_PI / 180.0;
    double alphaY = WxSB_RotateY->GetValue() * M_PI / 180.0;
    double alphaZ = WxSB_RotateZ->GetValue() * M_PI / 180.0;

    Matrix4 rotateZ = RotateZTransform(alphaZ);
    Matrix4 rotateY = RotateYTransform(alphaY);
    Matrix4 rotateX = RotateXTransform(alphaX);



    double translationX = (WxSB_TranslationX->GetValue() - 100.0) / 50.0;
    double translationY = (WxSB_TranslationY->GetValue() - 100.0) / 50.0;
    double translationZ = (WxSB_TranslationZ->GetValue() - 100.0) / 50.0;

    Matrix4 translation = TranslationTransform(translationX, translationY, translationZ);



    Matrix4 zhelper_matrix;
    zhelper_matrix.data[0][0] = 1.0;
    zhelper_matrix.data[1][1] = 1.0;
    zhelper_matrix.data[3][2] = 1.0 / 2.0;



    Matrix4 windowhelper_matrix;
    windowhelper_matrix.data[0][0] = WxPanel->GetSize().GetWidth() / 2.0;
    windowhelper_matrix.data[1][1] = -WxPanel->GetSize().GetHeight() / 2.0;
    windowhelper_matrix.data[0][3] = WxPanel->GetSize().GetWidth() / 2.0;
    windowhelper_matrix.data[1][3] = WxPanel->GetSize().GetHeight() / 2.0;




    Matrix4 transform1_matrix = translation * rotateX * rotateY* rotateZ * scale;

    Matrix4 transform2_matrix = windowhelper_matrix * zhelper_matrix;


    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    for (Segment segment : data)
    {
        dc.SetPen(wxPen(wxColour(segment.color.R, segment.color.G, segment.color.B)));

        Vector4 beginP, endP;
        beginP.Set(segment.begin.x, segment.begin.y, segment.begin.z);
        endP.Set(segment.end.x, segment.end.y, segment.end.z);

        beginP = transform1_matrix * beginP;
        endP = transform1_matrix * endP;

        for(int i=0; i<3; i++)
        {

            beginP.data[i] /= beginP.data[3];
            endP.data[i] /= endP.data[3];
        }

        auto clip = 1.0f;

        if ((beginP.GetZ() > -clip && endP.GetZ() <= -clip) || (endP.GetZ() > -clip && beginP.GetZ() <= -clip))
        {
            Vector4 p1;
            Vector4 p2;

            if(endP.GetZ()<= -clip)
            {
                p1 = endP;
                p2 = beginP;
            }
            else
            {
                p1 = beginP;
                p2 = endP;
            }

            double tmp = abs((-clip - p1.data[2]) / (p2.data[2] - p1.data[2]));
            p1.data[0] = (p2.data[0] - p1.data[0]) * tmp + p1.data[0];
            p1.data[1] = (p2.data[1] - p1.data[1]) * tmp + p1.data[1];
            p1.data[2] = -clip;

            beginP = transform2_matrix * p1;
            endP = transform2_matrix * p2;

            for(int i=0; i<3; i++)
            {
                beginP.data[i] /= beginP.data[3];
                endP.data[i] /= endP.data[3];
            }

        }


        else if (beginP.GetZ() <= -clip && endP.GetZ() <= -clip)
        {
            continue;
        }

        else
        {
            beginP = transform2_matrix * beginP;
            endP = transform2_matrix * endP;
            for(int i=0; i<3; i++)
            {
                beginP.data[i] /= beginP.data[3];
                endP.data[i] /= endP.data[3];
            }
        }

        dc.DrawLine(beginP.GetX(), beginP.GetY(), endP.GetX(), endP.GetY());
    }
}

void GUIMyFrame1::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(WxPanel);
    Repaint(dc);
}



