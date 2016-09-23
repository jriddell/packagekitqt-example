set( packagekitqtexample_SRCS
    main.cpp
    packagekitqtexample.cpp
)

ki18n_wrap_ui(packagekitqtexample_SRCS packagekitqtexample.ui)

add_executable( packagekitqtexample ${packagekitqtexample_SRCS} )

target_link_libraries( packagekitqtexample
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
)

target_link_libraries(packagekitqtexample PK::packagekitqt5)
target_link_libraries(packagekitqtexample AppstreamQt)
target_include_directories(packagekitqtexample PUBLIC ${Qt5DBus_INCLUDE_DIRS})
install( TARGETS packagekitqtexample ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS packagekitqtexample.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
