#ifndef SPECIALFUNCTIONSLIBRARY_H_INCLUDED
#define SPECIALFUNCTIONSLIBRARY_H_INCLUDED
#include "ERYAProfiling.h"
#include <cmath>


// Hermite polynomial
class HermitePolynomial
{
private:
double H(unsigned int Grade, double Argument);
public:
HermitePolynomial(){};
double GetValue(unsigned int Grade, double Argument){return this->H(Grade,Argument);};
};

// Chebyshev polynomial
class ChebyshevPolynomial
{
private:
double T(unsigned int Grade, double Argument);
public:
ChebyshevPolynomial(){};
double GetValue(unsigned int Grade, double Argument){return this->T(Grade,Argument);};
};

// Laudau Function
class LandauFunction
{
private:
double LandauStep,LandauMinimum,LandauMaximum,LandauEnergy,LandauXi,LandauBeta,LandauK;
double L(double lambda);
public:
LandauFunction(){};
void SetLandauStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative);
double GetLandauStep(){return LandauStep;};
double GetLandauMinimum(){return LandauMinimum;};
double GetLandauMaximum(){return LandauMaximum;};
double GetValue(double AtEnergy);
};

// Vavilov Function by Edgeworth approximation
class VavilovEdgeworthFunction
{
private:
double EdgeworthStep,EdgeworthMinimum,EdgeworthMaximum;
double VE(double delta, double xi, double beta, double k);
double VEalpha(unsigned int n);
double VEmu(unsigned int n);
double VEStdDev, VExi, VEk, VEbeta, VEdelta, VEDEM;
public:
VavilovEdgeworthFunction(){};
void SetEdgeworthStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative);
double GetEdgeworthStep(){return EdgeworthStep;};
double GetEdgeworthMinimum(){return EdgeworthMinimum;};
double GetEdgeworthMaximum(){return EdgeworthMaximum;};
double GetValue(double delta, double xi, double beta, double k){return this->VE(delta,xi,beta,k);};
double GetValue(double AtEnergy);
};

// Vavilov Function by Moyal approximation
class VavilovMoyalFunction
{
private:
double MoyalStep,MoyalMinimum,MoyalMaximum;
double VMCk, VMCbeta, VMDEM, VMxi;
double VMTable(unsigned int z, unsigned int i, unsigned int m, unsigned int n);
double VMbeta(double beta);
double VMk(double k);
double VMa(unsigned int i, double k, double beta);
double VMTwoSigma(double k, double beta, double lambda);
double VMThreeSigma(double k, double beta, double lambda);
double VMMain(double k, double beta, double lambda);
void MakeTable();
double VMT[3][13][10];
public:
VavilovMoyalFunction(){this->MakeTable();};
void SetMoyalStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative);
double GetMoyalStep(){return MoyalStep;};
double GetMoyalMinimum(){return MoyalMinimum;};
double GetMoyalMaximum(){return MoyalMaximum;};
double GetValue(double k, double beta, double lambda){return this->VMMain(k,beta,lambda);};
double GetValue(double AtEnergy);
};

// Vavilov Function by Airy approximation
class VavilovAiryFunction
{
 private:
 double AiryStep,AiryMinimum,AiryMaximum;
 double VAxi, VAk, VAbeta, VAdelta, VADEM;
 double VAa(unsigned int n);
 double Airy(double t);
 double VA(double delta, double xi, double beta, double k);
 public:
 VavilovAiryFunction(){};
 void SetAiryStep(double xi, double beta, double k, double DEM, unsigned int numberstep, bool TrimNegative);
 double GetAiryStep(){return AiryStep;};
 double GetAiryMinimum(){return AiryMinimum;};
 double GetAiryMaximum(){return AiryMaximum;};
 double GetValue(double delta, double xi, double beta, double k){return this->VA(delta,xi,beta,k);};
 double GetValue(double AtEnergy);
};

// Gauss Normal Distribution
class GaussFunction
{
private:
double GaussDelta,GaussMinimum,GaussMaximum,GaussAverage,GaussStandardDesviation;
double FG(double Mean, double StandardDesviation, double x);
public:
GaussFunction(){};
void SetGaussStep(double Mean, double StandardDesviation, unsigned int numberstep, bool TrimNegative);
double GetGaussStep(){return GaussDelta;};
double GetGaussMinimum(){return GaussMinimum;};
double GetGaussMaximum(){return GaussMaximum;};
double GetValue(double Mean, double StandardDesviation, double x){return this->FG(Mean,StandardDesviation,x);};
double GetValue(double AtEnergy){return this->FG(GaussAverage,GaussStandardDesviation,AtEnergy);};
};

// Dirac Delta Distribution
class DiracFunction
{
 private:
 double Dirac(double x);
 public:
 DiracFunction(){};
 double GetValue(double x){return this->Dirac(x);}
 double GetDiracStep(){return 1;};
 double GetDiracMinimum(){return 0;};
 double GetDiracMaximum(){return 1;};
};

#endif // SPECIALFUNCTIONSLIBRARY_H_INCLUDED
