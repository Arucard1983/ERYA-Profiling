#include "ERYAProfilingdialogRemark.h"
#include "ERYAProfilingdialogAddDatabase.h"
#include "ERYAProfilingdialogDatabaseManager.h"
#include "ERYAProfilingdialogDetectorSetup.h"
#include "ERYAProfilingdialogZieglerParameters.h"

ERYAProfilingdialogRemark::ERYAProfilingdialogRemark( wxWindow* parent )
:
dialogRemark( parent )
{

}

ERYAProfilingdialogRemark::ERYAProfilingdialogRemark( wxWindow* parent, wxString info, int n )
:
dialogRemark( parent )
{
 textRemark->SetValue(info);
 FlagValue = n;
}

void ERYAProfilingdialogRemark::OnRemarkSave( wxCommandEvent& event )
{
 // Call the parent frame
if(FlagValue==0)
{
 ERYAProfilingdialogAddDatabase *Parent = (ERYAProfilingdialogAddDatabase *) GetParent();
 wxString data = textRemark->GetValue();
 Parent->SetRemark(data);
 Close();
}
else if(FlagValue==1)
{
 ERYAProfilingdialogDatabaseManager *Parent = (ERYAProfilingdialogDatabaseManager *) GetParent();
 wxString data = textRemark->GetValue();
 Parent->SetRemark(data);
 Close();
}
else if(FlagValue==2)
{
 ERYAProfilingdialogDetectorSetup *Parent = (ERYAProfilingdialogDetectorSetup *) GetParent();
 wxString data = textRemark->GetValue();
 Parent->SetRemark(data);
 Close();
}
else if(FlagValue==3)
{
 ERYAProfilingdialogZieglerParameters *Parent = (ERYAProfilingdialogZieglerParameters *) GetParent();
 wxString data = textRemark->GetValue();
 Parent->SetRemark(data);
 Close();
}
else
{
 Close();
}
}

void ERYAProfilingdialogRemark::OnRemarkClear( wxCommandEvent& event )
{
 textRemark->Clear();
}

void ERYAProfilingdialogRemark::OnRemarkQuit( wxCommandEvent& event )
{
 Close();
}
