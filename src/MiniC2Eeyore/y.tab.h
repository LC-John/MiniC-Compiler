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
    MAIN = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    RETURN = 262,
    PRN_R = 263,
    ARR_L = 264,
    ARR_R = 265,
    BRC_R = 266,
    COMMA = 267,
    EOL = 268,
    PRN_L = 269,
    BRC_L = 270,
    NUM = 271,
    ID = 272,
    TYPE = 273,
    OP_7 = 274,
    OP_6 = 275,
    OP_5 = 276,
    OP_4 = 277,
    OP_3 = 278,
    OP_2 = 279,
    OP_1 = 280
  };
#endif
/* Tokens.  */
#define MAIN 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define RETURN 262
#define PRN_R 263
#define ARR_L 264
#define ARR_R 265
#define BRC_R 266
#define COMMA 267
#define EOL 268
#define PRN_L 269
#define BRC_L 270
#define NUM 271
#define ID 272
#define TYPE 273
#define OP_7 274
#define OP_6 275
#define OP_5 276
#define OP_4 277
#define OP_3 278
#define OP_2 279
#define OP_1 280

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "minic.y" /* yacc.c:1909  */

	int value;
	char* name;
	struct TreeNode* node;

#line 110 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
