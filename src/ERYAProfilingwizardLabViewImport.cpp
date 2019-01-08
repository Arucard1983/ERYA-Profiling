#include "ERYAProfilingwizardLabViewImport.h"
#include "ERYAProfilingERYAProfilingMain.h"

ERYAProfilingwizardLabViewImport::ERYAProfilingwizardLabViewImport( wxWindow* parent )
:
wizardLabViewImport( parent )
{

}

void ERYAProfilingwizardLabViewImport::OnLabViewImportCancel( wxWizardEvent& event )
{
  // Call the parent frame
 ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
 // Sync the values
 Parent->SetSync(false);
 return;
}

void ERYAProfilingwizardLabViewImport::OnLabViewImportFinish( wxWizardEvent& event )
{
 // Save the Elements Database
 wxString LabViewDatabase, ERYAProfilingDatabase;
 LabViewDatabase = fileLabViewDatabases->GetPath();
 ERYAProfilingDatabase = fileERYADatabase->GetPath();
 ElementDatabaseArray TestingDatabase;
 DatabaseFile labview(LabViewDatabase,wxT("txt"),TestingDatabase);
 if(labview.ERYAProfilingDatabaseFileLoad())
 {
  TestingDatabase.Clear();
  TestingDatabase = labview.GetDatabase();
  DatabaseFile eryaprofiling(ERYAProfilingDatabase,wxT("epd"),TestingDatabase);
  if(eryaprofiling.ERYAProfilingDatabaseFileSave())
  {
   TestingDatabase.Clear();
  }
  else
  {
   TestingDatabase.Clear();
    // Call the parent frame
    ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
    // Sync the values
    Parent->SetSync(false);
    return;
  }
 }
 else
 {
  TestingDatabase.Clear();
  // Call the parent frame
  ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
  // Sync the values
  Parent->SetSync(false);
  return;
 }

 // Save the Detector Profile
 wxString LabViewDetector, ERYAProfilingDetector;
 LabViewDetector = fileLabViewDetector->GetPath();
 ERYAProfilingDetector = fileERYADetector->GetPath();
 DetectorParameters TestingDetector;
 DetectorFile labview1(LabViewDetector,wxT("txt"),TestingDetector);
 if(labview1.DetectorFileLoad())
 {
  TestingDetector.Clear();
  TestingDetector = labview1.GetParameters();
  DetectorFile eryaprofiling1(ERYAProfilingDetector,wxT("epsd"),TestingDetector);
  if(eryaprofiling1.DetectorFileSave())
  {
   TestingDetector.Clear();
  }
  else
  {
   TestingDetector.Clear();
    // Call the parent frame
    ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
    // Sync the values
    Parent->SetSync(false);
    return;
  }
 }
 else
 {
  TestingDetector.Clear();
  // Call the parent frame
  ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
  // Sync the values
  Parent->SetSync(false);
  return;
 }

 // Saving the Ziegler Parameters
 wxString LabViewZiegler, LabViewDensity, LabViewBloch, ERYAProfilingZiegler;
 LabViewZiegler = fileLabViewZiegler->GetPath();
 LabViewDensity = fileLabViewDensity->GetPath();
 LabViewBloch = fileLabViewBloch->GetPath();
 ERYAProfilingZiegler = fileERYAZiegler->GetPath();
 ZieglerParameters TestingZiegler;
 ElementSRIMArray DummyZiegler;
 ZieglerFile labview2(LabViewZiegler,wxT("txt"),TestingZiegler,DummyZiegler,0);
 if(labview2.ZieglerFileLoad())
 {
  TestingZiegler.Clear();
  TestingZiegler = labview2.GetParameters();
  // Extract the data from text files
  wxArrayString ListDensity,ListBloch;
  wxTextFile density(LabViewDensity);
  wxTextFile bloch(LabViewBloch);
  density.Open();
  bloch.Open();
  for(int a=0; a<density.GetLineCount(); a++)
  {
   wxString temp = density.GetLine(a);
   if(temp.Trim().Len()>0) //Skip empty lines
   {
    TextLineParser test(temp,wxEmptyString);
   wxString check = test.GetAllTokens().Last();
   if(check.Trim().Len()>0)
    ListDensity.Add(check);
   else
    ListDensity.Add(wxString::Format("%.8f",1.0));
   }
  }
  for(int b=0; b<bloch.GetLineCount(); b++)
  {
   wxString temp = bloch.GetLine(b);
   if(temp.Trim().Len()>0)
   {
    TextLineParser test(temp,wxEmptyString);
   wxString check = test.GetAllTokens().Last();
   if(check.Trim().Len()>0)
    ListBloch.Add(check);
   else
    ListBloch.Add(wxString::Format("%.8f",10.0));
   }
  }
  density.Close();
  bloch.Close();
  // Update Ziegler Parameters
  TestingZiegler.FixElementNames();
  TestingZiegler.FixDensity(ListDensity);
  TestingZiegler.FixBloch(ListBloch);
  ZieglerFile eryaprofiling2(ERYAProfilingZiegler,wxT("epsz"),TestingZiegler,DummyZiegler,0);
  if(eryaprofiling2.ZieglerFileSave())
  {
   TestingZiegler.Clear();
  }
  else
  {
   TestingZiegler.Clear();
    // Call the parent frame
    ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
    // Sync the values
    Parent->SetSync(false);
    return;
  }
 }
 else
 {
  TestingZiegler.Clear();
  // Call the parent frame
  ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
  // Sync the values
  Parent->SetSync(false);
  return;
 }
 // Return OK
 // Call the parent frame
    ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
    // Sync the values
    Parent->SetSync(true);
    return;
}
