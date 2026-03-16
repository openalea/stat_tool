from openalea.stat_tool import *
from numpy.random import randint
h = Histogram(randint(10, size=10000).tolist())
h.plot()