/*
 *  Allwinner Mainline Lcd Tools
 * Copyright 2021 HandsomeYingyan <handsomeyingyan@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Big Thanks To:
 *    Linux-sunxi Community LCD wiki page: https://linux-sunxi.org/LCD
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int lcd_x,lcd_y,lcd_frm,lcd_dclk_freq,lcd_hspw,lcd_vspw,lcd_hbp,lcd_ht,lcd_vbp,lcd_vt;
	char *panel_model = malloc(sizeof(char)*50);
	int allwinner_type = -1;
	
	printf("Allwinner Lcd Tools By HandsomeYingyan<handsomeyingyan@gmail.com>\n");
	printf("Your Screen Model: ");
	scanf("%s",panel_model);
	printf("Allwinner Soc Type sun8i == 1 other == 0  :");
	scanf("%d",&allwinner_type);
	printf("lcd_x = ");
	scanf("%d",&lcd_x);
	printf("lcd_y = ");
	scanf("%d",&lcd_y);
	printf("lcd_frm = ");
	scanf("%d",&lcd_frm);
	printf("lcd_dclk_freq = ");
	scanf("%d",&lcd_dclk_freq);
	printf("lcd_hspw = ");
	scanf("%d",&lcd_hspw);
	printf("lcd_vspw = ");
	scanf("%d",&lcd_vspw);
	printf("lcd_hbp = ");
	scanf("%d",&lcd_hbp);
	printf("lcd_ht = ");
	scanf("%d",&lcd_ht);
	printf("lcd_vbp = ");
	scanf("%d",&lcd_vbp);
	printf("lcd_vt = ");
	scanf("%d",&lcd_vt);
	
	printf("Ok Here is result!!\n\n");
	int x = lcd_x;
	int y = lcd_y;
	int depth;
	if(lcd_frm == 1){
		depth=18;
	}else{
		depth=24;
	}
	int pclk_khz = lcd_dclk_freq * 1000;
	int hs = lcd_hspw;
	int vs = lcd_vspw;
	int le = lcd_hbp - hs;
	int ri = lcd_ht - lcd_x - lcd_hbp;
	int up  = lcd_vbp - vs;
	int lo;
	if(allwinner_type == 1){
		/* Sun8i */
		lo = lcd_vt - lcd_y - lcd_vbp;
	}else{
		/*   Sun4i 5i 7i*/
		lo = (lcd_vt / 2) - lcd_y - lcd_vbp;
	}
	int sync = 3;
	int vmode = 0;
	printf("U-BOOT Format: \n");
	printf("CONFIG_VIDEO_LCD_MODE=\"");
	printf("x:%d,y:%d,depth:%d,pclk_khz:%d,le:%d,ri:%d,up:%d",x,y,depth,pclk_khz,le,ri,up);
	printf(",lo:%d,hs:%d,vs:%d,sync:%d,vmode:%d\"",lo,hs,vs,sync,vmode);

	printf("\n\nMainline kernel's simple-panel struct: \n");
	printf("static const struct drm_display_mode %s = { \n",panel_model);
	printf("\t.clock = %d,\n",pclk_khz);
	printf("\t.hdisplay = %d,\n",x);
	printf("\t.hsync_start = %d,\n",x+ri);
	printf("\t.hsync_end = %d,\n",x+ri+hs);
	printf("\t.htotal = %d,\n",x+ri+hs+le);
	printf("\t.vdisplay = %d,\n",y);
	printf("\t.vsync_start = %d,\n",y+lo);
	printf("\t.vsync_end = %d,\n",y+lo+vs);
	printf("\t.vsync_end = %d,\n",y+lo+vs+up);
	printf("\t.vrefresh = 60,\n");
	printf("};");
	return 0;
}

