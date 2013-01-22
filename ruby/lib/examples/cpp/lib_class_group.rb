require 'codegen/cpp'
require 'codegen'
require 'codegen/cpp/cpp_class_group'
include Codegen::Cpp

classes = \
[
 CppClass.new({ 
                :name => 'A',
                :streamable_inline => true,
                :members =>
                [
                 { 
                   :name => 'a1',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"a1"'
                 },
                 { 
                   :name => 'a2',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"a2"'
                 },
                 { 
                   :name => 'a3',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"a3"'
                 },
                 { 
                   :name => 'total_chars_observed',
                   :cpp_type => 'boost::int64_t',
                   :member_ctor_defaulted => true,
                   :init => '0'
                 },
                 { 
                   :name => 'sum_log_do_good',
                   :cpp_type => 'double',
                   :member_ctor_defaulted => true,
                   :init => '0'
                 },
                 { 
                   :name => 'sum_rand_log_do_good',
                   :cpp_type => 'double',
                   :member_ctor_defaulted => true,
                   :init => '0'
                 },
                 { 
                   :name => 'sum_log_do_bad',
                   :cpp_type => 'double',
                   :member_ctor_defaulted => true,
                   :init => '0'
                 },
                 { 
                   :name => 'sum_rand_log_do_bad',
                   :cpp_type => 'double',
                   :member_ctor_defaulted => true,
                   :init => '0'
                 },
                ]
              }),

 CppClass.new({ 
                :name => 'B',
                :streamable_inline => true,
                :members =>
                [
                 { 
                   :name => 'b1',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"b1"'
                 },
                 { 
                   :name => 'b2',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"b2"'
                 },
                 { 
                   :name => 'b3',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"b3"'
                 }
                ]
              }),

 CppClass.new({ 
                :name => 'C',
                :streamable_inline => true,
                :members =>
                [
                 { 
                   :name => 'c1',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"c1"'
                 },
                 { 
                   :name => 'c2',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"c2"'
                 },
                 { 
                   :name => 'c3',
                   :cpp_type => 'std::string',
                   :member_ctor_defaulted => true,
                   :init => '"c3"'
                 }
                ]
              })
]

class_group = {  :name => 'One_ring', 
  :classes => classes, 
  :namespace => ['samples', 'examples', 'group'],
  :methods =>
  [
   { 
     :name => 'observe',
     :brief => 'Observes the data',
     :return => 'void',
     :args => [ ['int', 'i'], ['char const *', 's' ]],
   },
   { 
     :name => 'do_good',
     :brief => 'Does good',
     :return => 'void',
     :args => [ ['int', 'i'],],
   },
   { 
     :name => 'do_bad',
     :brief => 'Does bad',
     :return => 'void',
     :args => [ ['int', 'i'],],
   },
  ]}

class_vgroup = Marshal.load(Marshal.dump(class_group))
class_group = ClassGroup.new class_group
class_vgroup[:virtual] = true
class_vgroup = ClassGroup.new class_vgroup

Library.new({ 
              :classes => class_group.classes,
              :header_only => true,
              :static_only => true,
              :namespace => ['samples', 'examples', 'group'],
              :no_api_decl => true,
            })

Library.new({ 
              :classes => class_vgroup.classes,
              :header_only => true,
              :static_only => true,
              :namespace => ['samples', 'examples', 'vgroup'],
              :no_api_decl => true,
            })


program_options = 
  CppOptionParserGenerator.new( {
                                  :name => 'sample_group_dispatch',
                                  :standard_logging => true,
                                  :brief => 'Dispatch with simple jump table and void* allowing inline',
                                  :options => [
                                               { 
                                                 :name => 'iterations',
                                                 :short_name => 'i',
                                                 :cpp_type => 'int',
                                                 :descr => 'Number of iterations on the loop',
                                                 :default_value => '1000000',
                                               },
                                              ],

                                })

program_voptions = 
  CppOptionParserGenerator.new( {
                                  :name => 'sample_group_vdispatch',
                                  :standard_logging => true,
                                  :brief => 'Dispatch with simple jump table and void* allowing inline',
                                  :options => [
                                               { 
                                                 :name => 'iterations',
                                                 :short_name => 'i',
                                                 :cpp_type => 'int',
                                                 :descr => 'Number of iterations on the loop',
                                                 :default_value => '1000000',
                                               },
                                              ],

                                })


app = Application.new(
                      { 
                        :name => 'sample_group_dispatch',
                        :log_pantheios_fe => true,
                        :program_options => program_options,
                        :folder => 'performance',
                        :classes => [],
                        :namespace => [ 'samples', 'examples', ],
                        :app_includes => 
                        [ 
                         'samples/utils/streamers/vector.hpp',
                         'samples/sample/group/one_ring_dispatcher.hpp',
                         'samples/sample/group/one_ring_dispatch.hpp',
                         'samples/orm/code_metrics/block_tracker_orm.hpp',
                         'boost/foreach.hpp',
                         'algorithm',
                        ],
                        :jam_requirements => [ 
                                              '/site-config//otl',
                                              '/site-config//boost_program_options',
                                              '/site-config//boost_filesystem',
                                              '/site-config//boost_date_time',
                                              '$(PANTHEIOS_LIBS)',
                                             ],
                        :uses_pantheios => true,
                        
                      }
                      )

app = Application.new(
                      { 
                        :name => 'sample_group_vdispatch',
                        :log_pantheios_fe => true,
                        :program_options => program_voptions,
                        :folder => 'performance',
                        :classes => [],
                        :namespace => [ 'samples', 'examples', ],
                        :app_includes => 
                        [ 
                         'samples/utils/streamers/vector.hpp',
                         'samples/sample/vgroup/one_ring_base.hpp',
                         'samples/sample/vgroup/a_inl.hpp',
                         'samples/sample/vgroup/b_inl.hpp',
                         'samples/sample/vgroup/c_inl.hpp',
                         'samples/orm/code_metrics/block_tracker_orm.hpp',
                         'boost/foreach.hpp',
                         'algorithm',
                        ],
                        :jam_requirements => [ 
                                              '/site-config//otl',
                                              '/site-config//boost_program_options',
                                              '/site-config//boost_filesystem',
                                              '/site-config//boost_date_time',
                                              '$(PANTHEIOS_LIBS)',
                                             ],
                        :uses_pantheios => true,
                        
                      }
                      )
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
