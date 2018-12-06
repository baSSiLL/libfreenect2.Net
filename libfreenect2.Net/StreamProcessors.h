#pragma once

namespace libfreenect2Net
{
	/// <summary>Processor for color stream.</summary>
	public enum class ColorProcessor
	{
		/// <summary>Default.</summary>
		/// <remarks>Default processor produces frames with bitmap data, usually in BGRX format.</remarks>
		Default = 0,

		/// <summary>No processing.</summary>
		/// <remarks>Produced frames contain raw JPEG data.</remarks>
		None,
	};


	/// <summary>Processor for depth stream.</summary>
	/// <remarks>
	/// Some implementations may be not available depending on <c>libfreenect2</c> binaries
	/// and whether required components are installed in the OS.
	/// Depth frame data contains depth values in millimeters encoded as float numbers.
	/// </remarks>
	public enum class DepthProcessor
	{
		/// <summary>Default.</summary>
		/// <remarks>Processor is selected by <c>libfreenect2</c> from available implementations.</remarks>
		Default = 0,
		/// <summary>No processing.</summary>
		/// <remarks>Depth frames contain the same raw data as infrared frames.</remarks>
		None,
		/// <summary>Processing on CPU.</summary>
		Cpu,
		/// <summary>Processing on GPU with OpenGL.</summary>
		OpenGL,
		/// <summary>Processing on NVIDIA GPU with CUDA.</summary>
		Cuda,
		/// <summary>Processing on NVIDIA GPU with CUDA, using KDE algorithm.</summary>
		/// <seealso cref="http://users.isy.liu.se/cvl/perfo/abstracts/jaremo16.html"/>
		CudaKde,
		/// <summary>Processing on GPU with OpenCL.</summary>
		OpenCL,
		/// <summary>Processing on GPU with OpenCL, using KDE algorithm.</summary>
		/// <seealso cref="http://users.isy.liu.se/cvl/perfo/abstracts/jaremo16.html"/>
		OpenCLKde
	};
}