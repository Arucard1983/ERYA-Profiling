#include "ERYAProfilingdialogERYACalculator.h"
#include "ERYAProfilingdialogHelp.h"
#include "ParserLibrary.h"

ERYAProfilingdialogERYACalculator::ERYAProfilingdialogERYACalculator( wxWindow* parent )
:
dialogERYACalculator( parent )
{
 // Initialize the internal variables
 LastFyx = 0;
 LastAns = 0;
 DecimalPrecision = 10;
}

void ERYAProfilingdialogERYACalculator::OnAcos( wxCommandEvent& event )
{
 wxString data = wxT("acos(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnAsin( wxCommandEvent& event )
{
 wxString data = wxT("asin(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnAtan( wxCommandEvent& event )
{
  wxString data = wxT("atan(");
  textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnFxvar( wxCommandEvent& event )
{
  wxString data = wxT("fxvar =");
  textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnLeftParenthesis( wxCommandEvent& event )
{
 wxString data = wxT("(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnRightParenthesis( wxCommandEvent& event )
{
  wxString data = wxT(")");
  textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnSqrt( wxCommandEvent& event )
{
  wxString data = wxT("sqrt(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnPower( wxCommandEvent& event )
{
  wxString data = wxT("^");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnClearInput( wxCommandEvent& event )
{
 textCalculatorInput->Clear();
 LastFyx = 0;
}

void ERYAProfilingdialogERYACalculator::OnAcosh( wxCommandEvent& event )
{
  wxString data = wxT("acosh(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnAsinh( wxCommandEvent& event )
{
  wxString data = wxT("asinh(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnAtanh( wxCommandEvent& event )
{
  wxString data = wxT("atanh(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnFyvar( wxCommandEvent& event )
{
  wxString data = wxT("fyvar =");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnSeven( wxCommandEvent& event )
{
  wxString data = wxT("7");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnEight( wxCommandEvent& event )
{
  wxString data = wxT("8");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnNine( wxCommandEvent& event )
{
  wxString data = wxT("9");
  textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnPlus( wxCommandEvent& event )
{
  wxString data = wxT("+");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnClearOutput( wxCommandEvent& event )
{
 textCalculatorOutput->Clear();
 LastAns = 0;
}

void ERYAProfilingdialogERYACalculator::OnCos( wxCommandEvent& event )
{
  wxString data = wxT("cos(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnSin( wxCommandEvent& event )
{
  wxString data = wxT("sin(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnTan( wxCommandEvent& event )
{
  wxString data = wxT("tan(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnFxmin( wxCommandEvent& event )
{
  wxString data = wxT("fxmin =");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnFour( wxCommandEvent& event )
{
  wxString data = wxT("4");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnFive( wxCommandEvent& event )
{
  wxString data = wxT("5");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnSix( wxCommandEvent& event )
{
  wxString data = wxT("6");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnMinus( wxCommandEvent& event )
{
  wxString data = wxT("-");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnComma( wxCommandEvent& event )
{
  wxString data = wxT(",");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnCosh( wxCommandEvent& event )
{
  wxString data = wxT("cosh(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnSinh( wxCommandEvent& event )
{
  wxString data = wxT("sinh(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnTanh( wxCommandEvent& event )
{
  wxString data = wxT("tanh(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnFxmax( wxCommandEvent& event )
{
  wxString data = wxT("fxmax =");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnOne( wxCommandEvent& event )
{
  wxString data = wxT("1");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnTwo( wxCommandEvent& event )
{
  wxString data = wxT("2");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnThree( wxCommandEvent& event )
{
  wxString data = wxT("3");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnTimes( wxCommandEvent& event )
{
  wxString data = wxT("*");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnColon( wxCommandEvent& event )
{
  wxString data = wxT(":");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnExp( wxCommandEvent& event )
{
  wxString data = wxT("exp(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnLog( wxCommandEvent& event )
{
  wxString data = wxT("log(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnLn( wxCommandEvent& event )
{
  wxString data = wxT("ln(");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnFunctionVar( wxCommandEvent& event )
{
 wxTextEntryDialog *dialog = new wxTextEntryDialog(this,wxT("Value of x=... at "),wxT("Evaluate f(x), at x=?"),wxEmptyString); //Input variable value
 if (dialog->ShowModal() == wxID_OK)
 {
 double fdata;
 wxString data = dialog->GetValue();
  if(data.ToDouble(&fdata))
  {
   AlgebraicFunction *fx = new AlgebraicFunction(textCalculatorInput->GetValue()); // Compile the user defined function
   if(fx->GetErrorString().Len()>0)
   {
    textCalculatorOutput->SetValue(fx->GetErrorString()); //Error due to syntax errors
   }
   else
   {
    if(fx->IsFunctionDefined())
    {
     textCalculatorOutput->SetValue(this->GetConversion(fx->GetFyxEval(fdata),false)); // Get the y = f(x) value
     LastFyx = fx->GetFyxEval(fdata);
    }
    else
    {
      textCalculatorOutput->SetValue(wxT("Declaration Error: The function is not defined.")); // Error due to non-defined function
    }
   }
   delete fx;
  }
  else
  {
   textCalculatorOutput->SetValue(wxT("Declaration Error: Expected a numerical value for function variable.")); // Error due to non-numeric input.
  }
 }
 delete dialog;
}

void ERYAProfilingdialogERYACalculator::OnZero( wxCommandEvent& event )
{
  wxString data = wxT("0");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnDecimal( wxCommandEvent& event )
{
  wxString data = wxT(".");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnExponential( wxCommandEvent& event )
{
  wxString data = wxT("E");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnDivide( wxCommandEvent& event )
{
  wxString data = wxT("/");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnReturn( wxCommandEvent& event )
{
 AlgebraicFunction *fx = new AlgebraicFunction(textCalculatorInput->GetValue());
 if(fx->GetErrorString().Len()>0)
 {
  textCalculatorOutput->SetValue(fx->GetErrorString());
 }
 else
 {
  textCalculatorOutput->SetValue(this->GetConversion(fx->GetAnsEval(),false));
  LastAns = fx->GetAnsEval();
 }
 delete fx;
}

void ERYAProfilingdialogERYACalculator::OnHelp( wxCommandEvent& event )
{
 ERYAProfilingdialogHelp* help = new ERYAProfilingdialogHelp(this,wxT("Calculator.html"));
 help->ShowModal();
}

void ERYAProfilingdialogERYACalculator::OnBackSpace( wxCommandEvent& event )
{
 textCalculatorInput->Remove(textCalculatorInput->GetLastPosition()-1,textCalculatorInput->GetLastPosition());
}

void ERYAProfilingdialogERYACalculator::OnAssign( wxCommandEvent& event )
{
 wxString data = wxT(" = ");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnDisplayProgram( wxCommandEvent& event )
{
 textCalculatorInput->Clear();
 wxString data = wxT("FxAns = ") + this->GetConversion(LastFyx,false);
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnDisplayAnswer( wxCommandEvent& event )
{
 textCalculatorInput->Clear();
 wxString data = wxT("Ans = ") + this->GetConversion(LastAns,false);
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnLess( wxCommandEvent& event )
{
  wxString data = wxT("<");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnMore( wxCommandEvent& event )
{
 wxString data = wxT(">");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnVectorMacro( wxCommandEvent& event )
{
 wxString data = wxT("fnvar");
 textCalculatorInput->WriteText(data);
}

void ERYAProfilingdialogERYACalculator::OnSetDecimals( wxCommandEvent& event )
{
 wxNumberEntryDialog *decimal = new wxNumberEntryDialog(this,wxT("Define the number of decimal numbers that ERYA calculator should handle:"), wxT("Number of Decimal Digits"), wxT("ERYA Precision Settings"),10,6,15);
 if(decimal->ShowModal() == wxID_OK)
 {
  long temp = decimal->GetValue();
  DecimalPrecision = static_cast<int>(temp);
 }
 delete decimal;
}

void ERYAProfilingdialogERYACalculator::OnInputVariable( wxCommandEvent& event )
{
 wxTextEntryDialog *dialog = new wxTextEntryDialog(this,wxT("Variable Name ?"),wxT("Insert a valid variable name"),wxEmptyString); //Expect a valid variable
 if (dialog->ShowModal() == wxID_OK)
 {
 wxString data = dialog->GetValue();
  AlgebraicFunction *fx = new AlgebraicFunction(data+wxT("=0")); // Test the variable compatibility
  double test = fx->GetAnsEval();
  if(fx->GetErrorString().Len()>0)
   {
    textCalculatorOutput->SetValue(fx->GetErrorString() + wxT(" : Invalid Variable Name")); //Error due to syntax errors
   }
  else if (fx->GetOnlyConstants().GetCount() != 1)
  {
    textCalculatorOutput->SetValue(wxT("Declaration Error : Invalid Variable Name")); //Error due to syntax errors
  }
  else
  {
    textCalculatorInput->SetValue(data + wxT(" = ")); //Valid variable
  }
 }
 delete dialog;
}

wxString ERYAProfilingdialogERYACalculator::GetConversion(double Var, bool Sci)
{
  wxString NumberDecimalDigits = wxString::Format("%i",DecimalPrecision); //Convert the decimal points precision as a string.
  if((std::abs(Var) < 0.01) || (std::abs(Var) > 1e+10))
    Sci = true; // Override the scientific notation for large or small numbers.
  wxString NumberFormat;
  if (Sci)
    NumberFormat = wxT("%.") + NumberDecimalDigits + wxT("e");
  else
    NumberFormat = wxT("%.") + NumberDecimalDigits + wxT("f");
  // Return the number format
  return wxString::Format(NumberFormat,Var);
}
