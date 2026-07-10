#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char *argv[]){

    if(!glfwInit()){
	std::cout << "meow";
    } else {
	std::cout<<"meow2";
    }

}
