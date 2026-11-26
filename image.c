#include"image.h"
#include "function.h"
uint8 image[MT9V03X_H][MT9V03X_W];
uint8 base_image[MT9V03X_H][MT9V03X_W];
uint8 left_jidian;
uint8 right_jidian;
uint8 left_line_list[MT9V03X_H];
uint8 right_line_list[MT9V03X_H];
uint8 mid_line_list[MT9V03X_H];

#define GrayScale 256
#define grayscale 256
uint16 hist[GrayScale] ={0};
float P[GrayScale]={0};
float PK[GrayScale]={0};
float MK[GrayScale]={0};
uint8 img_threshold;
float imgsize;
uint8 Ostu(uint8 index[MT9V03X_H][MT9V03X_W])
{
     uint8 threshold;
     imgsize=MT9V03X_W*MT9V03X_H;
     uint8 images_value_temp;
     float sumPK=0;
     float sumMK=0;
     float var=0;
     float vartmp=0;
     for(uint16 i=0;i<GrayScale;i++)
     {
         hist[i]=0;
         P[i]=0;
         PK[i]=0;
         MK[i]=0;
     }
     for(uint8 i=0;i<MT9V03X_H; i++)
     {
         for(uint8 j=0;j<MT9V03X_W; j++)
         {
             images_value_temp=index[i][j];
             hist[images_value_temp]++;
         }
     }
     for(uint16 i=0;i<GrayScale;i++ )
     {
        P[i]=(float)hist[i]/imgsize;
        PK[i]=sumPK+P[i];
        sumPK=PK[i];
        MK[i]=sumMK+i*P[i];
        sumMK=MK[i];
     }
     for(uint8 i=5;i<245;i++)
     {
         vartmp=(MK[GrayScale-1]*PK[i]-MK[i]*(MK[GrayScale-1]*PK[i]-MK[i]))/(PK[i]*(1-PK[i]));
         if(vartmp>var)
         {
             var=vartmp;
             threshold=i;
         }
     }
    return threshold;
}
void set_image_twovalues(uint8 value)
{
    uint8 temp_value;
    for(uint8 i=0;i<40;i++)
    {
        for(uint8 j=0;j<MT9V03X_W;j++)
        {
            temp_value=base_image[i][j];
            if(temp_value<value+20)
            {
                image[i][j]=0;
            }
            else
            {
                image[i][j]=255;
            }
        }
    }
    for(uint8 i=40;i<MT9V03X_H;i++)
    {
        for(uint8 j=0;j<MT9V03X_W;j++)
        {
            temp_value=base_image[i][j];
            if(temp_value<value)
            {
                image[i][j]=0;
            }
            else
            {
                image[i][j]=255;
            }
        }
    }
}
void find_jidian(uint8 index[MT9V03X_H][MT9V03X_W])
{
    //判断二分之一点是否是白点
    if(index[jidian_search_line - 1][MT9V03X_W/2]==255 && index[jidian_search_line - 1][MT9V03X_W/2+1]==255 && index[jidian_search_line - 1][MT9V03X_W/2+2]==255)
    {
        //寻找左边界基点
        for(uint8 j = MT9V03X_W/2; j > 0; j--)
        {
            if(index[jidian_search_line - 1][j-1]==0 && index[jidian_search_line - 1][j]==255 && index[jidian_search_line - 1][j+1]==255)
            {
                left_jidian = j;
                break;
            }
            if(j-1==1)
            {
                left_jidian = 1;
                break;
            }
        }
        //寻找右边界基点
        for(uint8 j = MT9V03X_W/2; j < MT9V03X_W-2; j++)
        {
            if(index[jidian_search_line - 1][j-1]==255 && index[jidian_search_line - 1][j]==255 && index[jidian_search_line - 1][j+1]==0)
            {
                right_jidian = j;
                break;
            }
            if(j+1==MT9V03X_W - 2)
            {
                right_jidian = MT9V03X_W-2;
                break;
            }
        }
    }
    //判断四分之一点是否是白点
    else if(index[jidian_search_line - 1][MT9V03X_W/4]==255 && index[jidian_search_line - 1][MT9V03X_W/4+1]==255 && index[jidian_search_line-1][MT9V03X_W/4+2]==255)
    {
        //寻找左边界基点
        for(uint8 j = MT9V03X_W/4; j > 0; j--)
        {
            if(index[jidian_search_line - 1][j-1]==0 && index[jidian_search_line - 1][j]==255 && index[jidian_search_line - 1][j+1]==255)
            {
                left_jidian =j;
                break;
            }
            if(j-1==1)
            {
                left_jidian =1;
                break;
            }
        }
        //寻找右边界基点
        for(uint8 j = MT9V03X_W/4; j < MT9V03X_W-2; j++)
        {
            if(index[jidian_search_line - 1][j-1]==255 && index[jidian_search_line - 1][j]==255 && index[jidian_search_line - 1][j+1]==0)
            {
                right_jidian =j;
                break;
            }
            if(j+1==MT9V03X_W - 2)
            {
                right_jidian = MT9V03X_W-2;
                break;
            }
        }
    }
    //判断四分之三点是否是白点
    else if(index[jidian_search_line - 1][MT9V03X_W/4*3]==255 && index[jidian_search_line - 1][MT9V03X_W/4*3+1]==255 && index[jidian_search_line-1][MT9V03X_W/4*3+2]==255)
    {
        //寻找左边界基点
        for(uint8 j = MT9V03X_W/4*3; j > 0; j--)
        {
            if(index[jidian_search_line - 1][j-1]==0 && index[jidian_search_line - 1][j]==255 && index[jidian_search_line - 1][j+1]==255)
            {
                left_jidian =j;
                break;
            }
            if(j-1==1)
            {
                left_jidian =1;
                break;
            }
        }
        //寻找右边界基点
        for(uint8 j = MT9V03X_W/4*3; j < MT9V03X_W-2; j++)
        {
            if(index[jidian_search_line - 1][j-1]==255 && index[jidian_search_line - 1][j]==255 && index[jidian_search_line - 1][j+1]==0)
            {
                right_jidian =j;
                break;
            }
            if(j+1==MT9V03X_W - 2)
            {
                right_jidian = MT9V03X_W-2;
                break;
            }
        }
    }
}
void image_deal(uint8 index[MT9V03X_H][MT9V03X_W])
{
    //让第一次搜索参照边界基点
    uint8 left_point = left_jidian;
    uint8 right_point = right_jidian;
    for(uint8 i = search_start_line - 1; i > search_end_line; i--)
    {
        uint8 left_search_judge = 0;//向左搜线标志位
        uint8 mid_start_left_search_judge = 0;//从中间向左搜线标志位
        //寻找左边界点
        //右找10列
        for(uint8 j = left_point; j < left_point+left_line_right_scarch; j++)
        {
            if(index[i][j-1]==0 && index[i][j]==255 && index[i][j+1]==255)
            {
                left_point = j;
                break;
            }
            else if(j == MT9V03X_W-2)
            {
                left_point = MT9V03X_W-5;
                break;
            }
            else if(j == left_point + left_line_right_scarch - 1)
            {
                left_search_judge = 1;
                break;
            }
        }
        //左找5列
        if(left_search_judge == 1)
        {
            for(uint8 j = left_point; j > left_point-left_line_left_scarch; j--)
            {
                if(index[i][j-1]==0 && index[i][j]==255 && index[i][j+1]==255 && j < MT9V03X_W-5)
                {
                    left_point = j;
                    break;
                }
                else if(j == 1)
                {
                    left_point = 1;
                    mid_start_left_search_judge = 1;
                    break;
                }
                else if(j == left_point - left_line_left_scarch + 1)
                {
                    mid_start_left_search_judge = 1;
                    break;
                }
            }
        }
        //从中间往左找
        if(mid_start_left_search_judge == 1)
        {
            for(uint8 j = MID_W; j > 0; j--)
            {
                if(index[i][j-1]==0 && index[i][j]==255 && index[i][j+1]==255)
                {
                    left_point = j;
                    break;
                }
                else if(j == 1)
                {
                    left_point = 1;
                    break;
                }
            }
        }
            uint8 right_search_judge = 0;//向右搜线标志位
            uint8 mid_start_right_search_judge = 0;//从中间向右搜线标志位
            //寻找右边界点
            //左找10列
            for(uint8 j = right_point; j > right_point-right_line_left_scarch; j--)
            {
                if(index[i][j-1]==255 && index[i][j]==255 && index[i][j+1]==0)
                {
                    right_point = j;
                    break;
                }
                else if(j == 1)
                {
                    right_point = 4;
                    break;
                }
                else if(j == right_point - right_line_left_scarch + 1)
                {
                    right_search_judge = 1;
                    break;
                }
            }
            //右找5列
            if(right_search_judge == 1)
            {
                for(uint8 j = right_point; j < right_point+right_line_right_scarch; j++)
                {
                    if(index[i][j-1]==255 && index[i][j]==255 && index[i][j+1]==0 && j > 4)
                    {
                        right_point = j;
                        break;
                    }
                    else if(j == MT9V03X_W-2)
                    {
                        right_point = MT9V03X_W-2;
                        mid_start_right_search_judge = 1;
                        break;
                    }
                    else if(j == right_point + right_line_right_scarch - 1)
                    {
                        mid_start_right_search_judge = 1;
                        break;
                    }
                }
            }
                //从中间往右找
                if(mid_start_right_search_judge == 1)
                {
                    for(uint8 j = MID_W; j < MT9V03X_W-1; j++)
                    {
                        if(index[i][j-1]==255 && index[i][j]==255 && index[i][j+1]==0)
                        {
                            right_point = j;
                            break;
                        }
                        else if(j == MT9V03X_W-2)
                        {
                            right_point = MT9V03X_W-2;
                            break;
                        }
                    }
                }
                left_line_list[i]=Limit_uint8(1,left_point,MT9V03X_W-2);
                right_line_list[i]=Limit_uint8(1,right_point,MT9V03X_W-2);
                mid_line_list[i]=Limit_uint8(1,(left_line_list[i]+right_line_list[i])/2,MT9V03X_W-2);
      }
}
//图像权重数组
//权重越靠上，车转弯越早
uint8 mid_weight_list[130]=
{
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,
    6,6,6,6,6,6,6,6,6,6,6,
    7,8,9,10,11,12,13,14,15,16,
    17,18,19,20,20,20,20,19,18,17,
    16,15,14,13,12,11,10,9,8,7,
    6,6,6,6,6,6,6,6,6,6,6,
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,
};
uint8 final_mid_line = MID_W;    //最终输出的中线值
uint8 last_mid_line = MID_W;     //上次中线值
uint8 find_mid_line_weight(void)
{
    uint8 mid_line_value = MID_W; //最终中线输出值
    uint8 mid_line = MID_W;       //本次中线值
    uint32 weight_midline_sum = 0;//加权中线累加值
    uint32 weight_sum = 0;        //权重累加值
    for(uint8 i=MT9V03X_H - 1;i>search_end_line;i--)
    {
        weight_midline_sum += mid_line_list[i] * mid_weight_list[i];
        weight_sum += mid_weight_list[i];
    }
    mid_line=(uint8)(weight_midline_sum/weight_sum);
    mid_line_value=last_mid_line*0.2+mid_line*0.8;//互补滤波
    last_mid_line=mid_line_value;
    return mid_line_value;
}
