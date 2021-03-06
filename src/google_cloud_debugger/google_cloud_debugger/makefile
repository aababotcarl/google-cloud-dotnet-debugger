# Directory that contains this makefile.
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
THIRD_PARTY_DIR:=$(realpath $(ROOT_DIR)/../../../third_party)

ifeq ($(COVERAGE),true)
  COVERAGE_ARG = -coverage
endif

CONFIGURATION_ARG = -g
ifeq ($(RELEASE),true)
  CONFIGURATION_ARG = 
endif

# .NET Core headers.
PREBUILT_PAL_INC = $(THIRD_PARTY_DIR)/coreclr/src/pal/prebuilt/inc/
PAL_RT_INC = $(THIRD_PARTY_DIR)/coreclr/src/pal/inc/rt/
PAL_INC = $(THIRD_PARTY_DIR)/coreclr/src/pal/inc/
CORE_CLR_INC = $(THIRD_PARTY_DIR)/coreclr/src/inc/
DBGSHIM_INC = $(THIRD_PARTY_DIR)/coreclr-subset/
OPTION_PARSER_INC = $(THIRD_PARTY_DIR)/option-parser/
GCLOUD_DEBUGGER = $(ROOT_DIR)/../google_cloud_debugger_lib/

# .NET Core libraries.
CORE_CLR_LIB = $(THIRD_PARTY_DIR)/coreclr/bin/Product/Linux.x64.Debug/lib/
CORE_CLR_LIB2 = $(THIRD_PARTY_DIR)/coreclr/bin/Product/Linux.x64.Debug/

# ANTLR Library directory.
ANTLR_LIB = $(THIRD_PARTY_DIR)/antlr/lib/cpp

INCDIRS = -I${PREBUILT_PAL_INC} -I${PAL_RT_INC} -I${PAL_INC} -I${CORE_CLR_INC} -I${DBGSHIM_INC} -I${GCLOUD_DEBUGGER} -I${OPTION_PARSER_INC} `pkg-config --cflags protobuf`
INCLIBS = -L${GCLOUD_DEBUGGER} -L${ANTLR_LIB} -L${CORE_CLR_LIB} -L${CORE_CLR_LIB2} -lcorguids -lcoreclrpal -lpalrt -leventprovider -lpthread -ldl -lm -luuid -lunwind-x86_64 -lstdc++ -ldbgshim `pkg-config --libs protobuf` -lgoogle_cloud_debugger_lib -lantlr_lib
CC_FLAGS = -x c++ -std=c++11 -fPIC -fms-extensions -fsigned-char -fwrapv -DFEATURE_PAL -DPAL_STDCPP_COMPAT -DBIT64 -DPLATFORM_UNIX ${CONFIGURATION_ARG} ${COVERAGE_ARG}

google_cloud_debugger: consoledebugger.o
	clang-3.9 -o google_cloud_debugger consoledebugger.o ${INCDIRS} ${CC_FLAGS} ${INCLIBS} -v

consoledebugger.o: consoledebugger.cc
	clang-3.9 consoledebugger.cc ${INCDIRS} ${CC_FLAGS} -c

clean:
	rm -f *.o *.a *.g* google_cloud_debugger
