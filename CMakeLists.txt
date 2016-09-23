project(packagekitqtexample)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets DBus)

find_package(KF5 REQUIRED COMPONENTS
    CoreAddons
    I18n
)

find_package(PackageKitQt5 0.9.5)
set_package_properties(PackageKitQt5
    PROPERTIES DESCRIPTION "Software Manager integration"
    TYPE OPTIONAL
    PURPOSE "Needed to automatically install the samba package."
)

find_package(AppstreamQt 0.9.8)
set_package_properties(AppstreamQt
    PROPERTIES DESCRIPTION "StuffStream"
    TYPE OPTIONAL
    PURPOSE "Needed to find the stuff."
)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_subdirectory(src)
add_subdirectory(icons)
