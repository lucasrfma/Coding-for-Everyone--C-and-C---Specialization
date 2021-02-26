/*

Checking out enum class in c++ and a bit of operator overloading

Lucas Romero da F. M. de Andrade
feb 23 2021

*/

#include <iostream>

enum class Colour{ blue, red, green};

inline std::ostream& operator<<(std::ostream& out, Colour c){
    switch (c)
    {
    case Colour::blue: out << "blue"; break;
    case Colour::red: out << "red"; break;
    case Colour::green: out << "green"; break;
    
    default: break;
    }
    return out;
}

// using an enumerator Class, instead of a normal one, ambiguity is avoided!
// Is TrafficLight we define green as 0, even though it has been defined as 2 in Colour enum class, and there is no problem!
enum class TrafficLight{ green, yellow, red};

inline std::ostream& operator<<(std::ostream& out, TrafficLight c){
    switch (c)
    {
    case TrafficLight::green: out << "green"; break;
    case TrafficLight::yellow: out << "yellow"; break;
    case TrafficLight::red: out << "red"; break;
    
    default: break;
    }
    return out;
}

// when overloading operators, it is important for the result of the effect of the overloaded operation be natural:
// There is no obvious meaning to autoincrement the enum class Colour. But with traffic there is:
// traffic lights always change in the same order, afterall: green then yellow then red, finally back to green.
// so we can make a ++ operator, but a -- wouldn't make much sense in this case!
inline TrafficLight operator++(TrafficLight& light){
// static_cast<int> is needed when adding the enum class to an int, differently to when adding regular enum to int
    return (light = static_cast<TrafficLight>( ( static_cast<int>(light) + 1)%3) );
}

// the int at the end of the argument list is how c++ knows this is variable++. 
// Without it, this would be overloading for ++variable
inline TrafficLight operator++(TrafficLight& light, int){
	TrafficLight temp = light;
	light = static_cast<TrafficLight>( ( static_cast<int>(light) + 1)%3);
    return temp;
}


int main(){

    Colour colour = Colour::green;

    std::cout << "Colour Example:\n" << colour << std::endl;

    TrafficLight light = TrafficLight::green;

    std::cout << "\nTraffic Light Example:\n" << light << " -> " << light++ << " -> " << light << " -> " << ++light << " -> " << 
    light << " -> " << ++light << " -> " << ++light << std::endl;


    return 0;
}