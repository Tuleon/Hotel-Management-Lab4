#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace HotelApp;

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MainForm());
}