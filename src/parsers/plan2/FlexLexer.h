// -*-C++-*-
// FlexLexer.h -- define interfaces for lexical analyzer classes generated
// by flex

// SPDX-FileCopyrightText: 1993 The Regents of the University of California. All rights reserved.
// SPDX-FileContributor: This code is derived from software contributed to Berkeley by Kent Williams and Tom Epperly.
//
// SPDX-License-Identifier: BSD-2-Clause

// This file defines FlexLexer, an abstract class which specifies the
// external interface provided to flex C++ lexer objects, and yyFlexLexer,
// which defines a particular lexer class.
//
// If you want to create multiple lexer classes, you use the -P flag
// to rename each yyFlexLexer to some other xxFlexLexer.  You then
// include <FlexLexer.h> in your other sources once per lexer class:
//
//  #undef yyFlexLexer
//  #define yyFlexLexer xxFlexLexer
//  #include <FlexLexer.h>
//
//  #undef yyFlexLexer
//  #define yyFlexLexer zzFlexLexer
//  #include <FlexLexer.h>
//  ...

#ifndef __FLEX_LEXER_H
// Never included before - need to define base class.
#define __FLEX_LEXER_H

#include <iostream>
#ifndef FLEX_STD
#define FLEX_STD std::
#endif

extern "C++" {

struct yy_buffer_state;
typedef int yy_state_type;

class FlexLexer
{
public:
    virtual ~FlexLexer()
    {
    }

    const char *YYText() const
    {
        return yytext;
    }
    int YYLeng() const
    {
        return yyleng;
    }

    virtual void yy_switch_to_buffer(struct yy_buffer_state *new_buffer) = 0;
    virtual struct yy_buffer_state *yy_create_buffer(FLEX_STD istream *s, int size) = 0;
    virtual void yy_delete_buffer(struct yy_buffer_state *b) = 0;
    virtual void yyrestart(FLEX_STD istream *s) = 0;

    virtual int yylex() = 0;

    // Call yylex with new input/output sources.
    int yylex(FLEX_STD istream *new_in, FLEX_STD ostream *new_out = nullptr)
    {
        switch_streams(new_in, new_out);
        return yylex();
    }

    // Switch to new input/output streams.  A nil stream pointer
    // indicates "keep the current one".
    virtual void switch_streams(FLEX_STD istream *new_in = nullptr, FLEX_STD ostream *new_out = nullptr) = 0;

    int lineno() const
    {
        return yylineno;
    }

    int debug() const
    {
        return yy_flex_debug;
    }
    void set_debug(int flag)
    {
        yy_flex_debug = flag;
    }

protected:
    char *yytext;
    int yyleng;
    int yylineno; // only maintained if you use %option yylineno
    int yy_flex_debug; // only has effect with -d or "%option debug"
};
}
#endif // FLEXLEXER_H

#if defined(yyFlexLexer) || !defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
#define yyFlexLexerOnce

extern "C++" {

class yyFlexLexer : public FlexLexer
{
public:
    // arg_yyin and arg_yyout default to the cin and cout, but we
    // only make that assignment when initializing in yylex().
    yyFlexLexer(FLEX_STD istream *arg_yyin = nullptr, FLEX_STD ostream *arg_yyout = nullptr);

    ~yyFlexLexer() override;

    void yy_switch_to_buffer(struct yy_buffer_state *new_buffer) override;
    struct yy_buffer_state *yy_create_buffer(FLEX_STD istream *s, int size) override;
    void yy_delete_buffer(struct yy_buffer_state *b) override;
    void yyrestart(FLEX_STD istream *s) override;

    void yypush_buffer_state(struct yy_buffer_state *new_buffer);
    void yypop_buffer_state();

    int yylex() override;
    void switch_streams(FLEX_STD istream *new_in, FLEX_STD ostream *new_out = nullptr) override;
    virtual int yywrap();

protected:
    virtual int LexerInput(char *buf, int max_size);
    virtual void LexerOutput(const char *buf, int size);
    virtual void LexerError(const char *msg);

    void yyunput(int c, char *buf_ptr);
    int yyinput();

    void yy_load_buffer_state();
    void yy_init_buffer(struct yy_buffer_state *b, FLEX_STD istream *s);
    void yy_flush_buffer(struct yy_buffer_state *b);

    int yy_start_stack_ptr;
    int yy_start_stack_depth;
    int *yy_start_stack;

    void yy_push_state(int new_state);
    void yy_pop_state();
    int yy_top_state();

    yy_state_type yy_get_previous_state();
    yy_state_type yy_try_NUL_trans(yy_state_type current_state);
    int yy_get_next_buffer();

    FLEX_STD istream *yyin; // input source for default LexerInput
    FLEX_STD ostream *yyout; // output sink for default LexerOutput

    // yy_hold_char holds the character lost when yytext is formed.
    char yy_hold_char;

    // Number of characters read into yy_ch_buf.
    int yy_n_chars;

    // Points to the current character in buffer.
    char *yy_c_buf_p;

    int yy_init; // whether we need to initialize
    int yy_start; // start state number

    // Flag which is used to allow yywrap()'s to do buffer switches
    // instead of setting up a fresh yyin. A bit of a hack ...
    int yy_did_buffer_switch_on_eof;

    size_t yy_buffer_stack_top; /*< index of top of stack. */
    size_t yy_buffer_stack_max; /*< capacity of stack. */
    struct yy_buffer_state **yy_buffer_stack; /*< Stack as an array. */
    void yyensure_buffer_stack(void);

    // The following are not always needed, but may be depending
    // on use of certain flex features (like REJECT or yymore()).

    yy_state_type yy_last_accepting_state;
    char *yy_last_accepting_cpos;

    yy_state_type *yy_state_buf;
    yy_state_type *yy_state_ptr;

    char *yy_full_match;
    int *yy_full_state;
    int yy_full_lp;

    int yy_lp;
    int yy_looking_for_trail_begin;

    int yy_more_flag;
    int yy_more_len;
    int yy_more_offset;
    int yy_prev_more_offset;
};
}

#endif // yyFlexLexer || ! yyFlexLexerOnce
