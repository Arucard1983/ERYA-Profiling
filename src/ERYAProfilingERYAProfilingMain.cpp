#include "ERYAProfilingERYAProfilingMain.h"
#include "ERYAProfilingdialogDatabaseManager.h"
#include "ERYAProfilingdialogDetectorSetup.h"
#include "ERYAProfilingdialogZieglerParameters.h"
#include "ERYAProfilingdialogHelp.h"
#include "ERYAProfilingdialogERYACalculator.h"
#include "ERYAProfilingwizardFirstRun.h"
#include "ERYAProfilingwizardLabViewImport.h"
#include "ERYAProfilingdialogSetup.h"
#include "ERYAProfilingdialogERYAProfilingAdvanced.h"
#include "ERYAProfilingwizardSRIMImport.h"

ERYAProfilingERYAProfilingMain::ERYAProfilingERYAProfilingMain( wxWindow* parent )
:
ERYAProfilingMain( parent )
{
 if(this->StartUpProgram())
 {
  statusERYAProfiling->SetStatusText(wxT("ERYA-Profiling is ready...") ,0);
 }
 else
 {
  statusERYAProfiling->SetStatusText(wxT("Warning! ERYA Profiling starts in Default Mode") ,0);
 }
}

void ERYAProfilingERYAProfilingMain::OnFileNew( wxCommandEvent& event )
{
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Do you really create a new file?\nAll inserted or unsaved data will be lost."), wxT("Start a New File?"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
 if (dial->ShowModal() == wxID_YES)
 {
 this->GenerateTable();
 this->GenerateLayer();
 this->GenerateResult();
 this->GenerateLog();
 gridLayerEditor->ClearGrid();
 renderOutputData->DelAllLayers(false,true);
 textBeamEnergy->Clear();
 textTemperature->Clear();
 textCharge->Clear();
 textEnergyStep->Clear();
 textMaximumEnergy->Clear();
 textMinimumEnergy->Clear();
 textRessonanceWidth->Clear();
 textRessonancePeak->Clear();
 textRessonanceEnergy->Clear();
 checkRessonanceRange->SetValue(false);
 textRessonanceMinimum->Clear();
 textRessonanceMaximum->Clear();
 textCustomRessonance->Clear();
 radioRessonanceOption->SetSelection(0);
 }
}

void ERYAProfilingERYAProfilingMain::OnFileOpen( wxCommandEvent& event )
{
 wxFileDialog *OpenDialog = new wxFileDialog(this, wxT("Open a ERYA Profiling File from..."), wxEmptyString, wxEmptyString, wxT("ERYA Profiling Global Sample (*.epgs)|*.epgs"), wxFD_OPEN, wxDefaultPosition);
 if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "cancel"
{
 wxString CurrentERYAProfilingFilePath = OpenDialog->GetPath(); // Get absolute path of selected file
 wxFileName file(CurrentERYAProfilingFilePath);
 if(file.GetExt() == wxT("epgs"))
 {
  ERYAProfilingGlobalFile openfile(CurrentERYAProfilingFilePath);
  wxArrayString Elements,GammaPeaks,Numbers,Abundance,Isotopic,Atomic,LayerTableData;
  int ActualMode;
  unsigned int ActiveLog;
  bool IsLorentzian;
  if(openfile.ERYAProfilingGlobalLoad(textBeamEnergy,textTemperature,textCharge,textEnergyStep,textMinimumEnergy,textMaximumEnergy,textRessonanceWidth,textRessonancePeak,textRessonanceEnergy,textRessonanceMinimum,textRessonanceMaximum,textCustomRessonance,IsLorentzian,ActualMode,Elements,GammaPeaks,Numbers,Abundance,Isotopic,Atomic,LayerTableData,OpenDatabase,SamplePrecision,GaussPrecision,VavilovMoyalPrecision,VavilovEdgeworthPrecision,LandauPrecision,ThreadPrecision,ActiveLog))
  {
   this->GenerateTable(Elements.GetCount());
   for(int k=0; k<Elements.GetCount(); k++)
   {
    OpenDatabase.FindGetAllElementInfo(Elements.Item(k), GammaPeaks.Item(k), choiceElementName.Item(k), choiceGammaPeak.Item(k), textAtomicNumber.Item(k), textAbundance.Item(k), textAtomicMass.Item(k), textIsotopicMass.Item(k));
    if(Numbers.Item(k).Len() > 0)
     textAtomicNumber.Item(k)->SetValue(Numbers.Item(k));
    if(Abundance.Item(k).Len() > 0)
     textAbundance.Item(k)->SetValue(Abundance.Item(k));
    if(Isotopic.Item(k).Len() > 0)
     textIsotopicMass.Item(k)->SetValue(Isotopic.Item(k));
    if(Atomic.Item(k).Len() > 0)
     textAtomicMass.Item(k)->SetValue(Atomic.Item(k));
   }
   this->GenerateLayer();
   this->GenerateLayer(LayerTableData.GetCount()/(Elements.GetCount()+1));
     //Load the table contents
     for(int k=0; k<LayerTableData.GetCount(); k++)
     {
      int i = k / gridLayerEditor->GetNumberCols();
      int j = k % gridLayerEditor->GetNumberCols();
      gridLayerEditor->SetCellValue(i,j,LayerTableData.Item(k));
     }
   checkRessonanceRange->SetValue(IsLorentzian);
   radioRessonanceOption->SetSelection(ActualMode);
   if (ActiveLog == 0)
     EnableLog = false;
   else
     EnableLog = true;
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot read this file."), wxT("Error: Invalid ERYA file"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
 else
 {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot read this file."), wxT("Error: Invalid file"), wxOK | wxICON_ERROR);
   dial->ShowModal();
 }
}
OpenDialog->Destroy();
}

void ERYAProfilingERYAProfilingMain::OnFileSave( wxCommandEvent& event )
{
 wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Save the Current Ressonance Profile as..."), wxEmptyString, wxEmptyString,wxT("ERYA Profiling Global Sample (*.epgs)|*.epgs"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("epgs"))
  {
    ERYAProfilingGlobalFile file(CurrentERYAProfilingFilePath);
    unsigned int ActiveLog;
    if (EnableLog)
        ActiveLog = 1;
    else
        ActiveLog = 0;
    if(!(file.ERYAProfilingGlobalSave(textBeamEnergy,textTemperature,textCharge,textEnergyStep,textMinimumEnergy,textMaximumEnergy,textRessonanceWidth,textRessonancePeak,textRessonanceEnergy,textRessonanceMinimum,textRessonanceMaximum,textCustomRessonance,checkRessonanceRange->GetValue(),radioRessonanceOption->GetSelection(),choiceElementName,choiceGammaPeak,textAtomicNumber,textAbundance,textIsotopicMass,textAtomicMass,gridLayerEditor,OpenDatabase,SamplePrecision,GaussPrecision,VavilovMoyalPrecision,VavilovEdgeworthPrecision,LandauPrecision,ThreadPrecision,ActiveLog)))
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected error when ERYA-Profiling try to write file."), wxT("Error on file save!"), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot save the current file on unsupported formats!"), wxT("Error: Invalid File Extention!"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnFileSaveAs( wxCommandEvent& event )
{
 wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Save the Current Ressonance Profile as..."), wxEmptyString, wxEmptyString,wxT("ERYA Profiling Global Sample (*.epgs)|*.epgs"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("epgs"))
  {
    ERYAProfilingGlobalFile file(CurrentERYAProfilingFilePath);
    unsigned int ActiveLog;
    if (EnableLog)
        ActiveLog = 1;
    else
        ActiveLog = 0;
    if(!(file.ERYAProfilingGlobalSave(textBeamEnergy,textTemperature,textCharge,textEnergyStep,textMinimumEnergy,textMaximumEnergy,textRessonanceWidth,textRessonancePeak,textRessonanceEnergy,textRessonanceMinimum,textRessonanceMaximum,textCustomRessonance,checkRessonanceRange->GetValue(),radioRessonanceOption->GetSelection(),choiceElementName,choiceGammaPeak,textAtomicNumber,textAbundance,textIsotopicMass,textAtomicMass,gridLayerEditor,OpenDatabase,SamplePrecision,GaussPrecision,VavilovMoyalPrecision,VavilovEdgeworthPrecision,LandauPrecision,ThreadPrecision,ActiveLog)))
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected error when ERYA-Profiling try to write file."), wxT("Error on file save!"), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot save the current file on unsupported formats!"), wxT("Error: Invalid File Extention!"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnFileQuit( wxCommandEvent& event )
{
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Do you want to quit?\nAll opened data will be lost."), wxT("Quit?"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
 if (dial->ShowModal() == wxID_YES)
 {
 Close();
 }
}

void ERYAProfilingERYAProfilingMain::OnDatabaseDetector( wxCommandEvent& event )
{
 ERYAProfilingdialogDetectorSetup* detector = new ERYAProfilingdialogDetectorSetup(this);
 detector->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnDatabaseElements( wxCommandEvent& event )
{
 ERYAProfilingdialogDatabaseManager* database = new ERYAProfilingdialogDatabaseManager(this);
 database->ShowModal();

 // Refresh the main page
 if (ResetDatabase)
 {
  for(int k=0; k<choiceElementName.GetCount(); k++)
  {
   OpenDatabase.ResetElementGammaMenu(choiceElementName.Item(k),choiceGammaPeak.Item(k));
   OpenDatabase.FindGetAllElementInfo(choiceElementName.Item(k)->GetString(0),choiceGammaPeak.Item(k)->GetString(0), choiceElementName.Item(k), choiceGammaPeak.Item(k), textAtomicNumber.Item(k), textAbundance.Item(k), textAtomicMass.Item(k), textIsotopicMass.Item(k));
  }
  this->GenerateLayer();
 }
}

void ERYAProfilingERYAProfilingMain::OnDatabaseZiegler( wxCommandEvent& event )
{
 ERYAProfilingdialogZieglerParameters* ziegler = new ERYAProfilingdialogZieglerParameters(this);
 ziegler->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnSetupDefault( wxCommandEvent& event )
{
 ERYAProfilingdialogSetup* setup = new ERYAProfilingdialogSetup(this);
 setup->ShowModal();
 if(CloseProgram)
 {
  if(this->StartUpProgram())
    {
     statusERYAProfiling->SetStatusText(wxT("ERYA-Profiling is ready...") ,0);
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("A new ERYA-Profiling Configuration was done!\nThe new settings are now in use!"), wxT("Reset Complete!"), wxOK);
      dial->ShowModal();
    }
    else
    {
     statusERYAProfiling->SetStatusText(wxT("Warning! ERYA Profiling starts in Default Mode") ,0);
    }
 }
}

void ERYAProfilingERYAProfilingMain::OnSetupReset( wxCommandEvent& event )
{
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Do you want to reset the ERYA-Profiling configuration files?\nIt will start a new Setup Wizard..."), wxT("Reset ERYA-Profiling configurations?"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
 if (dial->ShowModal() == wxID_YES)
 {
  if(this->DeleteSetupFile())
  {
    if(this->StartUpProgram())
    {
     this->GenerateTable();
     this->GenerateLayer();
     this->GenerateResult();
     this->GenerateLog();
     statusERYAProfiling->SetStatusText(wxT("ERYA-Profiling is ready...") ,0);
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("A new ERYA-Profiling Configuration was done!\nThe new settings are now in use!"), wxT("Reset Complete!"), wxOK);
      dial->ShowModal();
    }
    else
    {
     statusERYAProfiling->SetStatusText(wxT("Warning! ERYA Profiling starts in Default Mode") ,0);
    }
  }
  else
  {
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Cannot reset ERYA Profiling.\nRefer to the User Guide about\nhow to perform a manual reset."), wxT("Reset Error!"), wxOK | wxICON_ERROR);
  dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnSRIMImport( wxCommandEvent& event )
{
 ERYAProfilingwizardSRIMImport *srimwizard = new ERYAProfilingwizardSRIMImport(this);
 srimwizard->StartWizard(); //Start the wizard at the first page...
 srimwizard->Destroy();
 if(AcceptSync)
 {
  wxMessageBox(wxT("SRIM Stopping-Power Import successful!"));
 }
 else
 {
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The SRIM Stopping-Power import was aborted by the user."), wxT("Error!"), wxOK | wxICON_ERROR);
  dial->ShowModal();
 }
}

void ERYAProfilingERYAProfilingMain::OnLabViewImport( wxCommandEvent& event )
{
 ERYAProfilingwizardLabViewImport *labviewwizard = new ERYAProfilingwizardLabViewImport(this);
 labviewwizard->StartWizard(); //Start the wizard at the first page...
 labviewwizard->Destroy();
 if(AcceptSync)
 {
  wxMessageBox(wxT("LabView ERYA Database Import successful!"));
 }
 else
 {
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid or Unsupported LabView ERYA Database."), wxT("Error!"), wxOK | wxICON_ERROR);
  dial->ShowModal();
 }
}

void ERYAProfilingERYAProfilingMain::OnCalculator( wxCommandEvent& event )
{
 ERYAProfilingdialogERYACalculator *calculator = new ERYAProfilingdialogERYACalculator(this);
 calculator->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnHelpManual( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("MainManual.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnHelpAbout( wxCommandEvent& event )
{
 wxMessageBox(wxT("ERYA-Profiling Version 2.40\nBuilt with wxWidgets 3.0.4, with wxMathPlot 0.13 and Custom Simple Xlsx Library 0.1\nCompiling with GCC 6.3.0\n(c) 2018 LIBPHYS"), wxT("Welcome to ERYA Profiling"));
}

void ERYAProfilingERYAProfilingMain::OnNumberElementSpin( wxSpinEvent& event )
{
 int Number = spinNumberElements->GetValue();
 this->GenerateTable(Number);
 this->GenerateResult();
 this->GenerateLog();
}

void ERYAProfilingERYAProfilingMain::OnNumberElementEnter( wxCommandEvent& event )
{
 int Number = spinNumberElements->GetValue();
 this->GenerateTable(Number);
 this->GenerateResult();
 this->GenerateLog();
}

void ERYAProfilingERYAProfilingMain::OnElementClear( wxCommandEvent& event )
{
 this->GenerateTable();
 this->GenerateResult();
 this->GenerateLog();
}

void ERYAProfilingERYAProfilingMain::OnElementLoad( wxCommandEvent& event )
{
 wxFileDialog *OpenDialog = new wxFileDialog(this, wxT("Open an Elements Sample from..."), wxEmptyString, wxEmptyString, wxT("ERYA Profiling Compound Sample (*.epcs)|*.epcs|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx"), wxFD_OPEN, wxDefaultPosition);
 if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "cancel"
{
 wxString CurrentERYAProfilingFilePath = OpenDialog->GetPath(); // Get absolute path of selected file
 wxFileName file(CurrentERYAProfilingFilePath);
 if(file.GetExt() == wxT("epcs"))
 {
  ERYAProfilingSampleFile openfile(CurrentERYAProfilingFilePath);
  wxArrayString Elements,GammaPeaks,Numbers,Abundance,Isotopic,Atomic;
  if(openfile.ERYAProfilingSampleLoad(Elements,GammaPeaks,Numbers,Abundance,Isotopic,Atomic,OpenDatabase))
  {
   this->GenerateTable(Elements.GetCount());
   for(int k=0; k<choiceElementName.GetCount(); k++)
   {
    OpenDatabase.FindGetAllElementInfo(Elements.Item(k), GammaPeaks.Item(k), choiceElementName.Item(k), choiceGammaPeak.Item(k), textAtomicNumber.Item(k), textAbundance.Item(k), textAtomicMass.Item(k), textIsotopicMass.Item(k));
    if(Numbers.Item(k).Len() > 0)
     textAtomicNumber.Item(k)->SetValue(Numbers.Item(k));
    if(Abundance.Item(k).Len() > 0)
     textAbundance.Item(k)->SetValue(Abundance.Item(k));
    if(Isotopic.Item(k).Len() > 0)
     textIsotopicMass.Item(k)->SetValue(Isotopic.Item(k));
    if(Atomic.Item(k).Len() > 0)
     textAtomicMass.Item(k)->SetValue(Atomic.Item(k));
   }
   this->GenerateLayer();
   this->GenerateResult();
   this->GenerateLog();
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot read this file."), wxT("Error: Invalid ERYA file"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
 else if(file.GetExt() == wxT("xlsx"))
 {
  ERYAProfilingSampleFile openfile(CurrentERYAProfilingFilePath);
  wxArrayString Elements,GammaPeaks,Numbers,Abundance,Isotopic,Atomic;
  if(openfile.ERYAProfilingSampleXlsxLoad(Elements,GammaPeaks,Numbers,Abundance,Isotopic,Atomic,OpenDatabase))
  {
   this->GenerateTable(Elements.GetCount());
   for(int k=0; k<choiceElementName.GetCount(); k++)
   {
    OpenDatabase.FindGetAllElementInfo(Elements.Item(k), GammaPeaks.Item(k), choiceElementName.Item(k), choiceGammaPeak.Item(k), textAtomicNumber.Item(k), textAbundance.Item(k), textAtomicMass.Item(k), textIsotopicMass.Item(k));
    if(Numbers.Item(k).Len() > 0)
     textAtomicNumber.Item(k)->SetValue(Numbers.Item(k));
    if(Abundance.Item(k).Len() > 0)
     textAbundance.Item(k)->SetValue(Abundance.Item(k));
    if(Isotopic.Item(k).Len() > 0)
     textIsotopicMass.Item(k)->SetValue(Isotopic.Item(k));
    if(Atomic.Item(k).Len() > 0)
     textAtomicMass.Item(k)->SetValue(Atomic.Item(k));
   }
   this->GenerateLayer();
   this->GenerateResult();
   this->GenerateLog();
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot read this file."), wxT("Error: Invalid Excel file"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
 else
 {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot read this file."), wxT("Error: Invalid file"), wxOK | wxICON_ERROR);
   dial->ShowModal();
 }
}
OpenDialog->Destroy();
}

void ERYAProfilingERYAProfilingMain::OnElementSave( wxCommandEvent& event )
{
 wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Save the Current Elements Compound as..."), wxEmptyString, wxEmptyString,wxT("ERYA Profiling Compound Sample (*.epcs)|*.epcs|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("epcs"))
  {
    ERYAProfilingSampleFile file(CurrentERYAProfilingFilePath);
    file.ERYAProfilingSampleSave(choiceElementName,choiceGammaPeak,textAtomicNumber,textAbundance,textIsotopicMass,textAtomicMass,OpenDatabase);
  }
  else if(Version == wxT("xlsx"))
  {
    ERYAProfilingSampleFile file(CurrentERYAProfilingFilePath);
    file.ERYAProfilingSampleXlsxSave(choiceElementName,choiceGammaPeak,textAtomicNumber,textAbundance,textIsotopicMass,textAtomicMass,OpenDatabase);
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot save the current file on unsupported formats!"), wxT("Error: Invalid File Extention!"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnElementHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("ElementProfiler.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnElementNameChoice( wxCommandEvent& event )
{
 for(int k=0; k<choiceElementName.GetCount(); k++)
 {
  int i = choiceElementName.Item(k)->GetSelection();
  if(OpenDatabase.RebuildElementGammaMenu(choiceElementName.Item(k), choiceGammaPeak.Item(k), i))
   {
    choiceElementName.Item(k)->SetSelection(i);
    choiceGammaPeak.Item(k)->SetSelection(0);
    int ElementAdress = OpenDatabase.FindElement(choiceElementName.Item(k)->GetString(i),choiceGammaPeak.Item(k)->GetString(0));
    textAtomicNumber.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetNumber());
    textAbundance.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetAbundance());
    textAtomicMass.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetAtomic());
    textIsotopicMass.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetIsotopic());
   }
   else
   {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The Element Database consistency are damaged. Please, reload with a new one."), wxT("Database is Corrupted!"), wxOK | wxICON_ERROR);
     dial->ShowModal();
   }
 }
 this->GenerateLayer();
}

void ERYAProfilingERYAProfilingMain::OnGammaPeakChoice( wxCommandEvent& event )
{
 for(int k=0; k<choiceElementName.GetCount(); k++)
 {
  int i = choiceElementName.Item(k)->GetSelection();
  int j = choiceGammaPeak.Item(k)->GetSelection();
  if(OpenDatabase.RebuildElementGammaMenu(choiceElementName.Item(k), choiceGammaPeak.Item(k), i))
   {
    choiceElementName.Item(k)->SetSelection(i);
    choiceGammaPeak.Item(k)->SetSelection(j);
    int ElementAdress = OpenDatabase.FindElement(choiceElementName.Item(k)->GetString(i),choiceGammaPeak.Item(k)->GetString(j));
    textAtomicNumber.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetNumber());
    textAbundance.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetAbundance());
    textAtomicMass.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetAtomic());
    textIsotopicMass.Item(k)->SetValue(OpenDatabase.Item(ElementAdress).GetIsotopic());
   }
   else
   {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The Element Database consistency are damaged. Please, reload with a new one."), wxT("Database is Corrupted!"), wxOK | wxICON_ERROR);
     dial->ShowModal();
   }
 }
 this->GenerateLayer();
}

void ERYAProfilingERYAProfilingMain::OnNumberLayerSpin( wxSpinEvent& event )
{
 int Number = spinNumberLayers->GetValue();
 this->GenerateLayer(Number);
}

void ERYAProfilingERYAProfilingMain::OnNumberLayerEnter( wxCommandEvent& event )
{
 int Number = spinNumberLayers->GetValue();
 this->GenerateLayer(Number);
}

void ERYAProfilingERYAProfilingMain::OnLayerClear( wxCommandEvent& event )
{
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Do you want to clear all numerical data inside the Layers Spreadsheet?"), wxT("Clear the entire Layer Contents?"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
 if (dial->ShowModal() == wxID_YES)
 {
  gridLayerEditor->ClearGrid();
 }
}

void ERYAProfilingERYAProfilingMain::OnLayerLoad( wxCommandEvent& event )
{
 wxFileDialog *OpenDialog = new wxFileDialog(this, wxT("Open a Layer Sample from..."), wxEmptyString, wxEmptyString, wxT("ERYA Profiling Layer Sample (*.epls)|*.epls|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx|Generic ASCII text file(*.txt)|*.txt"), wxFD_OPEN, wxDefaultPosition);
 if (OpenDialog->ShowModal() == wxID_OK)
 {
 wxString CurrentERYAProfilingFilePath = OpenDialog->GetPath(); // Get absolute path of selected file
 wxFileName file(CurrentERYAProfilingFilePath);
 wxString Version = file.GetExt();
  if(Version == wxT("epls"))
  {
    ERYAProfilingLayerFile file(CurrentERYAProfilingFilePath);
    wxArrayString ListElementNames, ListGammaPeaks, ListTableData;
    if(file.ERYAProfilingLayerLoad(ListElementNames,ListGammaPeaks,ListTableData,OpenDatabase))
    {
     //Create the table
     this->GenerateTable(ListElementNames.GetCount());
     for(int k=0; k<ListElementNames.GetCount(); k++)
     {
      OpenDatabase.FindGetAllElementInfo(ListElementNames.Item(k), ListGammaPeaks.Item(k), choiceElementName.Item(k), choiceGammaPeak.Item(k), textAtomicNumber.Item(k), textAbundance.Item(k), textAtomicMass.Item(k), textIsotopicMass.Item(k));
     }
     this->GenerateLayer();
     this->GenerateLayer(ListTableData.GetCount()/(ListElementNames.GetCount()+1));
     this->GenerateResult();
     this->GenerateLog();
     //Load the table contents
     for(int k=0; k<ListTableData.GetCount(); k++)
     {
      int i = k / gridLayerEditor->GetNumberCols();
      int j = k % gridLayerEditor->GetNumberCols();
      gridLayerEditor->SetCellValue(i,j,ListTableData.Item(k));
     }
    }
    else
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Error: Unexpected file structure format."), wxT("Error loading file."), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else if(Version == wxT("xlsx"))
  {
    ERYAProfilingLayerFile file(CurrentERYAProfilingFilePath);
    wxArrayString ListElementNames, ListGammaPeaks, ListTableData;
    if(file.ERYAProfilingLayerXlsxLoad(ListElementNames,ListGammaPeaks,ListTableData,OpenDatabase))
    {
     //Create the table
     this->GenerateTable(ListElementNames.GetCount());
     for(int k=0; k<ListElementNames.GetCount(); k++)
     {
      OpenDatabase.FindGetAllElementInfo(ListElementNames.Item(k), ListGammaPeaks.Item(k), choiceElementName.Item(k), choiceGammaPeak.Item(k), textAtomicNumber.Item(k), textAbundance.Item(k), textAtomicMass.Item(k), textIsotopicMass.Item(k));
     }
     this->GenerateLayer();
     this->GenerateLayer(ListTableData.GetCount()/(ListElementNames.GetCount()+1));
     this->GenerateResult();
     this->GenerateLog();
     //Load the table contents
     for(int k=0; k<ListTableData.GetCount(); k++)
     {
      int i = k / gridLayerEditor->GetNumberCols();
      int j = k % gridLayerEditor->GetNumberCols();
      gridLayerEditor->SetCellValue(i,j,ListTableData.Item(k));
     }
    }
    else
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Error: Unexpected file structure format."), wxT("Error loading file."), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else if(Version == wxT("txt"))
  {
    ERYAProfilingLayerFile file(CurrentERYAProfilingFilePath);
    if(file.ERYAProfilingLayerTextLoad(gridLayerEditor,OpenDatabase))
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Attention: When read ASCII files, it will fill only numerical data.\nIt expect that the user already define the Elements before!"), wxT("ASCII Import Sucessful"), wxOK | wxICON_WARNING);
      dial->ShowModal();
    }
    else
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The source ASCII file data structure is not readible by ERYA Profiling."), wxT("Invalid ASCII text file"), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot load unsupported formats!"), wxT("Error: Invalid File Extention!"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnLayerSave( wxCommandEvent& event )
{
 wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Save the Current Layer Sample as..."), wxEmptyString, wxEmptyString,wxT("ERYA Profiling Layer Sample (*.epls)|*.epls|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx|Generic ASCII text file(*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("epls"))
  {
    ERYAProfilingLayerFile file(CurrentERYAProfilingFilePath);
    if(!(file.ERYAProfilingLayerSave(gridLayerEditor,OpenDatabase)))
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected error when ERYA-Profiling try to write file."), wxT("Error on file save!"), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else if(Version == wxT("xlsx"))
  {
    ERYAProfilingLayerFile file(CurrentERYAProfilingFilePath);
    if(!(file.ERYAProfilingLayerXlsxSave(gridLayerEditor,OpenDatabase)))
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected error when ERYA-Profiling try to write file."), wxT("Error on file save!"), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else if(Version == wxT("txt"))
  {
    ERYAProfilingLayerFile file(CurrentERYAProfilingFilePath);
    if(file.ERYAProfilingLayerTextSave(gridLayerEditor,OpenDatabase))
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Warning: Save as ASCII format for compatibility to LabView ERYA Profiling only!\nOnly the spreadsheet numerical values are stored. The Elements names are not saved!"), wxT("Attention!"), wxOK | wxICON_WARNING);
      dial->ShowModal();
    }
    else
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected error when ERYA-Profiling try to write file."), wxT("Error on file save!"), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot save the current file on unsupported formats!"), wxT("Error: Invalid File Extention!"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnLayerHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("LayerEditor.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnDetectorClear( wxCommandEvent& event )
{
 textBeamEnergy->Clear();
 textTemperature->Clear();
 textCharge->Clear();
 textEnergyStep->Clear();
 textMaximumEnergy->Clear();
 textMinimumEnergy->Clear();
}

void ERYAProfilingERYAProfilingMain::OnDetectorReset( wxCommandEvent& event )
{
 textRessonanceWidth->Clear();
 textRessonancePeak->Clear();
 textRessonanceEnergy->Clear();
 checkRessonanceRange->SetValue(false);
 textRessonanceMinimum->Clear();
 textRessonanceMaximum->Clear();
}

void ERYAProfilingERYAProfilingMain::OnDetectorFunction( wxCommandEvent& event )
{
 textCustomRessonance->Clear();
}

void ERYAProfilingERYAProfilingMain::OnDetectorLoad( wxCommandEvent& event )
{
 wxFileDialog *OpenDialog = new wxFileDialog(this, wxT("Open a Ressonance profile from..."), wxEmptyString, wxEmptyString, wxT("ERYA Profiling Ressonance Sample (*.eprs)|*.eprs"), wxFD_OPEN, wxDefaultPosition);
 if (OpenDialog->ShowModal() == wxID_OK)
 {
 wxString CurrentERYAProfilingFilePath = OpenDialog->GetPath(); // Get absolute path of selected file
 wxFileName file(CurrentERYAProfilingFilePath);
 wxString Version = file.GetExt();
  if(Version == wxT("eprs"))
  {
    ERYAProfilingRessonanceFile file(CurrentERYAProfilingFilePath);
    bool IsLorentzian;
    int ActualMode;
    if(file.ERYAProfilingRessonanceLoad(textBeamEnergy,textTemperature,textCharge,textEnergyStep,textMinimumEnergy,textMaximumEnergy,textRessonanceWidth,textRessonancePeak,textRessonanceEnergy,textRessonanceMinimum,textRessonanceMaximum,textCustomRessonance,IsLorentzian,ActualMode))
    {
      checkRessonanceRange->SetValue(IsLorentzian);
      radioRessonanceOption->SetSelection(ActualMode);
    }
    else
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Error: Unexpected file structure format."), wxT("Error loading file."), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot load unsupported formats!"), wxT("Error: Invalid File Extention!"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnDetectorSave( wxCommandEvent& event )
{
 wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Save the Current Ressonance Profile as..."), wxEmptyString, wxEmptyString,wxT("ERYA Profiling Ressonance Sample (*.eprs)|*.eprs"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("eprs"))
  {
    ERYAProfilingRessonanceFile file(CurrentERYAProfilingFilePath);
    if(!(file.ERYAProfilingRessonanceSave(textBeamEnergy,textTemperature,textCharge,textEnergyStep,textMinimumEnergy,textMaximumEnergy,textRessonanceWidth,textRessonancePeak,textRessonanceEnergy,textRessonanceMinimum,textRessonanceMaximum,textCustomRessonance,checkRessonanceRange->GetValue(),radioRessonanceOption->GetSelection())))
    {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected error when ERYA-Profiling try to write file."), wxT("Error on file save!"), wxOK | wxICON_ERROR);
      dial->ShowModal();
    }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA - Profiling cannot save the current file on unsupported formats!"), wxT("Error: Invalid File Extention!"), wxOK | wxICON_ERROR);
   dial->ShowModal();
  }
 }
}

void ERYAProfilingERYAProfilingMain::OnDetectorHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("DetectorProfile.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnRessonanceRange( wxCommandEvent& event )
{
 if(!(checkRessonanceRange->GetValue()))
 {
  textRessonanceMinimum->Clear();
  textRessonanceMaximum->Clear();
 }
}

void ERYAProfilingERYAProfilingMain::OnRessonanceOption( wxCommandEvent& event )
{
 RessonanceMode = radioRessonanceOption->GetSelection();
}

void ERYAProfilingERYAProfilingMain::OnOutputData( wxCommandEvent& event )
{
 wxFileDialog *OpenDialog = new wxFileDialog(this, wxT("Import an experimental result from..."), wxEmptyString, wxEmptyString, wxT("Microsoft Excel Xlsx File(*.xlsx)|*.xlsx|Numeric ASCII file(*.txt)|*.txt"), wxFD_OPEN, wxDefaultPosition);
 if (OpenDialog->ShowModal() == wxID_OK)
 {
   wxString CurrentERYAProfilingFilePath = OpenDialog->GetPath();
   wxFileName file(CurrentERYAProfilingFilePath);
   if(file.GetExt() == wxT("txt"))
   {
     // If exists theoretical data, there's no need to delete the previous plots
     if(renderOutputData->CountAllLayers()>0)
     {
      // Make the plot
      wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     data->ExportFileTextVector(CurrentERYAProfilingFilePath,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax);
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *plot = data;
     plot->SetContinuity(false);
     //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
     // Write the fitted experimental data
    for(int k=0; k<gridTableData->GetNumberRows(); k++)
    {
    //Get the current energy at the right table position
    double AtEnergy;
    wxString AtValue = gridTableData->GetCellValue(k,0);
    AtValue.ToDouble(&AtEnergy);
    double epsilon1,epsilon2,E1,E2;
   // If the point was outside the boundaries, the final result will be set to zero.
   if( (AtEnergy >= ElementEnergy.at(0)) && ( AtEnergy <= ElementEnergy.at(ElementEnergy.size()-1)))
   {
   for (int i=0; i<ElementEnergy.size(); i++)  // In some situations, the yields points matches exactly at some element of main table
    {
    if (ElementEnergy.at(i) == AtEnergy)
     {
        gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(i)));
     }
    }
   for (int j=0; j<ElementEnergy.size() - 1; j++)  // But in general situations, it is necessary to interpolate two points.
    {
    if (AtEnergy>ElementEnergy.at(j) && AtEnergy<ElementEnergy.at(j+1))
     {
      E1 = ElementEnergy.at(j);
      E2 = ElementEnergy.at(j+1);
      epsilon1 = ElementYield.at(j);
      epsilon2 = ElementYield.at(j+1);
      double slope = (AtEnergy - E1)/(E2 - E1);
      double linear = epsilon1 + slope*(epsilon2 - epsilon1);
      gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",linear));
     }
    }
   }
   else
   {
     gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxT("0"));
   }
   }
  }
  else
  {
      // Make the plot
      wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     data->ExportFileTextVector(CurrentERYAProfilingFilePath,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax);
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Yield"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(false);
      //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->DelAllLayers(false,true);
     renderOutputData->AddLayer(axeEnergy);
     renderOutputData->AddLayer(axeYield);
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
     // Write the fitted experimental data
      int InitialDataSize = gridTableData->GetNumberRows();
     int FinalDataSize = ElementEnergy.size();
     if(InitialDataSize > 1)
     {
     gridTableData->DeleteRows(1,InitialDataSize-1,true);
     }
     gridTableData->AppendRows(FinalDataSize-1,true);
     for(int m=0; m<ElementEnergy.size(); m++) //And allocate the Energy column
      {
      gridTableData->SetCellValue(m,0,wxString::Format("%f",ElementEnergy.at(m)));
      gridTableData->SetCellValue(m,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(m)));
      }
     }
   }
   else
   {
    XlsxFile PlotXlsxFile(CurrentERYAProfilingFilePath);
    if(PlotXlsxFile.LoadFile())
    {
     if(renderOutputData->CountAllLayers()>0) //No eed to delete the plot. if exists some previous data
     {
     TableMatrix PlotTableData = PlotXlsxFile.GetTableMatrix();
     // Make the plot
     wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     if(data->ExportXlsxTableVector(PlotTableData,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax))
     {
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *plot = data;
     plot->SetContinuity(false);
     //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
          // Write the fitted experimental data
    for(int k=0; k<gridTableData->GetNumberRows(); k++)
    {
    //Get the current energy at the right table position
    double AtEnergy;
    wxString AtValue = gridTableData->GetCellValue(k,0);
    AtValue.ToDouble(&AtEnergy);
    double epsilon1,epsilon2,E1,E2;
   // If the point was outside the boundaries, the final result will be set to zero.
   if( (AtEnergy >= ElementEnergy.at(0)) && ( AtEnergy <= ElementEnergy.at(ElementEnergy.size()-1)))
   {
   for (int i=0; i<ElementEnergy.size(); i++)  // In some situations, the yields points matches exactly at some element of main table
    {
    if (ElementEnergy.at(i) == AtEnergy)
     {
        gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(i)));
     }
    }
   for (int j=0; j<ElementEnergy.size() - 1; j++)  // But in general situations, it is necessary to interpolate two points.
    {
    if (AtEnergy>ElementEnergy.at(j) && AtEnergy<ElementEnergy.at(j+1))
     {
      E1 = ElementEnergy.at(j);
      E2 = ElementEnergy.at(j+1);
      epsilon1 = ElementYield.at(j);
      epsilon2 = ElementYield.at(j+1);
      double slope = (AtEnergy - E1)/(E2 - E1);
      double linear = epsilon1 + slope*(epsilon2 - epsilon1);
      gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",linear));
     }
    }
   }
   else
   {
     gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxT("0"));
   }
   }
     }
     else
     {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Spreadsheet file structure are not compatible as an experimental data file.\nIt should have exactly two columns of data, even non-numeric cells are ignored."), wxT("Error: Invalid Excel file"), wxOK | wxICON_ERROR);
       dial->ShowModal();
     }
     }
     else
     {
     TableMatrix PlotTableData = PlotXlsxFile.GetTableMatrix();
     // Make the plot
     wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     if(data->ExportXlsxTableVector(PlotTableData,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax))
     {
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Yield"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(false);
     //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->DelAllLayers(false,true);
     renderOutputData->AddLayer(axeEnergy);
     renderOutputData->AddLayer(axeYield);
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
     // Write the fitted experimental data
      int InitialDataSize = gridTableData->GetNumberRows();
     int FinalDataSize = ElementEnergy.size();
     if(InitialDataSize > 1)
     {
     gridTableData->DeleteRows(1,InitialDataSize-1,true);
     }
     gridTableData->AppendRows(FinalDataSize-1,true);
     for(int m=0; m<ElementEnergy.size(); m++) //And allocate the Energy column
      {
      gridTableData->SetCellValue(m,0,wxString::Format("%f",ElementEnergy.at(m)));
      gridTableData->SetCellValue(m,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(m)));
      }
     }
     else
     {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Spreadsheet file structure are not compatible as an experimental data file.\nIt should have exactly two columns of data, even non-numeric cells are ignored."), wxT("Error: Invalid Excel file"), wxOK | wxICON_ERROR);
       dial->ShowModal();
     }
     }
    }
    else
    {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The source Excel file are corrupted or incompatible."), wxT("Error: Invalid Excel file"), wxOK | wxICON_ERROR);
       dial->ShowModal();
    }
   }
 }
}

void ERYAProfilingERYAProfilingMain::OnOutputImage( wxCommandEvent& event )
{
 wxFileDialog fileDialog(this, wxT("Save the current plot as Image File"), wxEmptyString, wxEmptyString, wxT("JPEG image (*.jpg)|*.jpeg;*.jpg|Bitmap image (*.bmp)|*.bmp|TIFF image (*.tiff)|*.tiff;*.tif|PNG image (*.png)|*.png"), wxFD_SAVE);
 if(fileDialog.ShowModal() == wxID_OK)
 {
  wxFileName namePath(fileDialog.GetPath());
  int fileType = wxBITMAP_TYPE_BMP;
  if( namePath.GetExt().CmpNoCase(wxT("jpeg")) == 0 )
    fileType = wxBITMAP_TYPE_JPEG;
  if( namePath.GetExt().CmpNoCase(wxT("jpg")) == 0 )
    fileType = wxBITMAP_TYPE_JPEG;
  if( namePath.GetExt().CmpNoCase(wxT("tiff")) == 0 )
    fileType = wxBITMAP_TYPE_TIFF;
  if( namePath.GetExt().CmpNoCase(wxT("tif")) == 0 )
    fileType = wxBITMAP_TYPE_TIFF;
  if( namePath.GetExt().CmpNoCase(wxT("png")) == 0 )
    fileType = wxBITMAP_TYPE_PNG;
  if( namePath.GetExt().CmpNoCase(wxT("bmp")) == 0 )
    fileType = wxBITMAP_TYPE_BMP;
  wxSize imgSize(1920,1080);
  renderOutputData->SaveScreenshot(fileDialog.GetPath(), fileType, imgSize, true);
 }
}

void ERYAProfilingERYAProfilingMain::OnOutputHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("Graphics.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnMainNew( wxCommandEvent& event )
{
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Do you really want to clear all\ninputed values on all panels?\nAll inserted or unsaved data will be lost."), wxT("Clear all data on Panels?"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
 if (dial->ShowModal() == wxID_YES)
 {
 this->GenerateTable();
 this->GenerateLayer();
 this->GenerateResult();
 this->GenerateLog();
 gridLayerEditor->ClearGrid();
 renderOutputData->DelAllLayers(false,true);
 textBeamEnergy->Clear();
 textTemperature->Clear();
 textCharge->Clear();
 textEnergyStep->Clear();
 textMaximumEnergy->Clear();
 textMinimumEnergy->Clear();
 textRessonanceWidth->Clear();
 textRessonancePeak->Clear();
 textRessonanceEnergy->Clear();
 checkRessonanceRange->SetValue(false);
 textRessonanceMinimum->Clear();
 textRessonanceMaximum->Clear();
 textCustomRessonance->Clear();
 radioRessonanceOption->SetSelection(0);
 }
}

void ERYAProfilingERYAProfilingMain::OnImportData( wxCommandEvent& event )
{
  wxFileDialog *OpenDialog = new wxFileDialog(this, wxT("Import an experimental result from..."), wxEmptyString, wxEmptyString, wxT("Microsoft Excel Xlsx File(*.xlsx)|*.xlsx|Numeric ASCII file(*.txt)|*.txt"), wxFD_OPEN, wxDefaultPosition);
 if (OpenDialog->ShowModal() == wxID_OK)
 {
   wxString CurrentERYAProfilingFilePath = OpenDialog->GetPath();
   wxFileName file(CurrentERYAProfilingFilePath);
   if(file.GetExt() == wxT("txt"))
   {
     // If exists theoretical data, there's no need to delete the previous plots
     if(renderOutputData->CountAllLayers()>0)
     {
      // Make the plot
      wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     data->ExportFileTextVector(CurrentERYAProfilingFilePath,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax);
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *plot = data;
     plot->SetContinuity(false);
      //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
          // Write the fitted experimental data
    for(int k=0; k<gridTableData->GetNumberRows(); k++)
    {
    //Get the current energy at the right table position
    double AtEnergy;
    wxString AtValue = gridTableData->GetCellValue(k,0);
    AtValue.ToDouble(&AtEnergy);
    double epsilon1,epsilon2,E1,E2;
   // If the point was outside the boundaries, the final result will be set to zero.
   if( (AtEnergy >= ElementEnergy.at(0)) && ( AtEnergy <= ElementEnergy.at(ElementEnergy.size()-1)))
   {
   for (int i=0; i<ElementEnergy.size(); i++)  // In some situations, the yields points matches exactly at some element of main table
    {
    if (ElementEnergy.at(i) == AtEnergy)
     {
        gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(i)));
     }
    }
   for (int j=0; j<ElementEnergy.size() - 1; j++)  // But in general situations, it is necessary to interpolate two points.
    {
    if (AtEnergy>ElementEnergy.at(j) && AtEnergy<ElementEnergy.at(j+1))
     {
      E1 = ElementEnergy.at(j);
      E2 = ElementEnergy.at(j+1);
      epsilon1 = ElementYield.at(j);
      epsilon2 = ElementYield.at(j+1);
      double slope = (AtEnergy - E1)/(E2 - E1);
      double linear = epsilon1 + slope*(epsilon2 - epsilon1);
      gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",linear));
     }
    }
   }
   else
   {
     gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxT("0"));
   }
   }
     }
     else
     {
      // Make the plot
      wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     data->ExportFileTextVector(CurrentERYAProfilingFilePath,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax);
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Yield"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(false);
      //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->DelAllLayers(false,true);
     renderOutputData->AddLayer(axeEnergy);
     renderOutputData->AddLayer(axeYield);
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
     // Write the fitted experimental data
      int InitialDataSize = gridTableData->GetNumberRows();
     int FinalDataSize = ElementEnergy.size();
     if(InitialDataSize > 1)
     {
     gridTableData->DeleteRows(1,InitialDataSize-1,true);
     }
     gridTableData->AppendRows(FinalDataSize-1,true);
     for(int m=0; m<ElementEnergy.size(); m++) //And allocate the Energy column
      {
      gridTableData->SetCellValue(m,0,wxString::Format("%f",ElementEnergy.at(m)));
      gridTableData->SetCellValue(m,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(m)));
      }
     }
   }
   else
   {
    XlsxFile PlotXlsxFile(CurrentERYAProfilingFilePath);
    if(PlotXlsxFile.LoadFile())
    {
     if(renderOutputData->CountAllLayers()>0) //No eed to delete the plot. if exists some previous data
     {
     TableMatrix PlotTableData = PlotXlsxFile.GetTableMatrix();
     // Make the plot
     wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     if(data->ExportXlsxTableVector(PlotTableData,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax))
     {
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *plot = data;
     plot->SetContinuity(false);
     //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
          // Write the fitted experimental data
    for(int k=0; k<gridTableData->GetNumberRows(); k++)
    {
    //Get the current energy at the right table position
    double AtEnergy;
    wxString AtValue = gridTableData->GetCellValue(k,0);
    AtValue.ToDouble(&AtEnergy);
   // If the point was outside the boundaries, the final result will be set to zero.
   if( (AtEnergy >= ElementEnergy.at(0)) && ( AtEnergy <= ElementEnergy.at(ElementEnergy.size()-1)))
   {
    for (int i=0; i<ElementEnergy.size(); i++)  // In some situations, the yields points matches exactly at some element of main table
    {
    if (ElementEnergy.at(i) == AtEnergy)
     {
        gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(i)));
     }
    }
   for (int j=0; j<ElementEnergy.size() - 1; j++)  // But in general situations, it is necessary to interpolate two points.
    {
    if (AtEnergy>ElementEnergy.at(j) && AtEnergy<ElementEnergy.at(j+1))
     {
      // Testing
       double epsilon1,epsilon2,E1,E2;
      E1 = ElementEnergy.at(j);
      E2 = ElementEnergy.at(j+1);
      epsilon1 = ElementYield.at(j);
      epsilon2 = ElementYield.at(j+1);
      double slope = (AtEnergy - E1)/(E2 - E1);
      double linear = epsilon1 + slope*(epsilon2 - epsilon1);
      gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxString::Format("%f",linear));
     }
    }
   }
   else
   {
     gridTableData->SetCellValue(k,gridTableData->GetNumberCols()-1,wxT("0"));
   }
   }
     }
     else
     {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Spreadsheet file structure are not compatible as an experimental data file.\nIt should have exactly two columns of data, even non-numeric cells are ignored."), wxT("Error: Invalid Excel file"), wxOK | wxICON_ERROR);
       dial->ShowModal();
     }
     }
     else
     {
     TableMatrix PlotTableData = PlotXlsxFile.GetTableMatrix();
     // Make the plot
     wxString PlotLabel = wxT("ExpLayer") + wxString::Format("%d",renderOutputData->CountAllLayers());
     // Prepare data
     std::vector<double> ElementEnergy;
     std::vector<double> ElementYield;
     double EnergyMin, EnergyMax, YieldMin, YieldMax;
     ElementEnergySigmaData *data = new ElementEnergySigmaData(PlotLabel);
     if(data->ExportXlsxTableVector(PlotTableData,ElementEnergy,ElementYield,EnergyMin,EnergyMax,YieldMin,YieldMax))
     {
     data->SetData(ElementEnergy,ElementYield);
     // Format the axes and plot
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Yield"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(false);
     //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      unsigned char red = distribution(generator);
      unsigned char green = distribution(generator);
      unsigned char blue = distribution(generator);
      wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 10, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderOutputData->DelAllLayers(false,true);
     renderOutputData->AddLayer(axeEnergy);
     renderOutputData->AddLayer(axeYield);
     renderOutputData->AddLayer(plot);
     renderOutputData->Fit(EnergyMin,EnergyMax,YieldMin,YieldMax);
     gridTableData->AppendCols(1,true);
     gridTableData->SetColLabelValue(gridTableData->GetNumberCols()-1,PlotLabel);
     gridTableData->SetColSize( gridTableData->GetNumberCols()-1, 350 );
     // Write the fitted experimental data
      int InitialDataSize = gridTableData->GetNumberRows();
     int FinalDataSize = ElementEnergy.size();
     if(InitialDataSize > 1)
     {
     gridTableData->DeleteRows(1,InitialDataSize-1,true);
     }
     gridTableData->AppendRows(FinalDataSize-1,true);
     for(int m=0; m<ElementEnergy.size(); m++) //And allocate the Energy column
      {
      gridTableData->SetCellValue(m,0,wxString::Format("%f",ElementEnergy.at(m)));
      gridTableData->SetCellValue(m,gridTableData->GetNumberCols()-1,wxString::Format("%f",ElementYield.at(m)));
      }
     }
     else
     {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Spreadsheet file structure are not compatible as an experimental data file.\nIt should have exactly two columns of data, even non-numeric cells are ignored."), wxT("Error: Invalid Excel file"), wxOK | wxICON_ERROR);
       dial->ShowModal();
     }
     }
    }
    else
    {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The source Excel file are corrupted or incompatible."), wxT("Error: Invalid Excel file"), wxOK | wxICON_ERROR);
       dial->ShowModal();
    }
   }
 }
}

void ERYAProfilingERYAProfilingMain::OnTableSave( wxCommandEvent& event )
{
wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Export the Yield Numerical results as..."), wxEmptyString, wxEmptyString,wxT("Spreadsheet ASCII file(*.txt)|*.txt|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("txt"))
  {
   wxTextFile file(CurrentERYAProfilingFilePath);
   file.Create();
   // First line are labels
   wxString LabelLine = wxT("Energy\t");
   for(int k=0; k<choiceElementName.GetCount(); k++)
   {
    int i = choiceElementName.Item(k)->GetSelection();
    int j = choiceGammaPeak.Item(k)->GetSelection();
    wxString temp = choiceElementName.Item(k)->GetString(i) + wxT(":") + choiceGammaPeak.Item(k)->GetString(j) + wxT("\t");
    LabelLine = LabelLine + temp ;
   }
   file.AddLine(LabelLine);
   // All remaining lines are numerical data
   for(int p=0; p<gridTableData->GetNumberRows(); p++)
   {
    wxString DataLine;
    for(int q=0; q<gridTableData->GetNumberCols(); q++)
    {
     DataLine = DataLine + gridTableData->GetCellValue(p,q) + wxT("\t");
    }
    file.AddLine(DataLine);
   }
   // Save the file
   file.Write();
   file.Close();
  }
  else if(Version == wxT("xlsx"))
  {
    TableMatrix YieldResults;
    YieldResults.Clear();
    YieldResults.DeclareDimension(1,gridTableData->GetNumberCols());
    for(int i=0; i<gridTableData->GetNumberCols(); i++)
    {
      YieldResults.Add(TableNode(gridTableData->GetColLabelValue(i)));
    }
    for(int p=0; p<gridTableData->GetNumberRows(); p++)
    {
      for(int q=0; q<gridTableData->GetNumberCols(); q++)
      {
        YieldResults.Add(TableNode(gridTableData->GetCellValue(p,q),1));
      }
    }
    XlsxFile ERYAProfilingYield(CurrentERYAProfilingFilePath,YieldResults,wxT("A1"));
    ERYAProfilingYield.WriteFile();
  }
  else
  {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA Profiling cannot export data to an unsupported file format!"), wxT("Error: Unsupported File Format"), wxOK | wxICON_ERROR);
       dial->ShowModal();
  }
 }
SaveDialog->Destroy();
}

void ERYAProfilingERYAProfilingMain::OnTableHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("Graphics.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnLogSave( wxCommandEvent& event )
{
 wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Export the Yield Log results as..."), wxEmptyString, wxEmptyString,wxT("Spreadsheet ASCII file(*.txt)|*.txt|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("txt"))
  {
   wxTextFile file(CurrentERYAProfilingFilePath);
   file.Create();
   // First line are labels
   wxString LabelLine = wxT("E0\tDepth\tLayer\tE_loss\tEnergy\tkl\tk\txil\txi\tbeta\tBohr_l\tBohr_t\tVavilov_l\tVavilov_t\t");
   for(int k=0; k<choiceElementName.GetCount(); k++)
   {
    int i = choiceElementName.Item(k)->GetSelection();
    int j = choiceGammaPeak.Item(k)->GetSelection();
    wxString temp = choiceElementName.Item(k)->GetString(i) + wxT(":") + choiceGammaPeak.Item(k)->GetString(j) + wxT("\t");
    LabelLine = LabelLine + temp ;
   }
   file.AddLine(LabelLine);
   // All remaining lines are numerical data
   for(int p=0; p<gridLogData->GetNumberRows(); p++)
   {
    wxString DataLine;
    for(int q=0; q<gridLogData->GetNumberCols(); q++)
    {
     DataLine = DataLine + gridLogData->GetCellValue(p,q) + wxT("\t");
    }
    file.AddLine(DataLine);
   }
   // Save the file
   file.Write();
   file.Close();
  }
  else if(Version == wxT("xlsx"))
  {
    TableMatrix YieldResults;
    YieldResults.Clear();
    YieldResults.DeclareDimension(1,gridLogData->GetNumberCols());
    for(int i=0; i<gridLogData->GetNumberCols(); i++)
    {
      YieldResults.Add(TableNode(gridLogData->GetColLabelValue(i)));
    }
    for(int p=0; p<gridLogData->GetNumberRows(); p++)
    {
      for(int q=0; q<gridLogData->GetNumberCols(); q++)
      {
        YieldResults.Add(TableNode(gridLogData->GetCellValue(p,q),1));
      }
    }
    XlsxFile ERYAProfilingYield(CurrentERYAProfilingFilePath,YieldResults,wxT("A1"));
    ERYAProfilingYield.WriteFile();
  }
  else
  {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA Profiling cannot export data to an unsupported file format!"), wxT("Error: Unsupported File Format"), wxOK | wxICON_ERROR);
       dial->ShowModal();
  }
 }
SaveDialog->Destroy();
}


void ERYAProfilingERYAProfilingMain::OnLogHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("Graphics.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnMainCheck( wxCommandEvent& event )
{
  wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Export the Yield Log results as..."), wxEmptyString, wxEmptyString,wxT("Spreadsheet ASCII file(*.txt)|*.txt|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("txt"))
  {
   wxTextFile file(CurrentERYAProfilingFilePath);
   file.Create();
   // First line are labels
   wxString LabelLine = wxT("E0\tDepth\tLayer\tE_loss\tEnergy\tkl\tk\txil\txi\tbeta\tBohr_l\tBohr_t\tVavilov_l\tVavilov_t\t");
   for(int k=0; k<choiceElementName.GetCount(); k++)
   {
    int i = choiceElementName.Item(k)->GetSelection();
    int j = choiceGammaPeak.Item(k)->GetSelection();
    wxString temp = choiceElementName.Item(k)->GetString(i) + wxT(":") + choiceGammaPeak.Item(k)->GetString(j) + wxT("\t");
    LabelLine = LabelLine + temp ;
   }
   file.AddLine(LabelLine);
   // All remaining lines are numerical data
   for(int p=0; p<gridLogData->GetNumberRows(); p++)
   {
    wxString DataLine;
    for(int q=0; q<gridLogData->GetNumberCols(); q++)
    {
     DataLine = DataLine + gridLogData->GetCellValue(p,q) + wxT("\t");
    }
    file.AddLine(DataLine);
   }
   // Save the file
   file.Write();
   file.Close();
  }
  else if(Version == wxT("xlsx"))
  {
    TableMatrix YieldResults;
    YieldResults.Clear();
    YieldResults.DeclareDimension(1,gridLogData->GetNumberCols());
    for(int i=0; i<gridLogData->GetNumberCols(); i++)
    {
      YieldResults.Add(TableNode(gridLogData->GetColLabelValue(i)));
    }
    for(int p=0; p<gridLogData->GetNumberRows(); p++)
    {
      for(int q=0; q<gridLogData->GetNumberCols(); q++)
      {
        YieldResults.Add(TableNode(gridLogData->GetCellValue(p,q),1));
      }
    }
    XlsxFile ERYAProfilingYield(CurrentERYAProfilingFilePath,YieldResults,wxT("A1"));
    ERYAProfilingYield.WriteFile();
  }
  else
  {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA Profiling cannot export data to an unsupported file format!"), wxT("Error: Unsupported File Format"), wxOK | wxICON_ERROR);
       dial->ShowModal();
  }
 }
SaveDialog->Destroy();
}

void ERYAProfilingERYAProfilingMain::OnMainAdvanced( wxCommandEvent& event )
{
 ERYAProfilingdialogERYAProfilingAdvanced* extra = new ERYAProfilingdialogERYAProfilingAdvanced(this);
 extra->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnMainRun( wxCommandEvent& event )
{
 ReactionProfiling* main = new ReactionProfiling();
  if(main->SetInitialParameters(textBeamEnergy,textTemperature,textCharge,textEnergyStep,textMinimumEnergy,textMaximumEnergy,textRessonanceWidth,textRessonancePeak,textRessonanceEnergy,textRessonanceMinimum,textRessonanceMaximum,textCustomRessonance,checkRessonanceRange->GetValue(),radioRessonanceOption->GetSelection()))
  {
   statusERYAProfiling->SetStatusText(wxT("Prepare simulation, please wait...") ,0);
   main->SetOverrideParameters(SamplePrecision,GaussPrecision,VavilovMoyalPrecision,VavilovEdgeworthPrecision,LandauPrecision,ThreadPrecision,EnableLog);
   if(main->SampleSetup(OpenDatabase,CurrentZieglerParameters,CurrentDetectorParameters,CurrentSRIMTables,gridLayerEditor,choiceElementName,choiceGammaPeak,textAtomicNumber,textAbundance,textIsotopicMass,textAtomicMass))
   {
     if(main->StartProcedure(statusERYAProfiling))
     {
      // Make the plot
      renderOutputData->DelAllLayers(false,true);
      mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
      mpLayer *axeYield = new mpScaleY(wxT("Yield"),mpALIGN_BORDER_LEFT,false);
      axeEnergy->SetDrawOutsideMargins(false);
      axeYield->SetDrawOutsideMargins(false);
      renderOutputData->AddLayer(axeEnergy);
      renderOutputData->AddLayer(axeYield);
      //Generate random numbers
      std::random_device r1, r2, r3, r4, r5, r6;
      std::seed_seq seed{ r1(), r2(), r3(), r4(), r5(), r6() };
      std::default_random_engine generator{seed};
      std::uniform_int_distribution<unsigned char> distribution(0,255);
      for(int i=0; i<main->GetNumberElements(); i++)
      {
       int p = choiceElementName.Item(i)->GetSelection();
       int q = choiceGammaPeak.Item(i)->GetSelection();
       wxString temp = choiceElementName.Item(i)->GetString(p) + wxT(" (") + choiceGammaPeak.Item(i)->GetString(q) + wxT(" keV)");
       mpFXYVector *data = new mpFXYVector(temp,mpALIGN_LEFT);
       data->SetData(main->GetEnergyRange(),main->GetElementYield(i));
       mpLayer *plot = data;
       plot->SetContinuity(true);
       unsigned char red = distribution(generator);
       unsigned char green = distribution(generator);
       unsigned char blue = distribution(generator);
       wxPen plotcolor(wxColor(red, green, blue, wxALPHA_OPAQUE), 5, wxSOLID);
       plot->SetPen(plotcolor);
       plot->SetDrawOutsideMargins(false);
       renderOutputData->AddLayer(plot);
      }
       mpInfoLegend *plotElements = new mpInfoLegend(wxRect(100,20,40,40), wxTRANSPARENT_BRUSH);
       renderOutputData->AddLayer(plotElements);
       renderOutputData->Fit();
       // Store the numerical data on the adequate table.
       this->GenerateResult(main->GetEnergyRange().size());
       // The remaining lines are numerical data
       for (int i=0; i<main->GetEnergyRange().size(); i++)
       {
         gridTableData->SetCellValue(i,0,wxString::Format("%f",main->GetEnergyRange().at(i)));
        for(int j=0; j<main->GetNumberElements(); j++)
        {
          gridTableData->SetCellValue(i,j+1,wxString::Format("%f",main->GetElementYield(j).at(i)));
        }
       }
       // If the user was enabled the partial log table, this step will dump the contents to the log tab
       if(EnableLog)
       {
        // Get the Sample Data to the adequate table
       this->GenerateLog(main->GetNumberAllSamples());
       int AuxiliaryCounter = 0;
       // Get the numerical data
       for(int i=0; i<main->GetNumberSamples(); i++)
       {
        for(int j=0; j<main->GetNumberSampleElementsAt(i); j++)
        {
          gridLogData->SetCellValue(AuxiliaryCounter,0,wxString::Format("%f",main->GetInitialEnergyAt(i))); //Initial Energy
          gridLogData->SetCellValue(AuxiliaryCounter,1,wxString::Format("%f",main->GetSampleDepth(i).at(j))); //Depth
          gridLogData->SetCellValue(AuxiliaryCounter,2,wxString::Format("%f",main->GetSampleLayer(i).at(j))); //Layer
          gridLogData->SetCellValue(AuxiliaryCounter,3,wxString::Format("%f",main->GetSampleDE(i).at(j))); //Energy Loss
          gridLogData->SetCellValue(AuxiliaryCounter,4,wxString::Format("%f",main->GetSampleEM(i).at(j))); //Current Energy
          gridLogData->SetCellValue(AuxiliaryCounter,5,wxString::Format("%f",main->GetSampleKL(i).at(j))); //Partial K
          gridLogData->SetCellValue(AuxiliaryCounter,6,wxString::Format("%f",main->GetSampleKT(i).at(j))); //Total K
          gridLogData->SetCellValue(AuxiliaryCounter,7,wxString::Format("%f",main->GetSampleXi(i).at(j))); //Partial Xi
          gridLogData->SetCellValue(AuxiliaryCounter,8,wxString::Format("%f",main->GetSampleXT(i).at(j))); //Total Xi
          gridLogData->SetCellValue(AuxiliaryCounter,9,wxString::Format("%f",main->GetSampleBeta(i).at(j))); //Current Beta
          gridLogData->SetCellValue(AuxiliaryCounter,10,wxString::Format("%f",main->GetSampleBL(i).at(j))); //Partial Bohr Variance
          gridLogData->SetCellValue(AuxiliaryCounter,11,wxString::Format("%f",main->GetSampleBV(i).at(j))); //Total Bohr Variance
          gridLogData->SetCellValue(AuxiliaryCounter,12,wxString::Format("%f",std::sqrt((main->GetSampleXi(i).at(j)*main->GetSampleXi(i).at(j)*(1-main->GetSampleBeta(i).at(j)*main->GetSampleBeta(i).at(j)/2))/main->GetSampleKL(i).at(j)))); //Partial Vavilov Variance
         if(main->GetSampleKT(i).at(j) == 0)
          gridLogData->SetCellValue(AuxiliaryCounter,13,wxString::Format("%f",0.0)); //Total Vavilov Variance
         else
          gridLogData->SetCellValue(AuxiliaryCounter,13,wxString::Format("%f",std::sqrt((main->GetSampleXT(i).at(j)*main->GetSampleXT(i).at(j)*(1-main->GetSampleBeta(i).at(j)*main->GetSampleBeta(i).at(j)/2))/main->GetSampleKT(i).at(j)))); //Total Vavilov Variance
          for(int k=0; k<main->GetNumberYieldElementsAt(i); k++)
          {
            gridLogData->SetCellValue(AuxiliaryCounter,14+k,wxString::Format("%f",main->GetSamplePY(i).at(main->GetNumberYieldElementsAt(i)*j+k))); //Partial Yield
          }
          AuxiliaryCounter = AuxiliaryCounter + 1; //A line was processed.
        }
       }
       }
       statusERYAProfiling->SetStatusText(wxT("Complete!") ,0);
     }
     else
     {
       statusERYAProfiling->SetStatusText(wxT("Error during calculation...") ,0);
       wxMessageDialog *error3 = new wxMessageDialog(NULL, main->GetErrorCode(), wxT("Numerical Error on Runtime!"), wxOK | wxICON_ERROR);
       error3->ShowModal();
     }
   }
   else
   {
    statusERYAProfiling->SetStatusText(wxT("Error during initialization...") ,0);
    wxMessageDialog *error2 = new wxMessageDialog(NULL, main->GetErrorCode(), wxT("Invalid Database Settings!"), wxOK | wxICON_ERROR);
    error2->ShowModal();
   }
  }
  else
  {
   statusERYAProfiling->SetStatusText(wxT("Error during initialization...") ,0);
   wxMessageDialog *error1 = new wxMessageDialog(NULL, main->GetErrorCode(), wxT("Invalid Initial Parameters!"), wxOK | wxICON_ERROR);
   error1->ShowModal();
  }
  delete main;
}

void ERYAProfilingERYAProfilingMain::OnMainHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("HowTo.html"));
 help->ShowModal();
}

void ERYAProfilingERYAProfilingMain::OnMainSave( wxCommandEvent& event )
{
 wxFileDialog *SaveDialog = new wxFileDialog(this, wxT("Export the Yield Numerical results as..."), wxEmptyString, wxEmptyString,wxT("Spreadsheet ASCII file(*.txt)|*.txt|Microsoft Excel Xlsx File(*.xlsx)|*.xlsx"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 if (SaveDialog->ShowModal() == wxID_OK)
 {
  wxString CurrentERYAProfilingFilePath = SaveDialog->GetPath();
  wxFileName ERYAProfilingFileName(CurrentERYAProfilingFilePath);
  wxString Version = ERYAProfilingFileName.GetExt();
  if(Version == wxT("txt"))
  {
   wxTextFile file(CurrentERYAProfilingFilePath);
   file.Create();
   // First line are labels
   wxString LabelLine = wxT("Energy\t");
   for(int k=0; k<choiceElementName.GetCount(); k++)
   {
    int i = choiceElementName.Item(k)->GetSelection();
    int j = choiceGammaPeak.Item(k)->GetSelection();
    wxString temp = choiceElementName.Item(k)->GetString(i) + wxT(":") + choiceGammaPeak.Item(k)->GetString(j) + wxT("\t");
    LabelLine = LabelLine + temp ;
   }
   file.AddLine(LabelLine);
   // All remaining lines are numerical data
   for(int p=0; p<gridTableData->GetNumberRows(); p++)
   {
    wxString DataLine;
    for(int q=0; q<gridTableData->GetNumberCols(); q++)
    {
     DataLine = DataLine + gridTableData->GetCellValue(p,q) + wxT("\t");
    }
    file.AddLine(DataLine);
   }
   // Save the file
   file.Write();
   file.Close();
  }
  else if(Version == wxT("xlsx"))
  {
    TableMatrix YieldResults;
    YieldResults.Clear();
    YieldResults.DeclareDimension(1,gridTableData->GetNumberCols());
    for(int i=0; i<gridTableData->GetNumberCols(); i++)
    {
      YieldResults.Add(TableNode(gridTableData->GetColLabelValue(i)));
    }
    for(int p=0; p<gridTableData->GetNumberRows(); p++)
    {
      for(int q=0; q<gridTableData->GetNumberCols(); q++)
      {
        YieldResults.Add(TableNode(gridTableData->GetCellValue(p,q),1));
      }
    }
    XlsxFile ERYAProfilingYield(CurrentERYAProfilingFilePath,YieldResults,wxT("A1"));
    ERYAProfilingYield.WriteFile();
  }
  else
  {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA Profiling cannot export data to an unsupported file format!"), wxT("Error: Unsupported File Format"), wxOK | wxICON_ERROR);
       dial->ShowModal();
  }
 }
SaveDialog->Destroy();
}

void ERYAProfilingERYAProfilingMain::GenerateLog(int Number)
{
 int CurrentTableSize = gridLogData->GetNumberRows();
 int NewTableSize = Number;
   if (CurrentTableSize != NewTableSize)
   {
    if (CurrentTableSize < NewTableSize)
    {
     gridLogData->AppendRows(NewTableSize-CurrentTableSize,true);
    }
    else
    {
     gridLogData->DeleteRows(NewTableSize,CurrentTableSize-NewTableSize,true);
    }
   }
}

void ERYAProfilingERYAProfilingMain::GenerateLog()
{
 gridLogData->ClearGrid();
 int InitialTableSize = gridLogData->GetNumberCols();
 if(InitialTableSize > 1)
 {
   gridLogData->DeleteCols(1,InitialTableSize-1,true);
 }
 int InitialDataSize = gridLogData->GetNumberRows();
 if(InitialDataSize > 1)
 {
   gridLogData->DeleteRows(1,InitialDataSize-1,true);
 }
 // Create a new label list
 wxArrayString TableLabels;
 TableLabels.Add(wxT("Initial Energy (keV)"));
 TableLabels.Add(wxT("Total Depth(x*10^15 atm/cm^2)"));
 TableLabels.Add(wxT("Current Layer"));
 TableLabels.Add(wxT("Energy Loss (keV)"));
 TableLabels.Add(wxT("Current Energy (keV)"));
 TableLabels.Add(wxT("Partial k-factor"));
 TableLabels.Add(wxT("Total k-factor"));
 TableLabels.Add(wxT("Partial Xi-factor"));
 TableLabels.Add(wxT("Total Xi-factor"));
 TableLabels.Add(wxT("Current Beta-factor"));
 TableLabels.Add(wxT("Partial Bohr Variance"));
 TableLabels.Add(wxT("Total Bohr Variance"));
 TableLabels.Add(wxT("Partial Vavilov-Gauss Variance"));
 TableLabels.Add(wxT("Total Vavilov-Gauss Variance"));

 // Fill the columns labels
 for (int k=0; k<choiceElementName.GetCount(); k++)
 {
  int i = choiceElementName.Item(k)->GetSelection();
  int j = choiceGammaPeak.Item(k)->GetSelection();
  wxString temp = choiceElementName.Item(k)->GetString(i) + wxT(" (") + choiceGammaPeak.Item(k)->GetString(j) + wxT(" keV)");
  TableLabels.Add(temp);
 }
 // Generate the new table
 gridLogData->AppendCols(TableLabels.GetCount()-1,true);
 for (int z=0; z<gridLogData->GetNumberCols(); z++)
 {
   gridLogData->SetColLabelValue(z,TableLabels.Item(z));
   gridLogData->SetColSize( z, 350 );
 }
}

void ERYAProfilingERYAProfilingMain::GenerateResult(int Number)
{
 int CurrentTableSize = gridTableData->GetNumberRows();
 int NewTableSize = Number;
   if (CurrentTableSize != NewTableSize)
   {
    if (CurrentTableSize < NewTableSize)
    {
     gridTableData->AppendRows(NewTableSize-CurrentTableSize,true);
    }
    else
    {
     gridTableData->DeleteRows(NewTableSize,CurrentTableSize-NewTableSize,true);
    }
   }
}

void ERYAProfilingERYAProfilingMain::GenerateResult()
{
 gridTableData->ClearGrid();
 int InitialTableSize = gridTableData->GetNumberCols();
 if(InitialTableSize > 1)
 {
   gridTableData->DeleteCols(1,InitialTableSize-1,true);
 }
 int InitialDataSize = gridTableData->GetNumberRows();
 if(InitialDataSize > 1)
 {
   gridTableData->DeleteRows(1,InitialDataSize-1,true);
 }
 // Create a new label list
 wxArrayString TableLabels;
 TableLabels.Add(wxT("Energy (keV)"));
 // Fill the columns labels
 for (int k=0; k<choiceElementName.GetCount(); k++)
 {
  int i = choiceElementName.Item(k)->GetSelection();
  int j = choiceGammaPeak.Item(k)->GetSelection();
  wxString temp = choiceElementName.Item(k)->GetString(i) + wxT(" (") + choiceGammaPeak.Item(k)->GetString(j) + wxT(" keV)");
  TableLabels.Add(temp);
 }
 // Generate the new table
 gridTableData->AppendCols(TableLabels.GetCount()-1,true);
 for (int z=0; z<gridTableData->GetNumberCols(); z++)
 {
   gridTableData->SetColLabelValue(z,TableLabels.Item(z));
   gridTableData->SetColSize( z, 350 );
 }
}


void ERYAProfilingERYAProfilingMain::GenerateLayer(int Number)
{
   int CurrentTableSize = gridLayerEditor->GetNumberRows();
   int NewTableSize = Number;
   if (CurrentTableSize != NewTableSize)
   {
    if (CurrentTableSize < NewTableSize)
    {
     gridLayerEditor->AppendRows(NewTableSize-CurrentTableSize,true);
    }
    else
    {
     gridLayerEditor->DeleteRows(NewTableSize,CurrentTableSize-NewTableSize,true);
    }
   }
}

void ERYAProfilingERYAProfilingMain::GenerateLayer()
{
 //Clear the current layer wxGrid, and generate a new table
 gridLayerEditor->ClearGrid();
 int InitialTableSize = gridLayerEditor->GetNumberCols();
 if(InitialTableSize > 1)
 {
   gridLayerEditor->DeleteCols(1,InitialTableSize-1,true);
 }
 // Create a new label list
 wxArrayString TableLabels;
 TableLabels.Add(wxT("Layer Depth x*10^15 at/cm^2"));
 // Fill the columns labels
 for (int k=0; k<choiceElementName.GetCount(); k++)
 {
  int i = choiceElementName.Item(k)->GetSelection();
  int j = choiceGammaPeak.Item(k)->GetSelection();
  wxString temp = choiceElementName.Item(k)->GetString(i) + wxT(" (") + choiceGammaPeak.Item(k)->GetString(j) + wxT(" keV)");
  TableLabels.Add(temp);
 }
 // Generate the new table
 gridLayerEditor->AppendCols(TableLabels.GetCount()-1,true);
 for (int z=0; z<gridLayerEditor->GetNumberCols(); z++)
 {
   gridLayerEditor->SetColLabelValue(z,TableLabels.Item(z));
   gridLayerEditor->SetColSize( z, 350 );
 }
 // Generate other tables
 this->GenerateResult();
 this->GenerateLog();
}

void ERYAProfilingERYAProfilingMain::GenerateTable(int Number )
{
 spinNumberElements->SetValue(Number);
 // Get the desired number of elements
 int NumberElements = Number;
 // Get the current number of elements
 int CurrentElements = choiceElementName.GetCount();
 // Get the Number of Operations
 int ChangeElements = NumberElements - CurrentElements;

 // If the number of elements will increase
 if (ChangeElements > 0)
 {
    // Get the pull-downs menus
    choiceElementNameChoices.Clear();
    choiceGammaPeakChoices.Clear();

    for (int k=CurrentElements; k<NumberElements; k++)
    {

	choiceElementName.Add(new wxChoice( scrollElementTable, wxID_ANY, wxDefaultPosition, wxSize(140,-1), choiceElementNameChoices, 0 ));
	choiceElementName.Last()->SetSelection( 0 );
	sizerElementEditor->Add( choiceElementName.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	choiceGammaPeak.Add(new wxChoice( scrollElementTable, wxID_ANY, wxDefaultPosition, wxSize(140,-1), choiceElementNameChoices, 0 ));
	choiceGammaPeak.Last()->SetSelection( 0 );
	sizerElementEditor->Add( choiceGammaPeak.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAtomicNumber.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textAtomicNumber.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAbundance.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textAbundance.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textIsotopicMass.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textIsotopicMass.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAtomicMass.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textAtomicMass.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

     choiceElementName.Last()->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ERYAProfilingERYAProfilingMain::OnElementNameChoice ), NULL, this );
	 choiceGammaPeak.Last()->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ERYAProfilingERYAProfilingMain::OnGammaPeakChoice ), NULL, this );

	 OpenDatabase.ResetElementGammaMenu(choiceElementName.Last(),choiceGammaPeak.Last());
     OpenDatabase.FindGetAllElementInfo(choiceElementName.Last()->GetString(0),choiceGammaPeak.Last()->GetString(0), choiceElementName.Last(), choiceGammaPeak.Last(), textAtomicNumber.Last(), textAbundance.Last(), textAtomicMass.Last(), textIsotopicMass.Last());

    }

    // Redraw the new elements on screen
    scrollElementTable->SetAutoLayout(true);
    scrollElementTable->SetSizer( sizerElementEditor );
	scrollElementTable->Layout();
	sizerElementEditor->Fit( scrollElementTable );
	tabElements->SetSizer( sizerElements );
	tabElements->Layout();
	sizerElements->Fit( tabElements );

   // Win32 API require external sizer refitting to correctly redraw the Elements tab, unlike the GTK which is irrelevant.
    this->SetSizer( sizerERYAProfilingMain );
	this->Layout();
	this->Centre( wxBOTH );
   // Generate a new table
    this->GenerateLayer();
    this->GenerateResult();
    this->GenerateLog();
}


// If the number of elements will increase
if (ChangeElements < 0)
{
 int NumberRemovedElements = std::abs(ChangeElements * 6); //Obtain the number of retired objects
 for (int i=0; i<NumberRemovedElements; i++)
 {
   int CurrentNumberElements = sizerElementEditor->GetItemCount();
   sizerElementEditor->Hide(CurrentNumberElements-1); //Hide last object
   sizerElementEditor->Remove(CurrentNumberElements-1); //Remove the last object
 }
 for(int k=0; k<std::abs(ChangeElements); k++) //Trim internal elements
 {
   choiceElementName.RemoveAt(choiceElementName.GetCount()-1);
   choiceGammaPeak.RemoveAt(choiceGammaPeak.GetCount()-1);
   textAtomicNumber.RemoveAt(textAtomicNumber.GetCount()-1);
   textIsotopicMass.RemoveAt(textIsotopicMass.GetCount()-1);
   textAbundance.RemoveAt(textAbundance.GetCount()-1);
   textAtomicMass.RemoveAt(textAtomicMass.GetCount()-1);
 }
 // Redraw the new elements on screen
    scrollElementTable->SetAutoLayout(true);
    scrollElementTable->SetSizer( sizerElementEditor );
	scrollElementTable->Layout();
	sizerElementEditor->Fit( scrollElementTable );
	tabElements->SetSizer( sizerElements );
	tabElements->Layout();
	sizerElements->Fit( tabElements );

   // Win32 API require external sizer refitting to correctly redraw the Elements tab, unlike the GTK which is irrelevant.
    this->SetSizer( sizerERYAProfilingMain );
	this->Layout();
	this->Centre( wxBOTH );
   // Generate a new table
    this->GenerateLayer();
    this->GenerateResult();
    this->GenerateLog();

}
 // No changes on number of elements, implies to modifications at all
}

void ERYAProfilingERYAProfilingMain::GenerateTable()
{
 this->GenerateTable(1);
}

bool ERYAProfilingERYAProfilingMain::StartUpProgram()
{
 // Define some internal variables
 GaussPrecision = 60;
 SamplePrecision = 10;
 VavilovMoyalPrecision = 10;
 VavilovEdgeworthPrecision = 70;
 LandauPrecision = 284;
 ThreadPrecision = 1;
 // Load the configuration file, or force the user to create a new configuration file
 if(!(this->LoadSetupFile(CurrentConfig,CurrentDetectorFile,CurrentDatabaseFile,CurrentZieglerFile)))
  {
   ERYAProfilingwizardFirstRun *firstrunwizard = new ERYAProfilingwizardFirstRun(this);
   firstrunwizard->StartWizard(); //Start the wizard at the first page...
   firstrunwizard->Destroy();
   if(AcceptSync) //The wizard was completed
   {
    wxBusyInfo* CreatingFiles = new wxBusyInfo(wxT("ERYA-Profiling are checking the files for consistency\nPlease wait, since on slow machines it can take\nseveral seconds to finish."));
    if(!(this->SaveSetupFile(CurrentConfig,CurrentDetectorFile,CurrentDatabaseFile,CurrentZieglerFile,DefaultSetting)))
    {
     if(CreatingFiles)
      delete CreatingFiles;
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Cannot create the configuration file, due to an error ...\nTry other settings, and also check if the target directory is not protected."), wxT("Error: Setup Failure!"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     return false;
    }
    else //Copy and convert the selected databases to the target directory
    {
     if(!(this->StartUpDatabases(CurrentConfig,CurrentDetectorFile,CurrentDatabaseFile,CurrentZieglerFile)))
     {
      if(CreatingFiles)
       delete CreatingFiles;
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The initial selected databases are not compatible with ERYA Profiling..."), wxT("Error: Setup Failure!"), wxOK | wxICON_ERROR);
      dial->ShowModal();
      return false;
     }
    }
    if(CreatingFiles)
      delete CreatingFiles;
   }
  }
 this->GenerateTable();
 this->GenerateLayer();
 this->GenerateResult();
 this->GenerateLog();
 if(CurrentDatabaseFile.Len()>0 && CurrentDetectorFile.Len()>0 && CurrentZieglerFile.Len()>0)
 {
 // Load the default database file
 wxFileName df(CurrentDatabaseFile);
 wxString DatabaseVersion = wxT("epd");
 DatabaseFile loadDatabase(CurrentConfig + wxFileName::GetPathSeparator() + CurrentDatabaseFile,DatabaseVersion,OpenDatabase);
   if(loadDatabase.ERYAProfilingDatabaseFileLoad())
    {
     OpenDatabase = loadDatabase.GetDatabase();
     // Rebuild the two pull down menus for all elements, while use the two STL integer vectors to handle their adress
     for(int k=0; k<choiceElementName.GetCount(); k++)
     {
      OpenDatabase.ResetElementGammaMenu(choiceElementName.Item(k),choiceGammaPeak.Item(k));
      OpenDatabase.FindGetAllElementInfo(choiceElementName.Item(k)->GetString(0),choiceGammaPeak.Item(k)->GetString(0), choiceElementName.Item(k), choiceGammaPeak.Item(k), textAtomicNumber.Item(k), textAbundance.Item(k), textAtomicMass.Item(k), textIsotopicMass.Item(k));
     }
     this->GenerateLayer();
    }
    else
    {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The default database is not compatible with ERYA Profiling."), wxT("Error: Invalid Database"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     return false;
    }

 // Load the default detector setup file
 wxFileName ef(CurrentDetectorFile);
 wxString DetectorVersion = wxT("epsd");
 DetectorFile loadDetector(CurrentConfig + wxFileName::GetPathSeparator() + CurrentDetectorFile,DetectorVersion,CurrentDetectorParameters);
   if(loadDetector.DetectorFileLoad())
    {
     CurrentDetectorParameters = loadDetector.GetParameters();
    }
    else
    {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The default detector is not compatible with ERYA Profiling."), wxT("Error: Invalid Database"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     return false;
    }

 // Load the default Ziegler parameters file
 wxFileName zf(CurrentZieglerFile);
 wxString ZieglerVersion = wxT("epsz");
 ZieglerFile loadZiegler(CurrentConfig + wxFileName::GetPathSeparator() + CurrentZieglerFile,ZieglerVersion,CurrentZieglerParameters,CurrentSRIMTables,0);
   if(loadZiegler.ZieglerFileLoad())
    {
     CurrentZieglerParameters = loadZiegler.GetParameters();
     CurrentSRIMTables = loadZiegler.GetTables();
    }
    else
    {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The default Ziegler is not compatible with ERYA Profiling."), wxT("Error: Invalid Database"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     return false;
    }
 }
 else
 {
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA Profiling will start without any default databases."), wxT("Error: Incorrect Configuration"), wxOK | wxICON_ERROR);
  dial->ShowModal();
  return false;
 }
 return true; //Init sucefull
}

bool ERYAProfilingERYAProfilingMain::StartUpDatabases()
{
   return this->StartUpDatabases(CurrentConfig,CurrentDetectorFile,CurrentDetectorFile,CurrentZieglerFile);
}

bool ERYAProfilingERYAProfilingMain::StartUpDatabases(wxString MainDirectory, wxString MainDetector, wxString MainDatabase, wxString MainZiegler)
{
    // Global settings
    wxString fileconfig = ::wxStandardPaths::Get().GetExecutablePath();
    wxFileName mainconfig(fileconfig);
    wxString rootconfig = mainconfig.GetPath();
    // Select the default detector settings
    wxString DetectorFileName = MainDirectory + wxFileName::GetPathSeparator() + MainDetector;
    wxString OriginalDetector = rootconfig + wxFileName::GetPathSeparator() + MainDetector;
    // Load, test and store the selected Detector Setup
    wxFileName ief(DetectorFileName);
    wxString DetectorVersion = ief.GetExt();
    DetectorFile testDetector(OriginalDetector,DetectorVersion,CurrentDetectorParameters);
   if(testDetector.DetectorFileLoad())
    {
     CurrentDetectorParameters = testDetector.GetParameters();
     DetectorVersion = wxT("epsd");
     DetectorFile targetDetector(DetectorFileName,DetectorVersion,CurrentDetectorParameters);
     if(targetDetector.DetectorFileSave())
     {
      CurrentDetectorParameters.Clear();
      CurrentDetectorParameters = targetDetector.GetParameters();
     }
     else
     {
      return false;
     }
    }
    else
    {
     return false;
    }

    // Select the default Ziegler settings
    wxString ZieglerFileName = MainDirectory + wxFileName::GetPathSeparator() + MainZiegler;
    wxString OriginalZiegler = rootconfig + wxFileName::GetPathSeparator() + MainZiegler;

    // Load, test and store the default Ziegler Parameters
    wxFileName izf(ZieglerFileName);
    wxString ZieglerVersion = izf.GetExt();
    ZieglerFile testZiegler(OriginalZiegler,ZieglerVersion,CurrentZieglerParameters,CurrentSRIMTables,0);
   if(testZiegler.ZieglerFileLoad())
    {
     CurrentZieglerParameters = testZiegler.GetParameters();
     CurrentSRIMTables = testZiegler.GetTables();
     ZieglerVersion = wxT("epsz");
     ZieglerFile targetZiegler(ZieglerFileName,ZieglerVersion,CurrentZieglerParameters,CurrentSRIMTables,0);
     if(targetZiegler.ZieglerFileSave())
     {
      CurrentZieglerParameters.Clear();
      CurrentSRIMTables.Clear();
      CurrentZieglerParameters = targetZiegler.GetParameters();
      CurrentSRIMTables = targetZiegler.GetTables();
     }
     else
     {
      return false;
     }
    }
    else
    {
     return false;
    }

    // Select the default Elements settings
    wxString ElementsFileName = MainDirectory + wxFileName::GetPathSeparator() + MainDatabase;
    wxString OriginalElements = rootconfig + wxFileName::GetPathSeparator() + MainDatabase;
     // Load, test and store the selected database on the selected folder
    wxFileName idf(ElementsFileName);
    wxString ElementsVersion = idf.GetExt();
    DatabaseFile testDatabase(OriginalElements,ElementsVersion,OpenDatabase);
   if(testDatabase.ERYAProfilingDatabaseFileLoad())
    {
     OpenDatabase = testDatabase.GetDatabase();
     ElementsVersion = wxT("epd");
     DatabaseFile targetDatabase(ElementsFileName,ElementsVersion,OpenDatabase);
     if(targetDatabase.ERYAProfilingDatabaseFileSave())
     {
      OpenDatabase.Clear();
      OpenDatabase = targetDatabase.GetDatabase();
     }
     else
     {
      return false;
     }
    }
    else
    {
     return false;
    }
   return true;
}

bool ERYAProfilingERYAProfilingMain::LoadSetupFile(wxString& MainDirectory, wxString& MainDetector, wxString& MainDatabase, wxString& MainZiegler)
{
  // Get the two compatible name paths
  wxString fileconfig = ::wxStandardPaths::Get().GetExecutablePath();
  wxFileName mainconfig(fileconfig);
  wxString rootconfig = mainconfig.GetPath();
  wxString pathconfig = rootconfig;
  wxString nameconfig = mainconfig.GetName();
  wxString standardconfig = ::wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + nameconfig + wxT(".conf");
  wxString portableconfig = ::wxStandardPaths::Get().GetExecutablePath() + wxT(".conf");
  // Clear variable contents
  MainDirectory.Clear();
  MainDetector.Clear();
  MainDetector.Clear();
  MainZiegler.Clear();
  // Load the file, while try to load at local profile, then the root profile.
  wxXmlDocument LocalSetupFile;
  if(wxFile::Exists(standardconfig))
  {
   if(!(LocalSetupFile.Load(standardconfig)))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA-Profiling don't find any configuration file\nThe program will start the Configuration Wizard..."), wxT("No Setup files found"), wxOK | wxICON_ERROR);
   dial->ShowModal();
   return false;
   }
  }
  else if(wxFile::Exists(portableconfig))
  {
   if(!(LocalSetupFile.Load(portableconfig)))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA-Profiling don't find any configuration file\nThe program will start the Configuration Wizard..."), wxT("No Setup files found"), wxOK | wxICON_ERROR);
   dial->ShowModal();
   return false;
   }
  }
  else
  {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA-Profiling don't find any configuration file\nThe program will start the Configuration Wizard..."), wxT("No Setup files found"), wxOK | wxICON_ERROR);
   dial->ShowModal();
   return false;
  }
  // Found a configuration file
   if(LocalSetupFile.GetRoot()->GetName() != wxT("ERYA-Profiling_Setup"))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("ERYA-Profiling Configuration File is invalid!\nThe program will start the Configuration Wizard..."), wxT("Setup File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
   // Begins the file processing
  wxXmlNode *SetupLabel = LocalSetupFile.GetRoot()->GetChildren();
  while(SetupLabel)
  {
   if(SetupLabel->GetName() == wxT("Setup_Contents"))
   {
    wxXmlNode *SetupNode = SetupLabel->GetChildren();
    while(SetupNode)
    {
      if(SetupNode->GetName() == wxT("Databases_Directory")) //Load the default database directory
      {
        wxXmlNode *DirectoryValue = SetupNode->GetChildren();
        if(DirectoryValue->GetName() == wxT("value"))
         {
           MainDirectory = DirectoryValue->GetNodeContent();
         }
      }
      if(SetupNode->GetName() == wxT("Detector_Setup")) //Load the default detector settings
      {
        wxXmlNode *DetectorValue = SetupNode->GetChildren();
        if(DetectorValue->GetName() == wxT("value"))
         {
           MainDetector = DetectorValue->GetNodeContent();
         }
      }
      if(SetupNode->GetName() == wxT("Databases_Elements")) //Load the default database contents
      {
        wxXmlNode *DatabaseValue = SetupNode->GetChildren();
        if(DatabaseValue->GetName() == wxT("value"))
         {
           MainDatabase = DatabaseValue->GetNodeContent();
         }
      }
      if(SetupNode->GetName() == wxT("Ziegler_Parameters")) //Load the default Ziegler parameters
      {
        wxXmlNode *ZieglerValue = SetupNode->GetChildren();
        if(ZieglerValue->GetName() == wxT("value"))
         {
           MainZiegler = ZieglerValue->GetNodeContent();
         }
      }
     SetupNode = SetupNode->GetNext();
    }
   }
   SetupLabel = SetupLabel->GetNext();
  }
 return true;
}

bool ERYAProfilingERYAProfilingMain::SaveSetupFile(wxString MainDirectory, wxString MainDetector, wxString MainDatabase, wxString MainZiegler, bool LocalSetting)
{
 // Get the current time
  wxDateTime ThisTime = wxDateTime::Now();
  wxString ActualTime =ThisTime.Format(wxT("%Y-%m-%dT%H:%M:%S.00Z"),wxDateTime::WET);
  // Get the two compatible name paths
  wxString fileconfig = ::wxStandardPaths::Get().GetExecutablePath();
  wxFileName mainconfig(fileconfig);
  wxString rootconfig = mainconfig.GetPath();
  wxString pathconfig = rootconfig;
  wxString nameconfig = mainconfig.GetName();
  wxString standardconfig = ::wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + nameconfig + wxT(".conf");
  wxString portableconfig = ::wxStandardPaths::Get().GetExecutablePath() + wxT(".conf");
  wxString controltag;
  wxString configfile;
  if(LocalSetting)
  {
   controltag = wxT("true");
   wxString localpathconfig = ::wxStandardPaths::Get().GetUserLocalDataDir();
   wxMkDir(localpathconfig,wxS_DIR_DEFAULT);
   configfile = standardconfig;
  }
  else
  {
   controltag = wxT("false");
   configfile = portableconfig;
  }
  // An xml file when written, all node are declared backwarks, but any atribute of the same node should be declared forwards
  wxXmlDocument LocalSetup;
  wxXmlNode* setup = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Setup");
  LocalSetup.SetRoot(setup);
  // save file data
  wxXmlNode* setupdata = new wxXmlNode(setup, wxXML_ELEMENT_NODE, "Setup_Contents");
  wxXmlNode* mainzig = new wxXmlNode(setupdata, wxXML_ELEMENT_NODE, "Ziegler_Parameters");
   wxXmlNode *valuezig = new wxXmlNode(mainzig, wxXML_ELEMENT_NODE, "value");
    valuezig->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, MainZiegler));
  wxXmlNode* maindat = new wxXmlNode(setupdata, wxXML_ELEMENT_NODE, "Databases_Elements");
   wxXmlNode *valuedat = new wxXmlNode(maindat, wxXML_ELEMENT_NODE, "value");
    valuedat->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, MainDatabase));
  wxXmlNode* maindet = new wxXmlNode(setupdata, wxXML_ELEMENT_NODE, "Detector_Setup");
   wxXmlNode *valuedet = new wxXmlNode(maindet, wxXML_ELEMENT_NODE, "value");
    valuedet->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, MainDetector));
  wxXmlNode* maindir = new wxXmlNode(setupdata, wxXML_ELEMENT_NODE, "Databases_Directory");
   wxXmlNode *valuedir = new wxXmlNode(maindir, wxXML_ELEMENT_NODE, "value");
    valuedir->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, MainDirectory));
  wxXmlNode* maindef = new wxXmlNode(setupdata, wxXML_ELEMENT_NODE, "Databases_Default");
   wxXmlNode *valuedef = new wxXmlNode(maindef, wxXML_ELEMENT_NODE, "value");
    valuedef->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, controltag));
  // Save file header
  wxXmlNode* fileversion = new wxXmlNode(setup, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programfilename = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Actual_File_Name");
     programfilename->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, configfile));
   wxXmlNode* programdatetime = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Date_File_Creation");
     programdatetime->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ActualTime));
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.40")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
  // Save the file
  return LocalSetup.Save(configfile,0);
}

bool ERYAProfilingERYAProfilingMain::DeleteSetupFile()
{
// Get the potential setup file on root directory (for portable installations, and local profile folders)
     wxString fileconfig = ::wxStandardPaths::Get().GetExecutablePath();
     wxFileName mainconfig(fileconfig);
     wxString rootconfig = mainconfig.GetPath();
     wxString nameconfig = mainconfig.GetName();
     wxString CheckLocalSetupFileName = ::wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + nameconfig + wxT(".conf");
     wxString CheckRootSetupFileName = ::wxStandardPaths::Get().GetExecutablePath() + wxT(".conf");
     wxString CheckUserProfileFolder = ::wxStandardPaths::Get().GetUserLocalDataDir();
   if(wxFileExists(CheckRootSetupFileName))
   {
   if(!(wxRemoveFile(CheckRootSetupFileName)))
    {
     wxMessageDialog *error = new wxMessageDialog(NULL, wxT("Cannot delete file at ") + CheckRootSetupFileName + wxT("\nSince it was protected."), wxT("Error: Protected Folder"), wxOK | wxICON_ERROR);
     error->ShowModal();
     return false;
    }
   }
   if(wxFileExists(CheckLocalSetupFileName))
   {
    if(!(wxRemoveFile(CheckLocalSetupFileName)))
    {
     wxMessageDialog *error = new wxMessageDialog(NULL, wxT("Cannot delete file at ") + CheckLocalSetupFileName + wxT("\nSince it was protected."), wxT("Error: Protected Folder"), wxOK | wxICON_ERROR);
     error->ShowModal();
     return false;
    }
   }
   if(wxDirExists(CheckUserProfileFolder))
   {
     wxString TestFileName = wxFindFirstFile(CheckUserProfileFolder + wxFileName::GetPathSeparator() + wxT("*.*"));
     do
     {
      if(wxFileExists(CheckUserProfileFolder + wxFileName::GetPathSeparator() + TestFileName))
      {
       if(!(wxRemoveFile(CheckUserProfileFolder + wxFileName::GetPathSeparator() + TestFileName)))
       {
     wxMessageDialog *error = new wxMessageDialog(NULL, wxT("Cannot delete file at ") + CheckUserProfileFolder + wxFileName::GetPathSeparator() + TestFileName + wxT("\nSince it was protected."), wxT("Error: Protected Folder"), wxOK | wxICON_ERROR);
     error->ShowModal();
       return false;
       }
      }
      TestFileName = wxFindNextFile();
     }while(TestFileName.Len()>0);
    if(!(wxFileName::Rmdir(CheckUserProfileFolder,wxPATH_RMDIR_RECURSIVE)))
    {
     wxMessageDialog *error = new wxMessageDialog(NULL, wxT("Cannot delete folder ") + CheckUserProfileFolder + wxT("\nSince it was protected."), wxT("Error: Protected Folder"), wxOK | wxICON_ERROR);
     error->ShowModal();
     return false;
    }
   }
   return true;
}

bool ERYAProfilingERYAProfilingMain::ReplaceSetupFile()
{
// Get the potential setup file on root directory (for portable installations, and local profile folders)
     wxString fileconfig = ::wxStandardPaths::Get().GetExecutablePath();
     wxFileName mainconfig(fileconfig);
     wxString rootconfig = mainconfig.GetPath();
     wxString nameconfig = mainconfig.GetName();
     wxString CheckLocalSetupFileName = ::wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + nameconfig + wxT(".conf");
     wxString CheckRootSetupFileName = ::wxStandardPaths::Get().GetExecutablePath() + wxT(".conf");
     wxString CheckUserProfileFolder = ::wxStandardPaths::Get().GetUserLocalDataDir();
   if(wxFileExists(CheckRootSetupFileName))
   {
   if(!(wxRemoveFile(CheckRootSetupFileName)))
    {
     wxMessageDialog *error = new wxMessageDialog(NULL, wxT("Cannot delete file at ") + CheckRootSetupFileName + wxT("\nSince it was protected."), wxT("Error: Protected Folder"), wxOK | wxICON_ERROR);
     error->ShowModal();
     return false;
    }
   }
   if(wxFileExists(CheckLocalSetupFileName))
   {
    if(!(wxRemoveFile(CheckLocalSetupFileName)))
    {
     wxMessageDialog *error = new wxMessageDialog(NULL, wxT("Cannot delete file at ") + CheckLocalSetupFileName + wxT("\nSince it was protected."), wxT("Error: Protected Folder"), wxOK | wxICON_ERROR);
     error->ShowModal();
     return false;
    }
   }
   return true;
}

