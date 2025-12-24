#include "jlog.hxx"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <sstream>

TEST_CASE("default")
{
	auto tmp = jlog::global_out;

	std::ostringstream out;
	jlog::global_out = out;

	jlog::info("Hello, world!!");
	CHECK_FALSE(out.str().empty());

	jlog::global_out = tmp;
}
