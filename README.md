<div align="center">

![PMMA logo](https://media.githubusercontent.com/media/Project-PMMA/PMMA-Documentation/main/docs/_static/logo.png)

</div>

# PMMA Benchmarks

![PyPI - Wheel](https://img.shields.io/pypi/wheel/pmma) ![Python 3.8](https://img.shields.io/badge/python-3.8-blue) ![Python 3.9](https://img.shields.io/badge/python-3.9-blue) ![Python 3.10](https://img.shields.io/badge/python-3.10-blue) ![Python 3.11](https://img.shields.io/badge/python-3.11-blue) ![Windows](https://img.shields.io/badge/platform-Windows-blue?logo=windows) ![Linux](https://img.shields.io/badge/platform-Linux-yellow?logo=linux) ![GitHub commit activity](https://img.shields.io/github/commit-activity/y/PycraftDeveloper/pmma) ![GitHub commits since latest release](https://img.shields.io/github/commits-since/PycraftDeveloper/pmma/latest)

<p align="center">
    <a href="https://github.com/Project-PMMA/PMMA/blob/main/repository/BuildGuides/intro.md#pmma-build-guide">Main Repository</a> •
    <a href="https://pmma.readthedocs.io/en/latest/">Documentation</a> •
    <a href="https://discord.gg/88duynCX57">Discord</a> •
    <a href="https://github.com/Project-PMMA/PMMA-Tests">Tests</a>
</p>

PMMA is a Python module targeted at helping you build applications in the Python programming language. It does this by providing its own tools covering areas like 2D graphics, noise generation, audio and video playback, event handling, text rendering and much more. The API has two fundamental goals; to make application development in Python easier, whilst also focusing on improving the performance and efficiency of the end result. The API is also being engineered with compatibility with other python modules, like [Pygame](https://github.com/pygame/pygame), [PIL](https://github.com/python-pillow/Pillow) and [Numpy](https://github.com/numpy/numpy) and is ideal for prototyping, application development, simulations, graphics intensive tasks and game development.

## About

> Please note: This is not the PMMA GitHub repository, which can instead be found [here](https://github.com/Project-PMMA/PMMA)

Welcome to the official PMMA Benchmarking repository. This site serves to provide
empirical quantitative data on the performance of PMMA against a range of competing APIs. This may include but is not limited to **CPU usage**, **system memory (RAM) usage**, **video memory (vRAM) usage**, **GPU usage** and **frame rate achieved**.

This repository is split into 4 different branches, each testing a different language and operating system combination. Each branch will be then further sub-divided into each version of PMMA tested (for example PMMA 4.2.2, PMMA 5.0.16 and more).

Each sub-division will include an automated test project that can be left to run unattended and complete all the test requirements. It will also include all the raw data, as well as a report on what the test is designed to achieve, an analysis on the results and make any observations on the testing process and results.

ALL tests, unless specified, have been run on an AMD Ryzen 7 5800X and AMD Radeon RX 7700 XT with the system containing 32 GB of RAM. Driver, Operating System, Software and API versions will also be listed in the testing report. Within a single test, all the variables listed in this paragraph will be kept constant.
