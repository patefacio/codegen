################################################################################
# Support for hdf5
################################################################################
require 'codegen'
require 'tenjin'
require 'place'
module Codegen::Cpp

  class Hdf5LogGroup

    attr_accessor :logged_class, :log_groups, :logging_classes, \
    :calculated_fields, :context, :string_members
    CPP_TYPE_TO_HDF5_TYPE = { 
        'int'=> 'H5T_NATIVE_INT',
        'int64_t'=> 'H5T_NATIVE_INT64',
        'std::int64_t'=> 'H5T_NATIVE_INT64',
        'boost::int_fast8_t'=> 'H5T_NATIVE_UCHAR',
        'boost::int_fast16_t'=> 'H5T_NATIVE_SHORT',
        'boost::int_fast32_t'=> 'H5T_NATIVE_INT32',
        'boost::int_fast64_t'=> 'H5T_NATIVE_INT64',

        'boost::uint_fast8_t'=> 'H5T_NATIVE_UCHAR',
        'boost::uint_fast16_t'=> 'H5T_NATIVE_USHORT',
        'boost::uint_fast32_t'=> 'H5T_NATIVE_UINT32',
        'boost::uint_fast64_t'=> 'H5T_NATIVE_UINT64',

        'boost::int_least8_t'=> 'H5T_NATIVE_SCHAR',
        'boost::int_least16_t'=> 'H5T_NATIVE_SHORT',
        'boost::int_least32_t'=> 'H5T_NATIVE_INT32',
        'boost::int_least64_t'=> 'H5T_NATIVE_INT64',

        'boost::uint_least8_t'=> 'H5T_NATIVE_UCHAR',
        'boost::uint_least16_t'=> 'H5T_NATIVE_USHORT',
        'boost::uint_least32_t'=> 'H5T_NATIVE_UINT32',
        'boost::uint_least64_t'=> 'H5T_NATIVE_UINT64',


        'boost::int8_t'=> 'H5T_NATIVE_SCHAR',
        'boost::int16_t'=> 'H5T_NATIVE_SHORT',
        'boost::int32_t'=> 'H5T_NATIVE_INT32',
        'boost::int64_t'=> 'H5T_NATIVE_INT64',
        'boost::uint8_t'=> 'H5T_NATIVE_UCHAR',
        'boost::uint16_t'=> 'H5T_NATIVE_USHORT',
        'boost::uint32_t'=> 'H5T_NATIVE_UINT32',
        'boost::uint64_t'=> 'H5T_NATIVE_UINT64',

        'long'=> 'H5T_NATIVE_LONG',
        'size_t'=> 'H5T_NATIVE_UINT',
        'double'=> 'H5T_NATIVE_DOUBLE',
        'short'=> 'H5T_NATIVE_SHORT',
        'char'=> 'H5T_NATIVE_CHAR',

        'Timestamp_t'=> 'H5T_NATIVE_INT64',
      }

    def h5_type(cpp_type)
      raise "DON'T USE int_(fast|least) as they are not portable" if cpp_type =~ /int_(?:fast|least)/
      result = CPP_TYPE_TO_HDF5_TYPE[cpp_type]
      if !result
        case cpp_type
        when /^\s*long\s+int\s*$/
          result = 'H5T_NATIVE_LONG'
        when /^\s*long\s+double\s*$/
          result = 'H5T_NATIVE_LDOUBLE'
        when /^\s*long\s+long\s*$/
          result = 'H5T_NATIVE_LLONG'
        when /^\s*unsigned\s+int\s*$/
          result = 'H5T_NATIVE_UINT32'
        when /^\s*unsigned\s+long\s*$/
          result = 'H5T_NATIVE_ULONG'
        when /^\s*unsigned\s+long\s+long\s*$/
          result = 'H5T_NATIVE_ULLONG'
        when /^\s*unsigned\s+char\s*$/
          result = 'H5T_NATIVE_UCHAR'
        when /^\s*signed\s+char\s*$/
          result = 'H5T_NATIVE_SCHAR'
        end
      end
      result
    end
    
    def initialize(data={})
      @logged_class = (data['logged_class'] or nil)
      @log_groups = data['log_groups']
      @logging_classes = []
      @log_groups.each do | log_group |
        group_name, group_members = log_group
        group_members = @logged_class.members.select { |m| group_members.include? m.name }
        group_name = "#{@logged_class.name}_#{group_name}" if group_name != @logged_class.name
        data_set_specifier_name = (group_name + '_data_set_specifier').capitalize
        
        additions_public_header = "
static std::string const& data_set_name() { return get_instance()->data_set_name_; }
static hid_t compound_data_type_id() { return get_instance()->compound_data_type_id_; }"

        @engine = Tenjin::Engine.new()
        @context = { 
          :self => self,
          :group_name => group_name, 
          :data_set_specifier_name => data_set_specifier_name,
          :cls => logged_class,
          :group_members => group_members
        }
        additions_private_header = @engine.render("#{Place['rb_codegen_tmpl']}/cpp_log_group_additions_private_header.tmpl", @context)
        #p "LOGGED CLASS AS header include #{@logged_class.header_as_include}"

        string_group_members = group_members.select {|m| m.cpp_type =~ /Fixed_size_char_array|string_\d+/i  }
        @string_members = []
        string_group_members.each do |string_member|
          string_members << Codegen::Cpp::Member.new(
                                                     { 
                                                       :cpp_type => 'hid_t',
                                                       :name => "#{string_member.name}_hid",
                                                       :init => -1,
                                                     }
                                                     )
        end

        dtor_cleanup = %q^ 

~#{@data_set_specifier_name}() {
  // Clean up created/openend h5 handles
<?rb @self.string_members.each do |string_member| ?>
  H5Tclose(#{string_member.variable_name});
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Closed #{@cls.name} string data type #{string_member.name}:", 
                 pantheios::integer(#{string_member.variable_name}));
<?rb end ?>
  H5Tclose(compound_data_type_id_);
  pantheios::log(PANTHEIOS_SEV_DEBUG, "Closed #{@cls.name} compound_data_type:", 
                 pantheios::integer(compound_data_type_id_));
}

^

        template = Tenjin::Template.new
        template.convert(dtor_cleanup)
        dtor_cleanup = template.render( context )

        @logging_classes << 
          Codegen::Cpp::CppClass.new({ 
                                       :name => data_set_specifier_name,
                                       :singleton => true,
                                       :header_only =>true,
                                       :brief => "Defines the location in the file and the data_set for writing",
                                       :namespace => @logged_class.namespace,
                                       :additions_public_header => additions_public_header + dtor_cleanup,
                                       :additions_private_header => additions_private_header,
                                       :members => [
                                                    Codegen::Cpp::Member.new({ :cpp_type =>'std::string', 
                                                                               :name =>'data_set_name',
                                                                               :init =>%Q{"/#{@logged_class.name.downcase}"},
                                                                             }),
                                                    Codegen::Cpp::Member.new({ :cpp_type =>'hid_t', 
                                                                               :name =>'compound_data_type_id',
                                                                               :init => -1,
                                                                             }),
                                                   ] + string_members,
                                       # Often header_as_include has not been determined since class has not
                                       # been scoped with a namespace
                                       :header_includes => [ 
                                                            lambda { @logged_class.header_as_include }, 
                                                            'pantheios/pantheios.hpp',
                                                            'pantheios/inserters/integer.hpp',
                                                            'hdf5.h' 
                                                            ],
                                       :ctor_default => true,
                                       :ctor_default_init_method =>true,
                                       #:ctor_member_init => true,
                                     })
      end

      forward_class_decls = []
      @logging_classes.each do |logging_class|
        forward_class_decls << "class #{logging_class.name};"
      end
      logged_class.additions_namespace_forward_class += forward_class_decls

      @log_groups.each do |group, fields|
        fields.each do |field|
          matches = @logged_class.members.select {|m| m.name == field }
          if matches.length != 1
            throw "FCS: Could not find match for field #{field} in class #{@logged_class.name}: available members\n\t" + 
              @logged_class.members.map {|m| m.name }.join("\n\t")
          end
        end

        # @logging_class.additions_public_header.push("void hdf5_log_#{group}();")
        # @logging_class.additions_impl.push("void #{@logging_class.name}::hdf5_log_#{group}() {}")
      end
    end
  end
end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
