//
// Created by Bartłomiej Obrochta on 03/04/2024.
//

#include "MonkeyPanel.h"

MonkeyPanel::MonkeyPanel(wxWindow* parent) : wxPanel(parent) {
    Bind(wxEVT_SIZE, &MonkeyPanel::OnSize, this);
    wxImage::AddHandler(new wxPNGHandler);
    wxImage image;
    if (image.LoadFile("/Users/bartek/Documents/Grafika Komputerowa/Lab03/banan.png", wxBITMAP_TYPE_PNG)) {   //Musiałem pdoać ścieżkę bezwzględną
        bitmapa = wxBitmap(image);
    }
    else {
        wxLogError("Nie ma bananów");
        return;
    }
}

void MonkeyPanel::OnSize(wxSizeEvent& event) {
    wxSize size = GetSize();
    center.x = size.GetWidth() / 2;
    center.y = size.GetHeight() / 2;
    Refresh();
}

void MonkeyPanel::OnPaint(wxPaintEvent& event) {
    wxPen transparentPen(*wxTRANSPARENT_PEN);
    wxBrush brush(wxColor(RGB[0], RGB[1], RGB[2]));
    wxPen pen(*wxBLACK, 1);

    wxPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);
    dc.Clear();
    dc.SetPen(transparentPen);

    wxString textToDraw = DisplayText;
    wxString textToDraw_2 = DisplayText;

    double maxAngle = M_PI / 3.0;
    double currentAngle = maxAngle * ArmUpValue / 100;
    int x = center.x - 100;
    int y = center.y - 100;
    int size = 40;

    switch (SymbolChoice) {
        case 0: {
            dc.SetBrush(brush);

            wxPoint points[5];
            points[0] = wxPoint(x, y - size);
            points[1] = wxPoint(x + size * 0.5878, y + size * 0.8090);
            points[2] = wxPoint(x - size * 0.9511, y - size * 0.3090);
            points[3] = wxPoint(x + size * 0.9511, y - size * 0.3090);
            points[4] = wxPoint(x - size * 0.5878, y + size * 0.8090);

            dc.DrawPolygon(5, points);
        }
            break;
        case 1: {
            dc.SetBrush(brush);

            dc.DrawCircle(x, y, size);
            dc.SetBrush(*wxWHITE_BRUSH);
            dc.DrawCircle(x + 20, y - 20, size);

            wxPen normalPen(*wxBLACK, 1);

            dc.SetPen(normalPen);
            dc.SetBrush(*wxBLACK_BRUSH);

            dc.DrawCircle(x - 25, y - 10, 5);
            dc.DrawLine(x + 15, y + 20, x - 5, y + 25);
        }
            break;
        case 2: {
            dc.SetBrush(brush);
            dc.DrawCircle(x, y, size - 10);
            dc.SetBrush(*wxBLACK_BRUSH);
            dc.DrawCircle(x-10,y-10,5);
            dc.DrawCircle(x+10,y-10,5);
            dc.DrawEllipticArc(x-10,y,25,10,40,100);
        }
            break;
    }

    dc.SetPen(pen);
    dc.SetBrush(*wxWHITE_BRUSH);

    Reka.x = center.x - Radius * sin(currentAngle + M_PI / 4);
    Reka.y = center.y + Radius * cos(currentAngle + M_PI / 4);

    dc.DrawLine(center.x, center.y, center.x + Radius * sin(M_PI / 4), center.y + Radius * cos(M_PI / 4));
    dc.DrawLine(Reka.x, Reka.y, center.x, center.y);
    dc.DrawLine(center.x, center.y - 20, center.x, center.y + 100);
    dc.DrawLine(center.x, center.y + 100, center.x + 50, center.y + 160);
    dc.DrawLine(center.x, center.y + 100, center.x - 50, center.y + 160);
    dc.DrawCircle(center.x, center.y - 40, 25);

    if (!eyes) {
        dc.DrawEllipticArc(center.x - 12, center.y - 30, 25, 25, 40, 140);
        dc.DrawEllipse(center.x - 15, center.y - 45, 7, 10);
        dc.DrawEllipse(center.x + 5, center.y - 45, 7, 10);
    }
    else {
        dc.DrawEllipticArc(center.x - 12, center.y - 45, 25, 25, 220, 320);
        dc.DrawEllipse(center.x - 15, center.y - 45, 10, 7);
        dc.DrawEllipse(center.x + 5, center.y - 45, 10, 7);
        dc.DrawBitmap(bitmapa, Reka.x - 60, Reka.y - 30, true);
    }
    dc.SetTextForeground(wxColour(255, 0, 0));
    dc.DrawText(textToDraw, center.x - 100, center.y + 175);

    dc.SetFont(wxFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false));
    dc.DrawRotatedText(textToDraw_2, center.x + 80, center.y + 170, 82);
}

BEGIN_EVENT_TABLE(MonkeyPanel, wxPanel)
                EVT_PAINT(MonkeyPanel::OnPaint)
END_EVENT_TABLE()
