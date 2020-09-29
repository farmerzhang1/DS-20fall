int compare(Sqlist a, Sqlist b) {
    int i = 0;
    while (a[i++] == b[i++] && i < a.length() && i < b.length());
    if (i == a.length() && i == b.length()) return 0;
    if (i < a.length() && i == b.length()) return 1;
    if (i < b.length() && i == a.length()) return -1;
    return a[i] - b[i];
}