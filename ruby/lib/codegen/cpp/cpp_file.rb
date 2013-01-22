################################################################################
# Support for creating consistent C++ files
################################################################################
require 'codegen'
require 'tenjin'
require 'place'

module Codegen::Cpp

  class FileDetails
    
    
    attr_accessor :filename, :fully_qualified_name, :brief, :includes, :namespace,
    :include_guard, :pre_namespace_contents, :post_namespace_contents,
    :namespace_contents, :include_pre_namespace_custom,
    :include_post_namespace_custom, :include_namespace_custom, 
    :pre_include_defines, :pre_include_additions, :version_control_commit,
    :pre_namespace_section, :post_namespace_section

    def initialize(data={})
      @filename = (data[:filename].class == Pathname)? data[:filename] : Pathname.new(data[:filename])
      @brief = data[:brief]
      @includes = (data[:includes] or [])
      @namespace = (data[:namespace] or [])
      if !data[:fully_qualified_name]
        @fully_qualified_name = @namespace.join('::')+'::'+filename.to_s.sub(/#{filename.extname}/, "") 
      else
        @fully_qualified_name = data[:fully_qualified_name]
      end
      @include_guard = data[:include_guard]
      @namespace_contents = (data[:namespace_contents] or "")
      @pre_namespace_contents = (data[:pre_namespace_contents] or "")
      @post_namespace_contents = (data[:post_namespace_contents] or "")
      @pre_namespace_section = data[:pre_namespace_section]
      @post_namespace_section = data[:post_namespace_section]
      @include_namespace_custom = (data[:include_namespace_custom] or "")
      @include_pre_namespace_custom = (data[:include_pre_namespace_custom] or "")
      @include_post_namespace_custom = (data[:include_post_namespace_custom] or "")
      @version_control_commit = data[:version_control_commit] 
      @pre_include_defines = (data[:pre_include_defines] or [])
      @pre_include_additions = (data[:pre_include_additions] or [])
      @pre_namespace_additions = (data[:pre_namespace_additions] or [])
    end

    def generate()
      engine = Tenjin::Engine.new()      
      context = {:file_details => self }
      output = engine.render("#{Place.place()['rb_codegen_tmpl']}/cpp_file.tmpl", context)      
    end

  end

end

if $0 == __FILE__
  t = Codegen::Cpp::FileDetails.new(
                                    { 
                                      'filename' => 'goo.cpp',
                                      'brief' => 'This is cool',
                                      'includes' => [ 'map', 'iostream', 'boost/filesystem.hpp'],
                                      'namespace' => ['foo', 'bar'],
                                      'namespace_contents' => "this is the contents",
                                      'pre_namespace_contents' => "Put this before the namespace",
                                      'post_namespace_contents' => "Put this after the namespace",
                                      'include_namespace_custom' => "InNamespace",
                                      'include_pre_namespace_custom' => "PrE",
                                      'include_post_namespace_custom' => "PoSt",
                                      'include_guard' => 'INCL_GUARD',
                                    }
                                    )
  puts t.generate()
end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
