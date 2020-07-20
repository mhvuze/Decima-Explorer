#pragma once

typedef enum CLI_COMMAND {
	EXTRACT,
	EXTRACT_ALL,
	REPACK
} CLI_COMMAND;

class CLI {
public:
	CLI(int argc, char **argv);
	~CLI();

	void run(const char* programName);
	void exit();
private:

	int argc;
	char **argv;

	const char *USAGE_MESSAGE = "Usage:\t DecimaExplorer.exe [option] inputfile fileid outputfile\n Available Options:\n Extract: -e, -extract\n";
	const char *EXIT_MESSAGE  = "Exiting\n";

	//command methods
	void extract(int id);
	void extractAll();
	void repack();

	//cli methods
	void printUsage();
	bool checkInput();
	bool isNumber(char* arg);
	bool isCommand(char* arg);
	int argToNumber(char* arg);
	CLI_COMMAND argToCommand(char* arg);
	void processCommand(CLI_COMMAND command, int id);
};