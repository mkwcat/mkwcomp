bctrHeader:
    .ascii  "bctr"
    .short  2
    .short  str_LytName - strtab
    .short  str_bmgName - strtab
    .short  str_TextureLytName - strtab
    .short  subHeader1 - bctrHeader
    .short  subHeader2 - bctrHeader
    .short  strtab - bctrHeader
    .short  0

subHeader1:
    .short  section1 - subHeader1
    .short  4 // num section 1
    .short  section2 - subHeader1
    .short  9 // num section 2

section1:
    /* entry 0 */
    .short  str_Loop - strtab
    .short  str_fuchi_pattern - strtab
    .short  0
    .short  1
    /* entry 1 */
    .short  str_Select - strtab
    .short  str_select_free_g - strtab
    .short  1
    .short  4
    /* entry 2 */
    .short  str_SelectIn - strtab
    .short  str_text_light_02 - strtab
    .short  5
    .short  2
    /* entry 3 */
    .short  str_OK - strtab
    .short  str_text_light_01 - strtab
    .short  7
    .short  2

section2:
    /* entry 0 */
    .short  str_Loop - strtab
    .short  str_brlanFuchiCheckLoop - strtab
    .short  0
    .short  0
    .float  1
    /* entry 1 */
    .short  str_Free - strtab
    .short  str_brlanFree - strtab
    .short  0
    .short  0
    .float  1
    /* entry 2 */
    .short  str_FreeToSelect - strtab
    .short  str_brlanFreeToSelect - strtab
    .short  str_Select - strtab
    .short  0
    .float  1
    /* entry 3 */
    .short  str_Select - strtab
    .short  str_brlanSelect - strtab
    .short  0
    .short  0
    .float  1
    /* entry 4 */
    .short  str_SelectToFree - strtab
    .short  str_brlanSelectToFree - strtab
    .short  str_Free - strtab
    .short  0
    .float  1
    /* entry 5 */
    .short  str_SelectIn - strtab
    .short  str_brlanTextLight02Select - strtab
    .short  str_SelectStop - strtab
    .short  0
    .float  1
    /* entry 6 */
    .short  str_SelectStop - strtab
    .short  str_brlanTextLight02Stop - strtab
    .short  0
    .short  0
    .float  1
    /* entry 7 */
    .short  str_OK - strtab
    .short  str_brlanTextLight01OK - strtab
    .short  str_OKStop - strtab
    .short  0
    .float  1
    /* entry 8 */
    .short  str_OKStop - strtab
    .short  str_brlanTextLight01Stop - strtab
    .short  0
    .short  0
    .float  1


subHeader2:
    .short  section3 - subHeader2
    .short  10 // count
    .short  section4 - subHeader2
    .short  0 // count
    .short  section5 - subHeader2
    .short  0 // count

/* 
 * Section 1 Entry - positions!
 * struct section1Entry {
 *     u16 nameOffset;
 *     u16 alpha;
 *     u16 useAnimation;
 *     u16 pad;
 * 
 *     f32 delayTime;
 * 
 *     f32 normalTransX;
 *     f32 normalTransY;
 *     f32 normalTransZ;
 *     f32 normalScaleX;
 *     f32 normalScaleY;
 * 
 *     f32 wideTransX;
 *     f32 wideTransY;
 *     f32 wideTransZ;
 *     f32 wideScaleX;
 *     f32 wideScaleY;
 * 
 *     u16 section4ID;
 *     u16 numSection4IDs;
 *     u16 section5ID;
 *     u16 numSection5IDs;
 * };
 */

#define X_WIDE_DIF 90
#define X_WIDE_DIF2 180
#define X_NORMAL_DIF 95
#define X_NORMAL_DIF2 190
#define SCALE_NORMAL 0.8

#define Y_WIDE_VAL1 110
#define Y_WIDE_VAL2 20
#define Y_NORMAL_VAL1 100
#define Y_NORMAL_VAL2 30

section3:
    /* entry 0 */
    .short  str_Button0 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  -X_NORMAL_DIF2
    .float  Y_NORMAL_VAL1
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  -X_WIDE_DIF2
    .float  Y_WIDE_VAL1
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 1 */
    .short  str_Button1 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  -X_NORMAL_DIF
    .float  Y_NORMAL_VAL1
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  -X_WIDE_DIF
    .float  Y_WIDE_VAL1
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 2 */
    .short  str_Button2 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  0
    .float  Y_NORMAL_VAL1
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  0
    .float  Y_WIDE_VAL1
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 3 */
    .short  str_Button3 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  X_NORMAL_DIF
    .float  Y_NORMAL_VAL1
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  X_WIDE_DIF
    .float  Y_WIDE_VAL1
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 4 */
    .short  str_Button4 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  X_NORMAL_DIF2
    .float  Y_NORMAL_VAL1
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  X_WIDE_DIF2
    .float  Y_WIDE_VAL1
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 5 */
    .short  str_Button5 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  -X_NORMAL_DIF2
    .float  Y_NORMAL_VAL2
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  -X_WIDE_DIF2
    .float  Y_WIDE_VAL2
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 6 */
    .short  str_Button6 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  -X_NORMAL_DIF
    .float  Y_NORMAL_VAL2
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  -X_WIDE_DIF
    .float  Y_WIDE_VAL2
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 7 */
    .short  str_Button7 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  0
    .float  Y_NORMAL_VAL2
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  0
    .float  Y_WIDE_VAL2
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 8 */
    .short  str_Button8 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  X_NORMAL_DIF
    .float  Y_NORMAL_VAL2
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  X_WIDE_DIF
    .float  Y_WIDE_VAL2
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

    /* entry 9 */
    .short  str_Button9 - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  X_NORMAL_DIF2
    .float  Y_NORMAL_VAL2
    .float  0
    .float  SCALE_NORMAL
    .float  SCALE_NORMAL
    // --- 16:9 position --- //
    .float  X_WIDE_DIF2
    .float  Y_WIDE_VAL2
    .float  0
    .float  1
    .float  1
    // --- section 4 ID --- //
    .short  0
    .short  0
    // --- section 5 ID --- //
    .short  0
    .short  0

section4:
section5:

/* <-------
 * String Table
 * -------> */
strtab:
str_null:
    .string ""
str_LytName:
    .string "competition_menu"
str_bmgName:
    .string "Menu"
str_TextureLytName:
    .string "competition_button_texture"

/* BRLAN names */
str_Loop:
    .string "Loop"
str_fuchi_pattern:
    .string "fuchi_pattern"

str_brlanFuchiCheckLoop:
    .string "common_w019_mii_fuchi_check_loop.brlan"

str_Select:
    .string "Select"
str_select_free_g:
    .string "select_free_g"

str_Free:
    .string "Free"
str_brlanFree:
    .string "common_w019_mii_free.brlan"

str_FreeToSelect:
    .string "FreeToSelect"
str_brlanFreeToSelect:
    .string "common_w019_mii_free_to_select.brlan"

str_brlanSelect:
    .string "common_w019_mii_select.brlan"

str_SelectToFree:
    .string "SelectToFree"
str_brlanSelectToFree:
    .string "common_w019_mii_select_to_free.brlan"

str_SelectIn:
    .string "SelectIn"
str_text_light_02:
    .string "chara_light_02"

str_brlanTextLight02Select:
    .string "common_w019_mii_chara_light_02_select.brlan"

str_SelectStop:
    .string "SelectStop"

str_brlanTextLight02Stop:
    .string "common_w019_mii_chara_light_02_stop.brlan"

str_OK:
    .string "OK"

str_text_light_01:
    .string "chara_light_01"
str_brlanTextLight01OK:
    .string "common_w019_mii_chara_light_01_ok.brlan"

str_OKStop:
    .string "OKStop"

str_brlanTextLight01Stop:
    .string "common_w019_mii_chara_light_01_stop.brlan"

/* Position names! */
str_Button0:
    .string "Button0"
str_Button1:
    .string "Button1"
str_Button2:
    .string "Button2"
str_Button3:
    .string "Button3"
str_Button4:
    .string "Button4"
str_Button5:
    .string "Button5"
str_Button6:
    .string "Button6"
str_Button7:
    .string "Button7"
str_Button8:
    .string "Button8"
str_Button9:
    .string "Button9"