#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>


#define MAX 1000


//all

int timeShoot = 0; //cycle of shooting
int poiNum[3]; //point number
double speed; //true speed

using namespace std;

class self{
public:
        double selfX; // x;
        double selfY; // y;
        int  dirX; // x direction; 
		int  dirY; // y direction; 
		int life;
		int bomb; 
		self();
		void move();
		IMAGE img[3];

public:
		void addX(double x){ // move on x
			 if((!(selfX <= 10 && x <= 0))&&(!(selfX >= 390 && x > 0)))
			 selfX += x;
		} 
		void addY(double y){ // move on y
			 if((!(selfY <= 10 && y <= 0))&&(!(selfY >= 630 && y > 0)))
			 selfY += y;
		}
}me;

self::self(){
	dirX = 3;
	dirY = 3;
	life = 3;
	bomb = 3;
	selfX = 200;
	selfY = 610;
    loadimage(&img[0], "picture\\stop.jpg");
    loadimage(&img[1], "picture\\left.jpg");
    loadimage(&img[2], "picture\\right.jpg");
}


class bomb{
public:
	bomb();
	int life;
	double Y;
	void show(){
		setlinecolor(BLACK);
		line(0, Y, 400, Y);
		Y -= 20; // move speed

		setlinecolor(RGB(rand()%123,rand()%50 + 40, 91));
		line(0, Y, 400, Y);
		if(Y < 0){
			life = 0;
			Y = 670;
		}
	}
}bb;

bomb::bomb(){
	life = 0;
	Y = 670;
}


class gift{
public:
	gift();
	double X;
	double Y;
	IMAGE img;
	int xc;
	// int yc; -- marcus
	double EnSpeed;
	int life;
	void move(){
		if(X > 350) xc=-1;
		// if(Y > 200) yc=-1; --marcus
		if(X < 50) xc=1;
		//if(Y < 50) yc=1; -- marcus
		X += xc*EnSpeed;
		// Y += yc*EnSpeed; -- marcus

		if((X - me.selfX)*(X - me.selfX) + (Y - me.selfY)*(Y - me.selfY) < 3600){ // touching the enemy will die;
			me.life--;
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillcircle(me.selfX, me.selfY, 50); // if touched with enemy, me will be filled within a circle; 
			me.selfX = 200;
			me.selfY = 630;
			bb.life = 1; // activate aoe; 
		}
	}
	void show(){
		setfillcolor(BLACK);
		solidrectangle(X - 50, Y - 50, X + 50, Y + 50);
		move(); // move() is a f(x) in show
		if(life > 0){
			putimage(X - 50, Y - 50, &img);
			char str[20];
			sprintf_s(str, "enemy:  %d   ", life);
      		outtextxy(5, 5, str);
		}
	}
}gift_;

gift::gift(){
	xc  = 1; // yc -- marcus
	EnSpeed = 1;
	X = 200;
	Y = 50;
	life = 2500;
	loadimage(&img, "picture\\enemy.jpg");
}

// smallEn can be used as small gifts coming out together with big gift; 
/* class smallEn{ // a small enemy
public:
	int X;
	int Y;
	int dir; // direction of small enemy
	smallEn();
	int life;
	IMAGE img;
	void set()
	{
		life = 400;
		X = 410;
		Y = 220;
		dir = 1;
	}
	void show()
	{
		setfillcolor(BLACK);
		setlinecolor(BLACK);
		fillcircle(X, Y, 25);
		X -= dir*3;
		if(X < 0){
			dir = -dir;
			X = 1;
		}
		if(X > 400){
			dir = -dir;
			X = 399;
		}
		putimage(X-10,Y-10,&img);
	}
}smallen[4];

smallEn::smallEn()
{
	loadimage(&img, "picture\\smallenemy.jpg");
}
*/ 


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
        if(type == 1){ // main bullet; 
			fillcircle(X, Y, 10);
			Y -= 20;
			setfillcolor(RGB(rand()%123,rand()%50+40,91));
			fillcircle(X, Y, 10);

			if((gift_.X - X)*(gift_.X - X)+(gift_.Y - Y)*(gift_.Y - Y) <= 3600){
				life = 0;
				setfillcolor(BLACK);
				fillcircle(X, Y, 20);
				gift_.life -= 100; 
			}

			//int i;
			/* for(i = 0; i < 4; i++){ // only 4 smallen[]; 
				if((smallen[i].X - X)*(smallen[i].X - X)+(smallen[i].Y - Y)*(smallen[i].Y - Y) <= 900){
					life=0;
					setfillcolor(BLACK);
					fillcircle(X, Y, 20);
					smallen[i].life -= 5;
					setfillcolor(BLACK);
					setlinecolor(BLACK);
					fillcircle(smallen[i].X, smallen[i].Y, 35);
					if(smallen[i].life <= 0){
						smallen[i].X = 410;
						smallen[i].Y = 220;
					}

				}
			} */ // marcus
		}

		if(type == 2){ // small bullet; 
			solidrectangle(X-3, Y-15, X+3, Y+26);
			Y -= 30;
			if(!(GetAsyncKeyState(VK_SHIFT)&0x8000)){
				if(X < me.selfX) X-=3;
				else X+=3;
			}
			putimage(X-3, Y-3, &img);
			if((gift_.X - X)*(gift_.X - X)+(gift_.Y - Y)*(gift_.Y - Y) <= 3600){
				life = 0; 
				solidrectangle(X-3,Y-15,X+3,Y+60);
				gift_.life -= 5;
			}


			//int i;
			/* for(i=0;i<4;i++){
				if((smallen[i].X - X)*(smallen[i].X - X)+(smallen[i].Y - Y)*(smallen[i].Y - Y) <= 900){
					life=0;
					setfillcolor(BLACK);
					solidrectangle(X-3, Y-15, X+3, Y+60);
					smallen[i].life -= 5;
					setfillcolor(BLACK);
					setlinecolor(BLACK);
					fillcircle(smallen[i].X, smallen[i].Y, 35);
					if(smallen[i].life <= 0){
						smallen[i].X = 410;
						smallen[i].Y = 220;
					}
				}
			} */ // -- marcus
		}
		setfillcolor(BLACK);
		setlinecolor(WHITE);
	}
}poi[15],poi2[30],poi3[30];

point::point()
{
	loadimage(&img, "picture\\point.jpg");
	life = 0;
	type = 1;
}


class yinyang
{
public:
	yinyang();
	double angle;
	int R;
	IMAGE img;
	double X1;
	double Y;
	double X2;
	void move(int x, int y){
        setfillcolor(BLACK);
        solidrectangle(X1-7, Y-7, X1+8, Y+8);
		solidrectangle(X2-7, Y-7, X2+8, Y+8);


		X1 = x - R*cos(angle);
		X2 = x + R*cos(angle);
		Y = y - R*sin(angle) - 10;
		putimage(X1-7, Y-7, &img);
		putimage(X2-7, Y-7, &img);
		//setfillcolor(WHITE);
		//solidrectangle(X1-7,Y-7,X1+8,Y+8);
		//solidrectangle(X2-7,Y-7,X2+8,Y+8);
		if(!(GetAsyncKeyState(VK_SHIFT)&0x8000)){
			angle -= 0.3;
		}
		if(GetAsyncKeyState(VK_SHIFT)&0x8000){
			angle += 0.3;
		}
		if(angle > 1.2 && GetAsyncKeyState(VK_SHIFT)&0x8000){
			angle = 1.2;
		}
		if((angle > 1.2 || angle < 0) && !(GetAsyncKeyState(VK_SHIFT)&0x8000)){
			angle = 0;
		}
		if(GetAsyncKeyState(0x5a)&0x8000 && timeShoot%3 == 0){ // key-z detect; 
			poi2[poiNum[1]].life = 1; // ?
			poi2[poiNum[1]].setPoint(X1, Y-33);
			poi3[poiNum[2]].life = 1;
			poi3[poiNum[2]].setPoint(X2, Y-33);
			poiNum[1]++;
			poiNum[2]++;
			if(poiNum[1] == 15){
				poiNum[1] = 0;
			}
			if(poiNum[2] == 15){
				poiNum[2] = 0;
			}
		}
	}
}yinyang;

yinyang::yinyang()
{
	angle = 0;
	R = 30;
	loadimage(&img, "picture\\yinyang.jpg");
}


void self::move(){
	dirX = 3;
    dirY = 3;
	speed = 6; // normal speed; 
	if(GetAsyncKeyState(VK_SHIFT)&0x8000){
		speed = 2.8; // press shift then you can move more slowly; 
	}

	if(GetAsyncKeyState(0x5a)&0x8000 && timeShoot%3 == 0){ // key-z derection; 
		poi[poiNum[0]].life = 1;
		poi[poiNum[0]].setPoint(me.selfX, me.selfY - 27);
		poiNum[0]++;
		if(poiNum[0] == 15){
			poiNum[0] = 0;
		}
	}

	if(GetAsyncKeyState(0x58)&0x8000){ // key-x detection; 
		if(me.bomb != 0 && bb.life == 0){
			bb.life = 1;
			me.bomb--;
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
		if(GetAsyncKeyState(VK_RIGHT)&0x8000)
			dirX = 1;
        else if(GetAsyncKeyState(VK_LEFT)&0x8000)
			dirX = 0;
	}
	else if(GetAsyncKeyState(VK_RIGHT)&0x8000){
		dirX = 1;
	}
	else if(GetAsyncKeyState(VK_LEFT)&0x8000){
		dirX = 0;
	}


    solidrectangle(me.selfX-9, me.selfY-18, me.selfX+9, me.selfY+18);

	// dirX == 3, straight; 
	// dirX == 1, left; 
	// dirX == 2, right;

	if(dirX == 3 && dirY == 1){me.addY(speed);}

	if(dirX == 3 && dirY == 0){me.addY(-speed);}

	if(dirX == 1 && dirY == 3){me.addX(speed);}

	if(dirX == 0 && dirY == 3){me.addX(-speed);}

	if(dirX == 1 && dirY == 1){me.addX(0.78*speed); me.addY(0.78*speed);}

	if(dirX == 1 && dirY == 0){me.addX(0.78*speed); me.addY(-0.78*speed);}

	if(dirX == 0 && dirY == 1){me.addX(-0.78*speed); me.addY(0.78*speed);}

	if(dirX == 0 && dirY == 0){me.addX(-0.78*speed); me.addY(-0.78*speed);}



	if(dirX == 3){
		putimage(me.selfX-9,me.selfY-18, &img[0]);
	}

	if(dirX == 0){
		putimage(me.selfX-9,me.selfY-18, &img[1]);
	}

	if(dirX == 1){
		putimage(me.selfX-9,me.selfY-18, &img[2]);
	}
    setfillcolor(WHITE);
	fillcircle(me.selfX, me.selfY, 3);
	setfillcolor(BLACK);

	char str[20];
	sprintf_s(str, "life:%2d  bomb:%2d ", me.life, me.bomb);
	outtextxy(300, 10, str);
}



class poiOfEn{ // the danmu of enemy
public:
	int type; // if tpye == 0 the point dead
	int time; // time of the point in the game
	double X;
	double Y;
	double kx;
	double ky;
	void setTXY(int t, double x, double y){
		type = t;
		X = x;
		Y = y;
		ky = 1;
		kx = (me.selfX - X)/(me.selfY - Y);
		if(Y > me.selfY){
			ky = -1;
			kx = -kx;
		}
	}
	void move(){
		if((X - me.selfX)*(X - me.selfX) + (Y - me.selfY)*(Y - me.selfY) < 44){
			me.life--;
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillcircle(me.selfX, me.selfY, 50);
			me.selfX = 200;
			me.selfY = 630;
			bb.life = 1;
		} // me gets injured; 

		if(bb.Y - Y < 20) type = 0; // aoe damage;

		if(type == 0){
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillcircle(X, Y, 5);
		}

		if(type == 1){ // the first kind of danmu; 
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillcircle(X, Y, 5);
			X += ((double) (rand()%100))/15.0; // y += 2*1 --marcus
			setfillcolor(RED);
			setlinecolor(WHITE);
			fillcircle(X, Y, 4);
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			if(X < 0 || X > 400 || Y < 0 || Y > 640){
				type = 0;
				setfillcolor(BLACK);
				setlinecolor(BLACK);
				fillcircle(X, Y, 5);
			}
			for(int i = 0; i < 15; i++){
				if(poi[i].life > 0 && (poi[i].X - X)*(poi[i].X - X)+(poi[i].Y - Y)*(poi[i].Y - Y) <= 225){
					poi[i].life = 0;
					setfillcolor(BLACK);
					fillcircle(poi[i].X, poi[i].Y, 20); // deal with my bullet disappearence; 

					type = 0; 
					setfillcolor(BLACK);
					setlinecolor(BLACK);
					fillcircle(X, Y, 5);
				}
			}

			for(int i = 0; i < 30; i++){
				if(poi2[i].life > 0 && (poi2[i].X - X)*(poi2[i].X - X)+(poi2[i].Y - Y)*(poi2[i].Y - Y) <= 225){
					poi2[i].life = 0;
					setfillcolor(BLACK);
					solidrectangle(poi2[i].X-3, poi2[i].Y-15, poi2[i].X+3, poi2[i].Y+60); // deal with my bullet disappearence; 

					type = 0; 
					setfillcolor(BLACK);
					setlinecolor(BLACK);
					fillcircle(X, Y, 5);
				}
			}

			for(int i = 0; i < 30; i++){
				if(poi3[i].life > 0 && (poi3[i].X - X)*(poi3[i].X - X)+(poi3[i].Y - Y)*(poi3[i].Y - Y) <= 225){
					poi3[i].life = 0;
					setfillcolor(BLACK);
					solidrectangle(poi2[i].X-3, poi2[i].Y-15, poi2[i].X+3, poi2[i].Y+60); // deal with my bullet disappearence; 

					type = 0; 
					setfillcolor(BLACK);
					setlinecolor(BLACK);
					fillcircle(X, Y, 5);
				}
			}
		}


    	if(type == 2){ // the second kind of danmu; 
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillcircle(X, Y, 5);
			X += 3*kx;
			Y += 3*ky;
			setfillcolor(WHITE);
			fillcircle(X, Y, 4);
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			if(X < 0 || X > 400 || Y < 0 || Y > 640){
				type = 0;
				setfillcolor(BLACK);
				setlinecolor(BLACK);
				fillcircle(X, Y, 5);
			}
		}
	}

}poiE[MAX];





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
			if((time+rand())%2 == 1) poiE[time++].setTXY(1, 0, 130); if(time == MAX) time = 0;
			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 140); if(time == MAX) time = 0;
			if((time+rand())%2 == 1) poiE[time++].setTXY(1, 0, 150); if(time == MAX) time = 0;
			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 160); if(time == MAX) time = 0;
			if((time+rand())%2 == 1) poiE[time++].setTXY(1, 0, 170); if(time == MAX) time = 0;
			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 180); if(time == MAX) time = 0;
			if((time+rand())%2 == 1) poiE[time++].setTXY(1, 0, 190); if(time == MAX) time = 0;
			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 200); if(time == MAX) time = 0;
			if((time+rand())%2 == 1) poiE[time++].setTXY(1, 0, 210); if(time == MAX) time = 0;
			if((time+rand())%2 == 0) poiE[time++].setTXY(1, 0, 220); if(time == MAX) time = 0;
		}



		/* if((num%20==0&&num>2000&&num<4000)||(num%20==0&&num>8000))
		{
			poiE[time++].setTXY(2, gift_.X+150, gift_.Y+30); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X+120, gift_.Y+40); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X+90, gift_.Y+45); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X+60, gift_.Y+52); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X+30, gift_.Y+54); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X, gift_.Y+55); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X-30, gift_.Y+54); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X-60, gift_.Y+52); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X-90, gift_.Y+45); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X-120, gift_.Y+40); if(time == MAX) time = 0;
			poiE[time++].setTXY(2, gift_.X-150, gift_.Y+30); if(time == MAX) time = 0;
		} */ // --marcus

		//int i;



		/*if(num%1000 == 0 && num > 3999){
			smallen[time2].set();
			time2++;
			if(time2 == 4) time=0;
		}*/ // -- marcus

		/*if(num%50 == 0)
		for( i= 0; i < 4; i++){
			if(smallen[i].life > 0){
				poiE[time++].setTXY(rand()%2+1,smallen[i].X,smallen[i].Y+55);
				if(time == MAX) time=0;
			}
		}*/ // -- marcus



		if(num<9002){
			num++;
			if(num==9002) num=8000;
		}

	}

}dan;

danmu::danmu(){
	num=0;
	time=0;
	time2=0;
}

void shoot(){ 
	int i;
	if(bb.life == 1){
		bb.show();
	}
	for(i = 0; i < 15; i++){ // my bullet;
		if(poi[i].life == 1) poi[i].pointMove();

		if(poi2[i].life == 1){
			poi2[i].type = 2;

			poi2[i].pointMove();
		}

		if(poi3[i].life == 1){

			poi3[i].type = 2;

			poi3[i].pointMove();
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
	int i;
	dan.move();
	gift_.show();
	//for(i = 0; i < 4; i++){
	//	if(smallen[i].life > 0) smallen[i].show(); -- marcus
	//}
	me.move();
	yinyang.move(me.selfX, me.selfY);
}

void UI()
{
	srand((unsigned int) time(NULL));
	initgraph(400, 640);
	setlinecolor(WHITE);
	setfillcolor(BLACK);
		IMAGE img[2];
	loadimage(&img[0],"picture\\start.jpg");
	loadimage(&img[1],"picture\\help.jpg");
	putimage(0,0, &img[1]);
	putimage(280,570, &img[0]);
	for(;;)
	{
		if(	GetAsyncKeyState(0x5a)&0x8000)
		{
			solidrectangle(0,0,400,640);
			break;
		}
	}

}

void start()
{
	poiNum[0]=0;
    poiNum[1]=0;
	poiNum[2]=0;
}

void End()
{
	IMAGE img;
	if(gift_.life < 0)
	{

		loadimage(&img, "picture\\win.jpg");
		putimage(0,300, &img);
	}

	else
	{
		loadimage(&img, "picture\\lose.jpg");
		putimage(0,300, &img);
	}
	Sleep(5000);

}

int main(){
	start();
    UI();

	for(;;){
		if(gift_.life < 0 || me.life < 0){
			End();
			break;
		}
		shoot();
		classMoveAction();
		
		Sleep(1);
	}
	Sleep(3000);
	return 0;
}
