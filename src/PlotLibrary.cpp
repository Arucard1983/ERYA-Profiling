/***************************************************************
 * Name:      PlotLibrary.cpp
 * Purpose:   wxMathPlot derived class implementation for graphical plotting
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2017-03-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

 #include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "PlotLibrary.h"


void ElementEnergySigmaData::ExportGridVector(wxGrid* EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax)
{
 // Load the table to a pair of dynamic vectors
 if (EnergySigmaTable->GetNumberCols() >= 2)
 {
   bool endrecord = false;
   for (int k=0; k<EnergySigmaTable->GetNumberRows(); k++)
   {
     wxString temp1 = EnergySigmaTable->GetCellValue(k,0);
     wxString temp2 = EnergySigmaTable->GetCellValue(k,1);
     if (temp1.Len() > 0 && temp2.Len() > 0 && !endrecord)
     {
       double c1,c2;
       if(temp1.ToDouble(&c1) && temp2.ToDouble(&c2))
       {
         EnergyData.push_back(c1);
         SigmaData.push_back(c2);
       }
     }
     else
     {
       endrecord = true;
     }
   }
  if (EnergyData.size() > 0 && SigmaData.size() > 0)
 {
 GetEnergyMax = EnergyData.at(0);
 GetEnergyMin = EnergyData.at(0);
 GetSigmaMax = SigmaData.at(0);
 GetSigmaMin = SigmaData.at(0);
 // Get Energy maximum and minimum
 for (int i = 0; i < EnergyData.size(); i++)
 {
  if (EnergyData.at(i) < GetEnergyMin)
   GetEnergyMin = EnergyData.at(i);
  if (EnergyData.at(i) > GetEnergyMax)
   GetEnergyMax = EnergyData.at(i);
 }
 // Get Cross-Section maximum and minimum
 for (int j = 0; j < SigmaData.size(); j++)
 {
  if (SigmaData.at(j) < GetSigmaMin)
   GetSigmaMin = SigmaData.at(j);
  if (SigmaData.at(j) > GetSigmaMax)
   GetSigmaMax = SigmaData.at(j);
 }
  return;
 }
  else
  {
   GetEnergyMax = 0;
   GetEnergyMin = 1;
   GetSigmaMax = 0;
   GetSigmaMin = 1;
    return;
  }
 }
 else
 {
  EnergyData.clear();
  SigmaData.clear();
  return;
 }
}


void ElementEnergySigmaData::ExportDetectorVector(DetectorParameters EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax)
{
 // Load the table to a pair of dynamic vectors
 if (EnergySigmaTable.GetDetectorEnergy().GetCount() == EnergySigmaTable.GetDetectorEfficiency().GetCount())
 {
   for (int k=0; k<EnergySigmaTable.GetDetectorEnergy().GetCount(); k++)
   {
     wxString temp1 = EnergySigmaTable.GetDetectorEnergy().Item(k);
     wxString temp2 = EnergySigmaTable.GetDetectorEfficiency().Item(k);
     if (temp1.Len() > 0 && temp2.Len() > 0)
     {
       double c1,c2;
       if(temp1.ToDouble(&c1) && temp2.ToDouble(&c2))
       {
         EnergyData.push_back(c1);
         SigmaData.push_back(c2);
       }
     }
   }
  if (EnergyData.size() > 0 && SigmaData.size() > 0)
 {
 GetEnergyMax = EnergyData.at(0);
 GetEnergyMin = EnergyData.at(0);
 GetSigmaMax = SigmaData.at(0);
 GetSigmaMin = SigmaData.at(0);
 // Get Energy maximum and minimum
 for (int i = 0; i < EnergyData.size(); i++)
 {
  if (EnergyData.at(i) < GetEnergyMin)
   GetEnergyMin = EnergyData.at(i);
  if (EnergyData.at(i) > GetEnergyMax)
   GetEnergyMax = EnergyData.at(i);
 }
 // Get Cross-Section maximum and minimum
 for (int j = 0; j < SigmaData.size(); j++)
 {
  if (SigmaData.at(j) < GetSigmaMin)
   GetSigmaMin = SigmaData.at(j);
  if (SigmaData.at(j) > GetSigmaMax)
   GetSigmaMax = SigmaData.at(j);
 }
  return;
 }
  else
  {
   GetEnergyMax = 0;
   GetEnergyMin = 1;
   GetSigmaMax = 0;
   GetSigmaMin = 1;
    return;
  }
 }
 else
 {
  EnergyData.clear();
  SigmaData.clear();
  return;
 }
}

bool ElementEnergySigmaData::ExportFileTextVector(wxString EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax)
{
 // Load the text file to form a pair of dynamic vectors
 wxTextFile textfile(EnergySigmaTable);
 if(!(textfile.Exists()))
  return false;
 textfile.Open();
 for (int k=0; k<textfile.GetLineCount(); k++)
 {
   wxString CurrentLine = textfile.GetLine(k);
   TextLineParser CurrentLineData(CurrentLine, wxEmptyString);
   if (CurrentLineData.GetUnexcluded().GetCount() == 2)
    {
       double c1,c2;
       if(CurrentLineData.GetUnexcluded().Item(0).ToDouble(&c1) && CurrentLineData.GetUnexcluded().Item(1).ToDouble(&c2))
       {
         EnergyData.push_back(c1);
         SigmaData.push_back(c2);
       }
    }
    else
    {
    return false;
    }
 }
 textfile.Close();
 // Check data consistency
 if (EnergyData.size() > 0 && SigmaData.size() > 0)
 {
   GetEnergyMax = EnergyData.at(0);
   GetEnergyMin = EnergyData.at(0);
   GetSigmaMax = SigmaData.at(0);
   GetSigmaMin = SigmaData.at(0);
  // Get Energy maximum and minimum
  for (int i = 0; i < EnergyData.size(); i++)
  {
  if (EnergyData.at(i) < GetEnergyMin)
   GetEnergyMin = EnergyData.at(i);
  if (EnergyData.at(i) > GetEnergyMax)
   GetEnergyMax = EnergyData.at(i);
  }
 // Get Yield maximum and minimum
  for (int j = 0; j < SigmaData.size(); j++)
  {
   if (SigmaData.at(j) < GetSigmaMin)
    GetSigmaMin = SigmaData.at(j);
   if (SigmaData.at(j) > GetSigmaMax)
    GetSigmaMax = SigmaData.at(j);
  }
  return true;
 }
  else
  {
    return false;
  }
 }


bool ElementEnergySigmaData::ExportXlsxTableVector(TableMatrix EnergySigmaTable, std::vector<double>& EnergyData, std::vector<double>& SigmaData, double& GetEnergyMin, double& GetEnergyMax, double& GetSigmaMin, double& GetSigmaMax)
{
 // Load the table to a pair of dynamic vectors
 int NumberRows,NumberColumns;
 EnergySigmaTable.GetRealMatrixSize(NumberRows,NumberColumns);
 if (NumberColumns >= 2)
 {
   for (int k=0; k<NumberRows; k++)
   {
     int DataType1,DataType2;
     wxString temp1 = EnergySigmaTable.GetTableMatrixValueAt(k,0,DataType1);
     wxString temp2 = EnergySigmaTable.GetTableMatrixValueAt(k,1,DataType2);
     if (temp1.Len() > 0 && temp2.Len() > 0 && DataType1 == 1 && DataType2 == 1)
     {
       double c1,c2;
       if(temp1.ToDouble(&c1) && temp2.ToDouble(&c2))
       {
         EnergyData.push_back(c1);
         SigmaData.push_back(c2);
       }
     }
   }
 if (EnergyData.size() > 0 && SigmaData.size() > 0)
 {
 GetEnergyMax = EnergyData.at(0);
 GetEnergyMin = EnergyData.at(0);
 GetSigmaMax = SigmaData.at(0);
 GetSigmaMin = SigmaData.at(0);
 // Get Energy maximum and minimum
 for (int i = 0; i < EnergyData.size(); i++)
 {
  if (EnergyData.at(i) < GetEnergyMin)
   GetEnergyMin = EnergyData.at(i);
  if (EnergyData.at(i) > GetEnergyMax)
   GetEnergyMax = EnergyData.at(i);
 }
 // Get Cross-Section maximum and minimum
 for (int j = 0; j < SigmaData.size(); j++)
 {
  if (SigmaData.at(j) < GetSigmaMin)
   GetSigmaMin = SigmaData.at(j);
  if (SigmaData.at(j) > GetSigmaMax)
   GetSigmaMax = SigmaData.at(j);
 }
  return true;
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
}

