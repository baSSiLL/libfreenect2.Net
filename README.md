# libfreenect2.Net
A .NET wrapper for [libfreenect2](https://github.com/OpenKinect/libfreenect2) library for working with Kinect v2.

## Build instructions

Sources are authored in VS 2017 Community edition, but C++ projects target VS 2015 runtime to be compatible with **libfreenect2** binaries compiled for VS 2015.
The distribution of **libfreenect2** (`bin`, `include` and `lib` directories) is not included in this repository, so you'll need to get it elsewhere.

For an easy start, you can try taking [the latest release](https://github.com/OpenKinect/libfreenect2/releases). However, it's rather outdated (as of end of 2018). Also it only contains build of _Release_ configuration, and that allows to build only _Release_ configuration of **libfreenect2.Net**. And finally, it's compiled with minimal options, so for instance, CUDA processing is not available.

A harder way is to compile from sources. Visual Studio 2015 Express for Desktop worked for me. When built according to their instruction, output files for distribution are placed into `/build/install` directory (relative to the root of a working copy). You can choose appropriate options to include in build and compile both _Release_ and _Debug_ configurations. Note that it's better to remove target dir before building another configuration so files from an older build do not stay in place (some names differ between configurations).

Copy contents of the distribution directory into `/libfreenect2/<Configuration>` directory in your working copy of this repository. Where `<Configuration>` is _Release_ for release build or _Debug_ for debug build. Now you should be able to build **libfreenect2.Net** solution.