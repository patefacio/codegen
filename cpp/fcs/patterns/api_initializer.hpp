/******************************************************************************
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
#ifndef _FCS_PATTERNS_API_INITIALIZER_HPP_
#define _FCS_PATTERNS_API_INITIALIZER_HPP_

#include "fcs/patterns/singleton.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/function.hpp>
#include <map>
#include <list>
#include <utility>
#include <memory>

namespace fcs {
namespace patterns {

  /** \brief Provides mechanism to run functor on scope exit
   */
  template < typename FUNCTOR >
  class Functor_scope_exit {

  public:
    typedef FUNCTOR Functor_t;

    Functor_scope_exit() : functor_(0) {
      FCS_LOG_CTOR();
    }

    Functor_scope_exit(Functor_t functor) : functor_(functor) {
      FCS_LOG_CTOR();
    }

    ~Functor_scope_exit() { 
      if(functor_) { 
        functor_(); 
      }
      FCS_LOG_DTOR();
    }
    Functor_t functor() {
      return functor_;
    }
  private:
    Functor_t functor_;
  };

  /// Common C void function
  typedef void (*VOID_FUNC)(void);

  /** \brief Registry for functions pairs that need to be run at startup and
   * shutdown.
   * 
   */
  template < typename INIT_FUNC = VOID_FUNC, 
             typename UNINIT_FUNC = VOID_FUNC,
             typename MUTEX_TYPE = boost::mutex,
             typename LOCK_TYPE = boost::lock_guard< MUTEX_TYPE > >
  class Api_initializer_registry : 
    public Singleton< Api_initializer_registry < INIT_FUNC, UNINIT_FUNC, MUTEX_TYPE, LOCK_TYPE > > {

  public:

    typedef std::shared_ptr< Functor_scope_exit < UNINIT_FUNC > > Functor_scope_exit_ptr;
    typedef std::map< INIT_FUNC, Functor_scope_exit_ptr > Registry_map_t;
    typedef std::list< Functor_scope_exit_ptr > Registry_list_t;
    typedef typename Singleton< Api_initializer_registry < INIT_FUNC, UNINIT_FUNC > >::Static_data_t Static_data_t;

    friend class Singleton_t;

    Api_initializer_registry() {
      FCS_LOG_CTOR();
    }

    ~Api_initializer_registry() {
      FCS_LOG_DTOR();
    }

    /// Runs the init function and saves the uninit function to be run in
    /// correct order when program shuts down (after main)
    Functor_scope_exit_ptr register_initializer(INIT_FUNC init, UNINIT_FUNC uninit) {
      typedef std::pair< typename Registry_map_t::iterator, bool > Insert_result_t;
      typedef MUTEX_TYPE Mutex_t;
      typedef LOCK_TYPE Lock_t;

      Lock_t lock(mutex_);
      Insert_result_t insert_result
        (registry_map_.insert
         (typename Registry_map_t::value_type(init, Functor_scope_exit_ptr())));

      if(insert_result.second) {
        insert_result.first->second = Functor_scope_exit_ptr
          (new Functor_scope_exit < UNINIT_FUNC >(uninit));
        registry_list_.push_front(insert_result.first->second);
        if(init) {
          init();
        }
      } else {
        if(insert_result.first->second->functor() != uninit) {
          throw std::logic_error
            ("Uninit functions must be consistent across translation units");
        }
      }
      return insert_result.first->second;
    }

  private:
    /// \brief Provides ordering for invoking uninit in reverse order
    Registry_list_t registry_list_;
    /// \brief Used to match init funcs with corresponding uninit funcs
    Registry_map_t registry_map_;
    /// \brief Protect concurrent access to the map and list
    MUTEX_TYPE mutex_;
  };
    
  /** \brief Used to add init/uninit functions for program initialization.
   *
   * For example, to register functions my_init/my_uninit use: <code>
   * fcs::patterns::Api_initializer< VFUNC, VFUNC > 
   * registry = fcs::patterns::Api_initializer< VFUNC,  VFUNC>
   * (&my_init, &my_uninit);
   * </code>
   */
  template < typename INIT_FUNC = VOID_FUNC, typename UNINIT_FUNC = VOID_FUNC >
  class Api_initializer {

  public:
    typedef Api_initializer_registry< INIT_FUNC, 
                                      UNINIT_FUNC > Api_initializer_registry_t;

    Api_initializer(INIT_FUNC init, UNINIT_FUNC uninit) {
      FCS_LOG_CTOR();
      uninit_ = Api_initializer_registry_t::get_instance()->register_initializer(init, uninit);
    }

    ~Api_initializer() {
      FCS_LOG_DTOR();
    }
  private:

    typename Api_initializer_registry_t::Functor_scope_exit_ptr uninit_;
  };

}}

#endif
