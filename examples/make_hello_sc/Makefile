######################################################################
#
# DESCRIPTION: Verilator Example: Small Makefile
#
# This calls the object directory makefile.  That allows the objects to
# be placed in the "current directory" which simplifies the Makefile.
#
# This file ONLY is placed under the Creative Commons Public Domain, for
# any use, without warranty, 2020 by Wilson Snyder.
# SPDX-License-Identifier: CC0-1.0
#
######################################################################
# Check for sanity to avoid later confusion

ifneq ($(words $(CURDIR)),1)
  $(error Unsupported: GNU Make cannot build in directories containing spaces, build elsewhere: '$(CURDIR)')
endif

######################################################################

# This is intended to be a minimal example.  Before copying this to start a
# real project, it is better to start with a more complete example,
# e.g. examples/make_tracing_sc.

# If $VERILATOR_ROOT isn't in the environment, we assume it is part of a
# package install, and verilator is in your path. Otherwise find the
# binary relative to $VERILATOR_ROOT (such as when inside the git sources).
ifeq ($(VERILATOR_ROOT),)
  VERILATOR = verilator
else
  export VERILATOR_ROOT
  VERILATOR = $(VERILATOR_ROOT)/bin/verilator
endif

# Check if SC exists via a verilator call (empty if not)
SYSTEMC_EXISTS := $(shell $(VERILATOR) --get-supported SYSTEMC)

ifneq ($(SYSTEMC_EXISTS),)
  default: run
else
  default: nosc
endif

run:
	@echo "-- Verilator hello-world simple example"
	@echo "-- VERILATE & COMPILE ------"
	$(VERILATOR) -sc --exe --build -j top.v sc_main.cpp
	@echo "-- RUN ---------------------"
	obj_dir/Vtop
	@echo "-- DONE --------------------"
	@echo "Note: Once this example is understood, see examples/make_tracing_sc."
	@echo "Note: See also https://verilator.org/guide/latest/examples.html"

######################################################################

nosc:
	@echo
	@echo "%Skip: SYSTEMC_INCLUDE not in environment"
	@echo "(If you have SystemC see the README, and rebuild Verilator)"
	@echo

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_dir *.log *.dmp *.vpd core
