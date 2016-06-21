        #ifndef _QUADRATIC_PROBING_PTR_H_
        #define _QUADRATIC_PROBING_PTR_H_

        #include "vector.h"
        #include "mystring.h"

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings

        template <class HashedObj>
        class QuadraticPtrHashTable
        {
          public:
            explicit QuadraticPtrHashTable( const HashedObj & notFound, int size = 101 );
            QuadraticPtrHashTable( const QuadraticPtrHashTable & rhs )
              : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                array( rhs.array ), currentSize( rhs.currentSize ) { }

            const HashedObj & find( const HashedObj & x ) const;
            ~QuadraticPtrHashTable();
            void makeEmpty( );
            void insert( const HashedObj & x );
            void remove( const HashedObj & x );

            const QuadraticPtrHashTable & operator=( const QuadraticPtrHashTable & rhs );

          private:
            vector<const HashedObj*> array;
            int currentSize;
            const HashedObj ITEM_NOT_FOUND;
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            int findPos( const HashedObj & x ) const;
            int hash( const string & key, int tableSize ) const;
            int hash( int key, int tableSize ) const;
            void rehash( );
        };

        #include "QuadraticProbingPtr.cpp"
        #endif
