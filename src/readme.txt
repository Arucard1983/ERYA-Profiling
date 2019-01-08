ERYA-Profiling 2.30 ReadMe
----------------------------------------

Testing Release

---------------------------------------

1. Minimum Requirements

ERYA-Profilinh requires a computer with an supported operating system or architecture.
- Current Version supports Windows 7 or greater (Windows XP may work), Mac OS X 10.11 or greater (Mac OS X 10.7 may work), Linux with GTK+ 3.0 toolkit (libwxgtk3 library) or greater.
- 64-bit x86-64 is the default suported architecture for all operating systems listed before. Windows and Linux 32-bit versions are provided for legacy systems.
- The minimum usefull screen resolution is 1280*720, but it is highly recommended to use a FullHD display (1920*1080) for better view.
- If the text size in labels and menus are to small or too big, even using the recomended screen resolutions, try to set the default pixel scale to normal (72 or 90 dpi), using the native operating system tools.
- About 100 Mb of free hard disk space is highly recommended.

2. Installation from the Source Code

If you have a computer with different architecture (ARM, PowerPC, Intel i386, etc), or an operating system not listed above (BSD, UNIX, etc) you can build ERYA-Profiling from the source.
- Your operating system should bundled or support a C++11 compilant compiler
- Linux and some Unix operating systems will use GCC as a default. Recently the Clang compiler was also a viable alternative.
- Microsoft Windows recommends the Visual Studio, since it is the native IDE for Microsoft Windows applications. 
- The MinGW/MSYS alternative to Windows is also supported, and may be more useful for users that are more familiar to POSIX/GCC tools. Clang on Windows requires an emulated UNIX shell like Cygwin.
- Mac OS X recently switch to Clang, where is GCC compilant, except some advanced features that are unimportant.

ERYA-Profiling require the wxWidgets framework version 3.0.4 to be built sucessfully. The current built Windows versions require patches from wxWidgets 3.0.4, to run on Windows 10 without problems.
- The wxWidgets framework is a C++ cross-platform toolkit that support several architectures and operating systems. Follow the instructions from wxWidgets website to download,
compile and build the libraries.
- For pure convenience, a patched third-source wxMathPlot library, was bundled on source-code, but you should not change the source code without contribute to the original wxMathPlot author.
- Now run your favorite compiler environment and choose the source folder. It should be built without issues.


3. Installation from Binary Package.

# Linux Instructions
- Download the "Linux" package to a temporary folder, and then open a Terminal emulator:
$ cd <temp folder>
# If you use Debian, or Ubuntu, then install the package using the following commands:
$ sudo dpkg -i eryaprofiling_2.30-5_amd64.deb && sudo apt-get -f install
# Or using the GUI GNOME Software installer, Synaptic or any package manager avaliable.
- And then open the ERYA-Profiling from your favorite Desktop Environment (Menu>Science>ERYA-Profiling), or simply type on Terminal:
$ /opt/ERYA-Profiling/ERYA-Profiling
- The ERYA-Profiling will create a profile directory as ~/.ERYA-Profiling, where the local configuration settings will be stored.
# To uninstall, simply use this command on Terminal:
$ sudo apt-get remove eryaprofiling
- If necessary, delete the user profile folder:
$ rm -rf ~/.ERYA-Profiling
- If the program complains about missing libraries, check your Linux Distro support website to search the package name of libwxgtk3. On Debian systems, just type:
$ sudo apt-get install libwxgtk3.0-0*
Note: To run ERYA-Profiling as a portable program, just untar the installation program, and run directly on the current directory.
Notice: To install ERYA-Profiling on Debian systems, you may need to check if the backports repositories are enabled, otherwise the installation will complain about unavailable dependencies.

# Windows Instructions
- Open the Self-Extractor archive, and select the desired target folder. You can extract to the standard Program Directory, or to a user Documents folder.
- To uninstall, just delete the program folder or run the uninstaller program.
- Ince removed, if necessary delete the C:\users\<name>\Local Settings\Application Data\ERYA-Profiling\ folder.

# Mac OS X Instructions
- Unpack the zipped file, and then copy the application package (ERYA-Profiling.app) to the Applications folder.
- To uninstall, delete the application from the Application folder, and then the ~/Library/Application Support/ERYA-Profiling folder.

4. First Run

# At start-up, once the program don't found any configuration file, it will display a wizard, asking the user to follow the instructions.
Once completed, ERYA-Profiling will create a ERYA-Profiling.conf on the local user settings directory, which location are defaulted by wxWidgets (see remarks above), where should store the target location and the name of three core database files (Element Database, Detector Efficiency and Ziegler Parameters).
# You can use the original Databases from LabView ERYA, including the text format, and the binary format. However ERYA-Profiling will export, check and convert to their native format as their default databases.
# If you use the LabView ERYA-Profiling program before, it is necessary to copy the Bloch and Densities text files. The wxWidgets ERYA-Profiling will copy them to the Ziegler's parameters native file format.
- It is strongly recomended to use the LabView Import Wizard from Tools>Labview, to convert the original databases and attachments to the new native ERYA-Profiling format. 
# The original bundled databases are located in the same directory of the program, and during this step the program will default this folder to ease the user selection. 
# The program will check the selected files, and if everything goes correctly, the selected databases and the configuration file will be stored sucefully, otherwise you will get an error and ERYA will start in reset mode (No database loaded at all).
- Once done selecting (it's better to choose the bundled databases first), ERYA-Profiling will start at full functionality.
- In next start-up, ERYA-Profiling will load the config file automatically and load the database files without user interaction.
# Note: If any default database is damaged, an error will be issued, and probably require to repeat the first time procedure to reset.
# Note: The ERYA-Profiling.conf file will be stored on the following directory.
- Linux : ~/.ERYA-Profiling/
- Windows : C:\users\<name>\Local Settings\Application Data\ERYA-Profiling\
- Mac OS X: ~/Library/Application Support/ERYA-Profiling
- Portable (All Operating Systems): The same program directory.

5. About files compability

- ERYA-Profiling can export the Ziegler, Detector and Element database from the ERYA software built with the LabView Runtime.
- LabView Binary database format is partial supported, and this software only import them. You cannot export the current database on LabView format, since the LabView DataLog format is not documented!
- Text-form databases can be exported (very good support), and imported(some issues). The on-line help contain some compability notes about the supported formats.
- The user can import IBANDL files to edit Element's characteristics, but saving is limited, since some data are not exported, due to the IBANDL file conventions.
- Experimental support of Microsoft Office Excel Xlsx files (2007,2010,2013, and beyond) at very basic level was implemented.
# Note: ERYA-Bulk will use internally the native file format, and makes automatically the conversions if it loads any supported third-party file format.

6. Implemented Features

This interim release had the following features:
# Can read and save profile files on XML format, avoiding the manual typesetting of every sample previously stored.
# The numerical physics libraries should work as expected, generating the output, than can be stored as an image file, or a spreadsheet file.
# The ported tools for Database Management from the ERYA-Bulk program works as expected.
# Revamping of importing tools, including a wizard to export binary databases from Labview to the native ERYA-Profiling XML format.
- The import/export tools on "Database Manager" still works to convert different file formats. 
# First Version of on-line help completed.
# It's now possible to choose between two asymptotic limits of Vavilov Distribution on "Advanced Settings": The Vavilov-Gauss limit, or the Bohr formula limit.
# An option to turn-on and turn-off the partial yields logs (that appears on the last tab on main program window) calculation on "Advanced Settings".
# With long samples, it avoids to create huge memory logs that can increase the computation and rendering time. 
# The main calculation progress now displays an additional gauge window, along the status bar. It also enables the user to abort the whole process.
# Fixed some bugs on the built-in ERYA's macro language:
- Expressions such as "(-3)", or "(+3)" now return "-3" and "3", instead the wrong "-" token error, due to an absent rule to the lexer when face a plus/minus signal and the left parenthesis, and split the signal before the number, instead to read the signed number as a whole token.
- When the interpreter tokenize a expression with a single token, like a variable "x" alone, it return a wrong "0" value instead the "Undefined variable: x" error. This was caused by an absent rule on the stack calculator logic on the final step, and now it is fixed.
# Fixed the numerical integration domain of yields, thus solving some abnormal results on some simulations.
# Support for Stopping-Power calculation by table interpolation, usally imported from the SRIM program.

7. Future Improvements

# It's expected a better integration with the ERYA-Bulk files, but none are still avaliable.
# An SRIM table import tool are intended in the future.

8. Troubleshooting and Issues

# This release is only tested to evaluate samples profiles, where the user can store the results, or save the inputs as templates that can be readed again.
# Notice that samples with huge depth, where the depth step can be tiny, or huge number of initial energy steps, can take several hours to complete.
- Disabling log on such samples, will avoid some time to ERYA convert the huge log memory stacks to the "Log" table, reducing the computation time a little.
# The log table on bigger samples can have hundred of thousand lines, taking several seconds to save, if you select the Excel file format output.
- Notice that the Excel files cannot have more than 1048576 lines. When finished the simulation, please check the table size on "Output Log" tab, or choose the ASCII file format.

Copyrights

Group: 2018 LibPhys
Programmer e-mail: vm.manteigas@campus.fct.unl.pt
wxMathPlot/wxWidgets licence: https://github.com/wxWidgets/wxWidgets/blob/master/docs/licence.txt
