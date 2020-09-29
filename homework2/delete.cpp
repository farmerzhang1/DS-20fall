int remove(List list, int mink, int maxk) {
    Node* node = list->next;
    Node* before = list;
    Node* temp;
    while (node) {
        if (node->value > mink) break;
        before = node;
        node = node->next;
    }
    while (node) {
        if (node->value < maxk) {
            temp = node;
            node = node->next;
            list.remove(temp);
        }
        else break;
    }
    before->next = node;
}