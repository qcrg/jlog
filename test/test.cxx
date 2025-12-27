#include "jlog.hxx"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <sstream>

struct fixture
{
	fixture() : global_out{jlog::config::out.get()} {
		jlog::config::out = out;
	}

	~fixture() {
		jlog::config::out = global_out;
	}

	std::ostream& global_out;
	std::ostringstream out;
};

TEST_CASE_FIXTURE(fixture, "default")
{
	jlog::info("Hello, world!!");
	CHECK_FALSE(out.str().empty());
}
