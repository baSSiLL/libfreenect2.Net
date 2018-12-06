#include "CompositePacketPipeline.h"

namespace libfreenect2Net
{
	CompositePacketPipeline::CompositePacketPipeline(PacketPipeline* colorImpl, PacketPipeline* depthImpl)
	{
		_colorImpl = colorImpl;
		_depthImpl = depthImpl;
	}

	CompositePacketPipeline::~CompositePacketPipeline()
	{
		delete _colorImpl;
		delete _depthImpl;
	}

	PacketPipeline::PacketParser* CompositePacketPipeline::getRgbPacketParser() const
	{
		return _colorImpl->getRgbPacketParser();
	}

	PacketPipeline::PacketParser* CompositePacketPipeline::getIrPacketParser() const
	{
		return _depthImpl->getIrPacketParser();
	}

	RgbPacketProcessor* CompositePacketPipeline::getRgbPacketProcessor() const
	{
		return _colorImpl->getRgbPacketProcessor();
	}

	DepthPacketProcessor* CompositePacketPipeline::getDepthPacketProcessor() const
	{
		return _depthImpl->getDepthPacketProcessor();
	}
}