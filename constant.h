#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/affinematrix2d.h>
#include <wx/dcbuffer.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>


const short id_static_array = 1;
const short id_dynamic_array = 2;
const short id_simply_linked_list = 3;
const short id_doubly_linked_list = 4;
const short id_circular_linked_list = 5;
const short id_stack = 6;
const short id_queue = 7;

const short size1 = 1090;
const short size2 = 690;

const short max_size = 12;
const short box_position[14] = {25, 100, 175, 250, 325, 400, 475, 550, 625, 700, 775, 850, 925, 1000};
const short box_y = 220;
const short box_size = 50;
const short box_color = 225;

const short rad[3] = {20, 25, 30};

const short black[3] = {0, 0, 0};