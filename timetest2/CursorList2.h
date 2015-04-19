        #ifndef _CursorList_H
        #define _CursorList_H


        #include "vector.h"
        #include "dsexceptions.h"

        // LinkedList class using a cursor implementation
        //
        // CONSTRUCTION: with no initializer
        // Access is via LinkedListItr class
        //
        // ******************PUBLIC OPERATIONS*********************
        // boolean isEmpty( )     --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // CursorListItr zeroth( )      --> Return position to prior to first
        // CursorListItr first( )       --> Return first position
        // void insert( x, p )    --> Insert x after current iterator position p
        // void remove( x )       --> Remove x
        // CursorListItr find( x )      --> Return position that views x
        // CursorListItr findPrevious( x )
        //                        --> Return position prior to x
        // ******************ERRORS********************************
        // No special errors

        template <class Object>
        class CursorListItr;     // Incomplete declaration.

        template <class Object>
        class CursorList;  // forward declaration

        template <class Object>
        class CursorNode
        {
                Object element;
                int    next;
           
                CursorNode( const Object & theElement, int n )
                  : element( theElement ), next( n ) { }
          public:
                CursorNode( ) : next( 0 ) { }
                friend class CursorList<Object>;
                friend class CursorListItr<Object>;
        };


        template <class Object>
        class CursorList
        {
          public:
            CursorList(vector<CursorNode <Object> > &cursorspace );
            CursorList( const CursorList & rhs );
            ~CursorList( );

            bool isEmpty( ) const;
            void makeEmpty( );
            CursorListItr<Object> zeroth( ) const ;
            CursorListItr<Object> first( ) const;
            void insert( const Object & x, const CursorListItr<Object> & p );
            CursorListItr<Object> find( const Object & x ) const;
            CursorListItr<Object> findPrevious( const Object & x ) const;
            void remove( const Object & x );

          public:
            const CursorList & operator=( const CursorList & rhs );

          private:
            int header;

           	vector<CursorNode <Object> > &cursorSpace;

            void initializeCursorSpace( );
            int alloc( );
            void free( int p );

            friend class CursorListItr<Object>;
        };


        // CursorListItr class; maintains "current position"
        //
        // CONSTRUCTION: Package friendly only, with an int
        //
        // ******************PUBLIC OPERATIONS*********************
        // bool isPastEnd( )      --> True if at valid position in CursorList
        // void advance( )        --> Advance (if not already null)
        // Object retrieve        --> Return item in current position

        template <class Object>
        class CursorListItr
        {
          public:
            CursorListItr(const CursorList<Object> &list ) : current( 0 ), cursorSpace(list.cursorSpace) { }
            bool isPastEnd( ) const
              { return current == 0; }
            void advance( )
              { if( !isPastEnd( ) ) current = cursorSpace[ current ].next; }
            const Object & retrieve( ) const
              { if( isPastEnd( ) ) throw BadIterator( );
                return cursorSpace[ current ].element; }

          private:
            int current;       // Current position
            const vector<CursorNode <Object> > &cursorSpace;
            friend class CursorList<Object>;

            CursorListItr( int theNode, const CursorList<Object> &list )
              : current( theNode ), cursorSpace(list.cursorSpace) { }
        };

        #include "CursorList2.cpp"
        #endif
