################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/cpp'
require 'codegen'
require 'place'
include Codegen::Cpp

def get_version_commit
  begin
    require 'rubygems'
    require 'grit'
    include Grit
    repo = Repo.new(Place[Place.top] + '.git')
    %Q{#{repo.commits[0]}}
  rescue
    warn "Could not deal with git versioning"
    %Q{NO_GIT_REPOSITORY}
  end
end

version_commit = get_version_commit

classes = [

           CppClass.new({ 
                          :name => 'Version_control_commit',
                          :singleton => true,
                          :members => [
                                        { 
                                         :cpp_type => 'char const *',
                                         :init => %Q/"#{version_commit}"/,
                                         :const => true,
                                         :name => 'git_commit',
                                         :access => Codegen::Access::RO,
                                        },
                                        { 
                                         :cpp_type => 'char const *',
                                         :init => %Q/"git commit => #{version_commit}"/,
                                         :name => 'search_string',
                                         :const => true,
                                         :access => Codegen::Access::RO,
                                        }

                                       ],
                          :ctor_default => true,
                          :additions_header_post_class => 
                          [
                          ]
                        }),


           CppClass.new({ 
                          :name => 'Fixed_size_char_array',
                          :template_decls => [ 'int ARRAY_SIZE' ],
                          :public_header_section => true,
                          :private_header_section => true,
                          :header_includes => [ 'ostream', 'cstring', 'cassert', 'boost/array.hpp' ],
                          :public_static_consts => [ 
                                                     'static const int BUFFER_SIZE = ARRAY_SIZE',
                                                     'static const int LAST_INDEX = BUFFER_SIZE - 1',
                                                    ],
                          :public_typedefs => [ 
                                                'typedef boost::array< char, ARRAY_SIZE > Array_t',
                                               ],
                          :post_class_section => true,
                          :members => [
                                        { 
                                          :cpp_type => 'Array_t',
                                          :name => 'data',
                                        }
                                       ],
                          # :disable_windows_warnings => [ '4996' ],
                          :include_unit_test => true,
                        }),

           CppClass.new({ 
                          :name => 'Value_min_max',
                          :template_decls => [ 'typename T' ],
                          :public_header_section => true,
                          :struct => true,
                          :header_includes => [ 'boost/call_traits.hpp', ],
                          :ctor_default => true,
                          :public_static_consts => [ ],
                          :public_typedefs => [ 
                                                'typedef typename boost::call_traits< T >::param_type Param_type',
                                               ],
                          :members => [
                                        { 
                                         :cpp_type => 'T',
                                         :name => 'min_value',
                                         :public => true,
                                         :init => 'std::numeric_limits< T >::max()',
                                        },
                                        { 
                                         :cpp_type => 'T',
                                         :name => 'max_value',
                                         :public => true,
                                         :init => 'std::numeric_limits< T >::min()',
                                        },
                                       ],
                          :include_unit_test => true,
                        }),

           CppClass.new({ 
                          :name => 'Block_indenter',
                          :public_header_section => true,
                          :additional_classes => [
                                                   CppClass.new({ 
                                                                  :name => 'Block_current_indent',
                                                                  :public_header_section => true,
                                                                  :singleton => true,
                                                                  :members => [
                                                                                { 
                                                                                  :cpp_type => 'boost::thread_specific_ptr< int >',
                                                                                  :name => 'indentation_length',
                                                                                }
                                                                               ],
                                                                })
                                                  ],
                          :additional_classes_come_first => true,
                          :header_includes => [ 'boost/thread/tss.hpp' ],
                          :include_unit_test => true,
                        }),

           CppClass.new({ 
                          :name => 'file_path',
                          :public_header_section => true,
                          :no_class => true,
                          :header_namespace_begin_section => true,
                          :header_includes =>
                          [
                           'boost/filesystem/path.hpp',
                          ]
                        }),

           CppClass.new({ 
                          :name => 'histogram',
                          :no_class => true,
                          :include_unit_test => true,
                          :header_includes =>
                          [
                           'boost/accumulators/accumulators.hpp',
                           'boost/accumulators/statistics/density.hpp',
                          ],
                          :additional_classes =>
                          [
                           CppClass.new({ 
                                          :name => 'Histogram_statistical',
                                          :include_unit_test => true,
                                          :template_decls => [ 'typename T = double' ],
                                          :public_typedefs =>
                                          [
                                           'typedef boost::accumulators::accumulator_set< 
  T, 
  boost::accumulators::features< boost::accumulators::tag::density > > Accumulator_t',
                                           'typedef boost::iterator_range< typename std::vector< std::pair< T, T > >::iterator > Hist_results_t',
                                          ],
                                          :streamable_inline => true,
                                          :public_header_section => true,
                                          :header_includes =>
                                          [
                                           'boost/accumulators/accumulators.hpp',
                                           'boost/accumulators/statistics/density.hpp',
                                           'boost/algorithm/minmax_element.hpp',
                                          ],
                                          :members =>
                                          [
                                           { 
                                             :name => 'num_bins',
                                             :cpp_type => 'int',
                                             :member_ctor_defaulted => true,
                                             :init => 20,
                                             :access => Codegen::Access::RO,
                                           },
                                           { 
                                             :name => 'cache_size',
                                             :cpp_type => 'int',
                                             :member_ctor_defaulted => true,
                                             :init => 10,
                                             :access => Codegen::Access::RO,
                                           },
                                           { 
                                             :name => 'accumulator',
                                             :cpp_type => 'Accumulator_t',
                                             :init => 'boost::accumulators::tag::density::num_bins = num_bins_, boost::accumulators::tag::density::cache_size = cache_size_',
                                             :access => Codegen::Access::RO,
                                           },
                                          ],
                                        }),


                           CppClass.new({ 
                                          :name => 'Histogram',
                                          :streamable_inline => true,
                                          :streamers_included => true,
                                          :template_decls => [ 'typename T = double' ],
                                          :ctor_member_template_decls => [ 'typename IT' ],
                                          :ctor_member_init_section => true,
                                          :public_header_section => true,
                                          :public_typedefs =>
                                          [
                                           'typedef std::vector< double > Result_vector_t',
                                          ],
                                          :additional_ctor_parms =>
                                          [ ['IT', 'begin'], ['IT', 'end']],
                                          :members =>
                                          [
                                           { 
                                             :name => 'num_bins',
                                             :cpp_type => 'int',
                                             :member_ctor_defaulted => true,
                                             :init => 20,
                                             :access => Codegen::Access::RO,
                                           },
                                           { 
                                             :name => 'results',
                                             :cpp_type => 'Result_vector_t',
                                             :init => 'num_bins',
                                             :access => Codegen::Access::RO,
                                           },
                                          ]
                                        })
                          ]
                        }),

          ]

lib = Library.new({ 
                    :classes => classes,
                    :header_only => true,
                    :namespace => ['fcs', 'utils'],
                    :no_api_decl => true,
                    :build_cpp_includes => [ '$(TBB_INCLUDE_PATH)' ],
                  })


