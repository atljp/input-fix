#include <Logger/Logger.h>

bool l_ExitOnAssert = true;
bool l_UseConsole, l_DebugOutput;
FILE* CON, * f_tracer, * f_logger;
HANDLE consoleHandle;
char dump_name[] = "dump";

namespace Log {

	bool ConsoleAllowed() { return l_UseConsole; }
	bool OutputAllowed() { return l_DebugOutput; }

	// Ported from WTDE, fix this in the future if desired
	// (For now, we'll just spit all logs to console)
	bool ChannelAllowed(const char* category) { return true; }

	//------------------------
	// Prepare the logger
	//------------------------

	void Initialize() {
		char logpath[MAX_PATH];
		char tracepath[MAX_PATH];

		//if (GameConfig::GetValue("Logger", "Console", 0))
			l_UseConsole = true;
		//if (GameConfig::GetValue("Logger", "WriteFile", 1))
			l_DebugOutput = true;

		//l_ExitOnAssert = GameConfig::GetValue("Logger", "ExitOnAssert", 1);

		// Create console?
		if (l_UseConsole)
		{
			AllocConsole();
			freopen_s(&CON, "CONIN$", "r", stdin);
			freopen_s(&CON, "CONOUT$", "w", stdout);
			freopen_s(&CON, "CONOUT$", "w", stderr);
			std::cout.clear();
			std::cerr.clear();

			consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		// Write to debug file?
		if (l_DebugOutput)
		{
			//Log("Logger file output initialized.\n");
			fopen_s(&f_logger, "debug.txt", "w");
			fopen_s(&f_tracer, "trace.txt", "w");

			if (!f_logger)
				PrintLog("Failed to create debug.txt file.\n");
			if (!f_tracer)
				PrintLog("Failed to create trace.txt file.\n");
		}
	}

	//------------------------
	// Prints message to console and log!
	//------------------------

	void CoreLog(const char* to_log, const char* category = CHN_LOG) {
		// Output to console
		if (ConsoleAllowed())
		{
			if (ChannelAllowed(category))
				printf("[%s] %s", category, to_log);
		}

		// Also write to .txt file!
		if (OutputAllowed() && f_logger)
		{
			fputs(to_log, f_logger);
			fflush(f_logger);
		}
	}

	//------------------------
	// Prints log message, with arguments!
	//------------------------

	void PrintLog(const char* Format, ...) {
		char final_buffer[2000];

		va_list args;
		va_start(args, Format);
		vsnprintf(final_buffer, 2000, Format, args);
		va_end(args);

		CoreLog(final_buffer, CHN_LOG);
	}

	//------------------------
	// Typed log
	//------------------------

	void TypedLog(const char* category, const char* Format, ...) {
		char final_buffer[3000];

		va_list args;
		va_start(args, Format);
		vsnprintf(final_buffer, 3000, Format, args);
		va_end(args);

		CoreLog(final_buffer, category);
	}


	//------------------------
	// Format string from pParams (built-in function)
	//------------------------

	typedef bool StringFromParamCall(char* print_dest, Script::LazyStruct* pParams);
	StringFromParamCall* s_from_params = (StringFromParamCall*)(0x0044C840); //THUG2

	void StringFromParams(char* print_dest, Script::LazyStruct* pParams)
	{
		s_from_params(print_dest, pParams);
	}

	//------------------------
	// Function to replace plain PrintF!
	//------------------------

	bool CFunc_PrintF(Script::LazyStruct* pParams)
	{
		char buf[2048];
		StringFromParams(buf, pParams);

		TypedLog(CHN_LOG, "%s", buf);

		return 1;
	}

	//CFuncs::RedirectFunction("PrintF", (void*)CFunc_PrintF);

}