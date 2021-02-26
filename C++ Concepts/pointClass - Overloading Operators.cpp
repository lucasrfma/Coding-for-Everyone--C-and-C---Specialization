#include <iostream>

using namespace std;

class point{
	
	public:
	
		point(double x = 0.0, double y = 0.0):x(x),y(y){}

		point(int x, int y = 0.0):x((double)x), y((double)y){}

		// point(point p){
		// 	x = p.getx();
		// 	y = p.gety();
		// }
		
		double getx(){
			return x;
		}
	
		double gety(){
			return y;
		}
		
		void setx(double v){
			x = v;
		}
		
		void sety(double v){
			y = v;
		}
		
		// friend ostream& operator<<(ostream& out, const point& p);
		
		friend ostream& operator<<(ostream& out,const point& p ){
			out << "( " << p.x << ", " << p.y << " )";
			return out;
		}
		
		friend point operator+(const point& p, const point& q){
			return point(p.x+q.x,p.y+q.y);
		} 
		
	private:
	
		double x,y;
	
};

int main(){

	point a(3.5,2.5), b;
	// a.setx(3.5);a.sety(2.5);
	b.setx(2.5);b.sety(4.5);
	
	std::cout << "a = " << a << " and b = " << b << std::endl;
	std::cout << "a + b = " << a + b << std::endl << std::endl << std::endl;


	int i = 1, j = 2;
	point c,d(i),e(i,j),f(2.9);

	std::cout << c << d << e << f << std::endl;

	return 0;
}