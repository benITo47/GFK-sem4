//
// Created by Bartłomiej Obrochta on 03/04/2024.
//

#ifndef LAB03_MONKEYPANEL_H
#define LAB03_MONKEYPANEL_H

#include "wx/wx.h"
#include <wx/filedlg.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/splitter.h>
#include <cmath>

class MonkeyPanel : public wxPanel {
public:
    MonkeyPanel(wxWindow* parent);
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

    bool eyes = false;
    int SymbolChoice = 0;
    int RGB[3] = {0, 0, 0};
    float Radius = sqrt(40 * 40 + 50 * 50);
    float ArmUpValue = 1.0;
    std::string DisplayText = "Tekst";

    DECLARE_EVENT_TABLE()

private:
    wxPoint center;
    wxPoint Reka;
    wxBitmap bitmapa;
};






#endif //LAB03_MONKEYPANEL_H
