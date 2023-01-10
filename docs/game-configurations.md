# Game configurations

The toolchain supports the use of game configurations. These allow the tools to access game and mod specific content.

Since the SteamPipe update, GoldSource games use a new directory structure for addon, hd and downloaded content. This configuration enables the toolchain to access game content in these directories.

## Available options

A single game configuration currently contains the following options:

Option | Description
------ | -----------
Name | Each configuration has a name. This name is unique and identifies the configuration.
Base path | The base path points to the root game directory, for example "common\Half-Life".
Game directory | The game directory. Typically this is "valve".
Mod directory | The mod directory. This can be left empty if the configuration is meant to be used for the game itself.
