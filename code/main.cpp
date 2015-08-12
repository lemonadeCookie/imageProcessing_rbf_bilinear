//
//  main.cpp
//  biliner
//
//  Created by logicRabbit on 14/11/12.
//  Copyright (c) 2014年 logicRabbit. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int main()
{
    const int x=375;
    const int y=500;
    const int tmpx[5]={-2,-1,0,1,2};
    const int tmpy[5]={-2,-1,0,1,2};
    double rate=0.1;
    
    double gph[x][y];
    ifstream fin;
    int count=0;
    
    double power[5][5];
    for(int k=0;k<5;k++){
        for(int m=0;m<5;m++){
            if(tmpx[k]*tmpx[k]+tmpy[m]*tmpy[m]!=0)power[k][m]=1/sqrt(tmpx[k]*tmpx[k]+tmpy[m]*tmpy[m]);
            else power[k][m]=0;
        }
    }
    fin.open("/Users/logicRabbit/Desktop/biliner/biliner/d.txt");
    
    //读入数据
    for (int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            fin>>gph[i][j];
        }
    }
    fin.clear();
    fin.close();
    //生成随机数，扣点
    for (int i=0;i<x;i++){
        for(int j=0;j<y*rate;j++){
            int t = rand()%y;
            if(gph[i][t]!=255)gph[i][t]=255;
            else j--;
        }
    }
    //特定的mask方法
   /* for (int i=0;i<x;i++){
        if((i+10)<y){
            for(int j=i;j<(i+10);j++){
                gph[i][j]=255;
            }
        }
    }*/
    //输出添加噪声后的效果
    ofstream gout;
    
    cout<<"3"<<endl;
    gout.open("/Users/logicRabbit/Desktop/biliner/biliner/BILINER_MIN_d_0.1.txt");
    for (int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            gout<<gph[i][j]<<" ";
        }
        gout<<endl;
    }
    gout.clear();
    gout.close();
    
    
    //bilinear
    for (int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(gph[i][j]==255){
                double tar=0;
                double t[5][5];
                
                for(int k=0;k<5;k++){
                    for(int m=0;m<5;m++){
                        if(((i+tmpx[k])>0)&&((i+tmpx[k])<x-1)&&((j+tmpy[m])>0)&&((j+tmpy[m])<y-1)){
                            t[k][m] = gph[i+tmpx[k]][j+tmpy[m]];
                        }
                    }
                }
                double s=0;
                //求目标值
                for(int k=0;k<5;k++){
                    for(int m=0;m<5;m++){
                        if(t[k][m]!=255) s+=power[k][m];
                    }
                }
                for(int k=0;k<5;k++){
                    for(int m=0;m<5;m++){
                        if(t[k][m]!=255) tar+=t[k][m]*(power[k][m]/s);
                    }
                }
                
                count++;
                gph[i][j]=tar;
            }
        }
    }
    //输出
    ofstream fout;
    fout.open("/Users/logicRabbit/Desktop/biliner/biliner/BILINER_OUT_d_0.1.txt");
    for (int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            fout<<gph[i][j]<<" ";
        }
        fout<<endl;
    }
    fout.clear();
    fout.close();
    
    cout<<count;
    return 0;
}


