/****************************************************************
 *
 *  Test distance matrices
 */

#include "stat_tools.h"
#include "stat_tool/vectors.h"
#include "stat_tool/distance_matrix.h"

using namespace stat_tool;

int main(void) {

  
  StatError error;
  int *ivariable = NULL;
  const int nb_cluster = 2;
  const char * vec_path = "chene_sessile.vec";
  Vectors *vec10 = NULL, *vec15 = NULL;
  DistanceMatrix *matrix10 = NULL;
  Clusters *clust = NULL;
  VectorDistance *vec_dist = NULL;
  variable_type *ivar_type = NULL;
  int *cluster_nb_pattern = new int[nb_cluster];
  int **cluster_pattern = new int*[nb_cluster];
  double *iweight = NULL;
  
  vec10 = stat_tool::Vectors::ascii_read(error, vec_path);
  ivariable = new int[3];
  ivariable[0] = 1;
  ivariable[1] = 3;
  ivariable[2] = 6;
  ivar_type = new variable_type[3];
  ivar_type[0] = NUMERIC;
  ivar_type[1] = NUMERIC;
  ivar_type[2] = NUMERIC;
  iweight = new double[3];
  iweight[0] = 1./3;
  iweight[1] = 1./3;
  iweight[2] = 1./3;
  if (error.get_nb_error() == 0) {
    vec15 = vec10->select_variable(error, 3, ivariable, false);
    if (error.get_nb_error() == 0) {
      vec_dist = new VectorDistance(3, ivar_type, iweight);
      matrix10 = vec15->comparison(error, *vec_dist);
      cluster_nb_pattern[0] = 2;
      cluster_nb_pattern[1] = 2;
      cluster_pattern[0] = new int[2];
      cluster_pattern[0][0] = 1;
      cluster_pattern[0][1] = 2;
      cluster_pattern[1] = new int[2];
      cluster_pattern[1][0] = 3;
      cluster_pattern[1][1] = 4;
      clust = matrix10->partitioning(error, &cout, nb_cluster, cluster_nb_pattern,
          cluster_pattern);
      delete [] cluster_pattern[0];
      delete [] cluster_pattern[1];
      if (error.get_nb_error() > 0)
        cout << error;
      delete [] cluster_pattern;
      delete [] cluster_nb_pattern;
      cluster_pattern = new int*[1];
      cluster_pattern[0] = new int[1];
      cluster_pattern[0][0] = 0;
      cluster_nb_pattern = new int[1];
      cluster_nb_pattern[0] = 0;
      clust = matrix10->partitioning(error, &cout, 1, cluster_nb_pattern,
          cluster_pattern);
      delete [] cluster_pattern[0];
    } else {
      cout << error;
    }
    delete [] cluster_pattern;
    delete [] cluster_nb_pattern;
    delete [] ivariable;
    delete [] ivar_type;
    delete [] iweight;
    delete vec_dist;
    delete vec10;
    delete vec15;
    delete matrix10;


  return 0; } else {    
    delete [] ivariable;
    delete [] ivar_type;
    delete [] iweight;      
    delete [] cluster_pattern;
    delete [] cluster_nb_pattern;
    return 1;
  }
  
}
