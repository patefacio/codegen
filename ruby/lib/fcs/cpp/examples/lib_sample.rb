require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

classes = [

           CppClass.new({ 
                          :name => 'apiheader',
                          :api_decl => 'SIMPLE_API',
                          :is_api_header => true,
                          :brief => 'Test performance of implementation of operator<',
                          :public_typedefs => [ 
                                               'typedef boost::function<int (void)> BoostFunctorGoo', 
                                               typedef_shared_ptr_of('boost::filesystem::path', 'PathPtr')
                                              ],
                          :header_includes => [ 'map', 'set', 'boost/lambda/lambda.hpp', 'boost/filesystem.hpp' ],
                          :enums => [ Enumeration.new(
                                                      {
                                                        :name => 'ApiHeaderFooEnum', :values => ['za_xyz', 'zb_xyz', 'zb_pdq'],
                                                        :pick_list_text_proc => proc {|x| x.gsub(/y/,'')}}), 
                                      Enumeration.new(
                                                      {
                                                        :name => 'GooEnum', :values => ['ga_xyz', 'gb_xyz', 'gc'],
                                                        :mask => true,
                                                        :pick_list_text_proc => proc {|x| x.gsub(/y/,'')}}),
                                    ],
                        }),

           CppClass.new(
                        :name => 'sqlstuff',
                        :descr => '
Example of formulas:
 The distance between \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$ is 
  \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$.

 Here is an example of inserting a mathematical formula into the text:
 If we wanted to insert the formula centered on a separate line:
 \f$
 \sqrt{ (x_2-x_1)^2 + (y_2 - y_1)^2 }
 \f$

And even more complex:

  \f[
    |I_2|=\left| \int_{0}^T \psi(t) 
             \left\{ 
                u(a,t)-
                \int_{\gamma(t)}^a 
                \frac{d\theta}{k(\theta,t)}
                \int_{a}^\theta c(\xi)u_t(\xi,t)\,d\xi
             \right\} dt
          \right|
  \f]

',
                        :boost_noncopyable => true,
                        :comparable => true,
                        :op_equal => true,
                        :header_only => true,
                        #                        :ctor_member => true,
                        :members => 
                        [
                         { 
                           :cpp_type => 'int',
                           :name => 'year',
                         },
                         { 
                           :cpp_type => 'int',
                           :name => 'month',
                         },
                         { 
                           :cpp_type => 'int',
                           :name => 'day',
                         },
                         { 
                           :cpp_type => 'int',
                           :name => 'hour',
                         },
                         { 
                           :cpp_type => 'int',
                           :name => 'minute',
                         },
                         { 
                           :cpp_type => 'int',
                           :name => 'second',
                         },
                         { 
                           :cpp_type => 'int',
                           :name => 'fraction',
                         },
                        ]
                        ),

           CppClass.new(
                        { 
                          :xml_serializable => true,
                          :text_serializable => true,
                          :binary_serializable => true,
                          :forward_enums => 
                          [ 
                           Enumeration.new(
                                           {
                                             :name => 'ApiHeaderFooEnum_Forward', :values => ['cls_fwd_za_xyz', 'cls_fwd_zb_xyz'],
                                             :pick_list_text_proc => proc {|x| x.gsub(/y/,'')}}), 
                           Enumeration.new(
                                           {
                                             :name => 'GooEnum_Forward', :values => ['cls_fwd_a_xyz', 'cls_fwd_b_xyz', 'cls_fwd_c'],
                                             :mask => true,
                                             :pick_list_text_proc => proc {|x| x.gsub(/y/,'')}}),

                           Enumeration.new(
                                           {
                                             :name => 'ZoopEnum', 
                                             :values => ['a_xyz', 'b_xyz', 'c'],
                                             :supports_picklist => true,
                                           }),

                          ],

                          :enums => 
                          [ 
                           Enumeration.new(
                                           {
                                             :name => 'ApiHeaderFooEnum_Cls', :values => ['cls_za_xyz', 'cls_zb_xyz'],
                                             :pick_list_text_proc => proc {|x| x.gsub(/y/,'')}}), 
                           Enumeration.new(
                                           {
                                             :name => 'GooEnum_Cls', :values => ['cls_a_xyz', 'cls_b_xyz', 'cls_c'],
                                             :mask => true,
                                             :pick_list_text_proc => proc {|x| x.gsub(/y/,'')}}),
                           Enumeration.new(
                                           {
                                             :name => 'ZoopEnum', 
                                             :values => ['za_xyz', 'zb_xyz', 'zc'],
                                             :supports_picklist => true,
                                           }),

                           Enumeration.new(
                                           {
                                             :name => 'VooEnum', 
                                             :values => ['va_xyz', 'vb_xyz', 'vc'],
                                             :inline => true,
                                             :supports_picklist => true,
                                           }),

                          ],
                          :ctor_default_init_section => true,
                          :members => 
                          [
                           Member.new({ :cpp_type =>'std::string', :name =>'s1', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s2', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s3', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s4', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s5', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s6', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s7', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s8', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'s9', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'std::string', :name =>'sA', :pass_by_ref =>true, :static =>true, :init =>'""'}), 
                           Member.new({ :cpp_type =>'int', :name =>'i1', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'int', :name =>'i2', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'int', :name =>'i3', :pass_by_ref =>true, :access => Codegen::Access::RW, :init => '1234567'}), 
                           Member.new({ :cpp_type =>'int', :name =>'i4', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'int', :name =>'i5', :pass_by_ref =>true,}), 
                           Member.new({ :cpp_type =>'int', :name =>'i6', :pass_by_ref =>true,}), 
                           Member.new({ :cpp_type =>'int', :name =>'i7', :pass_by_ref =>true,}), 
                           Member.new({ :cpp_type =>'int', :name =>'i8', :pass_by_ref =>true,}), 
                           Member.new({ :cpp_type =>'int', :name =>'i9', :pass_by_ref =>true,}), 
                           Member.new({ :cpp_type =>'int', :name =>'iA', :pass_by_ref =>true,}), 
                           Member.new({ :cpp_type =>'NameList', :name =>'nl', :pass_by_ref =>true,:access => Codegen::Access::RW}), 
                           Member.new({ :cpp_type =>'NameMap', :name =>'nm', :pass_by_ref =>true,:access => Codegen::Access::RW}), 
                          ],
                          :public_typedefs => [
                                               'typedef std::vector<std::string> NameList',
                                               'typedef std::map<std::string, std::string> NameMap',
                                              ],
                          :ctor_default => true,
                          :name => 'sample',
                          :api_decl => 'SIMPLE_API',
#                          :comparable => true,
                          :streamable => true,
#                          :op_equal => true,
                          #:boost_andable => true,
#                          :boost_totally_ordered => true,
                          #:boost_orable => true,
                          :brief => 'Test performance of implementation of operator<',
                          :impl_includes => ['fcs/utils/streamers/containers.hpp'],
                          :disable_windows_warnings => ['4251'],
                          :include_unit_test => true,
                          :property_tree => true,
                          :header_includes => [ 'map', 'set', 'boost/lambda/lambda.hpp',  
                                                'boost/serialization/vector.hpp', 'boost/serialization/map.hpp' ],
                        }
                        ),

           CppClass.new({ 
                          :members => [
                                       Member.new({ :cpp_type =>'std::string', :name =>'s1', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'std::string', :name =>'s2', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'int', :name =>'s3', :pass_by_ref =>true, :init => 5, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'std::string', :name =>'s4', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'double', :name =>'d5', :pass_by_ref =>true, :init =>3.145, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'NameList', :name =>'nameList', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       #                                      Member.new({ :cpp_type =>'NameListList', :name =>'nameListList', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'NameMap', :name =>'nameMap', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'NameMapMap', :name =>'nameMapMap', :pass_by_ref =>true, :access => Codegen::Access::RW, :member_ctor => true}), 
#                                       Member.new({ :cpp_type =>'sample', :name =>'embeddedSample', :pass_by_ref =>true, :access => Codegen::Access::RW, :ifdef_identifier => 'FOOBAR'}), 
                                       Member.new({ :cpp_type =>'PathPtr', :name =>'aPath', :pass_by_ref =>true, :stream_deref => true, :access => Codegen::Access::RW, :serializable => false, :hide_impl => true }), 
                                       Member.new({ :cpp_type =>'PathPtr', :name =>'anotherPath', :pass_by_ref =>true, :stream_deref_with_address => true, :access => Codegen::Access::RW, :serializable => false}), 
                                      ],
                          :name => 'goo',
                          :ctor_default => true,
                          :streamable => true,
                          :streamers_included => true,
                          :property_tree => true,
                          :forward_class_decls => ['boost::regex', 'my_special_class' ],
                          :public_typedefs => [ 
                                               'typedef boost::function<int (void)> BoostFunctorGoo', 
                                               typedef_shared_ptr_of('boost::filesystem::path', 'PathPtr'),
                                               'typedef std::vector<std::string> NameList',
                                               'typedef std::vector<NameList> NameListList',
                                               'typedef std::map<std::string, std::string> NameMap',
                                               'typedef std::map<std::string, NameMap> NameMapMap',
                                              ],
                          :comparable => true,
                          :op_equal => true,
                          #:boost_andable => true,
                          :boost_totally_ordered => true,
                          #:boost_orable => true,
                          #                        :ctor_default => true,
                          :brief => 'Test performance of implementation of operator<',
                          :global_header_section => true,
                          :header_includes => [
                                               'sample.hpp',
                                               'map', 'set', 
                                               'boost/lambda/lambda.hpp' ],
                        }),

           CppClass.new({ 
                          :members => [
                                       Member.new({ :cpp_type =>'std::string', :name =>'s1', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'std::string', :name =>'s2', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'int', :name =>'s3', :pass_by_ref =>true, :init => 5, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'std::string', :name =>'s4', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'double', :name =>'d5', :pass_by_ref =>true, :init =>3.145, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'NameList', :name =>'nameList', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       #                                      Member.new({ :cpp_type =>'NameListList', :name =>'nameListList', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'NameMap', :name =>'nameMap', :pass_by_ref =>true, :access => Codegen::Access::RW}), 
                                       Member.new({ :cpp_type =>'NameMapMap', :name =>'nameMapMap', :pass_by_ref =>true, :access => Codegen::Access::RW, :member_ctor => true}), 
#                                       Member.new({ :cpp_type =>'sample', :name =>'embeddedSample', :pass_by_ref =>true, :access => Codegen::Access::RW, :ifdef_identifier => 'FOOBAR'}), 
                                       Member.new({ :cpp_type =>'PathPtr', :name =>'aPath', :pass_by_ref =>true, :stream_deref => true, :access => Codegen::Access::RW, :serializable => false, :hide_impl => true }), 
                                       Member.new({ :cpp_type =>'PathPtr', :name =>'anotherPath', :pass_by_ref =>true, :stream_deref_with_address => true, :access => Codegen::Access::RW, :serializable => false}), 
                                      ],
                          :name => 'foo',
                          :ctor_default => true,
                          :pimpl_ptr => true,
#                          :streamable => true,
#                          :streamers_included => true,
                          :forward_class_decls => ['boost::regex', 'my_special_class' ],
                          :public_typedefs => [ 
                                               'typedef boost::function<int (void)> BoostFunctorGoo', 
                                               typedef_shared_ptr_of('boost::filesystem::path', 'PathPtr'),
                                               'typedef std::vector<std::string> NameList',
                                               'typedef std::vector<NameList> NameListList',
                                               'typedef std::map<std::string, std::string> NameMap',
                                               'typedef std::map<std::string, NameMap> NameMapMap',
                                              ],
                          :brief => 'Test performance of implementation of operator<',
                          :global_header_section => true,
                          :header_includes => [
                                               'sample.hpp',
                                               'map', 'set', 
                                               'boost/lambda/lambda.hpp' ],
                        })

          ]


lib = Codegen::Cpp::Library.new({ 
                                  :name =>'sample',
                                  :api_decl => 'SAMPLE_API',
                                  :jam_requirements => [ 
                                                        '/site-config//boost_serialization',
                                                        '$(PANTHEIOS_LIBS)'
                                                       ],
                                  :namespace => ['fcs', 'examples',],
                                  :classes => classes,
                                })

