/***************************************************************
 * Name:      ERYAProfilingdialogDetectorSetup.h
 * Purpose:   ERYA Detector Setup implementation classes
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2015-12-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#ifndef __ERYAProfilingdialogDetectorSetup__
#define __ERYAProfilingdialogDetectorSetup__

/**
@file
Subclass of dialogDetectorSetup, which is generated by wxFormBuilder.
*/

#include "ERYAProfiling.h"
#include "ParserLibrary.h"
#include "FileLibrary.h"
#include "DatabaseLibrary.h"

//// end generated include

/** Implementing dialogDetectorSetup */
class ERYAProfilingdialogDetectorSetup : public dialogDetectorSetup
{
	private:
	    wxString infoRemark;
	protected:
		// Handlers for dialogDetectorSetup events.
		void OnEficiencySelect( wxGridRangeSelectEvent& event );
        void OnEficiencyCopy( wxCommandEvent& event );
		void OnEficiencyPaste( wxCommandEvent& event );
		void OnEficiencyLoad( wxCommandEvent& event );
		void OnEficiencySave( wxCommandEvent& event );
		void OnEficiencyClear( wxCommandEvent& event );
		void OnEficiencyOK( wxCommandEvent& event );
		void OnEficiencyCancel( wxCommandEvent& event );
		void OnEficiencyHelp( wxCommandEvent& event );
	public:
		/** Constructor */
		ERYAProfilingdialogDetectorSetup( wxWindow* parent );
		void SetRemark(wxString &info){infoRemark = info; return;};
	//// end generated class members



};

#endif // __ERYAProfilingdialogDetectorSetup__
