TEMPLATE = subdirs
SUBDIRS = extplane-server \
    clients/extplane-client-qt \
    extplane-transformer
CONFIG += ordered

QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

include(common.pri)

defined(XPLANE_SDK_PATH, var) {
message("Building X-Plane plugin with SDK in $$XPLANE_SDK_PATH")
SUBDIRS += extplane-plugin
} else {
warning("No X-Plane SDK found in ../XPlaneSDK or ~/SDK - not building X-Plane plugin")
}

OTHER_FILES += README.md clients/extplane-client-qt/README
