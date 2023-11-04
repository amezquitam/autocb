#include "trigonometric.hpp"
#include "recognizer.hpp"


bool is_trigonometric(const char* str)
{
    Table<15> table = {
        // actions
        {
/* 00 */    [] (action_context const& ctx) {
                ctx.replace({"<S'>", "<R>"});
            },
/* 01 */    [] (action_context const& ctx) {
                ctx.replace({"<S'>", "<R>"});
                ctx.advance(ctx.entry_symbol.length());
            },
/* 02 */    [] (action_context const& ctx) {
                ctx.pop();
            },
/* 03 */    [] (action_context const& ctx) {
                ctx.replace({"<R'>", "<M>"});
            },
/* 04 */    [] (action_context const& ctx) {
                ctx.replace({"<R'>", "<M>"});
                ctx.advance(ctx.entry_symbol.length());
            },
/* 05 */    [] (action_context const& ctx) {
                ctx.replace({"<M'>", "<D>"});
            },
/* 06 */    [] (action_context const& ctx) {
                ctx.replace({"<M'>", "<D>"});
                ctx.advance(ctx.entry_symbol.length());
            },
/* 07 */    [] (action_context const& ctx) {
                ctx.replace({"<D'>", "<P>"});
            },
/* 08 */    [] (action_context const& ctx) {
                ctx.replace({"<D'>", "<P>"});
                ctx.advance(ctx.entry_symbol.length());
            },
/* 09 */    [] (action_context const& ctx) {
                ctx.replace({"<P'>", "<I>"});
            },
/* 10 */    [] (action_context const& ctx) {
                ctx.replace({"<P'>", "<I>"});
                ctx.advance(ctx.entry_symbol.length());
            },
/* 11 */    [] (action_context const& ctx) {
                ctx.replace({")", "<S>"});
                ctx.advance(ctx.entry_symbol.length());
            },
/* 12 */    [] (action_context const& ctx) {
                ctx.replace({"<T>"});
            },
/* 13 */    [] (action_context const& ctx) {
                ctx.replace({")", "<I>", "("});
                ctx.advance(ctx.entry_symbol.length());
            },
/* 14 */    [] (action_context const& ctx) {
                ctx.pop();
                ctx.advance(ctx.entry_symbol.length());
            },
        },
        // action table
        {
            { "<S>", {
                { "id", 0 },
                { "tan", 0 },
                { "cos", 0 },
                { "sen", 0 },
            }},
            { "<S'>", {
                { "+", 1 },
                { ")", 2 },
                { "", 2 },
            }},
            { "<R>", {
                { "id", 3 },
                { "tan", 3 },
                { "cos", 3 },
                { "sen", 3 },
            }},
            { "<R'>", {
                { "+", 2 },
                { "-", 4 },
                { "", 2 },
            }},
            { "<M>", {
                { "id", 5 },
                { "tan", 5 },
                { "cos", 5 },
                { "sen", 5 },
            }},
            { "<M'>", {
                { "-", 2 },
                { "*", 6 },
                { "", 2 },
            }},
            { "<D>", {
                { "id", 7 },
                { "tan", 7 },
                { "cos", 7 },
                { "sen", 7 },
            }},
            { "<D'>", {
                { "*", 2 },
                { "/", 8 },
                { "", 2 },
            }},
            { "<P>", {
                { "id", 9 },
                { "tan", 9 },
                { "cos", 9 },
                { "sen", 9 },
            }},
            { "<P'>", {
                { "/", 2 },
                { "^", 10 },
                { "", 2 },
            }},
            { "<I>", {
                { "id", 14 },
                { "tan", 12 },
                { "cos", 12 },
                { "sen", 12 },
                { "(", 11 },
            }},
            { "<T>", {
                { "tan", 13 },
                { "cos", 13 },
                { "sen", 13 },
            }},
        },
        "<S>"
    };

    Recognizer recognizer{ table };
    
    return recognizer.recognize(str);
}