#include "CLI.h"
#include <windows.h>
#include "../archive/DecimaArchive.h"

CLI::CLI(int argc, char **argv) {
	this->argc = argc;
	this->argv = argv;
}

CLI::~CLI() {
}

void CLI::processCommand(CLI_COMMAND command, int id) {
	switch (command) {
	case EXTRACT:
		extract(id);
		break;
	case EXTRACT_ALL:
		extractAll();
		break;
	case REPACK:
		repack();
		break;
	default:
		extract(id);
	}
}

void CLI::run(const char* programName) {
	if (!checkInput()) return;
	printf("Running %s:\n", programName);
	
	CLI_COMMAND command = argToCommand(argv[1]);
	int id = argToNumber(argv[3]);

	processCommand(command, id);
}

void CLI::extract(int id) {
	DecimaArchive decimaArchive(argv[2]);
	if (!decimaArchive.open()) return;
	if (!decimaArchive.extractFile(id, argv[4])) return;
	printf("Finished extracting file %s\n", argv[4]);
}

void CLI::extractAll() {
	printf("Extracting all files\n");
	DecimaArchive decimaArchive(argv[2]);
	if (!decimaArchive.open()) return;
	int count = decimaArchive.getFileTableCount();
	CreateDirectory("out", NULL);
	for (int i = 0; i < count; i++) {
		if (!decimaArchive.extractFile(i, "out\\" + std::string(8 - std::to_string(i).length(), '0') + std::to_string(i) + ".bin")) return;
	}
	printf("Finished extracting files\n");
}

bool CLI::checkInput() {
	if (argc != 5 || !isCommand(argv[1]) || !isNumber(argv[3])) {
		printUsage();
		return false;
	}
	return true;
}

int CLI::argToNumber(char* arg) {
	int num;
	sscanf_s(arg, "%d", &num);
	return num;
}

CLI_COMMAND CLI::argToCommand(char* arg) {
	if (strcmp(arg, "-extract") || strcmp(arg, "-e"))
		return EXTRACT_ALL;
	if (arg == "-repack" || arg == "-r")
		return REPACK;
}

bool CLI::isNumber(char* arg) {
	for (int i = 0; arg[i] != 0; i++) {
		if (!isdigit(arg[i]))
			return false;
	}
	return true;
}

bool CLI::isCommand(char* arg) {
	return arg[0] == 0x2D;
}

void CLI::repack() {
	printf("Sorry reapcking is not implemented yet\n");
}

void CLI::printUsage() {
	printf("%s", this->USAGE_MESSAGE);
}

void CLI::exit() {
	printf(this->EXIT_MESSAGE);
}