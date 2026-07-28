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
