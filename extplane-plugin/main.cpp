#include <cstdlib>
#include <QDebug>
#include <XPLMPlugin.h>
#include <XPLMDataAccess.h>
#include <XPLMProcessing.h>
#include "xplaneplugin.h"
#include "console.h"

XPlanePlugin *globalPlugin = nullptr;

PLUGIN_API float MyFlightLoopCallback(
        float inElapsedSinceLastCall,
        float inElapsedTimeSinceLastFlightLoop,
        int inCounter,
        void *inRefcon) {
    if(globalPlugin)
        return globalPlugin->flightLoop(inElapsedSinceLastCall, inElapsedTimeSinceLastFlightLoop, inCounter, inRefcon);
    return 1;
}

PLUGIN_API int XPluginStart(
        char * outName,
        char * outSig,
        char *outDesc) {
    XPLMRegisterFlightLoopCallback(MyFlightLoopCallback, 0.01f, NULL);
    Q_ASSERT(!globalPlugin);
    globalPlugin = new XPlanePlugin();
    if(globalPlugin) {
        return globalPlugin->pluginStart(outName, outSig, outDesc);
    } else {
        INFO << "Unable to create plugin";
        return 0;
    }
}

PLUGIN_API void XPluginStop() {
    DEBUG;
    XPLMUnregisterFlightLoopCallback(MyFlightLoopCallback, 0);
    globalPlugin->pluginStop();
    //delete globalPlugin;
    //globalPlugin = nullptr;
}

PLUGIN_API void XPluginDisable() {
    DEBUG;
}

PLUGIN_API int XPluginEnable() {
    DEBUG;
    return 1;
}

PLUGIN_API void XPluginReceiveMessage(
        XPLMPluginID inFromWho,
        long inMessage,
        void *inParam) {
    if(globalPlugin)
        globalPlugin->receiveMessage(inFromWho, inMessage, inParam);
}
