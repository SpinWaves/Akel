// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 21/11/2023

#include <Core/core.h>
#include <Platform/messageBox.h>
#include <Core/Event/event.h>

namespace Ak::Core::log
{
	namespace internal
	{
		static std::mutex mutex;
		static std::filesystem::path log_dir;

		const std::filesystem::path& getLogPath() { return log_dir; }

		std::string getCurrentFileName()
		{
			__time time = Time::getCurrentTime();
			std::string copy = log_dir.string();
			copy.append("session-");
			copy.append(std::to_string(time.day));
			copy.append("-");
			copy.append(std::to_string(time.month));
			copy.append("-");
			copy.append(std::to_string(time.year));
			copy.append(".akel.log");
			
			return copy;
		}

		bool isOlderThan(const std::filesystem::path& path, int hrs)
		{
			auto now = std::filesystem::file_time_type::clock::now();
			return std::chrono::duration_cast<std::chrono::hours>(now - std::filesystem::last_write_time(path)).count() > hrs ;
		}

		std::vector<std::filesystem::path> filesOlderThan(std::filesystem::path dir, int hrs)
		{
			std::vector<std::filesystem::path> result;
			for(const auto& p : std::filesystem::recursive_directory_iterator(dir))
			{
				if(std::filesystem::is_regular_file(p) && isOlderThan(p, hrs))
					result.push_back(p);
			}
			return result;
		}

		void removeFilesOlderThan(std::filesystem::path dir, uint32_t days)
		{
			for(const auto& p : filesOlderThan(dir, days * 24))
				std::filesystem::remove(p);
		}

		void init(std::filesystem::path path)
		{
			log_dir = path.remove_filename() / ".akel_logs/";

			std::lock_guard<std::mutex> watchdog(mutex);
			if(!std::filesystem::exists(log_dir))
				std::filesystem::create_directory(log_dir);

			removeFilesOlderThan(log_dir, 10);

			std::ofstream out(getCurrentFileName(), std::ios::app);
			if(out.is_open())
			{
				out << "==== New Session ====" << std::endl;
				out.close();
			}
		}

		class FatalErrorEvent : public BaseEvent
		{
			public:
				FatalErrorEvent() = default;
				uint32_t what() const override { return 167; }
				~FatalErrorEvent() = default;
		};
	}

	void report(enum LogType type, std::string message, ...)
	{
		#ifdef AK_RELEASE
			if(type == DEBUGLOG)
				return;
		#endif

		std::unique_lock<std::mutex> watchdog(internal::mutex);

		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		#ifdef AK_RELEASE
			if(type != STRONG_WARNING && type != WARNING)
				messageBox(type, "Akel logs recieved a report", buffer, false);
		#endif

		std::string stype;
		std::ofstream out(internal::getCurrentFileName(), std::ios::app);
		if(out.is_open())
		{
			switch(type)
			{
				case DEBUGLOG: std::cout << blue << "[Akel log Debug] " << def << buffer << '\n'; stype = "Debug: "; break;
				case MESSAGE: std::cout << blue << "[Akel log Message] " << def << buffer << '\n'; stype = "Message: "; break;
				case WARNING:
				{	
					if(getMainAppProjectFile().archive()["enable_warning_console_message"])
						std::cout << magenta << "[Akel log Warning] " << def << buffer << '\n';
					stype = "Warning: ";
					break;
				}
				case STRONG_WARNING: std::cout << yellow << "[Akel log Strong Warning] " << def << buffer << '\n'; stype = "Strong Warning: "; break;
				case ERROR: std::cerr << red << "[Akel log Error] " << def << buffer << '\n'; stype = "Error: "; break;
				case FATAL_ERROR: std::cerr << red << "[Akel log Fatal Error] " << def << buffer << '\n'; stype = "Fatal Error: "; break;

				default: break;
			}
			out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- " << stype << buffer << std::endl;
		}
		if(type == FATAL_ERROR)
		{
			std::cout << bg_red << "FATAL ERROR: emergency abortion program" << bg_def << std::endl;
			watchdog.unlock();
			EventBus::send("__engine", internal::FatalErrorEvent{});
		}
		out.close();
	}

	void report(std::string message, ...)
	{
		std::unique_lock<std::mutex> watchdog(internal::mutex);

		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		std::ofstream out(internal::getCurrentFileName(), std::ios::app);
		if(out.is_open())
		{
			out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- " << buffer << std::endl;
			out.close();
		}
	}
}

namespace Ak
{
	void FatalError(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Core::log::report(FATAL_ERROR, buffer);
	}

	void Error(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Core::log::report(ERROR, buffer);
	}

	void Warning(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Core::log::report(WARNING, buffer);
	}

	void Strong_Warning(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Core::log::report(STRONG_WARNING, buffer);
	}

	void Message(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Core::log::report(MESSAGE, buffer);
	}
}
