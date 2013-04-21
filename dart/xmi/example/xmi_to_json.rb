#!env ruby
require 'json'
require 'active_support/core_ext'
require 'net/http'
require 'ostruct'
require 'optparse'
require 'pathname'

options = OpenStruct.new
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: xmi_to_json -f XMI_FILE"
  opts.separator ""
  opts.separator "Specific options:"
  opts.on('-h', '--help', 'Display this screen' ) do
    raise "Help Follows"
  end
  opts.on('-f', '--file XMI_FILE', "XMI file to convert" ) do |f|
    options.file = f
  end
end
begin
  optparse.parse!
  raise OptionParser::MissingArgument if options.file.nil?
  input = Pathname.new options.file
  output = input.realdirpath.parent + (input.basename.to_s + '.json')
  s = File.open(input, "rb").read
  j = JSON.parse(Hash.from_xml(s).to_json)
  out = File.open(output, "w")
  out.write(JSON.pretty_generate(j))
  out.close
rescue Exception => e
  puts e.message
  puts optparse
  raise e
end


