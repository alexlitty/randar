ui.component('main-menu-bar', {
    data: function() {
        return {
            items: [
                {
                    text: 'Randar',
                    contextMenu: [
                        [
                            { text: 'Save Project', action: function() {
                                if (this.project.onDisk) {
                                    this.project.save();
                                }

                                ui.nativeDialog.showOpenDialog({
                                    title      : 'Save project to directory',
                                    properties : ['openDirectory']
                                }, function(filepaths) {
                                    if (filepaths && filepaths.length) {
                                        let dir = randar.path(filepaths[0]);
                                        this.project.directory(dir);
                                        this.project.save();
                                    }
                                }.bind(this));
                            }.bind(this)}
                        ],

                        [
                            { text: 'New Project', action: function() {
                                this.project.clear();
                            }.bind(this)},

                            { text: 'Open Project', action: function() {
                                ui.nativeDialog.showOpenDialog({
                                    title      : 'Load project directory',
                                    properties : ['openDirectory']
                                }, function(filepaths) {
                                    if (filepaths && filepaths.length) {
                                        let dir = randar.path(filepaths[0]);
                                        this.project.load(dir);
                                    }
                                }.bind(this));
                            }.bind(this)}
                        ],

                        [
                            { text: 'Toggle DevTools', action: function() {
                                ui.browser.toggleDevTools();
                            }}
                        ],

                        [
                            { text: 'Close', action: function() {
                                ui.exit();
                            }}
                        ]
                    ]
                },

                {
                    text: 'Help',
                    contextMenu: [
                        [
                            { text: 'About Randar', action: this.showAbout }
                        ]
                    ]
                }
            ]
        }
    },

    methods: {
        showAbout: function() {
            //ui.createBrowserWindow('about');
        },

        onClose: function() {
            ui.exit();
        }
    },

    template: `
        <div id="main-menu-bar">
            <menu-bar :items="items" :onClose="onClose"></menu-bar>
        </div>
    `
});
