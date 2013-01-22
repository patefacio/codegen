/******************************************************************************
 * pantheios_debug_log.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file pantheios_debug_log.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_PANTHEIOS_DEBUG_LOG_H_
#define _FCS_UTILS_PANTHEIOS_DEBUG_LOG_H_

#include <pantheios/pantheios.hpp>

namespace fcs {
namespace utils {


  void set_log_level(::pantheios::pan_sev_t);

#if defined(DEBUG)


  template < typename T0 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0) {
    return ::pantheios::log(severity, t0);
  }

  template < typename T0, typename T1 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1) {
    return ::pantheios::log(severity, t0, t1);
  }

  template < typename T0, typename T1, typename T2 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2) {
    return ::pantheios::log(severity, t0, t1, t2);
  }

  template < typename T0, typename T1, typename T2, typename T3 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3) {
    return ::pantheios::log(severity, t0, t1, t2, t3);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24, T25 const& t25) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24, T25 const& t25, T26 const& t26) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24, T25 const& t25, T26 const& t26, T27 const& t27) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24, T25 const& t25, T26 const& t26, T27 const& t27, T28 const& t28) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24, T25 const& t25, T26 const& t26, T27 const& t27, T28 const& t28, T29 const& t29) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24, T25 const& t25, T26 const& t26, T27 const& t27, T28 const& t28, T29 const& t29, T30 const& t30) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30);
  }

  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9, T10 const& t10, T11 const& t11, T12 const& t12, T13 const& t13, T14 const& t14, T15 const& t15, T16 const& t16, T17 const& t17, T18 const& t18, T19 const& t19, T20 const& t20, T21 const& t21, T22 const& t22, T23 const& t23, T24 const& t24, T25 const& t25, T26 const& t26, T27 const& t27, T28 const& t28, T29 const& t29, T30 const& t30, T31 const& t31) {
    return ::pantheios::log(severity, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31);
  }
#else

  template < typename T0 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&) { return 0; }


  template < typename T0, typename T1 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&) { return 0; }


  template < typename T0, typename T1, typename T2 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&, T25 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&, T25 const&, T26 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&, T25 const&, T26 const&, T27 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&, T25 const&, T26 const&, T27 const&, T28 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&, T25 const&, T26 const&, T27 const&, T28 const&, T29 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&, T25 const&, T26 const&, T27 const&, T28 const&, T29 const&, T30 const&) { return 0; }


  template < typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31 >
  inline 
  int debug_log(::pantheios::pan_sev_t severity, T0 const&, T1 const&, T2 const&, T3 const&, T4 const&, T5 const&, T6 const&, T7 const&, T8 const&, T9 const&, T10 const&, T11 const&, T12 const&, T13 const&, T14 const&, T15 const&, T16 const&, T17 const&, T18 const&, T19 const&, T20 const&, T21 const&, T22 const&, T23 const&, T24 const&, T25 const&, T26 const&, T27 const&, T28 const&, T29 const&, T30 const&, T31 const&) { return 0; }

#endif



} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_PANTHEIOS_DEBUG_LOG_H_
