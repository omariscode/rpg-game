#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

class Personagem {
private:
    std::string nome;
    int nivel;
    int experiencia;
    int vida;
    int ataque;

public:
    Personagem(std::string n) : nome(n), nivel(1), experiencia(0), vida(100), ataque(10) {}

    void ganharExperiencia(int exp) {
        experiencia += exp;
        while (experiencia >= pow(nivel, 2) * 10) {
            experiencia -= pow(nivel, 2) * 10;
            nivel++;
            vida += 20;
            ataque += 5;
            std::cout << "Parabéns! " << nome << " subiu para o nível " << nivel << "!\n";
        }
    }

    void atacar(class Monstro &m);
    void receberDano(int dano) { vida -= dano; }
    bool estaVivo() const { return vida > 0; }
    int getAtaque() const { return ataque; }
    std::string getNome() const { return nome; }
};

class Monstro {
private:
    std::string nome;
    int vida;
    int ataque;

public:
    Monstro(std::string n, int v, int a) : nome(n), vida(v), ataque(a) {}

    void receberDano(int dano) { vida -= dano; }
    bool estaVivo() const { return vida > 0; }
    int getAtaque() const { return ataque; }
    std::string getNome() const { return nome; }
};

void Personagem::atacar(Monstro &m) {
    std::cout << nome << " ataca " << m.getNome() << " causando " << ataque << " de dano!\n";
    m.receberDano(ataque);
}

class Jogo {
private:
    Personagem jogador;
    std::vector<Monstro> monstros;

public:
    Jogo(std::string nomeJogador) : jogador(nomeJogador) {
        monstros.push_back(Monstro("Goblin", 30, 5));
        monstros.push_back(Monstro("Orc", 50, 10));
        monstros.push_back(Monstro("Dragão", 100, 20));
    }

    void iniciar() {
        std::cout << "Bem-vindo ao RPG, " << jogador.getNome() << "!\n";
        while (jogador.estaVivo()) {
            std::cout << "Escolha um monstro para lutar:\n";
            for (size_t i = 0; i < monstros.size(); ++i) {
                std::cout << i + 1 << ". " << monstros[i].getNome() << "\n";
            }
            int escolha;
            std::cin >> escolha;
            if (escolha < 1 || escolha > monstros.size()) {
                std::cout << "Escolha inválida!\n";
                continue;
            }
            Monstro &monstro = monstros[escolha - 1];
            while (jogador.estaVivo() && monstro.estaVivo()) {
                jogador.atacar(monstro);
                if (monstro.estaVivo()) {
                    std::cout << monstro.getNome() << " ataca " << jogador.getNome() << " causando " << monstro.getAtaque() << " de dano!\n";
                    jogador.receberDano(monstro.getAtaque());
                }
            }
            if (jogador.estaVivo()) {
                std::cout << "Você derrotou " << monstro.getNome() << "!\n";
                jogador.ganharExperiencia(10);
            } else {
                std::cout << "Você foi derrotado!\n";
            }
        }
    }
};

int main() {
    std::srand(std::time(0));
    Jogo jogo("Herói");
    jogo.iniciar();
    return 0;
}
