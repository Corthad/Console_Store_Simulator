#ifndef UTILS_H
#define UTILS_H

#include <iostream>

void clean_screen();
void pause_screen();

void print_table_cell(int width, const char* value);
void print_table_row(int n, const int* widths, const char** data);

size_t utf_len(const char* str);
int num_len(long long num);

char* longlong2str(long long num);
char* double2str(double dnum);

long long str2longlong(char* str);
double str2double(char* str);

void input(char* str, size_t max_size);

void input(int& num);
void input(long long& num);

void input(float& dnum);
void input(double& dnum);

int randint(int min, int max);
long long randint(long long min, long long max);

float randfrac(float min, float max);
double randfrac(double min, double max);

#endif // UTILS_H