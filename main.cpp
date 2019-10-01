#include <iostream>
#include <cstdlib>
#include <string_view>
#include <vector>
#include <array>
#include <queue>

std::array<int,9> inst;
std::array<int,9> sol = {0,1,2,3,4,5,6,7,8,9};
std::vector<short> passos;

std::priority_queue<int, std::array<int,9>, stdf::less<int>> open;

bool checkObjetivo();
std::array<int,9> escolhePrimeiroNodo();
void expande();

void calc()
{
    long long num_passos;
    bool isObjetivo;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    nodo = escolhePrimeiroNodo();
    isObjetivo = checkObjetivo();
    if(isObjetivo) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Resultado: " << num_passos << ", " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
        
        return;
    }
    else{
        expande();
    }
    
    
    
    
}
int main(int argc, char* argv[])
{
    using namespace std::literals;

    std::cout << "Welcome to the app. Type -h or --help to learn more\n";
    
    if(argc > 1){
        if (argv[1] == "-bfs"sv || argv[1] == "--help"sv) {
            std::cout << "List of commands:...";
        }
    }
    
    
    
    for(int i=0; i<9; i++) {
        inst[i] = atoi(arg));
        calc(inst);
    }
    
    return 0;
}
