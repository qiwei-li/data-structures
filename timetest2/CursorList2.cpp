       // include "CursorList2.h"

        /**
         * Routine to initialize the cursorSpace.
         */
        template <class Object>
        void CursorList<Object>::initializeCursorSpace( )
        {
            static int cursorSpaceIsInitialized = false;

            if( !cursorSpaceIsInitialized )
            {
                cursorSpace.resize( 250001 );
                for( int i = 0; i < cursorSpace.size( ); i++ )
                    cursorSpace[ i ].next = i + 1;
                cursorSpace[ cursorSpace.size( ) - 1 ].next = 0;
                cursorSpaceIsInitialized = true;
            }
        }

        /**
         * Allocate a CursorNode.
         */
        template <class Object>
        int CursorList<Object>::alloc( )
        {
            int p = cursorSpace[ 0 ].next;
            cursorSpace[ 0 ].next = cursorSpace[ p ].next;
            return p;
        }

        /**
         * Free a CursorNode.
         */
        template <class Object>
        void CursorList<Object>::free( int p )
        {
            cursorSpace[ p ].next = cursorSpace[ 0 ].next;
            cursorSpace[ 0 ].next = p;
        }


        /**
         * Construct the CursorList.
         */
        template <class Object>
        CursorList<Object>::CursorList(vector<CursorNode <Object> > &cursorspace ) : cursorSpace(cursorspace)
        {
            initializeCursorSpace( );
            header = alloc( );
            cursorSpace[ header ].next = 0;
        }

        /**
         * Copy constructor.
         */
        template <class Object>
        CursorList<Object>::CursorList( const CursorList<Object> & rhs )
        {
            initializeCursorSpace( );
            header = alloc( );
            cursorSpace[ header ].next = 0;
            *this = rhs;
        }

        /**
         * Destroy the CursorList
         */
        template <class Object>
        CursorList<Object>::~CursorList( )
        {
            makeEmpty( );
            free( header );
        }

        /**
         * Test if the CursorList is logically empty.
         * Return true if empty, false, otherwise.
         */
        template <class Object>
        bool CursorList<Object>::isEmpty( ) const
        {
            return cursorSpace[ header ].next == 0;
        }

        /**
         * Make the CursorList logically empty.
         */
        template <class Object>
        void CursorList<Object>::makeEmpty( )
        {
            while( !isEmpty( ) )
                remove( first( ).retrieve( ) );
        }

        /**
         * Return an iterator representing the header node.
         */
        template <class Object>
        CursorListItr<Object> CursorList<Object>::zeroth()  const
        {
            return CursorListItr<Object>( header, cursorSpace );
        }

        /**
         * Return an iterator representing the first node in the CursorList.
         * This operation is valid for empty lists.
         */
        template <class Object>
        CursorListItr<Object> CursorList<Object>::first( ) const
        {
            return CursorListItr<Object>( cursorSpace[ header ].next, cursorSpace);
        }

        /**
         * Insert item x after p.
         */
        template <class Object>
        void CursorList<Object>::insert( const Object & x, const CursorListItr<Object> & p )
        {
            if( p.current != 0 )
            {
                int pos = p.current;
                int tmp = alloc( );

                cursorSpace[ tmp ] = CursorNode<Object>( x, cursorSpace[ pos ].next );
                cursorSpace[ pos ].next = tmp;
            }
        }

        /**
         * Return iterator corresponding to the first node containing an item x.
         * Iterator isPastEnd if item is not found.
         */
        template <class Object>
        CursorListItr<Object> CursorList<Object>::find( const Object & x ) const
        {
/* 1*/      int itr = cursorSpace[ header ].next;

/* 2*/      while( itr != 0 && cursorSpace[ itr ].element != x )
/* 3*/          itr = cursorSpace[ itr ].next;

/* 4*/      return CursorListItr<Object>( itr );
        }

        /**
         * Return iterator prior to the first node containing an item x.
         */
        template <class Object>
        CursorListItr<Object> CursorList<Object>::findPrevious( const Object & x ) const
        {
/* 1*/      int itr = header;

/* 2*/      while( cursorSpace[ itr ].next != 0 &&
                   cursorSpace[ cursorSpace[ itr ].next ].element != x )
/* 3*/          itr = cursorSpace[ itr ].next;

/* 4*/      return CursorListItr<Object>( itr, cursorSpace );
        }

        /**
         * Remove the first occurrence of an item x.
         */
        template <class Object>
        void CursorList<Object>::remove( const Object & x )
        {
            CursorListItr<Object> p = findPrevious( x );
            int pos = p.current;

            if( cursorSpace[ pos ].next != 0 )
            {
                int tmp = cursorSpace[ pos ].next;
                cursorSpace[ pos ].next = cursorSpace[ tmp ].next;
                free ( tmp );
            }
        }


        /**
         * Deep copy of linked lists.
         */
        template <class Object>
        const CursorList<Object> & CursorList<Object>::operator=( const CursorList<Object> & rhs )
        {
            CursorListItr<Object> ritr = rhs.first( );
            CursorListItr<Object> itr = zeroth( );

            if( this != &rhs )
            {
                makeEmpty( );
                for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
                    insert( ritr.retrieve( ), itr );
            }
            return *this;
        }


