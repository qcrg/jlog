# jlog

---

### Usage
```c++
#include <jlog.hxx>

int main()
{
  jlog::info("Hello, {}!", "World");
  return 0;
}
```

---

### Interface

##### Logging levels
```c++
enum class Level
{
	fatal = 0, // std::terminate after call
	error,
	warn,
	info,
	debug,
	trace
};
```

##### Global settings
```c++
Level
global_level = Level::info;

std::reference_wrapper<std::ostream>
global_out = std::clog;
```

##### Method interfaces
```c++
jlog::info("fmt string", fmt_args...);
```
