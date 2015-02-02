        #ifndef _STACKLI_H
        #define _STACKLI_H

        #include "dsexceptions.h"
        #include <iostream>       // For NULL
        using namespace std;

        // StackLi class -- linked list implementation
        //
        // CONSTRUCTION: with no parameters
        //
        // ******************PUBLIC OPERATIONS*********************
        // void push( x )         --> Insert x
        // void pop( )            --> Remove most recently inserted item
        // Object top( )          --> Return most recently inserted item
        // Object topAndPop( )    --> Return and remove most recently inserted item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Overflow and Underflow thrown as needed

        template <class Object>
        class StackLi
        {
          public:
            StackLi( );
            StackLi( const StackLi & rhs );
            ~StackLi( );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Object & top( ) const;

            void makeEmpty( );
            void pop( );
            void push( const Object & x );
            Object topAndPop( );

            const StackLi & operator=( const StackLi & rhs );

          private:
            struct ListNode
            {
                Object   element;
                ListNode *next;

                ListNode( const Object & theElement, ListNode * n = NULL )
                  : element( theElement ), next( n ) { }
            };

            ListNode *topOfStack;
        };

        #include "StackLi.cpp"
        #endif

