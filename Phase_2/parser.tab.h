/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    STRING = 258,
    LEFT_BRACE = 259,
    RIGHT_BRACE = 260,
    LEFT_BRACKET = 261,
    RIGHT_BRACKET = 262,
    LEFT_PARENTHESIS = 263,
    RIGHT_PARENTHESIS = 264,
    DOUBLE_COLON = 265,
    DOUBLE_DOT = 266,
    COLON = 267,
    DOT = 268,
    COMMA = 269,
    SEMI_COLON = 270,
    IF = 271,
    ELSE = 272,
    WHILE = 273,
    FOR = 274,
    FUNCTION = 275,
    RETURN = 276,
    BREAK = 277,
    CONTINUE = 278,
    AND = 279,
    NOT = 280,
    OR = 281,
    LOCAL = 282,
    TRUE = 283,
    FALSE = 284,
    NIL = 285,
    EQUAL = 286,
    NOT_EQUAL = 287,
    LESS_EQUAL = 288,
    GREATER_EQUAL = 289,
    ASSIGN = 290,
    LESS = 291,
    GREATER = 292,
    PLUS_PLUS = 293,
    PLUS = 294,
    MINUS_MINUS = 295,
    MINUS = 296,
    MULTIPLY = 297,
    DIVISION = 298,
    MOD = 299,
    CONST_INT = 300,
    CONST_REAL = 301,
    ID = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
