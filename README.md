# DenKr_essentials


Some basic functionalities to amplify a framework

worth mentioning:
- A Shared Memory information exchange mechanic for Threads
- An Information Exchange Method in a publish & subscribe styled manner
- The possibility to connect / communicate live with Python Scripts
-> Join the PubSub Message Bus (requires the plugin "DenKrement_plugin_predefined__connect_external_Python" from "DenKrement_plugins" and the Python Package "DenKrement_external_Python")
- Some aids for Multi-Threading
- A Thread Manager (including Thread spawn and tracking aid)
- A Plugin Manager (automatically detects and loads compatible Plugins. Allows to load plugins "as Threads" or "as Libraries". Automatically starts Thread-like plugins and tracks them using the Thread-Manager)
- Two differently typed Hash-Tables
- A collection of PreProcessor enhancing Macros
- A Macro/Function set to read out "Time" from different clocks, in different precisions or formats
- Several Sort & Search Algorithms
- "Function Creator / FanOut"  - Create Functions out of Macros. For example to unify the Place, where a Function Prototype is declared to exactly one position. Or Fan-Out multiple Functions with some common Code, but also Distinctions in them. Or dynamically create several functions, depending on "Macro Inputs"
- Aid for File-Handling, e.g. Config-File definition and read
- Some additional "auxiliary" functions (Framework Initialization, check system-endianess, helpful debug-print, macro/function overloading and whatnot)

This collection is nicely integrated into the Framework "DenKrement"


As a NOTE: I personally use »Eclipse« as IDE. With this you can Link to one and the same Copy of "DenKr_essentials" from different Projects.
