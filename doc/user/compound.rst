.. define some aliases:
.. _histogram_tutorial: ../usage.html#id1

.. define the setup for doctest:
.. testsetup:: *
   
    from openalea.stat_tool import *
    import pylab
    from pylab import savefig, clf


.. _compound:

Compound
========

Here is a brief description of the Compound type, which uses notions introduced in the `Histogram Usage <histogram_tutorial_>` section 
and is thus recommended to be looked at first.

A compound (or stopped-sum) distribution is defined as the distribution of the sum of :math:`n` independent and identically distributed 
random variables :math:`(X_i)_{i=1,\ldots,n}` where :math:`n` is the value taken by the random variable :math:`N`. 
The distribution of :math:`N` is referred to as the sum distribution while the distribution of the :math:`X_i` is referred to as the elementary distribution.

Constructor
-----------

Similarly to the histogram case, there are two constructors for the 
:func:`~openalea.stat_tool.compound.Compound` class that are used as 
follows:

.. doctest::

    >>> X = NegativeBinomial(0, 1, 0.1)
    >>> N = Binomial(0, 10, 0.5)
    >>> conv1 = Compound(N, X)
     
and

.. doctest:: 

    >>> from openalea.stat_tool import get_shared_data
    >>> conv2 = Compound(get_shared_data("compound1.comp")) 

In the first example, which we will use later on, one create the compound of 
two :func:`~openalea.stat_tool.distribution.Distribution` objects that are a 
:func:`~openalea.stat_tool.distribution.Binomial` and 
:func:`~openalea.stat_tool.distribution.NegativeBinomial` distributions.

The compound distribution as well as the original distributions are stored within the
Compound instance. We will see how to extract the original distributions later
on.

In order to display the contents, or to save the data, one uses the same functions
/methods as in the Histogram case.

  
plotting
--------


.. doctest::
    
    >>> clf()
    >>> import openalea.stat_tool.plot
    >>> plot.DISABLE_PLOT=True
    >>> conv1.plot()
    >>> savefig('user/stat_tool_compound_plot1.png')

The following figure gather the original distribution and the compound distribution within 
a single plot. 

.. figure:: stat_tool_compound_plot1.png
    :width: 50%
    :align: center    

It is easy to extract only the relevant distribution and to plot it. You need to 
use the **Extract**-like functions/methods:

.. doctest::

    >>> clf();
    >>> d1_bis = Extract(conv1, "Elementary",1).plot()
    >>> savefig('user/stat_tool_compound_plot2.png')
    
    >>> clf();
    >>> d2_bis = Extract(conv1, "Elementary",2).plot(show=False)
    >>> savefig('user/stat_tool_compound_plot3.png')
    
    >>> clf();
    >>> conv1_bis = Extract(conv1, "Compound").plot(show=False)
    >>> savefig('user/stat_tool_compound_plot4.png')
    
 
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

    >>> simulation = Simulate(conv1, 10)
 
and compare the resulting data with the original one. This comparison can be
done visually:

.. doctest::

    >>> simulation.plot(show=False)
    >>> Simulate(conv1,1000).plot(show=False) # equivalent to the line above 
    >>> savefig('doc/user/stat_tool_compound_plot5.png')
    
.. figure:: stat_tool_compound_plot5.png
    :width: 50%
    :align: center
    
    

 


