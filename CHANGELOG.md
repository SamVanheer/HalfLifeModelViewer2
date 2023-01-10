# Changelog

### V2.11

* Removed unnecessary filesystem path canonicalization (broken on Windows XP)
* Disabled "correct sequence group filenames" feature on Windows XP (does not work due to non-functional filesystem support)
* Disabled depth writing instead of clearing depth buffer bit so the OpenGL window isn't black in Textures mode [#223](https://github.com/SamVanheer/HalfLifeAssetManager/issues/223)
* Recompiled HLMV using Visual Studio 2017 to ensure the program works on Windows XP
* Bundled the latest Visual C++ redistributable (16.7) that works properly on Windows XP so users can run the program properly

Note for Windows XP users: do not install Visual C++ redistributables newer than version 16.7 (file version 14.27.29114.0). Newer redistributables will install a runtime that does not work on Windows XP and will break programs that rely on it. If you have one installed it is recommended to uninstall it.

### V2.10

* Fix bodyparts submodel defaulting to first submodel when changing selected body part instead of using the current submodel for that part
* Add check to prevent models with invalid length value from crashing the program
* Use higher resolution program icon (128x128 instead of 32x32)

### V2.9 Beta 005

* It is no longer an error to have no audio device (speakers, headphones, etc) available

### V2.9 Beta 004

* Made sure the window position & size is restored before setting the maximized property to ensure the window is restored to the correct display when using multiple displays
* Removed Refresh() call in C3DView::MouseEvents to fix animation framerate issue while interacting with the mouse
* Made sequence event info panel panel grow to fit options string
* Fixed incorrect grid column index for event info panel
* Reworked save model feature to use separate dialog
* Reworked SaveStudioModel function to use exceptions for error reporting
* Added option to correct sequence group filenames embedded in main model on save (setting will be remembered)
* Disabled GL_BLEND when drawing background texture to avoid leaking additive rendering state from additive textures
* Ensured correct wxImage constructor overload is selected
* Made image copying code easier to read
* Ensured background images load correctly if image width is not a multiple of 4

### V2.9 Beta 003

* Improved UTF8 filename support to allow loading and saving files that have Unicode characters in their paths, as well as UTF8 character handling in the settings file parser

### V2.9 Beta 002

* Added buttons to the File menu to load the previous and next models in the directory that the current model is located in. These buttons are hotkeyed to the arrow LEFT and RIGHT keys respectively. These actions will wrap around if they reach the beginning or end of the list of files in a directory
* The save model dialog is now initialized to the directory and name of the model that is being saved
* Improved texture file detection (*T.mdl); attempting to load a texture file will now show an error with appropriate information instead of loading the file as an empty model
    * Texture files are identified by their lack of a model name in the studiohdr_t::name field

### V2.9 Beta

#### Project level changes
* HL_Tools project now uses C++17
* Refactored the codebase: all libraries have been merged into HLMV, the SpriteViewer project has been removed
* Updated CMake to use version 3.16, CMakeLists files now use more modern ways to define targets
* Removed CString class (internal change, no change in program behavior)
* Removed app system (previously used to load libraries)
* Removed obsolete types and constants
* Set floating point behavior to strict to ensure floating point operations such as texture color hue alteration works properly

#### General
* The fullscreen window now uses the same 3D view as the normal window enabling it to share state such as individual hitbox or attachment drawing, as well as background textures
* Replaced FMOD with OpenAL Soft, AudioFile for wav file loading & Xiph libogg, libvorbis and libvorbisfile for Ogg Vorbis file loading to comply with FMOD non-commercial license clause 2 "FMOD Studio Engine is not distributed as part of a game engine or tool set;"
* Reworked studio model loading code to use exceptions for error handling. More information is now provided when an error occurs, which should help identify the cause of the problem (which file, which type of error, etc)
* Reworked studio model data storage to use smart pointers, which helps eliminate the possibility of memory leaks if an error occurs during loading
* Fixed off by one bug in sequence file saving code (did not affect saved data, internal issue)
* Fixed texture ids being deleted during texture replacement when they were still being used
* Pressing F5 will reload the model, and reset all viewer state (saving viewer state is too complicated to change in 2.x)
* The window position, size and whether the window is maximized are now saved and restored
* The current camera and control panel are now saved and restored
* Added support for Counter-Strike 9 way blends
* The Shift + Mouse drag translation operation directions now work like they did in Jed's Model Viewer and earlier by default

#### Options dialog
* Implemented option to use a timer for frame logic. The timer based version has a much lower framerate but does not keep the CPU busy
* Added options to invert the horizontal and vertical dragging directions in the 3D view

#### Control panels
* Improved control panel layout to reduce overall size
* Added readonly textboxes containing QC strings for attachments and hitboxes
* Moved the origin and scale controls to a new "Model Data" control panel
    * The Origin preview settings are no longer preview settings; they now modify all root bones allowing you to directly edit the model origin. The input values now map directly to the underlying values, previously X mapped to Z and Z mapped to -X
* Moved the crosshair and guidelines display options to the "Model Display" control panel
* Removed the Fullscreen panel and moved the button to the main control bar next to "Reset Light Vector"

##### Model Display
* Fixed the "Show Normals" option not showing the vertex normals stored in the model
* Added "Show Player Hitbox" option to draw a transparent green box showing the player hitbox (32x32x72)
* Added buttons to center model on origin and to align on ground using the bounding box minimum from either the `idle` sequence if it exists, or the first sequence if there is no `idle` sequence
* Added checkboxes to enable shadow rendering and to fix Z fighting in shadows (shadow quality is poor, just like the engine's shadows)

##### Global flags
* Fixed typo in model flag "Rotate"

##### Textures
* The default name for textures in the "Export Texture" file selection dialog is now the name used by the model for that texture
* Added "Import All Textures" button that will import all textures in a selected directory that match the name of the textures in the model
* Added "Export All Textures" button that will export all textures to a selected directory
* Chrome textures can have an arbitrary size now (still needs engine support, only Sven Co-op supports it at the moment)
* Fixed the mesh list not listing meshes for textures used as alternates only (e.g. scientist hands)
* Added sliders and spinners to set the topcolor and bottomcolor values for textures that use `Dm_Base.bmp` or `Remap` hue alteration. This also includes a read-only textbox containing the integer value used for `pev->colormap`

##### Sequences
* Added "Reset Speed" button to the Sequences panel to reset animation speed to the default setting
* Added "Looping Mode" sequence option
* Added "Restart Sequence" button
* Added Duration sequence info
* Added "Is Looping" sequence info
* Added Activity & Activity Weight sequence info (Activity name is based on SDK values; mods may use custom compilers to produce different activity names, which HLMV cannot access)
* Reworked the animation speed controls to use a spin control which acts as a framerate control, with a maximum of x10 (previous limit was x5). Pressing the up or down buttons, or using the up or down arrow keys will adjust the framerate by 0.1 second, pressing page up or page down adjusts by 1 second
* Added sliders and spinners to control the blending values

##### Attachments
* Attachment origins can now be edited in the Attachments panel. The "vectors" variables have been removed from this panel because the data is obsolete and never used

##### Hitboxes
* Added the Hitboxes control panel; this panel allows you to view individual hitboxes and edit all of their data (which bone it's tied to, the hitgroup, and the bounding box)

### V2.8 Beta

* Properly open the save file dialog for screenshots, provide different extensions and a default filename
* Infer screenshot extension from selected filename. Supported extensions are listed here: https://docs.wxwidgets.org/3.0/classwx_image.html#a9416097f955a828243cba8431e7044d4
* Default file format for screenshots is now PNG
* Use OpenGL viewport size to read & save screenshots
* Set pack alignment to 1 to prevent padding from skewing screenshot result
* Enable scrollbars in control panels when part of the control panel cannot be seen
* Changed checkbox layout for the Model Display panel to avoid creating a vertical scrollbar when there would otherwise be enough space
* Set correct OpenGL options when drawing axes
* Add check to prevent crash if framebuffer creation is not supported
* Rework UV render to texture code to eliminate need to use framebuffer

### V2.7 Beta

* Fixed Test Origins values not applying to correct axes (thanks Marphy Black)
* Fixed viewmodel origin being off by 1 unit in the Z axis (thanks Marphy Black)

### V2.6 Beta

* Added readonly field to display pev->body value

### V2.5 Beta

* Added support for .dol files (PS2 Half-Life model format)

### V2.4 Beta

* Increased far Z value from 4096 to 16777216 (2^24)
* Changed how the view is centered after loading a model to avoid putting the camera very far away from the origin, making the model invisible
* Added a new option to disable rescaling textures to power of 2

### V2.3 Beta

* Increased maximum texture dimensions to 4096

### V2.2 Beta

* Upgraded wxWidgets to 3.1.2
* (For developers only) Reworked wxWidgets library dependency lookup to find the installation automatically. This makes potential cross platform development easier
* Fixed a bug that made it impossible to change skin families if the model has an external textures file (*T.mdl) (Thanks Marphy Black). See https://github.com/SamVanheer/HalfLifeAssetManager/issues/57
* Compiled with Visual Studio 2017 targeting Windows XP with the v141_xp toolset

### V2.1 Beta

* Upgraded FMod sound system from FMod Ex to FMod Studio (Thanks Joël Troch)
* Fixed program icon not being used
* Activated Windows XP support to prevent compatibility issues
* Added global model flags control panel

### V2.0 Beta

Changes compared to Jed's Model Viewer and HLMV 1.25:
* Fixed UI bone controller sliders resetting to default despite the actual controllers being different
* Mirror on ground correctly limits itself to the floor quad by using the stencil buffer
* Fullscreen mode is actually fullscreen now
* Sound playback handles SteamPipe directory structure properly
* Settings are managed through an options dialog, rather than individual menu items
* Merged the Weapon Origin panel with the Sequences panel; Switching between free view and weapon origin is done using a separate radio button group
* Fixed a typo in the model info output: Attatchments -> Attachments
* Moved the "Drawn Polys" text to the main bar
* Added FPS counter
* Added logging to file support
* Converted mathlib to C++, changed to use GLM
* Added checkboxes for mirroring on each axis (helps simulate Counter-Strike weapon model looks)
* Fixed model viewer not shutting down when closed
* CPU usage is more reasonable
* New control panels have been added to provide more data analysis:
    * Attachments panel: Lists all attachments and highlights the currently selected attachment
    * Bones panel: Lists all bones and highlights the currently selected bone
* Coordinate system matches Half-Life's version
* Drag and drop support for models
* Corrected view right vector calculation
* Chrome now uses floating point coordinates for better accuracy (Thanks DoomMusic)
* Chrome calculations are now much closer to those of the engine
* New options have been added:
    * Cull backfaces
    * Adjust First and Third person Field Of View
    * Display surface normals
    * Show world axes, just like Hammer does
    * Multiply pitch with framerate to simulate pitch changes
* Text boxes that represent numbers use widgets that restrict input to numeric characters
* The texture in the Textures panel can be dragged around
* Maximum zoom level in the Textures panel is now x 10
* Increased maximum range for light vector manipulation
* Added button combination to control light vector Z axis: holding down CTRL and SHIFT enables it
* Added front-end for StudioMdl and MdlDec command line tools; this uses a generalized template approach for command line configurations to allow you to easily run the tools with slight differences in input
* The editor for QC files is now the system default for the file type
* Added option to edit sequence events
* Implemented high FPS render loop with frame limiter to prevent stuttering.
* Added fullbright rendering support (Svengine specific).
