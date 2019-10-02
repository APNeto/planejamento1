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
    
    board(std::array<int,9> board_in): ordem(board_in)
    {
        valor_h = calcManhattan();
        valor_g = 0;
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
                dist += std::abs(num % 3 - i) + std::abs(num / 3 - j)
            }
        return dist;
    }
    
    void expande(std::priority_queue<board> &open){
        valor_child_g = valor_g + 1;
        
    }
}


std::priority_queue<board> open;
std::set<board> closed;

void calc(board &inicial)
{
    long long num_passos;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    board h = open.top();
    if(isGoal(h)) {}
    
    isObjetivo = checkObjetivo();
    
    if(isObjetivo) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Resultado: " << num_passos << ", " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
        
        return;
    }
    else{
        open.pop();
        set.add(h);
        h.expande(open);
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
