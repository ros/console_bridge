This document is a declaration of software quality for the `libconsole-bridge-dev` ROS external dependency, based on the guidelines in [REP-2004](https://www.ros.org/reps/rep-2004.html).

# `libconsole-bridge-dev` Quality Declaration

The ROS external dependency `libconsole-bridge-dev` claims to be in the **Quality Level 1** category.

This library is used as an upstream package, not maintained as other ROS packages. However, the issues in [REP-2004](https://www.ros.org/reps/rep-2004.html) were addressed with some minor modifications, below is explained the rationale used for each topic.


## Version Policy

### Version Scheme

Current state: Their latest library release is set to 0.4.4
TODO: Move version 0.4.4 to >= 1.0.0, check/enforce semver use

`libconsole-bridge-dev` uses `semver` according to the recommendation for ROS Core packages in the [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#versioning), and is at or above a stable version, i.e. `>= 1.0.0`. 

### API Stability // ABI Stability

TODO: define policy to handle API/ABI stability for upstream packages, or at least for this one

`libconsole-bridge-dev` will not break public API nor ABI within a released ROS distribution, i.e. no major releases once the ROS distribution is released.

### Public API Declaration

The API of this package is considered to be the public definitions on the `include` [folder](https://github.com/ros/console_bridge/tree/master/include) of this repository.

## Change Control Process

TODO: define CI used for this package?

`libconsole-bridge-dev`  follows the recommended guidelines for ROS Core packages in the  [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#change-control-process).

This includes:

-   all changes occur through a pull request
-   all pull request have two peer reviews
-   all pull request must pass CI on all  [tier 1 platforms](https://www.ros.org/reps/rep-2000.html#support-tiers)
-   all pull request must resolve related documentation changes before merging

## Documentation

TODO fix links

`libconsole-bridge-dev`  has a  [feature list](TODO)  and each item in the list links to the corresponding feature documentation. There is documentation for all of the features, and new features require documentation before being added.

`libconsole-bridge-dev` has embedded API documentation and it is generated using doxygen and is [hosted](TODO) along side the feature documentation. There is documentation for all of the public API, and new additions to the public API require documentation before being added.

### License and Copyright Statements

TODO: Add license explicitly in the package LICENSE file, verify if the linter is run for upstream packages.

The copyright holders each provide a statement of copyright in each source code file in  `libconsole-bridge-dev`. The license used is [BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause).

There is an automated test which runs a linter that ensures each file has at least one copyright statement.

## Testing

TODO: Add more tests for the library, check that all the features are tested (coverage).

Each feature in  `libconsole-bridge-dev`  has corresponding tests which simulate typical usage, and they are located in the  `test`  directory. New features are required to have tests before being added.

Each part of the public API have tests, and new additions or changes to the public API require tests before being added. The tests aim to cover both typical usage and corner cases, but are quantified by contributing to code coverage.

## Coverage

TODO Add coverage reports / analysis

`libconsole-bridge-dev`  follows the recommendations for ROS Core packages in the  [ROS 2 Developer Guide]([https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#code-coverage](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#code-coverage)), and opts to use branch coverage instead of line coverage.

This includes:

-   tracking and reporting branch coverage statistics
-   achieving and maintaining branch coverage at or above 95%
-   no lines are manually skipped in coverage calculations

Changes are required to make a best effort to keep or increase coverage before being accepted, but decreases are allowed if properly justified and accepted by reviewers.

Current coverage statistics can be viewed [here](TODO):

## Dependencies

`libconsole-bridge-dev` dependencies all match quality level 1.

The only dependency for this package is [`pkg-config`](https://packages.debian.org/buster/pkg-config). As this is a widely used tool in Linux systems, we consider this dependency to match Quality Level 1. 

## Platform Support
TODO: Make a statement for platforms support, and CI report?

`libconsole-bridge-dev` supports all of the tier 1 platforms as described in [REP-2000](https://www.ros.org/reps/rep-2000.html#support-tiers), and tests each change against all of them.
