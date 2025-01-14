# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html
# -- Path setup --------------------------------------------------------------
# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import subprocess

# sys.path.insert(0, os.path.abspath('.'))
# -- Run Doxygen -------------------------------------------------------------

doxydir = "_doxygen"

if not os.path.isdir(doxydir):
    os.mkdir(doxydir)

subprocess.call(f"cmake .. -B{doxydir:s} -DBUILD_DOCS=1", shell=True)
subprocess.call(f"cd {doxydir:s}; make html", shell=True)
subprocess.call(f"python -m breathe.apidoc -m -f -p GooseFEM -o api {doxydir:s}/xml", shell=True)

# -- Project information -----------------------------------------------------

project = "GooseFEM"
copyright = "2017-2021, Tom de Geus"
author = "Tom de Geus"


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "breathe",
    "sphinx.ext.mathjax",
    "sphinx.ext.todo",
    "sphinx.ext.autodoc",
    "sphinx.ext.autosummary",
    "sphinx_tabs.tabs",
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
# html_theme = "sphinx_rtd_theme"
html_theme = "furo"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
# html_static_path = ["_static"]


# -- Breathe configuration ---------------------------------------------------

breathe_projects = {
    "GooseFEM": f"{doxydir:s}/xml/",
}
