#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    void CreateWidgets();

    // GUI elements
    wxPanel* mainPanel;
    wxButton* connectButton;
    wxStaticText* connectionCodeLabel;
    wxTextCtrl* connectionCodeText;
    wxBoxSizer* mainSizer;
    
};