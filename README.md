# Note: this tool has been deprecated and is provided for legacy support purposes only

This tool has been superseded by [Half-Life Asset Manager](https://github.com/SamVanheer/HalfLifeAssetManager). You should only use Half-Life Model Viewer 2 if you cannot run Half-Life Asset Manager.

Half-Life Model Viewer is a tool based on HLMV 1.25 and Jed's Model Viewer 1.36 that provides an entirely rebuilt model viewer.
Unlike previous model viewers, this tool uses a cross-platform GUI library, minimizes direct use of platform specific code, and is designed to allow for maximum code reuse.

## Download

See the releases for a download link: https://github.com/SamVanheer/HalfLifeModelViewer2/releases

## Options

Model viewer provides a number of options that allow for customization and enables it to provide a more complete representation of the models it has.

### Game configurations

Game configurations allow model viewer to access game content located in both the main game directory, as well as SteamPipe directories. It also supports mod directories. See [Game configurations](/docs/game-configurations.md) for more information.

## Changelog

See [CHANGELOG.md](/CHANGELOG.md)

## Screenshots

### Modern UI

![Modern UI](/docs/images/DSCiKfz.png)

Half-Life Model Viewer uses wxWidgets, which provides it with a modern, cross-platform UI.

### Bone information

![Bone Information](/docs/images/3PkxvTi.png)

The new Bones control panel displays information about each bone and highlights the currently selected bone.

### Attachment information

![Attachment Information](/docs/images/7EGhUrV.png)

The new Attachments control panel displays information about each attachment and highlights the currently selected attachment.

### Updated Weapon Origin view

![Weapon Origin](/docs/images/CDC4bHA.png)

The Weapon Origin view has been updated. It can now be used at any time, rather than when using a specific control panel. The Field Of View for both Free view and Weapon Origin view can be adjusted separately.

### Mirroring

![Mirroring](/docs/images/atLiTs6.png)

Several improvements have been made to the mirroring of models. The Mirror On Ground option now restricts itself to the ground, rather than being rendered underneath regardless of whether it's visibly inside the ground area.

It is now possible to mirror the model itself on all 3 axes. This allows you to view Counter-Strike weapon models as they appear in-game by mirroring them on the Y axis.

# License

Half-Life Tools

This repository contains code, libraries and executables for Half-life Tools.

This includes code copyrighted by Id Software and Valve Software, included in their SDK. It is included without the intend to infringe on any rights.
All code is redistributed freely.

All of the code in this repository may be used in other projects provided that the author(s) is/are credited.
