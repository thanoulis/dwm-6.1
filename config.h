// custom dwm header file

// appearance
static const char *fonts[]              = { "DejaVu Sans Mono:size=9" };
static const char dmenufont[]           = "DejaVu Sans Mono:size=9";

static const char normbordercolor[]     = "#3F403D";
static const char normbgcolor[]         = "#D6D6D6";
static const char normfgcolor[]         = "#4E4E4E";
static const char selbordercolor[]      = "#7AA3CC";
static const char selbgcolor[]          = "#4E4E4E";
static const char selfgcolor[]          = "#D6D6D6";

static const unsigned int borderpx      = 1;        // windows border (pixels)
static const unsigned int snap          = 24;       // snap pixels
static const int showbar                = 1;        // 0: no bar
static const int topbar                 = 1;        // 0: bottom bar

// systray
static const unsigned int systraypinning = 0;   // 0: sloppy systray follows selected monitor, >0: pin systray to monitor X
static const unsigned int systrayspacing = 2;   // systray spacing
static const int systraypinningfailfirst = 1;   // 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor
static const int showsystray             = 1;   // 0: no systray

// tagging
static const char *tags[] = { "Main", "Web", "Office", "Graphics", "Files", "Virtual", "Multimedia", "Fun", "Misc" };
/* query class:instance:title for regex matching info with following command:
xprop | awk ' /^WM_CLASS/{sub(/.* =/, "instance:"); sub(/,/, "\nclass:"); print} /^WM_NAME/{sub(/.* =/, "title:"); print}'
*/
static const Rule rules[] = {
    // class                    instance        title           tags mask   isfloating  monitor
    // -- General -----------------------------------------------------------------------------
    { NULL,                     NULL,           "Event Tester", 0,          True,       -1 },
    { "feh",                    NULL,           NULL,           0,          True,       -1 },
    { "XCalc",                  NULL,           NULL,           0,          True,       -1 },
    { "Display",                NULL,           NULL,           0,          True,       -1 },
    { "Stardict",               NULL,           NULL,           0,          True,       -1 },
    { "Xmessage",               NULL,           NULL,           0,          True,       -1 },
    { "MPlayer",                NULL,           NULL,           0,          True,       -1 },
    { "Firefox",                NULL,           NULL,           0,          True,       -1 },
    { "XFontSel",               NULL,           NULL,           0,          True,       -1 },
    { "Gtk2fontsel",            NULL,           NULL,           0,          True,       -1 },
    { "Xarchiver",              NULL,           NULL,           0,          True,       -1 },
    // -- Web ---------------------------------------------------------------------------------
    { "URxvt",                  "mutt",         NULL,           1 << 1,     False,      -1 },
    { "Firefox",                "Navigator",    NULL,           1 << 1,     False,      -1 },
    // -- Office ------------------------------------------------------------------------------
    { "MuPDF",                  NULL,           NULL,           1 << 2,     False,      -1 },
    { "libreoffice",            NULL,           NULL,           1 << 2,     False,      -1 },
    // -- Graphics ----------------------------------------------------------------------------
    { "Gimp",                   NULL,           NULL,           1 << 3,     True,       -1 },
    { "Inkscape",               NULL,           NULL,           1 << 3,     False,      -1 },
    // -- Files -------------------------------------------------------------------------------
    { "URxvt",                  "mc",           NULL,           1 << 4,     False,      -1 },
    // -- Virtual -----------------------------------------------------------------------------
    { "Qemu-system-",           NULL,           NULL,           1 << 5,     False,      -1 },
    // -- Multimedia --------------------------------------------------------------------------
    { "URxvt",                  "cmus",         NULL,           1 << 6,     False,      -1 },
    { "Easytag",                NULL,           NULL,           1 << 6,     False,      -1 },
    // -- Fun ---------------------------------------------------------------------------------
    { "Pychess",                NULL,           NULL,           1 << 7,     True,       -1 },
    { "wesnoth",                NULL,           NULL,           1 << 7,     False,      -1 },
    // -- Misc --------------------------------------------------------------------------------
    { "URxvt",                  "weechat",      NULL,           1 << 8,     False,      -1 },
    { "GParted",                NULL,           NULL,           1 << 8,     True,       -1 },
};

// include extras
#include "shiftview.c"

// layout(s)
static const float mfact        = 0.50;
static const int nmaster        = 1;        // number of clients in master area
static const int resizehints    = 0;        // 1: respect size hints in tiled resizals

static const Layout layouts[] = {
    // symbol	arrange function
    { "[]=",    tile },         // default tiling layout
    { "><>",    NULL },         // no layout function means floating behavior
    { "[M]",    monocle },      // maximize each window
};

// key definitions
#define AltKey  Mod1Mask    // Mod1Mask = Alt
#define WinKey  Mod4Mask    // Mod4Mask = Win
#define TAGKEYS(KEY,TAG) \
    { WinKey,                       KEY,    view,           {.ui = 1 << TAG} }, \
    { WinKey|ControlMask,           KEY,    toggleview,     {.ui = 1 << TAG} }, \
    { WinKey|ShiftMask,             KEY,    tag,            {.ui = 1 << TAG} }, \
    { WinKey|AltKey,                KEY,    toggletag,      {.ui = 1 << TAG} },

// helper for spawning shell commands in the pre dwm-5.0 fashion
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// commands
// -- programs -----------------------------------------------------
static char dmenumon[2]             = "0";  // 0: first monitor
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, "-p", "Execute:", NULL };
static const char *urxvt[]          = { "urxvtc", NULL };
static const char *xterm[]          = { "xterm", NULL };
static const char *firefox[]        = { "firefox", NULL, NULL, NULL, "Firefox" };
static const char *mc[]             = { "urxvtc", "-name", "mc", "-title", "File Manager", "-e", "mc", NULL };
static const char *tmux[]           = { "urxvtc", "-name", "tmux", "-title", "Terminal Multiplexer", "-e", "tmux", NULL };
static const char *htop[]           = { "urxvtc", "-name", "htop", "-title", "System Monitor", "-e", "htop", NULL };
static const char *mutt[]           = { "urxvtc", "-name", "mutt", "-title", "Mail Client", "-e", "mutt", NULL };
static const char *weechat[]        = { "urxvtc", "-name", "weechat", "-title", "IRC Client", "-e", "weechat", NULL };
// -- info ---------------------------------------------------------
static const char *xprop[]          = { "system-utils", "xprop", NULL };
static const char *system_info[]    = { "system-utils", "info", NULL };
// -- volume control -----------------------------------------------
static const char *volume_up[]      = { "system-utils", "volume", "up", NULL };
static const char *volume_down[]    = { "system-utils", "volume", "down", NULL };
static const char *volume_toggle[]  = { "system-utils", "volume", "toggle", NULL };
// -- screenshot ---------------------------------------------------
static const char *screenshot[]     = { "system-utils", "printscreen", "all", NULL };
static const char *selectshot[]     = { "system-utils", "printscreen", "select", NULL };
// -- record my desktop --------------------------------------------
static const char *rec_desk[]       = { "system-utils", "recordmydesktop", "all", NULL };
static const char *rec_desk_mute[]  = { "system-utils", "recordmydesktop", "all", "mute", NULL };
static const char *rec_win[]        = { "system-utils", "recordmydesktop", "select", NULL };
static const char *rec_win_mute[]   = { "system-utils", "recordmydesktop", "select", "mute", NULL };
// -- cmus ---------------------------------------------------------
static const char *cmus[]           = { "urxvtc", "-name", "cmus", "-title", "C* Music Player", "-e", "cmus", NULL };
static const char *cmus_prev[]      = { "cmus-remote", "--prev", NULL };
static const char *cmus_next[]      = { "cmus-remote", "--next", NULL };
static const char *cmus_toggle[]    = { "cmus-remote", "--pause", NULL };
static const char *cmus_stop[]      = { "cmus-remote", "--stop", NULL };
static const char *cmus_clear[]     = { "cmus-remote", "--clear", NULL };
static const char *cmus_repeat[]    = { "cmus-remote", "--repeat", NULL };
static const char *cmus_repeatcur[] = { "cmus-remote", "--raw", "toggle repeat_current", NULL };
static const char *cmus_shuffle[]   = { "cmus-remote", "--shuffle", NULL };
static const char *cmus_volup[]     = { "cmus-remote", "--volume", "+2%", NULL };
static const char *cmus_voldown[]   = { "cmus-remote", "--volume", "-2%", NULL };
static const char *cmus_seekup[]    = { "cmus-remote", "--seek", "+10", NULL };
static const char *cmus_seekdown[]  = { "cmus-remote", "--seek", "-10", NULL };
// -- power management ---------------------------------------------
static const char *reboot[]         = { "systemctl", "reboot", NULL };
static const char *shutdown[]       = { "systemctl", "poweroff", NULL };

// mappings
static Key keys[] = {
    // modifier                     key             function    argument
    // -- dmenu --------------------------------------------------------
    { 0,                            0x1008ff1b,     spawn,      {.v = dmenucmd } },
    { 0,                            XK_Menu,        spawn,      {.v = dmenucmd } },
    { WinKey,                       XK_r,           spawn,      {.v = dmenucmd } },
    // -- terminal -----------------------------------------------------
    { WinKey,                       XK_Return,      spawn,      {.v = urxvt } },
    { WinKey,                       XK_t,           spawn,      {.v = tmux } },
    { WinKey|ShiftMask,             XK_t,           spawn,      {.v = xterm } },
    // -- web browser --------------------------------------------------
    { 0,                            0x1008ff18,     runorraise, {.v = firefox } },
    { WinKey,                       XK_w,           runorraise, {.v = firefox } },
    // -- file manager -------------------------------------------------
    { WinKey,                       XK_f,           spawn,      {.v = mc } },
    // -- processes ----------------------------------------------------
    { WinKey,                       XK_p,           spawn,      {.v = htop } },
    // -- mail client --------------------------------------------------
    { WinKey|ShiftMask,             XK_m,           spawn,      {.v = mutt } },
    // -- irc client ---------------------------------------------------
    { WinKey,                       XK_i,           spawn,      {.v = weechat } },
    // -- show information ---------------------------------------------
    { WinKey,                       XK_F1,          spawn,      {.v = system_info } },
    // -- volume control -----------------------------------------------
    { 0,                            0x1008ff13,     spawn,      {.v = volume_up } },
    { WinKey,                       XK_equal,       spawn,      {.v = volume_up } },
    { WinKey,                       XK_KP_Add,      spawn,      {.v = volume_up } },
    { 0,                            0x1008ff11,     spawn,      {.v = volume_down } },
    { WinKey,                       XK_minus,       spawn,      {.v = volume_down } },
    { WinKey,                       XK_KP_Subtract, spawn,      {.v = volume_down } },
    { 0,                            0x1008ff12,     spawn,      {.v = volume_toggle } },
    { WinKey,                       XK_BackSpace,   spawn,      {.v = volume_toggle } },
    { WinKey,                       XK_KP_Multiply, spawn,      {.v = volume_toggle } },
    // -- screenshots --------------------------------------------------
    { 0,                            XK_Print,       spawn,      {.v = screenshot } },
    { WinKey,                       XK_Print,       spawn,      {.v = selectshot } },
    // -- record desktop -----------------------------------------------
    { ControlMask,                  XK_Print,       spawn,      {.v = rec_desk } },
    { ControlMask|AltKey,           XK_Print,       spawn,      {.v = rec_desk_mute } },
    { ControlMask|WinKey,           XK_Print,       spawn,      {.v = rec_win } },
    { ControlMask|WinKey|AltKey,    XK_Print,       spawn,      {.v = rec_win_mute } },
    // -- xprop --------------------------------------------------------
    { WinKey,                       XK_slash,       spawn,      {.v = xprop } },
    // -- music --------------------------------------------------------
    { WinKey,                       XK_m,           spawn,      {.v = cmus } },
    { WinKey,                       XK_KP_Divide,   spawn,      {.v = cmus } },
    { 0,                            0x1008ff14,     spawn,      {.v = cmus_toggle } },
    { WinKey,                       XK_KP_8,        spawn,      {.v = cmus_toggle } },
    { WinKey,                       XK_KP_Up,       spawn,      {.v = cmus_toggle } },
    { WinKey,                       XK_KP_2,        spawn,      {.v = cmus_stop } },
    { WinKey,                       XK_KP_Down,     spawn,      {.v = cmus_stop } },
    { 0,                            0x1008ff16,     spawn,      {.v = cmus_prev } },
    { WinKey,                       XK_KP_4,        spawn,      {.v = cmus_prev } },
    { WinKey,                       XK_KP_Left,     spawn,      {.v = cmus_prev } },
    { 0,                            0x1008ff17,     spawn,      {.v = cmus_next } },
    { WinKey,                       XK_KP_6,        spawn,      {.v = cmus_next } },
    { WinKey,                       XK_KP_Right,    spawn,      {.v = cmus_next } },
    { WinKey,                       XK_KP_Decimal,  spawn,      {.v = cmus_clear } },
    { WinKey,                       XK_KP_Delete,   spawn,      {.v = cmus_clear } },
    { WinKey,                       XK_KP_5,        spawn,      {.v = cmus_repeatcur } },
    { WinKey,                       XK_KP_Begin,    spawn,      {.v = cmus_repeatcur } },
    { WinKey|ControlMask,           XK_KP_5,        spawn,      {.v = cmus_repeat } },
    { WinKey|ControlMask,           XK_KP_Begin,    spawn,      {.v = cmus_repeat } },
    { WinKey,                       XK_KP_0,        spawn,      {.v = cmus_shuffle } },
    { WinKey,                       XK_KP_Insert,   spawn,      {.v = cmus_shuffle } },
    { WinKey,                       XK_KP_9,        spawn,      {.v = cmus_volup } },
    { WinKey,                       XK_KP_Prior,    spawn,      {.v = cmus_volup } },
    { WinKey,                       XK_KP_7,        spawn,      {.v = cmus_voldown } },
    { WinKey,                       XK_KP_Home,     spawn,      {.v = cmus_voldown } },
    { WinKey,                       XK_KP_3,        spawn,      {.v = cmus_seekup } },
    { WinKey,                       XK_KP_Next,     spawn,      {.v = cmus_seekup } },
    { WinKey,                       XK_KP_1,        spawn,      {.v = cmus_seekdown } },
    { WinKey,                       XK_KP_End,      spawn,      {.v = cmus_seekdown } },
    // -- close window -------------------------------------------------
    { WinKey,                       XK_q,           killclient, {0} },
    // -- toggle workspace bar -----------------------------------------
    { WinKey,                       XK_b,           togglebar,  {0} },
    // -- toggle floating window ---------------------------------------
    { WinKey,                       XK_space,       togglefloating,	{0} },
    // -- set layout ---------------------------------------------------
    { WinKey,                       XK_F2,          setlayout,  {.v = &layouts[0]} },
    { WinKey,                       XK_F3,          setlayout,  {.v = &layouts[1]} },
    { WinKey,                       XK_F4,          setlayout,  {.v = &layouts[2]} },
    // -- make master --------------------------------------------------
    { WinKey|ShiftMask,             XK_Return,      zoom,       {0} },
    // -- manage master size -------------------------------------------
    { WinKey,                       XK_Left,        setmfact,   {.f = -0.05} },
    { WinKey,                       XK_h,           setmfact,   {.f = -0.05} },
    { WinKey,                       XK_Right,       setmfact,   {.f = +0.05} },
    { WinKey,                       XK_l,           setmfact,   {.f = +0.05} },
    // -- circle windows -----------------------------------------------
    { WinKey,                       XK_Up,          focusstack, {.i = -1} },
    { WinKey,                       XK_k,           focusstack, {.i = -1} },
    { AltKey,                       XK_Tab,         focusstack, {.i = +1} },
    { WinKey,                       XK_Down,        focusstack, {.i = +1} },
    { WinKey,                       XK_j,           focusstack, {.i = +1} },
    // -- manage clients in master area --------------------------------
    { WinKey,                       XK_bracketleft, incnmaster, {.i = -1} },
    { WinKey,                       XK_bracketright,incnmaster, {.i = +1} },
    // -- view last workspace ------------------------------------------
    { WinKey,                       XK_Tab,         view,       {0} },
    // -- view workspace -----------------------------------------------
    TAGKEYS(                        XK_1,                       0)
    TAGKEYS(                        XK_2,                       1)
    TAGKEYS(                        XK_3,                       2)
    TAGKEYS(                        XK_4,                       3)
    TAGKEYS(                        XK_5,                       4)
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
    // -- view all workspaces ------------------------------------------
    { WinKey,                       XK_0,           view,       {.ui = ~0 } },
    // -- make window omnipresent/stick --------------------------------
    { WinKey|AltKey,                XK_0,           tag,        {.ui = ~0 } },
    // -- dual head support --------------------------------------------
    { WinKey,                       XK_comma,       focusmon,   {.i = -1 } },
    { WinKey,                       XK_period,      focusmon,   {.i = +1 } },
    { WinKey|ShiftMask,             XK_comma,       tagmon,     {.i = -1 } },
    { WinKey|ShiftMask,             XK_period,      tagmon,     {.i = +1 } },
    // -- exit DWM -----------------------------------------------------
    { WinKey|ShiftMask,             XK_q,           quit,       {0} },
    // -- reboot computer ----------------------------------------------
    { ControlMask,                  XK_F12,         spawn,      {.v = reboot } },
    { AltKey|ControlMask,           XK_Delete,      spawn,      {.v = reboot } },
    // -- shutdown computer --------------------------------------------
    { ControlMask|ShiftMask,        XK_F12,         spawn,      {.v = shutdown } },
};

// button definitions
#define TAGBUTTONS(TAG) \
    { TAG,              0,              Button1,        view,           {.ui = 1 << TAG} }, \
    { TAG,              0,              Button3,        toggleview,     {.ui = 1 << TAG} }, \
    { TAG,              WinKey,         Button1,        tag,            {.ui = 1 << TAG} }, \
    { TAG,              AltKey,         Button1,        tag,            {.ui = 1 << TAG} }, \
    { TAG,              WinKey,         Button3,        toggletag,      {.ui = 1 << TAG} }, \
    { TAG,              AltKey,         Button3,        toggletag,      {.ui = 1 << TAG} },

/* click can be a tag number (starting at 0),
 * ClkTagBar, ClkLtSymbol, ClkWinTitle, ClkStatusText, ClkRootWin and ClkClientWin */
static Button buttons[] = {
    // click            event mask      button          function        argument
    // -- click on tag bar (workspaces) -----------------------------------------
    { ClkTagBar,        0,              Button1,        view,           {0} },
    { ClkTagBar,        ControlMask,    Button1,        toggleview,     {0} },
    { ClkTagBar,        0,              Button3,        toggleview,     {0} },
    { ClkTagBar,        WinKey,         Button1,        tag,            {0} },
    { ClkTagBar,        AltKey,         Button1,        tag,            {0} },
    { ClkTagBar,        WinKey,         Button3,        toggletag,      {0} },
    { ClkTagBar,        AltKey,         Button3,        toggletag,      {0} },
    { ClkTagBar,        0,              Button4,        shiftview,      {.i = -1 } },
    { ClkTagBar,        0,              Button5,        shiftview,      {.i = +1 } },
    // -- click on layout symbol set layouts ------------------------------------
    { ClkLtSymbol,      0,              Button1,        setlayout,      {.v = &layouts[0]} },
    { ClkLtSymbol,      0,              Button2,        setlayout,      {.v = &layouts[1]} },
    { ClkLtSymbol,      0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkLtSymbol,      0,              Button4,        setlayout,      {.v = &layouts[0]} },
    { ClkLtSymbol,      0,              Button5,        setlayout,      {.v = &layouts[0]} },
    // -- click on window title -------------------------------------------------
    { ClkWinTitle,      0,              Button1,        focusstack,     {.i = +1 } },
    { ClkWinTitle,      0,              Button2,        killclient,     {0} },
    { ClkWinTitle,      0,              Button3,        togglefloating, {0} },
    { ClkWinTitle,      0,              Button4,        focusstack,     {.i = -1 } },
    { ClkWinTitle,      0,              Button5,        focusstack,     {.i = +1 } },
    // -- click on status bar (clock,etc) ---------------------------------------
    { ClkStatusText,    0,              Button1,        spawn,          {.v = screenshot } },
    { ClkStatusText,    WinKey,         Button1,        spawn,          {.v = selectshot } },
    { ClkStatusText,    0,              Button3,        quit,           {0} },
    // -- click on root window (desktop/background) -----------------------------
    { ClkRootWin,       0,              Button3,        spawn,          {.v = urxvt } },
    // -- click on focused window -----------------------------------------------
    { ClkClientWin,     WinKey,         Button1,        movemouse,      {0} },
    { ClkClientWin,     AltKey,         Button1,        movemouse,      {0} },
    { ClkClientWin,     WinKey,         Button2,        togglefloating, {0} },
    { ClkClientWin,     AltKey,         Button2,        togglefloating, {0} },
    { ClkClientWin,     WinKey,         Button3,        resizemouse,    {0} },
    { ClkClientWin,     AltKey,         Button3,        resizemouse,    {0} },
};
