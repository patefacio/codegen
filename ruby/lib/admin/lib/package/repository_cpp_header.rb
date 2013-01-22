require 'package'

module Package
  include Package::Identifier
  CppHeaderPackages = []

  CppHeaderPackages <<
    CppHeaderLib.new(:name => :stlsoft,
                     :version => '1.9.109',
                     :install_path => Place['install'] + 'stlsoft-#{version}',
                     :source_uri => 'http://downloads.sourceforge.net/project/stlsoft/STLSoft%201.9/#{version}/stlsoft-#{version}-hdrs.zip?r=http%3A%2F%2Fwww.stlsoft.org%2F&ts=1319905426&use_mirror=voxel')

  CppHeaderPackages <<
    CppHeaderLib.new(:name => :otl,
                     :install_path => Place['install'] + 'otlv4' + 'include',
                     :source_uri => 'http://otl.sourceforge.net/otlv4_h.zip')


end
