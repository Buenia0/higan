Before it can load a game,
higan requires that all the game's data
be stored correctly in the [Game Library].
For [regular games](#regular-games)
this is simple,
but some games require special treatment,
especially those that make use of
unusual hardware.

Regular games
-------------

higan's importing tool, [icarus], can import games
in the most commonly-used formats
for each supported console,
and also those same formats inside `.zip` files
(as long as the `.zip` file contains only one game).
More advanced compression formats
like RAR or 7-zip are not supported.

To import a game,
open the [Systems menu],
choose "Load ROM File ..."
to open a [filesystem browser],
choose the ROM file of the game you want to play,
and it will be imported into the library
and (if possible) start playing.

**Note:**
If you want to import many games,
run icarus directly.
See the [icarus] documentation for details.

To play a game for a particular console from your library,
open the [Systems menu],
then choose the appropriate console menu item.
A filesystem browser will appear
listing all the games in the library
for that particular console.
Select the game you want to play
and click the Open button,
or just double-click the game,
and it will begin playing.

**Note:**
Sometimes
the NTSC and PAL variants of a particular console
behave differently,
or the Japanese and American variants.
When choosing a game from the Game Library,
a drop-down list in the bottom-right of the filesystem browser
allows you to choose which regional variant
of the console higan should emulate.
For most consoles,
higan can reliably guess which variant to use,
and the list defaults to "Auto".

Games with co-processor firmware
--------------------------------

Many games included extra chips inside the game cartridge,
to provide enhanced capabilities of one kind or another.
Sometimes,
those extra chips were separate CPUs
running their own separate firmware,
and for those cases
higan requires a copy of the co-processor firmware
as well as the actual game data.
Unfortunately,
like games themselves,
most co-processor firmware cannot legally be distributed,
so you'll need to
obtain copies of the relevant firmware data
for yourself.

To import a game that requires co-processor firmware,
the easiest approach is to drop the firmware files into
icarus' `Firmware` directory
before importing the game.
The directory should be beside the icarus executable,
or it can be `%LOCALAPPDATA%\icarus\Firmware` (on Windows)
or `~/.local/share/icarus/Firmware/` (on Linux).

If the easy approach doesn't work for a particular game,
it may be because icarus has incorrectly guessed
which firmware that game needs.
To ensure icarus uses specific firmware with a specific game,
you must combine the game data and the firmware into a single file.
For example,
let's say you want to import *Super Bases Loaded 2* for the Super Famicom,
which is stored in the file `sbl2.sfc`
and requires firmware for the DSP1 co-processor
stored in `dsp1.program.rom` and `dsp1.data.rom`.
On Windows,
you can combine them from the command-line like this:

```dos
copy /b sbl2.sfc + dsp1.program.rom + dsp1.data.rom
```

On Linux,
the equivalent command-line syntax is:

```bash
cat dsp1.program.rom dsp1.data.rom >> sbl2.sfc
```

(note the use of `>>` to append rather than `>` to overwrite)

**Note:**
For co-processor chips with multiple firmware files,
always put the "program" file before the "data" file.

Wikipedia [lists which Super Famicom games use which co-processors][wpec],
although not all co-processors require separate firmware.
Once you've figured out which co-processor
(if any)
is used by the game you want to import,
here's the firmware files you'll need:

[wpec]: https://en.wikipedia.org/wiki/List_of_Super_NES_enhancement_chips#List_of_Super_NES_games_that_use_enhancement_chips

<table>
    <thead>
        <tr>
            <th>Co-processor</th>
            <th>Filename</th>
            <th>Size (bytes)</th>
            <th>SHA256</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th scope="row">CX4<br><sup>See Note 1</sup></th>
            <td><code>cx4.data.rom</code></td>
            <td>3072</td>
            <td><code>ae8d4d1961b93421ff00b3caa1d0f0ce7783e749772a3369c36b3dbf0d37ef18</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan=2>DSP1/1A<br><sup>See Note 2</sup></th>
            <td><code>dsp1.data.rom</code></td>
            <td>2048</td>
            <td><code>0b5da6533e55852ee8fc397977ec5576c5b9f1fb2e05656d8f87123a121b076e</code></td>
        </tr>
        <tr>
            <td><code>dsp1.program.rom</code></td>
            <td>6144</td>
            <td><code>269584b347a22953a2989494c850a7c1c027f4ca5add517a60e0c7d8833d0fac</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan=2>DSP1B<br><sup>See Note 3</sup></th>
            <td><code>dsp1b.data.rom</code></td>
            <td>2048</td>
            <td><code>8546cbac530830446bb8a277f6b139d4ad64d650bdbac7e4e150e2f095665049</code></td>
        </tr>
        <tr>
            <td><code>dsp1b.program.rom</code></td>
            <td>6144</td>
            <td><code>2eccb54a8f89374911f7e2db48f1b4cde855655e28103f7bda2982a5b418a187</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan=2>DSP2</th>
            <td><code>dsp2.data.rom</code></td>
            <td>2048</td>
            <td><code>3beef9bffdc1e84c9f99f3301d8bd3e520d2e62909a995320f9faeae8f46ec11</code></td>
        </tr>
        <tr>
            <td><code>dsp2.program.rom</code></td>
            <td>6144</td>
            <td><code>62a2ef8d2d7db638f4ec0fbcebf0e5bf18a75ee95be06e885d9519a10487f0da</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan="2">DSP3</th>
            <td><code>dsp3.data.rom</code></td>
            <td>2048</td>
            <td><code>7fe51796e9c97fee1fa2aab40592b7c78997f67dd00333e69d0f79a12f3cb69f</code></td>
        </tr>
        <tr>
            <td><code>dsp3.program.rom</code></td>
            <td>6144</td>
            <td><code>aea7b622e7c1de346cb15d16afcbedf92b6798507e179f83ed2a4cff40d0e663</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan="2">DSP4</th>
            <td><code>dsp4.data.rom</code></td>
            <td>2048</td>
            <td><code>ef3ffb4256dd896a60213269b4e2d3bdd120c97e2fd623bddabbf43c2be422af</code></td>
        </tr>
        <tr>
            <td><code>dsp4.program.rom</code></td>
            <td>6144</td>
            <td><code>89b1826e6038be3a0ea0f923e85d589ff6f02dc1a1819fb2ec8c0cea5b333dcd</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan="2">ST010</th>
            <td><code>st010.data.rom</code></td>
            <td>4096</td>
            <td><code>dc7056a51b53993d7a8ba5bacf9501f785d2fce5e5be748e9ff2737c5938d4a5</code></td>
        </tr>
        <tr>
            <td><code>st010.program.rom</code></td>
            <td>49152</td>
            <td><code>2c1f74bb5f466d81c64c326e71ac054489efe1abc9a5d6f91aac7747f2ddab67</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan="2">ST011</th>
            <td><code>st011.data.rom</code></td>
            <td>4096</td>
            <td><code>b5377d1bebe8adc507a024b6e2b9b8fdf4877e451da84fbad05dff4e4a70311e</code></td>
        </tr>
        <tr>
            <td><code>st011.program.rom</code></td>
            <td>49152</td>
            <td><code>d90a5cda380e81cb9ba11a9da7539b173c49b31bedc7a3ac9c3c8b3f97e89e14</code></td>
        </tr>
        <tr>
            <th scope="row" rowspan="2">ST018</th>
            <td><code>st018.data.rom</code></td>
            <td>32768</td>
            <td><code>c67032238b7182696cb80cf41b61bacda91adb2120b5370bea20c9dbf5cc79b8</code></td>
        </tr>
        <tr>
            <td><code>st018.program.rom</code></td>
            <td>131072</td>
            <td><code>6cceff3c6945bb2672040066d218efcd2f31492f3f5c28916c8e53435c2c887e</code></td>
        </tr>
    </tbody>
</table>

**Note 1:**
The CX4 firmware is shipped with higan,
because it just contains mathematical tables
and not a copyrightable program.

**Note 2:**
The DSP1 and DSP1A are physically different,
but the firmware inside is identical.

**Note 3:**
The DSP1B is very similar to the DSP1A,
but fixes some bugs.
Note that icarus' heuristics cannot distinguish between
a game that uses the DSP1
and one that uses the DSP1B,
so if it cannot find your game in its database,
it will assume it uses DSP1B.
Many games work just as well with either variant,
but *Pilotwings* requires the DSP1 firmware,
while *Ballz 3D* requires the DSP1B.

If you try to import a game with icarus,
but it cannot find the required firmware files,
a window will appear saying
"Import completed, but with 1 errors. View log?"
(or however many games were lacking firmware).
If you press "Yes",
a new window will appear listing the games that couldn't be imported,
and what problem was detected:

> [sbl2.sfc] ROM image is missing data: dsp1.program.rom; dsp1.data.rom

If you try to import a game
using the "Load ROM File ..." option in the [Systems menu]
but it does not include the correct firmware data,
nothing will happen,
and higan will just sit there
with "Unloaded" in
[the status bar](../interface/higan.md#the-status-bar).

Once a game with co-processor firmware is imported,
you can play it just like any [regular game](#regular-games).

Satellaview games
-----------------

The [Satellaview]
was a satellite modem peripheral
released for the Super Famicom in Japan.
As well as the actual modem
(designed to sit underneath the Super Famicom),
it also included a cartridge
with software to control the modem,
browse online services,
and download games and data.
This control cartridge was called
*BS-X Sore wa Namae o Nusumareta Machi no Monogatari*,
which in English is
*BS-X The Story of The Town Whose Name Was Stolen*.

[Satellaview]: https://en.wikipedia.org/wiki/Satellaview

The control cartridge had a slot that accepted
re-writable "memory paks",
so that people could store the games and data they downloaded.
A small number of games that did not use the Satellaview modem
also had a memory pak slot,
so the game's publishers could
publish extra content for the game
via the Satellaview service
after the game's release.
For the benefit of people who didn't own a Satellaview
some read-only memory paks
were sold in retail stores
containing extra content for specific games.

Importing a game that has a slot for a memory pak
is just like [importing a regular game](#regular-games).

To import a memory pak,
you should use [icarus].
You can use the "Load ROM File ..." menu item
in the [Systems menu],
but higan cannot actually load a memory pak directly,
so once you choose a file to load
it looks like nothing has happened.

When importing a memory pak,
the name of the memory pak file *must* end in `.bs`
(if it's in a `.zip` file,
that's OK,
but the name *inside* the `.zip` file
must end in `.bs`)
in order for it to be successfully imported.
Sometimes memory pak filenames end in `.sfc`,
which will make higan try to import them as
regular Super Famicom games
and fail.
Rename the file and it should work beautifully.

Playing a game that has a slot for a memory pak
is just like playing a regular game,
but after you have selected which game you want to play
higan will open another [filesystem browser]
to let you pick which previously-imported memory pak
you want to insert into the game.
If you press "Cancel" at this point,
the game will load without any cartridge in its memory pak slot.

If you load the control cartridge into higan,
make sure the emulated Satellaview
is connected to the emulated Super Famicom's expansion port
by opening the "Super Famicom" menu,
selecting the "Expansion Port" sub-menu,
and choosing "Satellaview".
If the expansion port was previously
configured with a different option,
power-cycle the Super Famicom
(also in the "Super Famicom" menu)
to make sure the control cartridge will find the Satellaview
when it starts up.
Note that higan's Satellaview emulation is not very accurate,
so the control cartridge may not work as it should.

Playing a memory pak on its own doesn't make much sense,
it's not a standalone cartridge.
Play a game with a memory pak slot,
and choose which memory pak you want when higan asks for it.

For more information about the Satellaview service,
a translation patch for the control cartridge
and emulators that do a better job of Satellaview emulation,
see [the BS-X Project](https://bsxproj.superfamicom.org/).

Sufami Turbo games
------------------

The [Sufami Turbo]
was a special cartridge released
for the Super Famicom in Japan.
The Sufami Turbo on its own does nothing,
but it has two slots in the top
that accept Sufami Turbo mini-cartridges.
The game in slot A is the one that actually plays,
but some games can make use of additional data
from a game in slot B.

Importing the Sufami Turbo cartridge
is just like [importing a regular game](#regular-games).

To import a mini-cartridge,
you should use [icarus].
You can use the "Load ROM File ..." menu item
in the [Systems menu],
but higan cannot actually load a mini-cartridge directly,
so once you choose a file to load
it looks like nothing has happened.

When importing a mini-cartridge,
the name of the file *must* end in `.st`
(if it's in a `.zip` file,
that's OK,
but the name *inside* the `.zip` file
must end in `.st`)
in order for it to be successfully imported.
Sometimes mini-cartridge filenames end in `.sfc`,
which will make higan try to import them as
regular Super Famicom games,
and fail miserably.
Rename the file and it should work beautifully.

To play a Sufami Turbo game,
load the Sufami Turbo cartridge like any other game.
higan will open another [filesystem browser]
to let you pick which previously-imported mini-cartridge
you want to insert into slot A.
If you press "Cancel" at this point,
the Sufami Turbo cartridge will boot without anything in slot A,
which just displays an image telling you
to turn off your Super Famicom,
insert a game into slot A,
and try again.
If you chose a cartridge for slot A,
higan will open yet another
filesystem browser
to let you choose a mini-cartridge for slot B.
If you press "Cancel" at this point,
the Sufami Turbo cartridge will boot without anything in slot B.

If you play Sufami Turbo games regularly,
you may want to add the Sufami Turbo base cartridge
to the [Systems menu]
so you don't have to tell higan where it is every time.

[Sufami Turbo]: https://en.wikipedia.org/wiki/Sufami_Turbo

Super Game Boy games
--------------------

The Super Game Boy was a special cartridge
released for the Super Famicom
(and all its regional variants around the world)
that allowed Game Boy games to be played
via the Super Famicom's controllers and video output.
The Super Game Boy does not emulate the Game Boy hardware,
it physically includes all the Game Boy components
so compatibility with Game Boy games is high.
However, the Super Game Boy drives the Game Boy hardware
from the Super Famicom's timing signals, which means
games play 2.4% faster than on a real Game Boy.

The Super Game Boy 2 was a Japan-only release
that fixed the timing problem of the original Super Game Boy,
and included a different set of default borders.
higan emulates the Super Game Boy 2 completely,
including the timing change.

Because the Super Game Boy cartridge includes
the original Game Boy hardware,
it needs a boot ROM.
icarus includes these files
and can reliably decide when to use them,
so importing either Super Game Boy cartridge
is just like [importing a regular game](#regular-games).

In case you need to check the Super Game Boy boot roms,
here are their details:

<table>
    <thead>
        <tr>
            <th>Cartridge</th>
            <th>Filename</th>
            <th>Size (bytes)</th>
            <th>SHA256</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th scope="row">SGB</th>
            <td><code>sgb1.boot.rom</code></td>
            <td>256</td>
            <td><code>0e4ddff32fc9d1eeaae812a157dd246459b00c9e14f2f61751f661f32361e360</code></td>
        </tr>
        <tr>
            <th scope="row">SGB2</th>
            <td><code>sgb2.boot.rom</code></td>
            <td>256</td>
            <td><code>fd243c4fb27008986316ce3df29e9cfbcdc0cd52704970555a8bb76edbec3988</code></td>
        </tr>
    </tbody>
</table>

To play a Game Boy game in Super Game Boy mode,
load the Super Game Boy cartridge like any other game.
higan will open another [filesystem browser]
to let you pick which previously-imported Game Boy game
you want to insert into the Super Game Boy.
If you press "Cancel" at this point,
higan will crash, so don't do that.

If you regularly play Game Boy games
through the Super Game Boy,
you may want to add it to the [Systems menu]
so you don't have to tell higan where it is every time.

**Note:**
Only games for the original, black-and-white Game Boy
can be used with the Super Game Boy.
Some games designed for the Game Boy Color
were backward compatible with the original Game Boy
and hence the Super Game Boy;
see [Playing Game Boy Color games in Game Boy mode][blackcarts]
for details.

[blackcarts]: ../notes.md#playing-game-boy-color-games-in-game-boy-mode

MSU1 games
----------

The MSU1 is a fictional expansion chip
invented by higan's author byuu,
designed to allow the Super Famicom
to stream data and audio.
Although the MSU1 is not specific
to any particular storage medium,
it gives the Super Famicom similar capabilities
to CD-based add-ons
like the Mega Drive's Mega CD
and the PC Engine's CD-ROM²,
such as CD-quality music and full-motion video.

Although the MSU1 was invented for higan,
it is now supported by other Super Famicom emulators too.
The [SD2SNES] programmable cartridge
even allows you to play MSU1 games on a real console.
There are a number of homebrew games
that make use of the MSU1,
and also mods for commercial Super Famicom games
that add higher-quality music and sometimes video.

One thing to be aware of
when importing an MSU1 game
is that early firmware versions of the SD2SNES
had a bug that caused MSU1 music to play too quietly.
Skipping over [the full details][msu1vol],
the short version is this:

  - If offered the choice between "boosted" or non-boosted audio,
    you want the non-boosted version.
  - If an MSU1 mod for a commercial game offers
    "emulator" and "hardware" versions of the patch file,
    it means the audio tracks are already boosted.
  - Some
    [third](https://www.zeldix.net/t1265-#18320)
    [parties](https://www.zeldix.net/t1339-#19818)
    have created replacement, non-boosted audio tracks
    for the most popular MSU1 mods.
    If the mod you want to play has a replacement pack,
    use it with the "hardware" version of the patch.
  - Even without access to non-boosted audio tracks,
    it may be that the existing audio is only slightly boosted,
    so try the "hardware" version first, for best quality.
  - If the audio tracks are heavily boosted,
    the "hardware" patch may sound terrible,
    distorting and clipping,
    in which case try the "emulator" patch.

To import an MSU1 game:

 1. If you have a single, large file
    with the `.msu1` extension,
    that is a pack for use with [Mercurial Magic],
    which can automatically set up a game folder
    in the correct format.
    Go read Mercurial Magic's documentation
    instead of these instructions.
 2. Otherwise,
    import the Super Famicom ROM with icarus,
    [like a regular game](#regular-games).
      - If this is a homebrew game with MSU1 support,
        there will probably be an ordinary ROM
        whose name ends in `.sfc`,
        which is the file you want to import.
      - If this is a commercial game modded for MSU1 support,
        there will probably be a patch file
        whose name ends in `.ips` or `.bps`.
        Get a copy of the correct version of the commercial game,
        apply the patch with a tool like [Flips],
        then import the patched file.
      - If there's "hardware" and "emulator" versions of the patch,
        see "One thing to be aware of..." above.
 3. Find the game folder in the [game library]
    that icarus created when it imported the game.
 4. Inside the game folder,
    create a new folder named `msu1`.
 5. Copy the MSU1 data file into the new `msu1` folder.
      - This should be named `data.rom`
      - If there's no file by that name,
        look for a file named `msu1.rom`,
        or a file with a `.msu` extension,
        and rename it to `msu1.rom`.
      - If there's no file ending in `.msu` either,
        create an empty file named `msu1.rom`.
 6. Copy the audio tracks into the game folder.
      - If you have to choose between two sets of audio files,
        see "One thing to be aware of..." above.
      - These should be named
        `track-1.pcm`,
        `track-2.pcm`,
        ... `track-9.pcm`,
        `track-10.pcm`,
        etc.
      - If there's no files with those names,
        there should be other numbered `.pcm` files
        that you can rename to match what higan expects.
      - If the `.pcm` files have no numbers in the filenames,
        there maybe a `.bml` or `.xml` file that lists
        which number goes with which file.
      - If there's no `.pcm` files at all,
        that's OK,
        this game probably just doesn't use the audio-playback feature.

Once the game folder is set up,
playing an MSU1 game is just like
[a regular game](#regular-games).

[SD2SNES]: https://sd2snes.de/
[Flips]: http://www.romhacking.net/utilities/1040/
[msu1vol]: http://blog.qwertymodo.com/2017/07/the-msu-1-volume-fiasco-explained.html
[Mercurial Magic]: https://github.com/qwertymodo/Mercurial-Magic

Patched games
-------------

The console emulation community
has a long and vibrant history of game modding,
or [ROM hacking],
including fan-translations,
new levels for existing games,
and more.
Since distributing the modified versions of existing games
would be copyright infringement,
the changes are typically distributed as "patches",
a file containing a list of modifications to make,
that can be automatically applied by a "patcher" tool
like [Flips].

higan does not support soft-patching,
so if you want to play a patched game in higan,
you will need to use a patcher to apply it yourself,
creating a new, patched copy of the game.

Then you can import and play the patched game just like
[a regular game](#regular-games).

[ROM hacking]: http://www.romhacking.net/

Game Boy Advance games
----------------------

Before you can play Game Boy Advance games,
you must provide a copy of the Game Boy Advance BIOS.
Unlike game-specific firmware,
the GBA BIOS was part of the console,
not the cartridge,
so it must be installed
[into higan](../install/general.md).

Once the GBA BIOS is installed,
GBA games can be imported and played just like
[any other games](#regular-games).

Note that some GBA games
have trouble with
[in-game saves](../notes.md#in-game-saves-and-the-game-boy-advance).

PowerFest '94
-------------

[PowerFest '94](https://en.wikipedia.org/wiki/Nintendo_PowerFest_%2794)
was a video game competition
organised by Nintendo,
in which contestants had six minutes
to complete a challenge based on three Super Famicom games.
The PowerFest '94 cartridge
was custom-built for the competition,
and included the three base games
as well as software to run each game,
switch between them after a specific time,
extract a score,
and display the combined total at the end.

Previous versions of higan
could emulate the PowerFest '94 cartridge,
but changes to higan's manifest system in v107
prevent PowerFest '94 from working in that version.
Support will likely be re-added in a future version,
but in the mean time you can use higan v106
and follow [that version's import instructions][pf94v106].

[pf94v106]: https://higan.readthedocs.io/en/v106/guides/import/#powerfest-94

[filesystem browser]: ../interface/common.md#the-filesystem-browser
[Game Library]: ../concepts/game-library.md
[icarus]: ../interface/icarus.md
[Systems menu]: ../interface/higan.md#the-systems-menu
