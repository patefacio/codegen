def commify(s)
  s.reverse.scan(/(?:\d*\.)?\d{1,3}-?/).join(',').reverse
end

def uncommify_float(s)
  Float(s.strip.gsub(/,/,''))
end

def uncommify_int(s)
  Integer(s.strip.gsub(/,/,''))
end
