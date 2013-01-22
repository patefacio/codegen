require 'pathname'

module Flare

  class FlateTypes
    BZ2                = '.bz2'
    GZ                 = '.gz'
#    RPM                = '.rpm'
    SEVEN_ZIP          = '.7z'
    TAR                = '.tar'
    TAR_BZ2            = '.tar.bz2'
    TAR_GZ             = '.tgz'
    TAR_LZMA           = '.tar.lzma'
    TAR_SEVEN_ZIP      = '.tar.7z'
    ZIP                = '.zip'
  end

  FlateExtensions = { 
    FlateTypes::BZ2 =>           '.bz2',
    FlateTypes::GZ =>            '.gz',
    FlateTypes::SEVEN_ZIP =>     '.7z',
    FlateTypes::TAR =>           '.tar',
    FlateTypes::TAR_BZ2 =>       '.tar.bz2', 
    FlateTypes::TAR_GZ =>        '.tgz', 
    FlateTypes::TAR_LZMA =>      '.tar.lzma', 
    FlateTypes::TAR_SEVEN_ZIP => '.tar.7z',    
    FlateTypes::ZIP =>           '.zip',
  }

  def determine_flate_type(path)
    path = Pathname.new(path) if path.class != Pathname
    if path.basename.to_s =~  /^(.+?)((?:\.zip|\.7z|\.tar|\.gz|\.tgz|\.bz2|\.lzma)+)$/
      name, type = $1, $2
      case type
      when '.zip'
        type = FlateTypes::ZIP
      when '.tar'
        type = FlateTypes::TAR
      when '.gz'
        type = FlateTypes::GZ
      when '.tar.7z'
        type = FlateTypes::TAR_SEVEN_ZIP
      when '.7z'
        type = FlateTypes::SEVEN_ZIP
      when '.tar.gz'
        type = FlateTypes::TAR_GZ
      when '.tgz'
        type = FlateTypes::TAR_GZ
      when '.bz2'
        type = FlateTypes::BZ2
      when '.tar.bz2'
        type = FlateTypes::TAR_BZ2
      when '.tar.lzma'
        type = FlateTypes::TAR_LZMA
      else
        warn "Flate type (#{type}) not supported!"
      end
      [name, type]
    end
  end

  def get_supported_flate_type(path)
    result = determine_flate_type(path)
    raise "Path is not a supported compression type: #{path}" if result.nil?
  end

end
