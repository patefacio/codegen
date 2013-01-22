require 'pathname'
class Place
  @@jam_place = { }
  @@place['boost_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/boost_1_52_0/include'
  @@jam_place['boost_include'.upcase + '_PATH'] = @@place['boost_include']
  @@place['boost_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/boost_1_52_0/lib'
  @@jam_place['boost_lib'.upcase + '_PATH'] = @@place['boost_lib']
  @@place['mongo_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/mongo_2_0_1/include'
  @@jam_place['mongo_include'.upcase + '_PATH'] = @@place['mongo_include']
  @@place['mongo_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/mongo_2_0_1/lib64'
  @@jam_place['mongo_lib'.upcase + '_PATH'] = @@place['mongo_lib']
  @@place['zlib_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/zlib_1_2_7/include'
  @@jam_place['zlib_include'.upcase + '_PATH'] = @@place['zlib_include']
  @@place['zlib_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/zlib_1_2_7/lib'
  @@jam_place['zlib_lib'.upcase + '_PATH'] = @@place['zlib_lib']
  @@place['bzip2_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/bzip2_1_0_6/include'
  @@jam_place['bzip2_include'.upcase + '_PATH'] = @@place['bzip2_include']
  @@place['bzip2_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/bzip2_1_0_6/lib'
  @@jam_place['bzip2_lib'.upcase + '_PATH'] = @@place['bzip2_lib']
  @@place['szip_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/szip_2_1/include'
  @@jam_place['szip_include'.upcase + '_PATH'] = @@place['szip_include']
  @@place['szip_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/szip_2_1/lib'
  @@jam_place['szip_lib'.upcase + '_PATH'] = @@place['szip_lib']
  @@place['hdf5_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/hdf5_1_8_10/include'
  @@jam_place['hdf5_include'.upcase + '_PATH'] = @@place['hdf5_include']
  @@place['hdf5_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/hdf5_1_8_10/lib'
  @@jam_place['hdf5_lib'.upcase + '_PATH'] = @@place['hdf5_lib']
  @@place['hdf5_debug_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/hdf5_debug_1_8_10_dbg/include'
  @@jam_place['hdf5_debug_include'.upcase + '_PATH'] = @@place['hdf5_debug_include']
  @@place['hdf5_debug_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/hdf5_debug_1_8_10_dbg/lib'
  @@jam_place['hdf5_debug_lib'.upcase + '_PATH'] = @@place['hdf5_debug_lib']
  @@place['qt_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/qt_5_0_0/include'
  @@jam_place['qt_include'.upcase + '_PATH'] = @@place['qt_include']
  @@place['qt_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/qt_5_0_0/lib'
  @@jam_place['qt_lib'.upcase + '_PATH'] = @@place['qt_lib']
  @@place['pantheios_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/pantheios_1_0_1/include'
  @@jam_place['pantheios_include'.upcase + '_PATH'] = @@place['pantheios_include']
  @@place['pantheios_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/pantheios_1_0_1/lib'
  @@jam_place['pantheios_lib'.upcase + '_PATH'] = @@place['pantheios_lib']
  @@place['tbb_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/tbb_4_0/include'
  @@jam_place['tbb_include'.upcase + '_PATH'] = @@place['tbb_include']
  @@place['tbb_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/tbb_4_0/lib'
  @@jam_place['tbb_lib'.upcase + '_PATH'] = @@place['tbb_lib']
  @@place['fastformat_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/fastformat_0_7_1/include'
  @@jam_place['fastformat_include'.upcase + '_PATH'] = @@place['fastformat_include']
  @@place['fastformat_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/fastformat_0_7_1/lib'
  @@jam_place['fastformat_lib'.upcase + '_PATH'] = @@place['fastformat_lib']
  @@place['quantlib_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/quantlib_1_1/include'
  @@jam_place['quantlib_include'.upcase + '_PATH'] = @@place['quantlib_include']
  @@place['quantlib_lib'] = Pathname.new '/home/dbdavidson/open_source/admin/install/quantlib_1_1/lib'
  @@jam_place['quantlib_lib'.upcase + '_PATH'] = @@place['quantlib_lib']
  @@place['stlsoft_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/stlsoft_1_9_109/include'
  @@jam_place['stlsoft_include'.upcase + '_PATH'] = @@place['stlsoft_include']
  @@place['otl_include'] = Pathname.new '/home/dbdavidson/open_source/admin/install/otl/include'
  @@jam_place['otl_include'.upcase + '_PATH'] = @@place['otl_include']
  @@place['stlsoft'] = @@place['stlsoft_include'].parent
  @@place['boost-build_install'] = @@place['boost_include'].parent
  ENV['STLSOFT'] = @@place['stlsoft'].to_s
end
