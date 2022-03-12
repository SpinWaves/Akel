// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/07/2021
// Updated : 10/03/2022

#ifndef __AK_STUDIO_CONSOLE__
#define __AK_STUDIO_CONSOLE__

#include <AkSpch.h>
#include <Panels/shell/shell.h>
#include <Panels/Base/panel.h>

class Console : public Panel
{
	public:
		Console(std::shared_ptr<Ak::ELTM> eltm, size_t inputBufferSize = 256);
		void onUpdate(Ak::Maths::Vec2<int>& size) override;
		void onEvent(Ak::Input& input) override;
		~Console() = default;

	protected:
		std::string _input;

	private:
		void inputBar();
		void logPart();

		static int InputCallback(ImGuiInputTextCallbackData *data);

		bool _autoScroll;
		bool _coloredOutput;
		bool _scrollToBottom;
		size_t _inBufferSize = 0;
		float _WindowAlpha;

		Shell _sh;

		Ak::audioFile ee = 0;

		Ak::Maths::Vec2<int>* _pos = nullptr;
		Ak::Maths::Vec2<int>* _size = nullptr;
};

#endif // __AK_STUDIO_CONSOLE__
