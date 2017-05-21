#pragma once

#ifndef _BOTTLES_
extern int* get_bottles();
extern bool check(int a, int b, int c); //检测三次输入瓶子数量是否相等
extern void writePath(int from, int to, int *start);

extern int num;
#endif // !_BOTTLES_