#ifndef __INTERFACE_KEYBOARD_H__
#define __INTERFACE_KEYBOARD_H__

enum
{
    KEYBOARD_MAP_BRITISH,
    KEYBOARD_MAP_DVORAK,
    KEYBOARD_MAP_RUSSIAN,
    KEYBOARD_MAP_SWEDISH,
    KEYBOARD_MAP_US,
};

enum
{
    KEYBOARD_SPECIAL_KEY_ESCAPE,
    KEYBOARD_SPECIAL_KEY_BACK_SPACE,
    KEYBOARD_SPECIAL_KEY_TAB,
    KEYBOARD_SPECIAL_KEY_ENTER,
    KEYBOARD_SPECIAL_KEY_LEFT_CONTROL,
    KEYBOARD_SPECIAL_KEY_RIGHT_CONTROL,
    KEYBOARD_SPECIAL_KEY_LEFT_SHIFT,
    KEYBOARD_SPECIAL_KEY_RIGHT_SHIFT,
    KEYBOARD_SPECIAL_KEY_PRINT_SCREEN,
    KEYBOARD_SPECIAL_KEY_LEFT_ALT,
    KEYBOARD_SPECIAL_KEY_RIGHT_ALT,
    KEYBOARD_SPECIAL_KEY_SPACE_BAR,
    KEYBOARD_SPECIAL_KEY_CAPS_LOCK,
    KEYBOARD_SPECIAL_KEY_F1,
    KEYBOARD_SPECIAL_KEY_F2,
    KEYBOARD_SPECIAL_KEY_F3,
    KEYBOARD_SPECIAL_KEY_F4,
    KEYBOARD_SPECIAL_KEY_F5, 
    KEYBOARD_SPECIAL_KEY_F6,
    KEYBOARD_SPECIAL_KEY_F7,
    KEYBOARD_SPECIAL_KEY_F8,
    KEYBOARD_SPECIAL_KEY_F9,
    KEYBOARD_SPECIAL_KEY_F10,
    KEYBOARD_SPECIAL_KEY_F11,
    KEYBOARD_SPECIAL_KEY_F12,
    KEYBOARD_SPECIAL_KEY_NUM_LOCK,
    KEYBOARD_SPECIAL_KEY_SCROLL_LOCK,
    KEYBOARD_SPECIAL_KEY_NUMERIC_7,
    KEYBOARD_SPECIAL_KEY_NUMERIC_8,
    KEYBOARD_SPECIAL_KEY_NUMERIC_9,
    KEYBOARD_SPECIAL_KEY_NUMERIC_MINUS,
    KEYBOARD_SPECIAL_KEY_NUMERIC_4,
    KEYBOARD_SPECIAL_KEY_NUMERIC_5,
    KEYBOARD_SPECIAL_KEY_NUMERIC_6,
    KEYBOARD_SPECIAL_KEY_NUMERIC_PLUS,
    KEYBOARD_SPECIAL_KEY_NUMERIC_1,
    KEYBOARD_SPECIAL_KEY_NUMERIC_2,
    KEYBOARD_SPECIAL_KEY_NUMERIC_3,
    KEYBOARD_SPECIAL_KEY_NUMERIC_0,
    KEYBOARD_SPECIAL_KEY_NUMERIC_DELETE,
    KEYBOARD_SPECIAL_KEY_NUMERIC_ENTER,
    KEYBOARD_SPECIAL_KEY_LEFT_WINDOWS,
    KEYBOARD_SPECIAL_KEY_RIGHT_WINDOWS,
    KEYBOARD_SPECIAL_KEY_MENU,

    KEYBOARD_SPECIAL_KEY_ARROW_UP    = KEYBOARD_SPECIAL_KEY_NUMERIC_8,
    KEYBOARD_SPECIAL_KEY_ARROW_DOWN  = KEYBOARD_SPECIAL_KEY_NUMERIC_2,
    KEYBOARD_SPECIAL_KEY_ARROW_LEFT  = KEYBOARD_SPECIAL_KEY_NUMERIC_4,
    KEYBOARD_SPECIAL_KEY_ARROW_RIGHT = KEYBOARD_SPECIAL_KEY_NUMERIC_6,

    KEYBOARD_SPECIAL_KEY_INSERT,
    KEYBOARD_SPECIAL_KEY_DELETE      = KEYBOARD_SPECIAL_KEY_NUMERIC_DELETE,

    KEYBOARD_SPECIAL_KEY_HOME,
    KEYBOARD_SPECIAL_KEY_END,
    KEYBOARD_SPECIAL_KEY_PAGE_UP,
    KEYBOARD_SPECIAL_KEY_PAGE_DOWN,

};

#endif /* !__INTERFACE_KEYBOARD_H__ */
