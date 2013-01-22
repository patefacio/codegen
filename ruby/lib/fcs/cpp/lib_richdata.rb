require 'tenjin'
require 'codegen/cpp'
require 'codegen'
include Codegen::Cpp

api_decl = 'FCS_CODEGEN_COVERAGE_API'
namespace = ['fcs', 'codegen', 'coverage' ]

members = [
           'int', 'double', 'long', 'long double', 'long int', 'long long', 
           'unsigned int', 'unsigned long', 'unsigned long long',
           #'char', 'signed char', 'unsigned char',
          ].map! { 
  |t| Member.new({ :cpp_type =>t, 
                   :name =>t.gsub(' ','_')+'_m', 
                   :init =>"std::numeric_limits<#{t}>::max()",
                   :access => Codegen::Access::RW}) } +

  # ['std::string'].map! { 
  #   |t| Member.new({ :cpp_type =>t, 
  #                                  :name =>t.gsub('::','_')+'_m', 
  #                                  :pass_by_ref =>true,
  #                                  :access => Codegen::Access::RW}) } +

  [
   'boost::int16_t', 'boost::int32_t', 'boost::int64_t',
   'boost::uint16_t', 'boost::uint32_t', 'boost::uint64_t',

  ].map! { 
  |t| Member.new({ :cpp_type =>t, 
                   :name =>t.gsub('::','_')+'_m', 
                   :init =>"std::numeric_limits<#{t}>::max()",
                   :access => Codegen::Access::RW}) }

members << Member.new(
                      { 
                        :cpp_type => 'fcs::utils::Fixed_size_char_array< 32 >',
                        :name => 'sample_string',
                        :pass_by_ref => true,
                        :access => Codegen::Access::RW
                      }
                      )



check_sizes = %Q{ 
static void check_sizes() {
   size_t actual(sizeof(All_types));
   size_t tally(0);
<?rb @members.each do |m| ?>
   tally += sizeof(\#{m.cpp_type});
<?rb end ?>
   std::cout << "Total:" << actual << " versus tally: " << tally << std::endl;
}

}

template = Tenjin::Template.new
template.script = template.convert(check_sizes)
check_sizes = template.render({ :members => members })


classes = [

           { 
             #:signaller_of => [ ['Something_good'], ['Something_good', nil, 'really_fast_good'], 
             #['Something_bad', 'Something_bad*'] ],
             #:observer_of => [ 'Goo', 'Foo'],
             #:observer_of_inline => [ 'GooInl', 'FooInl'],
             :include_unit_test => true,
             :members => members,            
             #:typedef_ptr => true,
             :ctor_default => true,
             :public_header_section => true,
             :streamable_inline => true,
             :additions_public_header => check_sizes,
             :name => 'All_types',
             :ctor_member_init_method => false,
             #:disable_windows_warnings => ['4251'],
             :api_decl => api_decl,
             :brief => 'Has all types',
             :header_includes => [ 'limits' ],
             :impl_includes => [ 'sstream' ],
             :enums => [ ],
             :hdf5_log_support => true,
             :hdf5_log_groups => { 
               'g1' => ['int_m', 'boost_int32_t_m'],
               'g2' => ['unsigned_int_m', 'boost_uint64_t_m', 'double_m'],
             },
           },

          ]


#Codegen::Cpp::CppClass.create_pod('goo', 'this is important', [['int', 'a', 'this is cool'], ['double', 'b',]])

lib = Library.new({ 
                    :name =>'richdata',
                    :header_only => true,
                    :static_only => true,
                    :jam_requirements => [ 
                                           '/site-config//hdf5_hl_cpp',
                                           '/site-config//boost_filesystem',
                                          ],
                    :namespace => namespace,
                    :classes => classes,
                  })

