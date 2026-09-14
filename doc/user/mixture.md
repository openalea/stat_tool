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

(Mixture)=

# Discrete mixtures of distributions

Here is a brief description of the Mixture class.

In stat_tool, it is a shortname for finite mixtures of discrete distributions and is formally represented by the class {py:class}`openalea.stat_tool._stat_tool._DiscreteMixture`.
A mixture of {math}`K` distributions with probability functions {math}`(p_1,\ldots,p_K)`, referred to as components, and weights {math}`(\pi_1,\ldots,\pi_K)` is the distribution 

{math}`p = \sum\limits_{k=1}^K \pi_k p_k.`

It represents the fact that a random variable {math}`X`  can be seen as issued from one the {math}`p_k`, each with a probability {math}`\pi_k`. As a consequence, it is 
suitable for model-based clustering, where a cluster is a set of points issued from the same distribution {math}`p_k`, which is unknown, as {math}`k` is for a given point.

Note that there is a fundamental difference with [Convolutions](./convolution.md): in the latter, the random variable is a sum of random variables while in mixtures, 
the probability measure of the mixture random variable is a weighted sum of probability measures of random variables.

## Constructor

Mixtures are built from their components and weights:

```{code-cell} python
D1 = NegativeBinomial(0, 1, 0.1)
D2 = Binomial(0, 10, 0.5)
D3 = Binomial(1, 5, 0.2)
M = Mixture(0.4, D1, 0.4, D2, 0.2, D3)
```     

In order to display the contents, or to save the data, one uses methods {func}`~openalea.stat_tool.output.Display` and 
{func}`~openalea.stat_tool.plot`.
  
## Plotting

The following figure gathers the probability (mass) function, PMF, of the mixture and the weighted PMFs of its components. 
    
```{code-cell} python
print(M.display())
M.plot()
```

## Simulate

Once you have a Mixture, you can simulate a data set using sample size as an argument:

```{code-cell} python    
simulation = M.simulate(400)
```

This creates an Histogram, formally a {py:class}`openalea.stat_tool._stat_tool._DiscreteMixtureData` that is associated 
with the mixture. Thus, plotting it provides both simulated data and distribution. Since in simulations, clusters are actually
known at the time these are simulated, each component can be displayed separately:

```{code-cell} python    
simulation.plot()
```   
    
## Estimate

A Mixture can be estimated from a {ref}`Histogram <Histogram>` or a derived class, such as {py:class}`openalea.stat_tool._stat_tool._DiscreteMixtureData`,
using {func}`openalea.stat_tool.estimate.Estimate`. The parametric family of each component is passed as an argument in an abbreviated way: 
"B" for Binomial, "NB" for Negative Binomial, "P" for Poisson, etc. 

```{code-cell} python
M_est = Estimate(simulation, "Mixture", "NB", "B", "B")
print(M_est.display())
``` 

Note that the order of the two Binomial components is arbitrary, thus they are likely to be switched.

## Discrete mixtures of multivariate distributions

Mixtures can be extended to multivariate distributions. The associated class is {py:class}`_MultivariateMixture <openalea.stat_tool._stat_tool._MultivariateMixture>`, 
which works essentially as {py:class}`DiscreteMixture <openalea.stat_tool._stat_tool._DiscreteMixture>`. Here is an example with 2 variables:

```{code-cell} python
from openalea.stat_tool.multivariate_mixture import _MultivariateMixture

d11 = Binomial(0, 12, 0.1)
d12 = Binomial(0, 12, 0.6)
d13 = Binomial(0, 12, 0.9)
   
d21 = Poisson(0, 25.0)
d22 = Poisson(0, 5.0)
d23 = Poisson(0, 0.2)

m = _MultivariateMixture([0.1, 0.2, 0.7], [[d11, d21], [d12, d22], [d13, d23]])
print(m)
```

The Plot function plots the mixture marginals:

```{code-cell} python
Plot(m, Title="Mixture model used for simulation: ")
```

Marginals can also be extracted as distributions: 

```{code-cell} python
marg1 = m.extract_mixture(1) # first variable
print(marg1)
```

[Vectors](./vectors.md) can be simulated with {func}`openalea.stat_tool._stat_tool._MultivariateMixture.simulate`:

```{code-cell} python
print("Simulate multivariate mixture: ")
set_seed(1)
v = m.simulate(500000)
v.plot()
```

Multivariate mixtures can be estimated by the EM algorithm from [Vectors](./vectors.md) 
with {func}`openalea.stat_tool._stat_tool._MultivariateMixtureData.mixture_estimation`:

```{code-cell} python
m_estim_model = v.mixture_estimation(m, 100,  [True, True])
print(m_estim_model)
```

Above, initialization was performed using an initial value for the model parameters. 
It is also possible to use default initialization, which only relies on the number of 
mixture components:

```{code-cell} python
m_estim_model = v.mixture_estimation(3, 100,  [True, True])
print(m_estim_model)
```

