/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EOL = 258,
    ARR_L = 259,
    ARR_R = 260,
    VAR = 261,
    MALLOC = 262,
    IF = 263,
    GOTO = 264,
    CALL = 265,
    STORE = 266,
    LOAD = 267,
    LOADADDR = 268,
    RETURN = 269,
    END = 270,
    COLON = 271,
    ASSIGN = 272,
    OP = 273,
    REG = 274,
    LABEL = 275,
    FUNC = 276,
    INT = 277
  };
#endif
/* Tokens.  */
#define EOL 258
#define ARR_L 259
#define ARR_R 260
#define VAR 261
#define MALLOC 262
#define IF 263
#define GOTO 264
#define CALL 265
#define STORE 266
#define LOAD 267
#define LOADADDR 268
#define RETURN 269
#define END 270
#define COLON 271
#define ASSIGN 272
#define OP 273
#define REG 274
#define LABEL 275
#define FUNC 276
#define INT 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "tigger2riscv.y" /* yacc.c:1909  */

	int val;
	char* str;

#line 103 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
