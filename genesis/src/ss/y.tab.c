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

static char parsercsid[] = "$Id: script.y,v 1.5 2006/02/15 18:47:00 svitak Exp $";

/*
** $Log: script.y,v $
** Revision 1.5  2006/02/15 18:47:00  svitak
** Changes to allow parsing of scripts which use linefeeds containing \r, or
** carriage return.
**
** Revision 1.4  2005/08/08 13:10:21  svitak
** Removed #ifdef around #include y.tab.h.
**
** Revision 1.3  2005/06/27 19:01:13  svitak
** Added explicit types to untyped functions and fixed return values as
** appropriate. Initialized values explicitly when it was unclear if
** they were being used uninitialized (may not apply to all files being
** checked in in this batch).
**
** Revision 1.2  2005/06/25 22:04:34  svitak
** Added explicit return types to untyped functions. Fixed return statements.
**
** Revision 1.1.1.1  2005/06/14 04:38:32  svitak
** Import from snapshot of CalTech CVS tree of June 8, 2005
**
** Revision 1.24  2003/03/28 21:03:58  gen-dbeeman
** Changes from Hugo Cornelis to enable debugging commands gctrace and gftrace
** Fix from Mike Vanier Jan 2003 to fix problem with bison ver. 1.75
**
** Revision 1.23  2001/04/25 17:17:04  mhucka
** Misc. small changes to improve portability and address compiler warnings.
**
** Revision 1.21  1997/07/24 00:32:16  dhb
** Additional T3E mods from PSC
**
** Revision 1.20  1997/06/12 22:49:35  dhb
** Added include of string.h for strlen() declaration needed by
** included lexer code.
**
** Revision 1.19  1996/06/26 18:17:55  venkat
** Added preprocessor macros to deal with the order of the include lex.yy.c
** statement and the definitions of the macros used in it on the DEC/alpha.
**
 * Revision 1.18  1995/06/16  06:01:10  dhb
 * FreeBSD compatibility.
 *
 * Revision 1.17  1995/06/14  20:34:25  dhb
 * Fix to allow variable names to appear as first part of a command
 * with trailing arg_component_list.
 *
 * Revision 1.16  1995/05/26  17:37:40  dhb
 * Changed lexer start state used for parsing opt_node syntax from
 * FUNCLIT to LIT which allows commas and parenthesis in the LITERALs
 * there.  The node syntax allows comma separated node specs.
 *
 * Revision 1.15  1995/05/08  22:34:16  dhb
 * Removed non-terminal typing for cmdname_expr (e.g. %type statement)
 *
 * Revision 1.14  1995/05/08  22:31:51  dhb
 * Changed optional node syntax appended to command and function calls
 * to be an optional arg_component_list.  This will allow just about
 * anything following an initial command for function name.
 *
 * Revision 1.13  1995/04/29  01:21:59  dhb
 * Moved include of lex.yy.c back to original location.  SGI specific
 * problem is fixed by extern void exit() in script.l.
 *
 * Revision 1.12  1995/04/24  22:36:15  dhb
 * Call to SymtabKey() in func_call production code was passing
 * a Symtab rather than a Symtab*.
 *
 * Revision 1.11  1995/04/15  02:23:11  dhb
 * Moved include of lex.yy.c after parse rules.  SGI lex generates calls
 * to exit() but SGI yacc doesn't include unistd.h until it starts doing
 * the rules.  Since unistd.h defines void exit() and cc interprets the
 * calls in the lexer as int exit() cc complains we are redefining the
 * return type.
 *
 * Revision 1.10  1994/12/15  21:52:36  dhb
 * Added support for adding @node to SLI script function calls.  Will allow
 * calling script function on other nodes on parallel systems.
 *
 * Revision 1.9  1994/12/02  00:05:45  dhb
 * Added elif to if then else construct.
 *
 * Added ** operator to do pow().
 *
 * Revision 1.8  1994/10/18  17:32:10  dhb
 * Changed PTEval() call to PTCall() which frees the evaluated result.
 *
 * Revision 1.7  1994/10/14  17:22:05  dhb
 * Another memory leak of ScriptInfo patched.
 *
 * Revision 1.6  1994/10/12  17:14:21  dhb
 * Removed dead code.
 *
 * Patched various memory leaks.
 *
 * Removed foreach restriction that the loop variable be a string.
 *
 * Revision 1.5  1994/08/31  03:03:23  dhb
 * Allow additional whitespace in foreach argument list.  This allows
 * for line continuations within the arglist including just after ( and
 * before ).
 *
 * Revision 1.4  1994/06/03  21:09:56  dhb
 * Fixed precedence problem where a == b && c == d was a syntax error.
 *
 * Revision 1.3  1994/04/16  17:19:55  dhb
 * Fixed operator precedence problem.  Made ! have higher prec than
 * || and &&.
 *
 * Revision 1.2  1993/03/01  17:39:01  dhb
 * 1.4 to 2.0 script language changes.
 *
 * 	Removed support for `function call' format of command invokation from
 * 	both the command line and expressions.  Commands are invoked in
 * 	expressions and command arguments by delimiting them with curly braces.
 *
 * 	Added @ operator for string concatenation.
 *
 * Revision 1.1  1992/12/11  21:19:07  dhb
 * Initial revision
 *
*/

#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <string.h>
#include "parse.h"
#include "symtab.h"
#include "ss_func_ext.h"

/*
** Parser routines which return something other than int.
*/

extern ParseNode *vardef();
extern char *TokenStr();
extern char *MakeScriptInfo();	/* Actually a generic pointer */

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

#line 196 "script.y"

#if !defined(decalpha) || defined(bison) || defined(T3E)
/*
** Start of lexical analyzer.  LEX source is in "script.l".
*/

extern YYSTYPE	yylval;

#include "y.tab.h"
#include "lex.yy.c"

#endif

#line 246 "y.tab.c"

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
    OR = 258,                      /* OR  */
    AND = 259,                     /* AND  */
    LT = 260,                      /* LT  */
    LE = 261,                      /* LE  */
    GT = 262,                      /* GT  */
    GE = 263,                      /* GE  */
    EQ = 264,                      /* EQ  */
    NE = 265,                      /* NE  */
    POW = 266,                     /* POW  */
    UMINUS = 267,                  /* UMINUS  */
    WHILE = 268,                   /* WHILE  */
    IF = 269,                      /* IF  */
    ELSE = 270,                    /* ELSE  */
    ELIF = 271,                    /* ELIF  */
    FOR = 272,                     /* FOR  */
    FOREACH = 273,                 /* FOREACH  */
    END = 274,                     /* END  */
    INCLUDE = 275,                 /* INCLUDE  */
    ENDSCRIPT = 276,               /* ENDSCRIPT  */
    BREAK = 277,                   /* BREAK  */
    INT = 278,                     /* INT  */
    FLOAT = 279,                   /* FLOAT  */
    STR = 280,                     /* STR  */
    RETURN = 281,                  /* RETURN  */
    WHITESPACE = 282,              /* WHITESPACE  */
    FUNCTION = 283,                /* FUNCTION  */
    INTCONST = 284,                /* INTCONST  */
    DOLLARARG = 285,               /* DOLLARARG  */
    FLOATCONST = 286,              /* FLOATCONST  */
    STRCONST = 287,                /* STRCONST  */
    LITERAL = 288,                 /* LITERAL  */
    IDENT = 289,                   /* IDENT  */
    VARREF = 290,                  /* VARREF  */
    FUNCREF = 291,                 /* FUNCREF  */
    EXTERN = 292,                  /* EXTERN  */
    SL = 293,                      /* SL  */
    COMMAND = 294,                 /* COMMAND  */
    EXPRCALL = 295,                /* EXPRCALL  */
    ARGUMENT = 296,                /* ARGUMENT  */
    ARGLIST = 297,                 /* ARGLIST  */
    LOCREF = 298,                  /* LOCREF  */
    ICAST = 299,                   /* ICAST  */
    FCAST = 300,                   /* FCAST  */
    SCAST = 301                    /* SCAST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define OR 258
#define AND 259
#define LT 260
#define LE 261
#define GT 262
#define GE 263
#define EQ 264
#define NE 265
#define POW 266
#define UMINUS 267
#define WHILE 268
#define IF 269
#define ELSE 270
#define ELIF 271
#define FOR 272
#define FOREACH 273
#define END 274
#define INCLUDE 275
#define ENDSCRIPT 276
#define BREAK 277
#define INT 278
#define FLOAT 279
#define STR 280
#define RETURN 281
#define WHITESPACE 282
#define FUNCTION 283
#define INTCONST 284
#define DOLLARARG 285
#define FLOATCONST 286
#define STRCONST 287
#define LITERAL 288
#define IDENT 289
#define VARREF 290
#define FUNCREF 291
#define EXTERN 292
#define SL 293
#define COMMAND 294
#define EXPRCALL 295
#define ARGUMENT 296
#define ARGLIST 297
#define LOCREF 298
#define ICAST 299
#define FCAST 300
#define SCAST 301

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
  YYSYMBOL_OR = 3,                         /* OR  */
  YYSYMBOL_AND = 4,                        /* AND  */
  YYSYMBOL_LT = 5,                         /* LT  */
  YYSYMBOL_LE = 6,                         /* LE  */
  YYSYMBOL_GT = 7,                         /* GT  */
  YYSYMBOL_GE = 8,                         /* GE  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_NE = 10,                        /* NE  */
  YYSYMBOL_11_ = 11,                       /* '!'  */
  YYSYMBOL_12_ = 12,                       /* '+'  */
  YYSYMBOL_13_ = 13,                       /* '-'  */
  YYSYMBOL_14_ = 14,                       /* '&'  */
  YYSYMBOL_15_ = 15,                       /* '|'  */
  YYSYMBOL_16_ = 16,                       /* '^'  */
  YYSYMBOL_17_ = 17,                       /* '@'  */
  YYSYMBOL_18_ = 18,                       /* '*'  */
  YYSYMBOL_19_ = 19,                       /* '/'  */
  YYSYMBOL_20_ = 20,                       /* '%'  */
  YYSYMBOL_21_ = 21,                       /* '~'  */
  YYSYMBOL_POW = 22,                       /* POW  */
  YYSYMBOL_UMINUS = 23,                    /* UMINUS  */
  YYSYMBOL_WHILE = 24,                     /* WHILE  */
  YYSYMBOL_IF = 25,                        /* IF  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_ELIF = 27,                      /* ELIF  */
  YYSYMBOL_FOR = 28,                       /* FOR  */
  YYSYMBOL_FOREACH = 29,                   /* FOREACH  */
  YYSYMBOL_END = 30,                       /* END  */
  YYSYMBOL_INCLUDE = 31,                   /* INCLUDE  */
  YYSYMBOL_ENDSCRIPT = 32,                 /* ENDSCRIPT  */
  YYSYMBOL_BREAK = 33,                     /* BREAK  */
  YYSYMBOL_INT = 34,                       /* INT  */
  YYSYMBOL_FLOAT = 35,                     /* FLOAT  */
  YYSYMBOL_STR = 36,                       /* STR  */
  YYSYMBOL_RETURN = 37,                    /* RETURN  */
  YYSYMBOL_WHITESPACE = 38,                /* WHITESPACE  */
  YYSYMBOL_FUNCTION = 39,                  /* FUNCTION  */
  YYSYMBOL_INTCONST = 40,                  /* INTCONST  */
  YYSYMBOL_DOLLARARG = 41,                 /* DOLLARARG  */
  YYSYMBOL_FLOATCONST = 42,                /* FLOATCONST  */
  YYSYMBOL_STRCONST = 43,                  /* STRCONST  */
  YYSYMBOL_LITERAL = 44,                   /* LITERAL  */
  YYSYMBOL_IDENT = 45,                     /* IDENT  */
  YYSYMBOL_VARREF = 46,                    /* VARREF  */
  YYSYMBOL_FUNCREF = 47,                   /* FUNCREF  */
  YYSYMBOL_EXTERN = 48,                    /* EXTERN  */
  YYSYMBOL_SL = 49,                        /* SL  */
  YYSYMBOL_COMMAND = 50,                   /* COMMAND  */
  YYSYMBOL_EXPRCALL = 51,                  /* EXPRCALL  */
  YYSYMBOL_ARGUMENT = 52,                  /* ARGUMENT  */
  YYSYMBOL_ARGLIST = 53,                   /* ARGLIST  */
  YYSYMBOL_LOCREF = 54,                    /* LOCREF  */
  YYSYMBOL_ICAST = 55,                     /* ICAST  */
  YYSYMBOL_FCAST = 56,                     /* FCAST  */
  YYSYMBOL_SCAST = 57,                     /* SCAST  */
  YYSYMBOL_58_n_ = 58,                     /* '\n'  */
  YYSYMBOL_59_r_ = 59,                     /* '\r'  */
  YYSYMBOL_60_ = 60,                       /* ';'  */
  YYSYMBOL_61_ = 61,                       /* '('  */
  YYSYMBOL_62_ = 62,                       /* ')'  */
  YYSYMBOL_63_ = 63,                       /* '='  */
  YYSYMBOL_64_ = 64,                       /* '{'  */
  YYSYMBOL_65_ = 65,                       /* '}'  */
  YYSYMBOL_66_ = 66,                       /* ','  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_script = 68,                    /* script  */
  YYSYMBOL_statement_list = 69,            /* statement_list  */
  YYSYMBOL_70_1 = 70,                      /* @1  */
  YYSYMBOL_stmnt_terminator = 71,          /* stmnt_terminator  */
  YYSYMBOL_statement = 72,                 /* statement  */
  YYSYMBOL_endscript_marker = 73,          /* endscript_marker  */
  YYSYMBOL_while_stmnt = 74,               /* while_stmnt  */
  YYSYMBOL_75_2 = 75,                      /* @2  */
  YYSYMBOL_for_stmnt = 76,                 /* for_stmnt  */
  YYSYMBOL_77_3 = 77,                      /* @3  */
  YYSYMBOL_foreach_stmnt = 78,             /* foreach_stmnt  */
  YYSYMBOL_79_4 = 79,                      /* $@4  */
  YYSYMBOL_80_5 = 80,                      /* $@5  */
  YYSYMBOL_if_stmnt = 81,                  /* if_stmnt  */
  YYSYMBOL_82_6 = 82,                      /* @6  */
  YYSYMBOL_else_clause = 83,               /* else_clause  */
  YYSYMBOL_84_7 = 84,                      /* @7  */
  YYSYMBOL_assign_stmnt = 85,              /* assign_stmnt  */
  YYSYMBOL_include_hdr = 86,               /* include_hdr  */
  YYSYMBOL_87_8 = 87,                      /* $@8  */
  YYSYMBOL_include_stmnt = 88,             /* include_stmnt  */
  YYSYMBOL_opt_node = 89,                  /* opt_node  */
  YYSYMBOL_cmd_name = 90,                  /* cmd_name  */
  YYSYMBOL_91_9 = 91,                      /* $@9  */
  YYSYMBOL_92_10 = 92,                     /* $@10  */
  YYSYMBOL_cmd_stmnt = 93,                 /* cmd_stmnt  */
  YYSYMBOL_94_11 = 94,                     /* $@11  */
  YYSYMBOL_funcref = 95,                   /* funcref  */
  YYSYMBOL_func_call = 96,                 /* func_call  */
  YYSYMBOL_97_12 = 97,                     /* $@12  */
  YYSYMBOL_opt_arg_list = 98,              /* opt_arg_list  */
  YYSYMBOL_arg_list = 99,                  /* arg_list  */
  YYSYMBOL_optwslist = 100,                /* optwslist  */
  YYSYMBOL_wslist = 101,                   /* wslist  */
  YYSYMBOL_ws = 102,                       /* ws  */
  YYSYMBOL_arg_component_list = 103,       /* arg_component_list  */
  YYSYMBOL_arg_component = 104,            /* arg_component  */
  YYSYMBOL_105_13 = 105,                   /* $@13  */
  YYSYMBOL_106_14 = 106,                   /* $@14  */
  YYSYMBOL_ac_func_cmd_expr = 107,         /* ac_func_cmd_expr  */
  YYSYMBOL_ext_func = 108,                 /* ext_func  */
  YYSYMBOL_func_hdr = 109,                 /* func_hdr  */
  YYSYMBOL_func_def = 110,                 /* func_def  */
  YYSYMBOL_111_15 = 111,                   /* $@15  */
  YYSYMBOL_112_16 = 112,                   /* $@16  */
  YYSYMBOL_func_args = 113,                /* func_args  */
  YYSYMBOL_func_arg_list = 114,            /* func_arg_list  */
  YYSYMBOL_decl_type = 115,                /* decl_type  */
  YYSYMBOL_decl_stmnt = 116,               /* decl_stmnt  */
  YYSYMBOL_decl_list = 117,                /* decl_list  */
  YYSYMBOL_118_17 = 118,                   /* $@17  */
  YYSYMBOL_decl_ident = 119,               /* decl_ident  */
  YYSYMBOL_120_18 = 120,                   /* $@18  */
  YYSYMBOL_init = 121,                     /* init  */
  YYSYMBOL_break_stmnt = 122,              /* break_stmnt  */
  YYSYMBOL_return_stmnt = 123,             /* return_stmnt  */
  YYSYMBOL_null_stmnt = 124,               /* null_stmnt  */
  YYSYMBOL_expr = 125                      /* expr  */
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
#define YYLAST   378

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  218

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


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
      58,     2,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    11,     2,     2,     2,    20,    14,     2,
      61,    62,    18,    12,    66,    13,     2,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    60,
       2,    63,     2,     2,    17,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,    15,    65,    21,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   212,   212,   216,   220,   219,   255,   256,   257,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   277,   298,   297,   315,   314,   337,
     343,   336,   360,   359,   377,   380,   383,   382,   399,   414,
     413,   423,   459,   493,   496,   537,   536,   551,   550,   582,
     581,   621,   629,   628,   650,   653,   659,   663,   669,   670,
     673,   674,   677,   678,   681,   687,   695,   702,   709,   717,
     721,   716,   730,   734,   738,   747,   766,   772,   807,   856,
     860,   855,   876,   877,   881,   892,   905,   911,   917,   925,
     931,   933,   932,   946,   945,   957,   958,   962,   974,   980,
     989,   992,   994,   996,   998,  1001,  1004,  1006,  1008,  1010,
    1012,  1014,  1016,  1019,  1021,  1023,  1026,  1028,  1030,  1032,
    1034,  1036,  1039,  1059,  1066,  1073,  1081,  1089,  1093,  1097,
    1101
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
  "\"end of file\"", "error", "\"invalid token\"", "OR", "AND", "LT",
  "LE", "GT", "GE", "EQ", "NE", "'!'", "'+'", "'-'", "'&'", "'|'", "'^'",
  "'@'", "'*'", "'/'", "'%'", "'~'", "POW", "UMINUS", "WHILE", "IF",
  "ELSE", "ELIF", "FOR", "FOREACH", "END", "INCLUDE", "ENDSCRIPT", "BREAK",
  "INT", "FLOAT", "STR", "RETURN", "WHITESPACE", "FUNCTION", "INTCONST",
  "DOLLARARG", "FLOATCONST", "STRCONST", "LITERAL", "IDENT", "VARREF",
  "FUNCREF", "EXTERN", "SL", "COMMAND", "EXPRCALL", "ARGUMENT", "ARGLIST",
  "LOCREF", "ICAST", "FCAST", "SCAST", "'\\n'", "'\\r'", "';'", "'('",
  "')'", "'='", "'{'", "'}'", "','", "$accept", "script", "statement_list",
  "@1", "stmnt_terminator", "statement", "endscript_marker", "while_stmnt",
  "@2", "for_stmnt", "@3", "foreach_stmnt", "$@4", "$@5", "if_stmnt", "@6",
  "else_clause", "@7", "assign_stmnt", "include_hdr", "$@8",
  "include_stmnt", "opt_node", "cmd_name", "$@9", "$@10", "cmd_stmnt",
  "$@11", "funcref", "func_call", "$@12", "opt_arg_list", "arg_list",
  "optwslist", "wslist", "ws", "arg_component_list", "arg_component",
  "$@13", "$@14", "ac_func_cmd_expr", "ext_func", "func_hdr", "func_def",
  "$@15", "$@16", "func_args", "func_arg_list", "decl_type", "decl_stmnt",
  "decl_list", "$@17", "decl_ident", "$@18", "init", "break_stmnt",
  "return_stmnt", "null_stmnt", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-102)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-64)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -102,    23,    28,  -102,   242,   -32,    17,    24,   -12,  -102,
    -102,  -102,  -102,  -102,  -102,    93,   -29,  -102,    27,  -102,
     -21,   -27,  -102,  -102,  -102,  -102,  -102,  -102,    47,  -102,
    -102,  -102,    43,  -102,  -102,  -102,  -102,    53,  -102,  -102,
    -102,  -102,    93,    93,    54,    38,    63,    93,    93,    93,
    -102,  -102,  -102,  -102,  -102,    93,    81,   309,  -102,  -102,
      43,    93,    43,  -102,  -102,  -102,  -102,  -102,  -102,    70,
    -102,  -102,  -102,  -102,  -102,  -102,    43,  -102,    48,  -102,
      45,  -102,   159,   179,    27,    55,  -102,  -102,  -102,   356,
    -102,    91,   200,    52,    65,    67,    32,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,  -102,   309,    43,    43,  -102,
      80,    81,  -102,  -102,    75,  -102,    74,  -102,  -102,  -102,
      93,   100,  -102,  -102,  -102,  -102,   327,   327,   345,   345,
     345,   345,   345,   345,   131,   131,   131,   131,   131,   131,
      91,    91,    91,  -102,    80,    43,   -38,    39,  -102,  -102,
    -102,  -102,   309,    80,  -102,   -58,  -102,    93,  -102,    53,
    -102,  -102,   241,  -102,    43,   102,    39,  -102,  -102,    43,
      76,  -102,  -102,    99,   113,   309,  -102,   116,   -15,    54,
     100,    43,  -102,  -102,  -102,  -102,  -102,    86,   122,    96,
    -102,    39,   125,    93,  -102,  -102,    97,   220,  -102,  -102,
    -102,   130,   140,  -102,  -102,  -102,   -15,  -102
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     4,     1,   100,     0,     0,     0,     0,    39,
      24,    97,    86,    87,    88,    99,     0,    45,    47,    51,
       0,     0,    15,     9,    10,    11,    12,    13,     0,    14,
      49,    16,    43,    17,    19,    79,    18,     0,    20,    21,
      22,    23,     0,     0,     0,     0,    62,     0,     0,     0,
     124,   126,   123,   125,   122,     0,     0,    98,    77,    78,
      43,     0,     0,    75,    76,     6,     7,     8,     5,    62,
      54,    68,    67,    66,    69,    52,    44,    64,    82,    93,
      89,    90,     0,     0,     0,     0,    29,    63,    40,   115,
     112,   104,     0,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,    38,    48,    63,    42,
      62,     0,    54,    65,     0,    80,    95,    91,    25,    32,
       0,    58,   130,   128,   129,   127,   113,   114,   116,   117,
     118,   119,   120,   121,   106,   107,   102,   101,   103,   105,
     108,   109,   110,   111,    62,    56,    60,     0,    50,    73,
      72,    70,    74,    62,    84,     0,     3,     0,    94,     0,
       3,     3,     0,    60,     0,    59,     0,    41,    61,    55,
       0,    53,    83,     0,     4,    96,    92,     4,     4,     0,
      58,    57,    71,    85,    81,    26,     3,     0,     0,     0,
      30,    59,     4,     0,    33,    27,     0,     0,     3,     3,
      36,     4,     4,     3,    28,    31,     4,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -102,  -102,    98,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,   -36,  -102,   -41,  -102,
    -102,  -102,   142,  -102,  -102,  -102,   -47,  -102,  -102,   -46,
    -102,    68,    26,    21,  -101,   -44,   -45,   -74,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,    62,  -102,  -102,  -102,  -102,  -102,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     4,    68,    21,    22,    23,   170,    24,
     208,    25,   131,   206,    26,   171,   198,   213,    27,    28,
      46,    29,    75,    30,    60,    62,    31,    70,    32,    33,
     122,   120,   154,   174,   157,    88,    76,    77,   121,   180,
     161,    34,    35,    36,    78,   166,   125,   165,    37,    38,
      80,   169,    81,   126,   168,    39,    40,    41,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      82,    83,   123,    85,   182,    89,    90,    91,   183,    94,
      95,   196,   197,    92,    96,   -34,    58,   117,    59,   116,
     -63,   -63,   -63,     3,    63,   119,    64,   -63,    -2,    42,
     175,    65,    66,    67,    45,    97,    98,    99,   100,   101,
     102,   103,   104,   123,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   176,   114,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   155,   159,   160,   158,   178,    43,   162,
      71,   123,    72,    73,    71,    44,    72,    73,   172,   201,
      61,    69,    47,   -47,    48,   -47,   -47,   135,    79,    86,
      84,    87,    49,    74,    47,   123,    48,    74,   118,   124,
     177,   127,   179,   114,    49,   130,   -47,   123,   156,   181,
     164,    50,    51,    52,    53,   185,    17,    93,    19,   155,
     133,   191,   134,    50,    51,    52,    53,   167,   173,    54,
     178,   192,    55,   194,   193,    56,   195,   203,   199,   111,
     112,   113,   204,   114,    55,   -35,   191,    56,   205,   209,
     214,   207,    97,    98,    99,   100,   101,   102,   103,   104,
     215,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     217,   114,    97,    98,    99,   100,   101,   102,   103,   104,
     163,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     190,   114,   115,    97,    98,    99,   100,   101,   102,   103,
     104,   200,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   128,   114,    97,    98,    99,   100,   101,   102,   103,
     104,   186,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   129,   114,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   132,   114,   184,     0,     5,     6,   187,   188,
       7,     8,     0,     9,    10,    11,    12,    13,    14,    15,
       0,    16,   210,     0,     0,     0,     0,    17,    18,    19,
      20,     0,     0,     0,   202,     0,     0,     0,     0,     0,
       0,   189,     0,     0,     0,     0,   211,   212,     0,     0,
       0,   216,    97,    98,    99,   100,   101,   102,   103,   104,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       0,   114,    99,   100,   101,   102,   103,   104,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     0,   114,
     -64,   -64,   -64,   -64,   -64,   -64,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     0,   114,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,   114
};

static const yytype_int16 yycheck[] =
{
      42,    43,    76,    44,    62,    47,    48,    49,    66,    56,
      56,    26,    27,    55,    56,    30,    45,    62,    47,    61,
      58,    59,    60,     0,    45,    69,    47,    65,     0,    61,
     131,    58,    59,    60,    46,     3,     4,     5,     6,     7,
       8,     9,    10,   117,    12,    13,    14,    15,    16,    17,
      18,    19,    20,   154,    22,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   118,   121,   121,   120,    38,    61,   121,
      41,   155,    43,    44,    41,    61,    43,    44,   130,   190,
      63,    44,    11,    41,    13,    43,    44,    65,    45,    61,
      46,    38,    21,    64,    11,   179,    13,    64,    38,    61,
     154,    66,   157,    22,    21,    60,    64,   191,    38,   163,
      45,    40,    41,    42,    43,   167,    45,    46,    47,   174,
      65,   176,    65,    40,    41,    42,    43,    63,    38,    46,
      38,    65,    61,    30,    45,    64,    30,    61,   189,    18,
      19,    20,    30,    22,    61,    30,   201,    64,    62,    62,
      30,   203,     3,     4,     5,     6,     7,     8,     9,    10,
      30,    12,    13,    14,    15,    16,    17,    18,    19,    20,
     216,    22,     3,     4,     5,     6,     7,     8,     9,    10,
     122,    12,    13,    14,    15,    16,    17,    18,    19,    20,
     174,    22,    60,     3,     4,     5,     6,     7,     8,     9,
      10,   190,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    62,    22,     3,     4,     5,     6,     7,     8,     9,
      10,   169,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    62,    22,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    62,    22,   166,    -1,    24,    25,   170,   171,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      -1,    39,    62,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    -1,    -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,   208,   209,    -1,    -1,
      -1,   213,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      -1,    22,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    22,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    -1,    22,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,    69,     0,    70,    24,    25,    28,    29,    31,
      32,    33,    34,    35,    36,    37,    39,    45,    46,    47,
      48,    72,    73,    74,    76,    78,    81,    85,    86,    88,
      90,    93,    95,    96,   108,   109,   110,   115,   116,   122,
     123,   124,    61,    61,    61,    46,    87,    11,    13,    21,
      40,    41,    42,    43,    46,    61,    64,   125,    45,    47,
      91,    63,    92,    45,    47,    58,    59,    60,    71,    44,
      94,    41,    43,    44,    64,    89,   103,   104,   111,    45,
     117,   119,   125,   125,    46,    85,    61,    38,   102,   125,
     125,   125,   125,    46,    93,    96,   125,     3,     4,     5,
       6,     7,     8,     9,    10,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    22,    89,   125,   103,    38,   102,
      98,   105,    97,   104,    61,   113,   120,    66,    62,    62,
      60,    79,    62,    65,    65,    65,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,    99,   103,    38,   101,   102,    93,
      96,   107,   125,    98,    45,   114,   112,    63,   121,   118,
      75,    82,   125,    38,   100,   101,   101,   102,    38,   103,
     106,   102,    62,    66,    69,   125,   119,    69,    69,    60,
      99,   103,    65,    45,    30,    30,    26,    27,    83,    85,
     100,   101,    69,    61,    30,    62,    80,   125,    77,    62,
      62,    69,    69,    84,    30,    30,    69,    83
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    69,    70,    69,    71,    71,    71,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    75,    74,    77,    76,    79,
      80,    78,    82,    81,    83,    83,    84,    83,    85,    87,
      86,    88,    88,    89,    89,    91,    90,    92,    90,    94,
      93,    95,    97,    96,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   105,
     106,   104,   107,   107,   107,   108,   108,   109,   109,   111,
     112,   110,   113,   113,   114,   114,   115,   115,   115,   116,
     117,   118,   117,   120,   119,   121,   121,   122,   123,   123,
     124,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     0,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     7,     0,    11,     0,
       0,    11,     0,     8,     0,     2,     0,     7,     3,     0,
       3,     5,     3,     0,     1,     0,     3,     0,     3,     0,
       4,     1,     0,     5,     0,     3,     1,     3,     0,     1,
       1,     2,     0,     1,     1,     2,     1,     1,     1,     0,
       0,     5,     1,     1,     1,     2,     2,     2,     2,     0,
       0,     6,     0,     3,     1,     3,     1,     1,     1,     2,
       1,     0,     4,     0,     3,     0,     2,     1,     2,     1,
       0,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     3,     3,     3,
       3
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
#line 216 "script.y"
                  { 
		    (yyval.pn) = NULL;
 		  }
#line 1681 "y.tab.c"
    break;

  case 4: /* @1: %empty  */
#line 220 "script.y"
                  {
		    (yyval.str) = (char *) MakeScriptInfo();
		    SetLine((yyval.str));
		  }
#line 1690 "y.tab.c"
    break;

  case 5: /* statement_list: statement_list @1 statement stmnt_terminator  */
#line 225 "script.y"
                  {
		    ResultValue	v;

		    if (InFunctionDefinition || Compiling)
			if ((yyvsp[-1].pn) != NULL)
			  {
			    v.r_str = (yyvsp[-2].str);
			    (yyval.pn) = PTNew(SL, v, (yyvsp[-3].pn), (yyvsp[-1].pn));
			  }
			else
			  {
			    FreeScriptInfo((yyvsp[-2].str));
			    (yyval.pn) = (yyvsp[-3].pn);
			  }
		    else
		      {
		        /* execute statement */
		        if (setjmp(BreakBuf) == 0) {
			    if (setjmp(ReturnBuf) == 0)
				PTCall((yyvsp[-1].pn));
			    else
				EndScript();
		        }
			FreeScriptInfo((yyvsp[-2].str));
			FreePTValues((yyvsp[-1].pn));
			PTFree((yyvsp[-1].pn));
		      }
		  }
#line 1723 "y.tab.c"
    break;

  case 24: /* endscript_marker: ENDSCRIPT  */
#line 278 "script.y"
                  {
		    /*
		    ** When the end of a script is encountered, the simulator
		    ** sgets routine returns NULL.  The nextchar routine in the
		    ** lexer returns a special character '\200' which is lexed
		    ** as ENDSCRIPT.  We need this when we include a script
		    ** in a function or control structure so that the script
		    ** local variable storage is allocated and deallocated.
		    */

		    if (Compiling || InFunctionDefinition)
		      {
			(yyval.pn) = PTNew(ENDSCRIPT, RV, NULL, NULL);
		      }
		    else
			(yyval.pn) = NULL;
		  }
#line 1745 "y.tab.c"
    break;

  case 25: /* @2: %empty  */
#line 298 "script.y"
                  {
		    Compiling++;
		    BreakAllowed++;
		    (yyval.str) = (char *) MakeScriptInfo();
		  }
#line 1755 "y.tab.c"
    break;

  case 26: /* while_stmnt: WHILE '(' expr ')' @2 statement_list END  */
#line 304 "script.y"
                  {
		    ResultValue	v;

		    v.r_str = (yyvsp[-2].str);
		    (yyval.pn) = PTNew(WHILE, v, (yyvsp[-4].pn), (yyvsp[-1].pn));
		    Compiling--;
		    BreakAllowed--;
		  }
#line 1768 "y.tab.c"
    break;

  case 27: /* @3: %empty  */
#line 315 "script.y"
                    {
		      Compiling++;
		      BreakAllowed++;
		      (yyval.str) = (char *) MakeScriptInfo();
		    }
#line 1778 "y.tab.c"
    break;

  case 28: /* for_stmnt: FOR '(' assign_stmnt ';' expr ';' assign_stmnt ')' @3 statement_list END  */
#line 322 "script.y"
                  {
		    ResultValue	v;
		    ParseNode	*forbody, *whilepart;

		    v.r_str = (char *) MakeScriptInfo();
		    forbody = PTNew(SL, v, (yyvsp[-1].pn), (yyvsp[-4].pn));
		    v.r_str = (yyvsp[-2].str);
		    whilepart = PTNew(FOR, v, (yyvsp[-6].pn), forbody);
		    (yyval.pn) = PTNew(SL, v, (yyvsp[-8].pn), whilepart);
		    Compiling--;
		    BreakAllowed--;
		  }
#line 1795 "y.tab.c"
    break;

  case 29: /* $@4: %empty  */
#line 337 "script.y"
                    {
			BEGIN FUNCLIT;
			Compiling++;
			BreakAllowed++;
		    }
#line 1805 "y.tab.c"
    break;

  case 30: /* $@5: %empty  */
#line 343 "script.y"
                    {
			BEGIN 0;
		    }
#line 1813 "y.tab.c"
    break;

  case 31: /* foreach_stmnt: FOREACH VARREF '(' $@4 optwslist arg_list optwslist $@5 ')' statement_list END  */
#line 347 "script.y"
                  {
		    Result	*rp;
		    ResultValue	v;

		    rp = (Result *) (yyvsp[-9].str);
		    v.r_str = (char *) rp;
		    (yyval.pn) = PTNew(FOREACH, v, (yyvsp[-5].pn), (yyvsp[-1].pn));
		    Compiling--;
		    BreakAllowed--;
		  }
#line 1828 "y.tab.c"
    break;

  case 32: /* @6: %empty  */
#line 360 "script.y"
                  {
		    Compiling++;
		    (yyval.str) = (char *) MakeScriptInfo();
		  }
#line 1837 "y.tab.c"
    break;

  case 33: /* if_stmnt: IF '(' expr ')' @6 statement_list else_clause END  */
#line 365 "script.y"
                  {
		    ResultValue	v;
		    ParseNode	*stmntlists;

		    stmntlists = PTNew(0, v, (yyvsp[-2].pn), (yyvsp[-1].pn));
		    v.r_str = (yyvsp[-3].str);
		    (yyval.pn) = PTNew(IF, v, (yyvsp[-5].pn), stmntlists);
		    Compiling--;
		  }
#line 1851 "y.tab.c"
    break;

  case 34: /* else_clause: %empty  */
#line 377 "script.y"
                  {
 		    (yyval.pn) = NULL;
 		  }
#line 1859 "y.tab.c"
    break;

  case 35: /* else_clause: ELSE statement_list  */
#line 381 "script.y"
                  { (yyval.pn) = (yyvsp[0].pn); }
#line 1865 "y.tab.c"
    break;

  case 36: /* @7: %empty  */
#line 383 "script.y"
                  {
		    Compiling++;
		    (yyval.str) = (char *) MakeScriptInfo();
		  }
#line 1874 "y.tab.c"
    break;

  case 37: /* else_clause: ELIF '(' expr ')' @7 statement_list else_clause  */
#line 388 "script.y"
                  {
		    ResultValue	v;
		    ParseNode	*stmntlists;

		    stmntlists = PTNew(0, v, (yyvsp[-1].pn), (yyvsp[0].pn));
		    v.r_str = (yyvsp[-2].str);
		    (yyval.pn) = PTNew(IF, v, (yyvsp[-4].pn), stmntlists);
		    Compiling--;
		  }
#line 1888 "y.tab.c"
    break;

  case 38: /* assign_stmnt: VARREF '=' expr  */
#line 400 "script.y"
                  {
		    ResultValue	v;
		    Result	*rp;

		    (yyval.pn) = NULL;
		    rp = (Result *) (yyvsp[-2].str);
			  {
			    v.r_str = (char *) rp;
		            (yyval.pn) = PTNew('=', v, (yyvsp[0].pn), NULL);
			  }
		  }
#line 1904 "y.tab.c"
    break;

  case 39: /* $@8: %empty  */
#line 414 "script.y"
                  {
		    Pushyybgin(LIT);
		  }
#line 1912 "y.tab.c"
    break;

  case 40: /* include_hdr: INCLUDE $@8 ws  */
#line 418 "script.y"
                  {
		    (yyval.str) = NULL;
		  }
#line 1920 "y.tab.c"
    break;

  case 41: /* include_stmnt: include_hdr LITERAL WHITESPACE arg_list ws  */
#line 424 "script.y"
                  {
		    ResultValue	v;
		    int		argc;
		    char	*argv[100];
		    char	argbuf[1000];

		    Popyybgin();
		    sprintf(argbuf, "%s", (yyvsp[-3].str));
		    argc = 1;
		    argv[0] = argbuf;
		    do_cmd_args((yyvsp[-1].pn), &argc, argv);
		    argv[argc] = NULL;

		    if (!IncludeScript(argc, argv))
		      {
			sprintf(argbuf, "Script '%s' not found", (yyvsp[-3].str));
			FreePTValues((yyvsp[-1].pn));
			PTFree((yyvsp[-1].pn));
			free((yyvsp[-3].str));
			yyerror(argbuf);
		      }

		    if (Compiling || InFunctionDefinition)
		      {
			v.r_str = (yyvsp[-3].str);
			(yyval.pn) = PTNew(INCLUDE, v, (yyvsp[-1].pn), NULL);
		      }
		    else
		      {
			FreePTValues((yyvsp[-1].pn));
			PTFree((yyvsp[-1].pn));
			free((yyvsp[-3].str));
			(yyval.pn) = NULL;
		      }
		  }
#line 1960 "y.tab.c"
    break;

  case 42: /* include_stmnt: include_hdr LITERAL ws  */
#line 460 "script.y"
                  {
		    ResultValue	v;
		    int		argc;
		    char	*argv[100];
		    char	argbuf[1000];

		    Popyybgin();
		    sprintf(argbuf, "%s", (yyvsp[-1].str));
		    argc = 1;
		    argv[0] = argbuf;
		    argv[argc] = NULL;

		    if (!IncludeScript(argc, argv))
		      {
			sprintf(argbuf, "Script '%s' not found", (yyvsp[-1].str));
			free((yyvsp[-1].str));
			yyerror(argbuf);
		      }

		    if (Compiling || InFunctionDefinition)
		      {
			v.r_str = (yyvsp[-1].str);
			(yyval.pn) = PTNew(INCLUDE, v, NULL, NULL);
		      }
		    else
		      {
			free((yyvsp[-1].str));
			(yyval.pn) = NULL;
		      }
		  }
#line 1995 "y.tab.c"
    break;

  case 43: /* opt_node: %empty  */
#line 493 "script.y"
                  {
		    (yyval.pn) = (ParseNode*) NULL;
		  }
#line 2003 "y.tab.c"
    break;

  case 44: /* opt_node: arg_component_list  */
#line 497 "script.y"
                  {
		    (yyval.pn) = (yyvsp[0].pn);
		  }
#line 2011 "y.tab.c"
    break;

  case 45: /* $@9: %empty  */
#line 537 "script.y"
                  {
		    Pushyybgin(LIT);
		  }
#line 2019 "y.tab.c"
    break;

  case 46: /* cmd_name: IDENT $@9 opt_node  */
#line 541 "script.y"
                  {
		    ResultValue	v;

		    v.r_str = (yyvsp[-2].str);
		    if ((yyvsp[0].pn) == NULL)
			(yyval.pn) = PTNew(COMMAND, v, NULL, NULL);
		    else
			(yyval.pn) = PTNew(FUNCTION, v, NULL, (yyvsp[0].pn));
		  }
#line 2033 "y.tab.c"
    break;

  case 47: /* $@10: %empty  */
#line 551 "script.y"
                  {
		    Pushyybgin(LIT);
		  }
#line 2041 "y.tab.c"
    break;

  case 48: /* cmd_name: VARREF $@10 arg_component_list  */
#line 555 "script.y"
                  {
		    ResultValue	v;
		    char*	varname;

		    varname = NULL;
		    if (LocalSymbols != NULL)
			varname = SymtabKey(LocalSymbols, (yyvsp[-2].str));
		    if (varname == NULL)
			varname = SymtabKey(&GlobalSymbols, (yyvsp[-2].str));
		    v.r_str = (char*) strsave(varname);

		    (yyval.pn) = PTNew(FUNCTION, v, NULL, (yyvsp[0].pn));
		  }
#line 2059 "y.tab.c"
    break;

  case 49: /* $@11: %empty  */
#line 582 "script.y"
                  {
		    BEGIN LIT;
		  }
#line 2067 "y.tab.c"
    break;

  case 50: /* cmd_stmnt: cmd_name $@11 opt_arg_list ws  */
#line 586 "script.y"
                  {
		    int		argc;
		    char	*argv[100];
		    char	argbuf[1000];

		    (yyval.pn) = (yyvsp[-3].pn);
		    (yyvsp[-3].pn)->pn_left = (yyvsp[-1].pn);
		    Popyybgin();
		    if ((yyvsp[-3].pn)->pn_val.r_type != EXPRCALL && (yyvsp[-3].pn)->pn_right == NULL &&
				!IsCommand((yyvsp[-3].pn)->pn_val.r.r_str))
		      {
			if (IsInclude((yyvsp[-3].pn)->pn_val.r.r_str))
			  {
			    sprintf(argbuf, "%s", (yyvsp[-3].pn)->pn_val.r.r_str);
			    argc = 1;
			    argv[0] = argbuf;
			    do_cmd_args((yyvsp[-1].pn), &argc, argv);
			    argv[argc] = NULL;
			    IncludeScript(argc, argv);

			    if (Compiling || InFunctionDefinition)
			      {
				(yyvsp[-3].pn)->pn_val.r_type = INCLUDE;
			      }
			    else
			      {
				FreePTValues((yyvsp[-3].pn));
				PTFree((yyvsp[-3].pn));
				(yyval.pn) = NULL;
			      }
			  }
		      }
		  }
#line 2105 "y.tab.c"
    break;

  case 51: /* funcref: FUNCREF  */
#line 622 "script.y"
                  {
		    Pushyybgin(LIT);
		    (yyval.str) = (yyvsp[0].str);
		  }
#line 2114 "y.tab.c"
    break;

  case 52: /* $@12: %empty  */
#line 629 "script.y"
                  {
		    BEGIN LIT;
		  }
#line 2122 "y.tab.c"
    break;

  case 53: /* func_call: funcref opt_node $@12 opt_arg_list ws  */
#line 633 "script.y"
                  {
		    ResultValue	v;
		    Result	*rp;

		    Popyybgin();
		    rp = (Result *) (yyvsp[-4].str);
		    if ((yyvsp[-3].pn) == NULL)
			(yyval.pn) = PTNew(FUNCTION, rp->r, (yyvsp[-1].pn), NULL);
		    else
		      {
			v.r_str = (char*) strsave(SymtabKey(&GlobalSymbols, rp));
			(yyval.pn) = PTNew(FUNCTION, v, (yyvsp[-1].pn), (yyvsp[-3].pn));
		      }
		  }
#line 2141 "y.tab.c"
    break;

  case 54: /* opt_arg_list: %empty  */
#line 650 "script.y"
                  {
		    (yyval.pn) = NULL;
		  }
#line 2149 "y.tab.c"
    break;

  case 55: /* opt_arg_list: opt_arg_list wslist arg_component_list  */
#line 654 "script.y"
                  {
		    (yyval.pn) = PTNew(ARGLIST, RV, (yyvsp[-2].pn), (yyvsp[0].pn));
		  }
#line 2157 "y.tab.c"
    break;

  case 56: /* arg_list: arg_component_list  */
#line 660 "script.y"
                  {
		    (yyval.pn) = PTNew(ARGLIST, RV, NULL, (yyvsp[0].pn));
		  }
#line 2165 "y.tab.c"
    break;

  case 57: /* arg_list: arg_list wslist arg_component_list  */
#line 664 "script.y"
                  {
		    (yyval.pn) = PTNew(ARGLIST, RV, (yyvsp[-2].pn), (yyvsp[0].pn));
		  }
#line 2173 "y.tab.c"
    break;

  case 64: /* arg_component_list: arg_component  */
#line 682 "script.y"
                          {
			    ResultValue	v;

			    (yyval.pn) = PTNew(ARGUMENT, v, NULL, (yyvsp[0].pn));
			  }
#line 2183 "y.tab.c"
    break;

  case 65: /* arg_component_list: arg_component_list arg_component  */
#line 688 "script.y"
                          {
			    ResultValue	v;

			    (yyval.pn) = PTNew(ARGUMENT, v, (yyvsp[-1].pn), (yyvsp[0].pn));
			  }
#line 2193 "y.tab.c"
    break;

  case 66: /* arg_component: LITERAL  */
#line 696 "script.y"
                  {
		    ResultValue	v;

		    v.r_str = (yyvsp[0].str);
		    (yyval.pn) = PTNew(LITERAL, v, NULL, NULL);
		  }
#line 2204 "y.tab.c"
    break;

  case 67: /* arg_component: STRCONST  */
#line 703 "script.y"
                  {
		    ResultValue	v;

		    v.r_str = (yyvsp[0].str);
		    (yyval.pn) = PTNew(LITERAL, v, NULL, NULL);
		  }
#line 2215 "y.tab.c"
    break;

  case 68: /* arg_component: DOLLARARG  */
#line 710 "script.y"
                  {
		    ResultValue	v;

		    v.r_int = (yyvsp[0].iconst);
		    (yyval.pn) = PTNew(DOLLARARG, v, NULL, NULL);
		  }
#line 2226 "y.tab.c"
    break;

  case 69: /* $@13: %empty  */
#line 717 "script.y"
                  {
		    Pushyybgin(0);
		  }
#line 2234 "y.tab.c"
    break;

  case 70: /* $@14: %empty  */
#line 721 "script.y"
                  {
		    Popyybgin();
		  }
#line 2242 "y.tab.c"
    break;

  case 71: /* arg_component: '{' $@13 ac_func_cmd_expr $@14 '}'  */
#line 725 "script.y"
                  {
		    (yyval.pn) = (yyvsp[-2].pn);
		  }
#line 2250 "y.tab.c"
    break;

  case 72: /* ac_func_cmd_expr: func_call  */
#line 731 "script.y"
                  {
		    (yyval.pn) = (yyvsp[0].pn);
		  }
#line 2258 "y.tab.c"
    break;

  case 73: /* ac_func_cmd_expr: cmd_stmnt  */
#line 735 "script.y"
                  {
		    (yyval.pn) = (yyvsp[0].pn);
		  }
#line 2266 "y.tab.c"
    break;

  case 74: /* ac_func_cmd_expr: expr  */
#line 739 "script.y"
                  {
		    if ((yyvsp[0].pn)->pn_val.r_type == STRCONST)
			(yyvsp[0].pn)->pn_val.r_type = LITERAL;

		    (yyval.pn) = (yyvsp[0].pn);
		  }
#line 2277 "y.tab.c"
    break;

  case 75: /* ext_func: EXTERN IDENT  */
#line 748 "script.y"
                  {
		    ParseNode	*funcpn;
		    ResultValue	v;
		    Result	*rp;

		    rp = SymtabNew(&GlobalSymbols, (yyvsp[0].str));
		    if (rp->r_type != 0 && rp->r_type != FUNCTION)
			fprintf(stderr, "WARNING: function name '%s' is redefining a variable!\n", (yyvsp[0].str));

		    rp->r_type = FUNCTION;

		    v.r_str = (char *) NULL;
		    funcpn = PTNew(SL, v, NULL, NULL);
		    rp->r.r_str = (char *) funcpn;

		    free((yyvsp[0].str));
		    (yyval.pn) = NULL;
		  }
#line 2300 "y.tab.c"
    break;

  case 76: /* ext_func: EXTERN FUNCREF  */
#line 767 "script.y"
                  {
		    (yyval.pn) = NULL;
		  }
#line 2308 "y.tab.c"
    break;

  case 77: /* func_hdr: FUNCTION IDENT  */
#line 773 "script.y"
                  {
		    ParseNode	*funcpn;
		    ResultValue	v;
		    Result	*rp;

		    if (InFunctionDefinition)
		      {
			fprintf(stderr, "Function definition within another function or\n");
			fprintf(stderr, "within a control structure (FUNCTION %s).\n", (yyvsp[0].str));
			yyerror("");
			/* No Return */
		      }

		    InFunctionDefinition++;
		    NextLocal = 0;
		    rp = SymtabNew(&GlobalSymbols, (yyvsp[0].str));
		    if (rp->r_type != 0 && rp->r_type != FUNCTION)
			fprintf(stderr, "WARNING: function name '%s' is redefining a variable!\n", (yyvsp[0].str));

		    rp->r_type = FUNCTION;

		    LocalSymbols = SymtabCreate();
		    v.r_str = (char *) LocalSymbols;
		    funcpn = PTNew(SL, v, NULL, NULL);

		    /*- copy function name as parse node info */

		    funcpn->pcInfo = strsave((yyvsp[0].str));

		    rp->r.r_str = (char *) funcpn;

		    free((yyvsp[0].str));
		    (yyval.pn) = funcpn;
		  }
#line 2347 "y.tab.c"
    break;

  case 78: /* func_hdr: FUNCTION FUNCREF  */
#line 808 "script.y"
                  {
		    ParseNode	*funcpn;
		    Result	*rp;

		    rp = (Result *) (yyvsp[0].str);
		    if (InFunctionDefinition)
		      {
			fprintf(stderr, "Function definition within another function or\n");
			fprintf(stderr, "within a control structure (FUNCTION %s).\n", (yyvsp[0].str));
			yyerror("");
			/* No Return */
		      }

		    /*
		    ** Free old function parse tree and symtab
		    */

		    funcpn = (ParseNode *) rp->r.r_str;
		    if (funcpn->pn_val.r.r_str != NULL)
			SymtabDestroy(funcpn->pn_val.r.r_str);
		    FreePTValues(funcpn->pn_left);
		    PTFree(funcpn->pn_left);
		    FreePTValues(funcpn->pn_right);
		    PTFree(funcpn->pn_right);

		    InFunctionDefinition++;
		    NextLocal = 0;
		    LocalSymbols = SymtabCreate();
		    funcpn->pn_val.r.r_str = (char *) LocalSymbols;

		    /*- copy the function name as parse node info */

		    if (!funcpn->pcInfo)
		    {
			funcpn->pcInfo = strsave(yytext);
		    }
		    else
		    {
			/*! this should not happen */

			int i = 0;
		    }

		    (yyval.pn) = funcpn;
		  }
#line 2397 "y.tab.c"
    break;

  case 79: /* $@15: %empty  */
#line 856 "script.y"
                  {
		    ReturnIdents = 1;
		  }
#line 2405 "y.tab.c"
    break;

  case 80: /* $@16: %empty  */
#line 860 "script.y"
                  {
		    ReturnIdents = 0;
		  }
#line 2413 "y.tab.c"
    break;

  case 81: /* func_def: func_hdr $@15 func_args $@16 statement_list END  */
#line 864 "script.y"
                  {
		    InFunctionDefinition--;

		    (yyvsp[-5].pn)->pn_left = (yyvsp[-3].pn);
		    (yyvsp[-5].pn)->pn_right = (yyvsp[-1].pn);

		    LocalSymbols = NULL;
		    (yyval.pn) = NULL;
		  }
#line 2427 "y.tab.c"
    break;

  case 82: /* func_args: %empty  */
#line 876 "script.y"
                  { (yyval.pn) = NULL; }
#line 2433 "y.tab.c"
    break;

  case 83: /* func_args: '(' func_arg_list ')'  */
#line 878 "script.y"
                  { (yyval.pn) = (yyvsp[-1].pn); }
#line 2439 "y.tab.c"
    break;

  case 84: /* func_arg_list: IDENT  */
#line 882 "script.y"
                  {
		    ResultValue	v;
		    ParseNode	*init;

		    ArgMatch = 1;
		    v.r_int = ArgMatch++;
		    init = PTNew(DOLLARARG, v, NULL, NULL);
		    (yyval.pn) = vardef((yyvsp[0].str), STR, SCAST, init);
		    free((yyvsp[0].str));
		  }
#line 2454 "y.tab.c"
    break;

  case 85: /* func_arg_list: func_arg_list ',' IDENT  */
#line 893 "script.y"
                  {
		    ResultValue	v;
		    ParseNode	*init;

		    v.r_int = ArgMatch++;
		    init = PTNew(DOLLARARG, v, NULL, NULL);
		    v.r_str = (char *) MakeScriptInfo();
		    (yyval.pn) = PTNew(SL, v, (yyvsp[-2].pn), vardef((yyvsp[0].str), STR, SCAST, init));
		    free((yyvsp[0].str));
		  }
#line 2469 "y.tab.c"
    break;

  case 86: /* decl_type: INT  */
#line 906 "script.y"
                  {
		    ReturnIdents = 1;
		    DefType = INT;
		    DefCast = ICAST;
		  }
#line 2479 "y.tab.c"
    break;

  case 87: /* decl_type: FLOAT  */
#line 912 "script.y"
                  {
		    ReturnIdents = 1;
		    DefType = FLOAT;
		    DefCast = FCAST;
		  }
#line 2489 "y.tab.c"
    break;

  case 88: /* decl_type: STR  */
#line 918 "script.y"
                  {
		    ReturnIdents = 1;
		    DefType = STR;
		    DefCast = SCAST;
		  }
#line 2499 "y.tab.c"
    break;

  case 89: /* decl_stmnt: decl_type decl_list  */
#line 926 "script.y"
                  {
		    (yyval.pn) = (yyvsp[0].pn);
		  }
#line 2507 "y.tab.c"
    break;

  case 91: /* $@17: %empty  */
#line 933 "script.y"
                  {
		    ReturnIdents = 1;
		  }
#line 2515 "y.tab.c"
    break;

  case 92: /* decl_list: decl_list ',' $@17 decl_ident  */
#line 937 "script.y"
                  {
		    ResultValue	v;

		    v.r_str = (char *) MakeScriptInfo();
		    (yyval.pn) = PTNew(SL, v, (yyvsp[-3].pn), (yyvsp[0].pn));
		  }
#line 2526 "y.tab.c"
    break;

  case 93: /* $@18: %empty  */
#line 946 "script.y"
                  {
		    ReturnIdents = 0;
		  }
#line 2534 "y.tab.c"
    break;

  case 94: /* decl_ident: IDENT $@18 init  */
#line 950 "script.y"
                  {
		    (yyval.pn) = vardef((yyvsp[-2].str), DefType, DefCast, (yyvsp[0].pn));
		    free((yyvsp[-2].str));
		  }
#line 2543 "y.tab.c"
    break;

  case 95: /* init: %empty  */
#line 957 "script.y"
                  { (yyval.pn) = NULL; }
#line 2549 "y.tab.c"
    break;

  case 96: /* init: '=' expr  */
#line 959 "script.y"
                  { (yyval.pn) = (yyvsp[0].pn); }
#line 2555 "y.tab.c"
    break;

  case 97: /* break_stmnt: BREAK  */
#line 963 "script.y"
                  {
		    ResultValue	v;

		    if (BreakAllowed)
			(yyval.pn) = PTNew(BREAK, v, NULL, NULL);
		    else
			yyerror("BREAK found outside of a loop");
			/* No Return */
		  }
#line 2569 "y.tab.c"
    break;

  case 98: /* return_stmnt: RETURN expr  */
#line 975 "script.y"
                  {
		    ResultValue	v;

		    (yyval.pn) = PTNew(RETURN, v, (yyvsp[0].pn), NULL);
		  }
#line 2579 "y.tab.c"
    break;

  case 99: /* return_stmnt: RETURN  */
#line 981 "script.y"
                  {
		    ResultValue	v;

		    (yyval.pn) = PTNew(RETURN, v, NULL, NULL);
		  }
#line 2589 "y.tab.c"
    break;

  case 100: /* null_stmnt: %empty  */
#line 989 "script.y"
                  { (yyval.pn) = NULL; }
#line 2595 "y.tab.c"
    break;

  case 101: /* expr: expr '|' expr  */
#line 993 "script.y"
                  { (yyval.pn) = PTNew('|', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2601 "y.tab.c"
    break;

  case 102: /* expr: expr '&' expr  */
#line 995 "script.y"
                  { (yyval.pn) = PTNew('&', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2607 "y.tab.c"
    break;

  case 103: /* expr: expr '^' expr  */
#line 997 "script.y"
                  { (yyval.pn) = PTNew('^', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2613 "y.tab.c"
    break;

  case 104: /* expr: '~' expr  */
#line 999 "script.y"
                  { (yyval.pn) = PTNew('~', RV, (yyvsp[0].pn), NULL); }
#line 2619 "y.tab.c"
    break;

  case 105: /* expr: expr '@' expr  */
#line 1002 "script.y"
                  { (yyval.pn) = PTNew('@', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2625 "y.tab.c"
    break;

  case 106: /* expr: expr '+' expr  */
#line 1005 "script.y"
                  { (yyval.pn) = PTNew('+', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2631 "y.tab.c"
    break;

  case 107: /* expr: expr '-' expr  */
#line 1007 "script.y"
                  { (yyval.pn) = PTNew('-', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2637 "y.tab.c"
    break;

  case 108: /* expr: expr '*' expr  */
#line 1009 "script.y"
                  { (yyval.pn) = PTNew('*', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2643 "y.tab.c"
    break;

  case 109: /* expr: expr '/' expr  */
#line 1011 "script.y"
                  { (yyval.pn) = PTNew('/', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2649 "y.tab.c"
    break;

  case 110: /* expr: expr '%' expr  */
#line 1013 "script.y"
                  { (yyval.pn) = PTNew('%', RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2655 "y.tab.c"
    break;

  case 111: /* expr: expr POW expr  */
#line 1015 "script.y"
                  { (yyval.pn) = PTNew(POW, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2661 "y.tab.c"
    break;

  case 112: /* expr: '-' expr  */
#line 1017 "script.y"
                  { (yyval.pn) = PTNew(UMINUS, RV, (yyvsp[0].pn), NULL); }
#line 2667 "y.tab.c"
    break;

  case 113: /* expr: expr OR expr  */
#line 1020 "script.y"
                  { (yyval.pn) = PTNew(OR, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2673 "y.tab.c"
    break;

  case 114: /* expr: expr AND expr  */
#line 1022 "script.y"
                  { (yyval.pn) = PTNew(AND, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2679 "y.tab.c"
    break;

  case 115: /* expr: '!' expr  */
#line 1024 "script.y"
                  { (yyval.pn) = PTNew('!', RV, (yyvsp[0].pn), NULL); }
#line 2685 "y.tab.c"
    break;

  case 116: /* expr: expr LT expr  */
#line 1027 "script.y"
                  { (yyval.pn) = PTNew(LT, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2691 "y.tab.c"
    break;

  case 117: /* expr: expr LE expr  */
#line 1029 "script.y"
                  { (yyval.pn) = PTNew(LE, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2697 "y.tab.c"
    break;

  case 118: /* expr: expr GT expr  */
#line 1031 "script.y"
                  { (yyval.pn) = PTNew(GT, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2703 "y.tab.c"
    break;

  case 119: /* expr: expr GE expr  */
#line 1033 "script.y"
                  { (yyval.pn) = PTNew(GE, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2709 "y.tab.c"
    break;

  case 120: /* expr: expr EQ expr  */
#line 1035 "script.y"
                  { (yyval.pn) = PTNew(EQ, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2715 "y.tab.c"
    break;

  case 121: /* expr: expr NE expr  */
#line 1037 "script.y"
                  { (yyval.pn) = PTNew(NE, RV, (yyvsp[-2].pn), (yyvsp[0].pn)); }
#line 2721 "y.tab.c"
    break;

  case 122: /* expr: VARREF  */
#line 1040 "script.y"
                  { 
		    Result	*rp;
		    ResultValue	v;

		    /*
		    ** Variable reference
		    */

		    rp = (Result *) (yyvsp[0].str);
		      {
			if (rp->r_type == FUNCTION || rp->r_type == LOCREF)
			    v = rp->r;
			else /* Global Variable */
			    v.r_str = (char *) rp;

		        (yyval.pn) = PTNew(rp->r_type, v, NULL, NULL);
		      }
 		  }
#line 2744 "y.tab.c"
    break;

  case 123: /* expr: FLOATCONST  */
#line 1060 "script.y"
                  { 
		    ResultValue	v;

		    v.r_float = (yyvsp[0].fconst);
		    (yyval.pn) = PTNew(FLOATCONST, v, NULL, NULL);
 		  }
#line 2755 "y.tab.c"
    break;

  case 124: /* expr: INTCONST  */
#line 1067 "script.y"
                  { 
		    ResultValue	v;

		    v.r_int = (yyvsp[0].iconst);
		    (yyval.pn) = PTNew(INTCONST, v, NULL, NULL);
 		  }
#line 2766 "y.tab.c"
    break;

  case 125: /* expr: STRCONST  */
#line 1074 "script.y"
                  { 
		    ResultValue	v;

		    v.r_str = (yyvsp[0].str);
		    (yyval.pn) = PTNew(STRCONST, v, NULL, NULL);
 		  }
#line 2777 "y.tab.c"
    break;

  case 126: /* expr: DOLLARARG  */
#line 1082 "script.y"
                  {
		    ResultValue	v;

		    v.r_int = (yyvsp[0].iconst);
		    (yyval.pn) = PTNew(DOLLARARG, v, NULL, NULL);
		  }
#line 2788 "y.tab.c"
    break;

  case 127: /* expr: '{' expr '}'  */
#line 1090 "script.y"
                  { (yyval.pn) = (yyvsp[-1].pn); }
#line 2794 "y.tab.c"
    break;

  case 128: /* expr: '{' cmd_stmnt '}'  */
#line 1094 "script.y"
                  { (yyval.pn) = (yyvsp[-1].pn); }
#line 2800 "y.tab.c"
    break;

  case 129: /* expr: '{' func_call '}'  */
#line 1098 "script.y"
                  { (yyval.pn) = (yyvsp[-1].pn); }
#line 2806 "y.tab.c"
    break;

  case 130: /* expr: '(' expr ')'  */
#line 1102 "script.y"
                  { (yyval.pn) = (yyvsp[-1].pn); }
#line 2812 "y.tab.c"
    break;


#line 2816 "y.tab.c"

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

#line 1105 "script.y"


#if defined(decalpha) && !defined(bison) && !defined(T3E)
/*
** Start of lexical analyzer.  LEX source is in "script.l".
*/

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
ParseNode	*init;

{	/* vardef --- Define a variable */

	ParseNode	*pn;
	Result		*rp;
	ResultValue	v, slv;

	if (InFunctionDefinition && LocalSymbols != NULL)
	  {
	    rp = SymtabNew(LocalSymbols, ident);
	    if (rp->r_type == 0)
	      {
	        rp->r_type = LOCREF;
		rp->r.r_loc.l_type = type;
		rp->r.r_loc.l_offs = NextLocal++;
	      }

	    v.r_str = (char *) rp;
	    pn = PTNew(castop, v, NULL, NULL);
	    if (init)
	      {
		slv.r_str = (char *) MakeScriptInfo();
		pn = PTNew(SL, slv, pn, PTNew('=', v, init, NULL));
	      }
	  }
	else
	  {
	    rp = SymtabNew(&GlobalSymbols, ident);
	    switch(type)
	      {

	      case INT:
	        if (rp->r_type == 0)
	            rp->r.r_int = 0;
	        else
		    CastToInt(rp);
	        break;

	      case FLOAT:
	        if (rp->r_type == 0)
	            rp->r.r_float = 0.0;
	        else
		    CastToFloat(rp);
	        break;

	      case STR:
	        if (rp->r_type == 0)
	            rp->r.r_str = (char *) strsave("");
	        else
		    CastToStr(rp);
	        break;

	      }

	    rp->r_type = type;
	    v.r_str = (char *) rp;
	    if (init)
	        pn = PTNew('=', v, init, NULL);
	    else
	        pn = NULL;
	  }

	return(pn);

}	/* vardef */


void ParseInit()

{    /* ParseInit --- Initialize parser variables */

        InFunctionDefinition = 0;
	Compiling = 0;
	BreakAllowed = 0;
	LocalSymbols = NULL;
	nextchar(1);	/* Flush lexer input */
	PTInit();	/* Reinit parse tree evaluation */

}    /* ParseInit */


int NestedLevel()

{    /* NestedLevel --- Return TRUE if in func_def or control structure */

        return(InFunctionDefinition || Compiling);

}    /* NestedLevel */
