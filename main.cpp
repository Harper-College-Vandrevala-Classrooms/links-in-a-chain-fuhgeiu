#include <iostream>
#include <cassert>

namespace node_container {

    template <typename T>
    struct node {

        T data;
        node* next = nullptr;
        node* previus = nullptr;

        node (T Data, node<T>* nnode) : data(Data), next(nnode) {

            if (data == nullptr || next == nullptr) throw std::runtime_error("failed to initilize");
        }

        node (T Data, node<T>* nnode, node<T>* n2node) : data(Data), next(nnode), previus(n2node) {

            if(data == nullptr || next == nullptr || previus == nullptr) throw std::runtime_error("failed to initilize");
        }

        node (T Data) : data(Data) {if(data == nullptr) throw std::runtime_error("failed to initilize");}

        node () = default;

    }; // end of S node


    namespace single {


        template <typename T>
        class slist {

            node<T> *head = nullptr;

        public:

            slist () : head(nullptr) {}

            slist(const slist<T>& cpy_from) {

                if (cpy_from.head != nullptr) {

                    node<T>* temp = cpy_from.head;
                    node<T>* prev_new = nullptr;

                    while (temp != nullptr) {

                        auto* new_node = new node<T>(temp->data);
                        if (prev_new == nullptr) {head = new_node;}
                            else {prev_new->next = new_node;}

                        prev_new = new_node;
                        temp = temp->next;
                    }
                }
            }

            T ret_value_first () {return head->data;}

            T ret_value_index (size_t index) {

                node<T>* temp = this->head;

                for (size_t i = 0; i < (index-1); i++) {

                    temp = temp->next;
                }

                return temp->data;
            }

            node<T>* first_cpy_ret () {if (head != nullptr) return head;}               // assignable

            node<T>* last_cpy_ret () {                                                  // assignable

                node<T>* temp = this->head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                return temp;
            }

            void add (T& data) {

                if (head != nullptr) {

                    node<T> *temp = this->head;

                    while (temp->next != nullptr) {

                        temp = temp->next;
                    }

                    auto *append = new node<T>(data);
                    temp->next = append;
                }

                if (head == nullptr) {this->head = new node<T> (data);}
            }

            ~slist() {

                node<T>* temp = head;

                while (temp != nullptr) {

                    node<T>* to_delete = temp;
                    temp = temp->next;
                    delete to_delete;
                }
            }

        }; // end of C slist

    }

} // end of N link

class ChainLink {
private:
    std::string color;

public:
    ChainLink(std::string color) {
        this->color = color;
    }

    std::string get_color() {
        return this->color;
    }
};


int main () {

    node_container::single::slist<ChainLink*> list1;

    auto link1 = new ChainLink("red");

    list1.add(link1);

    assert(list1.ret_value_first()->get_color() == "red");

    auto link2 = new ChainLink("blue");
    auto link3 = new ChainLink("orange");

    list1.add(link2);       // add blue
    list1.add(link3);       // add orange

    assert(list1.ret_value_first()->get_color() == "red");
    assert(list1.ret_value_index(2)->get_color() == "blue");
    assert(list1.ret_value_index(3)->get_color() == "orange");

}
