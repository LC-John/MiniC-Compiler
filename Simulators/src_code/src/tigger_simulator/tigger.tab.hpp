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

#ifndef YY_YY_HOME_LC_DOWNLOADS_MINIC_COMPILER_SIMULATORS_SRC_CODE_SRC_TIGGER_SIMULATOR_TIGGER_TAB_HPP_INCLUDED
# define YY_YY_HOME_LC_DOWNLOADS_MINIC_COMPILER_SIMULATORS_SRC_CODE_SRC_TIGGER_SIMULATOR_TIGGER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 10 "tigger.y" /* yacc.c:1909  */

void yyerror(const char *s);
#define REGNUM 28
extern const char *str_reg[REGNUM];

#line 50 "/home/lc/Downloads/MiniC-Compiler/Simulators/src_code/src/tigger_simulator/tigger.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_CONSTANT = 258,
    GVAR = 259,
    LABEL = 260,
    REGISTER = 261,
    FUNCTION = 262,
    END = 263,
    IF = 264,
    GOTO = 265,
    CALL = 266,
    LOAD = 267,
    STORE = 268,
    MALLOC = 269,
    LOADADDR = 270,
    RETURN = 271,
    GE = 272,
    LE = 273,
    AND = 274,
    OR = 275,
    NE = 276,
    EQ = 277
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "tigger.y" /* yacc.c:1909  */

    char *vstr;
    int vint;

#line 90 "/home/lc/Downloads/MiniC-Compiler/Simulators/src_code/src/tigger_simulator/tigger.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_LC_DOWNLOADS_MINIC_COMPILER_SIMULATORS_SRC_CODE_SRC_TIGGER_SIMULATOR_TIGGER_TAB_HPP_INCLUDED  */
