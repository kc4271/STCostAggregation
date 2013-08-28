/*
This project implements the methods in the following paper. Please cite this paper, depending on the use.

Xing Mei, Xun Sun, Weiming Dong, Haitao Wang and Xiaopeng Zhang. Segment-Tree based Cost Aggregation for Stereo Matching, in CVPR 2013.

The code is written by Yan Kong, <kongyanwork@gmail.com>, 2013.

LICENSE
Copyright (C) 2012-2013 by Yan Kong
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <cstdlib>
#include <cstdio>
#include "evaluate.h"
#include <fstream>
enum METHOD {ST_RAW, ST_REFINED};

void stereo_launch(const char *left_img, const char *right_img, const char *disp_img, int max_level, int scale, float sigma, METHOD m) {
	char command_buf[1023];
	sprintf(command_buf, "%s %s %s %s %d %d %f %d",
		RUN_PATH, left_img, right_img, disp_img, max_level, scale, sigma, m == ST_RAW ? 0 : 1);
	system(command_buf);
}

float TestRoutine_Batch_MiddleburyStandard(float sigma, METHOD bST_type) {
	stereo_launch( ROOT_PATH "Data/tsukuba/imL.png", ROOT_PATH "Data/tsukuba/imR.png", "tsukuba_dis.png", 16, 16, sigma, bST_type);
	stereo_launch( ROOT_PATH "Data/venus/imL.png", ROOT_PATH "Data/venus/imR.png", "venus_dis.png", 20, 8, sigma, bST_type);
	stereo_launch( ROOT_PATH "Data/teddy/imL.png", ROOT_PATH "Data/teddy/imR.png", "teddy_dis.png", 60, 4, sigma, bST_type);
	stereo_launch( ROOT_PATH "Data/cones/imL.png", ROOT_PATH "Data/cones/imR.png", "cones_dis.png", 60, 4, sigma, bST_type);


	float err_average=0, err_average_non_occ=0, err_non_occ=0;
	err_average += TestResult_OnePixel_Val("tsukuba_dis.png", ROOT_PATH "Data/tsukuba/groundtruth.bmp", ROOT_PATH "Data/tsukuba/mask.bmp", 16);
	err_average += TestResult_OnePixel_Val("tsukuba_dis.png", ROOT_PATH "Data/tsukuba/groundtruth.bmp", ROOT_PATH "Data/tsukuba/tsukuba_mask_disc.bmp", 16);
	err_average += err_non_occ = TestResult_OnePixel_Val("tsukuba_dis.png", ROOT_PATH "Data/tsukuba/groundtruth.bmp", ROOT_PATH "Data/tsukuba/tsukuba_mask_nonocc.bmp", 16, "tsukuba_bad.png");
	printf("  Tsukuba: %.02f%%\n",100 * err_non_occ);
	err_average_non_occ += err_non_occ;
	

	err_average += TestResult_OnePixel_Val("venus_dis.png", ROOT_PATH "Data/venus/groundtruth.png", ROOT_PATH "Data/venus/mask.bmp", 8);
	err_average += TestResult_OnePixel_Val("venus_dis.png", ROOT_PATH "Data/venus/groundtruth.png", ROOT_PATH "Data/venus/venus_mask_disc.bmp", 8);
	err_average += err_non_occ = TestResult_OnePixel_Val("venus_dis.png", ROOT_PATH "Data/venus/groundtruth.png", ROOT_PATH "Data/venus/venus_mask_nonocc.bmp", 8, "venus_bad.png");
	printf("  Venus: %.02f%%\n",100 * err_non_occ);
	err_average_non_occ+=err_non_occ;
	
	err_average += TestResult_OnePixel_Val("teddy_dis.png", ROOT_PATH "Data/teddy/groundtruth.png", ROOT_PATH "Data/teddy/mask.bmp", 4);
	err_average += TestResult_OnePixel_Val("teddy_dis.png", ROOT_PATH "Data/teddy/groundtruth.png", ROOT_PATH "Data/teddy/teddy_mask_disc.bmp", 4);
	err_average += err_non_occ = TestResult_OnePixel_Val("teddy_dis.png", ROOT_PATH "Data/teddy/groundtruth.png", ROOT_PATH "Data/teddy/teddy_mask_nonocc.bmp", 4, "teddy_bad.png");
	printf("  Teddy: %.02f%%\n",100 * err_non_occ);
	err_average_non_occ+=err_non_occ;
	
	err_average += TestResult_OnePixel_Val("cones_dis.png", ROOT_PATH "Data/cones/groundtruth.png", ROOT_PATH  "Data/cones/mask.bmp", 4);
	err_average += TestResult_OnePixel_Val("cones_dis.png", ROOT_PATH "Data/cones/groundtruth.png", ROOT_PATH  "Data/cones/cones_mask_disc.bmp", 4);
	err_average += err_non_occ = TestResult_OnePixel_Val("cones_dis.png", ROOT_PATH "Data/cones/groundtruth.png", ROOT_PATH "Data/cones/cones_mask_nonocc.bmp", 4, "cones_bad.png");
	printf("  Cones: %.02f%%\n",100 * err_non_occ);
	err_average_non_occ+=err_non_occ;
	
	return (100 * err_average_non_occ / 4);
}

char cTestFilePool[162][256]=
{
	ROOT_PATH "Data_extended/Aloe/disp1.png", ROOT_PATH "Data_extended/Aloe/disp5.png", "_Aloe.png", ROOT_PATH "Data_extended/Aloe/view1.png", ROOT_PATH "Data_extended/Aloe/view5.png", "_Aloe_bad.png",
	ROOT_PATH "Data_extended/Art/disp1.png", ROOT_PATH "Data_extended/Art/disp5.png", "_Art.png", ROOT_PATH "Data_extended/Art/view1.png", ROOT_PATH "Data_extended/Art/view5.png", "_Art_bad.png",
	ROOT_PATH "Data_extended/Baby1/disp1.png", ROOT_PATH "Data_extended/Baby1/disp5.png", "_Baby1.png", ROOT_PATH "Data_extended/Baby1/view1.png", ROOT_PATH "Data_extended/Baby1/view5.png", "_Baby1_bad.png",
	ROOT_PATH "Data_extended/Baby2/disp1.png", ROOT_PATH "Data_extended/Baby2/disp5.png", "_Baby2.png", ROOT_PATH "Data_extended/Baby2/view1.png", ROOT_PATH "Data_extended/Baby2/view5.png", "_Baby2_bad.png",
	ROOT_PATH "Data_extended/Baby3/disp1.png", ROOT_PATH "Data_extended/Baby3/disp5.png", "_Baby3.png", ROOT_PATH "Data_extended/Baby3/view1.png", ROOT_PATH "Data_extended/Baby3/view5.png", "_Baby3_bad.png",
	ROOT_PATH "Data_extended/Books/disp1.png", ROOT_PATH "Data_extended/Books/disp5.png", "_Books.png", ROOT_PATH "Data_extended/Books/view1.png", ROOT_PATH "Data_extended/Books/view5.png", "_Books_bad.png",
	ROOT_PATH "Data_extended/Cloth2/disp1.png", ROOT_PATH "Data_extended/Cloth2/disp5.png", "_Cloth2.png", ROOT_PATH "Data_extended/Cloth2/view1.png",ROOT_PATH  "Data_extended/Cloth2/view5.png", "_Cloth2_bad.png",
	ROOT_PATH "Data_extended/Cloth3/disp1.png", ROOT_PATH "Data_extended/Cloth3/disp5.png", "_Cloth3.png", ROOT_PATH "Data_extended/Cloth3/view1.png", ROOT_PATH "Data_extended/Cloth3/view5.png", "_Cloth3_bad.png",
	ROOT_PATH "Data_extended/Dolls/disp1.png", ROOT_PATH "Data_extended/Dolls/disp5.png", "_Dolls.png", ROOT_PATH "Data_extended/Dolls/view1.png", ROOT_PATH "Data_extended/Dolls/view5.png", "_Dolls_bad.png",
	ROOT_PATH "Data_extended/Flowerpots/disp1.png", ROOT_PATH "Data_extended/Flowerpots/disp5.png", "_Flowerpots.png", ROOT_PATH "Data_extended/Flowerpots/view1.png", ROOT_PATH "Data_extended/Flowerpots/view5.png", "_Flowerpots_bad.png",
	ROOT_PATH "Data_extended/Lampshade1/disp1.png", ROOT_PATH "Data_extended/Lampshade1/disp5.png", "_Lampshade1.png", ROOT_PATH "Data_extended/Lampshade1/view1.png", ROOT_PATH "Data_extended/Lampshade1/view5.png", "_Lampshade1_bad.png",
	ROOT_PATH "Data_extended/Laundry/disp1.png", ROOT_PATH "Data_extended/Laundry/disp5.png", "_Laundry.png", ROOT_PATH "Data_extended/Laundry/view1.png", ROOT_PATH "Data_extended/Laundry/view5.png", "_Laundry_bad.png",
	ROOT_PATH "Data_extended/Midd1/disp1.png", ROOT_PATH "Data_extended/Midd1/disp5.png", "_Midd1.png", ROOT_PATH "Data_extended/Midd1/view1.png", ROOT_PATH "Data_extended/Midd1/view5.png", "_Midd1_bad.png",
	ROOT_PATH "Data_extended/Moebius/disp1.png", ROOT_PATH "Data_extended/Moebius/disp5.png", "_Moebius.png", ROOT_PATH "Data_extended/Moebius/view1.png", ROOT_PATH "Data_extended/Moebius/view5.png", "_Moebius_bad.png",
	ROOT_PATH "Data_extended/Wood1/disp1.png", ROOT_PATH "Data_extended/Wood1/disp5.png", "_Wood1.png", ROOT_PATH "Data_extended/Wood1/view1.png", ROOT_PATH "Data_extended/Wood1/view5.png", "_Wood1_bad.png",	
};

char extendNames[50][256] = {
	"Aloe", "Art", "Baby1", "Baby2", "Baby3", "Books", "Cloth2", "Cloth3",
	"Dolls", "Flowerpots", "Lampshade1",  "Laundry", "Midd1", "Moebius", "Wood1"
};

float TestRoutine_Batch_MiddleburyExtended(float sigma, METHOD bST_type)//test non-occ regions only
{
	int scale=3;
	float err_ave=0;
	for(int i = 0;i < 15;i++)
	{
		int idx=i*6;
		char* gt_name_l = cTestFilePool[idx];
		char* gt_name_r = cTestFilePool[idx+1];
		char* filename_disparity_map = cTestFilePool[idx+2];
		char* filename_left_image = cTestFilePool[idx+3];
		char* filename_right_image = cTestFilePool[idx+4];
		char* filename_bad_image = cTestFilePool[idx+5];
		int max_disparity = CompDepthRange(gt_name_l, scale)+1;
		
		stereo_launch(filename_left_image, filename_right_image, filename_disparity_map, max_disparity, scale, sigma, bST_type);
		float err_non_occ = TestResult_OnePixel_NonOcc(filename_disparity_map, gt_name_l, gt_name_r, scale, filename_bad_image);
		printf("  %s: %.02f%%\n",extendNames[i], 100 * err_non_occ);
		err_ave += err_non_occ * 100;
	}
	
	err_ave /= 15;
	return err_ave;
}


int main(int argc, const char **argv) {
	float error1, error2;
	const char *head = "*****Segment-Tree based Cost Aggregation for Stereo Matching[CVPR2013]*****\n\n";
	printf("%sMethod ST_RAW(error rate):\n",head);
	//check executable file
	std::fstream _file;
	_file.open(RUN_PATH, std::ios::in);
	if(!_file) {
		printf("Cannot find executable file %s, quit.\n", RUN_PATH);
		exit(1);
	} else {
		_file.close();
	}

	error1 = TestRoutine_Batch_MiddleburyStandard(0.1f, ST_RAW);
	error2 = TestRoutine_Batch_MiddleburyExtended(0.1f, ST_RAW);
	printf("Avg. non-occ err in 19 pairs: %.02f%%\n", (4 * error1 + 15 * error2) / 19);

	printf("\nMethod ST_REFINED(error rate):\n");
	error1 = TestRoutine_Batch_MiddleburyStandard(0.05f, ST_REFINED);
	error2 = TestRoutine_Batch_MiddleburyExtended(0.05f, ST_REFINED);
	printf("Avg. non-occ err in 19 pairs: %.02f%%\n", (4 * error1 + 15 * error2) / 19);
	
	return 0;
}