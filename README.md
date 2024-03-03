# input-fix

## Features

- Unofficial port of [partymod-thaw](https://github.com/PARTYMANX/partymod-thaw)
- Replaced input system entirely with new, modern system using the SDL2 library
- Improved window handling allowing for custom resolutions and configurable windowing
- Replaced configuration files with new INI-based system (see partymod.ini)
- Option to disable intro movies
- Blur fix
- Selectable languages (English, French, German)
- Selectable button fonts (Keyboard, PS2, XBOX, or NGC)
- Increased memory which supports stability and level merging
- THUG Airdrift

## TODO

- Adjustable Spin delay `skater_xbox_shoulder_turn_no_rotate_time`
- Toggle for walk spin `flip_skater_if_180_off`
- Invert camera stick
- Adjustable Drop down key(s)
- Change GameSpy to OpenSpy

## Known issues:

- Separate menu controls needed
- Text inside the main menu wheel is not adjusted for the widescreen aspect ratios
- No keybinds for online quick chat and taunts

## Visual Studio Project

- Built with Visual Studio 2022
- Toolset v143
- Build configuration: Release, x86 (win32)
- Extract the SDL zip to: \input-fix\partymod-thug2\SDL2-2.28.3 
