void merge(List &a, List &b) {
    List c;
    Node* nodea = a->next;
    Node* nodeb = b->next;
    while (nodea && nodeb) {
        if (nodea->value > nodeb->value) {
            c.insert(nodeb);
            nodeb = nodeb->next;
        }
        else {
            c.insert(nodea);
            nodea = nodea->next;
        }
    }
    if (nodea && !nodeb) {
        while (nodea) {
            c.insert(nodea);
            nodea = nodea->next;
        }
    }
    else if (nodeb) {
        while (nodeb) {
            c.insert(nodeb);
            nodeb = nodeb->next;
        }
    }
}