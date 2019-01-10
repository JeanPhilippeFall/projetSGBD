#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"cJSON.h"
#include"svg.h"

#define N 500
#define SVG_WIDTH 1024
#define SVG_HEIGHT 1024
#define WINDOW_WIDTH 180
#define WINDOW_HEIGHT 80

char* readfile(const char* filepath);
void treatChild(const cJSON* element);
void treatJson(const char* filepath, char* outputName);
