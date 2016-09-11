#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>


#define MAX 1000


int timeShoot = 0; // cycle of shooting
int poiNum; // point number
double speed; // true speed

using namespace std;

class self{
public:
	double selfX; // x;
    double selfY; // y;
    int  dirX; // x direction; 
	int  dirY; // y direction; 
	int money;
	self();
	void move();
	IMAGE img[3];

public:
	void addX(double x){ // move on x
		if((!(selfX <= 10 && x <= 0))&&(!(selfX >= 390 && x > 0)))
		selfX += x;
	} 
	void addY(double y){ // move on y
		if((!(selfY <= 420 && y <= 0))&&(!(selfY >= 630 && y > 0)))
			selfY += y;
	}
}me; 

self::self(){
	dirX = 3;
	dirY = 3;
	money = 0;
	selfX = 200;
	selfY = 610;
    loadimage(&img[0], "picture\\stop.jpg");
    loadimage(&img[1], "picture\\left.jpg");
    loadimage(&img[2], "picture\\right.jpg");
}



class gift{
public:
	gift();
	double X;
	double Y;
	IMAGE img;
	int xc;
	double EnSpeed;
	int life;

	void move(){
		if(X > 450) xc = -1;
		if(X < -50) xc = 0;
		X += xc*EnSpeed;

	}
	void show(){
		setfillcolor(BLACK);
		move(); // move() is a f(x) in show
		if(life > 0){
			putimage(X - 50, Y - 50, &img);
			char str[20];
			//LOGFONT(FW_MEDIUM = 500);
			sprintf_s(str, "gift:  %d  ", life);
      		outtextxy(5, 5, str);
		}
	}
}gift_;

gift::gift(){
	xc  = 1; 
	EnSpeed = 2;
	X = 500;
	Y = 80;
	life = 2000;
	loadimage(&img, "picture\\car.jpg");
}



class point{
public:
	point();
	int type;
	double X;
	double Y;
	IMAGE img;
	int life;
	int num;
	void setPoint(double xx, double yy){
		X = xx;
		Y = yy;
	}
	void pointMove(){
		setlinecolor(BLACK);
        if(type == 1){ 
			fillcircle(X, Y, 10);
			Y -= 20;
			setfillcolor(RGB(rand()%123,rand()%50+40,91));
			fillcircle(X, Y, 10);

			if((life > 0) && (Y - gift_.Y <= 17.5) && (Y - gift_.Y >= 0) && (X - gift_.X <= 45) && (X - gift_.X >= -45)){ // bullet touches gift;
				life = 0;
				setfillcolor(BLACK);
				fillcircle(X, Y, 10);
				gift_.life -= 100; 
				me.money += 10;
			}

		}
		setfillcolor(BLACK);
	}
}poi[15];

point::point()
{
	loadimage(&img, "picture\\point.jpg");
	life = 0;
	type = 1;
}



void self::move(){ 
	
	// dirX == 3, straight; 
	// dirX == 1, left; 
	// dirX == 2, right;

	dirX = 3;
    dirY = 3;
	speed = 6; // normal speed; 
	if(GetAsyncKeyState(VK_SHIFT)&0x8000){
		speed = 2.8; // press shift then you can move more slowly; 
	}

	if(GetAsyncKeyState(0x5a)&0x8000 && timeShoot%3 == 0){ // key-z derection; 
		poi[poiNum].life = 1;
		poi[poiNum].setPoint(me.selfX, me.selfY - 27);
		poiNum++;
		if(poiNum == 15){
			poiNum = 0;
		}
	}

	if(GetAsyncKeyState(VK_UP)&0x8000){
		dirY = 0;
		if(GetAsyncKeyState(VK_RIGHT)&0x8000){
			dirX = 1;
		}
        else if(GetAsyncKeyState(VK_LEFT)&0x8000){
			dirX = 0;
		}
	}
	else if(GetAsyncKeyState(VK_DOWN)&0x8000){
		dirY = 1;
		if(GetAsyncKeyState(VK_RIGHT)&0x8000){
			dirX = 1;
		}
        else if(GetAsyncKeyState(VK_LEFT)&0x8000){
			dirX = 0;
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT)&0x8000){
		dirX = 1;
	}
	else if(GetAsyncKeyState(VK_LEFT)&0x8000){
		dirX = 0;
	}


    solidrectangle(me.selfX-9, me.selfY-18, me.selfX+9, me.selfY+18);


	if(dirX == 3 && dirY == 1){me.addY(speed);}

	if(dirX == 3 && dirY == 0){me.addY(-speed);}

	if(dirX == 1 && dirY == 3){me.addX(speed);}

	if(dirX == 0 && dirY == 3){me.addX(-speed);}

	if(dirX == 1 && dirY == 1){me.addX(0.75*speed); me.addY(0.75*speed);}

	if(dirX == 1 && dirY == 0){me.addX(0.75*speed); me.addY(-0.75*speed);}

	if(dirX == 0 && dirY == 1){me.addX(-0.75*speed); me.addY(0.75*speed);}

	if(dirX == 0 && dirY == 0){me.addX(-0.75*speed); me.addY(-0.75*speed);}



	if(dirX == 3){
		putimage(me.selfX-9,me.selfY-18, &img[0]);
	}

	if(dirX == 0){
		putimage(me.selfX-9,me.selfY-18, &img[1]);
	}

	if(dirX == 1){
		putimage(me.selfX-9,me.selfY-18, &img[2]);
	}
    setfillcolor(BLACK);
	fillcircle(me.selfX, me.selfY, 3);
	setfillcolor(BLACK);

	char str[50];
	sprintf_s(str, "rewards:%5d", me.money);
	outtextxy(300, 5, str);
}



class poiOfEn{ // the danmu of enemy
public:
	int type; // if tpye == 0 the point dead
	double X;
	double Y;
	double kx;
	double ky;
	IMAGE img; 
	poiOfEn();
	void setTXY(int t, double x, double y){
		type = t;
		X = x;
		Y = y;
		putimage(X, Y, &img);
		ky = 1;
		kx = (me.selfX - X)/(me.selfY - Y);
		if(Y > me.selfY){
			ky = -1;
			kx = -kx;
		}
	}
	void move(){
		if(type == 0){
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			solidrectangle(X, Y, X+70, Y+15);
		}

		if(type == 1){ 
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			solidrectangle(X, Y, X+70, Y+15);

			X += ((double) (rand()%100))/15.0; // y += 2*1 --marcus
			putimage(X, Y, &img);

			setfillcolor(BLACK);
			setlinecolor(BLACK);
			if(X < 0 || X > 400 || Y < 0 || Y > 640){
				type = 0;
				setfillcolor(BLACK);
				setlinecolor(BLACK);
				fillcircle(X, Y, 5);
			}
			for(int i = 0; i < 15; i++){
				if((poi[i].life > 0) && (poi[i].Y - Y <= 17.5) && (poi[i].Y - Y >= 0) && (poi[i].X - X <= 70) && (poi[i].X - X >= -10)){ // being killed by bullet;
					poi[i].life = 0;
					setfillcolor(BLACK);
					fillcircle(poi[i].X, poi[i].Y, 20); // deal with my bullet disappearence; 
					solidrectangle(X, Y, X+70, Y+15);

					type = 0; 
				}
			}
		}
	}

}poiE[MAX];

poiOfEn::poiOfEn(){
	loadimage(&img, "picture\\LOL.jpg");
}





class danmu{ // danmu happen system
public:
	int type;
	int time; // point of enemy's time
	int time2; // smallen time
	int num;
	danmu();
	void move(){
		if((num % 55 == 0 && num < 2000)||(num % 55 == 0 && num > 4500)){

			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 120); if(time == MAX) time = 0; //-- marcus
			if((time+rand())%2 == 1) poiE[time++].setTXY(1, 0, 160); if(time == MAX) time = 0;
			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 200); if(time == MAX) time = 0;
		}

		if((num % 37 == 0 && num < 2000)||(num % 37 == 0 && num > 4500)){

			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 120); if(time == MAX) time = 0; //-- marcus
		}



		if(num<9002){
			num++;
			if(num==9002) num=8000;
		}

	}

}dan;

danmu::danmu(){
	num=0;
	time=0;
}

void shoot(){ 
	int i;
	for(i = 0; i < 15; i++){ // my bullet;
		if(poi[i].life == 1){
			poi[i].pointMove();
		}
	} 


	for(i = 0; i < MAX; i++){ // enemy's bullet;
		if(poiE[i].type != 0){
			poiE[i].move();
		}
	}

	timeShoot++;
	if(timeShoot > 100) timeShoot = 0;
}

void classMoveAction()
{
	dan.move();
	gift_.show();
	me.move();
}

void UI(){
	srand((unsigned int) time(NULL));
	initgraph(400, 640);
	IMAGE img[3];
	loadimage(&img[0],"picture\\start.jpg");
	putimage(70, 160, &img[0]);
	for(;;){
		if(	GetAsyncKeyState(VK_CONTROL)&0x8000){ // press control to start; 
			setfillcolor(BLACK);
			solidrectangle(0,0,400,640);
			loadimage(&img[2],"picture\\twitch.jpg");
			putimage(0, 220, &img[2]);
			break;
		}
	}
}

void start(){
	poiNum = 0;
}

void End(){
	IMAGE img;
	if(gift_.life <= 0){
		setfillcolor(WHITE); 
		solidrectangle(0,0,400,640);
		settextstyle(20, 10, _T("TimesNewRoman"));
		char str[100], str1[100];
		sprintf_s(str, "Congratulations! You get all the money!");
		sprintf_s(str1, "You have got:  %d  ", me.money);
		outtextxy(0, 300, str);
		outtextxy(0, 320, str1);
	}

	else if(me.money == 0){
		setfillcolor(WHITE); 
		solidrectangle(0,0,400,640);
		settextstyle(20, 10, _T("TimesNewRoman"));
		char str[100], str1[100];
		sprintf_s(str, "Sorry! You have not got any");
		sprintf_s(str1, "money, please have another try!");
		outtextxy(0, 300, str);
		outtextxy(0, 320, str1);

	}
	else{
		setfillcolor(WHITE); 
		solidrectangle(0,0,400,640);
		settextstyle(20, 10, _T("TimesNewRoman"));
		char str[100], str1[100];
		sprintf_s(str, "Good-job! Here is the money you");
		sprintf_s(str1, "got: money:  %d  ", me.money);
		outtextxy(0, 300, str);
		outtextxy(0, 320, str1);
	}
	Sleep(5000);

}

int main(){
	start();
    UI();

	for(;;){
		if(gift_.life <= 0 || gift_.X < -50){
			End();
			break;
		}

		shoot();
		classMoveAction();
		IMAGE img;
		loadimage(&img,"picture\\twitch.jpg");
		setfillcolor(BLACK);
		putimage(0, 220, &img);
		Sleep(17);
	}

	Sleep(3000);
	return 0;
}
