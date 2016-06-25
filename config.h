/* see LICENSE for copyright and license */

#ifndef CONFIG_H
#define CONFIG_H

/** modifiers **/
#define MOD1            Mod1Mask    /* ALT key */
#define MOD4            Mod4Mask    /* Super/Windows key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */

/** generic settings **/
#define MASTER_SIZE     0.50
#define SHOW_PANEL      True      /* show panel by default on exec */
#define TOP_PANEL       True      /* False means panel is on bottom */
#define PANEL_HEIGHT    24        /* 0 for no space for panel, thus no panel */
#define DEFAULT_MODE    FLOAT     /* initial layout/mode: TILE MONOCLE BSTACK GRID FLOAT */
#define ATTACH_ASIDE    True      /* False means new window is master */
#define FOLLOW_WINDOW   False     /* follow the window when moved to a different desktop */
#define FOLLOW_MONITOR  True      /* follow the window when moved to a different monitor */
#define FOLLOW_MOUSE    False     /* focus the window the mouse just entered */
#define CLICK_TO_FOCUS  True      /* focus an unfocused window when clicked  */
#define FOCUS_BUTTON    Button3   /* mouse button to be used along with CLICK_TO_FOCUS */
#define BORDER_WIDTH    4         /* window border width */
#define FOCUS           "#CC6666" /* focused window border color   */
#define UNFOCUS         "#373B41" /* unfocused window border color */
#define INFOCUS         "#5F819D" /* focused window border color on unfocused monitor */
#define MINWSZ          50        /* minimum window size in pixels */
#define DEFAULT_MONITOR 0         /* the monitor to focus initially */
#define DEFAULT_DESKTOP 0         /* the desktop to focus initially */
#define DESKTOPS        5         /* number of desktops - edit DESKTOPCHANGE keys to suit */
#define USELESSGAP      8         /* the size of the useless gap in pixels */
#define COVER_PANEL     False     /* full screen window covers panel or not */
#define MONOCLE_GAP     False     /* useless gap in monocle mode
                                   * set MONOCLE_BORDER to **True** before using this*/
#define MONOCLE_BORDER  True     /* window border in monocle mode */

struct ml {
    int m; /* monitor that the desktop in on  */
    int d; /* desktop which properties follow */
    struct {
        int mode;  /* layout mode for desktop d of monitor m    */
        int masz;  /* incread or decrease master area in px     */
        Bool sbar; /* whether or not to show panel on desktop d */
    } dl;
};

/**
 * define initial values for each monitor and dekstop properties
 *
 * in the example below:
 * - the first desktop (0) on the first monitor (0) will have
 *   tile layout, with its master area increased by 50px and
 *   the panel will be visible.
 * - the third desktop (2) on the second monitor (1) will have
 *   grid layout, with no changes to its master area and
 *   the panel will be hidden.
 */
static const struct ml init[] = { \
    /* monitor  desktop   mode  masz  sbar   */
    {     0,       0,   { TILE,  50,  True  } },
    {     0,       1,   { FLOAT, 50,  True  } },
    {     0,       2,   { FLOAT, 50,  True  } },
    {     0,       3,   { FLOAT, 50,  True  } },
    {     0,       4,   { FLOAT, 50,  True  } },
    {     1,       0,   { GRID,  50,  False } },
    {     1,       1,   { FLOAT, 50,  False } },
    {     1,       2,   { FLOAT, 50,  False } },
    {     1,       3,   { FLOAT, 50,  False } },
    {     1,       4,   { FLOAT, 50,  False } },
};

/**
 * open applications to specified monitor and desktop
 * with the specified properties.
 * if monitor is negative, then current is assumed
 * if desktop is negative, then current is assumed
 */
static const AppRule rules[] = { \
    /*  class     monitor  desktop  follow  float */
    { "MPlayer",     0,       3,    True,   False },
    { "Gimp",        0,       2,    False,  True  },
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/**
 * custom commands
 * must always end with ', NULL };'
 */
static const char *termcmd[] = { "urxvt", NULL };
// static const char *menucmd[] = { "dmenu_run", "-dim", "0.6", "-fn", "-gohu-gohufont-medium-r-normal--14-100-100-100-c-80-iso10646-1", "-h", "22", "-l", "16", "-w", "200", "-sb", "#823232", NULL };
static const char *menucmd[] = { "dmenu_run", "-dim", "0.6", "-fn", "monofur for Powerline-13:bold", "-h", "24", "-l", "16", "-w", "200", "-sb", "#3f3f3f", "-centerx", "-s", "0", NULL };

#define MONITORCHANGE(K,N) \
    {  MOD4,             K,              change_monitor, {.i = N}}, \
    {  MOD4|ShiftMask,   K,              client_to_monitor, {.i = N}},

#define DESKTOPCHANGE(K,N) \
    {  MOD1,             K,              change_desktop, {.i = N}}, \
    {  MOD1|ShiftMask,   K,              client_to_desktop, {.i = N}},

/**
 * keyboard shortcuts
 */
static Key keys[] = {
    /* modifier          key            function           argument */
    {  MOD1,             XK_b,          togglepanel,       {NULL}},
    {  MOD1,             XK_Delete,     focusurgent,       {NULL}},
    {  MOD1|MOD4,        XK_c,          killclient,        {NULL}},
    {  MOD4,             XK_c,          centerwindow,      {NULL}},
    {  MOD1,             XK_j,          next_win,          {NULL}},
    {  MOD1,             XK_k,          prev_win,          {NULL}},
    {  MOD1,             XK_h,          resize_master,     {.i = -10}}, /* decrease size in px */
    {  MOD1,             XK_l,          resize_master,     {.i = +10}}, /* increase size in px */
    {  MOD1,             XK_o,          resize_stack,      {.i = -10}}, /* shrink   size in px */
    {  MOD1,             XK_p,          resize_stack,      {.i = +10}}, /* grow     size in px */
    {  MOD1|CONTROL,     XK_h,          rotate,            {.i = -1}},
    {  MOD1|CONTROL,     XK_l,          rotate,            {.i = +1}},
    {  MOD1|MOD4,        XK_h,          rotate_filled,     {.i = -1}},
    {  MOD1|MOD4,        XK_l,          rotate_filled,     {.i = +1}},
    {  MOD1,             XK_Tab,        last_desktop,      {NULL}},
    {  MOD1,             XK_Return,     swap_master,       {NULL}},
    {  MOD1|MOD4,        XK_j,          move_down,         {NULL}},
    {  MOD1|MOD4,        XK_k,          move_up,           {NULL}},
    {  MOD1|MOD4,        XK_6,          switch_mode,       {.i = TILE}},
    {  MOD1|MOD4,        XK_7,          switch_mode,       {.i = MONOCLE}},
    {  MOD1|MOD4,        XK_9,          switch_mode,       {.i = BSTACK}},
    {  MOD1|MOD4,        XK_0,          switch_mode,       {.i = GRID}},
    {  MOD1|MOD4,        XK_8,          switch_mode,       {.i = FLOAT}},
    {  MOD1|CONTROL,     XK_r,          quit,              {.i = 0}}, /* quit with exit value 0 */
    {  MOD1|CONTROL,     XK_q,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  MOD1|SHIFT,       XK_Return,     spawn,             {.com = termcmd}},
    {  MOD4,             XK_m,          spawn,             {.com = menucmd}},
    {  MOD4,             XK_j,          moveresize,        {.v = (int []){   0,  2,   0,   0 }}}, /* move down  */
    {  MOD4,             XK_k,          moveresize,        {.v = (int []){   0, -2,   0,   0 }}}, /* move up    */
    {  MOD4,             XK_l,          moveresize,        {.v = (int []){  2,   0,   0,   0 }}}, /* move right */
    {  MOD4,             XK_h,          moveresize,        {.v = (int []){ -2,   0,   0,   0 }}}, /* move left  */
    {  CONTROL|SHIFT,    XK_j,          moveresize,        {.v = (int []){   0,   0,   0,  2 }}}, /* height grow   */
    {  CONTROL|SHIFT,    XK_k,          moveresize,        {.v = (int []){   0,   0,   0, -2 }}}, /* height shrink */
    {  CONTROL|SHIFT,    XK_l,          moveresize,        {.v = (int []){   0,   0,  2,   0 }}}, /* width grow    */
    {  CONTROL|SHIFT,    XK_h,          moveresize,        {.v = (int []){   0,   0, -2,   0 }}}, /* width shrink  */
    {  MOD4|SHIFT,       XK_j,          moveresize,        {.v = (int []){   0,  20,  0,   0 }}}, /* move down  */
    {  MOD4|SHIFT,       XK_k,          moveresize,        {.v = (int []){   0, -20,  0,   0 }}}, /* move up    */
    {  MOD4|SHIFT,       XK_l,          moveresize,        {.v = (int []){  20,  0,   0,   0 }}}, /* move right */
    {  MOD4|SHIFT,       XK_h,          moveresize,        {.v = (int []){ -20,  0,   0,   0 }}}, /* move left  */
    {  MOD4|CONTROL,     XK_j,          moveresize,        {.v = (int []){   0,   0,   0, 20 }}}, /* height grow   */
    {  MOD4|CONTROL,     XK_k,          moveresize,        {.v = (int []){   0,   0,   0,-20 }}}, /* height shrink */
    {  MOD4|CONTROL,     XK_l,          moveresize,        {.v = (int []){   0,   0,  20,   0 }}}, /* width grow    */
    {  MOD4|CONTROL,     XK_h,          moveresize,        {.v = (int []){   0,   0, -20,   0 }}}, /* width shrink  */
       DESKTOPCHANGE(    XK_1,                             0)
       DESKTOPCHANGE(    XK_2,                             1)
       DESKTOPCHANGE(    XK_3,                             2)
       DESKTOPCHANGE(    XK_4,                             3)
       DESKTOPCHANGE(    XK_5,                             4)
       MONITORCHANGE(    XK_1,                             0)
       MONITORCHANGE(    XK_2,                             1)
};

/**
 * mouse shortcuts
 */
static Button buttons[] = {
    {  MOD1,    Button1,     mousemotion,   {.i = MOVE}},
    {  MOD1,    Button3,     mousemotion,   {.i = RESIZE}},
};
#endif

/* vim: set expandtab ts=4 sts=4 sw=4 : */
