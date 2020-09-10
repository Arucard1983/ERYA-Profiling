/***************************************************************
 * Name:      FileLibrary.cpp
 * Purpose:   ERYA file format for the Results(*.epz), Database (*.epd), Detector (*.epsd) and Ziegler(*.epsz) implementation
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2016-10-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#include "FileLibrary.h"

// Load a predefined list of elements
bool ERYAProfilingSampleFile::ERYAProfilingSampleLoad(wxArrayString& ListElements, wxArrayString& ListGammaPeaks, wxArrayString& ListNumber, wxArrayString& ListAbundance, wxArrayString& ListIsotopic, wxArrayString& ListAtomic, ElementDatabaseArray OpenDatabase)
{
  // Process the list of elements, while check their presence on main database.
    wxXmlDocument LocalCompoundFile;
    wxString CurrentElement;
    wxString CurrentGamma;
    wxString CurrentNumber;
    wxString CurrentAbundance;
    wxString CurrentAtomic;
    wxString CurrentIsotopic;
    wxString CurrentID;
    ListElements.Clear();
    ListGammaPeaks.Clear();
    ListNumber.Clear();
    ListAbundance.Clear();
    ListIsotopic.Clear();
    ListAtomic.Clear();
    if(!(LocalCompoundFile.Load(SampleFileName)))
    {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + SampleFileName, wxT("Compound Sample File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
    }
   if(LocalCompoundFile.GetRoot()->GetName() != wxT("ERYA-Profiling_Sample"))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + SampleFileName, wxT("Compound Sample File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
   wxXmlNode *CompoundNode = LocalCompoundFile.GetRoot()->GetChildren();
   while(CompoundNode)
   {
    if(CompoundNode->GetName() == wxT("Sample_Data"))
    {
      wxXmlNode *CompoundData = CompoundNode->GetChildren();
      if(CompoundData->GetName() == wxT("Sample_Element"))
      {
        wxXmlNode *CompoundSector = CompoundData->GetChildren();
        while(CompoundSector)
        {
          if(CompoundSector->GetName() == wxT("register"))
          {
            CurrentID = CompoundSector->GetAttribute(wxT("ID"),wxT("0"));
            CurrentElement = wxT("E") + CompoundSector->GetAttribute(wxT("n"),wxT("0"));
            CurrentElement = CompoundSector->GetAttribute(wxT("Element_Name"),CurrentElement);
            CurrentGamma = CompoundSector->GetAttribute(wxT("Gamma_Peak"),wxT("0"));
            CurrentNumber = CompoundSector->GetAttribute(wxT("Atomic_Number"),wxT("0"));
            CurrentAbundance = CompoundSector->GetAttribute(wxT("Abundance"),wxT("0"));
            CurrentAtomic = CompoundSector->GetAttribute(wxT("Atomic_Mass"),wxT("0"));
            CurrentIsotopic = CompoundSector->GetAttribute(wxT("Isotopic_Mass"),wxT("0"));
            // Element exists?
            if(OpenDatabase.FindElement(CurrentElement,CurrentGamma) != wxNOT_FOUND)
            {
             ListElements.Add(CurrentElement);
             ListGammaPeaks.Add(CurrentGamma);
             ListNumber.Add(CurrentNumber);
             ListAbundance.Add(CurrentAbundance);
             ListIsotopic.Add(CurrentIsotopic);
             ListAtomic.Add(CurrentAtomic);
            }
            else
            {
               wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unknown Element \"") + CurrentElement + wxT("\" and Gamma Peak") + CurrentGamma + wxT("\" keV, from Database!\nPlease check if you load the correct Element Database, and try again!"), wxT("Compound Sample File Loading Error"), wxOK | wxICON_ERROR);
               dial->ShowModal();
               return false;
            }
          }
          CompoundSector = CompoundSector->GetNext();
        }
      }
    }
    CompoundNode = CompoundNode->GetNext();
   }
  return true;
}

// Save a predefined list of elements
bool ERYAProfilingSampleFile::ERYAProfilingSampleSave(ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass, ArrayAtomicMass textAtomicMass, ElementDatabaseArray OpenDatabase)
{
  // An xml file when written, all node are declared backwarks, but any atribute of the same node should be declared forwards
  wxXmlDocument LocalDatabase;
  wxXmlNode* database = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Sample");
  LocalDatabase.SetRoot(database);
  wxXmlNode* data = new wxXmlNode(database, wxXML_ELEMENT_NODE, "Sample_Data");
  wxXmlNode* block = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Sample_Element");
  for(int i=0; i<choiceElementName.GetCount(); i++)
  {
   // Get the current values
   int CurrentValue = choiceElementName.GetCount()-i;
   int ElementSlot = choiceElementName.Item(CurrentValue-1)->GetSelection();
   int GammaSlot = choiceGammaPeak.Item(CurrentValue-1)->GetSelection();
   wxString c0 = choiceElementName.Item(CurrentValue-1)->GetString(ElementSlot);
   if(c0.Len()==0)
    c0 = wxT("E") + wxString::Format("%i",CurrentValue);
   wxString c1 = choiceGammaPeak.Item(CurrentValue-1)->GetString(GammaSlot);
   if(c1.Len()==0)
    c1 = wxT("0");
   wxString c2 = textAtomicNumber.Item(CurrentValue-1)->GetValue();
   if(c2.Len()==0)
    c2 = wxT("0");
   wxString c3 = textAbundance.Item(CurrentValue-1)->GetValue();
   if(c3.Len()==0)
    c3 = wxT("0");
   wxString c4 = textIsotopicMass.Item(CurrentValue-1)->GetValue();
   if(c4.Len()==0)
    c4 = wxT("0");
   wxString c5 = textAtomicMass.Item(CurrentValue-1)->GetValue();
   if(c5.Len()==0)
    c5 = wxT("0");
   // Check Element ID
   int ElementRegister = OpenDatabase.FindElement(c0,c1);
   if(ElementRegister == wxNOT_FOUND)
    return false; //Fatal Error
    // Allocate the elements
    wxXmlNode* header = new wxXmlNode(block, wxXML_ELEMENT_NODE, "register");
    header->AddAttribute(wxT("n"),wxString::Format("%i",CurrentValue));
    header->AddAttribute(wxT("ID"),wxString::Format("%i",ElementRegister));
    header->AddAttribute(wxT("Element_Name"),c0);
    header->AddAttribute(wxT("Gamma_Peak"),c1);
    header->AddAttribute(wxT("Atomic_Number"),c2);
    header->AddAttribute(wxT("Abundance"),c3);
    header->AddAttribute(wxT("Atomic_Mass"),c4);
    header->AddAttribute(wxT("Isotopic_Mass"),c5);
  }
  // Save file header
  wxXmlNode* fileversion = new wxXmlNode(database, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.80")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
 // Save the file
 return LocalDatabase.Save(SampleFileName,0);
}

// Load a predefined list of elements, using the text version
bool ERYAProfilingSampleFile::ERYAProfilingSampleXlsxLoad(wxArrayString& ListElements, wxArrayString& ListGammaPeaks, wxArrayString& ListNumber, wxArrayString& ListAbundance, wxArrayString& ListIsotopic, wxArrayString& ListAtomic, ElementDatabaseArray OpenDatabase)
{
 XlsxFile file(SampleFileName);
 if(file.LoadFile())
 {
  // Initialization
  ListElements.Clear();
  ListGammaPeaks.Clear();
  ListNumber.Clear();
  ListAbundance.Clear();
  ListIsotopic.Clear();
  ListAtomic.Clear();
  //Extract the Excel file contents
  int SampleColumns,SampleRows;
  TableMatrix data = file.GetTableMatrix();
  data.GetRealMatrixSize(SampleRows,SampleColumns);
  // It is expected a six-column data, where the first column is an element name, and other columns should contains only numeric values. Any line that violates the template are discarded.
  if(SampleColumns>=6)
  {
   for(int i=0; i<SampleRows; i++) //Read a row each time
   {
    wxString c0,c1,c2,c3,c4,c5;
    int i0,i1,i2,i3,i4,i5;
    c0 = data.GetTableMatrixValueAt(i,0,i0);
    c1 = data.GetTableMatrixValueAt(i,1,i1);
    c2 = data.GetTableMatrixValueAt(i,2,i2);
    c3 = data.GetTableMatrixValueAt(i,3,i3);
    c4 = data.GetTableMatrixValueAt(i,4,i4);
    c5 = data.GetTableMatrixValueAt(i,5,i5);
    if(c0.Len()>0 && c1.Len()>0 && c2.Len()>0 && c3.Len()>0 && c4.Len()>0 && c5.Len()>0 && i0 == 0 && i1 == 1 && i2 == 1 && i3 == 1 && i4 == 1 && i5 == 1)
    {
     //A compatible line
      if(OpenDatabase.FindElement(c0,c1) != wxNOT_FOUND) // Check the presence of the Element on Database
      {
      ListElements.Add(c0);
      ListGammaPeaks.Add(c1);
      ListNumber.Add(c2);
      ListAbundance.Add(c3);
      ListIsotopic.Add(c4);
      ListAtomic.Add(c5);
      }
      else
      {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unknown Element \"") + c0 + wxT("\" and Gamma Peak") + c1 + wxT("\" keV, from Database!\nPlease check if you load the correct Element Database, and try again!"), wxT("Compound Sample File Loading Error"), wxOK | wxICON_ERROR);
      dial->ShowModal();
      return false;
      }
    }
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

bool ERYAProfilingSampleFile::ERYAProfilingSampleXlsxSave(ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass, ArrayAtomicMass textAtomicMass, ElementDatabaseArray OpenDatabase)
{
// Create the transference matrix
TableMatrix data(choiceElementName.GetCount()+1,6);
data.Add(TableNode(wxT("Element Name")));
data.Add(TableNode(wxT("Gamma Peak (keV)")));
data.Add(TableNode(wxT("Atomic Number")));
data.Add(TableNode(wxT("Abundance")));
data.Add(TableNode(wxT("Isotopic Mass")));
data.Add(TableNode(wxT("Atomic Mass")));
// Allocate the data
 for(int k=0; k<choiceElementName.GetCount(); k++)
 {
  int i = choiceElementName.Item(k)->GetSelection();
  int j = choiceGammaPeak.Item(k)->GetSelection();
  data.Add(TableNode(choiceElementName.Item(k)->GetString(i),0));
  data.Add(TableNode(choiceGammaPeak.Item(k)->GetString(j),1));
  data.Add(TableNode(textAtomicNumber.Item(k)->GetValue(),1));
  data.Add(TableNode(textAbundance.Item(k)->GetValue(),1));
  data.Add(TableNode(textIsotopicMass.Item(k)->GetValue(),1));
  data.Add(TableNode(textAtomicMass.Item(k)->GetValue(),1));
 }
 // Save the file
 XlsxFile file(SampleFileName,data,wxT("A1"));
 return file.WriteFile();
}

bool ERYAProfilingLayerFile::ERYAProfilingLayerLoad(wxArrayString& ListElementNames, wxArrayString& ListGammaPeaks, wxArrayString& LayerGridData, ElementDatabaseArray OpenDatabase)
{
  // Initial preparation
  wxArrayString ListLabels;
  ListElementNames.Clear();
  ListGammaPeaks.Clear();
  LayerGridData.Clear();
  // Process the XML document
  wxXmlDocument LayerDocument;
  if(!(LayerDocument.Load(LayerFileName)))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + LayerFileName, wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
 if(LayerDocument.GetRoot()->GetName() != wxT("ERYA-Profiling_Layer"))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + LayerFileName, wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
   wxXmlNode *LayerNode = LayerDocument.GetRoot()->GetChildren();
   while(LayerNode)
   {
    if(LayerNode->GetName() == wxT("Layer_Data")) //Main data entry point
    {
     wxXmlNode *LayerData = LayerNode->GetChildren();
     while(LayerData)
     {
      if(LayerData->GetName() == wxT("Layer_Labels")) //Get the table labels
      {
        wxXmlNode *LayerLabels = LayerData->GetChildren();
        while(LayerLabels)
        {
          if(LayerLabels->GetName() == wxT("label"))
          {
            wxString LayerCount = LayerLabels->GetAttribute(wxT("n"),wxT("0"));
            long LayerValue;
            if(LayerCount.ToLong(&LayerValue))
            {
              if(LayerValue > 0)
              {
              wxString LayerString;
              wxXmlNode *LayerStringValue = LayerLabels->GetChildren();
              if(LayerStringValue->GetName() == wxT("value"))
               {
                LayerString = LayerStringValue->GetNodeContent();
               }
              // The first column are reserved for the units, so the Element checking are skipped.
               if(LayerValue > 1)
               {
                 wxArrayString SpecialSymbols;
                 SpecialSymbols.Add("(");
                 SpecialSymbols.Add(")");
                 TextLineParser CurrentLabelData(LayerString, SpecialSymbols);
                 if(OpenDatabase.FindElement(CurrentLabelData.GetUnexcluded().Item(0),CurrentLabelData.GetUnexcluded().Item(1)) == wxNOT_FOUND)
                 {
                  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unknown Element \"") + CurrentLabelData.GetUnexcluded().Item(0) + wxT("\" and Gamma Peak") + CurrentLabelData.GetUnexcluded().Item(1) + wxT("\" keV, \nPlease check if you load the correct Element Database, and try again!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
                  dial->ShowModal();
                  return false;
                 }
                 else
                 {
                  ListElementNames.Add(CurrentLabelData.GetUnexcluded().Item(0));
                  ListGammaPeaks.Add(CurrentLabelData.GetUnexcluded().Item(1));
                  ListLabels.Add(LayerString);
                 }
               }
               else
               {
                 ListLabels.Add(wxT("Layer Density x*10^15 at/cm^2"));
               }
              }
              else
              {
               wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Labels!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
               dial->ShowModal();
               return false;
              }
            }
            else
            {
             wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Labels!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
             dial->ShowModal();
             return false;
            }
          }
         LayerLabels = LayerLabels->GetNext();
        }
      }
      if(LayerData->GetName() == wxT("Layer_Table")) //Load the table data itself
      {
        wxXmlNode *LayerRows = LayerData->GetChildren();
        while(LayerRows)
        {
          if(LayerRows->GetName() == wxT("layer"))
          {
            wxString LayerCount = LayerRows->GetAttribute(wxT("n"),wxT("0"));
            long LayerValue;
            if(!(LayerCount.ToLong(&LayerValue)))
            {
             wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Dimension!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
             dial->ShowModal();
             return false;
            }
            wxXmlNode *LayerCols = LayerRows->GetChildren();
            while(LayerCols)
            {
             if(LayerCols->GetName() == wxT("element"))
             {
               wxString ElementCount = LayerCols->GetAttribute(wxT("n"),wxT("0"));
               long ElementValue;
               if(ElementCount.ToLong(&ElementValue))
               {
                wxString ElementString;
                wxXmlNode *ElementStringValue = LayerCols->GetChildren();
                 if(ElementStringValue->GetName() == wxT("value"))
                 {
                  ElementString = ElementStringValue->GetNodeContent();
                  LayerGridData.Add(ElementString);
                 }
               }
               else
               {
               wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Dimension!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
               dial->ShowModal();
               return false;
               }
             }
             LayerCols = LayerCols->GetNext();
            }
          }
         LayerRows = LayerRows->GetNext();
        }
      }
     LayerData = LayerData->GetNext();
     }
    }
    LayerNode = LayerNode->GetNext();
   }
   // Generate the new Table Grid
   return true;
}

bool ERYAProfilingLayerFile::ERYAProfilingLayerSave(wxGrid* LayerTable, ElementDatabaseArray OpenDatabase)
{
 // Get table boundaries, and global options
 int LayerNumberLayers = LayerTable->GetNumberRows();
 int LayerNumberElements = LayerTable->GetNumberCols();
 for(int i=0; i<LayerTable->GetNumberRows(); i++)
 {
  if(LayerTable->GetCellValue(i,0) == wxEmptyString )
  {
    LayerNumberLayers = i;
    break;
  }
 }
 // Create the XML file structure
 // An xml file when written, all node are declared backwards, but any attribute of the same node should be declared forwards
  wxXmlDocument LocalLayer;
  wxXmlNode* layer = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Layer");
  LocalLayer.SetRoot(layer);
  wxXmlNode* data = new wxXmlNode(layer, wxXML_ELEMENT_NODE, "Layer_Data");
  wxXmlNode* block = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Layer_Table");
   // Write the spreadsheet table
 for(int i=0; i<LayerNumberLayers; i++)
 {
  wxString CurrentLayerIndex = wxString::Format("%i",LayerNumberLayers-i);
  wxXmlNode* datarow = new wxXmlNode(block, wxXML_ELEMENT_NODE, "layer");
   datarow->AddAttribute(wxT("n"),CurrentLayerIndex);
  for(int j=0; j<LayerNumberElements; j++)
  {
   wxString CurrentElementIndex = wxString::Format("%i",LayerNumberElements-j);
   wxXmlNode* datacol = new wxXmlNode(datarow, wxXML_ELEMENT_NODE, "element");
   datacol->AddAttribute(wxT("n"),CurrentElementIndex);
   wxXmlNode* datavalue = new wxXmlNode(datacol, wxXML_ELEMENT_NODE, "value");
       datavalue->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, LayerTable->GetCellValue(LayerNumberLayers-i-1,LayerNumberElements-j-1)));
  }
 }
 // Write the spreadsheet labels
 wxXmlNode* label = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Layer_Labels");
 for(int k=0; k<LayerNumberElements; k++)
  {
   wxString CurrentLabelIndex = wxString::Format("%i",LayerNumberElements-k);
   wxXmlNode* datalabel = new wxXmlNode(label, wxXML_ELEMENT_NODE, "label");
   datalabel->AddAttribute(wxT("n"),CurrentLabelIndex);
   wxXmlNode* labelvalue = new wxXmlNode(datalabel, wxXML_ELEMENT_NODE, "value");
       labelvalue->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, LayerTable->GetColLabelValue(LayerNumberElements-k-1)));
  }
 // Save file header
  wxXmlNode* fileversion = new wxXmlNode(layer, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.80")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
 // Save the file
 return LocalLayer.Save(LayerFileName,0);
}

bool ERYAProfilingLayerFile::ERYAProfilingLayerTextLoad(wxGrid* &LayerTable, ElementDatabaseArray OpenDatabase)
{
   // The LabView text format, can have a first line of Element labels, or even none to maintain compatibility of a labView program
   // However, in either cases, the Layer table should be already allocated on main screen.
   wxTextFile file(LayerFileName);
   file.Open();
   // Get table boundaries, and global options
   int LayerNumberLayers = LayerTable->GetNumberRows();
   int LayerNumberElements = LayerTable->GetNumberCols();
   LayerTable->ClearGrid();
   if(file.GetLineCount() > LayerNumberLayers) // Fix table
   {
    LayerTable->AppendRows(file.GetLineCount()-LayerNumberLayers,true);
   }
   // Process document, line by line.
   for(int k=0; k<file.GetLineCount(); k++)
   {
    wxString CurrentLine = file.GetLine(k); // Get the current line
    TextLineParser CurrentLineData(CurrentLine, wxEmptyString); // Define the custom parser rules
    wxArrayString CurrentTokens = CurrentLineData.GetUnexcluded();
    if(CurrentTokens.GetCount() == LayerTable->GetNumberCols()) // It should fit the table, otherwise it get an error
    {
     for(int z=0; z<CurrentTokens.GetCount(); z++) //Copy the values for each column, and check if it is a numerical one
     {
       double temp;
       wxString value = CurrentTokens.Item(z);
       if(value.ToDouble(&temp))
        LayerTable->SetCellValue(k,z,CurrentTokens.Item(z));
       else
        return false;
     }
    }
    else
    {
    LayerTable->ClearGrid();
    return false;
    }
   }
   file.Close();
   return true;
}

bool ERYAProfilingLayerFile::ERYAProfilingLayerTextSave(wxGrid* LayerTable, ElementDatabaseArray OpenDatabase)
{
 wxTextFile file(LayerFileName);
 file.Create();
 for(int i=0; i<LayerTable->GetNumberRows(); i++)
 {
  if(LayerTable->GetCellValue(i,0) == wxEmptyString )
   break; //Empty line break
  wxString CurrentLine;
  for(int j=0; j<LayerTable->GetNumberCols(); j++)
  {
    if(LayerTable->GetCellValue(i,j) == wxEmptyString )
    {
     CurrentLine = CurrentLine + wxT("0\t");
    }
    else
    {
     CurrentLine = CurrentLine + LayerTable->GetCellValue(i,j) + wxT("\t");
    }
  }
  file.AddLine(CurrentLine); // Write line of text
 }
 if(!(file.Write()))
  return false;
 file.Close();
 return true;
}

bool ERYAProfilingLayerFile::ERYAProfilingLayerXlsxLoad(wxArrayString& ListElementNames, wxArrayString& ListGammaPeaks, wxArrayString& LayerGridData, ElementDatabaseArray OpenDatabase)
{
 XlsxFile file(LayerFileName);
 if(file.LoadFile())
 {
  // Initialization
  ListElementNames.Clear();
  ListGammaPeaks.Clear();
  LayerGridData.Clear();
  //Extract the Excel file contents
  int SampleColumns,SampleRows;
  TableMatrix data = file.GetTableMatrix();
  data.GetRealMatrixSize(SampleRows,SampleColumns);
  // At last the transference matrix should not be empty
  if(SampleColumns>0 && SampleRows>0)
  {
   //Check if the source Excel file had a initial row for the element labels
   int TableShift = 1;
   for(int z=1; z<SampleColumns; z++) //The first column is the unit column, so can had any value
   {
    int Type;
    wxString LocalData = data.GetTableMatrixValueAt(0,z,Type);
    if(Type == 0)
    {
       wxArrayString SpecialSymbols; // Parse the string to get the element name and gamma peak value
       SpecialSymbols.Add(wxT("("));
       SpecialSymbols.Add(wxT(")"));
       SpecialSymbols.Add(wxT(":"));
       SpecialSymbols.Add(wxT(";"));
       TextLineParser CurrentLineData(LocalData, SpecialSymbols);
       wxString c0,c1;
       if(CurrentLineData.GetUnexcluded().GetCount()>0)
        c0 = CurrentLineData.GetUnexcluded().Item(0);
       else
        c0 = wxEmptyString;
       if(CurrentLineData.GetUnexcluded().GetCount()>1)
        c1 = CurrentLineData.GetUnexcluded().Item(1);
       else
        c1 = wxT("0");
       if(OpenDatabase.FindElement(c0,c1) == wxNOT_FOUND)
                 {
                  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unknown Element \"") + c0 + wxT("\" and Gamma Peak ") + c1 + wxT("\" keV, from Database!\nPlease check if you load the correct Element Database, and try again!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
                  dial->ShowModal();
                  return false;
                 }
                 else
                 {
                  ListElementNames.Add(c0);
                  ListGammaPeaks.Add(c1);
                 }
    }
    else
    {
      TableShift = 0;
      ListElementNames.Clear();
      ListGammaPeaks.Clear();
      break; //Not a label
    }
   }
   // Extract the transference matrix contents, that should be numeric ones
   for(int i=TableShift; i<SampleRows; i++)
   {
     int TestType;
     wxString TestValue = data.GetTableMatrixValueAt(i,0,TestType);
     if(TestValue.Len()>0 && TestType == 1) //If the leading line are empty or filled with something else, just ignore the row as a remark
     {
      for(int j=0; j<SampleColumns; j++)
      {
       int Type;
       wxString value = data.GetTableMatrixValueAt(i,j,Type);
       if(Type == 1)
        LayerGridData.Add(value);
       else
        LayerGridData.Add(wxT("0"));
      }
     }
   }
   return true; // Extract successful
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

bool ERYAProfilingLayerFile::ERYAProfilingLayerXlsxSave(wxGrid* LayerTable, ElementDatabaseArray OpenDatabase)
{
 // Get table boundaries, and global options
 int LayerNumberLayers = LayerTable->GetNumberRows();
 int LayerNumberElements = LayerTable->GetNumberCols();
 for(int i=0; i<LayerTable->GetNumberRows(); i++)
 {
  if(LayerTable->GetCellValue(i,0) == wxEmptyString )
  {
    LayerNumberLayers = i;
    break;
  }
 }
 // Create the transference matrix
 TableMatrix data(LayerNumberLayers+1,LayerNumberElements);
 // Add the labels
 for(int z=0; z<LayerTable->GetNumberCols(); z++)
 {
   data.Add(TableNode(LayerTable->GetColLabelValue(z)));
 }
 // Copy the contents
 for(int i=0; i<LayerTable->GetNumberRows(); i++)
 {
  for(int j=0; j<LayerTable->GetNumberCols(); j++)
  {
   // Check if the grid contents are strictly numerical.
   double temp;
   wxString value = LayerTable->GetCellValue(i,j);
   if(value.ToDouble(&temp))
     data.Add(TableNode(value,1));
   else
     data.Add(TableNode(wxT("0"),1));
  }
 }
 // Save the file
 XlsxFile file(LayerFileName,data,wxT("A1"));
 return file.WriteFile();
}

// Load the detector settings file
bool ERYAProfilingRessonanceFile::ERYAProfilingRessonanceLoad(wxTextCtrl* &valueBeamResolution, wxTextCtrl* &valueTemperature, wxTextCtrl* &valueCharge, wxTextCtrl* &valueEnergyStep, wxTextCtrl* &valueMinimumEnergy, wxTextCtrl* &valueMaximumEnergy, wxTextCtrl* &valueRessonanceWidth, wxTextCtrl* &valueRessonancePeak, wxTextCtrl* &valueRessonanceEnergy, wxTextCtrl* &valueRessonanceMinimum, wxTextCtrl* &valueRessonanceMaximum, wxTextCtrl* &valueRessonanceFunction, wxTextCtrl* &valueStrenghtWidth, wxTextCtrl* &valueStrenghtPeak, wxTextCtrl* &valueStrenghtEnergy, wxTextCtrl* &valueStrenghtMinimum, wxTextCtrl* &valueStrenghtMaximum, bool& boolRessonanceLorentzian, bool& boolRessonanceStrenght, int& intRessonanceMode)
{
 // Process the XML document
  wxXmlDocument RessonanceDocument;
  if(!(RessonanceDocument.Load(RessonanceFileName)))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + RessonanceFileName, wxT("Ressonance Profiling File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
 if(RessonanceDocument.GetRoot()->GetName() != wxT("ERYA-Profiling_Ressonance"))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + RessonanceFileName, wxT("Ressonance Profiling File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
   wxXmlNode *RessonanceNode = RessonanceDocument.GetRoot()->GetChildren();
   while(RessonanceNode)
   {
    if(RessonanceNode->GetName() == wxT("Ressonance_Data")) //Main data entry point
    {
     wxXmlNode *RessonanceData = RessonanceNode->GetChildren();
     while(RessonanceData)
     {
      if(RessonanceData->GetName() == wxT("Ressonance_Table"))
      {
        wxXmlNode *RessonanceValues = RessonanceData->GetChildren();
        if(RessonanceValues->GetName() == wxT("Ressonance_Values"))
        {
         wxString BeamResolution,Temperature,Charge,EnergyStep,MinimumEnergy,MaximumEnergy,RessonanceWidth,RessonancePeak,RessonanceEnergy,RessonanceMinimum,RessonanceMaximum,StrenghtWidth,StrenghtPeak,StrenghtEnergy,StrenghtMinimum,StrenghtMaximum,RessonanceOption,StrenghtOption,RessonanceMode;
         BeamResolution = RessonanceValues->GetAttribute(wxT("Beam_Resolution"),wxT("0"));
         Temperature = RessonanceValues->GetAttribute(wxT("Temperature"),wxT("300"));
         Charge = RessonanceValues->GetAttribute(wxT("Charge"),wxT("1"));
         EnergyStep = RessonanceValues->GetAttribute(wxT("Energy_Step"),wxT("1"));
         MinimumEnergy = RessonanceValues->GetAttribute(wxT("Minimum_Energy"),wxT("0"));
         MaximumEnergy = RessonanceValues->GetAttribute(wxT("Maximum_Energy"),wxT("0"));
         RessonanceWidth = RessonanceValues->GetAttribute(wxT("Ressonance_Width"),wxT("0"));
         RessonancePeak = RessonanceValues->GetAttribute(wxT("Ressonance_Peak"),wxT("0"));
         RessonanceEnergy = RessonanceValues->GetAttribute(wxT("Ressonance_Energy"),wxT("0"));
         RessonanceMinimum = RessonanceValues->GetAttribute(wxT("Ressonance_Minimum"),wxT("0"));
         RessonanceMaximum = RessonanceValues->GetAttribute(wxT("Ressonance_Maximum"),wxT("0"));
         StrenghtWidth = RessonanceValues->GetAttribute(wxT("Strenght_Width"),wxT("0"));
         StrenghtPeak = RessonanceValues->GetAttribute(wxT("Strenght_Peak"),wxT("0"));
         StrenghtEnergy = RessonanceValues->GetAttribute(wxT("Strenght_Energy"),wxT("0"));
         StrenghtMinimum = RessonanceValues->GetAttribute(wxT("Strenght_Minimum"),wxT("0"));
         StrenghtMaximum = RessonanceValues->GetAttribute(wxT("Strenght_Maximum"),wxT("0"));
         RessonanceOption = RessonanceValues->GetAttribute(wxT("Ressonance_Lorentzian"),wxT("0"));
         StrenghtOption = RessonanceValues->GetAttribute(wxT("Strenght_Lorentzian"),wxT("0"));
         RessonanceMode = RessonanceValues->GetAttribute(wxT("Ressonance_Mode"),wxT("0"));
         valueBeamResolution->SetValue(BeamResolution);
         valueTemperature->SetValue(Temperature);
         valueCharge->SetValue(Charge);
         valueEnergyStep->SetValue(EnergyStep);
         valueMinimumEnergy->SetValue(MinimumEnergy);
         valueMaximumEnergy->SetValue(MaximumEnergy);
         valueRessonanceWidth->SetValue(RessonanceWidth);
         valueRessonancePeak->SetValue(RessonancePeak);
         valueRessonanceEnergy->SetValue(RessonanceEnergy);
         valueRessonanceMinimum->SetValue(RessonanceMinimum);
         valueRessonanceMaximum->SetValue(RessonanceMaximum);
         valueStrenghtWidth->SetValue(StrenghtWidth);
         valueStrenghtPeak->SetValue(StrenghtPeak);
         valueStrenghtEnergy->SetValue(StrenghtEnergy);
         valueStrenghtMinimum->SetValue(StrenghtMinimum);
         valueStrenghtMaximum->SetValue(StrenghtMaximum);
         if(RessonanceOption == wxT("1"))
           boolRessonanceLorentzian = true;
         else
           boolRessonanceLorentzian = false;
         if(StrenghtOption == wxT("1"))
           boolRessonanceStrenght = true;
         else
           boolRessonanceStrenght = false;
         long value;
         if(RessonanceMode.ToLong(&value))
           intRessonanceMode = value;
         else
           intRessonanceMode = 0;
        }
      }
     if(RessonanceData->GetName() == wxT("Ressonance_Function"))
     {
     wxXmlNode *RessonanceFunction = RessonanceData->GetChildren();
     while(RessonanceFunction)
     {
       if(RessonanceFunction->GetName() == wxT("macro"))
       {
         wxString CustomFunction = RessonanceFunction->GetNodeContent();
         valueRessonanceFunction->SetValue(CustomFunction);
       }
       RessonanceFunction = RessonanceFunction->GetNext();
     }
     }
      RessonanceData = RessonanceData->GetNext();
     }
    }
    RessonanceNode = RessonanceNode->GetNext();
   }
   return true;
}

// Save the detector settings file
bool ERYAProfilingRessonanceFile::ERYAProfilingRessonanceSave(wxTextCtrl* valueBeamResolution, wxTextCtrl* valueTemperature, wxTextCtrl* valueCharge, wxTextCtrl* valueEnergyStep, wxTextCtrl* valueMinimumEnergy, wxTextCtrl* valueMaximumEnergy, wxTextCtrl* valueRessonanceWidth, wxTextCtrl* valueRessonancePeak, wxTextCtrl *valueRessonanceEnergy, wxTextCtrl *valueRessonanceMinimum, wxTextCtrl* valueRessonanceMaximum, wxTextCtrl* valueRessonanceFunction, wxTextCtrl* valueStrenghtWidth, wxTextCtrl* valueStrenghtPeak, wxTextCtrl* valueStrenghtEnergy, wxTextCtrl* valueStrenghtMinimum, wxTextCtrl* valueStrenghtMaximum, bool boolRessonanceLorentzian, bool boolRessonanceStrenght, int intRessonanceMode)
{
 // Global variables
 wxString RessonanceOption, StrenghtOption, RessonanceMode;
 if(boolRessonanceLorentzian)
    RessonanceOption = wxT("1");
 else
    RessonanceOption = wxT("0");
 if(boolRessonanceStrenght)
    StrenghtOption = wxT("1");
 else
    StrenghtOption = wxT("0");
 RessonanceMode = wxString::Format("%i",intRessonanceMode);
 // Create the XML file structure
 // An xml file when written, all node are declared backwards, but any attribute of the same node should be declared forwards
  wxXmlDocument LocalRessonance;
  wxXmlNode* ressonance = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Ressonance");
  LocalRessonance.SetRoot(ressonance);
  wxXmlNode* data = new wxXmlNode(ressonance, wxXML_ELEMENT_NODE, "Ressonance_Data");
   wxXmlNode* block = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ressonance_Table");
    wxXmlNode* datalabel = new wxXmlNode(block, wxXML_ELEMENT_NODE, "Ressonance_Values");
     datalabel->AddAttribute(wxT("Beam_Resolution"),valueBeamResolution->GetValue());
     datalabel->AddAttribute(wxT("Temperature"),valueTemperature->GetValue());
     datalabel->AddAttribute(wxT("Charge"),valueCharge->GetValue());
     datalabel->AddAttribute(wxT("Energy_Step"),valueEnergyStep->GetValue());
     datalabel->AddAttribute(wxT("Minimum_Energy"),valueMinimumEnergy->GetValue());
     datalabel->AddAttribute(wxT("Maximum_Energy"),valueMaximumEnergy->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Width"),valueRessonanceWidth->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Peak"),valueRessonancePeak->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Energy"),valueRessonanceEnergy->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Minimum"),valueRessonanceMinimum->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Maximum"),valueRessonanceMaximum->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Width"),valueStrenghtWidth->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Peak"),valueStrenghtPeak->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Energy"),valueStrenghtEnergy->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Minimum"),valueStrenghtMinimum->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Maximum"),valueStrenghtMaximum->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Lorentzian"),RessonanceOption);
     datalabel->AddAttribute(wxT("Strenght_Lorentzian"),StrenghtOption);
     datalabel->AddAttribute(wxT("Ressonance_Mode"),RessonanceMode);
  wxXmlNode* custom = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ressonance_Function");
   wxXmlNode* customvalue = new wxXmlNode(custom, wxXML_ELEMENT_NODE, "macro");
    customvalue->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, valueRessonanceFunction->GetValue()));
  // Save file header
  wxXmlNode* fileversion = new wxXmlNode(ressonance, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.80")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
 // Save the file
 return LocalRessonance.Save(RessonanceFileName,0);
}

// Global ERYA profiling file loading
bool ERYAProfilingGlobalFile::ERYAProfilingGlobalLoad(wxTextCtrl* &valueBeamResolution, wxTextCtrl* &valueTemperature, wxTextCtrl* &valueCharge, wxTextCtrl* &valueEnergyStep, wxTextCtrl* &valueMinimumEnergy, wxTextCtrl* &valueMaximumEnergy, wxTextCtrl* &valueRessonanceWidth, wxTextCtrl* &valueRessonancePeak, wxTextCtrl* &valueRessonanceEnergy, wxTextCtrl* &valueRessonanceMinimum, wxTextCtrl* &valueRessonanceMaximum, wxTextCtrl* &valueRessonanceFunction, wxTextCtrl* &valueStrenghtWidth, wxTextCtrl* &valueStrenghtPeak, wxTextCtrl* &valueStrenghtEnergy, wxTextCtrl* &valueStrenghtMinimum, wxTextCtrl* &valueStrenghtMaximum, bool& boolRessonanceLorentzian, bool& boolRessonanceStrenght, int& intRessonanceMode, wxArrayString& ListElements, wxArrayString& ListGammaPeaks, wxArrayString& ListNumber, wxArrayString& ListAbundance, wxArrayString& ListIsotopic, wxArrayString& ListAtomic, wxArrayString& LayerGridData, ElementDatabaseArray OpenDatabase, unsigned int& SampleStep, unsigned int& GaussStep, unsigned int& MoyalStep, unsigned int& EdgeworthStep, unsigned int& AiryStep, unsigned int& LandauStep, unsigned int& VavilovLimit, unsigned int& EnableLog)
{
 // Process the initial globl variables
    wxXmlDocument LocalFile;
    wxString CurrentElement;
    wxString CurrentGamma;
    wxString CurrentNumber;
    wxString CurrentAbundance;
    wxString CurrentAtomic;
    wxString CurrentIsotopic;
    wxString CurrentID;
    ListElements.Clear();
    ListGammaPeaks.Clear();
    ListNumber.Clear();
    ListAbundance.Clear();
    ListIsotopic.Clear();
    ListAtomic.Clear();
    wxArrayString ListLabels;
    LayerGridData.Clear();
 // Process the XML document
  if(!(LocalFile.Load(GlobalFileName)))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + GlobalFileName, wxT("ERYA Profiling File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
 if(LocalFile.GetRoot()->GetName() != wxT("ERYA-Profiling_Global"))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + GlobalFileName, wxT("ERYA Profiling File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
   wxXmlNode *GlobalNode = LocalFile.GetRoot()->GetChildren();
   while(GlobalNode)
   {
    if(GlobalNode->GetName() == wxT("Ressonance_Data")) //Main data entry point
    {
     wxXmlNode *RessonanceData = GlobalNode->GetChildren();
     while(RessonanceData)
     {
      if(RessonanceData->GetName() == wxT("Ressonance_Table"))
      {
        wxXmlNode *RessonanceValues = RessonanceData->GetChildren();
        if(RessonanceValues->GetName() == wxT("Ressonance_Values"))
        {
         wxString BeamResolution,Temperature,Charge,EnergyStep,MinimumEnergy,MaximumEnergy,RessonanceWidth,RessonancePeak,RessonanceEnergy,RessonanceMinimum,RessonanceMaximum,StrenghtWidth,StrenghtPeak,StrenghtEnergy,StrenghtMinimum,StrenghtMaximum,RessonanceOption,StrenghtOption,RessonanceMode;
         BeamResolution = RessonanceValues->GetAttribute(wxT("Beam_Resolution"),wxT("0"));
         Temperature = RessonanceValues->GetAttribute(wxT("Temperature"),wxT("300"));
         Charge = RessonanceValues->GetAttribute(wxT("Charge"),wxT("1"));
         EnergyStep = RessonanceValues->GetAttribute(wxT("Energy_Step"),wxT("1"));
         MinimumEnergy = RessonanceValues->GetAttribute(wxT("Minimum_Energy"),wxT("0"));
         MaximumEnergy = RessonanceValues->GetAttribute(wxT("Maximum_Energy"),wxT("0"));
         RessonanceWidth = RessonanceValues->GetAttribute(wxT("Ressonance_Width"),wxT("0"));
         RessonancePeak = RessonanceValues->GetAttribute(wxT("Ressonance_Peak"),wxT("0"));
         RessonanceEnergy = RessonanceValues->GetAttribute(wxT("Ressonance_Energy"),wxT("0"));
         RessonanceMinimum = RessonanceValues->GetAttribute(wxT("Ressonance_Minimum"),wxT("0"));
         RessonanceMaximum = RessonanceValues->GetAttribute(wxT("Ressonance_Maximum"),wxT("0"));
         StrenghtWidth = RessonanceValues->GetAttribute(wxT("Strenght_Width"),wxT("0"));
         StrenghtPeak = RessonanceValues->GetAttribute(wxT("Strenght_Peak"),wxT("0"));
         StrenghtEnergy = RessonanceValues->GetAttribute(wxT("Strenght_Energy"),wxT("0"));
         StrenghtMinimum = RessonanceValues->GetAttribute(wxT("Strenght_Minimum"),wxT("0"));
         StrenghtMaximum = RessonanceValues->GetAttribute(wxT("Strenght_Maximum"),wxT("0"));
         RessonanceOption = RessonanceValues->GetAttribute(wxT("Ressonance_Lorentzian"),wxT("0"));
         StrenghtOption = RessonanceValues->GetAttribute(wxT("Strenght_Lorentzian"),wxT("0"));
         RessonanceMode = RessonanceValues->GetAttribute(wxT("Ressonance_Mode"),wxT("0"));
         valueBeamResolution->SetValue(BeamResolution);
         valueTemperature->SetValue(Temperature);
         valueCharge->SetValue(Charge);
         valueEnergyStep->SetValue(EnergyStep);
         valueMinimumEnergy->SetValue(MinimumEnergy);
         valueMaximumEnergy->SetValue(MaximumEnergy);
         valueRessonanceWidth->SetValue(RessonanceWidth);
         valueRessonancePeak->SetValue(RessonancePeak);
         valueRessonanceEnergy->SetValue(RessonanceEnergy);
         valueRessonanceMinimum->SetValue(RessonanceMinimum);
         valueRessonanceMaximum->SetValue(RessonanceMaximum);
         valueStrenghtWidth->SetValue(StrenghtWidth);
         valueStrenghtPeak->SetValue(StrenghtPeak);
         valueStrenghtEnergy->SetValue(StrenghtEnergy);
         valueStrenghtMinimum->SetValue(StrenghtMinimum);
         valueStrenghtMaximum->SetValue(StrenghtMaximum);
         if(RessonanceOption == wxT("1"))
           boolRessonanceLorentzian = true;
         else
           boolRessonanceLorentzian = false;
         if(StrenghtOption == wxT("1"))
           boolRessonanceStrenght = true;
         else
           boolRessonanceStrenght = false;
         long value;
         if(RessonanceMode.ToLong(&value))
           intRessonanceMode = value;
         else
           intRessonanceMode = 0;
        }
      }
     if(RessonanceData->GetName() == wxT("Ressonance_Function"))
     {
     wxXmlNode *RessonanceFunction = RessonanceData->GetChildren();
     while(RessonanceFunction)
     {
       if(RessonanceFunction->GetName() == wxT("macro"))
       {
         wxString CustomFunction = RessonanceFunction->GetNodeContent();
         valueRessonanceFunction->SetValue(CustomFunction);
       }
       RessonanceFunction = RessonanceFunction->GetNext();
     }
     }
      RessonanceData = RessonanceData->GetNext();
     }
    }
    if(GlobalNode->GetName() == wxT("Precision_Data")) //Main data entry point
    {
     wxXmlNode *PrecisionData = GlobalNode->GetChildren();
     while(PrecisionData)
     {
      if(PrecisionData->GetName() == wxT("Precision_Table"))
      {
        wxXmlNode *PrecisionValues = PrecisionData->GetChildren();
        if(PrecisionValues->GetName() == wxT("Precision_Values"))
        {
         wxString SampleData,GaussData,MoyalData,EdgeworthData,AiryData, LandauData, VavilovData, LogData;
         unsigned long SampleValue, GaussValue, MoyalValue, EdgeworthValue, AiryValue, LandauValue, VavilovValue, LogValue;
         SampleData = PrecisionValues->GetAttribute(wxT("Sample_Step"),wxT("10"));
         GaussData = PrecisionValues->GetAttribute(wxT("Gauss_Step"),wxT("60"));
         MoyalData = PrecisionValues->GetAttribute(wxT("Vavilov_Moyal_Step"),wxT("10"));
         EdgeworthData = PrecisionValues->GetAttribute(wxT("Vavilov_Edgeworth_Step"),wxT("70"));
         AiryData = PrecisionValues->GetAttribute(wxT("Vavilov_Airy_Step"),wxT("100"));
         LandauData = PrecisionValues->GetAttribute(wxT("Landau_Step"),wxT("284"));
         VavilovData = PrecisionValues->GetAttribute(wxT("Vavilov_Limit"),wxT("1"));
         LogData = PrecisionValues->GetAttribute(wxT("Active_Log"),wxT("0"));
         SampleData.ToULong(&SampleValue);
         GaussData.ToULong(&GaussValue);
         MoyalData.ToULong(&MoyalValue);
         EdgeworthData.ToULong(&EdgeworthValue);
         AiryData.ToULong(&AiryValue);
         LandauData.ToULong(&LandauValue);
         VavilovData.ToULong(&VavilovValue);
         LogData.ToULong(&LogValue);
         SampleStep = static_cast<unsigned int>(SampleValue);
         GaussStep = static_cast<unsigned int>(GaussValue);
         MoyalStep = static_cast<unsigned int>(MoyalValue);
         EdgeworthStep = static_cast<unsigned int>(EdgeworthValue);
         AiryStep = static_cast<unsigned int>(AiryValue);
         LandauStep = static_cast<unsigned int>(LandauValue);
         VavilovLimit = static_cast<unsigned int>(VavilovValue);
         EnableLog = static_cast<unsigned int>(LogValue);
        }
      }
      PrecisionData = PrecisionData->GetNext();
     }
    }
    if(GlobalNode->GetName() == wxT("Layer_Data")) //Main data entry point
    {
     wxXmlNode *LayerData = GlobalNode->GetChildren();
     while(LayerData)
     {
      if(LayerData->GetName() == wxT("Layer_Labels")) //Get the table labels
      {
        wxXmlNode *LayerLabels = LayerData->GetChildren();
        while(LayerLabels)
        {
          if(LayerLabels->GetName() == wxT("label"))
          {
            wxString LayerCount = LayerLabels->GetAttribute(wxT("n"),wxT("0"));
            long LayerValue;
            if(LayerCount.ToLong(&LayerValue))
            {
              if(LayerValue > 0)
              {
              wxString LayerString;
              wxXmlNode *LayerStringValue = LayerLabels->GetChildren();
              if(LayerStringValue->GetName() == wxT("value"))
               {
                LayerString = LayerStringValue->GetNodeContent();
               }
              // The first column are reserved for the units, so the Element checking are skipped.
               if(LayerValue > 1)
               {
                 wxArrayString SpecialSymbols;
                 SpecialSymbols.Add("(");
                 SpecialSymbols.Add(")");
                 TextLineParser CurrentLabelData(LayerString, SpecialSymbols);
                 if(OpenDatabase.FindElement(CurrentLabelData.GetUnexcluded().Item(0),CurrentLabelData.GetUnexcluded().Item(1)) == wxNOT_FOUND)
                 {
                  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unknown Element \"") + CurrentLabelData.GetUnexcluded().Item(0) + wxT("\" and Gamma Peak") + CurrentLabelData.GetUnexcluded().Item(1) + wxT("\" keV, \nPlease check if you load the correct Element Database, and try again!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
                  dial->ShowModal();
                  return false;
                 }
                 else
                 {
                  ListElements.Add(CurrentLabelData.GetUnexcluded().Item(0));
                  ListGammaPeaks.Add(CurrentLabelData.GetUnexcluded().Item(1));
                  ListLabels.Add(LayerString);
                 }
               }
               else
               {
                 ListLabels.Add(wxT("Layer Density x*10^15 at/cm^2"));
               }
              }
              else
              {
               wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Labels!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
               dial->ShowModal();
               return false;
              }
            }
            else
            {
             wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Labels!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
             dial->ShowModal();
             return false;
            }
          }
         LayerLabels = LayerLabels->GetNext();
        }
      }
      if(LayerData->GetName() == wxT("Layer_Table")) //Load the table data itself
      {
        wxXmlNode *LayerRows = LayerData->GetChildren();
        while(LayerRows)
        {
          if(LayerRows->GetName() == wxT("layer"))
          {
            wxString LayerCount = LayerRows->GetAttribute(wxT("n"),wxT("0"));
            long LayerValue;
            if(!(LayerCount.ToLong(&LayerValue)))
            {
             wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Dimension!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
             dial->ShowModal();
             return false;
            }
            wxXmlNode *LayerCols = LayerRows->GetChildren();
            while(LayerCols)
            {
             if(LayerCols->GetName() == wxT("element"))
             {
               wxString ElementCount = LayerCols->GetAttribute(wxT("n"),wxT("0"));
               long ElementValue;
               if(ElementCount.ToLong(&ElementValue))
               {
                wxString ElementString;
                wxXmlNode *ElementStringValue = LayerCols->GetChildren();
                 if(ElementStringValue->GetName() == wxT("value"))
                 {
                  ElementString = ElementStringValue->GetNodeContent();
                  LayerGridData.Add(ElementString);
                 }
               }
               else
               {
               wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Table Dimension!"), wxT("Layer Profiling File Loading Error"), wxOK | wxICON_ERROR);
               dial->ShowModal();
               return false;
               }
             }
             LayerCols = LayerCols->GetNext();
            }
          }
         LayerRows = LayerRows->GetNext();
        }
      }
     LayerData = LayerData->GetNext();
     }
    }
    if(GlobalNode->GetName() == wxT("Sample_Data"))
    {
      wxXmlNode *CompoundData = GlobalNode->GetChildren();
      if(CompoundData->GetName() == wxT("Sample_Element"))
      {
        wxXmlNode *CompoundSector = CompoundData->GetChildren();
        while(CompoundSector)
        {
          if(CompoundSector->GetName() == wxT("register"))
          {
            CurrentID = CompoundSector->GetAttribute(wxT("ID"),wxT("0"));
            CurrentElement = wxT("E") + CompoundSector->GetAttribute(wxT("n"),wxT("0"));
            CurrentElement = CompoundSector->GetAttribute(wxT("Element_Name"),CurrentElement);
            CurrentGamma = CompoundSector->GetAttribute(wxT("Gamma_Peak"),wxT("0"));
            CurrentNumber = CompoundSector->GetAttribute(wxT("Atomic_Number"),wxT("0"));
            CurrentAbundance = CompoundSector->GetAttribute(wxT("Abundance"),wxT("0"));
            CurrentAtomic = CompoundSector->GetAttribute(wxT("Atomic_Mass"),wxT("0"));
            CurrentIsotopic = CompoundSector->GetAttribute(wxT("Isotopic_Mass"),wxT("0"));
            // Element exists?
            if(OpenDatabase.FindElement(CurrentElement,CurrentGamma) != wxNOT_FOUND)
            {
             ListElements.Add(CurrentElement);
             ListGammaPeaks.Add(CurrentGamma);
             ListNumber.Add(CurrentNumber);
             ListAbundance.Add(CurrentAbundance);
             ListIsotopic.Add(CurrentIsotopic);
             ListAtomic.Add(CurrentAtomic);
            }
            else
            {
               wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unknown Element \"") + CurrentElement + wxT("\" and Gamma Peak") + CurrentGamma + wxT("\" keV, from Database!\nPlease check if you load the correct Element Database, and try again!"), wxT("Compound Sample File Loading Error"), wxOK | wxICON_ERROR);
               dial->ShowModal();
               return false;
            }
          }
          CompoundSector = CompoundSector->GetNext();
        }
      }
    }
    GlobalNode = GlobalNode->GetNext();
   }
  // Removing duplicates
  if(ListElements.GetCount() == 2*ListNumber.GetCount())
  {
    for(int z=0; z<ListNumber.GetCount(); z++)
    {
      ListElements.RemoveAt(ListElements.GetCount()-1);
      ListGammaPeaks.RemoveAt(ListGammaPeaks.GetCount()-1);
    }
  }
  else
  {
    return false;
  }
  // Finishes and return
   return true;
}

// Global ERYA profilng file saving
bool ERYAProfilingGlobalFile::ERYAProfilingGlobalSave(wxTextCtrl* valueBeamResolution, wxTextCtrl* valueTemperature, wxTextCtrl* valueCharge, wxTextCtrl* valueEnergyStep, wxTextCtrl* valueMinimumEnergy, wxTextCtrl* valueMaximumEnergy, wxTextCtrl* valueRessonanceWidth, wxTextCtrl* valueRessonancePeak, wxTextCtrl *valueRessonanceEnergy, wxTextCtrl *valueRessonanceMinimum, wxTextCtrl* valueRessonanceMaximum, wxTextCtrl* valueRessonanceFunction, wxTextCtrl* valueStrenghtWidth, wxTextCtrl* valueStrenghtPeak, wxTextCtrl* valueStrenghtEnergy, wxTextCtrl* valueStrenghtMinimum, wxTextCtrl* valueStrenghtMaximum, bool boolRessonanceLorentzian, bool boolRessonanceStrenght, int intRessonanceMode, ArrayElement choiceElementName, ArrayGammaPeak choiceGammaPeak, ArrayAtomicNumber textAtomicNumber, ArrayAbundance textAbundance, ArrayIsotopicMass textIsotopicMass, ArrayAtomicMass textAtomicMass,wxGrid* LayerTable, ElementDatabaseArray OpenDatabase, unsigned int SampleStep, unsigned int GaussStep, unsigned int MoyalStep, unsigned int EdgeworthStep, unsigned int AiryStep, unsigned int LandauStep, unsigned int VavilovLimit, unsigned int EnableLog)
{
 // Global variables
 wxString RessonanceOption, StrenghtOption, RessonanceMode;
 if(boolRessonanceLorentzian)
    RessonanceOption = wxT("1");
 else
    RessonanceOption = wxT("0");
 if(boolRessonanceStrenght)
    StrenghtOption = wxT("1");
 else
    StrenghtOption = wxT("0");
 RessonanceMode = wxString::Format("%i",intRessonanceMode);
 int LayerNumberLayers = LayerTable->GetNumberRows();
 int LayerNumberElements = LayerTable->GetNumberCols();
 for(int i=0; i<LayerTable->GetNumberRows(); i++)
 {
  if(LayerTable->GetCellValue(i,0) == wxEmptyString )
  {
    LayerNumberLayers = i;
    break;
  }
 }
  // Create the XML file structure
 // An xml file when written, all node are declared backwards, but any attribute of the same node should be declared forwards
  wxXmlDocument LocalFile;
  wxXmlNode* global = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Global");
  LocalFile.SetRoot(global);
  wxXmlNode* data = new wxXmlNode(global, wxXML_ELEMENT_NODE, "Ressonance_Data"); //Ressonance root
   wxXmlNode* block = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ressonance_Table");
    wxXmlNode* datalabel = new wxXmlNode(block, wxXML_ELEMENT_NODE, "Ressonance_Values");
     datalabel->AddAttribute(wxT("Beam_Resolution"),valueBeamResolution->GetValue());
     datalabel->AddAttribute(wxT("Temperature"),valueTemperature->GetValue());
     datalabel->AddAttribute(wxT("Charge"),valueCharge->GetValue());
     datalabel->AddAttribute(wxT("Energy_Step"),valueEnergyStep->GetValue());
     datalabel->AddAttribute(wxT("Minimum_Energy"),valueMinimumEnergy->GetValue());
     datalabel->AddAttribute(wxT("Maximum_Energy"),valueMaximumEnergy->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Width"),valueRessonanceWidth->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Peak"),valueRessonancePeak->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Energy"),valueRessonanceEnergy->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Minimum"),valueRessonanceMinimum->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Maximum"),valueRessonanceMaximum->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Width"),valueStrenghtWidth->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Peak"),valueStrenghtPeak->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Energy"),valueStrenghtEnergy->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Minimum"),valueStrenghtMinimum->GetValue());
     datalabel->AddAttribute(wxT("Strenght_Maximum"),valueStrenghtMaximum->GetValue());
     datalabel->AddAttribute(wxT("Ressonance_Lorentzian"),RessonanceOption);
     datalabel->AddAttribute(wxT("Strenght_Lorentzian"),StrenghtOption);
     datalabel->AddAttribute(wxT("Ressonance_Mode"),RessonanceMode);
  wxXmlNode* custom = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ressonance_Function");
   wxXmlNode* customvalue = new wxXmlNode(custom, wxXML_ELEMENT_NODE, "macro");
    customvalue->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, valueRessonanceFunction->GetValue()));
  wxXmlNode* data0 = new wxXmlNode(global, wxXML_ELEMENT_NODE, "Precision_Data"); //Advanced root
   wxXmlNode* block0 = new wxXmlNode(data0, wxXML_ELEMENT_NODE, "Precision_Table");
    wxXmlNode* datalabel0 = new wxXmlNode(block0, wxXML_ELEMENT_NODE, "Precision_Values");
     datalabel0->AddAttribute(wxT("Sample_Step"),wxString::Format("%ui",SampleStep));
     datalabel0->AddAttribute(wxT("Gauss_Step"),wxString::Format("%ui",GaussStep));
     datalabel0->AddAttribute(wxT("Vavilov_Moyal_Step"),wxString::Format("%ui",MoyalStep));
     datalabel0->AddAttribute(wxT("Vavilov_Edgeworth_Step"),wxString::Format("%ui",EdgeworthStep));
     datalabel0->AddAttribute(wxT("Vavilov_Airy_Step"),wxString::Format("%ui",AiryStep));
     datalabel0->AddAttribute(wxT("Landau_Step"),wxString::Format("%ui",LandauStep));
     datalabel0->AddAttribute(wxT("Vavilov_Limit"),wxString::Format("%ui",VavilovLimit));
     datalabel0->AddAttribute(wxT("Active_Log"),wxString::Format("%ui",EnableLog));
  wxXmlNode* data1 = new wxXmlNode(global, wxXML_ELEMENT_NODE, "Layer_Data"); // Layer root
   wxXmlNode* block1 = new wxXmlNode(data1, wxXML_ELEMENT_NODE, "Layer_Table");
   // Write the spreadsheet table
 for(int i=0; i<LayerNumberLayers; i++)
 {
  wxString CurrentLayerIndex = wxString::Format("%i",LayerNumberLayers-i);
  wxXmlNode* data1row = new wxXmlNode(block1, wxXML_ELEMENT_NODE, "layer");
   data1row->AddAttribute(wxT("n"),CurrentLayerIndex);
  for(int j=0; j<LayerNumberElements; j++)
  {
   wxString CurrentElementIndex = wxString::Format("%i",LayerNumberElements-j);
   wxXmlNode* data1col = new wxXmlNode(data1row, wxXML_ELEMENT_NODE, "element");
   data1col->AddAttribute(wxT("n"),CurrentElementIndex);
   wxXmlNode* data1value = new wxXmlNode(data1col, wxXML_ELEMENT_NODE, "value");
       data1value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, LayerTable->GetCellValue(LayerNumberLayers-i-1,LayerNumberElements-j-1)));
  }
 }
 // Write the spreadsheet labels
 wxXmlNode* label = new wxXmlNode(data1, wxXML_ELEMENT_NODE, "Layer_Labels");
 for(int k=0; k<LayerNumberElements; k++)
  {
   wxString CurrentLabelIndex = wxString::Format("%i",LayerNumberElements-k);
   wxXmlNode* data1label = new wxXmlNode(label, wxXML_ELEMENT_NODE, "label");
   data1label->AddAttribute(wxT("n"),CurrentLabelIndex);
   wxXmlNode* labelvalue = new wxXmlNode(data1label, wxXML_ELEMENT_NODE, "value");
       labelvalue->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, LayerTable->GetColLabelValue(LayerNumberElements-k-1)));
  }
  wxXmlNode* data2 = new wxXmlNode(global, wxXML_ELEMENT_NODE, "Sample_Data"); //Elements root
  wxXmlNode* block2 = new wxXmlNode(data2, wxXML_ELEMENT_NODE, "Sample_Element");
  for(int i=0; i<choiceElementName.GetCount(); i++)
  {
   // Get the current values
   int CurrentValue = choiceElementName.GetCount()-i;
   int ElementSlot = choiceElementName.Item(CurrentValue-1)->GetSelection();
   int GammaSlot = choiceGammaPeak.Item(CurrentValue-1)->GetSelection();
   wxString c0 = choiceElementName.Item(CurrentValue-1)->GetString(ElementSlot);
   if(c0.Len()==0)
    c0 = wxT("E") + wxString::Format("%i",CurrentValue);
   wxString c1 = choiceGammaPeak.Item(CurrentValue-1)->GetString(GammaSlot);
   if(c1.Len()==0)
    c1 = wxT("0");
   wxString c2 = textAtomicNumber.Item(CurrentValue-1)->GetValue();
   if(c2.Len()==0)
    c2 = wxT("0");
   wxString c3 = textAbundance.Item(CurrentValue-1)->GetValue();
   if(c3.Len()==0)
    c3 = wxT("0");
   wxString c4 = textIsotopicMass.Item(CurrentValue-1)->GetValue();
   if(c4.Len()==0)
    c4 = wxT("0");
   wxString c5 = textAtomicMass.Item(CurrentValue-1)->GetValue();
   if(c5.Len()==0)
    c5 = wxT("0");
   // Check Element ID
   int ElementRegister = OpenDatabase.FindElement(c0,c1);
   if(ElementRegister == wxNOT_FOUND)
    return false; //Fatal Error
    // Allocate the elements
    wxXmlNode* header = new wxXmlNode(block2, wxXML_ELEMENT_NODE, "register");
    header->AddAttribute(wxT("n"),wxString::Format("%i",CurrentValue));
    header->AddAttribute(wxT("ID"),wxString::Format("%i",ElementRegister));
    header->AddAttribute(wxT("Element_Name"),c0);
    header->AddAttribute(wxT("Gamma_Peak"),c1);
    header->AddAttribute(wxT("Atomic_Number"),c2);
    header->AddAttribute(wxT("Abundance"),c3);
    header->AddAttribute(wxT("Atomic_Mass"),c4);
    header->AddAttribute(wxT("Isotopic_Mass"),c5);
  }
  // Save file header
  wxXmlNode* fileversion = new wxXmlNode(global, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.80")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
 // Save the file
 return LocalFile.Save(GlobalFileName,0);
}


// Database file main constructor
DatabaseFile::DatabaseFile(wxString DatabaseFilePath, wxString Version, ElementDatabaseArray CurrentDatabase)
{
 DatabaseFileName = DatabaseFilePath;
 DatabaseFileVersion = Version;
 ParsedDatabase = CurrentDatabase;
}

// A private function to handle the database parsing
bool DatabaseFile::ElementBlockParsing(wxArrayString ElementBlock)
{
  // Setup the needed parameters
   wxString CurrentElement;
   wxString CurrentGamma;
   wxString CurrentNumber;
   wxString CurrentAbundance;
   wxString CurrentAtomic;
   wxString CurrentIsotopic;
   wxArrayString CurrentEnergy;
   wxArrayString CurrentEnergyError;
   wxArrayString CurrentSigma;
   wxArrayString CurrentSigmaError;
   if (DatabaseFileVersion == wxT("txt")) // Process the  LabView database source file format (is a plain text file, luckily)
  {
   wxArrayString CurrentGammaStack; //Required for LabView file format correct handling
   wxArrayString AllEnergyStack; //Required for LabView file format correct handling
   wxArrayString AllSigmaStack; //Required for LabView file format correct handling

    for (int i=0; i<ElementBlock.GetCount(); i++)
   {
    // Get the tokens
    wxArrayString CurrentSeparators;
    CurrentSeparators.Add("(");
    CurrentSeparators.Add(")");
    TextLineParser CurrentBlockLine(ElementBlock.Item(i), CurrentSeparators);
    wxArrayString CurrentTokens = CurrentBlockLine.GetUnexcluded();
    if (CurrentTokens.Item(0) == wxT("_Element") && CurrentTokens.GetCount() > 1) // Get the Element Name
    {
      if(CurrentTokens.Last() != wxT("_Element"))
      CurrentElement = CurrentTokens.Last();
      else
      CurrentElement.Clear();
    }
    else if (CurrentTokens.Item(0) == wxT("_Abundance") && CurrentTokens.GetCount() > 1) // Get the Abundance
    {
      if(CurrentTokens.Last() != wxT("_Abundance"))
      CurrentAbundance = CurrentTokens.Last();
      else
      CurrentAbundance.Clear();
    }
    else if (CurrentTokens.Item(0) == wxT("_AtomicNumber") && CurrentTokens.GetCount() > 1) // Get the Atomic Number in ERYA version
    {
     if(CurrentTokens.Last() != wxT("_AtomicNumber"))
     CurrentNumber = CurrentTokens.Last();
     else
     CurrentNumber.Clear();
    }
    else if (CurrentTokens.Item(0) == wxT("_AtomicMass") && CurrentTokens.GetCount() > 1) // Get the Atomic Mass in ERYA version
    {
     if(CurrentTokens.Last() != wxT("_AtomicMass"))
     CurrentAtomic = CurrentTokens.Last();
     else
     CurrentAtomic.Clear();
    }
    else if (CurrentTokens.Item(0) == wxT("_IsotopicMass") && CurrentTokens.GetCount() > 1) // Get the Isotopic Mass in ERYA version
    {
     if(CurrentTokens.Last() != wxT("_IsotopicMass"))
     CurrentIsotopic = CurrentTokens.Last();
     else
     CurrentIsotopic.Clear();
    }
    else if (CurrentTokens.Item(0) == wxT("_Sigma")) // Get the Gamma Peak in ERYA version, which can have several values
    {
     if (CurrentTokens.GetCount()>1)
      {
       for (int a=1; a<CurrentTokens.GetCount(); a++)
       {
         wxString number = CurrentTokens.Item(a);
         number = number.Left(number.Find(wxT("keV"))); // Remove the "keV" suffix from the number
         CurrentGammaStack.Add(number);
       }
      }
      else // If the gamma peak was not declared, the program will assume an element on ground-state.
      {
        CurrentGamma = wxT("0");
        CurrentGammaStack.Add("0");
      }
    }
    else // Begin the numerical column of data processing, which is a pair of columns for each gamma peak
    {
     if(CurrentTokens.GetCount() == 2 * CurrentGammaStack.GetCount())
     {
         for(int a=0; a<CurrentGammaStack.GetCount(); a++)
         {
          // Old ERYA Format store the cross-section in keV.barn, so it is necessary to convert to keV.milibarn
          double SigmaValue;
          wxString EnergyData = CurrentTokens.Item(2*a);
          wxString SigmaData = CurrentTokens.Item(2*a+1);
          SigmaData.ToDouble(&SigmaValue);
          SigmaValue = SigmaValue * 1000;
          SigmaData = wxString::Format("%f",SigmaValue);
          AllEnergyStack.Add(EnergyData);
          AllSigmaStack.Add(SigmaData);
         }
     }
     else
     {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid Cross-Section Data of Element: ") + CurrentElement, wxT("Element Database File Error"), wxOK | wxICON_ERROR);
        dial->ShowModal();
        return false;
     }
    } // Finishes the current line.
   } // Complete the main cycle.

   // Generates a sequence of independent elements from the previous cross-section data-pairs.
   for(int k=0; k<CurrentGammaStack.GetCount(); k++)
   {
     // At new gamma-peak, means a new element, so the cross-section data will be cleared.
     CurrentEnergy.Clear();
     CurrentEnergyError.Clear();
     CurrentSigma.Clear();
     CurrentSigmaError.Clear();
     for(int z=0; z<AllEnergyStack.GetCount(); z++)
     {
       if(k == z%CurrentGammaStack.GetCount()) // Check if the actual bi-vector adress matches the current gamma-peak
       {
         CurrentEnergy.Add(AllEnergyStack.Item(z));
         CurrentEnergyError.Add("0");
         CurrentSigma.Add(AllSigmaStack.Item(z));
         CurrentSigmaError.Add("0");
       }
     }
     // Add a new element
     if (CurrentElement.Len()>0)
     {
     ElementDatabase StoreNewElement(CurrentElement, CurrentGammaStack.Item(k), CurrentNumber, CurrentAbundance, CurrentAtomic, CurrentIsotopic, CurrentEnergy, CurrentEnergyError, CurrentSigma, CurrentSigmaError, wxEmptyString);
     ParsedDatabase.Add(StoreNewElement);
     }
     else
     {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Anonymous Element Name found during Database file loading."), wxT("Element Database File Error"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     return false;
     }
   }
   // And finishes the procedure
   if(CurrentGammaStack.GetCount() == 0)
   {
    ElementDatabase StoreNewElement(CurrentElement, wxT("0"), CurrentNumber, CurrentAbundance, CurrentAtomic, CurrentIsotopic, CurrentEnergy, CurrentEnergyError, CurrentSigma, CurrentSigmaError, wxEmptyString);
    ParsedDatabase.Add(StoreNewElement);
    return true;
   }
    return true;
  }
 else  // Error
 {
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unsupported database file!"), wxT("Invalid Database Format"), wxOK | wxICON_ERROR);
  dial->ShowModal();
  return false;
 }
}

// Load the database from the file, where support two different file formats
bool DatabaseFile::ERYAProfilingDatabaseFileLoad()
{
 // Prepare the original file for processing
 ParsedDatabase.Clear();
 // Apply the supported modes
 if ( DatabaseFileVersion == wxT("epd")) // Apply ERYA Version rules
 {
    wxXmlDocument LocalDatabaseFile;
    wxString CurrentElement;
    wxString CurrentGamma;
    wxString CurrentNumber;
    wxString CurrentAbundance;
    wxString CurrentAtomic;
    wxString CurrentIsotopic;
    wxString CurrentRemark;
    wxString FileInfo, FileProgram, FileVersion, FileDateTime;
    wxArrayString CurrentEnergy;
    wxArrayString CurrentEnergyError;
    wxArrayString CurrentSigma;
    wxArrayString CurrentSigmaError;
    if(!(LocalDatabaseFile.Load(DatabaseFileName)))
    {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + DatabaseFileName, wxT("Database File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
    }
   if(!(LocalDatabaseFile.GetRoot()->GetName() == wxT("ERYA-Bulk_Database") || LocalDatabaseFile.GetRoot()->GetName() == wxT("ERYA-Profiling_Database")))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + DatabaseFileName, wxT("Database File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
   wxXmlNode *DatabaseNode = LocalDatabaseFile.GetRoot()->GetChildren();
   while(DatabaseNode)
   {
    if(DatabaseNode->GetName() == wxT("File_Details")) //Load header file
    {
      wxXmlNode *DatabaseFileInfo = DatabaseNode->GetChildren();
      if(DatabaseFileInfo->GetName() == wxT("Contents"))
      {
        wxXmlNode *DatabaseFileContents = DatabaseFileInfo->GetChildren();
        while(DatabaseFileContents)
        {
         if(DatabaseFileContents->GetName() == wxT("Program_Name"))
          {
            FileProgram = DatabaseFileContents->GetNodeContent();
          }
          if(DatabaseFileContents->GetName() == wxT("Program_Version"))
          {
            FileVersion = DatabaseFileContents->GetNodeContent();
          }
          if(DatabaseFileContents->GetName() == wxT("Date_File_Creation"))
          {
            FileDateTime = DatabaseFileContents->GetNodeContent();
          }
          if(DatabaseFileContents->GetName() == wxT("Remark"))
          {
            FileInfo = DatabaseFileContents->GetNodeContent();
            ParsedDatabase.SetInfo(FileInfo);
          }
          DatabaseFileContents = DatabaseFileContents->GetNext();
        }
      }
    }
    if(DatabaseNode->GetName() == wxT("Database_Data")) // Read the data section of Element's database
    {
     wxXmlNode *DatabaseData = DatabaseNode->GetChildren();
     while(DatabaseData)
     {
      if(DatabaseData->GetName() == wxT("Database_Element")) // Element's data main root
      {
        wxXmlNode *DatabaseSector = DatabaseData->GetChildren();
        while(DatabaseSector)
        {
          CurrentEnergy.Clear();
          CurrentEnergyError.Clear();
          CurrentSigma.Clear();
          CurrentSigmaError.Clear();
          if(DatabaseSector->GetName() == wxT("register"))
          {
            CurrentElement = wxT("E") + DatabaseSector->GetAttribute(wxT("n"),wxT("0"));
            CurrentElement = DatabaseSector->GetAttribute(wxT("Element_Name"),CurrentElement);
            CurrentGamma = DatabaseSector->GetAttribute(wxT("Gamma_Peak"),wxT("0"));
            CurrentNumber = DatabaseSector->GetAttribute(wxT("Atomic_Number"),wxT("0"));
            CurrentAbundance = DatabaseSector->GetAttribute(wxT("Abundance"),wxT("0"));
            CurrentAtomic = DatabaseSector->GetAttribute(wxT("Atomic_Mass"),wxT("0"));
            CurrentIsotopic = DatabaseSector->GetAttribute(wxT("Isotopic_Mass"),wxT("0"));
          }
         if(DatabaseSector->GetName() == wxT("Element_Remark"))
          {
            CurrentRemark = DatabaseSector->GetNodeContent();
          }
          if(DatabaseSector->GetName() == wxT("Cross-Section"))
          {
            wxXmlNode *DatabaseSigma = DatabaseSector->GetChildren();
            while(DatabaseSigma)
            {
             if(DatabaseSigma->GetName() == wxT("sector"))
             {
               wxString c0 = DatabaseSigma->GetAttribute(wxT("Energy"),wxT("0"));
               wxString c1 = DatabaseSigma->GetAttribute(wxT("Energy_Error"),wxT("0"));
               wxString c2 = DatabaseSigma->GetAttribute(wxT("Sigma"),wxT("0"));
               wxString c3 = DatabaseSigma->GetAttribute(wxT("Sigma_Error"),wxT("0"));
               CurrentEnergy.Add(c0);
               CurrentEnergyError.Add(c1);
               CurrentSigma.Add(c2);
               CurrentSigmaError.Add(c3);
             }
             DatabaseSigma = DatabaseSigma->GetNext();
            }
          }
          DatabaseSector = DatabaseSector->GetNext();
        }
        // Store the loaded element to the Database array memory
        ElementDatabase StoreNewElement(CurrentElement, CurrentGamma, CurrentNumber, CurrentAbundance, CurrentAtomic, CurrentIsotopic, CurrentEnergy, CurrentEnergyError, CurrentSigma, CurrentSigmaError, CurrentRemark);
        ParsedDatabase.Add(StoreNewElement);
      }
      DatabaseData = DatabaseData->GetNext(); // Next Element's sector
     }
    }
    DatabaseNode = DatabaseNode->GetNext();
   }
  return ParsedDatabase.SortElementDatabase();
 }
 else if (DatabaseFileVersion == wxT("txt")) // Use the ASCII version (deprecated), and the LabView version
 {
  LabViewElements LabViewBinaryDatabase(DatabaseFileName);
  if(LabViewBinaryDatabase.IsLabViewElements()) // Use the LabView Binary Database Loader
  {
    if(LabViewBinaryDatabase.IsLabViewElements()) // It is a compatible file ?
    {
     ParsedDatabase = LabViewBinaryDatabase.GetElementsFromLabView();
     return ParsedDatabase.SortElementDatabase();
    }
    else
    {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Fatal Error: Unexpected data structure!"), wxT("LabView Import Error"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     ParsedDatabase.Clear();
     return false;
    }
  }
  else // Apply ASCII version
  {
   wxTextFile file(DatabaseFileName);
   wxArrayString ElementBlock;
   file.Open();
   ElementBlock.Clear();
   ElementBlock.Add(file.GetLine(0));
   for(int i=1; i<file.GetLineCount(); i++)
   {
     wxString TestingLine = file.GetLine(i);
     wxString CheckLine = TestingLine.Left(TestingLine.Find("\t"));
     if ( CheckLine == wxT("_Element") ) // All records start with "_Element"
     {
      if(this->ElementBlockParsing(ElementBlock)) // Process the element database
       ElementBlock.Clear(); // And clears the temporary cache
      else
       return false;
      ElementBlock.Add(file.GetLine(i)); // Add the current line to the cache.
     }
     else
     {
      ElementBlock.Add(file.GetLine(i)); // Add the current line to the cache.
     }
   }
   if (ElementBlock.GetCount()>0) // Check remaining temporary memory
   {
     if(this->ElementBlockParsing(ElementBlock)) // Process the element database
      ElementBlock.Clear(); // And clears the temporary cache
     else
      return false;
   }
   file.Close();
   return ParsedDatabase.SortElementDatabase();
  }
 }
 else
 {
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Invalid or unknown database file format"), wxT("Error file loading"), wxOK | wxICON_ERROR);
 dial->ShowModal();
 return false;
 }
}

// Save the current database from memory to a file
bool DatabaseFile::ERYAProfilingDatabaseFileSave()
{
  // Check versions formats
 if (DatabaseFileVersion == wxT("epd"))  // ERYA Version
 {
  // Get the current time
  wxDateTime ThisTime = wxDateTime::Now();
  wxString ActualTime =ThisTime.Format(wxT("%Y-%m-%dT%H:%M:%S.00Z"),wxDateTime::WET);
  // An xml file when written, all node are declared backwarks, but any atribute of the same node should be declared forwards
  wxXmlDocument LocalDatabase;
  wxXmlNode* database = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Database");
  LocalDatabase.SetRoot(database);
  wxXmlNode* data = new wxXmlNode(database, wxXML_ELEMENT_NODE, "Database_Data");
  for(int i=0; i<ParsedDatabase.GetCount(); i++)
  {
   wxXmlNode* block = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Database_Element");
   // Get the current values
   int CurrentValue = ParsedDatabase.GetCount()-i;
   wxString c0 = ParsedDatabase.Item(CurrentValue-1).GetElement();
   wxString c1 = ParsedDatabase.Item(CurrentValue-1).GetGamma();
   wxString c2 = ParsedDatabase.Item(CurrentValue-1).GetNumber();
   wxString c3 = ParsedDatabase.Item(CurrentValue-1).GetAbundance();
   wxString c4 = ParsedDatabase.Item(CurrentValue-1).GetAtomic();
   wxString c5 = ParsedDatabase.Item(CurrentValue-1).GetIsotopic();
   wxString c6 = ParsedDatabase.Item(CurrentValue-1).GetInfo();
   // Allocate the cross-section data
     wxXmlNode* cross = new wxXmlNode(block, wxXML_ELEMENT_NODE, "Cross-Section");
     for(int j=0; j<ParsedDatabase.Item(CurrentValue-1).GetEnergy().GetCount(); j++)
     {
      int CurrentSigma = ParsedDatabase.Item(CurrentValue-1).GetEnergy().GetCount()-j;
      if (ParsedDatabase.Item(CurrentValue-1).GetEnergy().Item(CurrentSigma-1).Len() > 0 && ParsedDatabase.Item(CurrentValue-1).GetSigma().Item(CurrentSigma-1).Len() > 0 )
      {
       wxString s0 = ParsedDatabase.Item(CurrentValue-1).GetEnergy().Item(CurrentSigma-1);
       wxString s1 = ParsedDatabase.Item(CurrentValue-1).GetEnergyError().Item(CurrentSigma-1);
       wxString s2 = ParsedDatabase.Item(CurrentValue-1).GetSigma().Item(CurrentSigma-1);
       wxString s3 = ParsedDatabase.Item(CurrentValue-1).GetSigmaError().Item(CurrentSigma-1);
       wxXmlNode* sigma = new wxXmlNode(cross, wxXML_ELEMENT_NODE, "sector");
       sigma->AddAttribute(wxT("n"),wxString::Format("%i",CurrentSigma));
       sigma->AddAttribute(wxT("Energy"),s0);
       sigma->AddAttribute(wxT("Energy_Error"),s1);
       sigma->AddAttribute(wxT("Sigma"),s2);
       sigma->AddAttribute(wxT("Sigma_Error"),s3);
      }
     }
    // Allocate the remark header
    wxXmlNode* elementremark = new wxXmlNode(block, wxXML_ELEMENT_NODE, "Element_Remark");
     elementremark->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c6));
    // Allocate the elements
    wxXmlNode* header = new wxXmlNode(block, wxXML_ELEMENT_NODE, "register");
    header->AddAttribute(wxT("n"),wxString::Format("%i",CurrentValue));
    header->AddAttribute(wxT("Element_Name"),c0);
    header->AddAttribute(wxT("Gamma_Peak"),c1);
    header->AddAttribute(wxT("Atomic_Number"),c2);
    header->AddAttribute(wxT("Abundance"),c3);
    header->AddAttribute(wxT("Atomic_Mass"),c4);
    header->AddAttribute(wxT("Isotopic_Mass"),c5);
  }
  // Save file header
  wxXmlNode* fileversion = new wxXmlNode(database, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programremark = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Remark");
     programremark->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ParsedDatabase.GetInfo()));
   wxXmlNode* programdatetime = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Date_File_Creation");
     programdatetime->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ActualTime));
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.80")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
 // Save the file
 return LocalDatabase.Save(DatabaseFileName,0);
}
else if (DatabaseFileVersion == wxT("txt")) // LabView Source ERYA Version
{
 wxTextFile file(DatabaseFileName);
 file.Create();
 for(int i=0; i<ParsedDatabase.GetCount(); i++)
 {
  file.AddLine( wxT("_Element\t") + ParsedDatabase.Item(i).GetElement());
  file.AddLine( wxT("_AtomicNumber\t") + ParsedDatabase.Item(i).GetNumber());
  file.AddLine( wxT("_Abundance\t") + ParsedDatabase.Item(i).GetAbundance());
  file.AddLine( wxT("_AtomicMass\t") + ParsedDatabase.Item(i).GetAtomic());
  file.AddLine( wxT("_IsotopicMass\t") + ParsedDatabase.Item(i).GetIsotopic());
  file.AddLine( wxT("_Sigma\t(") + ParsedDatabase.Item(i).GetGamma() + wxT("keV)"));
  for(int j=0; j<ParsedDatabase.Item(i).GetEnergy().GetCount(); j++)
  {
   if (ParsedDatabase.Item(i).GetEnergy().Item(j).Len() > 0 && ParsedDatabase.Item(i).GetSigma().Item(j).Len() > 0)
   {
    // It's necessary to convert the standard keV.mb to the keV.b before store on file
    double SigmaValue;
    wxString EnergyData = ParsedDatabase.Item(i).GetEnergy().Item(j);
    wxString SigmaData = ParsedDatabase.Item(i).GetSigma().Item(j);
    SigmaData.ToDouble(&SigmaValue);
    SigmaValue = SigmaValue / 1000;
    SigmaData = wxString::Format("%f",SigmaValue);
    file.AddLine( EnergyData + wxT("\t") + SigmaData);
   }
  }
 }
 file.Write();
 file.Close();
 return true;
} // End Old ERYA Version
 else  // Error
 {
  wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Cannot save database in this format!"), wxT("Invalid Database Format"), wxOK | wxICON_ERROR);
  dial->ShowModal();
  return false;
 }
}

// Detector file main constructor
DetectorFile::DetectorFile(wxString DetectorFilePath, wxString Version, DetectorParameters CurrentParameters)
{
 DetectorFileName = DetectorFilePath;
 DetectorFileVersion = Version;
 ParsedParameters = CurrentParameters;
}

// Loads the Detector settings from the file, which can be the default standard, or the old version from ITN
bool DetectorFile::DetectorFileLoad()
{
 wxString FileProgram, FileVersion, FileDateTime, FileInfo;
 ParsedParameters.Clear();
 if (DetectorFileVersion == wxT("epsd"))
  {
    wxXmlDocument LocalDetectorFile;
    if(!(LocalDetectorFile.Load(DetectorFileName)))
    {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + DetectorFileName, wxT("Detector File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
    }
   if(!(LocalDetectorFile.GetRoot()->GetName() == wxT("ERYA-Bulk_Detector") || LocalDetectorFile.GetRoot()->GetName() == wxT("ERYA-Profiling_Detector")))
   {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + DetectorFileName, wxT("Detector File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
   }
   wxXmlNode *DetectorNode = LocalDetectorFile.GetRoot()->GetChildren();
   while(DetectorNode)
   {
    if(DetectorNode->GetName() == wxT("File_Details")) //Load header file
    {
      wxXmlNode *DetectorFileInfo = DetectorNode->GetChildren();
      if(DetectorFileInfo->GetName() == wxT("Contents"))
      {
        wxXmlNode *DetectorFileContents = DetectorFileInfo->GetChildren();
        while(DetectorFileContents)
        {
         if(DetectorFileContents->GetName() == wxT("Program_Name"))
          {
            FileProgram = DetectorFileContents->GetNodeContent();
          }
          if(DetectorFileContents->GetName() == wxT("Program_Version"))
          {
            FileVersion = DetectorFileContents->GetNodeContent();
          }
          if(DetectorFileContents->GetName() == wxT("Date_File_Creation"))
          {
            FileDateTime = DetectorFileContents->GetNodeContent();
          }
          if(DetectorFileContents->GetName() == wxT("Remark"))
          {
            FileInfo = DetectorFileContents->GetNodeContent();
            ParsedParameters.SetInfo(FileInfo);
          }
          DetectorFileContents = DetectorFileContents->GetNext();
        }
      }
    }
    if(DetectorNode->GetName() == wxT("Detector_Data")) //Main data entry point
    {
     wxXmlNode *DetectorData = DetectorNode->GetChildren();
     while(DetectorData)
     {
      if(DetectorData->GetName() == wxT("Detector_Function")) //Load the custom function
      {
        wxString CustomFunction;
        wxXmlNode *DetectorFunction = DetectorData->GetChildren();
        if(DetectorFunction->GetName() == wxT("macro"))
         {
           CustomFunction = DetectorFunction->GetNodeContent();
         }
        ParsedParameters.SetDetectorFunction(CustomFunction);
      }
      if(DetectorData->GetName() == wxT("Energy_Efficiency")) //Get the table data
      {
        wxXmlNode *DetectorElement = DetectorData->GetChildren();
        while(DetectorElement)
        {
          if(DetectorElement->GetName() == wxT("register"))
          {
            wxString ActualEnergy = DetectorElement->GetAttribute(wxT("Energy"),wxT("0"));
            wxString ActualEfficiency = DetectorElement->GetAttribute(wxT("Efficiency"),wxT("0"));
            ParsedParameters.AddEnergyEfficiencyData(ActualEnergy,ActualEfficiency);
          }
         DetectorElement = DetectorElement->GetNext();
        }
      }
     DetectorData = DetectorData->GetNext();
     }
    }
    DetectorNode = DetectorNode->GetNext();
   }
   return true;
  }
  else if(DetectorFileVersion == wxT("txt"))
  {
   // The LabView ERYA format are simply a file with two columns of numbers, and the model function are hardcoded to the program
    wxTextFile file(DetectorFileName);
   file.Open();
  for(int i=0; i<file.GetLineCount(); i++)
  {
    wxString CurrentLine = file.GetLine(i); // Get the current line
    TextLineParser CurrentLineData(CurrentLine, wxEmptyString); // Define the custom parser rules
    if(CurrentLineData.GetUnexcluded().GetCount() == 2)
    {
     ParsedParameters.AddEnergyEfficiencyData(CurrentLineData.GetUnexcluded().Item(0), CurrentLineData.GetUnexcluded().Item(1));
    }
    else
    {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Fatal Error: Invalid file format!"), wxT("Import Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    ParsedParameters.Clear();
    return false;
    }
  }
   ParsedParameters.SetDetectorFunction(wxEmptyString);
   file.Close();
   return true;
  }
  else if(DetectorFileVersion == wxT("xlsx"))
 {
  XlsxFile DetectorXlsxFile(DetectorFileName);
  if(DetectorXlsxFile.LoadFile())
  {
   TableMatrix DetectorMatrix = DetectorXlsxFile.GetTableMatrix();
   int NumberElements,NumberValues;
   DetectorMatrix.GetRealMatrixSize(NumberElements,NumberValues);
   if(NumberElements > 1 && NumberValues == 2)
   {
     // Check and verify if a line are a pure numerical, otherwise, ignore the line since it is a label
     for(int i=0; i<NumberElements; i++)
     {
      int temp;
      double v0,v1;
      wxString c0 = DetectorMatrix.GetTableMatrixValueAt(i,0,temp);
      wxString c1 = DetectorMatrix.GetTableMatrixValueAt(i,1,temp);
      // Store the line
      if(c0.ToDouble(&v0) && c1.ToDouble(&v1))
       ParsedParameters.AddEnergyEfficiencyData(c0,c1);
     }
    return true;
   }
   else
   {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Expected a 2 column table"), wxT("Import Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    ParsedParameters.Clear();
    return false;
   }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Fatal Error: Invalid file format!"), wxT("Import Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    ParsedParameters.Clear();
    return false;
  }
 }
 else
 {
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unknown Detector Setup File Format!"), wxT("Invalid Format"), wxOK | wxICON_ERROR);
 dial->ShowModal();
 return false;
 }
}

bool DetectorFile::DetectorFileSave()
{
 if (DetectorFileVersion == wxT("epsd")) // Save in the native ERYA format
 {
  // Get the current time
  wxDateTime ThisTime = wxDateTime::Now();
  wxString ActualTime =ThisTime.Format(wxT("%Y-%m-%dT%H:%M:%S.00Z"),wxDateTime::WET);
  // An xml file when written, all node are declared backwarks, but any atribute of the same node should be declared forwards
  wxXmlDocument LocalDetector;
  wxXmlNode* detector = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Detector");
  LocalDetector.SetRoot(detector);
  wxXmlNode* data = new wxXmlNode(detector, wxXML_ELEMENT_NODE, "Detector_Data");
  wxXmlNode* block = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Energy_Efficiency");
  for(int i=0; i<ParsedParameters.GetDetectorEnergy().GetCount(); i++)
  {
   // Get the current values
   int CurrentValue = ParsedParameters.GetDetectorEnergy().GetCount()-i;
   wxString c0 = ParsedParameters.GetDetectorEnergy().Item(CurrentValue-1);
   wxString c1 = ParsedParameters.GetDetectorEfficiency().Item(CurrentValue-1);
   // Allocate the elements
   if (c0.Len()>0 && c1.Len()>0)
   {
    wxXmlNode* sigma = new wxXmlNode(block, wxXML_ELEMENT_NODE, "register");
    sigma->AddAttribute(wxT("n"),wxString::Format("%i",CurrentValue));
    sigma->AddAttribute(wxT("Energy"),c0);
    sigma->AddAttribute(wxT("Efficiency"),c1);
   }
  }
  // Store the custom function
  wxXmlNode *function = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Detector_Function");
   wxXmlNode *definition = new wxXmlNode(function, wxXML_ELEMENT_NODE, "macro");
    definition->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ParsedParameters.GetDetectorFunction()));
  // Save file header
  wxXmlNode* fileversion = new wxXmlNode(detector, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programremark = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Remark");
     programremark->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ParsedParameters.GetInfo()));
   wxXmlNode* programdatetime = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Date_File_Creation");
     programdatetime->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ActualTime));
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.80")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
 // Save the file
 return LocalDetector.Save(DetectorFileName,0);
 }
 else if (DetectorFileVersion == wxT("txt"))
 {
 wxTextFile file(DetectorFileName);
 file.Create();
 for(int i=0; i<ParsedParameters.GetDetectorEnergy().GetCount(); i++)
 {
  if (ParsedParameters.GetDetectorEnergy().Item(i).Len() > 0 && ParsedParameters.GetDetectorEfficiency().Item(i).Len() > 0 )
  {
   file.AddLine( ParsedParameters.GetDetectorEnergy().Item(i) + wxT("\t") + ParsedParameters.GetDetectorEfficiency().Item(i));
  }
 }
 file.Write();
 file.Close();
 return true;
 }
 else if (DetectorFileVersion == wxT("xlsx"))
 {
  TableMatrix DetectorMatrix(ParsedParameters.GetDetectorEnergy().GetCount(),2);
  DetectorMatrix.Add(TableNode(wxT("Energy (keV)"),0));
  DetectorMatrix.Add(TableNode(wxT("Absolute Efficiency"),0));
  for(int i=0; i<ParsedParameters.GetDetectorEnergy().GetCount(); i++)
  {
   if (ParsedParameters.GetDetectorEnergy().Item(i).Len() > 0 && ParsedParameters.GetDetectorEfficiency().Item(i).Len() > 0 )
   {
     DetectorMatrix.Add(TableNode(ParsedParameters.GetDetectorEnergy().Item(i),1));
     DetectorMatrix.Add(TableNode(ParsedParameters.GetDetectorEfficiency().Item(i),1));
   }
  }
  XlsxFile DetectorXlsxFile(DetectorFileName, DetectorMatrix, wxT("A1"));
  DetectorXlsxFile.WriteFile();
  return true;
 }
 else
 {
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Cannot save detector setup data in this format!"), wxT("Invalid Format"), wxOK | wxICON_ERROR);
 dial->ShowModal();
 return false;
 }
}

// Ziegler File main constructor
ZieglerFile::ZieglerFile(wxString ZieglerFilePath, wxString Version, ZieglerParameters CurrentParameters, ElementSRIMArray CurrentTables, int Argument)
{
 ZieglerFileName = ZieglerFilePath;
 ZieglerFileVersion = Version;
 ParsedParameters = CurrentParameters;
 ParsedTables = CurrentTables;
 TableMode = Argument; // If argument is zero, force Ziegler's Parameters, otherwise it will use the SRIM table corresponding to the Atomic Number
}

bool ZieglerFile::ZieglerFileLoad()
{
 if (ZieglerFileVersion == wxT("epsz")) // Load the ERYA's Ziegler native format.
 {
  ParsedParameters.Clear();
  ParsedTables.Clear();
  wxString FileProgram, FileVersion, FileDateTime, FileInfo;
  wxXmlDocument LocalZieglerFile;
  if(!(LocalZieglerFile.Load(ZieglerFileName)))
  {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + ZieglerFileName, wxT("Ziegler File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
  }
  if(LocalZieglerFile.GetRoot()->GetName() == wxT("ERYA-Bulk_Ziegler"))
  {
   wxMessageDialog *question = new wxMessageDialog(NULL, wxT("If you import a ERYA-Bulk Stopping-Power file to ERYA-Profiling,\nThe Ionization and Density are not defined, and fixed values will be inserted...\nImport Anyway ?"), wxT("Warning! Wrong Stopping-Power Version!"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
   if (question->ShowModal() == wxID_NO)
   {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + ZieglerFileName, wxT("Ziegler File Loading Error"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     return false;
   }
  }
  else if(LocalZieglerFile.GetRoot()->GetName() == wxT("ERYA-Profiling_Ziegler"))
  {
   int a=0;
  }
  else
  {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unexpected file format of ") + ZieglerFileName, wxT("Ziegler File Loading Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    return false;
  }
  wxXmlNode *ZieglerNode = LocalZieglerFile.GetRoot()->GetChildren();
  while(ZieglerNode)
  {
    if(ZieglerNode->GetName() == wxT("File_Details")) //Load header file
    {
      wxXmlNode *ZieglerFileInfo = ZieglerNode->GetChildren();
      if(ZieglerFileInfo->GetName() == wxT("Contents"))
      {
        wxXmlNode *ZieglerFileContents = ZieglerFileInfo->GetChildren();
        while(ZieglerFileContents)
        {
         if(ZieglerFileContents->GetName() == wxT("Program_Name"))
          {
            FileProgram = ZieglerFileContents->GetNodeContent();
          }
          if(ZieglerFileContents->GetName() == wxT("Program_Version"))
          {
            FileVersion = ZieglerFileContents->GetNodeContent();
          }
          if(ZieglerFileContents->GetName() == wxT("Date_File_Creation"))
          {
            FileDateTime = ZieglerFileContents->GetNodeContent();
          }
          if(ZieglerFileContents->GetName() == wxT("Remark"))
          {
            FileInfo = ZieglerFileContents->GetNodeContent();
            ParsedParameters.SetInfo(FileInfo);
          }
          ZieglerFileContents = ZieglerFileContents->GetNext();
        }
      }
    }
    if(ZieglerNode->GetName() == wxT("Ziegler_Data")) //Main data entry point
    {
     wxXmlNode *ZieglerData = ZieglerNode->GetChildren();
     while(ZieglerData)
     {
      if(ZieglerData->GetName() == wxT("Ziegler_Function")) //Set the custom function
      {
        wxString CustomFunction;
        wxXmlNode *ZieglerFunction = ZieglerData->GetChildren();
        if(ZieglerFunction->GetName() == wxT("macro"))
         {
           CustomFunction = ZieglerFunction->GetNodeContent();
         }
        ParsedParameters.SetZieglerFunction(CustomFunction);
      }
      if(ZieglerData->GetName() == wxT("Ziegler_Version")) //Set the version
      {
        wxString ActualZieglerVersion = ZieglerData->GetAttribute(wxT("zv"),wxT("0")); //Get the desired value
        ParsedParameters.SetZieglerVersion(ActualZieglerVersion);
      }
      if(ZieglerData->GetName() == wxT("Ziegler_Parameters")) //Get the table data
      {
        wxXmlNode *ZieglerElement = ZieglerData->GetChildren();
        while(ZieglerElement)
        {
          if(ZieglerElement->GetName() == wxT("Element_Number")) // Read one element array
          {
            wxString c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15;
            c14 = wxT("1");
            c15 = wxT("10");
            wxXmlNode *ZieglerElementData = ZieglerElement->GetChildren();
            while(ZieglerElementData)
            {
              if(ZieglerElementData->GetName() == wxT("Element_Name"))
              {
                wxXmlNode *ZieglerData0 = ZieglerElementData->GetChildren();
                if(ZieglerData0->GetName() == wxT("value"))
                {
                  c0 = ZieglerData0->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-1"))
              {
                wxXmlNode *ZieglerData1 = ZieglerElementData->GetChildren();
                if(ZieglerData1->GetName() == wxT("value"))
                {
                  c1 = ZieglerData1->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-2"))
              {
                wxXmlNode *ZieglerData2 = ZieglerElementData->GetChildren();
                if(ZieglerData2->GetName() == wxT("value"))
                {
                  c2 = ZieglerData2->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-3"))
              {
                wxXmlNode *ZieglerData3 = ZieglerElementData->GetChildren();
                if(ZieglerData3->GetName() == wxT("value"))
                {
                  c3 = ZieglerData3->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-4"))
              {
                wxXmlNode *ZieglerData4 = ZieglerElementData->GetChildren();
                if(ZieglerData4->GetName() == wxT("value"))
                {
                  c4 = ZieglerData4->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-5"))
              {
                wxXmlNode *ZieglerData5 = ZieglerElementData->GetChildren();
                if(ZieglerData5->GetName() == wxT("value"))
                {
                  c5 = ZieglerData5->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-6"))
              {
                wxXmlNode *ZieglerData6 = ZieglerElementData->GetChildren();
                if(ZieglerData6->GetName() == wxT("value"))
                {
                  c6 = ZieglerData6->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-7"))
              {
                wxXmlNode *ZieglerData7 = ZieglerElementData->GetChildren();
                if(ZieglerData7->GetName() == wxT("value"))
                {
                  c7 = ZieglerData7->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-8"))
              {
                wxXmlNode *ZieglerData8 = ZieglerElementData->GetChildren();
                if(ZieglerData8->GetName() == wxT("value"))
                {
                  c8 = ZieglerData8->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-9"))
              {
                wxXmlNode *ZieglerData9 = ZieglerElementData->GetChildren();
                if(ZieglerData9->GetName() == wxT("value"))
                {
                  c9 = ZieglerData9->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-10"))
              {
                wxXmlNode *ZieglerData10 = ZieglerElementData->GetChildren();
                if(ZieglerData10->GetName() == wxT("value"))
                {
                  c10 = ZieglerData10->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-11"))
              {
                wxXmlNode *ZieglerData11 = ZieglerElementData->GetChildren();
                if(ZieglerData11->GetName() == wxT("value"))
                {
                  c11 = ZieglerData11->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("A-12"))
              {
                wxXmlNode *ZieglerData12 = ZieglerElementData->GetChildren();
                if(ZieglerData12->GetName() == wxT("value"))
                {
                  c12 = ZieglerData12->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("Atomic_Mass"))
              {
                wxXmlNode *ZieglerData13 = ZieglerElementData->GetChildren();
                if(ZieglerData13->GetName() == wxT("value"))
                {
                  c13 = ZieglerData13->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("Atomic_Density"))
              {
                wxXmlNode *ZieglerData14 = ZieglerElementData->GetChildren();
                if(ZieglerData14->GetName() == wxT("value"))
                {
                  c14 = ZieglerData14->GetNodeContent();
                }
              }
              if(ZieglerElementData->GetName() == wxT("Bloch_Parameter"))
              {
                wxXmlNode *ZieglerData15 = ZieglerElementData->GetChildren();
                if(ZieglerData15->GetName() == wxT("value"))
                {
                  c15 = ZieglerData15->GetNodeContent();
                }
              }
              ZieglerElementData = ZieglerElementData->GetNext();
            }
           // Store the line
           ParsedParameters.AddZieglerParameterData(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15);
          }
          ZieglerElement = ZieglerElement->GetNext();
        }
      }
      if(ZieglerData->GetName() == wxT("Ziegler_SRIM_Tables")) //Get the top node of SRIM tables
      {
        wxXmlNode *SRIMElement = ZieglerData->GetChildren();
        while(SRIMElement)
        {
         if(SRIMElement->GetName() == wxT("Ziegler_SRIM_Element")) //Read the element contents
         {
           wxString AtomicNumber = SRIMElement->GetAttribute(wxT("atomic"),wxT("1"));
           wxArrayString SRIMEnergy, SRIMStoppingPower;
           wxXmlNode *SRIMData = SRIMElement->GetChildren();
           while(SRIMData)
           {
            if(SRIMData->GetName() == wxT("register")) // Read each pair of values from the vtable on stack
            {
            wxString ActualEnergy = SRIMData->GetAttribute(wxT("Energy"),wxT("0"));
            wxString ActualStoppingPower = SRIMData->GetAttribute(wxT("Stopping_Power"),wxT("0"));
            SRIMEnergy.Add(ActualEnergy);
            SRIMStoppingPower.Add(ActualStoppingPower);
            }
            SRIMData = SRIMData->GetNext();
           }
           long ZElement;
           int Z;
           if(AtomicNumber.ToLong(&ZElement))
            Z = static_cast<int>(ZElement);
           else
            Z = 1;
           ParsedTables.Replace(Z,SRIMEnergy,SRIMStoppingPower); //Store the complete element table on memory.
         }
         SRIMElement = SRIMElement->GetNext();
        }
      }
     ZieglerData = ZieglerData->GetNext();
     }
    }
   ZieglerNode = ZieglerNode->GetNext(); //Pass to next element
  }
  return true;
 }
 else if (ZieglerFileVersion == wxT("txt")) // Database files with such extension can be a genuine text file, or a LabView binary file
 {
  LabViewZiegler LabViewBinaryZiegler(ZieglerFileName);
  SRIMFile SRIMFileZiegler(ZieglerFileName);
  if(LabViewBinaryZiegler.IsLabViewFile()) // Use the LabView Binary Database Loader. First check the header file.
  {
    if(LabViewBinaryZiegler.IsLabViewZiegler()) // It is a compatible file ?
    {
     ParsedParameters.Clear();
     ParsedParameters = LabViewBinaryZiegler.GetZieglerParametersFromLabView();
     ParsedParameters.FixElementNames();
     return true;
    }
    else
    {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Fatal Error: Unexpected data structure!"), wxT("LabView Import Error"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     ParsedParameters.Clear();
     return false;
    }
  }
  else if(SRIMFileZiegler.IsSRIMFile()) // Check if the file is a SRIM file
  {
   if(SRIMFileZiegler.SRIMImport()) // Extract the data inside the SRIM file
   {
     wxArrayString DataElementEnergy = SRIMFileZiegler.GetEnergy();
     wxArrayString DataElementStoppingPower = SRIMFileZiegler.GetStoppingPower();
     int DataElementNumber = SRIMFileZiegler.GetAtomic();
     if(DataElementNumber == TableMode)
     {
       ParsedTables.Replace(DataElementNumber,DataElementEnergy,DataElementStoppingPower);
       return true;
     }
     else
     {
       wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("This SRIM file will overwrite the Stopping-Power of\n Element with Atomic Number ") + wxString::Format("%d",DataElementNumber) + wxT("\nWhile you have selected on SRIM spreadsheet the Element with Atomic Number ") + wxString::Format("%d", TableMode) , wxT("SRIM Import Warning. Replace anyway ?"), wxYES_NO | wxNO_DEFAULT | wxICON_WARNING);
       if (dial->ShowModal() == wxID_YES) // Replace anyway-
       {
        ParsedTables.Replace(DataElementNumber,DataElementEnergy,DataElementStoppingPower);
        return true;
       }
       else
       {
        return false;
       }
     }
   }
   else
   {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Fatal Error: Unexpected data structure!"), wxT("SRIM Import Error"), wxOK | wxICON_ERROR);
     dial->ShowModal();
     ParsedParameters.Clear();
     return false;
   }
  }
  else // It's a generic text file format
  {
   wxTextFile file(ZieglerFileName);
   file.Open();
   if (TableMode == 0)
    ParsedParameters.Clear();
   wxArrayString Energy, StoppingPower;
   for(int j=0; j<file.GetLineCount(); j++)
   {
    wxString CurrentLine = file.GetLine(j); // Get the current line
    TextLineParser CurrentLineData(CurrentLine, wxEmptyString); // Define the custom parser rules
    if(CurrentLineData.GetUnexcluded().GetCount() == 14 && TableMode == 0) // Ziegler Table
    {
     wxMessageDialog *question = new wxMessageDialog(NULL, wxT("If you import a ERYA-Bulk Stopping-Power file to ERYA-Profiling,\nThe Ionization and Density are not defined, and fixed values will be inserted...\nImport Anyway ?"), wxT("Warning! Wrong Stopping-Power Version!"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
     if (question->ShowModal() == wxID_NO)
     {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The user aborts the ASCII import of an ERYA-Bulk Stopping-Power table!"), wxT("ASCII Import Error"), wxOK | wxICON_ERROR);
      dial->ShowModal();
      ParsedParameters.Clear();
      return false;
     }
     // If the file is the legacy format, the program will treat the element symbol using the Z<n> format
     ParsedParameters.AddZieglerParameterData( wxT("Z") + CurrentLineData.GetUnexcluded().Item(0), CurrentLineData.GetUnexcluded().Item(1), CurrentLineData.GetUnexcluded().Item(2), CurrentLineData.GetUnexcluded().Item(3), CurrentLineData.GetUnexcluded().Item(4), CurrentLineData.GetUnexcluded().Item(5), CurrentLineData.GetUnexcluded().Item(6), CurrentLineData.GetUnexcluded().Item(7), CurrentLineData.GetUnexcluded().Item(8), CurrentLineData.GetUnexcluded().Item(9), CurrentLineData.GetUnexcluded().Item(10), CurrentLineData.GetUnexcluded().Item(11), CurrentLineData.GetUnexcluded().Item(12), CurrentLineData.GetUnexcluded().Item(13));
     // The difference of the two versions, is that the 1977 version require 12 parameters, and the 1991 only 8.
     double test1,test2,test3,test4;
     CurrentLineData.GetUnexcluded().Item(9).ToDouble(&test1);
     CurrentLineData.GetUnexcluded().Item(10).ToDouble(&test2);
     CurrentLineData.GetUnexcluded().Item(11).ToDouble(&test3);
     CurrentLineData.GetUnexcluded().Item(12).ToDouble(&test4);
     if (test1 < 1e-10 && test2 < 1e-10 && test3 < 1e-10 && test4 < 1e-10)
         ParsedParameters.SetZieglerVersion(wxT("1"));
     else
         ParsedParameters.SetZieglerVersion(wxT("0"));
    }
    else if(CurrentLineData.GetUnexcluded().GetCount() == 16 && TableMode == 0) // Ziegler Table
    {
     // If the file is the legacy format, the program will treat the element symbol using the Z<n> format
     ParsedParameters.AddZieglerParameterData( wxT("Z") + CurrentLineData.GetUnexcluded().Item(0), CurrentLineData.GetUnexcluded().Item(1), CurrentLineData.GetUnexcluded().Item(2), CurrentLineData.GetUnexcluded().Item(3), CurrentLineData.GetUnexcluded().Item(4), CurrentLineData.GetUnexcluded().Item(5), CurrentLineData.GetUnexcluded().Item(6), CurrentLineData.GetUnexcluded().Item(7), CurrentLineData.GetUnexcluded().Item(8), CurrentLineData.GetUnexcluded().Item(9), CurrentLineData.GetUnexcluded().Item(10), CurrentLineData.GetUnexcluded().Item(11), CurrentLineData.GetUnexcluded().Item(12), CurrentLineData.GetUnexcluded().Item(13), CurrentLineData.GetUnexcluded().Item(14), CurrentLineData.GetUnexcluded().Item(15));
     // The difference of the two versions, is that the 1977 version require 12 parameters, and the 1991 only 8.
     double test1,test2,test3,test4;
     CurrentLineData.GetUnexcluded().Item(9).ToDouble(&test1);
     CurrentLineData.GetUnexcluded().Item(10).ToDouble(&test2);
     CurrentLineData.GetUnexcluded().Item(11).ToDouble(&test3);
     CurrentLineData.GetUnexcluded().Item(12).ToDouble(&test4);
     if (test1 < 1e-10 && test2 < 1e-10 && test3 < 1e-10 && test4 < 1e-10)
         ParsedParameters.SetZieglerVersion(wxT("1"));
     else
         ParsedParameters.SetZieglerVersion(wxT("0"));
    }
    else if(CurrentLineData.GetUnexcluded().GetCount() == 2 && TableMode > 0) // A single SRIM Table
    {
      Energy.Add(CurrentLineData.GetUnexcluded().Item(0));
      StoppingPower.Add(CurrentLineData.GetUnexcluded().Item(1));
       ParsedParameters.SetZieglerVersion(wxT("3"));
    }
    else
    {
    wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Fatal Error: Invalid file format!"), wxT("Import Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    ParsedParameters.Clear();
    return false;
    }
   }
   file.Close();
   if (TableMode == 0)
    ParsedParameters.FixElementNames();
   else
    return ParsedTables.Replace(TableMode,Energy,StoppingPower);
   return true;
  }
 }
 else if (ZieglerFileVersion == wxT("xlsx")) //Load the table from an Excel Xlsx file format, which calls own methods
 {
  XlsxFile ZieglerXlsxFile(ZieglerFileName);
  if(ZieglerXlsxFile.LoadFile())
  {
   TableMatrix ZieglerMatrix = ZieglerXlsxFile.GetTableMatrix();
   int NumberElements,NumberValues;
   ZieglerMatrix.GetRealMatrixSize(NumberElements,NumberValues);
   if(NumberElements > 1 && NumberValues == 14 && TableMode == 0)
   {
     wxMessageDialog *question = new wxMessageDialog(NULL, wxT("If you import a ERYA-Bulk Stopping-Power file to ERYA-Profiling,\nThe Ionization and Density are not defined, and fixed values will be inserted...\nImport Anyway ?"), wxT("Warning! Wrong Stopping-Power Version!"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
     if (question->ShowModal() == wxID_NO)
     {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("The user aborts the Excel import of an ERYA-Bulk Stopping-Power table!"), wxT("Excel Import Error"), wxOK | wxICON_ERROR);
      dial->ShowModal();
      return false;
     }
     ParsedParameters.Clear();
     // Check if the entire line are numerical, except the first column.
     for(int i=0; i<NumberElements; i++)
     {
      int temp;
      double v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13;
      wxString c0 = ZieglerMatrix.GetTableMatrixValueAt(i,0,temp);
      wxString c1 = ZieglerMatrix.GetTableMatrixValueAt(i,1,temp);
      wxString c2 = ZieglerMatrix.GetTableMatrixValueAt(i,2,temp);
      wxString c3 = ZieglerMatrix.GetTableMatrixValueAt(i,3,temp);
      wxString c4 = ZieglerMatrix.GetTableMatrixValueAt(i,4,temp);
      wxString c5 = ZieglerMatrix.GetTableMatrixValueAt(i,5,temp);
      wxString c6 = ZieglerMatrix.GetTableMatrixValueAt(i,6,temp);
      wxString c7 = ZieglerMatrix.GetTableMatrixValueAt(i,7,temp);
      wxString c8 = ZieglerMatrix.GetTableMatrixValueAt(i,8,temp);
      wxString c9 = ZieglerMatrix.GetTableMatrixValueAt(i,9,temp);
      wxString c10 = ZieglerMatrix.GetTableMatrixValueAt(i,10,temp);
      wxString c11 = ZieglerMatrix.GetTableMatrixValueAt(i,11,temp);
      wxString c12 = ZieglerMatrix.GetTableMatrixValueAt(i,12,temp);
      wxString c13 = ZieglerMatrix.GetTableMatrixValueAt(i,13,temp);
      // Check the first column
      if(c0.ToDouble(&v0))
       c0 = wxT("Z") + c0;
      // Store the line
      if(c1.ToDouble(&v1) && c2.ToDouble(&v2) && c3.ToDouble(&v3) && c4.ToDouble(&v4) && c5.ToDouble(&v5) && c6.ToDouble(&v6) && c7.ToDouble(&v7) && c8.ToDouble(&v8) && c9.ToDouble(&v9) && c10.ToDouble(&v10) && c11.ToDouble(&v11) && c12.ToDouble(&v12) && c13.ToDouble(&v13))
       {
       ParsedParameters.AddZieglerParameterData(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13);
      // The difference of the two versions, is that the 1977 version require 12 parameters, and the 1991 only 8.
       double test1,test2,test3,test4;
       c9.ToDouble(&test1);
       c10.ToDouble(&test2);
       c11.ToDouble(&test3);
       c12.ToDouble(&test4);
       if (test1 < 1e-10 && test2 < 1e-10 && test3 < 1e-10 && test4 < 1e-10)
         ParsedParameters.SetZieglerVersion(wxT("1"));
       else
         ParsedParameters.SetZieglerVersion(wxT("0"));
       }
     }
    ParsedParameters.FixElementNames();
    return true;
   }
   else if(NumberElements > 1 && NumberValues == 16 && TableMode == 0)
   {
     ParsedParameters.Clear();
     // Check if the entire line are numerical, except the first column.
     for(int i=0; i<NumberElements; i++)
     {
      int temp;
      double v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15;
      wxString c0 = ZieglerMatrix.GetTableMatrixValueAt(i,0,temp);
      wxString c1 = ZieglerMatrix.GetTableMatrixValueAt(i,1,temp);
      wxString c2 = ZieglerMatrix.GetTableMatrixValueAt(i,2,temp);
      wxString c3 = ZieglerMatrix.GetTableMatrixValueAt(i,3,temp);
      wxString c4 = ZieglerMatrix.GetTableMatrixValueAt(i,4,temp);
      wxString c5 = ZieglerMatrix.GetTableMatrixValueAt(i,5,temp);
      wxString c6 = ZieglerMatrix.GetTableMatrixValueAt(i,6,temp);
      wxString c7 = ZieglerMatrix.GetTableMatrixValueAt(i,7,temp);
      wxString c8 = ZieglerMatrix.GetTableMatrixValueAt(i,8,temp);
      wxString c9 = ZieglerMatrix.GetTableMatrixValueAt(i,9,temp);
      wxString c10 = ZieglerMatrix.GetTableMatrixValueAt(i,10,temp);
      wxString c11 = ZieglerMatrix.GetTableMatrixValueAt(i,11,temp);
      wxString c12 = ZieglerMatrix.GetTableMatrixValueAt(i,12,temp);
      wxString c13 = ZieglerMatrix.GetTableMatrixValueAt(i,13,temp);
      wxString c14 = ZieglerMatrix.GetTableMatrixValueAt(i,14,temp);
      wxString c15 = ZieglerMatrix.GetTableMatrixValueAt(i,15,temp);
      // Check the first column
      if(c0.ToDouble(&v0))
       c0 = wxT("Z") + c0;
      // Store the line
      if(c1.ToDouble(&v1) && c2.ToDouble(&v2) && c3.ToDouble(&v3) && c4.ToDouble(&v4) && c5.ToDouble(&v5) && c6.ToDouble(&v6) && c7.ToDouble(&v7) && c8.ToDouble(&v8) && c9.ToDouble(&v9) && c10.ToDouble(&v10) && c11.ToDouble(&v11) && c12.ToDouble(&v12) && c13.ToDouble(&v13) && c14.ToDouble(&v14) && c15.ToDouble(&v15))
       {
       ParsedParameters.AddZieglerParameterData(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15);
      // The difference of the two versions, is that the 1977 version require 12 parameters, and the 1991 only 8.
       double test1,test2,test3,test4;
       c9.ToDouble(&test1);
       c10.ToDouble(&test2);
       c11.ToDouble(&test3);
       c12.ToDouble(&test4);
       if (test1 < 1e-10 && test2 < 1e-10 && test3 < 1e-10 && test4 < 1e-10)
         ParsedParameters.SetZieglerVersion(wxT("1"));
       else
         ParsedParameters.SetZieglerVersion(wxT("0"));
       }
     }
    ParsedParameters.FixElementNames();
    return true;
   }
   else if (NumberElements > 1 && NumberValues == 2 && TableMode > 0)
   {
    wxArrayString Energy, StoppingPower;
    for(int i=0; i<NumberElements; i++)
     {
      int temp;
      double v0,v1;
      wxString c0 = ZieglerMatrix.GetTableMatrixValueAt(i,0,temp);
      wxString c1 = ZieglerMatrix.GetTableMatrixValueAt(i,1,temp);
      // Check if the two values are numeric terms, otherwise are discarded.
      if(c0.ToDouble(&v0) && c1.ToDouble(&v1))
       {
         Energy.Add(c0);
         StoppingPower.Add(c1);
       }
     }
    return ParsedTables.Replace(TableMode,Energy,StoppingPower);
   }
   else
   {
     wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Expected a table with 2(SRIM),\n14(ERYA-Bulk)\nor 16(ERYA-Profiling) columns."), wxT("Excel Import Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    ParsedParameters.Clear();
    return false;
   }
  }
  else
  {
   wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Fatal Error: Invalid file format!"), wxT("Import Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
    ParsedParameters.Clear();
    return false;
  }
 }
 else
 {
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Cannot load Ziegler Parameters file in this format!"), wxT("Invalid Format"), wxOK | wxICON_ERROR);
 dial->ShowModal();
 return false;
 }
}

// Implement the Ziegler Parameters saving as a file in native epsz format, and legacy txt format
bool ZieglerFile::ZieglerFileSave()
{
 if (ZieglerFileVersion == wxT("epsz")) // Save on native ERYA-Bulk format, which is a plain xml file
 {
  // Get the current time
  wxDateTime ThisTime = wxDateTime::Now();
  wxString ActualTime =ThisTime.Format(wxT("%Y-%m-%dT%H:%M:%S.00Z"),wxDateTime::WET);
  // An xml file when written, all node are declared backwarks, but any atribute of the same node should be declared forwards
  wxXmlDocument LocalZiegler;
  wxXmlNode* ziegler = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "ERYA-Profiling_Ziegler");
  LocalZiegler.SetRoot(ziegler);
  wxXmlNode* data = new wxXmlNode(ziegler, wxXML_ELEMENT_NODE, "Ziegler_Data");
  wxXmlNode* tables = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ziegler_SRIM_Tables");
  for(int k=0; k<ParsedTables.GetCount(); k++)
  {
   // Set the table backwards.
   int CurrentAtomic = ParsedTables.GetCount()-k;
   int AtomicNumber = ParsedTables.Item(CurrentAtomic-1).GetElementAtomic();
   wxXmlNode* tableSRIM = new wxXmlNode(tables, wxXML_ELEMENT_NODE, "Ziegler_SRIM_Element");
    tableSRIM->AddAttribute(wxT("number"),wxString::Format("%i",CurrentAtomic));
    tableSRIM->AddAttribute(wxT("atomic"),wxString::Format("%i",AtomicNumber));
    for(int m=0; m<ParsedTables.Item(CurrentAtomic-1).GetElementEnergy().GetCount(); m++)
   {
   // Get the current values
   int CurrentValue = ParsedTables.Item(CurrentAtomic-1).GetElementEnergy().GetCount()-m;
   wxString c0 = ParsedTables.Item(CurrentAtomic-1).GetElementEnergy().Item(CurrentValue-1);
   wxString c1 = ParsedTables.Item(CurrentAtomic-1).GetElementStoppingPower().Item(CurrentValue-1);
   // Allocate the elements
   if (c0.Len()>0 && c1.Len()>0)
   {
    wxXmlNode* sigma = new wxXmlNode(tableSRIM, wxXML_ELEMENT_NODE, "register");
    sigma->AddAttribute(wxT("n"),wxString::Format("%i",CurrentValue));
    sigma->AddAttribute(wxT("Energy"),c0);
    sigma->AddAttribute(wxT("Stopping_Power"),c1);
   }
  }
  }
  wxXmlNode* parameters = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ziegler_Parameters");
  for(int i=0; i<ParsedParameters.GetZieglerElements().GetCount(); i++)
  {
   // Get the current values
   int CurrentElement = ParsedParameters.GetZieglerElements().GetCount()-i;
   wxString c0 = ParsedParameters.GetZieglerElements().Item(CurrentElement-1);
   wxString c1 = ParsedParameters.GetZieglerValues1().Item(CurrentElement-1);
   wxString c2 = ParsedParameters.GetZieglerValues2().Item(CurrentElement-1);
   wxString c3 = ParsedParameters.GetZieglerValues3().Item(CurrentElement-1);
   wxString c4 = ParsedParameters.GetZieglerValues4().Item(CurrentElement-1);
   wxString c5 = ParsedParameters.GetZieglerValues5().Item(CurrentElement-1);
   wxString c6 = ParsedParameters.GetZieglerValues6().Item(CurrentElement-1);
   wxString c7 = ParsedParameters.GetZieglerValues7().Item(CurrentElement-1);
   wxString c8 = ParsedParameters.GetZieglerValues8().Item(CurrentElement-1);
   wxString c9 = ParsedParameters.GetZieglerValues9().Item(CurrentElement-1);
   wxString c10 = ParsedParameters.GetZieglerValues10().Item(CurrentElement-1);
   wxString c11 = ParsedParameters.GetZieglerValues11().Item(CurrentElement-1);
   wxString c12 = ParsedParameters.GetZieglerValues12().Item(CurrentElement-1);
   wxString c13 = ParsedParameters.GetZieglerMass().Item(CurrentElement-1);
   wxString c14 = ParsedParameters.GetZieglerDensity().Item(CurrentElement-1);
   wxString c15 = ParsedParameters.GetZieglerBloch().Item(CurrentElement-1);
   // Allocate the elements
   if (c0.Len()>0 && c1.Len()>0 && c2.Len()>0 && c3.Len()>0 && c4.Len()>0 && c5.Len()>0 && c6.Len()>0 && c7.Len()>0 && c8.Len()>0 && c9.Len()>0 && c10.Len()>0 && c11.Len()>0 && c12.Len()>0 && c13.Len()>0 && c14.Len()>0 && c15.Len()>0)
   {
   wxXmlNode* parameternumber = new wxXmlNode(parameters, wxXML_ELEMENT_NODE, "Element_Number");
   parameternumber->AddAttribute(wxT("number"),wxString::Format("%i",CurrentElement));
   wxXmlNode* datac15 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "Bloch_Parameter");
     wxXmlNode* datac15value = new wxXmlNode(datac15, wxXML_ELEMENT_NODE, "value");
       datac15value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c15));
   wxXmlNode* datac14 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "Atomic_Density");
     wxXmlNode* datac14value = new wxXmlNode(datac14, wxXML_ELEMENT_NODE, "value");
       datac14value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c14));
    wxXmlNode* datac13 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "Atomic_Mass");
     wxXmlNode* datac13value = new wxXmlNode(datac13, wxXML_ELEMENT_NODE, "value");
       datac13value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c13));
    wxXmlNode* datac12 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-12");
     wxXmlNode* datac12value = new wxXmlNode(datac12, wxXML_ELEMENT_NODE, "value");
       datac12value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c12));
    wxXmlNode* datac11 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-11");
     wxXmlNode* datac11value = new wxXmlNode(datac11, wxXML_ELEMENT_NODE, "value");
       datac11value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c11));
    wxXmlNode* datac10 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-10");
     wxXmlNode* datac10value = new wxXmlNode(datac10, wxXML_ELEMENT_NODE, "value");
       datac10value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c10));
    wxXmlNode* datac9 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-9");
     wxXmlNode* datac9value = new wxXmlNode(datac9, wxXML_ELEMENT_NODE, "value");
       datac9value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c9));
    wxXmlNode* datac8 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-8");
     wxXmlNode* datac8value = new wxXmlNode(datac8, wxXML_ELEMENT_NODE, "value");
       datac8value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c8));
    wxXmlNode* datac7 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-7");
     wxXmlNode* datac7value = new wxXmlNode(datac7, wxXML_ELEMENT_NODE, "value");
       datac7value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c7));
    wxXmlNode* datac6 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-6");
     wxXmlNode* datac6value = new wxXmlNode(datac6, wxXML_ELEMENT_NODE, "value");
       datac6value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c6));
    wxXmlNode* datac5 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-5");
     wxXmlNode* datac5value = new wxXmlNode(datac5, wxXML_ELEMENT_NODE, "value");
       datac5value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c5));
    wxXmlNode* datac4 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-4");
     wxXmlNode* datac4value = new wxXmlNode(datac4, wxXML_ELEMENT_NODE, "value");
       datac4value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c4));
    wxXmlNode* datac3 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-3");
     wxXmlNode* datac3value = new wxXmlNode(datac3, wxXML_ELEMENT_NODE, "value");
       datac3value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c3));
    wxXmlNode* datac2 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-2");
     wxXmlNode* datac2value = new wxXmlNode(datac2, wxXML_ELEMENT_NODE, "value");
       datac2value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c2));
    wxXmlNode* datac1 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "A-1");
     wxXmlNode* datac1value = new wxXmlNode(datac1, wxXML_ELEMENT_NODE, "value");
       datac1value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c1));
    wxXmlNode* datac0 = new wxXmlNode(parameternumber, wxXML_ELEMENT_NODE, "Element_Name");
     wxXmlNode* datac0value = new wxXmlNode(datac0, wxXML_ELEMENT_NODE, "value");
       datac0value->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, c0));
   }
  }
   // Store the custom function
  wxXmlNode *dfunction = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ziegler_Function");
   wxXmlNode *definition = new wxXmlNode(dfunction, wxXML_ELEMENT_NODE, "macro");
    definition->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ParsedParameters.GetZieglerFunction()));
 // Store file headers and versions-
  wxXmlNode* version = new wxXmlNode(data, wxXML_ELEMENT_NODE, "Ziegler_Version");
   version->AddAttribute(wxT("zv"),ParsedParameters.GetZieglerVersion());
  wxXmlNode* fileversion = new wxXmlNode(ziegler, wxXML_ELEMENT_NODE, "File_Details");
   wxXmlNode* details = new wxXmlNode(fileversion, wxXML_ELEMENT_NODE, "Contents");
   wxXmlNode* programremark = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Remark");
     programremark->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ParsedParameters.GetInfo()));
   wxXmlNode* programdatetime = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Date_File_Creation");
     programdatetime->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, ActualTime));
   wxXmlNode* programversion = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Version");
     programversion->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("2.80")));
    wxXmlNode* programname = new wxXmlNode(details, wxXML_ELEMENT_NODE, "Program_Name");
     programname->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxEmptyString, wxT("ERYA-Profiling")));
 // Save the file
 return LocalZiegler.Save(ZieglerFileName,0);
 }
 else if (ZieglerFileVersion == wxT("txt")) // Save on ASCII Source format, i.e., a standard text file
 {
  wxTextFile file(ZieglerFileName);
  file.Create();
  if(TableMode == 0)
  {
  for(int j=0; j<ParsedParameters.GetZieglerElements().GetCount(); j++)
  {
   wxString c0 = wxString::Format("%i", j + 1);
   wxString c1 = ParsedParameters.GetZieglerValues1().Item(j);
   wxString c2 = ParsedParameters.GetZieglerValues2().Item(j);
   wxString c3 = ParsedParameters.GetZieglerValues3().Item(j);
   wxString c4 = ParsedParameters.GetZieglerValues4().Item(j);
   wxString c5 = ParsedParameters.GetZieglerValues5().Item(j);
   wxString c6 = ParsedParameters.GetZieglerValues6().Item(j);
   wxString c7 = ParsedParameters.GetZieglerValues7().Item(j);
   wxString c8 = ParsedParameters.GetZieglerValues8().Item(j);
   wxString c9 = ParsedParameters.GetZieglerValues9().Item(j);
   wxString c10 = ParsedParameters.GetZieglerValues10().Item(j);
   wxString c11 = ParsedParameters.GetZieglerValues11().Item(j);
   wxString c12 = ParsedParameters.GetZieglerValues12().Item(j);
   wxString c13 = ParsedParameters.GetZieglerMass().Item(j);
   wxString c14 = ParsedParameters.GetZieglerDensity().Item(j);
   wxString c15 = ParsedParameters.GetZieglerBloch().Item(j);
   if (c0.Len()>0 && c1.Len()>0 && c2.Len()>0 && c3.Len()>0 && c4.Len()>0 && c5.Len()>0 && c6.Len()>0 && c7.Len()>0 && c8.Len()>0 && c9.Len()>0 && c10.Len()>0 && c11.Len()>0 && c12.Len()>0 && c13.Len()>0 && c14.Len()>0 && c15.Len()>0)
  file.AddLine( c0 + wxT("\t") + c1 + wxT("\t") + c2 + wxT("\t") + c3 + wxT("\t") + c4 + wxT("\t") + c5 + wxT("\t") + c6 + wxT("\t") + c7 + wxT("\t") + c8 + wxT("\t") + c9 + wxT("\t") + c10 + wxT("\t") + c11 + wxT("\t") + c12 + wxT("\t") + c13 + wxT("\t") + c14 + wxT("\t") + c15);
  }
  }
  else
  {
   int CurrentAdress = ParsedTables.GetElementAdress(TableMode);
   for(int j=0; j<ParsedTables.Item(CurrentAdress).GetElementEnergy().GetCount(); j++)
   {
   wxString c0 = ParsedTables.Item(CurrentAdress).GetElementEnergy().Item(j);
   wxString c1 = ParsedTables.Item(CurrentAdress).GetElementStoppingPower().Item(j);
   if (c0.Len()>0 && c1.Len()>0)
   file.AddLine( c0 + wxT("\t") + c1 );
   }
  }
 file.Write();
 file.Close();
 return true;
 }
 else if (ZieglerFileVersion == wxT("xlsx")) //Save as an Excel Xlsx file format, which calls own methods
 {
  //First transform the Ziegler array in to a TableMatrix data block
  if(TableMode == 0)
  {
  TableMatrix ZieglerMatrix(ParsedParameters.GetZieglerElements().GetCount(),16);
  ZieglerMatrix.Add(TableNode(wxT("Element Name"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-1"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-2"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-3"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-4"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-5"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-6"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-7"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-8"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-9"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-10"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-11"),0));
  ZieglerMatrix.Add(TableNode(wxT("A-12"),0));
  ZieglerMatrix.Add(TableNode(wxT("Atomic Mass"),0));
  ZieglerMatrix.Add(TableNode(wxT("Atomic Density"),0));
  ZieglerMatrix.Add(TableNode(wxT("Bloch Parameter"),0));
  for(int j=0; j<ParsedParameters.GetZieglerElements().GetCount(); j++)
  {
   wxString c0 = ParsedParameters.GetZieglerElements().Item(j);
   wxString c1 = ParsedParameters.GetZieglerValues1().Item(j);
   wxString c2 = ParsedParameters.GetZieglerValues2().Item(j);
   wxString c3 = ParsedParameters.GetZieglerValues3().Item(j);
   wxString c4 = ParsedParameters.GetZieglerValues4().Item(j);
   wxString c5 = ParsedParameters.GetZieglerValues5().Item(j);
   wxString c6 = ParsedParameters.GetZieglerValues6().Item(j);
   wxString c7 = ParsedParameters.GetZieglerValues7().Item(j);
   wxString c8 = ParsedParameters.GetZieglerValues8().Item(j);
   wxString c9 = ParsedParameters.GetZieglerValues9().Item(j);
   wxString c10 = ParsedParameters.GetZieglerValues10().Item(j);
   wxString c11 = ParsedParameters.GetZieglerValues11().Item(j);
   wxString c12 = ParsedParameters.GetZieglerValues12().Item(j);
   wxString c13 = ParsedParameters.GetZieglerMass().Item(j);
   wxString c14 = ParsedParameters.GetZieglerDensity().Item(j);
   wxString c15 = ParsedParameters.GetZieglerBloch().Item(j);
    if (c0.Len()>0 && c1.Len()>0 && c2.Len()>0 && c3.Len()>0 && c4.Len()>0 && c5.Len()>0 && c6.Len()>0 && c7.Len()>0 && c8.Len()>0 && c9.Len()>0 && c10.Len()>0 && c11.Len()>0 && c12.Len()>0 && c13.Len()>0 && c14.Len()>0 && c15.Len()>0)
    {
         ZieglerMatrix.Add(TableNode(c0,0));
         ZieglerMatrix.Add(TableNode(c1,1));
         ZieglerMatrix.Add(TableNode(c2,1));
         ZieglerMatrix.Add(TableNode(c3,1));
         ZieglerMatrix.Add(TableNode(c4,1));
         ZieglerMatrix.Add(TableNode(c5,1));
         ZieglerMatrix.Add(TableNode(c6,1));
         ZieglerMatrix.Add(TableNode(c7,1));
         ZieglerMatrix.Add(TableNode(c8,1));
         ZieglerMatrix.Add(TableNode(c9,1));
         ZieglerMatrix.Add(TableNode(c10,1));
         ZieglerMatrix.Add(TableNode(c11,1));
         ZieglerMatrix.Add(TableNode(c12,1));
         ZieglerMatrix.Add(TableNode(c13,1));
         ZieglerMatrix.Add(TableNode(c14,1));
         ZieglerMatrix.Add(TableNode(c15,1));
    }
  }
  //Finally, save the content as a Xlsx file
  XlsxFile ZieglerXlsxFile(ZieglerFileName, ZieglerMatrix, wxT("A1"));
  ZieglerXlsxFile.WriteFile();
  return true;
  }
  else
  {
  TableMatrix ZieglerMatrix(ParsedParameters.GetZieglerElements().GetCount(),2);
  ZieglerMatrix.Add(TableNode(wxT("Energy"),0));
  ZieglerMatrix.Add(TableNode(wxT("Stopping Power"),0));
  int CurrentAdress = ParsedTables.GetElementAdress(TableMode);
  for(int j=0; j<ParsedTables.Item(CurrentAdress).GetElementEnergy().GetCount(); j++)
  {
   wxString c0 = ParsedTables.Item(CurrentAdress).GetElementEnergy().Item(j);
   wxString c1 = ParsedTables.Item(CurrentAdress).GetElementStoppingPower().Item(j);
    if (c0.Len()>0 && c1.Len()>0)
    {
         ZieglerMatrix.Add(TableNode(c0,1));
         ZieglerMatrix.Add(TableNode(c1,1));
    }
  }
  //Finally, save the content as a Xlsx file
  XlsxFile ZieglerXlsxFile(ZieglerFileName, ZieglerMatrix, wxT("A1"));
  ZieglerXlsxFile.WriteFile();
  return true;
  }
 }
 else
 {
 wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Cannot save Ziegler Parameters file in this format!"), wxT("Invalid Format"), wxOK | wxICON_ERROR);
 dial->ShowModal();
 return false;
 }
}

