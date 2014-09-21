#define LEVEL_INFO 0
#define LEVEL_WARNING 1
#define LEVEL_ERROR 2

// TODO: allow defining partial debug.
// OPTIMIZE: add high performance debug using memcpy, $pc, etc, rather than sprintf
// TODO: add file logging
// OPTIMIZE: make this work with C++ strings and not just C char* arrays! There are way too many .c_str() littering this code.

#ifdef TRACE 

#define INFO(...) debug_print(LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define WARNING(...) debug_print(LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define ERROR(...) debug_print(LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
void debug_print(int level, const char * file, int line, const char * fmt, ...);

#else

#define INFO(...) 
#define WARNING(...) 
#define ERROR(...) 

#endif
