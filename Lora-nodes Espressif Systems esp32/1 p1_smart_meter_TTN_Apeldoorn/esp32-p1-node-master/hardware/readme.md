# TTN-Apeldoorn P1-Node board and housing
The P1-Node is designed with reproduction in mind. Therefore the PCB was desigened using <a href="https://kicad-pcb.org/" target="_blank">KiCad</a>. In addition, the PCB was designed with an introduction to SMD soldering in mind. Components are chosen to be "big" so they can be hand-soldered or using reflow techniques. The housing can be finished using basic drill techniques and some parts are 3D-printed.

## repository content
The hardware part of the repository has 5 folders:

   1. Documentation
   2. Board (esp32-p1-node-board)
   3. Housing (esp32-p1-node-housing)
   4. ![BOM](bom.md "BOM")
   5. ![Building instructions](instructions.md "Building instructions")

### Documentation
This ![folder](documentation/ "folder") contains relevant documentation, datasheets and links to topics that are relevant for the project.

### Board (esp32-p1-node-board)
This ![folder](esp32-p1-node-board/ "folder") contains the complete PCB design and libraries for the P1-Node for <a href="https://kicad-pcb.org/" target="_blank">KiCad</a>.

### Housing (esp32-p1-node-housing)
This ![folder](esp32-p1-node-housing/ "folder") contains both the source of the 3D printed frame as well as the .stl file for printing it. Also the measures for the holes that shall be made in the ABS housing are documented here.

File            | Note
----------------|--------------------------
Venster_003.skp | Source file of the frame in <a href="https://www.sketchup.com/" target="_blank">Sketchup</a> format.
Venster_003.stl | 3D file for printing in <a href="https://en.wikipedia.org/wiki/STL_(file_format)" target="_blank">STL</a> format.

### BOM (Bill of Materials)
The ![BOM](bom.md "BOM") presents a extensive list of materials for the P1-Node.

### Building Instructions
The ![Building instructions](instructions.md "Building instructions") describe how to build and progam de P1-Node.

# License
The TTN-Apeldoorn P1-Node node is free soft- and hardware:
you can redistribute and/or modify it under the terms of a Creative Commons Attribution-NonCommercial 4.0 International License (http://creativecommons.org/licenses/by-nc/4.0/) by TTN-Apeldoorn (https://www.thethingsnetwork.org/community/apeldoorn/) E-mail: ttnapeldoorncoreteam@rfsee.nl

<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.