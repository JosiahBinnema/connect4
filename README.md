# Josiah's connect 4 bot  
### Description:
A simple connect 4 bot that makes use of the minimax approach to try to beat you. The UI is just a console, and there is no user input verification, so if you enter anything but an integer, your game is done. 

## User instructions:
The .exe file should be the most recent working version. Your computer will warn you a million times about downloading a random .exe (rightly so), so you can also download the code, and play around with it yourself.

Only enter integers into the program

Choose an AI level  
0 - Play versus another person
1 - Play versus my first attempt at intelligence   
2 - Play versus my second attempt at intelligence   
3+ - Play versus a bot that searches future moves and tries to choose the best. The bot's search depth is equal to its level. Exceeding level 8 will make the game run slowly. 

The game will restart whenever a player wins, or there is a draw. The only way to choose a different AI level is to restart the program from the start. Good luck!



---
This is my best attempt at a connect 4 ai (just for fun). I decided to stay away from any tutorials, because I wanted to try to figure out the problems myself. I did look at the wikipedia entry for minimax though, just to make sure I was heading in the right direction


This is a work in progress, whenever I have spare time. ~~I plan to implement the AI by evauating every position, then choosing the best path
Ideally I'll be able to implement Alpha-beta pruning first,~~ then I'll move on to searching good moves first, then I'll ensure it remembers positions so it doesn't reevaluate the same position twice during one search.     

This is also my first project where I will be actively using Git branching/merging/rebasing, so that will be an excellent learning opportunity!        

Likely I won't get a lot of this done, but if I can make an AI that uses alpha beta pruning and can beat me in connect 4. I'll call that a *mad* win.           
I did it! The AI is a good challenge, and something I can be proud of. I still want to improve on it because there are such mad performance gains available.


---
### Journal of the mission:  
June 8, 2021 - The AI is born. It evaluates at a depth of 0.5 and only stands a chance if it goes first.    
  
June 12 - Wow, I really messed up. My old evaluation simply tried to pick the best move. I was trying to base the value of the position off of the value of the best move. However this really doesn't work. It doesn't allow you to accurately analyze future board states with minimax because it doesn't take opponent's moves into account. I had to do a rewrite basically everything I'd done for the AI logic.     
	I had some really grandios ideas with boolean arrays representing the 69 possible ways to connect 4, then only evaluating the ones that were still possibilities, but I realized it was going to be more computationally heavy to keep track of that than it was to just calculate all of the states. The only bit of optimization I did for this was to keep track of the highest column, and not bother with horizontals above that. (I think this is worth it) and also the vertical evaluation stops intelligently. All diagonals almost always required evaluation, so I just always evaluate all of them.    
	
June 15 - Talk about a sprint! I made a whole new evaluate position function today. I'm busy with other things in life, but maybe by the end of the week I'll be able to plug this into my minimax, then we're good to go! I also did my first PR with conflicts.

June 17 - I got my minimax stuff working, but it's super weird when it gets to the isWin() function, I removed that base case, and now it works fine, but doesn't know the game ends when someone gets 4. It'll let you get connect4 if it is guarenteed it next turn *facepalm*

June 19 - rewrote the isWin() function so that it goes after the move is played, and now everything works great. Just adding like 6 comparisons per evaluation though...

June 20 - I added alpha beta pruning in like 5 minutes and search times are down enough to reasonably search to depth 8 (607815 microseconds for first move). I'm halting development on this project in favor of some other things I have to do, but I might revisit it

### TO DO:
- [X] Minimax Algorithm implementation
- [X] Alpha-Beta Pruning
- [ ] Evaluate "best" moves first. I could just search from middle-out, and that would save a ton of search time when combined with alpha-beta pruning
- [ ] Create a reference table to make sure we don't evaluate the same thing twice. This would give massive time savings because you end up double/triple or more evaluating positions because connect 4 is like that...
- [ ] Multi-threading would give me a massive boost in performance, but I have a class on that next semester, so I'll likely do that after.
- [ ] Small code optimizations like removing a lot of unnecessary faff in the functions, and adding a darn constructor to the Board class... I also think it would be fun to have an option to have two AI play against each other. Then you could have a little screen saver of something you wrote :)
- [ ] smarter Main function to allow users to choose their AI level again, and other stuff like that. 
- [ ] maybe a better GUI than a blank black box



