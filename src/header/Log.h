#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/stacktrace.hpp>

/*
_CRT_SECURE_NO_WARNINGS ist wegen C's Time Funktionen eingeschaltet
https://docs.microsoft.com/de-de/cpp/c-runtime-library/security-features-in-the-crt?view=vs-2019

TODO:
1. Stacktrace
2. Current File, Current Line
*/

namespace ProjectSpace
{
	enum class LogType
	{
		STATUS,
		WARNING,
		ERR
	};

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
		void add(std::string const& logMessage, bool printToConsole = false, LogType logType = LogType::STATUS,
			bool stacktrace = false, bool newLine = true)
		{
			std::string newEntry = "";

			switch (logType)
			{
				// Normal Status LogEntry for logging anything.
			case LogType::STATUS:
				newEntry.append("STATUS | ");
				break;

				/* Warning LogEntry for things that don't break the program,
				   but should be looked at.
				*/
			case LogType::WARNING:
				newEntry.append("WARNING | ");
				break;

				/* Error LogEntry for things that break the program
				   and need to be dealt with immediately.
				*/
			case LogType::ERR:
				newEntry.append("ERROR | ");
				break;
			}

			// Append current timestamp.
			time_t now = time(NULL);
			newEntry.append(ctime(&now));
			newEntry.erase(std::remove(newEntry.begin(), newEntry.end(), '\n'), newEntry.end());

			// Append Log Message.
			newEntry.append(" | ");
			newEntry.append(logMessage);

			// Append Stacktrace if necessary.
			if (stacktrace)
			{
				std::string st = boost::stacktrace::to_string(boost::stacktrace::stacktrace());

				// Indent stacktrace.
				for (std::string::iterator it = st.begin(); it != st.end() - 1; ++it)
				{
					if (*it == '\n')
					{
						st.insert(it + 1, '\t');
					}
				}
				newEntry.append("\n\t");
				newEntry.append(st);
			}

			// Append new line character at the end if necessary.
			if (newLine)
			{
				newEntry.append("\n");
			}

			// Print finished LogEntry to console if necessary.
			if (printToConsole)
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
			// Don't do anything if no LogEntries exist.
			if (numberOfLogs == 0)
			{
				std::cout << "There are no logs. Nothing written to file." << std::endl;
				return;
			}

			// Overwrite existing file contents if necessary.
			if (overwriteExistingContents)
			{
				std::ofstream out(pathToFile);
				out << log;
				out.close();
			}

			// Else append to existing file contents.
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

		// Returns number of LogEntries.
		int getNumberOfLogs()
		{
			return numberOfLogs;
		}

		// Mache es unmöglich den Kopierkonstruktor aufzurufen.
		Log(Log const&) = delete;

		// Mache es unmöglich den Zuweisungsoperator aufzurufen.
		void operator=(Log const&) = delete;

	private:
		Log() : log{ "LOGFILE\n\n" }, numberOfLogs{ 0 } {}

		std::string log;
		int numberOfLogs;
	};
}