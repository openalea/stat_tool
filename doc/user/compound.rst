
.. 
    Comment:
        define the setup for doctest:

.. testsetup:: *
   
    from openalea.stat_tool import *
    import pylab
    from pylab import savefig, clf
    from openalea.stat_tool import get_shared_data
    comp2 = Compound(get_shared_data("compound1.comp")) 

.. _compound:

Compound
========

Here is a brief description of the Compound type, which uses notions introduced in the :ref:`Histogram <Histogram>` Section, recommended to be looked at first. 

A compound (or stopped-sum) distribution is defined as the distribution of the sum of :math:`n` independent and identically distributed 
random variables :math:`(X_i)_{i=1,\ldots,n}` where :math:`n` is the value taken by the random variable :math:`N`. 
The distribution of :math:`N` is referred to as the sum distribution while the distribution of the :math:`X_i` is referred to as the elementary distribution.

Constructor
-----------

Similarly to the histogram case, there are two constructors for the 
:py:class:`openalea.stat_tool.compound.Compound` class that are used as 
follows:

.. doctest::

    >>> X = NegativeBinomial(0, 1, 0.1)
    >>> N = Binomial(0, 10, 0.5)
    >>> comp1 = Compound(N, X)
    >>> print(comp1)
    COMPOUND_DISTRIBUTION
    mean: 44.9985   median: 41   mode: 33
    variance: 652.252   standard deviation: 25.5392   lower quartile: 26   upper quartile: 60
    <BLANKLINE>
    SUM_DISTRIBUTION
    BINOMIAL   INF_BOUND : 0   SUP_BOUND : 10   PROBABILITY : 0.5
    mean: 5   median: 5   mode: 5
    variance: 2.5   standard deviation: 1.58114   lower quartile: 4   upper quartile: 6
    <BLANKLINE>
    ELEMENTARY_DISTRIBUTION
    NEGATIVE_BINOMIAL   INF_BOUND : 0   PARAMETER : 1   PROBABILITY : 0.1
    mean: 9   median: 6   mode: 0
    variance: 90   standard deviation: 9.48683   lower quartile: 2   upper quartile: 13
    <BLANKLINE>
    
and

.. doctest:: 

    >>> from openalea.stat_tool import get_shared_data #doctest: +SKIP
    >>> comp2 = Compound(get_shared_data("compound1.comp")) #doctest: +SKIP
    >>> print(comp2)
    COMPOUND_DISTRIBUTION
    mean: 6.96108   median: 5   mode: 0
    variance: 48.8557   standard deviation: 6.98969   lower quartile: 0.5   upper quartile: 10
    <BLANKLINE>
    SUM_DISTRIBUTION
    NEGATIVE_BINOMIAL   INF_BOUND : 0   PARAMETER : 2   PROBABILITY : 0.5
    mean: 2   median: 1.5   mode: 0.5
    variance: 4   standard deviation: 2   lower quartile: 0.5   upper quartile: 3
    <BLANKLINE>
    ELEMENTARY_DISTRIBUTION
    BINOMIAL   INF_BOUND : 2   SUP_BOUND : 5   PROBABILITY : 0.5
    mean: 3.5   median: 3.5   mode: 3.5
    variance: 0.75   standard deviation: 0.866025   lower quartile: 3   upper quartile: 4
    <BLANKLINE>

In the first example, which we will use later on, one create the compound of 
two :ref:`Distribution <Distribution>` objects that are a 
:py:class:`openalea.stat_tool.distribution.Binomial` and 
:py:class:`openalea.stat_tool.distribution.NegativeBinomial` distributions.

The compound distribution as well as the original distributions are stored within the
Compound instance. We will see how to extract the original distributions later
on.

In order to display the contents, or to save the data, one uses the same functions
/methods as in the Histogram case.

  
Plotting
--------

.. 
    original code
    >>> clf()
    >>> import openalea.stat_tool.plot
    >>> plot.DISABLE_PLOT=True
    >>> comp1.plot()
    >>> savefig('user/stat_tool_compound_plot1.png')



.. doctest::
    
    >>> import openalea.stat_tool.plot
    >>> comp1.plot()

The following figure gather the original distribution and the compound distribution within 
a single plot. 

.. figure:: stat_tool_compound_plot1.png
    :width: 50%
    :align: center    

It is easy to extract only the relevant distribution and to plot it. You need to 
use the **Extract**-like functions/methods:

.. doctest::

    >>> clf();
    >>> d1_bis = Extract(comp1, "Elementary").plot()
    
    >>> clf();
    >>> d2_bis = Extract(comp1, "Elementary").plot(show=False)
    
    >>> clf();
    >>> comp1_bis = Extract(comp1, "Compound").plot(show=False)

..
    once the figures are created    
 
    +--------------------------------------------+---------------------------------------------+
    | .. image:: stat_tool_compound_plot1.png | .. image:: stat_tool_compound_plot2.png  |
    |     :width: 100%                           |     :width: 100%                            |   
    +--------------------------------------------+---------------------------------------------+
    | .. image:: stat_tool_compound_plot3.png | .. image:: stat_tool_compound_plot4.png  |
    |     :width: 100%                           |     :width: 100%                            |
    +--------------------------------------------+---------------------------------------------+   



Simulate
--------

Once you have a Compound, you can simulate a data set using:

.. doctest::

    >>> simulation = Simulate(comp1, 10)
 
and compare the resulting data with the original one. This comparison can be
done visually:

.. doctest::

    >>> simulation.plot(show=False)
    >>> Simulate(comp1,1000).plot(show=False) # equivalent to the line above 

..
    once the figure is created    
    .. figure:: stat_tool_compound_plot5.png
        :width: 50%
        :align: center
    
    

 


