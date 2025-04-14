---@meta Core

Core = {}

---@enum Attribute
Core.GeneratedFile.Attribute = {
    OpenEditorAttribute = 0,
    OpenProjectAttribute = 0,
    CustomGeneratorAttribute = 0,
    KeepExistingFileAttribute = 0,
    ForceOverwrite = 0,
    TemporaryFile = 0,
}

---@class GeneratedFile
---@field filePath FilePath
---@field contents string
---@field isBinary boolean
---@field attributes Attribute A combination of Attribute.
Core.GeneratedFile = {}

---Create a new GeneratedFile.
---@return GeneratedFile
function Core.GeneratedFile.new() end

---@enum OpenEditorFlag
Core.OpenEditorFlag = {
    NoFlags = 0,
    DoNotChangeCurrentEditor = 0,
    IgnoreNavigationHistory = 0,
    DoNotMakeVisible = 0,
    OpenInOtherSplit = 0,
    DoNotSwitchToDesignMode = 0,
    DoNotSwitchToEditMode = 0,
    SwitchSplitIfAlreadyVisible = 0,
    DoNotRaise = 0,
    AllowExternalEditor = 0,
}

---@class EditorManager
Core.EditorManager = {}

---Open editor for given FilePath
---@param filePath Path to file
---@param flags OpenEditorFlag
---@return BaseTextEditor
function Core.EditorManager.openEditor(filePath, flags) end

return Core;
