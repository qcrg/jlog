#include "jlog.hxx"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <sstream>

TEST_CASE("default")
{
	auto tmp = jlog::config::out;

	std::ostringstream out;
	jlog::config::out = out;

	jlog::info("Hello, world!!");
	CHECK_FALSE(out.str().empty());

	jlog::config::out = tmp;
}
