# Usage

There are several types of object in the the stat_tool module, which are
associated with an ASCII format as well as a set of methods, including 
plotting methods. A full description of each of those objects and their methods are available in the
:ref:`Reference Guide <stat_tool_reference>`. :ref:`stat_tool_reference`. 
 
```{toctree}
:maxdepth: 1
:caption: Basic usage examples of these objects


.. note:: most of the docstrings provided in this document are tested with
    doctest and should work out of the box. However, you will need to import
    relevant modules.  For instance:

    >>> from openalea.stat_tool import *
    >>> from pylab import savefig



Histogram <user/histogram.rst>
Compound <user/compound.rst>
Convolution <user/convolution.rst>
Distribution <user/distribution.rst>
Mixture <user/mixture.rst>
Plotting <user/plotting.rst>
Vectors <user/vectors.rst>
..note:: Exceptions <user/errors.rst>
```

# Tutorials


The following tutorials come under the form of python notebooks:


```{nbgallery}
examples/clustering.ipynb
examples/comparison.ipynb
..note:: examples/data_transform.ipynb
..note:: examples/regression.ipynb
..note:: examples/simulate.ipynb
```
