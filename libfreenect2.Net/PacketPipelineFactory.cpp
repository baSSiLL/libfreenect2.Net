#include "CompositePacketPipeline.h"
#include "StreamProcessors.h"

using namespace libfreenect2;
using namespace libfreenect2Net;
using namespace System;

PacketPipeline* CreateDefaultDepthPipeline()
{
	// Duplicate logic for selecting a depth processor from libfreenect2
	// See createDefaultPacketPipeline function
	// https://github.com/OpenKinect/libfreenect2/blob/master/src/libfreenect2.cpp

#if defined(LIBFREENECT2_WITH_OPENGL_SUPPORT)
	return new OpenGLPacketPipeline();
#elif defined(LIBFREENECT2_WITH_CUDA_SUPPORT)
	return new CudaPacketPipeline();
#elif defined(LIBFREENECT2_WITH_OPENCL_SUPPORT)
	return new OpenCLPacketPipeline();
#else
	return new CpuPacketPipeline();
#endif
}

void ThrowPipelineNotSupported(String^ name)
{
	throw gcnew NotSupportedException(name + " implementation is not supported by this build of libfreenect2.");
}

PacketPipeline* CreateDepthPipeline(DepthProcessor depthProcessor)
{
	switch (depthProcessor)
	{
	case DepthProcessor::Cpu:
		return new CpuPacketPipeline();

	case DepthProcessor::OpenGL:
#if defined(LIBFREENECT2_WITH_OPENGL_SUPPORT)
		return new OpenGLPacketPipeline();
#else
		ThrowPipelineNotSupported("OpenGL");
		return nullptr;
#endif

	case DepthProcessor::Cuda:
#if defined(LIBFREENECT2_WITH_CUDA_SUPPORT)
		return new CudaPacketPipeline();
#else
		ThrowPipelineNotSupported("CUDA");
		return nullptr;
#endif

	case DepthProcessor::CudaKde:
#if defined(LIBFREENECT2_WITH_CUDA_SUPPORT)
		return new CudaKdePacketPipeline();
#else
		ThrowPipelineNotSupported("CUDA KDE");
		return nullptr;
#endif

	case DepthProcessor::OpenCL:
#if defined(LIBFREENECT2_WITH_OPENCL_SUPPORT)
		return new OpenCLPacketPipeline();
#else
		ThrowPipelineNotSupported("OpenCL");
		return nullptr;
#endif

	case DepthProcessor::OpenCLKde:
#if defined(LIBFREENECT2_WITH_OPENCL_SUPPORT)
		return new OpenCLKdePacketPipeline();
#else
		ThrowPipelineNotSupported("OpenCL KDE");
		return nullptr;
#endif

	default:
		return CreateDefaultDepthPipeline();
	}
}

PacketPipeline* GetPacketPipeline(ColorProcessor colorProcessor, DepthProcessor depthProcessor)
{
	if (colorProcessor == ColorProcessor::None)
	{
		if (depthProcessor == DepthProcessor::None)
		{
			// No processing for both => that's Dump
			return new DumpPacketPipeline();
		}
		else
		{
			// No processing for color only => combine Dump for color with selected for depth
			PacketPipeline* depthPipeline = CreateDepthPipeline(depthProcessor);
			PacketPipeline* colorPipeline = new DumpPacketPipeline();
			return new CompositePacketPipeline(colorPipeline, depthPipeline);
		}
	}
	else
	{
		switch (depthProcessor)
		{
		case DepthProcessor::Default:
			// Default for both => let libfreenect2 decide on its own
			return nullptr;
		case DepthProcessor::None:
			// No processing for depth only => combine Dump for depth with an arbitrary for color
			// (all implementations except Dump are the same for color)
			{
				PacketPipeline* depthPipeline = new DumpPacketPipeline();
				PacketPipeline* colorPipeline = new CpuPacketPipeline();
				return new CompositePacketPipeline(colorPipeline, depthPipeline);
			}
		default:
			// Default for color, selected for depth - that's how all implementations work
			// So just use proper implementation
			return CreateDepthPipeline(depthProcessor);
		}
	}
}
