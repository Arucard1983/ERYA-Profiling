///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 29 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ERYAPROFILING_H__
#define __ERYAPROFILING_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/html/htmlwin.h>
#include <wx/xml/xml.h>
#include <wx/textfile.h>
#include <wx/filesys.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/fs_zip.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <wx/stdpaths.h>
#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/statbox.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/radiobox.h>
#include <wx/statbmp.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/wizard.h>
#include <wx/dynarray.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/clipbrd.h>
#include <wx/busyinfo.h>
#include <wx/progdlg.h>
#include <wx/numdlg.h>
#include "mathplot.h"
#include "eryaprofiling.xpm"
#include "eryaprofilingwizard.xpm"
#include <cmath>
#include <limits>
#include <random>
WX_DEFINE_ARRAY_PTR( wxWizardPageSimple*, WizardPages );
WX_DECLARE_OBJARRAY( wxChoice*, ArrayElement);
WX_DECLARE_OBJARRAY( wxChoice*, ArrayGammaPeak);
WX_DECLARE_OBJARRAY( wxTextCtrl*, ArrayAtomicNumber);
WX_DECLARE_OBJARRAY( wxTextCtrl*, ArrayAbundance);
WX_DECLARE_OBJARRAY( wxTextCtrl*, ArrayIsotopicMass);
WX_DECLARE_OBJARRAY( wxTextCtrl*, ArrayAtomicMass);
WX_DECLARE_OBJARRAY( wxTextCtrl*, ArrayCalibrationFactor);


///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ERYAProfilingMain
///////////////////////////////////////////////////////////////////////////////
class ERYAProfilingMain : public wxFrame
{
	private:

	protected:
        wxArrayString choiceElementNameChoices;
        wxArrayString choiceGammaPeakChoices;
		wxStatusBar* statusERYAProfiling;
		wxMenuBar* menuERYAProfilingMain;
		wxMenu* menuERYAFile;
		wxMenu* menuERYADatabase;
		wxMenu* menuERYASetup;
		wxMenu* menuERYATool;
		wxMenu* menuERYAHelp;
		wxBoxSizer* sizerERYAProfilingMain;
		wxNotebook* tabERYAProfilingMain;
		wxPanel* tabElements;
		wxBoxSizer* sizerElements;
		wxStaticText* labelElementInfo;
		wxStaticText* labelNumberElements;
		wxSpinCtrl* spinNumberElements;
		wxButton* buttonElementClear;
		wxButton* buttonElementLoad;
		wxButton* buttonElementSave;
		wxButton* buttonElementHelp;
		wxStaticLine* lineElementsTools;
		wxFlexGridSizer* sizerElementEditor;
		wxScrolledWindow* scrollElementTable;
		wxStaticText* labelElementName;
		wxStaticText* labelGammaPeak;
		wxStaticText* labelAtomicNumber;
		wxStaticText* labelAbundance;
		wxStaticText* labelIsotopicMass;
		wxStaticText* labelAtomicMass;
		wxStaticText* labelCalibrationFactor;
		ArrayElement choiceElementName;
		ArrayGammaPeak choiceGammaPeak;
		ArrayAtomicNumber textAtomicNumber;
		ArrayAbundance textAbundance;
		ArrayIsotopicMass textIsotopicMass;
		ArrayAtomicMass textAtomicMass;
		ArrayCalibrationFactor textCalibrationFactor;
		wxPanel* tabLayers;
		wxStaticText* labelLayersInfo;
		wxStaticText* labelNumberLayers;
		wxSpinCtrl* spinNumberLayers;
		wxButton* buttonLayerClear;
		wxButton* buttonLayerLoad;
		wxButton* buttonLayerSave;
		wxButton* buttonLayerHelp;
		wxStaticLine* lineLayersTools;
		wxGrid* gridLayerEditor;
		wxPanel* tabDetector;
		wxStaticText* labelDetectorInfo;
		wxButton* buttonDetectorClear;
		wxButton* buttonDetectorReset;
		wxButton* buttonDetectorFunction;
		wxButton* buttonDetectorLoad;
		wxButton* buttonDetectorSave;
		wxButton* buttonDetectorHelp;
		wxStaticLine* lineDetectorTools;
		wxStaticText* labelBeamResolution;
		wxStaticText* labelTemperature;
		wxStaticText* labelCharge;
		wxStaticText* labelEnergyStep;
		wxStaticText* labelMinimumEnergy;
		wxStaticText* labelMaximumEnergy;
		wxTextCtrl* textBeamEnergy;
		wxTextCtrl* textTemperature;
		wxTextCtrl* textCharge;
		wxTextCtrl* textEnergyStep;
		wxTextCtrl* textMinimumEnergy;
		wxTextCtrl* textMaximumEnergy;
		wxStaticText* labelRessonanceWidth;
		wxTextCtrl* textRessonanceWidth;
		wxStaticText* labelRessonancePeak;
		wxTextCtrl* textRessonancePeak;
		wxStaticText* labelRessonanceEnergy;
		wxTextCtrl* textRessonanceEnergy;
		wxCheckBox* checkRessonanceRange;
		wxStaticText* labelRessonanceMinimum;
		wxTextCtrl* textRessonanceMinimum;
		wxStaticText* labelRessonanceMaximum;
		wxTextCtrl* textRessonanceMaximum;
		wxStaticText* labelRessonanceWidth1;
		wxTextCtrl* textRessonanceWidth1;
		wxStaticText* labelRessonancePeak1;
		wxTextCtrl* textRessonancePeak1;
		wxStaticText* labelRessonanceEnergy1;
		wxTextCtrl* textRessonanceEnergy1;
		wxCheckBox* checkRessonanceRange1;
		wxStaticText* labelRessonanceMinimum1;
		wxTextCtrl* textRessonanceMinimum1;
		wxStaticText* labelRessonanceMaximum1;
		wxTextCtrl* textRessonanceMaximum1;
		wxStaticText* labelMainCustomInfo;
		wxTextCtrl* textCustomRessonance;
		wxRadioBox* radioRessonanceOption;
		wxPanel* tabOutput;
		wxStaticText* labelOutputMain;
		wxButton* buttonOutputDataImport;
		wxButton* buttonOutputImageSave;
		wxButton* buttonOutputHelp;
		wxStaticLine* lineOutputTools;
		mpWindow* renderOutputData;
                wxPanel* tabTable;
		wxStaticText* labelTabOutputMain;
		wxButton* buttonTableDataImport;
		wxButton* buttonTableDataSave;
		wxButton* buttonTableHelp;
		wxStaticLine* lineTabTools;
		wxGrid* gridTableData;
		wxPanel* panelLog;
		wxStaticText* labelLogOutputMain;
		wxButton* buttonLogDistributionViewer;
                wxButton* buttonLogDataSave;
		wxButton* buttonLogHelp;
		wxStaticLine* lineLogTools;
		wxGrid* gridLogData;
		wxStaticLine* lineERYAMain;
		wxButton* buttonMainNew;
		wxButton* buttonMainAdvanced;
		wxButton* buttonMainRun;
		wxButton* buttonMainSave;
		wxButton* buttonMainLog;
		wxButton* buttonMainHelp;

		// Virtual event handlers, overide them in your derived class
		virtual void OnFileNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseDetector( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseElements( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseZiegler( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupDefault( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSRIMImport( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLabViewImport( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCalculator( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelpManual( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelpAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNumberElementSpin( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnNumberElementEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnElementClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnElementLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnElementSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnElementHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnElementNameChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGammaPeakChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNumberLayerSpin( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnNumberLayerEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDetectorClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDetectorReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDetectorFunction( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDetectorLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDetectorSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDetectorHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRessonanceRange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRessonanceRange1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRessonanceOption( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOutputData( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOutputImage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOutputHelp( wxCommandEvent& event ) { event.Skip(); }
                virtual void OnImportData( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableHelp( wxCommandEvent& event ) { event.Skip(); }
                virtual void OnLogViewer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLogSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLogHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMainNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMainAdvanced( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMainRun( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMainSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMainCheck( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMainHelp( wxCommandEvent& event ) { event.Skip(); }


	public:

		ERYAProfilingMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA Profiling - Emission Radiation Yield Analysis"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1920,1080 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~ERYAProfilingMain();

       static wxString GetAppVersion(){static int MajorVersion = 3; static int MinorVersion = 1; return wxString::Format("%i",MajorVersion) + wxString::Format(".%i",MinorVersion);}

};


///////////////////////////////////////////////////////////////////////////////
/// Class dialogDatabaseManager
///////////////////////////////////////////////////////////////////////////////
class dialogDatabaseManager : public wxDialog
{
	private:

	protected:
		wxStaticText* labelElementName;
		wxStaticText* labelGammaPeak;
		wxStaticText* labelAtomicNumber;
		wxStaticText* labelAbundance;
		wxStaticText* labelAtomicMass;
		wxStaticText* labelIsotopicMass;
		wxChoice* choiceElementName;
		wxChoice* choiceGammaPeak;
		wxTextCtrl* textAtomicNumber;
		wxTextCtrl* textAbundance;
		wxTextCtrl* textAtomicMass;
		wxTextCtrl* textIsotopicMass;
		wxStaticLine* separatorDisplay;
		wxGrid* tableElementViewer;
		mpWindow* renderElementViewer;
		wxStaticLine* separatorButtons;
		wxButton* buttonAdd;
		wxButton* buttonEdit;
		wxButton* buttonRemove;
		wxButton* buttonClear;
		wxButton* buttonLoad;
		wxButton* buttonSave;
		wxButton* buttonCancel;
		wxButton* buttonHelp;
		wxArrayString choiceElementNameChoices;
		wxArrayString choiceGammaPeakChoices;
        wxString MainDatabaseFile;

		// Virtual event handlers, overide them in your derived class
		virtual void OnElementName( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGammaPeak( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabaseHelp( wxCommandEvent& event ) { event.Skip(); }



	public:
		dialogDatabaseManager( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA - Database Manager"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1280, 720 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogDatabaseManager();

};

///////////////////////////////////////////////////////////////////////////////
/// Class dialogAddDatabase
///////////////////////////////////////////////////////////////////////////////
class dialogAddDatabase : public wxDialog
{
	private:

	protected:
		wxStaticText* labelEditElement;
		wxStaticText* labelEditGamma;
		wxStaticText* labelEditNumber;
		wxStaticText* labelEditAbundance;
		wxStaticText* labelEditAtomic;
		wxStaticText* labelEditIsotopic;
		wxTextCtrl* textEditElement;
		wxTextCtrl* textEditGamma;
		wxTextCtrl* textEditNumber;
		wxTextCtrl* textEditAbundance;
		wxTextCtrl* textEditAtomic;
		wxTextCtrl* textEditIsotopic;
		wxStaticLine* separatorEditor;
		wxGrid* tableDataEditor;
		wxStaticLine* separatorTable;
		wxButton* buttonImportR33;
		wxButton* buttonExportR33;
		wxButton* buttonEditCopy;
		wxButton* buttonEditPaste;
		wxButton* buttonEditClear;
		wxButton* buttonEditSave;
		wxButton* buttonEditCancel;
		wxButton* buttonEditHelp;
		wxString* dataClipboard;

		// Virtual event handlers, overide them in your derived class
		virtual void OnDatabaseSelect( wxGridRangeSelectEvent& event ) { event.Skip(); }
		virtual void OnDatabaseCopy( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDatabasePaste( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnImportR33( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExportR33( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditHelp( wxCommandEvent& event ) { event.Skip(); }


	public:
		dialogAddDatabase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA - Add Element to Database"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1200, 720 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogAddDatabase();

};


///////////////////////////////////////////////////////////////////////////////
/// Class dialogDetectorSetup
///////////////////////////////////////////////////////////////////////////////
class dialogDetectorSetup : public wxDialog
{
	private:

	protected:
		wxStaticText* labelFunctionEficiency;
		wxTextCtrl* textFunctionEficiency;
		wxStaticLine* separatorFunctionEficiency;
		wxStaticText* labelConstantsEficiency;
		wxGrid* tableConstantEficiency;
		wxStaticLine* separatorButtonEficiency;
		wxButton* buttonEficiencyLoad;
		wxButton* buttonEficiencySave;
        wxButton* buttonEficiencyCopy;
		wxButton* buttonEficiencyPaste;
		wxButton* buttonEficiencyClear;
		wxButton* buttonEficiencyOK;
		wxButton* buttonEficiencyCancel;
		wxButton* buttonEficiencyHelp;
        wxString* dataClipboard;

		// Virtual event handlers, overide them in your derived class
		virtual void OnEficiencySelect( wxGridRangeSelectEvent& event ) { event.Skip(); }
        virtual void OnEficiencyCopy( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEficiencyPaste( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEficiencyLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEficiencySave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEficiencyClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEficiencyOK( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEficiencyCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEficiencyHelp( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogDetectorSetup( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA - Detector Eficiency"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1200, 720 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogDetectorSetup();

};

///////////////////////////////////////////////////////////////////////////////
/// Class dialogZieglerParameters
///////////////////////////////////////////////////////////////////////////////
class dialogZieglerParameters : public wxDialog
{
	private:

	protected:
		wxStaticText* labelZieglerParameters;
		wxStaticLine* lineZieglerVersion;
		wxStaticText* labelZieglerVersion;
		wxChoice* choiceZieglerVersion;
		wxStaticLine* lineZieglerTables;
		wxStaticText* labelZieglerFunction;
		wxTextCtrl* textZieglerFunction;
		wxNotebook* tabZieglerTables;
		wxPanel* tabZieglerEquations;
		wxGrid* tableZieglerParameters;
		wxPanel* tabZieglerSRIM;
		wxStaticText* labelZieglerSRIMCurrentElement;
		wxSpinCtrl* spinZieglerSRIMCurrentElement;
		wxButton* buttonZieglerSRIMUpdate;
		wxButton* buttonZieglerSRIMEraseAllData;
		wxGrid* tableZieglerSRIM;
		wxStaticLine* lineZieglerParameters;
		wxButton* buttonZieglerLoad;
		wxButton* buttonZieglerSave;
		wxButton* buttonZieglerCopy;
		wxButton* buttonZieglerPaste;
		wxButton* buttonZieglerClear;
		wxButton* buttonZieglerOK;
		wxButton* buttonZieglerCancel;
		wxButton* buttonZieglerHelp;
        wxString* dataClipboard;

		// Virtual event handlers, overide them in your derived class
		virtual void OnZieglerSelectElement( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnZieglerSelectElementText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerSelectElementEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateZieglerSRIM( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEraseZieglerSRIM( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnZieglerVersion( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerSelect( wxGridRangeSelectEvent& event ) { event.Skip(); }
		virtual void OnZieglerLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerCopy( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerPaste( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerOK( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZieglerHelp( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogZieglerParameters( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA - Stopping Power"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1280,720 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogZieglerParameters();

};



///////////////////////////////////////////////////////////////////////////////
/// Class dialogERYACalculator
///////////////////////////////////////////////////////////////////////////////
class dialogERYACalculator : public wxDialog
{
	private:

	protected:
		wxStaticText* labelCalculatorInput;
		wxTextCtrl* textCalculatorInput;
		wxStaticLine* lineCalculatorInput;
		wxStaticText* labelCalculatorOutput;
		wxTextCtrl* textCalculatorOutput;
		wxStaticLine* lineCalculatorOutput;
		wxButton* buttonAcos;
		wxButton* buttonAsin;
		wxButton* buttonAtan;
		wxButton* buttonFxvar;
		wxButton* buttonLeftParenthesis;
		wxButton* buttonRightParanthesis;
		wxButton* buttonSqrt;
		wxButton* buttonPower;
		wxButton* buttonLess;
		wxButton* buttonHelp;
		wxButton* buttonClearInput;
		wxButton* buttonAsinh;
		wxButton* buttonAcosh;
		wxButton* buttonAtanh;
		wxButton* buttonFyvar;
		wxButton* buttonSeven;
		wxButton* buttonEight;
		wxButton* buttonNine;
		wxButton* buttonPlus;
		wxButton* buttonMore;
		wxButton* buttonBackSpace;
		wxButton* buttonClearOutput;
		wxButton* buttonCos;
		wxButton* buttonSin;
		wxButton* buttonTan;
		wxButton* buttonFxmin;
		wxButton* buttonFour;
		wxButton* buttonFive;
		wxButton* buttonSix;
		wxButton* buttonMinus;
		wxButton* buttonComma;
		wxButton* buttonDisplayProgram;
		wxButton* buttonCosh;
		wxButton* buttonSinh;
		wxButton* buttonTanh;
		wxButton* buttonFxmax;
		wxButton* buttonOne;
		wxButton* buttonTwo;
		wxButton* buttonThree;
		wxButton* buttonTimes;
		wxButton* buttonColon;
		wxButton* buttonDisplayAnswer;
		wxButton* buttonInputVariable;
		wxButton* buttonVectorMacro;
		wxButton* buttonSetDecimals;
		wxButton* buttonExp;
		wxButton* buttonLog;
		wxButton* buttonLn;
		wxButton* buttonFunctionVar;
		wxButton* buttonZero;
		wxButton* buttonDecimal;
		wxButton* buttonExponential;
		wxButton* buttonDivide;
		wxButton* buttonAssign;
		wxButton* buttonReturn;

		// Virtual event handlers, overide them in your derived class
		virtual void OnAcos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAsin( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAtan( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFxvar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeftParenthesis( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRightParenthesis( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSqrt( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPower( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearInput( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAsinh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAcosh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAtanh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFyvar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSeven( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEight( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNine( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBackSpace( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearOutput( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSin( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTan( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFxmin( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFour( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFive( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSix( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMinus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnComma( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisplayProgram( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCosh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSinh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTanh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFxmax( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOne( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTwo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnThree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnColon( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisplayAnswer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLog( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFunctionVar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZero( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDecimal( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExponential( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDivide( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAssign( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLess( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMore( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVectorMacro( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetDecimals( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInputVariable( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReturn( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogERYACalculator( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA Simple Calculator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,640 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogERYACalculator();

};

///////////////////////////////////////////////////////////////////////////////
/// Class wizardLabViewImport
///////////////////////////////////////////////////////////////////////////////
class wizardLabViewImport : public wxWizard
{
	private:

	protected:
		wxStaticText* labelLabView1;
		wxStaticText* labelLabView2;
		wxFilePickerCtrl* fileLabViewDatabases;
		wxStaticText* labelLabView3;
		wxFilePickerCtrl* fileLabViewZiegler;
		wxStaticText* labelLabView4;
		wxFilePickerCtrl* fileLabViewDetector;
		wxStaticText* labelLabView5;
		wxFilePickerCtrl* fileLabViewDensity;
		wxStaticText* labelLabView6;
		wxFilePickerCtrl* fileLabViewBloch;
		wxStaticText* labelLabView7;
		wxFilePickerCtrl* fileERYADatabase;
		wxStaticText* labelLabView8;
		wxFilePickerCtrl* fileERYADetector;
		wxStaticText* labelLabView9;
		wxFilePickerCtrl* fileERYAZiegler;
		wxStaticText* labelLabView10;

		wxWizardPage* GetFirstPage(){return m_pages.Item(0);}; //required hack

		// Virtual event handlers, overide them in your derived class
		virtual void OnLabViewImportCancel( wxWizardEvent& event ) { event.Skip(); }
		virtual void OnLabViewImportFinish( wxWizardEvent& event ) { event.Skip(); }


	public:

		wizardLabViewImport( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LabView ERYA Databases Converter"), const wxBitmap& bitmap = wxBitmap(eryaprofilingwizard_xpm), const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		WizardPages m_pages;
		bool StartWizard(){return this->RunWizard(this->GetFirstPage());}; //Create a nice function to simplify the wizard loading
		~wizardLabViewImport();

};

///////////////////////////////////////////////////////////////////////////////
/// Class wizardFirstRun
///////////////////////////////////////////////////////////////////////////////
class wizardFirstRun : public wxWizard
{
	private:

	protected:
		wxStaticText* labelFirstRun1;
		wxStaticText* labelFirstRun2;
		wxFilePickerCtrl* fileDetectorFirstRun;
		wxStaticText* labelFirstRun3;
		wxFilePickerCtrl* fileElementsFirstRun;
		wxStaticText* labelFirstRun4;
		wxFilePickerCtrl* fileZieglerFirstRun;
		wxStaticText* labelFirstRun5;
		wxRadioBox* radioSetupDefault;
		wxStaticText* labelFirstRun6;

        wxWizardPage* GetFirstPage(){return m_pages.Item(0);}; //required hack

		// Virtual event handlers, overide them in your derived class
		virtual void OnFirstRunCancel( wxWizardEvent& event ) { event.Skip(); }
		virtual void OnFirstRunFinish( wxWizardEvent& event ) { event.Skip(); }

	public:

		wizardFirstRun( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA Profiling Setup Wizard"), const wxBitmap& bitmap = wxBitmap(eryaprofilingwizard_xpm), const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		WizardPages m_pages;
        bool StartWizard(){return this->RunWizard(this->GetFirstPage());}; //Create a nice function to simplify the wizard loading
		~wizardFirstRun();

};

///////////////////////////////////////////////////////////////////////////////
/// Class wizardSRIMImport
///////////////////////////////////////////////////////////////////////////////
class wizardSRIMImport : public wxWizard
{
	private:

	protected:
		wxStaticText* labelSRIMImport1;
		wxStaticText* labelSRIMImport2;
		wxListBox* listSRIMSourceFiles;
		wxButton* buttonSRIMLoad;
		wxButton* buttonSRIMRemove;
		wxButton* buttonSRIMClear;
		wxStaticText* labelSRIMImport3;
		wxRadioBox* radioZieglerParameters;
		wxStaticText* labelZieglerSource;
		wxFilePickerCtrl* fileZieglerSource;
		wxStaticText* labelSRIMImport4;
		wxFilePickerCtrl* fileZieglerOutput;
		wxStaticText* labelSRIMImport5;

		wxWizardPage* GetFirstPage(){return m_pages.Item(0);}; //required hack

		// Virtual event handlers, overide them in your derived class
		virtual void OnSRIMImportCancel( wxWizardEvent& event ) { event.Skip(); }
		virtual void OnSRIMImportComplete( wxWizardEvent& event ) { event.Skip(); }
		virtual void OnSRIMSourceSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSRIMSourceLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSRIMSourceRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSRIMSourceClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnableZieglerFiles( wxCommandEvent& event ) { event.Skip(); }


	public:

		wizardSRIMImport( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA Profiling - SRIM Stopping Power Import Wizard"), const wxBitmap& bitmap = wxBitmap(eryaprofilingwizard_xpm), const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		WizardPages m_pages;
		bool StartWizard(){return this->RunWizard(this->GetFirstPage());}; //Create a nice function to simplify the wizard loading
		~wizardSRIMImport();

};


///////////////////////////////////////////////////////////////////////////////
/// Class dialogSetup
///////////////////////////////////////////////////////////////////////////////
class dialogSetup : public wxDialog
{
	private:

	protected:
		wxStaticText* lineDefaultButtons;
		wxStaticText* labelSetupTip;
		wxRadioBox* radioDefaultConfig;
		wxStaticLine* lineDefaultFiles;
		wxStaticText* labelFilesInfo;
		wxStaticText* labelDefaultDetector;
		wxFilePickerCtrl* fileDefaultDetector;
		wxStaticText* labelDefaultDatabase;
		wxFilePickerCtrl* fileDefaultDatabase;
		wxStaticText* labelDefaultZiegler;
		wxFilePickerCtrl* fileDefaultZiegler;
		wxStaticLine* lineSetupButton;
		wxButton* buttonDefaultSave;
		wxButton* buttonDefaultReset;
		wxButton* buttonDefaultDelete;
		wxButton* buttonDefaultQuit;
		wxButton* buttonDefaultHelp;

		// Virtual event handlers, overide them in your derived class
		virtual void OnDefaultSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDefaultReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDefaultDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDefaultQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDefaultHelp( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogSetup( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Default Databases"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,480 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogSetup();

};

///////////////////////////////////////////////////////////////////////////////
/// Class dialogR33DataImport
///////////////////////////////////////////////////////////////////////////////
class dialogR33DataImport : public wxDialog
{
	private:

	protected:
		wxStaticText* labelDataImportInfo;
		wxStaticLine* lineDataImportInfo;
		wxStaticText* labelDataImportUnits;
		wxRadioBox* radioDataImportUnits;
		wxRadioBox* radioDataImportAngle;
		wxCheckBox* checkIgnoreNonNumericalData;
		wxStaticLine* lineDataImportButtons;
		wxButton* buttonR33DataOK;
		wxButton* buttonR33DataCancel;
		wxButton* buttonR33DataReset;
		wxButton* buttonR33DataHelp;

		// Virtual event handlers, overide them in your derived class
		virtual void OnDataImportValidate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDataImportAbort( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDataImportReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDataImportHelp( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogR33DataImport( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Additional Data Import Options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,360 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~dialogR33DataImport();

};

///////////////////////////////////////////////////////////////////////////////
/// Class dialogXlsxDataImport
///////////////////////////////////////////////////////////////////////////////
class dialogXlsxDataImport : public wxDialog
{
	private:

	protected:
		wxStaticText* labelDataImportInfo;
		wxStaticLine* lineDataImportInfo;
		wxStaticText* labelDataImportUnits;
		wxRadioBox* radioDataImportUnits;
		wxRadioBox* radioDataImportAngle;
		wxRadioBox* radioDataImportColumn;
		wxStaticLine* lineDataImportButtons;
		wxButton* buttonXlsxDataOK;
		wxButton* buttonXlsxDataCancel;
		wxButton* buttonXlsxDataReset;
		wxButton* buttonXlsxDataHelp;

		// Virtual event handlers, overide them in your derived class
		virtual void OnDataImportValidate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDataImportAbort( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDataImportReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDataImportHelp( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogXlsxDataImport( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Additional Excel File Data Import Options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,450 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~dialogXlsxDataImport();

};

///////////////////////////////////////////////////////////////////////////////
/// Class dialogERYAProfilingAdvanced
///////////////////////////////////////////////////////////////////////////////
class dialogERYAProfilingAdvanced : public wxDialog
{
	private:

	protected:
		wxStaticText* labelERYAProfilingAdvanced;
		wxStaticLine* lineERYAProfilingSettings;
		wxStaticText* labelSampleStep;
		wxSpinCtrl* spinSampleStep;
		wxStaticText* labelGaussPrecision;
		wxSpinCtrl* spinGaussPrecision;
		wxStaticText* labelVavilovMoyal;
		wxSpinCtrl* spinVavilovMoyal;
		wxStaticText* labelVavilovEdgeworth;
		wxSpinCtrl* spinVavilovEdgeworth;
		wxStaticText* labelVavilovAiry;
		wxSpinCtrl* spinVavilovAiry;
		wxStaticText* labelLandau;
		wxSpinCtrl* spinLandau;
		wxStaticText* labelConvolution;
		wxSpinCtrl* spinConvolution;
        wxStaticText* labelNumberThreads;
		wxChoice* spinNumberThreads;
		wxStaticText* labelActiveLog;
		wxCheckBox* checkActiveLog;
		wxStaticLine* lineERYAProfilingTools;
		wxButton* buttonAdvancedOK;
		wxButton* buttonAdvancedDefault;
		wxButton* buttonAdvancedCancel;
		wxButton* buttonAdvancedHelp;

		// Virtual event handlers, overide them in your derived class
		virtual void OnAdvancedOK( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAdvancedDefault( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAdvancedCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAdvancedHelp( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogERYAProfilingAdvanced( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA Profiling Advanced Precision Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 900,700 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogERYAProfilingAdvanced();

};

///////////////////////////////////////////////////////////////////////////////
/// Class dialogRemark
///////////////////////////////////////////////////////////////////////////////
class dialogRemark : public wxDialog
{
	private:

	protected:
		wxTextCtrl* textRemark;
		wxButton* buttonSave;
		wxButton* buttonClear;
		wxButton* buttonQuit;

		// Virtual event handlers, overide them in your derived class
		virtual void OnRemarkSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemarkClear( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemarkQuit( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogRemark( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Database Remark Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 650,480 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dialogRemark();

};

///////////////////////////////////////////////////////////////////////////////
/// Class dialogERYAProfilingViewer
///////////////////////////////////////////////////////////////////////////////
class dialogERYAProfilingViewer : public wxDialog
{
	private:

	protected:
		mpWindow* renderViewer;
		wxStaticText* labelViewerInitial;
		wxTextCtrl* dataViewerInitial;
		wxStaticText* labelViewerEnergy;
		wxTextCtrl* dataViewerEnergy;
		wxStaticText* labelViewerK;
		wxTextCtrl* dataViewerK;
		wxStaticLine* lineViewer;
		wxButton* buttonViewerPrevious;
		wxButton* buttonViewerNext;
		wxButton* buttonViewerLayerMinus;
		wxButton* buttonViewerLayerPlus;
		wxButton* buttonViewerScreenshot;
		wxButton* buttonViewerQuit;

		// Virtual event handlers, overide them in your derived class
		virtual void OnEnergyPrevious( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnergyNext( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerMinus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerPlus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTakeScreenshoot( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewerQuit( wxCommandEvent& event ) { event.Skip(); }


	public:

		dialogERYAProfilingViewer( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ERYA Profiling Stragging Distribution Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1280,720 ), long style = wxDEFAULT_DIALOG_STYLE );
		~dialogERYAProfilingViewer();

};



#endif //__ERYAPROFILING_H__
