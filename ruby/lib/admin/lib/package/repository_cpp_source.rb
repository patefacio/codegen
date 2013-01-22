require 'package'

module Package
  include Package::Identifier
  CppSourcePackages = []
  CppSourcePackages << 
    CppSourcePackage.new(:name => :boost,
                         :version => '1.52.0',
                         :source_uri => SourceForge + '/boost/files/boost/#{version}/boost_#{Identifier.normalize_name(version)}.tar.gz/download')

  CppSourcePackages << 
    CppSourcePackage.new(:name => :mongo,
                         :version => '2.0.1',
                         :lib_path_basename => 'lib64',
                         :source_uri => 'http://downloads.mongodb.org/src/mongodb-src-r#{version}.tar.gz')

  CppSourcePackages << 
    CppSourcePackage.new(:name => :zlib,
                          :version => '1.2.7',
                          :source_uri => 'http://zlib.net/zlib-#{version}.tar.gz')

  CppSourcePackages << 
    CppSourcePackage.new(:name => :bzip2,
                          :version => '1.0.6',
                          :source_uri => 'http://www.bzip.org/#{version}/bzip2-#{version}.tar.gz')

  CppSourcePackages << 
    CppSourcePackage.new(:name => :szip,
                          :version => '2.1',
                          :source_uri => 'http://www.hdfgroup.org/ftp/lib-external/szip/#{version}/src/szip-#{version}.tar.gz')

  CppSourcePackages <<
    CppSourcePackage.new(:name => :hdf5,
                          :version => '1.8.10',
                          :source_uri => 'http://www.hdfgroup.org/ftp/HDF5/current/src/hdf5-1.8.10.tar.bz2')

  CppSourcePackages <<
    CppSourcePackage.new(:name => :hdf5_debug,
                          :version => '1.8.10-dbg',
                          :source_uri => 'http://www.hdfgroup.org/ftp/HDF5/current/src/hdf5-1.8.10.tar.bz2')

  CppSourcePackages <<
    CppSourcePackage.new(:name => :qt,
                         :version => '5.0.0',
                         :include_path => Place['install'] + 'Qt5.0.0/5.0.0/gcc_64/include',
                         :lib_path => Place['install'] + 'Qt5.0.0/5.0.0/gcc_64/lib',
                         :source_uri => 'http://releases.qt-project.org/qt5/5.0.0/qt-linux-opensource-5.0.0-x86_64-offline.run')

  CppSourcePackages <<
    CppSourcePackage.new(:name => :pantheios,
                          :version => '1.0.1',
                          :install_path => Place['install'] + 'pantheios-#{version}',
                          :source_uri => 'http://downloads.sourceforge.net/project/pantheios/Pantheios%20%28C%20and%20Cxx%29/1.0.1%20%28beta%20212%29/pantheios-1.0.1-beta212.zip?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fpantheios%2F&ts=1319978635&use_mirror=iweb')

  CppSourcePackages <<
    CppSourcePackage.new(:name => :tbb,
                         :version => '4.0',
                         :source_uri => 'http://threadingbuildingblocks.org/uploads/78/174/#{version}/tbb40_233oss_src.tgz')

  CppSourcePackages <<
    CppSourcePackage.new(:name => :fastformat,
                         :version => '0.7.1',
                         :source_uri => 'http://downloads.sourceforge.net/project/fastformat/fastformat/0.7/0.7.1/0.7.1%20%28alpha%203%29/fastformat-0.7.1-alpha-3.zip?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Ffastformat%2Ffiles%2Ffastformat%2F0.7%2F0.7.1%2F&ts=1321011577&use_mirror=superb-sea2')

    CppSourcePackages <<
    CppSourcePackage.new(:name => :quantlib,
                         :version => '1.1',
                         :source_uri => 'http://downloads.sourceforge.net/project/quantlib/QuantLib/1.1/QuantLib-1.1.tar.gz?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fquantlib%2Ffiles%2F&ts=1321732073&use_mirror=superb-dca2')


end  
