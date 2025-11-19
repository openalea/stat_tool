#include "reestimation.h"

namespace stat_tool {

// Explicitly instantiate only once in this cpp
template class Reestimation<int>;
template class Reestimation<double>;

}  // namespace stat_tool