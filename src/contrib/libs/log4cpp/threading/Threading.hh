/*
 * Threading.hh
 *
 * Copyright 2002, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2002, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_THREADING_THREADING_HH
#define _LOG4CPP_THREADING_THREADING_HH

#include <contrib/libs/log4cpp/Portability.hh>

#ifdef LOG4CPP_HAVE_THREADING

#ifdef LOG4CPP_USE_OMNITHREADS
#include <contrib/libs/log4cpp/threading/OmniThreads.hh>
#endif

#ifdef LOG4CPP_USE_BOOSTTHREADS
#include <contrib/libs/log4cpp/threading/BoostThreads.hh>
#endif

#ifdef LOG4CPP_USE_MSTHREADS
#include <contrib/libs/log4cpp/threading/MSThreads.hh>
#endif

#ifdef LOG4CPP_USE_PTHREADS
#include <contrib/libs/log4cpp/threading/PThreads.hh>
#endif

#else /* LOG4CPP_HAVE_THREADING */
#include <contrib/libs/log4cpp/threading/DummyThreads.hh>
#endif /* LOG4CPP_HAVE_THREADING */

#endif
