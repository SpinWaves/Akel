// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/05/2023
// Updated : 31/05/2023

#ifndef __AK_STUDIO_CODE_EDITOR__
#define __AK_STUDIO_CODE_EDITOR__

#include <AkSpch.h>
#include <Panels/Base/panel.h>
#include <Third_party/TextEditor.h>

enum class Lang
{
	Lua = 0,
	ELTM = 1,
};

struct FileData
{
	std::filesystem::path path;
	std::string name;
	std::string code;
	Lang lang;

	FileData() = default;
	FileData(std::filesystem::path p, std::string n, std::string c) :
		path(std::move(p)), name(std::move(n)), code(std::move(c))
	{}
	~FileData() = default;
};

class CodeEditor : public Panel
{
	public:
		CodeEditor(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project);
		void onUpdate(Ak::Vec2i& size) override;
		void onEvent(Ak::Input& input) override;
		~CodeEditor() = default;

	private:
		TextEditor _code;
		std::vector<FileData> _files;
		std::vector<TextEditor::LanguageDefinition> _lang_defs;
		ImFont* _code_font = nullptr;
		std::size_t _current_file = -1;
		bool _window_focused = false;
		bool _saved = false;
};

#endif
