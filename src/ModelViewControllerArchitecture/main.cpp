#include <iostream>
#include "../../include/ModelViewControllerArchitecture/SnakeAI.hpp"
#include<torch/torch.h>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

template <typename T>
void print(const T& t)
{
    std::cout<<t<<"\n";
}

//#include"external/third_party/doctest.hpp"
int main(int argc, char** argv)
{
    std::signal(SIGINT,RenderCount::signal_handler);
    // Disable rendering for doctest environment
    bool render = true;  // Force headless mode for testing
    RenSnake::SnakeAI g(render);
    if(!g.init()) return 1;
    std::cout << "Snake AI Training - Controls:\n";
    std::cout << "  Up/Down   : Select parameter\n";
    std::cout << "  Left/Right: Adjust selected parameter\n";
    std::cout << "  R         : Reset all to defaults\n";
    std::cout << "  Space     : Reset exploration (epsilon=1)\n\n";
    std::cout << "Starting training...\n";

    g.train(100000);
}
