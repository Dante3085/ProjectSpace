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
*/

namespace ProjectSpace
{
	enum class LogLevel
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
		void add(std::string const& logMessage, bool printToConsole = false, LogLevel logLevel = LogLevel::STATUS,
			bool stacktrace = false, bool newLine = true)
		{
			if (disabled)
				return;

			std::string newEntry = "";

			// Append marker for LogLevel.
			switch (logLevel)
			{
				// Normal Status LogEntry for logging anything.
			case LogLevel::STATUS:
				newEntry.append("STATUS | ");
				break;

				/* Warning LogEntry for things that don't break the program,
				   but should be looked at.
				*/
			case LogLevel::WARNING:
				newEntry.append("WARNING | ");
				break;

				/* Error LogEntry for things that break the program
				   and need to be dealt with immediately.
				*/
			case LogLevel::ERR:
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

				/* Look for newLines and put an indent after them,
				 * so that it's easy to see to which LogEntry the
				 * Stacktrace belongs. Because of iterating over 
				 * every char of the stacktrace string, this is noticeably slow.
				 * Defining the BOOST_STACKTRACE_USE_WINDBG_CACHED
				 * preprocessor macro helps by caching though.
				 * With the macro defined producing the same or similar
				 * stacktrace(s) is very fast. I am not sure about completely
				 * different stacktraces.
				*/
				/*for (std::string::iterator it = st.begin(); it != st.end() - 1; ++it)
				{
					if (*it == '\n')
					{
						st.insert(it + 1, '\t');
					}
				}*/
				replaceAll(st, "\n", "\n\t");

				newEntry.append("\n\t");
				newEntry.append(st);

				// -----
				/*newEntry.append("\n");
				for (boost::stacktrace::frame const& f : boost::stacktrace::stacktrace())
				{
 					std::string frameAsString = boost::stacktrace::to_string(f);
					frameAsString.append("\n\t");
					newEntry.append(frameAsString);
				}*/
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
			if (disabled)
				return;

			// Only sets capacity of string to 0. Might want to free allocated memory.
			log.clear();
			numberOfLogs = 0;
		}

		// Writes all LogEntries into to the given file.
		void writeToFile(std::string const& pathToFile = "stdlog.txt", bool overwriteExistingContents = false)
		{
			if (disabled)
				return;

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
			if (disabled)
				return;

			std::cout << log << std::endl;
		}

		// Returns number of LogEntries.
		int getNumberOfLogs()
		{
			return numberOfLogs;
		}

		// Enables all logging functionality.
		void enable()
		{
			std::string str = "";

			time_t now = time(NULL);
			str.append(ctime(&now));
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

			str.append(" | Logging enabled.\n");

			log.append(str);
			std::cout << str;

			disabled = false;
		}

		/* Disables all logging functionality except getting 
		   the current number of LogEntries.
		*/
		void disable()
		{
			std::string str = "";

			time_t now = time(NULL);
			str.append(ctime(&now));
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
			str.append(" | Logging disabled.\n");

			log.append(str);
			std::cout << str;

			disabled = true;
		}

		// Mache es unmöglich den Kopierkonstruktor aufzurufen.
		Log(Log const&) = delete;

		// Mache es unmöglich den Zuweisungsoperator aufzurufen.
		void operator=(Log const&) = delete;

	private:
		Log() : log{ "LOGFILE\n\n" }, numberOfLogs{ 0 }, disabled{false} {}

		// All LogEntries in a signle string.
		std::string log;

		int numberOfLogs;

		/* Controls if add, writeToFile and printToConsole are enabled.
		   In short for turning logging on and off without removing 
		   logging code all over the project.
		*/
		bool disabled;

		// Replaces all occurences of "from" in "str" to "to".
		void replaceAll(std::string& str, std::string const& from, std::string const& to)
		{
			if (from.empty())
				return;

			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos)
			{
				str.replace(start_pos, from.length(), to);
				start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
			}
		}
	};
}