require "common"

Config = {}
Config["Workspace"] = {}
Config.Workspace["Name"] = "Zengine"
Config.Workspace["Architecture"] = "x64"

Config.Workspace["Defines"] = {
    ["EngineDefines"] = {
        'ZENGINE_BIN_PATH=\"' .. path.translate(Dirs.Bin , '/') .. '\"',
        'ZENGINE_ASSETS_PATH=\"' .. path.translate(Dirs.Bin .. 'Assets/', '/') .. '\"',
        'ZENGINE_MODELS_PATH=\"' .. path.translate(Dirs.Bin .. 'Assets/Models/', '/') .. '\"',
        'ZENGINE_SETTINGS_PATH=\"' .. path.translate(Dirs.Bin .. 'Settings/', '/') .. '\"',
        'ZENGINE_VERTEX_SHADERS_PATH=\"' .. path.translate(Dirs.Bin .. 'Shaders/Vertex/', '/') .. '\"',
        'ZENGINE_PIXEL_SHADERS_PATH=\"' .. path.translate(Dirs.Bin .. 'Shaders/Pixel/', '/') .. '\"',
        'ZENGINE_SHADERS_PATH=\"' .. path.translate(Dirs.Bin .. 'Shaders/', '/') .. '\"',
        'ZENGINE_TEXTURES_PATH=\"' .. path.translate(Dirs.Bin .. 'Assets/Textures/', '/') .. '\"',
        'ZENGINE_MATERIALS_PATH=\"' .. path.translate(Dirs.Bin .. 'Assets/Materials/', '/') .. '\"',
        -- 'ZENGINE_SHADERS_SOURCE_PATH=\"' .. path.translate(Dirs.Projects, '/Shaders/') .. '\"',
        'ZENGINE_ENGINE_ASSETS_PATH=\"' .. path.translate(Dirs.Bin .. 'Engine Assets/', '/') .. '\"',
        'ZENGINE_ENGINE_EDITOR_ICONS_PATH=\"' .. path.translate(Dirs.Bin .. 'Engine Assets/Editor Icons/', '/') .. '\"',
        'ZENGINE_ENGINE_MODELS_PATH=\"' .. path.translate(Dirs.Bin .. 'Engine Assets/Models/', '/') .. '\"',
        'ZENGINE_ENGINE_TEXTURES_PATH=\"' .. path.translate(Dirs.Bin .. 'Engine Assets/Textures/', '/') .. '\"',
        'USE_DX11',
    },
}


workspace(Config.Workspace.Name)
location(Config.Workspace.Location)
architecture(Config.Workspace.Architecture)
startproject "Launcher"
defines(Config.Workspace.Defines.EngineDefines)

configurations {
    'Debug',
    'Release',
    'Retail'
}

Config.Workspace["ForceIncludeFiles"] = {
    Dirs.Projects.Root .. "EngineDefines.h",
    -- Dirs.Root .. "CodeGen/code_gen_defines.h",
}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"






local function include_projects(projects)
    for _, v in pairs(projects) do
        if type(v) == "string" then
            if v ~= "Root" then
                if os.isfile(path.join(v, 'premake5.lua')) then
                    include(v)
                end
            end
        elseif type(v) == "table" then
            group(_)
            include_projects(v)
            group ""
        end
    end
end

-- Include Projects
include_projects(Dirs.Projects)
