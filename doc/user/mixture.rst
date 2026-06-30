.. define the setup for doctest:

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
  
plotting
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

A Mixture can be estimated from a :ref:`histogram` or a derived class, such as :py:class:`openalea.stat_tool._stat_tool._DiscreteMixtureData`,
using :func:`openalea.stat_tool.estimate.Estimate`. The parametric family of each component is passed as an argument in an abbreviated way: 
"B" for Binomial, "NB" for Negative Binomial, "P" for Poisson, etc. 

.. doctest::

    >>> M_est = Estimate(simulation, "Mixture", "NB", "B", "B")
    >>> print(M_est.display())
    
Note that the order of the two Binomial components is arbitrary, thus they are likely to be switched.


.. todo::
    Multivariate Mixtures
 


