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

using innerTipo = char;
using tipo = std::array<innerTipo, 9>;

tipo sol = {0,1,2,3,4,5,6,7,8};
//std::vector<short> passos;

class board {
public:
    static int nodosCriados;
    static int nodosDeletados;
    tipo ordem;
    int valor_g;
    int valor_h;
    int valor_f;
    int id;
    
    board(tipo board_in, int g=0): ordem(board_in), valor_g(g)
    {
        valor_h = calcManhattan();
        updateF();
        nodosCriados++;
        id = nodosCriados;
        std::cout << "Nodo "<< id << " criado!!! com g = "<< valor_g << "e h = " << valor_h << "\n";
        
    }

    ~board()
    {
        nodosDeletados++;
        std::cout << "Nodo "<< id << " deletado!!!\n";

    }
    
    bool operator< (const board & b)const
    {
        std::cout <<"Comparacao ta erra poha!\n";
        if(this->valor_f == b.valor_f)
        {
            
            if(this->valor_h == b.valor_h) return false;
            std::cout << "Coparacao tem que esse h "<<this->valor_h <<" recebendo " << b.valor_h << "\n";
            return this->valor_h < b.valor_h;
        }
        else
        {
            std::cout << "Coparacao tem que esse f "<<this->valor_f <<" recebendo " << b.valor_f << "\n";
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
                num = this->ordem.at(3*i + 1*j); if(!num) continue;
                dist += std::abs(num / 3 - i) + std::abs(num % 3 - j);
            }
        return dist;
    }
};

struct DereferenceCompareNode
{
    bool operator()(const board* lhs, const board* rhs) const
    {
        if(lhs->valor_f == rhs->valor_f)
        {
            
            if(lhs->valor_h == rhs->valor_h) return false;
            std::cout << "Coparacao " << lhs->id <<" tem que h "<<lhs->valor_h <<" recebendo " << rhs->id << " " << rhs->valor_h << "\n";
            return lhs->valor_h > rhs->valor_h;
        }
        else
        {
            std::cout << "Coparacao " << lhs->id <<" tem que f "<<lhs->valor_f <<" recebendo " << rhs->id << " " << rhs->valor_f << "\n";
            return lhs->valor_f > rhs->valor_f;
        }
    }
};

std::priority_queue<board*,std::vector<board*>,DereferenceCompareNode> open;
std::set<tipo> closed;

int board::nodosCriados = 0;
int board::nodosDeletados = 0;

bool isObjetivo(const board &tentativa)
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
        //auto* new_board_ptr = new ;
        open.push(new board(novo_board, child_valor_g));
    }
}
    
void expande(board &pai){

    int pos_0 = 0;
    int i,j; // para verificar em qual linha e em qual coluna está o 0
    
    {
        tipo::iterator it;
        it = std::find (pai.ordem.begin(), pai.ordem.end(), (char)0); 
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
    }
    if(i != 2) // 0 não está na linha mais de baixo
    { 
        tipo novo_board = pai.ordem;
        novo_board.at(pos_0) = novo_board.at(pos_0 + 3);
        novo_board.at(pos_0 + 3) = 0; //move cima
            
        in_closed_or_open(novo_board, pai.valor_g);
    }
}

void calc(tipo &inicial)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    open.push(new board(inicial));
    
    while(!open.empty())
    {
        auto h = open.top();
        std::cout << "Tirou um nodo de g = " << h->valor_g << " com h = " << h->valor_h << "\n";
        
        if(isObjetivo(*h)) {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Resultado: " << h->valor_g << ", " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
            //std::cout << "Numero Criados: " << board::nodosCriados << " contra deletados: " << board::nodosDeletados << "\n";
            // while(!open.empty()) {
            //     std::cout << open.top()->id << ", ";
            //     open.pop();
            // }
            // return;
        }
        else{
            
            open.pop();
            expande(*h);
            //std::cout << "Expandido: " << h.ordem << "\n" ;
            
            std::cout << "Expandiu nodo " << h->id <<"\n";
            closed.insert(h->ordem);
            delete h;
            std::cout << "Ha #nodos closed: " << closed.size() << "\n";
        }
    }
}


int main(int argc, char* argv[])
{
    using namespace std::literals;

    std::cout << "Welcome to the app\n";
    
    if(argc == 11){
        if (argv[1] == "-astar"sv) {
            std::cout << "List of commands:...\n";
            
            tipo bd;            
            for(char i=0; i<9; i++) { 
                bd.at(i) = atoi(argv[i+2]);
            }
            calc(bd);
        }
        else if (argv[1] == "-bfs"sv) {

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
