################################################################################
# Code supporting code generation for various languages.
################################################################################
require 'pathname'
require 'set'
require 'fileutils'

module Codegen

  class Access
    RO = :read_only
    RW = :read_write
    IA = :inaccessible
  end

  def Codegen.cpp_copyright(fname, brief)
    author = ENV['CG_AUTHOR']
    if author.nil?
      author = 'Daniel Davidson'
    end
    license = ENV['CG_LICENSE']
    if license.nil?
      license = 'All Rights Reserved.'
    else
      if license.upcase == 'BOOST'
        license = 'Distributed under the Boost Software License
 * (http://www.boost.org/LICENSE_1_0.txt)'
      end
    end

    """/******************************************************************************
 * #{fname}
 *
 * Copyright (c) #{author}
 *
 * #{license}
 *******************************************************************************/
/*! 
 * \\file #{fname}
 *
 * \\brief #{brief}
 * 
 */"""
  end

  def Codegen.d_copyright
    "Copyright: 2012 by Daniel Davidson
All rights reserved.
"
  end

  def Codegen.open_source_notice
    'License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
'
  end

  @Codegen_indent_len = 2
  @Codegen_current = ''
  NL = "\n"
  TAB = "\t"
  CPP_PROTECT_BLOCK_DELIMITERS = ['// custom','// end']
  BUILD_PROTECT_BLOCK_DELIMITERS = ['# custom','# end']

  def Codegen.single_indent()
    ' '*@Codegen_indent_len
  end

  def Codegen.set_indent_length(n)
    @Codegen_indent_len = n
  end

  def Codegen.indent_length
    @Codegen_indent_len
  end

  def Codegen.indent()
    @Codegen_current += ' '*@Codegen_indent_len
    #puts "INDENTED: " + @Codegen_current.length.to_s
    @Codegen_current
  end

  def Codegen.outdent()
    if @Codegen_current.length > 0
      @Codegen_current = @Codegen_current[0, @Codegen_current.length-@Codegen_indent_len]
    end
    #puts "OUTDENT: " + @Codegen_current.length.to_s
    @Codegen_current
  end

  def Codegen.current_indent() 
    @Codegen_current
  end

  def Codegen.join_text txt
    txt = txt.join("") if txt.class == Array
    return txt
  end

  def Codegen.camel_case_to_binary_signal name
    prior = name
    name.gsub!(/ID/, 'Id')
    name.gsub!(/([A-Z])([A-Z]+)([A-Z])/) {"#{$1}#{$2.downcase}#{$3}"}
    name = name.sub(/([A-Z])/) {$1.downcase}.gsub(/([A-Z]+)/) { "_#{$1.downcase}" }
    warn "Caps remainging #{name}" if (name =~/[A-Z]/)
    return name
  end

  def Codegen.indent_text(txt, additional_levels = 0, rest = { })
    indent_len = (rest[:indent_len] or @Codegen_indent_len)
    trim_blank_lines = rest[:trim_blank_lines]
    txt = join_text txt
    i = @Codegen_current + (' '*additional_levels*indent_len)
    result = [ ]
    txt.split("\n").each do |line|
      line = '' if line =~ /^\s+$/
      result << i if line.length > 0
      result << line << "\n"
    end
    result = result.join().chomp
    result = Codegen.trim_blank_lines(result) if trim_blank_lines
    result
  end

  def Codegen.trim_blank_lines(text)
    text.gsub(/\n[\t ]+\n/ms, "\n\n")
  end

  def Codegen.clean_empty_lines(text)
    text.gsub(/\n{3,}/ms, "\n\n")
  end

  def Codegen.indent_absolute_text(txt, levels = 1, trim_blank_lines = true)
    txt = txt.join("") if txt.class == Array
    i = ' '*levels*@Codegen_indent_len
    result = [ ]
    txt.split("\n").each do |line|
      line = '' if line =~ /^\s+$/
      result << i if line.length > 0
      result << line << "\n"
    end
    result = result.join().chomp
    result = Codegen.trim_blank_lines(result) if trim_blank_lines
    result
  end

  def Codegen.protect_block(name, protected_pair = CPP_PROTECT_BLOCK_DELIMITERS)
    """#{protected_pair[0]} <#{name}>\n#{protected_pair[1]} <#{name}>"""
  end

  def Codegen.align_preprocessor(text)
    text.gsub(/(\n+)[\t ]*#/, '\1#')
  end

  def Codegen.default_to_true_if_not_set(hash, key)
    if hash.has_key? key
      return hash[key]
    else
      true
    end
  end

  def Codegen.clean_templates(text)
    text.gsub(/<(\w)/, '< \1').gsub(/(\w)>/, '\1 >')
  end

  @@merge_statistics =  Hash.new {|h,k| h[k] = Hash.new {|h,k| h[k] = [] } }
  @@files_with_no_custom_code = Set.new

  def Codegen.merge_statistics
    return @@merge_statistics
  end

  def Codegen.files_with_no_custom_code
    return @@files_with_no_custom_code
  end

  @@num_files_written = 0
  def Codegen.num_files_written
    return @@num_files_written
  end

  def Codegen.merge(generated_text, dest_fname, rest = 
                    { 
                      :protected_pair => CPP_PROTECT_BLOCK_DELIMITERS, 
                    })
    protected_pair = (rest[:protected_pair] or CPP_PROTECT_BLOCK_DELIMITERS)
    dest_path = Pathname.new(dest_fname)
    dest_text = ""
    original_text = ""
    if dest_path.file?
      dest_text = dest_path.read
      original_text = dest_text.clone
    end

    ######################################################################
    # Merge the protected blocks
    ######################################################################
    if protected_pair[0].length > 0
      while dest_text =~ /(\n\s*#{protected_pair[0]}[^\n]+)(.*?)(#{protected_pair[1]}[^\n]+)/msu
        dest_text = $'
        front = $1.strip
        guts = $2
        back = $3.strip
        front_clean = front.sub(/^\n\s*/, "\n")
        guts.gsub!(/^\s*\n(\s*)/, "\n\\1")
        guts.gsub!(/\n\s*$/, "\n")
        if guts =~ /\S+/
          #puts "non-empty-block: #{dest_path}\n----------------\n#{guts}\n---------------------\n"
          @@merge_statistics[:non_empty_blocks][dest_path.basename] << back
          repl = "\n#{front_clean}\n#{guts}\n#{back}"
        else
          #puts "Empty-block: #{dest_path}\n----------------\n#{guts}\n---------------------\n"
          @@merge_statistics[:empty_blocks][dest_path.basename] << back
          repl = "\n#{front_clean}\n#{back}"
        end
        repl.gsub!(/\\/, '\\\\\\')
        repl = generated_text.gsub!(/#{front}.*?#{back}/m, repl)
        if false
          if repl and repl.length > 0
            print "SUBST: on #{back} NOT EMPTY: #{repl.length}\n"
          else
            print "FRONT: #{front}\n"
            print "GUTS: #{guts}\n"
            print "BACK: #{back}\n"
            print "ORIG: #{generated_text}"
            print "SUBST: on #{protected_pair[0]} IS EMPTY\n"
          end
        end
      end

      if !@@merge_statistics[:empty_blocks][dest_path.basename].empty? and
          @@merge_statistics[:non_empty_blocks][dest_path.basename].empty? 
        #puts "NO CUSTOM: #{dest_path} #{@@merge_statistics[:empty_blocks][dest_path.basename].length} and #{@@merge_statistics[:non_empty_blocks][dest_path.basename].length}"
        @@files_with_no_custom_code << dest_path
      end
    end

    if original_text.empty? or (original_text != generated_text)
      FileUtils.makedirs(dest_path.parent, :verbose => true) if !File.exists? dest_path.parent
      outfile = File.new(dest_path.to_s, 'w')
      outfile.write(generated_text)
      outfile.close()
      puts "Wrote updates on #{dest_fname} because #{original_text.empty? ? 'original empty' : 'unequal'}"
      if false
        puts "====================="
        puts original_text
        puts "---------------------"
        puts generated_text
        puts "....................."
      end
      @@num_files_written += 1
    else
      puts "No change on #{dest_fname}"
    end
    return generated_text
  end

  def Codegen.macro(txt)
    return "${#{txt}}"
  end

  def Codegen.resolve_lambda(txt)
    return ((txt.class == Proc)? txt.call() : txt)
  end

  def Codegen.hash_from_object_list(items, rest = {})
    if items.class != Array
      raise ArgumentError, "Items must be in Array not #{items.class}"
    end
    rest[:index] = :name if rest[:index].nil?
    rest[:prefix] = 'hash_' if rest[:prefix].nil?
    index = rest[:index]
    result = { }
    items.each do |item|
      item_index = item.instance_variable_get("@#{index}").to_sym
      raise ArgumentError, 
      "Index #{index} does not exist in #{item}" if not item_index
      result[item_index] = item
    end
    result
  end

  def Codegen.block_comment(txt)  
    block_indent = '   '
    txt = block_indent + txt.split("\n").join("\n#{block_indent}")
    result = "/**\n#{txt}\n*/"
  end

  def Codegen.comma_chop(txt)
    result = txt.chomp
    if result[-1]==','
      result[0..-2]
    else
      result
    end
  end

end
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
