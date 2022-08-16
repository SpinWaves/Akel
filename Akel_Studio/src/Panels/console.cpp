// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 09/07/2021
// Updated : 16/08/2022

#include <Panels/console.h>
#include <Fonts/material_font.h>

Console::Console(std::shared_ptr<Ak::ELTM> eltm, size_t inputBufferSize) : Panel("__console"), _sh(eltm)
{
	_input.resize(inputBufferSize);
	_inBufferSize = inputBufferSize;

    _eltm = std::move(eltm);

	ee = Ak::AudioManager::loadSound(Ak::Core::getMainDirPath() + "ressources/sounds/42.wav");

	_sh.print("============================");
	_sh.print(_eltm->getLocalText("Console.welcome"));
	_sh.print("============================");
}

void Console::onEvent(Ak::Input& input)
{
	if(_sh.quit())
		input.finish();
}

void Console::onUpdate(Ak::Maths::Vec2<int>& size)
{
	_height = size.Y / 4;
	if(ImGui::Begin(std::string(AKS_ICON_MD_TERMINAL" " + _eltm->getLocalText("Console.name")).data(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
		logPart();
		ImGui::Separator();
		inputBar();

		ImGui::End();
    }
}

void Console::logPart()
{
	const float footerHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if(ImGui::BeginChild("Scrolling", ImVec2(0, _height - 75), true))
    {
		static const float timestamp_width = ImGui::CalcTextSize("00:00:00").x;

		for(auto& elem : _sh.getOutPut())
		{
			ImGui::PushTextWrapPos();

				ImGui::PushTextWrapPos(ImGui::GetColumnWidth() - timestamp_width);
				if(std::get<0>(elem) == 0)
					ImGui::TextUnformatted(std::get<1>(elem).data());
				else if(std::get<0>(elem) == 1)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.365f, 0.365f, 1.0f));
						ImGui::TextUnformatted(std::get<1>(elem).data());
					ImGui::PopStyleColor();
				}
				else if(std::get<0>(elem) == 2)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
						ImGui::TextUnformatted(std::get<1>(elem).data());
					ImGui::PopStyleColor();
				}
				ImGui::PopTextWrapPos();

				ImGui::SameLine(ImGui::GetColumnWidth(-1) - timestamp_width);

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
					ImGui::Text("%02d:%02d:%02d", std::get<2>(elem).hour, std::get<2>(elem).min, std::get<2>(elem).sec);
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
    if(ImGui::InputText(_eltm->getLocalText("Console.input").c_str(), in, _inBufferSize, inputTextFlags, InputCallback, this))
    {
		_input = in;
		_sh.command(_input);
		if(!_input.empty())
			_scrollToBottom = true;
		reclaimFocus = true;
		_input.clear();
		if(_sh.ee)
			Ak::AudioManager::playSound(ee);
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
