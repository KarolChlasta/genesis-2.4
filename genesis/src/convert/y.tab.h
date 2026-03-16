/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
