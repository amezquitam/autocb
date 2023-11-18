#include "trigonometric.hpp"
#include "recognizer.hpp"

#include <iostream>
#include <cmath>

/**

<S> -> <M> <S'>
<S'> -> + <M> <S'>
<S'> -> - <M> <S'>
<S'> -> E

<M> -> <P><M'>
<M'> -> * <P><M'>
<M'> -> / <P><M'>
<M'> -> E

<P> -> <I><P'>
<P'> -> ^ <I><P'>
<P'> -> E

<I> -> -<I'>
<I> -> +<I'>
<I> -> <I'>

<I'> -> (<S>)
<I'> -> <T>

<T> -> tan(<S>)
<T> -> cos(<S>)
<T> -> sen(<S>)
<T> -> <Num>

<Num> -> <Int><Float>
<Float> -> . <Int>
<Float> -> E
<Int> -> [0-9] <Int>
<Int> -> E


*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
*¨          [0-9]     Tan     Cos     Sin     +       -        *       /       ^       (       )      .        ¬
*   <S>      #1       #1      #1      #1      #1      #1      #E1     #E1     #E1     #1      #E1     #E1     #E2
*   <S'>     #3       #3      #3      #3      #2      #2      #3      #3      #3      #3      #3      #E1     #3
*   <M>      #4       #4      #4      #4      #4      #4      #E1     #E1     #E1     #4      #E1     #E1     #E2
*   <M'>     #3       #3      #3      #3      #3      #3      #5      #5      #3      #3      #3      #3     #3
*   <P>      #6       #6      #6      #6      #6      #6      #E1     #E1     #E1     #6      #E1     #E1     #E2
*   <P'>     #3       #3      #3      #3      #3      #3      #3      #3      #7      #3      #3      #3      #3
*   <I>      #8       #8      #8      #8      #9      #9      #E1     #E1     #E1     #8      #E1     #E1     #E2
*   <I'>     #11      #11     #11     #11     #E1     #E1     #E1     #E1     #E1     #10     #E1     #E1     #E1
*   <T>      #12      #13     #13     #13     #E1     #E1     #E1     #E1     #E1     #E1     #E1     #E1     #E1
*   <Num>    #14      #E1     #E1     #E1     #E1     #E1     #E1     #E1     #E1     #E1     #E1     #E1     #E1
*   <Int>    #15      #3      #3      #3      #3      #3      #3      #3      #3      #3      #3      #3      #3
*   <Float>  #3       #3      #3      #3      #3      #3      #3      #3      #3      #3      #3      #15     #3
*
*   #1: Remplace <S'> <M>, retenga
*   #2: Remplace <S'> <M>, avance
*   #3: Desapile, retenga
*   #4: Remplace <M'> <P>, retenga
*   #5: Remplace <M'> <P>, avance
*   #6: Remplace <P'> <I>, retenga
*   #7: Remplace <P'> <I>, avance
*   #8: Remplace <I'>, retenga
*   #9: Remplace <I'>, avance
*   #10: Remplace ) <S>, avance
*   #11: Remplace <T>, retenga
*   #12: Remplace <Num>, retenga
*   #13: Remplace ) <S> (, avance
*   #14: Remplace <Float> <Int>, retenga
*   #15: Remplace <Int>, avance
*
*   #E1: No se esperaba el símbolo {entry}
*   #E2: No se completó la expresión
*   #E3: Se esperaba un operador
*   #E4: Se esperaba el simbolo {stack symbol}
*/

std::pair<bool, double> is_trigonometric(const char* str)
{
    Table<19> table = {
        // actions
        {
        /* 00 */    [](action_context const& ctx) {
                        ctx.replace({"<S'>", "<M>"});
                    },
        /* 01 */    [](action_context const& ctx) {
                        ctx.advance(ctx.entry_symbol.length());
                        ctx.replace({"<S'>", "<M>"});
                    },
        /* 02 */    [](action_context const& ctx) {
                        ctx.pop();
                    },
        /* 03 */    [](action_context const& ctx) {
                        ctx.replace({"<M'>", "<P>"});
                    },
        /* 04 */    [](action_context const& ctx) {
                        ctx.advance(ctx.entry_symbol.length());
                        ctx.replace({"<M'>", "<P>"});
                    },
        /* 05 */    [](action_context const& ctx) {
                        ctx.replace({"<P'>", "<I>"});
                    },
        /* 06 */    [](action_context const& ctx) {
                        ctx.advance(ctx.entry_symbol.length());
                        ctx.replace({"<P'>", "<I>"});
                    },
        /* 07 */    [](action_context const& ctx) {
                        ctx.replace({"<I'>"});
                    },
        /* 08 */    [](action_context const& ctx) {
                        ctx.advance(ctx.entry_symbol.length());
                        ctx.replace({"<I'>"});
                    },
        /* 09 */    [](action_context const& ctx) {
                        ctx.advance(ctx.entry_symbol.length());
                        ctx.replace({")", "<S>"});
                    },
        /* 10 */    [](action_context const& ctx) {
                        ctx.replace({"<T>"});
                    },
        /* 11 */    [](action_context const& ctx) {
                        ctx.replace({"<Num>"});
                    },
        /* 12 */    [](action_context const& ctx) {
                        ctx.advance(ctx.entry_symbol.length());
                        ctx.replace({")", "<S>", "("});
                    },
        /* 13 */    [](action_context const& ctx) {
                        ctx.replace({"<Float>", "<Int>"});
                    },
        /* 14 */    [](action_context const& ctx) {
                        ctx.advance(ctx.entry_symbol.length());
                        ctx.replace({"<Int>"});
                    },
        // Errores
        /* 15 */    [](action_context const& ctx) {
                        std::cout << "Error: No se esperaba el simbolo '" << ctx.entry_symbol << "'\n";
                        ctx.exit();
                    },
        /* 16 */    [](action_context const& ctx) {
                        std::cout << "No se completo la expresion\n";
                        ctx.exit();
                    },
        /* 17 */    [](action_context const& ctx) {
                        std::cout << "Se esperaba un operador\n";
                        ctx.exit();
                    },
        /* 18 */    [](action_context const& ctx) {
                        std::cout << "Se esperaba el simbolo: '" << ctx.stack_symbol << "'\n";
                        ctx.exit();
                    },
                },
        // action table
        {
            { "<S>", {
                { "[0-9]", 0 },
                { "tan", 0 },
                { "cos", 0 },
                { "sen", 0 },
                { "+", 0 },
                { "-", 0 },
                { "(", 0 },
                { "",  16 },
                { "others",  15 },
            }},
            { "<S'>", {
                { "+", 1 },
                { "-", 1 },
                { "others", 2 },
            }},
            { "<M>", {
                { "[0-9]", 3 },
                { "tan", 3 },
                { "cos", 3 },
                { "sen", 3 },
                { "+", 3 },
                { "-", 3 },
                { "(", 3 },
                { "", 16 },
                { "others", 15 },
            }},
            { "<M'>", {
                { "*", 4 },
                { "/", 4 },
                { "others", 2 },
            }},
            { "<P>",     {
                { "[0-9]", 5 },
                { "tan", 5 },
                { "cos", 5 },
                { "sen", 5 },
                { "+", 5 },
                { "-", 5 },
                { "(", 5 },
                { "", 16 },
                { "others", 15 },
            }},
            { "<P'>", {
                { "^", 6 },
                { "others", 2 }
            }},
            { "<I>", {
                { "[0-9]", 7 },
                { "tan", 7 },
                { "cos", 7 },
                { "sen", 7 },
                { "+", 8 },
                { "-", 8 },
                { "(", 7 },
                { "", 16 },
                { "others", 15 },
            }},
            { "<I'>", {
                { "[0-9]", 10 },
                { "sen", 10 },
                { "tan", 10 },
                { "cos", 10 },
                { "(", 9 },
                { "others", 15 },
            }},
            { "<T>", {
                { "[0-9]", 11 },
                { "tan", 12 },
                { "cos", 12 },
                { "sen", 12 },
                { "others", 15 },
            }},
            { "<Num>", {
                { "[0-9]", 13 },
                { "others", 15 },
            }},
            { "<Int>", {
                { "[0-9]", 14 },
                { "others", 2 },
            }},
            { "<Float>", {
                { ".", 14 },
                { "others", 2 },
            }},
            { ")", {
                { "others", 18 },
            }}
        },
        "<S>"
    };

    Recognizer recognizer{ table };

    auto [isTrigonometric, tokenTree] = recognizer.recognize(str);

    if (!isTrigonometric)
        return { isTrigonometric, 0.0 };

    double value = evaluate(tokenTree);

    return { isTrigonometric, value };
}

// ---------- Numbers

std::string EvalInt(TokenTree& tokenTree) {
    if (tokenTree.children.empty()) return "";
    return tokenTree.children.front().value + EvalInt(tokenTree.children.back());
}

std::string EvalFloat(TokenTree& tokenTree) {
    if (tokenTree.children.empty()) return "";
    return EvalInt(tokenTree.children.back());
}

double EvalNumber(TokenTree& tokenTree) {
    double res = std::stod(EvalInt(tokenTree.children.front()) + "." + EvalFloat(tokenTree.children.back()));
    tokenTree.value = std::to_string(res);
    return res;
}

// ---------- Trigonometricas
double EvalT(TokenTree& tokenTree) {
    double res;

    if (tokenTree.children.size() == 1) {
        res = EvalNumber(tokenTree.children.front());
    }
    else {

        tokenTree.children.pop_back();

        if (tokenTree.children.front().value == "sen") {
            res = std::sin(evaluate(tokenTree.children.back()) * M_PI / 180);
        }

        else if (tokenTree.children.front().value == "cos") {
            res = std::cos(evaluate(tokenTree.children.back()) * M_PI / 180);
        }

        else {
            res = std::tan(evaluate(tokenTree.children.back()) * M_PI / 180);
        }
    }

    tokenTree.value = std::to_string(res);
    return res;
}

double EvalIPrime(TokenTree& tree) {
    double res;
    if (tree.children.size() == 1) {
        res = EvalT(tree.children.front());
    }
    else {
        tree.children.pop_back();
        res = evaluate(tree.children.back());
    }
    tree.value = std::to_string(res);
    return res;
}

double EvalI(TokenTree& tree) {
    double res;
    if (tree.children.size() == 1) {
        res = EvalIPrime(tree.children.front());
    }

    else if (tree.children.front().value == "-") {
        res = -EvalIPrime(tree.children.back());
    }

    else {
        res = EvalIPrime(tree.children.back());
    }
    tree.value = std::to_string(res);
    return res;
}

double EvalPPrime(TokenTree& tree) {
    double res;

    if (tree.children.empty())
        res = 1.0;
    else {
        tree.children.pop_front();
        res = EvalI(tree.children.front()) * EvalPPrime(tree.children.back());
    }

    tree.value = std::to_string(res);
    return res;
}

double EvalP(TokenTree& tree) {
    double res;
    res = std::pow(EvalI(tree.children.front()), EvalPPrime(tree.children.back()));
    tree.value = std::to_string(res);
    return res;
}

double EvalMPrime(TokenTree& tree) {
    double res;
    if (tree.children.empty()) res = 1.0;
    else if (tree.children.front().value == "*") {
        tree.children.pop_front();
        res = EvalP(tree.children.front()) * EvalMPrime(tree.children.back());
    }
    else {
        tree.children.pop_front();
        res = 1.0 / EvalP(tree.children.front()) * EvalMPrime(tree.children.back());
    }

    tree.value = std::to_string(res);
    return res;
}

double EvalM(TokenTree& tree) {
    double res;
    res = EvalP(tree.children.front()) * EvalMPrime(tree.children.back());
    tree.value = std::to_string(res);
    return res;
}

double EvalSPrime(TokenTree& tree) {
    double res;
    if (tree.children.empty()) {
        res = 0.0;
    }
    else if (tree.children.front().value == "+") {
        tree.children.pop_front();
        res = EvalM(tree.children.front()) + EvalSPrime(tree.children.back());
    }
    else {
        tree.children.pop_front();
        res = -EvalM(tree.children.front()) + EvalSPrime(tree.children.back());
    }
    tree.value = std::to_string(res);
    return res;
}

double evaluate(TokenTree& tokenTree) {
    double res = EvalM(tokenTree.children.front()) + EvalSPrime(tokenTree.children.back());
    tokenTree.value = std::to_string(res);
    return res;
}
