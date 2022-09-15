lib_LTLIBRARIES = avengerFlag.la

avengerFlag_la_SOURCES = avengerFlag.cpp
avengerFlag_la_CPPFLAGS= -I$(top_srcdir)/include -I$(top_srcdir)/plugins/plugin_utils
avengerFlag_la_LDFLAGS = -module -avoid-version -shared
avengerFlag_la_LIBADD = $(top_builddir)/plugins/plugin_utils/libplugin_utils.la

AM_CPPFLAGS = $(CONF_CPPFLAGS)
AM_CFLAGS = $(CONF_CFLAGS)
AM_CXXFLAGS = $(CONF_CXXFLAGS)

EXTRA_DIST = \
	README.avengerFlag.txt \
	avengerFlag.sln \
	avengerFlag.vcxproj	\
	avengerFlag.vcxproj.filters

MAINTAINERCLEANFILES =	\
	Makefile.in
