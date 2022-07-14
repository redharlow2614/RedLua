#include "script.h"
#include "keyboard.h"
#include "easyloggingpp.h"

#define EnsureDirectory(D) (!CreateDirectory(D, NULL) ? ERROR_ALREADY_EXISTS == GetLastError() : true)
el::Configurations conf("RedLua\\log.conf");
BOOL hasConsole = false;

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
	switch(reason) {
		case DLL_PROCESS_ATTACH:
			el::Loggers::reconfigureLogger("default", conf);
			if(el::Loggers::getLogger("default")->typedConfigurations()->toStandardOutput(el::Level::Global)) {
				if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
					freopen("CONOUT$", "w", stdout);
					freopen("CONOUT$", "w", stderr);
					hasConsole = true;
				}
			}
			LOG(INFO) << "Logger initialized";

			if(!EnsureDirectory("RedLua")
			|| !EnsureDirectory("RedLua\\Scripts"))
				break;

			scriptRegister(hInstance, ScriptMain);
			keyboardHandlerRegister(OnKeyboardMessage);
			break;
		case DLL_PROCESS_DETACH:
			scriptUnregister(hInstance);
			keyboardHandlerUnregister(OnKeyboardMessage);
			ScriptFinish();
			if(hasConsole && !FreeConsole())
				LOG(ERROR) << "Failed to free console";
			break;
	}

	return TRUE;
}
