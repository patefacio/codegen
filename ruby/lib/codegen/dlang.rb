#######################################################################
# Support for code generation of D
#######################################################################
require 'codegen'

module Codegen::Dlang

  ALIGN = :align
  
  class ProtectionAttribute
    PRIVATE = :private
    PACKAGE = :package
    PROTECTED = :protected
    PUBLIC = :public
    EXPORT = :export
  end

  def scope(tag, txt)
    txt = Codegen.single_indent + txt.split("\n").join("\n#{Codegen.single_indent}")
    "#{tag} {\n#{txt}\n}\n"
  end

  def _set_field(o, field_name, field_value)
    case o
    when Hash
      o[field_name] = field_value
    when Array
      o.each do |item|
        _set_field(item, field_name, field_value)
      end
    else
    end
    o
  end    


  def _add_d_attribute(o, attr)
    case o
    when Hash
      if o[:d_attributes].nil?
        o[:d_attributes] = [attr]
      else
        o[:d_attributes] << ProtectionAttribute::PUBLIC
      end
    when Array
      o.each do |item|
        _add_d_attribute(item, attr)
      end
    else
    end
    o
  end

  def Private(o) _set_field(o, :protection, :private); end
  def Package(o) _set_field(o, :protection, :package); end
  def Protected(o) _set_field(o, :protection, :protected); end
  def Export(o) _set_field(o, :protection, :export); end
  def Public(o) _set_field(o, :protection, :public); end

  def Align(o, align = 1) o[:alignment] = align; o; end
  def Deprecated(o) _set_field(o, :deprecated, true); o; end
  def Static(o) _set_field(o, :static, true); o; end
  def Final(o) _set_field(o, :final, true); o; end
  def Abstract(o) _set_field(o, :abstract, true); o; end
  def Const(o) _set_field(o, :const, true); o; end

  def Ia(o) _set_field(o, :access, :ia); o; end
  def Ro(o) _set_field(o, :access, :ro); o; end
  def Rw(o) _set_field(o, :access, :rw); o; end


  @@system_imports = 
    %w{  
     algorithm array ascii base64 bigint bitmanip compiler
     complex concurrency container conv cpuid cstream csv ctype datetime
     demangle encoding exception file format functional getopt json math
     mathspecial md5 metastrings mmfile numeric outbuffer parallelism path perf
     process random range regex regexp signals socket socketstream stdint
     stdiobase stdio stream string syserror system traits typecons typetuple
     uni uri utf uuid variant xml zip zlib
    }.inject({ }) {|c,i| c[i.to_sym] = "std.#{i}"; c }

  @@basic_types = %w{ void bool byte ubyte short ushort int uint long ulong
  cent ucent float double real ifloat idouble ireal cfloat cdouble creal char
  wchar dchar string }.map{ |t| t.to_sym }

  def type_name(t)
    return t if @@basic_types.include? t
    return make_id(t).cap_camel if t.class == Symbol
    return t if t.class == String
    raise ArgumentError, "type_name requires symbol or string"
  end

  def basic_types()
    return @@basic_types.dup
  end

  def basic_type(t)
    return t if @@basic_types.include? t
  end

  def clean_imports(imports)
    imports.each_index do |i|
      case imports[i]
      when Symbol
        imports[i] = @@system_imports[imports[i]]
      end
    end
    imports = imports.sort
  end

end

if __FILE__ == $0
  include Codegen::Dlang
  Public({ })
end
    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
