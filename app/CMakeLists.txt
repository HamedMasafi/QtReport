set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtReportDesigner
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(QtReportDesigner
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(QtReportDesigner PRIVATE QtReport Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QtReportDesigner PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtReportDesigner
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtReport)
endif()
