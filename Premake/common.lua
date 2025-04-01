-- Common definitions and global defines.

Dirs = {}
Dirs["Root"]        =   os.realpath("../")
Dirs["Temp"]        =   os.realpath(Dirs.Root .. "Temp/")
Dirs["Bin"]         =   os.realpath(Dirs.Root .. "Bin/")
Dirs["Shaders"]     =   os.realpath(Dirs.Bin .. "Shaders/")
Dirs["Settings"]    =   os.realpath(Dirs.Bin .. "Settings/")

Dirs["Projects"]                    = {}
Dirs.Projects["Root"]               = path.translate(os.realpath(Dirs.Root .. "Source/"), '/')
Dirs.Projects["Game"]               = path.translate(os.realpath(Dirs.Projects.Root .. "Game/"), '/')
Dirs.Projects["Launcher"]           = path.translate(os.realpath(Dirs.Projects.Root .. "Launcher/"), '/')
Dirs.Projects["Shaders"]            = path.translate(os.realpath(Dirs.Projects.Root .. "Shaders/"), '/')


Dirs.Projects["Externals"] = {};
Dirs.Projects.Externals["Root"]             = path.translate(os.realpath(Dirs.Projects.Root .. "Externals/"), '/')


Dirs.Projects.Externals["External"]         = path.translate(os.realpath(Dirs.Projects.Externals.Root  .. "/External/"), '/')
Dirs.Projects.Externals["ImGui"]            = path.translate(os.realpath(Dirs.Projects.Externals.Root .. "/ImGui/"), '/')
Dirs.Projects.Externals["Zultools"]         = path.translate(os.realpath(Dirs.Projects.Externals.Root .. "/Zultools/"), '/')
Dirs.Projects.Externals["nlohmann"]         = path.translate(os.realpath(Dirs.Projects.Externals.Root .. "/nlohmann/"), '/')

Dirs.Projects["Systems"] = {};
Dirs.Projects.Systems["Root"]               = path.translate(os.realpath(Dirs.Projects.Root .. "Systems/"), '/')
Dirs.Projects.Systems["ECS"]                = path.translate(os.realpath(Dirs.Projects.Systems.Root .. "ECS/"), '/')

Dirs.Projects["Engines"] = {};
Dirs.Projects.Engines["Root"]               = path.translate(os.realpath(Dirs.Projects.Root .. "Engines/"), '/')
Dirs.Projects.Engines["GraphicsEngine"]     = path.translate(os.realpath(Dirs.Projects.Engines.Root .. "GraphicsEngine/"), '/')
Dirs.Projects.Engines["Engine"]             = path.translate(os.realpath(Dirs.Projects.Engines.Root .. "Engine/"), '/')
Dirs.Projects.Engines["PhysicsEngine"]      = path.translate(os.realpath(Dirs.Projects.Engines.Root .. "PhysicsEngine/"), '/')


Dirs["Assets"] = {}
Dirs.Assets["Root"] = path.translate(os.realpath(Dirs.Bin .. "Assets/"), '/')
Dirs.Assets["Fonts"] = path.translate(os.realpath(Dirs.Assets.Root .. "Fonts/"), '/')
Dirs.Assets["Models"] = path.translate(os.realpath(Dirs.Assets.Root .. "Models/"), '/')
Dirs.Assets["Sprites"] = path.translate(os.realpath(Dirs.Assets.Root .. "Sprites/"), '/')
Dirs.Assets["Textures"] = path.translate(os.realpath(Dirs.Assets.Root .. "Textures/"), '/')
Dirs.Assets["Materials"] = path.translate(os.realpath(Dirs.Assets.Root .. "Materials/"), '/')


function create_directories(directories)
    for key, v in pairs(directories) do
        if type(v) == "string" and not os.isdir(v) then
            os.mkdir(v)
            print('created: ' .. v)
        elseif type(v) == "table" then
            create_directories(v)
        end
    end
end

create_directories(Dirs)