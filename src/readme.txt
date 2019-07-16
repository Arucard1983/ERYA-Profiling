ERYA-Profiling 2.70 ReadMe
----------------------------------------

Testing Release

---------------------------------------

1. Minimum Requirements

ERYA-Profiling requires a computer with an supported operating system or architecture.
- Windows 7, 10 or greater (Windows XP may work), Mac OS X 10.11 or greater (Mac OS X 10.10 may work), Linux Debian 10 or Ubuntu 18.04 or greater.
- 64-bit x86-64 is the default suported architecture for all operating systems listed before. Windows and Linux 32-bit versions are provided for legacy systems.
- ARM binary versions are also provided for Linux systems.
- The minimum usefull screen resolution is 1280*720, but it is highly recommended to use a FullHD display (1920*1080) for better view.
- About 100 Mb of free hard disk space is highly recommended.

2. Supported Features
# Ziegler's Parameters database supports the SRIM tables for all elements, along the Ziegler's Parameters of this stopping-power model itself. An optional algebraic expression are also supported.
# Detector's Efficiency suports algebraic functions as standard mode.
# Lorentzian Resonance supported, along a custom algebraic function option.
# The built-in algebraic parser are now a trimmed-down programming language by it's own, christianized as ERYA Macro.
# Isolation of legacy LabView code in order to support as a strict import feature.
# All native ERYA databases are XML files.
# All previous LabView ERYA features was ported to current ERYA.


3. Installation from Binary Package.

# Linux Instructions
3.1. Check first if your Linux distribution are compatible with Debian 9 or Ubuntu 18.04 codebase.

3.2. Download the correct arch version to your computer, then open a Terminal window on the same folder of the downloaded package.
- For Ubuntu systems, it's not necessary to open a root shell before install programs:
$ sudo apt update
$ sudo apt dist-upgrade
$ sudo dpkg -i *.deb
$ sudo apt -f install
- On Debian 9, due to higher security restrictions, it is necessary to open a root shell first:
$ su [Ask for your root password...]
$ apt update
$ apt dist-upgrade
$ dpkg -i *.deb
$ dpkg -t stretch-backports -f install

3.3. Open the ERYA-Profiling from your favorite Desktop Environment (Menu>Education>ERYA-Profiling), or simply type on Terminal:
$ /opt/ERYA-Profiling/ERYA-Profiling

3.4. The ERYA-Profiling will create a profile directory as ~/.ERYA-Profiling, where the local configuration settings will be stored.

3.5. To uninstall, simply use this command on Terminal:
$ sudo apt remove eryaprofiling

3.6. If necessary, delete the user profile folder:
$ rm -rf ~/.ERYA-Profiling

# Windows Instructions
- Open the Package File that will start the installation wizard program. Follow the instructions.
- To uninstall, just run the uninstaller program.
- Once removed, if necessary delete the C:\users\<name>\Local Settings\Application Data\ERYA-Profiling-Win64\ folder.

# Mac OS X Instructions
- Unpack the zipped file, and then copy the application package (ERYA-Profiling.app) to the Applications folder.
- To uninstall, delete the application from the Application folder, and then the ~/Library/Application Support/ERYA-Profiling-OSX folder.

4. First Run

# When ERYA don't find any configuration file, it will start a setup wizard, asking for the default Database, Detector and Ziegler files to be the default ones.
- Once completed the setup, ERYA will start automatically straight to GUI, loading the default databases into memory.
- A failure on this stage will make ERYA starts on reset mode, warning the user about the faulty file.
# You can import the original Databases from LabView ERYA, including the ones using plain text format, and the binary format, using the Database Tools on the program context.
- However ERYA-Bulk will import, check and convert to their native format when saves their content.
# To fix setup errors, open the tool from Database > Setup, and make the necessary changes.
- Once fixed, click on "Save" to create a new configuration file. The new settings will be tested, and ERYA will reload the databases to check if everything are fine.
- To reset any setup files, and forces ERYA to start the Setup Wizard, you can click on "Delete" button to make it.
# Note: The ERYA-Profiling.conf file will be stored on the following directory.
- Linux : ~/.ERYA-Profiling/
- Windows : C:\users\<name>\Local Settings\Application Data\ERYA-Profiling-Win64\
- Mac OS X: ~/Library/Application Support/ERYA-Profiling-OSX
- Portable (All Operating Systems): The same program directory.

5. About files compability

- ERYA-Profiling can export the Ziegler, Detector and Element database from the ERYA software built with the LabView Runtime.
- LabView Binary database format is partial supported, and this software only import them. You cannot export the current database on LabView format, since the LabView DataLog format is not documented!
- Text-form databases can be exported (very good support), and imported(some issues). The on-line help contain some compability notes about the supported formats.
- The user can import IBANDL files to edit Element's characteristics, but saving is limited, since some data are not exported, due to the IBANDL file conventions.
- SRIM parsing of Stopping-Power are now avaliable, making automatically all necessary convertions.
- Experimental support of Microsoft Office Excel Xlsx files (2007,2010,2013, and beyond) at very basic level was implemented.
# Note: ERYA-Bulk will use internally the native file format, and makes automatically the conversions if it loads any supported third-party file format.

6. Implemented Features

This interim release had the following features:
# Can read and save profile files on XML format, avoiding the manual typesetting of every sample previously stored.
# The numerical physics libraries should work as expected, generating the output, than can be stored as an image file, or a spreadsheet file.
# The ported tools for Database Management from the ERYA-Bulk program works as expected.
# Revamping of importing tools, including a wizard to export binary databases from Labview to the native ERYA-Profiling XML format.
- The import/export tools on "Database Manager" still works to convert different file formats.
# All on-line help contents are completed.
# It's now possible to choose between two asymptotic limits of Vavilov Distribution on "Advanced Settings": The Vavilov-Gauss limit, or the Bohr formula limit.
# Pure Gaussian mode to override the Vavilov Distribution are now avaliable on "Advanced Settings".
# An option to turn-on and turn-off the partial yields logs (that appears on the last tab on main program window) calculation on "Advanced Settings".
# With long samples, it avoids to create huge memory logs that can increase the computation and rendering time.
# The main calculation progress now displays an additional gauge window, along the status bar. It also enables the user to abort the whole process.
# Fixed some bugs on the built-in ERYA's macro language:
- Expressions such as "(-3)", or "(+3)" now return "-3" and "3", instead the wrong "-" token error, due to an absent rule to the lexer when face a plus/minus signal and the left parenthesis, and split the signal before the number, instead to read the signed number as a whole token.
- When the interpreter tokenize a expression with a single token, like a variable "x" alone, it return a wrong "0" value instead the "Undefined variable: x" error. This was caused by an absent rule on the stack calculator logic on the final step, and now it is fixed.
# Fixed the numerical integration domain of yields, thus solving some abnormal results on some simulations.
# Support for Stopping-Power calculation by table interpolation, usally imported from the SRIM program.
# Direct SRIM table parsing from Ziegler's import option.
# The window sizes can be resized with a mouse.
# SRIM tables are the default setting for the Stopping-Power.
# Added Airy Function as an approximation of the Vavilov Distribution, fixing abnormal oscillations on sharp resonances profiles.
# Help files was removed in favour to a unified PDF manual.
# Support to comment/remark on databases, while adding a simple text editor to edit/replace/clear them.

7. Future Improvements

# Future improvements on plots data are predicted.

8. Troubleshooting and Issues

# This release is only tested to evaluate samples profiles, where the user can store the results, or save the inputs as templates that can be readed again.
# Notice that samples with huge depth, where the depth step can be tiny, or huge number of initial energy steps, can take several hours to complete.
- Disabling log on such samples, will avoid some time to ERYA convert the huge log memory stacks to the "Log" table, reducing the computation time a little.
# The log table on bigger samples can have hundred of thousand lines, taking several seconds to save, if you select the Excel file format output.
- Notice that the Excel files cannot have more than 1048576 lines. When finished the simulation, please check the table size on "Output Log" tab, or choose the ASCII file format.

Copyrights

Group: 2018 LibPhys
Programmer e-mail: vm.manteigas@campus.fct.unl.pt
wxMathPlot/wxWidgets licence:  https://github.com/wxWidgets/wxWidgets/blob/master/docs/licence.txt
