//
// Created by Bartłomiej Obrochta on 15/05/2024.
//

#ifndef LAB08_EXIFPANEL_H
#define LAB08_EXIFPANEL_H

#include<wx/wx.h>



class ExifPanel: public wxPanel {

private:
    wxBoxSizer* mainSizer;
public:
    ExifPanel(wxWindow* parent)
            : wxPanel(parent) {
        mainSizer = new wxBoxSizer(wxVERTICAL);

        this->SetBackgroundColour(wxColour(255,0,255));
        this->SetSizer(mainSizer);
        this->Layout();
        this->Fit();
    }

    void UpdateExif(std::vector<std::pair<std::string, std::string>> data)
    {

        mainSizer->Clear(true);
        for(auto& elem: data)
        {
            wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

            wxStaticText* label = new wxStaticText(this,wxID_ANY, elem.first + ":", wxDefaultPosition,wxDefaultSize);
            wxStaticText* value = new wxStaticText(this,wxID_ANY,elem.second,wxDefaultPosition,wxDefaultSize);

            rowSizer->Add(label, 0,wxALL | wxALIGN_CENTER_VERTICAL,5);
            rowSizer->Add(value, 0,wxALL | wxALIGN_CENTER_VERTICAL,5);

            mainSizer->Add(rowSizer,0,wxEXPAND);
        }

        this->Layout();
        this->Fit();
    }


};


#endif //LAB08_EXIFPANEL_H
