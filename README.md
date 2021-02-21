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
Note: For kara the C++ code is not implemented yet.