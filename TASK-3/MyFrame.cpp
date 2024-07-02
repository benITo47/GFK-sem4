//
// Created by Bartłomiej Obrochta on 02/04/2024.
//

#include "MyFrame.h"
#include "wx/wx.h"

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    customPanel = new MonkeyPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString choices;
    choices.Add("Gwiazda");
    choices.Add("Księżyc");
    choices.Add("Słońce");
    choiceControl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
    choiceControl->SetSelection(0);

    ZapiszButton = new wxButton(this, ID_Zapis, "Zapisz do pliku");
    KolorSymbolu = new wxButton(this, ID_Kolor, "Kolor");
    CheckBox = new wxCheckBox(this, ID_CheckBox, "Banan");
    ScrollBar = new wxScrollBar(this, ID_Scroll);
    gauge = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
    text = new wxTextCtrl(this, ID_TEXT_ZMIENNY, _("Tekst"));

    sizer->Add(ZapiszButton, 1, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    sizer->Add(CheckBox, 1, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    sizer->Add(ScrollBar, 1, wxEXPAND | wxTOP, 10);
    sizer->Add(gauge, 1, wxEXPAND | wxTOP, 10);
    sizer->Add(KolorSymbolu, 1, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    sizer->Add(text, 1, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    sizer->Add(choiceControl, 1, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(customPanel, 7, wxEXPAND | wxALL, 5);
    mainSizer->Add(sizer, 3, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    SetSizerAndFit(mainSizer);

    ScrollBar->Enable(false);
    ScrollBar->SetThumbSize(1);
    ScrollBar->SetScrollbar(0, 0, 100, 10);

    Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame::OnScroll, this, ID_Scroll);
    Bind(wxEVT_CHECKBOX, &MyFrame::WxCheckBox1_Click, this, ID_CheckBox);
    Bind(wxEVT_BUTTON, &MyFrame::ZapiszDoPliku, this, ID_Zapis);
    Bind(wxEVT_BUTTON, &MyFrame::ColorPick, this, ID_Kolor);
    Bind(wxEVT_CHOICE, &MyFrame::OnChoice, this);
    Bind(wxEVT_TEXT, &MyFrame::TextUpdate, this, ID_TEXT_ZMIENNY);
    Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnExit, this);

    SetMinSize(wxSize(500, 500));
    Centre();
    Show(true);
}

void MyFrame::OnExit(wxCloseEvent& event) {
    if (wxMessageDialog(NULL, "Czy na pewno chcesz zamknąć?", "Pytanie", wxOK | wxCANCEL).ShowModal() == wxID_OK)
        Destroy();
}

void MyFrame::ZapiszDoPliku(wxCommandEvent& event) {
    wxClientDC dc(customPanel);
    wxSize panelSize = customPanel->GetSize();
    wxBitmap bitmapka(panelSize);

    wxMemoryDC memDC;
    memDC.SelectObject(bitmapka);
    memDC.Blit(0, 0, panelSize.GetWidth(), panelSize.GetHeight(), &dc, 0, 0);

    wxString filename = wxFileSelector("Save As", "", "", "png", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT, this);
    if (!filename.empty()) {
        wxBitmapType type = wxBITMAP_TYPE_PNG;
        bitmapka.SaveFile(filename, type);
    }
}

void MyFrame::OnScroll(wxScrollEvent& event) {
    int scroll_pos = customPanel->ArmUpValue = ScrollBar->GetThumbPosition();
    gauge->SetValue(scroll_pos);
    gauge->SetRange(100);
    customPanel->Refresh();
}

void MyFrame::WxCheckBox1_Click(wxCommandEvent& event) {
    if (!ScrollBar->IsEnabled()) {
        ScrollBar->Enable(true);
        customPanel->eyes = true;
    }
    else {
        ScrollBar->Enable(false);
         customPanel->eyes = false;
    }
    customPanel->Refresh();
}

void MyFrame::OnChoice(wxCommandEvent& event) {
    customPanel->SymbolChoice = choiceControl->GetSelection();
    customPanel->Refresh();
}

void MyFrame::ColorPick(wxCommandEvent& event) {
    wxColourDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        wxColourData data = dialog.GetColourData();
        wxColour color = data.GetColour();
        customPanel->RGB[0] = color.Red();
        customPanel->RGB[1] = color.Green();
        customPanel->RGB[2] = color.Blue();
        customPanel->Refresh();
    }
}

void MyFrame::TextUpdate(wxCommandEvent& event) {
    customPanel->DisplayText = text->GetValue();
    customPanel->Refresh();
}
