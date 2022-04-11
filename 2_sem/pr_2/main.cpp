#include <queue>
#include <future>
#include <iostream>

#include "MoveBase.h"
#include "Service.h"
#include "logging.h"

class MyService : public ServiceSkeleton {
public:
    virtual void onMethod1ResultAvailable(const Method1_In &in, const Method1_Out &out) override {
        std::cout << "Result, way 2: " << out.b << std::endl;
    }
 };

int main() {
    std::cout << "Starting..." << std::endl;

    MyService serviceA;

    std::future<Method1_Out> &resFuture1(serviceA.method1({5}));

    std::cout << "Result A1, way 1: " << resFuture1.get().b << std::endl;

    std::future<Method1_Out> &resFutureA(serviceA.method1({15}, [&](const Method1_In &in, const Method1_Out &out) {
        std::cout << "Result, way 3: " << out.b << std::endl;
    }));
    
    resFutureA.wait();
    return 0;
}
