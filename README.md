# libfreenect2.Net
A .NET wrapper for [libfreenect2](https://github.com/OpenKinect/libfreenect2) library for working with Kinect v2.

## Build instructions

* Build **libfreenect2** project for Win64 platform. When built according to their instruction, output files for distribution (include, lib and bin) are placed into `/build/install` directory (relative to the root of a workign copy).
* Copy contents of the distribution directory into `/libfreenect2` directory in your working copy of this repository.
* Now you should be able to build **libfreenect2.Net** solution.