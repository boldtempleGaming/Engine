#include "LuaKeyboard.h"

void LuaKeyboard::bind(sol::state& lua){
    sol::table table = lua.create_named_table("Key");

    table["UNKNOWN"] = 0;

    table["A"] = 4;
    table["B"] = 5;
    table["C"] = 6;
    table["D"] = 7;
    table["E"] = 8;
    table["F"] = 9;
    table["G"] = 10;
    table["H"] = 11;
    table["I"] = 12;
    table["J"] = 13;
    table["K"] = 14;
    table["L"] = 15;
    table["M"] = 16;
    table["N"] = 17;
    table["O"] = 18;
    table["P"] = 19;
    table["Q"] = 20;
    table["R"] = 21;
    table["S"] = 22;
    table["T"] = 23;
    table["U"] = 24;
    table["V"] = 25;
    table["W"] = 26;
    table["X"] = 27;
    table["Y"] = 28;
    table["Z"] = 29;

    table["1"] = 30;
    table["2"] = 31;
    table["3"] = 32;
    table["4"] = 33;
    table["5"] = 34;
    table["6"] = 35;
    table["7"] = 36;
    table["8"] = 37;
    table["9"] = 38;
    table["0"] = 39;

    table["RETURN"] = 40;
    table["ESCAPE"] = 41;
    table["BACKSPACE"] = 42;
    table["TAB"] = 43;
    table["SPACE"] = 44;

    table["MINUS"] = 45;
    table["EQUALS"] = 46;
    table["LEFTBRACKET"] = 47;
    table["RIGHTBRACKET"] = 48;
    table["BACKSLASH"] = 49;
    table["NONUSHASH"] = 50;
    table["SEMICOLON"] = 51;
    table["APOSTROPHE"] = 52;
    table["GRAVE"] = 53;
    table["COMMA"] = 54;
    table["PERIOD"] = 55;
    table["SLASH"] = 56;

    table["CAPSLOCK"] = 57;

    table["F1"] = 58;
    table["F2"] = 59;
    table["F3"] = 60;
    table["F4"] = 61;
    table["F5"] = 62;
    table["F6"] = 63;
    table["F7"] = 64;
    table["F8"] = 65;
    table["F9"] = 66;
    table["F10"] = 67;
    table["F11"] = 68;
    table["F12"] = 69;

    table["PRINTSCREEN"] = 70;
    table["SCROLLLOCK"] = 71;
    table["PAUSE"] = 72;
    table["INSERT"] = 73;
    table["HOME"] = 74;
    table["PAGEUP"] = 75;
    table["DELETE"] = 76;
    table["END"] = 77;
    table["PAGEDOWN"] = 78;
    table["RIGHT"] = 79;
    table["LEFT"] = 80;
    table["DOWN"] = 81;
    table["UP"] = 82;

    table["NUMLOCKCLEAR"] = 83;
    table["KP_DIVIDE"] = 84;
    table["KP_MULTIPLY"] = 85;
    table["KP_MINUS"] = 86;
    table["KP_PLUS"] = 87;
    table["KP_ENTER"] = 88;
    table["KP_1"] = 89;
    table["KP_2"] = 90;
    table["KP_3"] = 91;
    table["KP_4"] = 92;
    table["KP_5"] = 93;
    table["KP_6"] = 94;
    table["KP_7"] = 95;
    table["KP_8"] = 96;
    table["KP_9"] = 97;
    table["KP_0"] = 98;
    table["KP_PERIOD"] = 99;

    table["NONUSBACKSLASH"] = 100;
    table["APPLICATION"] = 101;
    table["POWER"] = 102;
    table["KP_EQUALS"] = 103;
    table["F13"] = 104;
    table["F14"] = 105;
    table["F15"] = 106;
    table["F16"] = 107;
    table["F17"] = 108;
    table["F18"] = 109;
    table["F19"] = 110;
    table["F20"] = 111;
    table["F21"] = 112;
    table["F22"] = 113;
    table["F23"] = 114;
    table["F24"] = 115;
    table["EXECUTE"] = 116;
    table["HELP"] = 117;
    table["MENU"] = 118;
    table["SELECT"] = 119;
    table["STOP"] = 120;
    table["AGAIN"] = 121;
    table["UNDO"] = 122;
    table["CUT"] = 123;
    table["COPY"] = 124;
    table["PASTE"] = 125;
    table["FIND"] = 126;
    table["MUTE"] = 127;
    table["VOLUMEUP"] = 128;
    table["VOLUMEDOWN"] = 129;

    table["KP_COMMA"] = 133;
    table["KP_EQUALSAS400"] = 134;

    table["ALTERASE"] = 153;
    table["SYSREQ"] = 154;
    table["CANCEL"] = 155;
    table["CLEAR"] = 156;
    table["PRIOR"] = 157;
    table["RETURN2"] = 158;
    table["SEPARATOR"] = 159;
    table["OUT"] = 160;
    table["OPER"] = 161;
    table["CLEARAGAIN"] = 162;
    table["CRSEL"] = 163;
    table["EXSEL"] = 164;

    table["KP_00"] = 176;
    table["KP_000"] = 177;
    table["THOUSANDSSEPARATOR"] = 178;
    table["DECIMALSEPARATOR"] = 179;
    table["CURRENCYUNIT"] = 180;
    table["CURRENCYSUBUNIT"] = 181;
    table["KP_LEFTPAREN"] = 182;
    table["KP_RIGHTPAREN"] = 183;
    table["KP_LEFTBRACE"] = 184;
    table["KP_RIGHTBRACE"] = 185;
    table["KP_TAB"] = 186;
    table["KP_BACKSPACE"] = 187;
    table["KP_A"] = 188;
    table["KP_B"] = 189;
    table["KP_C"] = 190;
    table["KP_D"] = 191;
    table["KP_E"] = 192;
    table["KP_F"] = 193;
    table["KP_XOR"] = 194;
    table["KP_POWER"] = 195;
    table["KP_PERCENT"] = 196;
    table["KP_LESS"] = 197;
    table["KP_GREATER"] = 198;
    table["KP_AMPERSAND"] = 199;
    table["KP_DBLAMPERSAND"] = 200;
    table["KP_VERTICALBAR"] = 201;
    table["KP_DBLVERTICALBAR"] = 202;
    table["KP_COLON"] = 203;
    table["KP_HASH"] = 204;
    table["KP_SPACE"] = 205;
    table["KP_AT"] = 206;
    table["KP_EXCLAM"] = 207;
    table["KP_MEMSTORE"] = 208;
    table["KP_MEMRECALL"] = 209;
    table["KP_MEMCLEAR"] = 210;
    table["KP_MEMADD"] = 211;
    table["KP_MEMSUBTRACT"] = 212;
    table["KP_MEMMULTIPLY"] = 213;
    table["KP_MEMDIVIDE"] = 214;
    table["KP_PLUSMINUS"] = 215;
    table["KP_CLEAR"] = 216;
    table["KP_CLEARENTRY"] = 217;
    table["KP_BINARY"] = 218;
    table["KP_OCTAL"] = 219;
    table["KP_DECIMAL"] = 220;
    table["KP_HEXADECIMAL"] = 221;

    table["LCTRL"] = 224;
    table["LSHIFT"] = 225;
    table["LALT"] = 226;
    table["LGUI"] = 227;
    table["RCTRL"] = 228;
    table["RSHIFT"] = 229;
    table["RALT"] = 230;
    table["RGUI"] = 231;

    table["MODE"] = 257,

    table["AUDIONEXT"] = 258;
    table["AUDIOPREV"] = 259;
    table["AUDIOSTOP"] = 260;
    table["AUDIOPLAY"] = 261;
    table["AUDIOMUTE"] = 262;
    table["MEDIASELECT"] = 263;
    table["WWW"] = 264;
    table["MAIL"] = 265;
    table["CALCULATOR"] = 266;
    table["COMPUTER"] = 267;
    table["AC_SEARCH"] = 268;
    table["AC_HOME"] = 269;
    table["AC_BACK"] = 270;
    table["AC_FORWARD"] = 271;
    table["AC_STOP"] = 272;
    table["AC_REFRESH"] = 273;
    table["AC_BOOKMARKS"] = 274;

    lua.new_simple_usertype<Keyboard>("Keyboard",
        "isKeyDown", &Keyboard::isKeyDown
    );
}
