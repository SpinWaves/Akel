// This file is a part of the Akel editor
// CREATED : 09/07/2021
// UPDATED : 09/07/2021

#include <Panels/console.h>

Console::Console(std::string name, size_t inputBufferSize)
{
	_name = std::move(name);
	_input.resize(inputBufferSize);
	_inBufferSize = inputBufferSize;

	_print.push_back("============================");
	_print.push_back("Welcome to Akel Editor !");
	_print.push_back("============================");
}

void Console::render(int width, int height)
{
	_width = width;
	_height = height;

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
	ImGui::SetWindowSize(ImVec2(width, height / 5));
	ImGui::SetWindowPos(ImVec2(0, height - height / 5), true);

	logPart();
	ImGui::Separator();
    inputBar();

    ImGui::End();
}

void Console::logPart()
{
	const float footerHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if(ImGui::BeginChild("Scrolling", ImVec2(0, (_height / 5) - 75), true))
    {
		static const float timestamp_width = ImGui::CalcTextSize("00:00:00:0000").x;
		int count = 0;

		for(int i = 0; i < _print.size(); i++)
		{
			ImGui::PushTextWrapPos();

				ImGui::PushTextWrapPos(ImGui::GetColumnWidth() - timestamp_width);
					ImGui::TextUnformatted(_print[i].data());
				ImGui::PopTextWrapPos();

				ImGui::SameLine(ImGui::GetColumnWidth(-1) - timestamp_width);

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
					ImGui::Text("%02d:%02d:%02d:%04d", ((12 / 1000 / 3600) % 24), ((12 / 1000 / 60) % 60), ((12 / 1000) % 60), 12 % 1000);
				ImGui::PopStyleColor();

			ImGui::PopTextWrapPos();
		}

		if(_scrollToBottom && (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() || _autoScroll))
			ImGui::SetScrollHereY(1.0f);
		_scrollToBottom = false;
	}

	ImGui::EndChild();
}

void Console::passELTM(std::shared_ptr<Ak::ELTMcontext> eltm)
{
	_eltm = eltm;
}

void Console::inputBar()
{
	ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackAlways;

    bool reclaimFocus = false;

	char in[_inBufferSize] = "";

    ImGui::PushItemWidth(-ImGui::GetStyle().ItemSpacing.x * 7);
    if(ImGui::InputText(_eltm->getText("Console.input").c_str(), in, IM_ARRAYSIZE(in), inputTextFlags, InputCallback, this))
    {
		_input = in;
		_print.push_back(_input);
        if(!_input.empty())
            _scrollToBottom = true;
        reclaimFocus = true;
		_input.clear();
    }
    ImGui::PopItemWidth();

    ImGui::SetItemDefaultFocus();
    if(reclaimFocus)
        ImGui::SetKeyboardFocusHere(-1);
}

int Console::InputCallback(ImGuiInputTextCallbackData *data)
{

    if(data->BufTextLen == 0 && (data->EventFlag != ImGuiInputTextFlags_CallbackHistory))
        return 0;

    std::string input_str = data->Buf;
    std::string trim_str;
    auto console = static_cast<Console*>(data->UserData);

    size_t startPos = console->_input.find_first_not_of(' ');
    size_t endPos = console->_input.find_last_not_of(' ');

    if(startPos != std::string::npos && endPos != std::string::npos)
        trim_str = console->_input.substr(startPos, endPos + 1);
    else
        trim_str = console->_input;

    switch (data->EventFlag)
    {
        case ImGuiInputTextFlags_CallbackCompletion:
        {
            size_t startSubtrPos = trim_str.find_last_of(' ');
            //csys::AutoComplete *console_autocomplete;

            if(startSubtrPos == std::string::npos)
            {
                startSubtrPos = 0;
                //console_autocomplete = &console->m_ConsoleSystem.CmdAutocomplete();
            }
            else
            {
                startSubtrPos += 1;
                //console_autocomplete = &console->m_ConsoleSystem.VarAutocomplete();
            }

            if(!trim_str.empty())
            {
                //if(!console->m_CmdSuggestions.empty())
                //{
                    //console->m_ConsoleSystem.Log(csys::COMMAND) << "Suggestions: " << csys::endl;

                    //for (const auto &suggestion : console->m_CmdSuggestions)
                        //console->m_ConsoleSystem.Log(csys::LOG) << suggestion << csys::endl;

                    //console->m_CmdSuggestions.clear();
                //}

                //std::string partial = console_autocomplete->Suggestions(trim_str.substr(startSubtrPos, endPos + 1), console->m_CmdSuggestions);

                //if(!console->m_CmdSuggestions.empty() && console->m_CmdSuggestions.size() == 1)
                //{
                    //data->DeleteChars(static_cast<int>(startSubtrPos), static_cast<int>(data->BufTextLen - startSubtrPos));
                    //data->InsertChars(static_cast<int>(startSubtrPos), console->m_CmdSuggestions[0].data());
                    //console->m_CmdSuggestions.clear();
                //}
                //else
                //{
                    //if(!partial.empty())
                    //{
                        //data->DeleteChars(static_cast<int>(startSubtrPos), static_cast<int>(data->BufTextLen - startSubtrPos));
                        //data->InsertChars(static_cast<int>(startSubtrPos), partial.data());
                    //}
                //}
            }

            //console->m_WasPrevFrameTabCompletion = true;
        }
            break;

        case ImGuiInputTextFlags_CallbackHistory:
        {
            data->DeleteChars(0, data->BufTextLen);

            //if(console->m_HistoryIndex == std::numeric_limits<size_t>::min())
                //console->m_HistoryIndex = console->m_ConsoleSystem.History().GetNewIndex();

            if(data->EventKey == ImGuiKey_UpArrow)
            {
                //if(console->m_HistoryIndex)
					//console->m_HistoryIndex--;
            }
            else
            {
                //if(console->m_HistoryIndex < console->m_ConsoleSystem.History().Size())
					//console->m_HistoryIndex++;
            }

            //std::string prevCommand = console->m_ConsoleSystem.History()[console->m_HistoryIndex];

            //data->InsertChars(data->CursorPos, prevCommand.data());
        }
            break;

        case ImGuiInputTextFlags_CallbackCharFilter:
        case ImGuiInputTextFlags_CallbackAlways:
        default:
            break;
    }
    return 0;
}

