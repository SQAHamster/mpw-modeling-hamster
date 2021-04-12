# Hamstersimulator - Release Checklist

## New Release of Source Code

* replace pom.xml versions
* replace MANIFEST.MF versions
* commit with pattern: "Version X.Y.Z"
* create tag on master

## C++ Simulator Library

* wait until C++ simulator is built on GitHub
* switch to branch "cpp-simulator"
* replace files from remote branch "cpp-simulator-snapshot"
* commit with pattern "C++ Simulator: Version X.Y.Z"
* tag with pattern "X.Y.Z-cpp-simulator"

## Set new SNAPSHOT Version

* replace pom.xml versions to next snapshot
* replace MANIFEST.MF versions to next snapshot
* commit with pattern: "Version X.Y.Z-SNAPSHOT"
