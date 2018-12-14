# Folder descriptions
  * `plan/` -- Contains the project plan and couple text files which were created during essential implementations, level
    format and main, were planned.

  * `doc/` -- Contains the project documentation. 

  * `src/` -- Source folder contains all source code and headers implemented apart from files that are used purely for testing.
    During compilation object files and the main executable game is build to src.

  * `test/` -- Contains unit test mains for the project. These file were used during testing phases of the project. 
    Test executables and objects are build to this folder by make test.

  * `data/` -- Contains subfolders for data related files. Fonts are stored in fonts. All game entity and button related 
    images are in img and one music file is in music. logs contains spdlog generated run logs (one for each run). 
    level_files contains game levels which are created by ingame level editor and level_img auto-generated images matching 
    levels. misc contains all miscellaneous data files which don’t fit to any other subfolder (i.e. files used to generate 
    help screens and stats view)

  * `./` -- Root of the repository contains Makefile which is used to compile the project binaries. It also contains
    Doxyfile for generating Doxygen documentation of the project.

# Libraries requirements
*libsfml-dev*, *libspdlog-dev*, *doxygen*.
These libraries are in Maari A, B and in CS-building Panic.

We have compiled with following versions:
* SFML Version: 2.3.2+dfsg-1
* Spdlog Version: 1.6-1
* Doxygen Version: 1.8.11-1


#Available commands
| Command             | Description                                                          |
|---------------------|----------------------------------------------------------------------|
| `make main`         | Build `src/`                                                         |
| `make test`         | Build `test/`                                                        |
| `make run-main`     | Build `src/` and run an application                                  |
| `make clean`        | Remove compiled objects and executable files from `src/` and `test/` |
| `doxygen`           | Generate documents of `src/`                                         |
