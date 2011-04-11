require 'mawkc'
require 'tempfile'
require 'stringio'

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
      begin
        stdout = $stdout.clone
        $stdout.reopen(file)
        awk(script)
      ensure
        $stdout.reopen(stdout)
      end

      file.rewind

      if block_given?
        file.each_line do |line|
          yield(line.chomp)
        end
      else
        out = file.read
      end
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

class StringIO
  include AWK
end
