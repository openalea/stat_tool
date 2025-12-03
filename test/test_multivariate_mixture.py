# -*- coding: utf-8 -*-
"""Multivariate mixture tests
#
#
#########################################################################
"""

try:
    from .tools import interface
except ImportError:
    from tools import interface


# from openalea.stat_tool.plot import DISABLE_PLOT

from openalea.stat_tool.distribution import Binomial, Poisson
from openalea.stat_tool.multivariate_mixture import _MultivariateMixture
from openalea.stat_tool.vectors import Vectors

import os, tempfile

import pytest

@pytest.fixture
def data():
    d11 = Binomial(0, 12, 0.1)
    d12 = Binomial(0, 12, 0.5)
    d13 = Binomial(0, 12, 0.8)

    d21 = Poisson(0, 18.0)
    d22 = Poisson(0, 5.0)
    d23 = Poisson(0, 0.20)

    data = _MultivariateMixture(
        [0.1, 0.2, 0.7], [[d11, d21], [d12, d22], [d13, d23]]
    )
    assert data.nb_component == 3
    assert data.nb_variable == 2
    return data

@pytest.fixture
def myi(data):
    return interface(data,  "data/mixture_mv1.mixt", _MultivariateMixture)

@pytest.fixture
def my_estimate():
    data_file = "data/cluster_vectors.vec"
    v = Vectors(data_file)
    assert len(v) == 836
    assert v.nb_variable == 5
    m = v.mixture_estimation(3, 300, [])

    return m, v

def _test_constructor_from_file(myi):
    # raise error (proba non equal to 1) when nosetests used from parent directory.
    myi.constructor_from_file()

def test_constructor_from_file_failure(myi):
    myi.constructor_from_file_failure()

def test_print(myi):
    myi.print_data()

def test_display(myi):
    myi.display()
    myi.display_versus_ascii_write()
    myi.display_versus_str()

def test_len(data):
    c = data
    assert len(c) == 3

def test_plot(data):
    # if DISABLE_PLOT == False:
    data.plot(1)
    #   self.data.plot(2)


def test_plot_write(myi):
    myi.plot_write()

def test_file_ascii_write(myi):
    myi.file_ascii_write()



def test_estimate(my_estimate):
    m, v = my_estimate
    assert m, v

def test_mixture_plots(my_estimate):
    m, v = my_estimate
    m.plot()
    # Get marginals
    for i in range(v.nb_variable):
        marginal = m.extract_distribution(i + 1)
        assert marginal.nb_component == 3
    marginal.plot()
    assert m, v

def test_spreadsheet_write(myi):
    myi.spreadsheet_write()

def test_simulate(myi):
    myi.simulate()

def test_extract(my_estimate):
    m, v = my_estimate
    for i in range(1, v.nb_variable + 1):
        m2 = v.extract(i)
        assert m2

def test_extract_data(my_estimate):
    m, v = my_estimate
    d = m.extract_data()
    assert d

def test_simulate2():
    d11 = Binomial(0, 12, 0.1)
    d12 = Binomial(0, 12, 0.5)
    d13 = Binomial(0, 12, 0.8)
    d21 = Poisson(0, 18.0)
    d22 = Poisson(0, 5.0)
    d23 = Poisson(0, 0.20)
    m = _MultivariateMixture([0.1, 0.2, 0.7], [[d11, d21], [d12, d22], [d13, d23]])
    v = m.simulate(5000)
    assert v

    # TODO: set seed
    estimation_failed = True
    while estimation_failed:
        try:
            m_estim_model = v.mixture_estimation(m, 100, [True, True])
        except Exception:
            pass
        else:
            estimation_failed = False
    assert m_estim_model

    estimation_failed = True
    while estimation_failed:
        try:
            m_estim_nbcomp = v.mixture_estimation(2)
        except Exception:
            pass
        else:
            estimation_failed = False
    assert m_estim_nbcomp

def _test_permutation(data):
    data1 = data

    data2 = _MultivariateMixture(data1)
    data2.state_permutation([0, 2, 1])
    data2.state_permutation([0, 2, 1])

    assert str(data1) == str(data2)

def test_cluster_data(my_estimate):
    """Clustering using the mixture model"""
    m, v = my_estimate
    clust_entropy = m.cluster_data(v, True)


    with tempfile.NamedTemporaryFile(delete=False) as tmp:
        clust_entropy.file_ascii_write(tmp.name, False)

    clust_plain = m.cluster_data(v, False)
    os.remove(tmp.name)

    assert clust_entropy.nb_variable == m.nb_variable + 2
    assert clust_plain.nb_variable == m.nb_variable + 1

def test_cluster_data_file(my_estimate):
    """Clustering using the mixture model, reading data from a file"""
    m, v = my_estimate
    clust_entropy = m.cluster_data(v, True)

    with tempfile.NamedTemporaryFile(delete=False) as tmp:
        clust_entropy.file_ascii_write(tmp.name, False)

    os.remove(tmp.name)

    assert clust_entropy.nb_variable == m.nb_variable + 2

