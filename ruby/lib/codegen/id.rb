################################################################################
# For providing consistency in naming, these utilities are designed to enforce
# certain conventions.
################################################################################
require 'codegen/attributes'

module Codegen
  
  ##############################################################################
  # An Id is a named entity, often used for naming variables and such.  The
  # initialization of the instance requires snake case words. In return for
  # inputing snake case, various formats of the word can be retrieved.
  ##############################################################################
  class Id
    extend Attributes

    attribute_defaults({ 
      :id => nil, :plural => nil,
    })

    attr_reader :cap, :camel, :cap_camel, :camels, \
    :cap_camels, :hyphenated, :words

    def id_words
      id.split('_')
    end

    def to_s
      id
    end

    def to_sym
      id.to_sym
    end

    def emacs
      hyphenated
    end

    def title
      words.map {|w| w.capitalize }.join(' ')
    end

    def titles
      plural.split('_').map {|w| w.capitalize }.join(' ')
    end

    def squish
      words.join('')
    end

    def squishes
      plural.split('_').join('')
    end

    def hyphenated
      words.join('-')
    end

    def hyphenateds
      plural.split('_').join('-')
    end

    def plural_words
      plural.split('_')
    end

    def abbrev
      words.map{ |s| s[0] }.join()
    end

    def shorten
      words.size >= 3 and abbrev or id
    end


    def initialize(opts={ })
      raise ArgumentError, "Id <id> '#{opts[:id]}' must be snake case" if /[A-Z]/.match(opts[:id])
      raise ArgumentError, "Id <plural> '#{opts[:plural]}' must be snake case" if /[A-Z]/.match(opts[:plural])
      set_attributes(opts)
      @id = id.to_s
      @plural = plural.to_s if not plural.nil?
      if @plural.nil?
        @plural = "#{@id}s"
      end
      @words = id_words
      @cap = id.upcase
      @cap_camel = (@camel = ([words[0]] + [words[1..-1].map {|w| w.capitalize }]).join()).clone
      @cap_camel[0] = camel[0].swapcase
      words = plural_words
      @cap_camels = @camels = ([words[0]] + [words[1..-1].map {|w| w.capitalize }]).join()
      @cap_camels[0] = camels[0].swapcase
    end
  end

  def make_id(s)
    if [Symbol, String].include? s.class
      return Id.new(:id => s)
    end
    if s.class != Id
      raise ArgumentError, "make_id requires symbol, string or Id: #{s.class} NOT ACCEPTED"
    end
    return s
  end
  module_function :make_id

  def infer_id(s)
    s = s.gsub(/([A-Z])/, '_\\1').sub(/^_/,'').downcase if s.class == String
    return make_id(s)
  end

  def Id.make_abbrev_map(ids)
    ordered = ids.sort_by {|i| i.id }
    result = ordered.inject({}) {|h, i| h[i] = ''; h }

    def invert(m)
      result = {}
      m.each_pair do |k,v|
        if result.has_key? v
          result[v] << k
        else
          result[v] = [k]
        end
      end
      result
    end


    def add_letters(result, step, max_words = 2)
      result.each_pair do |k,v|
        id = make_id(k)
        words = id.id_words[0..(max_words-1)]
        result[k] = words.inject('') {|abbrev, w| abbrev + w[0..step] } 
      end
      result
    end

    step = 0
    result.merge!(add_letters(result, step))
    while true
      collisions = { }
      inverted = invert(result)
      inverted.each_pair do |abbrev, ids|
        next if ids.size == 1
        ids.each do |id|
          collisions[id] = nil
        end
      end
      break if collisions.empty?
      result.merge!(add_letters(collisions, step))
      step = step + 1
    end
    result
  end

end

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
