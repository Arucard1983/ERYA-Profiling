/***************************************************************
 * Name:      ERYAProfilingdialogXlsxDataImport.h
 * Purpose:   ERYA Xlsx Data Import Tool implementation classes
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2017-01-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#ifndef ERYAPROFILINGDIALOGXLSXDATAIMPORT_H_INCLUDED
#define ERYAPROFILINGDIALOGXLSXDATAIMPORT_H_INCLUDED

/**
@file
Subclass of dialogXlsxDataImport, which is generated by wxFormBuilder.
*/

#include "ERYAProfiling.h"
//// end generated include

/** Implementing dialogXlsxDataImport */
class ERYAProfilingdialogXlsxDataImport : public dialogXlsxDataImport
{
	protected:
		// Handlers for dialogAddDatabase events.
	void OnDataImportValidate( wxCommandEvent& event );
    void OnDataImportAbort( wxCommandEvent& event );
    void OnDataImportReset( wxCommandEvent& event );
    void OnDataImportHelp( wxCommandEvent& event );
	public:
		/** Constructor */
		ERYAProfilingdialogXlsxDataImport( wxWindow* parent);

	//// end generated class members




};

#endif // ERYAPROFILINGDIALOGXLSXDATAIMPORT_H_INCLUDED
