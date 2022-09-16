#ifndef TRACE_H
#define TRACE_H

#include "Arduino.h"
#include <stdarg.h>
#include <stdio.h>
#include "tcp_server.h"

#define SERIAL_TRACE    1u
#define TCP_TRACE       1u


#if TCP_TRACE
#ifndef __XC32
#define tcp_trace __tcp_trace
void __tcp_trace(const char *fmt, ...);
#else
#define print_trace printf
#endif
#else
#define tcp_trace(arg...) _NOP()
#endif


#if SERIAL_TRACE
#ifndef __XC32
#define serial_trace __serial_trace
void __serial_trace(const char *fmt, ...);
#define serial_init __serial_init
void __serial_init(int badrate);
#endif
#else
#define serial_init(agr) _NOP()
#define serial_trace(arg...) _NOP()
#endif

#endif