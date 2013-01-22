################################################################################
# Copyright (c) by Daniel Davidson                                    
################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
require 'codegen/database/database'
require 'odbc_ini'

DB = OdbcIni::ParsedEntries.instance.get_dsn_connection('code_metrics')
DB.loggers << Logger.new(STDOUT)
DB['DESCRIBE code_locations'].each do |row|
  puts row
end

database = 
  Codegen::Database.new({ 
                          :database_connection => DB,
                          :use_vector_on => [ :code_packages ],
                          :support_options => { 
                            :supports_delete_all => true, 
                            :supports_insert_ignore => [ :code_packages, :code_locations ],
                          },
                          :intrusive => true,
                          :selects =>
                          [
                           { 
                             :query_business_name => 'rusage_delta_by_package_label',
                             :descr => 'Query that pulls rusage by code package or code location name',
                             :substitute_order => [ :package_name, :label ],
                             :select_statement =>
                             %Q{ 
select 
  CP.name as package_name,
  CL.label,
  CL.file_name,
  RD.created,
  CL.line_number,
  CL.git_commit,
  RD.!/id|created$/
from 
  code_locations as CL, 
  code_packages as CP,
  rusage_delta as RD
where  
  CL.label like {presubstitute(:cpp_type => 'std::string', :name => 'label')} and
  CP.name like {substitute('CP.name', :package_name)} and
  RD.code_locations_id = CL.id and
  CL.code_packages_id = CP.id
order by
  CP.name,
  CL.label,
  RD.created
}
                           },
                           { 
                             :query_business_name => 'code_tick_timings_by_package_label',
                             :descr => 'Pulls clock ticks by code package name or code location name',
                             :substitute_order => [ :package_name, :label ],
                             #:add_limit => true,
                             :select_statement =>
                             %Q{ 
select 
  CP.name as package_name,
  CL.label,
  CL.file_name,
  CTT.created,
  CL.line_number,
  CL.git_commit,
  CTT.!/id|created$/
from 
  code_locations as CL, 
  code_packages as CP,
  code_tick_timings as CTT
where  
  CL.label like {substitute('CL.label', :label)} and
  CP.name like {substitute('CP.name', :package_name)} and
  CTT.code_locations_id = CL.id and
  CL.code_packages_id = CP.id
order by
  CP.name,
  CL.label,
  CTT.created
}
                           },
                           
                          ],
                          :additional_classes =>
                          [
                           CppClass.new({ 
                                          :name => 'Block_tracker_orm',
                                          :brief => 'Used to time code blocks',
                                          :descr => 

"Supports both rusage timing and basic high res timing.",

                                          :public_header_section => true,
                                          :global_header_section => true,
                                          :public_typedefs =>
                                          [
                                           'typedef std::pair< char const*, char const* > Name_and_description_t',
                                          ],
                                          :ctor_member_init_inline_method => true,
                                          :include_unit_test => true,
                                          :header_includes => 
                                          [
                                           'pantheios/pantheios.hpp',
                                           'pantheios/inserters/integer.hpp',
                                           'pantheios/inserters/real.hpp',
                                           'fcs/utils/performance/cycle.h',
                                           'fcs/orm/code_metrics/table/rusage_delta.hpp',
                                           'fcs/orm/code_metrics/table/code_tick_timings.hpp',
                                           'fcs/orm/code_metrics/table/code_packages.hpp',
                                           'fcs/orm/code_metrics/table/code_locations.hpp',
                                           'fcs/linux_specific/cpu_info.hpp',
                                           'fcs/utils/version_control_commit.hpp',
                                           'boost/date_time/posix_time/posix_time.hpp',
                                           'boost/lexical_cast.hpp',
                                           'boost/math/special_functions/round.hpp',
                                           'sys/time.h',
                                           'sys/resource.h',
                                          ],
                                          :members =>
                                          [
                                           {
                                             :name => 'package_name_and_description',
                                             :brief => 'Pair of fields tying this to a package',
                                             :cpp_type => 'Name_and_description_t',
                                             :pass_by_ref => true,
                                             :member_ctor => true,
                                           },
                                           {
                                             :name => 'label',
                                             :brief => 'Label for this code block being timed',
                                             :cpp_type => 'char const*',
                                             :member_ctor => true,
                                           },
                                           {
                                             :name => 'file_name',
                                             :cpp_type => 'char const*',
                                             :member_ctor => true,
                                           },
                                           {
                                             :name => 'line_number',
                                             :cpp_type => 'size_t',
                                             :member_ctor => true,
                                           },
                                           { 
                                             :cpp_type => 'Timing_type',
                                             :name => 'timing_type',
                                             :init => 'TIMING_TICKS',
                                             :member_ctor_defaulted => true,
                                           },
                                           { 
                                             :cpp_type => 'int',
                                             :name => 'processor',
                                             :brief => 'If maps to processor number pins the thread to that processor first',
                                             :init => '-1',
                                             :member_ctor_defaulted => true,
                                           },
                                           { 
                                             :cpp_type => 'rusage',
                                             :name => 'initial_rusage',
                                           },
                                           { 
                                             :cpp_type => 'ticks',
                                             :name => 'initial_ticks',
                                             :init => '0',
                                           },
                                           { 
                                             :cpp_type => 'double',
                                             :name => 'cpu_mhz',
                                             :init => '0',
                                           },
                                           {
                                             :name => 'code_locations_id',
                                             :cpp_type => 'int',
                                           },
                                          ],
                                          :enums => [ 
                                                     {
                                                       :name => 'Timing_type', 
                                                       :brief => 'Which type of timing to track and store in the database',
                                                       :inline => true,
                                                       :values => [
                                                                   'TIMING_TICKS',
                                                                   'TIMING_RUSAGE',
                                                                  ],
                                                     }, 
                                                    ],
                                        }),

                          ],
                        }
                        )

