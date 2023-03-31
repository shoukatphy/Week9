///////////////////////////////
////2D function Minimization///
//L. Monteta //////////////////
///shoukat/////////////////////
///////////////////////////////
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom3.h"
#include "TError.h"
#include<iostream>
using namespace std;
//define the func
double myFunc(const double *x){
const Double_t a = x[0];
const Double_t b = x[1];
const Double_t para = a*a + b*b +a*b;
return (2*para);
}

void NumericalMinimization(const char * minName = "Minuit2", const char *algoName= "" , int randomSeed = -1){
//creating minimizer using name

	   // create minimizer giving a name and a name (optionally) for the specific
   // algorithm
   // possible choices are:
   //     minName                  algoName
   // Minuit /Minuit2             Migrad, Simplex,Combined,Scan  (default is Migrad)
   //  Minuit2                     Fumili2
   //  Fumili
   //  GSLMultiMin                ConjugateFR, ConjugatePR, BFGS,
   //                              BFGS2, SteepestDescent
   //  GSLMultiFit
   //   GSLSimAn
   //   Genetic

   ROOT::Math::Minimizer *min = ROOT::Math::Factory::CreateMinimizer(minName, algoName);

	   // set tolerance , etc...     
   //min->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
   //min->SetMaxIterations(10000);  // for GSL
   //min->SetTolerance(0.001);
   //min->SetPrintLevel(1);
 //creat func wrapper for minimizer
  //a IMultiGenFunction type
  ROOT::Math::Functor fn(&myFunc,2);

  double step[2]= {0.01, 0.01};//starting point

  double vari[2] = {-1. , 1.2};

  if(randomSeed>=0){
  auto *rn = new TRandom3();
	  vari[0] = rn->Uniform(-20, 20);
	  vari[1] = rn->Uniform(-20, 20);
  }//loop closed

 min->SetFunction(fn);//give the func 
 min->SetVariable(0, "x", vari[0], step[0]);//set the free variables to be minimized
min->SetVariable(1, "y", vari[1], step[1]);//for variable2

//do minimization

min->Minimize();

const double *xmn = min->X(); 

cout<<"minimize: fn minimizes at  (" <<xmn[0]<<" , "<<xmn[1]<< " ) : "<<endl;

cout<<"minimizer: "<<min->MinValue()<<endl;


}

int MinimizeFunc(){

	
       //calling the minimization func
	NumericalMinimization( "Minuit2",  "Migrad" ,  -1);


return 0;
}
