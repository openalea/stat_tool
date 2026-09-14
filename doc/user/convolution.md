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

(\_convolution)=
# Convolution

Here is a brief description of the Convolution class, which uses notions
introduced in the [Histogram](./histogram.md) Section, recommended to be looked at first.

The convolution of independent random variables {math}`(X_i)_{i=1,\ldots,n}` is the distribution of their sum {math}`\sum\limits_{i=1}^{n} X_i`.

## Constructor

Similarly to the histogram case, there are two constructors for the 
{py:class}`openalea.stat_tool.convolution.Convolution` class that are used as 
follows:

```{code-cell} python
d1 = Binomial(0, 10, 0.5)
d2 = NegativeBinomial(0, 1, 0.1)
conv1 = Convolution(d1, d2)
print(conv1)
```

and

```{code-cell} python 
from openalea.stat_tool import get_shared_data
conv2 = Convolution(get_shared_data("convolution1.conv"))
```

In the first example, which we'll use later on, one create the convolution of 
two {ref}`Distributions <Distribution>` that are a 
{py:class}`openalea.stat_tool.distribution.Binomial` and 
{py:class}`openalea.stat_tool.distribution.NegativeBinomial` distributions.

This can be extended to an arbitrary number of distributions:

```{code-cell} python
d1 = Binomial(0, 10, 0.5)
d2 = NegativeBinomial(0, 1, 0.1)
d3 = Binomial(1, 3, 0.2)
conv3 = Convolution(d1, d2, d3)
```     

The convolution as well as the original distributions are stored within the
Convolution instance. We will see how to extract the original distributions later
on.

In order to display the contents, or to save the data, one uses the same functions
/methods as in the Histogram case.

  
## Plotting

The following figure gather the original distribution and the convolution within 
a single plot. 

```{code-cell} python
conv1.plot()
```

:::{note}
The legend does not show up - why?
:::

It is easy to extract only the relevant distribution and to plot it. You need to 
use the **Extract**-like functions/methods:

```{code-cell} python
Extract(conv1, "Elementary",1).plot(Title="Elementary 1")
Extract(conv1, "Elementary",2).plot(Title="Elementary 2")   
Extract(conv1, "Convolution").plot(Title="Convolution")
```    

## Simulate

Once you have a Convolution, you can simulate a data set using:

```{code-cell} python
simulation = Simulate(conv1, 1000)
```

and compare the resulting data with the original one. This comparison can be
done visually:

```{code-cell} python
simulation.plot()
# equivalent to the line above 
# Simulate(conv1,1000).plot() 
```    
    

 


