This document is a declaration of software quality for the `libconsole-bridge-dev` ROS external dependency, based on the guidelines in [REP-2004](https://www.ros.org/reps/rep-2004.html).

# `libconsole-bridge-dev` Quality Declaration

The ROS external dependency `libconsole-bridge-dev` claims to be in the **Quality Level 4** category.

Below are the rationales, notes, and caveats for this claim, organized by each requirement listed in the [Package Quality Categories in REP-2004](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#package-quality-categories) of the ROS2 developer guide.

## Version Policy [1]

### Version Scheme [1.i]

`libconsole-bridge-dev` uses `semver` according to the recommendation for ROS Core packages in the [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#versioning).

### Version Stability [1.ii]

`libconsole-bridge-dev` is not yet at a stable version, i.e. `>= 1.0.0`.

### Public API Declaration [1.iii]

All symbols in the installed headers are considered part of the public API.

### API Stability Policy [1.iv]

`libconsole-bridge-dev` is used as an upstream package within the ROS2 ecosystem and has been API/ABI stable for several years. If a breaking change is introduced, ROS2 distributions will pin to a specific major version.

### ABI Stability Policy [1.v]

`libconsole-bridge-dev` is used as an upstream package within the ROS2 ecosystem and has been API/ABI stable for several years. If a breaking change is introduced, ROS2 distributions will pin to a specific major version.

### ABI and ABI Stability Within a Released ROS Distribution [1.vi]

If a breaking change is introduced, ROS2 distributions will pin `libconsole-bridge-dev` to a specific major version.

## Change Control Process [2]

`libconsole-bridge-dev` follows the recommended guidelines for ROS Core packages in the [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#change-control-process).

### Change Requests [2.i]

All changes will occur through a pull request, check [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#change-control-process) for additional information.

### Contributor Origin [2.ii]

This package uses DCO as its confirmation of contributor origin policy. More info can be seen under the [contributing file](./CONTRIBUTING.md) of this repository.

### Peer Review Policy [2.iii]

All pull requests will be peer-reviewed, check [ROS 2 Developer Guide](https://index.ros.org/doc/ros2/Contributing/Developer-Guide/#change-control-process) for additional information.

### Continuous Integration [2.iv]

Currently not tested on CI.

###  Documentation Policy [2.v]

All pull requests must resolve related documentation changes before merging.

## Documentation [3]

### Feature Documentation [3.i]

`libconsole-bridge-dev` does not have per-feature documentation. There is partial documentation on the ROS 1 [wiki](http://wiki.ros.org/console_bridge).

### Public API Documentation [3.ii]

There is no Public API documentation for this library.

### License [3.iii]

The license for `libconsole-bridge-dev` is 3-Clause BSD, and a summary is in each source file and a full copy of the license is in the [`LICENSE`](./LICENSE) file.

### Copyright Statements [3.iv]

The copyright holders each provide a statement of copyright in each source code file in `libconsole-bridge-dev`.

New source files added to this library will require having a copyright statement.

## Testing [4]

### Feature Testing [4.i]

`libconsole-bridge-dev` provides partial testing of some features under the [test folder](./test/).

### Public API Testing [4.ii]

`libconsole-bridge-dev` does not have Public API testing.

### Coverage [4.iii]

`libconsole-bridge-dev` does not provide coverage testing.

### Performance [4.iv]

`libconsole-bridge-dev` does not provide performance testing.

### Linters and Static Analysis [4.v]

`libconsole-bridge-dev` is being tested with `cppcheck` and `cpplint`.

## Dependencies [5]

`libconsole-bridge-dev` has no run-time or build-time dependencies that need to be considered for this declaration. 

## Platform Support [6]

It is not publicly stated which platforms are supported by `libconsole-bridge-dev`.

## Security

### Vulnerability Disclosure Policy [7.i]

This library does not have a Vulnerability Disclosure Policy.
