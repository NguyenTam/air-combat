# Sample README file for C++ programming project

This is an initial git repository for your programming project.
It contains an initial directory structure that we wish you could
use as follows:

  * `plan/` -- Here is your project plan. You may use different sources,
    but we hope to get the pan **also as pdf file**.

  * `doc/` -- here are the documentation sources related to your project.
    You may use different tools for documentation (e.g. latex),
    but we hope to get the final version of the document
    **also as pdf file**.

  * `src/` -- here are the C++ source files. You can have subfolders as needed.

  * `README.md` -- This file that you should modify to represent
    your project.

You may also add other new directories as needed, for example
for testing tools.


Requirements: *libsfml-dev*, *libspdlog-dev*, *doxygen*.

| Command             | Description                                                          |
|---------------------|----------------------------------------------------------------------|
| `make main`         | Build `src/`                                                         |
| `make test`         | Build `test/`                                                        |
| `make run-main`     | Build `src/` and run an application                                  |
| `make run-test`     | Build `test/` and run tests                                          |
| `make clean`        | Remove compiled objects and executable files from `src/` and `test/` |
| `doxygen`           | Generate documents of `src/`                                         |