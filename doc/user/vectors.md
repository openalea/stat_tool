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

(Vectors)=

# Vectors

An object with class {py:class}`~openalea.stat_tool.vectors.Vectors` is a collection of vectors, 
that is to say of containers for floating or integer values with fixed dimensions.

## Constructor

As for most other objects, {py:class}`~openalea.stat_tool.vectors.Vectors` can be generated either by 
loading an ASCII or directly using python lists as follows:

<!-- filename with respect to the directory where sphinx is launched -->
```{code-cell} python
v1 = Vectors(get_shared_data("chene_sessile.vec"))
v2 = Vectors([[1,2], [3,4], [4,5]])
```

:::{note} 
Note the syntax, which is a list of lists. The inner elements of the list correspond to the vectors, 
which consist here in a collection of 3 vectors of dimension 2.
:::

Then, you can access to various information using:

```{code-cell} python    
v2.nb_variable
v2.nb_vector
v2.get_identifiers()
```

Identifiers are the indices of each vector.

Eventually,  {py:class}`~openalea.stat_tool.vectors.Vectors` are containers so you can access the data
(starting at index 0):

```{code-cell} python  
v2[1]
v2[1][0]
```

Display, Save, str()  methods are available as in the previous cases. 

However, there is no plotting routines available.
    
There are many more methods available, some of which are explained here below.

## VarianceAnalysis

Here is the usage of One-way variance analysis, achieved with the {func}`~openalea.stat_tool.vectors.VarianceAnalysis` function.   
Its arguments are an object of class Vectors, the index of the class or group variable, the index of the response variable and the type of response variable: “NUMERIC” (“N”) or “ORDINAL” (“O”).
    
```{code-cell} python
print(VarianceAnalysis(v2, 1, 2, "O"))
```

See also the tutorial on [comparison](../examples/comparison.ipynb).

## Compare

Comparing vectors is basically creating a matrix of pairwise distances between
all vectors. This matrix can be used in clustering for example. This is different from
comparing histograms, in which case a statistical test is performed to compare distributions.

```{code-cell} python
print(Compare(v2, VectorDistance("N", "N")))
```

See also the tutorials on [comparison](../examples/comparison.ipynb)
and [clustering](../examples/clustering.ipynb).

## ContingencyTable

The function {func}`~openalea.stat_tool.vectors.ContingencyTable` displays a contingency 
table associated with 2 dimensions of a Vectors passed as arguments, that is, counts
of joint occurrences for each combination of 2-dimensional values. The last line 
(respectively, column) contains total counts for the columns (respectively, lines).

```{code-cell} python
print(ContingencyTable(v2, 1, 2))
```