from openalea.stat_tool import *
sum_dist = Binomial(0,10,0.5)
dist = Binomial(0,15,0.2)
c = Compound(sum_dist, dist)
c.plot()