.. define the setup for doctest:
.. testsetup:: *
   
    from openalea.stat_tool import *
    import pylab
    from pylab import savefig, clf


.. _distribution:
Distribution
========

Here is a brief description of the Distribution type.

In stat_tool, it is a shortname for discrete distributions and is formally represented by the class :py:class:`openalea.stat_tool._stat_tool._DiscreteParametricModel`.
Usually, it is more convenient for users to define directly usual parametric distributions deriving from Distribution, such as Binomial, Poisson, etc. 
These distributions can then be combined using :ref:`compound`, :ref:`convolution` or :ref:`Mixtures <mixture>`. The main other feature to be used with distributions is simulation.

Constructor
-----------

Here is how to build distributions. The parameters are specific to each family of distribution. The shift parameter comes first. If a parameter cannot be interpreted 
as a probability, it comes second and the other parameter, for example a probability parameter, comes third if any.

.. doctest::
    :pyversion: > 3.13.9

    >>> N = NegativeBinomial(0, 1, 0.1)
    >>> B = Binomial(0, 10, 0.5)
    >>> P = Poisson(1, 5.2)
    >>> U = Uniform(2, 10)
    >>> print(U)
    U

.. testcode::

   U = Uniform(2, 10)
   print(U)  # this will give output

.. testoutput::

    

It is equivalent to use the constructor of Distribution with an additional parameter: the name of the parametric family:

.. doctest:: 

    >>> N = Distribution("NEGATIVE_BINOMIAL", 0, 1, 0.1)
    >>> B = Distribution("BINOMIAL", 0, 10, 0.5)
    >>> P = Distribution("POISSON", 1, 5.2)
    >>> U = Distribution("UNIFORM", 2, 10)


In order to display the contents, or to save the data, one uses methods :func:`~openalea.stat_tool.output.Display` and 
:func:`~openalea.stat_tool.plot`.
  
Categorical distributions, i.e., multinomials :math:`{\mathcal M}(1; p_1, \ldots, p_k)` are recovered by the Multinomial class:

.. doctest:: 

    >>> M = Multinomial([0.1, 0.6, 0.29])

Note that the constructor has a single parameter, which is the vector of probabilities.

plotting
--------

.. doctest::
    
    >>> clf()
    >>> import openalea.stat_tool.plot
    >>> plot.DISABLE_PLOT=True
    >>> print(N.display())
    >>> N.plot()
    >>> savefig('user/stat_tool_distribution_plot1.png')

The following figure gathers the probability (mass) function, the cumulative distribution function and the concentration curve. 

.. figure:: stat_tool_distribution_plot1.png
    :width: 50%
    :align: center    


Simulate
--------

Once you have a Distribution, you can simulate a data set using sample size as an argument:

.. doctest::

    >>> simulation = N.simulate(400)
 
This creates an Histogram, formally a :py:class:`openalea.stat_tool._stat_tool._DiscreteDistributionData` that is associated 
with the distribution. Thus, plotting it provides both simulated data and distribution:

.. doctest::

    >>> clf() 
    >>> simulation.plot()
    >>> savefig('user/nbinom_simul.png')
    
.. figure:: nbinom_simul.png
    :width: 50%
    :align: center
    
    
Estimate
--------

A Distribution can be estimated from a :ref:`vectors` or a derived class, such as :py:class:`openalea.stat_tool._stat_tool._DiscreteDistributionData`,
using :func:`openalea.stat_tool.estimate.Estimate`. The parametric family is passed as an argument:

.. doctest::

    >>> N_est = Estimate(simulation, "NEGATIVE_BINOMIAL")
    >>> print(N_est.display())
 


