#include "list.h"

#define NULL nullptr

ListNode::ListNode(int data) {
    this->data = data;
}

List::List(int size) {
    this->create(size);
}

ListNode* List::find(short index) {
    // мюунфдемхе щкелемрю б яохяйе он хмдейяс

    ListNode* iter = head;

    if (index < 0 || index >= this->size) {
        std::cout << "invalid index";
        return NULL;
    }

    for (int i = 0; i < index; ++i) {
        iter = iter->next;
    }

    return iter;
}

void List::create(short size) {
    // янгдюмхе яохяйю пюглепмнярх SIZE

    ListNode *curr = NULL, *next = NULL, *prev = NULL;

    for (int i = 1; i <= size; ++i) {
        curr = new ListNode(size - i);

        if (prev != NULL) {
            prev->prev = curr;
        }
        
        curr->next = next;
        curr->data = (size - i) + 1;
        next = curr;
    }

    this->head = curr;
    this->size = size;
}

void List::print() {
    // бшбедемхе люяяхбю мю щйпюм

    ListNode* iter = this->head;

    std::cout << "NULL <- ";
    while (iter != NULL) {
        std::cout << iter->data;
        if (iter->next != NULL) {
            std::cout << " <-> ";
        }
        iter = iter->next;
    }
    std::cout << " -> NULL";
}

void List::insert(int data, int index) {
    // бярюбйю щкелемрю он хмдейяс б яохянй

    ListNode* new_cur = new ListNode(data);
    ListNode* next = NULL;
    ListNode* prev = NULL;

    if (index == 0) {
        next = this->head;

        this->head = new_cur;
        this->head->prev = NULL;
        this->head->next = next;
    } else {
        // нйпсфючыхе мндш
        prev = this->find(index - 1);
        next = prev->next;

        // пюяярбкъел сйюгюрекх нрмняхрекэмн опнькнцн щкелемрю
        prev->next = new_cur;
        new_cur->prev = prev;
         
        // пюяярюбкъел сйюгюрекх нрмняхрекэмн якед щкелемрю
        new_cur->next = next;
        if (next!= NULL) {
            next->prev = new_cur;
        }
    }

    this->size += 1;
    
}

void List::remove(int index) {
    // сдюкемхе щкелемрю хг яохяйю

    ListNode* del = NULL;

    if (index == 0) {
        del = this->head;
        this->head = this->head->next;
    } else {
        ListNode* prev = this->find(index - 1);
        ListNode* next = prev->next->next;

        //сдюкъелши йемр
        del = prev->next;

        //налем сйюгюрекълх
        prev->next = next;
        if (next != NULL) {
            next->prev = prev;
        }
    }

    this->size -= 1;
    delete del;
}
