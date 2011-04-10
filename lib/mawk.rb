require 'mawkc'

module AWK
  def awk(script)
    m = MAWK.new(script)

    self.each_line do |line|
      line.concat("\n") if line !~ /\n\Z/
      m << line
    end

    m.run_main
    m.uninitialize
  end
end

class IO
  include AWK
end

class String
  include AWK
end
