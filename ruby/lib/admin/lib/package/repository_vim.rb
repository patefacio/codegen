require 'package'

module Package
  include Package::Identifier
  VimPackages = []

  def Package.vim_additions
    [
     ['vimball.tar.gz', 'http://www.vim.org/scripts/download_script.php?src_id=15362' ],
# DOES NOT WORK     ['tselectbuffer.vim', 'http://www.vim.org/scripts/download_script.php?src_id=13974' ],
     ['tlib.vba', 'http://www.vim.org/scripts/download_script.php?src_id=1863' ],
     ['code_complete.vim', 'http://www.vim.org/scripts/download_script.php?src_id=10778'],
     ['NERD_tree.zip', 'http://www.vim.org/scripts/download_script.php?src_id=11834' ],
     ['bufexplorer.zip', 'http://www.vim.org/scripts/download_script.php?src_id=12904' ],
     ['taglist_45.zip', 'http://www.vim.org/scripts/download_script.php?src_id=7701' ],
     ['supertab.vba', 'http://www.vim.org/scripts/download_script.php?src_id=16104' ],
     ['vcscommand-1.99.45.zip', 'http://www.vim.org/scripts/download_script.php?src_id=16705' ],
     ['omnicppcomplete-0.41.zip', 'http://www.vim.org/scripts/download_script.php?src_id=7722' ],
     ['crefvim.zip', 'http://www.vim.org/scripts/download_script.php?src_id=3666' ],
    ].each do |name, url|
      VimPackages << VimScriptIdentity.new(:name => name, :source_uri => url)
    end
  end

  vim_additions
end
