#include <boost/pool/pool.hpp>
#include <iostream>
#include <random>

struct small_object
{
    int i[8] {0} ;
};

int main()
{
    constexpr std::size_t N = 1024 * 128 ;
    std::cout << N << " * sizeof(small_object) == " << N * sizeof(small_object) << '\n' ;

    {
        boost::pool<> pool(  sizeof(small_object) ) ;

        static small_object* seq[N] ;

        for( auto& p : seq )
        {
            // allocate large number of small_object intances
            // overloading operators new and delete would make this code more elegant.
            p = new ( pool.malloc() ) small_object ;

            // and just to be nasty, allocate another object of a random size
            // which are deliberately leaked; this is just a snippet to prove a point.
            static std::mt19937 rng ;
            static std::uniform_int_distribution<> distr( 4, 64 ) ;
            new char [ distr(rng) ] ;
        }

        std::cout << "memcheck 1: after allocating " << N << " small objects and "
                   << N << " random objects " ;
        std::cin.get() ;

        for( auto& p : seq ) { p->~small_object() ; pool.free(p) ; p = nullptr ; }
   }
    std::cout << "memcheck 2: after deallocating the " << N << " small objects" ;
    std::cin.get() ;
}
