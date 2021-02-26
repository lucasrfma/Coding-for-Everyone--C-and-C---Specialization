#include <iostream>

class List_Element{
    public:
        
        List_Element(int data = 0, List_Element* next = nullptr):
            data(data), next(next){}

        int data;
        List_Element *next;

};

class List{
    public:

        List(List_Element *head = nullptr):head(head),cursor(head){}

        List(const int array[], int size):head(nullptr),cursor(nullptr){

            for(--size; size >=0; --size){
                prepend(array[size]);
            }
        }

        ~List(){
            
            for(cursor = head; cursor!= nullptr; head = cursor){
                cursor = head->next;
                delete head;
            }
        }

        void prepend(int n){
            if( head ){
                head = new List_Element(n,head);
            }else{
                cursor = head = new List_Element(n,head);
            }
        }

        int get_element(){
            return cursor->data;
        }

        void advance(){
            cursor = cursor->next;
        }

        void print(){
            List_Element *h = head;
            while( h != nullptr ){
                std::cout << h->data << " -> ";
                h = h->next;
            }
            std::cout << "\n###" << std::endl;
        }

        friend std::ostream& operator<<(std::ostream &out,const List& list){
            List_Element *h = list.head;
            while(h != nullptr){
                out << h->data << " -> ";
                h = h->next;
            }
            return out;
        }

    private:
        List_Element *head;
        List_Element *cursor;
};

int main(){

    List list;
    List_Element testing(10);
    int array[10] =  {0,1,2,3,4,5};
    List listB(array,6);
    List listC(array,10);


    list.prepend(5);
    list.prepend(9);
    list.prepend(7);

    list.print();

    std::cout << "\nThis is a test!!\n" << list << std::endl;


    listB.print();
    printf("\n\n");
    listC.print();

    // listB.~List;
    // list.~List;
    // delete(list);
    // delete &list;

    // listB.print();


    return 0;
}