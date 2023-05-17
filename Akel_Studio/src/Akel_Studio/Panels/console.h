// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/07/2021
// Updated : 17/05/2023

#ifndef __AK_STUDIO_CONSOLE__
#define __AK_STUDIO_CONSOLE__

#include <AkSpch.h>
#include <Panels/shell/shell.h>
#include <Panels/Base/panel.h>

class Console : public Panel
{
	public:
		Console(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project, size_t inputBufferSize = 256);
		void onUpdate(Ak::Maths::Vec2<int>& size) override;
		void onEvent(Ak::Input& input) override;
		~Console();

	protected:
		std::string _input;

	private:
		void inputBar();
		void logPart();

		static int InputCallback(ImGuiInputTextCallbackData *data);

	private:
		Shell _sh;

		Ak::Sound _ee;

		Ak::Maths::Vec2<int>* _pos = nullptr;
		Ak::Maths::Vec2<int>* _size = nullptr;

		float _WindowAlpha;
		size_t _inBufferSize = 0;
		bool _autoScroll;
		bool _coloredOutput;
		bool _scrollToBottom;
};

#endif // __AK_STUDIO_CONSOLE__
