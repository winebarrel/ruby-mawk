require 'mawkc'
require 'tempfile'

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

  def sawk(script)
    file = Tempfile.new("mawk.#{$$}.#{Time.now.strftime '%Y%m%d%H%M%S'}")
    out = nil

    begin
      stdout = $stdout.clone
      $stdout.reopen(file)
      awk(script)
      file.rewind
      out = file.read
    ensure
      $stdout.reopen(stdout)
      file.close
      file.unlink
    end

    return out
  end
end

class IO
  include AWK
end

class String
  include AWK
end
