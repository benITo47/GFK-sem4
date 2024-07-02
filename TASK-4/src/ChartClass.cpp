#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg= std::move(c);
    x_step=2500;

}

void ChartClass::Set_Range()
{
 double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
 double x,y,step;
 int i;

 xmin=cfg->Get_x_start();
 xmax=cfg->Get_x_stop();

 step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
 x=cfg->Get_x_start();

 for (i=0;i<=x_step;i++)
  {
   y= GetFunctionValue(x);
   if (y>ymax) ymax=y;
   if (y<ymin) ymin=y;
   x=x+step;
  }

 y_min=ymin;
 y_max=ymax;
 x_min=xmin;
 x_max=xmax;
}


double ChartClass::GetFunctionValue(double x)
{
 if (cfg->Get_F_type()==1) return function1(x);
 if (cfg->Get_F_type()==2) return function2(x);
 return function3(x);
}

void ChartClass::Draw(wxDC *dc, int w, int h) {
    dc->SetBackground(wxBrush(wxColour(0, 0, 0)));
    dc->Clear();
    dc->SetPen(wxPen(wxColour(0, 0, 0)));
    dc->DrawRectangle(10, 10, w - 20, h - 20);
    dc->SetClippingRegion(wxRect(10, 10, w - 20, h - 20));
    dc->SetTextForeground(wxColour(0, 0, 0));

    Set_Range();

    const double x0 = cfg->Get_x0(), y0 = cfg->Get_y0(), x1 = cfg->Get_x1(), y1 = cfg->Get_y1();
    const double x_start = cfg->Get_x_start(), x_stop = cfg->Get_x_stop();
    const double delta_x = cfg->Get_dX(), delta_y = cfg->Get_dY();
    const double dx = (x_max - x_min) / x_step;
    const double alpha = cfg->Get_Alpha();


    Matrix transform(1, 1, 1, 1, 1, 1, 1, 1, 1);


    if (cfg->RotateScreenCenter()) {
        double dist_X = (x1 + x0) / 2.0, dist_Y = (y1 + y0) / 2.0;
        transform = GetTranslationTransform(w / 2, h / 2) *
                    GetRotationTransform(-alpha) *
                    GetTranslationTransform(-delta_x / (x1 - x0) * w, -delta_y / (y1 - y0) * h) *     //translacja wykresu wzgledem osi
                    GetTranslationTransform(-dist_X / (x1 - x0) * w, dist_Y / (y1 - y0) * h) *
                    GetTranslationTransform(delta_x / (x1 - x0) * w, delta_y / (y1 - y0) * h) *
                    GetScaleTransform(w - 20, h - 20, x0, y0, x1, y1);             // dla punktu rotacji w centrum okna

    } else {
        double dist_X = (x1 + x0) / 2.0, dist_Y = (y1 + y0) / 2.0;
        transform =
                GetTranslationTransform(delta_x / (x1 - x0) * w, delta_y / (y1 - y0) * h) *
                // to działa dla punktu obrotu w punkcie przeciecia osi wykresu
                GetTranslationTransform(w / 2, h / 2) *
                GetRotationTransform(-alpha) *
                GetTranslationTransform(-delta_x / (x1 - x0) * w, -delta_y / (y1 - y0) * h)*    //To jest do translacji wykresu wzgledem osi
                GetScaleTransform(w - 20, h - 20, x0, y0, x1, y1);
    }



    line2d(dc, transform, 0, y_min, 0, y_max);

    line2d(dc, transform, x_start, 0, x_stop, 0);

    if(cfg->GetShowMarkers()){
    int i;

    double xMarkerDistance = (x_stop-x_start) / 5;
    double yMarkerDistance = (y_max - y_min)/5;
    for (double x = x_start + delta_x; x < x_stop + delta_x; x += xMarkerDistance) {
        i++;
        double multiplier = 4.0;
        if (i % 2 == 0) { multiplier = -1.0; }
        if (x > -0.05 && x < 0.05) {
            DrawMarkers(dc, transform, alpha, 0 - 0.065* yMarkerDistance, multiplier * 0.05, 0);
        } else {
            line2d(dc, transform, x, 0.03, x, -0.03);
            DrawMarkers(dc, transform, alpha, x - 0.065, multiplier * 0.05*yMarkerDistance, x);
        }
    }

    for (double y = y_min + delta_y; y < y_max + delta_y; y += yMarkerDistance) {
        if (y <= -0.25 || y >= 0.20) {
            line2d(dc, transform, -0.015, y, 0.015, y);
            DrawMarkers(dc, transform, alpha, -0.25*xMarkerDistance, y + 0.075, y);
        }
    }
}

    dc->SetPen(wxPen(wxColour(255, 0, 0)));
    //  for (double x = x_start+delta_x; x < x_stop+delta_x; x += dx)
//        line2d(dc, transform, x, GetFunctionValue(x), x + dx, GetFunctionValue(x + dx));

    for (double x = x_start; x < x_stop ; x += dx) {

        double originalX = x, nextX = x + dx;
        double originalY = GetFunctionValue(x), nextY = GetFunctionValue(x + dx);
        double transformedX = originalX + delta_x;
        double transformedNextX = nextX + delta_x;
        double transformedY = originalY + delta_y;
        double transformedNextY = nextY + delta_y;

        line2d(dc, transform, transformedX, transformedY, transformedNextX, transformedNextY);
    }
}

void ChartClass::line2d(wxDC* dc, Matrix t, double x1, double y1, double x2, double y2)
{
    Vector u,v;
    u.Set(x1,y1);
    v.Set(x2,y2);
    Vector uPrim = t * v;
    Vector vPrim = t * u;

    x1 = uPrim.GetX();
    y1 = uPrim.GetY();
    x2 = vPrim.GetX();
    y2 = vPrim.GetY();

    dc->DrawLine(x1,y1,x2,y2);
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}



Matrix ChartClass::GetRotationTransform(double alpha)
{
    alpha = degToRad(alpha); //Zmiana ze stopni na radiany

    Matrix RotationTransform(cos(alpha), -sin(alpha), 0.0,
                             sin(alpha), cos(alpha), 0.0,
                             0.0, 0.0, 1.0
                             );

    return RotationTransform;
}


Matrix ChartClass::GetScaleTransform(double w, double h, double x0, double y0, double x1, double y1)
{
    double Sx = w/(x1-x0);
    double Sy = -h/(y1-y0);

    Matrix ScaleTransform(Sx, 0.0, 0.0,
                          0.0, Sy, 0.0,
                          0.0, 0.0, 1.0);
    return ScaleTransform;
}


Matrix ChartClass::GetTranslationTransform(double deltaX, double deltaY)
{

    Matrix TranslationTransform(1.0, 0.0, deltaX,
                                0.0, 1.0, deltaY,
                                0.0, 0.0, 1.0);

    return TranslationTransform;
}


void ChartClass::DrawMarkers(wxDC* dc, Matrix t, double alpha, double x, double y, double value) {
    // Prepare the marker position
    Vector MarkerPos;
    MarkerPos.Set(x, y);
    MarkerPos = t * MarkerPos;

    // Create a font object with the desired size (e.g., 12 points)
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // Set the font for the device context
    dc->SetFont(font);

    // Draw the rotated text with the specified font
    dc->DrawRotatedText(wxString::Format(wxT("%.2f"), value), MarkerPos.GetX(), MarkerPos.GetY(), alpha);
}