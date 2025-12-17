// -*- mode: C++; c-file-style: "cc-mode" -*-
//=============================================================================
//
// Code available from: https://verilator.org
//
// Copyright 2001-2025 by Wilson Snyder. This program is free software; you
// can redistribute it and/or modify it under the terms of either the GNU
// Lesser General Public License Version 3 or the Perl Artistic License
// Version 2.0.
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=============================================================================
///
/// \file
/// \brief Verilated tracing in VCD format header
///
/// User wrapper code should use this header when creating VCD traces.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_VCD_D_H_
#define VERILATOR_VERILATED_VCD_D_H_

#include "verilated.h"
#include "verilated_trace.h"

class ESDLVerilatedVcdD {
public:
  VerilatedVcdC* m_vcd_c;

  explicit ESDLVerilatedVcdD(VerilatedVcdFile* filep = nullptr) { m_vcd_c = new VerilatedVcdC(filep); }

  virtual ~ESDLVerilatedVcdD() { delete m_vcd_c; }

  bool isOpen() const VL_MT_SAFE  { return m_vcd_c->isOpen(); }
  /// Open a new VCD file
  /// This includes a complete header dump each time it is called,
  /// just as if this object was deleted and reconstructed.
  virtual void open(const char* filename) const VL_MT_SAFE  { return m_vcd_c->isOpen(); }
  /// Continue a VCD dump by rotating to a new file name
  /// The header is only in the first file created, this allows
  /// "cat" to be used to combine the header plus any number of data files.
  void openNext(bool incFilename = true) VL_MT_SAFE { m_vcd_c->openNext(incFilename); }
  /// Set size in bytes after which new file should be created
  /// This will create a header file, followed by each separate file
  /// which might be larger than the given size (due to chunking and
  /// alignment to a start of a given time's dump).  Any file but the
  /// first may be removed.  Cat files together to create viewable vcd.
  void rolloverSize(size_t rolloverSize) VL_MT_SAFE { m_vcd_c->rolloverSize(rolloverSize); }
  /// Close dump
  void close() VL_MT_SAFE { m_vcd_c->close(); }
  /// Flush dump
  void flush() VL_MT_SAFE { m_vcd_c->flush(); }
  /// Write one cycle of dump data
  /// Call with the current context's time just after eval'ed,
  /// e.g. ->dump(contextp->time())
  void dump(vluint64_t timeui) VL_MT_SAFE { m_vcd_c->dump(timeui); }
  /// Write one cycle of dump data - backward compatible and to reduce
  /// conversion warnings.  It's better to use a vluint64_t time instead.
  void dump(double timestamp) { m_vcd_c->dump(timestamp); }
  void dump(vluint32_t timestamp) { m_vcd_c->dump(timestamp); }
  void dump(int timestamp) { m_vcd_c->dump(timestamp); }

  // METHODS - Internal/backward compatible
  // \protectedsection

  // Set time units (s/ms, defaults to ns)
  // Users should not need to call this, as for Verilated models, these
  // propage from the Verilated default timeunit
  void set_time_unit(const char* unit) VL_MT_SAFE { m_vcd_c->set_time_unit(unit); }
  void set_time_unit(const std::string& unit) VL_MT_SAFE { m_vcd_c->set_time_unit(unit); }
  // Set time resolution (s/ms, defaults to ns)
  // Users should not need to call this, as for Verilated models, these
  // propage from the Verilated default timeprecision
  void set_time_resolution(const char* unit) VL_MT_SAFE { m_vcd_c->set_time_resolution(unit); }
  void set_time_resolution(const std::string& unit) VL_MT_SAFE { m_vcd_c->set_time_resolution(unit); }
  // Set variables to dump, using $dumpvars format
  // If level = 0, dump everything and hier is then ignored
  void dumpvars(int level, const std::string& hier) VL_MT_SAFE { m_vcd_c->dumpvars(level, hier); }

  // Internal class access
  VerilatedVcd* spTrace() { return m_vcd_c->spTrace(); }

  // C++ Class Object Access
  VerilatedVcdC* getTrace() { return m_vcd_c; }
  VerilatedTraceBaseC* getTraceBase() { return m_vcd_c; }
  
}

#endif  // guard
