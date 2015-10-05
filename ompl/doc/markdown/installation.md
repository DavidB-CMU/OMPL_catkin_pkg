# Installation

If you use Linux or OS X, then all dependencies can be installed either through a package manager or by OMPL's build system. In other words, you probably don't have to compile dependencies from source.

To compile OMPL the following two packages are required:
- [Boost], version 1.48 or higher, and
- [CMake], version 2.8.7 or higher.

The build system includes a [number of options](buildOptions.html) that you can enable or disable. To be able to generate python bindings you need to install the [Python] library and header files.

Below are more detailed installation instructions for [Linux](#install_linux), [OS X](#install_osx), and [Windows](#install_windows).

\note If you are using [ROS], please see [MoveIt!][moveit].

\htmlonly
<div class="btn-group">
  <a class="btn btn-default" href="#install_linux">Linux</a>
  <a class="btn btn-default" href="#install_osx">OS X</a>
  <a class="btn btn-default" href="#install_windows">Windows</a>
</div>
\endhtmlonly


# Installation on Linux {#install_linux}

## Ubuntu Linux {#install_linux_ubuntu}

###  Installation from repositories

Starting with Ubuntu 14.04, you can install OMPL like so

    apt-get install libompl-dev ompl-demos

Debian packages for the latest version of OMPL are also found in ROS distributions. All you need to do is add the ROS repository to your list of sources (you probably have added this already if you are using ROS):

    sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
    wget http://packages.ros.org/ros.key -O - | sudo apt-key add -

and install OMPL:

    sudo apt-get update
    sudo apt-get install ros-`rosversion -d`-ompl


### Installation from source

- Install Boost, CMake, and optional dependencies

      sudo apt-get install libboost-all-dev cmake doxygen graphviz python-dev libeigen3-dev libode-dev

- Create a build directory and run cmake:

      cd ompl
      mkdir -p build/Release
      cd build/Release
      cmake ../..

- If you want Python bindings, type the following two commands:

      make installpyplusplus && cmake . # download & install Py++
      make -j 4 update_bindings

- Compile OMPL by typing `make -j 4`.
- Optionally, run the test programs by typing `make test`.
- Optionally, generate documentation by typing `make doc`.
- If you need to install the library, you can type `sudo make install`. The install location is specified by `CMAKE_INSTALL_PREFIX`. If you install in a non-standard location, you have to set the environment variable PYTHONPATH to the directory where the OMPL python module is installed (e.g., $HOME/lib/python2.7/site-packages).

### Installation from source for use with ROS

If you'd like to use your own build of OMPL with ROS, follow the following steps:
- [Create a normal ROS catkin workspace](http://wiki.ros.org/catkin/Tutorials/create_a_workspace)
- [Clone OMPL into the src/ folder](\ref download_repos)
- Add the package.xml file:

      wget https://raw.githubusercontent.com/ros-gbp/ompl-release/debian/`rosversion -d`/`lsb_release -cs`/ompl/package.xml

- To build, you must run catkin_make_isolated instead of the normal catkin_make since OMPL is not a normal catkin package.
- When sourcing this workspace, be sure to source devel_isolated/setup.bash.

## Fedora Linux

Thanks to Rich Mattes, OMPL core is available as a package for Fedora:

    sudo yum install ompl

This package may not be the latest version, though. The source installation instructions for Fedora Linux are mostly the same as for Ubuntu Linux, although the packages have slightly different names. On Fedora, you can install the dependencies like so:

    sudo yum install boost-devel cmake python-devel eigen3 ode-devel doxygen graphviz

The build steps are the same as for Ubuntu Linux.


## Debian Linux

Thanks to Leopold Palomo-Avellaneda, OMPL core is available as a collection of packages for Debian:

      apt-get install libompl-dev ompl-demos


# Installation on Mac OS X {#install_osx}

It is easiest to install OMPL through [MacPorts], a package manager for OS X. However, if you feel adventurous, it is possible to install OMPL's dependencies with [HomeBrew](#install_homebrew) and compile OMPL yourself.


## MacPorts {#install_macports}

- Install [MacPorts].
- If you do not need to modify or see the source code of OMPL, then the easiest way to install OMPL is with the MacPorts `port` command:

      sudo port sync \; install ompl

  This is it. You are done. Demo programs can be found in `/opt/local/share/ompl`.
- If you downloaded the source distribution of OMPL, then you need to install the dependencies Boost, CMake, and optional dependencies. If you have MacPorts installed, type the following:

      sudo port sync
      sudo port install boost cmake ode py27-pyplusplus eigen3 graphviz doxygen

- It is __very__ important that you use the same installed version of Python for all dependencies and OMPL. If you are using MacPorts, then you __must__ use the MacPorts version of python 2.7 (most likely installed in `/opt/local/bin`). To make this version the default python version, make sure `/opt/local/bin` appears before `/usr/bin` in your PATH. You can add a line like this to your `${HOME}/.bash_profile`:

      export PATH=/opt/local/bin:/opt/local/sbin:$PATH

  Next, execute the following command:

      sudo port select python python27

- The build steps are the same as for Ubuntu Linux.


## Homebrew {#install_homebrew}

_Thanks to [Andrew Dobson](https://plus.google.com/104214233559576935970/about) for these instructions!_ __These instructions are somewhat experimental, however, and we haven't tested them ourselves.__ Email us if you have suggestions to improve these instructions.

- Install [Homebrew].
- Run `brew doctor` to make sure that everything is ready to go.  If not, follow its instructions until it is ready.
- Type the following commands:

      brew install boost cmake assimp ode eigen doxygen graphviz

- The build steps are the same as for Ubuntu Linux.


# Installation on Windows {#install_windows}

\note It is possible to run OMPL natively on Windows, although it must be stressed that __extensive testing on Windows is not performed__ at this time, and running OMPL on Windows is considered _highly_ experimental. It is _much_ easier to install [VirtualBox], create an Ubuntu virtual machine, and follow the Ubuntu installation directions above.

For best performance, the [MinGW] compiler is recommended. Visual Studio can also be used to build the core OMPL library, but currently it is not possible to generate the python bindings for OMPL with this compiler. However, if the bindings are generated with MinGW, the bindings can be compiled by Visual Studio with some minor tweaks to the code (not recommended, unless you are an experienced Windows developer).


## Required Dependencies

- [CMake], version 2.8.7 or higher,
- [MinGW][] (recommended) or Visual Studio compiler, and
- [Boost], version 1.48 or greater.

  It is recommended to make a complete Boost compilation from source.  If using Visual Studio, this process can be automated using the [BoostPro](http://www.boostpro.com/download) installer. Once complete, set the environment variables `BOOST_ROOT` and `BOOST_LIBRARYDIR` to the locations where Boost and its libraries are installed.  The default locations are `C:\\Boost` and `C:\\Boost\\lib`.  Ensure that `BOOST_LIBRARYDIR` is also in the system PATH so that any necessary Boost dlls are loaded properly at runtime.


## Optional Dependencies (for Python bindings)

- A __32-bit__ version of [Python] 2.7.  Ensure that this is installed __before building Boost__ so that Boost.Python is properly compiled.
- Ensure that Python is added to the system `PATH`.
- Py++: To generate the Python bindings, Py++ and its dependencies must be installed. A batch file has been included to automate this process (analogous to the Linux/Mac installation) that can be executed via cmake. Instructions can be found [here](installPyPlusPlus.html).  Note that this process assumes the MinGW compiler, and installs gccxml to `C:\\gccxml`.  You will need to be in a shell with administrator privileges to execute this batch file.  Once installed, it is recommended that you open a new shell to realize the new environment settings.


## Build

- Once the dependencies are installed, CMake can be used to generate MinGW makefiles or a Visual Studio solution
by specifying a specific GENERATOR:

    cd ompl
    mkdir build
    cd build
    mkdir Release
    cd Release
    cmake -G "GENERATOR" ../.. [-DCMAKE_INSTALL_PREFIX=/path/to/install]

The CMAKE_INSTALL_PREFIX variable is set to `C:\\Program Files (x86)\\ompl` by default.

### MinGW
- The CMake generator for MinGW is `"MinGW Makefiles"`
- To generate the python bindings (optional), execute the update_bindings make command before compiling:

      mingw32-make update_bindings

  __Note:__ `update_bindings` is _never_ run automatically. If you change any of the OMPL header files, you need to regenerate the bindings for the changes to be reflected in the Python modules. See also the [more detailed documentation on generating python bindings](\ref updating_python_bindings).
- Use `mingw32-make` to build OMPL.
- If you wish to install OMPL, use the install command to copy the binaries, demo code, and other resources to the cmake install prefix.  Note that you will need to be in a shell with administrator privileges to install to the default directory.

      mingw32-make install

- Make sure to add the install path's \\lib subdirectory to the PATH so that the DLLs are found when code is loaded.


### Visual Studio
- The CMake generator for Visual Studio depends on the version of Visual Studio to generate a solution for. The generator for VS 2010 is `"Visual Studio 10"`, and the generator for VS 2008 is `"Visual Studio 9 2008"`. Consult the CMake documentation for other generators.
- Open ompl.sln and build the solution.  A static library will be created (ompl.lib) to link your code against, as well as several demo programs.
- You can install OMPL by building the "INSTALL" project inside of the solution.  Note that this will attempt to copy files to `C:\\Program Files (x86)\\ompl` (the default).  The installation will fail unless Visual Studio is opened with administrator privileges, or a non-system install prefix is specified when cmake is run.

[boost]: http://www.boost.org
[cmake]: http://www.cmake.org
[python]: http://www.python.org
[ros]: http://www.ros.org
[moveit]: http://moveit.ros.org
[macports]: http://www.macports.org
[homebrew]: http://mxcl.github.com/homebrew
[mingw]: http://www.mingw.org
[virtualbox]: http://www.virtualbox.org
