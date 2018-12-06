#pragma once

#include <libfreenect2\libfreenect2.hpp>

using namespace libfreenect2;

namespace libfreenect2Net
{
	private class CompositePacketPipeline : public PacketPipeline
	{
	private:
		PacketPipeline* _colorImpl;
		PacketPipeline* _depthImpl;

	public:
		CompositePacketPipeline(PacketPipeline* colorImpl, PacketPipeline* depthImpl);
		~CompositePacketPipeline();

		PacketParser* getRgbPacketParser() const override;
		PacketParser* getIrPacketParser() const override;

		RgbPacketProcessor* getRgbPacketProcessor() const override;
		DepthPacketProcessor* getDepthPacketProcessor() const override;
	};
}