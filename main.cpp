#include <iostream>
#include <cstdlib>
#include <string_view>
#include <array>
#include <queue>
#include <set>
#include <cmath>

std::array<int,9> sol = {0,1,2,3,4,5,6,7,8,9};
//std::vector<short> passos;

class board {
public:
    std::array<int,9> ordem;
    int valor_g;
    int valor_h;
    int valor_f;
    
    board(std::array<int,9> board_in, g=0): ordem(board_in), valor_g(g)
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
            for(int j = 0; j , 3; j++)
            {
                num = this->ordem.at(3*i + 1*j);
                dist += std::abs(num % 3 - i) + std::abs(num / 3 - j);
            }
        return dist;
    }
    
    void expande(std::priority_queue<board> &open){
        int valor_child_g = valor_g + 1;
        int pos_0 = 0;
        int i,j; // para verificar em qual linha e em qual coluna está o 0
        
        {
            std::array<int>::iterator;
            it = std::find (ordem.begin(), ordem.end(), 0); 
            if (it != ordem.end()) 
            { 
                //std::cout << "Element " << 0 <<" found at position : " ; 
                pos_0 = it - ordem.begin(); 
            }
        }
        
        i = pos_0 % 3; // linha atual do 0
        j = pos_0 / 3; // coluna atual do 0
        
        // pos_0 += 1; // move direita
        // pos_0 -= 1; // move esquerda
        // pos_0 -= 3; // move cima
        // pos_0 += 3; // move baixo
        
        if(i != 0) // 0 não está na linha mais de cima
        {
            array<int, 9> novo_board(this->ordem);
            novo_board.at(pos_0) = novo_board.at(pos_0 - 3);
            novo_board.at(pos_0 - 3) = 0; //move cima
            
            //confere_se_em_closed
            if (auto search = closed.find(novo_board); search != example.end()) {
                //std::cout << "Found " << (*search) << '\n';
            } else {
                //std::cout << "Not found\n";
                auto* new_board_ptr = new board(novo_board, child_valor_g);
                open.push(*new_board_ptr);
            }
        }
        if(i != 2) expande_move_baixo(){
            array<int, 9> novo_board(this->ordem);
            novo_board.at(pos_0) = novo_board.at(pos_0 + 3);
            novo_board.at(pos_0 + 3) = 0; //move cima
            
            //confere_se_em_closed
            if (auto search = closed.find(novo_board); search != example.end()) {
                //std::cout << "Found " << (*search) << '\n';
            } else {
                //std::cout << "Not found\n";
                auto* new_board_ptr = new board(novo_board, child_valor_g);
                open.push(*new_board_ptr);
            }
        }
        if(j != 0) expande_move_esquerda(); // 0 não está na coluna mais da esquerda
        {
            array<int, 9> novo_board(this->ordem);
            novo_board.at(pos_0) = novo_board.at(pos_0 - 1);
            novo_board.at(pos_0 - 1) = 0; //move cima
            
            //confere_se_em_closed
            if (auto search = closed.find(novo_board); search != example.end()) {
                //std::cout << "Found " << (*search) << '\n';
            } else {
                //std::cout << "Not found\n";
                auto* new_board_ptr = new board(novo_board, child_valor_g);
                open.push(*new_board_ptr);
            }
        }
        if(j != 2) expande_move_direita();
        {
            array<int, 9> novo_board(this->ordem);
            novo_board.at(pos_0) = novo_board.at(pos_0 - 1);
            novo_board.at(pos_0 - 1) = 0; //move cima
            
            //confere_se_em_closed
            if (auto search = closed.find(novo_board); search != example.end()) {
                //std::cout << "Found " << (*search) << '\n';
            } else {
                //std::cout << "Not found\n";
                auto* new_board_ptr = new board(novo_board, child_valor_g);
                open.push(*new_board_ptr);
            }
        }
    }
}


std::priority_queue<board> open;
std::set<array<int,9>> closed;

bool isObjetivo(board &tentativa)
{
    for(int i=0; i<9; i++) if( tentativa->ordem.at(i) != sol.at(i) ) return false;
    return true;
}

void calc(board &inicial)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    while(!open.empty())
    {
        auto h = open.top();
        
        if(isObjetivo(h)) {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Resultado: " << h.valor_g << ", " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";

            return;
        }
        else{
            open.pop();
            h.expande(open);
            closed.insert(h.ordem);  
        }
    }
}


int main(int argc, char* argv[])
{
    using namespace std::literals;

    std::cout << "Welcome to the app\n";
    
    if(argc == 11){
        if (argv[1] == "-astar"sv || argv[1] == "--help"sv) {
            std::cout << "List of commands:...";
            
            array<int,9> bd;            
            for(int i=0; i<9; i++) { 
                bd.at(i) = atoi(arg[i+2]));
            }
            board inst(bd);
            calc(inst);
        }
    }
    else std::cout << "Sorry, we are not yet ready for that\nTry again later\n\n";
    
    return 0;
}
