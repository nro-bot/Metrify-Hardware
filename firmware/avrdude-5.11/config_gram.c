#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20101229

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 23 "config_gram.y"

#include "ac_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "avrdude.h"

#include "config.h"
#include "lists.h"
#include "par.h"
#include "serbb.h"
#include "pindefs.h"
#include "ppi.h"
#include "pgm.h"
#include "stk500.h"
#include "arduino.h"
#include "buspirate.h"
#include "stk500v2.h"
#include "wiring.h"
#include "stk500generic.h"
#include "avr910.h"
#include "butterfly.h"
#include "usbasp.h"
#include "usbtiny.h"
#include "avr.h"
#include "jtagmkI.h"
#include "jtagmkII.h"
#include "avrftdi.h"

#if defined(WIN32NATIVE)
#define strtok_r( _s, _sep, _lasts ) \
    ( *(_lasts) = strtok( (_s), (_sep) ) )
#endif

int yylex(void);
int yyerror(char * errmsg);

static int assign_pin(int pinno, TOKEN * v, int invert);
static int which_opcode(TOKEN * opcode);
static int parse_cmdbits(OPCODE * op);
 
#line 63 "config_gram.c"

#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#define YYERROR_DECL() yyerror(const char *s)
#define YYERROR_CALL(msg) yyerror(msg)

extern int YYPARSE_DECL();

#define K_READ 257
#define K_WRITE 258
#define K_READ_LO 259
#define K_READ_HI 260
#define K_WRITE_LO 261
#define K_WRITE_HI 262
#define K_LOADPAGE_LO 263
#define K_LOADPAGE_HI 264
#define K_LOAD_EXT_ADDR 265
#define K_WRITEPAGE 266
#define K_CHIP_ERASE 267
#define K_PGM_ENABLE 268
#define K_MEMORY 269
#define K_PAGE_SIZE 270
#define K_PAGED 271
#define K_ARDUINO 272
#define K_AVRFTDI 273
#define K_BAUDRATE 274
#define K_BS2 275
#define K_BUFF 276
#define K_BUSPIRATE 277
#define K_CHIP_ERASE_DELAY 278
#define K_DEDICATED 279
#define K_DEFAULT_PARALLEL 280
#define K_DEFAULT_PROGRAMMER 281
#define K_DEFAULT_SERIAL 282
#define K_DEFAULT_BITCLOCK 283
#define K_DESC 284
#define K_DEVICECODE 285
#define K_DRAGON_DW 286
#define K_DRAGON_HVSP 287
#define K_DRAGON_ISP 288
#define K_DRAGON_JTAG 289
#define K_DRAGON_PDI 290
#define K_DRAGON_PP 291
#define K_STK500_DEVCODE 292
#define K_AVR910_DEVCODE 293
#define K_EEPROM 294
#define K_ERRLED 295
#define K_FLASH 296
#define K_ID 297
#define K_IO 298
#define K_JTAG_MKI 299
#define K_JTAG_MKII 300
#define K_JTAG_MKII_AVR32 301
#define K_JTAG_MKII_DW 302
#define K_JTAG_MKII_ISP 303
#define K_JTAG_MKII_PDI 304
#define K_LOADPAGE 305
#define K_MAX_WRITE_DELAY 306
#define K_MIN_WRITE_DELAY 307
#define K_MISO 308
#define K_MOSI 309
#define K_NUM_PAGES 310
#define K_NVM_BASE 311
#define K_OFFSET 312
#define K_PAGEL 313
#define K_PAR 314
#define K_PARALLEL 315
#define K_PART 316
#define K_PGMLED 317
#define K_PROGRAMMER 318
#define K_PSEUDO 319
#define K_PWROFF_AFTER_WRITE 320
#define K_RDYLED 321
#define K_READBACK_P1 322
#define K_READBACK_P2 323
#define K_READMEM 324
#define K_RESET 325
#define K_RETRY_PULSE 326
#define K_SERBB 327
#define K_SERIAL 328
#define K_SCK 329
#define K_SIGNATURE 330
#define K_SIZE 331
#define K_STK500 332
#define K_STK500HVSP 333
#define K_STK500PP 334
#define K_STK500V2 335
#define K_STK500GENERIC 336
#define K_STK600 337
#define K_STK600HVSP 338
#define K_STK600PP 339
#define K_AVR910 340
#define K_USBASP 341
#define K_USBDEV 342
#define K_USBSN 343
#define K_USBTINY 344
#define K_USBPID 345
#define K_USBPRODUCT 346
#define K_USBVENDOR 347
#define K_USBVID 348
#define K_BUTTERFLY 349
#define K_BUTTERFLY_MK 350
#define K_TYPE 351
#define K_VCC 352
#define K_VFYLED 353
#define K_WIRING 354
#define K_NO 355
#define K_YES 356
#define K_TIMEOUT 357
#define K_STABDELAY 358
#define K_CMDEXEDELAY 359
#define K_HVSPCMDEXEDELAY 360
#define K_SYNCHLOOPS 361
#define K_BYTEDELAY 362
#define K_POLLVALUE 363
#define K_POLLINDEX 364
#define K_PREDELAY 365
#define K_POSTDELAY 366
#define K_POLLMETHOD 367
#define K_MODE 368
#define K_DELAY 369
#define K_BLOCKSIZE 370
#define K_READSIZE 371
#define K_HVENTERSTABDELAY 372
#define K_PROGMODEDELAY 373
#define K_LATCHCYCLES 374
#define K_TOGGLEVTG 375
#define K_POWEROFFDELAY 376
#define K_RESETDELAYMS 377
#define K_RESETDELAYUS 378
#define K_HVLEAVESTABDELAY 379
#define K_RESETDELAY 380
#define K_SYNCHCYCLES 381
#define K_HVCMDEXEDELAY 382
#define K_CHIPERASEPULSEWIDTH 383
#define K_CHIPERASEPOLLTIMEOUT 384
#define K_CHIPERASETIME 385
#define K_PROGRAMFUSEPULSEWIDTH 386
#define K_PROGRAMFUSEPOLLTIMEOUT 387
#define K_PROGRAMLOCKPULSEWIDTH 388
#define K_PROGRAMLOCKPOLLTIMEOUT 389
#define K_PP_CONTROLSTACK 390
#define K_HVSP_CONTROLSTACK 391
#define K_ALLOWFULLPAGEBITSTREAM 392
#define K_ENABLEPAGEPROGRAMMING 393
#define K_HAS_JTAG 394
#define K_HAS_DW 395
#define K_HAS_PDI 396
#define K_HAS_TPI 397
#define K_IDR 398
#define K_IS_AVR32 399
#define K_RAMPZ 400
#define K_SPMCR 401
#define K_EECR 402
#define K_FLASH_INSTR 403
#define K_EEPROM_INSTR 404
#define TKN_COMMA 405
#define TKN_EQUAL 406
#define TKN_SEMI 407
#define TKN_TILDE 408
#define TKN_NUMBER 409
#define TKN_STRING 410
#define TKN_ID 411
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    1,    1,    2,    2,    2,    2,    2,    2,
    6,    3,    8,    4,    9,    9,   10,   10,    5,    5,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
    7,    7,   14,   14,   15,   15,   17,   17,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   19,   13,   13,   16,   16,
   18,   18,   20,   20,   20,   20,   20,   20,   20,   20,
   20,   20,   20,   20,   20,   20,   20,   20,
};
static const short yylen[] = {                            2,
    0,    1,    1,    2,    2,    2,    4,    4,    4,    4,
    0,    3,    0,    3,    1,    3,    1,    3,    2,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    4,    4,    4,    4,    4,    4,    4,    4,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    3,    1,    1,    1,    1,    1,    1,    3,    3,
    3,    3,    3,    5,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    0,    4,    3,    1,    1,
    2,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,   13,   11,    0,    0,    3,    0,
    0,    0,    0,    0,    0,    0,    0,    4,    5,    6,
    0,    0,    0,    0,   79,   80,   81,   82,   83,   84,
   85,   86,   87,   88,   89,   90,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    8,
    7,    9,   10,  156,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   91,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   19,    0,  111,  109,  100,
  101,  102,  103,   99,  152,  110,   96,  160,  159,  154,
   95,   93,   94,  112,   97,   98,  155,  153,    0,  113,
  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,
  124,  125,  126,  127,  128,  129,  130,  131,  132,  140,
  133,  134,  135,  136,  137,  138,  139,   17,    0,    0,
  146,  147,  141,  142,  143,  144,  148,  145,  149,  150,
  151,    0,    0,   92,   15,    0,   62,    0,   53,    0,
   67,    0,    0,   66,    0,   65,    0,   69,    0,   68,
    0,   63,    0,   64,   56,   59,   58,   61,   60,   57,
   30,   31,   32,   47,   48,   49,   50,   51,   52,   41,
   42,   43,   44,   45,   46,   22,   23,   24,   27,   28,
   25,   29,   33,   34,   35,   36,   37,   38,   39,   40,
   26,    0,    0,   70,   20,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   75,   74,   73,   77,
   76,   71,   72,   78,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  161,  104,   18,   16,  165,  163,  169,  168,  166,
  167,  170,  171,  172,  164,  177,  173,  174,  175,  176,
    0,  162,
};
static const short yydgoto[] = {                          7,
    8,    9,   10,   11,  118,   17,   95,   16,  276,  259,
  119,   96,   97,  224,  220,  221,  227,  352,  207,  353,
};
static const short yysindex[] = {                      -253,
 -404, -380, -375, -368,    0,    0,    0, -253,    0, -348,
 -343, -341, -339, -336, -332, -217,  -15,    0,    0,    0,
 -314, -312, -310, -302,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -308, -300, -299, -296,
 -294, -291, -290, -289, -284, -283, -282, -281, -280, -279,
 -278, -277, -275, -274, -273, -272, -271, -270, -269, -268,
 -267, -254, -252, -241, -216, -215, -212, -211, -210, -209,
 -208, -207, -206, -205, -198, -197, -196, -195, -194, -193,
 -192, -185, -184, -183, -182, -181, -180, -179, -178, -175,
 -174, -173, -171, -170, -217, -169, -168, -166, -165, -164,
 -162, -161, -160, -159, -148, -144, -143, -142, -139, -138,
 -135, -134, -133, -132, -131, -130, -129,  -15, -128,    0,
    0,    0,    0,    0, -256, -126, -172, -125, -124, -123,
 -122, -120, -119, -266, -276, -306, -351, -118, -117, -114,
 -113, -112, -111, -110, -109, -108, -106, -105, -104, -101,
 -100,  -98,  -97,  -96,  -94,  -93,  -92,  -91,  -90,  -89,
  -88,  -87,  -86,  -85,  -83,  -80,  -75,  -75, -351, -351,
 -351, -351, -351, -351,  -74, -351,  -70,  -69,  -68,  -75,
  -75,  -82, -103,    0,  -67,  -75,  -66, -384, -103, -354,
 -326, -323, -321, -317, -309,  -65,  -64,  -62,  -61,  -60,
  -58,  -84,  -75, -305,  -59,    0, -250,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -57,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -127, -127,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -127, -127,    0,    0,  -52,    0, -127,    0,  -55,
    0,  -52,  -54,    0,  -53,    0,  -51,    0,  -50,    0,
  -49,    0,  -48,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -127,  -47,    0,    0,  -63,  -43,  -42,  -41,  -40,
  -39,  -38,  -37,  -36,  -35,  -34,  -33,  -32,  -31,  -30,
  -29, -250,  -28,  -27,  -26,  -25,    0,    0,    0,    0,
    0,    0,    0,    0,  -23, -351,  -22,  -21,  -20,  -19,
 -351,  -18,  -17,  -16,  -14,  -13,  -12,  -11,  -10, -103,
   -7,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -52,    0,
};
static const short yyrindex[] = {                       130,
    0,    0,    0,    0,    0,    0,    0,  281,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   -6,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   -5,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   -4,   -3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   -2,   -1,    0,    0,    1,    0,    2,    0,    0,
    0,    3,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    4,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    5,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    6,    0,
};
static const short yygindex[] = {                         0,
    0,  279,    0,    0,    0,    0,    0,    0, -188, -102,
  239, -201,  283,    0,    0, -137,    0,    0,    0,   28,
};
#define YYTABLESIZE 413
static const short yytable[] = {                        228,
  282,   12,  222,  218,  219,  351,   25,   26,   27,   28,
   29,   30,   31,   32,   33,   34,   35,   36,  225,  336,
  337,  223,  226,  280,  281,   13,    1,    2,    3,    4,
   14,  261,  262,  263,  264,  265,  266,   15,  268,   25,
   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
   36,   37,  217,  283,  284,  338,  339,   38,   19,  340,
   39,  341,    5,   20,    6,  260,   40,   41,   21,  342,
   22,  343,  344,   23,   42,   43,   24,  272,  273,   44,
  345,  285,  286,  278,  287,  288,  289,  290,  218,  219,
  291,  292,  120,   45,  121,   46,  122,   47,  293,  294,
  332,  124,  333,  334,  123,  125,  126,   48,   49,  127,
   50,  128,   51,  346,  129,  130,  131,  347,  348,  349,
  350,  132,  133,  134,  135,  136,  137,  138,  139,    1,
  140,  141,  142,  143,  144,  145,  146,  147,  148,   52,
   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,
  351,  149,  208,  150,   63,   64,   65,   66,   67,   68,
   69,   70,   71,   72,  151,   73,   74,   75,   76,   77,
   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,
   88,   89,   90,   91,   92,   93,   94,  301,  302,  152,
  153,  401,  303,  154,  155,  156,  157,  158,  159,  160,
  161,  304,  305,  306,  307,  308,  309,  162,  163,  164,
  165,  166,  167,  168,  310,  311,  312,  313,  314,  315,
  169,  170,  171,  172,  173,  174,  175,  176,  387,  316,
  177,  178,  179,  392,  180,  181,  183,  210,  184,  185,
  186,  187,  317,  188,  189,  190,  191,  318,  319,  320,
  321,  322,  323,  324,  325,  326,  327,  192,   98,  328,
   99,  193,  194,  195,  329,  330,  196,  197,  100,  331,
  198,  199,  200,  201,  202,  203,  204,  355,  206,  101,
    2,  102,  209,  211,  212,  213,   18,  214,  215,  216,
  229,  230,  103,  104,  231,  232,  233,  234,  235,  236,
  237,  105,  238,  239,  240,  106,  275,  241,  242,  107,
  243,  244,  245,  108,  246,  247,  248,  249,  250,  251,
  252,  253,  254,  255,  274,  256,  109,  110,  257,  111,
  112,  113,  114,  258,  267,  115,  116,  117,  269,  270,
  271,  277,  365,  279,  295,  296,  297,  335,  298,  299,
  300,  354,  356,  357,  358,  359,  205,  360,  361,  362,
  363,  364,  366,  367,  368,  369,  370,  371,  372,  373,
  374,  375,  376,  377,  378,  379,  380,  182,  382,  381,
    0,  383,  384,    0,  385,  386,  388,  389,  390,  391,
  393,  394,  395,    0,  396,  397,  398,  399,  400,  402,
   14,   12,  105,  106,  107,  108,    0,  158,   55,   21,
   54,  157,  178,
};
static const short yycheck[] = {                        137,
  189,  406,  279,  355,  356,  207,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  325,  270,
  271,  298,  329,  408,  409,  406,  280,  281,  282,  283,
  406,  169,  170,  171,  172,  173,  174,  406,  176,  257,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  319,  408,  409,  306,  307,  275,  407,  310,
  278,  312,  316,  407,  318,  168,  284,  285,  410,  320,
  410,  322,  323,  410,  292,  293,  409,  180,  181,  297,
  331,  408,  409,  186,  408,  409,  408,  409,  355,  356,
  408,  409,  407,  311,  407,  313,  407,  315,  408,  409,
  203,  410,  408,  409,  407,  406,  406,  325,  326,  406,
  328,  406,  330,  364,  406,  406,  406,  368,  369,  370,
  371,  406,  406,  406,  406,  406,  406,  406,  406,    0,
  406,  406,  406,  406,  406,  406,  406,  406,  406,  357,
  358,  359,  360,  361,  362,  363,  364,  365,  366,  367,
  352,  406,  409,  406,  372,  373,  374,  375,  376,  377,
  378,  379,  380,  381,  406,  383,  384,  385,  386,  387,
  388,  389,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,  400,  401,  402,  403,  404,  272,  273,  406,
  406,  380,  277,  406,  406,  406,  406,  406,  406,  406,
  406,  286,  287,  288,  289,  290,  291,  406,  406,  406,
  406,  406,  406,  406,  299,  300,  301,  302,  303,  304,
  406,  406,  406,  406,  406,  406,  406,  406,  366,  314,
  406,  406,  406,  371,  406,  406,  406,  410,  407,  406,
  406,  406,  327,  406,  406,  406,  406,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  406,  274,  344,
  276,  406,  406,  406,  349,  350,  406,  406,  284,  354,
  406,  406,  406,  406,  406,  406,  406,  405,  407,  295,
    0,  297,  409,  409,  409,  409,    8,  410,  409,  409,
  409,  409,  308,  309,  409,  409,  409,  409,  409,  409,
  409,  317,  409,  409,  409,  321,  410,  409,  409,  325,
  409,  409,  409,  329,  409,  409,  409,  409,  409,  409,
  409,  409,  409,  409,  407,  409,  342,  343,  409,  345,
  346,  347,  348,  409,  409,  351,  352,  353,  409,  409,
  409,  409,  406,  410,  410,  410,  409,  407,  410,  410,
  409,  409,  405,  409,  409,  409,  118,  409,  409,  409,
  409,  409,  406,  406,  406,  406,  406,  406,  406,  406,
  406,  406,  406,  406,  406,  406,  406,   95,  407,  352,
   -1,  409,  409,   -1,  410,  409,  409,  409,  409,  409,
  409,  409,  409,   -1,  409,  409,  409,  409,  409,  407,
  407,  407,  407,  407,  407,  407,   -1,  407,  407,  407,
  407,  407,  407,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 411
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"K_READ","K_WRITE","K_READ_LO",
"K_READ_HI","K_WRITE_LO","K_WRITE_HI","K_LOADPAGE_LO","K_LOADPAGE_HI",
"K_LOAD_EXT_ADDR","K_WRITEPAGE","K_CHIP_ERASE","K_PGM_ENABLE","K_MEMORY",
"K_PAGE_SIZE","K_PAGED","K_ARDUINO","K_AVRFTDI","K_BAUDRATE","K_BS2","K_BUFF",
"K_BUSPIRATE","K_CHIP_ERASE_DELAY","K_DEDICATED","K_DEFAULT_PARALLEL",
"K_DEFAULT_PROGRAMMER","K_DEFAULT_SERIAL","K_DEFAULT_BITCLOCK","K_DESC",
"K_DEVICECODE","K_DRAGON_DW","K_DRAGON_HVSP","K_DRAGON_ISP","K_DRAGON_JTAG",
"K_DRAGON_PDI","K_DRAGON_PP","K_STK500_DEVCODE","K_AVR910_DEVCODE","K_EEPROM",
"K_ERRLED","K_FLASH","K_ID","K_IO","K_JTAG_MKI","K_JTAG_MKII",
"K_JTAG_MKII_AVR32","K_JTAG_MKII_DW","K_JTAG_MKII_ISP","K_JTAG_MKII_PDI",
"K_LOADPAGE","K_MAX_WRITE_DELAY","K_MIN_WRITE_DELAY","K_MISO","K_MOSI",
"K_NUM_PAGES","K_NVM_BASE","K_OFFSET","K_PAGEL","K_PAR","K_PARALLEL","K_PART",
"K_PGMLED","K_PROGRAMMER","K_PSEUDO","K_PWROFF_AFTER_WRITE","K_RDYLED",
"K_READBACK_P1","K_READBACK_P2","K_READMEM","K_RESET","K_RETRY_PULSE","K_SERBB",
"K_SERIAL","K_SCK","K_SIGNATURE","K_SIZE","K_STK500","K_STK500HVSP",
"K_STK500PP","K_STK500V2","K_STK500GENERIC","K_STK600","K_STK600HVSP",
"K_STK600PP","K_AVR910","K_USBASP","K_USBDEV","K_USBSN","K_USBTINY","K_USBPID",
"K_USBPRODUCT","K_USBVENDOR","K_USBVID","K_BUTTERFLY","K_BUTTERFLY_MK","K_TYPE",
"K_VCC","K_VFYLED","K_WIRING","K_NO","K_YES","K_TIMEOUT","K_STABDELAY",
"K_CMDEXEDELAY","K_HVSPCMDEXEDELAY","K_SYNCHLOOPS","K_BYTEDELAY","K_POLLVALUE",
"K_POLLINDEX","K_PREDELAY","K_POSTDELAY","K_POLLMETHOD","K_MODE","K_DELAY",
"K_BLOCKSIZE","K_READSIZE","K_HVENTERSTABDELAY","K_PROGMODEDELAY",
"K_LATCHCYCLES","K_TOGGLEVTG","K_POWEROFFDELAY","K_RESETDELAYMS",
"K_RESETDELAYUS","K_HVLEAVESTABDELAY","K_RESETDELAY","K_SYNCHCYCLES",
"K_HVCMDEXEDELAY","K_CHIPERASEPULSEWIDTH","K_CHIPERASEPOLLTIMEOUT",
"K_CHIPERASETIME","K_PROGRAMFUSEPULSEWIDTH","K_PROGRAMFUSEPOLLTIMEOUT",
"K_PROGRAMLOCKPULSEWIDTH","K_PROGRAMLOCKPOLLTIMEOUT","K_PP_CONTROLSTACK",
"K_HVSP_CONTROLSTACK","K_ALLOWFULLPAGEBITSTREAM","K_ENABLEPAGEPROGRAMMING",
"K_HAS_JTAG","K_HAS_DW","K_HAS_PDI","K_HAS_TPI","K_IDR","K_IS_AVR32","K_RAMPZ",
"K_SPMCR","K_EECR","K_FLASH_INSTR","K_EEPROM_INSTR","TKN_COMMA","TKN_EQUAL",
"TKN_SEMI","TKN_TILDE","TKN_NUMBER","TKN_STRING","TKN_ID",
};
static const char *yyrule[] = {
"$accept : configuration",
"configuration :",
"configuration : config",
"config : def",
"config : config def",
"def : prog_def TKN_SEMI",
"def : part_def TKN_SEMI",
"def : K_DEFAULT_PROGRAMMER TKN_EQUAL TKN_STRING TKN_SEMI",
"def : K_DEFAULT_PARALLEL TKN_EQUAL TKN_STRING TKN_SEMI",
"def : K_DEFAULT_SERIAL TKN_EQUAL TKN_STRING TKN_SEMI",
"def : K_DEFAULT_BITCLOCK TKN_EQUAL TKN_NUMBER TKN_SEMI",
"$$1 :",
"prog_def : K_PROGRAMMER $$1 prog_parms",
"$$2 :",
"part_def : K_PART $$2 part_parms",
"string_list : TKN_STRING",
"string_list : string_list TKN_COMMA TKN_STRING",
"num_list : TKN_NUMBER",
"num_list : num_list TKN_COMMA TKN_NUMBER",
"prog_parms : prog_parm TKN_SEMI",
"prog_parms : prog_parms prog_parm TKN_SEMI",
"prog_parm : K_ID TKN_EQUAL string_list",
"prog_parm : K_TYPE TKN_EQUAL K_PAR",
"prog_parm : K_TYPE TKN_EQUAL K_SERBB",
"prog_parm : K_TYPE TKN_EQUAL K_STK500",
"prog_parm : K_TYPE TKN_EQUAL K_STK500V2",
"prog_parm : K_TYPE TKN_EQUAL K_WIRING",
"prog_parm : K_TYPE TKN_EQUAL K_STK500HVSP",
"prog_parm : K_TYPE TKN_EQUAL K_STK500PP",
"prog_parm : K_TYPE TKN_EQUAL K_STK500GENERIC",
"prog_parm : K_TYPE TKN_EQUAL K_ARDUINO",
"prog_parm : K_TYPE TKN_EQUAL K_AVRFTDI",
"prog_parm : K_TYPE TKN_EQUAL K_BUSPIRATE",
"prog_parm : K_TYPE TKN_EQUAL K_STK600",
"prog_parm : K_TYPE TKN_EQUAL K_STK600HVSP",
"prog_parm : K_TYPE TKN_EQUAL K_STK600PP",
"prog_parm : K_TYPE TKN_EQUAL K_AVR910",
"prog_parm : K_TYPE TKN_EQUAL K_USBASP",
"prog_parm : K_TYPE TKN_EQUAL K_USBTINY",
"prog_parm : K_TYPE TKN_EQUAL K_BUTTERFLY",
"prog_parm : K_TYPE TKN_EQUAL K_BUTTERFLY_MK",
"prog_parm : K_TYPE TKN_EQUAL K_JTAG_MKI",
"prog_parm : K_TYPE TKN_EQUAL K_JTAG_MKII",
"prog_parm : K_TYPE TKN_EQUAL K_JTAG_MKII_AVR32",
"prog_parm : K_TYPE TKN_EQUAL K_JTAG_MKII_DW",
"prog_parm : K_TYPE TKN_EQUAL K_JTAG_MKII_ISP",
"prog_parm : K_TYPE TKN_EQUAL K_JTAG_MKII_PDI",
"prog_parm : K_TYPE TKN_EQUAL K_DRAGON_DW",
"prog_parm : K_TYPE TKN_EQUAL K_DRAGON_HVSP",
"prog_parm : K_TYPE TKN_EQUAL K_DRAGON_ISP",
"prog_parm : K_TYPE TKN_EQUAL K_DRAGON_JTAG",
"prog_parm : K_TYPE TKN_EQUAL K_DRAGON_PDI",
"prog_parm : K_TYPE TKN_EQUAL K_DRAGON_PP",
"prog_parm : K_DESC TKN_EQUAL TKN_STRING",
"prog_parm : K_VCC TKN_EQUAL num_list",
"prog_parm : K_BUFF TKN_EQUAL num_list",
"prog_parm : K_USBDEV TKN_EQUAL TKN_STRING",
"prog_parm : K_USBVID TKN_EQUAL TKN_NUMBER",
"prog_parm : K_USBPID TKN_EQUAL TKN_NUMBER",
"prog_parm : K_USBSN TKN_EQUAL TKN_STRING",
"prog_parm : K_USBVENDOR TKN_EQUAL TKN_STRING",
"prog_parm : K_USBPRODUCT TKN_EQUAL TKN_STRING",
"prog_parm : K_BAUDRATE TKN_EQUAL TKN_NUMBER",
"prog_parm : K_RESET TKN_EQUAL TKN_NUMBER",
"prog_parm : K_SCK TKN_EQUAL TKN_NUMBER",
"prog_parm : K_MOSI TKN_EQUAL TKN_NUMBER",
"prog_parm : K_MISO TKN_EQUAL TKN_NUMBER",
"prog_parm : K_ERRLED TKN_EQUAL TKN_NUMBER",
"prog_parm : K_RDYLED TKN_EQUAL TKN_NUMBER",
"prog_parm : K_PGMLED TKN_EQUAL TKN_NUMBER",
"prog_parm : K_VFYLED TKN_EQUAL TKN_NUMBER",
"prog_parm : K_RESET TKN_EQUAL TKN_TILDE TKN_NUMBER",
"prog_parm : K_SCK TKN_EQUAL TKN_TILDE TKN_NUMBER",
"prog_parm : K_MOSI TKN_EQUAL TKN_TILDE TKN_NUMBER",
"prog_parm : K_MISO TKN_EQUAL TKN_TILDE TKN_NUMBER",
"prog_parm : K_ERRLED TKN_EQUAL TKN_TILDE TKN_NUMBER",
"prog_parm : K_RDYLED TKN_EQUAL TKN_TILDE TKN_NUMBER",
"prog_parm : K_PGMLED TKN_EQUAL TKN_TILDE TKN_NUMBER",
"prog_parm : K_VFYLED TKN_EQUAL TKN_TILDE TKN_NUMBER",
"opcode : K_READ",
"opcode : K_WRITE",
"opcode : K_READ_LO",
"opcode : K_READ_HI",
"opcode : K_WRITE_LO",
"opcode : K_WRITE_HI",
"opcode : K_LOADPAGE_LO",
"opcode : K_LOADPAGE_HI",
"opcode : K_LOAD_EXT_ADDR",
"opcode : K_WRITEPAGE",
"opcode : K_CHIP_ERASE",
"opcode : K_PGM_ENABLE",
"part_parms : part_parm TKN_SEMI",
"part_parms : part_parms part_parm TKN_SEMI",
"reset_disposition : K_DEDICATED",
"reset_disposition : K_IO",
"parallel_modes : yesno",
"parallel_modes : K_PSEUDO",
"retry_lines : K_RESET",
"retry_lines : K_SCK",
"part_parm : K_ID TKN_EQUAL TKN_STRING",
"part_parm : K_DESC TKN_EQUAL TKN_STRING",
"part_parm : K_DEVICECODE TKN_EQUAL TKN_NUMBER",
"part_parm : K_STK500_DEVCODE TKN_EQUAL TKN_NUMBER",
"part_parm : K_AVR910_DEVCODE TKN_EQUAL TKN_NUMBER",
"part_parm : K_SIGNATURE TKN_EQUAL TKN_NUMBER TKN_NUMBER TKN_NUMBER",
"part_parm : K_PP_CONTROLSTACK TKN_EQUAL num_list",
"part_parm : K_HVSP_CONTROLSTACK TKN_EQUAL num_list",
"part_parm : K_FLASH_INSTR TKN_EQUAL num_list",
"part_parm : K_EEPROM_INSTR TKN_EQUAL num_list",
"part_parm : K_CHIP_ERASE_DELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_PAGEL TKN_EQUAL TKN_NUMBER",
"part_parm : K_BS2 TKN_EQUAL TKN_NUMBER",
"part_parm : K_RESET TKN_EQUAL reset_disposition",
"part_parm : K_TIMEOUT TKN_EQUAL TKN_NUMBER",
"part_parm : K_STABDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_CMDEXEDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_HVSPCMDEXEDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_SYNCHLOOPS TKN_EQUAL TKN_NUMBER",
"part_parm : K_BYTEDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_POLLVALUE TKN_EQUAL TKN_NUMBER",
"part_parm : K_POLLINDEX TKN_EQUAL TKN_NUMBER",
"part_parm : K_PREDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_POSTDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_POLLMETHOD TKN_EQUAL TKN_NUMBER",
"part_parm : K_HVENTERSTABDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_PROGMODEDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_LATCHCYCLES TKN_EQUAL TKN_NUMBER",
"part_parm : K_TOGGLEVTG TKN_EQUAL TKN_NUMBER",
"part_parm : K_POWEROFFDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_RESETDELAYMS TKN_EQUAL TKN_NUMBER",
"part_parm : K_RESETDELAYUS TKN_EQUAL TKN_NUMBER",
"part_parm : K_HVLEAVESTABDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_RESETDELAY TKN_EQUAL TKN_NUMBER",
"part_parm : K_CHIPERASEPULSEWIDTH TKN_EQUAL TKN_NUMBER",
"part_parm : K_CHIPERASEPOLLTIMEOUT TKN_EQUAL TKN_NUMBER",
"part_parm : K_CHIPERASETIME TKN_EQUAL TKN_NUMBER",
"part_parm : K_PROGRAMFUSEPULSEWIDTH TKN_EQUAL TKN_NUMBER",
"part_parm : K_PROGRAMFUSEPOLLTIMEOUT TKN_EQUAL TKN_NUMBER",
"part_parm : K_PROGRAMLOCKPULSEWIDTH TKN_EQUAL TKN_NUMBER",
"part_parm : K_PROGRAMLOCKPOLLTIMEOUT TKN_EQUAL TKN_NUMBER",
"part_parm : K_SYNCHCYCLES TKN_EQUAL TKN_NUMBER",
"part_parm : K_HAS_JTAG TKN_EQUAL yesno",
"part_parm : K_HAS_DW TKN_EQUAL yesno",
"part_parm : K_HAS_PDI TKN_EQUAL yesno",
"part_parm : K_HAS_TPI TKN_EQUAL yesno",
"part_parm : K_IS_AVR32 TKN_EQUAL yesno",
"part_parm : K_ALLOWFULLPAGEBITSTREAM TKN_EQUAL yesno",
"part_parm : K_ENABLEPAGEPROGRAMMING TKN_EQUAL yesno",
"part_parm : K_IDR TKN_EQUAL TKN_NUMBER",
"part_parm : K_RAMPZ TKN_EQUAL TKN_NUMBER",
"part_parm : K_SPMCR TKN_EQUAL TKN_NUMBER",
"part_parm : K_EECR TKN_EQUAL TKN_NUMBER",
"part_parm : K_NVM_BASE TKN_EQUAL TKN_NUMBER",
"part_parm : K_SERIAL TKN_EQUAL yesno",
"part_parm : K_PARALLEL TKN_EQUAL parallel_modes",
"part_parm : K_RETRY_PULSE TKN_EQUAL retry_lines",
"$$3 :",
"part_parm : K_MEMORY TKN_STRING $$3 mem_specs",
"part_parm : opcode TKN_EQUAL string_list",
"yesno : K_YES",
"yesno : K_NO",
"mem_specs : mem_spec TKN_SEMI",
"mem_specs : mem_specs mem_spec TKN_SEMI",
"mem_spec : K_PAGED TKN_EQUAL yesno",
"mem_spec : K_SIZE TKN_EQUAL TKN_NUMBER",
"mem_spec : K_PAGE_SIZE TKN_EQUAL TKN_NUMBER",
"mem_spec : K_NUM_PAGES TKN_EQUAL TKN_NUMBER",
"mem_spec : K_OFFSET TKN_EQUAL TKN_NUMBER",
"mem_spec : K_MIN_WRITE_DELAY TKN_EQUAL TKN_NUMBER",
"mem_spec : K_MAX_WRITE_DELAY TKN_EQUAL TKN_NUMBER",
"mem_spec : K_PWROFF_AFTER_WRITE TKN_EQUAL yesno",
"mem_spec : K_READBACK_P1 TKN_EQUAL TKN_NUMBER",
"mem_spec : K_READBACK_P2 TKN_EQUAL TKN_NUMBER",
"mem_spec : K_MODE TKN_EQUAL TKN_NUMBER",
"mem_spec : K_DELAY TKN_EQUAL TKN_NUMBER",
"mem_spec : K_BLOCKSIZE TKN_EQUAL TKN_NUMBER",
"mem_spec : K_READSIZE TKN_EQUAL TKN_NUMBER",
"mem_spec : K_POLLINDEX TKN_EQUAL TKN_NUMBER",
"mem_spec : opcode TKN_EQUAL string_list",

};
#endif
/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 1431 "config_gram.y"

#if 0
static char * vtypestr(int type)
{
  switch (type) {
    case V_NUM : return "NUMERIC";
    case V_STR : return "STRING";
    default:
      return "<UNKNOWN>";
  }
}
#endif


static int assign_pin(int pinno, TOKEN * v, int invert)
{
  int value;

  value = v->value.number;

  if ((value <= 0) || (value >= 18)) {
    fprintf(stderr, 
            "%s: error at line %d of %s: pin must be in the "
            "range 1-17\n",
            progname, lineno, infile);
    exit(1);
  }
  if (invert)
    value |= PIN_INVERSE;

  current_prog->pinno[pinno] = value;

  return 0;
}


static int which_opcode(TOKEN * opcode)
{
  switch (opcode->primary) {
    case K_READ        : return AVR_OP_READ; break;
    case K_WRITE       : return AVR_OP_WRITE; break;
    case K_READ_LO     : return AVR_OP_READ_LO; break;
    case K_READ_HI     : return AVR_OP_READ_HI; break;
    case K_WRITE_LO    : return AVR_OP_WRITE_LO; break;
    case K_WRITE_HI    : return AVR_OP_WRITE_HI; break;
    case K_LOADPAGE_LO : return AVR_OP_LOADPAGE_LO; break;
    case K_LOADPAGE_HI : return AVR_OP_LOADPAGE_HI; break;
    case K_LOAD_EXT_ADDR : return AVR_OP_LOAD_EXT_ADDR; break;
    case K_WRITEPAGE   : return AVR_OP_WRITEPAGE; break;
    case K_CHIP_ERASE  : return AVR_OP_CHIP_ERASE; break;
    case K_PGM_ENABLE  : return AVR_OP_PGM_ENABLE; break;
    default :
      fprintf(stderr, 
              "%s: error at %s:%d: invalid opcode\n",
              progname, infile, lineno);
      exit(1);
      break;
  }
}


static int parse_cmdbits(OPCODE * op)
{
  TOKEN * t;
  int bitno;
  char ch;
  char * e;
  char * q;
  int len;
  char * s, *brkt = NULL;

  bitno = 32;
  while (lsize(string_list)) {

    t = lrmv_n(string_list, 1);

    s = strtok_r(t->value.string, " ", &brkt);
    while (s != NULL) {

      bitno--;
      if (bitno < 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: too many opcode bits for instruction\n",
                progname, infile, lineno);
        exit(1);
      }

      len = strlen(s);

      if (len == 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: invalid bit specifier \"\"\n",
                progname, infile, lineno);
        exit(1);
      }

      ch = s[0];

      if (len == 1) {
        switch (ch) {
          case '1':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 1;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case '0':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'x':
            op->bit[bitno].type  = AVR_CMDBIT_IGNORE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'a':
            op->bit[bitno].type  = AVR_CMDBIT_ADDRESS;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = 8*(bitno/8) + bitno % 8;
            break;
          case 'i':
            op->bit[bitno].type  = AVR_CMDBIT_INPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'o':
            op->bit[bitno].type  = AVR_CMDBIT_OUTPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          default :
            fprintf(stderr, 
                    "%s: error at %s:%d: invalid bit specifier '%c'\n",
                    progname, infile, lineno, ch);
            exit(1);
            break;
        }
      }
      else {
        if (ch == 'a') {
          q = &s[1];
          op->bit[bitno].bitno = strtol(q, &e, 0);
          if ((e == q)||(*e != 0)) {
            fprintf(stderr, 
                    "%s: error at %s:%d: can't parse bit number from \"%s\"\n",
                    progname, infile, lineno, q);
            exit(1);
          }
          op->bit[bitno].type = AVR_CMDBIT_ADDRESS;
          op->bit[bitno].value = 0;
        }
        else {
          fprintf(stderr, 
                  "%s: error at %s:%d: invalid bit specifier \"%s\"\n",
                  progname, infile, lineno, s);
          exit(1);
        }
      }

      s = strtok_r(NULL, " ", &brkt);
    }

    free_token(t);

  }  /* while */

  return 0;
}


#line 951 "config_gram.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 7:
#line 262 "config_gram.y"
	{
    strncpy(default_programmer, yystack.l_mark[-1]->value.string, MAX_STR_CONST);
    default_programmer[MAX_STR_CONST-1] = 0;
    free_token(yystack.l_mark[-1]);
  }
break;
case 8:
#line 268 "config_gram.y"
	{
    strncpy(default_parallel, yystack.l_mark[-1]->value.string, PATH_MAX);
    default_parallel[PATH_MAX-1] = 0;
    free_token(yystack.l_mark[-1]);
  }
break;
case 9:
#line 274 "config_gram.y"
	{
    strncpy(default_serial, yystack.l_mark[-1]->value.string, PATH_MAX);
    default_serial[PATH_MAX-1] = 0;
    free_token(yystack.l_mark[-1]);
  }
break;
case 10:
#line 280 "config_gram.y"
	{
    default_bitclock = yystack.l_mark[-1]->value.number;
    free_token(yystack.l_mark[-1]);
  }
break;
case 11:
#line 289 "config_gram.y"
	{ current_prog = pgm_new();
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
    }
break;
case 12:
#line 294 "config_gram.y"
	{ 
      if (lsize(current_prog->id) == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      if (current_prog->type[0] == 0) {
        fprintf(stderr, "%s: error at %s:%d: programmer type not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      PUSH(programmers, current_prog); 
      current_prog = NULL; 
    }
break;
case 13:
#line 314 "config_gram.y"
	{
      current_part = avr_new_part();
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;
    }
break;
case 14:
#line 320 "config_gram.y"
	{ 
      LNODEID ln;
      AVRMEM * m;

      if (current_part->id[0] == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }

      /*
       * perform some sanity checking, and compute the number of bits
       * to shift a page for constructing the page address for
       * page-addressed memories.
       */
      for (ln=lfirst(current_part->mem); ln; ln=lnext(ln)) {
        m = ldata(ln);
        if (m->paged) {
          if (m->page_size == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify page_size for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->num_pages == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify num_pages for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->size != m->page_size * m->num_pages) {
            fprintf(stderr, 
                    "%s: error at %s:%d: page size (%u) * num_pages (%u) = "
                    "%u does not match memory size (%u)\n",
                    progname, infile, lineno,
                    m->page_size, 
                    m->num_pages, 
                    m->page_size * m->num_pages,
                    m->size);
            exit(1);
          }

        }
      }

      PUSH(part_list, current_part); 
      current_part = NULL; 
    }
break;
case 15:
#line 375 "config_gram.y"
	{ ladd(string_list, yystack.l_mark[0]); }
break;
case 16:
#line 376 "config_gram.y"
	{ ladd(string_list, yystack.l_mark[0]); }
break;
case 17:
#line 381 "config_gram.y"
	{ ladd(number_list, yystack.l_mark[0]); }
break;
case 18:
#line 382 "config_gram.y"
	{ ladd(number_list, yystack.l_mark[0]); }
break;
case 21:
#line 393 "config_gram.y"
	{
    { 
      TOKEN * t;
      while (lsize(string_list)) {
        t = lrmv_n(string_list, 1);
        ladd(current_prog->id, dup_string(t->value.string));
        free_token(t);
      }
    }
  }
break;
case 22:
#line 404 "config_gram.y"
	{
    { 
      par_initpgm(current_prog);
    }
  }
break;
case 23:
#line 410 "config_gram.y"
	{
    {
      serbb_initpgm(current_prog);
    }
  }
break;
case 24:
#line 416 "config_gram.y"
	{
    { 
      stk500_initpgm(current_prog);
    }
  }
break;
case 25:
#line 422 "config_gram.y"
	{
    {
      stk500v2_initpgm(current_prog);
    }
  }
break;
case 26:
#line 428 "config_gram.y"
	{
    {
      wiring_initpgm(current_prog);
    }
  }
break;
case 27:
#line 434 "config_gram.y"
	{
    {
      stk500hvsp_initpgm(current_prog);
    }
  }
break;
case 28:
#line 440 "config_gram.y"
	{
    {
      stk500pp_initpgm(current_prog);
    }
  }
break;
case 29:
#line 446 "config_gram.y"
	{
    {
      stk500generic_initpgm(current_prog);
    }
  }
break;
case 30:
#line 452 "config_gram.y"
	{
    { 
      arduino_initpgm(current_prog);
    }
  }
break;
case 31:
#line 458 "config_gram.y"
	{
    {
      avrftdi_initpgm(current_prog);
    }
  }
break;
case 32:
#line 464 "config_gram.y"
	{
    {
      buspirate_initpgm(current_prog);
    }
  }
break;
case 33:
#line 470 "config_gram.y"
	{
    {
      stk600_initpgm(current_prog);
    }
  }
break;
case 34:
#line 476 "config_gram.y"
	{
    {
      stk600hvsp_initpgm(current_prog);
    }
  }
break;
case 35:
#line 482 "config_gram.y"
	{
    {
      stk600pp_initpgm(current_prog);
    }
  }
break;
case 36:
#line 488 "config_gram.y"
	{
    { 
      avr910_initpgm(current_prog);
    }
  }
break;
case 37:
#line 494 "config_gram.y"
	{
    {
      usbasp_initpgm(current_prog);
    }
  }
break;
case 38:
#line 500 "config_gram.y"
	{
    {
      usbtiny_initpgm(current_prog);
    }
  }
break;
case 39:
#line 506 "config_gram.y"
	{
    { 
      butterfly_initpgm(current_prog);
    }
  }
break;
case 40:
#line 512 "config_gram.y"
	{
    { 
      butterfly_mk_initpgm(current_prog);
    }
  }
break;
case 41:
#line 518 "config_gram.y"
	{
    {
      jtagmkI_initpgm(current_prog);
    }
  }
break;
case 42:
#line 524 "config_gram.y"
	{
    {
      jtagmkII_initpgm(current_prog);
    }
  }
break;
case 43:
#line 529 "config_gram.y"
	{
    {
      jtagmkII_avr32_initpgm(current_prog);
    }
  }
break;
case 44:
#line 535 "config_gram.y"
	{
    {
      jtagmkII_dw_initpgm(current_prog);
    }
  }
break;
case 45:
#line 541 "config_gram.y"
	{
    {
      stk500v2_jtagmkII_initpgm(current_prog);
    }
  }
break;
case 46:
#line 547 "config_gram.y"
	{
    {
      jtagmkII_pdi_initpgm(current_prog);
    }
  }
break;
case 47:
#line 553 "config_gram.y"
	{
    {
      jtagmkII_dragon_dw_initpgm(current_prog);
    }
  }
break;
case 48:
#line 559 "config_gram.y"
	{
    {
      stk500v2_dragon_hvsp_initpgm(current_prog);
    }
  }
break;
case 49:
#line 565 "config_gram.y"
	{
    {
      stk500v2_dragon_isp_initpgm(current_prog);
    }
  }
break;
case 50:
#line 571 "config_gram.y"
	{
    {
      jtagmkII_dragon_initpgm(current_prog);
    }
  }
break;
case 51:
#line 577 "config_gram.y"
	{
    {
      jtagmkII_dragon_pdi_initpgm(current_prog);
    }
  }
break;
case 52:
#line 583 "config_gram.y"
	{
    {
      stk500v2_dragon_pp_initpgm(current_prog);
    }
  }
break;
case 53:
#line 589 "config_gram.y"
	{
    strncpy(current_prog->desc, yystack.l_mark[0]->value.string, PGM_DESCLEN);
    current_prog->desc[PGM_DESCLEN-1] = 0;
    free_token(yystack.l_mark[0]);
  }
break;
case 54:
#line 595 "config_gram.y"
	{
    { 
      TOKEN * t;
      int pin;

      current_prog->pinno[PPI_AVR_VCC] = 0;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
        pin = t->value.number;
        current_prog->pinno[PPI_AVR_VCC] |= (1 << pin);

        free_token(t);
      }
    }
  }
break;
case 55:
#line 612 "config_gram.y"
	{
    { 
      TOKEN * t;
      int pin;

      current_prog->pinno[PPI_AVR_BUFF] = 0;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
        pin = t->value.number;
        current_prog->pinno[PPI_AVR_BUFF] |= (1 << pin);

        free_token(t);
      }
    }
  }
break;
case 56:
#line 628 "config_gram.y"
	{
    {
      strncpy(current_prog->usbdev, yystack.l_mark[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbdev[PGM_USBSTRINGLEN-1] = 0;
      free_token(yystack.l_mark[0]);
    }
  }
break;
case 57:
#line 635 "config_gram.y"
	{
    {
      current_prog->usbvid = yystack.l_mark[0]->value.number;
    }
  }
break;
case 58:
#line 641 "config_gram.y"
	{
    {
      current_prog->usbpid = yystack.l_mark[0]->value.number;
    }
  }
break;
case 59:
#line 647 "config_gram.y"
	{
    {
      strncpy(current_prog->usbsn, yystack.l_mark[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbsn[PGM_USBSTRINGLEN-1] = 0;
      free_token(yystack.l_mark[0]);
    }
  }
break;
case 60:
#line 655 "config_gram.y"
	{
    {
      strncpy(current_prog->usbvendor, yystack.l_mark[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbvendor[PGM_USBSTRINGLEN-1] = 0;
      free_token(yystack.l_mark[0]);
    }
  }
break;
case 61:
#line 663 "config_gram.y"
	{
    {
      strncpy(current_prog->usbproduct, yystack.l_mark[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbproduct[PGM_USBSTRINGLEN-1] = 0;
      free_token(yystack.l_mark[0]);
    }
  }
break;
case 62:
#line 671 "config_gram.y"
	{
    {
      current_prog->baudrate = yystack.l_mark[0]->value.number;
    }
  }
break;
case 63:
#line 677 "config_gram.y"
	{ free_token(yystack.l_mark[-2]); 
                                  assign_pin(PIN_AVR_RESET, yystack.l_mark[0], 0); }
break;
case 64:
#line 679 "config_gram.y"
	{ free_token(yystack.l_mark[-2]); 
                                  assign_pin(PIN_AVR_SCK, yystack.l_mark[0], 0); }
break;
case 65:
#line 681 "config_gram.y"
	{ assign_pin(PIN_AVR_MOSI, yystack.l_mark[0], 0); }
break;
case 66:
#line 682 "config_gram.y"
	{ assign_pin(PIN_AVR_MISO, yystack.l_mark[0], 0); }
break;
case 67:
#line 683 "config_gram.y"
	{ assign_pin(PIN_LED_ERR, yystack.l_mark[0], 0); }
break;
case 68:
#line 684 "config_gram.y"
	{ assign_pin(PIN_LED_RDY, yystack.l_mark[0], 0); }
break;
case 69:
#line 685 "config_gram.y"
	{ assign_pin(PIN_LED_PGM, yystack.l_mark[0], 0); }
break;
case 70:
#line 686 "config_gram.y"
	{ assign_pin(PIN_LED_VFY, yystack.l_mark[0], 0); }
break;
case 71:
#line 688 "config_gram.y"
	{ free_token(yystack.l_mark[-3]); 
                                  assign_pin(PIN_AVR_RESET, yystack.l_mark[0], 1); }
break;
case 72:
#line 690 "config_gram.y"
	{ free_token(yystack.l_mark[-3]); 
                                  assign_pin(PIN_AVR_SCK, yystack.l_mark[0], 1); }
break;
case 73:
#line 692 "config_gram.y"
	{ assign_pin(PIN_AVR_MOSI, yystack.l_mark[0], 1); }
break;
case 74:
#line 693 "config_gram.y"
	{ assign_pin(PIN_AVR_MISO, yystack.l_mark[0], 1); }
break;
case 75:
#line 694 "config_gram.y"
	{ assign_pin(PIN_LED_ERR, yystack.l_mark[0], 1); }
break;
case 76:
#line 695 "config_gram.y"
	{ assign_pin(PIN_LED_RDY, yystack.l_mark[0], 1); }
break;
case 77:
#line 696 "config_gram.y"
	{ assign_pin(PIN_LED_PGM, yystack.l_mark[0], 1); }
break;
case 78:
#line 697 "config_gram.y"
	{ assign_pin(PIN_LED_VFY, yystack.l_mark[0], 1); }
break;
case 99:
#line 737 "config_gram.y"
	{
      strncpy(current_part->id, yystack.l_mark[0]->value.string, AVR_IDLEN);
      current_part->id[AVR_IDLEN-1] = 0;
      free_token(yystack.l_mark[0]);
    }
break;
case 100:
#line 744 "config_gram.y"
	{
      strncpy(current_part->desc, yystack.l_mark[0]->value.string, AVR_DESCLEN);
      current_part->desc[AVR_DESCLEN-1] = 0;
      free_token(yystack.l_mark[0]);
    }
break;
case 101:
#line 750 "config_gram.y"
	{
    {
      fprintf(stderr, 
              "%s: error at %s:%d: devicecode is deprecated, use "
              "stk500_devcode instead\n",
              progname, infile, lineno);
      exit(1);
    }
  }
break;
case 102:
#line 760 "config_gram.y"
	{
    {
      current_part->stk500_devcode = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
  }
break;
case 103:
#line 767 "config_gram.y"
	{
    {
      current_part->avr910_devcode = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
  }
break;
case 104:
#line 774 "config_gram.y"
	{
    {
      current_part->signature[0] = yystack.l_mark[-2]->value.number;
      current_part->signature[1] = yystack.l_mark[-1]->value.number;
      current_part->signature[2] = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[-2]);
      free_token(yystack.l_mark[-1]);
      free_token(yystack.l_mark[0]);
    }
  }
break;
case 105:
#line 785 "config_gram.y"
	{
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      if (current_part->ctl_stack_type != CTL_STACK_NONE)
	{
	  fprintf(stderr,
		  "%s: error at line %d of %s: "
		  "control stack already defined\n",
		  progname, lineno, infile);
	  exit(1);
	}

      current_part->ctl_stack_type = CTL_STACK_PP;
      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
break;
case 106:
#line 827 "config_gram.y"
	{
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      if (current_part->ctl_stack_type != CTL_STACK_NONE)
	{
	  fprintf(stderr,
		  "%s: error at line %d of %s: "
		  "control stack already defined\n",
		  progname, lineno, infile);
	  exit(1);
	}

      current_part->ctl_stack_type = CTL_STACK_HVSP;
      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
break;
case 107:
#line 869 "config_gram.y"
	{
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < FLASH_INSTR_SIZE)
	  {
	    current_part->flash_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in flash instructions\n",
                  progname, lineno, infile);
        }
    }
  }
break;
case 108:
#line 901 "config_gram.y"
	{
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < EEPROM_INSTR_SIZE)
	  {
	    current_part->eeprom_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in EEPROM instructions\n",
                  progname, lineno, infile);
        }
    }
  }
break;
case 109:
#line 934 "config_gram.y"
	{
      current_part->chip_erase_delay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 110:
#line 940 "config_gram.y"
	{
      current_part->pagel = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 111:
#line 946 "config_gram.y"
	{
      current_part->bs2 = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 112:
#line 952 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_DEDICATED)
        current_part->reset_disposition = RESET_DEDICATED;
      else if (yystack.l_mark[0]->primary == K_IO)
        current_part->reset_disposition = RESET_IO;

      free_tokens(2, yystack.l_mark[-2], yystack.l_mark[0]);
    }
break;
case 113:
#line 962 "config_gram.y"
	{
      current_part->timeout = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 114:
#line 968 "config_gram.y"
	{
      current_part->stabdelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 115:
#line 974 "config_gram.y"
	{
      current_part->cmdexedelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 116:
#line 980 "config_gram.y"
	{
      current_part->hvspcmdexedelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 117:
#line 986 "config_gram.y"
	{
      current_part->synchloops = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 118:
#line 992 "config_gram.y"
	{
      current_part->bytedelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 119:
#line 998 "config_gram.y"
	{
      current_part->pollvalue = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 120:
#line 1004 "config_gram.y"
	{
      current_part->pollindex = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 121:
#line 1010 "config_gram.y"
	{
      current_part->predelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 122:
#line 1016 "config_gram.y"
	{
      current_part->postdelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 123:
#line 1022 "config_gram.y"
	{
      current_part->pollmethod = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 124:
#line 1028 "config_gram.y"
	{
      current_part->hventerstabdelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 125:
#line 1034 "config_gram.y"
	{
      current_part->progmodedelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 126:
#line 1040 "config_gram.y"
	{
      current_part->latchcycles = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 127:
#line 1046 "config_gram.y"
	{
      current_part->togglevtg = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 128:
#line 1052 "config_gram.y"
	{
      current_part->poweroffdelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 129:
#line 1058 "config_gram.y"
	{
      current_part->resetdelayms = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 130:
#line 1064 "config_gram.y"
	{
      current_part->resetdelayus = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 131:
#line 1070 "config_gram.y"
	{
      current_part->hvleavestabdelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 132:
#line 1076 "config_gram.y"
	{
      current_part->resetdelay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 133:
#line 1082 "config_gram.y"
	{
      current_part->chiperasepulsewidth = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 134:
#line 1088 "config_gram.y"
	{
      current_part->chiperasepolltimeout = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 135:
#line 1094 "config_gram.y"
	{
      current_part->chiperasetime = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 136:
#line 1100 "config_gram.y"
	{
      current_part->programfusepulsewidth = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 137:
#line 1106 "config_gram.y"
	{
      current_part->programfusepolltimeout = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 138:
#line 1112 "config_gram.y"
	{
      current_part->programlockpulsewidth = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 139:
#line 1118 "config_gram.y"
	{
      current_part->programlockpolltimeout = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 140:
#line 1124 "config_gram.y"
	{
      current_part->synchcycles = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 141:
#line 1130 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_JTAG;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_JTAG;

      free_token(yystack.l_mark[0]);
    }
break;
case 142:
#line 1140 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_DW;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_DW;

      free_token(yystack.l_mark[0]);
    }
break;
case 143:
#line 1150 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_PDI;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_PDI;

      free_token(yystack.l_mark[0]);
    }
break;
case 144:
#line 1160 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_TPI;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_TPI;

      free_token(yystack.l_mark[0]);
    }
break;
case 145:
#line 1170 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_AVR32;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= AVRPART_AVR32;

      free_token(yystack.l_mark[0]);
    }
break;
case 146:
#line 1180 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_ALLOWFULLPAGEBITSTREAM;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_ALLOWFULLPAGEBITSTREAM;

      free_token(yystack.l_mark[0]);
    }
break;
case 147:
#line 1190 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_ENABLEPAGEPROGRAMMING;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_ENABLEPAGEPROGRAMMING;

      free_token(yystack.l_mark[0]);
    }
break;
case 148:
#line 1200 "config_gram.y"
	{
      current_part->idr = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 149:
#line 1206 "config_gram.y"
	{
      current_part->rampz = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 150:
#line 1212 "config_gram.y"
	{
      current_part->spmcr = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 151:
#line 1218 "config_gram.y"
	{
      current_part->eecr = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 152:
#line 1224 "config_gram.y"
	{
      current_part->nvm_base = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 153:
#line 1230 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES)
        current_part->flags |= AVRPART_SERIALOK;
      else if (yystack.l_mark[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_SERIALOK;

      free_token(yystack.l_mark[0]);
    }
break;
case 154:
#line 1240 "config_gram.y"
	{
      if (yystack.l_mark[0]->primary == K_YES) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if (yystack.l_mark[0]->primary == K_NO) {
        current_part->flags &= ~AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if (yystack.l_mark[0]->primary == K_PSEUDO) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags |= AVRPART_PSEUDOPARALLEL;
      }


      free_token(yystack.l_mark[0]);
    }
break;
case 155:
#line 1259 "config_gram.y"
	{
      switch (yystack.l_mark[0]->primary) {
        case K_RESET :
          current_part->retry_pulse = PIN_AVR_RESET;
          break;
        case K_SCK :
          current_part->retry_pulse = PIN_AVR_SCK;
          break;
      }

      free_token(yystack.l_mark[-2]);
    }
break;
case 156:
#line 1282 "config_gram.y"
	{ 
      current_mem = avr_new_memtype(); 
      strcpy(current_mem->desc, strdup(yystack.l_mark[0]->value.string)); 
      free_token(yystack.l_mark[0]); 
    }
break;
case 157:
#line 1288 "config_gram.y"
	{ 
      ladd(current_part->mem, current_mem); 
      current_mem = NULL; 
    }
break;
case 158:
#line 1293 "config_gram.y"
	{
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode(yystack.l_mark[-2]);
      op = avr_new_opcode();
      parse_cmdbits(op);
      current_part->op[opnum] = op;

      free_token(yystack.l_mark[-2]);
    }
  }
break;
case 163:
#line 1322 "config_gram.y"
	{
      current_mem->paged = yystack.l_mark[0]->primary == K_YES ? 1 : 0;
      free_token(yystack.l_mark[0]);
    }
break;
case 164:
#line 1328 "config_gram.y"
	{
      current_mem->size = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 165:
#line 1335 "config_gram.y"
	{
      current_mem->page_size = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 166:
#line 1341 "config_gram.y"
	{
      current_mem->num_pages = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 167:
#line 1347 "config_gram.y"
	{
      current_mem->offset = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 168:
#line 1353 "config_gram.y"
	{
      current_mem->min_write_delay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 169:
#line 1359 "config_gram.y"
	{
      current_mem->max_write_delay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 170:
#line 1365 "config_gram.y"
	{
      current_mem->pwroff_after_write = yystack.l_mark[0]->primary == K_YES ? 1 : 0;
      free_token(yystack.l_mark[0]);
    }
break;
case 171:
#line 1371 "config_gram.y"
	{
      current_mem->readback[0] = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 172:
#line 1377 "config_gram.y"
	{
      current_mem->readback[1] = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 173:
#line 1384 "config_gram.y"
	{
      current_mem->mode = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 174:
#line 1390 "config_gram.y"
	{
      current_mem->delay = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 175:
#line 1396 "config_gram.y"
	{
      current_mem->blocksize = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 176:
#line 1402 "config_gram.y"
	{
      current_mem->readsize = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 177:
#line 1408 "config_gram.y"
	{
      current_mem->pollindex = yystack.l_mark[0]->value.number;
      free_token(yystack.l_mark[0]);
    }
break;
case 178:
#line 1414 "config_gram.y"
	{
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode(yystack.l_mark[-2]);
      op = avr_new_opcode();
      parse_cmdbits(op);
      current_mem->op[opnum] = op;

      free_token(yystack.l_mark[-2]);
    }
  }
break;
#line 2483 "config_gram.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
