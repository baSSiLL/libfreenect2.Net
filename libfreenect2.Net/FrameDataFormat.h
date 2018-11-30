#pragma once

namespace libfreenect2Net
{
	public enum class FrameDataFormat
	{
		/// <summary>Invalid format.</summary>
		Invalid = 0,
		/// <summary>Raw bitstream. <see cref='Frame::BytesPerPixel'/> defines the total number of bytes.
		Raw = 1, 
		/// <summary>A 4-byte float per pixel.</summary>
		Float = 2, 
		/// <summary>4 bytes of B, G, R, and unused per pixel.</summary>
		Bgrx = 4, 
		/// <summary>4 bytes of R, G, B, and unused per pixel.</summary>
		Rgbx = 5, 
		/// <summary>1 byte of gray per pixel.</summary>
		Gray = 6, 
	};
}