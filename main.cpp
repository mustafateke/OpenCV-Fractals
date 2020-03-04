#include "cv.h"
#include "highgui.h"
#include <math.h> 
#include <stdio.h>
typedef struct { float x, y; } Complex;
//Complex Sayi Yapisi.

int maxIter =50;//maksimum iteration.
Complex z;

Complex complexSquare (Complex c){
	Complex cSq;
	cSq.x = c.x * c.x - c.y * c.y;
	cSq.y = 2 * c.x * c.y;
	return (cSq);
}

int iterate (Complex zInit, int maxIter){
	Complex C;
	Complex z = zInit;
	int cnt = 0;	
/*
 *	Mandelbrot Kümesi
 *	Zn=(Zn-1)^2+C
 *	Burda Z'in ilk degeri Z0 = 0
 *	Julia kümesi elde etmek için
 *	z.x += zInit.x; yerine z.x += C.x; yani sectigniz sabit sayiyi
 *	ekleyin,Y içinde aynýsýný yapýn.
 *	Degisik formullerde Eklenebilir mesela 
 *	Zn=(Zn-1)^3+C gibi
 *	OpenCV'yi resimleri boyamak için kullandým
 *	OpenGL veya baska bir yontem kullanabilirsiniz.
 *	OpenCV'yi http://sourceforge.net/projects/opencvlibrary/
 *	Adresinden indirebilrsiniz.Biraz büyük
 *	Eger Computer Vision ile ilgilenmiyorsanýz
 *	Boyamak için baþka bir yöntem kullanmanýz tavsiye Ederim.
 */
	while ((z.x * z.x + z.y * z.y <= 4.0) && (cnt < maxIter)) {
		z = complexSquare (z);
		z.x += zInit.x;
		z.y += zInit.y;
		cnt++;
	}
	return (cnt);
}

int main(){


	CvSize fractal_image_size ={400,400};
	CvPoint my_point;
	IplImage* fractal = cvCreateImage( fractal_image_size,
		IPL_DEPTH_8U,
		3 );

	int x,y= 0;
	int cnt = 0;
	
	for(double j=-2.0;j<=2;j+=0.01,x=0,y++) {		
		for(double i=-2.0;i<=2;i+=0.01,x++,z.x=i,z.y=j,cnt=0) {
			int color=iterate (z, maxIter);
			my_point.x=x;
			my_point.y=y;
			if(color<5)
				cvCircle(fractal,my_point,1,CV_RGB(color*60,0,0),1);
			else
				if(color<10)
					cvCircle(fractal,my_point,1,CV_RGB(0,color*30,0),1);
				else
					if(color<15)
						cvCircle(fractal,my_point,1,CV_RGB(0,0,color*15),1);
					else 
						if(color<20)
							cvCircle(fractal,my_point,1,CV_RGB(color*16,0,0),1);			
						else
							if (color<30)
								cvCircle(fractal,my_point,1,CV_RGB(color*5,color*8,color*11),1);
							else
								if(color<45)
									cvCircle(fractal,my_point,1,CV_RGB(color*1,color*3,color*4),1);
			
		}
	}

	cvNamedWindow("fractal",1);
	cvShowImage("fractal",fractal);
	printf("test\n");
	cvWaitKey(0);
	
	return 0;
}