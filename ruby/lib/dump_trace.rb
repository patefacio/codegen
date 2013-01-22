def dump_trace(header="")
  raise "dump_trace: #{header}"
rescue => detail
  puts detail.to_s
  puts "\t" + detail.backtrace[1..-1].join("\n\t")
end

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
