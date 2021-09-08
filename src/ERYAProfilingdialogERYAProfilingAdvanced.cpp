#include "ERYAProfilingdialogERYAProfilingAdvanced.h"
#include "ERYAProfilingERYAProfilingMain.h"

ERYAProfilingdialogERYAProfilingAdvanced::ERYAProfilingdialogERYAProfilingAdvanced( wxWindow* parent )
:
dialogERYAProfilingAdvanced( parent )
{
 // Call the parent frame
 ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
 // Copy the current variables
 unsigned int CP,G,L,VE,VM,VA,NT;
 bool EL;
 Parent->GetPrecisionParameters(CP,G,VM,VE,VA,L,NT,EL);
 // And set the controls
 spinSampleStep->SetValue(CP);
 spinGaussPrecision->SetValue(G);
 spinLandau->SetValue(L);
 spinVavilovEdgeworth->SetValue(VE);
 spinVavilovAiry->SetValue(VA);
 spinVavilovMoyal->SetValue(VM);
 spinNumberThreads->SetSelection(NT);
 checkActiveLog->SetValue(EL);
}

void ERYAProfilingdialogERYAProfilingAdvanced::OnAdvancedOK( wxCommandEvent& event )
{
 // Call the parent frame
 ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
 // Set the current variables
 unsigned int CP,G,L,VE,VM,VA,NT;
 bool EL;
 // Get the controls
 CP = spinSampleStep->GetValue();
 G = spinGaussPrecision->GetValue();
 L = spinLandau->GetValue();
 VE = spinVavilovEdgeworth->GetValue();
 VA = spinVavilovAiry->GetValue();
 VM = spinVavilovMoyal->GetValue();
 NT = spinNumberThreads->GetSelection();
 EL = checkActiveLog->GetValue();
 // And save the new values
 Parent->SetPrecisionParameters(CP,G,VM,VE,VA,L,NT,EL);
 // Before close
 Close();
}

void ERYAProfilingdialogERYAProfilingAdvanced::OnAdvancedDefault( wxCommandEvent& event )
{
 // And set the controls
 spinSampleStep->SetValue(10);
 spinGaussPrecision->SetValue(10);
 spinLandau->SetValue(100);
 spinVavilovEdgeworth->SetValue(40);
 spinVavilovAiry->SetValue(20);
 spinVavilovMoyal->SetValue(1);
 spinNumberThreads->SetSelection(1);
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
 Parent->SetPrecisionParameters(10,60,10,70,100,284,1,false);
 Close();
}
