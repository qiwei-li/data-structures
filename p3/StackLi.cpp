        #include "StackLi.h"
        #include <iostream>

        using namespace std;

        /**
         * Construct the stack.
         */
        template <class Object>
        StackLi<Object>::StackLi( )
        {
            topOfStack = NULL;
        }

        /**
         * Copy constructor.
         */
        template <class Object>
        StackLi<Object>::StackLi( const StackLi<Object> & rhs )
        {
            topOfStack = NULL;
            *this = rhs;
        }

        /**
         * Destructor.
         */
        template <class Object>
        StackLi<Object>::~StackLi( )
        {
            makeEmpty( );
        }

        /**
         * Test if the stack is logically full.
         * Return false always, in this implementation.
         */
        template <class Object>
        bool StackLi<Object>::isFull( ) const
        {
            return false;
        }

        /**
         * Test if the stack is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Object>
        bool StackLi<Object>::isEmpty( ) const
        {
            return topOfStack == NULL;
        }

        /**
         * Make the stack logically empty.
         */
        template <class Object>
        void StackLi<Object>::makeEmpty( )
        {
            while( !isEmpty( ) )
                pop( );
        }

        /**
         * Get the most recently inserted item in the stack.
         * Return the most recently inserted item in the stack
         * or throw an exception if empty.
         */
        template <class Object>
        const Object & StackLi<Object>::top( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return topOfStack->element;
        }

        /**
         * Remove the most recently inserted item from the stack.
         * Exception Underflow if the stack is empty.
         */
        template <class Object>
        void StackLi<Object>::pop( )
        {
            if( isEmpty( ) )
                throw new Underflow( );

            ListNode *oldTop = topOfStack;
            topOfStack = topOfStack->next;
            delete oldTop;
        }

        /**
         * Return and remove the most recently inserted item
         * from the stack.
         */
        template <class Object>
        Object StackLi<Object>::topAndPop( )
        {
            Object topItem = top( );
            pop( );
            return topItem;
        }

        /**
         * Insert x into the stack.
         */
        template <class Object>
        void StackLi<Object>::push( const Object & x )
        {
            topOfStack = new ListNode( x, topOfStack );
        }

        /**
         * Deep copy.
         */
        template <class Object>
        const StackLi<Object> & StackLi<Object>::
        operator=( const StackLi<Object> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                if( rhs.isEmpty( ) )
                    return *this;

                ListNode *rptr = rhs.topOfStack;
                ListNode *ptr  = new ListNode( rptr->element );
                topOfStack = ptr;

                for( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
                    ptr = ptr->next = new ListNode( rptr->element );
            }
            return *this;
        }
