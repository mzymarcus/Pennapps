# Pennapps

This is the program we built for PennApps Fall 2016; It is called BarrageGame; 

My friends and I form a team of three: 

1. Zhiyu Ma (me); 
2. Ziang Zhao; 
3. Yibo Chen; 

It is similar to a shooting game and it is totally implemented by C++; 

To run the program, just download the picture folder(under path PennApps/BarrageGame/BarrageGame) and "BarrageGame.cpp" (path PennApps/BarrageGame/BarrageGame) to the same directory on your own computer, then compile the program or you can simply run the .exe file we provide under path path PennApps/BarrageGame together with the picture folder;

Hope you like it and enjoy playing the game; 

The original idea for us to design this game is from the online live show. Many funs will post their comments as barrage. Sometimes, there may be gifts to the live show host. In order to attract more audiences to the show and make the show more entertaining, giving some awards to the audiences sounds like a nice idea. 

So we design that, at certain time during the live show, a gift will appear; Each audience can use a virtual rocket to shoot the gift and each bullte hitting the gift will give the audience a certain amount of reward. In the game, random appearing barrage acts like barriers to the audience, which means that the audience will not get award if he hits the barriers. Each barriers will disappear after being shot. 

There are five panels located from the top to the bottom on the game interface: 
  - Stats Panel; 
  - Gift Panel;
  - Barrage Panel;
  - Show Panel; 
  - User Panel; 

Stat panel is for showing some stats for the game. It include the HP value of the gift("gift") and the reward the user currently have("reward"). 

Gift shows up in gift panel and it travels from one end to the other end but not way back. It is only a one-way trip for the gift; We use a car as a symbol of the gift in our game. 

Barrages appear randomly in barrage panel to block the bullet from hitting the gift; 

Live show is still on in the show panel. We use a game live show picture to represent in our game. 

User is able to control the direction and location of the rocket(to aim the gift) in user panel. However, there is a limit range of the panel. User cannot locate the rocket out of the user panel. After aimming, user can press "z" to shoot the bullets. If the gift is shot by the bullet, the HP value of gift decreases and the user will get a certain amount of reward. However, if the bullet hits the barrage, the barrage will disappear, but the user gets no rewards. 

The game ends in three situations: 
  1. The user successfully shoots down the whole gift (the HP value of the gift drops to 0); This is a perfect ending! Consgratulations! At the end of the game, the user will be able to see how much rewards he/she gets. 
  
  2. The user is able to hit the gift for a few times, but not the whole gift. After the gift finishes the journey, the user can see how much rewards he/she gets. 
  
  3. The user is not able to hit gift for even one bullet. After the gift finishes the journey, a "sorry" message will appear; 
