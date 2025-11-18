"""vectors tests"""

__version__ = "$Id$"

try:
    from .tools import interface
    from .tools import robust_path as get_shared_data
except ImportError:
    from tools import interface
    from tools import robust_path as get_shared_data

from openalea.stat_tool.comparison import Compare
from openalea.stat_tool.data_transform import SelectVariable
from openalea.stat_tool.vectors import VectorDistance, Vectors

import pytest

@pytest.fixture
def data():
    vec10 = Vectors(get_shared_data("chene_sessile.vec"))
    vec15 = SelectVariable(vec10, [1, 3, 6], Mode="Reject")
    matrix10 = Compare(vec15, VectorDistance("N", "N", "N"))
    assert 138 == matrix10.nb_row
    assert 138 == matrix10.nb_column
    return matrix10

@pytest.fixture
def myi(data):
    # init expect the 4th argument to be provided.
    # vectors is therefore passed as dummy structure
    return interface(data, None, Vectors)


def test_print(myi):
    myi.print_data()

def test_display(myi):
    myi.display()
    myi.display_versus_ascii_write()
    myi.display_versus_str()

def test_plot(myi):
    myi.plot()

def test_plot_write(myi):
    myi.plot_write()

def test_file_ascii_write(myi):
    myi.file_ascii_write()

def test_spreadsheet_write(myi):
    myi.spreadsheet_write()
