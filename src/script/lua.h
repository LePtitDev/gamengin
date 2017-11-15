#ifndef LUA_H
#define LUA_H

#include <string>

class LuaScript {

public:

    // Lua variable types
    enum VariableType {
        NIL,
        BOOLEAN,
        NUMBER,
        STRING,
        TABLE,
        FUNCTION,
        UNKNOW
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

    // Get a variable type
    VariableType getType(const char * name);

    // Get a boolean global variable
    bool getVariable(const char * name, bool& value);

    // Get an integer global variable
    bool getVariable(const char * name, int& value);

    // Get a floatting global variable
    bool getVariable(const char * name, float& value);

    // Get a string global variable
    bool getVariable(const char * name, std::string& value);

    // Create a function in lua state
    void createFunction(const char * name, int (*value)(void * state));

};

#endif // LUA_H
