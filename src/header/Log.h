#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/stacktrace.hpp>

#include "Logable.h"

/*
_CRT_SECURE_NO_WARNINGS ist wegen C's Time Funktionen eingeschaltet
https://docs.microsoft.com/de-de/cpp/c-runtime-library/security-features-in-the-crt?view=vs-2019

TODO: Mit <<operator. Verarbeitung von beliebigen Daten. Kein Log* für mehrere Aufrufe, sondern
      einfach <<operator erneut aufrufen. Log::getInstance() << "dasdasdasd" << object << Log::trace << std::endl

TODO: Log in separatem Thread.
*/

namespace ProjectSpace
{
	enum class LogLevel
	{
		STATUS,
		WARNING,
		ERR
	};

	enum class LogOption
	{
		STACKTRACE,
		TIMESTAMP,
		PRINT_TO_CONSOLE,
		END,
		WRITE_TO_FILE
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

				// Indent the whole stacktrace.
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
			logString.append(newEntry);

			++numberOfLogs;
		}

		// Removes every LogEntry.
		void clear()
		{
			if (disabled)
				return;

			// Only sets capacity of string to 0. Might want to free allocated memory.
			logString.clear();
			numberOfLogs = 0;
		}

		// Writes all LogEntries into to the given file.
		void writeToFile(std::string const& pathToFile = "", bool overwriteExistingContents = false)
		{
			if (disabled)
				return;

			// Don't do anything if no LogEntries exist.
			if (numberOfLogs == 0)
			{
				std::cout << "There are no logs. Nothing written to file." << std::endl;
				return;
			}

			/* TODO: Wenn pathToFile leer ist, immer zu Logfile das
			   aktuelles Datum als Namen hat loggen.*/
			// Overwrite existing file contents if necessary.
			if (overwriteExistingContents)
			{
				std::ofstream out(pathToFile);
				out << logString;
				out.close();
			}

			// Else append to existing file contents.
			else
			{
				std::ofstream out(pathToFile, std::ofstream::app);
				out << logString;
				out.close();
			}
		}

		// Prints all LogEntries to the console.
		void printToConsole()
		{
			if (disabled)
				return;

			std::cout << logString << std::endl;
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

			logString.append(str);
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

			logString.append(str);
			std::cout << str;

			disabled = true;
		}

		// Mache es unmöglich den Kopierkonstruktor aufzurufen.
		Log(Log const&) = delete;

		// Mache es unmöglich den Zuweisungsoperator aufzurufen.
		void operator=(Log const&) = delete;

		// ----- Ab hier operator<< Stream Ansatz Funktionen. ------

		Log& operator<<(Logable const& l)
		{
			std::string temp = l.toString();

			if (printNextEntryToConsole)
			{
				tempLogEntry.append(temp);
			}

			logString.append(temp);
			return *this;
		}

		Log& operator<<(std::string const& s)
		{
			if (printNextEntryToConsole)
			{
				tempLogEntry.append(s);
			}

			logString.append(s);
			return *this;
		}

		Log& operator<<(LogOption const& lo)
		{
			std::string temp = "";

			switch (lo)
			{
			case LogOption::STACKTRACE:
			{
				temp = boost::stacktrace::to_string(boost::stacktrace::stacktrace());
				replaceAll(temp, "\n", "\n\t");
				temp.insert(temp.begin(), '\n');
				break;
			}
			case LogOption::TIMESTAMP:
			{
				time_t now = time(NULL);
				temp.append(ctime(&now));

				// TODO: War \n nicht nur am Ende. Warum dann von begin bis end ?
				temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
				break;
			}
			case LogOption::WRITE_TO_FILE:
			{
				// TODO: Nicht Funktion aufrufen, sondern hier direkt implementieren.
				writeToFile();
				break;
			}
			case LogOption::PRINT_TO_CONSOLE:
			{
				printNextEntryToConsole = true;
				break;
			}
			case LogOption::END:
			{
				if (printNextEntryToConsole)
				{
					std::cout << tempLogEntry << std::endl;
					tempLogEntry.clear();
					printNextEntryToConsole = false;
				}
				break;
			}
			default:
			{
				temp.append("Unknown LogOption");
			}
			}

			if (printNextEntryToConsole)
			{
				tempLogEntry.append(temp);
			}

			logString.append(temp);
			return *this;
		}

		Log& operator<<(LogLevel const& ll)
		{
			std::string temp;

			switch (ll)
			{
			case LogLevel::STATUS:
			{
				temp.append("STATUS | ");
				break;
			}
			case LogLevel::WARNING:
			{
				temp.append("WARNING | ");
				break;
			}
			case LogLevel::ERR:
			{
				temp.append("ERROR | ");
				break;
			}
			default:
			{
				temp.append("Unknown LogLevel | ");
			}
			}

			if (printNextEntryToConsole)
			{
				tempLogEntry.append(temp);
			}

			logString.append(temp);
			return *this;
		}

	private:
		Log() : logString{ "LOGFILE\n\n" }, numberOfLogs{ 0 }, disabled{false},
			printNextEntryToConsole{ false }, tempLogEntry{""} {}
		~Log()
		{
			// TODO: Write log to file before Object gets destroyed.
		}

		// All LogEntries in a signle string.
		std::string logString;

		int numberOfLogs;

		/* Controls if add, writeToFile and printToConsole are enabled.
		   In short for turning logging on and off without removing 
		   logging code all over the project.
		*/
		bool disabled;

		// ----- Ab hier operator<< Stream Ansatz Variablen. ------

		/* Stores if the next LogEntry will be printed to console.
		*/
		bool printNextEntryToConsole;

		/* Stores a LogEntry temporarily. */
		std::string tempLogEntry;

	private:
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