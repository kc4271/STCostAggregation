STCostAggregation
=================

This project provides a reference implementation of the following paper:

* Xing Mei, Xun Sun, Weiming Dong, Haitao Wang and Xiaopeng Zhang. Segment-Tree based Cost Aggregation for Stereo Matching, in CVPR 2013.

Project URL: http://xing-mei.net/resource/page/segment-tree.html

The code is written by Yan Kong, please email comments and bug reports to kongyanwork@gmail.com.

How to Run:  
-------------------

* Use CMake to generate the project files.   
* Build the project.  
* Run "STCostAggre" or "STCostAggreTest" in the bin directory.  

Program Description:
-------------------

1.`STCostAggre` - the program which computes the disparity result for a given stereo pair. 

      STCostAggre leftImg rightImg dispImg [maxLevel] [scale] [sigma] [method]
         leftImg/rightImg: the file path of the left/right image
         dispImg: the output disparity file for the left image
         maxLevel: the maximum disparity level (default 60)
         scale: the scaling parameter for image display (default 4)
         sigma: the threshold parameter for the color distance (default 0.1)
         method: the two aggregation methods (0 for ST-1, 1 for ST-2)
  
2.`STCostAggreTest` - the program which tests `STCostAggre` on the Middlebury data sets. Place 
                     this program and `STCostAggre` in the same directory.


LICENSE
-------------------

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
