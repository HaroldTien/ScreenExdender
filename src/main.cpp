#include <iostream>
#include "../include/ConnectionCodeGeneration.h"
#include <wx/wx.h>
#include "../include/MainFrame.h"

class ScreenExtenderApp : public wxApp {
public:
    bool OnInit() {
        MainFrame* mainFrame = new MainFrame("Screen Extender");
        mainFrame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(ScreenExtenderApp);