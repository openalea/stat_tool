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

(Errors)=
# Errors

The stat_tool module has its own classes for exceptions: _StatError, which is a short name for {py:class}`openalea.stat_tool._stat_tool._StatError <openalea.stat_tool._stat_tool._StatError>`, and FormatError.

FormatError is used to handle errors in estimation (inconsistency between models or data).

Constructor
-----------

You may use {py:class}`_StatError <openalea.stat_tool._stat_tool._StatError>` to raise your own exceptions. In that case, the constructor of _StatError takes a string as an argument. You may count the number of errors
in _StatError if there are several of them, and use :func:`~openalea.stat_tool._stat_tool._StatError`

:::{note} 
TODO:Let _StatError derive from BaseException
:::

```python
from openalea.stat_tool.multivariate_mixture import _MultivariateMixture
from openalea.stat_tool.error import _StatError

d11 = Binomial(0, 12, 0.1)
d12 = Binomial(0, 12, 0.6)
d13 = Binomial(0, 12, 0.9)
   
d21 = Poisson(0, 25.0)
d22 = Poisson(0, 5.0)
d23 = Poisson(0, 0.2)

m = _MultivariateMixture([0.1, 0.2, 0.7], [[d11, d21], [d12, d22], [d13, d23]])
try:
    m.state_permutation([0, 1, 1])
except Exception:
    E = _StatError()
    E.update("Wrong Permutation")
    assert(E.get_nb_error() == 1)
    raise(BaseException(E))
```

