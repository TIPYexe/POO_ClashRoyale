#include "Elixir.h"

Elixir::Elixir() : elixir(0) {
}

void Elixir::automat() {
       std::this_thread::sleep_for(std::chrono::seconds(1));
        elixir += 0.35;
        if(elixir > 10)
            elixir = 10;
}

float Elixir::getElixir() const {
    return elixir;
}

void Elixir::spendElixir(float cost) {
    Elixir::elixir -= cost;
}

void Elixir::printElixir() const {
    printf("%.2f -baza\n", elixir);
}

Elixir::~Elixir() {

}

Elixir::Elixir(const Elixir &elixir) {
    *this = elixir;
}

Elixir &Elixir::operator=(const Elixir &elixir) = default;
