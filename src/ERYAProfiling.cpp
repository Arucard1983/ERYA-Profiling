///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 29 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ERYAProfiling.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY( ArrayElement);
WX_DEFINE_OBJARRAY( ArrayGammaPeak);
WX_DEFINE_OBJARRAY( ArrayAtomicNumber);
WX_DEFINE_OBJARRAY( ArrayAbundance);
WX_DEFINE_OBJARRAY( ArrayIsotopicMass);
WX_DEFINE_OBJARRAY( ArrayAtomicMass);
///////////////////////////////////////////////////////////////////////////

ERYAProfilingMain::ERYAProfilingMain( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	statusERYAProfiling = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	menuERYAProfilingMain = new wxMenuBar( 0 );
	menuERYAFile = new wxMenu();
	wxMenuItem* menuERYAFileNew;
	menuERYAFileNew = new wxMenuItem( menuERYAFile, wxID_ANY, wxString( wxT("New") ) , wxT("Clears all opened data, and starts a new one"), wxITEM_NORMAL );
	menuERYAFile->Append( menuERYAFileNew );

	wxMenuItem* menuERYAFileOpen;
	menuERYAFileOpen = new wxMenuItem( menuERYAFile, wxID_ANY, wxString( wxT("Open") ) , wxT("Opens a ERYA compatible file"), wxITEM_NORMAL );
	menuERYAFile->Append( menuERYAFileOpen );

	wxMenuItem* menuERYAFileSave;
	menuERYAFileSave = new wxMenuItem( menuERYAFile, wxID_ANY, wxString( wxT("Save") ) , wxT("Saves the current results as the ERYA native file format"), wxITEM_NORMAL );
	menuERYAFile->Append( menuERYAFileSave );

	wxMenuItem* menuERYAFileSaveAs;
	menuERYAFileSaveAs = new wxMenuItem( menuERYAFile, wxID_ANY, wxString( wxT("Save As") ) , wxT("Save the current results as other file formats"), wxITEM_NORMAL );
	menuERYAFile->Append( menuERYAFileSaveAs );

	menuERYAFile->AppendSeparator();

	wxMenuItem* menuERYAFileQuit;
	menuERYAFileQuit = new wxMenuItem( menuERYAFile, wxID_ANY, wxString( wxT("Quit") ) , wxT("Close the program"), wxITEM_NORMAL );
	menuERYAFile->Append( menuERYAFileQuit );

	menuERYAProfilingMain->Append( menuERYAFile, wxT("File") );

	menuERYADatabase = new wxMenu();
	wxMenuItem* menuERYADatabaseDetector;
	menuERYADatabaseDetector = new wxMenuItem( menuERYADatabase, wxID_ANY, wxString( wxT("Detector Efficiency") ) , wxT("Changes the Detector Efficiency Profile"), wxITEM_NORMAL );
	menuERYADatabase->Append( menuERYADatabaseDetector );

	wxMenuItem* menuERYADatabaseElements;
	menuERYADatabaseElements = new wxMenuItem( menuERYADatabase, wxID_ANY, wxString( wxT("Elements Database") ) , wxT("Opens the Database Manager for Elements"), wxITEM_NORMAL );
	menuERYADatabase->Append( menuERYADatabaseElements );

	wxMenuItem* menuERYADatabaseZiegler;
	menuERYADatabaseZiegler = new wxMenuItem( menuERYADatabase, wxID_ANY, wxString( wxT("Stopping Power") ) , wxT("Opens the Stopping Powers Editor"), wxITEM_NORMAL );
	menuERYADatabase->Append( menuERYADatabaseZiegler );

	menuERYAProfilingMain->Append( menuERYADatabase, wxT("Databases") );

	menuERYASetup = new wxMenu();
	wxMenuItem* menuERYASetupDefault;
	menuERYASetupDefault = new wxMenuItem( menuERYASetup, wxID_ANY, wxString( wxT("Program Settings") ) , wxT("Change the Program Settings"), wxITEM_NORMAL );
	menuERYASetup->Append( menuERYASetupDefault );

	wxMenuItem* menuERYASetupReset;
	menuERYASetupReset = new wxMenuItem( menuERYASetup, wxID_ANY, wxString( wxT("Reset Settings") ) , wxT("Revert the program to initial settings"), wxITEM_NORMAL );
	menuERYASetup->Append( menuERYASetupReset );

	menuERYAProfilingMain->Append( menuERYASetup, wxT("Settings") );

	menuERYATool = new wxMenu();

	wxMenuItem* menuERYAToolCalculator;
	menuERYAToolCalculator = new wxMenuItem( menuERYATool, wxID_ANY, wxString( wxT("Simple Calculator") ) , wxT("Import ERYA Bulk Databases"), wxITEM_NORMAL );
	menuERYATool->Append( menuERYAToolCalculator );

	wxMenuItem* menuERYAToolLabView;
	menuERYAToolLabView = new wxMenuItem( menuERYATool, wxID_ANY, wxString( wxT("Import ERYA LabView") ) , wxT("Import ERYA LabView Databases"), wxITEM_NORMAL );
	menuERYATool->Append( menuERYAToolLabView );

	wxMenuItem* menuERYAToolSRIM;
	menuERYAToolSRIM = new wxMenuItem( menuERYATool, wxID_ANY, wxString( wxT("Import SRIM Tables") ) ,  wxT("Import SRIM Stopping Power Tables"), wxITEM_NORMAL );
	menuERYATool->Append( menuERYAToolSRIM );


	menuERYAProfilingMain->Append( menuERYATool, wxT("Tools") );

	menuERYAHelp = new wxMenu();
	wxMenuItem* menuERYAHelpManual;
	menuERYAHelpManual = new wxMenuItem( menuERYAHelp, wxID_ANY, wxString( wxT("User Guide Manual") ) , wxT("Open the User Manual"), wxITEM_NORMAL );
	menuERYAHelp->Append( menuERYAHelpManual );

	wxMenuItem* menuERYAHelpAbout;
	menuERYAHelpAbout = new wxMenuItem( menuERYAHelp, wxID_ANY, wxString( wxT("About ERYA Profiling") ) , wxT("Display program version"), wxITEM_NORMAL );
	menuERYAHelp->Append( menuERYAHelpAbout );

	menuERYAProfilingMain->Append( menuERYAHelp, wxT("Help") );

	this->SetMenuBar( menuERYAProfilingMain );

	sizerERYAProfilingMain = new wxBoxSizer( wxVERTICAL );

	tabERYAProfilingMain = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	tabElements = new wxPanel( tabERYAProfilingMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sizerElements = new wxBoxSizer( wxVERTICAL );

	labelElementInfo = new wxStaticText( tabElements, wxID_ANY, wxT("All Elements and their Gamma Peaks present on the Layers are managed here. Custom modifications on each elements will affect the results derived from the layers composition."), wxDefaultPosition, wxDefaultSize, 0 );
	labelElementInfo->Wrap( -1 );
	sizerElements->Add( labelElementInfo, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* sizerElementsTools;
	sizerElementsTools = new wxGridSizer( 1, 6, 0, 0 );

	labelNumberElements = new wxStaticText( tabElements, wxID_ANY, wxT("Number of Elements"), wxDefaultPosition, wxDefaultSize, 0 );
	labelNumberElements->Wrap( -1 );
	sizerElementsTools->Add( labelNumberElements, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	spinNumberElements = new wxSpinCtrl( tabElements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1 );
	sizerElementsTools->Add( spinNumberElements, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	buttonElementClear = new wxButton( tabElements, wxID_ANY, wxT("Clear Editor"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerElementsTools->Add( buttonElementClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	buttonElementLoad = new wxButton( tabElements, wxID_ANY, wxT("Load Template"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerElementsTools->Add( buttonElementLoad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	buttonElementSave = new wxButton( tabElements, wxID_ANY, wxT("Save Template"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerElementsTools->Add( buttonElementSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	buttonElementHelp = new wxButton( tabElements, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerElementsTools->Add( buttonElementHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	sizerElements->Add( sizerElementsTools, 0, wxEXPAND, 5 );

	lineElementsTools = new wxStaticLine( tabElements, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerElements->Add( lineElementsTools, 0, wxEXPAND | wxALL, 5 );

	scrollElementTable = new wxScrolledWindow( tabElements, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	scrollElementTable->SetScrollRate( 5, 5 );
	sizerElementEditor = new wxFlexGridSizer( 0, 6, 30, 30 );
	sizerElementEditor->AddGrowableCol( 0 );
	sizerElementEditor->AddGrowableCol( 1 );
	sizerElementEditor->AddGrowableCol( 2 );
	sizerElementEditor->AddGrowableCol( 3 );
	sizerElementEditor->AddGrowableCol( 4 );
	sizerElementEditor->AddGrowableCol( 5 );
	sizerElementEditor->SetFlexibleDirection( wxBOTH );

	labelElementName = new wxStaticText( scrollElementTable, wxID_ANY, wxT("Element Name"), wxDefaultPosition, wxSize(140,-1), 0 );
	labelElementName->Wrap( -1 );
	sizerElementEditor->Add( labelElementName, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelGammaPeak = new wxStaticText( scrollElementTable, wxID_ANY, wxT("Gamma Peak"), wxDefaultPosition, wxSize(140,-1), 0 );
	labelGammaPeak->Wrap( -1 );
	sizerElementEditor->Add( labelGammaPeak, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelAtomicNumber = new wxStaticText( scrollElementTable, wxID_ANY, wxT("Atomic Number"), wxDefaultPosition, wxSize(140,-1), 0 );
	labelAtomicNumber->Wrap( -1 );
	sizerElementEditor->Add( labelAtomicNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelAbundance = new wxStaticText( scrollElementTable, wxID_ANY, wxT("Abundance"), wxDefaultPosition, wxSize(140,-1), 0 );
	labelAbundance->Wrap( -1 );
	sizerElementEditor->Add( labelAbundance, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelIsotopicMass = new wxStaticText( scrollElementTable, wxID_ANY, wxT("Isotopic Mass"), wxDefaultPosition, wxSize(140,-1), 0 );
	labelIsotopicMass->Wrap( -1 );
	sizerElementEditor->Add( labelIsotopicMass, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelAtomicMass = new wxStaticText( scrollElementTable, wxID_ANY, wxT("Atomic Mass"), wxDefaultPosition, wxSize(140,-1), 0 );
	labelAtomicMass->Wrap( -1 );
	sizerElementEditor->Add( labelAtomicMass, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	choiceElementName.Add(new wxChoice( scrollElementTable, wxID_ANY, wxDefaultPosition, wxSize(140,-1), choiceElementNameChoices, 0 ));
	choiceElementName.Last()->SetSelection( 0 );
	sizerElementEditor->Add( choiceElementName.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	choiceGammaPeak.Add(new wxChoice( scrollElementTable, wxID_ANY, wxDefaultPosition, wxSize(140,-1), choiceElementNameChoices, 0 ));
	choiceGammaPeak.Last()->SetSelection( 0 );
	sizerElementEditor->Add( choiceGammaPeak.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAtomicNumber.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textAtomicNumber.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAbundance.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textAbundance.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textIsotopicMass.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textIsotopicMass.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAtomicMass.Add(new wxTextCtrl( scrollElementTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(140,-1), 0 ));
	sizerElementEditor->Add( textAtomicMass.Last(), 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	scrollElementTable->SetSizer( sizerElementEditor );
	scrollElementTable->Layout();
	sizerElementEditor->Fit( scrollElementTable );
	sizerElements->Add( scrollElementTable, 1, wxALL|wxEXPAND, 5 );
    scrollElementTable->Centre(wxBOTH);

	tabElements->SetSizer( sizerElements );
	tabElements->Layout();
	sizerElements->Fit( tabElements );
	tabERYAProfilingMain->AddPage( tabElements, wxT("Elements Editor"), false );
	tabLayers = new wxPanel( tabERYAProfilingMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerLayers;
	sizerLayers = new wxBoxSizer( wxVERTICAL );

	labelLayersInfo = new wxStaticText( tabLayers, wxID_ANY, wxT("Use this tool to edit, save or load from a file, the sample constitution for each layer. Use the Elements tab to modify the number of avaliable Elements to the Layers editor."), wxDefaultPosition, wxDefaultSize, 0 );
	labelLayersInfo->Wrap( -1 );
	sizerLayers->Add( labelLayersInfo, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* sizerLayersTools;
	sizerLayersTools = new wxGridSizer( 1, 6, 0, 0 );

	labelNumberLayers = new wxStaticText( tabLayers, wxID_ANY, wxT("Number of Layers"), wxDefaultPosition, wxDefaultSize, 0 );
	labelNumberLayers->Wrap( -1 );
	sizerLayersTools->Add( labelNumberLayers, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	spinNumberLayers = new wxSpinCtrl( tabLayers, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 65535, 1 );
	sizerLayersTools->Add( spinNumberLayers, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLayerClear = new wxButton( tabLayers, wxID_ANY, wxT("Clear Table"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerLayersTools->Add( buttonLayerClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLayerLoad = new wxButton( tabLayers, wxID_ANY, wxT("Load Table"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerLayersTools->Add( buttonLayerLoad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLayerSave = new wxButton( tabLayers, wxID_ANY, wxT("Save Table"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerLayersTools->Add( buttonLayerSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLayerHelp = new wxButton( tabLayers, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerLayersTools->Add( buttonLayerHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerLayers->Add( sizerLayersTools, 0, wxEXPAND, 5 );

	lineLayersTools = new wxStaticLine( tabLayers, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerLayers->Add( lineLayersTools, 0, wxEXPAND | wxALL, 5 );

	gridLayerEditor = new wxGrid( tabLayers, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	gridLayerEditor->CreateGrid( 1, 1 );
	gridLayerEditor->EnableEditing( true );
	gridLayerEditor->EnableGridLines( true );
	gridLayerEditor->EnableDragGridSize( false );
	gridLayerEditor->SetMargins( 0, 0 );

	// Columns
	gridLayerEditor->EnableDragColMove( false );
	gridLayerEditor->EnableDragColSize( true );
	gridLayerEditor->SetColLabelSize( 40 );
	gridLayerEditor->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	gridLayerEditor->EnableDragRowSize( true );
	gridLayerEditor->SetRowLabelSize( 80 );
	gridLayerEditor->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	gridLayerEditor->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerLayers->Add( gridLayerEditor, 1, wxALL|wxEXPAND, 5 );


	tabLayers->SetSizer( sizerLayers );
	tabLayers->Layout();
	sizerLayers->Fit( tabLayers );
	tabERYAProfilingMain->AddPage( tabLayers, wxT("Layers Editor"), false );
	tabDetector = new wxPanel( tabERYAProfilingMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerDetector;
	sizerDetector = new wxBoxSizer( wxVERTICAL );

	labelDetectorInfo = new wxStaticText( tabDetector, wxID_ANY, wxT("Configure the Detector main physical parameters here. Optionally, define the ressonance model."), wxDefaultPosition, wxDefaultSize, 0 );
	labelDetectorInfo->Wrap( -1 );
	sizerDetector->Add( labelDetectorInfo, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* sizerDetectorTools;
	sizerDetectorTools = new wxGridSizer( 1, 6, 0, 0 );

	buttonDetectorClear = new wxButton( tabDetector, wxID_ANY, wxT("Clear Detector"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerDetectorTools->Add( buttonDetectorClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDetectorReset = new wxButton( tabDetector, wxID_ANY, wxT("Clear Ressonance"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerDetectorTools->Add( buttonDetectorReset, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDetectorFunction = new wxButton( tabDetector, wxID_ANY, wxT("Clear Custom"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerDetectorTools->Add( buttonDetectorFunction, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDetectorLoad = new wxButton( tabDetector, wxID_ANY, wxT("Load Profile"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerDetectorTools->Add( buttonDetectorLoad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDetectorSave = new wxButton( tabDetector, wxID_ANY, wxT("Save Profile"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerDetectorTools->Add( buttonDetectorSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDetectorHelp = new wxButton( tabDetector, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerDetectorTools->Add( buttonDetectorHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerDetector->Add( sizerDetectorTools, 0, wxEXPAND, 5 );

	lineDetectorTools = new wxStaticLine( tabDetector, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDetector->Add( lineDetectorTools, 0, wxEXPAND | wxALL, 5 );

	wxStaticBoxSizer* sizerDetectorParameters;
	sizerDetectorParameters = new wxStaticBoxSizer( new wxStaticBox( tabDetector, wxID_ANY, wxT("Detector Parameters") ), wxVERTICAL );

	wxGridSizer* sizerMainDetector;
	sizerMainDetector = new wxGridSizer( 2, 6, 0, 0 );

	labelBeamResolution = new wxStaticText( tabDetector, wxID_ANY, wxT("Beam Resolution (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelBeamResolution->Wrap( -1 );
	sizerMainDetector->Add( labelBeamResolution, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelTemperature = new wxStaticText( tabDetector, wxID_ANY, wxT("Temperature (K)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelTemperature->Wrap( -1 );
	sizerMainDetector->Add( labelTemperature, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelCharge = new wxStaticText( tabDetector, wxID_ANY, wxT("Charge (uC)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelCharge->Wrap( -1 );
	sizerMainDetector->Add( labelCharge, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelEnergyStep = new wxStaticText( tabDetector, wxID_ANY, wxT("Energy Step (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEnergyStep->Wrap( -1 );
	sizerMainDetector->Add( labelEnergyStep, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelMinimumEnergy = new wxStaticText( tabDetector, wxID_ANY, wxT("Minimum Energy (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelMinimumEnergy->Wrap( -1 );
	sizerMainDetector->Add( labelMinimumEnergy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelMaximumEnergy = new wxStaticText( tabDetector, wxID_ANY, wxT("Maximum Energy (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelMaximumEnergy->Wrap( -1 );
	sizerMainDetector->Add( labelMaximumEnergy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textBeamEnergy = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainDetector->Add( textBeamEnergy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textTemperature = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainDetector->Add( textTemperature, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textCharge = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainDetector->Add( textCharge, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textEnergyStep = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainDetector->Add( textEnergyStep, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textMinimumEnergy = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainDetector->Add( textMinimumEnergy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textMaximumEnergy = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainDetector->Add( textMaximumEnergy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerDetectorParameters->Add( sizerMainDetector, 1, wxEXPAND, 5 );


	sizerDetector->Add( sizerDetectorParameters, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sizerLorentzianRessonance;
	sizerLorentzianRessonance = new wxStaticBoxSizer( new wxStaticBox( tabDetector, wxID_ANY, wxT("Lorentzian Ressonance Setup") ), wxVERTICAL );

	wxGridSizer* sizerMainLorentzian;
	sizerMainLorentzian = new wxGridSizer( 2, 6, 0, 0 );

	labelRessonanceWidth = new wxStaticText( tabDetector, wxID_ANY, wxT("Ressonance Width (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelRessonanceWidth->Wrap( -1 );
	sizerMainLorentzian->Add( labelRessonanceWidth, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textRessonanceWidth = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainLorentzian->Add( textRessonanceWidth, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelRessonancePeak = new wxStaticText( tabDetector, wxID_ANY, wxT("Ressonance Peak (milibarn)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelRessonancePeak->Wrap( -1 );
	sizerMainLorentzian->Add( labelRessonancePeak, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textRessonancePeak = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainLorentzian->Add( textRessonancePeak, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelRessonanceEnergy = new wxStaticText( tabDetector, wxID_ANY, wxT("Ressonance Energy (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelRessonanceEnergy->Wrap( -1 );
	sizerMainLorentzian->Add( labelRessonanceEnergy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textRessonanceEnergy = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainLorentzian->Add( textRessonanceEnergy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerMainLorentzian->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	checkRessonanceRange = new wxCheckBox( tabDetector, wxID_ANY, wxT("Define a Limited Energy Range ?"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainLorentzian->Add( checkRessonanceRange, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelRessonanceMinimum = new wxStaticText( tabDetector, wxID_ANY, wxT("Minimum Ressonance\nEnergy (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelRessonanceMinimum->Wrap( -1 );
	sizerMainLorentzian->Add( labelRessonanceMinimum, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textRessonanceMinimum = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainLorentzian->Add( textRessonanceMinimum, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelRessonanceMaximum = new wxStaticText( tabDetector, wxID_ANY, wxT("Maximum Ressonance\nEnergy (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelRessonanceMaximum->Wrap( -1 );
	sizerMainLorentzian->Add( labelRessonanceMaximum, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textRessonanceMaximum = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainLorentzian->Add( textRessonanceMaximum, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerLorentzianRessonance->Add( sizerMainLorentzian, 1, wxEXPAND, 5 );


	sizerDetector->Add( sizerLorentzianRessonance, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sizerCustomRessonance;
	sizerCustomRessonance = new wxStaticBoxSizer( new wxStaticBox( tabDetector, wxID_ANY, wxT("Custom Function Ressonance Setup") ), wxVERTICAL );

	wxBoxSizer* sizerMainCustom;
	sizerMainCustom = new wxBoxSizer( wxVERTICAL );

	labelMainCustomInfo = new wxStaticText( tabDetector, wxID_ANY, wxT("Write down the algebric function that models the ressonance. When save the Detector profile, any custom function is also stored. Read the User Guide for more information."), wxDefaultPosition, wxDefaultSize, 0 );
	labelMainCustomInfo->Wrap( -1 );
	sizerMainCustom->Add( labelMainCustomInfo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	textCustomRessonance = new wxTextCtrl( tabDetector, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerMainCustom->Add( textCustomRessonance, 0, wxALL|wxEXPAND, 5 );


	sizerCustomRessonance->Add( sizerMainCustom, 1, wxEXPAND, 5 );


	sizerDetector->Add( sizerCustomRessonance, 0, wxEXPAND, 5 );

	wxString radioRessonanceOptionChoices[] = { wxT("Without Ressonance (default)"), wxT("Select Lorentzian Ressonance"), wxT("Select Custom Function Ressonance") };
	int radioRessonanceOptionNChoices = sizeof( radioRessonanceOptionChoices ) / sizeof( wxString );
	radioRessonanceOption = new wxRadioBox( tabDetector, wxID_ANY, wxT("Select Default Ressonance"), wxDefaultPosition, wxDefaultSize, radioRessonanceOptionNChoices, radioRessonanceOptionChoices, 3, wxRA_SPECIFY_ROWS );
	radioRessonanceOption->SetSelection( 0 );
	sizerDetector->Add( radioRessonanceOption, 0, wxALL|wxEXPAND, 5 );


	tabDetector->SetSizer( sizerDetector );
	tabDetector->Layout();
	sizerDetector->Fit( tabDetector );
	tabERYAProfilingMain->AddPage( tabDetector, wxT("Detector and Ressonances"), true );
	tabOutput = new wxPanel( tabERYAProfilingMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerOutput;
	sizerOutput = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* sizerOutputMainTools;
	sizerOutputMainTools = new wxFlexGridSizer( 1, 4, 30, 30 );
	sizerOutputMainTools->AddGrowableCol( 0 );
	sizerOutputMainTools->SetFlexibleDirection( wxBOTH );
	sizerOutputMainTools->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	labelOutputMain = new wxStaticText( tabOutput, wxID_ANY, wxT("The graphic output are rendered here. Optionally, it is possible to and experimental data, or store the results as an image file."), wxDefaultPosition, wxDefaultSize, 0 );
	labelOutputMain->Wrap( -1 );
	sizerOutputMainTools->Add( labelOutputMain, 1, wxALL|wxEXPAND, 5 );

	buttonOutputDataImport = new wxButton( tabOutput, wxID_ANY, wxT("Import Experimental Data"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerOutputMainTools->Add( buttonOutputDataImport, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonOutputImageSave = new wxButton( tabOutput, wxID_ANY, wxT("Save as Image"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerOutputMainTools->Add( buttonOutputImageSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonOutputHelp = new wxButton( tabOutput, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerOutputMainTools->Add( buttonOutputHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerOutput->Add( sizerOutputMainTools, 0, wxEXPAND, 5 );

	lineOutputTools = new wxStaticLine( tabOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerOutput->Add( lineOutputTools, 0, wxEXPAND | wxALL, 5 );

	renderOutputData = new mpWindow( tabOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	sizerOutput->Add( renderOutputData, 1, wxALL|wxEXPAND, 5 );


	tabOutput->SetSizer( sizerOutput );
	tabOutput->Layout();
	sizerOutput->Fit( tabOutput );
	tabERYAProfilingMain->AddPage( tabOutput, wxT("Output Results"), false );
        tabTable = new wxPanel( tabERYAProfilingMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerTable;
	sizerTable = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* sizerTableMainTools;
	sizerTableMainTools = new wxFlexGridSizer( 1, 4, 20, 100 );
	sizerTableMainTools->AddGrowableCol( 0 );
	sizerTableMainTools->SetFlexibleDirection( wxBOTH );
	sizerTableMainTools->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	labelTabOutputMain = new wxStaticText( tabTable, wxID_ANY, wxT("Displays here the yield results on a spreadsheet table, accordling to the same results from the graphical output."), wxDefaultPosition, wxDefaultSize, 0 );
	labelTabOutputMain->Wrap( -1 );
	sizerTableMainTools->Add( labelTabOutputMain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	buttonTableDataImport = new wxButton( tabTable, wxID_ANY, wxT("Import Experimental Data"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerTableMainTools->Add( buttonTableDataImport, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonTableDataSave = new wxButton( tabTable, wxID_ANY, wxT("Save Table Data"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerTableMainTools->Add( buttonTableDataSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonTableHelp = new wxButton( tabTable, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerTableMainTools->Add( buttonTableHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerTable->Add( sizerTableMainTools, 0, wxEXPAND, 5 );

	lineTabTools = new wxStaticLine( tabTable, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerTable->Add( lineTabTools, 0, wxEXPAND | wxALL, 5 );

	gridTableData = new wxGrid( tabTable, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	gridTableData->CreateGrid( 1, 20 );
	gridTableData->EnableEditing( true );
	gridTableData->EnableGridLines( true );
	gridTableData->EnableDragGridSize( false );
	gridTableData->SetMargins( 0, 0 );

	// Columns
	gridTableData->EnableDragColMove( false );
	gridTableData->EnableDragColSize( true );
	gridTableData->SetColLabelSize( 30 );
	gridTableData->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	gridTableData->EnableDragRowSize( true );
	gridTableData->SetRowLabelSize( 80 );
	gridTableData->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	gridTableData->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerTable->Add( gridTableData, 1, wxALL|wxEXPAND, 5 );


	tabTable->SetSizer( sizerTable );
	tabTable->Layout();
	sizerTable->Fit( tabTable );
	tabERYAProfilingMain->AddPage( tabTable, wxT("Table Output"), true );
	panelLog = new wxPanel( tabERYAProfilingMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerLog;
	sizerLog = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* sizerLogMainTools;
	sizerLogMainTools = new wxFlexGridSizer( 1, 3, 20, 100 );
	sizerLogMainTools->AddGrowableCol( 0 );
	sizerLogMainTools->SetFlexibleDirection( wxBOTH );
	sizerLogMainTools->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	labelLogOutputMain = new wxStaticText( panelLog, wxID_ANY, wxT("Displays all partial results intended for logging porpouses."), wxDefaultPosition, wxDefaultSize, 0 );
	labelLogOutputMain->Wrap( -1 );
	sizerLogMainTools->Add( labelLogOutputMain, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLogDataSave = new wxButton( panelLog, wxID_ANY, wxT("Save Log Data"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerLogMainTools->Add( buttonLogDataSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLogHelp = new wxButton( panelLog, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerLogMainTools->Add( buttonLogHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerLog->Add( sizerLogMainTools, 0, wxEXPAND, 5 );

	lineLogTools = new wxStaticLine( panelLog, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerLog->Add( lineLogTools, 0, wxEXPAND | wxALL, 5 );

	gridLogData = new wxGrid( panelLog, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	gridLogData->CreateGrid( 1, 20 );
	gridLogData->EnableEditing( true );
	gridLogData->EnableGridLines( true );
	gridLogData->EnableDragGridSize( false );
	gridLogData->SetMargins( 0, 0 );

	// Columns
	gridLogData->EnableDragColMove( false );
	gridLogData->EnableDragColSize( true );
	gridLogData->SetColLabelSize( 30 );
	gridLogData->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	gridLogData->EnableDragRowSize( true );
	gridLogData->SetRowLabelSize( 80 );
	gridLogData->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	gridLogData->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerLog->Add( gridLogData, 1, wxALL|wxEXPAND, 5 );


	panelLog->SetSizer( sizerLog );
	panelLog->Layout();
	sizerLog->Fit( panelLog );
	tabERYAProfilingMain->AddPage( panelLog, wxT("Log Details"), false );

	sizerERYAProfilingMain->Add( tabERYAProfilingMain, 1, wxEXPAND | wxALL, 5 );

	lineERYAMain = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerERYAProfilingMain->Add( lineERYAMain, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerERYAMainTools;
	sizerERYAMainTools = new wxGridSizer( 1, 6, 0, 0 );


	buttonMainNew = new wxButton( this, wxID_ANY, wxT("Clear All"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAMainTools->Add( buttonMainNew, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonMainAdvanced = new wxButton( this, wxID_ANY, wxT("Advanced Options"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAMainTools->Add( buttonMainAdvanced, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonMainRun = new wxButton( this, wxID_ANY, wxT("Run Simulation"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAMainTools->Add( buttonMainRun, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonMainSave = new wxButton( this, wxID_ANY, wxT("Export Results to File"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAMainTools->Add( buttonMainSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonMainLog = new wxButton( this, wxID_ANY, wxT("Export Log to File"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAMainTools->Add( buttonMainLog, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonMainHelp = new wxButton( this, wxID_ANY, wxT("Open User Guide"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAMainTools->Add( buttonMainHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerERYAProfilingMain->Add( sizerERYAMainTools, 0, wxEXPAND, 5 );


	this->SetSizer( sizerERYAProfilingMain );
	this->Layout();
    tabERYAProfilingMain->SetSelection( 0 );
	this->Centre( wxBOTH );

	this->SetIcon(eryaprofiling_xpm);

	// Connect Events
	this->Connect( menuERYAFileNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileNew ) );
	this->Connect( menuERYAFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileOpen ) );
	this->Connect( menuERYAFileSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileSave ) );
	this->Connect( menuERYAFileSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileSaveAs ) );
	this->Connect( menuERYAFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileQuit ) );
	this->Connect( menuERYADatabaseDetector->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnDatabaseDetector ) );
	this->Connect( menuERYADatabaseElements->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnDatabaseElements ) );
	this->Connect( menuERYADatabaseZiegler->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnDatabaseZiegler ) );
	this->Connect( menuERYASetupDefault->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnSetupDefault ) );
	this->Connect( menuERYASetupReset->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnSetupReset ) );
	this->Connect( menuERYAToolSRIM->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnSRIMImport ) );
	this->Connect( menuERYAToolLabView->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnLabViewImport ) );
	this->Connect( menuERYAToolCalculator->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnCalculator ) );
	this->Connect( menuERYAHelpManual->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnHelpManual ) );
	this->Connect( menuERYAHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnHelpAbout ) );
	spinNumberElements->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ERYAProfilingMain::OnNumberElementSpin ), NULL, this );
	spinNumberElements->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ERYAProfilingMain::OnNumberElementEnter ), NULL, this );
	buttonElementClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementClear ), NULL, this );
	buttonElementLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementLoad ), NULL, this );
	buttonElementSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementSave ), NULL, this );
	buttonElementHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementHelp ), NULL, this );
	choiceElementName.Last()->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnElementNameChoice ), NULL, this );
	choiceGammaPeak.Last()->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnGammaPeakChoice ), NULL, this );
	spinNumberLayers->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ERYAProfilingMain::OnNumberLayerSpin ), NULL, this );
	spinNumberLayers->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ERYAProfilingMain::OnNumberLayerEnter ), NULL, this );
	buttonLayerClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerClear ), NULL, this );
	buttonLayerLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerLoad ), NULL, this );
	buttonLayerSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerSave ), NULL, this );
	buttonLayerHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerHelp ), NULL, this );
	buttonDetectorClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorClear ), NULL, this );
	buttonDetectorReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorReset ), NULL, this );
	buttonDetectorFunction->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorFunction ), NULL, this );
	buttonDetectorLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorLoad ), NULL, this );
	buttonDetectorSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorSave ), NULL, this );
	buttonDetectorHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorHelp ), NULL, this );
	checkRessonanceRange->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnRessonanceRange ), NULL, this );
	radioRessonanceOption->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnRessonanceOption ), NULL, this );
	buttonOutputDataImport->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnOutputData ), NULL, this );
	buttonOutputImageSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnOutputImage ), NULL, this );
	buttonOutputHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnOutputHelp ), NULL, this );
        buttonTableDataImport->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnImportData ), NULL, this );
	buttonTableDataSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnTableSave ), NULL, this );
	buttonTableHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnTableHelp ), NULL, this );
	buttonLogDataSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLogSave ), NULL, this );
	buttonLogHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLogHelp ), NULL, this );
	buttonMainNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainNew ), NULL, this );
	buttonMainAdvanced->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainAdvanced ), NULL, this );
	buttonMainRun->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainRun ), NULL, this );
	buttonMainSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainSave ), NULL, this );
	buttonMainLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainCheck ), NULL, this );
	buttonMainHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainHelp ), NULL, this );

}

ERYAProfilingMain::~ERYAProfilingMain()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileNew ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileOpen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileSave ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileSaveAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnFileQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnDatabaseDetector ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnDatabaseElements ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnDatabaseZiegler ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnSetupDefault ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnSetupReset ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnSRIMImport ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnLabViewImport ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnCalculator ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnHelpManual ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnHelpAbout ) );
	spinNumberElements->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ERYAProfilingMain::OnNumberElementSpin ), NULL, this );
	spinNumberElements->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ERYAProfilingMain::OnNumberElementEnter ), NULL, this );
	buttonElementClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementClear ), NULL, this );
	buttonElementLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementLoad ), NULL, this );
	buttonElementSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementSave ), NULL, this );
	buttonElementHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnElementHelp ), NULL, this );
	choiceElementName.Last()->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnElementNameChoice ), NULL, this );
	choiceGammaPeak.Last()->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnGammaPeakChoice ), NULL, this );
	spinNumberLayers->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ERYAProfilingMain::OnNumberLayerSpin ), NULL, this );
	spinNumberLayers->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ERYAProfilingMain::OnNumberLayerEnter ), NULL, this );
	buttonLayerClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerClear ), NULL, this );
	buttonLayerLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerLoad ), NULL, this );
	buttonLayerSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerSave ), NULL, this );
	buttonLayerHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLayerHelp ), NULL, this );
	buttonDetectorClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorClear ), NULL, this );
	buttonDetectorReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorReset ), NULL, this );
	buttonDetectorFunction->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorFunction ), NULL, this );
	buttonDetectorLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorLoad ), NULL, this );
	buttonDetectorSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorSave ), NULL, this );
	buttonDetectorHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnDetectorHelp ), NULL, this );
	checkRessonanceRange->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnRessonanceRange ), NULL, this );
	radioRessonanceOption->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ERYAProfilingMain::OnRessonanceOption ), NULL, this );
	buttonOutputDataImport->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnOutputData ), NULL, this );
	buttonOutputImageSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnOutputImage ), NULL, this );
	buttonOutputHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnOutputHelp ), NULL, this );
	buttonTableDataImport->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnImportData ), NULL, this );
	buttonTableDataSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnTableSave ), NULL, this );
	buttonTableHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnTableHelp ), NULL, this );
	buttonLogDataSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLogSave ), NULL, this );
	buttonLogHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnLogHelp ), NULL, this );
        buttonMainNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainNew ), NULL, this );
	buttonMainAdvanced->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainAdvanced ), NULL, this );
	buttonMainRun->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainRun ), NULL, this );
	buttonMainSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainSave ), NULL, this );
	buttonMainLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainCheck ), NULL, this );
	buttonMainHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ERYAProfilingMain::OnMainHelp ), NULL, this );

}

dialogDatabaseManager::dialogDatabaseManager( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerDatabaseManager;
	sizerDatabaseManager = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* sizerElements;
	sizerElements = new wxGridSizer( 2, 6, 0, 0 );

	labelElementName = new wxStaticText( this, wxID_ANY, wxT("Element Name"), wxDefaultPosition, wxDefaultSize, 0 );
	labelElementName->Wrap( -1 );
	sizerElements->Add( labelElementName, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelGammaPeak = new wxStaticText( this, wxID_ANY, wxT("Gamma Peak (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelGammaPeak->Wrap( -1 );
	sizerElements->Add( labelGammaPeak, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelAtomicNumber = new wxStaticText( this, wxID_ANY, wxT("Atomic Number"), wxDefaultPosition, wxDefaultSize, 0 );
	labelAtomicNumber->Wrap( -1 );
	sizerElements->Add( labelAtomicNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelAbundance = new wxStaticText( this, wxID_ANY, wxT("Abundance"), wxDefaultPosition, wxDefaultSize, 0 );
	labelAbundance->Wrap( -1 );
	sizerElements->Add( labelAbundance, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelAtomicMass = new wxStaticText( this, wxID_ANY, wxT("Atomic Mass"), wxDefaultPosition, wxDefaultSize, 0 );
	labelAtomicMass->Wrap( -1 );
	sizerElements->Add( labelAtomicMass, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelIsotopicMass = new wxStaticText( this, wxID_ANY, wxT("Isotopic Mass"), wxDefaultPosition, wxDefaultSize, 0 );
	labelIsotopicMass->Wrap( -1 );
	sizerElements->Add( labelIsotopicMass, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	choiceElementName = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceElementNameChoices, 0 );
	choiceElementName->SetSelection( 0 );
	sizerElements->Add( choiceElementName, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	choiceGammaPeak = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceGammaPeakChoices, 0 );
	choiceGammaPeak->SetSelection( 0 );
	sizerElements->Add( choiceGammaPeak, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAtomicNumber = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sizerElements->Add( textAtomicNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAbundance = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sizerElements->Add( textAbundance, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textAtomicMass = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sizerElements->Add( textAtomicMass, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textIsotopicMass = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sizerElements->Add( textIsotopicMass, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

    sizerDatabaseManager->Add( sizerElements, 0, wxEXPAND, 5 );

	separatorDisplay = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDatabaseManager->Add( separatorDisplay, 0, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* sizerElementDisplay;
	sizerElementDisplay = new wxFlexGridSizer( 1, 2, 0, 0 );

	sizerElementDisplay->AddGrowableCol(1);

    wxBoxSizer* sizerElementGrid;
	sizerElementGrid = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* sizerElementGraph;
	sizerElementGraph = new wxBoxSizer( wxVERTICAL );

	tableElementViewer = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	tableElementViewer->CreateGrid( 1000, 2 );
	tableElementViewer->EnableEditing( false );
	tableElementViewer->EnableGridLines( true );
	tableElementViewer->EnableDragGridSize( false );
	tableElementViewer->SetMargins( 0, 0 );

	// Columns
	tableElementViewer->SetColSize( 0, 200 );
	tableElementViewer->SetColSize( 1, 200 );
	tableElementViewer->EnableDragColMove( false );
	tableElementViewer->EnableDragColSize( true );
	tableElementViewer->SetColLabelSize( 30 );
	tableElementViewer->SetColLabelValue( 0, wxT("Energy (keV)") );
	tableElementViewer->SetColLabelValue( 1, wxT("Cross Section (mbarn.keV)") );
	tableElementViewer->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	tableElementViewer->EnableDragRowSize( true );
	tableElementViewer->SetRowLabelSize( 80 );
	tableElementViewer->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	tableElementViewer->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerElementGrid->Add( tableElementViewer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

    sizerElementDisplay->Add( sizerElementGrid, 1, wxEXPAND, 5 );

	renderElementViewer = new mpWindow( this, wxID_ANY,  wxDefaultPosition, wxDefaultSize, 0 );
	sizerElementGraph->Add( renderElementViewer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

    sizerElementDisplay->Add( sizerElementGraph, 1, wxEXPAND, 5 );

	sizerDatabaseManager->Add( sizerElementDisplay, 1, wxEXPAND, 5 );

	separatorButtons = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDatabaseManager->Add( separatorButtons, 0, wxEXPAND | wxALL, 5 );


	wxGridSizer* sizerButtons;
	sizerButtons = new wxGridSizer( 1, 8, 0, 0 );

	buttonAdd = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonAdd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEdit = new wxButton( this, wxID_ANY, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonEdit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonRemove = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonRemove, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonClear = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLoad = new wxButton( this, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonLoad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSave = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtons->Add( buttonHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerDatabaseManager->Add( sizerButtons, 0, wxEXPAND, 5 );

	this->SetSizer( sizerDatabaseManager );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	choiceElementName->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( dialogDatabaseManager::OnElementName ), NULL, this );
	choiceGammaPeak->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( dialogDatabaseManager::OnGammaPeak ), NULL, this );
	buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseAdd ), NULL, this );
	buttonEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseEdit ), NULL, this );
	buttonRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseRemove ), NULL, this );
	buttonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseClear ), NULL, this );
	buttonLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseLoad ), NULL, this );
	buttonSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseSave ), NULL, this );
	buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseCancel ), NULL, this );
	buttonHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseHelp ), NULL, this );

}

dialogDatabaseManager::~dialogDatabaseManager()
{
	// Disconnect Events
	choiceElementName->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( dialogDatabaseManager::OnElementName ), NULL, this );
	choiceGammaPeak->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( dialogDatabaseManager::OnGammaPeak ), NULL, this );
	buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseAdd ), NULL, this );
	buttonEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseEdit ), NULL, this );
	buttonRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseRemove ), NULL, this );
	buttonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseClear ), NULL, this );
	buttonLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseLoad ), NULL, this );
	buttonSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseSave ), NULL, this );
	buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseCancel ), NULL, this );
	buttonHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDatabaseManager::OnDatabaseHelp ), NULL, this );

}

dialogAddDatabase::dialogAddDatabase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerDatabaseEditor;
	sizerDatabaseEditor = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* sizerEditor;
	sizerEditor = new wxGridSizer( 2, 6, 0, 0 );

	labelEditElement = new wxStaticText( this, wxID_ANY, wxT("Element Name"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEditElement->Wrap( -1 );
	sizerEditor->Add( labelEditElement, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelEditGamma = new wxStaticText( this, wxID_ANY, wxT("Gamma Peak (keV)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEditGamma->Wrap( -1 );
	sizerEditor->Add( labelEditGamma, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelEditNumber = new wxStaticText( this, wxID_ANY, wxT("Atomic Number"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEditNumber->Wrap( -1 );
	sizerEditor->Add( labelEditNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelEditAbundance = new wxStaticText( this, wxID_ANY, wxT("Abundance"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEditAbundance->Wrap( -1 );
	sizerEditor->Add( labelEditAbundance, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelEditAtomic = new wxStaticText( this, wxID_ANY, wxT("Atomic Mass"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEditAtomic->Wrap( -1 );
	sizerEditor->Add( labelEditAtomic, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelEditIsotopic = new wxStaticText( this, wxID_ANY, wxT("Isotopic Mass"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEditIsotopic->Wrap( -1 );
	sizerEditor->Add( labelEditIsotopic, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	textEditElement = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditor->Add( textEditElement, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textEditGamma = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditor->Add( textEditGamma, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textEditNumber = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditor->Add( textEditNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textEditAbundance = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditor->Add( textEditAbundance, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textEditAtomic = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditor->Add( textEditAtomic, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	textEditIsotopic = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditor->Add( textEditIsotopic, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	sizerDatabaseEditor->Add( sizerEditor, 0, wxEXPAND, 5 );

	separatorEditor = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDatabaseEditor->Add( separatorEditor, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerTable;
	sizerTable = new wxGridSizer( 1, 1, 0, 0 );

	tableDataEditor = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	tableDataEditor->CreateGrid( 2000, 4 );
	tableDataEditor->EnableEditing( true );
	tableDataEditor->EnableGridLines( true );
	tableDataEditor->EnableDragGridSize( false );
	tableDataEditor->SetMargins( 0, 0 );

	// Columns
	tableDataEditor->SetColSize( 0, 300 );
	tableDataEditor->SetColSize( 1, 300 );
	tableDataEditor->SetColSize( 2, 300 );
	tableDataEditor->SetColSize( 3, 300 );
	tableDataEditor->EnableDragColMove( true );
	tableDataEditor->EnableDragColSize( true );
	tableDataEditor->SetColLabelSize( 30 );
	tableDataEditor->SetColLabelValue( 0, wxT("Energy (keV)") );
	tableDataEditor->SetColLabelValue( 1, wxT("Energy Error (keV)") );
	tableDataEditor->SetColLabelValue( 2, wxT("Cross Section (mbarn.keV)") );
	tableDataEditor->SetColLabelValue( 3, wxT("Cross Section Error(mbarn.keV)") );
	tableDataEditor->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	tableDataEditor->EnableDragRowSize( true );
	tableDataEditor->SetRowLabelSize( 80 );
	tableDataEditor->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	tableDataEditor->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerTable->Add( tableDataEditor, 0, wxALL|wxEXPAND, 5 );


	sizerDatabaseEditor->Add( sizerTable, 1, wxEXPAND, 5 );

	separatorTable = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDatabaseEditor->Add( separatorTable, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerEditButtons;
	sizerEditButtons = new wxGridSizer( 1, 8, 0, 0 );

	buttonImportR33 = new wxButton( this, wxID_ANY, wxT("Import"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonImportR33, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonExportR33 = new wxButton( this, wxID_ANY, wxT("Export"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonExportR33, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

    buttonEditCopy = new wxButton( this, wxID_ANY, wxT("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonEditCopy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEditPaste = new wxButton( this, wxID_ANY, wxT("Paste"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonEditPaste, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEditClear = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonEditClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEditSave = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonEditSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEditCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonEditCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEditHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerEditButtons->Add( buttonEditHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerDatabaseEditor->Add( sizerEditButtons, 0, wxEXPAND, 5 );


	this->SetSizer( sizerDatabaseEditor );
	this->Layout();

	this->Centre( wxBOTH );

    // Clipboard text variable
    dataClipboard = new wxString();

	// Connect Events
	tableDataEditor->Connect( wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler( dialogAddDatabase::OnDatabaseSelect ), NULL, this );
	buttonImportR33->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnImportR33 ), NULL, this );
	buttonExportR33->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnExportR33 ), NULL, this );
	buttonEditCopy->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnDatabaseCopy ), NULL, this );
	buttonEditPaste->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnDatabasePaste ), NULL, this );
	buttonEditClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditClear ), NULL, this );
	buttonEditSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditSave ), NULL, this );
	buttonEditCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditCancel ), NULL, this );
	buttonEditHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditHelp ), NULL, this );
}

dialogAddDatabase::~dialogAddDatabase()
{
	// Disconnect Events
	tableDataEditor->Disconnect( wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler( dialogAddDatabase::OnDatabaseSelect ), NULL, this );
	buttonImportR33->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnImportR33 ), NULL, this );
	buttonExportR33->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnExportR33 ), NULL, this );
	buttonEditCopy->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnDatabaseCopy ), NULL, this );
	buttonEditPaste->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnDatabasePaste ), NULL, this );
	buttonEditClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditClear ), NULL, this );
	buttonEditSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditSave ), NULL, this );
	buttonEditCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditCancel ), NULL, this );
	buttonEditHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogAddDatabase::OnEditHelp ), NULL, this );

}

dialogDetectorSetup::dialogDetectorSetup( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerDetectorSetup;
	sizerDetectorSetup = new wxBoxSizer( wxVERTICAL );

	labelFunctionEficiency = new wxStaticText( this, wxID_ANY, wxT("Input the desired algebraic function that models your detector efficiency:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelFunctionEficiency->Wrap( -1 );
	sizerDetectorSetup->Add( labelFunctionEficiency, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	textFunctionEficiency = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerDetectorSetup->Add( textFunctionEficiency, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	separatorFunctionEficiency = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDetectorSetup->Add( separatorFunctionEficiency, 0, wxEXPAND | wxALL, 5 );

	labelConstantsEficiency = new wxStaticText( this, wxID_ANY, wxT("Or export a file, and edit the following table:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelConstantsEficiency->Wrap( -1 );
	sizerDetectorSetup->Add( labelConstantsEficiency, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	tableConstantEficiency = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	tableConstantEficiency->CreateGrid( 2000, 2 );
	tableConstantEficiency->EnableEditing( true );
	tableConstantEficiency->EnableGridLines( true );
	tableConstantEficiency->EnableDragGridSize( false );
	tableConstantEficiency->SetMargins( 0, 0 );

	// Columns
	tableConstantEficiency->SetColSize( 0, 550 );
	tableConstantEficiency->SetColSize( 1, 550 );
	tableConstantEficiency->EnableDragColMove( false );
	tableConstantEficiency->EnableDragColSize( true );
	tableConstantEficiency->SetColLabelSize( 30 );
	tableConstantEficiency->SetColLabelValue( 0, wxT("Energy (keV)") );
	tableConstantEficiency->SetColLabelValue( 1, wxT("Absolute Efficiency") );
	tableConstantEficiency->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	tableConstantEficiency->EnableDragRowSize( true );
	tableConstantEficiency->SetRowLabelSize( 80 );
	tableConstantEficiency->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	tableConstantEficiency->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerDetectorSetup->Add( tableConstantEficiency, 1, wxALL, 5 );

	separatorButtonEficiency = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDetectorSetup->Add( separatorButtonEficiency, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerButtonSetup;
	sizerButtonSetup = new wxGridSizer( 1, 8, 0, 0 );

	buttonEficiencyLoad = new wxButton( this, wxID_ANY, wxT("Import"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencyLoad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEficiencySave = new wxButton( this, wxID_ANY, wxT("Export"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencySave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

    buttonEficiencyCopy = new wxButton( this, wxID_ANY, wxT("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencyCopy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEficiencyPaste = new wxButton( this, wxID_ANY, wxT("Paste"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencyPaste, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEficiencyClear = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencyClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEficiencyOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencyOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEficiencyCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencyCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEficiencyHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerButtonSetup->Add( buttonEficiencyHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerDetectorSetup->Add( sizerButtonSetup, 0, wxEXPAND, 5 );


	this->SetSizer( sizerDetectorSetup );
	this->Layout();

	this->Centre( wxBOTH );

    // Clipboard text variable
    dataClipboard = new wxString();

	// Connect Events
	tableConstantEficiency->Connect( wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler( dialogDetectorSetup::OnEficiencySelect ), NULL, this );
    buttonEficiencyCopy->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyCopy ), NULL, this );
	buttonEficiencyPaste->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyPaste ), NULL, this );
	buttonEficiencyLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyLoad ), NULL, this );
	buttonEficiencySave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencySave ), NULL, this );
	buttonEficiencyClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyClear ), NULL, this );
	buttonEficiencyOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyOK ), NULL, this );
	buttonEficiencyCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyCancel ), NULL, this );
	buttonEficiencyHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyHelp ), NULL, this );
}

dialogDetectorSetup::~dialogDetectorSetup()
{
	// Disconnect Events
	tableConstantEficiency->Disconnect( wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler( dialogDetectorSetup::OnEficiencySelect ), NULL, this );
    buttonEficiencyCopy->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyCopy ), NULL, this );
	buttonEficiencyPaste->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyPaste ), NULL, this );
	buttonEficiencyLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyLoad ), NULL, this );
	buttonEficiencySave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencySave ), NULL, this );
	buttonEficiencyClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyClear ), NULL, this );
	buttonEficiencyOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyOK ), NULL, this );
	buttonEficiencyCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyCancel ), NULL, this );
	buttonEficiencyHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogDetectorSetup::OnEficiencyHelp ), NULL, this );

}

dialogZieglerParameters::dialogZieglerParameters( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerZieglerParameters;
	sizerZieglerParameters = new wxBoxSizer( wxVERTICAL );

	labelZieglerParameters = new wxStaticText( this, wxID_ANY, wxT("It's necessary to fill manually the following spreadsheets or import the necessary files, to model the Stopping-Power (Click \"Help\" for more detail.)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelZieglerParameters->Wrap( -1 );
	sizerZieglerParameters->Add( labelZieglerParameters, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	lineZieglerVersion = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerZieglerParameters->Add( lineZieglerVersion, 0, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* selectorZieglerVersion;
	selectorZieglerVersion = new wxFlexGridSizer( 1, 2, 0, 0 );
	selectorZieglerVersion->AddGrowableCol( 0 );
	selectorZieglerVersion->SetFlexibleDirection( wxBOTH );
	selectorZieglerVersion->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	labelZieglerVersion = new wxStaticText( this, wxID_ANY, wxT("Select the correct option from the following list options, to model the Ziegler's or SRIM parameters."), wxDefaultPosition, wxDefaultSize, 0 );
	labelZieglerVersion->Wrap( -1 );
	selectorZieglerVersion->Add( labelZieglerVersion, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	wxString choiceZieglerVersionChoices[] = { wxT("1977/1983 Version (12 Parameters)"), wxT("1991/2000 Version (8 Parameters)"), wxT("Custom Interpolation Formula (Algebraic)"), wxT("SRIM Experimental Data (Interpolation)"), wxEmptyString };
	int choiceZieglerVersionNChoices = sizeof( choiceZieglerVersionChoices ) / sizeof( wxString );
	choiceZieglerVersion = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceZieglerVersionNChoices, choiceZieglerVersionChoices, 0 );
	choiceZieglerVersion->SetSelection( 0 );
	selectorZieglerVersion->Add( choiceZieglerVersion, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerZieglerParameters->Add( selectorZieglerVersion, 0, wxEXPAND, 5 );

	lineZieglerTables = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerZieglerParameters->Add( lineZieglerTables, 0, wxEXPAND | wxALL, 5 );

	labelZieglerFunction = new wxStaticText( this, wxID_ANY, wxT("To override the built-in Ziegler Functions and SRIM tables, while reading the tables values, you can insert on the box blow, a custom ERYA macro function (See \"Help\" for more details)."), wxDefaultPosition, wxDefaultSize, 0 );
	labelZieglerFunction->Wrap( -1 );
	sizerZieglerParameters->Add( labelZieglerFunction, 1, wxALL|wxEXPAND, 5 );

	textZieglerFunction = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerParameters->Add( textZieglerFunction, 0, wxALL|wxEXPAND, 5 );

	tabZieglerTables = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	tabZieglerEquations = new wxPanel( tabZieglerTables, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerZieglerEquationsTable;
	sizerZieglerEquationsTable = new wxBoxSizer( wxVERTICAL );

	tableZieglerParameters = new wxGrid( tabZieglerEquations, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	tableZieglerParameters->CreateGrid( 200, 16 );
	tableZieglerParameters->EnableEditing( true );
	tableZieglerParameters->EnableGridLines( true );
	tableZieglerParameters->EnableDragGridSize( false );
	tableZieglerParameters->SetMargins( 0, 0 );

	// Columns
	tableZieglerParameters->SetColSize( 0, 180 );
	tableZieglerParameters->SetColSize( 1, 180 );
	tableZieglerParameters->SetColSize( 2, 180 );
	tableZieglerParameters->SetColSize( 3, 180 );
	tableZieglerParameters->SetColSize( 4, 180 );
	tableZieglerParameters->SetColSize( 5, 180 );
	tableZieglerParameters->SetColSize( 6, 180 );
	tableZieglerParameters->SetColSize( 7, 180 );
	tableZieglerParameters->SetColSize( 8, 180 );
	tableZieglerParameters->SetColSize( 9, 180 );
	tableZieglerParameters->SetColSize( 10, 180 );
	tableZieglerParameters->SetColSize( 11, 180 );
	tableZieglerParameters->SetColSize( 12, 180 );
	tableZieglerParameters->SetColSize( 13, 180 );
	tableZieglerParameters->SetColSize( 14, 180 );
	tableZieglerParameters->SetColSize( 15, 180 );
	tableZieglerParameters->EnableDragColMove( false );
	tableZieglerParameters->EnableDragColSize( true );
	tableZieglerParameters->SetColLabelSize( 30 );
	tableZieglerParameters->SetColLabelValue( 0, wxT("Element") );
	tableZieglerParameters->SetColLabelValue( 1, wxT("A-1") );
	tableZieglerParameters->SetColLabelValue( 2, wxT("A-2") );
	tableZieglerParameters->SetColLabelValue( 3, wxT("A-3") );
	tableZieglerParameters->SetColLabelValue( 4, wxT("A-4") );
	tableZieglerParameters->SetColLabelValue( 5, wxT("A-5") );
	tableZieglerParameters->SetColLabelValue( 6, wxT("A-6") );
	tableZieglerParameters->SetColLabelValue( 7, wxT("A-7") );
	tableZieglerParameters->SetColLabelValue( 8, wxT("A-8") );
	tableZieglerParameters->SetColLabelValue( 9, wxT("A-9") );
	tableZieglerParameters->SetColLabelValue( 10, wxT("A-10") );
	tableZieglerParameters->SetColLabelValue( 11, wxT("A-11") );
	tableZieglerParameters->SetColLabelValue( 12, wxT("A-12") );
	tableZieglerParameters->SetColLabelValue( 13, wxT("Atomic Mass") );
	tableZieglerParameters->SetColLabelValue( 14, wxT("Atomic Density") );
	tableZieglerParameters->SetColLabelValue( 15, wxT("Bloch Parameter") );
	tableZieglerParameters->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	tableZieglerParameters->EnableDragRowSize( true );
	tableZieglerParameters->SetRowLabelSize( 80 );
	tableZieglerParameters->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	tableZieglerParameters->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerZieglerEquationsTable->Add( tableZieglerParameters, 1, wxALL|wxEXPAND, 5 );


	tabZieglerEquations->SetSizer( sizerZieglerEquationsTable );
	tabZieglerEquations->Layout();
	sizerZieglerEquationsTable->Fit( tabZieglerEquations );
	tabZieglerTables->AddPage( tabZieglerEquations, wxT("Ziegler Equations Parameters"), false );
	tabZieglerSRIM = new wxPanel( tabZieglerTables, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerZieglerSRIMTable;
	sizerZieglerSRIMTable = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* sizerZieglerSRIMSelector;
	sizerZieglerSRIMSelector = new wxFlexGridSizer( 1, 4, 0, 0 );
	sizerZieglerSRIMSelector->AddGrowableCol( 0 );
	sizerZieglerSRIMSelector->SetFlexibleDirection( wxBOTH );
	sizerZieglerSRIMSelector->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	labelZieglerSRIMCurrentElement = new wxStaticText( tabZieglerSRIM, wxID_ANY, wxT("The SRIM data related to Atomic Number Element selected, are displayed here:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelZieglerSRIMCurrentElement->Wrap( -1 );
	sizerZieglerSRIMSelector->Add( labelZieglerSRIMCurrentElement, 0, wxALL|wxEXPAND, 5 );

	spinZieglerSRIMCurrentElement = new wxSpinCtrl( tabZieglerSRIM, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 200, 1 );
	sizerZieglerSRIMSelector->Add( spinZieglerSRIMCurrentElement, 0, wxALL, 5 );

	buttonZieglerSRIMUpdate = new wxButton( tabZieglerSRIM, wxID_ANY, wxT("Update Element"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerSRIMSelector->Add( buttonZieglerSRIMUpdate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	buttonZieglerSRIMEraseAllData = new wxButton( tabZieglerSRIM, wxID_ANY, wxT("Erase All Tables"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerSRIMSelector->Add( buttonZieglerSRIMEraseAllData, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );


	sizerZieglerSRIMTable->Add( sizerZieglerSRIMSelector, 0, wxEXPAND, 5 );

	tableZieglerSRIM = new wxGrid( tabZieglerSRIM, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	tableZieglerSRIM->CreateGrid( 1000, 2 );
	tableZieglerSRIM->EnableEditing( true );
	tableZieglerSRIM->EnableGridLines( true );
	tableZieglerSRIM->EnableDragGridSize( false );
	tableZieglerSRIM->SetMargins( 0, 0 );

	// Columns
	tableZieglerSRIM->SetColSize( 0, 600 );
	tableZieglerSRIM->SetColSize( 1, 600 );
	tableZieglerSRIM->EnableDragColMove( false );
	tableZieglerSRIM->EnableDragColSize( true );
	tableZieglerSRIM->SetColLabelSize( 30 );
	tableZieglerSRIM->SetColLabelValue( 0, wxT("Energy (keV)") );
	tableZieglerSRIM->SetColLabelValue( 1, wxT("Stopping Power (ev*10^15 atm/cm^2)") );
	tableZieglerSRIM->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	tableZieglerSRIM->EnableDragRowSize( true );
	tableZieglerSRIM->SetRowLabelSize( 80 );
	tableZieglerSRIM->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	tableZieglerSRIM->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sizerZieglerSRIMTable->Add( tableZieglerSRIM, 1, wxALL|wxEXPAND, 5 );


	tabZieglerSRIM->SetSizer( sizerZieglerSRIMTable );
	tabZieglerSRIM->Layout();
	sizerZieglerSRIMTable->Fit( tabZieglerSRIM );
	tabZieglerTables->AddPage( tabZieglerSRIM, wxT("SRIM Stopping Power Tables"), true );

	sizerZieglerParameters->Add( tabZieglerTables, 1, wxALL, 5 );

	lineZieglerParameters = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerZieglerParameters->Add( lineZieglerParameters, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* sizerZieglerButtons;
	sizerZieglerButtons = new wxGridSizer( 1, 8, 0, 0 );

	buttonZieglerLoad = new wxButton( this, wxID_ANY, wxT("Import"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerLoad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZieglerSave = new wxButton( this, wxID_ANY, wxT("Export"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZieglerCopy = new wxButton( this, wxID_ANY, wxT("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerCopy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZieglerPaste = new wxButton( this, wxID_ANY, wxT("Paste"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerPaste, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZieglerClear = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZieglerOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZieglerCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZieglerHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerZieglerButtons->Add( buttonZieglerHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerZieglerParameters->Add( sizerZieglerButtons, 0, wxEXPAND, 5 );


	this->SetSizer( sizerZieglerParameters );
	this->Layout();

	this->Centre( wxBOTH );

        // Clipboard text variable
        dataClipboard = new wxString();

	// Connect Events
	spinZieglerSRIMCurrentElement->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( dialogZieglerParameters::OnZieglerSelectElement ), NULL, this );
	spinZieglerSRIMCurrentElement->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerSelectElementText ), NULL, this );
	spinZieglerSRIMCurrentElement->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( dialogZieglerParameters::OnZieglerSelectElementEnter ), NULL, this );
	buttonZieglerSRIMUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnUpdateZieglerSRIM ), NULL, this );
	buttonZieglerSRIMEraseAllData->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnEraseZieglerSRIM ), NULL, this );
	tableZieglerParameters->Connect( wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler( dialogZieglerParameters::OnZieglerSelect ), NULL, this );
    buttonZieglerLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerLoad ), NULL, this );
	buttonZieglerSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerSave ), NULL, this );
	buttonZieglerCopy->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerCopy ), NULL, this );
	buttonZieglerPaste->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerPaste ), NULL, this );
	buttonZieglerClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerClear ), NULL, this );
	buttonZieglerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerOK ), NULL, this );
	buttonZieglerCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerCancel ), NULL, this );
	buttonZieglerHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerHelp ), NULL, this );
}

dialogZieglerParameters::~dialogZieglerParameters()
{
	// Disconnect Events
	spinZieglerSRIMCurrentElement->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( dialogZieglerParameters::OnZieglerSelectElement ), NULL, this );
	spinZieglerSRIMCurrentElement->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerSelectElementText ), NULL, this );
	spinZieglerSRIMCurrentElement->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( dialogZieglerParameters::OnZieglerSelectElementEnter ), NULL, this );
	buttonZieglerSRIMUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnUpdateZieglerSRIM ), NULL, this );
	buttonZieglerSRIMEraseAllData->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnEraseZieglerSRIM ), NULL, this );
    tableZieglerParameters->Disconnect( wxEVT_GRID_RANGE_SELECT, wxGridRangeSelectEventHandler( dialogZieglerParameters::OnZieglerSelect ), NULL, this );
	buttonZieglerLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerLoad ), NULL, this );
	buttonZieglerSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerSave ), NULL, this );
	buttonZieglerCopy->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerCopy ), NULL, this );
	buttonZieglerPaste->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerPaste ), NULL, this );
	buttonZieglerClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerClear ), NULL, this );
	buttonZieglerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerOK ), NULL, this );
	buttonZieglerCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerCancel ), NULL, this );
	buttonZieglerHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogZieglerParameters::OnZieglerHelp ), NULL, this );

}

dialogHelp::dialogHelp( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerHelpViewer;
	sizerHelpViewer = new wxBoxSizer( wxVERTICAL );

	pageHelpViewer = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	sizerHelpViewer->Add( pageHelpViewer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	lineHelpViewer = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerHelpViewer->Add( lineHelpViewer, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerHelpButtons;
	sizerHelpButtons = new wxGridSizer( 1, 6, 0, 0 );

	buttonHelpMain = new wxButton( this, wxID_ANY, wxT("Main Page"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerHelpButtons->Add( buttonHelpMain, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonHelpIndex = new wxButton( this, wxID_ANY, wxT("Index"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerHelpButtons->Add( buttonHelpIndex, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonHelpReadme = new wxButton( this, wxID_ANY, wxT("Read Me"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerHelpButtons->Add( buttonHelpReadme, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonHelpBack = new wxButton( this, wxID_ANY, wxT("Back"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerHelpButtons->Add( buttonHelpBack, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonHelpForward = new wxButton( this, wxID_ANY, wxT("Forward"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerHelpButtons->Add( buttonHelpForward, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonHelpClose = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerHelpButtons->Add( buttonHelpClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerHelpViewer->Add( sizerHelpButtons, 0, wxEXPAND, 5 );


	this->SetSizer( sizerHelpViewer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	buttonHelpMain->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpMain ), NULL, this );
	buttonHelpIndex->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpIndex ), NULL, this );
	buttonHelpReadme->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpReadme ), NULL, this );
	buttonHelpBack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpBack ), NULL, this );
	buttonHelpForward->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpForward ), NULL, this );
	buttonHelpClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpClose ), NULL, this );
}

dialogHelp::~dialogHelp()
{
	// Disconnect Events
	buttonHelpMain->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpMain ), NULL, this );
	buttonHelpIndex->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpIndex ), NULL, this );
	buttonHelpReadme->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpReadme ), NULL, this );
	buttonHelpBack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpBack ), NULL, this );
	buttonHelpForward->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpForward ), NULL, this );
	buttonHelpClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogHelp::OnHelpClose ), NULL, this );

}


dialogERYACalculator::dialogERYACalculator( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerERYACalculator;
	sizerERYACalculator = new wxBoxSizer( wxVERTICAL );

	labelCalculatorInput = new wxStaticText( this, wxID_ANY, wxT("Paste any custom algebraic function from the relevant ERYA-Profiling functionality here:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelCalculatorInput->Wrap( -1 );
	sizerERYACalculator->Add( labelCalculatorInput, 0, wxALL|wxEXPAND, 5 );

	textCalculatorInput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYACalculator->Add( textCalculatorInput, 0, wxALL|wxEXPAND, 5 );

	lineCalculatorInput = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerERYACalculator->Add( lineCalculatorInput, 0, wxEXPAND | wxALL, 5 );

	labelCalculatorOutput = new wxStaticText( this, wxID_ANY, wxT("Evaluation Results:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelCalculatorOutput->Wrap( -1 );
	sizerERYACalculator->Add( labelCalculatorOutput, 0, wxALL|wxEXPAND, 5 );

	textCalculatorOutput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sizerERYACalculator->Add( textCalculatorOutput, 0, wxALL|wxEXPAND, 5 );

	lineCalculatorOutput = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerERYACalculator->Add( lineCalculatorOutput, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerCalculatorTools;
	sizerCalculatorTools = new wxGridSizer( 5, 11, 0, 0 );

	buttonAcos = new wxButton( this, wxID_ANY, wxT("acos"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonAcos, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAsin = new wxButton( this, wxID_ANY, wxT("asin"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonAsin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAtan = new wxButton( this, wxID_ANY, wxT("atan"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonAtan, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonFxvar = new wxButton( this, wxID_ANY, wxT("fxvar"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonFxvar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLeftParenthesis = new wxButton( this, wxID_ANY, wxT("("), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonLeftParenthesis, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonRightParanthesis = new wxButton( this, wxID_ANY, wxT(")"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonRightParanthesis, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSqrt = new wxButton( this, wxID_ANY, wxT("sqrt"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonSqrt, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonPower = new wxButton( this, wxID_ANY, wxT("^"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonPower, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLess = new wxButton( this, wxID_ANY, wxT("<"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonLess, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonClearInput = new wxButton( this, wxID_ANY, wxT("ClrProg"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonClearInput, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAsinh = new wxButton( this, wxID_ANY, wxT("asinh"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonAsinh, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAcosh = new wxButton( this, wxID_ANY, wxT("acosh"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonAcosh, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAtanh = new wxButton( this, wxID_ANY, wxT("atanh"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonAtanh, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonFyvar = new wxButton( this, wxID_ANY, wxT("fyvar"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonFyvar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSeven = new wxButton( this, wxID_ANY, wxT("7"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonSeven, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonEight = new wxButton( this, wxID_ANY, wxT("8"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonEight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonNine = new wxButton( this, wxID_ANY, wxT("9"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonNine, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonPlus = new wxButton( this, wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonPlus, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonMore = new wxButton( this, wxID_ANY, wxT(">"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonMore, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonClearOutput = new wxButton( this, wxID_ANY, wxT("ClrAns"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonClearOutput, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonBackSpace = new wxButton( this, wxID_ANY, wxT("BckSpc"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonBackSpace, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonCos = new wxButton( this, wxID_ANY, wxT("cos"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonCos, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSin = new wxButton( this, wxID_ANY, wxT("sin"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonSin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonTan = new wxButton( this, wxID_ANY, wxT("tan"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonTan, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonFxmin = new wxButton( this, wxID_ANY, wxT("fxmin"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonFxmin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonFour = new wxButton( this, wxID_ANY, wxT("4"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonFour, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonFive = new wxButton( this, wxID_ANY, wxT("5"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonFive, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSix = new wxButton( this, wxID_ANY, wxT("6"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonSix, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonMinus = new wxButton( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonMinus, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonComma = new wxButton( this, wxID_ANY, wxT(","), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonComma, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDisplayProgram = new wxButton( this, wxID_ANY, wxT("DspProg"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonDisplayProgram, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSetDecimals = new wxButton( this, wxID_ANY, wxT("SetDec"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonSetDecimals, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonCosh = new wxButton( this, wxID_ANY, wxT("cosh"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonCosh, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSinh = new wxButton( this, wxID_ANY, wxT("sinh"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonSinh, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonTanh = new wxButton( this, wxID_ANY, wxT("tanh"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonTanh, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonFxmax = new wxButton( this, wxID_ANY, wxT("fxmax"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonFxmax, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonOne = new wxButton( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonOne, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonTwo = new wxButton( this, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonTwo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonThree = new wxButton( this, wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonThree, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonTimes = new wxButton( this, wxID_ANY, wxT("*"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonTimes, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonColon = new wxButton( this, wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonColon, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDisplayAnswer = new wxButton( this, wxID_ANY, wxT("DspAns"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonDisplayAnswer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonFunctionVar = new wxButton( this, wxID_ANY, wxT("f(x=?)"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonFunctionVar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonExp = new wxButton( this, wxID_ANY, wxT("exp"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonExp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLog = new wxButton( this, wxID_ANY, wxT("log"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonLog, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonLn = new wxButton( this, wxID_ANY, wxT("ln"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonLn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonVectorMacro = new wxButton( this, wxID_ANY, wxT("fnvar"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonVectorMacro, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonZero = new wxButton( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonZero, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDecimal = new wxButton( this, wxID_ANY, wxT("."), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonDecimal, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonExponential = new wxButton( this, wxID_ANY, wxT("EE"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonExponential, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDivide = new wxButton( this, wxID_ANY, wxT("/"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonDivide, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAssign = new wxButton( this, wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonAssign, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonInputVariable = new wxButton( this, wxID_ANY, wxT("InpVar"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonInputVariable, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonReturn = new wxButton( this, wxID_ANY, wxT("Return"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerCalculatorTools->Add( buttonReturn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerERYACalculator->Add( sizerCalculatorTools, 1, wxEXPAND, 5 );


	this->SetSizer( sizerERYACalculator );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	buttonAcos->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAcos ), NULL, this );
	buttonAsin->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAsin ), NULL, this );
	buttonAtan->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAtan ), NULL, this );
	buttonFxvar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFxvar ), NULL, this );
	buttonLeftParenthesis->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLeftParenthesis ), NULL, this );
	buttonRightParanthesis->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnRightParenthesis ), NULL, this );
	buttonSqrt->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSqrt ), NULL, this );
	buttonPower->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnPower ), NULL, this );
	buttonHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnHelp ), NULL, this );
	buttonClearInput->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnClearInput ), NULL, this );
	buttonAsinh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAsinh ), NULL, this );
	buttonAcosh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAcosh ), NULL, this );
	buttonAtanh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAtanh ), NULL, this );
	buttonFyvar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFyvar ), NULL, this );
	buttonSeven->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSeven ), NULL, this );
	buttonEight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnEight ), NULL, this );
	buttonNine->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnNine ), NULL, this );
	buttonPlus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnPlus ), NULL, this );
	buttonLess->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLess ), NULL, this );
	buttonMore->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnMore ), NULL, this );
	buttonBackSpace->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnBackSpace ), NULL, this );
	buttonClearOutput->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnClearOutput ), NULL, this );
	buttonCos->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnCos ), NULL, this );
	buttonSin->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSin ), NULL, this );
	buttonTan->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTan ), NULL, this );
	buttonFxmin->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFxmin ), NULL, this );
	buttonFour->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFour ), NULL, this );
	buttonFive->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFive ), NULL, this );
	buttonSix->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSix ), NULL, this );
	buttonMinus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnMinus ), NULL, this );
	buttonComma->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnComma ), NULL, this );
	buttonDisplayProgram->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDisplayProgram ), NULL, this );
	buttonCosh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnCosh ), NULL, this );
	buttonSinh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSinh ), NULL, this );
	buttonTanh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTanh ), NULL, this );
	buttonFxmax->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFxmax ), NULL, this );
	buttonOne->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnOne ), NULL, this );
	buttonTwo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTwo ), NULL, this );
	buttonThree->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnThree ), NULL, this );
	buttonTimes->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTimes ), NULL, this );
	buttonColon->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnColon ), NULL, this );
	buttonDisplayAnswer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDisplayAnswer ), NULL, this );
	buttonExp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnExp ), NULL, this );
	buttonLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLog ), NULL, this );
	buttonLn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLn ), NULL, this );
	buttonFunctionVar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFunctionVar ), NULL, this );
	buttonZero->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnZero ), NULL, this );
	buttonDecimal->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDecimal ), NULL, this );
	buttonExponential->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnExponential ), NULL, this );
	buttonDivide->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDivide ), NULL, this );
	buttonAssign->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAssign ), NULL, this );
	buttonVectorMacro->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnVectorMacro ), NULL, this );
	buttonInputVariable->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnInputVariable ), NULL, this );
	buttonSetDecimals->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSetDecimals ), NULL, this );
	buttonReturn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnReturn ), NULL, this );
}

dialogERYACalculator::~dialogERYACalculator()
{
	// Disconnect Events
	buttonAcos->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAcos ), NULL, this );
	buttonAsin->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAsin ), NULL, this );
	buttonAtan->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAtan ), NULL, this );
	buttonFxvar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFxvar ), NULL, this );
	buttonLeftParenthesis->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLeftParenthesis ), NULL, this );
	buttonRightParanthesis->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnRightParenthesis ), NULL, this );
	buttonSqrt->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSqrt ), NULL, this );
	buttonPower->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnPower ), NULL, this );
	buttonHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnHelp ), NULL, this );
	buttonClearInput->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnClearInput ), NULL, this );
	buttonAsinh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAsinh ), NULL, this );
	buttonAcosh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAcosh ), NULL, this );
	buttonAtanh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAtanh ), NULL, this );
	buttonFyvar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFyvar ), NULL, this );
	buttonSeven->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSeven ), NULL, this );
	buttonEight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnEight ), NULL, this );
	buttonNine->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnNine ), NULL, this );
	buttonPlus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnPlus ), NULL, this );
	buttonLess->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLess ), NULL, this );
	buttonMore->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnMore ), NULL, this );
	buttonBackSpace->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnBackSpace ), NULL, this );
	buttonClearOutput->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnClearOutput ), NULL, this );
	buttonCos->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnCos ), NULL, this );
	buttonSin->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSin ), NULL, this );
	buttonTan->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTan ), NULL, this );
	buttonFxmin->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFxmin ), NULL, this );
	buttonFour->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFour ), NULL, this );
	buttonFive->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFive ), NULL, this );
	buttonSix->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSix ), NULL, this );
	buttonMinus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnMinus ), NULL, this );
	buttonComma->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnComma ), NULL, this );
	buttonDisplayProgram->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDisplayProgram ), NULL, this );
	buttonCosh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnCosh ), NULL, this );
	buttonSinh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSinh ), NULL, this );
	buttonTanh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTanh ), NULL, this );
	buttonFxmax->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFxmax ), NULL, this );
	buttonOne->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnOne ), NULL, this );
	buttonTwo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTwo ), NULL, this );
	buttonThree->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnThree ), NULL, this );
	buttonTimes->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnTimes ), NULL, this );
	buttonColon->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnColon ), NULL, this );
	buttonDisplayAnswer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDisplayAnswer ), NULL, this );
	buttonExp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnExp ), NULL, this );
	buttonLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLog ), NULL, this );
	buttonLn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnLn ), NULL, this );
	buttonFunctionVar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnFunctionVar ), NULL, this );
	buttonZero->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnZero ), NULL, this );
	buttonDecimal->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDecimal ), NULL, this );
	buttonExponential->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnExponential ), NULL, this );
	buttonDivide->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnDivide ), NULL, this );
	buttonAssign->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnAssign ), NULL, this );
	buttonVectorMacro->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnVectorMacro ), NULL, this );
	buttonInputVariable->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnInputVariable ), NULL, this );
	buttonSetDecimals->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnSetDecimals ), NULL, this );
	buttonReturn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYACalculator::OnReturn ), NULL, this );

}

wizardLabViewImport::wizardLabViewImport( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style )
{
	this->Create( parent, id, title, bitmap, pos, style );
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxWizardPageSimple* wizardlabViewImport1 = new wxWizardPageSimple( this );
	m_pages.Add( wizardlabViewImport1 );

	wxBoxSizer* sizerLabView1;
	sizerLabView1 = new wxBoxSizer( wxVERTICAL );

	labelLabView1 = new wxStaticText( wizardlabViewImport1, wxID_ANY, wxT("This wizard tool will help to export the original LabView Database files for the native ERYA-Profiling format.\nYou will need the LabView binary files of any Ziegler and Element Databases, plus some text files for additional settings.\n\n\nClick \"Next\" to begin..."), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView1->Wrap( -1 );
	sizerLabView1->Add( labelLabView1, 1, wxALL|wxEXPAND, 5 );


	wizardlabViewImport1->SetSizer( sizerLabView1 );
	wizardlabViewImport1->Layout();
	sizerLabView1->Fit( wizardlabViewImport1 );
	wxWizardPageSimple* wizardLabView2 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView2 );

	wxBoxSizer* sizerlabView2;
	sizerlabView2 = new wxBoxSizer( wxVERTICAL );

	labelLabView2 = new wxStaticText( wizardLabView2, wxID_ANY, wxT("Select the correct LabView ERYA Database from the file widget below.\n\nNote: To avoid problems, save and close LabView ERYA before continue.\n\nOnce done, choose the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView2->Wrap( -1 );
	sizerlabView2->Add( labelLabView2, 1, wxALL|wxEXPAND, 5 );

	fileLabViewDatabases = new wxFilePickerCtrl( wizardLabView2, wxID_ANY, wxEmptyString, wxT("Select a Compatible LabView ERYA Database"), wxT("LabView Database Binary File (*.txt)|*.txt"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerlabView2->Add( fileLabViewDatabases, 0, wxALL|wxEXPAND, 5 );


	wizardLabView2->SetSizer( sizerlabView2 );
	wizardLabView2->Layout();
	sizerlabView2->Fit( wizardLabView2 );
	wxWizardPageSimple* wizardLabView3 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView3 );

	wxBoxSizer* sizerlabView3;
	sizerlabView3 = new wxBoxSizer( wxVERTICAL );

	labelLabView3 = new wxStaticText( wizardLabView3, wxID_ANY, wxT("Select the correct LabView ERYA Ziegler from the file widget below.\n\nNote: To avoid problems, save and close LabView ERYA before continue.\n\nOnce done, choose the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView3->Wrap( -1 );
	sizerlabView3->Add( labelLabView3, 1, wxALL|wxEXPAND, 5 );

	fileLabViewZiegler = new wxFilePickerCtrl( wizardLabView3, wxID_ANY, wxEmptyString, wxT("Select a Compatible LabView ERYA Database"), wxT("LabView Database Binary File (*.txt)|*.txt"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerlabView3->Add( fileLabViewZiegler, 0, wxALL|wxEXPAND, 5 );


	wizardLabView3->SetSizer( sizerlabView3 );
	wizardLabView3->Layout();
	sizerlabView3->Fit( wizardLabView3 );
	wxWizardPageSimple* wizardLabView4 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView4 );

	wxBoxSizer* sizerlabView4;
	sizerlabView4 = new wxBoxSizer( wxVERTICAL );

	labelLabView4 = new wxStaticText( wizardLabView4, wxID_ANY, wxT("Select the correct LabView ERYA Detector from the file widget below.\n(Actually a plain text file)\n\nNote: To avoid problems, save and close LabView ERYA before continue.\n\nOnce done, choose the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView4->Wrap( -1 );
	sizerlabView4->Add( labelLabView4, 1, wxALL|wxEXPAND, 5 );

	fileLabViewDetector = new wxFilePickerCtrl( wizardLabView4, wxID_ANY, wxEmptyString, wxT("Select a Compatible ASCII file for Detector"), wxT("ASCII Text File (*.txt)|*.txt"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerlabView4->Add( fileLabViewDetector, 0, wxALL|wxEXPAND, 5 );


	wizardLabView4->SetSizer( sizerlabView4 );
	wizardLabView4->Layout();
	sizerlabView4->Fit( wizardLabView4 );
	wxWizardPageSimple* wizardLabView5 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView5 );

	wxBoxSizer* sizerlabView5;
	sizerlabView5 = new wxBoxSizer( wxVERTICAL );

	labelLabView5 = new wxStaticText( wizardLabView5, wxID_ANY, wxT("Select the correct text file that contains the Element Densities from the file widget below.\n\nNote: To avoid problems, save and close LabView ERYA before continue.\n\nOnce done, choose the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView5->Wrap( -1 );
	sizerlabView5->Add( labelLabView5, 1, wxALL|wxEXPAND, 5 );

	fileLabViewDensity = new wxFilePickerCtrl( wizardLabView5, wxID_ANY, wxEmptyString, wxT("Select a Compatible ASCII file for Density"), wxT("ASCII Text File (*.txt)|*.txt"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerlabView5->Add( fileLabViewDensity, 0, wxALL|wxEXPAND, 5 );


	wizardLabView5->SetSizer( sizerlabView5 );
	wizardLabView5->Layout();
	sizerlabView5->Fit( wizardLabView5 );
	wxWizardPageSimple* wizardLabView6 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView6 );

	wxBoxSizer* sizerlabView6;
	sizerlabView6 = new wxBoxSizer( wxVERTICAL );

	labelLabView6 = new wxStaticText( wizardLabView6, wxID_ANY, wxT("Select the correct text file that contains the Bloch's Parameters from the file widget below.\n\nNote: To avoid problems, save and close LabView ERYA before continue.\n\nOnce done, choose the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView6->Wrap( -1 );
	sizerlabView6->Add( labelLabView6, 1, wxALL|wxEXPAND, 5 );

	fileLabViewBloch = new wxFilePickerCtrl( wizardLabView6, wxID_ANY, wxEmptyString, wxT("Select a Compatible ASCII file for Bloch"), wxT("LabView Database Binary File (*.txt)|*.txt"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerlabView6->Add( fileLabViewBloch, 0, wxALL|wxEXPAND, 5 );


	wizardLabView6->SetSizer( sizerlabView6 );
	wizardLabView6->Layout();
	sizerlabView6->Fit( wizardLabView6 );
	wxWizardPageSimple* wizardLabView7 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView7 );

	wxBoxSizer* sizerlabView7;
	sizerlabView7 = new wxBoxSizer( wxVERTICAL );

	labelLabView7 = new wxStaticText( wizardLabView7, wxID_ANY, wxT("Save the converted Element Database to a file and directory of your choice.\n\nOnce done, save the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView7->Wrap( -1 );
	sizerlabView7->Add( labelLabView7, 1, wxALL|wxEXPAND, 5 );

	fileERYADatabase = new wxFilePickerCtrl( wizardLabView7, wxID_ANY, wxEmptyString, wxT("Save the Converted ERYA Database as..."), wxT("ERYA Profiling Database (*.epd)|*.epd"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE );
	sizerlabView7->Add( fileERYADatabase, 0, wxALL|wxEXPAND, 5 );


	wizardLabView7->SetSizer( sizerlabView7 );
	wizardLabView7->Layout();
	sizerlabView7->Fit( wizardLabView7 );
	wxWizardPageSimple* wizardLabView8 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView8 );

	wxBoxSizer* sizerlabView8;
	sizerlabView8 = new wxBoxSizer( wxVERTICAL );

	labelLabView8 = new wxStaticText( wizardLabView8, wxID_ANY, wxT("Save the converted Detector Profile to a file and directory of your choice.\n\nOnce done, save the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView8->Wrap( -1 );
	sizerlabView8->Add( labelLabView8, 1, wxALL|wxEXPAND, 5 );

	fileERYADetector = new wxFilePickerCtrl( wizardLabView8, wxID_ANY, wxEmptyString, wxT("Save the Converted ERYA Detector as..."), wxT("ERYA Profiling Detector (*.epsd)|*.epsd"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE );
	sizerlabView8->Add( fileERYADetector, 0, wxALL|wxEXPAND, 5 );


	wizardLabView8->SetSizer( sizerlabView8 );
	wizardLabView8->Layout();
	sizerlabView8->Fit( wizardLabView8 );
	wxWizardPageSimple* wizardLabView9 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView9 );

	wxBoxSizer* sizerlabView9;
	sizerlabView9 = new wxBoxSizer( wxVERTICAL );

	labelLabView9 = new wxStaticText( wizardLabView9, wxID_ANY, wxT("Save the converted Ziegler Parameters to a file and directory of your choice.\n\nOnce done, save the file, and click \"Next\" "), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView9->Wrap( -1 );
	sizerlabView9->Add( labelLabView9, 1, wxALL|wxEXPAND, 5 );

	fileERYAZiegler = new wxFilePickerCtrl( wizardLabView9, wxID_ANY, wxEmptyString, wxT("Save the Converted ERYA Ziegler as..."), wxT("ERYA Profiling Ziegler (*.epsz)|*.epsz"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE );
	sizerlabView9->Add( fileERYAZiegler, 0, wxALL|wxEXPAND, 5 );


	wizardLabView9->SetSizer( sizerlabView9 );
	wizardLabView9->Layout();
	sizerlabView9->Fit( wizardLabView9 );
	wxWizardPageSimple* wizardLabView10 = new wxWizardPageSimple( this );
	m_pages.Add( wizardLabView10 );

	wxBoxSizer* sizerLabView10;
	sizerLabView10 = new wxBoxSizer( wxVERTICAL );

	labelLabView10 = new wxStaticText( wizardLabView10, wxID_ANY, wxT("ERYA Profiling should have all necessary options gathered.\nThe conversion may take several seconds on slower computers.\n\nClick \"Finish\" to close this wizard, and start the export."), wxDefaultPosition, wxDefaultSize, 0 );
	labelLabView10->Wrap( -1 );
	sizerLabView10->Add( labelLabView10, 1, wxALL|wxEXPAND, 5 );


	wizardLabView10->SetSizer( sizerLabView10 );
	wizardLabView10->Layout();
	sizerLabView10->Fit( wizardLabView10 );

	this->Centre( wxBOTH );

	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}

	// Connect Events
	this->Connect( wxID_ANY, wxEVT_WIZARD_CANCEL, wxWizardEventHandler( wizardLabViewImport::OnLabViewImportCancel ) );
	this->Connect( wxID_ANY, wxEVT_WIZARD_FINISHED, wxWizardEventHandler( wizardLabViewImport::OnLabViewImportFinish ) );
}

wizardLabViewImport::~wizardLabViewImport()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_WIZARD_CANCEL, wxWizardEventHandler( wizardLabViewImport::OnLabViewImportCancel ) );
	this->Disconnect( wxID_ANY, wxEVT_WIZARD_FINISHED, wxWizardEventHandler( wizardLabViewImport::OnLabViewImportFinish ) );

	m_pages.Clear();
}


wizardFirstRun::wizardFirstRun( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style )
{
	this->Create( parent, id, title, bitmap, pos, style );
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxWizardPageSimple* wizardFirstRun1 = new wxWizardPageSimple( this );
	m_pages.Add( wizardFirstRun1 );

	wxBoxSizer* sizerFirstRun1;
	sizerFirstRun1 = new wxBoxSizer( wxVERTICAL );

	labelFirstRun1 = new wxStaticText( wizardFirstRun1, wxID_ANY, wxT("Welcome to ERYA Profiling!\n\nBefore use the program, \nERYA requires some additional informations to write a Configuration File,\nwhere the main Database files will be loaded when ERYA starts.\n\nPlease follow the instructions."), wxDefaultPosition, wxDefaultSize, 0 );
	labelFirstRun1->Wrap( -1 );
	sizerFirstRun1->Add( labelFirstRun1, 1, wxALL|wxEXPAND, 5 );


	wizardFirstRun1->SetSizer( sizerFirstRun1 );
	wizardFirstRun1->Layout();
	sizerFirstRun1->Fit( wizardFirstRun1 );
	wxWizardPageSimple* wizardFirstRun2 = new wxWizardPageSimple( this );
	m_pages.Add( wizardFirstRun2 );

	wxBoxSizer* sizerFirstRun2;
	sizerFirstRun2 = new wxBoxSizer( wxVERTICAL );

	labelFirstRun2 = new wxStaticText( wizardFirstRun2, wxID_ANY, wxT("Select the Detector Efficiency Profile file, from the widget below.\n\nNote: It will only support native ERYA Profile files.\nIf you had another file formats, \nplease use the Database Management tools to convert them first.\n\nIf necessary, read the User Guide before proceding."), wxDefaultPosition, wxDefaultSize, 0 );
	labelFirstRun2->Wrap( -1 );
	sizerFirstRun2->Add( labelFirstRun2, 1, wxALL|wxEXPAND, 5 );

	fileDetectorFirstRun = new wxFilePickerCtrl( wizardFirstRun2, wxID_ANY, wxEmptyString, wxT("Select a Compatible File for the ERYA Detector Efficiency"), wxT("ERYA Profiling Detector Efficiency (*.epsd)|*.epsd"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerFirstRun2->Add( fileDetectorFirstRun, 0, wxALL|wxEXPAND, 5 );


	wizardFirstRun2->SetSizer( sizerFirstRun2 );
	wizardFirstRun2->Layout();
	sizerFirstRun2->Fit( wizardFirstRun2 );
	wxWizardPageSimple* wizardFirstRun3 = new wxWizardPageSimple( this );
	m_pages.Add( wizardFirstRun3 );

	wxBoxSizer* sizerFirstRun3;
	sizerFirstRun3 = new wxBoxSizer( wxVERTICAL );

	labelFirstRun3 = new wxStaticText( wizardFirstRun3, wxID_ANY, wxT("Select the Elements Database compatible with ERYA Profiling, from the widget below.\n\nNote: Only native ERYA Databases are supported by this wizard.\n\nIf necessary, read the User Guide for further details."), wxDefaultPosition, wxDefaultSize, 0 );
	labelFirstRun3->Wrap( -1 );
	sizerFirstRun3->Add( labelFirstRun3, 1, wxALL|wxEXPAND, 5 );

	fileElementsFirstRun = new wxFilePickerCtrl( wizardFirstRun3, wxID_ANY, wxEmptyString, wxT("Select a Compatible File for the ERYA Element Database"), wxT("ERYA Element Database (*.epd)|*.epd"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerFirstRun3->Add( fileElementsFirstRun, 0, wxALL|wxEXPAND, 5 );


	wizardFirstRun3->SetSizer( sizerFirstRun3 );
	wizardFirstRun3->Layout();
	sizerFirstRun3->Fit( wizardFirstRun3 );
	wxWizardPageSimple* wizardFirstRun4 = new wxWizardPageSimple( this );
	m_pages.Add( wizardFirstRun4 );

	wxBoxSizer* sizerFirstRun4;
	sizerFirstRun4 = new wxBoxSizer( wxVERTICAL );

	labelFirstRun4 = new wxStaticText( wizardFirstRun4, wxID_ANY, wxT("Select a compatible ERYA Ziegler Parameters file,\nfrom the widget below.\n\nNote: Only native ERYA Databases are supported by this wizard.\n\nPlease read the User Guide, before continue."), wxDefaultPosition, wxDefaultSize, 0 );
	labelFirstRun4->Wrap( -1 );
	sizerFirstRun4->Add( labelFirstRun4, 1, wxALL|wxEXPAND, 5 );

	fileZieglerFirstRun = new wxFilePickerCtrl( wizardFirstRun4, wxID_ANY, wxEmptyString, wxT("Select a Compatible File for the ERYA Ziegler Parameters"), wxT("ERYA Profiling Ziegler Parameters (*.epsz)|*.epsz"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerFirstRun4->Add( fileZieglerFirstRun, 0, wxALL|wxEXPAND, 5 );


	wizardFirstRun4->SetSizer( sizerFirstRun4 );
	wizardFirstRun4->Layout();
	sizerFirstRun4->Fit( wizardFirstRun4 );
	wxWizardPageSimple* wizardFirstRun5 = new wxWizardPageSimple( this );
	m_pages.Add( wizardFirstRun5 );

	wxBoxSizer* sizerFirstRun5;
	sizerFirstRun5 = new wxBoxSizer( wxVERTICAL );

	labelFirstRun5 = new wxStaticText( wizardFirstRun5, wxID_ANY, wxT("Select where the ERYA Profiling Configuration file should be placed.\n\nThe default Databases will also be placed at the same Configuration directory.\n\nThe recomended setting is to choose the default folder defined by the operating system itself.\n\nRead the manual for more information."), wxDefaultPosition, wxDefaultSize, 0 );
	labelFirstRun5->Wrap( -1 );
	sizerFirstRun5->Add( labelFirstRun5, 1, wxALL|wxEXPAND, 5 );

	wxString radioSetupDefaultChoices[] = { wxT("At the User Profile Directory"), wxT("At the ERYA's Root Directory")};
	int radioSetupDefaultNChoices = sizeof( radioSetupDefaultChoices ) / sizeof( wxString );
	radioSetupDefault = new wxRadioBox( wizardFirstRun5, wxID_ANY, wxT("Place the Setup Profile..."), wxDefaultPosition, wxDefaultSize, radioSetupDefaultNChoices, radioSetupDefaultChoices, 2, wxRA_SPECIFY_ROWS );
	radioSetupDefault->SetSelection( 0 );
	sizerFirstRun5->Add( radioSetupDefault, 0, wxALL|wxEXPAND, 5 );


	wizardFirstRun5->SetSizer( sizerFirstRun5 );
	wizardFirstRun5->Layout();
	sizerFirstRun5->Fit( wizardFirstRun5 );
	wxWizardPageSimple* wizardFirstRun6 = new wxWizardPageSimple( this );
	m_pages.Add( wizardFirstRun6 );

	wxBoxSizer* sizerFirstRun6;
	sizerFirstRun6 = new wxBoxSizer( wxVERTICAL );

	labelFirstRun6 = new wxStaticText( wizardFirstRun6, wxID_ANY, wxT("ERYA Profiling Setup Complete!\n\nThe default configuration file was stored, and the default Databases will be loaded automatically at next start-ups.\n\nYou can reset the configurations using the \"Reset Settings\" option menu, and it will repeat the same process again."), wxDefaultPosition, wxDefaultSize, 0 );
	labelFirstRun6->Wrap( -1 );
	sizerFirstRun6->Add( labelFirstRun6, 1, wxALL|wxEXPAND, 5 );


	wizardFirstRun6->SetSizer( sizerFirstRun6 );
	wizardFirstRun6->Layout();
	sizerFirstRun6->Fit( wizardFirstRun6 );

	this->Centre( wxBOTH );

	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}

	// Connect Events
	this->Connect( wxID_ANY, wxEVT_WIZARD_CANCEL, wxWizardEventHandler( wizardFirstRun::OnFirstRunCancel ) );
	this->Connect( wxID_ANY, wxEVT_WIZARD_FINISHED, wxWizardEventHandler( wizardFirstRun::OnFirstRunFinish ) );
}

wizardFirstRun::~wizardFirstRun()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_WIZARD_CANCEL, wxWizardEventHandler( wizardFirstRun::OnFirstRunCancel ) );
	this->Disconnect( wxID_ANY, wxEVT_WIZARD_FINISHED, wxWizardEventHandler( wizardFirstRun::OnFirstRunFinish ) );

	m_pages.Clear();
}

wizardSRIMImport::wizardSRIMImport( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style )
{
	this->Create( parent, id, title, bitmap, pos, style );
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxWizardPageSimple* pageSRIMImport1 = new wxWizardPageSimple( this );
	m_pages.Add( pageSRIMImport1 );

	wxBoxSizer* sizerSRIMImport1;
	sizerSRIMImport1 = new wxBoxSizer( wxVERTICAL );

	labelSRIMImport1 = new wxStaticText( pageSRIMImport1, wxID_ANY, wxT("This tool are intended to convert the files output generated by SRIM software, when the user create Stopping Power tables related to the selected elements.\n\nBefore continue, check first the output files contents, and verify if the ion beam are always Hydrogen, and the target are a single Element.\n\nERYA only support a single table per Element.\n\nOnce complete, click \"Next\" to begin."), wxDefaultPosition, wxDefaultSize, 0 );
	labelSRIMImport1->Wrap( -1 );
	sizerSRIMImport1->Add( labelSRIMImport1, 1, wxALL|wxEXPAND, 5 );


	pageSRIMImport1->SetSizer( sizerSRIMImport1 );
	pageSRIMImport1->Layout();
	sizerSRIMImport1->Fit( pageSRIMImport1 );
	wxWizardPageSimple* pageSRIMImport2 = new wxWizardPageSimple( this );
	m_pages.Add( pageSRIMImport2 );

	wxBoxSizer* sizerSRIMImport2;
	sizerSRIMImport2 = new wxBoxSizer( wxVERTICAL );

	labelSRIMImport2 = new wxStaticText( pageSRIMImport2, wxID_ANY, wxT("Use this widget to load all required source files, and once completed, click \"Next\"."), wxDefaultPosition, wxDefaultSize, 0 );
	labelSRIMImport2->Wrap( -1 );
	sizerSRIMImport2->Add( labelSRIMImport2, 0, wxALL|wxEXPAND, 5 );

	listSRIMSourceFiles = new wxListBox( pageSRIMImport2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	sizerSRIMImport2->Add( listSRIMSourceFiles, 1, wxALL|wxEXPAND, 5 );

	wxGridSizer* sizerSRIMSourceFiles;
	sizerSRIMSourceFiles = new wxGridSizer( 1, 3, 0, 0 );

	buttonSRIMLoad = new wxButton( pageSRIMImport2, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSRIMSourceFiles->Add( buttonSRIMLoad, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSRIMRemove = new wxButton( pageSRIMImport2, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSRIMSourceFiles->Add( buttonSRIMRemove, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSRIMClear = new wxButton( pageSRIMImport2, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSRIMSourceFiles->Add( buttonSRIMClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerSRIMImport2->Add( sizerSRIMSourceFiles, 0, wxEXPAND, 5 );


	pageSRIMImport2->SetSizer( sizerSRIMImport2 );
	pageSRIMImport2->Layout();
	sizerSRIMImport2->Fit( pageSRIMImport2 );
	wxWizardPageSimple* pageSRIMImport3 = new wxWizardPageSimple( this );
	m_pages.Add( pageSRIMImport3 );

	wxBoxSizer* sizerSRIMImport3;
	sizerSRIMImport3 = new wxBoxSizer( wxVERTICAL );

	labelSRIMImport3 = new wxStaticText( pageSRIMImport3, wxID_ANY, wxT("As optional step, select  the source file for the Ziegler Equation Parameters, since the SRIM tables will be merged on ERYA's Ziegler database.\n\nYou can use either the native ERYA Ziegler format, or the ASCII/LabView ERYA format as source file.\n\nExcel Xlsx are also compatible.\n\nYou can select the option to copy the current Ziegler Parameters on ERYA memory."), wxDefaultPosition, wxDefaultSize, 0 );
	labelSRIMImport3->Wrap( -1 );
	sizerSRIMImport3->Add( labelSRIMImport3, 1, wxALL|wxEXPAND, 5 );

	wxString radioZieglerParametersChoices[] = { wxT("Use the current loaded Ziegler Parameters."), wxT("Load an external file supported by ERYA with the Ziegler Parameters"), wxT("Do not export any Ziegler Parameters.") };
	int radioZieglerParametersNChoices = sizeof( radioZieglerParametersChoices ) / sizeof( wxString );
	radioZieglerParameters = new wxRadioBox( pageSRIMImport3, wxID_ANY, wxT("Export the Ziegler Parameters ?"), wxDefaultPosition, wxDefaultSize, radioZieglerParametersNChoices, radioZieglerParametersChoices, 1, wxRA_SPECIFY_COLS );
	radioZieglerParameters->SetSelection( 0 );
	sizerSRIMImport3->Add( radioZieglerParameters, 0, wxALL|wxEXPAND, 5 );

	labelZieglerSource = new wxStaticText( pageSRIMImport3, wxID_ANY, wxT("Select the Source File with the Ziegler Parameters"), wxDefaultPosition, wxDefaultSize, 0 );
	labelZieglerSource->Wrap( -1 );
	sizerSRIMImport3->Add( labelZieglerSource, 0, wxALL|wxEXPAND, 5 );

	fileZieglerSource = new wxFilePickerCtrl( pageSRIMImport3, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("ERYA Ziegler Database (*.epsz)|*.epsz|LabView ERYA Ziegler/ASCII (*.txt)|*.txt|Microsoft Excel Xlsx (*.xlsx)|*.xlsx"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_OPEN );
	sizerSRIMImport3->Add( fileZieglerSource, 0, wxALL|wxEXPAND, 5 );


	pageSRIMImport3->SetSizer( sizerSRIMImport3 );
	pageSRIMImport3->Layout();
	sizerSRIMImport3->Fit( pageSRIMImport3 );
	wxWizardPageSimple* pageSRIMImport4 = new wxWizardPageSimple( this );
	m_pages.Add( pageSRIMImport4 );

	wxBoxSizer* sizerSRIMImport4;
	sizerSRIMImport4 = new wxBoxSizer( wxVERTICAL );

	labelSRIMImport4 = new wxStaticText( pageSRIMImport4, wxID_ANY, wxT("Select the new output file, which will be on native ERYA Ziegler format.\nThe original SRIM tables for the insert elements will be agruped on the new database file."), wxDefaultPosition, wxDefaultSize, 0 );
	labelSRIMImport4->Wrap( -1 );
	sizerSRIMImport4->Add( labelSRIMImport4, 1, wxALL|wxEXPAND, 5 );

	fileZieglerOutput = new wxFilePickerCtrl( pageSRIMImport4, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("ERYA Ziegler Files (*.epsz)|*.epsz"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE );
	sizerSRIMImport4->Add( fileZieglerOutput, 0, wxALL|wxEXPAND, 5 );


	pageSRIMImport4->SetSizer( sizerSRIMImport4 );
	pageSRIMImport4->Layout();
	sizerSRIMImport4->Fit( pageSRIMImport4 );
	wxWizardPageSimple* pageSRIMImport5 = new wxWizardPageSimple( this );
	m_pages.Add( pageSRIMImport5 );

	wxBoxSizer* sizerSRIMImport5;
	sizerSRIMImport5 = new wxBoxSizer( wxVERTICAL );

	labelSRIMImport5 = new wxStaticText( pageSRIMImport5, wxID_ANY, wxT("Once gathered all necessary source files, and options, click \"Finish\" to start the conversion process.\n\nTake notice that repeated tables for the same Element will be overwritten in sequence, and the last one are actually stored.\n\nIf you make duplicates, please go \"Back\", and delete the unecessary source files on the list."), wxDefaultPosition, wxDefaultSize, 0 );
	labelSRIMImport5->Wrap( -1 );
	sizerSRIMImport5->Add( labelSRIMImport5, 1, wxALL|wxEXPAND, 5 );


	pageSRIMImport5->SetSizer( sizerSRIMImport5 );
	pageSRIMImport5->Layout();
	sizerSRIMImport5->Fit( pageSRIMImport5 );

	this->Centre( wxBOTH );

	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}

	// Connect Events
	this->Connect( wxID_ANY, wxEVT_WIZARD_CANCEL, wxWizardEventHandler( wizardSRIMImport::OnSRIMImportCancel ) );
	this->Connect( wxID_ANY, wxEVT_WIZARD_FINISHED, wxWizardEventHandler( wizardSRIMImport::OnSRIMImportComplete ) );
	listSRIMSourceFiles->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceSelect ), NULL, this );
	buttonSRIMLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceLoad ), NULL, this );
	buttonSRIMRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceRemove ), NULL, this );
	buttonSRIMClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceClear ), NULL, this );
	radioZieglerParameters->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( wizardSRIMImport::OnEnableZieglerFiles ), NULL, this );
}

wizardSRIMImport::~wizardSRIMImport()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_WIZARD_CANCEL, wxWizardEventHandler( wizardSRIMImport::OnSRIMImportCancel ) );
	this->Disconnect( wxID_ANY, wxEVT_WIZARD_FINISHED, wxWizardEventHandler( wizardSRIMImport::OnSRIMImportComplete ) );
	listSRIMSourceFiles->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceSelect ), NULL, this );
	buttonSRIMLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceLoad ), NULL, this );
	buttonSRIMRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceRemove ), NULL, this );
	buttonSRIMClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wizardSRIMImport::OnSRIMSourceClear ), NULL, this );
	radioZieglerParameters->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( wizardSRIMImport::OnEnableZieglerFiles ), NULL, this );

	m_pages.Clear();
}


dialogSetup::dialogSetup( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerSetup;
	sizerSetup = new wxBoxSizer( wxVERTICAL );

	lineDefaultButtons = new wxStaticText( this, wxID_ANY, wxT("The Default Databases loaded during ERYA Profiling initialization are displayed here."), wxDefaultPosition, wxDefaultSize, 0 );
	lineDefaultButtons->Wrap( -1 );
	sizerSetup->Add( lineDefaultButtons, 0, wxALL|wxEXPAND, 5 );

	labelSetupTip = new wxStaticText( this, wxID_ANY, wxT("Use this tool to change the setup file, and reset if necessary."), wxDefaultPosition, wxDefaultSize, 0 );
	labelSetupTip->Wrap( -1 );
	sizerSetup->Add( labelSetupTip, 0, wxALL|wxEXPAND, 5 );

	wxString radioDefaultConfigChoices[] = { wxT("The default operating system profile folder"), wxT("At the same root program folder.") };
	int radioDefaultConfigNChoices = sizeof( radioDefaultConfigChoices ) / sizeof( wxString );
	radioDefaultConfig = new wxRadioBox( this, wxID_ANY, wxT("Store the ERYA-Profiling configuration file at..."), wxDefaultPosition, wxDefaultSize, radioDefaultConfigNChoices, radioDefaultConfigChoices, 1, wxRA_SPECIFY_COLS );
	radioDefaultConfig->SetSelection( 0 );
	sizerSetup->Add( radioDefaultConfig, 0, wxALL|wxEXPAND, 5 );

	lineDefaultFiles = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerSetup->Add( lineDefaultFiles, 0, wxEXPAND | wxALL, 5 );

	labelFilesInfo = new wxStaticText( this, wxID_ANY, wxT("Select the Default Databases"), wxDefaultPosition, wxDefaultSize, 0 );
	labelFilesInfo->Wrap( -1 );
	sizerSetup->Add( labelFilesInfo, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* sizerDefaultDatabase;
	sizerDefaultDatabase = new wxGridSizer( 3, 2, 0, 0 );

	labelDefaultDetector = new wxStaticText( this, wxID_ANY, wxT("Default Detector Setup File"), wxDefaultPosition, wxDefaultSize, 0 );
	labelDefaultDetector->Wrap( -1 );
	sizerDefaultDatabase->Add( labelDefaultDetector, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	fileDefaultDetector = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("ERYA-Profiling Detector Setup files"), wxT("*.epsd"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerDefaultDatabase->Add( fileDefaultDetector, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelDefaultDatabase = new wxStaticText( this, wxID_ANY, wxT("Default Elements Database File"), wxDefaultPosition, wxDefaultSize, 0 );
	labelDefaultDatabase->Wrap( -1 );
	sizerDefaultDatabase->Add( labelDefaultDatabase, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	fileDefaultDatabase = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("ERYA-Profiling Database Files"), wxT("*.epd"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerDefaultDatabase->Add( fileDefaultDatabase, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	labelDefaultZiegler = new wxStaticText( this, wxID_ANY, wxT("Default Ziegler Parameters File"), wxDefaultPosition, wxDefaultSize, 0 );
	labelDefaultZiegler->Wrap( -1 );
	sizerDefaultDatabase->Add( labelDefaultZiegler, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	fileDefaultZiegler = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("ERYA-Profiling Ziegler Parameters file"), wxT("*.epsz"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	sizerDefaultDatabase->Add( fileDefaultZiegler, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerSetup->Add( sizerDefaultDatabase, 1, wxEXPAND, 5 );

	lineSetupButton = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerSetup->Add( lineSetupButton, 0, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxGridSizer* sizerSetupButtons;
	sizerSetupButtons = new wxGridSizer( 1, 5, 0, 0 );

	buttonDefaultSave = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSetupButtons->Add( buttonDefaultSave, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDefaultReset = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSetupButtons->Add( buttonDefaultReset, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDefaultDelete = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSetupButtons->Add( buttonDefaultDelete, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonDefaultQuit = new wxButton( this, wxID_ANY, wxT("Quit"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSetupButtons->Add( buttonDefaultQuit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

    buttonDefaultHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSetupButtons->Add( buttonDefaultHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	sizerSetup->Add( sizerSetupButtons, 0, wxEXPAND, 5 );


	this->SetSizer( sizerSetup );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	buttonDefaultSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultSave ), NULL, this );
	buttonDefaultReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultReset ), NULL, this );
	buttonDefaultDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultDelete ), NULL, this );
	buttonDefaultQuit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultQuit ), NULL, this );
    buttonDefaultHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultHelp ), NULL, this );
}

dialogSetup::~dialogSetup()
{
	// Disconnect Events
	buttonDefaultSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultSave ), NULL, this );
	buttonDefaultReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultReset ), NULL, this );
	buttonDefaultDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultDelete ), NULL, this );
	buttonDefaultQuit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultQuit ), NULL, this );
    buttonDefaultHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogSetup::OnDefaultHelp ), NULL, this );
}



dialogR33DataImport::dialogR33DataImport( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerDataImport;
	sizerDataImport = new wxBoxSizer( wxVERTICAL );

	labelDataImportInfo = new wxStaticText( this, wxID_ANY, wxT("The imported file require some additional information to export correctly."), wxDefaultPosition, wxDefaultSize, 0 );
	labelDataImportInfo->Wrap( -1 );
	sizerDataImport->Add( labelDataImportInfo, 0, wxALL|wxEXPAND, 5 );

	lineDataImportInfo = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDataImport->Add( lineDataImportInfo, 0, wxEXPAND | wxALL, 5 );

	labelDataImportUnits = new wxStaticText( this, wxID_ANY, wxT("Select from the options below, the original units from the source file."), wxDefaultPosition, wxDefaultSize, 0 );
	labelDataImportUnits->Wrap( -1 );
	sizerDataImport->Add( labelDataImportUnits, 0, wxALL|wxEXPAND, 5 );

	wxString radioDataImportUnitsChoices[] = { wxT("MiliBarn (mb)"), wxT("Barn (b)") };
	int radioDataImportUnitsNChoices = sizeof( radioDataImportUnitsChoices ) / sizeof( wxString );
	radioDataImportUnits = new wxRadioBox( this, wxID_ANY, wxT("Select the Cross-Section Units"), wxDefaultPosition, wxDefaultSize, radioDataImportUnitsNChoices, radioDataImportUnitsChoices, 1, wxRA_SPECIFY_COLS );
	radioDataImportUnits->SetSelection( 0 );
	sizerDataImport->Add( radioDataImportUnits, 0, wxALL|wxEXPAND, 5 );

	wxString radioDataImportAngleChoices[] = { wxT("Esterradian (sr)"), wxT("Total Angle (tot)") };
	int radioDataImportAngleNChoices = sizeof( radioDataImportAngleChoices ) / sizeof( wxString );
	radioDataImportAngle = new wxRadioBox( this, wxID_ANY, wxT("Select the Cross-Section Angle Unit"), wxDefaultPosition, wxDefaultSize, radioDataImportAngleNChoices, radioDataImportAngleChoices, 1, wxRA_SPECIFY_COLS );
	radioDataImportAngle->SetSelection( 0 );
	sizerDataImport->Add( radioDataImportAngle, 0, wxALL|wxEXPAND, 5 );

	checkIgnoreNonNumericalData = new wxCheckBox( this, wxID_ANY, wxT("Ignore all lines with labels, or other non-numerical data columns."), wxDefaultPosition, wxDefaultSize, 0 );
	sizerDataImport->Add( checkIgnoreNonNumericalData, 0, wxALL|wxEXPAND, 5 );

	lineDataImportButtons = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDataImport->Add( lineDataImportButtons, 0, wxEXPAND | wxALL, 5 );

    wxGridSizer* sizerR33DataButtons;
	sizerR33DataButtons = new wxGridSizer( 1, 4, 0, 0 );

	buttonR33DataOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerR33DataButtons->Add( buttonR33DataOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonR33DataCancel = new wxButton( this, wxID_ANY, wxT("Default"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerR33DataButtons->Add( buttonR33DataCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonR33DataReset = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerR33DataButtons->Add( buttonR33DataReset, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonR33DataHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerR33DataButtons->Add( buttonR33DataHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	sizerDataImport->Add( sizerR33DataButtons, 0, wxEXPAND, 5 );


	this->SetSizer( sizerDataImport );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	buttonR33DataOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportValidate ), NULL, this );
	buttonR33DataCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportAbort ), NULL, this );
	buttonR33DataReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportReset ), NULL, this );
	buttonR33DataHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportHelp ), NULL, this );

}

dialogR33DataImport::~dialogR33DataImport()
{
	// Disconnect Events
	buttonR33DataOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportValidate ), NULL, this );
	buttonR33DataCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportAbort ), NULL, this );
	buttonR33DataReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportReset ), NULL, this );
	buttonR33DataHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogR33DataImport::OnDataImportHelp ), NULL, this );

}

dialogXlsxDataImport::dialogXlsxDataImport( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerDataImport;
	sizerDataImport = new wxBoxSizer( wxVERTICAL );

	labelDataImportInfo = new wxStaticText( this, wxID_ANY, wxT("The imported file require some additional information to import correctly."), wxDefaultPosition, wxDefaultSize, 0 );
	labelDataImportInfo->Wrap( -1 );
	sizerDataImport->Add( labelDataImportInfo, 0, wxALL|wxEXPAND, 5 );

	lineDataImportInfo = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDataImport->Add( lineDataImportInfo, 0, wxEXPAND | wxALL, 5 );

	labelDataImportUnits = new wxStaticText( this, wxID_ANY, wxT("Select from the options below, the original units from the source file."), wxDefaultPosition, wxDefaultSize, 0 );
	labelDataImportUnits->Wrap( -1 );
	sizerDataImport->Add( labelDataImportUnits, 0, wxALL|wxEXPAND, 5 );

	wxString radioDataImportUnitsChoices[] = { wxT("MiliBarn (mb)"), wxT("Barn (b)") };
	int radioDataImportUnitsNChoices = sizeof( radioDataImportUnitsChoices ) / sizeof( wxString );
	radioDataImportUnits = new wxRadioBox( this, wxID_ANY, wxT("Select the Cross-Section Units"), wxDefaultPosition, wxDefaultSize, radioDataImportUnitsNChoices, radioDataImportUnitsChoices, 1, wxRA_SPECIFY_COLS );
	radioDataImportUnits->SetSelection( 0 );
	sizerDataImport->Add( radioDataImportUnits, 0, wxALL|wxEXPAND, 5 );

	wxString radioDataImportAngleChoices[] = { wxT("Esterradian (sr)"), wxT("Total Angle (tot)") };
	int radioDataImportAngleNChoices = sizeof( radioDataImportAngleChoices ) / sizeof( wxString );
	radioDataImportAngle = new wxRadioBox( this, wxID_ANY, wxT("Select the Cross-Section Angle Unit"), wxDefaultPosition, wxDefaultSize, radioDataImportAngleNChoices, radioDataImportAngleChoices, 1, wxRA_SPECIFY_COLS );
	radioDataImportAngle->SetSelection( 0 );
	sizerDataImport->Add( radioDataImportAngle, 0, wxALL|wxEXPAND, 5 );

	wxString radioDataImportColumnChoices[] = { wxT("Automatic (Use the default 2 or 4-columns profile by program own guess)"), wxT("Override the first column for Energy, and second column for Cross-section"), wxT("Override the first column for Energy, and third column for Cross-section") };
	int radioDataImportColumnNChoices = sizeof( radioDataImportColumnChoices ) / sizeof( wxString );
	radioDataImportColumn = new wxRadioBox( this, wxID_ANY, wxT("Select the Importation Profile "), wxDefaultPosition, wxDefaultSize, radioDataImportColumnNChoices, radioDataImportColumnChoices, 1, wxRA_SPECIFY_COLS );
	radioDataImportColumn->SetSelection( 0 );
	sizerDataImport->Add( radioDataImportColumn, 0, wxALL|wxEXPAND, 5 );

	lineDataImportButtons = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerDataImport->Add( lineDataImportButtons, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerXlsxDataButtons;
	sizerXlsxDataButtons = new wxGridSizer( 1, 4, 0, 0 );

	buttonXlsxDataOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerXlsxDataButtons->Add( buttonXlsxDataOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonXlsxDataCancel = new wxButton( this, wxID_ANY, wxT("Default"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerXlsxDataButtons->Add( buttonXlsxDataCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonXlsxDataReset = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerXlsxDataButtons->Add( buttonXlsxDataReset, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonXlsxDataHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerXlsxDataButtons->Add( buttonXlsxDataHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	sizerDataImport->Add( sizerXlsxDataButtons, 0, wxEXPAND, 5 );


	this->SetSizer( sizerDataImport );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	buttonXlsxDataOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportValidate ), NULL, this );
	buttonXlsxDataCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportAbort ), NULL, this );
	buttonXlsxDataReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportReset ), NULL, this );
	buttonXlsxDataHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportHelp ), NULL, this );
}

dialogXlsxDataImport::~dialogXlsxDataImport()
{
	// Disconnect Events
	buttonXlsxDataOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportValidate ), NULL, this );
	buttonXlsxDataCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportAbort ), NULL, this );
	buttonXlsxDataReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportReset ), NULL, this );
	buttonXlsxDataHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogXlsxDataImport::OnDataImportHelp ), NULL, this );

}

dialogERYAProfilingAdvanced::dialogERYAProfilingAdvanced( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerERYAProfilingAdvanced;
	sizerERYAProfilingAdvanced = new wxBoxSizer( wxVERTICAL );

	labelERYAProfilingAdvanced = new wxStaticText( this, wxID_ANY, wxT("Use this tool to change the level of numerical accuracy for each setting below."), wxDefaultPosition, wxDefaultSize, 0 );
	labelERYAProfilingAdvanced->Wrap( -1 );
	sizerERYAProfilingAdvanced->Add( labelERYAProfilingAdvanced, 0, wxALL|wxEXPAND, 5 );

	lineERYAProfilingSettings = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerERYAProfilingAdvanced->Add( lineERYAProfilingSettings, 0, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* sizerERYAProfilingSettings;
	sizerERYAProfilingSettings = new wxFlexGridSizer( 7, 2, 20, 20 );
	sizerERYAProfilingSettings->AddGrowableRow( 0 );
	sizerERYAProfilingSettings->SetFlexibleDirection( wxBOTH );
	sizerERYAProfilingSettings->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	labelSampleStep = new wxStaticText( this, wxID_ANY, wxT("Sample Step in x*10^15 atm/cm^2"), wxDefaultPosition, wxDefaultSize, 0 );
	labelSampleStep->Wrap( -1 );
	sizerERYAProfilingSettings->Add( labelSampleStep, 0, wxALL, 5 );

	spinSampleStep = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 10 );
	sizerERYAProfilingSettings->Add( spinSampleStep, 0, wxALL, 5 );

	labelGaussPrecision = new wxStaticText( this, wxID_ANY, wxT("Number of Points for the Three-Sigma Range of Gauss Distribution:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelGaussPrecision->Wrap( -1 );
	sizerERYAProfilingSettings->Add( labelGaussPrecision, 0, wxALL, 5 );

	spinGaussPrecision = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 100, 60 );
	sizerERYAProfilingSettings->Add( spinGaussPrecision, 0, wxALL, 5 );

	labelVavilovMoyal = new wxStaticText( this, wxID_ANY, wxT("Number of Points per Lambda Step for Vavilov-Moyal Distribution:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelVavilovMoyal->Wrap( -1 );
	sizerERYAProfilingSettings->Add( labelVavilovMoyal, 0, wxALL, 5 );

	spinVavilovMoyal = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 20, 10 );
	sizerERYAProfilingSettings->Add( spinVavilovMoyal, 0, wxALL, 5 );

	labelVavilovEdgeworth = new wxStaticText( this, wxID_ANY, wxT("Number of Points for Main Range of Vavilov-Edgeworth Distribution:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelVavilovEdgeworth->Wrap( -1 );
	sizerERYAProfilingSettings->Add( labelVavilovEdgeworth, 0, wxALL, 5 );

	spinVavilovEdgeworth = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 100, 70 );
	sizerERYAProfilingSettings->Add( spinVavilovEdgeworth, 0, wxALL, 5 );

	labelLandau = new wxStaticText( this, wxID_ANY, wxT("Number of Points for Main Range of Landau Distribution:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelLandau->Wrap( -1 );
	sizerERYAProfilingSettings->Add( labelLandau, 0, wxALL, 5 );

	spinLandau = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 100, 500, 284 );
	sizerERYAProfilingSettings->Add( spinLandau, 0, wxALL, 5 );

        labelNumberThreads = new wxStaticText( this, wxID_ANY, wxT("Asymptotic Vavilov Variance Model:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelNumberThreads->Wrap( -1 );
	sizerERYAProfilingSettings->Add( labelNumberThreads, 0, wxALL, 5 );

	wxString spinNumberThreadsChoices[] = { wxT("Bohr Variance"), wxT("Vavilov Limit"), wxT("Gaussian Only") };
	int spinNumberThreadsNChoices = sizeof( spinNumberThreadsChoices ) / sizeof( wxString );
	spinNumberThreads = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, spinNumberThreadsNChoices, spinNumberThreadsChoices, 0 );
	spinNumberThreads->SetSelection( 1 );
	sizerERYAProfilingSettings->Add( spinNumberThreads, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	labelActiveLog = new wxStaticText( this, wxID_ANY, wxT("Enable partial Yield log table?"), wxDefaultPosition, wxDefaultSize, 0 );
	labelActiveLog->Wrap( -1 );
	sizerERYAProfilingSettings->Add( labelActiveLog, 0, wxALL, 5 );

    checkActiveLog = new wxCheckBox(this, wxID_ANY, wxT("Enable Log ?"), wxDefaultPosition, wxDefaultSize, 0);
    sizerERYAProfilingSettings->Add( checkActiveLog, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	sizerERYAProfilingAdvanced->Add( sizerERYAProfilingSettings, 0, wxEXPAND, 5 );

	lineERYAProfilingTools = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerERYAProfilingAdvanced->Add( lineERYAProfilingTools, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* sizerERYAProfilingTools;
	sizerERYAProfilingTools = new wxGridSizer( 1, 4, 0, 0 );

	buttonAdvancedOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAProfilingTools->Add( buttonAdvancedOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAdvancedCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAProfilingTools->Add( buttonAdvancedCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAdvancedDefault = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAProfilingTools->Add( buttonAdvancedDefault, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonAdvancedHelp = new wxButton( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerERYAProfilingTools->Add( buttonAdvancedHelp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	sizerERYAProfilingAdvanced->Add( sizerERYAProfilingTools, 1, wxEXPAND, 5 );


	this->SetSizer( sizerERYAProfilingAdvanced );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	buttonAdvancedOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedOK ), NULL, this );
	buttonAdvancedDefault->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedDefault ), NULL, this );
	buttonAdvancedCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedCancel ), NULL, this );
	buttonAdvancedHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedHelp ), NULL, this );
}

dialogERYAProfilingAdvanced::~dialogERYAProfilingAdvanced()
{
	// Disconnect Events
	buttonAdvancedOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedOK ), NULL, this );
	buttonAdvancedDefault->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedDefault ), NULL, this );
	buttonAdvancedCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedCancel ), NULL, this );
	buttonAdvancedHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( dialogERYAProfilingAdvanced::OnAdvancedHelp ), NULL, this );

}
