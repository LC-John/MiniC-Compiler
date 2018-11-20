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
    VAR = 259,
    END = 260,
    IF = 261,
    GOTO = 262,
    PARAM = 263,
    CALL = 264,
    RETURN = 265,
    NUM = 266,
    ID_TMP = 267,
    ID_PARAM = 268,
    ID_NATIVE = 269,
    ID_LABEL = 270,
    ID_FUNC = 271,
    ASSIGN = 272,
    OP_BI_LOGIC = 273,
    OP_BI_ARITH = 274,
    OP_UNI = 275,
    ARR_L = 276,
    ARR_R = 277,
    COLON = 278
  };
#endif
/* Tokens.  */
#define EOL 258
#define VAR 259
#define END 260
#define IF 261
#define GOTO 262
#define PARAM 263
#define CALL 264
#define RETURN 265
#define NUM 266
#define ID_TMP 267
#define ID_PARAM 268
#define ID_NATIVE 269
#define ID_LABEL 270
#define ID_FUNC 271
#define ASSIGN 272
#define OP_BI_LOGIC 273
#define OP_BI_ARITH 274
#define OP_UNI 275
#define ARR_L 276
#define ARR_R 277
#define COLON 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "eeyore.y" /* yacc.c:1909  */

	int val;
	char* str;
	struct TreeNode* node;

#line 106 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
