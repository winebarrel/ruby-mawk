Gem::Specification.new do |spec|
  spec.name              = 'mawk'
  spec.version           = '0.1.1'
  spec.summary           = 'Ruby binding for libmawk'
  spec.require_paths     = %w(lib)
  spec.files             = Dir.glob('ext/*.{c,h}') + %w(ext/extconf.rb README lib/mawk.rb)
  spec.author            = 'winebarrel'
  spec.email             = 'sgwr_dts@yahoo.co.jp'
  spec.homepage          = 'https://bitbucket.org/winebarrel/ruby-mawk'
  spec.extensions        = 'ext/extconf.rb'
  spec.has_rdoc          = false
end
