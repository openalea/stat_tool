---
jupytext:
  formats: md:myst
  text_representation:
    extension: .md
    format_name: myst
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

```{code-cell} python
:tags: [remove-cell]
from openalea.stat_tool import *
import warnings
warnings.filterwarnings('ignore')
```

(Distribution)=

# Distribution

Here is a brief description of the Distribution class.

In stat_tool, it is a shortname for discrete distributions and is formally represented by the class {py:class}`openalea.stat_tool._stat_tool._DiscreteParametricModel`.
Usually, it is more convenient for users to define directly usual parametric distributions deriving from Distribution, such as Binomial, Poisson, etc. 
These distributions can then be combined using [Compound](./compound.md), [Convolution](./convolution.md) or [Mixtures](./mixture.md). The main other feature to be used with distributions is simulation.

## Constructor

Here is how to build distributions. The parameters are specific to each family of distribution. The shift parameter comes first. If a parameter cannot be interpreted 
as a probability, it comes second and the other parameter, for example a probability parameter, comes third if any.

```{code-cell} python
N = NegativeBinomial(0, 1, 0.1)
B = Binomial(0, 10, 0.5)
P = Poisson(1, 5.2)
U = Uniform(2, 10)
print(U)
```

It is equivalent to use the constructor of Distribution with an additional parameter - the name of the parametric family:

```{code-cell} python 
N = Distribution("NEGATIVE_BINOMIAL", 0, 1, 0.1)
B = Distribution("BINOMIAL", 0, 10, 0.5)
P = Distribution("POISSON", 1, 5.2)
U = Distribution("UNIFORM", 2, 10)
```

In order to display the contents, or to save the data, one uses methods {func}`~openalea.stat_tool.output.Display` and 
{func}`~openalea.stat_tool.plot`.
  
Categorical distributions, i.e., multinomials {math}`{\mathcal M}(1; p_1, \ldots, p_k)` are recovered by the Multinomial class:

```{code-cell} python 
M = Multinomial([0.1, 0.6, 0.3])
```

Note that the constructor has a single parameter, which is the vector of probabilities.

## Plotting

Distributions have a plot method for graphical representations. 

The following figure gathers the probability (mass) function, the cumulative distribution function and the concentration curve. 

```{code-cell} python
print(N.display())
N.plot()
```

## Simulate

Once you have a Distribution, you can simulate a data set using sample size as an argument:

```{code-cell} python
simulation = N.simulate(400)
```

This creates an Histogram, formally a {py:class}`openalea.stat_tool._stat_tool._DiscreteDistributionData` that is associated 
with the distribution. Thus, plotting it provides both simulated data and distribution:

```{code-cell} python
simulation.plot()
```    
    
## Estimate

A Distribution can be estimated from an object of class [Histogram](./histogram.md) or a derived class, such as {py:class}`openalea.stat_tool._stat_tool._DiscreteDistributionData`,
using {func}`openalea.stat_tool.estimate.Estimate`. The parametric family is passed as an argument:

```{code-cell} python
N_est = Estimate(simulation, "NEGATIVE_BINOMIAL")
print(N_est.display())
```

