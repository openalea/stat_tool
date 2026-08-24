/****************************************************************
 *
 *  Test multivariate mixture models
 */

#include "stat_tool/stat_tools.h"
#include "stat_tool/vectors.h"
#include "stat_tool/distribution.h"
#include "stat_tool/curves.h"
#include "stat_tool/markovian.h"
#include "stat_tool/discrete_mixture.h"
#include "stat_tool/multivariate_mixture.h"

using namespace stat_tool;

int main(void) {

  const int  dim = 2; // dimension
  bool *force_param = NULL;
  MultivariateMixture *MultiM = NULL, *m3 = NULL;
  MultivariateMixtureData *simulation_MultiM = NULL;
  double *weights = NULL;
  DiscreteParametric *d11 = NULL, *d12 = NULL, *d13 = NULL;
  DiscreteParametric *d21 = NULL, *d22 = NULL, *d23 = NULL;
  DiscreteParametricProcess **pprocess = NULL;
  CategoricalProcess **npprocess = NULL;
  DiscreteParametric **ppcomponent = NULL;
  Distribution **nppcomponent = NULL;
  StatError error;
  Vectors *debug_vectors = NULL;

  weights = new double[3];
  weights[0] = 0.1;
  weights[1] = 0.2;
  weights[2] = 0.7;
  d11 = new DiscreteParametric(BINOMIAL, 0, 12, 0.1, D_DEFAULT);
  d12 = new DiscreteParametric(BINOMIAL, 0, 12, 0.6, D_DEFAULT);
  d13 = new DiscreteParametric(BINOMIAL, 0, 12, 0.9, D_DEFAULT);
  d21 = new DiscreteParametric(POISSON, 0, 0, 25.0, D_DEFAULT);
  d22 = new DiscreteParametric(POISSON, 0, 0, 5.0, D_DEFAULT);
  d23 = new DiscreteParametric(POISSON, 0, 0, 1.2, D_DEFAULT);

  pprocess = new DiscreteParametricProcess*[dim];

  npprocess = new CategoricalProcess*[dim];

  ppcomponent = new DiscreteParametric*[3];
  nppcomponent = new Distribution*[3];

  // variable 1
  ppcomponent[0] = d11;
  ppcomponent[1] = d12;
  ppcomponent[2] = d13;
  pprocess[0] = new DiscreteParametricProcess(3, ppcomponent);  
  npprocess[0] = NULL;

  // variable 2
  ppcomponent[0] = d21;
  ppcomponent[1] = d22;
  ppcomponent[2] = d23;
  pprocess[1] = new DiscreteParametricProcess(3, ppcomponent);  
  npprocess[1] = NULL;

  MultiM = new MultivariateMixture(3, weights, dim, pprocess, npprocess);
  // MultiM->ascii_write(cout, true);
  
  set_seed(0);
  simulation_MultiM = MultiM->simulation(error, 400);

  force_param = new bool[2];
  force_param[0] = true;
  force_param[1] = true;
  m3 = simulation_MultiM->mixture_estimation(error, &cout, 3, 100, force_param) ;
  if (m3 != NULL)
    m3->ascii_write(cout, true);
  else {
    cout << error;
    return 1;
  }

  delete d11;
  delete d12;
  delete d13;

  delete d21;
  delete d22;
  delete d23;

  delete [] weights;

  delete pprocess[0];
  delete pprocess[1];

  delete [] pprocess; 
  delete [] npprocess; 
  delete [] ppcomponent; 
  delete [] nppcomponent; 
  delete [] force_param;

  debug_vectors = new Vectors(*(m3->get_mixture_data()));
  delete debug_vectors;
  delete simulation_MultiM;
  delete MultiM;
  delete m3;

  return 0;
}
