#include "MainFrame.h"
#include "ConnectionCodeGeneration.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    CreateWidgets();
}

void MainFrame::CreateWidgets()
{
    // Create main panel
    mainPanel = new wxPanel(this);
    
    // Create a vertical sizer for layout
    mainSizer = new wxBoxSizer(wxVERTICAL);
    
    
    connectionCodeLabel = new wxStaticText(mainPanel, wxID_ANY, "Connection Code:");
    connectionCodeText = new wxTextCtrl(mainPanel, wxID_ANY, ConnectionCodeGeneration(), wxDefaultPosition, wxDefaultSize,wxTE_READONLY | wxTE_CENTER);
    
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(connectionCodeLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL);
    mainSizer->Add(connectionCodeText, 0, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL,0);
    
    mainSizer->AddStretchSpacer(1);
    
    mainPanel->SetSizer(mainSizer);
}

