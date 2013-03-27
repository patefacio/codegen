require 'plusauri/place'
require 'codegen/dart/cg'
require 'logger'
require 'pp'
include Codegen::Dart


lib = Lib.new({
                :id => 'ctor_examples',
                :root_path => Place['dart'],
                :namespace => ['examples',],
                :generated_main => ['
  var p = new Class1(1,"foo", new DateTime(1999, 12, 31));
  print("${p.m1} ${p.m2} ${p.m3}");

  p = new Class1Named(m1:1,m2:"foo",m3:new DateTime(1999, 12, 31));
  print("${p.m1} ${p.m2} ${p.m3}");

  p = new Class1Opt(2, "goo");
  print("${p.m1} ${p.m2} ${p.m3}");

'],
                :parts =>
                [
                 { 
                   :id => 'part_1',
                   :classes =>
                   [
                    { 
                      :id => 'class_1',
                      :public => true,
                      :custom_ctors => 'default',
                      :ctor => true,
                      :members => 
                      [ 
                       { :id => 'm_1', :type => 'int', :access => :ro,  },
                       { :id => 'm_2', :type => 'String', :access => :ro, :init => '"xyz"' },
                       { :id => 'm_3', :type => 'DateTime', :access => :ro, :init => 'new DateTime(1929,10,29)'  },
                      ]
                    },

                    { 
                      :id => 'class_1_named',
                      :public => true,
                      :custom_ctors => 'default',
                      :ctor_named => true,
                      :members => 
                      [ 
                       { :id => 'm_1', :type => 'int', :access => :ro,  },
                       { :id => 'm_2', :type => 'String', :access => :ro, :init => '"xyz"' },
                       { :id => 'm_3', :type => 'DateTime', :access => :ro, :init => 'new DateTime(1929,10,29)'  },
                      ]
                    },

                    { 
                      :id => 'class_1_opt',
                      :custom_ctors => 'default',
                      :public => true,
                      :ctor_opt => true,
                      :members => 
                      [ 
                       { :id => 'm_1', :type => 'int', :access => :ro,  },
                       { :id => 'm_2', :type => 'String', :access => :ro, :init => '"xyz"' },
                       { :id => 'm_3', :type => 'DateTime', :access => :ro, :init => 'new DateTime(1929,10,29)'  },
                      ]
                    },
                   ]
                 },
                ]
              })


if __FILE__ == $0
  include Codegen::Dart
  require 'yaml'
  lib.generate
  #puts lib.to_yaml
else
  lib.generate
end
