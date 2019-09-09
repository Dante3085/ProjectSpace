
#ifndef LOG_H
#define LOG_H

#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/stacktrace.hpp>
#include <utility>
#include <array>

#include "Logable.h"

/*
_CRT_SECURE_NO_WARNINGS is defined because of C's Time functions.
BOOST_STACKTRACE_USE_WINDBG_CACHED is defined to make boost::stacktrace creation faster.
https://docs.microsoft.com/de-de/cpp/c-runtime-library/security-features-in-the-crt?view=vs-2019

TODO: Seperate Thread for Logging ?
TODO: Write to file in destructor ? Possible IO-Exceptions.
TODO: Serialize Log Object ?
TODO: Log verbosity(low, medium, high). On low, only error LogEntries are printed.
TODO: Logging channels(Animation channel, Combat channel, Scene channel, ...). Mute channels to only get desired LogEntries.
TODO: Limit Log for duplicate LogEntries.
TODO: LogRotation: Have 2 or more Logs. After certain size or time save log. (https://en.wikipedia.org/wiki/Log_rotation)
*/

namespace ProjectSpace
{
	enum class LogLevel
	{
		INVALID = -1,
		STATUS,  // Mark LogEntry as a Status LogEntry. Status LogEntries exist for general logging. Low priority.
		WARNING, // Mark LogEntry as Warning LogEntry. Warning LogEntries exist for issues that don't break the program, but should be looked at. Mid Priority.
		ERR      // Mark LogEntry as Error LogEntry. Error LogEntries exist for issues that break the program and need to be looked at immediately. High priority.
	};
	using ll = LogLevel;

	enum class LogOption
	{
		INVALID = -1,
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
		CLEAR,      // Remove all LogEntries.
		CH_STD,     // Log to Standard Channel.
		CH_ANIM,    // Log to Animation Channel.
		CH_COMB,    // Log to Combat Channel.
		FLUSH,      // Write every logging channel to file.
		EXIT        // Write log to file/Save log then exit the program. For situations when it doesn't make sense to keep the program running.
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

		// Make it impossible to call Copy Constructor.
		Log(Log const&) = delete;

		// Make it impossible to call assignment operator.
		void operator=(Log const&) = delete;

		/* Appends a LogEntry with a timestamp, stacktrace, the given message and loglevel
		   and prints it to the console.
		*/
		void defaultLog(std::string const& message, LogLevel logLevel)
		{
			*this << lo::PTC << logLevel << lo::TIMESTAMP << message << lo::STACKTRACE << lo::END;
		}

		// Only allow numeric types.
		template< typename T, 
	    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		Log& operator<<(T t)
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

			channels[activeChannel].first.append(temp);
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

			channels[activeChannel].first.append(temp);
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
				channels[activeChannel].second = s;
				setFilename = false;
			}
			else
			{
				if (printNextEntryToConsole)
				{
					tempLogEntry.append(s);
				}

				channels[activeChannel].first.append(s);
			}
			return *this;
		}

		Log& operator<<(LogOption lo)
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
				channels[activeChannel].first.append(temp);
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
						std::ofstream out(channels[activeChannel].second, std::ofstream::app);
						out << channels[activeChannel].first;
						out.close();
					}
					else
					{
						std::ofstream out(channels[activeChannel].second);
						out << channels[activeChannel].first;
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
					channels[activeChannel].first.clear();
					disabled = false;
					printNextEntryToConsole = false;
					tempLogEntry.clear();
					appendToFile = true;
					break;
				}
				case LogOption::CLEAR:
				{
					channels[activeChannel].first.clear();
					tempLogEntry.clear();
					break;
				}
				case LogOption::CH_STD:
				{
					activeChannel = 0;
					break;
				}
				case LogOption::CH_ANIM:
				{
					activeChannel = 1;
					break;
				}
				case LogOption::CH_COMB:
				{
					activeChannel = 2;
					break;
				}
				case LogOption::FLUSH:
				{
					for (int i = 0; i < channels.size(); ++i)
					{
						activeChannel = i;
						*this << lo::WTF;
					}

					break;
				}
				case LogOption::EXIT:
				{
					// TODO: Serialize Log Object?

					*this << lo::PTC << lo::TIMESTAMP << "Exiting program due to unsalvageable state. Press Enter to exit...\n" << lo::END
						  << lo::FLUSH;
					std::cin.get();
					exit(1);

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

				channels[activeChannel].first.append(temp);
			}
			return *this;
		}

		Log& operator<<(LogLevel ll)
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

			channels[activeChannel].first.append(temp);
			return *this;
		}

	private:
		Log() : 
			disabled{ false }, printNextEntryToConsole{ false }, tempLogEntry{ "" }, appendToFile{ true },
			setFilename{ false }, activeChannel{0}
		{
			// The standard logging channel is initially always turned on.
			channels[0].first = "";
			channels[0].second = "log/stdLogChannel.txt";

			channels[1].first = "";
			channels[1].second = "log/animationLogChannel.txt";

			channels[2].first = "";
			channels[2].second = "log/combatLogChannel.txt";
		}

		~Log()
		{
			*this << LogOption::FLUSH;
		}

		/* A channel consists of a logString that contains all LogEntries and a logFileName.
		*/
		std::array<std::pair<std::string, std::string>, 3> channels;
		unsigned int activeChannel; // Holds which channel is currently being written to.
		bool disabled;
		bool printNextEntryToConsole;

		/* If next LogEntry is to be printed on console, the result of all the stream-operators
		   has to be stored as a LogEntry in one string.
	    */
		std::string tempLogEntry;
		bool appendToFile;
		bool setFilename;


	private:
		// Replaces all occurences of "from" in "str" with "to".
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

#endif