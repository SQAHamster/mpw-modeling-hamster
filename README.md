# Polyglot Hamster - MPW Simulator

This is the modeled hamster MPW simulator example based on the MPW framework (https://github.com/Fumapps/mpw-modeling-framework).

![modeling approach](documentation/graphics/mdsd-approach-concrete-simulator.svg)

It defines the modeling of the hamster-simulator under `/bundles/de.unistuttgart.iste.sqa.mpw.modeling.hamstersimulator`.
After code-generation with Maven `package`, in `/simulators` the both simulators for Java and C++ can be found.

## Java Simulator

The Java simulator is similar to the PSE-Simulator (https://git.rss.iste.uni-stuttgart.de/open-to-public/pse).
It uses Maven, Java 15 and JavaFX.

##  C++ Simulator

The C++ simulator is based on CMake and SDL2.
Import the CMake project with an IDE like Visual Studio or CLion.
How to setup the dependencies for SDL2 is explained in the `README.md` under `/simulators/de.unistuttgart.iste.sqa.mpw.hamstersimulator.cpp/ui`.

## Setup

### Preparation of Eclipse

* Download "Eclipse Modeling Tools" from https://www.eclipse.org/downloads/packages/
* Use Java JDK 15
* Install required Eclipse features
    * use the `p2f` file from `/releng/installed-items.p2f`
    * File / Import / Install / Install Software Items from File
    * Note: Includes Maven, Henshin, Query-DSL, MPW Modeling Framework, CDT, Tycho Configurators, Xpand

### Generation of modeled entities

Note: after checkout there are many errors due to ungenerated files. They shall disappear after the following steps.
Simply click "Proceed" when a dialog occurs due to errors.

* run genmodels for "generate model code" or call Maven `generate-sources`
    * `/de.unistuttgart.iste.sqa.mpw.modeling.hamstersimulator/src-workflow/workflow/hamstersimulator_genmodel.mwe2`

* run transformation / generation workflow or call Maven `package`
    * `/de.unistuttgart.iste.sqa.mpw.modeling.hamstersimulator/src-workflow/workflow/hamstersimulator_workflow.mwe2`

* open target project in the IDE of choice
    * Java: by Maven: `/simulators/de.unistuttgart.iste.sqa.mpw.hamstersimulator.java`
    * C++: by CMake: `/simulators/de.unistuttgart.iste.sqa.mpw.hamstersimulator.cpp`

* run unit tests
    * Java: under `/core/src/test/java`
    * C++: use CTest after building