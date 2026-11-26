#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_

#include "zf_common_headfile.h"

#define jidian_search_line 120        //基点搜索行
#define search_start_line 120         //搜线起始行
#define search_end_line 30            //搜线停止行
#define left_line_right_scarch 10     //搜索左边线时向右搜索几列
#define left_line_left_scarch 5       //搜索左边线时向左搜索几列
#define right_line_right_scarch 10    //搜索右边线时向右搜索几列
#define right_line_left_scarch 5      //搜索右边线时向左搜索几列
#define MID_W 93                      //赛道中值

extern uint8 base_image[MT9V03X_H][MT9V03X_W];
extern uint8 image[MT9V03X_H][MT9V03X_W];
extern uint8 img_threshold;
extern uint8 left_jidian;
extern uint8 right_jidian;
extern uint8 left_line_list[MT9V03X_H];
extern uint8 right_line_list[MT9V03X_H];
extern uint8 mid_line_list[MT9V03X_H];

uint8 Ostu(uint8 index[MT9V03X_H][MT9V03X_W]);
void set_image_twovalues(uint8 value);
void find_jidian(uint8 index[MT9V03X_H][MT9V03X_W]);
void image_deal(uint8 index[MT9V03X_H][MT9V03X_W]);

#endif /* CODE_IMAGE_H_ */
