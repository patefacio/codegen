################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

lib = Library.new({ 
                    :classes => [
                                  CppClass.new({ 
                                                 :header_includes => [ 'exception', 'boost/exception/all.hpp',],
                                                 :name => 'make_exception',
                                                 :pre_class_section => true,
                                                 :no_class => true,
                                               }),

                                 ],
                    :header_only => true,
                    :static_only => true,
                    :namespace => ['fcs', 'utils', 'exception'],
                    :no_api_decl => true,
                  })

