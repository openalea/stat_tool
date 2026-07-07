.. define the setup for doctest

.. testsetup:: *
   
    from openalea.stat_tool import *
    import pylab
    from pylab import savefig, clf


.. _distribution:

Distribution
============

Here is a brief description of the Distribution type.

In stat_tool, it is a shortname for discrete distributions and is formally represented by the class :py:class:`openalea.stat_tool._stat_tool._DiscreteParametricModel`.
Usually, it is more convenient for users to define directly usual parametric distributions deriving from Distribution, such as Binomial, Poisson, etc. 
These distributions can then be combined using :ref:`compound`, :ref:`convolution` or :ref:`Mixtures <mixture>`. The main other feature to be used with distributions is simulation.

Constructor
-----------

Here is how to build distributions. The parameters are specific to each family of distribution. The shift parameter comes first. If a parameter cannot be interpreted 
as a probability, it comes second and the other parameter, for example a probability parameter, comes third if any.

.. doctest::

    >>> N = NegativeBinomial(0, 1, 0.1)
    >>> B = Binomial(0, 10, 0.5)
    >>> P = Poisson(1, 5.2)
    >>> U = Uniform(2, 10)
    >>> print(U)
    UNIFORM   INF_BOUND : 2   SUP_BOUND : 10
    mean: 6   median: 6   mode: 6
    variance: 6.66667   standard deviation: 2.58199   lower quartile: 4   upper quartile: 8
    coefficient of skewness: 0   coefficient of kurtosis: -0.5
    mean absolute deviation: 2.22222   coefficient of concentration: 0.246914
    information: -2.19722
    <BLANKLINE>

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

    >>> M = Multinomial([0.1, 0.6, 0.3])

Note that the constructor has a single parameter, which is the vector of probabilities.

Plotting
--------

.. doctest::
    
    >>> clf()
    >>> import openalea.stat_tool.plot
    >>> plot.DISABLE_PLOT=True
    >>> print(N.display())
    NEGATIVE_BINOMIAL   INF_BOUND : 0   PARAMETER : 1   PROBABILITY : 0.1
    mean: 9   median: 6   mode: 0
    variance: 90   standard deviation: 9.48683   lower quartile: 2   upper quartile: 13
    coefficient of skewness: 2.00278   coefficient of kurtosis: 6.01111
    mean absolute deviation: 6.90287   coefficient of concentration: 0.523978
    information: -3.24418
    <BLANKLINE>    
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

A Distribution can be estimated from an object of class :ref:`Vectors <vectors>` or a derived class, such as :py:class:`openalea.stat_tool._stat_tool._DiscreteDistributionData`,
using :func:`openalea.stat_tool.estimate.Estimate`. The parametric family is passed as an argument:

.. doctest::

    >>> N_est = Estimate(simulation, "NEGATIVE_BINOMIAL")
    >>> print(N_est.display())
    NEGATIVE_BINOMIAL   INF_BOUND : 0   PARAMETER : 0.953195   PROBABILITY : 0.0943692
    mean: 9.1475   median: 6   mode: 0
    variance: 96.9331   standard deviation: 9.84546   lower quartile: 2   upper quartile: 13
    coefficient of skewness: 2.05103   coefficient of kurtosis: 6.30494
    mean absolute deviation: 7.13637   coefficient of concentration: 0.532088
    <BLANKLINE>
    frequency distribution - sample size: 400
    mean: 9.1475   median: 6   mode: 0
    variance: 96.9331   standard deviation: 9.84546   lower quartile: 2   upper quartile: 13
    coefficient of skewness: 1.80722   coefficient of kurtosis: 3.6898
    mean absolute deviation: 7.34454   coefficient of concentration: 0.539223
    <BLANKLINE>
    log-likelihood: -1306.02   (normalized: -3.26506)
    maximum possible log-likelihood: -1267.79   (information: -3.16947)
    deviance: 76.47
    <BLANKLINE>
    chi-square test (36 degrees of freedom)
    chi-square value: 49.4593   critical probability: 0.0668912
    reference chi-square value: 50.9985   reference critical probability: 0.05
    <BLANKLINE>


