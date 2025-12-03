bctrHeader:
    .ascii  "bctr"
    .short  2
    .short  str_LytName - strtab
    .short  0
    .short  0
    .short  subHeader1 - bctrHeader
    .short  subHeader2 - bctrHeader
    .short  strtab - bctrHeader
    .short  0

subHeader1:
    .short  section1 - subHeader1
    .short  0 // num section 1
    .short  section2 - subHeader1
    .short  0 // num section 2

subHeader2:
    .short  section3 - subHeader2
    .short  1 // count
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

section3:
    /* entry 0 */
    .short  str_TitleLogo - strtab
    .short  0xFF
    .short  1
    .short  0
    .float  0
    // --- 4:3 position --- //
    .float  0
    .float  70
    .float  0
    .float  1
    .float  1
    // --- 16:9 position --- //
    .float  0
    .float  70
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
    .string "mkwtm_logo"

/* Position names! */
str_TitleLogo:
    .string "TitleLogo"