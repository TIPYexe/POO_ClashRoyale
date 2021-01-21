#ifndef CONSOLEAPPLICATION1_ELIXIR_H
#define CONSOLEAPPLICATION1_ELIXIR_H

#include <thread>
#include "Harta.h"

class Elixir {
private:
    float elixir{};

public:

    Elixir();

    void automat();

    float getElixir() const;

    virtual void printElixir() const;

    virtual ~Elixir();

    Elixir &operator=(const Elixir &elixir);

    Elixir(const Elixir &elixir);

    void spendElixir(float cost);
};


#endif //CONSOLEAPPLICATION1_ELIXIR_H
