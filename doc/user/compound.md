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

(\_compound)=
# Compound

Here is a brief description of the Compound type, which uses notions introduced in the [Histogram](#Histogram) Section, recommended to be looked at first.
 <!--{ref}`Histogram <Histogram>` Section, recommended to be looked at first.-->

A compound (or stopped-sum) distribution is defined as the distribution of the sum of {math}`n` independent and identically distributed
random variables {math}`(X_i)_{i=1,\ldots,n}` where {math}`n` is the value taken by the random variable {math}`N`.
The distribution of {math}`N` is referred to as the sum distribution while the distribution of the {math}`X_i` is referred to as the elementary distribution.

## Constructor

Similarly to the histogram case, there are two constructors for the
{py:class}`openalea.stat_tool.compound.Compound` class that are used as
follows:

```{code-cell} python
X = NegativeBinomial(0, 1, 0.1)
N = Binomial(0, 10, 0.5)
comp1 = Compound(N, X)
print(comp1)
```

and

```{code-cell} python
from openalea.stat_tool import get_shared_data
comp2 = Compound(get_shared_data("compound1.comp"))
print(comp2)
```

In the first example, which we will use later on, one create the compound of
two {ref}`Distribution <Distribution>` objects that are a
{py:class}`openalea.stat_tool.distribution.Binomial` and
{py:class}`openalea.stat_tool.distribution.NegativeBinomial` distributions.

The compound distribution as well as the original distributions are stored within the
Compound instance. We will see how to extract the original distributions later
on.

In order to display the contents, or to save the data, one uses the same functions
/methods as in the Histogram case.

## Plotting

The following figure gather the original distribution and the compound distribution within
a single plot.

```{code-cell} python
comp1.plot()
```

It is easy to extract only the relevant distribution and to plot it. You need to
use the **Extract**-like functions/methods:

```{code-cell} python
d1_bis = Extract(comp1, "Elementary").plot()
```

```{code-cell} python
d2_bis = Extract(comp2, "Elementary").plot()
```

```{code-cell} python
comp1_bis = Extract(comp1, "Compound").plot()
```

## Simulate

Once you have a Compound, you can simulate a data set using:

```{code-cell} python
simulation = Simulate(comp1, 10)
```

and compare the resulting data with the original one. This comparison can be
done visually:

```{code-cell} python
simulation.plot()
Simulate(comp1,1000).plot() # equivalent to the line above
```
