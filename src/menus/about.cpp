#include "menus\helpers.hpp"
#include "menus\about.hpp"
#include "constants.hpp"
#include "langctl.hpp"

MenuBase *CreateAbout(MenuController *controller) {
	auto menu = new MenuBase(new MenuItemTitle(Lng.Get("core.main.about")));
	controller->RegisterMenu(menu);

	menu->AddItem(new MenuItemLink("RedLua: igor725", "https://github.com/igor725/RedLua"));
	menu->AddItem(new MenuItemLink("LuaJIT: Mike Pall", "https://github.com/LuaJIT/LuaJIT"));
	menu->AddItem(new MenuItemLink("UI/ScriptHook: Alexander Blade", "https://www.dev-c.com/rdr2/scripthookrdr2/"));
	menu->AddItem(new MenuItemLink("NativeDB: alloc8or", "https://github.com/alloc8or/rdr3-nativedb-data"));
	menu->AddItem(new MenuItemLink("JSON parser: Niels Lohmann", "https://github.com/nlohmann/json"));
	menu->AddItem(new MenuItemLink("Logging: abumusamq", "https://github.com/amrayn/easyloggingpp"));

	return menu;
}
