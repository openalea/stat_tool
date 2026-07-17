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

  int v, i;
  int **rand_list = NULL;
  int *identifier = NULL;
  bool *force_param = NULL;
  Vectors *vec = NULL;
  MultivariateMixture *m = NULL;
  DiscreteParametric *U = NULL;
  StatError error;

  set_seed(0);
  U = new DiscreteParametric(UNIFORM, 0, 10, D_DEFAULT, D_DEFAULT);
  rand_list = new int*[1000];
  identifier = new int[1000];
  for (v=0; v<1000; v++)  {
    identifier[v] = v+1;
    rand_list[v] = new int[3];
    for (i=0; i<3; i++) 
      rand_list[v][i] = U->simulation();
  }

  vec = new Vectors(1000, identifier, 3, rand_list);
  force_param = new bool[3];
  for (i=0; i<3; i++)  
    force_param[i] = true;
  m =  vec->mixture_estimation(error, &cout, 2, 100,  force_param);

  delete [] force_param;
  for (v=0; v<1000; v++)  
    delete [] rand_list[v];
  
  delete [] rand_list;
  delete [] identifier;

  delete m;

  delete U;

  return 0;
}
