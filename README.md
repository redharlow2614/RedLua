# Lua scripting mod for Red Dead Redemption 2

RedLua is a ScriptHookRDR2 library that simplifies the process of modifying the game.

## Installation

Download the latest [release](https://github.com/igor725/RedLua/releases) and extract the archive contents into your game folder.

## Usage
Press F7 to open the RedLua menu. Here you can load/reload/stop/unload scripts, reload the NativeDB and change library settings.


## Scripting

RedLua searches for scripts in the `<Your game directory>\RedLua\Scripts\` folder. Each script located in this folder will be loaded automatically (If the `Autorun feature` is enabled). Every script should return a `table` (can be empty) with functions `OnLoad`, `OnTick`, `OnStop`.

Example:
```lua
local t = {}

function t.OnLoad()
	print('Yay!')
end

function t.OnTick()
	print('Tick!')
end

function t.OnStop()
	print('Goodbye!')
end

return t
```

### There are two ways to call native functions:
1. `native.call('PLAYER', 'PLAYER_ID')`
2. `PLAYER:GET_PLAYER_PED(PLAYER:PLAYER_ID())`

Note that the native functions can return RedLua's `userdata` called `NativeObject`. Each `NativeObject` has its own type (like `const char *`, `Ped`, `Vehicle`, `Entity *`, `Vector`, etc), as Lua-values, the native functions return (take) only the following types: `boolean`, `int`, `float`, `Hash`, `Any` and `string` (take only). Also, `NativeObjects` that are pointers, can be indexed.

Native functions that expect a parameter of type `Any *` as an argument can take a `cdata` value. Here is the example:
```lua
-- This script will display an in-game toast notification for 2 seconds when F8 key is released
local t = {}

function t.OnTick()
	if misc.iskeyjustup(VK_F8, true) then
		local duration = ffi.new([[
			struct {
				int duration;
				int some_weird_padding[14];
			}
		]], {
			2000 -- 2000 milliseconds
		})

		local data = ffi.new([[
			struct {
				uint64_t _offset;
				const char *title;
				const char *text;
				uint64_t _offset2;
				uint64_t iconDict;
				uint64_t icon;
				uint64_t iconColor;
			}
		]], {
			0,
			MISC:VAR_STRING(10, 'LITERAL_STRING', 'Hello, RedLua!'):topointer(),
			MISC:VAR_STRING(10, 'LITERAL_STRING', jit.version):topointer(),
			0,
			MISC:GET_HASH_KEY('HUD_TOASTS'), MISC:GET_HASH_KEY('toast_player_deadeye'),
			MISC:GET_HASH_KEY('COLOR_RED')
		})

		UIFEED:_UI_FEED_POST_SAMPLE_TOAST(duration, data, true, true)
	end
end

return t
```

Here is a list of all the Lua functions provided by the RedLua library:
```lua
--[[
	Library: native
]]

-- Cast native object to poimter
NativeObject:topointer()

-- Invoke the native function
native.call('PLAYER', 'PLAYER_ID') -- Faster
PLAYER:PLAYER_ID() -- Simpler, but uses a lot of metacalls

-- Get the information abot the function
native.info('BUILTIN', 'WAIT') -- Returns: {hash = '0x4EDE34FBADD967A6', build = 1207, returns = 'void', params = {[1] = {type = 'int', name = 'ms'}}} or nothing if specified function does not exists

-- Create new typed array
native.new('Vehicle', 5) -- Returns: NativeObject of 5 Vehicles

-- Create new vector
native.vector(13.37, 66.6, 12.3) -- Returns: NativeVector, can be used in functions like ENTITY:GET_ENTITY_MATRIX(...)

-- Get all world objects
native.allobjects(objects_typed_array) -- Returns: objects count
native.allpeds(peds_typed_array)
native.allpickups(pickups_typed_array)
native.allvehicles(vehicles_typed_array)

--[[
	Library: misc
]]

-- Is key down for the last 5 seconds
misc.iskeydown(VK_*)

-- Is key down for the last 30 seconds
misc.iskeydownlong(VK_*)

-- Is key just up
misc.iskeyjustup(VK_*, exclusive = false)

-- Reset key state
misc.resetkey(VK_*)

-- Get game version
misc.gamever() -- Returns: number, e.g. 1436.31
```
