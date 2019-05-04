/***************************************************************
 * Name:      ReactionYield.h
 * Purpose:   ERYA Reaction Yield declaration
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2016-10-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#ifndef REACTIONYIELD_H_INCLUDED
#define REACTIONYIELD_H_INCLUDED
#include "ERYAProfiling.h"
#include "DatabaseLibrary.h"
#include "ParserLibrary.h"
#include "SpecialFunctionsLibrary.h"

class Element;
class Layer;
class Yield;
class Sample;
WX_DECLARE_OBJARRAY( Element, ElementArray);
WX_DECLARE_OBJARRAY( Layer, LayerArray);
WX_DECLARE_OBJARRAY( Yield, YieldArray);
WX_DECLARE_OBJARRAY( Sample, SampleArray);

// Handle the Custom or built-in Briet-Wigner ressonance distribution
class RessonanceFunction
{
private:
int RFMode;
std::vector<double> BWEnergy, BWWidth, BWPeak, BWmin, BWmax;
double GBWmin, GBWmax;
double BrietWigner(double Energy);
double CRFunction(double Energy);
AlgebraicFunction CustomRessonanceFunction;
bool CheckStatus;
wxString ErrorMessage;
bool ParseRessonanceList(wxString RessonanceWidth, wxString RessonancePeak, wxString RessonanceEnergy);
public:
RessonanceFunction(){};
RessonanceFunction(wxString CustomMacro);
RessonanceFunction(wxString RessonanceWidth, wxString RessonancePeak, wxString RessonanceEnergy);
RessonanceFunction(wxString RessonanceWidth, wxString RessonancePeak, wxString RessonanceEnergy, wxString RessonanceMinimum, wxString RessonanceMaximum);
void ResetFunction(){RFMode = 0; return;};
double GetValue(double Energy);
double GetDomainMinimum();
double GetDomainMaximum();
bool IsValid(){return CheckStatus;}
wxString GetErrorMessage(){return ErrorMessage;}
bool IsNullRessonance(){return (RFMode == 0);}
};

// Handle the distributions related to the straggling, thermal Doppler and Beam Resolution
class PhysicsDistribution
{
private:
double AverageBeamResolution, ThermalDopplerEnergy, AverageDopplerEnergy;
double ThermalStep,ThermalMinimum,ThermalMaximum,StraggStep,StraggMinimum,StraggMaximum;
GaussFunction ThermalFunction,StraggGauss;
LandauFunction StraggLandau;
VavilovEdgeworthFunction StraggEdgeworth;
VavilovAiryFunction StraggAiry;
VavilovMoyalFunction StraggMoyal;
DiracFunction StraggDirac,ThermalDirac;
unsigned int PDMode;
bool IsDefined;
wxString ErrorMessage;
public:
PhysicsDistribution(){};
PhysicsDistribution(wxString BeamResolution, wxString Temperature);
double GetBeamResolution(){return AverageBeamResolution;}
double GetThermalDoppler(double AtEnergy, double TargetMolarMass);
double GetThermalVariance(){return std::sqrt(AverageBeamResolution*AverageBeamResolution + AverageDopplerEnergy * AverageDopplerEnergy);};
bool CheckValidity(){return IsDefined;}
wxString GetErrorMessage(){return ErrorMessage;}
bool SetDistribution(double xi, double beta, double k, double DEM, double VEM, unsigned int Gauss, unsigned int Moyal, unsigned int Edgeworth, unsigned int Airy, unsigned int Landau, bool StrictGaussian);
double GetStraggStep(){return StraggStep;};
double GetStraggMin(){return StraggMinimum;};
double GetStraggMax(){return StraggMaximum;};
double GetThermalStep(){return ThermalStep;};
double GetThermalMin(){return ThermalMinimum;};
double GetThermalMax(){return ThermalMaximum;};
double GetValue(double StraggEnergy, double ThermalEnergy);
};

// Class to handle the detector efficiency in function of their energy.
class Detector
{
private:
std::vector<double> Energy;
std::vector<double> Sigma;
AlgebraicFunction DetectorFittingFunction;
bool Sucess;
bool DefinedFunction;
wxString ErrorCode;
public:
Detector(){};
Detector(DetectorParameters DetectorSetup);
double GetEval(double arg);
bool CheckDetector() {return Sucess;};
wxString GetErrorCode(){return ErrorCode;};
};


// For each Element declared on main screen, it should generate from the Database classes, an Element object.
class Element
{
private:
wxString Symbol;
double Stoichiometry;
double GammaPeak;
long Number;
long ZieglerModel;
double Abundance;
double Atomic;
double Isotopic;
double Density;
double Bloch;
std::vector<double> Energy;
std::vector<double> EnergyError;
std::vector<double> Sigma;
std::vector<double> SigmaError;
std::vector<double> ZieglerTable;
std::vector<double> SRIMEnergy;
std::vector<double> SRIMStoppingPower;
AlgebraicFunction CustomZieglerFunction;
void CreateElement(ElementDatabase ThisElement, ZieglerParameters ThisZiegler, ElementSRIMArray ThisSRIM, wxString StoichiometricGuess);
public:
Element(ElementDatabase ThisElement, ZieglerParameters ThisZiegler, ElementSRIMArray ThisSRIM, wxString StoichiometricGuess){this->CreateElement(ThisElement,ThisZiegler,ThisSRIM,StoichiometricGuess);};
double EvaluateSigma(double AtEnergy);
double EvaluateZiegler(double AtEnergy);
wxString GetIsotopeSymbol() { return Symbol;};
double GetGammaPeak() { return GammaPeak;};
int GetAtomicNumber() { return Number;};
long SetAtomicNumber(long value) { Number = value; return Number;};
double GetAbundance() { return Abundance;};
double SetAbundance(double value) { Abundance = value; return Abundance;};
double GetAtomicMass() { return Atomic;};
double SetAtomicMass(double value) { Atomic = value; return Atomic;};
double GetIsotopicMass() { return Isotopic;};
double SetIsotopicMass(double value) { Isotopic = value; return Isotopic;};
double GetStoichiometry() { return Stoichiometry;};
double SetStoichiometry(double value) { Stoichiometry = value; return Stoichiometry;};
double GetDensity(){ return Density;};
double GetBloch(){ return Bloch;};
double GetIonization(){return Bloch * Number * 0.001;};
};

// An auxiliary class for the array of Elements, for global handling.
class ElementVector : public ElementArray
{
private:
double TotalStoichiometry;
double TotalMass;
public:
ElementVector(){};
double GetTotalStoichiometry();
double GetTotalMass();
double EvaluateCrossSection(int ElementID, double AtEnergy);
double EvaluateBragg(double AtEnergy);
double GetMolarMass();
double GetIsotopicMass();
double GetGlobalDensity();
double GetGlobalCharge();
bool RenormStoichiometry();
double GetMassFraction(int ElementID);
};

// The atomic class to handle the layers calculations
class Layer
{
private:
double Thickness;
double ThicknessStep;
ElementVector LayerCompound;
double Xi(double E);
double Emax(double E);
double MakeBeta(double E);
public:
Layer(ElementVector CompoundElements, double LayerThickness, double LayerThicknessStep){LayerCompound = CompoundElements; Thickness = LayerThickness; ThicknessStep = LayerThicknessStep;};
double GetK(double E){return this->Xi(E)/this->Emax(E);};
double GetXi(double E){return this->Xi(E);};
double GetBeta(double E){return this->MakeBeta(E);};
double GetThickness(){return Thickness;};
double GetGammaPeakAt(int ElementID){return LayerCompound.Item(ElementID).GetGammaPeak();};
double GetAbundanceAt(int ElementID){return LayerCompound.Item(ElementID).GetAbundance();};
double GetAtomicMassAt(int ElementID){return LayerCompound.Item(ElementID).GetAtomicMass();};
double GetMassFractionAt(int ElementID){return LayerCompound.GetMassFraction(ElementID);};
double GetStoichiometryAt(int ElementID){return LayerCompound.Item(ElementID).GetStoichiometry();};
double EvaluateCrossSectionAt(int ElementID, double AtEnergy){return LayerCompound.EvaluateCrossSection(ElementID,AtEnergy);};
double GetMolarMass(){return LayerCompound.GetMolarMass();};
double EvaluateBragg(double AtEnergy){return LayerCompound.EvaluateBragg(AtEnergy);};
double GetGVL(double E);
double GetVVL(double E);
double GetDEML(double E){return LayerCompound.EvaluateBragg(E) * ThicknessStep * 0.001;};
};

// Sample class
class LayerVector : public LayerArray
{
private:
ElementVector LayerCompound;
bool CreateSample(ElementDatabaseArray AllElements, ZieglerParameters ThisZiegler, ElementSRIMArray ThisSRIM, wxGrid* SourceTable, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass,ArrayAtomicMass textAtomicMass, double DefaultLayerStep);
bool ErrorFlag;
wxString ErrorMessage;
public:
LayerVector(){};
LayerVector(ElementDatabaseArray AllElements, ZieglerParameters ThisZiegler, ElementSRIMArray ThisSRIM, wxGrid* SourceTable, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass,ArrayAtomicMass textAtomicMass, double DefaultLayerStep);
bool IsCorrect(){return ErrorFlag;};
wxString GetErrorMessage(){return ErrorMessage;};
int GetElementsCount(){return LayerCompound.GetCount();};
double GetGammaPeakAt(int ElementID){return LayerCompound.Item(ElementID).GetGammaPeak();};
double GetAbundanceAt(int ElementID){return LayerCompound.Item(ElementID).GetAbundance();};
double GetAtomicMassAt(int ElementID){return LayerCompound.Item(ElementID).GetAtomicMass();};
double GetMassFractionAt(int ElementID){return LayerCompound.GetMassFraction(ElementID);};
double GetAverageMolarMass();
double GetTotalThickness();
bool IsSampleBoundedAtThickness(double AtThickness);
int GetLayerAtThickness(double AtThickness);
};

// The atomic class to handle the yield calculations
class Yield
{
private:
int PositionID;
std::vector<double> YieldValues;
double ElementCharge;
double ElementEfficiency;
double YieldStep;
LayerVector LocalSample;
RessonanceFunction ElementRessonance;
PhysicsDistribution ElementDistribution;
double EvaluateSigma(int LayerNumber, double Energy);
double SigmaDistributionConvolution(int LayerNumber, double Energy);
double YieldFunction(int LayerNumber, double Energy);
public:
Yield(){};
Yield(int ElementID, double Charge, double Efficiency, double Step, LayerVector CurrentSample);
void Clear(){YieldValues.clear(); return;};
void AddNewYield(){YieldValues.push_back(0.0); return;};
double AddYieldLayer(RessonanceFunction CurrentRessonance, PhysicsDistribution CurrentDistribution, int AtLayer, double AtEnergy, double RangeEnergy);
std::vector<double> GetYield(){return YieldValues;}
};

// Yield Fittings require a Yield array overriding
class YieldVector : public YieldArray
{
private:
std::vector<double> YieldEnergy;
wxString ErrorCode;
public:
YieldVector(){};
YieldVector(std::vector<YieldVector> Original);
YieldVector(LayerVector CurrentSample, Detector CurrentDetector, double CurrentCharge, double CurrentStep);
void ClearData(){YieldEnergy.clear(); return;}
void SetEnergy(double InitialEnergy);
std::vector<double> SetValue(RessonanceFunction CurrentRessonance, PhysicsDistribution CurrentDistribution, int AtLayer, double AtEnergy, double RangeEnergy);
std::vector<double> GetEnergy(){return YieldEnergy;}
std::vector<double> GetYieldAt(int ElementID){return this->Item(ElementID).GetYield();}
wxString GetErrorCode(){return ErrorCode;};
};

// Handle sample slicing data, useful for partial results
class Sample
{
private:
double InitialEnergy;
std::vector<double> Depth;
std::vector<double> LayerNumber;
std::vector<double> DE;
std::vector<double> EM;
std::vector<double> KL;
std::vector<double> K;
std::vector<double> XiL;
std::vector<double> Xi;
std::vector<double> CurrentBeta;
std::vector<double> BL;
std::vector<double> BV;
std::vector<double> PY;
public:
Sample(){};
Sample(double SetInitialEnergy){InitialEnergy = SetInitialEnergy;};
void AddSampleLayer(double D, double L, double DEL, double EML, double KLL, double KU, double X, double XT, double beta, double BVL, double BVT, std::vector<double> PartialYield);
std::vector<double> GetDepth(){return Depth;};
std::vector<double> GetLayer(){return LayerNumber;};
std::vector<double> GetDE(){return DE;};
std::vector<double> GetEM(){return EM;};
std::vector<double> GetKL(){return KL;};
std::vector<double> GetKT(){return K;};
std::vector<double> GetXi(){return XiL;};
std::vector<double> GetXT(){return Xi;};
std::vector<double> GetBeta(){return CurrentBeta;};
std::vector<double> GetBL(){return BL;};
std::vector<double> GetBV(){return BV;};
std::vector<double> GetPY(){return PY;};
int GetNumberSampleElements(){return DE.size();};
int GetNumberYieldElements(){return PY.size()/DE.size();};
double GetInitialEnergy(){return InitialEnergy;};
};

// Handles all sample energy decay for all selected energies.
class SampleVector : public SampleArray
{
private:
int SumAllSamples();
public:
SampleVector(){};
SampleVector(std::vector<SampleVector> Original);
void NewRegister(double SetInitialEnergy){this->Add(Sample(SetInitialEnergy)); return;};
void SetValue(double D, double L, double DEL, double EML, double KLL, double KU, double X, double XT, double beta, double BVL, double BV, std::vector<double> PartialYield);
std::vector<double> GetSampleDepth(int Position){return this->Item(Position).GetDepth();};
std::vector<double> GetSampleLayer(int Position){return this->Item(Position).GetLayer();};
std::vector<double> GetSampleDE(int Position){return this->Item(Position).GetDE();};
std::vector<double> GetSampleEM(int Position){return this->Item(Position).GetEM();};
std::vector<double> GetSampleKL(int Position){return this->Item(Position).GetKL();};
std::vector<double> GetSampleKT(int Position){return this->Item(Position).GetKT();};
std::vector<double> GetSampleXi(int Position){return this->Item(Position).GetXi();};
std::vector<double> GetSampleXT(int Position){return this->Item(Position).GetXT();};
std::vector<double> GetSampleBeta(int Position){return this->Item(Position).GetBeta();};
std::vector<double> GetSampleBL(int Position){return this->Item(Position).GetBL();};
std::vector<double> GetSampleBV(int Position){return this->Item(Position).GetBV();};
std::vector<double> GetSamplePY(int Position){return this->Item(Position).GetPY();};
int GetNumberSampleElementsAt(int Position){return this->Item(Position).GetNumberSampleElements();};
int GetNumberYieldElementsAt(int Position){return this->Item(Position).GetNumberYieldElements();};
double GetInitialEnergyAt(int Position){return this->Item(Position).GetInitialEnergy();};
int GetNumberAllSample(){return this->SumAllSamples();}
};

// Base class that handles the interface between the GUI event, and the whole numeric setup
class ReactionProfiling
{
 private:
 long TotalNumberSteps, PartialNumberSteps, CompleteThreads;
 bool MainProcedure(wxStatusBar* progress);
 std::vector<YieldVector> TotalYield;
 std::vector<SampleVector> TotalSample;
 PhysicsDistribution LocalDistribution;
 RessonanceFunction LocalRessonance;
 LayerVector LocalSample;
 YieldVector LocalResults;
 SampleVector LocalDepth;
 Detector LocalDetector;
 wxString LastErrorCode;
 double Charge, EnergyStep, EnergyMinimum, EnergyMaximum;
 bool SampleComplete, InputComplete, DefaultParameters, RequireRessonance, RequireLog;
 unsigned int DefaultSampleStep, DefaultGauss, DefaultVavilovMoyal, DefaultVavilovEdgeworth, DefaultVavilovAiry, DefaultLandau, DefaultThreads;
 public:
 ReactionProfiling(){SampleComplete = false; InputComplete = false; RequireRessonance = false; DefaultParameters = true; LastErrorCode = wxT("General Error: Empty Input Data!");};
 bool StartProcedure(wxStatusBar* progress);
 bool SampleSetup(ElementDatabaseArray AllElements, ZieglerParameters ThisZiegler, DetectorParameters ThisDetector, ElementSRIMArray ThisSRIM, wxGrid* SourceTable, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass,ArrayAtomicMass textAtomicMass);
 bool SetOverrideParameters(unsigned int SamplePrecision, unsigned int GaussPrecision, unsigned int VavilovMoyalPrecision, unsigned int VavilovEdgeworthPrecision, unsigned int VavilovAiryPrecision, unsigned int LandauPrecision, unsigned int ThreadPrecision, bool EnableLog);
 bool SetInitialParameters(wxTextCtrl* valueBeamResolution, wxTextCtrl* valueTemperature, wxTextCtrl* valueCharge, wxTextCtrl* valueEnergyStep, wxTextCtrl* valueMinimumEnergy, wxTextCtrl* valueMaximumEnergy, wxTextCtrl* valueRessonanceWidth, wxTextCtrl* valueRessonancePeak, wxTextCtrl *valueRessonanceEnergy, wxTextCtrl *valueRessonanceMinimum, wxTextCtrl* valueRessonanceMaximum, wxTextCtrl* valueRessonanceFunction, bool boolRessonanceLorentzian, int intRessonanceMode);
 wxString GetErrorCode(){return LastErrorCode;};
 std::vector<double> GetEnergyRange(){return LocalResults.GetEnergy();};
 std::vector<double> GetElementYield(int ElementID){return LocalResults.GetYieldAt(ElementID);};
 int GetNumberElements(){return LocalResults.GetCount();};
 int GetNumberSamples(){return LocalDepth.GetCount();};
 int GetNumberAllSamples(){return LocalDepth.GetNumberAllSample();};
 std::vector<double> GetSampleDepth(int Position){return LocalDepth.GetSampleDepth(Position);};
 std::vector<double> GetSampleLayer(int Position){return LocalDepth.GetSampleLayer(Position);};
 std::vector<double> GetSampleDE(int Position){return LocalDepth.GetSampleDE(Position);};
 std::vector<double> GetSampleEM(int Position){return LocalDepth.GetSampleEM(Position);};
 std::vector<double> GetSampleKL(int Position){return LocalDepth.GetSampleKL(Position);};
 std::vector<double> GetSampleKT(int Position){return LocalDepth.GetSampleKT(Position);};
 std::vector<double> GetSampleXi(int Position){return LocalDepth.GetSampleXi(Position);};
 std::vector<double> GetSampleXT(int Position){return LocalDepth.GetSampleXT(Position);};
 std::vector<double> GetSampleBeta(int Position){return LocalDepth.GetSampleBeta(Position);};
 std::vector<double> GetSampleBL(int Position){return LocalDepth.GetSampleBL(Position);};
 std::vector<double> GetSampleBV(int Position){return LocalDepth.GetSampleBV(Position);};
 std::vector<double> GetSamplePY(int Position){return LocalDepth.GetSamplePY(Position);};
 int GetNumberSampleElementsAt(int Position){return LocalDepth.GetNumberSampleElementsAt(Position);};
 int GetNumberYieldElementsAt(int Position){return LocalDepth.GetNumberYieldElementsAt(Position);};
 double GetInitialEnergyAt(int Position){return LocalDepth.GetInitialEnergyAt(Position);};
};

#endif // REACTIONYIELD_H_INCLUDED
