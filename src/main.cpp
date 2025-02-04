#include <iostream>
#include "../include/ConnectionCodeGeneration.h"
#include <wx/wx.h>
#include "../include/capturing.h"
#include "../include/Communication.h"
#include <wx/thread.h>

class ConnectionThread : public wxThread {
public:
    ConnectionThread() : wxThread(wxTHREAD_DETACHED) {}

protected:
    virtual ExitCode Entry() {
        try {
            CommunicationServer communicationServer(8080);
            communicationServer.EstablishConnection();
            std::string wallPaperPath = getWallPaperPath();
        } catch (const std::exception& e) {
            std::cerr << "Error initializing connection: " << e.what() << std::endl;
        }
        return nullptr;
    }
};

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
        // Create main panel
        wxPanel* mainPanel = new wxPanel(this);

        // Create a vertical sizer for layout
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* connectionCodeLabel = new wxStaticText(mainPanel, wxID_ANY, "Connection Code:");
        wxTextCtrl* connectionCodeText = new wxTextCtrl(mainPanel, wxID_ANY, ConnectionCodeGeneration(8080),
            wxDefaultPosition, wxSize(200, -1), wxTE_READONLY | wxTE_CENTER);

        wxFont font;
        font.SetPointSize(16); // You can adjust this number to change text size
        connectionCodeText->SetFont(font);

        mainSizer->AddStretchSpacer(1);
        mainSizer->Add(connectionCodeLabel, 0, wxALL | wxALIGN_CENTER, 5);
        mainSizer->Add(connectionCodeText, 0, wxALL | wxEXPAND, 5);
        mainSizer->AddStretchSpacer(1);

        mainPanel->SetSizer(mainSizer);
    }
};

class ScreenExtenderApp : public wxApp {
public:
    bool OnInit() {
        std::cout << "Running custom initialization code..." << std::endl;
        initializeResources();

        MainFrame* mainFrame = new MainFrame("Screen Extender");
        mainFrame->Show();

        // Start the connection thread
        ConnectionThread* connectionThread = new ConnectionThread();
        if (connectionThread->Run() != wxTHREAD_NO_ERROR) {
            std::cerr << "Failed to start connection thread." << std::endl;
            delete connectionThread;
        }

        return true;
    }

private:
    void initializeResources() {
        std::cout << "Resources initialized." << std::endl;
    }
};

wxIMPLEMENT_APP(ScreenExtenderApp);