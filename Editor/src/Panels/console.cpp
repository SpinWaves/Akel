// This file is a part of the Akel editor
// CREATED : 09/07/2021
// UPDATED : 13/07/2021

#include <Panels/console.h>

Console::Console(std::string name, std::shared_ptr<Ak::ELTMcontext> eltm, size_t inputBufferSize) : _sh()
{
	_name = std::move(name);
	_input.resize(inputBufferSize);
	_inBufferSize = inputBufferSize;
	_eltm = eltm;

	_print.push_back(std::pair<std::string, std::array<uint8_t, 3>>("============================", {Ak::Time::getCurrentTime().hour, Ak::Time::getCurrentTime().min, Ak::Time::getCurrentTime().sec})); // Tempo
	_print.push_back(std::pair<std::string, std::array<uint8_t, 3>>(_eltm->getText("Console.welcome"), {Ak::Time::getCurrentTime().hour, Ak::Time::getCurrentTime().min, Ak::Time::getCurrentTime().sec})); // Tempo
	_print.push_back(std::pair<std::string, std::array<uint8_t, 3>>("============================", {Ak::Time::getCurrentTime().hour, Ak::Time::getCurrentTime().min, Ak::Time::getCurrentTime().sec})); // Tempo
}

void Console::render(int width, int height)
{
	_width = width;
	_height = height / 4;

	_WindowAlpha = 1.0f;
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, _WindowAlpha);
	if(!ImGui::Begin(_name.data(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
    {
        ImGui::PopStyleVar();
        ImGui::End();
		Ak::messageBox(ERROR, _eltm->getText("errors.consoleMainWin"), "error from ImGui::Begin()");
        return;
    }
    ImGui::PopStyleVar();

	ImGui::SetWindowSize(ImVec2(width, _height));
	ImGui::SetWindowPos(ImVec2(0, height - _height), true);

	logPart();
	ImGui::Separator();
    inputBar();

    ImGui::End();
}

void Console::logPart()
{
	const float footerHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if(ImGui::BeginChild("Scrolling", ImVec2(0, _height - 75), true))
    {
		static const float timestamp_width = ImGui::CalcTextSize("00:00:00").x;

		for(auto& elem : _print)
		{
			ImGui::PushTextWrapPos();

				ImGui::PushTextWrapPos(ImGui::GetColumnWidth() - timestamp_width);
					ImGui::TextUnformatted(elem.first.data());
				ImGui::PopTextWrapPos();

				ImGui::SameLine(ImGui::GetColumnWidth(-1) - timestamp_width);

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
					ImGui::Text("%02d:%02d:%02d", elem.second[0], elem.second[1], elem.second[2]);
				ImGui::PopStyleColor();

			ImGui::PopTextWrapPos();
		}

		if(_scrollToBottom && (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() || _autoScroll))
			ImGui::SetScrollHereY(1.0f);
		_scrollToBottom = false;
	}

	ImGui::EndChild();
}

void Console::inputBar()
{
	ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackAlways | ImGuiInputTextFlags_AutoSelectAll;

    bool reclaimFocus = false;

	char in[_inBufferSize] = "";

    ImGui::PushItemWidth(-ImGui::GetStyle().ItemSpacing.x * 7);
    if(ImGui::InputText(_eltm->getText("Console.input").c_str(), in, _inBufferSize, inputTextFlags, InputCallback, this))
    {
		_input = in;
		_print.push_back(std::pair<std::string, std::array<uint8_t, 3>>(_input, {Ak::Time::getCurrentTime().hour, Ak::Time::getCurrentTime().min, Ak::Time::getCurrentTime().sec})); // Tempo
        if(!_input.empty())
            _scrollToBottom = true;
        reclaimFocus = true;
		_sh.command(_input);
		_input.clear();
    }
    ImGui::PopItemWidth();

    ImGui::SetItemDefaultFocus();
    if(reclaimFocus)
        ImGui::SetKeyboardFocusHere(-1);
}

int Console::InputCallback(ImGuiInputTextCallbackData *data)
{
	// TODO
    return 0;
}

