/***************************************************************
 * Name:      ERYAProfilingdialogR33DataImport.cpp
 * Purpose:   ERYA ITN/R33 Text Data Import Tool functions
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2017-01-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

 #include "ERYAProfilingdialogR33DataImport.h"
 #include "ERYAProfilingdialogAddDatabase.h"

ERYAProfilingdialogR33DataImport::ERYAProfilingdialogR33DataImport( wxWindow* parent)
:
dialogR33DataImport( parent )
{

}

void ERYAProfilingdialogR33DataImport::OnDataImportValidate( wxCommandEvent& event )
{
 ERYAProfilingdialogAddDatabase *Parent = (ERYAProfilingdialogAddDatabase *) GetParent();
 Parent->SetSelectUnit(radioDataImportUnits->GetSelection());
 Parent->SetSelectAngle(radioDataImportAngle->GetSelection());
 Parent->SetIgnoreInvalidLine(checkIgnoreNonNumericalData->GetValue());
 Close();
}

void ERYAProfilingdialogR33DataImport::OnDataImportAbort( wxCommandEvent& event )
{
 ERYAProfilingdialogAddDatabase *Parent = (ERYAProfilingdialogAddDatabase *) GetParent();
 Parent->SetSelectUnit(0);
 Parent->SetSelectAngle(0);
 Parent->SetIgnoreInvalidLine(false);
 Close();
}

void ERYAProfilingdialogR33DataImport::OnDataImportReset( wxCommandEvent& event )
{
 radioDataImportUnits->SetSelection(0);
 radioDataImportAngle->SetSelection(0);
 checkIgnoreNonNumericalData->SetValue(true);
}

void ERYAProfilingdialogR33DataImport::OnDataImportHelp( wxCommandEvent& event )
{
 radioDataImportUnits->SetSelection(0);
 radioDataImportAngle->SetSelection(0);
 checkIgnoreNonNumericalData->SetValue(true);
 Close();
}
