
/**
 * @author whimsycwd
 * @date   2014.9.26
 * 类似Vector
 */
#include <iostream>
#include <cassert>
#include "List.h"

using namespace std;

template <typename T>
class ArrayList : public List<T> {

    private :
        T* array;
        int cnt;
        int capacity;

        int modCnt;  // modification counter

        const static int initialCapacity = 16;

        void arrayCopy(T* dest, T* sou, int num) {
            for (int i = 0; i< num; ++i) {
                dest[i] = sou[i];
            }
        }

        void expandCapacity() {
            capacity = capacity * 2;
            T * newArray = new T[capacity];    
            
            arrayCopy(newArray, array, cnt);

            delete [] array;
            array = newArray;
        }
        void shrinkCapacity() {
            // funny thing happen without this line
            if (capacity <= initialCapacity) {
                return;
            }

            capacity = capacity / 2;
            T * newArray = new T[capacity];
            
            arrayCopy(newArray, array, cnt);

            delete [] array;
            array = newArray;

        }

        void rangeCheck(int index) const {
            assert(index >= 0 && index < cnt);
        }
       
        /**
         * Iterator Implementation
         */

        template <typename E>
        class ArrayIterator : public Iterator<E> {
            private :
                int itCnt;
                int itModCnt;

                ArrayList<E>* outer;

                void modifiedCheck() {
                    if (itModCnt != outer->modCnt) {
                        throw logic_error("the host arrayList has been changed!");
                    }
                }
            
            public :
                ArrayIterator(ArrayList<E>* outer) {
                    itCnt = 0;
                    itModCnt = outer->modCnt;
                    this->outer = outer;
                }     
               
                // TODO : fill it. 
                bool hasNext() {
                   modifiedCheck();
                   return itCnt<outer->cnt;
                }

                // TODO : fill it.
                E next() {
                   (outer->modCnt)++;
                   itModCnt++;
                   return outer->array[itCnt++];
                }

                ~ArrayIterator() {
                    outer = 0;
                }
                 
        };

    public :

        ArrayList() {
            capacity = initialCapacity;
            array = new T[capacity];
            cnt = 0;
            modCnt=0;
        }

        ArrayList(int defaultCapacity) {
            if (defaultCapacity <= initialCapacity) {
                defaultCapacity = initialCapacity;
            }
            capacity = defaultCapacity;
            array = new T[capacity];
            cnt = 0;
            modCnt=0;
        }
        
        // TODO : fill it.
        int size() const {
            return cnt;
        }
        // TODO : fill it.
        bool isEmpty() const {
            return cnt==0;
        }
        // TODO : fill it.
        T get(int index) const {
            if (index<cnt)
                return array[index];
        }
        // TODO : fill it.
        void add(T element) {
            if (cnt>=capacity)
                expandCapacity();
            array[cnt]=element;
            cnt++;
            modCnt++;
        } 
        // TODO : fill it. 
        T remove(int index) {
            for (int i=index; i<cnt-1; i++)
                array[i]=array[i+1];
            cnt--;

            if (cnt<=capacity / 2)
                shrinkCapacity();
        }

        // tricky, return a pointer, how to ensure this ArrayIterator free properly
        // can we manage this allocated Iterators by self?
        Iterator<T>* iterator() {
            return new ArrayIterator<int>(this);
        }

        ~ArrayList() {
            delete [] array;
        }

};


