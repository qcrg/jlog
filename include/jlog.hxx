#pragma once

#include <chrono>
#include <format>
#include <functional>
#include <iostream>
#include <utility>

namespace jlog {

	enum class Level
	{
		fatal = 0,
		error,
		warn,
		info,
		debug,
		trace
	};

	namespace impl {

		constexpr const char* LEVEL_NAMES[] = {
			"\x1b[41;97mfatal\x1b[0m",
			"\x1b[31;1merror\x1b[0m",
			"\x1b[33;1mwarn\x1b[0m",
			"\x1b[32minfo\x1b[0m",
			"\x1b[36mdebug\x1b[0m",
			"\x1b[90mtrace\x1b[0m",
		};

		constexpr const char* _level_to_str(Level level) {
			return LEVEL_NAMES[static_cast<int>(level)];
		}

	} //namespace impl

	namespace config {

		inline Level level = Level::info;
		inline std::reference_wrapper<std::ostream> out = std::clog;

	} //namespace config

	namespace impl {

		inline auto print_prefix(std::ostream& out, Level level) -> void
		{
			out << std::format(
				"[{:%Y-%m-%d %H:%M:%S}] [{}] ",
				std::chrono::utc_clock::now(),
				_level_to_str(level)
			);
		}

	} // namespace impl

	template<typename ...Args>
	auto log(Level level, std::format_string<Args...> fmt, Args&&... args) -> void
	{
		if (level > config::level)
			return;
		std::ostream& out = config::out.get();
		impl::print_prefix(config::out, level);
		out << std::format(fmt, std::forward<Args>(args)...) << '\n';
	}

	template<typename ...Args>
	auto log(Level level, Args&&... args) -> void
	{
		if (level > config::level)
			return;
		auto& out = config::out.get();
		impl::print_prefix(out, level);
		bool first = true;
		((out << args << (first ? "" : " ")), ...);
	}

	template<typename ...Args>
	auto fatal(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		log(Level::fatal, fmt, std::forward<Args>(args)...);
		std::terminate();
	}

	template<typename ...Args>
	auto error(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		return log(Level::error, fmt, std::forward<Args>(args)...);
	}

	template<typename ...Args>
	auto warn(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		return log(Level::warn, fmt, std::forward<Args>(args)...);
	}

	template<typename ...Args>
	auto info(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		return log(Level::info, fmt, std::forward<Args>(args)...);
	}

	template<typename ...Args>
	auto debug(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		return log(Level::debug, fmt, std::forward<Args>(args)...);
	}

	template<typename ...Args>
	auto trace(std::format_string<Args...> fmt, Args&&... args) -> void
	{
		return log(Level::trace, fmt, std::forward<Args>(args)...);
	}

} //namespace jlog
