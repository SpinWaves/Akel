// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/03/2022
// Updated : 30/03/2022

#include "stage.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	RenderStage::RenderStage(std::vector<Attachment> images, std::vector<SubpassType> subpasses, const Viewport& viewport) :
		_attachments(std::move(images)),
		_subpasses(std::move(subpasses)),
		_viewport(viewport),
		_subpassAttachmentCount(_subpasses.size()),
		_subpassMultisampled(_subpasses.size())
	{
		for(const auto& image : attachments)
		{
			VkClearValue clearValue = {};

			switch(image.getType())
			{
				case Attachment::type::image:
				{
					clearValue.color = {{image.getClearColour().X, image.getClearColour().Y, image.getClearColour().Z, image.getClearColour().W}};

					for(const auto& subpass : _subpasses)
					{
						if(auto subpassBindings = subpass.GetAttachmentBindings(); std::find(subpassBindings.begin(), subpassBindings.end(), image.getBinding()) != subpassBindings.end())
						{
							_subpassAttachmentCount[subpass.GetBinding()]++;
							if(image.isMultisampled())
								_subpassMultisampled[subpass.GetBinding()] = true;
						}
					}

					break;
				}

				case Attachment::type::depth:
					_clearValue.depthStencil = {1.0f, 0};
					_depthAttachment = image;
					break;

				case Attachment::type::swapchain:
					_clearValue.color = {{image.getClearColour().X, image.getClearColour().Y, image.getClearColour().Z, image.getClearColour().W}};
					_swapchainAttachment = image;
					break;
			}

			clearValues.emplace_back(clearValue);
		}
	}

	void RenderStage::update()
	{
		auto lastRenderArea = _renderArea;

		_renderArea.setOffset(_viewport.getOffset());

		if(_viewport.getSize())
			_renderArea.setExtent(_viewport.getScale() * *_viewport.getSize());
		else
			_renderArea.setExtent(_viewport.getScale() * Window::Get()->getSize());

		_renderArea.setAspectRatio(static_cast<float>(_renderArea.getExtent().X) / static_cast<float>(_renderArea.getExtent().Y));
		_renderArea.setExtent(_renderArea.getExtent() + _renderArea.getOffset());

		_outOfDate = _renderArea != lastRenderArea;
	}

	void RenderStage::rebuild(const Swapchain& swapchain)
	{
		update();

		auto physicalDevice = Render_Core::get().getPhysicalDevice();
		auto surface = Render_Core::get().getSurface();

		auto msaaSamples = physicalDevice->getMsaaSamples();

		if(_depthAttachment)
			_depthStencil = std::make_unique<ImageDepth>(_renderArea.getExtent(), _depthAttachment->isMultisampled() ? msaaSamples : VK_SAMPLE_COUNT_1_BIT);

		if(!_renderpass)
			_renderpass = std::make_unique<Renderpass>(*this, _depthStencil ? _depthStencil->getFormat() : VK_FORMAT_UNDEFINED, surface->getFormat().format, msaaSamples);

		_framebuffers = std::make_unique<Framebuffers>(_renderArea.getExtent(), *this, *_renderpass, swapchain, *_depthStencil, msaaSamples);
		_outOfDate = false;

		_descriptors.clear();

		for(const auto &image : _attachments)
		{
			if(image.getType() == Attachment::type::depth)
				_descriptors.emplace(image.getName(), _depthStencil.get());
			else
				_descriptors.emplace(image.getName(), _framebuffers->getAttachment(image.getBinding()));
		}
	}

	std::optional<Attachment> RenderStage::getAttachment(const std::string& name) const
	{
		auto it = std::find_if(_attachments.begin(), _attachments.end(), [name](const Attachment& a) { return a.getName() == name; });
		return it != _attachments.end() ? *it : std::nullopt;
	}

	std::optional<Attachment> RenderStage::getAttachment(uint32_t binding) const
	{
		auto it = std::find_if(_attachments.begin(), _attachments.end(), [binding](const Attachment& a) { return a.getBinding() == binding; });
		return it != _attachments.end() ? *it : std::nullopt;
	}

	const Descriptor *RenderStage::getDescriptor(const std::string &name) const
	{
		auto it = _descriptors.find(name);
		return it != _descriptors.end() ? it->second : nullptr;
	}

	const VkFramebuffer &RenderStage::GetActiveFramebuffer(uint32_t activeSwapchainImage) const
	{
		return activeSwapchainImage > _framebuffers->getFramebuffers().size() ? _framebuffers->getFramebuffers().at(0) : _framebuffers->getFramebuffers().at(activeSwapchainImage);
	}
}
