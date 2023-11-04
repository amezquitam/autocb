#pragma once 

#include <vector>
#include <stack>
#include <functional>
#include <string>
#include <unordered_map>
#include "util.hpp"


// tipo: string de c
using cstring = const char*;
// tipo: envoltorio de string de c
using vstring = std::string_view;
// tipo: lista de vstring (debe ser definida en tiempo de compilación)
using strlist = std::initializer_list<vstring>;


// tipos: funciones para operar con la pila
using f_push = std::function<void(vstring)>;
using f_pop = std::function<void(void)>;
using f_replace = std::function<void(strlist)>;


// tipo: funcion para operar con la cadena de entrada
using f_advance = std::function<void(int)>;


struct action_context {
    f_pop       pop;
    f_push      push;
    f_replace   replace;
    f_advance   advance;
    vstring     entry_symbol;
    vstring     stack_symbol;
};


// tipo: funcion que representa una accion en la pila
using f_action = std::function<void(action_context)>;
// tipo: double hashmap [simbolo de pila] -> [simbolo de entrada] -> action number
using action_map = std::unordered_map<vstring, std::unordered_map<vstring, int>>;


// tipo template: tabla de acciones del automata
template <int num_actions>
struct Table {
    f_action actions[num_actions];
    action_map action_table;
    vstring initial_symbol;

    struct action_info {
        vstring entry_symbol;
        int action_index;
    };

    /**
     * @param stack_symbol: Simbolo que se encuentra en el topa de la pila
     * @param rem_string: String pendiente por procesar
    **/
    action_info action(vstring stack_symbol, vstring rem_string) const {
        // un iterador que contiene un par con la clave y el 
        // valor correspondiente, el cual es otro mapa
        auto entry_table_it = action_table.find(stack_symbol);
        if (entry_table_it == action_table.end())
            return {"", -1};
        
        // se accede al mapa, el cual es está en la propiedad second
        // ya que en first se encuentra la key
        auto entry_table = entry_table_it->second;
        
        // se crea un substring con el primer caracter de la cadena
        auto entry = rem_string.substr(0, 1);
        // se busca si hay alguna accion asociada
        auto index_it = entry_table.find(entry);
        if (index_it != entry_table.end()) {
            return { entry, index_it->second };
        }

        for (auto [key, action_index]: entry_table) {
            if (rem_string.size() < key.size())
                continue;
            // se recorta el string, para ajustarlo a la key
            auto entry = rem_string.substr(0, key.size());
            if (key == entry) 
                return {entry, action_index};
        }

        return {"", -1};
    }
};


// tipo template: recibe una tabla personalizada
template <int num_actions>
struct Recognizer {
public:
    /**
     * funcion: Pasa la cadena de entrada por un proceso de reconocimiento. 
     * si no hay errores, y la pila queda vacia despues de finalizar la cadena
     * entonces retorna true.
    **/
    bool recognize(std::string str);

    constexpr Recognizer(Table<num_actions> const& table)
        : table{ table } {}

private:
    // Pila 
    std::stack<vstring> stack;
    // tabla de acciones (personalizable)
    const Table<num_actions> &table;
};


// Guia de deduccion, deduce el parametro num_actions dependiendo 
// del argumento del constructor
template <int num_actions>
Recognizer(Table<num_actions> const&) -> Recognizer<num_actions>;


// implementacion de la funcion reconocedora
template<int num_actions>
inline bool Recognizer<num_actions>::recognize(std::string str) {
    // quitar espacios
    str.erase(std::remove_if(str.begin(), str.end(), 
        [] (char c) { return c == ' ' || c == '\t';  }), str.end());

    // vacea la pila
    clean(stack);

    // marca el indice del caracter actual en str
    int marker = 0;

    // Funciones de control, tienen referencias a la pila o el marcador

    auto push = [&] (vstring str) {
        stack.push(str);
    };

    auto pop = [&] {
        stack.pop();
    };
    
    auto replace = [&] (strlist list) {
        stack.pop();
        for (auto str: list) 
            stack.push(str);
    };

    auto advance = [&] (int step) {
        marker += step;
    };

    action_context action_context = {
        pop, push, replace, advance
    };

    stack.push(table.initial_symbol);

    while (!stack.empty()) {
        auto stack_symbol = stack.top();

        // cuando el simbolo de la pila es el mismo que el de la entrada se debe
        // desapilar
        if ( stack_symbol == str.substr(marker, stack_symbol.size()) ) {
            pop();
            advance(stack_symbol.size());
            continue;
        }
        
        // se recorta el string, para pasar solo el string que falta por procesar
        auto [entry_symbol, action_index] = table.action(stack_symbol, str.substr(marker));

        if (action_index != -1) {
            action_context.entry_symbol = entry_symbol;
            action_context.stack_symbol = stack_symbol;
            // se ejecuta la accion que corresponde
            table.actions[action_index](action_context);
        } else {
            return false;
        }
    }

    return stack.empty() && marker == str.size();
}
