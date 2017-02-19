![beethduino_logo](https://github.com/amcajal/beethduino/blob/master/software/5_support/readme_beethduino_logo.png)

### Overview

**Beethduino** (pun intended between Beethoven and Arduino) is a simple, Do-It-Yourself, Arduino-based electronic metronome. Let there be Rhythm!
![beethduino_device.png](https://github.com/amcajal/beethduino/blob/master/software/5_support/beethduino_device.png)

### Index
1. [Project Content](#project-content)
2. [Quickstart](#quickstart)
3. [License](#license)
4. [Contributions](#contributions)
5. [Contact](#contact)

---

### Project Content

*Master Branch*: Contains all files required to built Beethduino -source code, schematics, diagrams-.
- **Software Folder**: Contains the *Software Development Life Cycle* deliverables.
	- 1_Requirements: CSV and text files with a mixture of user, system, high level and low level requirements. Note this requirements are early approximations, and while they were used to design the software, they don't represent the definitive ones.
	- 2_Design: UML -activity- diagrams of Beethduino functions. Saved in XML files, intended to be opened with [draw.io](https://www.draw.io/), a free online diagram software.
	- 3_Implementation: Arduino C/C++ subset Source Code of Beethduino. One single file.
	- 4_Testing: C++ Beethduino library (for testing purposes), as well as Component test, Unit test and Integration test folders, with test codes for each section (in Arduino C/C++ subset too).
                 Includes an XML file with the **Beethduino** call-graph, with the priority of each function depicted (risk assesment), used to define the test cases. Opened with draw.io tool too.
	- 5_Support: Miscellaneous resources -as images- used both in this README and in the [Wiki](https://github.com/amcajal/beethduino/wiki).
- **Hardware Folder**: Contains component-level-physical- specifications.
	- List of materials: txt file with list of electronic devices used in Beethduino.
	- Protoboard: PNG Image with Beethduino protoype connection and appearance.
	- Schematic: PNG Image with Beethduino connections at technical level.
	- Fritzing sketch: [Fritzing](http://fritzing.org/home/) file, containing previous Protoboard and tentative related PCB and schematic (neither used due to lack of accuracy).
- LICENSE: file with the [GNU GPL v3.0 license](https://www.gnu.org/licenses/gpl-3.0.html), applied to this project.
- README.md (this very file).

####*[Wiki Page](https://github.com/amcajal/beethduino/wiki)*: Contains all documentation about the project -rationale, used tools and external resources-.

Note: Both README and Wiki pages are writen using Markdown syntax.

[Back to index](#index)


### Quickstart

Watch Beethduino in action, and learn to use it in this simple, short, cut-to-the-chase video.
[![Beethduino Tutorial](http://img.youtube.com/vi/TdTyggPhVdc/0.jpg)](http://www.youtube.com/watch?v=TdTyggPhVdc)

Summary:
- LCD show all the information: BPM value, mode, and if Buzzer is muted or not.
- Press "Reset" to return Beethduino to its initial state: 60 BPM, "Add" mode and buzzer muted.
- Press "AddOrSub" to change the mode of the BPM. When "Add", BPM value is increased; when "Sub", BPM value is decreased.
- Press "ByOne" to modify BPM value by one unit.
- Press "ByTen" to modify BPM value by ten units.
- Press "MuteOrUnmute" to turn on and off the buzzer. When on, the buzzer will "bip" at the established frequency (i.e: 60 BPM = 60 Beats Per Minute).


[Back to index](#index)


### License

Alberto Martin Cajal is the original author of **Beethduino** project.
**Beethduino** project is released under GNU GPL version 3.0 license. [Check LICENSE file](https://github.com/amcajal/beethduino/blob/master/LICENSE) for a full version of it, or [visit the official GNU web page](https://www.gnu.org/licenses/gpl-3.0.html).

[Back to index](#index)



### Contributions

Feel free to clone or branch the repository, as long as you keep the license terms.
To report bugs, request information, new features or any relate operation, go to [Issues page](https://github.com/amcajal/beethduino/issues) 

[Back to index](#index)


### Contact
Alberto Martin Cajal at:
 
- Gmail: amartin.glimpse23@gmail.com (amartin DOT glimpse23 AT gmail DOT com)
- [Blogspot](http://glimpse-23.blogspot.com.es/)
- [LinkedIn](https://es.linkedin.com/in/alberto-martin-cajal-b0a63379)
- Twitter: @amartin_g23

[Back to index](#index)

---

#### This project has been created trying to make it usefull. This project has been created in order to learn new things. But over all, this project has been created because it is fun. As Isaac Asimov said:

*The most exciting phrase to hear in science, the one that heralds new discoveries, is not 'Eureka' but 'That’s funny...'*

