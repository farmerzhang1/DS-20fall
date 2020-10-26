enum Status {ERROR, OK};
Status Replace(string T, string V) {
    int i;

    if(Empty(S) || Empty(T)) {
        return ERROR;
    }

    // 在主串S中寻找模式串T第一次出现的位置
    i = index(T, 1);

    // 如果存在匹配的字符串，且可以被完全替换（替换后不溢出）
    while(i != 0 && S[0] - T[0] + V[0] <= MAXSTRLEN) {
        Delete(i, Length(T));  // 从S中删除T
        Insert(i, V);             // 向S中插入V

        i += Length(V);      // i切换到下一个位置

        i = index(T, i);   // 查找下一个匹配的字符串
    }

    if(i == 0) {                // S中的T已全部被替换
        return OK;
    } else {                    // S中尚有T，但是V已经插不进去了
        return ERROR;
    }
}