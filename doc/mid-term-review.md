# Review form for project Air Combat 3

**Names of reviewers:**
Tam Nguyen
Oskari Järvi
Lauri Blomberg
Lauri Westerholm

Provide short comments (2-4 sentences) for each item below.

## 1. Overall design and functionality (0-6p)

  * 1.1: The implementation corresponds to the selected topic and
scope. The extent of project is large enough to accommodate work for
everyone (2p)
    * The project is large enough, but work distribution is missing. 
    1p

  * 1.2: The software structure is appropriate, clear and well
documented. e.g. class structure is justified, inheritance used where
appropriate, information hiding is implemented as appropriate. (2p)
    * The class structure is quite well planned. Moving objects are divided based on their properties. 
    * Furthermore, the main game loop and graphics & UI are separated to own classes. 
    2p

  * 1.3: Use of external libraries is justified and well documented. (2p)
    * They used recommended libraries: SFML and Box2D. And it is mentioned in their document. 
    * However, they haven’t covered which libraries are used for testing and building. 
    1p 

## 2. Working practices (0-6p)

  * 2.1: Git is used appropriately (e.g., commits are logical and
frequent enough, commit logs are descriptive). (2 p)

    * At the moment there is only a few commits made. Some commit logs could be improved. 
    1p

  * 2.2: Work is distributed and organised well. Everyone contributes to
the project and has a relevant role that matches his/her skills. The
distribution of roles is described well enough. (2p)

    * The class structure is logical and the functions of different classes are well planned. 
    * There is no distribution of work between different members of the team. 
    1p

  * 2.3: Quality assurance is appropriate. Implementation is tested
comprehensively and those testing principles are well documented. (2p)

    * No test file nor test folder is provided. 
    0p

## 3. Implementation aspects (0-8p)

  * 3.1: Building the software is easy and well documented. CMake or
such tool is highly recommended. (2p)

    * At the moment building is not practical. There isn’t Makefile, CMake or any tool to build the program.
    0p

  * 3.2: Memory management is robust, well-organised and
coherent. E.g., smart pointers are used where appropriate or RO3/5 is
followed. The memory management practices should be documented. (2p)

    * Difficult to comment on memory management because the software is currently severely incomplete.
    However, game.cpp unnecessarily uses heap memory where stack could be used.
    0p  

  * 3.3: C++ standard library is used where appropriate. For example,
containers are used instead of own solutions where it makes sense. (2
p)

    * game.cpp: char pointer is used instead of string
    * game.cpp: fgetc (c library) is used instead of c++ iostream.
    * vector and map is used.
    1p

  * 3.4: Implementation works robustly also in exceptional
situations. E.g., functions can survive invalid inputs and exception
handling is used where appropriate. (2p)

    * Own exception class is implemented and exceptions are thrown but not catched.
    0p

## 4. Project extensiveness (0-10p)

  * Project contains features beyond the minimal requirements: Most of
the projects list additional features which can be implemented for
more points. Teams can also suggest their own custom features, though
they have to be in the scope of the project and approved by the course
assistant who is overseeing the project. (0-10p)

    * They have planned for infantry and flak. There’s also possibility to use many different types of weapons with the airplane. 
    * Multiplayer is also planned, but not implemented. Also AI enemy planes are in the plan. 
    * There’s no plan for hangars or level editor.
    6p

