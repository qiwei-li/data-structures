        #include "QueueLL.h"
        #include "dsexceptions.h"

        /**
         * Construct the queue.
         */
        template <class Object>
        QueueLL<Object>::QueueLL()
        {
           head = NULL;
           back = NULL;
        }

        /**
         * Test if the QueueLL is logically empty.
         * Return true if empty, false, otherwise.
         */
        template <class Object>
        bool QueueLL<Object>::isEmpty( ) const
        {
            return head == NULL;
        }


        /**
         * Make the QueueLL logically empty.
         */
        template <class Object>
        void QueueLL<Object>::makeEmpty( )
        {
        	if(!isEmpty())
          {
            ListNode<Object> *temp = head;
            while(temp != NULL)
            {
            	head = temp->next;
              delete temp;
              temp = head;
            }
            back = NULL;
          }
        }

        /**
         * Get the least recently inserted item in the QueueLL.
         * Return the least recently inserted item in the QueueLL
         * or throw Underflow if empty.
         */
        template <class Object>
        const Object & QueueLL<Object>::getFront( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return head->element;
        }

        /**
         * Return and remove the least recently inserted item from the QueueLL.
         * Throw Underflow if empty.
         */
        template <class Object>
        Object QueueLL<Object>::dequeue( )
        {
          if( isEmpty( ) )
                throw Underflow( );

          Object frontItem = head->element;
          ListNode<Object> *temp = head->next;
          delete head;
          head = temp;

          return frontItem;
        }

        /**
         * Insert x into the QueueLL.
         */

        template <class Object>
        void QueueLL<Object>::enqueue( const Object & x )
        {
        	if(isEmpty())
          {
          	head = new ListNode<Object>(x);
            back = head;
          }
          else {
          	back->next = new ListNode<Object>(x);
            back = back->next;
          }
        }


