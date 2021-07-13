// This file is a part of the Akel editor
// CREATED : 08/07/2021
// UPDATED : 13/07/2021

#ifndef __AK_EDITOR_CONSOLE__
#define __AK_EDITOR_CONSOLE__

#include <AkEpch.h>
#include <Panels/shell/shell.h>

class Console
{
	public:
		explicit Console(std::string name, std::shared_ptr<Ak::ELTMcontext> eltm, size_t inputBufferSize = 256);
		void render(int width, int height);

	protected:
		std::string _input;
		std::vector<std::pair<std::string, std::array<uint8_t, 3>>> _print; // Tempo

	private:
		void inputBar();
		void logPart();

		static int InputCallback(ImGuiInputTextCallbackData *data);

		std::string _name;
		std::shared_ptr<Ak::ELTMcontext> _eltm;
		Shell _sh;
		bool _autoScroll;
		bool _coloredOutput;
		bool _scrollToBottom;
		size_t _inBufferSize = 0;
		float _WindowAlpha;

		int _width, _height = 0;
};

#endif // __AK_EDITOR_CONSOLE__

