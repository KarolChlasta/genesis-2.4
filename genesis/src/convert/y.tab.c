/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "script.y"

static char parsercsid[] = "$Id: script.y,v 1.3 2005/08/08 13:10:23 svitak Exp $";

/*
** $Log: script.y,v $
**
** Revision 1.4  2019/01/15 14:40:0  jcrone
** Added gcmalloc header file
**
** Revision 1.3  2005/08/08 13:10:23  svitak
** Removed #ifdef around #include y.tab.h.
**
** Revision 1.2  2005/07/01 10:03:01  svitak
** Misc fixes to address compiler warnings, esp. providing explicit types
** for all functions and cleaning up unused variables.
**
** Revision 1.1.1.1  2005/06/14 04:38:28  svitak
** Import from snapshot of CalTech CVS tree of June 8, 2005
**
** Revision 1.9  2003/03/28 21:07:05  gen-dbeeman
** Fix from Mike Vanier Jan 2003 to fix problem with bison ver. 1.75
**
** Revision 1.8  2001/04/18 22:39:36  mhucka
** Miscellaneous portability fixes, mainly for SGI IRIX.
**
** Revision 1.7  1997/06/12 22:50:55  dhb
** Added include of string.h for strlen() declaration needed by
** included lexer code.
**
** Revision 1.6  1996/07/15 23:19:00  venkat
** Added preprocessor macros to deal with the order of the include lex.yy.c
** statement and the definitions of the macros used in it, for the DEC/alpha
**
 * Revision 1.5  1995/06/16  05:57:12  dhb
 * FreeBSD compatibility.
 *
 * Revision 1.4  1995/04/29  01:18:16  dhb
 * Moved include of lex.yy.c back to original location.  Previous
 * problem is fixed by extern void exit() in script.l.
 *
 * Fixed bug in call to SymtabLook() call where a Symtab rather than
 * a Symtab* was passed.
 *
 * Revision 1.3  1995/04/15  02:26:28  dhb
 * Moved include of lex.yy.c after the parse rules to work around SGI
 * yacc misplacement of include statements.
 *
 * Revision 1.2  1995/04/14  01:03:20  dhb
 * Null change to force patch and reprocessing by yacc.
 *
 * Revision 1.1  1995/01/13  01:09:48  dhb
 * Initial revision
 *
 * Revision 1.1  1992/12/11  21:19:07  dhb
 **
 ** This file is from GENESIS 1.4.1
 **
 * Initial revision
 *
*/

#define YYDEBUG	1

#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include "parse.h"
#include "symtab.h"
#include "gcmalloc_ext.h"

/*
** General declarations.
*/
extern char *strsave();

/*
** Parser routines which return something other than int.
*/

extern ParseNode *vardef();
extern char *TokenStr();

extern char* Combine();
extern char* ArgListToStr();
extern char** AllocateArgList();

/*
** Parser global variables
*/

extern jmp_buf	BreakBuf;	/* Used to break out of a loop */
extern jmp_buf	ReturnBuf;	/* Used to return out of a script */

static int	DefType;	/* Remembers type in a var decl */
static int	DefCast;	/* Remembers cast in a var decl */
static int	BreakAllowed = 0; /* In a loop control structure */
static int	ReturnIdents = 0; /* 1 ==> lexer doesn't classify IDENTs */
static int	Compiling = 0;	/* Make a statement list rather than execute */
static int	InFunctionDefinition = 0;
static int	NextLocal;	/* Next local symbol offset */
static int	ArgMatch;	/* Matches argument number to name in func */
Symtab		GlobalSymbols;	/* Symbols defined outside a function */
static Symtab	*LocalSymbols = NULL;	/* Symbols local to a function */
static ResultValue RV;			/* Dummy ReturnValue for PTNew */

#line 137 "script.y"


#if !defined(decalpha) || defined(bison) || defined(T3E)
/*
** Start of lexical analyzer.  LEX source is in "script.l".
*/

extern YYSTYPE	yylval;

#include "y.tab.h"
#include "lex.yy.c"

#endif

#line 192 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LT = 258,                      /* LT  */
    LE = 259,                      /* LE  */
    GT = 260,                      /* GT  */
    GE = 261,                      /* GE  */
    EQ = 262,                      /* EQ  */
    NE = 263,                      /* NE  */
    OR = 264,                      /* OR  */
    AND = 265,                     /* AND  */
    UMINUS = 266,                  /* UMINUS  */
    WHILE = 267,                   /* WHILE  */
    IF = 268,                      /* IF  */
    ELSE = 269,                    /* ELSE  */
    FOR = 270,                     /* FOR  */
    FOREACH = 271,                 /* FOREACH  */
    END = 272,                     /* END  */
    INCLUDE = 273,                 /* INCLUDE  */
    ENDSCRIPT = 274,               /* ENDSCRIPT  */
    BREAK = 275,                   /* BREAK  */
    INT = 276,                     /* INT  */
    FLOAT = 277,                   /* FLOAT  */
    STR = 278,                     /* STR  */
    RETURN = 279,                  /* RETURN  */
    WHITESPACE = 280,              /* WHITESPACE  */
    FUNCTION = 281,                /* FUNCTION  */
    INTCONST = 282,                /* INTCONST  */
    DOLLARARG = 283,               /* DOLLARARG  */
    FLOATCONST = 284,              /* FLOATCONST  */
    STRCONST = 285,                /* STRCONST  */
    LITERAL = 286,                 /* LITERAL  */
    IDENT = 287,                   /* IDENT  */
    VARREF = 288,                  /* VARREF  */
    FUNCREF = 289,                 /* FUNCREF  */
    EXTERN = 290,                  /* EXTERN  */
    SL = 291,                      /* SL  */
    COMMAND = 292,                 /* COMMAND  */
    ARGUMENT = 293,                /* ARGUMENT  */
    ARGLIST = 294,                 /* ARGLIST  */
    LOCREF = 295,                  /* LOCREF  */
    ICAST = 296,                   /* ICAST  */
    FCAST = 297,                   /* FCAST  */
    SCAST = 298                    /* SCAST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LT 258
#define LE 259
#define GT 260
#define GE 261
#define EQ 262
#define NE 263
#define OR 264
#define AND 265
#define UMINUS 266
#define WHILE 267
#define IF 268
#define ELSE 269
#define FOR 270
#define FOREACH 271
#define END 272
#define INCLUDE 273
#define ENDSCRIPT 274
#define BREAK 275
#define INT 276
#define FLOAT 277
#define STR 278
#define RETURN 279
#define WHITESPACE 280
#define FUNCTION 281
#define INTCONST 282
#define DOLLARARG 283
#define FLOATCONST 284
#define STRCONST 285
#define LITERAL 286
#define IDENT 287
#define VARREF 288
#define FUNCREF 289
#define EXTERN 290
#define SL 291
#define COMMAND 292
#define ARGUMENT 293
#define ARGLIST 294
#define LOCREF 295
#define ICAST 296
#define FCAST 297
#define SCAST 298

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LT = 3,                         /* LT  */
  YYSYMBOL_LE = 4,                         /* LE  */
  YYSYMBOL_GT = 5,                         /* GT  */
  YYSYMBOL_GE = 6,                         /* GE  */
  YYSYMBOL_EQ = 7,                         /* EQ  */
  YYSYMBOL_NE = 8,                         /* NE  */
  YYSYMBOL_9_ = 9,                         /* '!'  */
  YYSYMBOL_OR = 10,                        /* OR  */
  YYSYMBOL_AND = 11,                       /* AND  */
  YYSYMBOL_12_ = 12,                       /* '+'  */
  YYSYMBOL_13_ = 13,                       /* '-'  */
  YYSYMBOL_14_ = 14,                       /* '&'  */
  YYSYMBOL_15_ = 15,                       /* '|'  */
  YYSYMBOL_16_ = 16,                       /* '^'  */
  YYSYMBOL_17_ = 17,                       /* '*'  */
  YYSYMBOL_18_ = 18,                       /* '/'  */
  YYSYMBOL_19_ = 19,                       /* '%'  */
  YYSYMBOL_20_ = 20,                       /* '~'  */
  YYSYMBOL_UMINUS = 21,                    /* UMINUS  */
  YYSYMBOL_WHILE = 22,                     /* WHILE  */
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_ELSE = 24,                      /* ELSE  */
  YYSYMBOL_FOR = 25,                       /* FOR  */
  YYSYMBOL_FOREACH = 26,                   /* FOREACH  */
  YYSYMBOL_END = 27,                       /* END  */
  YYSYMBOL_INCLUDE = 28,                   /* INCLUDE  */
  YYSYMBOL_ENDSCRIPT = 29,                 /* ENDSCRIPT  */
  YYSYMBOL_BREAK = 30,                     /* BREAK  */
  YYSYMBOL_INT = 31,                       /* INT  */
  YYSYMBOL_FLOAT = 32,                     /* FLOAT  */
  YYSYMBOL_STR = 33,                       /* STR  */
  YYSYMBOL_RETURN = 34,                    /* RETURN  */
  YYSYMBOL_WHITESPACE = 35,                /* WHITESPACE  */
  YYSYMBOL_FUNCTION = 36,                  /* FUNCTION  */
  YYSYMBOL_INTCONST = 37,                  /* INTCONST  */
  YYSYMBOL_DOLLARARG = 38,                 /* DOLLARARG  */
  YYSYMBOL_FLOATCONST = 39,                /* FLOATCONST  */
  YYSYMBOL_STRCONST = 40,                  /* STRCONST  */
  YYSYMBOL_LITERAL = 41,                   /* LITERAL  */
  YYSYMBOL_IDENT = 42,                     /* IDENT  */
  YYSYMBOL_VARREF = 43,                    /* VARREF  */
  YYSYMBOL_FUNCREF = 44,                   /* FUNCREF  */
  YYSYMBOL_EXTERN = 45,                    /* EXTERN  */
  YYSYMBOL_SL = 46,                        /* SL  */
  YYSYMBOL_COMMAND = 47,                   /* COMMAND  */
  YYSYMBOL_ARGUMENT = 48,                  /* ARGUMENT  */
  YYSYMBOL_ARGLIST = 49,                   /* ARGLIST  */
  YYSYMBOL_LOCREF = 50,                    /* LOCREF  */
  YYSYMBOL_ICAST = 51,                     /* ICAST  */
  YYSYMBOL_FCAST = 52,                     /* FCAST  */
  YYSYMBOL_SCAST = 53,                     /* SCAST  */
  YYSYMBOL_54_n_ = 54,                     /* '\n'  */
  YYSYMBOL_55_ = 55,                       /* ';'  */
  YYSYMBOL_56_ = 56,                       /* '('  */
  YYSYMBOL_57_ = 57,                       /* ')'  */
  YYSYMBOL_58_ = 58,                       /* '='  */
  YYSYMBOL_59_ = 59,                       /* ','  */
  YYSYMBOL_60_ = 60,                       /* '{'  */
  YYSYMBOL_61_ = 61,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_script = 63,                    /* script  */
  YYSYMBOL_statement_list = 64,            /* statement_list  */
  YYSYMBOL_stmnt_terminator = 65,          /* stmnt_terminator  */
  YYSYMBOL_statement = 66,                 /* statement  */
  YYSYMBOL_endscript_marker = 67,          /* endscript_marker  */
  YYSYMBOL_while_stmnt = 68,               /* while_stmnt  */
  YYSYMBOL_69_1 = 69,                      /* $@1  */
  YYSYMBOL_for_stmnt = 70,                 /* for_stmnt  */
  YYSYMBOL_71_2 = 71,                      /* $@2  */
  YYSYMBOL_foreach_stmnt = 72,             /* foreach_stmnt  */
  YYSYMBOL_73_3 = 73,                      /* $@3  */
  YYSYMBOL_74_4 = 74,                      /* $@4  */
  YYSYMBOL_if_stmnt = 75,                  /* if_stmnt  */
  YYSYMBOL_76_5 = 76,                      /* $@5  */
  YYSYMBOL_else_clause = 77,               /* else_clause  */
  YYSYMBOL_78_6 = 78,                      /* $@6  */
  YYSYMBOL_assign_stmnt = 79,              /* assign_stmnt  */
  YYSYMBOL_include_hdr = 80,               /* include_hdr  */
  YYSYMBOL_81_7 = 81,                      /* $@7  */
  YYSYMBOL_include_stmnt = 82,             /* include_stmnt  */
  YYSYMBOL_opt_node = 83,                  /* opt_node  */
  YYSYMBOL_cmd_name = 84,                  /* cmd_name  */
  YYSYMBOL_85_8 = 85,                      /* $@8  */
  YYSYMBOL_cmd_stmnt = 86,                 /* cmd_stmnt  */
  YYSYMBOL_87_9 = 87,                      /* $@9  */
  YYSYMBOL_funcref = 88,                   /* funcref  */
  YYSYMBOL_func_call = 89,                 /* func_call  */
  YYSYMBOL_90_10 = 90,                     /* $@10  */
  YYSYMBOL_opt_arg_list = 91,              /* opt_arg_list  */
  YYSYMBOL_arg_list = 92,                  /* arg_list  */
  YYSYMBOL_optwslist = 93,                 /* optwslist  */
  YYSYMBOL_wslist = 94,                    /* wslist  */
  YYSYMBOL_func_call_list = 95,            /* func_call_list  */
  YYSYMBOL_ws = 96,                        /* ws  */
  YYSYMBOL_arg_component_list = 97,        /* arg_component_list  */
  YYSYMBOL_arg_component = 98,             /* arg_component  */
  YYSYMBOL_99_11 = 99,                     /* $@11  */
  YYSYMBOL_100_12 = 100,                   /* $@12  */
  YYSYMBOL_ext_func = 101,                 /* ext_func  */
  YYSYMBOL_func_hdr = 102,                 /* func_hdr  */
  YYSYMBOL_func_def = 103,                 /* func_def  */
  YYSYMBOL_104_13 = 104,                   /* $@13  */
  YYSYMBOL_105_14 = 105,                   /* $@14  */
  YYSYMBOL_func_args = 106,                /* func_args  */
  YYSYMBOL_107_15 = 107,                   /* $@15  */
  YYSYMBOL_func_arg_list = 108,            /* func_arg_list  */
  YYSYMBOL_decl_type = 109,                /* decl_type  */
  YYSYMBOL_decl_stmnt = 110,               /* decl_stmnt  */
  YYSYMBOL_decl_list = 111,                /* decl_list  */
  YYSYMBOL_112_16 = 112,                   /* $@16  */
  YYSYMBOL_decl_ident = 113,               /* decl_ident  */
  YYSYMBOL_114_17 = 114,                   /* $@17  */
  YYSYMBOL_init = 115,                     /* init  */
  YYSYMBOL_break_stmnt = 116,              /* break_stmnt  */
  YYSYMBOL_return_stmnt = 117,             /* return_stmnt  */
  YYSYMBOL_null_stmnt = 118,               /* null_stmnt  */
  YYSYMBOL_expr = 119,                     /* expr  */
  YYSYMBOL_120_18 = 120,                   /* $@18  */
  YYSYMBOL_121_19 = 121,                   /* $@19  */
  YYSYMBOL_122_20 = 122,                   /* $@20  */
  YYSYMBOL_123_21 = 123                    /* $@21  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   471

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  224

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      54,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     9,     2,     2,     2,    19,    14,     2,
      56,    57,    17,    12,    59,    13,     2,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    55,
       2,    58,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    15,    61,    20,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,    10,    11,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   154,   154,   158,   161,   168,   172,   178,   179,   180,
     181,   182,   187,   188,   189,   194,   199,   200,   201,   202,
     203,   204,   207,   214,   213,   226,   225,   239,   245,   238,
     258,   257,   270,   274,   273,   279,   286,   285,   296,   301,
     308,   311,   318,   317,   333,   332,   365,   396,   403,   415,
     414,   432,   439,   450,   459,   470,   471,   474,   475,   478,
     487,   498,   499,   502,   506,   512,   516,   520,   525,   529,
     524,   548,   563,   570,   596,   621,   627,   620,   642,   644,
     643,   654,   659,   666,   673,   680,   689,   697,   699,   698,
     709,   708,   723,   726,   732,   739,   744,   752,   755,   757,
     759,   761,   764,   777,   779,   781,   783,   785,   788,   790,
     792,   795,   797,   799,   801,   803,   805,   809,   813,   808,
     855,   859,   854,   868,   880,   886,   918,   923,   928,   934,
     940,   947
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LT", "LE", "GT", "GE",
  "EQ", "NE", "'!'", "OR", "AND", "'+'", "'-'", "'&'", "'|'", "'^'", "'*'",
  "'/'", "'%'", "'~'", "UMINUS", "WHILE", "IF", "ELSE", "FOR", "FOREACH",
  "END", "INCLUDE", "ENDSCRIPT", "BREAK", "INT", "FLOAT", "STR", "RETURN",
  "WHITESPACE", "FUNCTION", "INTCONST", "DOLLARARG", "FLOATCONST",
  "STRCONST", "LITERAL", "IDENT", "VARREF", "FUNCREF", "EXTERN", "SL",
  "COMMAND", "ARGUMENT", "ARGLIST", "LOCREF", "ICAST", "FCAST", "SCAST",
  "'\\n'", "';'", "'('", "')'", "'='", "','", "'{'", "'}'", "$accept",
  "script", "statement_list", "stmnt_terminator", "statement",
  "endscript_marker", "while_stmnt", "$@1", "for_stmnt", "$@2",
  "foreach_stmnt", "$@3", "$@4", "if_stmnt", "$@5", "else_clause", "$@6",
  "assign_stmnt", "include_hdr", "$@7", "include_stmnt", "opt_node",
  "cmd_name", "$@8", "cmd_stmnt", "$@9", "funcref", "func_call", "$@10",
  "opt_arg_list", "arg_list", "optwslist", "wslist", "func_call_list",
  "ws", "arg_component_list", "arg_component", "$@11", "$@12", "ext_func",
  "func_hdr", "func_def", "$@13", "$@14", "func_args", "$@15",
  "func_arg_list", "decl_type", "decl_stmnt", "decl_list", "$@16",
  "decl_ident", "$@17", "init", "break_stmnt", "return_stmnt",
  "null_stmnt", "expr", "$@18", "$@19", "$@20", "$@21", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -107,     2,   248,  -107,   -44,   -38,   -35,   -21,  -107,  -107,
    -107,  -107,  -107,  -107,   207,   -27,  -107,   -32,  -107,    35,
     -48,  -107,  -107,  -107,  -107,  -107,  -107,     3,  -107,   -25,
    -107,    14,  -107,  -107,  -107,  -107,    10,  -107,  -107,  -107,
    -107,   207,   207,    52,    43,    65,   207,   207,   207,  -107,
    -107,  -107,  -107,    72,  -107,    80,   207,   207,   435,  -107,
    -107,    91,   207,  -107,  -107,  -107,  -107,  -107,    66,  -107,
      73,  -107,    73,  -107,    81,  -107,    79,  -107,   106,   154,
      86,  -107,  -107,   101,   219,  -107,  -107,  -107,  -107,   171,
      29,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,  -107,  -107,   435,
    -107,  -107,  -107,  -107,   108,    66,  -107,  -107,    66,   110,
     108,    66,   108,  -107,  -107,    89,  -107,  -107,  -107,   207,
      65,  -107,    73,    73,  -107,  -107,   452,   452,   452,   452,
     452,   452,   240,   240,    67,    67,    67,    67,    67,  -107,
    -107,  -107,   207,    -4,   -11,  -107,  -107,    73,    66,  -107,
     -11,  -107,    73,  -107,   109,  -107,   207,  -107,    10,  -107,
    -107,   188,    66,    66,    66,   435,    66,    24,    66,    37,
    -107,    76,   296,   435,  -107,   320,   272,    52,   108,    73,
      73,    92,  -107,    73,  -107,  -107,   112,  -107,  -107,  -107,
     123,    95,  -107,    96,    96,  -107,    66,  -107,  -107,  -107,
    -107,    99,   140,   151,    66,   344,  -107,  -107,  -107,  -107,
     368,   392,  -107,  -107
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    97,     1,     0,     0,     0,     0,    36,    22,
      94,    83,    84,    85,    96,     0,    42,     0,    47,     0,
       0,    13,     7,     8,     9,    10,    11,    61,    12,    44,
      14,    49,    15,    17,    75,    16,     0,    18,    19,    20,
      21,     0,     0,     0,     0,    61,     0,     0,     0,   127,
     129,   126,   128,   125,   123,   124,     0,     0,    95,    73,
      74,    40,     0,    71,    72,     5,     6,     4,    62,    39,
      55,    51,    55,    51,    78,    90,    86,    87,     0,     0,
       0,    27,    62,     0,   110,   107,   101,   117,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    43,    35,
      67,    66,    65,    68,    61,    53,    63,    57,     0,    56,
      61,     0,    61,    79,    76,    92,    88,    23,    30,     0,
      61,    37,    55,    55,   131,   130,   111,   112,   113,   114,
     115,   116,   108,   109,   102,   103,    99,    98,   100,   104,
     105,   106,     0,    57,     0,    38,    64,    55,    59,    58,
       0,    45,    55,    50,     0,     3,     0,    91,     0,     3,
       3,     0,     0,     0,     0,    69,    54,     0,    52,     0,
      81,     0,    97,    93,    89,    97,    97,     0,    61,    55,
      55,     0,    46,    55,    48,    80,     0,    77,    24,    33,
       0,     0,    28,   118,   121,    70,     0,    82,     3,    31,
      25,     0,     0,     0,    60,    97,     3,     3,   119,   122,
      97,    97,    26,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,  -107,   -68,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,   -43,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,   107,
      38,   -59,  -106,   -98,   -42,   -67,   -87,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,    41,  -107,  -107,  -107,  -107,  -107,   -37,  -107,  -107,
    -107,  -107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    67,    20,    21,    22,   169,    23,   216,
      24,   130,   211,    25,   170,   200,   208,    26,    27,    45,
      28,   108,    29,    61,    30,    71,    31,    32,    73,   120,
     114,   118,   119,   157,    69,   158,   116,   152,   191,    33,
      34,    35,    74,   165,   124,   164,   181,    36,    37,    76,
     168,    77,   125,   167,    38,    39,    40,    58,   132,   212,
     133,   213
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,   115,     3,    83,    78,    79,    65,    66,   154,    84,
      85,    86,    41,   121,   160,    59,   160,    60,    42,    89,
      90,    43,    44,   162,   159,   109,    62,   110,   156,   111,
     112,    70,    91,    92,    93,    94,    95,    96,    68,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   113,
     -62,   -62,    75,   -62,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
      72,   156,   155,   173,   174,   189,   190,    63,   161,    64,
     163,   192,   154,   193,   104,   105,   106,   176,   172,   156,
     135,   156,   171,   178,   194,    17,   193,   182,   177,    81,
      82,   185,   186,   179,   110,   115,   111,   112,   117,    91,
      92,    93,    94,    95,    96,   175,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   113,   156,    87,   183,
     203,   204,   107,   195,   206,   196,    88,   123,   126,   214,
     215,   129,   131,   153,   201,   159,   202,   166,   220,   221,
     209,   180,   210,   205,   207,   193,   217,    91,    92,    93,
      94,    95,    96,   127,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    91,    92,    93,    94,    95,    96,
     122,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,    91,    92,    93,    94,    95,    96,   218,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   219,   184,
     188,   128,     0,     0,     0,     0,    46,     0,     0,     0,
      47,     0,     0,     0,     0,     0,     0,    48,   134,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,     0,
       0,     0,     0,   187,    49,    50,    51,    52,    -2,    53,
      54,    55,    99,   100,   101,   102,   103,   104,   105,   106,
       0,     0,     0,    56,     0,     0,     0,    57,     0,     0,
       4,     5,     0,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,     0,    15,     0,     0,     0,     0,     0,
      16,    17,    18,    19,     4,     5,   199,     6,     7,   -32,
       8,     9,    10,    11,    12,    13,    14,     0,    15,     0,
       0,     0,     0,     0,    16,    17,    18,    19,     4,     5,
       0,     6,     7,   197,     8,     9,    10,    11,    12,    13,
      14,     0,    15,     0,     0,     0,     0,     0,    16,    17,
      18,    19,     4,     5,     0,     6,     7,   198,     8,     9,
      10,    11,    12,    13,    14,     0,    15,     0,     0,     0,
       0,     0,    16,    17,    18,    19,     4,     5,     0,     6,
       7,   -34,     8,     9,    10,    11,    12,    13,    14,     0,
      15,     0,     0,     0,     0,     0,    16,    17,    18,    19,
       4,     5,     0,     6,     7,   222,     8,     9,    10,    11,
      12,    13,    14,     0,    15,     0,     0,     0,     0,     0,
      16,    17,    18,    19,     4,     5,     0,     6,     7,   223,
       8,     9,    10,    11,    12,    13,    14,     0,    15,     0,
       0,     0,     0,     0,    16,    17,    18,    19,    91,    92,
      93,    94,    95,    96,     0,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   -63,   -63,   -63,   -63,   -63,
     -63,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106
};

static const yytype_int16 yycheck[] =
{
      43,    68,     0,    45,    41,    42,    54,    55,   114,    46,
      47,    48,    56,    72,   120,    42,   122,    44,    56,    56,
      57,    56,    43,   121,    35,    62,    58,    38,   115,    40,
      41,    56,     3,     4,     5,     6,     7,     8,    35,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    60,
      54,    55,    42,    57,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
      56,   158,   114,   132,   133,   173,   174,    42,   120,    44,
     122,    57,   188,    59,    17,    18,    19,   154,   130,   176,
      61,   178,   129,   160,    57,    43,    59,   165,   157,    56,
      35,   169,   170,   162,    38,   172,    40,    41,    35,     3,
       4,     5,     6,     7,     8,   152,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    60,   214,    56,   166,
     189,   190,    41,    57,   193,    59,    56,    56,    59,   206,
     208,    55,    41,    35,   187,    35,   188,    58,   216,   217,
      27,    42,    57,    61,    42,    59,    57,     3,     4,     5,
       6,     7,     8,    57,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     3,     4,     5,     6,     7,     8,
      73,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     3,     4,     5,     6,     7,     8,    57,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    57,   168,
     172,    57,    -1,    -1,    -1,    -1,     9,    -1,    -1,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    57,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    55,    37,    38,    39,    40,     0,    42,
      43,    44,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    -1,    -1,
      22,    23,    -1,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      42,    43,    44,    45,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    42,    43,    44,    45,    22,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,
      44,    45,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      42,    43,    44,    45,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    42,    43,    44,    45,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    63,    64,     0,    22,    23,    25,    26,    28,    29,
      30,    31,    32,    33,    34,    36,    42,    43,    44,    45,
      66,    67,    68,    70,    72,    75,    79,    80,    82,    84,
      86,    88,    89,   101,   102,   103,   109,   110,   116,   117,
     118,    56,    56,    56,    43,    81,     9,    13,    20,    37,
      38,    39,    40,    42,    43,    44,    56,    60,   119,    42,
      44,    85,    58,    42,    44,    54,    55,    65,    35,    96,
      56,    87,    56,    90,   104,    42,   111,   113,   119,   119,
      79,    56,    35,    96,   119,   119,   119,    56,    56,   119,
     119,     3,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    41,    83,   119,
      38,    40,    41,    60,    92,    97,    98,    35,    93,    94,
      91,    93,    91,    56,   106,   114,    59,    57,    57,    55,
      73,    41,   120,   122,    57,    61,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,    99,    35,    94,    96,    98,    95,    97,    35,
      94,    96,    95,    96,   107,   105,    58,   115,   112,    69,
      76,   119,    96,    93,    93,   119,    97,    93,    97,    93,
      42,   108,    64,   119,   113,    64,    64,    55,    92,    95,
      95,   100,    57,    59,    57,    57,    59,    27,    27,    24,
      77,    79,    96,    93,    93,    61,    93,    42,    78,    27,
      57,    74,   121,   123,    97,    64,    71,    57,    57,    57,
      64,    64,    27,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    69,    68,    71,    70,    73,    74,    72,
      76,    75,    77,    78,    77,    79,    81,    80,    82,    82,
      83,    83,    85,    84,    87,    86,    86,    88,    89,    90,
      89,    91,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    98,    98,    98,    99,   100,
      98,   101,   101,   102,   102,   104,   105,   103,   106,   107,
     106,   108,   108,   109,   109,   109,   110,   111,   112,   111,
     114,   113,   115,   115,   116,   117,   117,   118,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   120,   121,   119,
     122,   123,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     7,     0,    11,     0,     0,    11,
       0,     8,     0,     0,     3,     3,     0,     4,     4,     2,
       0,     1,     0,     3,     0,     4,     6,     1,     6,     0,
       4,     0,     3,     1,     3,     0,     1,     1,     2,     1,
       5,     0,     1,     1,     2,     1,     1,     1,     0,     0,
       5,     2,     2,     2,     2,     0,     0,     6,     0,     0,
       4,     1,     3,     1,     1,     1,     2,     1,     0,     4,
       0,     3,     0,     2,     1,     2,     1,     0,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     2,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     0,     0,     8,
       0,     0,     8,     1,     1,     1,     1,     1,     1,     1,
       3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* statement_list: %empty  */
#line 158 "script.y"
                  { 
		    (yyval.str) = NULL;
 		  }
#line 1643 "y.tab.c"
    break;

  case 4: /* statement_list: statement_list statement stmnt_terminator  */
#line 163 "script.y"
                  {
		    Output((yyvsp[0].str), NULL);
		  }
#line 1651 "y.tab.c"
    break;

  case 5: /* stmnt_terminator: '\n'  */
#line 169 "script.y"
                  {
		    (yyval.str) = "\n";
		  }
#line 1659 "y.tab.c"
    break;

  case 6: /* stmnt_terminator: ';'  */
#line 173 "script.y"
                  {
		    (yyval.str) = "; ";
		  }
#line 1667 "y.tab.c"
    break;

  case 11: /* statement: assign_stmnt  */
#line 183 "script.y"
                  {
		    OutputIndentation();
		    Output((yyvsp[0].str), NULL);
		  }
#line 1676 "y.tab.c"
    break;

  case 14: /* statement: cmd_stmnt  */
#line 190 "script.y"
                  {
		    OutputIndentation();
		    OutputArgList((yyvsp[0].str));
		  }
#line 1685 "y.tab.c"
    break;

  case 15: /* statement: func_call  */
#line 195 "script.y"
                  {
		    OutputIndentation();
		    OutputArgList((yyvsp[0].str));
		  }
#line 1694 "y.tab.c"
    break;

  case 22: /* endscript_marker: ENDSCRIPT  */
#line 208 "script.y"
                  {
		    yyaccept();
		  }
#line 1702 "y.tab.c"
    break;

  case 23: /* $@1: %empty  */
#line 214 "script.y"
                  {
		    OutputIndentation();
		    Output("while (", (yyvsp[-1].expr).s, ")", NULL);
		  }
#line 1711 "y.tab.c"
    break;

  case 24: /* while_stmnt: WHILE '(' expr ')' $@1 statement_list END  */
#line 219 "script.y"
                  {
		    OutputIndentation();
		    Output("end", NULL);
		  }
#line 1720 "y.tab.c"
    break;

  case 25: /* $@2: %empty  */
#line 226 "script.y"
                  {
		    OutputIndentation();
		    Output("for (", (yyvsp[-5].str), "; ", (yyvsp[-3].expr).s, "; ", (yyvsp[-1].str), ")", NULL);
		  }
#line 1729 "y.tab.c"
    break;

  case 26: /* for_stmnt: FOR '(' assign_stmnt ';' expr ';' assign_stmnt ')' $@2 statement_list END  */
#line 232 "script.y"
                  {
		    OutputIndentation();
		    Output("end", NULL);
		  }
#line 1738 "y.tab.c"
    break;

  case 27: /* $@3: %empty  */
#line 239 "script.y"
                    {
			BEGIN FUNCLIT;
			OutputIndentation();
			Output("foreach ", (yyvsp[-1].str), " (", NULL);
		    }
#line 1748 "y.tab.c"
    break;

  case 28: /* $@4: %empty  */
#line 245 "script.y"
                    {
			BEGIN 0;
			OutputArgList((yyvsp[-1].str));
			Output(")", NULL);
		    }
#line 1758 "y.tab.c"
    break;

  case 29: /* foreach_stmnt: FOREACH VARREF '(' $@3 ws arg_list ws $@4 ')' statement_list END  */
#line 251 "script.y"
                  {
		    OutputIndentation();
		    Output("end", NULL);
		  }
#line 1767 "y.tab.c"
    break;

  case 30: /* $@5: %empty  */
#line 258 "script.y"
                  {
		    OutputIndentation();
		    Output("if (", (yyvsp[-1].expr).s, ")", NULL);
		  }
#line 1776 "y.tab.c"
    break;

  case 31: /* if_stmnt: IF '(' expr ')' $@5 statement_list else_clause END  */
#line 263 "script.y"
                  {
		    OutputIndentation();
		    Output("end", NULL);
		  }
#line 1785 "y.tab.c"
    break;

  case 32: /* else_clause: %empty  */
#line 270 "script.y"
                  {
 		    (yyval.str) = NULL;
 		  }
#line 1793 "y.tab.c"
    break;

  case 33: /* $@6: %empty  */
#line 274 "script.y"
                  { OutputIndentation(); Output("else", NULL); }
#line 1799 "y.tab.c"
    break;

  case 34: /* else_clause: ELSE $@6 statement_list  */
#line 276 "script.y"
                  { (yyval.str) = NULL; }
#line 1805 "y.tab.c"
    break;

  case 35: /* assign_stmnt: VARREF '=' expr  */
#line 280 "script.y"
                  {
		    (yyval.str) = Combine((yyvsp[-2].str), " = ", (yyvsp[0].expr).s, NULL);
		  }
#line 1813 "y.tab.c"
    break;

  case 36: /* $@7: %empty  */
#line 286 "script.y"
                  {
		    Pushyybgin(LIT);
		  }
#line 1821 "y.tab.c"
    break;

  case 37: /* include_hdr: INCLUDE $@7 ws LITERAL  */
#line 290 "script.y"
                  {
		    OutputIndentation();
		    Output("include ", (yyvsp[0].str), " ", NULL);
		  }
#line 1830 "y.tab.c"
    break;

  case 38: /* include_stmnt: include_hdr WHITESPACE arg_list ws  */
#line 297 "script.y"
                  {
		    Popyybgin();
		    OutputArgList((yyvsp[-1].str));
		  }
#line 1839 "y.tab.c"
    break;

  case 39: /* include_stmnt: include_hdr ws  */
#line 302 "script.y"
                  {
		    Popyybgin();
		  }
#line 1847 "y.tab.c"
    break;

  case 40: /* opt_node: %empty  */
#line 308 "script.y"
                  {
		    (yyval.str) = (char*) strsave("");
		  }
#line 1855 "y.tab.c"
    break;

  case 41: /* opt_node: LITERAL  */
#line 312 "script.y"
                  {
		    (yyval.str) = (yyvsp[0].str);
		  }
#line 1863 "y.tab.c"
    break;

  case 42: /* $@8: %empty  */
#line 318 "script.y"
                  {
		    Pushyybgin(FUNCLIT);
		  }
#line 1871 "y.tab.c"
    break;

  case 43: /* cmd_name: IDENT $@8 opt_node  */
#line 322 "script.y"
                  {
		    char	cmd[200];

		    sprintf(cmd, "%s%s", (yyvsp[-2].str), (yyvsp[0].str));
		    free((yyvsp[-2].str));
		    free((yyvsp[0].str));
		    (yyval.str) = (char*) strsave(cmd);
		  }
#line 1884 "y.tab.c"
    break;

  case 44: /* $@9: %empty  */
#line 333 "script.y"
                  {
		    BEGIN LIT;
		  }
#line 1892 "y.tab.c"
    break;

  case 45: /* cmd_stmnt: cmd_name $@9 opt_arg_list ws  */
#line 337 "script.y"
                  {
		    char*	cmdname;
		    char**	argv;
		    int		i;

		    Popyybgin();
		    cmdname = (yyvsp[-3].str);
		    argv = (char**) (yyvsp[-1].str);
		    switch (MapCommand(&cmdname, argv, NULL))
		      {
		      case -1:
			fprintf(stderr, "Error mapping command: %s", cmdname);
			for (i = 0; argv[i] != NULL; i++)
			    fprintf(stderr, " %s", argv[i]);
			fprintf(stderr, "\n");
			InsertItemInArgList(argv, 0, "/* Could not map:", 100);
			InsertItemInArgList(argv, 1, cmdname, 100);
			AddItemToArgList(argv, "*/", 100);
			break;
		      case 0:
			argv[0] = NULL; /* don't output anything */
			break;
		      default:
			InsertItemInArgList(argv, 0, cmdname, 100);
			break;
		      }
		    (yyval.str) = (char*) argv;
		  }
#line 1925 "y.tab.c"
    break;

  case 46: /* cmd_stmnt: cmd_name '(' optwslist func_call_list optwslist ')'  */
#line 366 "script.y"
                  {
		    char*	cmdname;
		    char**	argv;
		    int		i;

		    Popyybgin();
		    cmdname = (yyvsp[-5].str);
		    argv = (char**) (yyvsp[-2].str);
		    switch (MapCommand(&cmdname, argv, NULL))
		      {
		      case -1:
			fprintf(stderr, "Error mapping command: %s", cmdname);
			for (i = 0; argv[i] != NULL; i++)
			    fprintf(stderr, " %s", argv[i]);
			fprintf(stderr, "\n");
			InsertItemInArgList(argv, 0, "/* Could not map:", 100);
			InsertItemInArgList(argv, 1, cmdname, 100);
			AddItemToArgList(argv, "*/", 100);
			break;
		      case 0:
			argv[0] = NULL; /* don't output anything */
			break;
		      default:
			InsertItemInArgList(argv, 0, cmdname, 100);
			break;
		      }
		    (yyval.str) = (char*) argv;
		  }
#line 1958 "y.tab.c"
    break;

  case 47: /* funcref: FUNCREF  */
#line 397 "script.y"
                  {
		    Pushyybgin(FUNCLIT);
		    (yyval.str) = (yyvsp[0].str);
		  }
#line 1967 "y.tab.c"
    break;

  case 48: /* func_call: funcref '(' optwslist func_call_list optwslist ')'  */
#line 404 "script.y"
                  {
		    char*	cmdname;
		    char**	argv;

		    Popyybgin();
		    cmdname = (yyvsp[-5].str);
		    argv = (char**) (yyvsp[-2].str);
		    InsertItemInArgList(argv, 0, cmdname, 100);
		    (yyval.str) = (char*) argv;
		  }
#line 1982 "y.tab.c"
    break;

  case 49: /* $@10: %empty  */
#line 415 "script.y"
                  {
		    BEGIN LIT;
		  }
#line 1990 "y.tab.c"
    break;

  case 50: /* func_call: funcref $@10 opt_arg_list ws  */
#line 419 "script.y"
                  {
		    char*	cmdname;
		    char**	argv;

		    Popyybgin();
		    cmdname = (yyvsp[-3].str);
		    argv = (char**) (yyvsp[-1].str);
		    InsertItemInArgList(argv, 0, cmdname, 100);
		    (yyval.str) = (char*) argv;
		  }
#line 2005 "y.tab.c"
    break;

  case 51: /* opt_arg_list: %empty  */
#line 432 "script.y"
                  {
		    char**	argv;

		    argv = AllocateArgList(100);
		    argv[0] = NULL;
		    (yyval.str) = (char*) argv;
		  }
#line 2017 "y.tab.c"
    break;

  case 52: /* opt_arg_list: opt_arg_list wslist arg_component_list  */
#line 440 "script.y"
                  {
		    char**	argv;

		    argv = (char**) (yyvsp[-2].str);
		    AddItemToArgList(argv, (yyvsp[0].str), 100);

		    (yyval.str) = (yyvsp[-2].str);
		  }
#line 2030 "y.tab.c"
    break;

  case 53: /* arg_list: arg_component_list  */
#line 451 "script.y"
                  {
		    char**	argv;

		    argv = AllocateArgList(100);
		    argv[0] = (yyvsp[0].str);
		    argv[1] = NULL;
		    (yyval.str) = (char*) argv;
		  }
#line 2043 "y.tab.c"
    break;

  case 54: /* arg_list: arg_list wslist arg_component_list  */
#line 460 "script.y"
                  {
		    char**	argv;

		    argv = (char**) (yyvsp[-2].str);
		    AddItemToArgList(argv, (yyvsp[0].str), 100);

		    (yyval.str) = (yyvsp[-2].str);
		  }
#line 2056 "y.tab.c"
    break;

  case 59: /* func_call_list: arg_component_list  */
#line 479 "script.y"
                  {
		    char**	argv;

		    argv = AllocateArgList(100);
		    argv[0] = (yyvsp[0].str);
		    argv[1] = NULL;
		    (yyval.str) = (char*) argv;
		  }
#line 2069 "y.tab.c"
    break;

  case 60: /* func_call_list: func_call_list optwslist ',' optwslist arg_component_list  */
#line 488 "script.y"
                  {
		    char**	argv;

		    argv = (char**) (yyvsp[-4].str);
		    AddItemToArgList(argv, (yyvsp[0].str), 100);

		    (yyval.str) = (yyvsp[-4].str);
		  }
#line 2082 "y.tab.c"
    break;

  case 63: /* arg_component_list: arg_component  */
#line 503 "script.y"
                          {
			    (yyval.str) = (yyvsp[0].str);
			  }
#line 2090 "y.tab.c"
    break;

  case 64: /* arg_component_list: arg_component_list arg_component  */
#line 507 "script.y"
                          {
			    (yyval.str) = Combine((yyvsp[-1].str), (yyvsp[0].str), NULL);
			  }
#line 2098 "y.tab.c"
    break;

  case 65: /* arg_component: LITERAL  */
#line 513 "script.y"
                  {
		    (yyval.str) = (yyvsp[0].str);
		  }
#line 2106 "y.tab.c"
    break;

  case 66: /* arg_component: STRCONST  */
#line 517 "script.y"
                  {
		    (yyval.str) = Combine("\"", (yyvsp[0].str), "\"", NULL);
		  }
#line 2114 "y.tab.c"
    break;

  case 67: /* arg_component: DOLLARARG  */
#line 521 "script.y"
                  {
		    (yyval.str) = (yyvsp[0].str);
		  }
#line 2122 "y.tab.c"
    break;

  case 68: /* $@11: %empty  */
#line 525 "script.y"
                  {
		    Pushyybgin(0);
		  }
#line 2130 "y.tab.c"
    break;

  case 69: /* $@12: %empty  */
#line 529 "script.y"
                  {
		    Popyybgin();
		  }
#line 2138 "y.tab.c"
    break;

  case 70: /* arg_component: '{' $@11 expr $@12 '}'  */
#line 533 "script.y"
                  {
		    /*
		    ** Often the expression is just a call to a command
		    ** or function, in which case we get the command
		    ** already wrapped in a {} pair.  Avoid the additional
		    ** curley braces.
		    */

		    if (AlreadyBracketed((yyvsp[-2].expr).s))
			(yyval.str) = (yyvsp[-2].expr).s;
		    else
			(yyval.str) = Combine("{", (yyvsp[-2].expr).s, "}", NULL);
		  }
#line 2156 "y.tab.c"
    break;

  case 71: /* ext_func: EXTERN IDENT  */
#line 549 "script.y"
                  {
		    ParseNode	*funcpn;
		    ResultValue	v;
		    Result	*rp;

		    rp = SymtabNew(&GlobalSymbols, (yyvsp[0].str));
		    if (rp->r_type != 0 && rp->r_type != FUNCTION)
			fprintf(stderr, "WARNING: function name '%s' is redefining a variable!\n", (yyvsp[0].str));

		    rp->r_type = FUNCTION;

		    OutputIndentation();
		    Output("extern ", (yyvsp[0].str), NULL);
		  }
#line 2175 "y.tab.c"
    break;

  case 72: /* ext_func: EXTERN FUNCREF  */
#line 564 "script.y"
                  {
		    OutputIndentation();
		    Output("extern ", (yyvsp[0].str), NULL);
		  }
#line 2184 "y.tab.c"
    break;

  case 73: /* func_hdr: FUNCTION IDENT  */
#line 571 "script.y"
                  {
		    ParseNode	*funcpn;
		    ResultValue	v;
		    Result	*rp;
		    char	*script;

		    if (InFunctionDefinition)
		      {
			fprintf(stderr, "Function definition within another function or\n");
			fprintf(stderr, "within a control structure (FUNCTION %s).\n", (yyvsp[0].str));
			fprintf(stderr, "conversion failed\n");
			exit(1);
		      }

		    InFunctionDefinition++;
		    NextLocal = 0;
		    rp = SymtabNew(&GlobalSymbols, (yyvsp[0].str));
		    if (rp->r_type != 0 && rp->r_type != FUNCTION)
			fprintf(stderr, "WARNING: function name '%s' is redefining a variable!\n", (yyvsp[0].str));

		    rp->r_type = FUNCTION;

		    LocalSymbols = SymtabCreate();
		    (yyval.str) = (yyvsp[0].str);
		  }
#line 2214 "y.tab.c"
    break;

  case 74: /* func_hdr: FUNCTION FUNCREF  */
#line 597 "script.y"
                  {
		    ParseNode	*funcpn;
		    ResultValue	v;
		    Result	*rp;
		    char	*script;

		    rp = (Result *) (yyvsp[0].str);
		    if (InFunctionDefinition)
		      {
			fprintf(stderr, "Function definition within another function or\n");
			fprintf(stderr, "within a control structure (FUNCTION %s).\n", (yyvsp[0].str));
			fprintf(stderr, "conversion failed\n");
			exit(1);
		      }

		    InFunctionDefinition++;
		    NextLocal = 0;
		    LocalSymbols = SymtabCreate();

		    (yyval.str) = (yyvsp[0].str);
		  }
#line 2240 "y.tab.c"
    break;

  case 75: /* $@13: %empty  */
#line 621 "script.y"
                  {
		    OutputIndentation();
		    Output("function ", (yyvsp[0].str), NULL);
		    ReturnIdents = 1;
		  }
#line 2250 "y.tab.c"
    break;

  case 76: /* $@14: %empty  */
#line 627 "script.y"
                  {
		    ReturnIdents = 0;
		  }
#line 2258 "y.tab.c"
    break;

  case 77: /* func_def: func_hdr $@13 func_args $@14 statement_list END  */
#line 631 "script.y"
                  {
		    OutputIndentation();
		    Output("end", NULL);

		    InFunctionDefinition--;
		    SymtabDestroy(LocalSymbols);
		    LocalSymbols = NULL;
		  }
#line 2271 "y.tab.c"
    break;

  case 78: /* func_args: %empty  */
#line 642 "script.y"
                  { (yyval.str) = NULL; }
#line 2277 "y.tab.c"
    break;

  case 79: /* $@15: %empty  */
#line 644 "script.y"
                  {
		    Output("(", NULL);
		  }
#line 2285 "y.tab.c"
    break;

  case 80: /* func_args: '(' $@15 func_arg_list ')'  */
#line 649 "script.y"
                  { 
		    Output(")", NULL);
		  }
#line 2293 "y.tab.c"
    break;

  case 81: /* func_arg_list: IDENT  */
#line 655 "script.y"
                  {
		    Output((yyvsp[0].str), NULL);
		    vardef((yyvsp[0].str), STR, SCAST, NULL);
		  }
#line 2302 "y.tab.c"
    break;

  case 82: /* func_arg_list: func_arg_list ',' IDENT  */
#line 660 "script.y"
                  {
		    Output(", ", (yyvsp[0].str), NULL);
		    vardef((yyvsp[0].str), STR, SCAST, NULL);
		  }
#line 2311 "y.tab.c"
    break;

  case 83: /* decl_type: INT  */
#line 667 "script.y"
                  {
		    ReturnIdents = 1;
		    DefType = INT;
		    DefCast = ICAST;
		    (yyval.str) = "int";
		  }
#line 2322 "y.tab.c"
    break;

  case 84: /* decl_type: FLOAT  */
#line 674 "script.y"
                  {
		    ReturnIdents = 1;
		    DefType = FLOAT;
		    DefCast = FCAST;
		    (yyval.str) = "float";
		  }
#line 2333 "y.tab.c"
    break;

  case 85: /* decl_type: STR  */
#line 681 "script.y"
                  {
		    ReturnIdents = 1;
		    DefType = STR;
		    DefCast = SCAST;
		    (yyval.str) = "str";
		  }
#line 2344 "y.tab.c"
    break;

  case 86: /* decl_stmnt: decl_type decl_list  */
#line 690 "script.y"
                  {
		    OutputIndentation();
		    Output((yyvsp[-1].str), " ", (yyvsp[0].str), NULL);
		    (yyval.str) = (yyvsp[0].str);
		  }
#line 2354 "y.tab.c"
    break;

  case 88: /* $@16: %empty  */
#line 699 "script.y"
                  {
		    ReturnIdents = 1;
		  }
#line 2362 "y.tab.c"
    break;

  case 89: /* decl_list: decl_list ',' $@16 decl_ident  */
#line 703 "script.y"
                  {
		    (yyval.str) = Combine((yyvsp[-3].str), ", ", (yyvsp[0].str), NULL);
		  }
#line 2370 "y.tab.c"
    break;

  case 90: /* $@17: %empty  */
#line 709 "script.y"
                  {
		    ReturnIdents = 0;
		  }
#line 2378 "y.tab.c"
    break;

  case 91: /* decl_ident: IDENT $@17 init  */
#line 713 "script.y"
                  {
		    vardef((yyvsp[-2].str), DefType, DefCast, NULL);
		    if ((yyvsp[0].str) != NULL)
			(yyval.str) = Combine((yyvsp[-2].str), " = ", (yyvsp[0].str), NULL);
		    else
			(yyval.str) = (yyvsp[-2].str);
		  }
#line 2390 "y.tab.c"
    break;

  case 92: /* init: %empty  */
#line 723 "script.y"
                  {
		    (yyval.str) = NULL;
		  }
#line 2398 "y.tab.c"
    break;

  case 93: /* init: '=' expr  */
#line 727 "script.y"
                  {
		    (yyval.str) = (yyvsp[0].expr).s;
		  }
#line 2406 "y.tab.c"
    break;

  case 94: /* break_stmnt: BREAK  */
#line 733 "script.y"
                  {
		    OutputIndentation();
		    Output("break", NULL);
		  }
#line 2415 "y.tab.c"
    break;

  case 95: /* return_stmnt: RETURN expr  */
#line 740 "script.y"
                  {
		    OutputIndentation();
		    Output("return ", (yyvsp[0].expr).s, NULL);
		  }
#line 2424 "y.tab.c"
    break;

  case 96: /* return_stmnt: RETURN  */
#line 745 "script.y"
                  {
		    OutputIndentation();
		    Output("return", NULL);
		  }
#line 2433 "y.tab.c"
    break;

  case 97: /* null_stmnt: %empty  */
#line 752 "script.y"
                  { (yyval.str) = NULL; }
#line 2439 "y.tab.c"
    break;

  case 98: /* expr: expr '|' expr  */
#line 756 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, "|", (yyvsp[0].expr).s, NULL); }
#line 2445 "y.tab.c"
    break;

  case 99: /* expr: expr '&' expr  */
#line 758 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, "&", (yyvsp[0].expr).s, NULL); }
#line 2451 "y.tab.c"
    break;

  case 100: /* expr: expr '^' expr  */
#line 760 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, "^", (yyvsp[0].expr).s, NULL); }
#line 2457 "y.tab.c"
    break;

  case 101: /* expr: '~' expr  */
#line 762 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine("~", (yyvsp[0].expr).s, NULL); }
#line 2463 "y.tab.c"
    break;

  case 102: /* expr: expr '+' expr  */
#line 765 "script.y"
                  {
		    if ((yyvsp[-2].expr).t == STR && (yyvsp[0].expr).t == STR)
		      {
			(yyval.expr).s = Combine((yyvsp[-2].expr).s, " @ ", (yyvsp[0].expr).s, NULL);
			(yyval.expr).t = STR;
		      }
		    else
		      {
			(yyval.expr).s = Combine((yyvsp[-2].expr).s, " + ", (yyvsp[0].expr).s, NULL);
			(yyval.expr).t = INT;
		      }
		  }
#line 2480 "y.tab.c"
    break;

  case 103: /* expr: expr '-' expr  */
#line 778 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " - ", (yyvsp[0].expr).s, NULL); }
#line 2486 "y.tab.c"
    break;

  case 104: /* expr: expr '*' expr  */
#line 780 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, "*", (yyvsp[0].expr).s, NULL); }
#line 2492 "y.tab.c"
    break;

  case 105: /* expr: expr '/' expr  */
#line 782 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, "/", (yyvsp[0].expr).s, NULL); }
#line 2498 "y.tab.c"
    break;

  case 106: /* expr: expr '%' expr  */
#line 784 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, "%", (yyvsp[0].expr).s, NULL); }
#line 2504 "y.tab.c"
    break;

  case 107: /* expr: '-' expr  */
#line 786 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine("-", (yyvsp[0].expr).s, NULL); }
#line 2510 "y.tab.c"
    break;

  case 108: /* expr: expr OR expr  */
#line 789 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " || ", (yyvsp[0].expr).s, NULL); }
#line 2516 "y.tab.c"
    break;

  case 109: /* expr: expr AND expr  */
#line 791 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " && ", (yyvsp[0].expr).s, NULL); }
#line 2522 "y.tab.c"
    break;

  case 110: /* expr: '!' expr  */
#line 793 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine("!", (yyvsp[0].expr).s, NULL); }
#line 2528 "y.tab.c"
    break;

  case 111: /* expr: expr LT expr  */
#line 796 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " < ", (yyvsp[0].expr).s, NULL); }
#line 2534 "y.tab.c"
    break;

  case 112: /* expr: expr LE expr  */
#line 798 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " <= ", (yyvsp[0].expr).s, NULL); }
#line 2540 "y.tab.c"
    break;

  case 113: /* expr: expr GT expr  */
#line 800 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " > ", (yyvsp[0].expr).s, NULL); }
#line 2546 "y.tab.c"
    break;

  case 114: /* expr: expr GE expr  */
#line 802 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " >= ", (yyvsp[0].expr).s, NULL); }
#line 2552 "y.tab.c"
    break;

  case 115: /* expr: expr EQ expr  */
#line 804 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " == ", (yyvsp[0].expr).s, NULL); }
#line 2558 "y.tab.c"
    break;

  case 116: /* expr: expr NE expr  */
#line 806 "script.y"
                  { (yyval.expr).t = INT; (yyval.expr).s = Combine((yyvsp[-2].expr).s, " != ", (yyvsp[0].expr).s, NULL); }
#line 2564 "y.tab.c"
    break;

  case 117: /* $@18: %empty  */
#line 809 "script.y"
                    {
			BEGIN FUNCLIT;
		    }
#line 2572 "y.tab.c"
    break;

  case 118: /* $@19: %empty  */
#line 813 "script.y"
                    {
			BEGIN 0;
		    }
#line 2580 "y.tab.c"
    break;

  case 119: /* expr: IDENT '(' $@18 optwslist func_call_list optwslist $@19 ')'  */
#line 817 "script.y"
                  {
		    char*	cmdname;
		    char**	argv;
		    char*	argstr;
		    int		retstr;
		    int		i;

		    cmdname = (yyvsp[-7].str);
		    argv = (char**) (yyvsp[-3].str);
		    switch (MapCommand(&cmdname, argv, &retstr))
		      {
		      case -1:
			argstr = ArgListToStr(argv);
			fprintf(stderr, "Error mapping command: %s %s",
			    cmdname, argstr);
			for (i = 0; argv[i] != NULL; i++)
			    fprintf(stderr, " %s", argv[i]);
			fprintf(stderr, "\n");
			(yyval.expr).t = INT;
			(yyval.expr).s = Combine("/* Could not map: ", cmdname, " ",
							argstr, " */", NULL);
			break;
		      case 0:
			fprintf(stderr, "Possible replacement of a command in an expression\n");
			fprintf(stderr, "with multiple commands.  Look for \"probable error\"\n");
			fprintf(stderr, "in converted script file.\n");
			(yyval.expr).t = INT;
			(yyval.expr).s = "/* probable error */"; /* don't output anything */
			break;
		      default:
			(yyval.expr).t = retstr ? STR : INT;
			(yyval.expr).s = Combine("{", cmdname, " ", ArgListToStr(argv),
								    "}", NULL);
			break;
		      }
		  }
#line 2621 "y.tab.c"
    break;

  case 120: /* $@20: %empty  */
#line 855 "script.y"
                    {
			BEGIN FUNCLIT;
		    }
#line 2629 "y.tab.c"
    break;

  case 121: /* $@21: %empty  */
#line 859 "script.y"
                    {
			BEGIN 0;
		    }
#line 2637 "y.tab.c"
    break;

  case 122: /* expr: FUNCREF '(' $@20 optwslist func_call_list optwslist $@21 ')'  */
#line 863 "script.y"
                  {
		    (yyval.expr).t = INT;
		    (yyval.expr).s = Combine("{", (yyvsp[-7].str), " ", ArgListToStr((yyvsp[-3].str)), "}", NULL);
		  }
#line 2646 "y.tab.c"
    break;

  case 123: /* expr: VARREF  */
#line 869 "script.y"
                  { 
		    Result*	rp;

		    rp = SymtabLook(LocalSymbols, (yyvsp[0].str));
		    if (rp == NULL)
			rp = SymtabLook(&GlobalSymbols, (yyvsp[0].str));

		    (yyval.expr).t = rp->r_type;
		    (yyval.expr).s = (yyvsp[0].str);
 		  }
#line 2661 "y.tab.c"
    break;

  case 124: /* expr: FUNCREF  */
#line 881 "script.y"
                  { 
		    (yyval.expr).t = INT;
		    (yyval.expr).s = Combine("{", (yyvsp[0].str), "}", NULL);
 		  }
#line 2670 "y.tab.c"
    break;

  case 125: /* expr: IDENT  */
#line 887 "script.y"
                  { 
		    char*	cmdname;
		    char*	argv[1];
		    int		retstr;
		    int		i;

		    cmdname = (yyvsp[0].str);
		    argv[0] = NULL;
		    switch (MapCommand(&cmdname, argv, &retstr))
		      {
		      case -1:
			fprintf(stderr, "Error mapping command: %s", cmdname);
			fprintf(stderr, "\n");
			(yyval.expr).t = INT;
			(yyval.expr).s = Combine("/* Could not map: ", cmdname,
							    " */", NULL);
			break;
		      case 0:
			fprintf(stderr, "Possible replacement of a command in an expression\n");
			fprintf(stderr, "with multiple commands.  Look for \"probable error\"\n");
			fprintf(stderr, "in converted script file.\n");
			(yyval.expr).t = INT;
			(yyval.expr).s = "/* probable error */"; /* don't output anything */
			break;
		      default:
			(yyval.expr).t = retstr ? STR : INT;
			(yyval.expr).s = Combine("{", cmdname, "}", NULL);
			break;
		      }
 		  }
#line 2705 "y.tab.c"
    break;

  case 126: /* expr: FLOATCONST  */
#line 919 "script.y"
                  { 
		    (yyval.expr).t = INT;
		    (yyval.expr).s = (yyvsp[0].str);
 		  }
#line 2714 "y.tab.c"
    break;

  case 127: /* expr: INTCONST  */
#line 924 "script.y"
                  { 
		    (yyval.expr).t = INT;
		    (yyval.expr).s = (yyvsp[0].str);
 		  }
#line 2723 "y.tab.c"
    break;

  case 128: /* expr: STRCONST  */
#line 929 "script.y"
                  { 
		    (yyval.expr).t = STR;
		    (yyval.expr).s = Combine("\"", (yyvsp[0].str), "\"", NULL);
 		  }
#line 2732 "y.tab.c"
    break;

  case 129: /* expr: DOLLARARG  */
#line 935 "script.y"
                  {
		    (yyval.expr).t = STR;
		    (yyval.expr).s = (yyvsp[0].str);
		  }
#line 2741 "y.tab.c"
    break;

  case 130: /* expr: '{' expr '}'  */
#line 941 "script.y"
                  {
		    (yyval.expr).t = (yyvsp[-1].expr).t;
		    (yyval.expr).s = Combine("(", (yyvsp[-1].expr).s, ")", NULL);
		  }
#line 2750 "y.tab.c"
    break;

  case 131: /* expr: '(' expr ')'  */
#line 948 "script.y"
                  {
		    (yyval.expr).t = (yyvsp[-1].expr).t;
		    (yyval.expr).s = Combine("(", (yyvsp[-1].expr).s, ")", NULL);
		  }
#line 2759 "y.tab.c"
    break;


#line 2763 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 954 "script.y"


#if defined(decalpha) && !defined(bison)
extern YYSTYPE	yylval;

#if defined(__FreeBSD__)
#include "y.tab.h"
#endif

#include "lex.yy.c"

#endif
/*
** TokenStr
**
**	Return the token string for the given token.
*/

char *TokenStr(token)

int	token;

{	/* TokenStr --- Return token string for token */

	static char	buf[100];

	switch (token)
	  {

	  case LT: return("<");
	  case LE: return("<=");
	  case GT: return(">");
	  case GE: return(">=");
	  case EQ: return("==");
	  case NE: return("!=");

	  case OR: return("||");
	  case AND: return("&&");

#define	RET(tok)	case tok: return("tok")

	  RET(UMINUS);

	  RET(WHILE);
	  RET(IF);
	  RET(ELSE);
	  RET(FOR);
	  RET(FOREACH);
	  RET(END);
	  RET(INCLUDE);
	  RET(BREAK);
	  RET(INT);
	  RET(FLOAT);
	  RET(STR);
	  RET(RETURN);
	  RET(WHITESPACE);
	  RET(FUNCTION);
	  RET(INTCONST);
	  RET(DOLLARARG);
	  RET(FLOATCONST);
	  RET(STRCONST);
	  RET(LITERAL);
	  RET(IDENT);
	  RET(VARREF);
	  RET(FUNCREF);
	  RET(SL);
	  RET(COMMAND);
	  RET(ARGUMENT);
	  RET(ARGLIST);
	  RET(LOCREF);
	  RET(ICAST);
	  RET(FCAST);
	  RET(SCAST);

	  }

	if (token < 128)
	    if (token < ' ')
		sprintf(buf, "^%c", token+'@');
	    else
		sprintf(buf, "%c", token);
	else
	    sprintf(buf, "%d", token);

	return(buf);

}	/* TokenStr */



ParseNode *vardef(ident, type, castop, init)

char		*ident;
int		type;
int		castop;
char	*init;

{	/* vardef --- Define a variable */

	ParseNode	*pn;
	Result		*rp, r;
	ResultValue	v, slv;

	if (InFunctionDefinition && LocalSymbols != NULL)
	  {
	    rp = SymtabNew(LocalSymbols, ident);
	        rp->r_type = type;
		rp->r.r_loc.l_type = type;
		rp->r.r_loc.l_offs = NextLocal++;
	  }
	else
	  {
	    rp = SymtabNew(&GlobalSymbols, ident);

	    rp->r_type = type;
	  }

}	/* vardef */


ParseInit()

{    /* ParseInit --- Initialize parser variables */

        InFunctionDefinition = 0;
	Compiling = 0;
	BreakAllowed = 0;
	LocalSymbols = NULL;
	nextchar(1);	/* Flush lexer input */

}    /* ParseInit */


int NestedLevel()

{    /* NestedLevel --- Return TRUE if in func_def or control structure */

        return(InFunctionDefinition || Compiling);

}    /* NestedLevel */

int AlreadyBracketed(str)

char*	str;

{	/* AlreadyBracketed --- Return TRUE if the string has valid curley
				braces */

	if (*str == '{')
	  {
	    int	braceCount;

	    braceCount = 1;
	    for (str++; braceCount > 0 && *str != '\0'; str++)
	      {
		if (*str == '{')
		    braceCount++;
		else if (*str == '}')
		    braceCount--;
	      }

	    return braceCount == 0 && *str == '\0';
	  }
	else
	    return 0;

}	/* AlreadyBracketed */
