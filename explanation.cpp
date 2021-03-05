/* Перед началом рекомендуется прочитать, если не до конца понятны указатели:
 * https://ravesli.com/urok-80-ukazateli-vvedenie/
 * https://ravesli.com/urok-93-ukazateli-na-ukazateli/
 *
 * индексация производится с нуля */
#include <iostream>

using namespace std;


struct List{
    char item;
    /* next_item_ptr - казатель на следующий элемент списка.
     Значение nullptr означает, что данный указатель ни на что сейчас не указывает.
     При создании новых членов листа, значение next_item_ptr будет изменено на адрес последующего элемента. */
    List* next_item_ptr = nullptr;
    /* Следующие 7 строчек после комментария это конструкторы. Они перегружены.
       Подробнее про конструкторы можно почитать тут: https://ravesli.com/urok-116-konstruktory/
       Без конструкторов можно обойтись, но прийдётся каждый раз задавать значение переменной вручную. */
    List(char input) {
        item = input;
    }
    List(char input, List* next_item) {
        item = input;
        next_item_ptr = next_item;
    }
};


/* Создаём глобальную переменную list, которая является началом, и itemCounter, которая нужна для подсчёта количества
   элементов и реализации некоторых функций ниже. */
List *list = nullptr;
int itemCounter = 0;


void add_item(int index,char input) {
    ++itemCounter;
    // Создаём копию указателя, чтобы можно было проводить итерацию по листу.
    List *tempPointer = list;

    if (index == 0) {
        list = new List(input, tempPointer);
    } else {
        for (int i = 1; i < index; ++i) {
            tempPointer = tempPointer->next_item_ptr;
        }
        /* Что просходит в следующей строчке?
           Код функции выше нашёл элемент списка, предшествующий нужному для замены члену. Результат находится в
           tempPointer, то есть это предшествющий элемент.
           Теперь мы меняем значение указателя предшествующего элемента на адрес нашего нового элемента.
           В новом элемента будет находиться новое значение и указатель на последующий член. Установка этих значений
           реализована через конструкторы.
         */
        tempPointer->next_item_ptr = new List(input, tempPointer->next_item_ptr);
    }
};

// Данная функция похожа на предыдущую, но вместо создания новой связи, мы разрываем старую.
void delete_item(int index) {
    ++itemCounter;
    List *tempPointer = list;
    if (index == 0) {
        list = list->next_item_ptr;
        delete tempPointer;
    } else {
        for (int i = 1; i < index; ++i) {
            tempPointer = tempPointer->next_item_ptr;
        }
        List *PointerToDelete = tempPointer->next_item_ptr;
        tempPointer->next_item_ptr = PointerToDelete->next_item_ptr;
        delete PointerToDelete;
    }

}

// Возвращается не нулевой указатель при наличии объекта с нужным значением. Ищется первое соответствие.
List* find_item_pointer(char value){
    List *tempPointer = list;
    for (int i =0; i<itemCounter; ++i) {
        if (value == tempPointer->item)
            return tempPointer;
        tempPointer = tempPointer->next_item_ptr;

    }
    return nullptr;
}
// Поиск первого элемента списка по его значению возвращает его id, иначе говоря, номер элемента. Если не найден, то возвращает -1
int find_item_id(char value) {
    List *tempPointer = list;
    for (int i =0; i<itemCounter; ++i) {
        if (value == tempPointer->item)
            return i;
        tempPointer = tempPointer->next_item_ptr;

    }
    return -1;

}




void print_all() {
    List *tempPointer = list;
    while (tempPointer != nullptr) {
        cout << tempPointer->item << endl;
        tempPointer = tempPointer->next_item_ptr;
    }

}

// печать элемента списка по его id
void print_item_id(int id){
    List *tempPointer = list;
    for (int i =0; i<id; ++i) {
        tempPointer = tempPointer->next_item_ptr;
    }
    cout << tempPointer->item;


};


// ниже функции-обёртки

// Функция замены первого найденного элемента списка по его значению
void change_item(char value, char newValue) {
    List* tempPointer = find_item_pointer(value);
    if (tempPointer != nullptr)
        tempPointer->item = newValue;


}


// добавиление элемента в конец списка.
void input_item(char input) {
    //
    add_item(itemCounter, input);

}


int main() {
    printf("string len:\n");
    int len; scanf("%d", &len);

    printf("string:\n");
    char buff[255]; scanf("%s", buff);

    for (int i = 0; i < len; ++i)
        input_item(buff[i]);


// программа создаст список, выведет его, удалит первый элемент, а затем снова выведет его.
    print_all(); 
    delete_item(0);
    print_all();


    return 0;
}

// Также хорошо помогает понять как работает список отладка. Используя данный пример, можно поставить брекпоинт и посмотреть как он будет выглядить.
