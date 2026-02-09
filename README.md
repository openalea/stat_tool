# stat_tool

---

[![Docs](https://readthedocs.org/projects/stat_tool/badge/?version=latest)](https://stat_tool.readthedocs.io/)
[![Build Status](https://github.com/openalea/stat_tool/actions/workflows/conda-package-build.yml/badge.svg?branch=main)](https://github.com/openalea/stat_tool/actions/workflows/conda-package-build.yml?query=branch%3Amaster)
[![License](https://img.shields.io/badge/License--CeCILL-C-blue)](https://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html)
[![Anaconda-Server Badge](https://anaconda.org/openalea3/stat_tool/badges/version.svg)](https://anaconda.org/openalea3/stat_tool)

---

[Read Latest Documentation](https://stat_tool.readthedocs.io/) - [Browse GitHub Code Repository](https://github.com/openalea/stat_tool/)

---

**stat_tool** Basic Statistical tools used by different Structure Analysis libraries.

## Contributors

Thanks to all that ontribute making this package what it is !

<a href="https://github.com/openalea/stat_tool/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=openalea/stat_tool" />
</a>

## Note for developers

- Compile and install with

  pip install -e .

after activation of the conda environment depicted in the online documentation.

- Comilation options for developers such are WITH_TEST, WITH_EFENCE are defined in pyproject.toml. They can be used with

  pip install --no-build-isolation --config-settings=cmake.define.WITH_TEST=TRUE -e .
  pip install --no-build-isolation --config-settings=cmake.build-type="Debug" -e .

and also combined:

    pip install --no-build-isolation --config-settings=cmake.define.WITH_TEST=TRUE --config-settings=cmake.define.WITH_EFENCE=TRUE --config-settings=cmake.build-type="Debug" -e .
