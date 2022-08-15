#pragma once

#define REDLUA_NAME "RedLua"
#define REDLUA_VERSION "v0.6.0"
#define REDLUA_VERSION_NUM 060
#define REDLUA_FULLNAME REDLUA_NAME " " REDLUA_VERSION

#ifdef REDLUA_GTAV
#	define REDLUA_GAMECODE "gta5"
#	define REDLUA_HOTKEY_DEFAULT 0x73
#else
#	define REDLUA_GAMECODE "rdr3"
#	define REDLUA_HOTKEY_DEFAULT 0x76
#endif

#define REDLUA_TAGS_URL "https://api.github.com/repos/igor725/RedLua/tags"
#define REDLUA_RELS_URL "https://github.com/igor725/RedLua/releases/tag/"
#define REDLUA_NATIVEDB_URL "https://raw.githubusercontent.com/alloc8or/" REDLUA_GAMECODE "-nativedb-data/master/natives.json"

#define REDLUA_ROOT_DIR ".\\RedLua\\"
#define REDLUA_SCRIPTS_DIR REDLUA_ROOT_DIR "Scripts\\"
#define REDLUA_LANGS_DIR REDLUA_ROOT_DIR "Langs\\"
#define REDLUA_LIBS_DIR "Libs\\"
#define REDLUA_CLIBS_DIR "Libs\\C\\"

#define REDLUA_NATIVES_FILE REDLUA_ROOT_DIR "Natives.json"
#define REDLUA_SETTINGS_FILE REDLUA_ROOT_DIR "Settings.json"
#define REDLUA_LOGCONF_FILE REDLUA_ROOT_DIR "Log.conf"

#define REDLUA_LPATH1 REDLUA_LIBS_DIR "?.lua;"
#define REDLUA_LPATH2 REDLUA_LIBS_DIR "?\\init.lua"

#define REDLUA_CPATH1 REDLUA_CLIBS_DIR "?.dll;"
#define REDLUA_CPATH2 REDLUA_CLIBS_DIR "?\\core.dll"

#define REDLUA_PATHS REDLUA_ROOT_DIR REDLUA_LPATH1 REDLUA_ROOT_DIR REDLUA_LPATH2
#define REDLUA_CPATHS REDLUA_ROOT_DIR REDLUA_CPATH1 REDLUA_ROOT_DIR REDLUA_CPATH2 
