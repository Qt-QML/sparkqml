import QtQuick 2.4
import Spark.actions 1.0

BrowserActionBarForm {
    closeButton.onClicked: {
        AppActions.pop();
    }
}
