// -*- mode: C++; c-file-style: "cc-mode" -*-
//=============================================================================
//
// Code available from: https://verilator.org
//
// Copyright 2001-2025 by Puneet Goel. This program is free software; you
// can redistribute it and/or modify it under the terms of either the GNU
// Lesser General Public License Version 3 or the Perl Artistic License
// Version 2.0.
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=============================================================================
///
/// \file
/// \brief Verilated tracing in FST format header
///
/// User wrapper code should use this header when creating FST traces.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_FST_D_H_
#define VERILATOR_VERILATED_FST_D_H_

#include "verilated.h"
#include "verilated_trace.h"

#include "verilated_fst_c.h"

#include <string>

//=============================================================================
// VerilatedFstD
/// VerilatedFstC class wrapper for interfacing with Dlang

class VerilatedFstD {
public:
    VerilatedFstC* m_fst_c;

    /// Construct the dump. Optional argument is ignored.
    explicit VerilatedFstD(void* filep = nullptr) {
	m_fst_c = new VerilatedFstC(filep);
    }
    /// Destruct, flush, and close the dump
    virtual ~VerilatedFstD() { delete m_fst_c; }

    // METHODS - User called

    /// Return if file is open
    bool isOpen() const override VL_MT_SAFE { return m_fst_c->isOpen(); }
    /// Open a new FST file
    virtual void open(const char* filename) VL_MT_SAFE  { m_fst_c->open(filename); };
    /// Close dump
    void close() VL_MT_SAFE { m_fst_c->close(); }
    /// Flush dump
    void flush() VL_MT_SAFE { m_fst_c->flush(); }
    /// Write one cycle of dump data
    /// Call with the current context's time just after eval'ed,
    /// e.g. ->dump(contextp->time())
    void dump(uint64_t timeui) { m_fst_c->dump(timeui); }
    /// Write one cycle of dump data - backward compatible and to reduce
    /// conversion warnings.  It's better to use a uint64_t time instead.
    void dump(double timestamp) { m_fst_c->dump(timestamp); }
    void dump(uint32_t timestamp) { m_fst_c->dump(timestamp); }
    void dump(int timestamp) { m_fst_c->dump(timestamp); }

    // METHODS - Internal/backward compatible
    // \protectedsection

    // Set time units (s/ms, defaults to ns)
    // Users should not need to call this, as for Verilated models, these
    // propagate from the Verilated default timeunit
    void set_time_unit(const char* unitp) VL_MT_SAFE { m_fst_c->set_time_unit(unitp); }
    void set_time_unit(const std::string& unit) VL_MT_SAFE { m_fst_c->set_time_unit(unit); }
    // Set time resolution (s/ms, defaults to ns)
    // Users should not need to call this, as for Verilated models, these
    // propagate from the Verilated default timeprecision
    void set_time_resolution(const char* unitp) VL_MT_SAFE { m_fst_c->set_time_resolution(unitp); }
    void set_time_resolution(const std::string& unit) VL_MT_SAFE { m_fst_c->set_time_resolution(unit); }
    // Set variables to dump, using $dumpvars format
    // If level = 0, dump everything and hier is then ignored
    void dumpvars(int level, const std::string& hier) VL_MT_SAFE { m_fst_c->dumpvars(level, hier); }

    // Internal class access
    VerilatedFst* spTrace() { return m_fst_c->spTrace(); }

    // C++ Class Object Access
    VerilatedFstC* getTrace() { return m_fst_c; }
    VerilatedTraceBaseC* getTraceBase() { return m_fst_c; }
  
};

#endif  // guard
