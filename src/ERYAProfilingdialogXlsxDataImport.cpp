/***************************************************************
 * Name:      ERYAProfilingdialogXlsxDataImport.cpp
 * Purpose:   ERYA Xlsx Data Import Tool functions
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2017-01-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

 #include "ERYAProfilingdialogXlsxDataImport.h"
 #include "ERYAProfilingdialogAddDatabase.h"

ERYAProfilingdialogXlsxDataImport::ERYAProfilingdialogXlsxDataImport( wxWindow* parent)
:
dialogXlsxDataImport( parent )
{

}

void ERYAProfilingdialogXlsxDataImport::OnDataImportValidate( wxCommandEvent& event )
{
 ERYAProfilingdialogAddDatabase *Parent = (ERYAProfilingdialogAddDatabase *) GetParent();
 Parent->SetSelectUnit(radioDataImportUnits->GetSelection());
 Parent->SetSelectAngle(radioDataImportAngle->GetSelection());
 Parent->SetSelectMode(radioDataImportColumn->GetSelection());
 Close();
}

void ERYAProfilingdialogXlsxDataImport::OnDataImportAbort( wxCommandEvent& event )
{
 ERYAProfilingdialogAddDatabase *Parent = (ERYAProfilingdialogAddDatabase *) GetParent();
 Parent->SetSelectUnit(0);
 Parent->SetSelectAngle(0);
 Parent->SetSelectMode(0);
 Close();
}

void ERYAProfilingdialogXlsxDataImport::OnDataImportReset( wxCommandEvent& event )
{
 radioDataImportUnits->SetSelection(0);
 radioDataImportAngle->SetSelection(0);
 radioDataImportColumn->SetSelection(0);
}

void ERYAProfilingdialogXlsxDataImport::OnDataImportHelp( wxCommandEvent& event )
{
 radioDataImportUnits->SetSelection(0);
 radioDataImportAngle->SetSelection(0);
 radioDataImportColumn->SetSelection(0);
 Close();
}
