#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>

/*
_CRT_SECURE_NO_WARNINGS ist wegen C's Time Funktionen eingeschaltet
https://docs.microsoft.com/de-de/cpp/c-runtime-library/security-features-in-the-crt?view=vs-2019

TODO:
1. Stacktrace
2. Current File, Current Line
*/

class Log
{
public:

	static Log& getInstance()
	{
		/* Memory for singleton is only allocated on the first call of getInstance().
		 * singleton is avaible for every subsequent call of getInstance().
		*/
		static Log singleton;
		return singleton;
	}

	// Appends the given LogEntry to the Log.
	void add(std::string const& logEntry, bool print = false, int logType = 0, bool newLine = true)
	{
		std::string newEntry = "";
		
		switch (logType)
		{
			// Normal Status LogEntry for logging anything.
		case 0:
			newEntry.append("STATUS | ");
			break;

			/* Warning LogEntry for things that don't break the program,
			   but should be looked at.
			*/
		case -1:
			newEntry.append("WARNING | ");
			break;

			/* Error LogEntry for things that break the program
			   and need to be dealt with immediately.
			*/
		case -2:
			newEntry.append("ERROR | ");
			break;

			// Every unknown logType automatically produces a Status LogEntry.
		default:
			newEntry.append("STATUS | ");
			break;
		}

		// Append current timestamp.
		time_t now = time(NULL);
		newEntry.append(ctime(&now));
		newEntry.erase(std::remove(newEntry.begin(), newEntry.end(), '\n'), newEntry.end());

		// Append LogEntry
		newEntry.append(" | ");
		newEntry.append(logEntry);

		if (newLine)
		{
			newEntry.append("\n");
		}

		if (print)
		{
			std::cout << newEntry;

		}

		// Append new LogEntry to the log.
		log.append(newEntry);

		++numberOfLogs;
	}

	// Removes every LogEntry.
	void clear()
	{
		// Only sets capacity of string to 0. Might want to free allocated memory.
		log.clear();
		numberOfLogs = 0;
	}

	// Writes all LogEntries in the Log to the given file.
	void writeToFile(std::string const& pathToFile = "stdlog.txt", bool overwriteExistingContents = false)
	{
		if (numberOfLogs == 0)
		{
			std::cout << "There are no logs. Nothing written to file." << std::endl;
			return;
		}

		if (overwriteExistingContents)
		{
			std::ofstream out(pathToFile);
			out << log;
			out.close();
		}
		else
		{
			std::ofstream out(pathToFile, std::ofstream::app);
			out << log;
			out.close();
		}
	}

	// Prints all LogEntries to the console.
	void printToConsole()
	{
		std::cout << log << std::endl;
	}

	int getNumberOfLogs()
	{
		return numberOfLogs;
	}

	// Mache es unmöglich den Kopierkonstruktor aufzurufen.
	Log(Log const&) = delete;

	// Mache es unmöglich den Zuweisungsoperator aufzurufen.
	void operator=(Log const&) = delete;

private:
	Log() : log{"LOGFILE\n\n"}, numberOfLogs { 0 } {}
	
	std::string log;
	int numberOfLogs;
};