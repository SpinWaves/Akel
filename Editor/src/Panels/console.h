// This file is a part of the Akel editor
// CREATED : 08/07/2021
// UPDATED : 09/07/2021

#ifndef __AK_EDITOR_CONSOLE__
#define __AK_EDITOR_CONSOLE__

#include <AkEpch.h>

class Console
{
	public:
		explicit Console(std::string name, size_t inputBufferSize = 256);
		void render(int width, int height);
		void passELTM(std::shared_ptr<Ak::ELTMcontext> eltm);

	protected:
		std::string _input;
		std::vector<std::string> _print; // Tempo

	private:
		void inputBar();
		void logPart();

		static int InputCallback(ImGuiInputTextCallbackData *data);

		std::string _name;
		std::shared_ptr<Ak::ELTMcontext> _eltm;
		bool _autoScroll;
		bool _coloredOutput;
		bool _scrollToBottom;
		size_t _inBufferSize = 0;
		float _WindowAlpha;

		int _width, _height = 0;
};

#endif // __AK_EDITOR_CONSOLE__

