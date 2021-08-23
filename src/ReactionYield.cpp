/***************************************************************
 * Name:      ReactionYield.cpp
 * Purpose:   ERYA Reaction Yield implementation
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2016-10-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#include "ReactionYield.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY( ElementArray);
WX_DEFINE_OBJARRAY( LayerArray);
WX_DEFINE_OBJARRAY( YieldArray);
WX_DEFINE_OBJARRAY( SampleArray);


//Ressonance Function main constructor,when a custom macro are defined.
RessonanceFunction::RessonanceFunction(wxString CustomMacro)
{
 CustomRessonanceFunction = AlgebraicFunction(CustomMacro);
 if(CustomRessonanceFunction.GetErrorString().Len()==0)
    {
     if(CustomRessonanceFunction.IsDomainDefined())
     {
      CheckStatus = true;
      ErrorMessage.Clear();
      RFMode = 1;
      GBWmin = CustomRessonanceFunction.GetFunctionMinimum();
      GBWmax = CustomRessonanceFunction.GetFunctionMaximum();
     }
     else // Requires a correct function definition, that is, what is the independent and dependent variables ?
     {
      CheckStatus = false;
      ErrorMessage = wxT("Custom Resonance Function Error:\nA Custom Resonance Function should have:\n1.A defined independent and dependent variable;\n2.A defined left and right independent variable domain.");
     }
    }
    else // Algebraic or syntax errors will halt the fit procedure
    {
      CheckStatus = false;
      ErrorMessage = wxT("Custom Resonance Function Error:\n") + CustomRessonanceFunction.GetErrorString();
    }
}

//Alternative constructor, when a list of several Lorentzian peaks are defined.
//The function domain are defined between the lower peak, and the higher peak.
RessonanceFunction::RessonanceFunction(wxString RessonanceWidth, wxString RessonancePeak, wxString RessonanceEnergy)
{
 if(this->ParseRessonanceList(RessonanceWidth,RessonancePeak,RessonanceEnergy))
 {
   RFMode = 2;
   CheckStatus = true;
   ErrorMessage.Clear();
 }
 else
 {
   CheckStatus = false;
 }
}

RessonanceFunction::RessonanceFunction(wxString RessonanceWidth, wxString RessonancePeak, wxString RessonanceEnergy, wxString RessonanceMinimum, wxString RessonanceMaximum)
{
 if(this->ParseRessonanceList(RessonanceWidth,RessonancePeak,RessonanceEnergy))
 {
  if(RessonanceMinimum.ToDouble(&GBWmin) && RessonanceMaximum.ToDouble(&GBWmax))
  {
   RFMode = 2;
   CheckStatus = true;
   ErrorMessage.Clear();
  }
  else
  {
   CheckStatus = false;
   ErrorMessage = wxT("Data Error: Non-numerical values found on Lorentzian Ressonance Parameters.");
  }
 }
 else
 {
   CheckStatus = false;
 }
}

//Alternative constructor, when a list of several resonance strenghts are defined.
//The function domain are defined between the lower peak, and the higher peak.
RessonanceFunction::RessonanceFunction(wxString RessonanceWidth, wxString RessonanceStrenght, wxString RessonanceEnergy, wxString RessonanceAtomicMass)
{
 if(this->ParseRessonanceList(RessonanceWidth,RessonanceStrenght,RessonanceEnergy))
 {
  if(RessonanceAtomicMass.ToDouble(&GBAtomicMass))
  {
   RFMode = 3;
   CheckStatus = true;
   ErrorMessage.Clear();
  }
  else
  {
   CheckStatus = false;
   ErrorMessage = wxT("Data Error: Non-numerical values found on Lorentzian Ressonance Strenght Parameters.");
  }
 }
 else
 {
   CheckStatus = false;
 }
}

RessonanceFunction::RessonanceFunction(wxString RessonanceWidth, wxString RessonanceStrenght, wxString RessonanceEnergy, wxString RessonanceAtomicMass, wxString RessonanceMinimum, wxString RessonanceMaximum)
{
 if(this->ParseRessonanceList(RessonanceWidth,RessonanceStrenght,RessonanceEnergy))
 {
  if(RessonanceMinimum.ToDouble(&GBWmin) && RessonanceMaximum.ToDouble(&GBWmax) && RessonanceAtomicMass.ToDouble(&GBAtomicMass))
  {
   RFMode = 3;
   CheckStatus = true;
   ErrorMessage.Clear();
  }
  else
  {
   CheckStatus = false;
   ErrorMessage = wxT("Data Error: Non-numerical values found on Lorentzian Ressonance Strenght Parameters.");
  }
 }
 else
 {
   CheckStatus = false;
 }
}


// private function to handle the list of values
bool RessonanceFunction::ParseRessonanceList(wxString RessonanceWidth, wxString RessonancePeak, wxString RessonanceEnergy)
{
 // Parse list of values.
 TextLineParser ListWidth(RessonanceWidth,wxT(","));
 TextLineParser ListPeak(RessonancePeak,wxT(","));
 TextLineParser ListEnergy(RessonanceEnergy,wxT(","));
 wxArrayString TokenWidth = ListWidth.GetUnexcluded();
 wxArrayString TokenPeak = ListPeak.GetUnexcluded();
 wxArrayString TokenEnergy = ListEnergy.GetUnexcluded();
 if(TokenWidth.GetCount() == TokenPeak.GetCount() && TokenPeak.GetCount() == TokenEnergy.GetCount() && TokenEnergy.GetCount()>0 && TokenWidth.GetCount()>0 && TokenPeak.GetCount()>0) //The size should be equal
 {
  for(int k=0; k<TokenEnergy.GetCount(); k++)
  {
    double TBWEnergy, TBWPeak, TBWWidth, TBWmin, TBWmax;
    if(TokenEnergy.Item(k).ToDouble(&TBWEnergy) && TokenPeak.Item(k).ToDouble(&TBWPeak) && TokenWidth.Item(k).ToDouble(&TBWWidth)) // Parse list to a numerical vector
    {
      TBWmin = TBWEnergy - 5 * TBWWidth;
      TBWmax = TBWEnergy + 5 * TBWWidth;
    }
    else
    {
      ErrorMessage = wxT("Data Error: Non-numerical values found on Lorentzian Resonance Parameters.");
      return false;
    }
    BWEnergy.push_back(TBWEnergy); //Add item to the vector
    BWPeak.push_back(TBWPeak);
    BWWidth.push_back(TBWWidth);
    BWmin.push_back(TBWmin);
    BWmax.push_back(TBWmax);
  }
  // Sorting routine, by the Energy Peak, since the user could make such mistake.
   int n = BWEnergy.size();
   for (int i=0; i<n-1; i++)
   {
     for(int j=0; j<n-i-1; j++)
     {
      if (BWEnergy.at(j) > BWEnergy.at(j+1))
      {
      double temp1 = BWEnergy.at(j);
      double temp2 = BWPeak.at(j);
      double temp3 = BWWidth.at(j);
      double temp4 = BWmin.at(j);
      double temp5 = BWmax.at(j);
      BWEnergy.at(j) = BWEnergy.at(j+1);
      BWPeak.at(j) = BWPeak.at(j+1);
      BWWidth.at(j) = BWWidth.at(j+1);
      BWmin.at(j) = BWmin.at(j+1);
      BWmax.at(j) = BWmax.at(j+1);
      BWEnergy.at(j+1) = temp1;
      BWPeak.at(j+1) = temp2;
      BWWidth.at(j+1) = temp3;
      BWmin.at(j+1) = temp4;
      BWmax.at(j+1) = temp5;
      }
     }
   }
  // Get global domain, checking from the list of each individual domains, to find the real global domain, and return once done.
  GBWmin = BWmin.at(0);
  GBWmax = BWmax.at(BWmax.size()-1);
  for(int z1=0; z1<BWmin.size(); z1++)
  {
   if(GBWmin > BWmin.at(z1))
    GBWmin = BWmin.at(z1);
  }
  for(int z2=0; z2<BWmax.size(); z2++)
  {
   if(GBWmax < BWmax.at(z2))
    GBWmax = BWmax.at(z2);
  }
  return true;
 }
 else
 {
  ErrorMessage = wxT("Data Error: Unequal number of list parameters on Lorentzian Resonance Parameters.");
  return false;
 }
}

//Evaluate the Briet-Wigner at a certain energy.
// f(E) = (energy / E) * (peak * width^2 / 4 ) / (width^2 / 4 + (E-energy)^2)
double RessonanceFunction::BrietWigner(double Energy)
{
 if(GBWmin <= Energy && Energy <= GBWmax)
 {
   double BWSum = 0;
   for(int i=0; i<BWEnergy.size(); i++)
   {
    if(BWmin.at(i) <= Energy && Energy <= BWmax.at(i))
     BWSum = BWSum + (BWEnergy.at(i) / Energy) * (BWPeak.at(i) * BWWidth.at(i) * BWWidth.at(i) / 4 ) / (BWWidth.at(i) * BWWidth.at(i) / 4 + std::pow(Energy - BWEnergy.at(i),2));
   }
  return BWSum;
 }
 else
 {
   return 0;
 }
}

//Evaluate the Briet-Wigner with a Resonance Strenght at a certain energy.
// f(E) = (K * strenght * width / 4 )/ (width^2 / 4 + (E-energy)^2)
// where K = 2607472.5 (A+1)/(A*E) mili-barn
double RessonanceFunction::StrenghtEnergy(double Energy)
{
 if(GBWmin <= Energy && Energy <= GBWmax)
 {
   double BWSum = 0;
   for(int i=0; i<BWEnergy.size(); i++)
   {
    if(BWmin.at(i) <= Energy && Energy <= BWmax.at(i))
     BWSum = BWSum + ((BWPeak.at(i) * BWWidth.at(i) * 2607472.5 * (GBAtomicMass + 1) ) / (4 * Energy * GBAtomicMass) ) / (BWWidth.at(i) * BWWidth.at(i) / 4 + std::pow(Energy - BWEnergy.at(i),2));
   }
  return BWSum;
 }
 else
 {
   return 0;
 }
}

//Evaluate the Custom Ressonance Function
double RessonanceFunction::CRFunction(double Energy)
{
 if(CustomRessonanceFunction.IsDomainDefined())
  return CustomRessonanceFunction.GetFyxEval(Energy);
 else
  return 0;
}

//Get the Ressonance function value
double RessonanceFunction::GetValue(double Energy)
{
 if(RFMode == 1)
  return this->CRFunction(Energy);
 else if (RFMode == 2)
  return this->BrietWigner(Energy);
 else if (RFMode == 3)
  return this->StrenghtEnergy(Energy);
 else
  return 0;
}

double RessonanceFunction::GetDomainMinimum()
{
 if(RFMode == 1)
  return CustomRessonanceFunction.GetFunctionMinimum();
 else if (RFMode == 2)
  return GBWmin;
 else if (RFMode == 3)
  return GBWmin;
 else
  return NAN;
}

double RessonanceFunction::GetDomainMaximum()
{
 if(RFMode == 1)
  return CustomRessonanceFunction.GetFunctionMaximum();
 else if (RFMode == 2)
  return GBWmax;
 else if (RFMode == 3)
  return GBWmax;
 else
  return NAN;
}


// Distribution main constructor
PhysicsDistribution::PhysicsDistribution(wxString BeamResolution, wxString Temperature)
{
 if(BeamResolution.Len()>0)
 {
  if(BeamResolution.ToDouble(&AverageBeamResolution))
  {
   IsDefined = true;
   ErrorMessage.Clear();
  }
  else
  {
   IsDefined = false;
   ErrorMessage = wxT("Error: Non-numerical input at the Detector's Beam Resolution.");
  }
 }
 else
 {
  IsDefined = true;
  ErrorMessage.Clear();
  AverageBeamResolution = 0.0; //Default value
 }
 if(Temperature.Len()>0)
 {
  if(Temperature.ToDouble(&ThermalDopplerEnergy))
  {
   IsDefined = true;
   ErrorMessage.Clear();
   ThermalDopplerEnergy = 8.6173303e-8 * ThermalDopplerEnergy; // E=kT, to get the temperature in keV
  }
  else
  {
   IsDefined = false;
   ErrorMessage = wxT("Error: Non-numerical input at the Detector's Sample Temperature.");
  }
 }
 else
 {
  IsDefined = true;
  ErrorMessage.Clear();
  ThermalDopplerEnergy = 2.5e-5; //Default value, T=300 K or 1/40 eV
 }
}

// Obtain the Thermal Doppler variance, that depends from energy and ion mass target
double PhysicsDistribution::GetThermalDoppler(double AtEnergy, double TargetMolarMass)
{
 double ProtonMolarMass = 1.007276;
 double RatioMolarMass = ProtonMolarMass / TargetMolarMass; //non-dimensional parameter
 AverageDopplerEnergy = 2.355 * std::sqrt(2 * RatioMolarMass * AtEnergy * ThermalDopplerEnergy); //keV
 return AverageDopplerEnergy; //Requires to store the last value on certain calculations
}

// Set the total distribution, making the convolution of the thermal distribution with the straggling, that requires the following new parameters
bool PhysicsDistribution::SetDistribution(double xi, double beta, double k, double DEM, double VEM, unsigned int Gauss, unsigned int Moyal, unsigned int Edgeworth, unsigned int Airy, unsigned int Landau, bool StrictGaussian)
{
 // The thermal distribution is always Gaussian, but if the variance are zero, then collapse to a Dirac's delta.
 double ThermalVariance = std::sqrt(AverageBeamResolution*AverageBeamResolution + AverageDopplerEnergy * AverageDopplerEnergy);
 unsigned int VarianceMode;
 if(std::abs(ThermalVariance)<1e-3)
 {
  ThermalDirac = DiracFunction();
  ThermalStep = ThermalDirac.GetDiracStep();
  ThermalMinimum = ThermalDirac.GetDiracMinimum();
  ThermalMaximum = ThermalDirac.GetDiracMaximum();
  VarianceMode = 0;
 }
 else
 {
  ThermalFunction = GaussFunction();
  ThermalFunction.SetGaussStep(0.0,ThermalVariance,Gauss,false);
  ThermalStep = ThermalFunction.GetGaussStep();
  ThermalMinimum = ThermalFunction.GetGaussMinimum();
  ThermalMaximum = ThermalFunction.GetGaussMaximum();
  VarianceMode = 6;
 }
 // The second distribution depends from the actual value of k-factor
  if (StrictGaussian) // Applies the Gaussian Distribution for k>0
  {
    if(k==0) //happens on first layer.
    {
    StraggDirac = DiracFunction();
    StraggStep = StraggDirac.GetDiracStep();
    StraggMaximum = StraggDirac.GetDiracMaximum();
    StraggMinimum = StraggDirac.GetDiracMinimum();
    PDMode = 0 + VarianceMode;
    return true;
    }
    else
    {
      //Gauss Distribution
     if (VEM <= 0) //It collapses to a Dirac's Delta
     {
     StraggDirac = DiracFunction();
     StraggStep = StraggDirac.GetDiracStep();
     StraggMaximum = StraggDirac.GetDiracMaximum();
     StraggMinimum = StraggDirac.GetDiracMinimum();
     PDMode = 0 + VarianceMode;
     return true;
     }
     else
     {
     StraggGauss = GaussFunction();
     StraggGauss.SetGaussStep(DEM,VEM,Gauss,false);
     StraggStep = StraggGauss.GetGaussStep();
     StraggMaximum = StraggGauss.GetGaussMaximum();
     StraggMinimum = StraggGauss.GetGaussMinimum();
     PDMode = 5 + VarianceMode;
     return true;
     }
    }
  }
  else
  {
   if(k==0) //happens on first layer.
   {
    StraggDirac = DiracFunction();
    StraggStep = StraggDirac.GetDiracStep();
    StraggMaximum = StraggDirac.GetDiracMaximum();
    StraggMinimum = StraggDirac.GetDiracMinimum();
    PDMode = 0 + VarianceMode;
    return true;
   }
   else if(k>0 && k<0.02) //Landau Distribution
   {
    StraggLandau = LandauFunction();
    StraggLandau.SetLandauStep(xi,beta,k,DEM,Landau,false);
    StraggStep = StraggLandau.GetLandauStep();
    StraggMaximum = StraggLandau.GetLandauMaximum();
    StraggMinimum = StraggLandau.GetLandauMinimum();
    PDMode = 1 + VarianceMode;
    return true;
   }
   else if(k>=0.02 && k<0.24) //Vavilov-Moyal Distribution
   {
    StraggMoyal = VavilovMoyalFunction();
    StraggMoyal.SetMoyalStep(xi,beta,k,DEM,Moyal,false);
    StraggStep = StraggMoyal.GetMoyalStep();
    StraggMaximum = StraggMoyal.GetMoyalMaximum();
    StraggMinimum = StraggMoyal.GetMoyalMinimum();
    PDMode = 2 + VarianceMode;
    return true;
   }
   else if(k>=0.24 && k<22.00) //Vavilov-Airy Distribution
   {
    StraggAiry = VavilovAiryFunction();
    StraggAiry.SetAiryStep(xi,beta,k,DEM,Airy,false);
    StraggStep = StraggAiry.GetAiryStep();
    StraggMaximum = StraggAiry.GetAiryMaximum();
    StraggMinimum = StraggAiry.GetAiryMinimum();
    PDMode = 3 + VarianceMode;
    return true;
   }
   else if(k>=22.00 && k<25.00) //Vavilov-Edgeworth Distribution
   {
    StraggEdgeworth = VavilovEdgeworthFunction();
    StraggEdgeworth.SetEdgeworthStep(xi,beta,k,DEM,Edgeworth,false);
    StraggStep = StraggEdgeworth.GetEdgeworthStep();
    StraggMaximum = StraggEdgeworth.GetEdgeworthMaximum();
    StraggMinimum = StraggEdgeworth.GetEdgeworthMinimum();
    PDMode = 4 + VarianceMode;
    return true;
   }
   else
   {
    //Gauss Distribution
    if (VEM <= 0) //It collapses to a Dirac's Delta
    {
     StraggDirac = DiracFunction();
     StraggStep = StraggDirac.GetDiracStep();
     StraggMaximum = StraggDirac.GetDiracMaximum();
     StraggMinimum = StraggDirac.GetDiracMinimum();
     PDMode = 0 + VarianceMode;
     return true;
    }
    else
    {
     StraggGauss = GaussFunction();
     StraggGauss.SetGaussStep(DEM,VEM,Gauss,false);
     StraggStep = StraggGauss.GetGaussStep();
     StraggMaximum = StraggGauss.GetGaussMaximum();
     StraggMinimum = StraggGauss.GetGaussMinimum();
     PDMode = 5 + VarianceMode;
     return true;
    }
   }
  }
  return false;
}


// Get the distribution at an certain point
double PhysicsDistribution::GetValue(double StraggEnergy, double ThermalEnergy)
{
  if(PDMode ==0)
   return ThermalDirac.GetValue(ThermalEnergy) * StraggDirac.GetValue(StraggEnergy);
  if(PDMode ==1)
   return ThermalDirac.GetValue(ThermalEnergy) * StraggLandau.GetValue(StraggEnergy);
  if(PDMode ==2)
   return ThermalDirac.GetValue(ThermalEnergy) * StraggMoyal.GetValue(StraggEnergy);
  if(PDMode ==3)
   return ThermalDirac.GetValue(ThermalEnergy) * StraggAiry.GetValue(StraggEnergy);
  if(PDMode ==4)
   return ThermalDirac.GetValue(ThermalEnergy) * StraggEdgeworth.GetValue(StraggEnergy);
  if(PDMode ==5)
   return ThermalDirac.GetValue(ThermalEnergy) * StraggGauss.GetValue(StraggEnergy);
  if(PDMode ==6)
   return ThermalFunction.GetValue(ThermalEnergy) * StraggDirac.GetValue(StraggEnergy);
  if(PDMode ==7)
   return ThermalFunction.GetValue(ThermalEnergy) * StraggLandau.GetValue(StraggEnergy);
  if(PDMode ==8)
   return ThermalFunction.GetValue(ThermalEnergy) * StraggMoyal.GetValue(StraggEnergy);
  if(PDMode ==9)
   return ThermalFunction.GetValue(ThermalEnergy) * StraggAiry.GetValue(StraggEnergy);
  if(PDMode ==10)
   return ThermalFunction.GetValue(ThermalEnergy) * StraggEdgeworth.GetValue(StraggEnergy);
  if(PDMode ==11)
   return ThermalFunction.GetValue(ThermalEnergy) * StraggGauss.GetValue(StraggEnergy);
  else
   return 0;
}

// Detector Default Constructor
Detector::Detector(DetectorParameters DetectorSetup)
{
 if (DetectorSetup.GetDetectorEnergy().GetCount()>0)  // Get the mandatory pair of Energy,Sigma data
 {
   Energy.clear();
   Sigma.clear();
   for (int i=0;i<DetectorSetup.GetDetectorEnergy().GetCount();i++)
   {
     double temp1,temp2; // Notice the conversion inside the vector !!! Otherwise it would get random numbers!!!
     wxString stemp1 = DetectorSetup.GetDetectorEnergy().Item(i);
     wxString stemp2 = DetectorSetup.GetDetectorEfficiency().Item(i);
     if(stemp1.ToDouble(&temp1) && stemp2.ToDouble(&temp2))
     {
      Energy.push_back(temp1);
      Sigma.push_back(temp2);
     }
     else
     {
       Sucess = false;
       Energy.clear();
       Sigma.clear();
       break;
     }
   }
   // Sorting routine for Energy/Sigma vector
   int n = Energy.size();
   for (int i=0; i<n-1; i++)
   {
     for(int j=0; j<n-i-1; j++)
     {
      if (Energy.at(j) > Energy.at(j+1))
      {
      double temp1 = Energy.at(j);
      double temp2 = Sigma.at(j);
      Energy.at(j) = Energy.at(j+1);
      Sigma.at(j) = Sigma.at(j+1);
      Energy.at(j+1) = temp1;
      Sigma.at(j+1) = temp2;
      }
     }
   }
   // Handles a user-defined fitting function
   if(DetectorSetup.GetDetectorFunction().Len() == 0) //Handles the empty function case, which is fine, as long exists interpolation data.
   {
    if(Energy.size()>0 && Sigma.size()>0)
    {
     Sucess = true;
     DefinedFunction = false;
    }
    else
    {
     Sucess = false;
    ErrorCode = wxT("Detector Setup Error: Empty Detector Profile Data to handle!");
    }
   }
   else // Parse the custom-defined function
   {
    DetectorFittingFunction = AlgebraicFunction(DetectorSetup.GetDetectorFunction());
    if (DetectorFittingFunction.GetErrorString().Len() == 0)
    {
     if(DetectorFittingFunction.IsFunctionDefined())
     {
      Sucess = true;
      DefinedFunction = true;
     }
     else // Requires a correct function definition, that is, what is the independent and dependent variables ?
     {
      Sucess = false;
      ErrorCode = wxT("Detector Setup Error:\n") + DetectorFittingFunction.GetErrorString();
     }
    }
    else // Algebraic or syntax errors will halt the fit procedure
    {
      Sucess = false;
      ErrorCode = wxT("Detector Setup Error:\n") + DetectorFittingFunction.GetErrorString();
    }
   }
 }
 else    // You cannot evaluate anything without the Detector Database!
 {
   Sucess = false;
   ErrorCode = wxT("Detector Setup Error: Detector Data Empty!");
 }
}


// Evaluate the numerical result of the function, when an argument is issued
double Detector::GetEval(double arg)
{
  if (DefinedFunction && arg>0)    // Get the energy value, if a fitting function was provided
  {
   double FunctionResult = DetectorFittingFunction.GetFyxEval(arg);
   if(std::isfinite(FunctionResult))
    return FunctionResult;
   else
    return 0; // Avoid overflows, by setting at out-of-boundary result to zero, since the yield will be reset to zero.
  }
  else if ( !DefinedFunction && Energy.size()>0 && arg > 0)   // If any fitting function was not provided, the only hope is to interpolate two pairs of neighbors points
  {
   double epsilon1,epsilon2,E1,E2;
   if (Energy.at(0)>arg && Energy.at(Energy.size()-1)<arg)  // If the point was outside the boundaries, the final result will be set to zero.
   {
   for (int i=0; i<Energy.size(); i++)  // In some situations, some gamma points matches exactly at some element of main table
    {
    if (Energy.at(i) == arg)
     {
       return Sigma.at(i);
     }
    }
   for (int j=0; j<Energy.size() - 1; j++)  // But in general situations, it is necessary to interpolate two points.
    {
    if (Energy.at(j)<arg && arg<Energy.at(j+1))
     {
      E1 = Energy.at(j);
      E2 = Energy.at(j+1);
      epsilon1 = Sigma.at(j);
      epsilon2 = Sigma.at(j+1);
      double slope = (arg - E1)/(E2 - E1);
      double linear = epsilon1 + slope*(epsilon2 - epsilon1);
      return linear;
     }
    }
    return 0;
   }
   else
  {
   return 0;
  }
  }
  else
  {
   return 0;
  }
}


// Store the elements parameters in pure numerical forms
void Element::CreateElement(ElementDatabase ThisElement, ZieglerParameters ThisZiegler, ElementSRIMArray ThisSRIM, wxString StoichiometricGuess)
{
  // Convert the original table of strings to form a numerical table it's straightforward
  StoichiometricGuess.ToDouble(&Stoichiometry);
  Symbol = ThisElement.GetElement();
  ThisElement.GetGamma().ToDouble(&GammaPeak);
  ThisElement.GetNumber().ToLong(&Number);
  ThisElement.GetAbundance().ToDouble(&Abundance);
  if (ThisElement.GetAtomic().Len()>0)
  {
   ThisElement.GetAtomic().ToDouble(&Atomic);
  }
   else
  {
   ThisZiegler.GetZieglerMass().Item(Number-1).ToDouble(&Atomic);
  }
  ThisElement.GetIsotopic().ToDouble(&Isotopic);
  ThisZiegler.GetZieglerDensity().Item(Number-1).ToDouble(&Density);
  ThisZiegler.GetZieglerBloch().Item(Number-1).ToDouble(&Bloch);
  Energy.clear();
  EnergyError.clear();
  Sigma.clear();
  SigmaError.clear();
  for(int i=0; i<ThisElement.GetEnergy().GetCount(); i++)
  {
    double temp1, temp2, temp3, temp4;
    if(ThisElement.GetEnergy().Item(i).ToDouble(&temp1) && ThisElement.GetEnergyError().Item(i).ToDouble(&temp2) && ThisElement.GetSigma().Item(i).ToDouble(&temp3) && ThisElement.GetSigmaError().Item(i).ToDouble(&temp4))
    {
      Energy.push_back(temp1);
      EnergyError.push_back(temp2);
      Sigma.push_back(temp3);
      SigmaError.push_back(temp4);
    }
  }
  // Sorting routine for Energy vector
   int n = Energy.size();
   for (int i=0; i<n-1; i++)
   {
     for(int j=0; j<n-i-1; j++)
     {
      if (Energy.at(j) > Energy.at(j+1))
      {
      double temp1 = Energy.at(j);
      double temp3 = Sigma.at(j);
      double temp2 = EnergyError.at(j);
      double temp4 = SigmaError.at(j);
      Energy.at(j) = Energy.at(j+1);
      Sigma.at(j) = Sigma.at(j+1);
      EnergyError.at(j) = EnergyError.at(j+1);
      SigmaError.at(j) = SigmaError.at(j+1);
      Energy.at(j+1) = temp1;
      Sigma.at(j+1) = temp3;
      EnergyError.at(j+1) = temp2;
      SigmaError.at(j+1) = temp4;
      }
     }
   }
  // Load the adequate SRIM table from the database
  int ZNumber = static_cast<int>(Number);
  int ZAdress = ThisSRIM.GetElementAdress(ZNumber);
  if((ThisSRIM.GetElementAdress(ZNumber) != wxNOT_FOUND) && (ThisSRIM.Item(ZAdress).GetElementEnergy().GetCount() == ThisSRIM.Item(ZAdress).GetElementStoppingPower().GetCount()))
  {
    SRIMEnergy.clear(); //Once confirmed the existence, load and convert the original data into an array of vectors.
    SRIMStoppingPower.clear();
    for (int k=0; k<ThisSRIM.Item(ZAdress).GetElementEnergy().GetCount(); k++)
    {
      double temp0,temp1;
      wxString c0 = ThisSRIM.Item(ZAdress).GetElementEnergy().Item(k);
      wxString c1 = ThisSRIM.Item(ZAdress).GetElementStoppingPower().Item(k);
      if(c0.ToDouble(&temp0) && c1.ToDouble(&temp1)) //If the pair of values are numerical data, just copy it.
      {
        SRIMEnergy.push_back(temp0);
        SRIMStoppingPower.push_back(temp1);
      }
    }
    // Sorting routine
    int n = SRIMEnergy.size();
    for (int i=0; i<n-1; i++)
    {
     for(int j=0; j<n-i-1; j++)
     {
      if (SRIMEnergy.at(j) > SRIMEnergy.at(j+1))
      {
      double temp1 = SRIMEnergy.at(j);
      double temp2 = SRIMStoppingPower.at(j);
      SRIMEnergy.at(j) = SRIMEnergy.at(j+1);
      SRIMStoppingPower.at(j) = SRIMStoppingPower.at(j+1);
      SRIMEnergy.at(j+1) = temp1;
      SRIMStoppingPower.at(j+1) = temp2;
      }
     }
    }
  }
  else //Without SRIM data, the vectors are left empty
  {
    SRIMEnergy.clear();
    SRIMStoppingPower.clear();
  }
  // Load the adequate Ziegler parameters from the database
  if (ThisZiegler.GetZieglerElements().GetCount()>Number)
   {
     ThisZiegler.GetZieglerVersion().ToLong(&ZieglerModel);
     ZieglerTable.clear();
     double temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11, temp12;
     if(ThisZiegler.GetZieglerValues1().Item(Number-1).ToDouble(&temp1))
         ZieglerTable.push_back(temp1);
     if(ThisZiegler.GetZieglerValues2().Item(Number-1).ToDouble(&temp2))
         ZieglerTable.push_back(temp2);
     if(ThisZiegler.GetZieglerValues3().Item(Number-1).ToDouble(&temp3))
         ZieglerTable.push_back(temp3);
     if(ThisZiegler.GetZieglerValues4().Item(Number-1).ToDouble(&temp4))
         ZieglerTable.push_back(temp4);
     if(ThisZiegler.GetZieglerValues5().Item(Number-1).ToDouble(&temp5))
         ZieglerTable.push_back(temp5);
     if(ThisZiegler.GetZieglerValues6().Item(Number-1).ToDouble(&temp6))
         ZieglerTable.push_back(temp6);
     if(ThisZiegler.GetZieglerValues7().Item(Number-1).ToDouble(&temp7))
         ZieglerTable.push_back(temp7);
     if(ThisZiegler.GetZieglerValues8().Item(Number-1).ToDouble(&temp8))
         ZieglerTable.push_back(temp8);
     if(ThisZiegler.GetZieglerValues9().Item(Number-1).ToDouble(&temp9))
         ZieglerTable.push_back(temp9);
     if(ThisZiegler.GetZieglerValues10().Item(Number-1).ToDouble(&temp10))
         ZieglerTable.push_back(temp10);
     if(ThisZiegler.GetZieglerValues11().Item(Number-1).ToDouble(&temp11))
         ZieglerTable.push_back(temp11);
     if(ThisZiegler.GetZieglerValues12().Item(Number-1).ToDouble(&temp12))
         ZieglerTable.push_back(temp12);
     if(ZieglerTable.size() != 12) // Failure!
     {
      ZieglerTable.clear();
      for (int j=0; j<12; j++)
      {
       ZieglerTable.push_back(0);
      }
     }
   }
   else // Element not declared, so it will be set equal zero
   {
     ZieglerTable.clear();
     for (int j=0; j<12; j++)
     {
       ZieglerTable.push_back(0);
     }
   }
   // For custom Ziegler-code
   if(ZieglerModel == 2)
   {
     CustomZieglerFunction = AlgebraicFunction(ThisZiegler.GetZieglerFunction());
     std::vector<double> CompleteZieglerTable;
     CompleteZieglerTable.push_back(Number*1.0);
     for(int k=0; k<ZieglerTable.size(); k++)
     {
       CompleteZieglerTable.push_back(ZieglerTable.at(k));
     }
     CompleteZieglerTable.push_back(Atomic);
     CompleteZieglerTable.push_back(Density);
     CompleteZieglerTable.push_back(Bloch);
     CustomZieglerFunction.SetFunctionNumberParameter(CompleteZieglerTable);
   }
  return;
}

// Calculate the cross-section from the table of data
double Element::EvaluateSigma(double AtEnergy)
{
 if(Energy.size()>0 && AtEnergy > 0)
 {
   double epsilon1,epsilon2,E1,E2;
   // If the point was outside the boundaries, the final result will be set to zero.
   if ((Energy.at(Energy.size()-1)>=AtEnergy) && (Energy.at(0)<=AtEnergy))
   {
   for (int i=0; i<Energy.size(); i++)  // In some situations, some gamma points matches exactly at some element of main table
    {
    if (Energy.at(i) == AtEnergy)
     {
       return Sigma.at(i);
     }
    }
   for (int j=0; j<Energy.size() - 1; j++)  // But in general situations, it is necessary to interpolate two points.
    {
    if (AtEnergy>Energy.at(j) && AtEnergy<Energy.at(j+1))
     {
      E1 = Energy.at(j);
      E2 = Energy.at(j+1);
      epsilon1 = Sigma.at(j);
      epsilon2 = Sigma.at(j+1);
      double slope = (AtEnergy - E1)/(E2 - E1);
      double linear = epsilon1 + slope*(epsilon2 - epsilon1);
      return linear;
     }
    }
    return 0;
   }
   else
   {
    return 0;
   }
  }
  else
  {
   return 0;
  }
}


// Evaluate the Ziegler function
double Element::EvaluateZiegler(double AtEnergy)
{
  if (ZieglerModel == 0) // 1977 Ziegler Model
 {
  if ( AtEnergy >= 0 && AtEnergy < 10)  // At very low energies
  {
    return ZieglerTable.at(0)*std::sqrt(AtEnergy);
  }
  else  if (AtEnergy > 10 && AtEnergy < 1000)  // Medium range energy
  {
    double StoppingLow, StoppingHigh, Stopping;
    StoppingLow = ZieglerTable.at(1)*std::pow(AtEnergy,0.45);
    StoppingHigh = (ZieglerTable.at(2)/AtEnergy)*std::log(1 + (ZieglerTable.at(3)/AtEnergy) + (ZieglerTable.at(4)*AtEnergy));
    Stopping = (StoppingLow*StoppingHigh)/(StoppingHigh+StoppingLow);
    return Stopping;
  }
  else   // At high energies, greater that 1 MeV
  {
    double ProtonMass = 938280; // Proton Mass in keV
    double RelativisticVelocity = (AtEnergy*AtEnergy + 2 * AtEnergy * ProtonMass)/((ProtonMass + AtEnergy) * (ProtonMass + AtEnergy));
    double PolynomialStopping = ZieglerTable.at(7) + ZieglerTable.at(8) * std::log(AtEnergy) + ZieglerTable.at(9) * std::pow(std::log(AtEnergy),2) + ZieglerTable.at(10) * std::pow(std::log(AtEnergy),3) + ZieglerTable.at(11) * std::pow(std::log(AtEnergy),4);
    double LogarithmStopping = std::log(ZieglerTable.at(6)*RelativisticVelocity/(1-RelativisticVelocity)) - RelativisticVelocity;
    double Stopping = (ZieglerTable.at(5)/RelativisticVelocity)*(LogarithmStopping - PolynomialStopping);
    return Stopping;
  }
 }
 else if (ZieglerModel == 1) // 1991 Ziegler Model, which contains a single condition
  {
   if ( AtEnergy == 0)
   {
    return 0;
   }
   else if ( AtEnergy >= 0 && AtEnergy < 25)  // Simplification to get Ziegler(0)=0
   {
    return ZieglerTable.at(0)*std::pow(AtEnergy,ZieglerTable.at(1)) + ZieglerTable.at(2)*std::pow(AtEnergy,ZieglerTable.at(3));
   }
   else
   {
    double StoppingLow, StoppingHigh, Stopping;
    StoppingLow = ZieglerTable.at(0)*std::pow(AtEnergy,ZieglerTable.at(1)) + ZieglerTable.at(2)*std::pow(AtEnergy,ZieglerTable.at(3));
    StoppingHigh = (ZieglerTable.at(4)/std::pow(AtEnergy,ZieglerTable.at(5)))*std::log( (ZieglerTable.at(6)/AtEnergy) + (ZieglerTable.at(7)*AtEnergy));
    Stopping = (StoppingLow*StoppingHigh)/(StoppingHigh+StoppingLow);
    return Stopping;
   }
  }
  else if (ZieglerModel == 2) // Apply a custom function
  {
    return CustomZieglerFunction.GetFyxEval(AtEnergy);
  }
  else if (ZieglerModel == 3) // Apply a linear interpolation of SRIM tables
  {
   if(SRIMEnergy.size()>0 && SRIMStoppingPower.size()>0 && AtEnergy>0)
   {
    double epsilon1,epsilon2,E1,E2;
    // If the point was outside the boundaries, the final result will be set to zero, otherwise use the table interpolation data.
    if (( SRIMEnergy.at(0) <= AtEnergy) && (AtEnergy <= SRIMEnergy.at(SRIMEnergy.size()-1)))
    {
     for (int i=0; i<SRIMEnergy.size(); i++)  // In some situations, some table points matches exactly at some element of main table
     {
      if (SRIMEnergy.at(i) == AtEnergy)
      {
        return SRIMStoppingPower.at(i);
      }
     }
     for (int j=0; j<SRIMEnergy.size() - 1; j++)  // But in general situations, it is necessary to interpolate two points.
     {
      if (SRIMEnergy.at(j)<AtEnergy && AtEnergy<SRIMEnergy.at(j+1))
      {
      E1 = SRIMEnergy.at(j);
      E2 = SRIMEnergy.at(j+1);
      epsilon1 = SRIMStoppingPower.at(j);
      epsilon2 = SRIMStoppingPower.at(j+1);
      double slope = (AtEnergy - E1)/(E2 - E1);
      double linear = epsilon1 + slope*(epsilon2 - epsilon1);
      return linear;
      }
     }
    return 0;
    }
    else if (AtEnergy < SRIMEnergy.at(0)) // Apply a linear continuity to low energies, to avoid false zero values at finite energy losses
    {
      double slope = AtEnergy / SRIMEnergy.at(0);
      double linear = slope * SRIMStoppingPower.at(0);
      return linear;
    }
    else if(AtEnergy > SRIMEnergy.at(SRIMEnergy.size()-1))
    {
     return SRIMStoppingPower.at(SRIMStoppingPower.size()-1); // For higher energies, the stopping power goes to an approximate constant value.
    }
    else
    {
     return 0; // Default value
    }
   }
  }
  else
  {
    return 0; // Default Value
  }
 return 0; // Default Value
}


// Evaluates the total stoichiometry of all Elements found on main spreadsheet
double ElementVector::GetTotalStoichiometry()
{
 TotalStoichiometry = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
  TotalStoichiometry = TotalStoichiometry + this->Item(i).GetStoichiometry();
 }
 return TotalStoichiometry;
}

// Evaluates the total atomic and/or isotopic mass of all Elements found on main spreadsheet
double ElementVector::GetTotalMass()
{
 TotalMass = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
  TotalMass = TotalMass + this->Item(i).GetStoichiometry() * this->Item(i).GetIsotopicMass();
 }
 return TotalMass;
}

// Evaluate the cross-section of a single element
double ElementVector::EvaluateCrossSection(int ElementID, double AtEnergy)
{
 if(this->GetCount() <= ElementID)
  return 0.0;
 else
 return this->Item(ElementID).EvaluateSigma(AtEnergy);
}

// Evaluate the weight stoichiometry ratio
double ElementVector::GetWeightStoichiometry(int i)
{
 return this->Item(i).GetStoichiometry();
}

// Evaluate the stopping power of all Elements, combined with the Bragg´s Law.
double ElementVector::EvaluateBragg(double AtEnergy)
{
 double StoppingPowerSum = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
  StoppingPowerSum = StoppingPowerSum + this->Item(i).EvaluateZiegler(AtEnergy) * this->GetWeightStoichiometry(i);
 }
 return StoppingPowerSum;
}

// Return the entire molar mass of all Elements
double ElementVector::GetMolarMass()
{
 double MolarMass = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
  MolarMass = MolarMass + this->Item(i).GetAtomicMass() * this->Item(i).GetStoichiometry();
 }
 return MolarMass;
}

// Return the isotopic mass of all Elements
double ElementVector::GetIsotopicMass()
{
 double MolarMass = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
  MolarMass = MolarMass + this->Item(i).GetIsotopicMass() * this->Item(i).GetStoichiometry();
 }
 return MolarMass;
}

// Return the entire density of all Elements
double ElementVector::GetGlobalDensity()
{
 double DensityMass = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
  DensityMass = DensityMass + this->Item(i).GetDensity() * this->Item(i).GetStoichiometry();
 }
 return DensityMass;
}

// Return the entire charge of all Elements
double ElementVector::GetGlobalCharge()
{
 double DensityMass = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
  DensityMass = DensityMass + this->Item(i).GetAtomicNumber() * this->Item(i).GetStoichiometry();
 }
 return DensityMass;
}

// Renormalize the stoichiometry of fitting Elements
bool ElementVector::RenormStoichiometry()
{
 double SumStoichiometry = this->GetTotalStoichiometry();
 if(this->GetCount() == 0)
  return false;
 for(int i=0; i<this->GetCount(); i++)
 {
  double temp = this->Item(i).GetStoichiometry();
  this->Item(i).SetStoichiometry(temp/SumStoichiometry);
 }
 return true;
}

// Evaluate the mass fraction of a element respective to the whole sample
double ElementVector::GetMassFraction(int ElementID)
{
 if(this->GetCount() <= ElementID)
  return 0.0;
 double TotalStoichiometricMass = 0;
 for(int i=0; i<this->GetCount(); i++)
 {
   TotalStoichiometricMass = TotalStoichiometricMass + this->Item(i).GetStoichiometry() * this->Item(i).GetAtomicMass();
 }
 if (this->GetCount() > 0)
 {
  double WeightElement = this->Item(ElementID).GetStoichiometry() * this->Item(ElementID).GetAtomicMass();
  return WeightElement / TotalStoichiometricMass;
 }
 else
 {
  return 1.0;
 }
}

//Evaluate the k and x factors
double Layer::MakeBeta(double E)
{
 double mp = 938272; //proton's mass in keV
 return std::sqrt(2 * mp * E + E * E) / (mp + E);
}

double Layer::Xi(double E)
{
 //Xi = 2.5507e-7 * Z * M * n / (A * b^2) [keV]
 double XiFactor = 2.5507e-7;
 double TotalCharge = LayerCompound.GetGlobalCharge();
 double TotalMass = LayerCompound.GetIsotopicMass();
 double MolarMass = LayerCompound.GetMolarMass();
 double Beta = this->MakeBeta(E);
 double f = (XiFactor * TotalCharge * MolarMass * ThicknessStep)/(TotalMass * Beta * Beta);
 return f;
}

double Layer::Emax(double E)
{
 //E = (2 * m * c^2 * b^2 * g^2)/(1 + 2*g*m/M)
 double me = 511; //electron's mass in keV
 double mp = 938272; //proton's mass in keV
 double Beta = this->MakeBeta(E);
 double Gamma = 1/std::sqrt(1-Beta*Beta);
 double f = (2 * me * Beta * Beta * Gamma * Gamma) / (1 + (2*Gamma*me)/mp);
 return f;
}

//Get the Bohr variance of the current layer
double Layer::GetGVL(double E)
{
 double BohrFactor = (8 * this->GetXi(E)) / (3);
 double Beta = this->MakeBeta(E);
 double me = 511; //electron mass in keV
 double SumIonization = 0;
 for(int i=0; i<LayerCompound.GetCount(); i++)
 {
    double x = LayerCompound.Item(i).GetStoichiometry() * LayerCompound.Item(i).GetIonization() * std::log(2 * me * Beta * Beta / LayerCompound.Item(i).GetIonization());
    if(x>0)
     SumIonization = SumIonization + x;
 }
 return std::sqrt(BohrFactor * SumIonization);
}

//Get the Vavilov variance of the current layer
double Layer::GetVVL(double E)
{
 double Xi = this->GetXi(E);
 double Beta = this->GetBeta(E);
 double K = this->GetK(E);
 return std::sqrt(Xi*Xi*(1-Beta*Beta/2)/K);
}

// Sample main constructor
LayerVector::LayerVector(ElementDatabaseArray AllElements, ZieglerParameters ThisZiegler, ElementSRIMArray ThisSRIM, wxGrid* SourceTable, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass,ArrayAtomicMass textAtomicMass,ArrayCalibrationFactor textCalibrationFactor, double DefaultLayerStep)
{
 if(this->CreateSample(AllElements,ThisZiegler,ThisSRIM,SourceTable,choiceElementName,choiceGammaPeak,textAtomicNumber,textAbundance,textIsotopicMass,textAtomicMass,textCalibrationFactor,DefaultLayerStep))
 {
  ErrorFlag = true;
  ErrorMessage.Clear();
 }
 else
 {
  ErrorFlag = false;
 }
}

// Sample Builder
bool LayerVector::CreateSample(ElementDatabaseArray AllElements, ZieglerParameters ThisZiegler, ElementSRIMArray ThisSRIM, wxGrid* SourceTable, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass,ArrayAtomicMass textAtomicMass,ArrayCalibrationFactor textCalibrationFactor, double DefaultLayerStep)
{
 // Read the table, row by row
 for(int z=0; z<SourceTable->GetNumberRows(); z++)
 {
  LayerCompound.Clear();
  for(int k=0; k<choiceElementName.GetCount(); k++) //read the Elements database
  {
   int i = choiceElementName.Item(k)->GetSelection();
   int j = choiceGammaPeak.Item(k)->GetSelection();
   if(AllElements.FindElement(choiceElementName.Item(k)->GetString(i),choiceGammaPeak.Item(k)->GetString(j)) != wxNOT_FOUND)
   {
    double ActualStoichiometry;
    wxString TestStoichiometry = SourceTable->GetCellValue(z,k+1);
    int x = AllElements.FindElement(choiceElementName.Item(k)->GetString(i),choiceGammaPeak.Item(k)->GetString(j));
    if(TestStoichiometry.ToDouble(&ActualStoichiometry))
    {
     LayerCompound.Add(Element(AllElements.Item(x),ThisZiegler,ThisSRIM,TestStoichiometry));
     wxString PatchNumber = textAtomicNumber.Item(k)->GetValue();
     wxString PatchAbundance = textAbundance.Item(k)->GetValue();
     wxString PatchIsotopic = textIsotopicMass.Item(k)->GetValue();
     wxString PatchAtomic = textAtomicMass.Item(k)->GetValue();
     wxString PatchCalibration = textCalibrationFactor.Item(k)->GetValue();
     long ActualNumber;
     double ActualAbundance, ActualIsotopic, ActualAtomic, ActualCalibration;
     if(PatchNumber.ToLong(&ActualNumber) && PatchAbundance.ToDouble(&ActualAbundance) && PatchIsotopic.ToDouble(&ActualIsotopic) && PatchAtomic.ToDouble(&ActualAtomic) && PatchCalibration.ToDouble(&ActualCalibration))
     {
       LayerCompound.Last().SetAtomicNumber(ActualNumber);
       LayerCompound.Last().SetAbundance(ActualAbundance);
       LayerCompound.Last().SetIsotopicMass(ActualIsotopic);
       LayerCompound.Last().SetAtomicMass(ActualAtomic);
       LayerCompound.Last().SetCalibrationFactor(ActualCalibration);
     }
     else
     {
      ErrorMessage = wxT("Data Error: Non-numerical Custom Element Physical Parameters.");
      return false;
     }
    }
    else
    {
     ErrorMessage = wxT("Data Error: Non-numerical value found on Layer Table on Layer #") + wxString::Format("%i",z+1) + wxT (" , and Element \"") + choiceElementName.Item(k)->GetString(i) + wxT("(") + choiceGammaPeak.Item(k)->GetString(j) + wxT(")\", at Column #") + wxString::Format("%i",k+2);
     return false;
    }
   }
   else
   {
   ErrorMessage = wxT("Fatal Error: Cannot find Element \"") + choiceElementName.Item(k)->GetString(i) + wxT(" , ") + choiceGammaPeak.Item(k)->GetString(j) + wxT(" keV.");
   return false;
   }
  }
  // Add Layer Thickness
  LayerCompound.RenormStoichiometry();
  double ActualThickness;
  wxString TestThickness = SourceTable->GetCellValue(z,0);
  if(TestThickness.ToDouble(&ActualThickness))
  {
   this->Add(Layer(LayerCompound,ActualThickness,DefaultLayerStep));
  }
  else
  {
    ErrorMessage = wxT("Data Error: Non-numerical value found on Layer Table on Layer #") + wxString::Format("%i",z+1) + wxT (" , at Thickness column.");
     return false;
  }
 }
 return true;
}

// Evaluate the average molar mass of all layers
double LayerVector::GetAverageMolarMass()
{
 double TotalMass = 0;
 int NumberLayers = this->GetCount();
 if(NumberLayers > 0)
 {
  for (int i=0; i<this->GetCount(); i++)
  {
   TotalMass = TotalMass + this->Item(i).GetMolarMass();
  }
  return TotalMass/NumberLayers;
 }
 else
 {
  return 0;
 }
}


double LayerVector::GetTotalThickness()
{
 double TotalThickess = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
   TotalThickess = TotalThickess + this->Item(i).GetThickness();
 }
 return TotalThickess;
}

bool LayerVector::IsSampleBoundedAtThickness(double AtThickness)
{
 if(AtThickness <= this->GetTotalThickness())
  return true;
 else
  return false;
}

int LayerVector::GetLayerAtThickness(double AtThickness)
{
 double PartialThickess = 0;
 for (int i=0; i<this->GetCount(); i++)
 {
   PartialThickess = PartialThickess + this->Item(i).GetThickness();
   if(AtThickness < PartialThickess)
    return i;
 }
 return this->GetCount()-1;
}

// Main Yield constructor
Yield::Yield(int ElementID, double Charge, double Efficiency, double Step, LayerVector CurrentSample)
{
 ElementCharge = Charge;
 ElementEfficiency = Efficiency;
 LocalSample = CurrentSample;
 PositionID = ElementID;
 YieldStep = Step;
}

// Evaluate Z = int(f_T (E) f_S(S-E) sigma(S+DEM+EM),E,S)
double Yield::SigmaDistributionConvolution(int LayerNumber, double Energy)
{
 //Implements a double numerical integration using the Simpson method
 double DT = ElementDistribution.GetThermalStep();
 double DS = ElementDistribution.GetStraggStep();
 double Tmin = ElementDistribution.GetThermalMin();
 double Tmax = ElementDistribution.GetThermalMax();
 double Smin = ElementDistribution.GetStraggMin();
 double Smax = ElementDistribution.GetStraggMax();
 unsigned int Tsteps = std::ceil((Tmax-Tmin)/(DT));
 unsigned int Ssteps = std::ceil((Smax-Smin)/(DS));
 if(Tsteps%2==1)
    Tsteps = Tsteps + 1;
 if(Ssteps%2==1)
    Ssteps = Ssteps + 1;
 // Create the weights matrix
 std::vector< std::vector<unsigned int> > SimpsonWeight(Ssteps+1, std::vector<unsigned int> (Tsteps+1,0));
 for(unsigned int i=0; i<=Ssteps; i++)
 {
   unsigned int SWRFactor;
   if(i==0 || i==Ssteps)
        SWRFactor = 1;
     else if (i>0 && i<Ssteps && i%2==1)
        SWRFactor = 4;
     else if (i>0 && i<Ssteps && i%2==0)
        SWRFactor = 2;
     else
        SWRFactor = 0;
   for(unsigned int j=0; j<=Tsteps; j++)
   {
     unsigned int SWCFactor;
     if(j==0 || j==Tsteps)
        SWCFactor = 1;
     else if (j>0 && j<Tsteps && j%2==1)
        SWCFactor = 4;
     else if (j>0 && j<Tsteps && j%2==0)
        SWCFactor = 2;
     else
        SWCFactor = 0;
     SimpsonWeight[i][j] = SWRFactor * SWCFactor;
   }
 }
 // Evaluate the integral itself, including the renormalization integral.
 // Insert the stopping power inside the integral
 double DoubleSimpsonSum = 0;
 double RenormalizationSum = 0;
 for(unsigned int i=0; i<=Ssteps; i++)
 {
   for(unsigned int j=0; j<=Tsteps; j++)
   {
     double S = Smin + i * DS ;
     double T = Tmin + j * DT ;
     double LocalStoppingPower = LocalSample.Item(LayerNumber).EvaluateBragg(Energy-S);
     double LocalDistribution = ElementDistribution.GetValue(S-T,T);
      DoubleSimpsonSum = DoubleSimpsonSum + SimpsonWeight[i][j] * LocalDistribution * this->EvaluateSigma(LayerNumber,Energy-S) / LocalStoppingPower;
      RenormalizationSum = RenormalizationSum + SimpsonWeight[i][j] * LocalDistribution;
   }
 }
 double CrossSigmaSum = (DS * DT) * DoubleSimpsonSum / 9;
 double DistributionSum = (DS * DT) * RenormalizationSum / 9;
 // If the renormalization itself are zero, return zero, since the first integral will also the zero.
 if(DistributionSum == 0.0)
   return 0;
 else
   return CrossSigmaSum / DistributionSum;
}

double Yield::EvaluateSigma(int LayerNumber, double Energy)
{
 //When a custom resonance function are defined, the cross-section data are ignored
 if(ElementRessonance.IsNullRessonance())
 {
   return LocalSample.Item(LayerNumber).EvaluateCrossSectionAt(PositionID,Energy) * LocalSample.Item(LayerNumber).GetCalibrationFactorAt(PositionID);
 }
 else //Otherwise use the custom resonance function, when the value itself are greater than the default database value.
 {
   if(ElementRessonance.GetDomainMinimum() <= Energy && Energy <= ElementRessonance.GetDomainMaximum())
    return ElementRessonance.GetValue(Energy) * LocalSample.Item(LayerNumber).GetCalibrationFactorAt(PositionID);
   else
    return LocalSample.Item(LayerNumber).EvaluateCrossSectionAt(PositionID,Energy) * LocalSample.Item(LayerNumber).GetCalibrationFactorAt(PositionID);
 }
}

//Evaluate the Yield at a certain energy and layer
double Yield::YieldFunction(int LayerNumber, double Energy)
{
 // Define numerical conversions
  double AvogradoNumber = 6.022140857e+23;
  double ElementaryCharge = 1.6021766208e-19;
  double ZieglerFactor = 1.0e+24;
  double MicroColoumb = 1.0e-6; // Convert Colomb to Micro-Colomb
  double MiliBarnUnit = 1.0e-27; // Convert milibarn to sq.cm
  double MicroGram = 1.0e-6; // Convert grams to micro-grams.
  double YieldFactor = AvogradoNumber * MicroColoumb * MiliBarnUnit * MicroGram / ElementaryCharge; // Set yield unit conversion
  double BraggFactor = AvogradoNumber / ZieglerFactor; // Set stepping-power unit conversion
 // Evaluate the physics
 double ElementAtomicMass = LocalSample.Item(LayerNumber).GetAtomicMassAt(PositionID);
 double ElementAbundance = LocalSample.Item(LayerNumber).GetAbundanceAt(PositionID);
 double ElementMassFraction = LocalSample.Item(LayerNumber).GetMassFractionAt(PositionID);
 double ElementMass = LocalSample.Item(LayerNumber).GetMolarMass();
 double YieldNull = ElementEfficiency * ElementCharge * ElementMassFraction * ElementAbundance * YieldFactor / ElementAtomicMass;
 double ElementSigma = this->SigmaDistributionConvolution(LayerNumber,Energy);
 double ElementStoppingPower = BraggFactor / ElementMass;
 double YieldLayer = YieldNull * ElementSigma * YieldStep / ElementStoppingPower;
 double LayerAtomicMass = LocalSample.Item(LayerNumber).GetMolarMass();
 ElementRessonance.SetAtomicMass(LayerAtomicMass);
 // In some circumstances, it may occur a numerical overflow (Stopping-Power equal to zero are the most common one), without physical meaning.
 if (!(std::isfinite(YieldLayer)))
    YieldLayer = 0.0;
 // return the value
 return YieldLayer;
}

double Yield::AddYieldLayer(RessonanceFunction CurrentRessonance, PhysicsDistribution CurrentDistribution, int AtLayer, double AtEnergy, double RangeEnergy)
{
 ElementRessonance = CurrentRessonance;
 ElementDistribution = CurrentDistribution;
 YieldStep = RangeEnergy;
 double ActualYieldLayer = this->YieldFunction(AtLayer,AtEnergy);
 YieldValues.at(YieldValues.size()-1) = YieldValues.at(YieldValues.size()-1) + ActualYieldLayer;
 return ActualYieldLayer;
}

// Main Yield Vector constructor
YieldVector::YieldVector(LayerVector CurrentSample, Detector CurrentDetector, double CurrentCharge, double CurrentStep)
{
 // Initialize values
 double DetectorCharge, YieldPrecison;
 DetectorCharge = CurrentCharge;
 YieldPrecison = CurrentStep;
 for(int i=0; i<CurrentSample.GetElementsCount(); i++)
 {
   double DetectorEnergy = CurrentSample.GetGammaPeakAt(i);
   double DetectorEfficiency = CurrentDetector.GetEval(DetectorEnergy);
   this->Add(Yield(i,DetectorCharge,DetectorEfficiency,YieldPrecison,CurrentSample));
 }
}

void YieldVector::SetEnergy(double InitialEnergy)
{
 YieldEnergy.push_back(InitialEnergy);
 for(int i=0; i<this->GetCount(); i++)
 {
  this->Item(i).AddNewYield();
 }
 return;
}

// Trigger the evaluation of all Yields, and store the values on stack
std::vector<double> YieldVector::SetValue(RessonanceFunction CurrentRessonance, PhysicsDistribution CurrentDistribution, int AtLayer, double AtEnergy, double RangeEnergy)
{
 std::vector<double> PartialYields;
 for(int i=0; i<this->GetCount(); i++)
 {
  double temp = this->Item(i).AddYieldLayer(CurrentRessonance,CurrentDistribution,AtLayer,AtEnergy,RangeEnergy);
  PartialYields.push_back(temp);
 }
 return PartialYields;
}

//Create a combined vector of Yields
YieldVector::YieldVector(std::vector<YieldVector> Original)
{
 // Sort the vector
 std::vector<int> VectorAdress;
 std::vector<double> VectorValue;
 for(int i=0; i<Original.size(); i++)
 {
   VectorAdress.push_back(i);
   VectorValue.push_back(Original.at(i).GetEnergy().at(0));
 }
 int n = VectorAdress.size();
   for (int i=0; i<n-1; i++)
   {
     for(int j=0; j<n-i-1; j++)
     {
      if (VectorValue.at(j) > VectorValue.at(j+1))
      {
      double temp1 = VectorAdress.at(j);
      double temp2 = VectorValue.at(j);
      VectorAdress.at(j) = VectorAdress.at(j+1);
      VectorValue.at(j) = VectorValue.at(j+1);
      VectorAdress.at(j+1) = temp1;
      VectorValue.at(j+1) = temp2;
      }
     }
   }
  // Prepare the Energy vector
  YieldEnergy.clear();
  // Copy the vector contents
  for(int z=0; z<Original.size(); z++)
  {
    std::vector<double> PartialYieldEnergy = Original.at(VectorAdress.at(z)).GetEnergy();
    YieldEnergy.insert(std::end(YieldEnergy), std::begin(PartialYieldEnergy), std::end(PartialYieldEnergy));
    int NumberLocalRegisters = Original.at(VectorAdress.at(z)).GetCount();
    for (int zz=0; zz<NumberLocalRegisters; zz++)
    {
      this->Add(Original.at(VectorAdress.at(z)).Item(zz));
    }
  }
}

// Add a new set of values
void Sample::AddSampleLayer(double D, double L, double DEL, double EML, double KLL, double KU, double X, double XT, double beta, double BVL, double BVT, std::vector<double> PartialYield)
{
 Depth.push_back(D);
 LayerNumber.push_back(L);
 DE.push_back(DEL);
 EM.push_back(EML);
 KL.push_back(KLL);
 K.push_back(KU);
 XiL.push_back(X);
 Xi.push_back(XT);
 CurrentBeta.push_back(beta);
 BL.push_back(BVL);
 BV.push_back(BVT);
 for(int i=0; i<PartialYield.size(); i++) //Store lineary
 {
  PY.push_back(PartialYield.at(i));
 }
 return;
}

int SampleVector::SumAllSamples()
{
 int AllSum = 0;
 for(int i=0; i<this->GetCount(); i++)
 {
    AllSum = AllSum + this->Item(i).GetNumberSampleElements();
 }
 return AllSum;
}

void SampleVector::SetValue(double D, double L, double DEL, double EML, double KLL, double KU, double X, double XT, double beta, double BVL, double BV, std::vector<double> PartialYield)
{
 this->Last().AddSampleLayer(D,L,DEL,EML,KLL,KU,X,XT,beta,BVL,BV,PartialYield);
}

SampleVector::SampleVector(std::vector<SampleVector> Original)
{
// Sort the vector
 std::vector<int> VectorAdress;
 std::vector<double> VectorValue;
 for(int i=0; i<Original.size(); i++)
 {
   VectorAdress.push_back(i);
   VectorValue.push_back(Original.at(i).GetInitialEnergyAt(0));
 }
 int n = VectorAdress.size();
   for (int i=0; i<n-1; i++)
   {
     for(int j=0; j<n-i-1; j++)
     {
      if (VectorValue.at(j) > VectorValue.at(j+1))
      {
      double temp1 = VectorAdress.at(j);
      double temp2 = VectorValue.at(j);
      VectorAdress.at(j) = VectorAdress.at(j+1);
      VectorValue.at(j) = VectorValue.at(j+1);
      VectorAdress.at(j+1) = temp1;
      VectorValue.at(j+1) = temp2;
      }
     }
   }
  // Copy the vector contents
  for(int z=0; z<Original.size(); z++)
  {
    int NumberLocalRegisters = Original.at(VectorAdress.at(z)).GetCount();
    for (int zz=0; zz<NumberLocalRegisters; zz++)
    {
      this->Add(Original.at(VectorAdress.at(z)).Item(zz));
    }
  }
}

// Makes the initial processing, placing the minimum information to build the  numerical tables
bool ReactionProfiling::SampleSetup(ElementDatabaseArray AllElements, ZieglerParameters ThisZiegler, DetectorParameters ThisDetector, ElementSRIMArray ThisSRIM, wxGrid* SourceTable, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass,ArrayAtomicMass textAtomicMass,ArrayCalibrationFactor textCalibrationFactor)
{
 // Check Custom Ziegler macros forehand
 if(ThisZiegler.GetZieglerVersion() == wxT("2"))
 {
  wxString TestingZieglerFunction = ThisZiegler.GetZieglerFunction();
  std::vector<double> DummyData (16,1.0);
  AlgebraicFunction ZieglerCheck(TestingZieglerFunction);
  if(!(ZieglerCheck.IsFunctionDefined()))
  {
    LastErrorCode = wxT("Ziegler Function Error: Syntax Error\n") + ZieglerCheck.GetErrorString();
    SampleComplete = false;
    return false;
  }
  if(!(ZieglerCheck.SetFunctionNumberParameter(DummyData)))
  {
    LastErrorCode = wxT("Ziegler Function Error: Undefined Function Error\n") +ZieglerCheck.GetErrorString();
    SampleComplete = false;
    return false;
  }
 }
 // Create the table of all physical features of all elements at all layers
 LocalSample.Clear();
 LocalSample = LayerVector(AllElements,ThisZiegler,ThisSRIM,SourceTable,choiceElementName,choiceGammaPeak,textAtomicNumber,textAbundance,textIsotopicMass,textAtomicMass,textCalibrationFactor,DefaultSampleStep);
 if(LocalSample.IsCorrect())
 {
  //A final check, dedicated to verify the consistency of the Detector.
  LocalDetector = Detector(ThisDetector);
  if(LocalDetector.CheckDetector())
  {
    SampleComplete = true;
    return true;
  }
  else
  {
    LastErrorCode = LocalDetector.GetErrorCode();
    SampleComplete = false;
    return false;
  }
 }
 else
 {
   LastErrorCode = LocalSample.GetErrorMessage();
   SampleComplete = false;
   return false;
 }
}


// Main cycle of processing
bool ReactionProfiling::MainProcedure(wxStatusBar* progress)
{
 // Steps Counter
 PartialNumberSteps = 0;
 //Get the number of energy steps
 int NumberSteps = std::ceil((EnergyMaximum-EnergyMinimum)/EnergyStep);
 //Get the number of sample steps
 int SampleSteps = std::ceil(LocalSample.GetTotalThickness()/DefaultSampleStep);
 // Prepare YieldVector object
 LocalResults = YieldVector(LocalSample,LocalDetector,Charge,EnergyStep);
 // Clear Sample log class
 LocalDepth.Clear();
 // Number of maximum steps
 TotalNumberSteps = (SampleSteps+1)*(NumberSteps+1);
 // Create an additional modal progress bar:
 wxProgressDialog *dial = new wxProgressDialog(wxT("Numerical Simulation Progress"), wxT("Starting, please wait..."),TotalNumberSteps,NULL,wxPD_CAN_ABORT|wxPD_APP_MODAL|wxPD_AUTO_HIDE);
 // And start the main cycle
 for (int i=0; i<=NumberSteps; i++)
 {
  double InitialEnergy = EnergyMinimum + 1.0 * i * EnergyStep;
  double InitiaThermalDoppler = LocalDistribution.GetThermalDoppler(InitialEnergy,LocalSample.GetAverageMolarMass());
  double EM = InitialEnergy;
  double GV = 0;
  double VV = 0;
  double DEM = 0;
  double Xi = 0;
  double K = 0;
  LocalResults.SetEnergy(InitialEnergy); //Allocate a new Y(E) register
  LocalDepth.NewRegister(InitialEnergy); //Allocate a new D(E) register
  for (int j=0; j<=SampleSteps; j++)
  {
   // Get the current layer
   int CurrentLayer;
   if(LocalSample.IsSampleBoundedAtThickness(1.0*j*DefaultSampleStep))
    CurrentLayer = LocalSample.GetLayerAtThickness(1.0*j*DefaultSampleStep);
   else
    break;
   //Notice that the distribution calculation are taken by the previous parameters, which means at the first layer it takes the initial value.
   double DEML = LocalSample.Item(CurrentLayer).GetDEML(EM);
   double GVL  = LocalSample.Item(CurrentLayer).GetGVL(EM);
   double VVL  = LocalSample.Item(CurrentLayer).GetVVL(EM);
   double KL   = LocalSample.Item(CurrentLayer).GetK(EM);
   double Beta = LocalSample.Item(CurrentLayer).GetBeta(EM);
   double XiL = LocalSample.Item(CurrentLayer).GetXi(EM);
   // Handle the choose between Bohr or Vavilov Variance Limit
   double LV = 0.0;
   if (DefaultThreads > 0)
    LV = VV;
   else
    LV = GV;
   // Check the forced Gaussian option
   bool AlwaysGaussian = false;
   if (DefaultThreads > 1)
       AlwaysGaussian = true;
   else
       AlwaysGaussian = false;
   // Extract the distribution values
   if(LocalDistribution.SetDistribution(Xi,Beta,K,DEML,LV,DefaultGauss,DefaultVavilovMoyal,DefaultVavilovEdgeworth,DefaultVavilovAiry,DefaultLandau,AlwaysGaussian))
   {
     // Compute the Yields, adding the partial yield of each element, layer by layer
   std::vector<double> YieldsAtLayer = LocalResults.SetValue(LocalRessonance,LocalDistribution,CurrentLayer,EM,DEML);
   // If enabled by the user: Store partial results to the debug register
   if(RequireLog)
    LocalDepth.SetValue(1.0*j*DefaultSampleStep,1.0*CurrentLayer+1,DEML,EM,KL,K,XiL,Xi,Beta,GVL,GV,YieldsAtLayer);
   // Update step...
   PartialNumberSteps = PartialNumberSteps + 1;
   // Update the progress bar...
   progress->SetStatusText(wxT("Calculation Progress...") + wxString::Format("%.3f",(100.0*PartialNumberSteps)/(TotalNumberSteps)) + wxT("%") ,0);
   dial->Update(PartialNumberSteps,wxT("Calculation Progress...") + wxString::Format("%.3f",(100.0*PartialNumberSteps)/(TotalNumberSteps)) + wxT("%"));
   // If hit the "Cancel" button, the procedure are aborted.
   if(dial->WasCancelled())
    {
     dial->Destroy();
     LastErrorCode = wxT("Stop! The simulation was aborted by the user!");
     return false;
    }
   }
   else
   {
    LastErrorCode = LocalDistribution.GetErrorMessage();
    return false;
   }
   // Update values
   DEM = DEM + DEML;
   EM = EM - DEML;
   K = K + KL;
   GV = std::sqrt(GV*GV + GVL*GVL);
   VV = std::sqrt(VV*VV + VVL*VVL);
   Xi = Xi + XiL;
   // Negative energy values will break the inner cycle, since it means that the beam was absorbed on some layer.
   if(EM < 1e-3)
   {
    PartialNumberSteps = PartialNumberSteps + SampleSteps - j;
    break;
   }
  }
 }
 // The procedure was finished
 dial->Destroy();
 return true;
}


// Public function control of main cycle
bool ReactionProfiling::StartProcedure(wxStatusBar* progress)
{
 if(SampleComplete && InputComplete) //requires two modules
 {
   if(this->MainProcedure(progress))
   {
     return true;
   }
   else
   {
     return false;
   }
 }
 else
 {
  LastErrorCode = wxT("General Error: Incomplete Data Input!");
  return false;
 }
}

// Changes some parameters
bool ReactionProfiling::SetOverrideParameters(unsigned int SamplePrecision, unsigned int GaussPrecision, unsigned int VavilovMoyalPrecision, unsigned int VavilovEdgeworthPrecision, unsigned int VavilovAiryPrecision, unsigned int LandauPrecision, unsigned int ThreadPrecision, bool EnableLog)
{
 DefaultSampleStep = SamplePrecision;
 DefaultGauss = GaussPrecision;
 DefaultLandau = LandauPrecision;
 DefaultVavilovEdgeworth = VavilovEdgeworthPrecision;
 DefaultVavilovMoyal = VavilovMoyalPrecision;
 DefaultVavilovAiry = VavilovAiryPrecision;
 DefaultThreads = ThreadPrecision;
 RequireLog = EnableLog;
 DefaultParameters = false;
 return true;
}

// Set additional values
bool ReactionProfiling::SetInitialParameters(wxTextCtrl* valueBeamResolution, wxTextCtrl* valueTemperature, wxTextCtrl* valueCharge, wxTextCtrl* valueEnergyStep, wxTextCtrl* valueMinimumEnergy, wxTextCtrl* valueMaximumEnergy, wxTextCtrl* valueRessonanceWidth, wxTextCtrl* valueRessonancePeak, wxTextCtrl *valueRessonanceEnergy, wxTextCtrl *valueRessonanceMinimum, wxTextCtrl* valueRessonanceMaximum, wxTextCtrl* valueStrenghtWidth, wxTextCtrl* valueStrenghtPeak, wxTextCtrl *valueStrenghtEnergy, wxTextCtrl *valueStrenghtMinimum, wxTextCtrl* valueStrenghtMaximum, wxTextCtrl* valueRessonanceFunction, bool boolRessonanceLorentzian, bool boolRessonanceStrenght, int intRessonanceMode)
{
 //Define the physics distribution object, first.
 LocalDistribution = PhysicsDistribution(valueBeamResolution->GetValue(),valueTemperature->GetValue());
 if(!(LocalDistribution.CheckValidity())) //Error handling
 {
  InputComplete = false;
  LastErrorCode = wxT("Numerical Distribution Error: Found a numerical error during numerical integration\n") +  LocalDistribution.GetErrorMessage();
  return false;
 }
 // Secondly, define the ressonance object, taking care of several options!
  if(intRessonanceMode == 0) //No ressonance
  {
    LocalRessonance.ResetFunction();
    RequireRessonance = false;
  }
  else if(intRessonanceMode == 1) //Lorentzian ressonance
  {
   if(boolRessonanceLorentzian)
   {
     LocalRessonance = RessonanceFunction(valueRessonanceWidth->GetValue(),valueRessonancePeak->GetValue(),valueRessonanceEnergy->GetValue(),valueRessonanceMinimum->GetValue(),valueRessonanceMaximum->GetValue());
     if(!(LocalRessonance.IsValid()))
     {
       InputComplete = false;
       LastErrorCode = wxT("Numerical Resonance Error: Failure on Runtime\n") + LocalRessonance.GetErrorMessage();
       return false;
     }
     else
     {
      RequireRessonance = true;
     }
   }
   else
   {
     LocalRessonance = RessonanceFunction(valueRessonanceWidth->GetValue(),valueRessonancePeak->GetValue(),valueRessonanceEnergy->GetValue());
     if(!(LocalRessonance.IsValid()))
     {
       InputComplete = false;
       LastErrorCode = wxT("Numerical Resonance Error: Failure on Runtime\n") +  LocalRessonance.GetErrorMessage();
       return false;
     }
     else
     {
       RequireRessonance = true;
     }
   }
  }
  else if(intRessonanceMode == 2) //Resonance Strenght
  {
   if(boolRessonanceStrenght)
   {
     LocalRessonance = RessonanceFunction(valueStrenghtWidth->GetValue(),valueStrenghtPeak->GetValue(),valueStrenghtEnergy->GetValue(),wxT("1"),valueStrenghtMinimum->GetValue(),valueStrenghtMaximum->GetValue());
     if(!(LocalRessonance.IsValid()))
     {
       InputComplete = false;
       LastErrorCode = wxT("Numerical Resonance Error: Failure on Runtime\n") + LocalRessonance.GetErrorMessage();
       return false;
     }
     else
     {
      RequireRessonance = true;
     }
   }
   else
   {
     LocalRessonance = RessonanceFunction(valueStrenghtWidth->GetValue(),valueStrenghtPeak->GetValue(),valueStrenghtEnergy->GetValue(),wxT("1"));
     if(!(LocalRessonance.IsValid()))
     {
       InputComplete = false;
       LastErrorCode = wxT("Numerical Resonance Error: Failure on Runtime\n") +  LocalRessonance.GetErrorMessage();
       return false;
     }
     else
     {
       RequireRessonance = true;
     }
   }
  }
  else if (intRessonanceMode == 3) //Custom function
  {
    LocalRessonance = RessonanceFunction(valueRessonanceFunction->GetValue());
    if(!(LocalRessonance.IsValid()))
     {
       InputComplete = false;
       LastErrorCode = wxT("Numerical Resonance Error: Failure on Runtime\n") + LocalRessonance.GetErrorMessage();
       return false;
     }
     else
     {
       RequireRessonance = true;
     }
  }
  else //Fatal error
  {
    InputComplete = false;
    LastErrorCode = wxT("General Error: Invalid Resonance Mode.");
    return false;
  }
 //Finally, get the Energy domain
 if(valueCharge->GetValue().ToDouble(&Charge) && valueEnergyStep->GetValue().ToDouble(&EnergyStep) && valueMinimumEnergy->GetValue().ToDouble(&EnergyMinimum) && valueMaximumEnergy->GetValue().ToDouble(&EnergyMaximum))
 {
   if(Charge<=0 || EnergyStep<=0 || EnergyMinimum >= EnergyMaximum)
   {
     InputComplete = false;
     LastErrorCode = wxT("Error: Invalid Energy Range Domain.\nPlease, verify the inserted values, and try again.");
     return false;
   }
 }
 else
 {
    InputComplete = false;
    LastErrorCode = wxT("Error: Non-numerical values found on Detector's Energy Range input.");
    return false;
 }
 //Complete
 InputComplete = true;
 LastErrorCode.Clear();
 return true;
}
