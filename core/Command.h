#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    virtual ~Command() {}
    virtual bool execute() = 0;
    virtual void undo() = 0;
};

#endif
