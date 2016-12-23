.pragma library
.import "qrc:///QRedux/qredux.js" as QRedux

function create(provider) {

    return function (store) {

        return function(next) {

            return function (action) {
                try {
                    next(action);
                } catch (e) {
                    console.warn(e.fileName + ":" + e.lineNumber +":" + e);
                }

                switch (action.type) {

                case "quitApp":
                    Qt.quit();
                    break;

                case "startApp":
                    var state = store.getState();
                    QRedux.patch(provider, state);
                    break;
                }
            }
        }
    }
}
