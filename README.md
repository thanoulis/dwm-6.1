dwm - dynamic window manager
============================
**dwm** is an extremely fast, small, and dynamic window manager for X.

Differences from official dwm:

* Mod4 instead of Mod1 as basic modifier key
* special behaviour per application (floating/tiling, go to specific tag, etc)
* intuitive key bindings
* better mouse support
* build-in system tray area
* mouse wheel on tag list to go to previous or next tag

For more information: `man dwm`

Requirements
------------
In order to build **dwm** you need the _Xlib_ header files.
Also, you'll need _Xinerama_ header files to enable multiple displays.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```shell
while :; do
    # battery information
    batt_info=$(acpi -b | awk '{gsub(",",""); print $4}')
    # thermal information
    thermal_info=$(acpi -t | grep -Eo '[[:digit:]]+\.[[:digit:]]')
    # date information
    date_info=$(date +'%a %d %b %R')
    # print information
    xsetroot -name "Temp:${thermal_info:-N/A} Battery:${batt_info:-AC} $date_info"
    # update every 30 seconds
    sleep 30s
done &
```

or using conky:

```shell
conky | while read -r; do xsetroot -name "$REPLY"; done &
```

Configuration
-------------
The configuration of dwm is done by editing config.h and (re)compiling the source code.
