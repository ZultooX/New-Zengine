require "common"

Config = {}
Config["Workspace"] = {}
Config.Workspace["Name"] = "Zengine"
Config.Workspace["Architecture"] = "x64"

Config.Workspace["Defines"] = {
    ["EngineDefines"] = {
        'ZENGINE_ASSETS_PATH=\"' .. path.translate(Dirs.Bin, '/') .. '\"',
        'ZENGINE_MODELS_PATH=\"' .. path.translate(Dirs.Bin .. 'Assets/Models/', '/') .. '\"',
        'ZENGINE_SETTINGS_PATH=\"' .. path.translate(Dirs.Bin .. 'Settings/', '/') .. '\"',
        'ZENGINE_SHADERS_PATH=\"' .. path.translate(Dirs.Bin .. 'Shaders/', '/') .. '\"',
        'ZENGINE_TEXTURES_PATH=\"' .. path.translate(Dirs.Bin .. 'Assets/Textures/', '/') .. '\"',
        -- 'ZENGINE_SHADERS_SOURCE_PATH=\"' .. path.translate(Dirs.Projects, '/Shaders/') .. '\"',
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
