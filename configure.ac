dnl Process this file with autoconf to produce a configure script.
AC_INIT(algo_test, 1.0, mikeage@gmail.com)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src/)

AM_INIT_AUTOMAKE

AC_ARG_ENABLE(debug,
			  AS_HELP_STRING([--enable-debug],
							 [enable debugging, default: no]),
							 [case "${enableval}" in
							  yes) debug=true ;;
						  no)  debug=false ;;
					  *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
				  esac],
				  [debug=false])
AC_ARG_ENABLE(trace,
			  AS_HELP_STRING([--enable-trace],
							 [enable trace logs, default: no]),
							 [case "${enableval}" in
							  yes) trace=true ;;
						  no)  trace=false ;;
					  *)   AC_MSG_ERROR([bad value ${enableval} for --enable-trace]) ;;
				  esac],
				  [trace=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_CONDITIONAL(TRACE, test x"$trace" = x"true")
AM_COND_IF(DEBUG, CXXFLAGS="-g3 -O0", /bin/true)

AC_PROG_CXX

AC_OUTPUT(Makefile src/Makefile)
