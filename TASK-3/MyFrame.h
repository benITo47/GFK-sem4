//
// Created by Bartłomiej Obrochta on 02/04/2024.
//

#ifndef LAB03_MYFRAME_H
#define LAB03_MYFRAME_H
#include <wx/wx.h>


#include "MonkeyPanel.h"


class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);
    void OnButtonClick(wxCommandEvent& event);
    void ColorPick(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    void OnScroll(wxScrollEvent& event);
    void ZapiszDoPliku(wxCommandEvent& event);
    void OnExit(wxCloseEvent& event);
    void WxCheckBox1_Click(wxCommandEvent& event);
    void TextUpdate(wxCommandEvent& event);

private:
    MonkeyPanel* customPanel;
    wxButton* ZapiszButton;
    wxButton* KolorSymbolu;
    wxCheckBox* CheckBox;
    wxScrollBar* ScrollBar;
    wxGauge* gauge;
    wxTextCtrl* text;
    wxChoice* choiceControl;

    enum {
        ID_Zapis = 1001,
        ID_Kolor = 2001,
        ID_CheckBox = 3001,
        ID_Scroll = 4001,
        ID_TEXT_ZMIENNY = 5001
    };
};

#endif //LAB03_MYFRAME_H
