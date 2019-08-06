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

TODO: Log in separatem Thread ?
TODO: Stream-Operator für Zahlentypen.
TODO: Im Destruktor von Log Logeinträge in Datei schreiben, um Data Loss zu verhindern.
      Problem IO-Exceptions.
*/

namespace ProjectSpace
{
	enum class LogLevel
	{
		STATUS,  // Mark LogEntry as a Status LogEntry. Status LogEntries exist for general logging. Low priority.
		WARNING, // Mark LogEntry as Warning LogEntry. Warning LogEntries exist for issues that don't break the program, but should be looked at. Mid Priority.
		ERR      // Mark LogEntry as Error LogEntry. Error LogEntries exist for issues that break the program and need to be looked at immediately. High priority.
	};
	using ll = LogLevel;

	enum class LogOption
	{
		ENABLE,     // Enable all Logging functionality.
		DISABLE,    // Disable all Logging functionality(After disabling, LogOption::ENABLE and LogOption::DISABLE are still processed.)
		STACKTRACE, // Append Stacktrace to LogEntry.
		TIMESTAMP,  // Append Timestamp to LogEntry.
		PTC,        // Print next LogEntry to console. End of LogEntry is signaled with LogOption::END.
		END,        // Signal end of LogEntry.
		WTF,        // Write Log(Set of all LogEntries) to the LogFile.
		APPEND,     // Append to existing file contents on LogOption::WTF(Write to file).
		OVERWRITE,  // Overwrite existing file contents on LogOption::WTF(Write to file).
		FILENAME,   // Set Logfile name(i.e. Path to Logfile).
		RESET,      // Reset the Log to it's initial state(Remove all LogEntries and reset variables to their initial state.)
		CLEAR       // Remove all LogEntries.
	};
	using lo = LogOption;

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

		// Mache es unmöglich den Kopierkonstruktor aufzurufen.
		Log(Log const&) = delete;

		// Mache es unmöglich den Zuweisungsoperator aufzurufen.
		void operator=(Log const&) = delete;

		/* Appends a LogEntry with a timestamp, stacktrace, the given message and loglevel
		   and prints it to the console.
		*/
		void defaultLog(std::string const& message, LogLevel logLevel)
		{
			*this << lo::PTC << logLevel << lo::TIMESTAMP << message << lo::STACKTRACE << lo::END;
		}

		// Soll nur Zahlentypen zulassen.
		template< typename T, 
	    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		Log& operator<<(T const& t)
		{
			if (disabled)
			{
				return *this;
			}

			std::string temp = std::to_string(t);

			if (printNextEntryToConsole)
			{
				tempLogEntry.append(temp);
			}

			logString.append(temp);
			return *this;
		}

		Log& operator<<(Logable const& l)
		{
			if (disabled)
			{
				return *this;
			}

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
			if (disabled)
			{
				return *this;
			}

			if (setFilename)
			{
				logFileName = s;
				setFilename = false;
			}
			else
			{
				if (printNextEntryToConsole)
				{
					tempLogEntry.append(s);
				}

				logString.append(s);
			}
			return *this;
		}

		Log& operator<<(LogOption const& lo)
		{
			if (lo == LogOption::ENABLE || lo == LogOption::DISABLE)
			{
				std::string temp{};
				time_t now = time(NULL);
				temp.append(ctime(&now));
				// temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
				temp.erase(temp.size() - 1);
				temp.append(" ");

				if (lo == LogOption::ENABLE)
				{
					disabled = false;
					temp.append("Logging Enabled\n");
				}
				else if (lo == LogOption::DISABLE)
				{
					disabled = true;
					temp.append("Logging Disabled\n");
				}

				std::cout << temp;
				logString.append(temp);
			}
			else
			{
				if (disabled)
				{
					return *this;
				}

				std::string temp{};
				switch (lo)
				{
				case LogOption::STACKTRACE:
				{
					temp = boost::stacktrace::to_string(boost::stacktrace::stacktrace());
					replaceAll(temp, "\n", "\n\t");
					temp.insert(temp.begin(), '\n');
					temp.insert(temp.begin() + 1, '\t');
					temp.erase(temp.end() - 1);
					break;
				}
				case LogOption::TIMESTAMP:
				{
					time_t now = time(NULL);
					temp.append(ctime(&now));
					temp.erase(temp.size() - 1);
					temp.append(" | ");
					break;
				}
				case LogOption::PTC:
				{
					printNextEntryToConsole = true;
					break;
				}
				case LogOption::END:
				{
					if (printNextEntryToConsole)
					{
						std::cout << tempLogEntry;
						tempLogEntry.clear();
						printNextEntryToConsole = false;
					}
					break;
				}
				case LogOption::WTF:
				{
					if (appendToFile)
					{
						std::ofstream out(logFileName, std::ofstream::app);
						out << logString;
						out.close();
					}
					else
					{
						std::ofstream out(logFileName);
						out << logString;
						out.close();
					}
					break;
				}
				case LogOption::APPEND:
				{
					appendToFile = true;
					break;
				}
				case LogOption::OVERWRITE:
				{
					appendToFile = false;
					break;
				}
				case LogOption::FILENAME:
				{
					setFilename = true;
					break;
				}
				case LogOption::RESET:
				{
					logString.clear();
					disabled = false;
					printNextEntryToConsole = false;
					tempLogEntry.clear();
					appendToFile = true;
					logFileName = "stdlog.txt";
					break;
				}
				case LogOption::CLEAR:
				{
					logString.clear();
					tempLogEntry.clear();
					break;
				}
				default:
				{
					temp.append("Unknown LogOption.");
				}
				}

				if (printNextEntryToConsole)
				{
					tempLogEntry.append(temp);
				}

				logString.append(temp);
			}
			return *this;
		}

		Log& operator<<(LogLevel const& ll)
		{
			if (disabled)
			{
				return *this;
			}

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
		Log() : logString{ "" }, disabled{false},
			printNextEntryToConsole{ false }, tempLogEntry{""},
			appendToFile{ true }, logFileName{"stdlog.txt"},
			setFilename{false} {}

		~Log()
		{
			
		}

		std::string logString;
		bool disabled;
		bool printNextEntryToConsole;

		/* Falls nächster Logeintrag auf Konsole geprinted werden soll, muss das Ergebnis
		   der verschiedenen Stream-Operatoren als ein Logeintrag in einem string festgehalten
		   werden.
	    */
		std::string tempLogEntry;
		bool appendToFile;
		std::string logFileName;
		bool setFilename;

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