#include "SpecialFunctionsLibrary.h"

// Evaluate the value of a Hermite polynomial.
double HermitePolynomial::H(unsigned int Grade, double Argument)
{
 // Recurrence Hermite Polynomial:
 // For n>=2: H_{n}(x) = x * H_{n-1}(x) - (n-1) * H_{n-2}(x)
 // And n=0 : H_{0} = 1 ; n = 1 : H_{1} = x
 if(Grade == 0)
  return 1;
 else if (Grade == 1)
  return Argument;
 else
  return Argument * this->H(Grade-1,Argument) - (Grade - 1 ) * this->H(Grade-2,Argument);
}

// Evaluate the value of a Chebyshev polynomial.
double ChebyshevPolynomial::T(unsigned int Grade, double Argument)
{
 // Recurrence Chebyshev Polynomial:
 // For n>=2: T_{n}(x) = 2 * x * T_{n-1}(x) - T_{n-2}(x)
 // And n=0 : T_{0} = 1 ; n = 1 : T_{1} = x
 if(Grade == 0)
  return 1;
 else if (Grade == 1)
  return Argument;
 else
  return 2 * Argument * this->T(Grade-1,Argument) - this->T(Grade-2,Argument);
}

// Evaluate the value of the Laudau function
double LandauFunction::L(double lambda)
{
// Wilkinson interpolation formula.
 if(lambda<=-3.4)
 {
  return 0;
 }
 else if (lambda > -3.4 && lambda <= -1)
 {
  double f = (1/std::sqrt(4*std::acos(0)))*std::exp((std::abs(lambda)-1)/2 - exp(std::abs(lambda)-1));
  double g = 1 + 0.01*(6.7853 + 4.884*lambda + 1.4488*std::pow(lambda,2) + 0.20802*std::pow(lambda,3) + 0.012057*std::pow(lambda,4));
  return (f*g > 0) ? f*g : 0.0;
 }
 else if (lambda >-1 && lambda <=3)
 {
  double f = 0.17885481 - 0.015464468 * lambda - 0.030040482 * std::pow(lambda,2) + 0.013781358 * std::pow(lambda,3) - 0.0011491556 * std::pow(lambda,4) - 0.0012835837 * std::pow(lambda,5) + 0.00062395162 * std::pow(lambda,6) - 0.0001262613 * std::pow(lambda,7) + 0.000010108918 * std::pow(lambda,8);
  return (f > 0) ? f : 0.0;
 }
 else if (lambda > 3 && lambda <= 150)
 {
  double x = std::log(lambda);
  double f = std::exp(-1.5669876 - 1.5811676 * x + 1.677088 * std::pow(x,2) - 1.4972908 * std::pow(x,3) + 0.57062974 * std::pow(x,4) - 0.11777036 * std::pow(x,5) + 0.01343737 * std::pow(x,6) - 0.00076315158 * std::pow(x,7) + 0.000014881108 * std::pow(x,8));
  return (f > 0) ? f : 0.0;
 }
 else if (lambda > 150)
 {
  double x = std::log(lambda);
  double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
  double g = std::pow(lambda,-2) - ( 3 - 2 * euler - 2 * x) * std::pow(lambda,-3);
  double f = 1 - 0.01 * std::exp(5.157 - 1.42 * x);
  return (g/f > 0) ? g/f : 0.0;
 }
 else
 {
  return 0; //No valid argument
 }
}

// Define the default function domain
void LandauFunction::SetLandauStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative)
{
 // Function domain in terms of lambda
 double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
 double lambdalow = -3.4;
 double lambdahigh = 25;
 double lambdastep = (lambdahigh - lambdalow)/numberstep;
 // Function domain in terms of energy, using the Landau's variable E = xi(lambda - lambda_M) + DEM , where lambda_M = -1 + euler - beta^2 - log(k)
 LandauStep = xi * lambdastep;
 LandauMinimum = xi * (lambdalow + 1 - euler + beta*beta + std::log(k)) + DEM;
 LandauMaximum = xi * (lambdahigh + 1 - euler + beta*beta + std::log(k)) + DEM;
 LandauEnergy = DEM;
 LandauXi = xi;
 LandauBeta = beta;
 LandauK = k;
 // Cut energy loss greater than average
 if((LandauMinimum < 0) && TrimNegative)
 {
  LandauMinimum = 0;
 }
 return;
}

double LandauFunction::GetValue(double AtEnergy)
{
 double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
 double EnergyLambda = (AtEnergy - LandauEnergy)/LandauXi - 1 + euler - LandauBeta*LandauBeta - std::log(LandauK);
 return this->L(EnergyLambda);
}

// Auxiliary private functions
double VavilovEdgeworthFunction::VEalpha(unsigned int n)
{
 double alpha = (std::pow(VExi,n)/std::pow(VEk,n-1)) * ( (1 / ( n - 1)) - (VEbeta * VEbeta) / n);
 return alpha;
}

double VavilovEdgeworthFunction::VEmu(unsigned int n)
{
 if (n==0)
  return 1;
 else if (n==1)
  return 0;
 else if (n==2)
  return this->VEalpha(2);
 else if (n==3)
  return this->VEalpha(3);
 else if (n==4)
  return 3 * this->VEalpha(2) * this->VEalpha(2) + this->VEalpha(4);
 else if (n==5)
  return 10 * this->VEalpha(2) * this->VEalpha(3) + this->VEalpha(5);
 else
  return 0;
}

// Evaluate the value of the Vavilov distribution by the Edgeworth approximation
double VavilovEdgeworthFunction::VE(double delta, double xi, double beta, double k)
{
 // Initialize global variables
 double pi = 2 * std::acos(0);
 double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
 VExi = xi;
 VEk = k;
 VEbeta = beta;
 VEdelta = delta;
 VEStdDev = std::sqrt(this->VEmu(2));
 // Evaluate the function
 HermitePolynomial h;
 double gauss = (1 / std::sqrt(2 * pi * VEStdDev * VEStdDev)) * std::exp((-1 * VEdelta * VEdelta) / (2 * VEStdDev * VEStdDev));
 double edgeworth3 = (1 / 6) * (this->VEmu(3) / std::pow(VEStdDev,3)) * h.GetValue(3,VEdelta/VEStdDev);
 double edgeworth4 = (1 / 24) * (this->VEmu(4) / std::pow(VEStdDev,4) - 3) * h.GetValue(4,VEdelta/VEStdDev);
 double edgeworth5 = (1 / 120) * ((this->VEmu(5) / std::pow(VEStdDev,5)) - 10 * (this->VEmu(3) / std::pow(VEStdDev,3))) * h.GetValue(5,VEdelta/VEStdDev);
 double edgeworth6 = (1 / 72) * std::pow(this->VEmu(3) / std::pow(VEStdDev,3),2) * h.GetValue(6,VEdelta/VEStdDev);
 double edgeworth7 = (1 / 144) * (this->VEmu(3) / std::pow(VEStdDev,3)) * (this->VEmu(4) / std::pow(VEStdDev,4) - 3) * h.GetValue(7,VEdelta/VEStdDev);
 double edgeworth9 = (1 / 1296) * std::pow( this->VEmu(3) / std::pow(VEStdDev,3) , 3) * h.GetValue(9,VEdelta/VEStdDev);
 double edgeworth = 1 + edgeworth3 + edgeworth4 + edgeworth5 + edgeworth6 + edgeworth7 + edgeworth9;
 double f = gauss * edgeworth;
 return (f > 0) ? f : 0.0;
}

// Define the distribution domain
void VavilovEdgeworthFunction::SetEdgeworthStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative)
{
 // The integral domain may be evaluated from k and beta parameters
 double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
 VExi = xi;
 VEk = k;
 VEbeta = beta;
 VEDEM = DEM;
 double lowlambda = (-0.0322 * VEbeta * VEbeta - 0.0743)*VEk + (-0.2453 * VEbeta * VEbeta + 0.0701)/std::sqrt(VEk) + (-0.5561 * VEbeta * VEbeta - 3.1579);
 double highlambda = (-0.0135 * VEbeta * VEbeta - 0.0488)*VEk + (-1.6921 * VEbeta * VEbeta + 8.3656)/std::sqrt(VEk) + (-0.7327 * VEbeta * VEbeta - 3.5226);
 double lambdastep = (highlambda - lowlambda)/numberstep;
 // Define the Function Domain
 EdgeworthStep = VExi * lambdastep;
 EdgeworthMinimum = VExi * (lowlambda + 1 - euler + VEbeta*VEbeta + std::log(VEk)) + DEM;
 EdgeworthMaximum = VExi * (highlambda + 1 - euler + VEbeta*VEbeta + std::log(VEk)) + DEM;
 // Cut energy loss greater than average
 if((EdgeworthMinimum < 0) && TrimNegative)
 {
  EdgeworthMinimum = 0;
 }
 return;
}

double VavilovEdgeworthFunction::GetValue(double AtEnergy)
{
 VEdelta = AtEnergy - VEDEM;
 return this->VE(VEdelta,VExi,VEbeta,VEk);
}

// Moyal auxiliary functions
double VavilovMoyalFunction::VMbeta(double beta)
{
 double betamin,betamax,betabar;
 if(beta>=0 && beta<=1)
 {
   betamin = 0.05; betamax = 1.0;
 }
 else
 {
   return 0;
 }
 betabar = 1 + 2 * (beta - betamax) / (betamax - betamin);
 return betabar;
}

double VavilovMoyalFunction::VMk(double k)
{
 double kmin,kmax,kbar;
 if(k>=0.02 && k<0.11)
 {
   kmin = 0.02; kmax = 0.10;
 }
 else if(k>=0.11 && k<0.22)
 {
   kmin = 0.114; kmax = 0.20;
 }
 else if(k>=0.22 && k<0.30)
 {
   kmin = 0.22; kmax = 0.30;
 }
 else
 {
  return 0;
 }
 kbar = 1 + 2 * (k - kmax) / (kmax - kmin) ;
 return kbar;
}

// Moyal Parameters. (An hard-coded table that is loaded by the class constructor)
void VavilovMoyalFunction::MakeTable()
{
 VMT[0][0][0] = 0; VMT[0][0][1] = 0; VMT[0][0][2] = 0.25850874; VMT[0][0][3] = 0.43142617; VMT[0][0][4] = 0.25225964; VMT[0][0][5] = 1.2593243; VMT[0][0][6] = -0.024864376; VMT[0][0][7] = 0.035855696; VMT[0][0][8] = 10.234692; VMT[0][0][9] = 21.487522;
 VMT[0][1][0] = 0; VMT[0][1][1] = 1; VMT[0][1][2] = 0.024880692; VMT[0][1][3] = 0.042127077; VMT[0][1][4] = 0.023834176; VMT[0][1][5] = -0.046865180; VMT[0][1][6] = 0.0018751903; VMT[0][1][7] = -0.00084479939; VMT[0][1][8] = -1.9952390; VMT[0][1][9] = -3.4343169;
 VMT[0][2][0] = 0; VMT[0][2][1] = 2; VMT[0][2][2] = 0.0047404356; VMT[0][2][3] = 0.0073167928; VMT[0][2][4] = 0.0021624675; VMT[0][2][5] = -0.0077222986; VMT[0][2][6] = 0.0012668869; VMT[0][2][7] = 0; VMT[0][2][8] = -0.45679694; VMT[0][2][9] = -1.1063164;
 VMT[0][3][0] = 0; VMT[0][3][1] = 3; VMT[0][3][2] = -0.00074445130; VMT[0][3][3] = -0.0014026047; VMT[0][3][4] = -0.0026865597; VMT[0][3][5] = 0.0032241039; VMT[0][3][6] = -0.00048736023; VMT[0][3][7] = -0.00045675843; VMT[0][3][8] = 0; VMT[0][3][9] = -0.21000819;
 VMT[0][4][0] = 1; VMT[0][4][1] = 0; VMT[0][4][2] = 0.032477982; VMT[0][4][3] = 0.040797543; VMT[0][4][4] = 0.064820468; VMT[0][4][5] = -0.20374501; VMT[0][4][6] = -0.0010368495; VMT[0][4][7] = -0.027542114; VMT[0][4][8] = -3.5619655; VMT[0][4][9] = -11.825253;
 VMT[0][5][0] = 1; VMT[0][5][1] = 1; VMT[0][5][2] = 0.0073225731; VMT[0][5][3] = 0.016195241; VMT[0][5][4] = -0.0054891384; VMT[0][5][5] = 0.0089882920; VMT[0][5][6] = 0.0034850854; VMT[0][5][7] = -0.0069836141; VMT[0][5][8] = 0.50505298; VMT[0][5][9] = 1.7891643;
 VMT[0][6][0] = 1; VMT[0][6][1] = 2; VMT[0][6][2] = 0; VMT[0][6][3] = 0; VMT[0][6][4] = -0.0089439554; VMT[0][6][5] = 0.018786468; VMT[0][6][6] = 0.0019372124; VMT[0][6][7] = 0; VMT[0][6][8] = 0; VMT[0][6][9] = 0.73410606;
 VMT[0][7][0] = 1; VMT[0][7][1] = 3; VMT[0][7][2] = -0.0015727318; VMT[0][7][3] = -0.0025141668; VMT[0][7][4] = -0.0062756944; VMT[0][7][5] = 0.014484097; VMT[0][7][6] = 0.00070761825; VMT[0][7][7] = 0.0015298434; VMT[0][7][8] = 0; VMT[0][7][9] = 0;
 VMT[0][8][0] = 2; VMT[0][8][1] = 0; VMT[0][8][2] = -0.0059020496; VMT[0][8][3] = -0.0091490215; VMT[0][8][4] = -0.023615759; VMT[0][8][5] = 0.095055662; VMT[0][8][6] = 0.0014330117; VMT[0][8][7] = 0.012631023; VMT[0][8][8] = 0.69387764; VMT[0][8][9] = 4.3133087;
 VMT[0][9][0] = 2; VMT[0][9][1] = 1; VMT[0][9][2] = 0; VMT[0][9][3] = 0.0024714789; VMT[0][9][4] = 0.0039800522; VMT[0][9][5] = -0.0067167236; VMT[0][9][6] = 0; VMT[0][9][7] = 0.0039876546; VMT[0][9][8] = 0; VMT[0][9][9] = -0.89601916;
 VMT[0][10][0] = 2; VMT[0][10][1] = 2; VMT[0][10][2] = -0.0011210142; VMT[0][10][3] = -0.0014064022; VMT[0][10][4] = -0.0024655436; VMT[0][10][5] = 0; VMT[0][10][6] = 0.00046898375; VMT[0][10][7] = 0.0019247256; VMT[0][10][8] = 0; VMT[0][10][9] = -0.32454506;
 VMT[0][11][0] = 3; VMT[0][11][1] = 0; VMT[0][11][2] = 0; VMT[0][11][3] = 0; VMT[0][11][4] = 0; VMT[0][11][5] = -0.020771531; VMT[0][11][6] = 0.00020052730; VMT[0][11][7] = -0.0030188807; VMT[0][11][8] = -0.14047599; VMT[0][11][9] = -1.4500543;
 VMT[0][12][0] = 3; VMT[0][12][1] = 1; VMT[0][12][2] = 0.0011668284; VMT[0][12][3] = 0.0020751278; VMT[0][12][4] = 0.0048447456; VMT[0][12][5] = -0.013049241; VMT[0][12][6] = -0.00036597173; VMT[0][12][7] = -0.0036055679; VMT[0][12][8] = 0; VMT[0][12][9] = 0.39120793;
 VMT[1][0][0] = 0; VMT[1][0][1] = 0; VMT[1][0][2] = 0.27827257; VMT[1][0][3] = 0.41421789; VMT[1][0][4] = 0.20191059; VMT[1][0][5] = 1.3206085; VMT[1][0][6] = 0.016435245; VMT[1][0][7] = 0.033432409; VMT[1][0][8] = 5.4529572; VMT[1][0][9] = 9.3841352;
 VMT[1][1][0] = 0; VMT[1][1][1] = 1; VMT[1][1][2] = 0.045091424; VMT[1][1][3] = 0.12693873; VMT[1][1][4] = 0.053921588; VMT[1][1][5] = -0.14986093; VMT[1][1][6] = -0.010775802; VMT[1][1][7] = -0.013346861; VMT[1][1][8] = -1.2218009; VMT[1][1][9] = -1.8160479;
 VMT[1][2][0] = 0; VMT[1][2][1] = 2; VMT[1][2][2] = 0.0080559636; VMT[1][2][3] = 0.022999801; VMT[1][2][4] = 0.0035068740; VMT[1][2][5] = -0.012720568; VMT[1][2][6] = 0.0051476061; VMT[1][2][7] = -0.0017402116; VMT[1][2][8] = -0.32324120; VMT[1][2][9] = -0.50919193;
 VMT[1][3][0] = 0; VMT[1][3][1] = 3; VMT[1][3][2] = -0.0038974523; VMT[1][3][3] = -0.0086792801; VMT[1][3][4] = -0.012621494; VMT[1][3][5] = 0.024972042; VMT[1][3][6] = 0.0056856517; VMT[1][3][7] = 0.0021052496; VMT[1][3][8] = -0.027373591; VMT[1][3][9] = -0.051384654;
 VMT[1][4][0] = 1; VMT[1][4][1] = 0; VMT[1][4][2] = -0.0014227603; VMT[1][4][3] = -0.030061649; VMT[1][4][4] = -0.046831422; VMT[1][4][5] = 0.10036618; VMT[1][4][6] = 0.036051400; VMT[1][4][7] = 0.0060583916; VMT[1][4][8] = -0.90906096; VMT[1][4][9] = -1.6276904;
 VMT[1][5][0] = 1; VMT[1][5][1] = 1; VMT[1][5][2] = 0; VMT[1][5][3] = 0.031875584; VMT[1][5][4] = -0.0054996531; VMT[1][5][5] = -0.0097751962; VMT[1][5][6] = -0.013438433; VMT[1][5][7] = 0.0015528195; VMT[1][5][8] = 0.12173464; VMT[1][5][9] = 0.21413992;
 VMT[1][6][0] = 1; VMT[1][6][1] = 2; VMT[1][6][2] = 0.0054730726; VMT[1][6][3] = 0.019716857; VMT[1][6][4] = 0.018513506; VMT[1][6][5] = -0.048282515; VMT[1][6][6] = -0.0025421507; VMT[1][6][7] = -0.0045124157; VMT[1][6][8] = 0.040917471; VMT[1][6][9] = 0.066596366;
 VMT[1][7][0] = 1; VMT[1][7][1] = 3; VMT[1][7][2] = 0.0019792507; VMT[1][7][3] = 0.0032596742; VMT[1][7][4] = 0.0068332334; VMT[1][7][5] = -0.0098552378; VMT[1][7][6] = 0.0020169108; VMT[1][7][7] = -0.0015629454; VMT[1][7][8] = 0; VMT[1][7][9] = 0;
 VMT[1][8][0] = 2; VMT[1][8][1] = 0; VMT[1][8][2] = 0.0024848327; VMT[1][8][3] = 0.0052249697; VMT[1][8][4] = 0.0096777473; VMT[1][8][5] = -0.022015201; VMT[1][8][6] = 0.0023036520; VMT[1][8][7] = -0.0023381379; VMT[1][8][8] = 0.086122438; VMT[1][8][9] = 0.16571423;
 VMT[1][9][0] = 2; VMT[1][9][1] = 1; VMT[1][9][2] = -0.0030634124; VMT[1][9][3] = -0.0061757928; VMT[1][9][4] = -0.0090029985; VMT[1][9][5] = 0.026087455; VMT[1][9][6] = 0; VMT[1][9][7] = 0.0021900670; VMT[1][9][8] = 0; VMT[1][9][9] = 0;
 VMT[1][10][0] = 2; VMT[1][10][1] = 2; VMT[1][10][2] = 0; VMT[1][10][3] = 0; VMT[1][10][4] = -0.0012940502; VMT[1][10][5] = 0; VMT[1][10][6] = -0.0015144931; VMT[1][10][7] = 0.00022499176; VMT[1][10][8] = 0; VMT[1][10][9] = 0;
 VMT[1][11][0] = 3; VMT[1][11][1] = 0; VMT[1][11][2] = 0; VMT[1][11][3] = 0; VMT[1][11][4] = -0.0017995317; VMT[1][11][5] = 0.0061667091; VMT[1][11][6] = -0.00061666343; VMT[1][11][7] = 0.00083846081; VMT[1][11][8] = 0; VMT[1][11][9] = 0;
 VMT[1][12][0] = 3; VMT[1][12][1] = 1; VMT[1][12][2] = 0.00075633702; VMT[1][12][3] = 0; VMT[1][12][4] = 0.0034958743; VMT[1][12][5] = -0.011399062; VMT[1][12][6] = 0; VMT[1][12][7] = -0.0013202847; VMT[1][12][8] = 0; VMT[1][12][9] = 0;
 VMT[2][0][0] = 0; VMT[2][0][1] = 0; VMT[2][0][2] = 0.29712948; VMT[2][0][3] = 0.40882632; VMT[2][0][4] = 0.16861629; VMT[2][0][5] = 1.3493897; VMT[2][0][6] = 0.10264949; VMT[2][0][7] = 0.029568177; VMT[2][0][8] = 0; VMT[2][0][9] = 6.6184654;
 VMT[2][1][0] = 0; VMT[2][1][1] = 1; VMT[2][1][2] = 0.035707399; VMT[2][1][3] = 0.18719727; VMT[2][1][4] = 0.030144338; VMT[2][1][5] = -0.083447911; VMT[2][1][6] = -0.043097757; VMT[2][1][7] = -0.0048515387; VMT[2][1][8] = 0; VMT[2][1][9] = -1.4540925;
 VMT[2][2][0] = 0; VMT[2][2][1] = 2; VMT[2][2][2] = 0.0096221631; VMT[2][2][3] = 0.056954987; VMT[2][2][4] = 0.013891826; VMT[2][2][5] = -0.048061360; VMT[2][2][6] = -0.0022647176; VMT[2][2][7] = -0.0040797531; VMT[2][2][8] = 0; VMT[2][2][9] = -0.39529833;
 VMT[2][3][0] = 0; VMT[2][3][1] = 3; VMT[2][3][2] = -0.0018402821; VMT[2][3][3] = 0; VMT[2][3][4] = -0.0058030495; VMT[2][3][5] = 0.0076473951; VMT[2][3][6] = 0.0094531290; VMT[2][3][7] = 0.00040403265; VMT[2][3][8] = 0; VMT[2][3][9] = -0.044293243;
 VMT[2][4][0] = 1; VMT[2][4][1] = 0; VMT[2][4][2] = 0.0097572934; VMT[2][4][3] = 0.014474912; VMT[2][4][4] = 0; VMT[2][4][5] = -0.0026863185; VMT[2][4][6] = 0.032738857; VMT[2][4][7] = -0.00163000060; VMT[2][4][8] = 0; VMT[2][4][9] = -0.73866379;
 VMT[2][5][0] = 1; VMT[2][5][1] = 1; VMT[2][5][2] = -0.0049821585; VMT[2][5][3] = 0.023020158; VMT[2][5][4] = -0.0038717547; VMT[2][5][5] = 0.024494430; VMT[2][5][6] = -0.012442571; VMT[2][5][7] = 0.0018200105; VMT[2][5][8] = 0; VMT[2][5][9] = 0.088741049;
 VMT[2][6][0] = 1; VMT[2][6][1] = 2; VMT[2][6][2] = 0.0020301312; VMT[2][6][3] = 0.019300232; VMT[2][6][4] = 0.0082387775; VMT[2][6][5] = -0.047890063; VMT[2][6][6] = -0.0088293329; VMT[2][6][7] = -0.0037432073; VMT[2][6][8] = 0; VMT[2][6][9] = 0;
 VMT[2][7][0] = 1; VMT[2][7][1] = 3; VMT[2][7][2] = -0.0018723311; VMT[2][7][3] = 0; VMT[2][7][4] = -0.010116105; VMT[2][7][5] = 0.017778596; VMT[2][7][6] = 0.0052537299; VMT[2][7][7] = 0.0019950380; VMT[2][7][8] = 0; VMT[2][7][9] = 0;
 VMT[2][8][0] = 2; VMT[2][8][1] = 0; VMT[2][8][2] = 0; VMT[2][8][3] = 0.0025023704; VMT[2][8][4] = 0.0036317285; VMT[2][8][5] = -0.0035216040; VMT[2][8][6] = 0; VMT[2][8][7] = -0.00021119745; VMT[2][8][8] = 0; VMT[2][8][9] = 0.044693973;
 VMT[2][9][0] = 2; VMT[2][9][1] = 1; VMT[2][9][2] = 0.0018831112; VMT[2][9][3] = 0.0050574313; VMT[2][9][4] = 0.0085359607; VMT[2][9][5] = -0.016209200; VMT[2][9][6] = -0.0032283517; VMT[2][9][7] = -0.0014346306; VMT[2][9][8] = 0; VMT[2][9][9] = 0;
 VMT[2][10][0] = 2; VMT[2][10][1] = 2; VMT[2][10][2] = -0.00073403108; VMT[2][10][3] = 0; VMT[2][10][4] = -0.0055135670; VMT[2][10][5] = 0.013179324; VMT[2][10][6] = 0.0013340546; VMT[2][10][7] = 0.0012222675; VMT[2][10][8] = 0; VMT[2][10][9] = 0;
 VMT[2][11][0] = 3; VMT[2][11][1] = 0; VMT[2][11][2] = -0.0015291686; VMT[2][11][3] = -0.0037707379; VMT[2][11][4] = -0.0043657818; VMT[2][11][5] = 0.024434909; VMT[2][11][6] = 0.0043608779; VMT[2][11][7] = 0.0023599053; VMT[2][11][8] = 0; VMT[2][11][9] = 0;
 VMT[2][12][0] = 3; VMT[2][12][1] = 1; VMT[2][12][2] = 0.0043541673; VMT[2][12][3] = 0.0094550140; VMT[2][12][4] = 0.014507659; VMT[2][12][5] = -0.037768479; VMT[2][12][6] = -0.0075640352; VMT[2][12][7] = -0.0039165276; VMT[2][12][8] = 0; VMT[2][12][9] = 0;
 return;
}

// Return the table value from the arguments
double VavilovMoyalFunction::VMTable(unsigned int z, unsigned int i, unsigned int m, unsigned int n)
{
 // Find the correct address
 for (unsigned int x=0; x<13; x++)
 {
   if(VMT[z][x][0] == m && VMT[z][x][1] == n)
    return VMT[z][x][i+1];
 }
 return 0;
}

// Moyal Coefficients.
// i=0: lambda_0, where not need the table.
// i=1,2,3,4,5,6 : a_1, a_2, a_3, a_4, a_5, a_6
// i=7 : lambda_0.95 (2-sigma)
// i=8 : lambda_0.995 (3-sigma)
double VavilovMoyalFunction::VMa(unsigned int i, double k, double beta)
{
 ChebyshevPolynomial Tm,Tn;
 double asum = 0;
 unsigned int z;
 if(k>=0.02 && k<0.11)
 {
   z = 0;
   if(i==0)
    return -3.03;
 }
 else if(k>=0.11 && k<0.22)
 {
   z = 1;
   if(i==0)
    return -3.04;
 }
 else if(k>=0.22 && k<0.30)
 {
   z = 2;
   if(i==0)
    return -3.05;
 }
 else
 {
  return 0;
 }
 for(unsigned int m=0; m<4; m++)
 {
  for(unsigned int n=0; n<4; n++)
  {
    if(m+n<=4)
    {
     double kterm = this->VMk(k);
     double betaterm = this->VMbeta(beta);
     double aterm = this->VMTable(z,i,m,n) * Tm.GetValue(m,kterm) * Tn.GetValue(n,betaterm);
     asum = asum + aterm;
    }
  }
 }
 return asum;
}

// Evaluate the value of the Vavilov distribution by the Moyal approximation
double VavilovMoyalFunction::VMTwoSigma(double k, double beta, double lambda)
{
 // Evaluate the function
 double f = this->VMa(1,k,beta) * std::exp(-1*this->VMa(2,k,beta) * (lambda + this->VMa(5,k,beta) * lambda * lambda) - (this->VMa(3,k,beta) * std::exp(-1*this->VMa(4,k,beta) * (lambda + this->VMa(6,k,beta) * lambda * lambda))));
 return (f>0) ? f : 0.0;
}

double VavilovMoyalFunction::VMThreeSigma(double k, double beta, double lambda)
{
 // Global parameters. Notice that a7 is lambda-TwoSigma, and a8 is Lambda-ThreeSigma
 double f = this->VMTwoSigma(k,beta,this->VMa(7,k,beta));
 double I0 = 0.045;
 double b = (this->VMa(8,k,beta) - this->VMa(7,k,beta)) / (this->VMa(8,k,beta) * this->VMa(7,k,beta));
 double a = 1 / std::log(this->VMa(8,k,beta)/this->VMa(7,k,beta));
 double D = this->VMa(7,k,beta) * this->VMa(7,k,beta) * (f - (a*I0)/this->VMa(7,k,beta)) * (1/(1 - this->VMa(7,k,beta) * a * b)) ;
 double delta = a * (I0/D-b);
 // Evaluate the function
 double x = D * ((1 / (lambda * lambda)) + (delta / lambda));
 return (x>0) ? x : 0.0;
}

// Evaluate the Vavilov-Moyal function
double VavilovMoyalFunction::VMMain(double k, double beta, double lambda)
{
 // Obtain the distribution value
 if(k>=0.02 && k<0.22)
 {
   double lambda0 = this->VMa(0,k,beta); //Absolute minimum value cut-off
   // Function selection
   if(lambda0 <= lambda && lambda < this->VMa(7,k,beta))
   {
     return this->VMTwoSigma(k,beta,lambda);
   }
   else if(this->VMa(7,k,beta) <= lambda && lambda < this->VMa(8,k,beta))
   {
     return this->VMThreeSigma(k,beta,lambda);
   }
   else
   {
    return 0;
   }
 }
 else if(k>=0.22 && k<0.29)
 {
   double lambda0 = this->VMa(0,k,beta); //Absolute minimum value cut-off
   // Function selection
   if(lambda0 <= lambda && lambda < this->VMa(8,k,beta))
   {
     return this->VMTwoSigma(k,beta,lambda);
   }
   else
   {
     return 0;
   }
 }
 else
 {
   return 0; //Out-of-Domain
 }
}


// Define the distribution domain
void VavilovMoyalFunction::SetMoyalStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative)
{
 double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
 double lambdalow = this->VMa(0,k,beta); //lambda_0
 double lambdahigh = this->VMa(8,k,beta); //lambda_0.995
 if(k>=0.22)
  lambdahigh = this->VMa(8,0.22,beta); // For the extended Moyal
 //Since the distribution domain cannot be bounded analytically, the number of steps are the division by unity.
 double lambdastep = 1.0/numberstep;
 VMCbeta = beta;
 VMCk = k;
 VMDEM = DEM;
 VMxi = xi;
 MoyalStep = xi*lambdastep;
 MoyalMinimum = xi*(lambdalow + 1 - euler + beta*beta + std::log(k)) + DEM;
 MoyalMaximum = xi*(lambdahigh + 1 - euler + beta*beta + std::log(k)) + DEM;
 // Cut energy loss greater than average
 if((MoyalMinimum < 0) && TrimNegative)
 {
  MoyalMinimum = 0;
 }
 return;
}

double VavilovMoyalFunction::GetValue(double AtEnergy)
{
 double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
 double MoyalLambda = (AtEnergy - VMDEM)/VMxi - 1 + euler - VMCbeta*VMCbeta - std::log(VMCk);
 return this->VMMain(VMCk,VMCbeta,MoyalLambda);
}

// Solve numerically the equation Ai'(tp)/Ai(tp)+a=0, which is equivalent to find the maximum value of log(Ai(tp))+tp*a=0, where tp are the optimal value for the maximum of Vavilov-Airy Distribution
double VavilovAiryFunction::MaximumFunction(double a)
{
 // The method adopts the Golden-Search Algorithm which are adequate for f'(x)/f(x) kind of functions
 double dx = 1e-3;
 double x1,x2,xl,xu,d;
 // Initial Values
 xl = -2.338107; // First Airy Root
 xu = a*a; // Gaussian condition: tp - a*a = 0
 d = (std::sqrt(5)-1)*(xu-xl)/2;
 x1 = xl + d;
 x2 = xu - d;
 // Cycle condition
 while(std::abs(xu-xl)<dx)
 {
  if((std::log(this->Airy(x1))+a*x1) > (std::log(this->Airy(x2))+a*x2)) // Recalculate x1
  {
    xl = x2;
    x2 = x1;
    xu = xu;
    x1 = xl + (std::sqrt(5)-1)*(xu-xl)/2;
  }
  else // Recalculate x2
  {
    xl = xl;
    xu = x1;
    x1 = x2;
    x2 = xu - (std::sqrt(5)-1)*(xu-xl)/2;
  }
 }
 // Found a solution
 return (xu+xl)/2;
}

// Set the Airy Distribution domain, using the same procedure of Laudau variable on Edgeworth function
void VavilovAiryFunction::SetAiryStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative)
{
 // The integral domain may be evaluated from k and beta parameters
 double euler = (std::lgamma(0.999999) - std::lgamma(1.000001)) / (0.000002); // Euler's Constant
 VAxi = xi;
 VAk = k;
 VAbeta = beta;
 VADEM = DEM;
 double lowlambda = (-0.0322 * VAbeta * VAbeta - 0.0743)*VAk + (-0.2453 * VAbeta * VAbeta + 0.0701)/std::sqrt(VAk) + (-0.5561 * VAbeta * VAbeta - 3.1579);
 double highlambda = (-0.0135 * VAbeta * VAbeta - 0.0488)*VAk + (-1.6921 * VAbeta * VAbeta + 8.3656)/std::sqrt(VAk) + (-0.7327 * VAbeta * VAbeta - 3.5226);
 double lambdastep = (highlambda - lowlambda)/numberstep;
 // For lower k values, the Edgeworth optimal interval may truncate the left side of distribution. To fix this, a new lambda value should be evauated from the first zero of Airy's function.
 double t0 = -2.33811;
 double eta = (xi * std::pow((1 - (2*VAbeta*VAbeta)/3),1.0/3.0))/(std::pow(2.0*VAk,2.0/3.0));
 double a = (std::pow(2.0*VAk,1.0/3.0) * (1 - (VAbeta*VAbeta)/2)) / (std::pow((1 - (2.0*VAbeta*VAbeta)/3.0),2.0/3.0));
 double deltafix = eta*(t0-a*a);
 double tp = this->MaximumFunction(a);
 double deltamax = eta*(tp-a*a);
 // Define the Function Domain
 //AiryStep = VAxi * lambdastep;
 //AiryMinimum = VAxi * (lowlambda + 1 - euler + VAbeta*VAbeta + std::log(VAk)) + DEM;
 AiryMinimum = DEM + deltafix;
 // AiryMaximum = VAxi * (highlambda + 1 - euler + VAbeta*VAbeta + std::log(VAk)) + DEM;
 AiryMaximum = DEM - deltamax - deltafix;
 AiryStep = (AiryMaximum - AiryMinimum) / numberstep;
 // Cut energy loss greater than average
 if((AiryMinimum < 0) && TrimNegative)
 {
  AiryMinimum = 0;
  AiryStep = (AiryMaximum - AiryMinimum) / numberstep;
 }
 return;
}

// Evaluate the Airy-Ai function between the first negative zero (-2.33811) to all positive values. Around t=5 it will use the taylor expansion, and beyond that an assymptotic exponential function

double VavilovAiryFunction::VAa(unsigned int n)
{
 if (n == 0)
  return 1 / (std::pow(3.0,2.0/3.0) * std::tgamma(2.0/3.0));
 else if (n==1)
  return -1 / (std::pow(3.0,1.0/3.0) * std::tgamma(1.0/3.0));
 else if (n==2)
  return 0;
 else
  return (this->VAa(n-3))/(1.0*n*(1.0*n-1));
}

double VavilovAiryFunction::Airy(double t)
{
 // Apply a domain cut-off
 if ((t>-2.33811) && (t<=5))
 {
   double x=0;
   for(unsigned int n=0; n<123; n++)
   {
     x = x + this->VAa(n)*std::pow(t,n*1.0);
   }
  return x;
 }
 else if (t>5)
 {
  return ((std::exp((-2.0/3.0)*std::pow(t,3.0/2.0)))/(std::sqrt(16.0*std::atan(1.0))*std::pow(t,1.0/4.0)))*(1-5/(48*std::pow(t,3.0/2.0)));
 }
 else
 {
  return 0;
 }
}

// Evaluate the Airy approximation value of Vavilov distribution
double VavilovAiryFunction::VA(double delta, double xi, double beta, double k)
{
 // Set the following model parameters
 double eta = (xi * std::pow((1 - (2*VAbeta*VAbeta)/3),1.0/3.0))/(std::pow(2.0*VAk,2.0/3.0));
 double a = (std::pow(2.0*VAk,1.0/3.0) * (1 - (VAbeta*VAbeta)/2)) / (std::pow((1 - (2.0*VAbeta*VAbeta)/3.0),2.0/3.0));
 double t = delta / eta + a*a;
 double f = this->Airy(t) * std::exp(a*t-(a*a*a)/3) / eta;
 return (f>0) ? f : 0.0;
}


// Return the distribution value in terms of energy
double VavilovAiryFunction::GetValue(double AtEnergy)
{
 VAdelta = AtEnergy - VADEM;
 return this->VA(VAdelta,VAxi,VAbeta,VAk)*VAxi;
}


double GaussFunction::FG(double Mean, double StandardDesviation, double x)
{
 double pi = 2*std::acos(0.0);
 double arg = (x - Mean)/StandardDesviation;
 double f = (1/std::sqrt(2 * pi * StandardDesviation * StandardDesviation)) * std::exp(-1 * arg * arg / 2);
 return f;
}

void GaussFunction::SetGaussStep(double Mean, double StandardDesviation, unsigned int numberstep, bool TrimNegative)
{
 GaussDelta = (6 * StandardDesviation)/numberstep;
 GaussMinimum = Mean - 3 * StandardDesviation;
 GaussMaximum = Mean + 3 * StandardDesviation;
 GaussAverage = Mean;
 GaussStandardDesviation = StandardDesviation;
 // Cut negative minimum values
 if(GaussMinimum < 0 && TrimNegative)
 {
  GaussMinimum = 0;
 }
 return;
}

// Dirac's delta function
// It gives one when x=0
double DiracFunction::Dirac(double x)
{
 if(std::abs(x) < 1e-9)
 {
   return 1;
 }
 else
 {
   return 0;
 }
}
