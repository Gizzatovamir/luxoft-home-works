#include <iostream>
#include <set>
#include <cmath>

struct point{
    int x,y;

	point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

bool operator<(const point& first, const point& second) {
	return (first.x != second.x) ? first.x < second.x : first.y < second.y;
}

int main(){
	point a(1,1);
	std::set<point> set_points;
	set_points.insert(point(0,5));
	set_points.insert(point(-1,10));
	set_points.insert(point(9,4));
	set_points.insert(point(9,4));
	set_points.insert(point(9,4));
	set_points.insert(point(9,4));
	set_points.insert(point(3,-1));
	set_points.insert(point(3,2));
	set_points.insert(a);
	for(const auto &item: set_points)
	        std::cout << "X: " << item.x << " , Y: " << item.y << std::endl;
	return 0;
}
