#ifndef __ERYAProfilingERYAProfilingMain__
#define __ERYAProfilingERYAProfilingMain__

/**
@file
Subclass of ERYAProfilingMain, which is generated by wxFormBuilder.
*/

#include "ERYAProfiling.h"
#include "DatabaseLibrary.h"
#include "FileLibrary.h"
#include "PlotLibrary.h"
#include "XlsxLibrary.h"
#include "ReactionYield.h"

//// end generated include
class MainThread;

/** Implementing ERYAProfilingMain */
class ERYAProfilingERYAProfilingMain : public ERYAProfilingMain
{
	protected:
		// Handlers for ERYAProfilingMain events.
		void OnFileNew( wxCommandEvent& event );
		void OnFileOpen( wxCommandEvent& event );
		void OnFileSave( wxCommandEvent& event );
		void OnFileSaveAs( wxCommandEvent& event );
		void OnFileQuit( wxCommandEvent& event );
		void OnDatabaseDetector( wxCommandEvent& event );
		void OnDatabaseElements( wxCommandEvent& event );
		void OnDatabaseZiegler( wxCommandEvent& event );
		void OnSetupDefault( wxCommandEvent& event );
		void OnSetupReset( wxCommandEvent& event );
		void OnSRIMImport( wxCommandEvent& event );
		void OnLabViewImport( wxCommandEvent& event );
		void OnCalculator( wxCommandEvent& event );
		void OnHelpAbout( wxCommandEvent& event );
		void OnNumberElementSpin( wxSpinEvent& event );
		void OnNumberElementEnter( wxCommandEvent& event );
		void OnElementClear( wxCommandEvent& event );
		void OnElementLoad( wxCommandEvent& event );
		void OnElementSave( wxCommandEvent& event );
		void OnElementHelp( wxCommandEvent& event );
		void OnElementNameChoice( wxCommandEvent& event );
		void OnGammaPeakChoice( wxCommandEvent& event );
		void OnNumberLayerSpin( wxSpinEvent& event );
		void OnNumberLayerEnter( wxCommandEvent& event );
		void OnLayerClear( wxCommandEvent& event );
		void OnLayerLoad( wxCommandEvent& event );
		void OnLayerSave( wxCommandEvent& event );
		void OnLayerHelp( wxCommandEvent& event );
		void OnDetectorClear( wxCommandEvent& event );
		void OnDetectorReset( wxCommandEvent& event );
		void OnDetectorFunction( wxCommandEvent& event );
		void OnDetectorLoad( wxCommandEvent& event );
		void OnDetectorSave( wxCommandEvent& event );
		void OnDetectorHelp( wxCommandEvent& event );
		void OnRessonanceRange( wxCommandEvent& event );
		void OnRessonanceRange1( wxCommandEvent& event );
		void OnRessonanceOption( wxCommandEvent& event );
		void OnOutputData( wxCommandEvent& event );
		void OnOutputImage( wxCommandEvent& event );
		void OnOutputHelp( wxCommandEvent& event );
        void OnImportData( wxCommandEvent& event );
		void OnTableSave( wxCommandEvent& event );
		void OnTableHelp( wxCommandEvent& event );
		void OnLogViewer( wxCommandEvent& event );
		void OnLogSave( wxCommandEvent& event );
		void OnLogHelp( wxCommandEvent& event );
		void OnMainNew( wxCommandEvent& event );
		void OnMainCheck( wxCommandEvent& event );
		void OnMainAdvanced( wxCommandEvent& event );
		void OnMainRun( wxCommandEvent& event );
		void OnMainHelp( wxCommandEvent& event );
		void OnMainSave( wxCommandEvent& event );



        // Local Variables
		DetectorParameters CurrentDetectorParameters; // Local Detector Setup
		ZieglerParameters CurrentZieglerParameters; // Local Ziegler Setup
        ElementDatabaseArray OpenDatabase; // Local Default database
        ElementSRIMArray CurrentSRIMTables; // Local SRIM Tables database
        wxString CurrentConfig,CurrentDetectorFile,CurrentDatabaseFile,CurrentZieglerFile; //Default Database Directory
        bool DisplayExternalOutput;
        bool ResetDatabase; //Refresh flag
        bool CloseProgram; //Refresh flag
        bool AcceptSync;
        bool DefaultSetting;
        bool EnableLog;
        int RessonanceMode;
        unsigned int SamplePrecision, LandauPrecision, VavilovEdgeworthPrecision, VavilovMoyalPrecision, VavilovAiryPrecision, GaussPrecision, ThreadPrecision, ConvolutionPrecision;

	public:
		/** Constructor */
		ERYAProfilingERYAProfilingMain( wxWindow* parent );
	//// end generated class members

                // Local Functions
        void SaveDetector(DetectorParameters ThisDetector) { CurrentDetectorParameters = ThisDetector; return;}  // Safe storing method
        void SaveZiegler(ZieglerParameters ThisZiegler) { CurrentZieglerParameters = ThisZiegler; return;}  // Safe storing method
        void SaveDatabase(ElementDatabaseArray ThisDatabase) { OpenDatabase = ThisDatabase; return;}  // Safe storing method
        void SaveSRIM(ElementSRIMArray ThisSRIM) {CurrentSRIMTables = ThisSRIM; return;} // Safe storing method
        void RefreshDatabase(bool ResetAction) { ResetDatabase = ResetAction; return;}  // Safe storing method
        void ProgramQuit(bool QuitFlag) { CloseProgram = QuitFlag; return;}  // Safe storing method
        void GetDatabase(ElementDatabaseArray& ThisDatabase) { ThisDatabase = OpenDatabase; return;}  // Safe sync method
        void GetDetector(DetectorParameters& ThisDetector) { ThisDetector = CurrentDetectorParameters; return;}  // Safe sync method
        void GetZiegler(ZieglerParameters& ThisZiegler) { ThisZiegler = CurrentZieglerParameters; return;}  // Safe sync method
        void GetSRIM(ElementSRIMArray& ThisSRIM) {ThisSRIM = CurrentSRIMTables; return;} // Safe storing method
        void GetConfig(wxString& ThisConfig) { ThisConfig = CurrentConfig; return;}  // Safe sync method
        void GetDetectorFileName(wxString& ThisDFN) { ThisDFN = CurrentDetectorFile; return;}  // Safe sync method
        void GetDatabaseFileName(wxString& ThisEFN) { ThisEFN = CurrentDatabaseFile; return;}  // Safe sync method
        void GetZieglerFileName(wxString& ThisZFN) { ThisZFN = CurrentZieglerFile; return;}  // Safe sync method
        void SetConfig(wxString ThisConfig) { CurrentConfig = ThisConfig; return;}  // Safe sync method
        void SetDetectorFileName(wxString ThisDFN) { CurrentDetectorFile = ThisDFN; return;}  // Safe sync method
        void SetDatabaseFileName(wxString ThisEFN) { CurrentDatabaseFile = ThisEFN; return;}  // Safe sync method
        void SetZieglerFileName(wxString ThisZFN) {  CurrentZieglerFile  = ThisZFN; return;}  // Safe sync method
        void SetSync(bool flag){AcceptSync = flag; return;}
        void SetDefault(bool flag){DefaultSetting = flag; return;}
	    bool IsDetectorEmpty(DetectorParameters ThisDetector) { return !(ThisDetector.GetDetectorEnergy().GetCount() > 0 || ThisDetector.GetDetectorFunction().Len()>0); }  // Check if Detector Setup are empty
	    bool IsZieglerEmpty(ZieglerParameters ThisZiegler) { return !(ThisZiegler.GetZieglerElements().GetCount() > 0);  }  // Check if Ziegler Setup are empty
        bool IsDatabaseEmpty(ElementDatabaseArray ThisDatabase) { return !(ThisDatabase.GetCount() > 0);  }  // Check if the Database are empty
        void GetPrecisionParameters(unsigned int& CP, unsigned int& G, unsigned int& VM, unsigned int& VE, unsigned int& VA, unsigned int& L, unsigned int& NT, unsigned int& CM, bool& EL){CP = SamplePrecision; G = GaussPrecision; VM = VavilovMoyalPrecision; VE = VavilovEdgeworthPrecision; VA = VavilovAiryPrecision; L = LandauPrecision; NT = ThreadPrecision; CM = ConvolutionPrecision; EL = EnableLog; return;};
	    void SetPrecisionParameters(unsigned int CP, unsigned int G, unsigned int VM, unsigned int VE, unsigned int VA, unsigned int L, unsigned int NT, unsigned int CM, bool EL){SamplePrecision = CP; GaussPrecision = G; VavilovMoyalPrecision = VM; VavilovEdgeworthPrecision = VE; VavilovAiryPrecision = VA; LandauPrecision = L; ThreadPrecision = NT; ConvolutionPrecision = CM; EnableLog = EL; return;};
	    void CloseExternalOutput(bool Flag){DisplayExternalOutput = Flag; return;}
	    void GenerateLayer(int Number);
        void GenerateLayer();
        void GenerateCleanLayer();
        void GenerateNewLayer(int Number);
        void GenerateCleanTable(int Number);
        void GenerateCleanTable();
        void GenerateTable(int Number);
        void GenerateTable();
        void GenerateLog(int Number);
        void GenerateLog();
        void GenerateResult(int Number);
        void GenerateResult();
        bool StartUpProgram();
        bool StartUpDatabases(wxString MainDirectory, wxString MainDetector, wxString MainDatabase, wxString MainZiegler);
        bool StartUpDatabases();
        bool LoadSetupFile(wxString& MainDirectory, wxString& MainDetector, wxString& MainDatabase, wxString& MainZiegler);
        bool SaveSetupFile(wxString MainDirectory, wxString MainDetector, wxString MainDatabase, wxString MainZiegler, bool LocalSetting);
        bool DeleteSetupFile();
        bool ReplaceSetupFile();


};


#endif // __ERYAProfilingERYAProfilingMain__
