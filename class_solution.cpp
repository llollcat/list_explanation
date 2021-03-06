#include <iostream>
#include "vector"
using namespace std;

template <typename type>
class List {
public:
    int itemCounter = 0;
    struct List_struct{
        type item;
        List_struct* next_item_ptr = nullptr;
        explicit List_struct(type input) {
            item = input;
        }
        explicit List_struct(type input, List_struct* next_item) {
            item = input;
            next_item_ptr = next_item;
        }
    };
    List_struct *head = nullptr;


public:
    void insert(int index,type input) {
        ++itemCounter;

        List_struct *tempPointer = head;

        if (index == 0) {
            head = new List_struct(input, tempPointer);
        } else {
            for (int i = 1; i < index; ++i) {
                tempPointer = tempPointer->next_item_ptr;
            }

            tempPointer->next_item_ptr = new List_struct(input, tempPointer->next_item_ptr);
        }
    };

    void delete_item(int index) {
        --itemCounter;
        List_struct *tempPointer = head;
        if (index == 0) {
            head = head->next_item_ptr;
            delete tempPointer;
        } else {
            for (int i = 1; i < index; ++i) {
                tempPointer = tempPointer->next_item_ptr;
            }
            List_struct *PointerToDelete = tempPointer->next_item_ptr;
            tempPointer->next_item_ptr = PointerToDelete->next_item_ptr;
            delete PointerToDelete;
        }

    }


    List_struct* find_item_pointer(type value){
        List_struct *tempPointer = head;
        for (int i =0; i<itemCounter; ++i) {
            if (value == tempPointer->item)
                return tempPointer;
            tempPointer = tempPointer->next_item_ptr;

        }
        return nullptr;
    }
    int find_item_id(type value) {
        List_struct *tempPointer = head;
        for (int i =0; i<itemCounter; ++i) {
            if (value == tempPointer->item)
                return i;
            tempPointer = tempPointer->next_item_ptr;

        }
        return -1;

    }




    void print_all() {
        List_struct *tempPointer = head;
        while (tempPointer != nullptr) {
            cout << tempPointer->item << endl;
            tempPointer = tempPointer->next_item_ptr;
        }

    }


    void print_item_id(int id){
        List_struct *tempPointer = head;
        for (int i =0; i<id; ++i) {
            tempPointer = tempPointer->next_item_ptr;
        }
        cout << tempPointer->item;


    };



    void change_item(type value, type newValue) {
        List_struct* tempPointer = find_item_pointer(value);
        if (tempPointer != nullptr)
            tempPointer->item = newValue;


    }



    void push_back(type input) {

        insert(itemCounter, input);

    }
    
};



int main() {

    List<int> list= List<int>();
    list.push_back(101);
    list.print_all();



    return 0;
}
