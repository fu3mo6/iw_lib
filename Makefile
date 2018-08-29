
CXX ?= g++
CC ?= gcc
CFLAGS ?= -Wall
CXXFLAGS ?= -Wall

# Auto, native compiler, detect netlink version using pkg-config
ifeq ($(CROSS_COMPILE), )
include makefile_nl.am
CXXFLAGS += ${NL_CFLAGS}
CFLAGS += ${NL_CFLAGS}
LIBS += ${NL_LIBS}
	
IW_CFLAGS = -O2 -g -D__MAKE_LIB -Wno-unused-function -Wno-missing-field-initializers
IW_MAKE_ENV = CFLAGS="${IW_CFLAGS}"

# Manual or cross compiler
# should define CC, CFLAGS, LIBS, and -DCONFIG_LIBNL30 or -DCONFIG_LIBNL20 for iw to use
else

IW_CFLAGS = ${CFLAGS}
IW_CFLAGS += -O2 -g -D__MAKE_LIB -Wno-unused-function -Wno-missing-field-initializers
IW_CFLAGS += -DCONFIG_LIBNL30
IW_MAKE_ENV = CC=${CC} CFLAGS="${IW_CFLAGS}" LIBS="${LIBS}" NO_PKG_CONFIG=Y

endif

LIBS += -L./iw_src -liwstatic
OBJS += iw_util.o iw_src/libiwstatic.a

EXE = iw_lib_sample

all: $(EXE)

%.o: %.c
	$(CXX) $(CXXFLAGS) $^ -o $@
		
iw_src/libiwstatic.a :
	$(IW_MAKE_ENV) $(MAKE) -C iw_src libiwstatic.a
	
$(EXE): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) $^ -o $@  $(LIBS)

clean:
	rm -f *.o $(OBJS) $(EXE)
	$(MAKE) -C iw_src clean

