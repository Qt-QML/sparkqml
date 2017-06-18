import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import Spark.constants 1.0
import Spark.actions 1.0
import Spark.sys 1.0
import Spark.reducers 1.0
import Qt.labs.settings 1.0
import QtQuick.Dialogs 1.2
import Spark.store 1.0
import QRedux 1.0
import "./Spark/views/mainpanel"
import "./Spark/views"
import "./Spark/views/navigationpanel"

ApplicationWindow {
    id: mainWindow
    visible: provider.mainWindowVisible
    width: 640
    height: 480
    title: provider.mainWindowTitle

    property var store

    Settings {
        id: mainSettings
        property alias x: mainWindow.x
        property alias y: mainWindow.y
        property alias width: mainWindow.width
        property alias height: mainWindow.height
        property string saveFolder: ""
        property string recentFiles: ""
    }

    ActionCreator {
        id: actions
        objectName: "actions"
    }

    StoreProvider {
        id: provider
        objectName: "provider"
    }

    FileDialog {
        id: mainFileDialog
    }

    FileWatcher {
        source: provider.source
        onChanged: {
            actions.reload();
        }
    }

    FocusScope {
        anchors.fill: parent
        ViewStack {
            anchors.fill: parent
        }

        NavigationDrawer {
            id: drawer
            height: mainWindow.height
        }
    }

    Component.onCompleted: {
        function logger(store) {
            return function (next) {
                return function(action) {
                    console.log(action.type);
                    next(action);
                }
            }
        }

        var middlewares = QRedux.applyMiddleware(
//                        logger,
                        LoadingMiddleware.create(),
                        CopyToFileMiddleware.create(mainFileDialog, mainSettings),
                        SystemMiddleware.create(provider),
                        SettingsMiddleware.create(mainSettings),
                        QRedux.signalProxyMiddleware(provider),
                        QRedux.syncMiddleware(provider)
                    );
        mainWindow.store = Redux.createStore(App.reducer, middlewares);
        actions.dispatch = store.dispatch
    }

}
