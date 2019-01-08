/***************************************************************
 * Name:      PlotLibrary.h
 * Purpose:   wxMathPlot derived classes for graphical plotting
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2017-03-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#ifndef __PlotLibrary__
#define __PlotLibrary__

#include "ERYAProfiling.h"
#include "DatabaseLibrary.h"
#include "ParserLibrary.h"
#include "XlsxLibrary.h"

// Handle a pair of STL-vectores to make a xy-plot between Energy and Sigma
class ElementEnergySigmaData : public mpFXYVector
{
std::vector<double> EnergyData;
std::vector<double> SigmaData;
public:
ElementEnergySigmaData() {};
ElementEnergySigmaData(wxString LabelEnergySigma):mpFXYVector(LabelEnergySigma, mpALIGN_LEFT) {};
void ExportGridVector(wxGrid* EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax);
void ExportDetectorVector(DetectorParameters EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax);
bool ExportFileTextVector(wxString EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax);
bool ExportXlsxTableVector(TableMatrix EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax);
std::vector<double> GetEnergyData() {return EnergyData;};
std::vector<double> GetSigmaData() {return SigmaData;};
std::vector<double> FitExperimentalData(wxArrayString InputEnergy, wxArrayString InputData);
};


#endif // __PlotLibrary__
