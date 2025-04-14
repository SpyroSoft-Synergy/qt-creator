// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include "../luaengine.h"

#include <coreplugin/generatedfile.h>
#include <coreplugin/editormanager/editormanager.h>
#include <texteditor/texteditor.h>

using namespace Core;

namespace Lua::Internal {

void setupCoreModule()
{
    registerProvider("Core", [](sol::state_view lua) -> sol::object {
        sol::table core = lua.create_table();

        auto generatedFileType = core.new_usertype<GeneratedFile>(
            "GeneratedFile",
            "filePath",
            sol::property(&GeneratedFile::filePath, &GeneratedFile::setFilePath),
            "contents",
            sol::property(&GeneratedFile::contents, &GeneratedFile::setContents),
            "attributes",
            sol::property([](GeneratedFile *f) -> int { return f->attributes().toInt(); },
                          [](GeneratedFile *f, int flags) {
                              f->setAttributes(GeneratedFile::Attributes::fromInt(flags));
                          }),
            "isBinary",
            sol::property(&GeneratedFile::isBinary, &GeneratedFile::setBinary));

        // clang-format off
        generatedFileType["Attribute"] = lua.create_table_with(
            "OpenEditorAttribute", GeneratedFile::OpenEditorAttribute,
            "OpenProjectAttribute", GeneratedFile::OpenProjectAttribute,
            "CustomGeneratorAttribute", GeneratedFile::CustomGeneratorAttribute,
            "KeepExistingFileAttribute", GeneratedFile::KeepExistingFileAttribute,
            "ForceOverwrite", GeneratedFile::ForceOverwrite,
            "TemporaryFile", GeneratedFile::TemporaryFile
        );
        // clang-format on

        core.new_enum("OpenEditorFlag",
            "NoFlags", EditorManager::OpenEditorFlag::NoFlags,
            "DoNotChangeCurrentEditor", EditorManager::OpenEditorFlag::DoNotChangeCurrentEditor,
            "IgnoreNavigationHistory", EditorManager::OpenEditorFlag::IgnoreNavigationHistory,
            "DoNotMakeVisible", EditorManager::OpenEditorFlag::DoNotMakeVisible,
            "OpenInOtherSplit", EditorManager::OpenEditorFlag::OpenInOtherSplit,
            "DoNotSwitchToDesignMode", EditorManager::OpenEditorFlag::DoNotSwitchToDesignMode,
            "DoNotSwitchToEditMode", EditorManager::OpenEditorFlag::DoNotSwitchToEditMode,
            "SwitchSplitIfAlreadyVisible", EditorManager::OpenEditorFlag::SwitchSplitIfAlreadyVisible,
            "DoNotRaise", EditorManager::OpenEditorFlag::DoNotRaise,
            "AllowExternalEditor", EditorManager::OpenEditorFlag::AllowExternalEditor
        );

        auto editorManager = core.new_usertype<EditorManager>(
            "EditorManager",
            sol::no_constructor);

        editorManager["openEditor"] = [](const Utils::FilePath &filePath,
            EditorManager::OpenEditorFlag flags = EditorManager::OpenEditorFlag::NoFlags) -> QPointer<TextEditor::BaseTextEditor> {
            IEditor* editor = EditorManager::openEditor(filePath, Utils::Id::generate(), flags);
            return dynamic_cast<TextEditor::BaseTextEditor*>(editor);
        };
        
        return core;
    });
}

} // namespace Lua::Internal
