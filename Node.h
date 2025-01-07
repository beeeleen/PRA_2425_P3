#include <ostream>

using namespace std;

template <typename T> class Node{
        public:
                T data;
                Node<T>* next;

                Node(T d, Node<T>* next = nullptr){ //
            data = d;
            this->next = next;
        }

        friend std::ostream& operator<<(std::ostream &out, const Node<T> &node){
            out << node.data;
            return out;
        }
};
