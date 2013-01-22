################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
require 'place'
include Codegen::Cpp
classes = [

           CppClass.new({ 
                          :name => 'timestamp',
                          :header_only => true,
                          :is_namespace_header => true,
                          :header_namespace_end_section => true,
                          :header_includes => 
                          [
                           'boost/date_time/microsec_time_clock.hpp',
                           'boost/date_time/posix_time/posix_time.hpp',
                           'boost/date_time/c_local_time_adjustor.hpp',
                           'boost/date_time/local_time_adjustor.hpp',
                          ],
                          :public_typedefs => 
                          [
                           typedef_timestamp,
                           typedef_time_duration,
                          ],
                          :public_header_section => true,
                          :include_unit_test => true,
                          :members => [ ],
                        }),

           CppClass.new({ 
                          :name => 'timestamp_from_file',
                          :header_namespace_end_section => true,
                          :no_class => true,
                          :header_includes => 
                          [
                           'sys/types.h',
                           'sys/stat.h',
                           'unistd.h',
                           'boost/filesystem/path.hpp',
                           'boost/filesystem/operations.hpp',
                          ],
                          :public_typedefs => 
                          [
                          ],
                          :public_header_section => true,
                          :include_unit_test => true,
                          :members => [ ],
                        }),

          ]

lib = Library.new({ 
                    :classes => classes,
                    :header_only => true,
                    :namespace => ['fcs', 'timestamp'],
                    :no_api_decl => true,
                  })


