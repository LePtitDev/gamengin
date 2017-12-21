#ifndef LUA_H
#define LUA_H

#include <string>
#include <vector>

class LuaScript {

public:

    // Lua variable types
    enum VariableType {
        NIL,
        BOOLEAN,
        INTEGER,
        NUMBER,
        STRING,
        TABLE,
        FUNCTION,
        POINTER,
        UNKNOW
    };

    // Lua variable
    struct Variable {
        VariableType type;
        union {
            bool v_boolean;
            int v_integer;
            float v_number;
            void * v_pointer;
        };
        std::string v_string;
    };

private:

    // Lua script state
    void * state;

    // Indicate if destrution need to
    // unallocate state
    bool need_close;

public:

    // Basic constructor
    LuaScript();

    // Reference constructor
    LuaScript(void * state);

    // Destructor
    ~LuaScript();

    // Load a lua source code in the state
    bool load(const char * code);

    // Execute lua script
    bool execute();

    // Return error message
    const char * getError();

    // Get a global variable
    Variable getVariable(const char *name);

    // Get a global variable
    Variable getVariable(int luaID);

    // Push a variable
    void pushVariable(const Variable& var);

    // Create a variable in lua state
    void createVariable(const char * name, const Variable& var);

    // Create a function in lua state
    void createFunction(const char * name, int (*value)(void * state));

    // Call a LUA function
    std::vector<Variable> callFunction(const char * name, Variable * args, int count);

    // Load main game script lib
    void loadLibGame();

    // Load scene script lib
    void loadLibScene();

    // Load script lib
    void loadLibScript();

};

#endif // LUA_H
