// Straggling distributions Viewer, mainly for diagnostic tests.

#include "ERYAProfilingdialogERYAProfilingViewer.h"
#include "ERYAProfilingERYAProfilingMain.h"
#include "SpecialFunctionsLibrary.h"

ERYAProfilingdialogERYAProfilingViewer::ERYAProfilingdialogERYAProfilingViewer( wxWindow* parent )
:
dialogERYAProfilingViewer( parent )
{

}

ERYAProfilingdialogERYAProfilingViewer::ERYAProfilingdialogERYAProfilingViewer( wxWindow* parent, wxGrid* data )
:
dialogERYAProfilingViewer( parent )
{
 ViewerData = data;
 ViewerSlot = 0;
 if(this->FindSlot(0)) //Check thepresence of a valid first data
 {
  this->DisplaySlot(0);
 }
 else // Check failure to render the data
 {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Log Data found to be displayed.\nPlease run a new simulation with the log active, and try again."), wxT("Error: Empty Log Data"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    this->Destroy();
 }
}

void ERYAProfilingdialogERYAProfilingViewer::OnEnergyPrevious( wxCommandEvent& event )
{
 if(this->FindSlot(ViewerSlot-1))
 {
    this->DisplaySlot(ViewerSlot-1);
    ViewerSlot=ViewerSlot-1;
 }
}

void ERYAProfilingdialogERYAProfilingViewer::OnEnergyNext( wxCommandEvent& event )
{
 if(this->FindSlot(ViewerSlot+1))
 {
  this->DisplaySlot(ViewerSlot+1);
    ViewerSlot=ViewerSlot+1;
 }
}

void ERYAProfilingdialogERYAProfilingViewer::OnLayerMinus( wxCommandEvent& event )
{
 int value = this->FindPrevSlot(ViewerSlot);
 this->DisplaySlot(value);
 ViewerSlot = value;
}

void ERYAProfilingdialogERYAProfilingViewer::OnLayerPlus( wxCommandEvent& event )
{
 int value = this->FindNextSlot(ViewerSlot);
 this->DisplaySlot(value);
 ViewerSlot = value;
}

// Save the plot to an image file
void ERYAProfilingdialogERYAProfilingViewer::OnTakeScreenshoot( wxCommandEvent& event )
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
  renderViewer->SaveScreenshot(fileDialog.GetPath(), fileType, imgSize, true);
 }
}

void ERYAProfilingdialogERYAProfilingViewer::OnViewerQuit( wxCommandEvent& event )
{
 this->Close();
}

bool ERYAProfilingdialogERYAProfilingViewer::FindSlot(int adress)
{
 int GridDataNumber = ViewerData->GetNumberRows();
 if(adress < 0)
 {
   return false;
 }
 else if(adress<GridDataNumber)
 {
   wxString test = ViewerData->GetCellValue(adress,0);
   if(test.Trim().Len()>0)
    return true;
   else
    return false;
 }
 else
 {
   return false;
 }
}

// Find the adress of previous major energy register
int ERYAProfilingdialogERYAProfilingViewer::FindPrevSlot(int adress)
{
 if(this->FindSlot(adress))
 {
   bool FoundLayer = false;
   for(int i=adress; i>1; i--)
     {
       double CurrentEnergy,CurrentEnergy1;
       wxString CurrentData = ViewerData->GetCellValue(i,0);
       wxString CurrentData1 = ViewerData->GetCellValue(i-1,0);
       if(CurrentData.ToDouble(&CurrentEnergy) && CurrentData1.ToDouble(&CurrentEnergy1) && FoundLayer) // Detected the initial layer of previous energy adress.
       {
         if(CurrentEnergy!=CurrentEnergy1)
           return i;
       }
       else if(CurrentData.ToDouble(&CurrentEnergy) && CurrentData1.ToDouble(&CurrentEnergy1) && !FoundLayer)
       {
         if(CurrentEnergy!=CurrentEnergy1)
           FoundLayer = true; // Set the flag once found the ending of the previous energy adress.
       }
       else
       {
          int x=0; //Bogus
       }
     }
     return 0; // Default value
 }
 else
 {
  return adress;
 }
}

// Find the adress of next major energy register
int ERYAProfilingdialogERYAProfilingViewer::FindNextSlot(int adress)
{
if(this->FindSlot(adress))
 {
   for(int i=adress; i<ViewerData->GetNumberRows()-1; i++)
     {
       double CurrentEnergy,CurrentEnergy1;
       wxString CurrentData = ViewerData->GetCellValue(i,0);
       wxString CurrentData1 = ViewerData->GetCellValue(i+1,0);
       if(CurrentData.ToDouble(&CurrentEnergy) && CurrentData1.ToDouble(&CurrentEnergy1))
       {
         if(CurrentEnergy!=CurrentEnergy1) // found a different initial energy value
         {
            return i+1; // return the next energy layer adress
         }
       }
       else
       {
           return adress; // return the initial argument
       }
     }
     return ViewerData->GetNumberRows()-1; // default value
 }
 else
 {
  return adress;
 }
}

bool ERYAProfilingdialogERYAProfilingViewer::DisplaySlot(int adress)
{
  // Call the parent frame
 ERYAProfilingERYAProfilingMain *Parent = (ERYAProfilingERYAProfilingMain *) GetParent();
 // Copy the precision variables
 unsigned int CP,G,L,VE,VM,VA,CM,NT;
 bool EL;
 Parent->GetPrecisionParameters(CP,G,VM,VE,VA,L,NT,CM,EL);
  // Retrieve the Laudau parameters
  double E0,E1,Delta,K,Xi,Beta;
  wxString E0D = ViewerData->GetCellValue(adress,0);
  wxString E1D = ViewerData->GetCellValue(adress,4);
  wxString DD = ViewerData->GetCellValue(adress,3);
  wxString KD = ViewerData->GetCellValue(adress,6);
  wxString XD = ViewerData->GetCellValue(adress,8);
  wxString BD = ViewerData->GetCellValue(adress,9);
  E0D.ToDouble(&E0);
  E1D.ToDouble(&E1);
  KD.ToDouble(&K);
  XD.ToDouble(&Xi);
  BD.ToDouble(&Beta);
  DD.ToDouble(&Delta);
  // Display the information
  dataViewerInitial->SetValue(E0D);
  dataViewerEnergy->SetValue(E1D);
  dataViewerK->SetValue(KD);
  // Set the correct function
  if(K==0) // Dirac's funcrion
  {
    DiracFunction l;
  double LS = l.GetDiracStep();
  double LM = l.GetDiracMinimum();
  double LX = l.GetDiracMaximum();
  double Step = l.GetDiracStep();
  //Get the function plot
  std::vector<double> Y,X;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   X.push_back(E1+LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Dirac\nDistribution"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(true);
     wxPen plotcolor(*wxBLUE, 3, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderViewer->DelAllLayers(false,true);
     renderViewer->AddLayer(axeEnergy);
     renderViewer->AddLayer(axeYield);
     renderViewer->AddLayer(plot);
     renderViewer->Fit(E1+LM,E1+LX,0.0,3.0);
  }
  else if(K>0 && K<0.02 && NT<2) //Landau Distribution
  {
  LandauFunction l;
  l.SetLandauStep(Xi,Beta,K,Delta,L,false);
  double LS = l.GetLandauStep();
  double LM = l.GetLandauMinimum();
  double LX = l.GetLandauMaximum();
  //Get the function plot
  std::vector<double> Y,X;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   X.push_back(E1+LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Laudau\nDistribution"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(true);
     wxPen plotcolor(*wxBLUE, 3, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderViewer->DelAllLayers(false,true);
     renderViewer->AddLayer(axeEnergy);
     renderViewer->AddLayer(axeYield);
     renderViewer->AddLayer(plot);
     renderViewer->Fit(E1+LM,E1+LX,0.0,0.23);
  }
  else if(K>=0.02 && K<0.39 && NT<2) //Vavilov-Moyal Distribution
  {
  VavilovMoyalFunction l;
  l.SetMoyalStep(Xi,Beta,K,Delta,VM,false);
  double LS = l.GetMoyalStep();
  double LM = l.GetMoyalMinimum();
  double LX = l.GetMoyalMaximum();
  //Get the function plot
  std::vector<double> Y,X;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   X.push_back(E1+LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Moyal\nDistribution"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(true);
     wxPen plotcolor(*wxBLUE, 3, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderViewer->DelAllLayers(false,true);
     renderViewer->AddLayer(axeEnergy);
     renderViewer->AddLayer(axeYield);
     renderViewer->AddLayer(plot);
     renderViewer->Fit(E1+LM,E1+LX,0.0,0.23);
  }
  else if(K>=0.39 && K<22.00 && NT<2) //Vavilov-Airy Distribution
  {
  VavilovAiryFunction l;
  l.SetAiryStep(Xi,Beta,K,Delta,VA,false);
  double LS = l.GetAiryStep();
  double LM = l.GetAiryMinimum();
  double LX = l.GetAiryMaximum();
  //Get the function plot
  std::vector<double> Y,X;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   X.push_back(E1+LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Airy\nDistribution"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(true);
     wxPen plotcolor(*wxBLUE, 3, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderViewer->DelAllLayers(false,true);
     renderViewer->AddLayer(axeEnergy);
     renderViewer->AddLayer(axeYield);
     renderViewer->AddLayer(plot);
     renderViewer->Fit(E1+LM,E1+LX,0.0,0.23);
  }
  else if(K>=22.00 && K<25.00 && NT<2) //Vavilov-Edgeworth Distribution
  {
  VavilovEdgeworthFunction l;
  l.SetEdgeworthStep(Xi,Beta,K,Delta,VE,false);
  double LS = l.GetEdgeworthStep();
  double LM = l.GetEdgeworthMinimum();
  double LX = l.GetEdgeworthMaximum();
  //Get the function plot
  std::vector<double> Y,X;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   X.push_back(E1+LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Edgeworth\nDistribution"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(true);
     wxPen plotcolor(*wxBLUE, 3, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderViewer->DelAllLayers(false,true);
     renderViewer->AddLayer(axeEnergy);
     renderViewer->AddLayer(axeYield);
     renderViewer->AddLayer(plot);
     renderViewer->Fit(E1+LM,E1+LX,0.0,0.23);
  }
  else // Gauss Function
  {
  GaussFunction l;
  double Sigma = std::sqrt(Xi*Xi*(1-Beta*Beta/2)/K);
  l.SetGaussStep(Delta,Sigma,G,false);
  double LS = l.GetGaussStep();
  double LM = l.GetGaussMinimum();
  double LX = l.GetGaussMaximum();
  double AV = (LX + LM)/2;
  //Get the function plot
  std::vector<double> Y,X;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   X.push_back(E1+LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Gaussian\nDistribution"),mpALIGN_BORDER_LEFT,false);
     mpLayer *plot = data;
     plot->SetContinuity(true);
     wxPen plotcolor(*wxBLUE, 3, wxSOLID);
     plot->SetPen(plotcolor);
     axeEnergy->SetDrawOutsideMargins(false);
     axeYield->SetDrawOutsideMargins(false);
     plot->SetDrawOutsideMargins(false);
     // Draw the plot elements on selected frame
     renderViewer->DelAllLayers(false,true);
     renderViewer->AddLayer(axeEnergy);
     renderViewer->AddLayer(axeYield);
     renderViewer->AddLayer(plot);
     renderViewer->Fit(E1+LM,E1+LX,0.0,0.23);
  }
  return true;
}
