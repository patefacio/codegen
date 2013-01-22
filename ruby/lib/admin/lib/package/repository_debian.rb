module Package
  include Package::Identifier

  DebianPackages = []
  %w{ autotools-dev build-essential cvs dctrl-tools
    devscripts dict diffstat doxygen doxygen-doc dpkg-dev dput emacs
    emacs-goodies-el emacs23 emacs23-bin-common emacs23-common emacsen-common
    exuberant-ctags fakeroot g++ g++-4.4 gettext giggle git-buildpackage
    git-cola git-core git-doc git-gui gitg gitk gitmagic gitpkg gitweb
    graphviz graphviz-doc intltool-debian irb1.8 lacheck libapt-pkg-perl
    libaudio2 libauthen-sasl-perl libdevel-symdump-perl libdigest-sha1-perl
    liberror-perl libexpat1-dev libgemplugin-ruby libgemplugin-ruby1.8
    libgit-ruby1.8 libgraphviz-dev libgv-ruby libio-pty-perl
    libio-stringy-perl libipc-run-perl libltdl-dev libmaa2 libmngl libmyodbc
    libmysqlclient16 libpalm-perl libparse-debcontrol-perl libphonon4 libpod
    libqt3-mt libqt4-assistant libqt4-dbus libqt4-designer libqt4-help
    libqt4-network libqt4-script libqt4-scripttools libqt4-sql
    libqt4-sql-mysql libqt4-svg libqt4-test libqt4-webkit libqt4-xml
    libqt4-xmlpatterns libqtcore4 libqtgui4 libreadline-ruby1.8 libreadline5
    librecode0 libruby1.8 libstdc++6-4.4-dev libterm-size-perl
    libtest-pod-perl libtool libxdelta2 libxml-writer-perl lintian lmodern
    luatex m4 magit meld mysql-common mysql-query-browser ocaml-base-nox
    p7zip-full patch patchutils pbzip2 perl-doc postfix pristine-tar
    python-all python-all-dev python-dateutil python-dev python-qt4 python-sip
    python2.6-dev python-tables python-numpy python-tables-doc rdoc1.8 recode
    ri ri1.8 ruby ruby-elisp ruby1.8 ruby1.8-dev ruby1.8-elisp rubygems1.8
    subversion tcl tex-common texlive-base texlive-binaries texlive-common
    texlive-doc-base texlive-extra-utils texlive-luatex thunderbird tk vim
    vim-addon-manager vim-gnome vim-gui-common vim-puppet vim-runtime
    vim-scripts vim-vimoutliner vimrails wdiff xdelta xxdiff xz-utils
    zlib1g-devbsd-mailx libglib2.0-dev libSM-dev libxrender-dev
    libfontconfig1-dev libxext-dev libgl1-mesa-swx11-dev libglu-dev unixodbc
  }.each do |deb|
    DebianPackages << DebianIdentity.new(:name => deb)
  end

end
