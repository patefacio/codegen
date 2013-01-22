/******************************************************************************
 * fixed_size_char_array.hpp
 *
 * Copyright (c) Daniel Davidson
 *
 * Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)
 *******************************************************************************/
/*! 
 * \file fixed_size_char_array.hpp
 *
 * \brief 
 * 
 */
#ifndef _FCS_UTILS_FIXED_SIZE_CHAR_ARRAY_H_
#define _FCS_UTILS_FIXED_SIZE_CHAR_ARRAY_H_

#include <boost/array.hpp>
#include <ostream>
#include <cstring>
#include <cassert>

namespace fcs {
namespace utils {

  template < int ARRAY_SIZE > 
  class Fixed_size_char_array 
  {
  public:

    // Public static consts
    static const int BUFFER_SIZE = ARRAY_SIZE;
    static const int LAST_INDEX = BUFFER_SIZE - 1;
    // Class typedefs
    typedef boost::array< char, ARRAY_SIZE > Array_t;

  
// custom <Fixed_size_char_array public header section>

    Fixed_size_char_array() {
      data_[LAST_INDEX] = data_[0] = 0;
    }

    Fixed_size_char_array(char const* s) {
      this->operator=(s);
    }

    Fixed_size_char_array(Fixed_size_char_array const& other) {
      this->operator=(other.operator char const*());
    }

    void operator=(char const* s) {
      if(this->operator const char*() != s) {
#if defined(WIN32)
        strncpy_s(&data_[0], ARRAY_SIZE, s, LAST_INDEX);
#else
        std::strncpy(&data_[0], s, LAST_INDEX);
#endif
        data_[LAST_INDEX] = 0;
      }
    }

    operator char const* () const {
      return &data_[0];
    }

    operator char * () {
      return &data_[0];
    }

    char & operator[](int i) {
      return get_char_ref(i);
    }

    char const& operator[](int i) const {
      return get_char_ref(i);
    }

    operator std::string () const {
      return std::string(&data_[0]);
    }

    std::string str() const {
      return std::string(&data_[0]);
    }

    void clear() {
      data_[0] = 0;
    }

    void clean() {
      std::memset(&data_[0], 0, ARRAY_SIZE);
    }

    bool operator==(Fixed_size_char_array const& other) const {
      return *this == other.operator char const* ();
    }

    bool operator==(char const* other) const {
      if(&data_[0] == other) {
        return true;
      } else {
        return (0 == std::strncmp(const_cast<char *>(this->operator char const*()), other, ARRAY_SIZE));
      }
    }

    bool operator<(Fixed_size_char_array const& other) const {
      return (std::strncmp(const_cast<char *>(this->operator char const*()), other, ARRAY_SIZE) < 0);
    }

    bool operator!=(Fixed_size_char_array const& other) const {
      return !(*this == other);
    }

// end <Fixed_size_char_array public header section>

  private:

  
// custom <Fixed_size_char_array private header section>

    char & get_char_ref(int i) {
      assert(i < BUFFER_SIZE);
      return data_[i];
    }

// end <Fixed_size_char_array private header section>

    Array_t data_;
  };

  
// custom <Fixed_size_char_array post class>

    template < int ARRAY_SIZE >
    inline std::ostream& operator<<(std::ostream &out, Fixed_size_char_array< ARRAY_SIZE > const& item) {
        out << item.operator char const *();
        return out;
    }

// end <Fixed_size_char_array post class>

} // namespace utils
} // namespace fcs
#endif // _FCS_UTILS_FIXED_SIZE_CHAR_ARRAY_H_
