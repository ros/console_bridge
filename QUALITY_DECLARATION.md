

This document is a declaration of software quality for the `libconsole-bridge-dev` ROS external dependency, based on the guidelines in [REP-2004](https://www.ros.org/reps/rep-2004.html).

# `libconsole-bridge-dev` Quality Declaration

The ROS external dependency `libconsole-bridge-dev` **does not claim** to be in the **Quality Level 1** category.

Below are the rationales, notes, and caveats for this claim, organized by each requirement listed in the [External dependencies requirements for Quality Level 1 in REP-2XXX](https://www.ros.org/reps/rep-2004.html).

External dependencies are evaluated on a case by case basis, some items may not adhere to standards defined for ROS packages.

## Version Policy

### Version Scheme

It is not publicly available the information regarding `libconsole-bridge-dev` uses a versioning system to manage automatically their version schemes. Their latest library release is set to 0.4.4

### API Stability // ABI Stability

`libconsole-bridge-dev` library do not make any declaration regarding if it's API or ABI stable.

### Public API Declaration

There is no specific documentation regarding a Public API or expected functions that can be used from the library. 

`console.h` is available in the source code, the functions available can be seen there, but the API is not documented.

## Change Control Process

There is no specific implementation/guidelines stated as to how authors are maintaining that library.

## Documentation

`libconsole-bridge-dev` does not provide any type of documentation of how the library is used in their source code repository. There is a [Wiki](http://wiki.ros.org/console_bridge) related to their functionality and expected behavior for its old ROS package.

Feature and API documentation are not addressed.

### License and Copyright Statements

It is not explicitly stated a License or Copyright statement for the library. There is no particular LICENSE file in the source files or on the repository of the library. However, the source files (.cpp and .hpp) all contain the following BSD license header: 

	/*********************************************************************
	* Software License Agreement (BSD License)
	* *
	* * Copyright (c) 2008, Willow Garage, Inc.
	* * All rights reserved.
	* *
	* * Redistribution and use in source and binary forms, with or without
	* * modification, are permitted provided that the following conditions
	* * are met:
	*
	* * Redistributions of source code must retain the above copyright
	* notice, this list of conditions and the following disclaimer.
	* * Redistributions in binary form must reproduce the above
	* copyright notice, this list of conditions and the following
	* disclaimer in the documentation and/or other materials provided
	* with the distribution.
	* * Neither the name of the Willow Garage nor the names of its
	* contributors may be used to endorse or promote products derived
	* from this software without specific prior written permission.
	*
	* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
	* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
	* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
	* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	* POSSIBILITY OF SUCH DAMAGE.
	*********************************************************************/

## Testing

The `libconsole-bridge-dev` library includes a simple testing to check if it compiles properly the basic simple case use. Does not include any kind of performance tests, coverage information nor static analysis.

## Dependencies

There is no dependency on external sources for the `libconsole-bridge-dev` library, only C++ libraries included in the standard library (mutex, iostream).

## Platform Support

There is no particular statement regarding this library provides, or not, support for any particular platform. The fact that it does not use external dependencies to C++ makes it portable enough to consider it compatible with Tier1 ROS2 platforms. But there is no public information related from this available on its repository.

## Conclusion summary

The `libconsole-bridge-dev` has a simple case test and license headers over its source files. However, does not cover several of the standards defined for quality level 1 packages. It was decided by the XYZ committee that the `libconsole-bridge-dev` library will not be considered quality level 1.