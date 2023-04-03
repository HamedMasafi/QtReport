cmake_minimum_required(VERSION 3.5)

project(QtReport VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    core/dataconnection.cpp
    core/dataconnection.h
    core/datatable.cpp
    core/datatable.h
    core/document.cpp
    core/document.h
    core/event.h
    core/parametere.cpp
    core/parametere.h
    core/report.cpp
    core/reportdatamodel.cpp
    core/reportdatamodel.h
    core/report.h
    core/reportmodel.cpp
    core/reportmodel.h
    core/reportprintsettings.cpp
    core/reportprintsettings.h
    core/variable.cpp
    core/variable.h
    designer/colorpicker.cpp
    designer/colorpicker.h
    designer/databaseinfodialog.cpp
    designer/databaseinfodialog.h
    designer/databaseinfodialog.ui
    designer/databasetablesdialog.cpp
    designer/databasetablesdialog.h
    designer/databasetablesdialog.ui
    designer/datatabledialog.cpp
    designer/datatabledialog.h
    designer/datatabledialog.ui
    designer/designeraboutdialog.cpp
    designer/designeraboutdialog.h
    designer/designeraboutdialog.ui
    designer/designerfactory.cpp
    designer/designerfactory.h
    designer/designerwindow.cpp
    designer/designerwindow.h
    designer/designerwindow.ui
    designer/docpage.cpp
    designer/docpage.h
    designer/documentdesigner.cpp
    designer/documentdesigner.h
    designer/documentview.cpp
    designer/documentview.h
    designer/modeltreeview.cpp
    designer/modeltreeview.h
    designer/newconnectionwizard.cpp
    designer/newconnectionwizard.h
    designer/newconnectionwizard.ui
    designer/parameteredialog.cpp
    designer/parameteredialog.h
    designer/parameteredialog.ui
    designer/querybuilderdialog.cpp
    designer/querybuilderdialog.h
    designer/querybuilderdialog.ui
    designer/ruler.cpp
    designer/ruler.h
    designer/scene.cpp
    designer/scene.h
    designer/seriazbleobject.cpp
    designer/seriazbleobject.h
    designer/treemanager.cpp
    designer/treemanager.h
    designer/undocommands.cpp
    designer/undocommands.h
    designer/widgetresizer.cpp
    designer/widgetresizer_p.h
    propertypages/propertyband.cpp
    propertypages/propertyband.h
    propertypages/propertyband.ui
    propertypages/propertydialog.cpp
    propertypages/propertydialog.h
    propertypages/propertyfilter.cpp
    propertypages/propertyfilter.h
    propertypages/propertyfilter.ui
    propertypages/propertypagealign.cpp
    propertypages/propertypagealign.h
    propertypages/propertypagealign.ui
    propertypages/propertypagebarcode.cpp
    propertypages/propertypagebarcode.h
    propertypages/propertypagebarcode.ui
    propertypages/propertypagebase.cpp
    propertypages/propertypagebase.h
    propertypages/propertypagefont.cpp
    propertypages/propertypagefont.h
    propertypages/propertypagefont.ui
    propertypages/propertypageformat.cpp
    propertypages/propertypageformat.h
    propertypages/propertypageformat.ui
    propertypages/propertypageimage.cpp
    propertypages/propertypageimage.h
    propertypages/propertypageimage.ui
    propertypages/propertypagelinetype.cpp
    propertypages/propertypagelinetype.h
    propertypages/propertypagepage.cpp
    propertypages/propertypagepage.h
    propertypages/propertypagepage.ui
    propertypages/propertypagepos.cpp
    propertypages/propertypagepos.h
    propertypages/propertypagepos.ui
    propertypages/propertypagerectangle.cpp
    propertypages/propertypagerectangle.h
    propertypages/propertypagerectangle.ui
    propertypages/propertypagerichtext.cpp
    propertypages/propertypagerichtext.h
    propertypages/propertypagerichtext.ui
    propertypages/propertypagetext.cpp
    propertypages/propertypagetext.h
    propertypages/propertypagetext.ui
    propertypages/propertypagewidget.cpp
    propertypages/propertypagewidget.h
    propertypages/propertypagewidget.ui
    propertypages/propertysort.cpp
    propertypages/propertysort.h
    propertypages/propertysort.ui
    propertypages/propertytext.cpp
    propertypages/propertytext.h
    propertypages/sectiondataproperties.cpp
    propertypages/sectiondataproperties.h
    propertypages/sectiondataproperties.ui
    propertypages/sectionsproperties.cpp
    propertypages/sectionsproperties.h
    propertypages/sectionsproperties.ui
    qtreportglobal.h
    typehelper.cpp
    typehelper.h
    widgets/band.cpp
    widgets/band.h
    widgets/displaybase.cpp
    widgets/displaybase.h
    widgets/horizontalline.cpp
    widgets/horizontalline.h
    widgets/image.cpp
    widgets/image.h
    widgets/linebase.cpp
    widgets/linebase.h
    widgets/panel.cpp
    widgets/panel.h
    widgets/rectanglebase.cpp
    widgets/rectanglebase.h
    widgets/textbox.cpp
    widgets/textbox.h
    widgets/verticalline.cpp
    widgets/verticalline.h
    widgets/widgetbase.cpp
    widgets/widgetbase.h
    widgets/widget.cpp
    widgets/widget.h
    resources.qrc
)

add_library(QtReport SHARED
    ${PROJECT_SOURCES}
)

target_link_libraries(QtReport PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Xml)
target_include_directories(QtReport PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(QtReport PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtReport
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtReport)
endif()
