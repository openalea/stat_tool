/****************************************************************
 *
 *  Test class Distribution
 */

#include <fstream>
#include <cstdio>
#include <cstdlib>

#include "stat_tool/stat_tools.h"
#include "stat_tool/distribution.h"

using namespace stat_tool;

int main(void) {

  StatError error;
  const std::string nhist1 = "./meri1.his", nhist2 = "./meri2.his";
  DiscreteDistributionData *hist1 = NULL, *hist2 = NULL;
  ostringstream os;

  hist1 = DiscreteDistributionData::ascii_read(error, nhist1);
  hist2 = DiscreteDistributionData::ascii_read(error, nhist2);

  hist1->F_comparison(os , *hist2);
  cout << os.str() << "\n";
  

  hist1->t_comparison(os , *hist2);
  cout << os.str() << "\n";

  hist1->wilcoxon_mann_whitney_comparison(error, os , *hist2);
  cout << os.str() << "\n";

  delete hist1;
  delete hist2;

  return 0;
}
