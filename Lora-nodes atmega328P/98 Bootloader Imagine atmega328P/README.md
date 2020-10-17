Imagine Solutions BV Arduino board definitions for the Imagine IOT node
Version 1.0.0 => 9-8-2019


These files tell the Arduino IDE about the hardware, how to compile code for it, and how to upload the compiled code to the board.

To set this up, you can use the Arduino IDE boards manager:

Open the Arduino IDE, and go to File -> Preferences.

In the "Additional board manager URLs", add the following url: 
https://raw.githubusercontent.com/EvertVersteeg/ImagineNode/master/package_imagine_index.json

Close the preferences, and open Tools -> Board -> Boards Manager...

Find the "Imagine IOT node" in the list, and click Install



License
The files in this repository are distributed under various licenses. Each file lists the license that applies to it, with the exception of the bootloader binaries. These are distributed under the GPLv2, see https://github.com/Optiboot/optiboot for the full terms and the sources used to compile the bootloader (see the commit log of this repository to find out the exact version used).