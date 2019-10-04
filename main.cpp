#include <iostream>
#include <cstdlib>
#include <string_view>
#include <array>
#include <queue>
#include <set>
#include <cmath>
#include <chrono>
#include <algorithm>

using tipo = std::array<char, 9>;

tipo sol = {0,1,2,3,4,5,6,7,8};
//std::vector<short> passos;

class board;

std::priority_queue<board> open;
std::set<tipo> closed;


class board {
public:
    tipo ordem;
    int valor_g;
    int valor_h;
    int valor_f;
    
    board(tipo board_in, int g=0): ordem(board_in), valor_g(g)
    {
        valor_h = calcManhattan();
        updateF();
    }
    
    bool operator< (const board & b)const
    {
        if(this->valor_f == b.valor_f)
        {
            if(this->valor_h == b.valor_h) return false;
            return this->valor_h > b.valor_h;
        }
        else
        {
            return this->valor_f > b.valor_f;
        }
    }

    void updateF()
    {
        this->valor_f = this->valor_g + this->valor_h;
    }
    
    int calcManhattan()
    {
        int dist = 0;
        int num = 0;
        
        for(int i = 0; i < 3 ; i++)
            for(int j = 0; j < 3; j++)
            {
                num = this->ordem.at(3*i + 1*j);
                dist += std::abs(num % 3 - i) + std::abs(num / 3 - j);
            }
        return dist;
    }

    
};


bool isObjetivo(board &tentativa)
{
    for(char i=0; i<9; i++) if( tentativa.ordem.at(i) != sol.at(i) ) return false;
    return true;
}

void in_closed_or_open(tipo novo_board, int valor_g){
    //std::cout << "Em in_closed_or_open\n";
    int child_valor_g = valor_g + 1;

    //confere_se_em_closed
    if (auto search = closed.find(novo_board); search != closed.end()) {
        std::cout << "Found in closed" << '\n';

    } else {
        //std::cout << "Not found\n";
        auto* new_board_ptr = new board(novo_board, child_valor_g);
        //std::cout << "Not found Error\n";
        open.push(*new_board_ptr);
    }
}
    
void expande(board &pai){

    int pos_0 = 0;
    int i,j; // para verificar em qual linha e em qual coluna está o 0
    
    {
        tipo::iterator it;
        it = std::find (pai.ordem.begin(), pai.ordem.end(), 0); 
        if (it != pai.ordem.end()) 
        { 
            //std::cout << "Element " << 0 <<" found at position : \n" ; 
            pos_0 = it - pai.ordem.begin(); 
        }
        else std::cout << "Ha um erro de acesso a array na linha\n";
    }
    
    i = pos_0 / 3; // linha atual do 0
    j = pos_0 % 3; // coluna atual do 0

    std::cout << "0 ta na linha " << i << " e coluna " << j << " \n";
    
    if(i != 0) // 0 não está na linha mais de cima
    {
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 - 3);
        novo_board.at(pos_0 - 3) = 0; //move cima
        
        in_closed_or_open(novo_board, pai.valor_g);
        
    }
    if(i != 2) // 0 não está na linha mais de baixo
    { 
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 + 3);
        novo_board.at(pos_0 + 3) = 0; //move cima
            
        in_closed_or_open(novo_board, pai.valor_g);
    }
    if(j != 0) // 0 não está na coluna mais da esquerda
    {
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 - 1);
        novo_board.at(pos_0 - 1) = 0; //move cima
        
        in_closed_or_open(novo_board, pai.valor_g);
    }
    if(j != 2) // 0 não está na coluna mais da direita
    {
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 + 1);
        novo_board.at(pos_0 + 1) = 0; //move cima
        
        in_closed_or_open(novo_board, pai.valor_g);
        //confere_se_em_closed
        // if (auto search = closed.find(novo_board); search != closed.end()) {
        //     std::cout << "Found " << '\n';
        // } else {
        //     std::cout << "Not found\n";
        //     auto *new_board_ptr = new board(novo_board, child_valor_g);
        //     std::cout << "Not found Error\n";
        //     open.push(*new_board_ptr);
        // }
    }
}

void calc(tipo &inicial)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    open.push(*(new board(inicial)));
    
    while(!open.empty())
    {
        auto h = open.top();
        std::cout << "Tirou um nodo de g = " << h.valor_g << "\n";
        
        if(isObjetivo(h)) {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Resultado: " << h.valor_g << ", " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";

            return;
        }
        else{
            open.pop();
            expande(h);
            std::cout << "Expandiu nodo\n";
            //closed.insert(h.ordem);
        }
    }
}


int main(int argc, char* argv[])
{
    using namespace std::literals;

    std::cout << "Welcome to the app\n";
    
    if(argc == 11){
        if (argv[1] == "-astar"sv || argv[1] == "--help"sv) {
            std::cout << "List of commands:...\n";
            
            tipo bd;            
            for(char i=0; i<9; i++) { 
                bd.at(i) = atoi(argv[i+2]);
            }
            calc(bd);
        }
    }
    else std::cout << "Sorry, we are not yet ready for that\nTry again later\n\n";
    
    return 0;
}
