.. 
    Comment:
    define the setup for doctest:

.. testsetup:: *
   
    from openalea.stat_tool import *
    import pylab
    from pylab import savefig, clf


.. _mixture:

Discrete mixtures of distributions
==================================

Here is a brief description of the Mixture type.

In stat_tool, it is a shortname for finite mixtures of discrete distributions and is formally represented by the class :py:class:`openalea.stat_tool._stat_tool._DiscreteMixture`.
A mixture of :math:`K` distributions with probability functions :math:`(p_1,\ldots,p_K)`, referred to as components, and weights :math:`(\pi_1,\ldots,\pi_K)` is the distribution 

.. math::
    p = \sum\limits_{k=1}^K \pi_k p_k.

It represents the fact that a random variable :math:`X`  can be seen as issued from one the :math:`p_k`, each with a probability :math:`\pi_k`. As a consequence, it is 
suitable for model-based clustering, where a cluster is a set of points issued from the same distribution :math:`p_k`, which is unknown, as :math:`k` is for a given point.

Constructor
-----------

Mixtures are built from their components and weights:

.. doctest::

    >>> D1 = NegativeBinomial(0, 1, 0.1)
    >>> D2 = Binomial(0, 10, 0.5)
    >>> D3 = Binomial(1, 5, 0.2)
    >>> M = Mixture(0.4, D1, 0.4, D2, 0.2, D3)
     


In order to display the contents, or to save the data, one uses methods :func:`~openalea.stat_tool.output.Display` and 
:func:`~openalea.stat_tool.plot`.
  
Plotting
--------

.. doctest::
    
    >>> clf()
    >>> import openalea.stat_tool.plot
    >>> plot.DISABLE_PLOT=True
    >>> print(M.display())
    >>> M.plot()
    >>> savefig('user/stat_tool_mixture1.png')

The following figure gathers the probability (mass) function, PMF, of the mixture and the weighted PMFs of its components. 

.. figure:: stat_tool_mixture1.png
    :width: 50%
    :align: center    


Simulate
--------

Once you have a Mixture, you can simulate a data set using sample size as an argument:

.. doctest::

    >>> simulation = M.simulate(400)
 
This creates an Histogram, formally a :py:class:`openalea.stat_tool._stat_tool._DiscreteMixtureData` that is associated 
with the mixture. Thus, plotting it provides both simulated data and distribution. Since in simulations, clusters are actually
known at the time these are simulated, each component can be displayed separately:

.. doctest::

    >>> clf() 
    >>> simulation.plot()
    >>> savefig('user/mixture_simul.png')
    
.. figure:: mixture_simul.png
    :width: 50%
    :align: center
    
    
Estimate
--------

A Mixture can be estimated from a :ref:`Histogram <Histogram>` or a derived class, such as :py:class:`openalea.stat_tool._stat_tool._DiscreteMixtureData`,
using :func:`openalea.stat_tool.estimate.Estimate`. The parametric family of each component is passed as an argument in an abbreviated way: 
"B" for Binomial, "NB" for Negative Binomial, "P" for Poisson, etc. 

.. doctest::

    >>> M_est = Estimate(simulation, "Mixture", "NB", "B", "B")
    >>> print(M_est.display())
    
Note that the order of the two Binomial components is arbitrary, thus they are likely to be switched.


Discrete mixtures of multivariate distributions
===============================================

Mixtures can be extended to multivariate distributions. The associated class is :py:class:`_MultivariateMixture <openalea.stat_tool._stat_tool._MultivariateMixture>`, 
which works essentially as :py:class:`DiscreteMixture <openalea.stat_tool._stat_tool._DiscreteMixture>`. Here is an example with 2 variables:

.. doctest::

    >>> from openalea.stat_tool.multivariate_mixture import _MultivariateMixture
    >>> 
    >>> d11 = Binomial(0, 12, 0.1)
    >>> d12 = Binomial(0, 12, 0.6)
    >>> d13 = Binomial(0, 12, 0.9)
    >>>    
    >>> d21 = Poisson(0, 25.0)
    >>> d22 = Poisson(0, 5.0)
    >>> d23 = Poisson(0, 0.2)
    >>> 
    >>> m = _MultivariateMixture([0.1, 0.2, 0.7], [[d11, d21], [d12, d22], [d13, d23]])
    >>> print(m)
    MIXTURE
    <BLANKLINE>
    3 DISTRIBUTIONS
    <BLANKLINE>
    WEIGHTS
    0.1  0.2  0.7  
    <BLANKLINE>
    2 VARIABLES
    <BLANKLINE>
    VARIABLE 1 : DISCRETE_PARAMETRIC
    <BLANKLINE>
    STATE 0 OBSERVATION_DISTRIBUTION
    BINOMIAL   INF_BOUND : 0   SUP_BOUND : 12   PROBABILITY : 0.1
    mean: 1.2   median: 1   mode: 1
    variance: 1.08   standard deviation: 1.03923   lower quartile: 0   upper quartile: 2
    <BLANKLINE>
    STATE 1 OBSERVATION_DISTRIBUTION
    BINOMIAL   INF_BOUND : 0   SUP_BOUND : 12   PROBABILITY : 0.6
    mean: 7.2   median: 7   mode: 7
    variance: 2.88   standard deviation: 1.69706   lower quartile: 6   upper quartile: 8
    <BLANKLINE>
    STATE 2 OBSERVATION_DISTRIBUTION
    BINOMIAL   INF_BOUND : 0   SUP_BOUND : 12   PROBABILITY : 0.9
    mean: 10.8   median: 11   mode: 11
    variance: 1.08   standard deviation: 1.03923   lower quartile: 10   upper quartile: 12
    <BLANKLINE>
    VARIABLE 2 : DISCRETE_PARAMETRIC
    <BLANKLINE>
    STATE 0 OBSERVATION_DISTRIBUTION
    POISSON   INF_BOUND : 0   PARAMETER : 25
    mean: 25   median: 25   mode: 24.5
    variance: 25   standard deviation: 5   lower quartile: 22   upper quartile: 28
    <BLANKLINE>
    STATE 1 OBSERVATION_DISTRIBUTION
    POISSON   INF_BOUND : 0   PARAMETER : 5
    mean: 5   median: 5   mode: 4.5
    variance: 5   standard deviation: 2.23607   lower quartile: 3   upper quartile: 6
    <BLANKLINE>
    STATE 2 OBSERVATION_DISTRIBUTION
    POISSON   INF_BOUND : 0   PARAMETER : 0.2
    mean: 0.2   median: 0   mode: 0
    variance: 0.2   standard deviation: 0.447214   lower quartile: 0   upper quartile: 0
    <BLANKLINE>

The Plot function plots the mixture marginals:

.. doctest::

    >>> Plot(m, Title="Mixture model used for simulation: ")

Marginals can also be extracted as distributions: 

.. doctest::

    >>> marg1 = m.extract_mixture(1) # first variable
    >>> print(marg1)
    coefficient of concentration: 0.177522 | 0.177522
    CATEGORICAL
    mean: 9.12   median: 10   mode: 11
    variance: 10.4256   standard deviation: 3.22887   lower quartile: 8   upper quartile: 11
    coefficient of skewness: -1.49966   coefficient of kurtosis: 1.32361
    mean absolute deviation: 2.45149   coefficient of concentration: 0.177522
    information: -2.11067
    <BLANKLINE>

:ref:`Vectors <vectors>` can be simulated with :func:`openalea.stat_tool._stat_tool._MultivariateMixture.simulate`:

.. doctest::

    >>> print("Simulate multivariate mixture: ")
    >>> set_seed(1)
    >>> v = m.simulate(500000)

Multivariate mixtures can be estimated by the EM algorithm from :ref:`Vectors <vectors>` 
with :func:`openalea.stat_tool._stat_tool._MultivariateMixtureData.mixture_estimation`:

.. doctest::

    >>> m_estim_model = v.mixture_estimation(m, 100,  [True, True])
    >>> print(m_estim_model)
    MIXTURE
    <BLANKLINE>
    3 DISTRIBUTIONS
    <BLANKLINE>
    WEIGHTS
    0.0999758  0.20025  0.699774  
    <BLANKLINE>
    2 VARIABLES
    <BLANKLINE>
    VARIABLE 1 : DISCRETE_PARAMETRIC
    <BLANKLINE>
    <BLANKLINE>
    STATE 0 OBSERVATION_DISTRIBUTION
    BINOMIAL   INF_BOUND : 0   SUP_BOUND : 12   PROBABILITY : 0.0999885
    mean: 1.19986   median: 1   mode: 1
    variance: 1.07989   standard deviation: 1.03918   lower quartile: 0   upper quartile: 2
    <BLANKLINE>
    state 0 observation frequency distribution - sample size: 49989
    mean: 1.19982   median: 1   mode: 1
    variance: 1.08568   standard deviation: 1.04196   lower quartile: 0   upper quartile: 2
    <BLANKLINE>
    STATE 1 OBSERVATION_DISTRIBUTION
    BINOMIAL   INF_BOUND : 0   SUP_BOUND : 12   PROBABILITY : 0.600068
    mean: 7.20081   median: 7   mode: 7
    variance: 2.87984   standard deviation: 1.69701   lower quartile: 6   upper quartile: 8
    <BLANKLINE>
    state 1 observation frequency distribution - sample size: 98510
    mean: 7.16891   median: 7   mode: 7
    variance: 2.83682   standard deviation: 1.68429   lower quartile: 6   upper quartile: 8
    <BLANKLINE>
    STATE 2 OBSERVATION_DISTRIBUTION
    BINOMIAL   INF_BOUND : 0   SUP_BOUND : 12   PROBABILITY : 0.900095
    mean: 10.8011   median: 11   mode: 11
    variance: 1.07909   standard deviation: 1.03879   lower quartile: 10   upper quartile: 12
    <BLANKLINE>
    state 2 observation frequency distribution - sample size: 351501
    mean: 10.7936   median: 11   mode: 11
    variance: 1.095   standard deviation: 1.04642   lower quartile: 10   upper quartile: 12
    <BLANKLINE>
    VARIABLE 2 : DISCRETE_PARAMETRIC
    <BLANKLINE>
    <BLANKLINE>
    STATE 0 OBSERVATION_DISTRIBUTION
    POISSON   INF_BOUND : 0   PARAMETER : 25.0277
    mean: 25.0277   median: 25   mode: 25
    variance: 25.0277   standard deviation: 5.00277   lower quartile: 22   upper quartile: 28
    <BLANKLINE>
    state 0 observation frequency distribution - sample size: 49989
    mean: 25.0282   median: 25   mode: 24
    variance: 24.859   standard deviation: 4.98588   lower quartile: 22   upper quartile: 28
    <BLANKLINE>
    STATE 1 OBSERVATION_DISTRIBUTION
    POISSON   INF_BOUND : 0   PARAMETER : 5.00441
    mean: 5.00441   median: 5   mode: 5
    variance: 5.00441   standard deviation: 2.23705   lower quartile: 3   upper quartile: 6
    <BLANKLINE>
    state 1 observation frequency distribution - sample size: 98510
    mean: 5.0797   median: 5   mode: 5
    variance: 4.68722   standard deviation: 2.165   lower quartile: 3   upper quartile: 6
    <BLANKLINE>
    STATE 2 OBSERVATION_DISTRIBUTION
    POISSON   INF_BOUND : 0   PARAMETER : 0.19947
    mean: 0.19947   median: 0   mode: 0
    variance: 0.19947   standard deviation: 0.446621   lower quartile: 0   upper quartile: 0
    <BLANKLINE>
    state 2 observation frequency distribution - sample size: 351501
    mean: 0.200301   median: 0   mode: 0
    variance: 0.195032   standard deviation: 0.441624   lower quartile: 0   upper quartile: 0
    <BLANKLINE>
    information: -1e+37 (-2e+31)
    <BLANKLINE>
    log-likelihood: -1.69433e+06   (normalized: -3.38866)
    deviance: -2e+37
    <BLANKLINE>
    17 free parameters   2 * penalyzed log-likelihood (AIC): -3.38869e+06
    17 free parameters   2 * penalyzed log-likelihood (AICc): -3.38869e+06
    17 free parameters   2 * penalyzed log-likelihood (BIC): -3.38888e+06
    17 free parameters   2 * penalyzed log-likelihood (BICc): -3.38886e+06
    <BLANKLINE>

