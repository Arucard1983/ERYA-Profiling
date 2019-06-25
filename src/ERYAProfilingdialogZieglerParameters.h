/***************************************************************
 * Name:      ERYAProfilingdialogZieglerParameters.h
 * Purpose:   ERYA Ziegler Bragg parameters class
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2015-12-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#ifndef __ERYAProfilingdialogZieglerParameters__
#define __ERYAProfilingdialogZieglerParameters__

/**
@file
Subclass of dialogZieglerParameters, which is generated by wxFormBuilder.
*/

#include "ERYAProfiling.h"
#include "FileLibrary.h"
#include "ParserLibrary.h"
#include "DatabaseLibrary.h"

//// end generated include

/** Implementing dialogZieglerParameters */
class ERYAProfilingdialogZieglerParameters : public dialogZieglerParameters
{
	private:
	    wxString infoRemark;
	protected:
		// Handlers for dialogZieglerParameters events.
        void OnZieglerSelectElement( wxSpinEvent& event );
		void OnZieglerSelectElementText( wxCommandEvent& event );
		void OnZieglerSelectElementEnter( wxCommandEvent& event );
		void OnUpdateZieglerSRIM( wxCommandEvent& event );
		void OnEraseZieglerSRIM( wxCommandEvent& event );
        void OnZieglerVersion( wxCommandEvent& event );
		void OnZieglerSelect( wxGridRangeSelectEvent& event );
        void OnZieglerCopy( wxCommandEvent& event );
		void OnZieglerPaste( wxCommandEvent& event );
		void OnZieglerLoad( wxCommandEvent& event );
		void OnZieglerSave( wxCommandEvent& event );
		void OnZieglerClear( wxCommandEvent& event );
		void OnZieglerOK( wxCommandEvent& event );
		void OnZieglerCancel( wxCommandEvent& event );
		void OnZieglerHelp( wxCommandEvent& event );
	private:
        ElementSRIMArray LocalSRIMTable;
	public:
		/** Constructor */
		ERYAProfilingdialogZieglerParameters( wxWindow* parent );
		void SetRemark(wxString &info){infoRemark = info; return;};
	//// end generated class members


};

#endif // __ERYAProfilingdialogZieglerParameters__
