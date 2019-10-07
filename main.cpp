#include <iostream>
#include <cstdlib>
#include <string_view>
#include <array>
#include <queue>
#include <set>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <vector>

using tipo = std::array<char, 9>;

tipo sol = {0,1,2,3,4,5,6,7,8};
//std::vector<short> passos;

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

class boardGBFS : public board {
public:
    boardGBFS(tipo board_in, int g=0): board(board_in, g)
    {}

    void updateF()
    {
        this->valor_f = this->valor_h;
    }
};


class ComparatorASTAR {
public:
    bool operator()(const board* lhs, const board* rhs)
    {
        if(lhs->valor_f == rhs->valor_f)
        {
            if(lhs->valor_h == rhs->valor_h) return false;
            return lhs->valor_h > rhs->valor_h;
        }
        else
        {
            return lhs->valor_f > rhs->valor_f;
        }
    }
};

//std::priority_queue<board*, std::vector<board*>, Comparator> open;
std::set<tipo> closed;

bool isObjetivo(board &tentativa)
{
    for(char i=0; i<9; i++) if( tentativa.ordem.at(i) != sol.at(i) ) return false;
    return true;
}

template <typename T, typename S>
void in_closed_or_open(tipo novo_board, int valor_g, S &open){
    //std::cout << "Em in_closed_or_open\n";
    int child_valor_g = valor_g + 1;

    //confere_se_em_closed
    if (auto search = closed.find(novo_board); search == closed.end()) {
        open.push(new T(novo_board, child_valor_g));

    } else {
        
    }
}


template <typename T, typename S>
void expande(T &pai, S &open){

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
        //else std::cout << "Ha um erro de acesso a array na linha\n";
    }
    
    i = pos_0 / 3; // linha atual do 0
    j = pos_0 % 3; // coluna atual do 0

    //std::cout << "0 ta na linha " << i << " e coluna " << j << " \n";
    
    if(i != 0) // 0 não está na linha mais de cima
    {
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 - 3);
        novo_board.at(pos_0 - 3) = 0; //move cima
        
        in_closed_or_open<T>(novo_board, pai.valor_g, open);
        
    }
    if(i != 2) // 0 não está na linha mais de baixo
    { 
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 + 3);
        novo_board.at(pos_0 + 3) = 0; //move cima
            
        in_closed_or_open<T>(novo_board, pai.valor_g, open);
    }
    if(j != 0) // 0 não está na coluna mais da esquerda
    {
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 - 1);
        novo_board.at(pos_0 - 1) = 0; //move cima
        
        in_closed_or_open<T>(novo_board, pai.valor_g, open);
    }
    if(j != 2) // 0 não está na coluna mais da direita
    {
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 + 1);
        novo_board.at(pos_0 + 1) = 0; //move cima
        
        in_closed_or_open<T>(novo_board, pai.valor_g, open);
    }
}

template <typename T, typename S>
void calc(tipo &inicial)
{
    T open;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    open.push(new S(inicial));
    
    while(!open.empty())
    {
        S *h = open.top();
        //std::cout << "Tirou um nodo de g = " << h->valor_g << "\n";
        
        if(isObjetivo(*h)) {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Resultado: " << h->valor_g << ", " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
            return;
        }
        else{
            open.pop();
            expande(*h, open);
            std::cout << "Expandiu nodo\n";
            closed.insert(h->ordem);
            delete h;
        }
    }
}


int main(int argc, char* argv[])
{
    using namespace std::literals;

    std::cout << "Welcome to the app\n";
        if (argv[1] == "-astar"sv) {
            int k = 2;
            while(k<argc)
            {
                if(","sv == argv[k]) k++;
                std::cout << "List of commands:...\n";
                tipo bd;            
                for(char i=0; i<9; i++) { 
                    bd.at(i) = atoi(argv[i+k]);
                }
                calc<std::priority_queue<board*, std::vector<board*>, ComparatorASTAR>, board>(bd);
                k+=9;
            }
        }
        else if (argv[1] == "-gbfs"sv) {
            int k = 2;
            while(k<argc)
            {
            std::cout << "List of commands:...\n";
            tipo bd;
            for(char i=0; i<9; i++) { 
                bd.at(i) = atoi(argv[i+2]);
            }
            calc<std::priority_queue<boardGBFS*, std::vector<boardGBFS*>, ComparatorASTAR>, boardGBFS>(bd);
            k+=9;
        }
    else{ std::cout << "Sorry, we are not yet ready for that\n\n";}
    
    return 0;
}
