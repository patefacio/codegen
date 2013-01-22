#######################################################################
# Support for code generation of c++
#######################################################################
require 'yaml'
require 'place'
require 'codegen/cpp/cpp_member'
require 'codegen/cpp/cpp_enumeration'
require 'codegen/cpp/cpp_class'
require 'codegen/cpp/cpp_lib'
require 'codegen/cpp/cpp_app'
require 'codegen/cpp/cpp_option_class'
require 'codegen/cpp/cpp_file'
require 'codegen/cpp/cpp_hdf5_log_group'
require 'codegen'
require 'set'
require 'pp'

module Codegen
  module Cpp

    FUNDAMENTAL_TYPE_RE = Regexp::compile(%q(^(?:
char|
signed\s+char|
unsigned\s+char|
short\s+int|
int|
long\s+int|
unsigned\s+short\s+int|
unsigned\s+int|
unsigned\s+long\s+int|
wchar_t|
bool|
float|
double|
long\s+double
)$), 
                                          Regexp::EXTENDED)
    Codegen::Cpp::SystemHeaders = 
      Set.new([

               'algorithm', 'bitset', 'complex', 'deque', 'exception',
               'fstream', 'functional', 'hash_map', 'hash_set', 'iomanip',
               'ios', 'iosfwd', 'iostream', 'iso646.h', 'istream', 'iterator',
               'limits', 'list', 'locale', 'map', 'memory', 'new', 'numeric',
               'ostream', 'queue', 'set', 'sstream', 'stack', 'stdexcept',
               'streambuf', 'string', 'strstream', 'utility', 'valarray',
               'vector', 'cassert', 'cctype', 'cerrno', 'cfloat', 'ciso646',
               'climits', 'clocale', 'cmath', 'csetjmp', 'csignal', 'cstdarg',
               'cstddef', 'cstdio', 'cstdlib', 'cstring', 'ctime', 'cwchar',
               'cwctype', 'cstdint'

              ] +
              
              # C Posix
              [

               'aio.h', 'arpa/inet.h', 'assert.h', 'complex.h', 'cpio.h',
               'ctype.h', 'dirent.h', 'dlfcn.h', 'errno.h', 'fcntl.h',
               'fenv.h', 'float.h', 'fmtmsg.h', 'fnmatch.h', 'ftw.h',
               'glob.h', 'grp.h', 'iconv.h', 'inttypes.h', 'iso646.h',
               'langinfo.h', 'libgen.h', 'limits.h', 'locale.h', 'math.h',
               'monetary.h', 'mqueue.h', 'ndbm.h', 'net/if.h', 'netdb.h',
               'netinet/in.h', 'netinet/tcp.h', 'nl_types.h', 'poll.h',
               'pthread.h', 'pwd.h', 'regex.h', 'sched.h', 'search.h',
               'semaphore.h', 'setjmp.h', 'signal.h', 'spawn.h', 'stdarg.h',
               'stdbool.h', 'stddef.h', 'stdint.h', 'stdio.h', 'stdlib.h',
               'string.h', 'strings.h', 'stropts.h', 'sys/ipc.h',
               'sys/mman.h', 'sys/msg.h', 'sys/resource.h', 'sys/select.h',
               'sys/sem.h', 'sys/shm.h', 'sys/socket.h', 'sys/stat.h',
               'sys/statvfs.h', 'sys/time.h', 'sys/times.h', 'sys/types.h',
               'sys/uio.h', 'sys/un.h', 'sys/utsname.h', 'sys/wait.h',
               'syslog.h', 'tar.h', 'termios.h', 'tgmath.h', 'time.h',
               'trace.h', 'ulimit.h', 'unistd.h', 'utime.h', 'utmpx.h',
               'wchar.h', 'wctype.h', 'wordexp.h',

              ] +
              
              [
               'sys/prctl.h',
              ]

              ) 

    Codegen::Cpp::QtGuiHeaders = Set.new(%w{ QAbstractButton
      QAbstractFontEngine QAbstractGraphicsShapeItem QAbstractItemDelegate
      QAbstractItemView QAbstractPageSetupDialog QAbstractPrintDialog
      QAbstractProxyModel QAbstractScrollArea QAbstractSlider QAbstractSpinBox
      QAbstractTextDocumentLayout QAbstractUndoItem QAccessible
      QAccessible2Interface QAccessibleActionInterface QAccessibleApplication
      QAccessibleBridge QAccessibleBridgeFactoryInterface
      QAccessibleBridgePlugin QAccessibleEditableTextInterface
      QAccessibleEvent QAccessibleFactoryInterface QAccessibleImageInterface
      QAccessibleInterface QAccessibleInterfaceEx QAccessibleObject
      QAccessibleObjectEx QAccessiblePlugin
      QAccessibleSimpleEditableTextInterface QAccessibleTableInterface
      QAccessibleTextInterface QAccessibleValueInterface QAccessibleWidget
      QAccessibleWidgetEx QAction QActionEvent QActionGroup QApplication
      QAuthDevice QBitmap QBoxLayout QBrush QBrushData QButtonGroup
      QCalendarWidget QCDEStyle QCheckBox QCleanlooksStyle QClipboard
      QClipboardEvent QCloseEvent QColor QColorDialog QColorGroup QColormap
      QColumnView QComboBox QCommandLinkButton QCommonStyle QCompleter
      QConicalGradient QContextMenuEvent QCopChannel QCursor QCursorShape
      QDataWidgetMapper QDateEdit QDateTimeEdit QDecoration QDecorationAction
      QDecorationDefault QDecorationFactory QDecorationFactoryInterface
      QDecorationPlugin QDecorationStyled QDecorationWindows QDesktopServices
      QDesktopWidget QDial QDialog QDialogButtonBox QDirectPainter QDirModel
      QDockWidget QDoubleSpinBox QDoubleValidator QDrag QDragEnterEvent
      QDragLeaveEvent QDragMoveEvent QDragResponseEvent QDropEvent
      QErrorMessage QFileDialog QFileIconProvider QFileOpenEvent
      QFileSystemModel QFocusEvent QFocusFrame QFont QFontComboBox
      QFontDatabase QFontDialog QFontEngineFactoryInterface QFontEngineInfo
      QFontEnginePlugin QFontInfo QFontMetrics QFontMetricsF QFormLayout
      QFrame QGenericMatrix QGesture QGestureEvent QGestureRecognizer
      QGradient QGradientStop QGradientStops QGraphicsAnchor
      QGraphicsAnchorLayout QGraphicsBlurEffect QGraphicsColorizeEffect
      QGraphicsDropShadowEffect QGraphicsEffect QGraphicsEllipseItem
      QGraphicsGridLayout QGraphicsItem QGraphicsItemAnimation
      QGraphicsItemGroup QGraphicsLayout QGraphicsLayoutItem
      QGraphicsLinearLayout QGraphicsLineItem QGraphicsObject
      QGraphicsOpacityEffect QGraphicsPathItem QGraphicsPixmapItem
      QGraphicsPolygonItem QGraphicsProxyWidget QGraphicsRectItem
      QGraphicsRotation QGraphicsScale QGraphicsScene
      QGraphicsSceneContextMenuEvent QGraphicsSceneDragDropEvent
      QGraphicsSceneEvent QGraphicsSceneHelpEvent QGraphicsSceneHoverEvent
      QGraphicsSceneMouseEvent QGraphicsSceneMoveEvent
      QGraphicsSceneResizeEvent QGraphicsSceneWheelEvent
      QGraphicsSimpleTextItem QGraphicsTextItem QGraphicsTransform
      QGraphicsView QGraphicsWidget QGridLayout QGroupBox QGtkStyle
      QHBoxLayout QHeaderView QHelpEvent QHideEvent QHoverEvent QIcon
      QIconDragEvent QIconEngine QIconEngineFactoryInterface
      QIconEngineFactoryInterfaceV2 QIconEnginePlugin QIconEnginePluginV2
      QIconEngineV2 QIconSet QImage QImageIOHandler
      QImageIOHandlerFactoryInterface QImageIOPlugin QImageReader
      QImageTextKeyLang QImageWriter QInputContext QInputContextFactory
      QInputContextFactoryInterface QInputContextPlugin QInputDialog
      QInputEvent QInputMethodEvent QIntValidator QItemDelegate
      QItemEditorCreator QItemEditorCreatorBase QItemEditorFactory
      QItemSelection QItemSelectionModel QItemSelectionRange QKbdDriverFactory
      QKbdDriverPlugin QKeyEvent QKeyEventTransition QKeySequence QLabel
      QLayout QLayoutItem QLayoutIterator QLCDNumber QLinearGradient QLineEdit
      QLinuxFbScreen QLinuxFb_Shared QListView QListWidget QListWidgetItem
      QMacCocoaViewContainer QMacMime QMacNativeWidget QMacPasteboardMime
      QMacStyle QMainWindow QMatrix QMatrix2x2 QMatrix2x3 QMatrix2x4
      QMatrix3x2 QMatrix3x3 QMatrix3x4 QMatrix4x2 QMatrix4x3 QMatrix4x4
      QMdiArea QMdiSubWindow QMenu QMenuBar QMenubarUpdatedEvent QMenuItem
      QMessageBox QMimeSource QMotifStyle QMouseDriverFactory
      QMouseDriverPlugin QMouseEvent QMouseEventTransition QMoveEvent QMovie
      QPageSetupDialog QPaintDevice QPaintEngine QPaintEngineState QPainter
      QPainterPath QPainterPathPrivate QPainterPathStroker QPaintEvent
      QPalette QPanGesture QPen QPicture QPictureFormatInterface
      QPictureFormatPlugin QPictureIO QPinchGesture QPixmap QPixmapCache
      QPlainTextDocumentLayout QPlainTextEdit QPlastiqueStyle QPolygon
      QPolygonF QPoolEntry QPrintDialog QPrintEngine QPrinter QPrinterInfo
      QPrintPreviewDialog QPrintPreviewWidget QProgressBar QProgressDialog
      QProxyModel QProxyScreen QProxyScreenCursor QProxyStyle QPushButton
      QQnxMouseHandler QQnxScreen QQuaternion QRadialGradient QRadioButton
      QRegExpValidator QRegion QResizeEvent QRgb QRubberBand
      QS60MainApplication QS60MainApplicationBase QS60MainAppUi
      QS60MainAppUiBase QS60MainDocument QS60MainDocumentBase QS60StubAknAppUi
      QS60StubAknAppUiBase QS60StubMAknTouchPaneObserver
      QS60StubMEikStatusPaneObserver QS60Style QScreen QScreenCursor
      QScreenDriverFactory QScreenDriverFactoryInterface QScreenDriverPlugin
      QScrollArea QScrollBar QSessionManager QShortcut QShortcutEvent
      QShowEvent QSizeGrip QSizePolicy QSlider QSortFilterProxyModel QSound
      QSpacerItem QSpinBox QSplashScreen QSplitter QSplitterHandle
      QStackedLayout QStackedWidget QStandardItem QStandardItemEditorCreator
      QStandardItemModel QStaticText QStatusBar QStatusTipEvent
      QStringListModel QStyle QStyledItemDelegate QStyleFactory
      QStyleFactoryInterface QStyleHintReturn QStyleHintReturnMask
      QStyleHintReturnVariant QStyleOption QStyleOptionButton
      QStyleOptionComboBox QStyleOptionComplex QStyleOptionDockWidget
      QStyleOptionDockWidgetV2 QStyleOptionFocusRect QStyleOptionFrame
      QStyleOptionFrameV2 QStyleOptionFrameV3 QStyleOptionGraphicsItem
      QStyleOptionGroupBox QStyleOptionHeader QStyleOptionMenuItem
      QStyleOptionProgressBar QStyleOptionProgressBarV2
      QStyleOptionQ3DockWindow QStyleOptionQ3ListView
      QStyleOptionQ3ListViewItem QStyleOptionRubberBand QStyleOptionSizeGrip
      QStyleOptionSlider QStyleOptionSpinBox QStyleOptionTab
      QStyleOptionTabBarBase QStyleOptionTabBarBaseV2 QStyleOptionTabV2
      QStyleOptionTabV3 QStyleOptionTabWidgetFrame
      QStyleOptionTabWidgetFrameV2 QStyleOptionTitleBar QStyleOptionToolBar
      QStyleOptionToolBox QStyleOptionToolBoxV2 QStyleOptionToolButton
      QStyleOptionViewItem QStyleOptionViewItemV2 QStyleOptionViewItemV3
      QStyleOptionViewItemV4 QStylePainter QStylePlugin QSwipeGesture
      QSymbianEvent QSyntaxHighlighter QSystemTrayIcon QTabBar QTabletEvent
      QTableView QTableWidget QTableWidgetItem QTableWidgetSelectionRange
      QTabWidget QTapAndHoldGesture QTapGesture QtEvents QTextBlock
      QTextBlockFormat QTextBlockGroup QTextBlockUserData QTextBrowser
      QTextCharFormat QTextCursor QTextDocument QTextDocumentFragment
      QTextDocumentWriter QTextEdit QTextFormat QTextFragment QTextFrame
      QTextFrameFormat QTextFrameLayoutData QTextImageFormat QTextInlineObject
      QTextItem QTextLayout QTextLength QTextLine QTextList QTextListFormat
      QTextObject QTextObjectInterface QTextOption QTextTable QTextTableCell
      QTextTableCellFormat QTextTableFormat QtGui QTileRules QTimeEdit
      QToolBar QToolBarChangeEvent QToolBox QToolButton QToolTip QTouchEvent
      QTransform QTransformedScreen QTransportAuth QTreeView QTreeWidget
      QTreeWidgetItem QTreeWidgetItemIterator QUndoCommand QUndoGroup
      QUndoStack QUndoView QUnixPrintWidget QUpdateLaterEvent QValidator
      QVBoxLayout QVector2D QVector3D QVector4D QVFbHeader QVFbKeyboardHandler
      QVFbKeyData QVFbMouseHandler QVFbScreen QWhatsThis
      QWhatsThisClickedEvent QWheelEvent QWidget QWidgetAction QWidgetData
      QWidgetItem QWidgetItemV2 QWidgetList QWidgetMapper QWidgetSet
      QWindowsCEStyle QWindowsMime QWindowsMobileStyle QWindowsStyle
      QWindowStateChangeEvent QWindowsVistaStyle QWindowsXPStyle QWizard
      QWizardPage QWMatrix QWorkspace QWSCalibratedMouseHandler QWSClient
      QWSCursor QWSCursorMap QWSDisplay QWSEmbedWidget QWSEvent QWSInputMethod
      QWSInternalWindowInfo QWSKeyboardHandler
      QWSKeyboardHandlerFactoryInterface QWSLinuxInputKeyboardHandler
      QWSLinuxInputMouseHandler QWSLinuxTPMouseHandler QWSManager
      QWSMouseHandler QWSMouseHandlerFactoryInterface QWSPcMouseHandler
      QWSPointerCalibrationData QWSPropertyManager QWSProtocolItem
      QWSQnxKeyboardHandler QWSScreenSaver QWSServer QWSServerSocket QWSSocket
      QWSSoundClient QWSSoundServer QWSSoundServerSocket QWSTslibMouseHandler
      QWSTtyKeyboardHandler QWSUmKeyboardHandler QWSWindow QWSWindowInfo
      QX11EmbedContainer QX11EmbedWidget QX11Info

    })

    def clean_name_as_type(name)
      return name.gsub(/std::/, '').gsub(/::/, '').gsub(/_t_/, '_').downcase.capitalize
    end
    
    def get_typedef_names_from_arg(data)
      return [ data[-1][:name], data[-1][:full_name] ] if ((data.class == Array) and (data[-1].class == Hash))
      return data
    end

    def typedef_date()
      'typedef boost::gregorian::date Date_t'
    end

    def typedef_path()
      'typedef boost::filesystem::path Path_t'
    end

    def typedef_timestamp()
      'typedef boost::posix_time::ptime Timestamp_t'
    end

    def typedef_time_duration()
      'typedef boost::posix_time::time_duration Time_duration_t'
    end

    def typedef_shared_ptr_of(type, name = nil)
      name = clean_name_as_type("#{type}_ptr") if !name
      if use_boost_shared_ptr
        "typedef boost::shared_ptr< #{type} > #{name}"
      else
        "typedef std::shared_ptr< #{type} > #{name}"
      end
    end

    def typedef_pair_of(type_1, *rest)
      type_2 = rest.shift if !rest.empty? and rest[0].class != Hash
      type_2 = type_1 if !type_2
      name, full_name = get_typedef_names_from_arg(rest)      
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_pair_t" : 
                                                        ((type_1 == type_2)? "#{type_1}_pair_t" : "#{type_1}_#{type_2}_pair_t}"))
      "typedef std::pair< #{type_1}, #{type_2} > #{name}"
    end

    def typedef_thread_specific_ptr_of(type, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_ptr" : "#{type}_ptr")
      "typedef boost::thread_specific_ptr< #{type} > #{name}"
    end

    def typedef_vector_of(type, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_list_t" : "#{type}_list_t")
      return "typedef std::vector< #{type} > #{name}"
    end

    def typedef_list_of(type, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_list_t" : "#{type}_list_t")
      return "typedef std::list< #{type} > #{name}"
    end

    def typedef_mmap_of(key, value, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_mmap_t" : "#{key}_to_#{value}_mmap_t")
      return "typedef std::multimap< #{key}, #{value} > #{name}"
    end

    def typedef_map_of(key, value, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_map_t" : "#{key}_to_#{value}_map_t")
      return "typedef std::map< #{key}, #{value} > #{name}"
    end

    def typedef_set_of(type, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_set_t" : "#{type}_set_t")
      return "typedef std::set< #{type} > #{name}"
    end

    def typedef_ptr_vector_of(type, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_ptr_list_t" : "#{type}_ptr_list_t")
      return "typedef boost::ptr_vector< #{type} > #{name}"
    end

    def Cpp.typedef_ptr_map_of(key, value, *rest)
      name, full_name = get_typedef_names_from_arg(rest)
      name = full_name ? full_name : clean_name_as_type(name ? "#{name}_ptr_map_t" : "#{key}_to_#{value}_ptr_map_t")
      return "typedef boost::ptr_map< #{key}, #{value} > #{name}"
    end
    
    def Cpp.clean_accessors(text, is_struct = false)
      data = text.gsub(/((?:public|protected|private):)\s+((?:public|protected|private):)/m) { "#{$2}" }
      data = data.split(/((?:public|private|protected):)/)
      moribund = []
      prev = nil
      data.each_index do |i|
        if data[i] =~ /^((?:public|private|protected):)$/
          current = $1 
          if prev == current
            moribund << i 
          end
          prev = current
        elsif data[i] =~ /^\s+$/
          #moribund << i-1
          #moribund << i
        end
      end
      moribund.reverse.each do |i|
        data[i-1].chomp!
        data.delete_at i
      end
      if is_struct
        if data[1] == 'public:'
          data.delete_at 1 
          data[0].chomp!
        end
      else
        if data[1] == 'private:'
          data.delete_at 1 
          data[0].chomp!
        end
      end
      data.join('')
    end

    def Cpp.clean_typedef(td)
      return td.sub(/<(\S)/, '< \1').sub(/(\S)>/, '\1 >')
    end

    def Cpp.template_types_from_template_decls(template_decls)
      template_decls.map { |td| $1 if td =~ /\s*[\w:]+\s+(\w+)/ }
    end

    def Cpp.header_path(namespace)
      Place.place['cpp']+namespace.join('/')          
    end

    def Cpp.impl_path(namespace)
      Place.place['libs']+namespace.join('/')+'src'
    end

    def Cpp.clean_ordered(a)
      result = []
      data = Set.new()
      a.each do |i|
        result.push i if not data.include? i
        data.add i
      end
      return result
    end

    def Cpp.make_c_string_literal txt, indent = ''
      if txt.empty?
        return '""'
      else
        lines = txt.split(/\n/)
        last_index = lines.length - 1
        result = []
        lines.each_index do |i|
          result << "#{indent}\"" + lines[i] + ((i == last_index)? '"' : "\\n\"")
        end
        result.join("\n")
      end
    end

    def Cpp.resolve_include_lambdas(includes)
      includes.collect {|i| (i.class == Proc)? i.call() : i }
    end

    def Cpp.clean_includes(includes)
      includes = resolve_include_lambdas includes
      include_set = Set.new()
      result = []
      boost = []
      pantheios = []
      other_system = []
      latter = []
      current = ""
      includes.each do |i|
        if i.to_s =~ /([<"]?)(.*)[>"]?/
          system_header = $1 == '<'
          guts = $2
          if guts =~ /^\s*$/
            print "SKIPPING EMPTY INCLUDE #{includes.join(%Q{, })}\n"
            next
          end
          if Codegen::Cpp::SystemHeaders.include? guts
            current = "#include <#{guts}>" 
            latter.push current if not include_set.include? current
          elsif guts =~ /boost\//
            current = "#include <#{guts}>" 
            boost.push current if not boost.include? current
          elsif guts =~ /pantheios\//
            current = "#include <#{guts}>" 
            pantheios.push current if not pantheios.include? current
          elsif system_header
            current = "#include #{i}"
            other_system.push current if not other_system.include? current
          else
            current = "#include \"#{i}\"" 
            result.push current if not include_set.include? current
          end
        else
          print "SKIPPING (#{i}) #{i =~ /([<\"]?)(.*)[>\"]?/}\n"
        end
        
        include_set.add current
      end
      all_includes = (((pantheios.length>0)? pantheios : []) +
                      result + 
                      ((other_system.length>0)? other_system : []) +
                      ((boost.length>0)? boost : []) +
                      ((latter.length>0)? latter : []))
      all_includes.delete_if {|incl| incl =~ /#include <iosfwd>/ } if all_includes.include? '#include <iostream>'
      includes_win_warnings = { 
        'boost/program_options.hpp' => [ 4275, 4251 ],
      }

      includes_win_warnings.each do | include, warnings |
        all_includes.map! do |i|               
          if i =~ /#{include}/
              i = "#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : #{warnings.join(' ')})
#endif
#{i}
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
" 
          else
            i = i
          end
        end
      end
      all_includes.join("\n")
    end
  end
end

################################################################################
# License: <a href="http://www.boost.org/LICENSE_1_0.txt">Boost License 1.0</a>.
################################################################################
