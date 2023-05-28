// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/05/2023
// Updated : 28/05/2023

#ifndef __AK_STUDIO_CODE_EDITOR__
#define __AK_STUDIO_CODE_EDITOR__

#include <AkSpch.h>
#include <Panels/Base/panel.h>
#include <Third_party/TextEditor.h>

class CodeEditor : public Panel
{
	public:
		CodeEditor(std::shared_ptr<Ak::ELTM> eltm, Ak::Core::ProjectFile& project);
		void onUpdate(Ak::Vec2i& size) override;
		~CodeEditor() = default;

	private:
		TextEditor _code;
		std::filesystem::path _file;
};

#endif
