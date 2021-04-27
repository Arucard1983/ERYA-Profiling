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
  if(!(this->DisplaySlot(ViewerSlot-1)))
    this->DisplaySlot(ViewerSlot);
 }
}

void ERYAProfilingdialogERYAProfilingViewer::OnEnergyNext( wxCommandEvent& event )
{
 if(this->FindSlot(ViewerSlot+1))
 {
  if(!(this->DisplaySlot(ViewerSlot+1)))
    this->DisplaySlot(ViewerSlot);
 }
}

void ERYAProfilingdialogERYAProfilingViewer::OnLayerMinus( wxCommandEvent& event )
{
 int value = this->FindPrevSlot(ViewerSlot);
 this->DisplaySlot(value);
}

void ERYAProfilingdialogERYAProfilingViewer::OnLayerPlus( wxCommandEvent& event )
{
 int value = this->FindNextSlot(ViewerSlot);
 this->DisplaySlot(value);
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
 if(adress<GridDataNumber)
    return true;
 else
    return false;
}

// Find the adress of previous major energy register
int ERYAProfilingdialogERYAProfilingViewer::FindPrevSlot(int adress)
{
 if(this->FindSlot(adress))
 {
   double InitialEnergy;
   wxString InitialData = ViewerData->GetCellValue(adress,0);
   int InitialAdress = 0;
   if(InitialData.ToDouble(&InitialEnergy))
   {
     for(int i=0; i<adress-1; i++)
     {
       double CurrentEnergy,CurrentEnergy1;
       wxString CurrentData = ViewerData->GetCellValue(i,0);
       wxString CurrentData1 = ViewerData->GetCellValue(i+1,0);
       if(CurrentData.ToDouble(&CurrentEnergy) && CurrentData1.ToDouble(&CurrentEnergy1))
       {
         if(CurrentEnergy!=CurrentEnergy1) // found a different initial energy value
         {
           if(CurrentEnergy1==InitialEnergy) // The previous energy value are the wanted one
            return InitialAdress;
           else
            InitialAdress = i+1;
         }
       }
       else
       {
           return adress;
       }
     }
     return adress;
   }
   else
   {
     return adress;
   }
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
   double InitialEnergy;
   wxString InitialData = ViewerData->GetCellValue(adress,0);
   int InitialAdress = adress;
   if(InitialData.ToDouble(&InitialEnergy))
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
           if(CurrentEnergy==InitialEnergy) // The next energy value are the wanted one
            return i+1;
         }
       }
       else
       {
           return adress;
       }
     }
     return adress;
   }
   else
   {
     return adress;
   }
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
 unsigned int CP,G,L,VE,VM,VA,NT;
 bool EL;
 Parent->GetPrecisionParameters(CP,G,VM,VE,VA,L,NT,EL);
  // Retrieve the Laudau parameters
  double E0,E1,Delta,K,Xi,Beta;
  wxString E0D = ViewerData->GetCellValue(adress,0);
  wxString E1D = ViewerData->GetCellValue(adress,3);
  wxString KD = ViewerData->GetCellValue(adress,6);
  wxString XD = ViewerData->GetCellValue(adress,8);
  wxString BD = ViewerData->GetCellValue(adress,9);
  E0D.ToDouble(&E0);
  E1D.ToDouble(&E1);
  KD.ToDouble(&K);
  XD.ToDouble(&Xi);
  BD.ToDouble(&Beta);
  Delta = E0 - E1;
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
   X.push_back(LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Distribution"),mpALIGN_BORDER_LEFT,false);
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
     renderViewer->Fit(LM,LX,0.0,1.0);
  }
  else if(K>0 && K<0.02) //Landau Distribution
  {
  LandauFunction l;
  l.SetLandauStep(Xi,Beta,K,Delta,L,false);
  double LS = l.GetLandauStep();
  double LM = l.GetLandauMinimum();
  double LX = l.GetLandauMaximum();
  //Get the function plot
  std::vector<double> Y,X,L;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   double arg = LM+1.0*i*LS;
   double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002);
   double lambda = (arg-Delta)/Xi - 1 + euler - Beta*Beta - std::log(K);
   X.push_back(LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
   L.push_back(lambda);
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Distribution"),mpALIGN_BORDER_LEFT,false);
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
     renderViewer->Fit(LM,LX,0.0,0.2);
  }
  else if(K>=0.02 && K<0.24) //Vavilov-Moyal Distribution
  {
  VavilovMoyalFunction l;
  l.SetMoyalStep(Xi,Beta,K,Delta,VM,false);
  double LS = l.GetMoyalStep();
  double LM = l.GetMoyalMinimum();
  double LX = l.GetMoyalMaximum();
  //Get the function plot
  std::vector<double> Y,X,L;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   double arg = LM+1.0*i*LS;
   double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002);
   double lambda = (arg-Delta)/Xi - 1 + euler - Beta*Beta - std::log(K);
   X.push_back(LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
   L.push_back(lambda);
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Distribution"),mpALIGN_BORDER_LEFT,false);
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
     renderViewer->Fit(LM,LX,0.0,0.2);
  }
  else if(K>=0.02 && K<0.24) //Vavilov-Moyal Distribution
  {
  VavilovMoyalFunction l;
  l.SetMoyalStep(Xi,Beta,K,Delta,VM,false);
  double LS = l.GetMoyalStep();
  double LM = l.GetMoyalMinimum();
  double LX = l.GetMoyalMaximum();
  //Get the function plot
  std::vector<double> Y,X,L;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   double arg = LM+1.0*i*LS;
   double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002);
   double lambda = (arg-Delta)/Xi - 1 + euler - Beta*Beta - std::log(K);
   X.push_back(LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
   L.push_back(lambda);
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Distribution"),mpALIGN_BORDER_LEFT,false);
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
     renderViewer->Fit(LM,LX,0.0,0.2);
  }
  else if(K>=0.24 && K<22.00) //Vavilov-Airy Distribution
  {
  VavilovEdgeworthFunction l;
  l.SetEdgeworthStep(Xi,Beta,K,Delta,VA,false);
  double LS = l.GetEdgeworthStep();
  double LM = l.GetEdgeworthMinimum();
  double LX = l.GetEdgeworthMaximum();
  //Get the function plot
  std::vector<double> Y,X,L;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   double arg = LM+1.0*i*LS;
   double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002);
   double lambda = (arg-Delta)/Xi - 1 + euler - Beta*Beta - std::log(K);
   X.push_back(LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
   L.push_back(lambda);
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Distribution"),mpALIGN_BORDER_LEFT,false);
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
     renderViewer->Fit(LM,LX,0.0,0.2);
  }
  else if(K>=22.00 && K<25.00) //Vavilov-Edgeworth Distribution
  {
  VavilovEdgeworthFunction l;
  l.SetEdgeworthStep(Xi,Beta,K,Delta,VE,false);
  double LS = l.GetEdgeworthStep();
  double LM = l.GetEdgeworthMinimum();
  double LX = l.GetEdgeworthMaximum();
  //Get the function plot
  std::vector<double> Y,X,L;
  int NumberPlots = std::ceil((LX-LM)/LS);
  for(int i=0; i<=NumberPlots; i++)
  {
   double arg = LM+1.0*i*LS;
   double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002);
   double lambda = (arg-Delta)/Xi - 1 + euler - Beta*Beta - std::log(K);
   X.push_back(LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
   L.push_back(lambda);
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Distribution"),mpALIGN_BORDER_LEFT,false);
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
     renderViewer->Fit(LM,LX,0.0,0.2);
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
   X.push_back(LM+1.0*i*LS);
   Y.push_back(l.GetValue(LM+1.0*i*LS));
  }
  // Format the axes and plot
     mpFXYVector* data = new mpFXYVector();
     data->SetData(X,Y);
     mpLayer *axeEnergy = new mpScaleX(wxT("Energy (keV)"),mpALIGN_BORDER_BOTTOM,false);
     mpLayer *axeYield = new mpScaleY(wxT("Distribution"),mpALIGN_BORDER_LEFT,false);
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
     renderViewer->Fit(LM,LX,0.0,0.4);
  }
  return true;
}
