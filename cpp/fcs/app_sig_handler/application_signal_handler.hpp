/******************************************************************************
 * application_signal_handler.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file application_signal_handler.hpp
 *
 * \brief Adds support for handling signals
 * 
 */
#ifndef _FCS_APP_SIG_HANDLER_APPLICATION_SIGNAL_HANDLER_H_
#define _FCS_APP_SIG_HANDLER_APPLICATION_SIGNAL_HANDLER_H_

#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "fcs/patterns/singleton.hpp"
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/thread.hpp>
#include <exception>
#include <vector>
#include <csignal>

namespace fcs {
namespace app_sig_handler {

  //! Adds support for handling signals
  template < typename LOCK_TYPE = boost::mutex,
             typename GUARD_TYPE = boost::lock_guard< LOCK_TYPE > > 
  class Application_signal_handler :
    public fcs::patterns::Singleton< Application_signal_handler< LOCK_TYPE, GUARD_TYPE > > 
  {
  public:

    // Class typedefs
    typedef boost::function < bool (int) > Handler_function_t;
    typedef std::vector< Handler_function_t > Handler_function_list_t;

  protected:

    Application_signal_handler() :
      handler_list_(),
      instance_mutex_() 
    {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Created Application_signal_handler(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
      ctor_default_init();
    }

  public:

    ~Application_signal_handler() {
      pantheios::log(PANTHEIOS_SEV_INFORMATIONAL, "Destroyed Application_signal_handler(", 
                     pantheios::hex_ptr(reinterpret_cast<void*>(this)),
                     pantheios::character(')'));
    }

  
// custom <Application_signal_handler public header section>

    void add_handler(Handler_function_t const& handler) {
      GUARD_TYPE guard(instance_mutex_);
      handler_list_.push_back(handler);
    }

#if !defined(_MSC_VER)

    static inline void signal_handler_thread(sigset_t selected_signals) {
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Signal handler thread running"); 
      while(true) {
        int signal(0);
        int rc(sigwait(&selected_signals, &signal));
        if(rc) {
          throw std::runtime_error("Unable to wait for signals");
        } else {
          pantheios::log(PANTHEIOS_SEV_DEBUG, "Handling signal - calling user handlers");
          if(!Application_signal_handler::get_instance()->call_handlers(signal)) {
            break;
          }
        }
      }
      pantheios::log(PANTHEIOS_SEV_DEBUG, "Signal handler done"); 
    }

    bool call_handlers(int signal) {
      bool keep_running(false);
      Handler_function_list_t::const_iterator it(handler_list_.begin());
      Handler_function_list_t::const_iterator end(handler_list_.end());
      for(; it != end; ++it) {
        keep_running |= (*it)(signal);
      }
      return keep_running;
    }

#endif

// end <Application_signal_handler public header section>

  private:

    //! Initialize the instance
    inline void ctor_default_init() {
      
// custom <Application_signal_handler::ctor_default_init>

#if !defined(_MSC_VER)

      sigset_t selected_signals;
      sigemptyset(&selected_signals);
      sigaddset(&selected_signals, SIGHUP);
      sigaddset(&selected_signals, SIGINT);
      sigaddset(&selected_signals, SIGTERM);
      int rc(pthread_sigmask(SIG_BLOCK, &selected_signals, 0));
      if(rc) {
        throw std::runtime_error("Unable to mask signals");
      } else {
        boost::thread handler_thread(boost::bind(&signal_handler_thread, selected_signals)); 
      }

#endif

// end <Application_signal_handler::ctor_default_init>
    }
    //! List of handlers to execute on signal <I>inaccessible</I>
    Handler_function_list_t handler_list_;
    //! Protection for instance data <I>inaccessible</I>
    LOCK_TYPE instance_mutex_;
    friend class fcs::patterns::Singleton_impl< Application_signal_handler >;
  };

} // namespace app_sig_handler
} // namespace fcs
#endif // _FCS_APP_SIG_HANDLER_APPLICATION_SIGNAL_HANDLER_H_
