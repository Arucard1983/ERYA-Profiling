/***************************************************************
 * Name:      FileLibrary.h
 * Purpose:   ERYA-Profiling file format for the Results(*.epz), Database (*.epd), Detector (*.epsd) and Ziegler(*.epsz) library
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2016-10-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#ifndef FILELIBRARY_H_INCLUDED
#define FILELIBRARY_H_INCLUDED
#include "ERYAProfiling.h"
#include "DatabaseLibrary.h"
#include "ParserLibrary.h"
#include "R33Library.h"
#include "XlsxLibrary.h"

class ERYAProfilingSampleFile
{
 private:
 wxString SampleFileName;
 public:
 ERYAProfilingSampleFile(wxString SampleFile){SampleFileName = SampleFile;};
 bool ERYAProfilingSampleLoad(wxArrayString& ListElements, wxArrayString& ListGammaPeaks, wxArrayString& ListNumber, wxArrayString& ListAbundance, wxArrayString& ListIsotopic, wxArrayString& ListAtomic, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingSampleSave(ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass, ArrayAtomicMass textAtomicMass, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingSampleXlsxLoad(wxArrayString& ListElements, wxArrayString& ListGammaPeaks, wxArrayString& ListNumber, wxArrayString& ListAbundance, wxArrayString& ListIsotopic, wxArrayString& ListAtomic, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingSampleXlsxSave(ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass, ArrayAtomicMass textAtomicMass, ElementDatabaseArray OpenDatabase);
};

class ERYAProfilingLayerFile
{
 private:
 wxString LayerFileName;
 public:
 ERYAProfilingLayerFile(wxString LayerFile){LayerFileName = LayerFile;};
 bool ERYAProfilingLayerLoad(wxArrayString& ListElementNames, wxArrayString& ListGammaPeaks, wxArrayString& LayerGridData, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingLayerSave(wxGrid* LayerTable, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingLayerTextLoad(wxGrid* &LayerTable, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingLayerTextSave(wxGrid* LayerTable, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingLayerXlsxLoad(wxArrayString& ListElementNames, wxArrayString& ListGammaPeaks, wxArrayString& LayerGridData, ElementDatabaseArray OpenDatabase);
 bool ERYAProfilingLayerXlsxSave(wxGrid* LayerTable, ElementDatabaseArray OpenDatabase);
};

class ERYAProfilingRessonanceFile
{
 private:
 wxString RessonanceFileName;
 public:
 ERYAProfilingRessonanceFile(wxString RessonanceFile){RessonanceFileName = RessonanceFile;};
 bool ERYAProfilingRessonanceLoad(wxTextCtrl* &valueBeamResolution, wxTextCtrl* &valueTemperature, wxTextCtrl* &valueCharge, wxTextCtrl* &valueEnergyStep, wxTextCtrl* &valueMinimumEnergy, wxTextCtrl* &valueMaximumEnergy, wxTextCtrl* &valueRessonanceWidth, wxTextCtrl* &valueRessonancePeak, wxTextCtrl* &valueRessonanceEnergy, wxTextCtrl* &valueRessonanceMinimum, wxTextCtrl* &valueRessonanceMaximum, wxTextCtrl* &valueRessonanceFunction, bool& boolRessonanceLorentzian, int& intRessonanceMode);
 bool ERYAProfilingRessonanceSave(wxTextCtrl* valueBeamResolution, wxTextCtrl* valueTemperature, wxTextCtrl* valueCharge, wxTextCtrl* valueEnergyStep, wxTextCtrl* valueMinimumEnergy, wxTextCtrl* valueMaximumEnergy, wxTextCtrl* valueRessonanceWidth, wxTextCtrl* valueRessonancePeak, wxTextCtrl *valueRessonanceEnergy, wxTextCtrl *valueRessonanceMinimum, wxTextCtrl* valueRessonanceMaximum, wxTextCtrl* valueRessonanceFunction, bool boolRessonanceLorentzian, int intRessonanceMode);
};

class ERYAProfilingGlobalFile
{
 private:
 wxString GlobalFileName;
 public:
 ERYAProfilingGlobalFile(wxString GlobalFile){GlobalFileName = GlobalFile;};
 bool ERYAProfilingGlobalLoad(wxTextCtrl* &valueBeamResolution, wxTextCtrl* &valueTemperature, wxTextCtrl* &valueCharge, wxTextCtrl* &valueEnergyStep, wxTextCtrl* &valueMinimumEnergy, wxTextCtrl* &valueMaximumEnergy, wxTextCtrl* &valueRessonanceWidth, wxTextCtrl* &valueRessonancePeak, wxTextCtrl* &valueRessonanceEnergy, wxTextCtrl* &valueRessonanceMinimum, wxTextCtrl* &valueRessonanceMaximum, wxTextCtrl* &valueRessonanceFunction, bool& boolRessonanceLorentzian, int& intRessonanceMode, wxArrayString& ListElements, wxArrayString& ListGammaPeaks, wxArrayString& ListNumber, wxArrayString& ListAbundance, wxArrayString& ListIsotopic, wxArrayString& ListAtomic, wxArrayString& LayerGridData, ElementDatabaseArray OpenDatabase, unsigned int& SampleStep, unsigned int& GaussStep, unsigned int& MoyalStep, unsigned int& EdgeworthStep, unsigned int& AiryStep, unsigned int& LandauStep, unsigned int& VavilovLimit, unsigned int& EnableLog);
 bool ERYAProfilingGlobalSave(wxTextCtrl* valueBeamResolution, wxTextCtrl* valueTemperature, wxTextCtrl* valueCharge, wxTextCtrl* valueEnergyStep, wxTextCtrl* valueMinimumEnergy, wxTextCtrl* valueMaximumEnergy, wxTextCtrl* valueRessonanceWidth, wxTextCtrl* valueRessonancePeak, wxTextCtrl *valueRessonanceEnergy, wxTextCtrl *valueRessonanceMinimum, wxTextCtrl* valueRessonanceMaximum, wxTextCtrl* valueRessonanceFunction, bool boolRessonanceLorentzian, int intRessonanceMode, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass, ArrayAtomicMass textAtomicMass,wxGrid* LayerTable, ElementDatabaseArray OpenDatabase, unsigned int SampleStep, unsigned int GaussStep, unsigned int MoyalStep, unsigned int EdgeworthStep, unsigned int AiryStep, unsigned int LandauStep, unsigned int VavilovLimit, unsigned int EnableLog);
};

class DatabaseFile
{
 private:
 wxString DatabaseFileName;
 wxString DatabaseFileVersion;
 ElementDatabaseArray ParsedDatabase;
 bool ElementBlockParsing(wxArrayString ElementBlock);
 public:
 DatabaseFile(wxString DatabaseFilePath, wxString Version, ElementDatabaseArray CurrentDatabase);
 bool ERYAProfilingDatabaseFileLoad();
 bool ERYAProfilingDatabaseFileSave();
 ElementDatabaseArray GetDatabase(){return ParsedDatabase;};
 };

 class DetectorFile
{
 private:
 wxString DetectorFileName;
 wxString DetectorFileVersion;
 DetectorParameters ParsedParameters;
 public:
 DetectorFile(wxString DetectorFilePath, wxString Version, DetectorParameters CurrentParameters);
 bool DetectorFileLoad();
 bool DetectorFileSave();
 DetectorParameters GetParameters(){return ParsedParameters;};
};

class ZieglerFile
{
 private:
 wxString ZieglerFileName;
 wxString ZieglerFileVersion;
 ZieglerParameters ParsedParameters;
 ElementSRIMArray ParsedTables;
 int TableMode;
 public:
 ZieglerFile(wxString ZieglerFilePath, wxString Version, ZieglerParameters CurrentParameters, ElementSRIMArray CurrentTables, int Argument);
 bool ZieglerFileLoad();
 bool ZieglerFileSave();
 ZieglerParameters GetParameters(){return ParsedParameters;};
 ElementSRIMArray GetTables(){return ParsedTables;};
};

#endif // FILELIBRARY_H_INCLUDED
