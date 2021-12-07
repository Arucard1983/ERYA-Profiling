#include "ERYAProfilingdialogERYAProfilingAdvanced.h"
#include "ERYAProfilingERYAProfilingMain.h"

ERYAProfilingdialogERYAProfilingAdvanced::ERYAProfilingdialogERYAProfilingAdvanced( wxWindow* parent )
:
dialogERYAProfilingAdvanced( parent )
{
 // Call the parent frame
 ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
 // Copy the current variables
 unsigned int CP,G,L,VE,VM,VA,NT,CM;
 bool EL;
 Parent->GetPrecisionParameters(CP,G,VM,VE,VA,L,NT,CM,EL);
 // And set the controls
 spinSampleStep->SetValue(0.1*CP); //Implicit conversion using 0.1e-15 at/cm^2 units.
 spinGaussPrecision->SetValue(G);
 spinLandau->SetValue(L);
 spinVavilovEdgeworth->SetValue(VE);
 spinVavilovAiry->SetValue(VA);
 spinVavilovMoyal->SetValue(VM);
 spinNumberThreads->SetSelection(NT);
 spinConvolution->SetValue(CM);
 checkActiveLog->SetValue(EL);
}

void ERYAProfilingdialogERYAProfilingAdvanced::OnAdvancedOK( wxCommandEvent& event )
{
 // Call the parent frame
 ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
 // Set the current variables
 unsigned int CP,G,L,VE,VM,VA,NT,CM;
 double CPT;
 bool EL;
 // Get the controls
 CPT = spinSampleStep->GetValue();
 G = spinGaussPrecision->GetValue();
 L = spinLandau->GetValue();
 VE = spinVavilovEdgeworth->GetValue();
 VA = spinVavilovAiry->GetValue();
 VM = spinVavilovMoyal->GetValue();
 NT = spinNumberThreads->GetSelection();
 CM = spinConvolution->GetValue();
 EL = checkActiveLog->GetValue();
 // Internal conversion
 CP = static_cast<unsigned int>(std::floor(10*CPT)); // Internal conversion
 // And save the new values
 Parent->SetPrecisionParameters(CP,G,VM,VE,VA,L,NT,CM,EL);
 // Before close
 Close();
}

void ERYAProfilingdialogERYAProfilingAdvanced::OnAdvancedDefault( wxCommandEvent& event )
{
 // And set the controls
 spinSampleStep->SetValue(10);
 spinGaussPrecision->SetValue(10);
 spinLandau->SetValue(284);
 spinVavilovEdgeworth->SetValue(70);
 spinVavilovAiry->SetValue(40);
 spinVavilovMoyal->SetValue(10);
 spinNumberThreads->SetSelection(1);
 spinConvolution->SetValue(0);
 checkActiveLog->SetValue(false);
}

void ERYAProfilingdialogERYAProfilingAdvanced::OnAdvancedCancel( wxCommandEvent& event )
{
 Close();
}

void ERYAProfilingdialogERYAProfilingAdvanced::OnAdvancedHelp( wxCommandEvent& event )
{
 // Call the parent frame
 ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
 Parent->SetPrecisionParameters(100,10,10,70,40,284,1,0,false);
 Close();
}
