// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/05/2023
// Updated : 07/06/2023

#include <Panels/code.h>
#include <Fonts/material_font.h>

const TextEditor::Palette& getPalette()
{
	const static TextEditor::Palette p = { {
		0xff7f7f7f,	// Default
		0xffc086c5,	// Keyword
		0xffa8ceb5,	// Number
		0xff7991ce,	// String
		0xff7991ce,	// Char literal
		0xffffffff, // Punctuation
		0xff408080,	// Preprocessor
		0xffd4d4d4, // Identifier
		0xffd69c56, // Known identifier
		0xffd69c56, // Preproc identifier
		0xff4d8a5f, // Comment (single line)
		0xff4d8a5f, // Comment (multi line)
		0xff171717, // Background
		0xffe0e0e0, // Cursor
		0x80a06020, // Selection
		0x800020ff, // ErrorMarker
		0x40f08000, // Breakpoint
		0xff595554, // Line number
		0x40000000, // Current line fill
		0x40808080, // Current line fill (inactive)
		0x40a0a0a0, // Current line edge
	} };
	return p;
}

const TextEditor::LanguageDefinition& ELTMLang()
{
	static bool inited = false;
	static TextEditor::LanguageDefinition langDef;
	if(!inited)
	{
		static const char* const keywords[] = {
			"begin", "module", "end", "let", "import"
		};

		for(auto& k : keywords)
			langDef.mKeywords.insert(k);

		static const char* const identifiers[] = {
			"get"
		};
		for(auto& k : identifiers)
		{
			TextEditor::Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.mIdentifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", TextEditor::PaletteIndex::String));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[\\(\\)\\=]", TextEditor::PaletteIndex::Punctuation));

		langDef.mCommentStart = "/*";
		langDef.mCommentEnd = "*/";
		langDef.mSingleLineComment = "//";

		langDef.mCaseSensitive = true;
		langDef.mAutoIndentation = false;

		langDef.mName = "ELTM";

		inited = true;
	}
	return langDef;
}

CodeEditor::CodeEditor(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project) : Panel("__code_editor", project)
{
	_eltm = std::move(eltm);
	auto lua_lang = TextEditor::LanguageDefinition::Lua();

	std::vector<const char*> identifiers = {
		"Ak", "Message", "Warning", "StrongWarning", "Error", "FatalError", "AkelOnInit", "AkelOnUpdate", "AkelOnQuit",
		"getInKey", "getInMouse", "isMouseMoving", "getMouseX", "getMouseY", "getMouseXRel", "getMouseYRel", "finish",
		"run", "up", "down", "action", "Vec2", "Vec3", "Vec4", "switchToScene", "TransformAttribute", "AudioAttribute",
		"getAttribute", "key", "mouse",
		"A","B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
		"X", "Y", "Z", "k0", "k1", "k2", "k3", "k4", "k5", "k6", "k7", "k8", "k9", "left", "right", "middle", "x1", "x2"
	};
	for(const char* str : identifiers)
	{
		TextEditor::Identifier id;
		id.mDeclaration = "Built-in Akel";
		lua_lang.mIdentifiers.insert(std::make_pair(std::string(str), id));
	}
	lua_lang.mAutoIndentation = true;

	_lang_defs.push_back(lua_lang);
	_lang_defs.push_back(ELTMLang());

	_code.SetTabSize(3);
	_code.SetShowWhitespaces(false);
	_code.SetPalette(getPalette());

	ImGuiIO& io = ImGui::GetIO();
	_code_font = io.Fonts->AddFontFromFileTTF(std::string(std::filesystem::path(Ak::VFS::getMainDirPath() / "resources/fonts/sono/Sono-Medium.ttf").string()).c_str(), 13.0f);
}

void CodeEditor::onEvent(Ak::Input& input)
{
	if(!_window_focused)
		return;
	if((input.getInKey(AK_KEY_RCTRL) || input.getInKey(AK_KEY_LCTRL)) && input.getInKey(AK_KEY_S))
	{
		if(_current_file != -1 && _current_file < _files.size())
		{
			std::ofstream f(_files[_current_file].path);
			if(f.good())
			{
				std::string str(_code.GetText());
				str.pop_back(); // remove new line
				f << str;
				_saved = true;
			}
		}
	}
}

void CodeEditor::onUpdate(Ak::Vec2i& size)
{
	static int selected = -1;
	if(ImGui::Begin(std::string(AKS_ICON_MD_CODE" " + _eltm->getText("Code.name")).c_str(), nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		_window_focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
		if(ImGui::BeginMenuBar())
		{
			if(ImGui::BeginMenu(std::string(AKS_ICON_MD_FOLDER" " + _eltm->getText("Code.file")).c_str()))
			{
				if(ImGui::MenuItem(std::string(AKS_ICON_MD_FILE_OPEN" " + _eltm->getText("Code.open")).c_str()))
				{
					auto file = pfd::open_file(_eltm->getText("Code.load"), _project.getDir().string(), { "Script files (.lua, .eltm, .tm)", "*.lua *.eltm *.tm", "All files", "*"});
					if(!file.result().empty())
					{
						std::filesystem::path path = file.result()[0];
						std::ifstream f(path);
						if(f.good())
						{
							std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
							_code.SetText(str);
							_files.emplace_back(path, path.filename().string(), std::move(str));
							if(path.extension() == ".lua")
							{
								_files.back().lang = Lang::Lua;
								_code.SetLanguageDefinition(_lang_defs[static_cast<int>(Lang::Lua)]);
							}
							else if(path.extension() == ".eltm" || path.extension() == ".tm")
							{
								_files.back().lang = Lang::ELTM;
								_code.SetLanguageDefinition(_lang_defs[static_cast<int>(Lang::ELTM)]);
							}
							_current_file = _files.size() - 1;
							selected = _current_file;
						}
					}
				}
				if(ImGui::MenuItem(std::string(AKS_ICON_MD_SAVE" " + _eltm->getText("Code.save")).c_str(), "Ctrl+S"))
				{
					if(_current_file != -1 && _current_file < _files.size())
					{
						std::ofstream f(_files[_current_file].path);
						if(f.good())
						{
							std::string str(_code.GetText());
							str.pop_back(); // remove new line
							f << str;
							_saved = true;
						}
					}
				}
				if(ImGui::MenuItem(std::string(AKS_ICON_MD_SAVE_AS" " + _eltm->getText("Code.save_as")).c_str()))
				{
					if(_current_file != -1 && _current_file < _files.size())
					{
						std::filesystem::path file = pfd::save_file("Select a file", ".", { "Lua File", ".lua", "All Files", "*" }, pfd::opt::force_overwrite).result();
						std::ofstream f(file);
						if(f.good())
						{
							_files[_current_file].path = std::move(file);
							std::string str(_code.GetText());
							str.pop_back(); // remove new line
							f << str;
							_saved = true;
						}
					}
				}
				ImGui::EndMenu();
			}
			if(_saved)
			{
				ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(_eltm->getText("Code.saved").data()).x - 25);
				ImGui::TextUnformatted(_eltm->getText("Code.saved").data());
			}
			ImGui::EndMenuBar();
		}
		if(ImGui::BeginChild("CodePanelSide", ImVec2(200, 0), true))
		{
			int i = 0;
			for(FileData& data : _files)
			{
				if(ImGui::Selectable(std::string(AKS_ICON_MD_CODE" " + data.name).data(), selected == i))
				{
					selected = i;
					if(selected != _current_file)
					{
						_files[_current_file].code = _code.GetText();
						_files[_current_file].code.pop_back(); // to remove new line every time
						_code.SetText(data.code);
						_current_file = selected;
						_code.SetLanguageDefinition(_lang_defs[static_cast<int>(_files[_current_file].lang)]);
					}
				}
				i++;
			}
			ImGui::EndChild();
		}
		ImGui::SameLine(0);
		if(_code.IsTextChanged())
			_saved = false;
		ImGui::PushFont(_code_font);
			_code.Render("Code", ImVec2(), true);
		ImGui::PopFont();
		ImGui::End();
	}
}
