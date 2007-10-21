#include "gbm.h"
#include "gbmmap.h"
#include "gbmxpmcn.h"

#include <string.h>

#define MakeRGB(r,g,b)  (((dword) r) | ((dword) g << 8) | ((dword) b << 16))
#define GetR(rgb)       ((rgb)         & 0xff)
#define GetG(rgb)       (((rgb) >> 8)  & 0xff)
#define GetB(rgb)       (((rgb) >> 16) & 0xff)


struct GBM_XPM_RGB_NAMES_T
{
    const dword        rgb;
    const char * const name;
};

/* X Consortium: rgb.txt,v 10.41 94/02/20 */

static const struct GBM_XPM_RGB_NAMES_T GBM_XPM_RGB_NAMES[] =
{
    MakeRGB( 255, 250, 250 ), "snow",
    MakeRGB( 248, 248, 255 ), "ghost_white",
    MakeRGB( 248, 248, 255 ), "GhostWhite",
    MakeRGB( 245, 245, 245 ), "white_smoke",
    MakeRGB( 245, 245, 245 ), "WhiteSmoke",
    MakeRGB( 220, 220, 220 ), "gainsboro",
    MakeRGB( 255, 250, 240 ), "floral_white",
    MakeRGB( 255, 250, 240 ), "FloralWhite",
    MakeRGB( 253, 245, 230 ), "old_lace",
    MakeRGB( 253, 245, 230 ), "OldLace",
    MakeRGB( 250, 240, 230 ), "linen",
    MakeRGB( 250, 235, 215 ), "antique_white",
    MakeRGB( 250, 235, 215 ), "AntiqueWhite",
    MakeRGB( 255, 239, 213 ), "papaya_whip",
    MakeRGB( 255, 239, 213 ), "PapayaWhip",
    MakeRGB( 255, 235, 205 ), "blanched_almond",
    MakeRGB( 255, 235, 205 ), "BlanchedAlmond",
    MakeRGB( 255, 228, 196 ), "bisque",
    MakeRGB( 255, 218, 185 ), "peach_puff",
    MakeRGB( 255, 218, 185 ), "PeachPuff",
    MakeRGB( 255, 222, 173 ), "navajo_white",
    MakeRGB( 255, 222, 173 ), "NavajoWhite",
    MakeRGB( 255, 228, 181 ), "moccasin",
    MakeRGB( 255, 248, 220 ), "cornsilk",
    MakeRGB( 255, 255, 240 ), "ivory",
    MakeRGB( 255, 250, 205 ), "lemon_chiffon",
    MakeRGB( 255, 250, 205 ), "LemonChiffon",
    MakeRGB( 255, 245, 238 ), "seashell",
    MakeRGB( 240, 255, 240 ), "honeydew",
    MakeRGB( 245, 255, 250 ), "mint_cream",
    MakeRGB( 245, 255, 250 ), "MintCream",
    MakeRGB( 240, 255, 255 ), "azure",
    MakeRGB( 240, 248, 255 ), "alice_blue",
    MakeRGB( 240, 248, 255 ), "AliceBlue",
    MakeRGB( 230, 230, 250 ), "lavender",
    MakeRGB( 255, 240, 245 ), "lavender_blush",
    MakeRGB( 255, 240, 245 ), "LavenderBlush",
    MakeRGB( 255, 228, 225 ), "misty_rose",
    MakeRGB( 255, 228, 225 ), "MistyRose",
    MakeRGB( 255, 255, 255 ), "white",
    MakeRGB(   0,   0,   0 ), "black",
    MakeRGB(  47,  79,  79 ), "dark_slate_gray",
    MakeRGB(  47,  79,  79 ), "DarkSlateGray",
    MakeRGB(  47,  79,  79 ), "dark_slate_grey",
    MakeRGB(  47,  79,  79 ), "DarkSlateGrey",
    MakeRGB( 105, 105, 105 ), "dim_gray",
    MakeRGB( 105, 105, 105 ), "DimGray",
    MakeRGB( 105, 105, 105 ), "dim_grey",
    MakeRGB( 105, 105, 105 ), "DimGrey",
    MakeRGB( 112, 128, 144 ), "slate_gray",
    MakeRGB( 112, 128, 144 ), "SlateGray",
    MakeRGB( 112, 128, 144 ), "slate_grey",
    MakeRGB( 112, 128, 144 ), "SlateGrey",
    MakeRGB( 119, 136, 153 ), "light_slate_gray",
    MakeRGB( 119, 136, 153 ), "LightSlateGray",
    MakeRGB( 119, 136, 153 ), "light_slate_grey",
    MakeRGB( 119, 136, 153 ), "LightSlateGrey",
    MakeRGB( 190, 190, 190 ), "gray",
    MakeRGB( 190, 190, 190 ), "grey",
    MakeRGB( 211, 211, 211 ), "light_grey",
    MakeRGB( 211, 211, 211 ), "LightGrey",
    MakeRGB( 211, 211, 211 ), "light_gray",
    MakeRGB( 211, 211, 211 ), "LightGray",
    MakeRGB(  25,  25, 112 ), "midnight_blue",
    MakeRGB(  25,  25, 112 ), "MidnightBlue",
    MakeRGB(   0,   0, 128 ), "navy",
    MakeRGB(   0,   0, 128 ), "navy_blue",
    MakeRGB(   0,   0, 128 ), "NavyBlue",
    MakeRGB( 100, 149, 237 ), "cornflower_blue",
    MakeRGB( 100, 149, 237 ), "CornflowerBlue",
    MakeRGB(  72,  61, 139 ), "dark_slate_blue",
    MakeRGB(  72,  61, 139 ), "DarkSlateBlue",
    MakeRGB( 106,  90, 205 ), "slate_blue",
    MakeRGB( 106,  90, 205 ), "SlateBlue",
    MakeRGB( 123, 104, 238 ), "medium_slate_blue",
    MakeRGB( 123, 104, 238 ), "MediumSlateBlue",
    MakeRGB( 132, 112, 255 ), "light_slate_blue",
    MakeRGB( 132, 112, 255 ), "LightSlateBlue",
    MakeRGB(   0,   0, 205 ), "medium_blue",
    MakeRGB(   0,   0, 205 ), "MediumBlue",
    MakeRGB(  65, 105, 225 ), "royal_blue",
    MakeRGB(  65, 105, 225 ), "RoyalBlue",
    MakeRGB(   0,   0, 255 ), "blue",
    MakeRGB(  30, 144, 255 ), "dodger_blue",
    MakeRGB(  30, 144, 255 ), "DodgerBlue",
    MakeRGB(   0, 191, 255 ), "deep_sky_blue",
    MakeRGB(   0, 191, 255 ), "DeepSkyBlue",
    MakeRGB( 135, 206, 235 ), "sky_blue",
    MakeRGB( 135, 206, 235 ), "SkyBlue",
    MakeRGB( 135, 206, 250 ), "light_sky_blue",
    MakeRGB( 135, 206, 250 ), "LightSkyBlue",
    MakeRGB(  70, 130, 180 ), "steel_blue",
    MakeRGB(  70, 130, 180 ), "SteelBlue",
    MakeRGB( 176, 196, 222 ), "light_steel_blue",
    MakeRGB( 176, 196, 222 ), "LightSteelBlue",
    MakeRGB( 173, 216, 230 ), "light_blue",
    MakeRGB( 173, 216, 230 ), "LightBlue",
    MakeRGB( 176, 224, 230 ), "powder_blue",
    MakeRGB( 176, 224, 230 ), "PowderBlue",
    MakeRGB( 175, 238, 238 ), "pale_turquoise",
    MakeRGB( 175, 238, 238 ), "PaleTurquoise",
    MakeRGB(   0, 206, 209 ), "dark_turquoise",
    MakeRGB(   0, 206, 209 ), "DarkTurquoise",
    MakeRGB(  72, 209, 204 ), "medium_turquoise",
    MakeRGB(  72, 209, 204 ), "MediumTurquoise",
    MakeRGB(  64, 224, 208 ), "turquoise",
    MakeRGB(   0, 255, 255 ), "cyan",
    MakeRGB( 224, 255, 255 ), "light_cyan",
    MakeRGB( 224, 255, 255 ), "LightCyan",
    MakeRGB(  95, 158, 160 ), "cadet_blue",
    MakeRGB(  95, 158, 160 ), "CadetBlue",
    MakeRGB( 102, 205, 170 ), "medium_aquamarine",
    MakeRGB( 102, 205, 170 ), "MediumAquamarine",
    MakeRGB( 127, 255, 212 ), "aquamarine",
    MakeRGB(   0, 100,   0 ), "dark_green",
    MakeRGB(   0, 100,   0 ), "DarkGreen",
    MakeRGB(  85, 107,  47 ), "dark_olive_green",
    MakeRGB(  85, 107,  47 ), "DarkOliveGreen",
    MakeRGB( 143, 188, 143 ), "dark_sea_green",
    MakeRGB( 143, 188, 143 ), "DarkSeaGreen",
    MakeRGB(  46, 139,  87 ), "sea_green",
    MakeRGB(  46, 139,  87 ), "SeaGreen",
    MakeRGB(  60, 179, 113 ), "medium_sea_green",
    MakeRGB(  60, 179, 113 ), "MediumSeaGreen",
    MakeRGB(  32, 178, 170 ), "light_sea_green",
    MakeRGB(  32, 178, 170 ), "LightSeaGreen",
    MakeRGB( 152, 251, 152 ), "pale_green",
    MakeRGB( 152, 251, 152 ), "PaleGreen",
    MakeRGB(   0, 255, 127 ), "spring_green",
    MakeRGB(   0, 255, 127 ), "SpringGreen",
    MakeRGB( 124, 252,   0 ), "lawn_green",
    MakeRGB( 124, 252,   0 ), "LawnGreen",
    MakeRGB(   0, 255,   0 ), "green",
    MakeRGB( 127, 255,   0 ), "chartreuse",
    MakeRGB(   0, 250, 154 ), "medium_spring_green",
    MakeRGB(   0, 250, 154 ), "MediumSpringGreen",
    MakeRGB( 173, 255,  47 ), "green_yellow",
    MakeRGB( 173, 255,  47 ), "GreenYellow",
    MakeRGB(  50, 205,  50 ), "lime_green",
    MakeRGB(  50, 205,  50 ), "LimeGreen",
    MakeRGB( 154, 205,  50 ), "yellow_green",
    MakeRGB( 154, 205,  50 ), "YellowGreen",
    MakeRGB(  34, 139,  34 ), "forest_green",
    MakeRGB(  34, 139,  34 ), "ForestGreen",
    MakeRGB( 107, 142,  35 ), "olive_drab",
    MakeRGB( 107, 142,  35 ), "OliveDrab",
    MakeRGB( 189, 183, 107 ), "dark_khaki",
    MakeRGB( 189, 183, 107 ), "DarkKhaki",
    MakeRGB( 240, 230, 140 ), "khaki",
    MakeRGB( 238, 232, 170 ), "pale_goldenrod",
    MakeRGB( 238, 232, 170 ), "PaleGoldenrod",
    MakeRGB( 250, 250, 210 ), "light_goldenrod yellow",
    MakeRGB( 250, 250, 210 ), "LightGoldenrodYellow",
    MakeRGB( 255, 255, 224 ), "light_yellow",
    MakeRGB( 255, 255, 224 ), "LightYellow",
    MakeRGB( 255, 255,   0 ), "yellow",
    MakeRGB( 255, 215,   0 ), "gold",
    MakeRGB( 238, 221, 130 ), "light_goldenrod",
    MakeRGB( 238, 221, 130 ), "LightGoldenrod",
    MakeRGB( 218, 165,  32 ), "goldenrod",
    MakeRGB( 184, 134,  11 ), "dark_goldenrod",
    MakeRGB( 184, 134,  11 ), "DarkGoldenrod",
    MakeRGB( 188, 143, 143 ), "rosy_brown",
    MakeRGB( 188, 143, 143 ), "RosyBrown",
    MakeRGB( 205,  92,  92 ), "indian_red",
    MakeRGB( 205,  92,  92 ), "IndianRed",
    MakeRGB( 139,  69,  19 ), "saddle_brown",
    MakeRGB( 139,  69,  19 ), "SaddleBrown",
    MakeRGB( 160,  82,  45 ), "sienna",
    MakeRGB( 205, 133,  63 ), "peru",
    MakeRGB( 222, 184, 135 ), "burlywood",
    MakeRGB( 245, 245, 220 ), "beige",
    MakeRGB( 245, 222, 179 ), "wheat",
    MakeRGB( 244, 164,  96 ), "sandy_brown",
    MakeRGB( 244, 164,  96 ), "SandyBrown",
    MakeRGB( 210, 180, 140 ), "tan",
    MakeRGB( 210, 105,  30 ), "chocolate",
    MakeRGB( 178,  34,  34 ), "firebrick",
    MakeRGB( 165,  42,  42 ), "brown",
    MakeRGB( 233, 150, 122 ), "dark_salmon",
    MakeRGB( 233, 150, 122 ), "DarkSalmon",
    MakeRGB( 250, 128, 114 ), "salmon",
    MakeRGB( 255, 160, 122 ), "light_salmon",
    MakeRGB( 255, 160, 122 ), "LightSalmon",
    MakeRGB( 255, 165,   0 ), "orange",
    MakeRGB( 255, 140,   0 ), "dark_orange",
    MakeRGB( 255, 140,   0 ), "DarkOrange",
    MakeRGB( 255, 127,  80 ), "coral",
    MakeRGB( 240, 128, 128 ), "light_coral",
    MakeRGB( 240, 128, 128 ), "LightCoral",
    MakeRGB( 255,  99,  71 ), "tomato",
    MakeRGB( 255,  69,   0 ), "orange_red",
    MakeRGB( 255,  69,   0 ), "OrangeRed",
    MakeRGB( 255,   0,   0 ), "red",
    MakeRGB( 255, 105, 180 ), "hot_pink",
    MakeRGB( 255, 105, 180 ), "HotPink",
    MakeRGB( 255,  20, 147 ), "deep_pink",
    MakeRGB( 255,  20, 147 ), "DeepPink",
    MakeRGB( 255, 192, 203 ), "pink",
    MakeRGB( 255, 182, 193 ), "light_pink",
    MakeRGB( 255, 182, 193 ), "LightPink",
    MakeRGB( 219, 112, 147 ), "pale_violet_red",
    MakeRGB( 219, 112, 147 ), "PaleVioletRed",
    MakeRGB( 176,  48,  96 ), "maroon",
    MakeRGB( 199,  21, 133 ), "medium_violet_red",
    MakeRGB( 199,  21, 133 ), "MediumVioletRed",
    MakeRGB( 208,  32, 144 ), "violet_red",
    MakeRGB( 208,  32, 144 ), "VioletRed",
    MakeRGB( 255,   0, 255 ), "magenta",
    MakeRGB( 238, 130, 238 ), "violet",
    MakeRGB( 221, 160, 221 ), "plum",
    MakeRGB( 218, 112, 214 ), "orchid",
    MakeRGB( 186,  85, 211 ), "medium_orchid",
    MakeRGB( 186,  85, 211 ), "MediumOrchid",
    MakeRGB( 153,  50, 204 ), "dark_orchid",
    MakeRGB( 153,  50, 204 ), "DarkOrchid",
    MakeRGB( 148,   0, 211 ), "dark_violet",
    MakeRGB( 148,   0, 211 ), "DarkViolet",
    MakeRGB( 138,  43, 226 ), "blue_violet",
    MakeRGB( 138,  43, 226 ), "BlueViolet",
    MakeRGB( 160,  32, 240 ), "purple",
    MakeRGB( 147, 112, 219 ), "medium_purple",
    MakeRGB( 147, 112, 219 ), "MediumPurple",
    MakeRGB( 216, 191, 216 ), "thistle",
    MakeRGB( 255, 250, 250 ), "snow1",
    MakeRGB( 238, 233, 233 ), "snow2",
    MakeRGB( 205, 201, 201 ), "snow3",
    MakeRGB( 139, 137, 137 ), "snow4",
    MakeRGB( 255, 245, 238 ), "seashell1",
    MakeRGB( 238, 229, 222 ), "seashell2",
    MakeRGB( 205, 197, 191 ), "seashell3",
    MakeRGB( 139, 134, 130 ), "seashell4",
    MakeRGB( 255, 239, 219 ), "AntiqueWhite1",
    MakeRGB( 238, 223, 204 ), "AntiqueWhite2",
    MakeRGB( 205, 192, 176 ), "AntiqueWhite3",
    MakeRGB( 139, 131, 120 ), "AntiqueWhite4",
    MakeRGB( 255, 228, 196 ), "bisque1",
    MakeRGB( 238, 213, 183 ), "bisque2",
    MakeRGB( 205, 183, 158 ), "bisque3",
    MakeRGB( 139, 125, 107 ), "bisque4",
    MakeRGB( 255, 218, 185 ), "PeachPuff1",
    MakeRGB( 238, 203, 173 ), "PeachPuff2",
    MakeRGB( 205, 175, 149 ), "PeachPuff3",
    MakeRGB( 139, 119, 101 ), "PeachPuff4",
    MakeRGB( 255, 222, 173 ), "NavajoWhite1",
    MakeRGB( 238, 207, 161 ), "NavajoWhite2",
    MakeRGB( 205, 179, 139 ), "NavajoWhite3",
    MakeRGB( 139, 121,  94 ), "NavajoWhite4",
    MakeRGB( 255, 250, 205 ), "LemonChiffon1",
    MakeRGB( 238, 233, 191 ), "LemonChiffon2",
    MakeRGB( 205, 201, 165 ), "LemonChiffon3",
    MakeRGB( 139, 137, 112 ), "LemonChiffon4",
    MakeRGB( 255, 248, 220 ), "cornsilk1",
    MakeRGB( 238, 232, 205 ), "cornsilk2",
    MakeRGB( 205, 200, 177 ), "cornsilk3",
    MakeRGB( 139, 136, 120 ), "cornsilk4",
    MakeRGB( 255, 255, 240 ), "ivory1",
    MakeRGB( 238, 238, 224 ), "ivory2",
    MakeRGB( 205, 205, 193 ), "ivory3",
    MakeRGB( 139, 139, 131 ), "ivory4",
    MakeRGB( 240, 255, 240 ), "honeydew1",
    MakeRGB( 224, 238, 224 ), "honeydew2",
    MakeRGB( 193, 205, 193 ), "honeydew3",
    MakeRGB( 131, 139, 131 ), "honeydew4",
    MakeRGB( 255, 240, 245 ), "LavenderBlush1",
    MakeRGB( 238, 224, 229 ), "LavenderBlush2",
    MakeRGB( 205, 193, 197 ), "LavenderBlush3",
    MakeRGB( 139, 131, 134 ), "LavenderBlush4",
    MakeRGB( 255, 228, 225 ), "MistyRose1",
    MakeRGB( 238, 213, 210 ), "MistyRose2",
    MakeRGB( 205, 183, 181 ), "MistyRose3",
    MakeRGB( 139, 125, 123 ), "MistyRose4",
    MakeRGB( 240, 255, 255 ), "azure1",
    MakeRGB( 224, 238, 238 ), "azure2",
    MakeRGB( 193, 205, 205 ), "azure3",
    MakeRGB( 131, 139, 139 ), "azure4",
    MakeRGB( 131, 111, 255 ), "SlateBlue1",
    MakeRGB( 122, 103, 238 ), "SlateBlue2",
    MakeRGB( 105,  89, 205 ), "SlateBlue3",
    MakeRGB(  71,  60, 139 ), "SlateBlue4",
    MakeRGB(  72, 118, 255 ), "RoyalBlue1",
    MakeRGB(  67, 110, 238 ), "RoyalBlue2",
    MakeRGB(  58,  95, 205 ), "RoyalBlue3",
    MakeRGB(  39,  64, 139 ), "RoyalBlue4",
    MakeRGB(   0,   0, 255 ), "blue1",
    MakeRGB(   0,   0, 238 ), "blue2",
    MakeRGB(   0,   0, 205 ), "blue3",
    MakeRGB(   0,   0, 139 ), "blue4",
    MakeRGB(  30, 144, 255 ), "DodgerBlue1",
    MakeRGB(  28, 134, 238 ), "DodgerBlue2",
    MakeRGB(  24, 116, 205 ), "DodgerBlue3",
    MakeRGB(  16,  78, 139 ), "DodgerBlue4",
    MakeRGB(  99, 184, 255 ), "SteelBlue1",
    MakeRGB(  92, 172, 238 ), "SteelBlue2",
    MakeRGB(  79, 148, 205 ), "SteelBlue3",
    MakeRGB(  54, 100, 139 ), "SteelBlue4",
    MakeRGB(   0, 191, 255 ), "DeepSkyBlue1",
    MakeRGB(   0, 178, 238 ), "DeepSkyBlue2",
    MakeRGB(   0, 154, 205 ), "DeepSkyBlue3",
    MakeRGB(   0, 104, 139 ), "DeepSkyBlue4",
    MakeRGB( 135, 206, 255 ), "SkyBlue1",
    MakeRGB( 126, 192, 238 ), "SkyBlue2",
    MakeRGB( 108, 166, 205 ), "SkyBlue3",
    MakeRGB(  74, 112, 139 ), "SkyBlue4",
    MakeRGB( 176, 226, 255 ), "LightSkyBlue1",
    MakeRGB( 164, 211, 238 ), "LightSkyBlue2",
    MakeRGB( 141, 182, 205 ), "LightSkyBlue3",
    MakeRGB(  96, 123, 139 ), "LightSkyBlue4",
    MakeRGB( 198, 226, 255 ), "SlateGray1",
    MakeRGB( 185, 211, 238 ), "SlateGray2",
    MakeRGB( 159, 182, 205 ), "SlateGray3",
    MakeRGB( 108, 123, 139 ), "SlateGray4",
    MakeRGB( 202, 225, 255 ), "LightSteelBlue1",
    MakeRGB( 188, 210, 238 ), "LightSteelBlue2",
    MakeRGB( 162, 181, 205 ), "LightSteelBlue3",
    MakeRGB( 110, 123, 139 ), "LightSteelBlue4",
    MakeRGB( 191, 239, 255 ), "LightBlue1",
    MakeRGB( 178, 223, 238 ), "LightBlue2",
    MakeRGB( 154, 192, 205 ), "LightBlue3",
    MakeRGB( 104, 131, 139 ), "LightBlue4",
    MakeRGB( 224, 255, 255 ), "LightCyan1",
    MakeRGB( 209, 238, 238 ), "LightCyan2",
    MakeRGB( 180, 205, 205 ), "LightCyan3",
    MakeRGB( 122, 139, 139 ), "LightCyan4",
    MakeRGB( 187, 255, 255 ), "PaleTurquoise1",
    MakeRGB( 174, 238, 238 ), "PaleTurquoise2",
    MakeRGB( 150, 205, 205 ), "PaleTurquoise3",
    MakeRGB( 102, 139, 139 ), "PaleTurquoise4",
    MakeRGB( 152, 245, 255 ), "CadetBlue1",
    MakeRGB( 142, 229, 238 ), "CadetBlue2",
    MakeRGB( 122, 197, 205 ), "CadetBlue3",
    MakeRGB(  83, 134, 139 ), "CadetBlue4",
    MakeRGB(   0, 245, 255 ), "turquoise1",
    MakeRGB(   0, 229, 238 ), "turquoise2",
    MakeRGB(   0, 197, 205 ), "turquoise3",
    MakeRGB(   0, 134, 139 ), "turquoise4",
    MakeRGB(   0, 255, 255 ), "cyan1",
    MakeRGB(   0, 238, 238 ), "cyan2",
    MakeRGB(   0, 205, 205 ), "cyan3",
    MakeRGB(   0, 139, 139 ), "cyan4",
    MakeRGB( 151, 255, 255 ), "DarkSlateGray1",
    MakeRGB( 141, 238, 238 ), "DarkSlateGray2",
    MakeRGB( 121, 205, 205 ), "DarkSlateGray3",
    MakeRGB(  82, 139, 139 ), "DarkSlateGray4",
    MakeRGB( 127, 255, 212 ), "aquamarine1",
    MakeRGB( 118, 238, 198 ), "aquamarine2",
    MakeRGB( 102, 205, 170 ), "aquamarine3",
    MakeRGB(  69, 139, 116 ), "aquamarine4",
    MakeRGB( 193, 255, 193 ), "DarkSeaGreen1",
    MakeRGB( 180, 238, 180 ), "DarkSeaGreen2",
    MakeRGB( 155, 205, 155 ), "DarkSeaGreen3",
    MakeRGB( 105, 139, 105 ), "DarkSeaGreen4",
    MakeRGB(  84, 255, 159 ), "SeaGreen1",
    MakeRGB(  78, 238, 148 ), "SeaGreen2",
    MakeRGB(  67, 205, 128 ), "SeaGreen3",
    MakeRGB(  46, 139,  87 ), "SeaGreen4",
    MakeRGB( 154, 255, 154 ), "PaleGreen1",
    MakeRGB( 144, 238, 144 ), "PaleGreen2",
    MakeRGB( 124, 205, 124 ), "PaleGreen3",
    MakeRGB(  84, 139,  84 ), "PaleGreen4",
    MakeRGB(   0, 255, 127 ), "SpringGreen1",
    MakeRGB(   0, 238, 118 ), "SpringGreen2",
    MakeRGB(   0, 205, 102 ), "SpringGreen3",
    MakeRGB(   0, 139,  69 ), "SpringGreen4",
    MakeRGB(   0, 255,   0 ), "green1",
    MakeRGB(   0, 238,   0 ), "green2",
    MakeRGB(   0, 205,   0 ), "green3",
    MakeRGB(   0, 139,   0 ), "green4",
    MakeRGB( 127, 255,   0 ), "chartreuse1",
    MakeRGB( 118, 238,   0 ), "chartreuse2",
    MakeRGB( 102, 205,   0 ), "chartreuse3",
    MakeRGB(  69, 139,   0 ), "chartreuse4",
    MakeRGB( 192, 255,  62 ), "OliveDrab1",
    MakeRGB( 179, 238,  58 ), "OliveDrab2",
    MakeRGB( 154, 205,  50 ), "OliveDrab3",
    MakeRGB( 105, 139,  34 ), "OliveDrab4",
    MakeRGB( 202, 255, 112 ), "DarkOliveGreen1",
    MakeRGB( 188, 238, 104 ), "DarkOliveGreen2",
    MakeRGB( 162, 205,  90 ), "DarkOliveGreen3",
    MakeRGB( 110, 139,  61 ), "DarkOliveGreen4",
    MakeRGB( 255, 246, 143 ), "khaki1",
    MakeRGB( 238, 230, 133 ), "khaki2",
    MakeRGB( 205, 198, 115 ), "khaki3",
    MakeRGB( 139, 134,  78 ), "khaki4",
    MakeRGB( 255, 236, 139 ), "LightGoldenrod1",
    MakeRGB( 238, 220, 130 ), "LightGoldenrod2",
    MakeRGB( 205, 190, 112 ), "LightGoldenrod3",
    MakeRGB( 139, 129,  76 ), "LightGoldenrod4",
    MakeRGB( 255, 255, 224 ), "LightYellow1",
    MakeRGB( 238, 238, 209 ), "LightYellow2",
    MakeRGB( 205, 205, 180 ), "LightYellow3",
    MakeRGB( 139, 139, 122 ), "LightYellow4",
    MakeRGB( 255, 255,   0 ), "yellow1",
    MakeRGB( 238, 238,   0 ), "yellow2",
    MakeRGB( 205, 205,   0 ), "yellow3",
    MakeRGB( 139, 139,   0 ), "yellow4",
    MakeRGB( 255, 215,   0 ), "gold1",
    MakeRGB( 238, 201,   0 ), "gold2",
    MakeRGB( 205, 173,   0 ), "gold3",
    MakeRGB( 139, 117,   0 ), "gold4",
    MakeRGB( 255, 193,  37 ), "goldenrod1",
    MakeRGB( 238, 180,  34 ), "goldenrod2",
    MakeRGB( 205, 155,  29 ), "goldenrod3",
    MakeRGB( 139, 105,  20 ), "goldenrod4",
    MakeRGB( 255, 185,  15 ), "DarkGoldenrod1",
    MakeRGB( 238, 173,  14 ), "DarkGoldenrod2",
    MakeRGB( 205, 149,  12 ), "DarkGoldenrod3",
    MakeRGB( 139, 101,   8 ), "DarkGoldenrod4",
    MakeRGB( 255, 193, 193 ), "RosyBrown1",
    MakeRGB( 238, 180, 180 ), "RosyBrown2",
    MakeRGB( 205, 155, 155 ), "RosyBrown3",
    MakeRGB( 139, 105, 105 ), "RosyBrown4",
    MakeRGB( 255, 106, 106 ), "IndianRed1",
    MakeRGB( 238,  99,  99 ), "IndianRed2",
    MakeRGB( 205,  85,  85 ), "IndianRed3",
    MakeRGB( 139,  58,  58 ), "IndianRed4",
    MakeRGB( 255, 130,  71 ), "sienna1",
    MakeRGB( 238, 121,  66 ), "sienna2",
    MakeRGB( 205, 104,  57 ), "sienna3",
    MakeRGB( 139,  71,  38 ), "sienna4",
    MakeRGB( 255, 211, 155 ), "burlywood1",
    MakeRGB( 238, 197, 145 ), "burlywood2",
    MakeRGB( 205, 170, 125 ), "burlywood3",
    MakeRGB( 139, 115,  85 ), "burlywood4",
    MakeRGB( 255, 231, 186 ), "wheat1",
    MakeRGB( 238, 216, 174 ), "wheat2",
    MakeRGB( 205, 186, 150 ), "wheat3",
    MakeRGB( 139, 126, 102 ), "wheat4",
    MakeRGB( 255, 165,  79 ), "tan1",
    MakeRGB( 238, 154,  73 ), "tan2",
    MakeRGB( 205, 133,  63 ), "tan3",
    MakeRGB( 139,  90,  43 ), "tan4",
    MakeRGB( 255, 127,  36 ), "chocolate1",
    MakeRGB( 238, 118,  33 ), "chocolate2",
    MakeRGB( 205, 102,  29 ), "chocolate3",
    MakeRGB( 139,  69,  19 ), "chocolate4",
    MakeRGB( 255,  48,  48 ), "firebrick1",
    MakeRGB( 238,  44,  44 ), "firebrick2",
    MakeRGB( 205,  38,  38 ), "firebrick3",
    MakeRGB( 139,  26,  26 ), "firebrick4",
    MakeRGB( 255,  64,  64 ), "brown1",
    MakeRGB( 238,  59,  59 ), "brown2",
    MakeRGB( 205,  51,  51 ), "brown3",
    MakeRGB( 139,  35,  35 ), "brown4",
    MakeRGB( 255, 140, 105 ), "salmon1",
    MakeRGB( 238, 130,  98 ), "salmon2",
    MakeRGB( 205, 112,  84 ), "salmon3",
    MakeRGB( 139,  76,  57 ), "salmon4",
    MakeRGB( 255, 160, 122 ), "LightSalmon1",
    MakeRGB( 238, 149, 114 ), "LightSalmon2",
    MakeRGB( 205, 129,  98 ), "LightSalmon3",
    MakeRGB( 139,  87,  66 ), "LightSalmon4",
    MakeRGB( 255, 165,   0 ), "orange1",
    MakeRGB( 238, 154,   0 ), "orange2",
    MakeRGB( 205, 133,   0 ), "orange3",
    MakeRGB( 139,  90,   0 ), "orange4",
    MakeRGB( 255, 127,   0 ), "DarkOrange1",
    MakeRGB( 238, 118,   0 ), "DarkOrange2",
    MakeRGB( 205, 102,   0 ), "DarkOrange3",
    MakeRGB( 139,  69,   0 ), "DarkOrange4",
    MakeRGB( 255, 114,  86 ), "coral1",
    MakeRGB( 238, 106,  80 ), "coral2",
    MakeRGB( 205,  91,  69 ), "coral3",
    MakeRGB( 139,  62,  47 ), "coral4",
    MakeRGB( 255,  99,  71 ), "tomato1",
    MakeRGB( 238,  92,  66 ), "tomato2",
    MakeRGB( 205,  79,  57 ), "tomato3",
    MakeRGB( 139,  54,  38 ), "tomato4",
    MakeRGB( 255,  69,   0 ), "OrangeRed1",
    MakeRGB( 238,  64,   0 ), "OrangeRed2",
    MakeRGB( 205,  55,   0 ), "OrangeRed3",
    MakeRGB( 139,  37,   0 ), "OrangeRed4",
    MakeRGB( 255,   0,   0 ), "red1",
    MakeRGB( 238,   0,   0 ), "red2",
    MakeRGB( 205,   0,   0 ), "red3",
    MakeRGB( 139,   0,   0 ), "red4",
    MakeRGB( 255,  20, 147 ), "DeepPink1",
    MakeRGB( 238,  18, 137 ), "DeepPink2",
    MakeRGB( 205,  16, 118 ), "DeepPink3",
    MakeRGB( 139,  10,  80 ), "DeepPink4",
    MakeRGB( 255, 110, 180 ), "HotPink1",
    MakeRGB( 238, 106, 167 ), "HotPink2",
    MakeRGB( 205,  96, 144 ), "HotPink3",
    MakeRGB( 139,  58,  98 ), "HotPink4",
    MakeRGB( 255, 181, 197 ), "pink1",
    MakeRGB( 238, 169, 184 ), "pink2",
    MakeRGB( 205, 145, 158 ), "pink3",
    MakeRGB( 139,  99, 108 ), "pink4",
    MakeRGB( 255, 174, 185 ), "LightPink1",
    MakeRGB( 238, 162, 173 ), "LightPink2",
    MakeRGB( 205, 140, 149 ), "LightPink3",
    MakeRGB( 139,  95, 101 ), "LightPink4",
    MakeRGB( 255, 130, 171 ), "PaleVioletRed1",
    MakeRGB( 238, 121, 159 ), "PaleVioletRed2",
    MakeRGB( 205, 104, 137 ), "PaleVioletRed3",
    MakeRGB( 139,  71,  93 ), "PaleVioletRed4",
    MakeRGB( 255,  52, 179 ), "maroon1",
    MakeRGB( 238,  48, 167 ), "maroon2",
    MakeRGB( 205,  41, 144 ), "maroon3",
    MakeRGB( 139,  28,  98 ), "maroon4",
    MakeRGB( 255,  62, 150 ), "VioletRed1",
    MakeRGB( 238,  58, 140 ), "VioletRed2",
    MakeRGB( 205,  50, 120 ), "VioletRed3",
    MakeRGB( 139,  34,  82 ), "VioletRed4",
    MakeRGB( 255,   0, 255 ), "magenta1",
    MakeRGB( 238,   0, 238 ), "magenta2",
    MakeRGB( 205,   0, 205 ), "magenta3",
    MakeRGB( 139,   0, 139 ), "magenta4",
    MakeRGB( 255, 131, 250 ), "orchid1",
    MakeRGB( 238, 122, 233 ), "orchid2",
    MakeRGB( 205, 105, 201 ), "orchid3",
    MakeRGB( 139,  71, 137 ), "orchid4",
    MakeRGB( 255, 187, 255 ), "plum1",
    MakeRGB( 238, 174, 238 ), "plum2",
    MakeRGB( 205, 150, 205 ), "plum3",
    MakeRGB( 139, 102, 139 ), "plum4",
    MakeRGB( 224, 102, 255 ), "MediumOrchid1",
    MakeRGB( 209,  95, 238 ), "MediumOrchid2",
    MakeRGB( 180,  82, 205 ), "MediumOrchid3",
    MakeRGB( 122,  55, 139 ), "MediumOrchid4",
    MakeRGB( 191,  62, 255 ), "DarkOrchid1",
    MakeRGB( 178,  58, 238 ), "DarkOrchid2",
    MakeRGB( 154,  50, 205 ), "DarkOrchid3",
    MakeRGB( 104,  34, 139 ), "DarkOrchid4",
    MakeRGB( 155,  48, 255 ), "purple1",
    MakeRGB( 145,  44, 238 ), "purple2",
    MakeRGB( 125,  38, 205 ), "purple3",
    MakeRGB(  85,  26, 139 ), "purple4",
    MakeRGB( 171, 130, 255 ), "MediumPurple1",
    MakeRGB( 159, 121, 238 ), "MediumPurple2",
    MakeRGB( 137, 104, 205 ), "MediumPurple3",
    MakeRGB(  93,  71, 139 ), "MediumPurple4",
    MakeRGB( 255, 225, 255 ), "thistle1",
    MakeRGB( 238, 210, 238 ), "thistle2",
    MakeRGB( 205, 181, 205 ), "thistle3",
    MakeRGB( 139, 123, 139 ), "thistle4",
    MakeRGB(   0,   0,   0 ), "gray0",
    MakeRGB(   0,   0,   0 ), "grey0",
    MakeRGB(   3,   3,   3 ), "gray1",
    MakeRGB(   3,   3,   3 ), "grey1",
    MakeRGB(   5,   5,   5 ), "gray2",
    MakeRGB(   5,   5,   5 ), "grey2",
    MakeRGB(   8,   8,   8 ), "gray3",
    MakeRGB(   8,   8,   8 ), "grey3",
    MakeRGB(  10,  10,  10 ), "gray4",
    MakeRGB(  10,  10,  10 ), "grey4",
    MakeRGB(  13,  13,  13 ), "gray5",
    MakeRGB(  13,  13,  13 ), "grey5",
    MakeRGB(  15,  15,  15 ), "gray6",
    MakeRGB(  15,  15,  15 ), "grey6",
    MakeRGB(  18,  18,  18 ), "gray7",
    MakeRGB(  18,  18,  18 ), "grey7",
    MakeRGB(  20,  20,  20 ), "gray8",
    MakeRGB(  20,  20,  20 ), "grey8",
    MakeRGB(  23,  23,  23 ), "gray9",
    MakeRGB(  23,  23,  23 ), "grey9",
    MakeRGB(  26,  26,  26 ), "gray10",
    MakeRGB(  26,  26,  26 ), "grey10",
    MakeRGB(  28,  28,  28 ), "gray11",
    MakeRGB(  28,  28,  28 ), "grey11",
    MakeRGB(  31,  31,  31 ), "gray12",
    MakeRGB(  31,  31,  31 ), "grey12",
    MakeRGB(  33,  33,  33 ), "gray13",
    MakeRGB(  33,  33,  33 ), "grey13",
    MakeRGB(  36,  36,  36 ), "gray14",
    MakeRGB(  36,  36,  36 ), "grey14",
    MakeRGB(  38,  38,  38 ), "gray15",
    MakeRGB(  38,  38,  38 ), "grey15",
    MakeRGB(  41,  41,  41 ), "gray16",
    MakeRGB(  41,  41,  41 ), "grey16",
    MakeRGB(  43,  43,  43 ), "gray17",
    MakeRGB(  43,  43,  43 ), "grey17",
    MakeRGB(  46,  46,  46 ), "gray18",
    MakeRGB(  46,  46,  46 ), "grey18",
    MakeRGB(  48,  48,  48 ), "gray19",
    MakeRGB(  48,  48,  48 ), "grey19",
    MakeRGB(  51,  51,  51 ), "gray20",
    MakeRGB(  51,  51,  51 ), "grey20",
    MakeRGB(  54,  54,  54 ), "gray21",
    MakeRGB(  54,  54,  54 ), "grey21",
    MakeRGB(  56,  56,  56 ), "gray22",
    MakeRGB(  56,  56,  56 ), "grey22",
    MakeRGB(  59,  59,  59 ), "gray23",
    MakeRGB(  59,  59,  59 ), "grey23",
    MakeRGB(  61,  61,  61 ), "gray24",
    MakeRGB(  61,  61,  61 ), "grey24",
    MakeRGB(  64,  64,  64 ), "gray25",
    MakeRGB(  64,  64,  64 ), "grey25",
    MakeRGB(  66,  66,  66 ), "gray26",
    MakeRGB(  66,  66,  66 ), "grey26",
    MakeRGB(  69,  69,  69 ), "gray27",
    MakeRGB(  69,  69,  69 ), "grey27",
    MakeRGB(  71,  71,  71 ), "gray28",
    MakeRGB(  71,  71,  71 ), "grey28",
    MakeRGB(  74,  74,  74 ), "gray29",
    MakeRGB(  74,  74,  74 ), "grey29",
    MakeRGB(  77,  77,  77 ), "gray30",
    MakeRGB(  77,  77,  77 ), "grey30",
    MakeRGB(  79,  79,  79 ), "gray31",
    MakeRGB(  79,  79,  79 ), "grey31",
    MakeRGB(  82,  82,  82 ), "gray32",
    MakeRGB(  82,  82,  82 ), "grey32",
    MakeRGB(  84,  84,  84 ), "gray33",
    MakeRGB(  84,  84,  84 ), "grey33",
    MakeRGB(  87,  87,  87 ), "gray34",
    MakeRGB(  87,  87,  87 ), "grey34",
    MakeRGB(  89,  89,  89 ), "gray35",
    MakeRGB(  89,  89,  89 ), "grey35",
    MakeRGB(  92,  92,  92 ), "gray36",
    MakeRGB(  92,  92,  92 ), "grey36",
    MakeRGB(  94,  94,  94 ), "gray37",
    MakeRGB(  94,  94,  94 ), "grey37",
    MakeRGB(  97,  97,  97 ), "gray38",
    MakeRGB(  97,  97,  97 ), "grey38",
    MakeRGB(  99,  99,  99 ), "gray39",
    MakeRGB(  99,  99,  99 ), "grey39",
    MakeRGB( 102, 102, 102 ), "gray40",
    MakeRGB( 102, 102, 102 ), "grey40",
    MakeRGB( 105, 105, 105 ), "gray41",
    MakeRGB( 105, 105, 105 ), "grey41",
    MakeRGB( 107, 107, 107 ), "gray42",
    MakeRGB( 107, 107, 107 ), "grey42",
    MakeRGB( 110, 110, 110 ), "gray43",
    MakeRGB( 110, 110, 110 ), "grey43",
    MakeRGB( 112, 112, 112 ), "gray44",
    MakeRGB( 112, 112, 112 ), "grey44",
    MakeRGB( 115, 115, 115 ), "gray45",
    MakeRGB( 115, 115, 115 ), "grey45",
    MakeRGB( 117, 117, 117 ), "gray46",
    MakeRGB( 117, 117, 117 ), "grey46",
    MakeRGB( 120, 120, 120 ), "gray47",
    MakeRGB( 120, 120, 120 ), "grey47",
    MakeRGB( 122, 122, 122 ), "gray48",
    MakeRGB( 122, 122, 122 ), "grey48",
    MakeRGB( 125, 125, 125 ), "gray49",
    MakeRGB( 125, 125, 125 ), "grey49",
    MakeRGB( 127, 127, 127 ), "gray50",
    MakeRGB( 127, 127, 127 ), "grey50",
    MakeRGB( 130, 130, 130 ), "gray51",
    MakeRGB( 130, 130, 130 ), "grey51",
    MakeRGB( 133, 133, 133 ), "gray52",
    MakeRGB( 133, 133, 133 ), "grey52",
    MakeRGB( 135, 135, 135 ), "gray53",
    MakeRGB( 135, 135, 135 ), "grey53",
    MakeRGB( 138, 138, 138 ), "gray54",
    MakeRGB( 138, 138, 138 ), "grey54",
    MakeRGB( 140, 140, 140 ), "gray55",
    MakeRGB( 140, 140, 140 ), "grey55",
    MakeRGB( 143, 143, 143 ), "gray56",
    MakeRGB( 143, 143, 143 ), "grey56",
    MakeRGB( 145, 145, 145 ), "gray57",
    MakeRGB( 145, 145, 145 ), "grey57",
    MakeRGB( 148, 148, 148 ), "gray58",
    MakeRGB( 148, 148, 148 ), "grey58",
    MakeRGB( 150, 150, 150 ), "gray59",
    MakeRGB( 150, 150, 150 ), "grey59",
    MakeRGB( 153, 153, 153 ), "gray60",
    MakeRGB( 153, 153, 153 ), "grey60",
    MakeRGB( 156, 156, 156 ), "gray61",
    MakeRGB( 156, 156, 156 ), "grey61",
    MakeRGB( 158, 158, 158 ), "gray62",
    MakeRGB( 158, 158, 158 ), "grey62",
    MakeRGB( 161, 161, 161 ), "gray63",
    MakeRGB( 161, 161, 161 ), "grey63",
    MakeRGB( 163, 163, 163 ), "gray64",
    MakeRGB( 163, 163, 163 ), "grey64",
    MakeRGB( 166, 166, 166 ), "gray65",
    MakeRGB( 166, 166, 166 ), "grey65",
    MakeRGB( 168, 168, 168 ), "gray66",
    MakeRGB( 168, 168, 168 ), "grey66",
    MakeRGB( 171, 171, 171 ), "gray67",
    MakeRGB( 171, 171, 171 ), "grey67",
    MakeRGB( 173, 173, 173 ), "gray68",
    MakeRGB( 173, 173, 173 ), "grey68",
    MakeRGB( 176, 176, 176 ), "gray69",
    MakeRGB( 176, 176, 176 ), "grey69",
    MakeRGB( 179, 179, 179 ), "gray70",
    MakeRGB( 179, 179, 179 ), "grey70",
    MakeRGB( 181, 181, 181 ), "gray71",
    MakeRGB( 181, 181, 181 ), "grey71",
    MakeRGB( 184, 184, 184 ), "gray72",
    MakeRGB( 184, 184, 184 ), "grey72",
    MakeRGB( 186, 186, 186 ), "gray73",
    MakeRGB( 186, 186, 186 ), "grey73",
    MakeRGB( 189, 189, 189 ), "gray74",
    MakeRGB( 189, 189, 189 ), "grey74",
    MakeRGB( 191, 191, 191 ), "gray75",
    MakeRGB( 191, 191, 191 ), "grey75",
    MakeRGB( 194, 194, 194 ), "gray76",
    MakeRGB( 194, 194, 194 ), "grey76",
    MakeRGB( 196, 196, 196 ), "gray77",
    MakeRGB( 196, 196, 196 ), "grey77",
    MakeRGB( 199, 199, 199 ), "gray78",
    MakeRGB( 199, 199, 199 ), "grey78",
    MakeRGB( 201, 201, 201 ), "gray79",
    MakeRGB( 201, 201, 201 ), "grey79",
    MakeRGB( 204, 204, 204 ), "gray80",
    MakeRGB( 204, 204, 204 ), "grey80",
    MakeRGB( 207, 207, 207 ), "gray81",
    MakeRGB( 207, 207, 207 ), "grey81",
    MakeRGB( 209, 209, 209 ), "gray82",
    MakeRGB( 209, 209, 209 ), "grey82",
    MakeRGB( 212, 212, 212 ), "gray83",
    MakeRGB( 212, 212, 212 ), "grey83",
    MakeRGB( 214, 214, 214 ), "gray84",
    MakeRGB( 214, 214, 214 ), "grey84",
    MakeRGB( 217, 217, 217 ), "gray85",
    MakeRGB( 217, 217, 217 ), "grey85",
    MakeRGB( 219, 219, 219 ), "gray86",
    MakeRGB( 219, 219, 219 ), "grey86",
    MakeRGB( 222, 222, 222 ), "gray87",
    MakeRGB( 222, 222, 222 ), "grey87",
    MakeRGB( 224, 224, 224 ), "gray88",
    MakeRGB( 224, 224, 224 ), "grey88",
    MakeRGB( 227, 227, 227 ), "gray89",
    MakeRGB( 227, 227, 227 ), "grey89",
    MakeRGB( 229, 229, 229 ), "gray90",
    MakeRGB( 229, 229, 229 ), "grey90",
    MakeRGB( 232, 232, 232 ), "gray91",
    MakeRGB( 232, 232, 232 ), "grey91",
    MakeRGB( 235, 235, 235 ), "gray92",
    MakeRGB( 235, 235, 235 ), "grey92",
    MakeRGB( 237, 237, 237 ), "gray93",
    MakeRGB( 237, 237, 237 ), "grey93",
    MakeRGB( 240, 240, 240 ), "gray94",
    MakeRGB( 240, 240, 240 ), "grey94",
    MakeRGB( 242, 242, 242 ), "gray95",
    MakeRGB( 242, 242, 242 ), "grey95",
    MakeRGB( 245, 245, 245 ), "gray96",
    MakeRGB( 245, 245, 245 ), "grey96",
    MakeRGB( 247, 247, 247 ), "gray97",
    MakeRGB( 247, 247, 247 ), "grey97",
    MakeRGB( 250, 250, 250 ), "gray98",
    MakeRGB( 250, 250, 250 ), "grey98",
    MakeRGB( 252, 252, 252 ), "gray99",
    MakeRGB( 252, 252, 252 ), "grey99",
    MakeRGB( 255, 255, 255 ), "gray100",
    MakeRGB( 255, 255, 255 ), "grey100",
    MakeRGB( 169, 169, 169 ), "dark_grey",
    MakeRGB( 169, 169, 169 ), "DarkGrey",
    MakeRGB( 169, 169, 169 ), "dark_gray",
    MakeRGB( 169, 169, 169 ), "DarkGray",
    MakeRGB( 0  ,   0, 139 ), "dark_blue",
    MakeRGB( 0  ,   0, 139 ), "DarkBlue",
    MakeRGB( 0  , 139, 139 ), "dark_cyan",
    MakeRGB( 0  , 139, 139 ), "DarkCyan",
    MakeRGB( 139,   0, 139 ), "dark_magenta",
    MakeRGB( 139,   0, 139 ), "DarkMagenta",
    MakeRGB( 139,   0,   0 ), "dark_red",
    MakeRGB( 139,   0,   0 ), "DarkRed",
    MakeRGB( 144, 238, 144 ), "light_green",
    MakeRGB( 144, 238, 144 ), "LightGreen"
};

static const int GBM_XPM_RGB_NAMES_LENGTH = sizeof(GBM_XPM_RGB_NAMES) /
                                            sizeof(GBM_XPM_RGB_NAMES[0]);

/* ---------------------------------------- */
/* ---------------------------------------- */

/* convert hex color names, wrong digits (not a-f,A-F,0-9) are treated as zero */
static word hexCharToWord(const char c)
{
    word r;

    if (c >= '0' && c <= '9')
    {
       r = c - '0';
    }
    else if (c >= 'a' && c <= 'f')
    {
       r = c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F')
    {
       r = c - 'A' + 10;
    }
    else
    {
       r = 0;
    }
    return r;
}

/* Input: hex code string starting with # */
BOOLEAN rgb16FromHex(const byte *hex, int hex_len, GBMRGB_16BPP * gbmrgb16)
{
    if (hex == 0 || hex[0] != '#')
    {
       return FALSE;
    }

    if (hex_len == 3 + 1)
    {
       /* it's like c #323 (4 bit per color component) */
       gbmrgb16->r = hexCharToWord(hex[1]) << 4;
       gbmrgb16->g = hexCharToWord(hex[2]) << 4;
       gbmrgb16->b = hexCharToWord(hex[3]) << 4;
    }
    else if (hex_len == 6 + 1)
    {
       /* it's like c #323299 (8 bit per color component) */
       gbmrgb16->r = hexCharToWord(hex[1]) * 16 + hexCharToWord(hex[2]);
       gbmrgb16->g = hexCharToWord(hex[3]) * 16 + hexCharToWord(hex[4]);
       gbmrgb16->b = hexCharToWord(hex[5]) * 16 + hexCharToWord(hex[6]);
    }
    else if (hex_len == 9 + 1)
    {
       /* it's like c #323999CCC (12 bit per color component) */
       gbmrgb16->r = (hexCharToWord(hex[1])  * 16*16 + hexCharToWord(hex[2]) * 16 +
                      hexCharToWord(hex[3])) << 4;
       gbmrgb16->g = (hexCharToWord(hex[4])  * 16*16 + hexCharToWord(hex[5]) * 16 +
                      hexCharToWord(hex[6])) << 4;
       gbmrgb16->b = (hexCharToWord(hex[7])  * 16*16 + hexCharToWord(hex[8]) * 16 +
                      hexCharToWord(hex[9])) << 4;
    }
    else if (hex_len == 12 + 1)
    {
       /* it's like c #32329999CCCC (16 bit per color component) */
       gbmrgb16->r = hexCharToWord(hex[1])  * 16*16*16 + hexCharToWord(hex[2])  * 16*16 +
                     hexCharToWord(hex[3])  * 16       + hexCharToWord(hex[4]);
       gbmrgb16->g = hexCharToWord(hex[5])  * 16*16*16 + hexCharToWord(hex[6])  * 16*16 +
                     hexCharToWord(hex[7])  * 16       + hexCharToWord(hex[8]);
       gbmrgb16->b = hexCharToWord(hex[9])  * 16*16*16 + hexCharToWord(hex[10]) * 16*16 +
                     hexCharToWord(hex[11]) * 16       + hexCharToWord(hex[12]);
    }
    else
    {
       return FALSE;
    }
    return TRUE;
}

/* ---------------------------------------- */
/* ---------------------------------------- */

BOOLEAN rgb16FromColorName(const byte *color_name, int color_name_len, GBMRGB_16BPP * gbmrgb16)
{
    int i;
    color_name_len = color_name_len;
    for (i = 0; i < GBM_XPM_RGB_NAMES_LENGTH; i++)
    {
        if (strnicmp(color_name, GBM_XPM_RGB_NAMES[i].name, strlen(color_name)) == 0)
        {
            gbmrgb16->r = GetR(GBM_XPM_RGB_NAMES[i].rgb);
            gbmrgb16->g = GetG(GBM_XPM_RGB_NAMES[i].rgb);
            gbmrgb16->b = GetB(GBM_XPM_RGB_NAMES[i].rgb);
            return TRUE;
        }
    }
    return FALSE;
}

/* ---------------------------------------- */
/* ---------------------------------------- */

static char nibbleToHexChar(const byte b)
{
    return (b <= 9) ? ('0' + b) : ('A' + b - 10);
}

BOOLEAN hexFromRgb16(const int bpp, const GBMRGB_16BPP * gbmrgb16, byte *hex, int hex_len)
{
    switch(bpp)
    {
        case  1:
        case  4:
        case  8:
        case 24:
            /* 8 bit per color component */
            if (hex_len < 7 + 1)
            {
                return FALSE;
            }
            hex[0] = '#';
            hex[1] = nibbleToHexChar((gbmrgb16->r >>  4) & 0xf);
            hex[2] = nibbleToHexChar( gbmrgb16->r        & 0xf);
            hex[3] = nibbleToHexChar((gbmrgb16->g >>  4) & 0xf);
            hex[4] = nibbleToHexChar( gbmrgb16->g        & 0xf);
            hex[5] = nibbleToHexChar((gbmrgb16->b >>  4) & 0xf);
            hex[6] = nibbleToHexChar( gbmrgb16->b        & 0xf);
            hex[7] = 0;
            break;

        case 48:
            /* 16 bit per color component */
            if (hex_len < 13 + 1)
            {
                return FALSE;
            }
            hex[0]  = '#';
            hex[1]  = nibbleToHexChar((gbmrgb16->r >> 12) & 0xf);
            hex[2]  = nibbleToHexChar((gbmrgb16->r >>  8) & 0xf);
            hex[3]  = nibbleToHexChar((gbmrgb16->r >>  4) & 0xf);
            hex[4]  = nibbleToHexChar( gbmrgb16->r        & 0xf);
            hex[5]  = nibbleToHexChar((gbmrgb16->g >> 12) & 0xf);
            hex[6]  = nibbleToHexChar((gbmrgb16->g >>  8) & 0xf);
            hex[7]  = nibbleToHexChar((gbmrgb16->g >>  4) & 0xf);
            hex[8]  = nibbleToHexChar( gbmrgb16->g        & 0xf);
            hex[9]  = nibbleToHexChar((gbmrgb16->b >> 12) & 0xf);
            hex[10] = nibbleToHexChar((gbmrgb16->b >>  8) & 0xf);
            hex[11] = nibbleToHexChar((gbmrgb16->b >>  4) & 0xf);
            hex[12] = nibbleToHexChar( gbmrgb16->b        & 0xf);
            hex[13] = 0;
            break;

        default:
            return FALSE;
    }
    return TRUE;
}

